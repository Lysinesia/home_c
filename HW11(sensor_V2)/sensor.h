#ifndef SENSOR_H
#define SENSOR_H
#include <stdint.h>
#define MAX_SENSORS 30

struct sensor 
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
    int8_t t;
};

struct data 
{
    uint32_t number;
    struct sensor info[MAX_SENSORS];
};

union sensor_serdes 
{
    struct data _data;
    uint8_t bytes[sizeof(struct data)];
};

//из исходного
void AddRecord(struct sensor* info, int number, uint16_t year, uint8_t month, uint8_t day, int8_t t);
int AddInfo(struct sensor* info);
void SortByT(struct sensor* info, int n);
void SortByDate(struct sensor* info, int n);
void print(struct sensor* info, int number);

// раб с файл
void save_bin(struct sensor* info, int number);
void load_bin(struct sensor* info, int number);
void save_bin_ser(union sensor_serdes* d);
void load_bin_des(union sensor_serdes* d);

// стат
void print_month_stats(struct sensor* info, int count, uint8_t month);
void print_year_stats(struct sensor* info, int count);

#endif