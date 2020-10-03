#include <stdio.h>
#include "./src/tree.h"

#define UNUSED(x)	((void)(x))

static void callback(uitem_t item)
{
	printf("%u ", item);
}

int main(int argc, char **argv)
{
	UNUSED(argc);
	UNUSED(argv);

	tree_t *tree = NULL;
	tree_t *tmp;
	uitem_t data[] = {49, 6, 17, 10, 47, 87, 34, 17, 6, 82};
	int i;

	for (i = 0; i < 10; i++) {
		tree_recursive_insert(&tree, data[i]);
	}

	tmp = tree_search(tree, 49);

	if (tmp != NULL) {
		printf("(recursive) tmp->item: %d\n", tmp->item);
	}

	tmp = tree_search(tree, 4);

	if (tmp != NULL) {
		printf("(recursive) tmp->item: %d\n", tmp->item);
	}

	tmp = tree_iterative_search(tree, 49);

	if (tmp != NULL) {
		printf("(iterative) tmp->item: %d\n", tmp->item);
	}

	tmp = tree_iterative_search(tree, 600);

	if (tmp != NULL) {
		printf("(iterative) tmp->item: %d\n", tmp->item);
	}

	tmp = tree_minimum(tree);
	printf("(iterative) minimum: %d\n", tmp->item);

	tmp = tree_maximum(tree);
	printf("(iterative) maximum: %d\n", tmp->item);

	tmp = tree_recursive_minimum(tree);
	printf("(recursive) minimum: %d\n", tmp->item);

	tmp = tree_recursive_maximum(tree);
	printf("(recursive) maximum: %d\n", tmp->item);

	tmp = tree_search(tree, 47);

	if (tmp != NULL) {
		printf("%d is exists in search-tree, and it's successor is: ", tmp->item);

		tmp = tree_successor(tmp);
		printf("%d\n", tmp->item);
	}

	tmp = tree_search(tree, 47);

	if (tmp != NULL) {
		printf("%d is exists in search-tree, and it's predecessor is: ", tmp->item);

		tmp = tree_predecessor(tmp);
		printf("%d\n", tmp->item);
	}

	printf("(inorder) ");
	tree_inorder_walk(tree, callback);
	printf("\n");

	printf("(preorder) ");
	tree_preorder_walk(tree, callback);
	printf("\n");

	printf("(postorder) ");
	tree_postorder_walk(tree, callback);
	printf("\n");

	tree_delete(&tree, 47);

	printf("(inorder) after removing 47 from tree ");
	tree_inorder_walk(tree, callback);
	printf("\n");

	tree_delete(&tree, 6);

	printf("(inorder) after removing 6 from tree ");
	tree_inorder_walk(tree, callback);
	printf("\n");

	tree_delete(&tree, 6);

	printf("(inorder) after removing 6 again from tree ");
	tree_inorder_walk(tree, callback);
	printf("\n");

	tree_free_mem(tree);
	return 0;
}
