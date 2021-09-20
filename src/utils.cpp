#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int get_win_width()
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

int get_opt_int(int *num)
{
    char *p;

    *num = (int)strtol(optarg, &p, 10);
    return (!*p);
}
