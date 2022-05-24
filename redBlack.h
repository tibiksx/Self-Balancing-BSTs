#include <stdio.h>
#include <stdlib.h>

typedef struct redBlackNode {
	void *data;
	char color;
	struct redBlackNode *parent, *left, *right;
} redBlackNode, *RedBlackTree;

redBlackNode* initNode(int item);
RedBlackTree insert(RedBlackTree rbt, redBlackNode *node);
redBlackNode* searchTree(RedBlackTree rbt, int value);
RedBlackTree deleteNode(RedBlackTree rbt, redBlackNode *node);
RedBlackTree leftRotate(RedBlackTree rbt, redBlackNode *node);
RedBlackTree rightRotate(RedBlackTree rbt, redBlackNode *node);
RedBlackTree balance(RedBlackTree rbt, redBlackNode *node);
redBlackNode* getSuccessor(redBlackNode *node);
void printInorderTraversal(RedBlackTree rbt, int buildUp, int direction);
RedBlackTree freeTree(RedBlackTree rbt);
