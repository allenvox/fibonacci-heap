#pragma once

typedef struct node {
    struct node *parent;
    int key;
	int value;
	int mark;
    int degree;
	struct node *left;
	struct node *right;
	struct node *child;
} node;

typedef struct
{
    node *min;
    int count;
} fibheap;

fibheap *fibheap_insert(fibheap *heap, int key, char *value);
node *fibheap_min(fibheap *heap);
fibheap *fibheap_union(fibheap *heap1, fibheap *heap2);
fibheap *fibheap_delete_min(fibheap *heap);
fibheap *fibheap_decrease_key(fibheap *heap, fibheap *node, int newkey);
fibheap *fibheap_delete(fibheap *heap, int key);