/**
 * @file    list.h
 * @author  S4MasterRace
 * @version 1.0
 * @brief   Intrusive list implement
 */

#ifndef TAITRIS_LIST_H
#define TAITRIS_LIST_H

#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

/** Head of a singly-linked list. */
struct list {
  size_t length; /**< List length. */
  struct list_node *first; /**< First node. */
};

/** A node of a singly-linked list. */
struct list_node {
  struct list_node *next; /**< Next node. */
};

/**
 * Initializes the list.
 *
 * @param list a list.
 *
 * @pre `list` must be not NULL.
 *
 * @post `list` is empty.
 * @post `list` has a size of 0.
 *
 * @remarks Complexity: O(1)
 */
extern inline
void list_init(struct list *list);

/**
 * Returns the size of the list.
 *
 * @param list a list.
 * @return the length of the list.
 *
 * @pre `list` must be not NULL.
 *
 * @remarks Complexity: O(1)
 */
extern inline
size_t list_length(const struct list *list);

/**
 * Returns the first node.
 *
 * @param list a list.
 * @return the first node.
 *
 * @pre `list` must be not NULL.
 * @pre `list` must be not empty.
 *
 * @remarks Complexity: O(1)
 */
extern inline
struct list_node *list_first(const struct list *list);

/**
 * Returns the last node.
 *
 * @param list a list.
 * @return the last node.
 *
 * @pre `list` must be not NULL.
 *
 * @remarks Complexity: O(N)
 */
extern inline
struct list_node *list_last(const struct list *list);

/**
 * Returns the next node.
 *
 * @param node a node.
 * @return the next node.
 *
 * @pre `node` must be not NULL.
 *
 * @remarks Complexity: O(1)
 */
extern inline
struct list_node *list_next(const struct list_node *node);

/**
 * Returns the nth-node after the current one.
 *
 * @param node     a node.
 * @param distance distance to move on.
 * @return the nth-node after `node`.
 *
 * @pre `node` must be not NULL.
 *
 * @remarks Complexity: O(n)
 */
extern inline
struct list_node *list_advance(struct list_node *node, size_t distance);

/**
 * Returns node at the position `pos`.
 *
 * @param list a list.
 * @param pos  position (0-based) of the node.
 * @return the node at the position `pos`.
 *
 * @pre `list` must be not NULL.
 * @pre `list` must be not empty.
 * @pre `pos` must be in [0; list_length(list)[.
 *
 * @remarks Complexity: O(N)
 */
extern inline
struct list_node *list_at(const struct list *list, size_t pos);

/**
 * Returns a pointer to the structure which contains the node.
 *
 * @param node      a list node (struct list_node*).
 * @param type      type of the structure which contains the node.
 * @param fieldname name of the node (field name) in the structure.
 *
 * @pre `node` must be not NULL.
 *
 * @remarks Complexity: O(1)
 */
#define list_elt(node, type, fieldname) \
    ((type*)((char*)(node) - offsetof(type, fieldname)))

/**
 * Reverses the order of the elements in the list.
 *
 * @param list a list.
 *
 * @pre `list` must be not NULL.
 *
 * @remarks Complexity: O(N)
 */
extern inline
void list_reverse(struct list *list);

/**
 * Swaps two lists.
 *
 * @param l1 list 1.
 * @param l2 list 2.
 *
 * @pre `l1` must be not NULL.
 * @pre `l2` must be not NULL.
 * @pre `l1` must be different of `l2`.
 *
 * @remarks Complexity: O(1)
 */
extern inline
void list_swap(struct list *l1, struct list *l2);

