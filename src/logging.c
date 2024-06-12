#include "logging.h"

const char *log_level_names[] = {"TRACE", "DEBUG", "INFO",
                                 "WARN",  "ERROR", "FATAL"};
const char *log_level_colors[] = {
    FG_RGB(0, 100, 140), GREEN, CYAN,
    FG_RGB(255, 150, 0), RED,   FG_RGB(255, 50, 50)};
const __uint16_t MAX_MESSAGE_SIZE = 1024;

// Return time in format HH:MM:SS:µs
void _get_time(char *t) {
    struct timeval ttime;
    gettimeofday(&ttime, NULL);
    struct tm *time = localtime(&ttime.tv_sec);
    sprintf(t, "%02d:%02d:%02d:%06ld", time->tm_hour, time->tm_min,
            time->tm_sec, ttime.tv_usec);
}

void _log_msg(enum log_levels level, int line, const char *file, bool newline,
              const char *format, ...) {
    // Get the message
    char message[MAX_MESSAGE_SIZE];
    va_list args;
    va_start(args, format);
    vsprintf(message, format, args);
    va_end(args);

    // Get the time
    char time[20];
    _get_time(time);
    // print in the format: file:line [LEVEL] time - message
    printf("%s%s:%d%s %s[%s%s%s] %s%s%s | %s%s", FG_RGB(200, 100, 0), file,
           line, RESET, BOLD, log_level_colors[level], log_level_names[level],
           RESET, CYAN, time, RESET, message, RESET);
    if (newline) {
        printf("\n");
    }
}