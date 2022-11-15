#include "fibheap.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

fibheap *fibheap_allocate_memory()
{
	fibheap *h = malloc(sizeof(fibheap));
	h->min = NULL;
	h->count = 0;
	return h;	
}

fibheap *fibheap_insert(fibheap *heap, int key, char *value) {
    node *n = malloc(sizeof(node));
	n->parent = NULL;
	n->left = n;
	n->right = n;
	n->child = NULL;
	n->key = key;
	n->degree = 0;
	n->value = value;
	n->mark = 0; // 0 - false, 1 - true
	fibheap_add_node_to_root_list(n, heap->min);
	if (heap->min == NULL || n->key < heap->min->key) {
		heap->min = n;
	}
	heap->count++;
	return heap;
}

void fibheap_add_node_to_root_list(node *n, node *min) {
    if (min == NULL) {
		return;
    }
	if (min->left == min) {
		min->left = n;
		min->right = n;
		n->right = min;
		n->left = min;
	} else {
		n->left = min->left;
		n->left->right = n;
		min->left = n;
		n->right = min;
	}
}

node *fibheap_min(fibheap *heap) {
    return heap->min;
}

fibheap *fibheap_union(fibheap *heap1, fibheap *heap2) {
    if(heap1 == NULL) {
        heap1 = fibheap_allocate_memory();
    }
    if(heap2 == NULL) {
        heap2 = fibheap_allocate_memory();
    }
    fibheap *heap = fibheap_allocate_memory();
    heap->min = heap1->min;
    fibheap_link_lists(heap1->min, heap2->min);
    if((heap1->min == NULL) || ((heap2->min != NULL) && (strcmp(heap2->min->key, heap->min->key) < 0))) {
        heap->min = heap2->min;
    }
    heap->count = heap1->count + heap2->count;
    free(heap1);
    free(heap2);
    return heap;
}

void fibheap_link_lists(node *m1, node *m2)
{
	if (m1 == NULL || m2 == NULL) {
		return;
    }
	m1->right->left = m2->left;
	m2->left->right = m1->right;
	m1->right = m2;
	m2->left = m1;
}

fibheap *fibheap_delete_min(fibheap *heap) {
    node *z = heap->min;
    if (z == NULL) {
        return NULL;
    }
    for (node *x = z->child; x != NULL; x = x->child) {
        FibHeapAddNodeToRootList(x, heap); /* Добавляем дочерний узел x в список корней */
        x->parent = NULL;
    }
    fibheap_remove_node_from_root_list(z, heap); /* Удаляем z из списка корней */
    if (z == z->right) {
        heap->min = NULL;
    } else {
        heap->min = z->right;
        fibheap_consolidate(heap);
    }
    heap->count--;
    return z;
}

void fibheap_link(fibheap *heap, node *y, node *x)
{
	x->degree++;
	fibheap_remove_node_from_root_list(y, heap->min);
	y->parent = x;
	fibheap_add_node_to_root_list(y, x->child);
	y->mark = 0;
}

fibheap *fibheap_decrease_key(fibheap *heap, node *n, int new_key)
{
	node *parent = n->parent;
	if (n->key < new_key) {
		return;
    }
	n->key = new_key;
	if (parent != NULL && parent->key > n->key) {
		fibheap_cut(heap, n, parent);
		fibheap_cascading_cut(heap, parent);
	}
	if (heap->min == NULL || n->key < heap->min->key) {
		heap->min = n;
	}
}

fibheap *fibheap_delete(fibheap *heap, node *x) {
    fibheap_decrease_key(heap, x, -INT_MAX);
    fibheap_delete_min(heap);
}

void fibheap_remove_node_from_root_list(node *x, node *y) {
    if (x == y->child && x != x->right) {
		y->child = x->right;
	} else {
		y->child = NULL;
	}
    x->right->left = x->left;
	x->left->right = x->right;
}

fibheap *fibheap_consolidate(fibheap *heap) {

    return heap;
}

void fibheap_cut(fibheap *heap, node *x, node *y) {
    fibheap_remove_node_from_root_list(x, y);
    y->degree--;
    fibheap_add_node_to_root_list(x, heap->min);
    x->parent = NULL;
    x->mark = 0;
}

void fibheap_cascading_cut(fibheap *heap, node *n)
{
	if (n->parent == NULL) {
		return;
    }
	if (n->mark == 0) {
		n->mark = 1;
	} else {
		fibheap_cut(heap, n, n->parent);
		fibheap_cascading_cut(heap, n->parent);
	}
}

int D(fibheap* heap) {
    return floor(log(2, heap->count));
}