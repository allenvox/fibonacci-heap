#include "fibheap.h"
#include <stdio.h>

int main() {
    fibheap *h1 = fibheap_allocate_memory();
    h1 = fibheap_insert(h1, 5, "malfoy");
    h1 = fibheap_insert(h1, 10, "harry");
    h1 = fibheap_insert(h1, 15, "dobby");
    h1 = fibheap_insert(h1, 20, "ron");
    h1 = fibheap_insert(h1, 25, "hermione");
    printf("Heap 1:\n");
    fibheap_print(h1->min);
    printf("\n");

    fibheap *h2 = fibheap_allocate_memory();
    h2 = fibheap_insert(h2, 3, "dumbledore");
    h2 = fibheap_insert(h2, 7, "snape");
    h2 = fibheap_insert(h2, 9, "macgonagoll");
    h2 = fibheap_insert(h2, 11, "hagrid");
    h2 = fibheap_insert(h2, 13, "umbridge");
    printf("Heap 2:\n");
    fibheap_print(h2->min);
    printf("\n");

    fibheap *h3 = fibheap_union(h1, h2);
    printf("Heap 3:\n");
    fibheap_print(h3->min);
    printf("\n");

    node *min = fibheap_min(h3);
    printf("Minimal: %d - '%s'\n", min->key, min->value);
    fibheap_delete_min(h3);
    min = fibheap_min(h3);
    printf("New minimal: %d - '%s'\n", min->key, min->value);
    fibheap_print(min);
    return 0;
}