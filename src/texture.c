/* texture.c: the texture handler. */
#include <SDL2/SDL_image.h>
#include "hashmap.h"
#include "texture.h"

void add_texture(game_t *game, const char *path, const char *name)
{
    texture_t *texture;
    SDL_Texture *t;
    SDL_Surface *s;

    s = IMG_Load(path);
    if (!s) fail("unable to load texture from %s", path); /* !__LINE__ */
    t = SDL_CreateTextureFromSurface(game->renderer, s);
    if (!t) fail("%s (%d): unable to create texture from %s", ORIGIN, path);


    texture = (texture_t *)malloc(sizeof(texture_t));
    if (!texture) {
        fail("%s (%d): unable to allocate texture: %s", ORIGIN, name);
        return; /* never reached */
    }

    texture->name = name;
    texture->tex = t;
    append_texture(game, texture);

    SDL_FreeSurface(s);
}

void append_texture(game_t *g, texture_t *t)
{
    g->num_textures++;
    debug_log("%s (%d): added %d", ORIGIN, g->num_textures);
    add_texture_to_map(g->textures, (void *)t);
}

void render_all_textures(game_t *g, SDL_Rect *src, SDL_Rect *dest)
{
    int i;
    node_t *head;
    node_t *node;
    texture_t *tex;

    for (i = 0; i < MAPSIZE; i++) {
        head = (*g->textures)[i];
        for (node = head; node != NULL; node = node->next) {
            tex = (texture_t *)(node->data);
            SDL_RenderCopy(g->renderer, tex->tex, src, dest);
        }
    }
}

void render_texture(game_t *g, const char *name, SDL_Rect *src, SDL_Rect *dest)
{
    unsigned int h;
    node_t *head;
    node_t *node;
    texture_t *tex;

    h = hash(name);
    head = (*g->textures)[h];
    for (node = head; node != NULL; node = node->next) {
        tex = (texture_t *)(node->data);
        if (!strcmp(tex->name, name))
            SDL_RenderCopy(g->renderer, tex->tex, src, dest);
    }
}

void free_textures(game_t *g)
{
    int i;
    node_t *head;
    node_t *next;
    texture_t *tex;

    for (i = 0; i < MAPSIZE; i++) {
        head = (*g->textures)[i];
        for (next = head; next != NULL; next = next->next) {
            tex = (texture_t *)next->data;
            SDL_DestroyTexture(tex->tex);
            free(tex);
        }
        free_list(head);
    }
    free(g->textures);
}
