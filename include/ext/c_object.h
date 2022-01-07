/**
 * @file c_object.h
 * @author Jung-kang Lee (ntoskrnl7@gmail.com)
 * @brief This module implements c object helper features.
 *
 * @copyright Copyright (c) 2020 C++ Extended template library Authors
 *
 */

#ifndef __EXT_C_OBJECT_H__
#define __EXT_C_OBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#ifndef NULL
#define NULL 0
#endif

typedef struct object_base {
  void *context;
  void (*finalize)(void *);
} object_base, *ext_object_base_ptr;

#ifndef ext_alloc_object_base
static void *ext_alloc_object_base_default(size_t object_size, void *context) {
  (void)context;
  return malloc(object_size);
}
#define ext_alloc_object_base ext_alloc_object_base_default
#endif

#ifndef ext_free_object_base
static void ext_free_object_base_default(void *object, void *context) {
  (void)context;
  free(object);
}
#define ext_free_object_base ext_free_object_base_default
#endif

#ifndef alloc_scope_entry
#define alloc_scope_entry malloc
#endif
#ifndef free_scope_entry
#define free_scope_entry free
#endif

static ext_object_base_ptr ext_get_object_base_by_object(void *object) {
  if (!object)
    return NULL;
  return (ext_object_base_ptr)(((ptrdiff_t)object) - sizeof(object_base));
}

static void *ext_get_object_by_base(ext_object_base_ptr base) {
  if (!base)
    return NULL;
  return (void *)(((ptrdiff_t)base) + sizeof(object_base));
}

static void ext_delete_object_base(ext_object_base_ptr);

//
// scope
//

typedef struct ext_scope_entry {
  void *object;
  struct ext_scope_entry *next;
} * ext_scope_entry_ptr;

typedef struct ext_scope_context {
  struct ext_scope_entry root;
  ext_scope_entry_ptr current;
} * ext_scope_context_ptr;

static void *ext_push_scope_entry(void *object, ext_scope_context_ptr context) {
  ext_scope_entry_ptr ptr =
      (ext_scope_entry_ptr)alloc_scope_entry(sizeof(struct ext_scope_entry));
  if (ptr) {
    ptr->object = object;
    ptr->next = NULL;
  }
  context->current->next = ptr;
  context->current = ptr;
  return object;
}

static void ext_remove_scope_entry(void *object,
                                   ext_scope_context_ptr context) {
  ext_scope_entry_ptr prev = NULL;
  ext_scope_entry_ptr current = context->root.next;
  while (current) {
    if (current->object == object) {
      if (prev) {
        prev->next = current->next;
      }
      free_scope_entry(current);
      break;
    }
    prev = current;
    current = current->next;
  }
}

static void ext_initialize_scope(ext_scope_context_ptr context) {
  context->root.object = NULL;
  context->root.next = NULL;
  context->current = &context->root;
}

static void ext_finalize_scope(ext_scope_context_ptr context) {
  ext_scope_entry_ptr current = context->root.next;
  while (current) {
    ext_scope_entry_ptr prev = current;
    ext_delete_object_base(ext_get_object_base_by_object(current->object));
    current = current->next;
    free_scope_entry(prev);
  }
}

//
// object_base
//

static ext_object_base_ptr
ext_create_object_base(size_t object_size, void *context,
                       void (*initialize)(void *, void *context),
                       void (*finalize)(void *)) {
  ext_object_base_ptr base = (ext_object_base_ptr)ext_alloc_object_base(
      sizeof(object_base) + object_size, context);
  if (base) {
    void *object = (void *)ext_get_object_by_base(base);
    base->finalize = finalize;
    base->context = context;
    initialize(object, context);
  }
  return base;
}

static void ext_delete_object_base(ext_object_base_ptr base) {
  void (*finalize)(void *) = NULL;
  if (!base)
    return;
  finalize = base->finalize;
  if (finalize) {
    void *object = ext_get_object_by_base(base);
    if (object)
      finalize(object);
  }
  ext_free_object_base(base, base->context);
}

#define ext_create_object(_object_type_)                                       \
  ext_create_object_ex(_object_type_, NULL)

#define ext_create_object_ex(_object_type_, context)                           \
  (_object_type_##_ptr) ext_push_scope_entry(                                  \
      ext_get_object_by_base(ext_create_object_base(                           \
          sizeof(_object_type_), context,                                      \
          (void (*)(void *, void *))_object_type_##_initialize,                \
          (void (*)(void *))_object_type_##_finalize)),                        \
      &__scope_context__)

#define ext_delete_object(_object_)                                            \
  ext_remove_scope_entry(_object_, &__scope_context__);                        \
  ext_delete_object_base(ext_get_object_base_by_object(_object_));             \
  _object_ = NULL

//
// ext_begin_safe/ext_end_safe/ext_return_safe macro
//

#define ext_safe_scope(body) ext_begin_scope body ext_end_scope

#define ext_begin_safe(fn) fn ext_begin_scope;

#define ext_end_safe() ext_end_scope;

//
// safe_fn/invoke_safe_fn macro
//

#define ext_safe_fn(ret, fn_proto, body)                                       \
  ret safe_##fn_proto ext_begin_scope body ext_end_scope;

#define ext_invoke_safe_fn(_safe_fn_, ...)                                     \
  ext_push_scope_entry(safe_##_safe_fn_(__VA_ARGS__), &__scope_context__);

// 모든 object를 파괴하고 반환환할때 사용하는 매크로
#define ext_return_safe(r)                                                     \
  { ext_exit_scope return (r); }

// object를 파괴하지 않고 반환할때 사용하는 매크로
#define ext_return_safe_object(_object_)                                       \
  {                                                                            \
    ext_scope_entry_ptr current = &__scope_context__.root;                     \
    while (current) {                                                          \
      if (current->object && current->object != _object_)                      \
        ext_delete_object_base(                                                \
            ext_get_object_base_by_object(current->object));                   \
      current = current->next;                                                 \
    }                                                                          \
    return _object_;                                                           \
  }

//
// scope macros
// ext_begin_scope/ext_end_scope/ext_exit_scope
//

#define ext_exit_scope                                                         \
  { ext_finalize_scope(&__scope_context__); }

#define ext_begin_scope                                                        \
  {                                                                            \
    struct ext_scope_context __scope_context__;                                \
    ext_initialize_scope(&__scope_context__);

#define ext_end_scope                                                          \
  ext_exit_scope                                                               \
  }

//
// object_type macros
//

#define ext_begin_object_type(_type_name_)                                     \
  typedef struct {                                                             \
    struct object_base _base_;

#define ext_end_object_type(_type_name_, _initialize_body_, _finalize_body_)   \
  }                                                                            \
  _type_name_, *_type_name_##_ptr;                                             \
  static void _type_name_##_initialize(_type_name_##_ptr self,                 \
                                       void *context) {                        \
    _initialize_body_                                                          \
  }                                                                            \
  static void _type_name_##_finalize(_type_name_##_ptr self) { _finalize_body_ }

#define ext_decl_object_type(_type_name_, _initializer_, _finalizer_,          \
                             _members_)                                        \
  typedef struct _type_name_ _members_ _type_name_;                            \
  typedef _type_name_ *_type_name_##_ptr;                                      \
  static void _type_name_##_initialize(_type_name_##_ptr self, void *context)  \
      _initializer_ static void _type_name_##_finalize(_type_name_##_ptr self) \
          _finalizer_

#endif // __EXT_C_OBJECT_H__