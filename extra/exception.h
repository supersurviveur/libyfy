#ifndef PANIC_H
#define PANIC_H

#include "logging.h"

/// @brief Panic with a message and exit the program
/// @param format message format
/// @param ... message arguments
#define PANIC(format, ...)            \
    {                                 \
        FATAL(format, ##__VA_ARGS__); \
        exit(EXIT_FAILURE);           \
    }

/// @brief Panic with a message and exit the program with a line and file
/// @param line line of the panic
/// @param file file of the panic
/// @param ... message arguments
#define PANIC_AT(line, file, format, ...)            \
    {                                                \
        FATAL_AT(line, file, format, ##__VA_ARGS__); \
        exit(EXIT_FAILURE);                          \
    }

typedef struct {
    char *name;
    char *message;
} Exception;

/// @brief Create an exception
/// @param n name of the exception
/// @param ... message of the exception
#define CREATE_EXCEPTION(n, ...) \
    Exception n = (Exception){.name = #n, .message = __VA_ARGS__ ""};

/// @brief Create an exception in-place
/// @param n name of the exception
/// @param ... message of the exception
#define exception(n, ...) \
    (Exception) { .name = #n, .message = __VA_ARGS__ "" }

/// @brief Create a result type
/// @param T type of the result
#define CREATE_RESULT_TYPE(T) \
    typedef struct {          \
        Exception error;      \
        T value;              \
    } Result_##T;

/// @brief Check if the assertion is true, if not panic
/// @param V assertion
#define ASSERT(V)                          \
    if (!(V)) {                            \
        PANIC("Assertion failed: %s", #V); \
    }

/// @brief Result type
#define Result(T) Result_##T

/// @brief Create a result with a value
/// @param T type of the result
/// @param V value of the result
#define Ok(T, V) \
    (Result(T)) { .value = V, .error = exception(NO_EXCEPTION) }

/// @brief Create a result with an error
/// @param T type of the result
/// @param E error of the result
#define Err(T, E) \
    (Result(T)) { .error = E }

/// @brief Check if the result is an error
#define is_err(R) (R.error.name != exception(NO_EXCEPTION).name)

/// @brief Check if the result is not an error
#define is_ok(R) (R.error.name == exception(NO_EXCEPTION).name)

/// @brief Check if the result is an error with a specific exception
#define is_exception(R, E) (R.error.name == E.name)

/// @brief Unwrap the result, panic if it's an error
/// @param R result
#define unwrap(R)                                            \
    ({                                                       \
        if (is_err(R)) {                                     \
            PANIC("%s - %s", R.error.name, R.error.message); \
        }                                                    \
        R.value;                                             \
    })

/// @brief Unwrap the result, return the default value if it's an error
/// @param R result
/// @param default default value
#define unwrap_or(R, default) (is_err(R) ? default : R.value)

/// @brief Unwrap the result, panic with a custom message if it's an error
/// @param R result
/// @param message custom message
#define except(R, message)                           \
    ({                                               \
        if (is_err(R)) {                             \
            PANIC("%s - %s", R.error.name, message); \
        }                                            \
        R.value;                                     \
    })

#endif  // PANIC_H