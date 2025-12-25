#ifndef SENSOR_H
#define SENSOR_H
#include <stdint.h>

struct sensor 
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
};

struct sensor_array 
{
    struct sensor* data;
    int capacity;
    int size;
};

struct sensor_array* sensor_array_create(int initial_capacity);
void sensor_array_free(struct sensor_array* array);

int sensor_array_add(struct sensor_array* array,
                     uint16_t year, uint8_t month, uint8_t day,
                     uint8_t hour, uint8_t minute, int8_t temperature);

void SortByT(struct sensor* info, int n);
void SortByDate(struct sensor* info, int n);
void print(struct sensor* info, int number);

void print_month_stats(struct sensor* info, int count, uint8_t month);
void print_year_stats(struct sensor* info, int count);

#endif