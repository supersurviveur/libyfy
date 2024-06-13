# Libyfy

This is my small library of C data structures, algorithms, and utilities.

## Data Structures
### Vector
```c
#define VECTOR_TYPE int
#define VECTOR_NAME my_vector // Optional, default to the type name
#include "structures/vector.h"

Vec_type vec_type_create();
void vec_type_free(Vec_type *vec);
void vec_type_push(Vec_type *vec, type value);
type vec_type_pop(Vec_type *vec);
type vec_type_pop_at(Vec_type *vec, size_t index);
void vec_type_print(Vec_type *vec, bool beautify, void (*print)(const type *));
void vec_type_print2d(void *vec, bool beautify, void (*print)(const type *)
bool vec_type_contains(Vec_type *vec, type value);
int64_t vec_type_index_of(Vec_type *vec, type value);
void vec_type_concat(Vec_type *vec1, Vec_type *vec2);
void vec_type_map(Vec_type *vec, void (*map)(type *));
void vec_type_quicksort(Vec_type *vec, int (*compare)(const type *, const type *));
```

### HashTable
```c
#define KEY_TYPE int
#define VALUE_TYPE float
#define HASHMAP_NAME my_name // Optional, default to keyType_valueType
#include "structures/hashmap.h"

HashMap_type hashmap_type_create(
    uint32_t (*hash)(keyType),
    bool (*equals)(keyType, keyType));
void hashmap_type_free(HashMap_type *hashmap);
void hashmap_type_set(HashMap_type *hashmap, keyType key, valueType value);
valueType *hashmap_type_get(HashMap_type *hashmap, keyType key);
bool hashmap_type_contains(HashMap_type *hashmap, keyType key);
void hashmap_type_delete(HashMap_type *hashmap, keyType key);
```

### LinkedList
```c
// TODO type templating
```

### Heap
```c
MinHeap heap_create(type);
void heap_free(MinHeap *heap);
void heap_push(MinHeap *heap, int64_t priority, type value);
void heap_pop(MinHeap *heap, void *value);
```

### BinaryTree
```c
BinaryTree *binarytree_create(type value);
void binarytree_free(BinaryTree *node);
int64_t binarytree_height(BinaryTree *tree);
void print_binarytree(BinaryTree *tree, void (*print)(void *), uint8_t width);
```


## Utilities
### Logging
```c
TIME_START(1);
TRACE("Hello from main");
DEBUG("This is a debug message");
INFO("Hello from main");
WARN("This is a warn");
ERROR("This is an error");
TIME_END(1);
PANIC("This is a panic");
```
Variants with `NO_NL` are also available to avoid printing a newline at the end.
`TRACE` and `DEBUG` only print if `-DLOG_DEBUG` or `-DLOG_TRACE` is passed.

### Ansi Colors
Some terminal colors are defined for easy use.

### Types
Usefull types are redefined in a more modern way (`u8`, `i64`, `f32`, ...).