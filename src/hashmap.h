#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "list.h"

#define MAPSIZE 1024

typedef node_t *hashmap_t[MAPSIZE];

unsigned int hash(const char *);
void add_texture_to_map(hashmap_t, void *);

#endif /*_HASHMAP_H_ */
