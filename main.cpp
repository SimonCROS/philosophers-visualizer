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

int	main(int argc, char **argv)
{
    struct winsize w;
    string action;
    int size;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    size = w.ws_col;

    map<int, map<int, string> > philos = get_data();
    map<int, map<int, string> >::iterator philos_itr;

    int end_time;
    for (philos_itr = philos.begin(); philos_itr != philos.end(); ++philos_itr)
    {
        map<int, string> actions;

        actions = philos_itr->second;
        if (philos_itr == philos.begin())
            end_time = actions.rbegin()->first;
        else
            end_time = max(actions.rbegin()->first, end_time);
    }

    for (philos_itr = philos.begin(); philos_itr != philos.end(); ++philos_itr)
    {
        map<int, string> actions;
        map<int, string>::iterator actions_itr;
        int actual;
        int duration;
        int action_size;
        int write = 0;

        actions = philos_itr->second;
        actions_itr = actions.begin();

        actual = actions_itr->first;
        action = actions_itr->second;

        action_size = actual * size / end_time;
        cout << space(action_size);

        while (++actions_itr != actions.end())
        {
            duration = actions_itr->first - actual;
            action_size = roundf(duration * size / (float)end_time);
            if (!action.compare("is eating"))
                cout << eat(action_size);
            else if (!action.compare("is sleeping"))
                cout << sleep(action_size);
            else if (!action.compare("is thinking"))
                cout << think(action_size);

            actual = actions_itr->first;
            action = actions_itr->second;
        }
        duration = end_time - actual;
        action_size = roundf(duration * size / (float)end_time);
        if (!action.compare("is eating"))
            cout << eat(action_size);
        else if (!action.compare("is sleeping"))
            cout << sleep(action_size);
        else if (!action.compare("is thinking"))
            cout << think(action_size);
        cout << endl;
    }
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

