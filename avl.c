#include "avl.h"
#include <string.h>

int compareIntsAvl(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

int getHeight(avlNode *node) {
	if (node == NULL) {
		return 0;
	}

	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);

	if (leftHeight > rightHeight) {
		return 1 + leftHeight;
	}

	return 1 + rightHeight;
}

avlNode* initNodeAvl(void *data) {
	avlNode *node = (avlNode *) malloc(sizeof(avlNode));
	node->data = (void *) malloc(sizeof(int));
	memcpy(node->data, data, sizeof(int));
	node->height = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

avlNode* rotateLeftAvl(avlNode *node) {
	avlNode *tmp = node->right;
	avlNode *snd = tmp->left;

	tmp->left = node;
	node->right = snd;

	node->height = getHeight(node);
	tmp->height = getHeight(tmp);

	return tmp;
}

avlNode* rotateRightAvl(avlNode *node) {
	avlNode *tmp = node->left;
	avlNode *snd = tmp->right;

	tmp->right = node;
	node->left = snd;

	node->height = getHeight(node);
	tmp->height = getHeight(tmp);

	return tmp;
}

AvlTree insertAvl(AvlTree avl, avlNode *node) {
	if (avl == NULL) {
		return node;
	}

	if (compareIntsAvl(node->data, avl->data) < 0) {
		avl->left = insertAvl(avl->left, node);
	} else if (compareIntsAvl(node->data, avl->data) > 0) {
		avl->right = insertAvl(avl->right, node);
	} else {
		return avl;
	}

	avl->height = getHeight(avl);

	if (getHeight(avl->left) - getHeight(avl->right) > 1 && compareIntsAvl(node->data, avl->left->data) < 0) {
		return rotateRightAvl(avl);
	}

	if (getHeight(avl->left) - getHeight(avl->right) < -1 && compareIntsAvl(node->data, avl->right->data) > 0) {
		return rotateLeftAvl(avl);
	}

	if (getHeight(avl->left) - getHeight(avl->right) > 1 && compareIntsAvl(node->data, avl->left->data) > 0) {
		avl->left = rotateLeftAvl(avl->left);
		return rotateRightAvl(avl);
	}

	if (getHeight(avl->left) - getHeight(avl->right) < -1 && compareIntsAvl(node->data, avl->right->data) < 0) {
		avl->right = rotateRightAvl(avl->right);
		return rotateLeftAvl(avl);
	}

	return avl;
}

avlNode* searchAvl(AvlTree avl, void *data) {
	if (avl == NULL || !compareIntsAvl(avl->data, data)) {
		return avl;
	}

	if (compareIntsAvl(avl->data, data) < 0) {
		return searchAvl(avl->right, data);
	}

	return searchAvl(avl->left, data);
}

void printPreorderTraversalAvl(AvlTree avl) {
	if (avl == NULL) {
		return;
	}

	printf("%d ", *(int *)(avl->data));
	printPreorderTraversalAvl(avl->left);
	printPreorderTraversalAvl(avl->right);
}
