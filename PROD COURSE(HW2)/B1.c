#include <stdio.h>
#include <stdint.h>
#include <inttypes.h> 

typedef struct list
{
     void *address;
    size_t size;
    //char COMMENT[64];
    struct list *next;
}list;
size_t totalMemoryUsage(list *head)
{
    if(head == NULL) return 0;

    size_t total_size = 0;
    list *current = head;
    while(current != NULL)
    {
        total_size += current -> size;
        current = current -> next;
    }
    return total_size;
}

int main()
{
    list node1, node2, node3;
    uint64_t addr1, addr2, addr3;
    
    scanf("%" SCNu64 " %zu", &addr1, &node1.size);
    scanf("%" SCNu64 " %zu", &addr2, &node2.size);
    scanf("%" SCNu64 " %zu", &addr3, &node3.size);
    
    node1.address = (void*)(uintptr_t)addr1;
    node2.address = (void*)(uintptr_t)addr2;
    node3.address = (void*)(uintptr_t)addr3;

    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;

    list *head = &node1;

    size_t result = totalMemoryUsage(head);
    printf("%zu\n", result);
    return 0;
}