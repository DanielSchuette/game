#ifndef _LIST_H_
#define _LIST_H_

typedef struct node_t {
    void *data;             /* data associated with this node */
    struct node_t *next;    /* next node or NULL */
} node_t;

/* add_node: returns the new list head. */
node_t *add_node(node_t *, node_t *);

/* free_list: frees all list items, any data must be free elsewhere. */
void free_list(node_t *);

#endif /*_LIST_H_ */
