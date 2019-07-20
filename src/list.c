/* list.c: a singly-linked list implementation. */
#include <stdlib.h>
#include "list.h"
#include "utils.h"

node_t *add_node(node_t *head, node_t *new)
{
    node_t *p;

    if (head == NULL)
        return new;

    for (p = head; p->next != NULL; p = p->next)
        ;
    p->next = new;
    new->next = NULL; /* just in case */
    return head;
}

void free_list(node_t *head)
{
    node_t *p;
    node_t *tmp;

    for (p = head; p != NULL;) {
        tmp = p->next;
        free(p);
        p = tmp;
    }
}

/*
 * TODO:
 * - remove_node()
 */
