#include "treap.h"

int compareIntsTreap(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

treapNode* initNodeTreap(void *data) {
	treapNode *node = (treapNode *) malloc(sizeof(treapNode));
	node->data = (void *) malloc(sizeof(int));
	memcpy(node->data, data, sizeof(int));
	node->priority = rand() % 30;
	node->left = NULL;
	node->right = NULL;
	return node;
}

treapNode* rotateLeftTreap(treapNode *node) {
	treapNode *tmp = node->right;
	treapNode *snd = tmp->left;

	tmp->left = node;
	node->right = snd;

	return tmp;
}

treapNode* rotateRightTreap(treapNode *node) {
	treapNode *tmp = node->left;
	treapNode *snd = tmp->right;

	tmp->right = node;
	node->left = snd;

	return tmp;
}

treapNode* searchTreap(Treap trp, void *data) {
	if (trp == NULL || !compareIntsTreap(trp->data, data)) {
		return trp;
	}

	if (compareIntsTreap(trp->data, data) < 0) {
		return searchTreap(trp->right, data);
	}

	return searchTreap(trp->left, data);
}

Treap insertTreap(Treap trp, treapNode *node) {
	if (trp == NULL) {
		return node;
	}

	if (compareIntsTreap(node->data, trp->data) < 0) {
		trp->left = insertTreap(trp->left, node);

		if (trp->left->priority > trp->priority) {
			trp = rotateRightTreap(trp);
		}
	} else {
		trp->right = insertTreap(trp->right, node);

		if (trp->right->priority > trp->priority) {
			trp = rotateLeftTreap(trp);
		}
	}

	return trp;
}

Treap deleteTreap(Treap trp, void *data) {
	if (trp == NULL) {
		return trp;
	}

	// in left subtree
	if (compareIntsTreap(data, trp->data) < 0) {
		trp->left = deleteTreap(trp->left, data);

	// in right subtree
	} else if (compareIntsTreap(data, trp->data) > 0) {
		trp->right = deleteTreap(trp->right, data);

	// in root and left subtree null
	} else if (trp->left == NULL) {
		treapNode *tmp = trp->right;
		free(trp);
		trp = tmp;

	// in root and right subtree null
	} else if (trp->right == NULL) {
		treapNode *tmp = trp->left;
		free(trp);
		trp->left = tmp;

	// in root and both subtrees != null rotate based on priority
	} else if (trp->left->priority < trp->right->priority) {
		trp = rotateLeftTreap(trp);
		trp->left = deleteTreap(trp->left, data);
	} else {
		trp = rotateRightTreap(trp);
		trp->right = deleteTreap(trp->right, data);
	}

	return trp;
}

void printInorderTraversalTreap(Treap trp) {
	if (trp == NULL) {
		return;
	}

	printInorderTraversalTreap(trp->left);

	printf("NODE: %d - Priority: %d ", *(int *)(trp->data), trp->priority);
	if (trp->left) {
		printf("| left: %d ", *(int *)(trp->left->data));
	}
	if (trp->right) {
		printf("| right: %d", *(int *)(trp->right->data));
	}
	printf("\n");

	printInorderTraversalTreap(trp->right);
}

Treap freeTreap(Treap trp) {
	if (trp == NULL) {
		return trp;
	}

	treapNode *save = trp;
	freeTreap(trp->left);
	freeTreap(trp->right);
	free(save->data);
	free(save);
	return NULL;
}