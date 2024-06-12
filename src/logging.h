#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "ansi.h"
#include "stdlib.h"

enum log_levels {
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

/// @brief Log a message
void _log_msg(enum log_levels level, int line, const char *file, bool newline,
              const char *format, ...);

#if defined(LOG_TRACE)
/// @brief Log a trace message
#define TRACE(format, ...) \
    _log_msg(LOG_LEVEL_TRACE, __LINE__, __FILE__, true, format, ##__VA_ARGS__)
/// @brief Log a trace message without a newline
#define TRACE_NO_NL(format, ...) \
    _log_msg(LOG_LEVEL_TRACE, __LINE__, __FILE__, false, format, ##__VA_ARGS__)
#else
/// @brief Log a trace message
#define TRACE(format, ...)
/// @brief Log a trace message without a newline
#define TRACE_NO_NL(format, ...)
#endif

#if defined(LOG_DEBUG) || defined(LOG_TRACE)
/// @brief Log a debug message
#define DEBUG(format, ...) \
    _log_msg(LOG_LEVEL_DEBUG, __LINE__, __FILE__, true, format, ##__VA_ARGS__)
/// @brief Log a debug message without a newline
#define DEBUG_NO_NL(format, ...) \
    _log_msg(LOG_LEVEL_DEBUG, __LINE__, __FILE__, false, format, ##__VA_ARGS__)
#else
/// @brief Log a debug message
#define DEBUG(format, ...)
/// @brief Log a debug message without a newline
#define DEBUG_NO_NL(format, ...)
#endif
/// @brief Log an info message without a newline
#define INFO_NO_NL(format, ...) \
    _log_msg(LOG_LEVEL_INFO, __LINE__, __FILE__, false, format, ##__VA_ARGS__)
/// @brief Log an info message
#define INFO(format, ...) \
    _log_msg(LOG_LEVEL_INFO, __LINE__, __FILE__, true, format, ##__VA_ARGS__)

/// @brief Log a warn message
#define WARN(format, ...) \
    _log_msg(LOG_LEVEL_WARN, __LINE__, __FILE__, true, format, ##__VA_ARGS__)
/// @brief Log a warn message without a newline
#define WARN_NO_NL(format, ...) \
    _log_msg(LOG_LEVEL_WARN, __LINE__, __FILE__, false, format, ##__VA_ARGS__)

/// @brief Log an error message
#define ERROR(format, ...) \
    _log_msg(LOG_LEVEL_ERROR, __LINE__, __FILE__, true, format, ##__VA_ARGS__)
/// @brief Log an error message without a newline
#define ERROR_NO_NL(format, ...) \
    _log_msg(LOG_LEVEL_ERROR, __LINE__, __FILE__, false, format, ##__VA_ARGS__)

/// @brief Log a fatal message
#define FATAL(format, ...) \
    _log_msg(LOG_LEVEL_FATAL, __LINE__, __FILE__, true, format, ##__VA_ARGS__)
/// @brief Log a fatal message without a newline
#define FATAL_NO_NL(format, ...) \
    _log_msg(LOG_LEVEL_FATAL, __LINE__, __FILE__, false, format, ##__VA_ARGS__)

/// @brief Start a clock with the given id
#define TIME_START(id) clock_t _clock_##id = clock();

/// @brief End a clock with the given id, and log the time taken in µs
#define TIME_END(id)                                   \
    _log_msg(LOG_LEVEL_INFO, __LINE__, __FILE__, true, \
             "Time taken for clock " #id ": %dµs",     \
             (clock() - _clock_##id) / (CLOCKS_PER_SEC / 1000000));
/// @brief End a clock with the given id, and log the time taken in ms
#define TIME_END_MS(id)                                \
    _log_msg(LOG_LEVEL_INFO, __LINE__, __FILE__, true, \
             "Time taken for clock " #id ": %.3fms",   \
             ((double)clock() - _clock_##id) / (CLOCKS_PER_SEC / 1000));
/// @brief End a clock with the given id, and log the time taken in s
#define TIME_END_S(id)                                 \
    _log_msg(LOG_LEVEL_INFO, __LINE__, __FILE__, true, \
             "Time taken for clock " #id ": %.3fs",    \
             ((double)clock() - _clock_##id) / (CLOCKS_PER_SEC));
