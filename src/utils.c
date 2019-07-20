/* utils.h: utility functions. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

extern char *progname;

void leave(int status)
{
    exit(status);
}

void warn(const char *fmt, ...)
{
    va_list ap;
    char buf[BUFSIZ];

    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ-1, fmt, ap);
    va_end(ap);

    fprintf(stderr, "%s: %swarning%s: %s.\n", progname, ANSI_YELLOW, ANSI_RESET, buf);
}

void fail(const char *fmt, ...)
{
    va_list ap;
    char buf[BUFSIZ];

    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ-1, fmt, ap);
    va_end(ap);

    fprintf(stderr, "%s: %serror%s: %s.\n",
            progname, ANSI_RED, ANSI_RESET, buf);
    leave(EXIT_FAILURE);
}
