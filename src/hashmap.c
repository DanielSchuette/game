/* hasmap.c: a hashmap implementation. */
#include <string.h>
#include "game.h"
#include "hashmap.h"
#include "utils.h"

/* FIXME: is this hashing function any good? */
unsigned int hash(const char *s)
{
    unsigned int i, len, h;

    len = strlen(s);
    h = 0;
    for (i = 0; i < len; i++)
        h = h * 31 + s[i];

    return h % MAPSIZE;
}

/* init_map: initialize map points to NULL. */
void init_map(hashmap_t *map)
{
    int i;

    for (i = 0; i < MAPSIZE; i++)
        (*map)[i] = NULL;
}

/* add_texture_to_map: make sure to only use texture here. */
void add_texture_to_map(hashmap_t *map, void *texture)
{
    unsigned int h;
    texture_t *tex;
    node_t *node;

    tex = (texture_t *)texture;
    h = hash(tex->name);
    debug_log("%s (%d): adding %s (%d) texture", ORIGIN, tex->name, h);
    node = (node_t *)malloc(sizeof(node_t));
    node->data = texture;
    (*map)[h] = add_node((*map)[h], node);
}

/*
 * TODO:
 * - remove_texture_from_map()
 * - replace uses of MAPSIZE with a macro/iterator
 */
