#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL2/SDL.h>
#include "game.h"
#include "utils.h"

void add_texture(game_t *, const char *, const char *);
void append_texture(game_t *, texture_t *);
void free_textures(game_t *);
void render_all_textures(game_t *, SDL_Rect *, SDL_Rect *);
void render_texture(game_t *, const char *, SDL_Rect *, SDL_Rect *);

#endif /* _TEXTURE_H_ */
