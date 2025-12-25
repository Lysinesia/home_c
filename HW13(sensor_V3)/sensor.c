#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sensor.h"

static void changeIJ(struct sensor* info, int i, int j)
{
    struct sensor temp;
    temp = info[i];
    info[i] = info[j];
    info[j] = temp;
}

struct sensor_array* sensor_array_create(int initial_capacity)
{
    struct sensor_array* array = malloc(sizeof(struct sensor_array));
    if (!array) return NULL;
    
    array->data = malloc(initial_capacity * sizeof(struct sensor));
    if (!array->data) 
    {
        free(array);
        return NULL;
    }
    
    array->capacity = initial_capacity;
    array->size = 0;
    return array;
}

void sensor_array_free(struct sensor_array* array)
{
    if (array) 
    {
        free(array->data);
        free(array);
    }
}

int sensor_array_add(struct sensor_array* array,
                     uint16_t year, uint8_t month, uint8_t day,
                     uint8_t hour, uint8_t minute, int8_t temperature)
{
    if (!array) return 0;
    
    if (array->size >= array->capacity) 
    {
        int new_capacity = array->capacity * 2;
        struct sensor* new_data = realloc(array->data, new_capacity * sizeof(struct sensor));
        
        if (!new_data) return 0;
        array->data = new_data;
        array->capacity = new_capacity;
    }
    
    array->data[array->size].year = year;
    array->data[array->size].month = month;
    array->data[array->size].day = day;
    array->data[array->size].hour = hour;
    array->data[array->size].minute = minute;
    array->data[array->size].temperature = temperature;
    
    array->size++;
    return 1;
}

// Sort by temperature
void SortByT(struct sensor* info, int n)
{
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) 
        {
            if (info[j].temperature > info[j + 1].temperature) 
            {
                changeIJ(info, j, j + 1);
            }
        }
    }
}

static unsigned long long DateToInt(struct sensor* s)
{
    return (unsigned long long)s->year * 100000000 +
           (unsigned long long)s->month * 1000000 +
           (unsigned long long)s->day * 10000 +
           (unsigned long long)s->hour * 100 +
           (unsigned long long)s->minute;
}

// Sort by date and time
void SortByDate(struct sensor* info, int n)
{
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (DateToInt(&info[j]) > DateToInt(&info[j + 1])) 
            {
                changeIJ(info, j, j + 1);
            }
        }
    }
}

void print(struct sensor* info, int number)
{
    if (number == 0) {
        printf("No data to display\n");
        return;
    }
    
    printf("First 20 records (total: %d)\n", number);
    printf("===================================================\n");
    printf("Date                Time                Temperature\n");
    printf("---------------------------------------------------\n");
    
    int limit = number < 20 ? number : 20;
    for (int i = 0; i < limit; i++) 
    {
        printf("%04d-%02d-%02d          %02d:%02d                    %3d°C\n",
               info[i].year,
               info[i].month,
               info[i].day,
               info[i].hour,
               info[i].minute,
               info[i].temperature);
    }
    
    if (number > 20) 
    {
        printf("... and %d more records\n", number - 20);
    }
    printf("===================================================\n");
}

void print_month_stats(struct sensor* info, int count, uint8_t month)
{
    if (count == 0) {
        printf("No data available\n");
        return;
    }
    
    int sum = 0;
    int month_count = 0;
    int min_temp = 100;
    int max_temp = -100;
    int year = -1;

    for (int i = 0; i < count; i++) 
    {
        if (info[i].month == month) 
        {
            if (year == -1) year = info[i].year;
            sum += info[i].temperature;
            month_count++;
            if (info[i].temperature < min_temp) min_temp = info[i].temperature;
            if (info[i].temperature > max_temp) max_temp = info[i].temperature;
        }
    }

    if (month_count > 0) 
    {
        float average = (float)sum / month_count;
        printf("\n===== Statistics for month %02d (%04d) =====\n", month, year);
        printf("==========================================\n");
        printf("  Records:              %d\n", month_count);
        printf("------------------------------------------\n");
        printf("  Average:              %.2f°C\n", average);
        printf("------------------------------------------\n");
        printf("  Minimum:              %d°C\n", min_temp);
        printf("------------------------------------------\n");
        printf("  Maximum:              %d°C\n", max_temp);
        printf("------------------------------------------\n");
        printf("  Temperature range:    %d°C\n", max_temp - min_temp);
        printf("==========================================\n");
    } 
    else 
    {
        if (count > 0 && year == -1) 
        {
            year = info[0].year;
        }
        printf("No data available for month %02d (%04d)\n", month, year > 0 ? year : 2021);
    }
}

void print_year_stats(struct sensor* info, int count) 
{
    //for big data
    if (count == 0) 
    {
        printf("No data available for statistics\n");
        return;
    }
    int min_temp_all = 100;
    int max_temp_all = -100;
    long long sum_all = 0;
    
    // first run: common ststs
    for (int i = 0; i < count; i++) 
    {
        sum_all += info[i].temperature;
        if (info[i].temperature < min_temp_all) min_temp_all = info[i].temperature;
        if (info[i].temperature > max_temp_all) max_temp_all = info[i].temperature;
    }
    
    float average_all = (float)sum_all / count;


    printf("\n\n==========================================\n");
    printf("=========== Overall Statistics ===========\n");
    printf("==========================================\n");
    printf("|  Average:        %.2f°C\n", average_all);
    printf("|  Minimum:        %d°C\n", min_temp_all);
    printf("|  Maximum:        %d°C\n", max_temp_all);
    printf("==========================================\n");
    printf("  Total records:  %d\n", count);
    printf("==========================================\n");
}