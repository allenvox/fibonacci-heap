#include "fibheap.h"
#include <stdlib.h>

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

}

void fibheap_link_lists(node* m1, node* m2)
{
	if (m1 == NULL || m2 == NULL) {
		return;
    }
	m1->right->left = m2->left;
	m2->left->right = m1->right;
	m1->right = m2;
	m2->left = m1;
}

void fibheap_link(node* n, node* child)
{
	n->degree++;
	fibheap_remove_node_from_root_list(child);
	child->parent = n;
	fibheap_add_node_to_root_list(child, n->child);
	child->mark = 0;
}

fibheap *fibheap_decrease_key(fibheap* heap, node* n, int new_key)
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

int fibheap_max_degree(fibheap* heap) {
    return floor(log(heap->count));
}