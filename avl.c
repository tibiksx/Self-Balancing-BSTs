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

avlNode* minNode(AvlTree avl) {
	avlNode *iter = avl;

	while (iter->left != NULL) {
		iter = iter->left;
	}

	return iter;
}

AvlTree deleteAvl(AvlTree avl, void *data) {
	if (avl == NULL) {
		return avl;
	}

	if (compareIntsAvl(data, avl->data) < 0) {
		avl->left = deleteAvl(avl->left, data);
	} else if (compareIntsAvl(data, avl->data) > 0) {
		avl->right = deleteAvl(avl->right, data);
	} else {
		if (avl->left == NULL || avl->right == NULL) {
			avlNode *tmp = NULL;

			if (avl->left != NULL) {
				tmp = avl->left;
			} else {
				tmp = avl->right;
			}

			if (tmp == NULL) {
				tmp = avl;
				avl = NULL;
			} else {
				*avl = *tmp;
			}

			free(tmp);
		} else {
			avlNode *tmp = minNode(avl->right);

			memcpy(avl->data, tmp->data, sizeof(int));

			avl->right = deleteAvl(avl->right, tmp->data);
		}
	}

	if (avl == NULL) {
		return avl;
	}

	if (getHeight(avl->left) > getHeight(avl->right)) {
		avl->height = 1 + getHeight(avl->left);
	} else {
		avl->height = 1 + getHeight(avl->right);
	}

	int diff = getHeight(avl->left) - getHeight(avl->right);

	if (diff > 1 && getHeight(avl->left->left) - getHeight(avl->left->right) >= 0) {
		return rotateRightAvl(avl);
	}

	if (diff > 1 && getHeight(avl->left->left) - getHeight(avl->left->right) < 0) {
		avl->left = rotateLeftAvl(avl->left);
		return rotateRightAvl(avl);
	}

	if (diff < -1 && getHeight(avl->right->left) - getHeight(avl->right->right) <= 0) {
		return rotateLeftAvl(avl);
	}

	if (diff < -1 && getHeight(avl->right->left) - getHeight(avl->right->right) > 0) {
		avl->right = rotateRightAvl(avl->right);
		return rotateLeftAvl(avl);
	}

	return avl;
}

void printInorderTraversalAvl(AvlTree avl, int buildUp, int direction) {
	if (avl == NULL) {
		return;
	}

	buildUp += 15;

	printInorderTraversalAvl(avl->right, buildUp, 1);
	printf("\n");

	for (int i = 15; i < buildUp; ++i) {
		printf(" ");
	}

	buildUp -= 15;
	if (direction && buildUp)
		printf("/ ");
	else if (!direction && buildUp)
		printf("\\ ");

	buildUp += 15;
	printf("%d\n", *(int *)(avl->data));
	printInorderTraversalAvl(avl->left, buildUp, 0);
}

AvlTree freeAvl(AvlTree avl) {
	if (avl == NULL) {
		return avl;
	}

	avlNode *save = avl;
	freeAvl(avl->left);
	freeAvl(avl->right);
	free(save->data);
	free(save);
	return NULL;
}
