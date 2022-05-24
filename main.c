#include "redBlack.h"
#include "splay.h"
#include <string.h>

void redBlack() {
	RedBlackTree rbt = NULL;

	printf("INSERTION\n");
	for (int i = 0; i < 15; ++i) {
		int elem = rand() % 50;
		redBlackNode *node = initNode(elem);
		printf("To be inserted: %d\n", elem);

		rbt = insert(rbt, node);

		printf("BEFORE BALANCING\n");
		printInorderTraversal(rbt, 0, 0);
		printf("\n");
		rbt = balance(rbt, node);

		printf("AFTER BALANCING\n");
		printInorderTraversal(rbt, 0, 0);
		printf("\n");
	}

	printf("SEARCH\n");
	for (int i = 0; i < 30; ++i) {
		redBlackNode *search = searchTree(rbt, rand() % 50);
		if (search != NULL) {
			printf("found: %d\n", *(int *)(search->data));
		}
	}

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

	st = freeSplay(st);
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

	} while (strcmp(buffer, "exit"));

	return 0;
}
