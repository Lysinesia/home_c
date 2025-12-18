#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "sensor.h"

typedef struct {
    char* csv_file;
    int month_filter;
    int show_all;
} CliOptions;

int parse_csv(const char* filename, struct sensor* info);
void print_help(const char* program_name);
CliOptions parse_cli_args(int argc, char* argv[]);

#endif