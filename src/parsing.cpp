#include "visualizer.hpp"

using namespace std;

map<int, map<int, string> > get_data(FILE *file)
{
    int time;
    int philo;
    char actionc[20];
    string action;
    map<int, map<int, string> > philos;

    while (fscanf(file, "%d %d %[^\n]\n", &time, &philo, actionc) != EOF)
    {
        action = actionc;
        if (!action.compare("has taken a fork"))
            continue ;
        if (!philos.count(philo))
        {
            map<int, string> actions;
            actions[time] = action;
            philos[philo] = actions;
        }
        else
            philos.at(philo)[time] = action;
    }
    return (philos);
}
