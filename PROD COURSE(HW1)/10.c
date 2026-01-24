#include <stdio.h>
#include <stdint.h>

struct pack_array 
{
    uint32_t array;
    uint32_t count0 : 8;
    uint32_t count1 : 8;
};

void array2struct(int arr[], struct pack_array *pack) 
{
    pack->array = 0;
    pack->count0 = 0;
    pack->count1 = 0;
    
    for (int i = 0; i < 32; i++) 
    {
        if (arr[i] == 1) 
        {
            pack->array |= (1u << (31 - i));
            pack->count1++;
        } 
        else pack->count0++;
    }
}

int main() 
{
    int arr[32];
    for (int i = 0; i < 32; i++) 
    {
        scanf("%d", &arr[i]);
    }
    struct pack_array pack;
    array2struct(arr, &pack);

    printf("%u %u %u\n", pack.array, pack.count0, pack.count1);
    return 0;
}