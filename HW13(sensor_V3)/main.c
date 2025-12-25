#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "sensor.h"
#include "csv_parser.h"

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    
    CliOptions options = parse_cli_args(argc, argv);
    
    // initialize dynamic array
    struct sensor_array* sensors = sensor_array_create(100000);
    if (!sensors) 
    {
        fprintf(stderr, "Error: Cannot allocate memory for sensor data\n");
        return 1;
    }
    
    if (options.csv_file) 
    {
        // load in CSV
        printf("\nLoading data from %s...\n", options.csv_file);
        int loaded = parse_csv(options.csv_file, sensors);
        
        if (loaded == 0) 
        {
            printf("No data loaded from CSV.\n");
            sensor_array_free(sensors);
            return 1;
        }
        
        //printf("Total memory used: %.2f MB\n", 
        //       (sensors->size * sizeof(struct sensor)) / (1024.0 * 1024.0));
    }
    else 
    {
        // test plug
        printf("Using test data (no CSV file specified)\n");
        printf("Use -h for help\n\n");
        sensor_array_add(sensors, 2021, 1, 1, 0, 0, -5);
        sensor_array_add(sensors, 2021, 1, 1, 0, 1, -6);
        sensor_array_add(sensors, 2021, 1, 1, 0, 2, -7);
        sensor_array_add(sensors, 2021, 1, 2, 7, 5, -10);
        sensor_array_add(sensors, 2021, 2, 15, 12, 0, 5);
        sensor_array_add(sensors, 2021, 2, 15, 12, 1, 6);
        sensor_array_add(sensors, 2021, 2, 15, 12, 2, 7);
    }
    
    // data output
    if (options.show_all) 
    {
        printf("\nOriginal data (%d records)\n", sensors->size);
        print(sensors->data, sensors->size);

        // printf("\n========= Sorted by temperature (first 20) ========\n");
        // SortByT(sensors->data, sensors->size);
        // print(sensors->data, sensors->size);
    }
    
    // Stat
    if (options.month_filter > 0)
    {
        // only one month
        printf("\n");
        print_month_stats(sensors->data, sensors->size, options.month_filter);
    } 
    else 
    {
        // all months
        printf("\n\n\n=========== Monthly Statistics ===========\n");
        printf("==========================================\n");
        for (int month = 1; month <= 12; month++) 
        {
            print_month_stats(sensors->data, sensors->size, month);
        }
        
        printf("\n");
        print_year_stats(sensors->data, sensors->size);
    }

    sensor_array_free(sensors);
    
    return 0;
}