#include "list.h"

void list_init(struct list *list) {
  assert(list != NULL);

  list->length = 0;
  list->first = NULL;
}

size_t list_length(const struct list *list) {
  assert(list != NULL);

  return list->length;
}

struct list_node *list_first(const struct list *list) {
  assert(list != NULL);
  assert(list->length > 0);

  return list->first;
}

struct list_node *list_last(const struct list *list) {
  assert(list != NULL);
  assert(list->length > 0);

  return list_at(list, list->length - 1);
}

struct list_node *list_next(const struct list_node *node) {
  assert(node != NULL);

  return node->next;
}

struct list_node *list_advance(struct list_node *node, size_t distance) {
  assert(node != NULL);

  size_t i = 0;
  while (i < distance && node != NULL) {
    node = list_next(node);
    ++i;
  }

  return node;
}

struct list_node *list_at(const struct list *list, size_t pos) {
  assert(list != NULL);
  assert(list->length > 0);
  assert(pos < list->length);

  struct list_node *curr = list->first;
  size_t i = 0;

  while (i < pos) {
    curr = curr->next;
    ++i;
  }
  return curr;
}

void list_reverse(struct list *list) {
  assert(list != NULL);

  struct list_node *prev = NULL;
  struct list_node *next = NULL;
  struct list_node *curr = list->first;

  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  list->first = prev;
}

void list_swap(struct list *l1, struct list *l2) {
  assert(l1 != NULL);
  assert(l2 != NULL);
  assert(l1 != l2);

  struct list tmp;
  memcpy(&tmp, l1, sizeof *l1);
  memcpy(l1, l2, sizeof *l2);
  memcpy(l2, &tmp, sizeof tmp);
}

void list_split_at(struct list *list, size_t pos, struct list *right) {
  assert(list != NULL);
  assert(right != NULL);
  assert(right->length == 0);
  assert(list != right);

  if (pos > list_length(list))
    pos = list_length(list);

  if (pos == 0)
    list_swap(list, right);
  else if (pos == list_length(list));
  else {
    struct list_node *cutting_point = list_at(list, pos - 1);

    right->first = cutting_point->next;
    right->length = list->length - pos;

    cutting_point->next = NULL;
    list->length = pos;
  }
}

void list_concat(struct list *l1, struct list *l2) {
  assert(l1 != NULL);
  assert(l2 != NULL);
  assert(l1 != l2);

  if (list_is_empty(l1))
    list_swap(l1, l2);
  else {
    struct list_node *last = list_last(l1);

    last->next = l2->first;
    l2->first = NULL;

    l1->length += l2->length;
    l2->length = 0;
  }
}

void list_sort(
    struct list *list,
    int (*cmp)(struct list_node *, struct list_node *)
) {
  assert(list != NULL);
  assert(cmp != NULL);

  struct list_node *tail;
  struct list_node *p;
  struct list_node *p_end;
  struct list_node *q;
  struct list_node *q_end;
  size_t run_size;
  size_t length = list->length;

  for (run_size = 1; run_size < length; run_size *= 2) {
    p = list->first;
    tail = NULL;

    while (p != NULL) {
      struct list_node *node;

      q = list_advance(p, run_size);
      p_end = q;

      q_end = q == NULL ? NULL : list_advance(q, run_size);

      while (p != p_end || q != q_end) {
        if (q == q_end || (p != p_end && cmp(p, q) <= 0)) {
          node = p;
          p = p->next;
        } else {
          node = q;
          q = q->next;
        }

        if (tail != NULL)
          tail->next = node;
        else
          list->first = node;
        tail = node;
      }

      p = q_end;
      tail->next = NULL;
    }
  }
}

int list_is_empty(const struct list *list) {
  assert(list != NULL);

  return list->length == 0;
}

void list_add(struct list *list, struct list_node *node) {
  assert(list != NULL);
  assert(node != NULL);

  node->next = list->first;
  list->first = node;
  list->length++;
}

void list_append(struct list *list, struct list_node *node) {
  assert(list != NULL);
  assert(node != NULL);

  if (list_is_empty(list))
    list_add(list, node);
  else
    list_insert_after(list, list_last(list), node);
}

void list_insert_after(
    struct list *list,
    struct list_node *curr,
    struct list_node *node
) {
  assert(list != NULL);
  assert(curr != NULL);
  assert(node != NULL);

  node->next = curr->next;
  curr->next = node;
  list->length++;
}

void list_insert_at(struct list *list, struct list_node *node, size_t pos) {
  assert(list != NULL);
  assert(node != NULL);
  assert(pos <= list->length);

  if (pos == 0)
    list_add(list, node);
  else {
    struct list_node *curr = list_at(list, pos - 1);
    list_insert_after(list, curr, node);
  }
}

void list_del(struct list *list) {
  assert(list != NULL);
  assert(list->length > 0);

  list->first = list->first->next;
  list->length--;
}

void list_del_after(struct list *list, struct list_node *node) {
  assert(list != NULL);
  assert(node != NULL);
  assert(list->length > 0);

  node->next = node->next->next;
  list->length--;
}

void list_del_at(struct list *list, size_t pos) {
  assert(list != NULL);
  assert(list->length > 0);
  assert(pos < list->length);

  if (pos == 0)
    list_del(list);
  else {
    struct list_node *curr = list_at(list, pos - 1);
    list_del_after(list, curr);
  }
}

void list_print(const struct list *list)
{
  assert(list != NULL);

  printf("List length: %zu\n", list->length);
  printf("List first: %p\n", list->first);

  size_t i = 0;
  struct list_node *curr = list->first;

  while (curr != NULL) {
    if (i == 0) printf("\n");

    printf("[%zu] %p (next: %p)\n", i, curr, curr->next);
    i++;
    curr = curr->next;
  }

  printf("\n");
}