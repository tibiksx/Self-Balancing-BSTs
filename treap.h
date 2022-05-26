#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treapNode {
	void *data;
	int priority;
	struct treapNode *left, *right;
} treapNode, *Treap;

int compareIntsTreap(void *a, void *b);
treapNode* rotateLeftTreap(treapNode *node);
treapNode* rotateRightTreap(treapNode *node);
treapNode* initNodeTreap(void *data);
treapNode* searchTreap(Treap trp, void *data);
Treap insertTreap(Treap trp, treapNode *node);
Treap deleteTreap(Treap trp, void *data);
void printInorderTraversalTreap(Treap trp, int buildUp, int direction);
Treap freeTreap(Treap trp);