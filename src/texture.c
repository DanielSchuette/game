/* texture.c: the texture handler. */
#include <SDL2/SDL_image.h>
#include "hashmap.h"
#include "texture.h"

void add_texture(game_t *game, const char *path, const char *name,
                 int width, int height, SDL_Rect *src_rect)
{
    texture_t *texture;
    SDL_Texture *t;
    SDL_Surface *s;
    SDL_Rect *dest_rect;

    s = IMG_Load(path);
    if (!s) fail("unable to load texture from %s", path);
    t = SDL_CreateTextureFromSurface(game->renderer, s);
    if (!t) fail("unable to create texture from %s", path);


    texture = (texture_t *)malloc(sizeof(texture_t));
    if (!texture) {
        fail("unable to allocate texture: %s", name);
        return; /* never reached */
    }

    dest_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    dest_rect->w = width;
    dest_rect->h = height;
    dest_rect->x = dest_rect->y = 0;

    texture->name = name;
    texture->tex = t;
    texture->src = src_rect; /* provided by the caller bc it might be NULL */
    texture->dest = dest_rect;

    append_texture(game, texture);

    SDL_FreeSurface(s);
}

void append_texture(game_t *g, texture_t *t)
{
    g->num_textures++;
    add_texture_to_map(*(g->textures), (void *)t);
}

void render_all_textures(game_t *g)
{
    int i;
    node_t *head;
    node_t *node;
    texture_t *tex;

    for (i = 0; i < MAPSIZE; i++) {
        head = (*g->textures)[i];
        for (node = head; node != NULL; node = node->next) {
            tex = (texture_t *)node->data;
            SDL_RenderCopy(g->renderer, tex->tex, tex->src, tex->dest);
        }
    }
}

void render_texture(game_t *g, const char *name)
{

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
            free(tex->src);
            free(tex->dest);
            free(tex);
        }
        free_list(head);
    }
    free(g->textures);
}
