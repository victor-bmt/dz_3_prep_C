#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

unsigned char get_height(const node* p) {
	return p ? p->height : 0;
}

int bfactor(const node* p) {
	if (!p) {
		printf("Incorrect use of 'bfactor()'\n");
		return -3;
	}

	return (get_height(p->right) - get_height(p->left));
}

void set_height(node* p) {
	if (!p) {
		error_glob = -3;
		printf("Incorrect use of 'set_height()'\n");
		return;
	}

	unsigned char h_left = get_height(p->left);
	unsigned char h_right = get_height(p->right);

	p->height = (h_left > h_right ? h_left : h_right) + 1;

	return;
}

node* rotate_right(node* p) {
	if (!p) {
		printf("Incorrect use of 'rotate_right()'\n");
		return NULL;
	}

	node* q = p->left;
	p->left = q->right;
	q->right = p;

	set_height(p);
	set_height(q);

	return q;
}

node* rotate_left(node* q) {
	if (!q) {
		printf("Incorrect use of 'rotate_left()'\n");
		return NULL;
	}

	node* p = q->right;
	q->right = p->left;
	p->left = q;

	set_height(q);
	set_height(p);

	return p;
}


node* balance(node* p) {

	if (!p) {
		printf("Incorrect use of 'balance()'\n");
		return NULL;
	}

	set_height(p);

	if (bfactor(p) == 2) {
		if (bfactor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}

	if (bfactor(p) == -2) {
		if (bfactor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}

	// Если дерево изначально сбалансировано
	return p;
}

node* insert(node *p, unsigned int k) {
	if (!p) {
		node* new_node = malloc(sizeof(node));
		if (!new_node) {
			error_glob = -2;
			return NULL;
		}
		new_node->height = 1;
		new_node->key = k;
		new_node->left = NULL;
		new_node->right = NULL;
		return new_node;
	}

	if (k == p->key) {
		printf("Attempt to create existing node with key '%u'\n", k);
		error_glob = -1;
		return p;
	}

	if (k < (p->key))
		p->left = insert(p->left, k);

	else
		p->right = insert(p->right, k);

	return balance(p);
}

node* find_min(node* p) {
	if (!p) {
		printf("Incorrect use of 'find_min()'\n");
		return NULL;
	}

	return ((p->left) ? find_min(p->left) : p);
}

node* remove_min(node* p) {
	if (!p) {
		printf("Incorrect use of 'remove_min()'\n");
		return NULL;
	}

	if (!(p->left))
		return p->right;

	p->left = remove_min(p->left);
	return balance(p);
}

node* remove_node(node* p, unsigned int k) {
	if (!p) {
		printf("Attempt to remove unexisting node with key '%u'\n", k);
		error_glob = -1;
		return NULL;
	}

	if (k < (p->key))
		p->left = remove_node(p->left, k);

	else if (k > (p->key))
		(p->right) = remove_node(p->right, k);

	else {
		node* q = p->left;
		node* r = p->right;

		free(p);

		if (!r)
			return q;

		node* min = find_min(r);
		min->right = remove_min(r);
		min->left = q;
		return balance(min);
	}

	return balance(p);
}

void destruct_tree(node* p) {

	if (!p) {
		printf("Tree is not created yet\n");
		return;
	}

	if (p->left)
		destruct_tree(p->left);

	if (p->right)
		destruct_tree(p->right);

	free(p);

	return;
}

int find_key(const node* p, unsigned int k) {
	if (!p)
		return 0;

	if (k == p->key)
		return 1;

	if (k > (p->key))
		return (find_key(p->right, k));

	else
		return (find_key(p->left, k));
}

void print_tree(const node* p) {
	unsigned char height = get_height(p);
	unsigned int num = 1;

	for (unsigned int i = 1; i <= height; ++i) {
		unsigned int pos = 0;

		printf(" ");
		
		while (pos < num) {
			
			unsigned int cur = goto_next(i, pos, p);
			if (cur)
				printf("%u", cur );
			else 
				printf("N");

			printf("\t");

			++pos;
		}
		
		num *= 2;
		printf("\n\n");
	}
}

unsigned int goto_next(const unsigned int string_n, unsigned int pos, const node* p) {
	int max = 1;
	node m = *p;

	for (int i = 1; i < string_n; ++i)
		max *= 2;

	for (int i = 1; i < string_n; ++i) {
		if (pos < (max / 2)) {
			if (m.left)
				m = *(m.left);
			else
				return 0;
		}
		else {
			if (m.right)
				m = *(m.right);
			else
				return 0;
		}

		max /= 2;
		pos %= max;
	}
	
	return m.key;
}
