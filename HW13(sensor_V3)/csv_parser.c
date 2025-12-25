#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "sensor.h"
#include "csv_parser.h"

int parse_csv(const char* filename, struct sensor_array* array) 
{
    FILE* file = fopen(filename, "r");
    if (!file) 
    {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 0;
    }
    
    char line[256];
    int line_number = 0;
    int valid_records = 0;
    
    while (fgets(line, sizeof(line), file)) 
    {
        line_number++;
        
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;
        if (line_number == 1 && strstr(line, "YEAR")) 
        {
            continue;
        }
        
        uint16_t year;
        uint8_t month, day, hour, minute;
        int8_t temperature;
        
        if (sscanf(line, "%hu;%hhu;%hhu;%hhu;%hhu;%hhd", 
                  &year, &month, &day, &hour, &minute, &temperature) == 6) {
            
            int valid = 1;
            
            if (year < 1900 || year > 2100) 
            {
                if (line_number < 10) // only first errors
                {
                    fprintf(stderr, "Warning line %d: Invalid year %d\n", line_number, year);
                }
                valid = 0;
            }
            if (month < 1 || month > 12) 
            {
                if (line_number < 10) 
                {
                    fprintf(stderr, "Warning line %d: Invalid month %d\n", line_number, month);
                }
                valid = 0;
            }
            if (day < 1 || day > 31) 
            {
                if (line_number < 10) 
                {
                    fprintf(stderr, "Warning line %d: Invalid day %d\n", line_number, day);
                }
                valid = 0;
            }
            if (hour > 23) 
            {
                if (line_number < 10) 
                {
                    fprintf(stderr, "Warning line %d: Invalid hour %d\n", line_number, hour);
                }
                valid = 0;
            }
            if (minute > 59) 
            {
                if (line_number < 10) 
                {
                    fprintf(stderr, "Warning line %d: Invalid minute %d\n", line_number, minute);
                }
                valid = 0;
            }
            if (temperature < -99 || temperature > 99) 
            {
                if (line_number < 10) 
                {
                    fprintf(stderr, "Warning line %d: Invalid temperature %d\n", line_number, temperature);
                }
                valid = 0;
            }
            
            if (valid) 
            {
                if (sensor_array_add(array, year, month, day, hour, minute, temperature)) 
                {
                    valid_records++;
                } 
                else 
                {
                    fprintf(stderr, "Error: Memory allocation failed at line %d\n", line_number);
                    break;
                }
            }
        } 
        else 
        {
            if (line_number < 10) 
            {
                fprintf(stderr, "Error line %d: Invalid format: %s\n", line_number, line);
                //fprintf(stderr, "Expected format: YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE\n");
            }
        }
        
        // for big numbers
        if (line_number % 100000 == 0) 
        {
            printf("Processed %d lines, loaded %d records...\n", line_number, valid_records);
        }
    }
    
    fclose(file);
    
    if (valid_records > 0) {
        printf("Successfully loaded %d records from %s (total lines: %d)\n", 
               valid_records, filename, line_number);
    } else {
        printf("No valid records loaded from %s\n", filename);
    }
    
    return valid_records;
}

void print_help(const char* program_name) 
{
    printf("Temperature Statistics Application\n");
    printf("Usage: %s [options]\n\n", program_name);
    printf("Options:\n");
    printf("  -h                 Show this help message\n");
    printf("  -f <csv_file>      Input CSV file for processing\n");
    printf("  -m <month_number>  Show statistics for specific month (1-12)\n");
    printf("  -a                 Show all data with sorting\n");
    printf("\nExample:\n");
    printf("  %s -f data.csv -m 9    # Process data.csv and show stats for September\n", program_name);
    printf("  %s -f data.csv -a      # Process data.csv with full output\n", program_name);
    printf("  %s                      # Run with test data\n", program_name);
}

CliOptions parse_cli_args(int argc, char* argv[]) 
{
    CliOptions options = {NULL, -1, 0};
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) 
        {
            print_help(argv[0]);
            exit(0);
        } 
        else if (strcmp(argv[i], "-f") == 0) 
        {
            if (i + 1 < argc) 
            {
                options.csv_file = argv[++i];
            } 
            else 
            {
                fprintf(stderr, "Error: -f requires a filename\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "-m") == 0) 
        {
            if (i + 1 < argc) 
            {
                options.month_filter = atoi(argv[++i]);
                if (options.month_filter < 1 || options.month_filter > 12) 
                {
                    fprintf(stderr, "Error: Month must be between 1 and 12\n");
                    exit(1);
                }
            } 
            else 
            {
                fprintf(stderr, "Error: -m requires a month number\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "-a") == 0) 
        {
            options.show_all = 1;
        }
        else 
        {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_help(argv[0]);
            exit(1);
        }
    }
    
    return options;
}