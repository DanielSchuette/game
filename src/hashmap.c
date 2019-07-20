/* hasmap.c: a hashmap implementation. */
#include <string.h>
#include "game.h"
#include "hashmap.h"

/* FIXME: is this hashing function any good? */
unsigned int hash(const char *s)
{
    int i;
    int len;
    unsigned int sum;

    sum = 0;
    len = strlen(s);
    for (i = 0; i < len; i++)
        sum += s[i];

    return sum % MAPSIZE;
}

/* add_texture_to_map: make sure to only use texture here. */
void add_texture_to_map(hashmap_t map, void *texture)
{
    unsigned int h;
    texture_t *tex;
    node_t *node;

    tex = (texture_t *)texture;
    h = hash(tex->name);
    node = (node_t *)malloc(sizeof(node_t));
    map[h] = add_node(map[h], node);
}

/*
 * TODO:
 * - remove_texture_from_map()
 * - replace uses of MAPSIZE with a macro/iterator
 */
