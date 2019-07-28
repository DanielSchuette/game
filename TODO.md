# To-Do
- add game object:

```c
/*
 * the `game' object should store a list of game_obj_t
 * to be able to free resources.
 */
typedef struct GOBJ {
    int xpos, ypos;                               /* 2D position of object */
    int width, height;                            /* used for texture scaling */
    char *texture;                                /* *must* be in game hashmap */
    void (*update)(struct GOBJ *self, void *);    /* ptr to update func */
    void (*render)(struct GOBJ *self, void *);    /* ptr to render func */
    void (*free_obj)(struct GOBJ *self, void *);  /* ptr to free func */
} game_obj_t;

/* call func ptrs as follows: */
PLAYER_ARGS args = { _newx = 7, _newy = 12 }; /* PLAYER_ARGS is a custom type */
player->update(player, (void *)args);
```