/**
 * Splits a list in two parts at the position `pos`.
 *
 * After the split:
 * \li `list` contains nodes in [0, pos[
 * \li `right` contains nodes in [pos,length(list)[
 *
 * Examples:
 * \code{.txt}
 * list = [1, 2, 3]
 * list_split_at(list, 0, right) => ([],[1,2,3])
 * list_split_at(list, 1, right) => ([1],[2,3])
 * list_split_at(list, 2, right) => ([1,2],[3])
 * list_split_at(list, 3, right) => ([1,2,3],[])
 * list = []
 * list_split_at(list, 0, right) => ([],[])
 * \endcode
 *
 * @param list     list to split.
 * @param pos      position (0-based) where to split the list.
 * @param right an empty list to receive the part after `pos`
 *
 * @pre `list` must be not NULL.
 * @pre `right` must be not NULL.
 * @pre `right` must be empty.
 * @pre `list` must be different of `right`.
 *
 * @remarks Complexity: O(N)
 */
extern inline
void list_split_at(struct list *list, size_t pos, struct list *right);

/**
 * Concatenates two lists.
 *
 * @param l1 list 1.
 * @param l2 list 2.
 *
 * @pre `l1` must be not NULL.
 * @pre `l2` must be not NULL.
 * @pre `l1` must be different of `l2`.
 *
 * @post `l2` is reset to an empty list.
 *
 * @remarks Complexity: O(N)
 */
extern inline
void list_concat(struct list *l1, struct list *l2);

/**
 * Sort a list using a comparison function.
 *
 * The contents of the list are sorted in ascending order according to a
 * comparison function which is called with two arguments that point to the node
 * being compared.
 *
 * The comparison function must return an integer less than, equal to, or
 * greater than zero if the first argument is considered to be respectively less
 * than, equal to, or greater than the second.
 *
 * If two members compare as equal, their order in the sorted list is preserved.
 *
 * @param list list to sort.
 * @param cmp  comparison function to use.
 *
 * @pre `list` must be not NULL.
 * @pre `cmp` must be not NULL.
 *
 * @remarks The sort is stable.
 * @remarks Complexity: O(N log N)
 * @remarks Space complexity: O(1)
 */
extern inline
void list_sort(
    struct list *list,
    int (*cmp)(struct list_node *, struct list_node *)
);

/**
 * Iterates over list (nodes).
 * @param list a list (struct list*).
 * @param curr a struct list_node* used to hold the current element.
 *
 * @pre `list` must be not NULL.
 * @pre `curr` must be not NULL.
 *
 * @remarks Complexity: O(N)
 */
#define list_foreach(list, curr) \
    for (curr = list_first(list); curr != NULL; curr = list_next(curr))

/**
 * Iterates over list (elements)
 * @param list      a list (struct list*).
 * @param curr      pointer (type*) used to hold the current element.
 * @param type      type of the structure which contains the node.
 * @param fieldname name of the node (field name) in the structure.
 *
 * @pre `list` must be not NULL.
 * @pre `list` must be not empty.
 * @pre `curr` must be not NULL.
 *
 * @remarks Complexity: O(N)
 */
#define list_foreach_elt(list, curr, type, fieldname)               \
    for (curr = list_elt(list_first(list), type, fieldname);       \
         curr != NULL;                           \
         curr = curr->fieldname.next == NULL ? NULL :           \
         list_elt(list_next(&(curr->fieldname)), type, fieldname))

/**
 * Iterates over list (nodes), allows deletion of the current node.
 * @param list a list (struct list*).
 * @param curr a struct list_node* used to hold the current element.
 * @param tmp  a struct list_node* used as temporary storage.
 *
 * @pre `list` must be not NULL.
 * @pre `curr` must be not NULL.
 * @pre `tmp` must be not NULL.
 *
 * @remarks Complexity: O(N)
 */
#define list_foreach_safe(list, curr, tmp)            \
    for (curr = list_first(list), tmp = list_next(curr);    \
         curr != NULL;                    \
         curr = tmp, tmp = tmp == NULL ? NULL : list_next(tmp))

/**
 * Iterates over list (elements), allows deletion of the current element.
 * @param list      a list (struct list*).
 * @param curr      pointer (type*) used to hold the current element.
 * @param tmp       a struct list_node* used as temporary storage.
 * @param type      type of the structure which contains the node.
 * @param fieldname name of the node (field name) in the structure.
 *
 * @pre `list` must be not NULL.
 * @pre `list` must be not empty.
 * @pre `curr` must be not NULL.
 *
 * @remarks Complexity: O(N)
 */
