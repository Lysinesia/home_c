#include <stdio.h>
#include <string.h>
#include "sensor.h"

void cgangeIJ(struct sensor* info, int i, int j)
{
    struct sensor temp;
    temp = info[i];
    info[i] = info[j];
    info[j] = temp;
}

void AddRecord(struct sensor* info, int number, uint16_t year, uint8_t month, uint8_t day, int8_t t)
{
    info[number].year = year;
    info[number].month = month;
    info[number].day = day;
    info[number].t = t;
}

int AddInfo(struct sensor* info)
{
    int counter = 0;
    AddRecord(info, counter++, 2021, 9, 16, 9);
    AddRecord(info, counter++, 2022, 9, 2, -9);
    AddRecord(info, counter++, 2021, 1, 7, 8);
    AddRecord(info, counter++, 2021, 9, 5, 1);
    return counter;
}

void SortByT(struct sensor* info, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (info[i].t >= info[j].t)
                cgangeIJ(info, i, j);
}

unsigned int DateToInt(struct sensor* info)
{
    return info->year << 16 | info->month << 8 | info->day;
}

void SortByDate(struct sensor* info, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (DateToInt(info + i) >= DateToInt(info + j))
                cgangeIJ(info, i, j);
}

void print(struct sensor* info, int number)
{
    printf("===================================\n");
    for (int i = 0; i < number; i++)
        printf("%04d-%02d-%02d t=%3d\n",
               info[i].year,
               info[i].month,
               info[i].day,
               info[i].t);
}

// Файловые операции
void save_bin(struct sensor* info, int number)
{
    FILE* f = fopen("sensor.bin", "wb");
    fwrite(info, number * sizeof(struct sensor), 1, f);
    fclose(f);
}

void load_bin(struct sensor* info, int number)
{
    FILE* f = fopen("sensor.bin", "rb");
    fread(info, number * sizeof(struct sensor), 1, f);
    fclose(f);
}

void save_bin_ser(union sensor_serdes* d)
{
    FILE* f = fopen("sensor.bin", "wb");
    fwrite(d->bytes, sizeof(d->_data.number), 1, f);
    fwrite(d->bytes + sizeof(d->_data.number),
           d->_data.number * sizeof(struct sensor),
           1, f);
    fclose(f);
}

void load_bin_des(union sensor_serdes* d)
{
    FILE* f = fopen("sensor.bin", "rb");
    fread(d->bytes, sizeof(d->_data.number), 1, f);
    fread(d->bytes + sizeof(d->_data.number),
          d->_data.number * sizeof(struct sensor),
          1, f);
    fclose(f);
}

// стат
void print_month_stats(struct sensor* info, int count, uint8_t month)
{
    int sum = 0;
    int month_count = 0;
    int min_temp = 100;
    int max_temp = -100;

    for (int i = 0; i < count; i++)
    {
        if (info[i].month == month)
        {
            sum += info[i].t;
            month_count++;
            if (info[i].t < min_temp) min_temp = info[i].t;
            if (info[i].t > max_temp) max_temp = info[i].t;
        }
    }

    if (month_count > 0)
    {
        float average = (float)sum / month_count;
        printf("\nStatistics for month %02d:\n", month);
        printf("  Entries: %d\n", month_count);
        printf("  Average: %.1f°C\n", average);
        printf("  Min: %d°C\n", min_temp);
        printf("  Max: %d°C\n", max_temp);
    } 
    else printf("\nNo data for month %02d\n", month);
}

void print_year_stats(struct sensor* info, int count) 
{
    if (count == 0) 
    {
        printf("\nNo data for statistics\n");
        return;
    }
    int sum = 0;
    int min_temp = 100;
    int max_temp = -100;
    int current_year = info[0].year;

    for (int i = 0; i < count; i++)
    {
        sum += info[i].t;
        if (info[i].t < min_temp) min_temp = info[i].t;
        if (info[i].t > max_temp) max_temp = info[i].t;
    }

    float average = (float)sum / count;
    printf("\nStatistics for year %d:\n", current_year);
    printf("  Total records: %d\n", count);
    printf("  Average: %.1f°C\n", average);
    printf("  Min: %d°C\n", min_temp);
    printf("  Max: %d°C\n", max_temp);
}