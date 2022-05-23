#include "redBlack.h"
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

int main(int argc, char const *argv[]) {
	char buffer[16];
	do {
		scanf("%s", buffer);

		if (!strcmp(buffer, "rbt")) {
			redBlack();
		}
	} while (strcmp(buffer, "exit"));

	return 0;
}
