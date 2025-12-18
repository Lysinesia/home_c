#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sensor.h"

int parse_csv(const char* filename, struct sensor* info) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    
    char line[100];
    int counter = 0;
    
    while (fgets(line, sizeof(line), file) && counter < MAX_SENSORS) {
        uint16_t year;
        uint8_t month, day;
        int8_t temp;
        
        // Форматы: ГГГГ-ММ-ДД,температура или ГГГГ-ММ-ДД температура
        if (sscanf(line, "%hu-%hhu-%hhu,%hhd", &year, &month, &day, &temp) == 4 ||
            sscanf(line, "%hu-%hhu-%hhu %hhd", &year, &month, &day, &temp) == 4) {
            AddRecord(info, counter++, year, month, day, temp);
        }
    }
    
    fclose(file);
    printf("Loaded %d records from %s\n", counter, filename);
    return counter;
}

void print_help(const char* program_name) {
    printf("Temperature Statistics Application\n");
    printf("Usage: %s [options]\n\n", program_name);
    printf("Options:\n");
    printf("  -h                 Show this help message\n");
    printf("  -f <csv_file>      Input CSV file for processing\n");
    printf("  -m <month_number>  Show statistics for specific month (1-12)\n");
    printf("  -a                 Show all data with sorting (default without -m)\n");
    printf("\nExample:\n");
    printf("  %s -f data.csv -m 9    # Process data.csv and show stats for September\n", program_name);
    printf("  %s -f data.csv -a      # Process data.csv with full output\n", program_name);
}

typedef struct {
    char* csv_file;
    int month_filter;
    int show_all;
} CliOptions;

CliOptions parse_cli_args(int argc, char* argv[]) {
    CliOptions options = {NULL, -1, 0};
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            print_help(argv[0]);
            exit(0);
        } 
        else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                options.csv_file = argv[++i];
            } else {
                fprintf(stderr, "Error: -f requires a filename\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "-m") == 0) {
            if (i + 1 < argc) {
                options.month_filter = atoi(argv[++i]);
                if (options.month_filter < 1 || options.month_filter > 12) {
                    fprintf(stderr, "Error: Month must be between 1 and 12\n");
                    exit(1);
                }
            } else {
                fprintf(stderr, "Error: -m requires a month number\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "-a") == 0) {
            options.show_all = 1;
        }
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_help(argv[0]);
            exit(1);
        }
    }
    
    return options;
}