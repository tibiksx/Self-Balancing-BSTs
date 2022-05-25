#include "redBlack.h"
#include "splay.h"
#include "treap.h"
#include "avl.h"
#include <string.h>

void redBlack() {
	RedBlackTree rbt = NULL;

	printf("INSERTION\n");
	for (int i = 0; i < 15; ++i) {
		int elem = i;
		redBlackNode *node = initNode(elem);
		printf("To be inserted: %d\n", elem);

		rbt = insert(rbt, node);

		printf("AFTER BALANCING\n");
		printInorderTraversal(rbt, 0, 0);
		printf("\n");
	}

	printf("SEARCH\n");
	redBlackNode *search = NULL;
	void *data = (void *) malloc(sizeof(int));
	*(int *)data = 0;

	for (int i = 0; i < 10; ++i) {
		*(int *)data = rand() % 30;
		search = searchTree(rbt, data);
		if (compareIntsRB(search->data, data) == 0) {
			printf("found: %d\n", *(int *)(search->data));

			break;
		} else {
			printf("not found: %d\n", *(int *)data);
		}
	}

	printf("DELETION\n");
	if (compareIntsRB(search->data, data) == 0) {
		rbt = deleteNode(rbt, search);
	}

	printInorderTraversal(rbt, 0, 0);

	rbt = freeTree(rbt);
}

void splay() {
	void *item = (void *) malloc(sizeof(int));
	*(int *)item = 30;
	SplayTree st = initNodeSplay(item);
	*(int *)item = 80;
	st->left = initNodeSplay(item);
	*(int *)item = 180;
	st->right = initNodeSplay(item);
	*(int *)item = 33;
	st->left->left = initNodeSplay(item);
	*(int *)item = 20;
	st->left->left->left = initNodeSplay(item);
	*(int *)item = 19;
	st->left->left->left->left = initNodeSplay(item);

	*(int *)item = 85;
	splayNode *toInsert = initNodeSplay(item);
	st = insertSplay(st, toInsert);
	printPreorderTraversalSplay(st);
	printf("\n");
	toInsert = NULL;
	*(int *)item = 300;
	toInsert = initNodeSplay(item);
	st = insertSplay(st, toInsert);
	printPreorderTraversalSplay(st);
	printf("\n");

	*(int *)item = 30;
	st = searchSplay(st, item);

	if (compareInts(st->data, item) != 0) {
		printf("Not found%d\n", *(int *)(st->data));
	} else {
		printf("%d\n", *(int *)(st->data));
	}
	printPreorderTraversalSplay(st);
	printf("\n");

	st = deleteSplay(st, item);
	printPreorderTraversalSplay(st);

	st = freeSplay(st);
}

void treap() {
	void *data = (void *) malloc(sizeof(int));
	*(int *)data = 50;
	treapNode *node = initNodeTreap(data);
	Treap trp = NULL;
	trp = insertTreap(trp, node);
	*(int *)data = 45;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);
	*(int *)data = 90;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);
	*(int *)data = 66;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);
	*(int *)data = 105;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);
	*(int *)data = 60;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);
	*(int *)data = 30;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);
	*(int *)data = 55;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);
	*(int *)data = 34;
	node = initNodeTreap(data);
	trp = insertTreap(trp, node);

	printInorderTraversalTreap(trp);

	*(int *)data = 105;
	treapNode *res = searchTreap(trp, data);

	if (res != NULL)
		printf("found: %d\n", *(int *)(res->data));
	else
		printf("not found\n");

	*(int *)data = 20;
	trp = deleteTreap(trp, data);
	printInorderTraversalTreap(trp);

	free(data);
	trp = freeTreap(trp);
}

void avl() {
	void *data = (void *) malloc(sizeof(int));
	*(int *)data = 10;
	avlNode *node = initNodeAvl(data);

	AvlTree avl = NULL;
	avl = insertAvl(avl, node);

	*(int *)data = 20;
	node = initNodeAvl(data);
	avl = insertAvl(avl, node);

	*(int *)data = 30;
	node = initNodeAvl(data);
	avl = insertAvl(avl, node);

	*(int *)data = 40;
	node = initNodeAvl(data);
	avl = insertAvl(avl, node);

	*(int *)data = 50;
	node = initNodeAvl(data);
	avl = insertAvl(avl, node);

	*(int *)data = 25;
	node = initNodeAvl(data);
	avl = insertAvl(avl, node);

	printPreorderTraversalAvl(avl);
	printf("\n");
	*(int *)data = 5;
	avlNode *searched = NULL;
	searched = searchAvl(avl, data);

	if (searched != NULL) {
		printf("found %d\n", *(int *)(searched->data));
	} else {
		printf("not found\n");
	}

	free(data);
}

int main(int argc, char const *argv[]) {
	char buffer[16];
	do {
		scanf("%s", buffer);

		if (!strcmp(buffer, "rbt")) {
			redBlack();
		}

		if (!strcmp(buffer, "splay")) {
			splay();
		}

		if (!strcmp(buffer, "treap")) {
			treap();
		}

		if (!strcmp(buffer, "avl")) {
			avl();
		}

	} while (strcmp(buffer, "exit"));

	return 0;
}
