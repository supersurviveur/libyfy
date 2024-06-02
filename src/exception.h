#pragma once

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

/// @brief Check if the assertion is true, if not panic
/// @param V assertion
#define ASSERT(V)                          \
    if (!(V)) {                            \
        PANIC("Assertion failed: %s", #V); \
    }
