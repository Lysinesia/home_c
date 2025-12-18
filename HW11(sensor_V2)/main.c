#include <stdio.h>
#include <windows.h>
#include "sensor.h"
#include "csv_parser.h"

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    
    CliOptions options = parse_cli_args(argc, argv);
    
    struct data d;
    union sensor_serdes* ds = (union sensor_serdes*)&d;

    if (options.csv_file) 
    {
        // из CSV
        d.number = parse_csv(options.csv_file, d.info);
        if (d.number == 0) {
            printf("No data loaded from CSV. Using default data.\n");
            d.number = AddInfo(d.info);
        }
    }
    else 
    {
        // Исп стандарт данных
        d.number = AddInfo(d.info);
        if (argc == 1) {
            printf("Using default data (no CSV file specified)\n");
            printf("Use -h for help\n");
        }
    }

    save_bin_ser(ds);
    
    // Вывод
    if (options.show_all || options.month_filter == -1) 
    {
        printf("\nOriginal data (%d records):\n", d.number);
        print(d.info, d.number);

        printf("\nSorted by temperature:\n");
        SortByT(d.info, d.number);
        print(d.info, d.number);

        printf("\nSorted by date:\n");
        SortByDate(d.info, d.number);
        print(d.info, d.number);

        load_bin_des(ds);
        printf("\nLoaded from binary file:\n");
        print(d.info, d.number);
    }
    
    // Стат
    if (options.month_filter > 0)
    {
        // Только указ
        printf("\n=== Statistics for month %02d ===\n", options.month_filter);
        print_month_stats(d.info, d.number, options.month_filter);
    } else {
        // Все
        printf("\n=== Monthly Statistics ===\n");
        for (int month = 1; month <= 12; month++) 
        {
            print_month_stats(d.info, d.number, month);
        }     
        // Год стат
        print_year_stats(d.info, d.number);
    }

    return 0;
}