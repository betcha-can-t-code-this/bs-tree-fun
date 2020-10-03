#ifndef __TREE_H__
#define __TREE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef unsigned int uitem_t;

typedef struct tree {
	uitem_t item;
	struct tree *left;
	struct tree *parent;
	struct tree *right;
} tree_t;

#define TREE_LEFT(tree) ((tree)->left)
#define TREE_RIGHT(tree) ((tree)->right)
#define TREE_PARENT(tree) ((tree)->parent)

#define TREE_LEFT_REF(tree)	(&(TREE_LEFT(tree)))
#define TREE_RIGHT_REF(tree)	(&(TREE_RIGHT(tree)))
#define TREE_PARENT_REF(tree)	(&(TREE_PARENT(tree)))

#define TREE_ASSIGN(tree, val)	((tree) = (val))
#define TREE_ASSIGN_ITEM(tree, val)	((tree)->item = (val))
#define TREE_FETCH_ITEM(tree)	((tree)->item)

#define TREE_COMPARE_EQ(tree, data)	(data == TREE_FETCH_ITEM(tree))
#define TREE_COMPARE_NEQ(tree, data)	(data != TREE_FETCH_ITEM(tree))
#define TREE_COMPARE_LT(tree, data)	(data < TREE_FETCH_ITEM(tree))
#define TREE_COMPARE_GT(tree, data)	(data > TREE_FETCH_ITEM(tree))

void tree_insert(tree_t **tree, uitem_t data);
void tree_recursive_insert(tree_t **tree, uitem_t data);
void tree_delete(tree_t **delete, uitem_t item);
tree_t *tree_search(tree_t *tree, uitem_t data);
tree_t *tree_iterative_search(tree_t *tree, uitem_t data);
tree_t *tree_minimum(tree_t *tree);
tree_t *tree_recursive_minimum(tree_t *tree);
tree_t *tree_maximum(tree_t *tree);
tree_t *tree_recursive_maximum(tree_t *tree);
tree_t *tree_successor(tree_t *tree);
tree_t *tree_predecessor(tree_t *tree);
void tree_inorder_walk(tree_t *tree, void (*visitor)(uitem_t item));
void tree_preorder_walk(tree_t *tree, void (*visitor)(uitem_t item));
void tree_postorder_walk(tree_t *tree, void (*visitor)(uitem_t item));
void tree_free_mem(tree_t *tree);

#ifdef __cplusplus
}
#endif

#endif /* __TREE_H__ */
