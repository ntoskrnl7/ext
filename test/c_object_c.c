#include <stdio.h>
#include <stdlib.h>

static size_t object_count = 0;

typedef struct object_entry {
  struct object_entry *prev;
  struct object_entry *next;
  void *object;
} object_entry, *object_entry_ptr;

object_entry root = {NULL, NULL, NULL};

void *alloc_object_base_with_trace(size_t object_size, void *context) {
  void *object = malloc(object_size);
  object_entry_ptr ptr = (object_entry_ptr)malloc(sizeof(object_entry));

  object_count++;

  printf("alloc_object(count : %zd) - object : %p, ctx : %p\n", object_count,
         object, context);

  if (ptr) {
    ptr->object = object;

    if (root.next == NULL)
      root.next = &root;

    if (root.prev == NULL)
      root.prev = &root;
    {
      object_entry_ptr prev = root.prev;
      object_entry_ptr next = root.next;
      root.next = ptr;
      next->prev = ptr;

      ptr->prev = &root;
      ptr->next = next;
    }
  }
  return object;
}

void free_object_with_trace(void *object, void *context) {
  object_entry_ptr entry = root.next;
  object_count--;

  printf("free_object(count : %zd) - object : %p, ctx : %p\n", object_count,
         object, context);

  for (; entry == &root; entry = entry->next) {
    if (entry->object == object)
      break;
  }

  if (entry != &root) {
    object_entry_ptr prev = entry->prev;
    object_entry_ptr next = entry->next;
    prev->next = next;
    next->prev = prev;
    free(entry);
  }

  free(object);
}

#define ext_alloc_object_base alloc_object_base_with_trace
#define ext_free_object_base free_object_with_trace
#include <ext/c_object.h>

ext_decl_object_type(
    test_object,
    // Initializer(test_object *self, void *context)
    {
      printf("test_object::initializer(self : %p, context : %p)\n", self,
             context);
      self->value = 100;
    },
    // Finalizer(test_object *self)
    {
      printf("test_object::finalizer(self : %p)\n", self);

      self->value = 0;
    },
    // Member variables.
    {
      int value;
      double value2;
      int value3;
    });

ext_decl_object_type(
    test_object2,
    // Initializer(test_object2 *self, void *context)
    {
      printf("test_object2::initializer(self : %p, context : %p)\n", self,
             context);
      self->value = 2;
    },
    // Finalizer(test_object2 *self)
    {
      printf("test_object2::finalizer(self : %p)\n", self);
      self->value = 0;
    },
    // Member variables.
    {
      int value;
      double value2;
    });

ext_begin_safe(int test_safe_fn(int a, int b)) {
  test_object2_ptr test2 = ext_create_object(test_object2);
  test2->value = 1;

  {
    test_object_ptr obj = ext_create_object(test_object);
    obj->value = 2;
  }

  ext_return_safe(0);

  {
    test_object_ptr obj2 = ext_create_object_ex(test_object, (void *)1234);
    obj2->value = 3;
  }

  {
    test_object_ptr obj3 = ext_create_object(test_object);
    obj3->value = 4;
  }

  ext_return_safe(0);
}
ext_end_safe();

test_object_ptr create_test_object_unsafe() {

  ext_safe_scope({
    test_object_ptr obj = ext_create_object(test_object);
    obj->value = 8;

    test_safe_fn(1, 2);

    {
      test_object_ptr obj2 = ext_create_object_ex(test_object, (void *)16);
      obj2->value = 9;
      ext_return_safe_object(obj2);
    }

    {
      test_object_ptr obj3 = ext_create_object(test_object);
      obj3->value = 10;
    }
  });

  return NULL;
}

ext_safe_fn(test_object_ptr, create_test_object(int value), {
  if (value) {
    test_object2_ptr test2 = ext_create_object(test_object2);
    test2->value = 11;
    {
      test_object_ptr obj = ext_create_object(test_object);
      obj->value = 12;
    }
    {
      test_object_ptr obj2 = ext_create_object(test_object);
      obj2->value = value;
      ext_return_safe_object(obj2);
    }
  }
  {
    test_object_ptr obj3 = ext_create_object(test_object);
    obj3->value = 14;
  }
  ext_return_safe(NULL);
});

// 일반 함수에 ext_safe_scope매크로 사용
int test_c1() {
  ext_safe_scope({
    test_object_ptr obj = ext_create_object(test_object);
    obj->value = 5;
    test_safe_fn(1, 2);
    {
      test_object_ptr obj2 = ext_create_object(test_object);
      obj->value = 6;
    }
    {
      test_object_ptr obj3 = ext_create_object(test_object);
      obj3->value = 7;
    }
  });

  return EXIT_FAILURE;
}

//
// begin_safe/end_safe 매크로를 사용하여 정의한 함수
//

ext_begin_safe(int object_test_c()) {
  test_object2_ptr test2 = ext_create_object(test_object2);
  test2->value = 15;

  {
    test_object_ptr obj = ext_create_object_ex(test_object, (void *)1);
    obj->value = 16;
    {
      test_object_ptr obj2 = ext_create_object(test_object);
      obj2->value = 17;
    }
    ext_delete_object(obj);
  }
  {
    test_object_ptr obj3 = ext_create_object(test_object);
    obj3->value = 18;
  }
  {
    test_object_ptr obj5 =
        (test_object_ptr)ext_invoke_safe_fn(create_test_object, 0);
    if (obj5)
      obj5->value = 19;
    else
      obj5 = (test_object_ptr)ext_invoke_safe_fn(create_test_object, 1);
    {
      test_object_ptr obj6 = create_test_object_unsafe();
      obj6->value = 20;
      ext_delete_object(obj6);
    }
    if (obj5->value == 19)
      ext_return_safe(test_c1());
  }
  {
    test_object_ptr obj7 = ext_create_object(test_object);
    obj7->value = 21;
  }
  ext_return_safe(EXIT_SUCCESS);
}
ext_end_safe();

size_t object_count_c() { return object_count; }