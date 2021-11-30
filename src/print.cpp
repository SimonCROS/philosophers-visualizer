#include <stdio.h>

#include "visualizer.hpp"

using namespace std;

void print_rule(int size, int end, int step)
{
    int current;
    int parts;

    while ((size / (float)end) * step < to_string(end).length() + 3)
        step *= 2;
    parts = end / step + 1;

    current = 0;
    for (size_t i = 0; i < parts; i++)
    {
        write_duration(size, end, current, current + step, "time");
        current += step;
    }
    cout.put('\n');
    current = 0;
    for (size_t i = 0; i < parts; i++)
    {
        write_duration(size, end, current, current + step, "time_bar");
        current += step;
    }
    cout.put('\n');
}

static void print_philo(int size, int end, map<int, string> actions)
{
    map<int, string>::iterator  actions_itr;
    string                      action;
    int                         actual;

    actions_itr = actions.begin();

    write_duration(size, end, 0, actions_itr->first, "empty");
    actual = actions_itr->first;
    action = actions_itr->second;
    while (++actions_itr != actions.end())
    {
        write_duration(size, end, actual, actions_itr->first, action);
        actual = actions_itr->first;
        action = actions_itr->second;
    }
    write_duration(size, end, actual, end, action);
    cout << endl;
}

void print_data(int size, int end, map<int, map<int, string> > philos)
{
    map<int, map<int, string> >::iterator philos_itr;

    for (philos_itr = philos.begin(); philos_itr != philos.end(); ++philos_itr)
        print_philo(size, end, philos_itr->second);
}

void print_caption()
{
    cout
    << endl
    << eat(1) << " eat"
    << " "
    << sleep(1) << " sleep"
    << " "
    << think(1) << " think"
    << endl;
}

void print_help(FILE *file)
{
    fprintf(file, "usage:\n./visualizer [-s step]\n");
}
