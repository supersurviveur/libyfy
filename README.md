# Libyfy

This is my small library of C data structures, algorithms, and utilities.

## Data Structures
### Vector

#### Warnings
Vector uses macro to change the variable pointer on push, pop, etc.. So keeping multiple pointers to the same vector is not recommended, as only one will be updated in case of reallocation. If you need to keep multiple pointers to the same vector, you should store the base pointer somewhere, and keep a reference to that, not the vector itself.

### LinkedList

### Heap

### BinaryTree

### HashTable
TODO

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
Variants with `_AT` suffix are also available, to specify the file and line number. `NO_NL` are also available to avoid printing a newline at the end.
`TRACE` and `DEBUG` only print if `-DLOG_DEBUG` or `-DLOG_TRACE` is passed.

### Ansi Colors
Some terminal colors are defined for easy use.