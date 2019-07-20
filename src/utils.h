#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef COLORS_ENABLED
/* ANSI escape codes for terminal colors */
# define ANSI_RESET   "\x1b[0m"
# define ANSI_BLACK   "\x1b[30m"
# define ANSI_RED     "\x1b[31m"
# define ANSI_GREEN   "\x1b[32m"
# define ANSI_YELLOW  "\x1b[33m"
# define ANSI_BLUE    "\x1b[34m"
# define ANSI_MAGENTA "\x1b[35m"
# define ANSI_CYAN    "\x1b[36m"
# define ANSI_WHITE   "\x1b[37m"
#else
# define ANSI_RESET   ""
# define ANSI_BLACK   ""
# define ANSI_RED     ""
# define ANSI_GREEN   ""
# define ANSI_YELLOW  ""
# define ANSI_BLUE    ""
# define ANSI_MAGENTA ""
# define ANSI_CYAN    ""
# define ANSI_WHITE   ""
#endif

void leave(int);
void fail(const char *, ...);
void warn(const char *, ...);

#endif /* _UTILS_H_ */
