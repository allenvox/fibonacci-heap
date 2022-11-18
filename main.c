#include "fibheap.h"

int main() {
    fibheap *h1 = fibheap_allocate_memory();
    h1 = fibheap_insert(h1, 5, "malfoy");
    h1 = fibheap_insert(h1, 10, "harry");
    h1 = fibheap_insert(h1, 15, "dobby");
    h1 = fibheap_insert(h1, 20, "ron");
    h1 = fibheap_insert(h1, 25, "hermione");
    fibheap_print(h1);

    fibheap *h2 = fibheap_allocate_memory();
    h2 = fibheap_insert(h2, 3, "dumbledore");
    h2 = fibheap_insert(h2, 7, "snape");
    h2 = fibheap_insert(h2, 9, "macgonagoll");
    h2 = fibheap_insert(h2, 11, "hagrid");
    h2 = fibheap_insert(h2, 13, "umbridge");
    fibheap_print(h2);

    fibheap *h3 = fibheap_union(h1, h2);
    fibheap_print(h3);
    return 0;
}