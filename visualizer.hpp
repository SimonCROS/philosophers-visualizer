#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <iostream>
# include <string>
# include <map>

std::string space(int n);
std::string eat(int n);
std::string sleep(int n);
std::string think(int n);

void print_rule(int size, int end, int step);
void print_data(int size, int end, std::map<int, std::map<int, std::string> > philos);
void print_help(FILE *file);
void print_caption();

void write_duration(int size, int last, int start, int end, std::string action);

std::map<int, std::map<int, std::string> > get_data(FILE *file);

int get_win_width();
int get_opt_int(int *num);

#endif
