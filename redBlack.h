#include <stdio.h>
#include <stdlib.h>

typedef struct redBlackNode {
	void *data;
	char color;
	struct redBlackNode *parent, *left, *right;
} redBlackNode, *RedBlackTree;

int compareIntsRB(void *a, void *b);
redBlackNode* initNode(int item);
RedBlackTree insert(RedBlackTree rbt, redBlackNode *node);
redBlackNode* searchTree(RedBlackTree rbt, void *data);
RedBlackTree deleteNode(RedBlackTree rbt, redBlackNode *node);
redBlackNode* leftRotate(RedBlackTree *rbt, redBlackNode *node);
redBlackNode* rightRotate(RedBlackTree *rbt, redBlackNode *node);
RedBlackTree balance(RedBlackTree rbt, redBlackNode *node);
redBlackNode* getSuccessor(redBlackNode *node);
redBlackNode* getSibling(redBlackNode *node);
RedBlackTree balanceBlacks(RedBlackTree rbt, redBlackNode *replacement);
void printInorderTraversal(RedBlackTree rbt, int buildUp, int direction);
RedBlackTree freeTree(RedBlackTree rbt);
