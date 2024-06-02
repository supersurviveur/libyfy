#pragma once

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define REVERSE "\033[7m"
#define INVISIBLE "\033[8m"
#define STRIKE "\033[9m"

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

#define CLEAR "\033[2J\033[H"

#define FG_RGB(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"
#define BG_RGB(r, g, b) "\033[48;2;" #r ";" #g ";" #b "m"
