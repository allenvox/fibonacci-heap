#include "fibheap.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

fibheap *fibheap_allocate_memory() { //
	fibheap *h = malloc(sizeof(fibheap));
	h->min = NULL;
	h->count = 0;
	return h;	
}

node *fibheap_create_node(int key, char *value) { //
	node *n = malloc(sizeof(node));
	n->parent = NULL;
	n->left = n;
	n->right = n;
	n->child = NULL;
	n->key = key;
	n->degree = 0;
	n->value = value;
	n->mark = 0; // 0 - false, 1 - true
	return n;
}

fibheap *fibheap_insert(fibheap *heap, int key, char *value) { //
    node *n = fibheap_create_node(key, value);
	fibheap_add_node_to_root_list(n, heap->min);
	if (heap->min == NULL || n->key < heap->min->key) {
		heap->min = n;
	}
	heap->count++;
	return heap;
}

void fibheap_add_node_to_root_list(node *n, node *min) {
    if (!min) {
    	min = n;
    	n->left = n;
    	n->right = n;
	} else {
    	n->left = min->left;
    	n->right = min;
    	min->left->right = n;
    	min->left = n;
  	}
  	n->parent = NULL;
}

node *fibheap_min(fibheap *heap) { //
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
    if((heap1->min == NULL) || ((heap2->min != NULL) && (heap2->min->key < heap->min->key))) {
        heap->min = heap2->min; // if minimal of 2nd heap is less - put it as new min for unified heap
    }
    heap->count = heap1->count + heap2->count;
    free(heap1);
    free(heap2);
    return heap;
}

void fibheap_link_lists(node *n1, node *n2) { //
	if (n1 == NULL || n2 == NULL) {
		return;
    }
	node *l1 = n1->left, *l2 = n2->left;
	l1->right = n2, l2->right = n1;
	n1->left = l2;
	n2->left = l1;
}

fibheap *fibheap_delete_min(fibheap *heap) {
	node *min = heap->min;
    if (min == NULL) {
        return NULL;
    }
	node *child = min->child;
	while (child) {
		fibheap_add_node_to_root_list(child, heap->min);
		child->parent = NULL;
		if (child->left == child) { break; }
		child = child->left;
	}
	fibheap_link_lists(min, min->child);
	fibheap_remove_node_from_root_list(min);
	if (min == min->right) {
		heap->min = NULL;
	} else {
		heap->min = min->right;
		fibheap_consolidate(heap);
	}
    heap->count--;
	free(min);
    return heap;
}

void fibheap_insert_child(node *parent, node *child) {
	if (!parent || !child) { return; }
	if (!parent->child) {
    	parent->child = child;
    	child->left = child;
    	child->right = child;
  	} else {
    	child->left = parent->child->left;
    	child->right = parent->child;
		parent->child->left->right = child;
    	parent->child->left = child;
  	}
	child->parent = parent;
}

void fibheap_link(node *parent, node *child) {
	if(parent == NULL || child == NULL) {
		return;
	}
	parent->degree++;
	fibheap_remove_node_from_root_list(child);
	fibheap_insert_child(parent, child);
	child->mark = 0;
}

fibheap *fibheap_decrease_key(fibheap *heap, node *n, int new_key) {
	node *parent = n->parent;
	if (n->key < new_key) {
		return heap;
    }
	n->key = new_key;
	if (parent != NULL && parent->key > n->key) {
		fibheap_cut(heap, n, parent);
		fibheap_cascading_cut(heap, parent);
	}
	if (heap->min == NULL || n->key < heap->min->key) {
		heap->min = n;
	}
	return heap;
}

fibheap *fibheap_delete(fibheap *heap, node *x) { //
    fibheap_decrease_key(heap, x, -INT_MAX);
    fibheap_delete_min(heap);
	return heap;
}

void fibheap_remove_node_from_root_list(node *n) { //
	n->right->left = n->left;
	n->left->right = n->right;
}

fibheap *fibheap_consolidate(fibheap *heap) {
	int max_degree = D(heap);
	node** A = malloc(sizeof(node) * max_degree);
	for (int i = 0; i < max_degree; i++) {
		A[i] = NULL;
	}
	node *x = NULL;
	while (1) {
		if (x == NULL) {
			x = heap->min;
		}
		int d = x->degree;
		while(A[d] != NULL) {
			node *y = A[d];
			if(x == y) { break; }
			if(x->key > y->key) {
				node *temp = x;
        		x = y;
        		y = temp;
			}
			fibheap_link(x, y);
			A[d] = NULL;
			d++;
			heap->min = x;
		}
		A[d] = x;
		x = x->right;
		if(x == heap->min) { break; }
	}
	
	for(int i = 0; i < max_degree; i++) {
		if(A[i] != NULL) {
			fibheap_add_node_to_root_list(A[i], heap->min);
			printf("%d\n", heap->min->key);
			if(A[i]->key < heap->min->key) {
				heap->min = A[i];
			}
		}
	}
    return heap;
}

void fibheap_cut(fibheap *heap, node *x, node *y) { //
	if (x == y->child && x != x->right) {
		y->child = x->right;
	} else {
		y->child = NULL;
	}
	x->left->right = x->right;
	x->right->left = x->left;
	x->right = heap->min;
	x->left = heap->min->left;
	heap->min->left->right = x;
	heap->min->left = x;
	x->parent = NULL;
	y->degree--;
    x->mark = 0;
}

void fibheap_cascading_cut(fibheap *heap, node *n) { //
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

void fibheap_print(node *root) { //
	if (root == NULL) return;
    node *n = root, *child;
	while(1) {
		printf("%d:", n->key);
		child = n->child;
		if(child == NULL) {
			printf(" no child");
		}
		while(child) {
			printf(" %d", child->key);
			child = child->right;
			if(child == n->child) { break; }
		}
		printf("\n");
		fibheap_print(child);
		n = n->right;
		if(n == root) { break; }
	}
}

int D(fibheap* heap) { //
    return floor(log(heap->count)) + 1;
}