#define list_foreach_elt_safe(list, curr, tmp, type, fieldname)      \
    for (curr = list_elt(list_first(list), type, fieldname),      \
         tmp  = list_next(&(curr->fieldname));              \
         curr != NULL;                          \
         curr = tmp == NULL ? NULL : list_elt(tmp, type, fieldname), \
         tmp  = tmp == NULL ? NULL : list_next(tmp))          \

/**
 * Tests if a list is empty.
 *
 * @param list a list.
 * @return 1 if the list is empty, otherwise 0.
 *
 * @pre `list` must be not NULL.
 *
 * @remarks Complexity: O(1)
 */
extern inline
int list_is_empty(const struct list *list);

/**
 * Adds `node` in the front of `list`
 *
 * @param list a list.
 * @param node the new node.
 *
 * @pre `list` must be not NULL.
 * @pre `node` must be not NULL.
 *
 * @post List size increases by 1.
 *
 * @remarks Complexity: O(1)
 */
extern inline
void list_add(struct list *list, struct list_node *node);

/**
 * Adds `node` at the end of `list`.
 *
 * @param list a list.
 * @param node the new node.
 *
 * @pre `list` must be not NULL.
 * @pre `node` must be not NULL.
 *
 * @post List size increases by 1.
 *
 * @remarks Complexity: O(n)
 */
extern inline
void list_append(struct list *list, struct list_node *node);

/**
 * Inserts `node` at after the node `curr`.
 *
 * @param list a list.
 * @param curr a node of `list`.
 * @param node new node.
 *
 * @pre `list` must be not NULL.
 * @pre `curr` must be not NULL.
 * @pre `curr` must a node of `list`.
 * @pre `node` must be not NULL.
 *
 * @post List size increases by 1.
 *
 * @remarks Complexity: O(1)
 */
extern inline
void list_insert_after(
    struct list *list,
    struct list_node *curr,
    struct list_node *node
);

/**
 * Inserts `node` at the position `pos` in `list`.
 *
 * @param list a list.
 * @param node new node.
 * @param pos  position (0-based) where to insert the new node.
 *
 * @pre `list` must be not NULL.
 * @pre `node` must be not NULL.
 * @pre `pos` must be in [0; list_length(list)].
 *
 * @post List size increases by 1.
 *
 * @remarks Complexity: O(n)
 */
extern inline
void list_insert_at(struct list *list, struct list_node *node, size_t pos);

/**
 * Deletes the first node.
 *
 * @param list a list.
 *
 * @pre `list` must be not NULL.
 * @pre `list` must be not empty.
 *
 * @post List size decreases by 1.
 *
 * @remarks Complexity: O(1)
 */
extern inline
void list_del(struct list *list);

/**
 * Deletes the node at after the node `curr`.
 *
 * @param list a list.
 * @param node a node of `list`.
 *
 * @pre `list` must be not NULL.
 * @pre `node` must be not NULL.
 * @pre `list` must be not empty.
 * @pre `node` must a node of `list`.
 *
 * @post List size decreases by 1.
 *
 * @remarks Complexity: O(1)
 */
extern inline
void list_del_after(struct list *list, struct list_node *node);

/**
 * Deletes the node at the position `pos`.
 *
 * @param list a list.
 * @param pos  index (0-based) of the node to delete.
 *
 * @pre `list` must be not NULL.
 * @pre `list` must be not empty.
 * @pre `pos` must be in [0; list_length(list)[.
 *
 * @post List size decreases by 1.
 *
 * @remarks Complexity: O(n)
 */
extern inline
void list_del_at(struct list *list, size_t pos);

/**
 * Print the list
 *
 * @param list a list
 */
void list_print(const struct list *list);

#endif //TAITRIS_LIST_H
