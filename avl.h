#include <stdio.h>
#include <stdlib.h>

typedef struct avlNode {
	void *data;
	int height;
	struct avlNode *left, *right;
} avlNode, *AvlTree;

int compareIntsAvl(void *a, void *b);
int getHeight(avlNode *node);
avlNode* initNodeAvl(void *data);
avlNode* rotateLeftAvl(avlNode *node);
avlNode* rotateRightAvl(avlNode *node);
AvlTree insertAvl(AvlTree avl, avlNode *node);
avlNode* searchAvl(AvlTree avl, void *data);
AvlTree deleteAvl(AvlTree avl, void *data);
void printPreorderTraversalAvl(AvlTree avl);
AvlTree freeAvl(AvlTree avl);
