#include <stdio.h>
#include <stdlib.h>

typedef struct scapeGoatNode {
	void *data;
	struct scapeGoatNode *left, *right;
	struct scapeGoatNode *parent;
} scapeGoatNode, *ScapeGoatTree;

int compareIntsSG(void *a, void *b);
int log32(int n);
int getSize(ScapeGoatTree sgt);
scapeGoatNode* initNodeSG(void *data);
int storeInArr(scapeGoatNode *node, scapeGoatNode **arr, int i);
ScapeGoatTree insertSG(ScapeGoatTree sgt, void *data, int *n);
ScapeGoatTree rebuildTree(scapeGoatNode *node, ScapeGoatTree sgt);
scapeGoatNode* buildTreeFromArray(ScapeGoatTree *arr, int idx, int n);
int insertAndFindDepth(ScapeGoatTree *sgt, scapeGoatNode *node, int *n);
void preorderSG(ScapeGoatTree sgt);
ScapeGoatTree freeSG(ScapeGoatTree sgt);
