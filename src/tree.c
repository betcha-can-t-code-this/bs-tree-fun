#include <assert.h>
#include <stdlib.h>
#include "tree.h"

static tree_t *tree_create(uitem_t data)
{
	tree_t *tree = malloc(sizeof(tree_t));

	if (tree == NULL) {
		return NULL;
	}

	TREE_ASSIGN_ITEM(tree, data);
	TREE_ASSIGN(TREE_LEFT(tree), NULL);
	TREE_ASSIGN(TREE_RIGHT(tree), NULL);
	TREE_ASSIGN(TREE_PARENT(tree), NULL);

	return tree;
}

static void tree_set_parent(tree_t *tree, tree_t *parent)
{
	TREE_ASSIGN(TREE_PARENT(tree), parent);
}

static void tree_transplant(tree_t **tree, tree_t *a, tree_t *b)
{
	// if 'a' is root of 'tree'.
	if (TREE_PARENT(a) == NULL) {
		TREE_ASSIGN(*(tree), b);
	}

	// if a == a->parent->left,
	// update a->parent->left to b
	if (a == TREE_LEFT(TREE_PARENT(a))) {
		TREE_ASSIGN(TREE_LEFT(TREE_PARENT(a)), b);
	}

	// if a == a->parent->right,
	// update a->parent->right to b
	if (a == TREE_RIGHT(TREE_PARENT(a))) {
		TREE_ASSIGN(TREE_RIGHT(TREE_PARENT(a)), b);
	}

	// if b != NULL, set b->parent = a->parent
	if (b != NULL) {
		TREE_ASSIGN(TREE_PARENT(b), TREE_PARENT(a));
	}
}

void tree_insert(tree_t **tree, uitem_t data)
{
	tree_t *new;
	tree_t *tmp = (*tree);
	tree_t *current = *(tree);

	while (current != NULL) {
		TREE_ASSIGN(tmp, current);
		TREE_ASSIGN(
			current,
			TREE_COMPARE_LT(current, data) ? TREE_LEFT(current) : TREE_RIGHT(current)
		);
	}

	assert((new = tree_create(data)) != NULL);
	tree_set_parent(new, tmp);

	if (tmp == NULL) {
		*(tree) = new;
		return;
	}

	if (TREE_COMPARE_LT(tmp, data)) {
		TREE_ASSIGN(TREE_LEFT(tmp), new);
	} else {
		TREE_ASSIGN(TREE_RIGHT(tmp), new);
	}
}

void tree_recursive_insert(tree_t **tree, uitem_t data)
{
	if (*(tree) == NULL) {
		assert((*(tree) = tree_create(data)) != NULL);
		return;
	}

	if (TREE_COMPARE_LT(*(tree), data)) {
		tree_insert(TREE_LEFT_REF(*(tree)), data);
		tree_set_parent(TREE_LEFT(*(tree)), *(tree));
	} else {
		tree_insert(TREE_RIGHT_REF(*(tree)), data);
		tree_set_parent(TREE_RIGHT(*(tree)), *(tree));
	}
}

void tree_delete(tree_t **tree, uitem_t item)
{
	tree_t *tmp, *x;

	if ((tmp = tree_search(*(tree), item)) == NULL) {
		return;
	}

	if (TREE_LEFT(tmp) == NULL) {
		tree_transplant(tree, tmp, TREE_RIGHT(tmp));
		goto done;
	}

	if (TREE_RIGHT(tmp) == NULL) {
		tree_transplant(tree, tmp, TREE_LEFT(tmp));
		goto done;
	}

	x = tree_minimum(TREE_RIGHT(tmp));

	if (TREE_PARENT(x) != tmp) {
		tree_transplant(tree, x, TREE_RIGHT(x));
		TREE_ASSIGN(TREE_RIGHT(x), TREE_RIGHT(tmp));
		TREE_ASSIGN(TREE_PARENT(TREE_RIGHT(x)), x);
	}

	tree_transplant(tree, tmp, x);
	TREE_ASSIGN(TREE_LEFT(x), TREE_LEFT(tmp));
	TREE_ASSIGN(TREE_PARENT(TREE_LEFT(x)), x);

done:
	// release memory of removed node.
	free(tmp);
}

