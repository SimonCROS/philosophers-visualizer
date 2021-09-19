#include <iostream>

#include <unistd.h>
#include <stdio.h>

#include "visualizer.hpp"

using namespace std;

void write_duration(int size, int last, int start, int end, string action)
{
    float diff = size / (float)last;
    int start_pos = start * diff;
    int end_pos = min(size, (int)(end * diff));
    int width = end_pos - start_pos;

    if (!width)
        return ;
    if (!action.compare("time"))
        printf("%-*d", width, start);
    else if (!action.compare("time_bar"))
        printf("⎸%*c", width - 1, ' ');
    else if (!action.compare("empty"))
        printf("%*c", width, ' ');
    else if (!action.compare("is eating"))
        cout << eat(width);
    else if (!action.compare("is sleeping"))
        cout << sleep(width);
    else if (!action.compare("is thinking"))
        cout << think(width);
}

int get_end(map<int, map<int, string> > philos)
{
    map<int, map<int, string> >::iterator philos_itr;
    int end;

    end = 0;
    for (philos_itr = philos.begin(); philos_itr != philos.end(); ++philos_itr)
    {
        map<int, string> actions;

        actions = philos_itr->second;
        end = max(actions.rbegin()->first, end);
    }
    return end;
}

void start(int step)
{
    map<int, map<int, string> > philos;
    int size;
    int end;

    size = get_win_width();

    philos = get_data(stdin);
    if (!philos.size())
        exit(EXIT_FAILURE);

    end = get_end(philos);
    print_rule(size, end, step);
    print_data(size, end, philos);
    print_caption();
}

int	main(int argc, char **argv)
{
    int opt;
    int step;

    step = 25;
    while ((opt = getopt(argc, argv, "hs:")) != EOF)
    {
        switch(opt)
        {
            case 'h':
                print_help(stdout);
                exit(0);
            case 's':
                if (get_opt_int(&step))
                    break;
            default:
                print_help(stderr);
                exit(1);
        }
    }

    start(step);
    return (0);
}
