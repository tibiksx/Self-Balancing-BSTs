#include "scapegoat.h"
#include <string.h>
#include <math.h>

int compareIntsSG(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

int log32(int n) {
	return (int)ceil(2.4663034623764317 * log(n));
}

int getSize(ScapeGoatTree sgt) {
	if (sgt == NULL) {
		return 0;
	}

	return 1 + getSize(sgt->left) + getSize(sgt->right);
}

scapeGoatNode* initNodeSG(void *data) {
	scapeGoatNode *node = (scapeGoatNode *) malloc(sizeof(scapeGoatNode));
	node->data = (void *) malloc(sizeof(int));
	memcpy(node->data, data, sizeof(int));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int storeInArr(scapeGoatNode *node, scapeGoatNode **arr, int i) {
	if (node == NULL) {
		return i;
	}

	i = storeInArr(node->left, arr, i);
	arr[i++] = node;
	return storeInArr(node->right, arr, i);
}

ScapeGoatTree insertSG(ScapeGoatTree sgt, void *data, int *n) {
	scapeGoatNode *node = initNodeSG(data);

	int height = insertAndFindDepth(&sgt, node, n);

	if (height > log32(*n)) {
		// find scapegoat

		scapeGoatNode *scapeGoat = node->parent;
		while (3 * getSize(scapeGoat) <= 2 * getSize(scapeGoat->parent)) {
			scapeGoat = scapeGoat->parent;
		}

		sgt = rebuildTree(scapeGoat->parent, sgt);
	}

	return sgt;
}

ScapeGoatTree rebuildTree(scapeGoatNode *node, ScapeGoatTree sgt) {
	int n = getSize(node);

	scapeGoatNode *parent = node->parent;
	scapeGoatNode **arr = (scapeGoatNode **) malloc(sizeof(scapeGoatNode *));

	storeInArr(node, arr, 0);

	if (parent == NULL) {
		sgt = buildTreeFromArray(arr, 0, n);
		sgt->parent = NULL;
	} else if (parent->right == node) {
		parent->right = buildTreeFromArray(arr, 0, n);
		parent->right->parent = parent;
	} else {
		parent->left = buildTreeFromArray(arr, 0, n);
		parent->left->parent = parent;
	}

	return sgt;
}

scapeGoatNode* buildTreeFromArray(ScapeGoatTree *arr, int idx, int n) {
	if (n == 0) {
		return NULL;
	}

	int median = n / 2;

	arr[idx + median]->left = buildTreeFromArray(arr, idx, median);

	if (arr[idx + median]->left != NULL) {
		arr[idx + median]->left->parent = arr[idx + median];
	}

	arr[idx + median]->right = buildTreeFromArray(arr, idx + median + 1, n - median - 1);

	if (arr[idx + median]->right != NULL) {
		arr[idx + median]->right->parent = arr[idx + median];
	}

	return arr[idx + median];
}

int insertAndFindDepth(ScapeGoatTree *sgt, scapeGoatNode *node, int *n) {
	scapeGoatNode *iter = *sgt;

	if (iter == NULL) {
		*sgt = node;
		(*n)++;
		return 0;
	}

	int done = 0;
	int d = 0;

	do {
		if (compareIntsSG(node->data, iter->data) < 0) {
			if (iter->left == NULL) {
				iter->left = node;
				node->parent = iter;
				done = 1;
			} else {
				iter = iter->left;
			}
		} else if (compareIntsSG(node->data, iter->data) > 0) {
			if (iter->right == NULL) {
				iter->right = node;
				node->parent = iter;
				done = 1;
			} else {
				iter = iter->right;
			}
		} else {
			return -1;
		}

		d++;
	} while (!done);

	(*n)++;
	return d;
}

void preorderSG(ScapeGoatTree sgt) {
	if (sgt == NULL) {
		return;
	}

	printf("%d ", *(int *)(sgt->data));
	preorderSG(sgt->left);
	preorderSG(sgt->right);
}
