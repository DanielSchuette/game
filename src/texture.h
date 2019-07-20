#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL2/SDL.h>
#include "game.h"
#include "utils.h"

void add_texture(game_t *, const char *, const char *, int, int, SDL_Rect *);
void append_texture(game_t *, texture_t *);
void free_textures(game_t *);
void render_all_textures(game_t *);
void render_texture(game_t *, const char *);

#endif /* _TEXTURE_H_ */
