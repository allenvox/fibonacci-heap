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

// - undone
fibheap *fibheap_allocate_memory();
fibheap *fibheap_insert(fibheap *heap, int key, char *value);
void fibheap_add_node_to_root_list(node *n, node *min);
node *fibheap_min(fibheap *heap);
fibheap *fibheap_union(fibheap *heap1, fibheap *heap2);
void fibheap_link_lists(node *m1, node *m2);
fibheap *fibheap_delete_min(fibheap *heap);
fibheap *fibheap_decrease_key(fibheap *heap, node *node, int new_key);
fibheap *fibheap_delete(fibheap *heap, node *x);
void fibheap_remove_node_from_root_list(node *x, node *y);
fibheap *fibheap_consolidate(fibheap *heap); //
void fibheap_link(fibheap *heap, node *y, node *x);
void fibheap_cut(fibheap *heap, node *x, node* y);
void fibheap_cascading_cut(fibheap *heap, node *n);
void fibheap_print(fibheap *heap, int level);
int D(fibheap *heap);