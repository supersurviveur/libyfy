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

/// @brief Check if the assertion is true, if not panic
/// @param V assertion
#define ASSERT(V)                          \
    if (!(V)) {                            \
        PANIC("Assertion failed: %s", #V); \
    }
