#include <stdio.h>
#include <stdint.h>
#include <inttypes.h> 

typedef struct list
{
    uint64_t address;
    size_t size;
    //char COMMENT[64];
    struct list *next;
}list;

uint64_t findMaxBlock(list *head)
{
    if(head == NULL) return 0;

    size_t max_size = 0;
    uint64_t max_addr = 0;

    list *current = head;
    while(current != NULL)
    {
        if(current -> size  > max_size)
        {
            max_size = current -> size;
            max_addr = current -> address;
        }
        current = current -> next;
    }
    return max_addr;
}

int main()
{
    list node1, node2, node3;
    scanf("%" SCNu64 " %zu", &node1.address, &node1.size);
    scanf("%" SCNu64 " %zu", &node2.address, &node2.size);
    scanf("%" SCNu64 " %zu", &node3.address, &node3.size);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;

    list *head = &node1;

    uint64_t result = findMaxBlock(head);
    printf("%" PRIu64 "\n", result);
    return 0;
}