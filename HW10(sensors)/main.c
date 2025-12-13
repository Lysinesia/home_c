#include <stdio.h>
#include "sensor.h"
#include <windows.h>

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    struct data d;
    union sensor_serdes* ds = (union sensor_serdes*)&d;

    d.number = AddInfo(d.info);
    print(d.info, d.number);

    // Пример сохранения/загрузки
    save_bin_ser(ds);

    printf("\nSort by temperature:\n");
    SortByT(d.info, d.number);
    print(d.info, d.number);

    printf("\nSort by date:\n");
    SortByDate(d.info, d.number);
    print(d.info, d.number);

    // Загрузка обратно
    load_bin_des(ds);
    print(d.info, d.number);
    // стат 
    print_month_stats(d.info, d.number, 9); // Сентябрь
    print_month_stats(d.info, d.number, 1); // Январь
    print_year_stats(d.info, d.number);

    return 0;
}