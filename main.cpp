/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:33 by scros             #+#    #+#             */
/*   Updated: 2021/08/02 12:32:42 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <map>

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

using namespace std;

string space(int n)
{
    return string(n, ' ');
}

string eat(int n)
{
    return "\033[48;5;203m" + string(n, ' ') + "\033[0m";
}

string sleep(int n)
{
    return "\033[48;5;039m" + string(n, ' ') + "\033[0m";
}

string think(int n)
{
    return "\033[48;5;077m" + string(n, ' ') + "\033[0m";
}

map<int, map<int, string> > get_data()
{
    int time;
    int philo;
    char actionc[20];
    string action;
    map<int, map<int, string> > philos;

    while (scanf("%d %d %[^\n]\n", &time, &philo, actionc) != EOF)
    {
        action = actionc;
        if (!action.compare("has taken a fork"))
            continue ;
        if (!philos.count(philo))
        {
            map<int, string> actions;
            actions.insert(make_pair(time, action));
            philos.insert(make_pair(philo, actions));
        }
        else
            philos.at(philo).insert(make_pair(time, action));
    }
    return (philos);
}

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

int	main(int argc, char **argv)
{
    struct winsize w;
    string action;
    int size;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    size = w.ws_col;

    map<int, map<int, string> > philos = get_data();
    map<int, map<int, string> >::iterator philos_itr;

    if (!philos.size())
        exit(EXIT_FAILURE);
    int end_time = 0;
    for (philos_itr = philos.begin(); philos_itr != philos.end(); ++philos_itr)
    {
        map<int, string> actions;

        actions = philos_itr->second;
        end_time = max(actions.rbegin()->first, end_time);
    }

    {
        int step = 100;

        while ((size / (float)end_time) * step < to_string(end_time).length() + 3)
            step *= 2;

        int parts = end_time / step;
        int current;

        current = 0;
        for (size_t i = 0; i < parts; i++)
        {
            write_duration(size, end_time, current, current + step, "time");
            current += step;
        }
        printf("\n");
        current = 0;
        for (size_t i = 0; i < parts; i++)
        {
            write_duration(size, end_time, current, current + step, "time_bar");
            current += step;
        }
        printf("\n");
    }

    for (philos_itr = philos.begin(); philos_itr != philos.end(); ++philos_itr)
    {
        map<int, string> actions;
        map<int, string>::iterator actions_itr;

        actions = philos_itr->second;
        actions_itr = actions.begin();

        int actual = 0;

        write_duration(size, end_time, actual, actions_itr->first, "empty");
        actual = actions_itr->first;
        action = actions_itr->second;
        while (++actions_itr != actions.end())
        {
            write_duration(size, end_time, actual, actions_itr->first, action);

            actual = actions_itr->first;
            action = actions_itr->second;
        }
        write_duration(size, end_time, actual, end_time, action);
        cout << endl;
    }
    cout << endl;
    cout << eat(1) << " eat  ";
    cout << sleep(1) << " sleep  ";
    cout << think(1) << " think";
    cout << endl;
    return (0);
}

// void show_help(FILE *file)
// {
//     fprintf(file, "usage: ./visualizer [-s time] [command-and-arguments]\n");
// }

// int main(int argc, char *argv[])
// {
//     int opt;
//     long max_duration;

//     max_duration = -1;
//     while ((opt = getopt(argc, argv, "hs:")) != EOF)
//     {
//         switch(opt)
//         {
//             case 'h':
//                 show_help(stdout);
//                 exit(0);
//             case 's':
//                 char *p;
//                 max_duration = strtol(optarg, &p, 10);
//                 if (!*p && max_duration > 0)                    
//                     break;
//             case '?':
//                 show_help(stderr);
//             default:
//                 exit(1);
//         }
//     }
//     cout << max_duration << endl;
//     return 0;
// }

