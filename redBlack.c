#include "redBlack.h"

redBlackNode* initNode(int item) {
	redBlackNode *node = (redBlackNode *) malloc(sizeof(redBlackNode));
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->data = (void *) malloc(sizeof(item));
	*(int *)(node->data) = item;
	node->color = 1;

	return node;
}

RedBlackTree insert(RedBlackTree rbt, redBlackNode *node) {
	if (rbt == NULL) {
		return node;
	}

	if (*(int *)(rbt->data) < *(int *)(node->data)) {
		rbt->right = insert(rbt->right, node);
		rbt->right->parent = rbt;
	} else {
		rbt->left = insert(rbt->left, node);
		rbt->left->parent = rbt;
	}

	return rbt;
}

redBlackNode* searchTree(RedBlackTree rbt, int value) {
	if (rbt == NULL) {
		return NULL;
	}

	if (value > *(int *)(rbt->data)) {
		return searchTree(rbt->right, value);
	} else if (value < *(int *)(rbt->data)) {
		return searchTree(rbt->left, value);
	} else {
		return rbt;
	}

	return NULL;
}

RedBlackTree leftRotate(RedBlackTree rbt, redBlackNode *node) {
	redBlackNode *right = node->right;
	node->right = right->left;

	if (node->right) {
		node->right->parent = node;
	}
	right->parent = node->parent;

	if (!node->parent) {
		rbt = right;
	} else if (node == node->parent->left) {
		node->parent->left = right;
	} else {
		node->parent->right = right;
	}

	right->left = node;
	node->parent = right;

	return rbt;
}

RedBlackTree rightRotate(RedBlackTree rbt, redBlackNode *node) {
	redBlackNode *left = node->left;
	node->left = left->right;

	if (node->left) {
		node->left->parent = node;
	}
	left->parent = node->parent;

	if (!node->parent) {
		rbt = left;
	} else if (node == node->parent->left) {
		node->parent->left = left;
	} else {
		node->parent->right = left;
	}

	left->right = node;
	node->parent = left;

	return rbt;
}

RedBlackTree balance(RedBlackTree rbt, redBlackNode *node) {
	redBlackNode *parent, *grandParent;

	while (node != rbt && node->color && node->parent->color) {
		parent = node->parent;
		grandParent = node->parent->parent;

		if (parent == grandParent->left) {
			redBlackNode *uncle = grandParent->right;

			// uncle is red - recoloring else rotation
			if (uncle != NULL && uncle->color) {
				grandParent->color = 1;
				parent->color = 0;
				uncle->color = 0;
				node = grandParent;
			} else {
				if (node == parent->right) {
					rbt = leftRotate(rbt, parent);
					node = parent;
					parent = node->parent;
				}

				rbt = rightRotate(rbt, grandParent);
				char parentColor = parent->color;
				parent->color = grandParent->color;
				grandParent->color = parentColor;
				node = parent;
			}
		} else if (parent == grandParent->right) {
			redBlackNode *uncle = grandParent->left;

			// uncle is red - recoloring else rotation
			if (uncle != NULL && uncle->color) {
				grandParent->color = 1;
				parent->color = 0;
				uncle->color = 0;
				node = grandParent;
			} else {
				if (node == parent->left) {
					rbt = rightRotate(rbt, parent);
					node = parent;
					parent = node->parent;
				}

				rbt = leftRotate(rbt, grandParent);
				char parentColor = parent->color;
				parent->color = grandParent->color;
				grandParent->color = parentColor;
				node = parent;
			}
		}
	}

	rbt->color = 0;
	return rbt;
}

redBlackNode* getSuccessor(redBlackNode *node) {
	redBlackNode *iter = node;

	while (iter->left != NULL) {
		iter = iter->left;
	}

	return iter;
}

redBlackNode* replace(redBlackNode *node) {
	if (node->left == NULL && node->right == NULL)
		return NULL;

	if (node->left != NULL && node->right != NULL)
		return getSuccessor(node->right);

	if (node->left != NULL)
		return node->left;

	return node->right;
}

void printInorderTraversal(RedBlackTree rbt, int buildUp, int direction) {
	if (rbt == NULL) {
		return;
	}

	buildUp += 15;

	printInorderTraversal(rbt->right, buildUp, 1);
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
	printf("%d: %d\n", *(int *)(rbt->data), rbt->color);
	printInorderTraversal(rbt->left, buildUp, 0);
}

RedBlackTree freeTree(RedBlackTree rbt) {
	if (rbt == NULL) {
		return rbt;
	}

	redBlackNode *save = rbt;
	freeTree(rbt->left);
	freeTree(rbt->right);
	free(save->data);
	free(save);
	return NULL;
}
