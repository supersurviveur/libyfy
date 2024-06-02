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
/// @brief Log a trace message with the given line and file
#define TRACE_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_TRACE, line, file, true, format, ##__VA_ARGS__)
/// @brief Log a trace message with the given line and file without a newline
#define TRACE_NO_NL_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_TRACE, line, file, false, format, ##__VA_ARGS__)
/// @brief Log a trace message
#define TRACE(format, ...) TRACE_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log a trace message without a newline
#define TRACE_NO_NL(format, ...) \
    TRACE_NO_NL_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
#else
/// @brief Log a trace message with the given line and file
#define TRACE_AT(line, file, format, ...)
/// @brief Log a trace message with the given line and file without a newline
#define TRACE_NO_NL_AT(line, file, format, ...)
/// @brief Log a trace message
#define TRACE(format, ...)
/// @brief Log a trace message without a newline
#define TRACE_NO_NL(format, ...)
#endif

#if defined(LOG_DEBUG) || defined(LOG_TRACE)
/// @brief Log a debug message with the given line and file
#define DEBUG_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_DEBUG, line, file, true, format, ##__VA_ARGS__)
/// @brief Log a debug message with the given line and file without a newline
#define DEBUG_NO_NL_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_DEBUG, line, file, false, format, ##__VA_ARGS__)
/// @brief Log a debug message
#define DEBUG(format, ...) DEBUG_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log a debug message without a newline
#define DEBUG_NO_NL(format, ...) \
    DEBUG_NO_NL_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
#else
/// @brief Log a debug message with the given line and file
#define DEBUG_AT(line, file, format, ...)
/// @brief Log a debug message with the given line and file without a newline
#define DEBUG_NO_NL_AT(line, file, format, ...)
/// @brief Log a debug message
#define DEBUG(format, ...)
/// @brief Log a debug message without a newline
#define DEBUG_NO_NL(format, ...)
#endif
/// @brief Log an error message with the given line and file
#define INFO_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_INFO, line, file, true, format, ##__VA_ARGS__)
/// @brief Log an info message with the given line and file without a newline
#define INFO_NO_NL_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_INFO, line, file, false, format, ##__VA_ARGS__)
/// @brief Log an info message
#define INFO(format, ...) INFO_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log an info message without a newline
#define INFO_NO_NL(format, ...) \
    INFO_NO_NL_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log a warn message with the given line and file
#define WARN_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_WARN, line, file, true, format, ##__VA_ARGS__)
/// @brief Log a warn message with the given line and file without a newline
#define WARN_NO_NL_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_WARN, line, file, false, format, ##__VA_ARGS__)
/// @brief Log a warn message
#define WARN(format, ...) WARN_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log a warn message without a newline
#define WARN_NO_NL(format, ...) \
    WARN_NO_NL_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log an error message with the given line and file
#define ERROR_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_ERROR, line, file, true, format, ##__VA_ARGS__)
/// @brief Log an error message with the given line and file without a newline
#define ERROR_NO_NL_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_ERROR, line, file, false, format, ##__VA_ARGS__)
/// @brief Log an error message
#define ERROR(format, ...) ERROR_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log an error message without a newline
#define ERROR_NO_NL(format, ...) \
    ERROR_NO_NL_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log a fatal message with the given line and file
#define FATAL_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_FATAL, line, file, true, format, ##__VA_ARGS__)
/// @brief Log a fatal message with the given line and file without a newline
#define FATAL_NO_NL_AT(line, file, format, ...) \
    _log_msg(LOG_LEVEL_FATAL, line, file, false, format, ##__VA_ARGS__)
/// @brief Log a fatal message
#define FATAL(format, ...) FATAL_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)
/// @brief Log a fatal message without a newline
#define FATAL_NO_NL(format, ...) \
    FATAL_NO_NL_AT(__LINE__, __FILE__, format, ##__VA_ARGS__)

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