tree_t *tree_search(tree_t *tree, uitem_t data)
{
	if (tree == NULL) {
		return NULL;
	}

	if (TREE_COMPARE_EQ(tree, data)) {
		return tree;
	}

	return TREE_COMPARE_LT(tree, data)
		? tree_search(TREE_LEFT(tree), data)
		: tree_search(TREE_RIGHT(tree), data);
}

tree_t *tree_iterative_search(tree_t *tree, uitem_t data)
{
	while (tree != NULL && TREE_COMPARE_NEQ(tree, data)) {
		tree = TREE_COMPARE_LT(tree, data)
			? TREE_LEFT(tree)
			: TREE_RIGHT(tree);
	}

	return tree;
}

tree_t *tree_minimum(tree_t *tree)
{
	while (TREE_LEFT(tree) != NULL) {
		tree = TREE_LEFT(tree);
	}

	return tree;
}

tree_t *tree_recursive_minimum(tree_t *tree)
{
	if (TREE_LEFT(tree) != NULL) {
		tree = tree_recursive_minimum(TREE_LEFT(tree));
	}

	return tree;
}

tree_t *tree_maximum(tree_t *tree)
{
	while (TREE_RIGHT(tree) != NULL) {
		tree = TREE_RIGHT(tree);
	}

	return tree;
}

tree_t *tree_recursive_maximum(tree_t *tree)
{
	if (TREE_RIGHT(tree) != NULL) {
		tree = tree_recursive_maximum(TREE_RIGHT(tree));
	}

	return tree;
}

tree_t *tree_successor(tree_t *tree)
{
	if (TREE_RIGHT(tree) != NULL) {
		return tree_minimum(TREE_RIGHT(tree));
	}

	tree_t *tmp = TREE_PARENT(tree);

	while (tmp != NULL && tree == TREE_RIGHT(tmp)) {
		tree = tmp;
		tmp = TREE_PARENT(tree);
	}

	return tmp;
}

tree_t *tree_predecessor(tree_t *tree)
{
	if (TREE_LEFT(tree) != NULL) {
		return tree_maximum(TREE_LEFT(tree));
	}

	tree_t *tmp = TREE_PARENT(tree);

	while (tmp != NULL && tree == TREE_LEFT(tmp)) {
		tree = tmp;
		tmp = TREE_PARENT(tree);
	}

	return tmp;
}

void tree_inorder_walk(tree_t *tree, void (*visitor)(uitem_t item))
{
	if (tree == NULL) {
		return;
	}

	tree_inorder_walk(TREE_LEFT(tree), visitor);
	visitor(TREE_FETCH_ITEM(tree));
	tree_inorder_walk(TREE_RIGHT(tree), visitor);
}

void tree_preorder_walk(tree_t *tree, void (*visitor)(uitem_t item))
{
	if (tree == NULL) {
		return;
	}

	visitor(TREE_FETCH_ITEM(tree));
	tree_preorder_walk(TREE_LEFT(tree), visitor);
	tree_preorder_walk(TREE_RIGHT(tree), visitor);
}

void tree_postorder_walk(tree_t *tree, void (*visitor)(uitem_t item))
{
	if (tree == NULL) {
		return;
	}

	tree_postorder_walk(TREE_LEFT(tree), visitor);
	tree_postorder_walk(TREE_RIGHT(tree), visitor);
	visitor(TREE_FETCH_ITEM(tree));
}

void tree_free_mem(tree_t *tree)
{
	if (tree == NULL) {
		return;
	}

	tree_free_mem(TREE_LEFT(tree));
	tree_free_mem(TREE_RIGHT(tree));
	free(tree);
}
