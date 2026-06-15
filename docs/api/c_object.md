# c_object

[Back to API reference](README.md)

## Header

`#include <ext/c_object.h>`

## Overview

Provides C-only object-lifetime helpers built around a small header placed
before the user object. The macros create typed C structs with matching
initializer/finalizer functions and register allocated objects in a scope list
so they can be finalized automatically when leaving a safe scope.

## Key APIs

- `object_base` stores per-object `context` and `finalize` callback data.
- `ext_create_object(type)` creates a typed object and registers it in the
  current safe scope.
- `ext_create_object_ex(type, context)` does the same while passing a caller
  context pointer to the initializer.
- `ext_delete_object(object)` unregisters, finalizes, frees, and nulls an object
  pointer.
- `ext_safe_scope({ ... })` creates a scope context for automatic cleanup.
- `ext_begin_safe(signature)` and `ext_end_safe()` wrap an entire function body
  in a safe scope.
- `ext_safe_fn(ret, prototype, body)` defines a `safe_` prefixed helper function
  that owns a safe scope.
- `ext_invoke_safe_fn(fn, ...)` invokes `safe_fn(...)` and registers its returned
  object in the current safe scope.
- `ext_return_safe(value)` finalizes all objects in the scope before returning.
- `ext_return_safe_object(object)` returns one object to the caller and finalizes
  the other objects in the current scope.
- `ext_decl_object_type(type, initializer, finalizer, members)` declares a C
  object type plus `type_initialize` and `type_finalize` functions.
- `ext_begin_object_type(type)` and `ext_end_object_type(...)` provide the split
  form for declaring a type.

## Custom Allocation

Define these macros before including `<ext/c_object.h>` to override allocation
and scope-entry storage:

- `ext_alloc_object_base(object_size, context)`
- `ext_free_object_base(object, context)`
- `alloc_scope_entry(size)`
- `free_scope_entry(entry)`

The test suite uses these hooks to count allocations and verify that safe scopes
release every registered object.

## Behavior Notes

- The macros require a safe scope variable named `__scope_context__`; create
  objects only inside `ext_safe_scope`, `ext_begin_safe`/`ext_end_safe`, or
  `ext_safe_fn` bodies.
- `ext_create_object` stores `object_base` immediately before the returned
  object pointer. Use `ext_delete_object`, not raw `free`, for objects created
  by these helpers.
- `ext_return_safe_object(object)` transfers exactly one object out of the safe
  scope. The caller becomes responsible for deleting that returned object in a
  later safe scope or with `ext_delete_object`.
- Initializers receive `(self, context)`. Finalizers receive only `self`.
- This header is C-compatible and is intentionally macro-heavy. Prefer ordinary
  C++ RAII when writing C++ code.

## Requirements

- C compiler or C++ compiler
- `malloc`/`free`, unless allocation hooks are overridden

## Examples

```C
#include <stdlib.h>
#include <ext/c_object.h>

ext_decl_object_type(
    sample_object,
    {
      self->value = context ? *(int *)context : 0;
    },
    {
      self->value = 0;
    },
    {
      int value;
    });

ext_begin_safe(int run_sample(void)) {
  int initial = 42;
  sample_object_ptr object =
      ext_create_object_ex(sample_object, &initial);

  if (object->value == 42)
    ext_return_safe(EXIT_SUCCESS);

  ext_return_safe(EXIT_FAILURE);
}
ext_end_safe();
```

```C
ext_safe_fn(sample_object_ptr, make_sample(int value), {
  sample_object_ptr object = ext_create_object(sample_object);
  object->value = value;
  ext_return_safe_object(object);
});
```
