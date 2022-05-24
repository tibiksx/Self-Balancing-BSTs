#include <stdio.h>
#include <stdlib.h>

typedef struct splayNode {
	void *data;
	struct splayNode *left, *right;
} splayNode, *SplayTree;

int compareInts(void *a, void *b);
splayNode* initNodeSplay(void *data);
splayNode* rotateLeft(splayNode *node);
splayNode* rotateRight(splayNode *node);
SplayTree balanceWithSplay(SplayTree st, void *data);
SplayTree insertSplay(SplayTree st, splayNode *node);
SplayTree searchSplay(SplayTree st, void *data);
SplayTree deleteSplay(SplayTree st, void *data);
void printPreorderTraversalSplay(SplayTree st);
void printInorderTraversalSplay(SplayTree st, int buildUp, int direction);
SplayTree freeSplay(SplayTree st);
