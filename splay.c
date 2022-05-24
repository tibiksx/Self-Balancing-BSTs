#include "splay.h"
#include <string.h>

int compareInts(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

splayNode* initNodeSplay(void *data) {
	splayNode *node = (splayNode *) malloc(sizeof(splayNode));
	node->data = (void *) malloc(sizeof(int));
	memcpy(node->data, data, sizeof(int));
	node->left = NULL;
	node->right = NULL;
	return node;
}

splayNode* rotateLeft(splayNode *node) {
	splayNode *tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	return tmp;
}

splayNode* rotateRight(splayNode *node) {
	splayNode *tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	return tmp;
}

SplayTree balanceWithSplay(SplayTree st, void *data) {
	if (st == NULL || !compareInts(st->data, data)) {
		return st;
	}

	if (compareInts(st->data, data) > 0) {
		if (st->left == NULL) {
			return st;
		}

		if (compareInts(st->left->data, data) > 0) {
			st->left->left = balanceWithSplay(st->left->left, data);

			st = rotateRight(st);
		} else {
			st->left->right = balanceWithSplay(st->left->right, data);

			st = rotateLeft(st->left);
		}

		if (st->left == NULL) {
			return st;
		}

		return rotateRight(st);
	} else {
		if (st->right == NULL) {
			return st;
		}

		if (compareInts(st->right->data, data) > 0) {
			st->right->left = balanceWithSplay(st->right->left, data);

			if (st->right->left != NULL) {
				st->right = rotateRight(st->right);
			}
		} else {
			st->right->right = balanceWithSplay(st->right->right, data);

			st = rotateLeft(st);
		}

		if (st->right == NULL) {
			return st;
		}

		return rotateLeft(st);
	}
}

SplayTree insertSplay(SplayTree st, splayNode *node) {
	if (st == NULL) {
		return node;
	}

	st = balanceWithSplay(st, node->data);

	if (compareInts(st->data, node->data) == 0) {
		return st;
	}

	if (compareInts(st->data, node->data) > 0) {
		node->right = st;
		node->left = st->left;
		st->left = NULL;
	} else {
		node->left = st;
		node->right = st->right;
		st->right = NULL;
	}

	return node;
}

void printPreorderTraversalSplay(SplayTree st) {
	if (st == NULL) {
		return;
	}

	printf("%d ", *(int *)(st->data));
	printPreorderTraversalSplay(st->left);
	printPreorderTraversalSplay(st->right);
}

SplayTree freeSplay(SplayTree st) {
	if (st == NULL) {
		return st;
	}

	splayNode *save = st;
	freeSplay(st->left);
	freeSplay(st->right);
	free(save->data);
	free(save);
	return NULL;
}
