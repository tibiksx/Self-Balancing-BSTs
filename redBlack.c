#include "redBlack.h"
#include <string.h>

int compareIntsRB(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

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

redBlackNode* leftRotate(RedBlackTree *rbt, redBlackNode *node) {
	redBlackNode *newParent = node->right;

	if (node == *rbt) {
		*rbt = newParent;
	}

	if (node->parent != NULL) {
		if (node == node->parent->left) {
			node->parent->left = newParent;
		} else {
			node->parent->right = newParent;
		}
	}

	newParent->parent = node->parent;
	node->parent = newParent;

	node->right = newParent->left;

	if (newParent->left != NULL) {
		newParent->left->parent = node;
	}

	newParent->left = node;

	return node;
}

redBlackNode* rightRotate(RedBlackTree *rbt, redBlackNode *node) {
	redBlackNode *newParent = node->left;

	if (node == *rbt) {
		*rbt = newParent;
	}

	if (node->parent != NULL) {
		if (node == node->parent->left) {
			node->parent->left = newParent;
		} else {
			node->parent->right = newParent;
		}
	}

	newParent->parent = node->parent;
	node->parent = newParent;

	node->left = newParent->right;

	if (newParent->right != NULL) {
		newParent->right->parent = node;
	}

	newParent->right = node;

	return node;
}
void printInorderTraversal(RedBlackTree rbt, int buildUp, int direction);

RedBlackTree balance(RedBlackTree rbt, redBlackNode *node) {
	if (node == rbt) {
		node->color = 0;
		return rbt;
	}

	redBlackNode *parent = node->parent;
	redBlackNode *grandParent = parent->parent;
	redBlackNode *uncle;

	if (parent == NULL || grandParent == NULL) {
		uncle = NULL;
	} else {
		if (parent == grandParent->left) {
			uncle = grandParent->right;
		} else {
			uncle = grandParent->left;
		}
	}

	if (parent->color != 0) {
		if (uncle != NULL && uncle->color == 1) {
			parent->color = 0;
			uncle->color = 0;
			grandParent->color = 1;

			rbt = balance(rbt, grandParent);
		} else {
			if (parent == grandParent->left) {
				if (node == parent->left) {
					char tmp = parent->color;
					parent->color = grandParent->color;
					grandParent->color = tmp;
				} else {
					parent = leftRotate(&rbt, parent);

					char tmp = node->color;
					node->color = grandParent->color;
					grandParent->color = tmp;
				}

				grandParent = rightRotate(&rbt, grandParent);
			} else {
				if (node == parent->left) {
					parent = rightRotate(&rbt, parent);

					char tmp = node->color;
					node->color = grandParent->color;
					grandParent->color = tmp;
				} else {
					char tmp = parent->color;
					parent->color = grandParent->color;
					grandParent->color = tmp;
				}
				// printf("before rotate\n");
				// printInorderTraversal(rbt, 0, 0);
				grandParent = leftRotate(&rbt, grandParent);
				// printf("after rotate\n");
				// printInorderTraversal(rbt, 0, 0);
			}
		}
	}

	// printf("before exit\n");
	// printInorderTraversal(rbt, 0, 0);
	return rbt;
}

redBlackNode* searchTree(RedBlackTree rbt, void *data) {
	redBlackNode *tmp = rbt;

	while (tmp != NULL) {
		if (compareIntsRB(data, tmp->data) < 0) {
			if (tmp->left == NULL) {
				break;
			} else {
				tmp = tmp->left;
			}
		} else if (compareIntsRB(data, tmp->data) == 0) {
			break;
		} else {
			if (tmp->right == NULL) {
				break;
			} else {
				tmp = tmp->right;
			}
		}
	}

	return tmp;
}

RedBlackTree insert(RedBlackTree rbt, redBlackNode *node) {
	if (rbt == NULL) {
		node->color = 0;
		return node;
	}

	redBlackNode *position = searchTree(rbt, node->data);

	if (compareIntsRB(position->data, node->data) == 0) {
		return rbt;
	}

	node->parent = position;

	if (compareIntsRB(node->data, position->data) < 0) {
		position->left = node;
	} else {
		position->right = node;
	}

	printInorderTraversal(rbt, 0, 0);

	rbt = balance(rbt, node);

	// printf("after exit\n");
	// printInorderTraversal(rbt, 0, 0);

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

redBlackNode* getSibling(redBlackNode *node) {
	if (node->parent == NULL) {
		return NULL;
	}

	if (node == node->parent->left) {
		return node->parent->right;
	}

	return node->parent->left;
}

RedBlackTree balanceBlacks(RedBlackTree rbt, redBlackNode *replacement) {
	if (replacement == rbt) {
		return rbt;
	}

	redBlackNode *sibling = getSibling(replacement);

	if (sibling == NULL) {
		return balanceBlacks(rbt, replacement->parent);
	} else {
		if (sibling->color == 1) { //red
			replacement->parent->color = 1;
			sibling->color = 0;

			if (sibling->parent->left == sibling) {
				sibling->parent = rightRotate(rbt, sibling->parent);
			} else {
				sibling->parent = leftRotate(rbt, sibling->parent);
			}

			return balanceBlacks(rbt, replacement->parent);
		} else {
			if ((sibling->left != NULL && sibling->left->color == 1) || (sibling->right != NULL && sibling->right->color == 1)) {
				if (sibling->left != NULL && sibling->left->color == 1) {
					if (sibling->parent->left == sibling) {
						sibling->left->color = sibling->color;
						sibling->color = replacement->parent->color;
						replacement->parent = rightRotate(rbt, replacement->parent);
					} else {
						sibling->left->color = replacement->parent->color;
						sibling = leftRotate(rbt, sibling);
						replacement->parent = rightRotate(rbt, replacement->parent);
					}
				} else {
					if (sibling == sibling->parent->left) {
						sibling->right->color = replacement->parent->color;
						sibling = leftRotate(rbt, sibling);
						replacement->parent = rightRotate(rbt, replacement->parent);
					} else {
						sibling->right->color = sibling->color;
						sibling->color = replacement->parent->color;
						replacement->parent = leftRotate(rbt, replacement->parent);
					}
				}

				replacement->parent->color = 0;
			} else {
				sibling->color = 1;
				if (replacement->parent->color == 0) {
					return balanceBlacks(rbt, replacement->parent);
				} else {
					replacement->parent->color = 0;
				}
			}
		}
	}

	return rbt;
}

RedBlackTree deleteNode(RedBlackTree rbt, redBlackNode *node) {
	redBlackNode *replacement = replace(node);
	int areBothBlack = ((replacement == NULL || replacement->color == 0) && node->color == 0);

	if (replacement == NULL) {
		if (node == rbt) {
			rbt = NULL;
		} else {
			if (areBothBlack) {
				rbt = balanceBlacks(rbt, node);
			} else {
				redBlackNode *sibling = getSibling(node);
				if (sibling != NULL) {
					sibling->color = 1;
				}
			}

			if (node == node->parent->left) {
				node->parent->left = NULL;
			} else {
				node->parent->right = NULL;
			}
		}

		free(node->data);
		free(node);
		return rbt;
	}

	if (node->left == NULL || node->right == NULL) {
		if (node == rbt) {
			memcpy(&(rbt->data), &(replacement->data), sizeof(int));
			replacement->right = NULL;
			replacement->left = NULL;
			free(replacement->data);
			free(replacement);
		} else {
			if (node->parent->left == node) {
				node->parent->left = replacement;
			} else {
				node->parent->right = replacement;
			}
			replacement->parent = node->parent;

			free(node->data);
			free(node);

			if (areBothBlack) {
				rbt = balanceBlacks(rbt, replacement);
			} else {
				replacement->color = 0;
			}
		}

		return rbt;
	}

	void *tmp = (void *) malloc(sizeof(int));
	memcpy(tmp, &(node->data), sizeof(int));
	memcpy(&(node->data), &(replacement->data), sizeof(int));
	memcpy(&(replacement->data), tmp, sizeof(int));
	free(tmp);

	rbt = deleteNode(rbt, replacement);

	return rbt;
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
