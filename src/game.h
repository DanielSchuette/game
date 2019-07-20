#ifndef _GAME_H_
#define _GAME_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "hashmap.h"

#define WIDTH  800
#define HEIGHT 600
#define MAX_TEXTURES 1024

/*
 * All struct definitions and typedefs are done here to avoid circular
 * dependencies between header files.
 */
typedef struct texture_t {
    SDL_Texture *tex;   /* the actual SDL texture */
    const char *name;   /* should be a unique identifier */
} texture_t;

typedef struct game_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    hashmap_t *textures;    /* textures are saved in a hashmap */
    int num_textures;       /* the total number of textures */
    bool active;            /* false if main loop should terminate */
    int framerate;
} game_t;

game_t *init_game(const char *, int, int, int, int, bool, unsigned int);
void load_assets(game_t *, const char *, const char *);
void handle_events(game_t *);
void quit_game(game_t *);
bool is_active(game_t *);
void update(game_t *);
void render(game_t *);
void adjust_framerate(game_t *, unsigned int, unsigned int);

#endif /* _GAME_H_ */
