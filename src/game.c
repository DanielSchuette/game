/* game.c: functions handling the game. */
#include "game.h"
#include "texture.h"
#include "utils.h"

/* init_game: create a new game. */
game_t *init_game(const char *title, int x_pos, int y_pos,
                 int width, int height, bool fullscreen)
{
    int flags;
    SDL_Window *w;
    SDL_Renderer *r;
    game_t *g;
    hashmap_t *hm;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) /* SDL_INIT_EVERYTHING ? */
        fail("failed to initialize SDL: %s", SDL_GetError());

    flags = SDL_WINDOW_SHOWN;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    w = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
    if (!w) fail("failed to create window");

    r = SDL_CreateRenderer(w, -1, 0);
    if (!r) fail("failed to create renderer");
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

    g = (game_t *)malloc(sizeof(game_t));
    if (!g) {
        fail("failed to allocate game");
        return NULL; /* never reached */
    }

    hm = (hashmap_t *)malloc(sizeof(hashmap_t));

    /* initialize game state */
    g->active = true;
    g->renderer = r;
    g->window = w;
    g->textures = hm;
    g->num_textures = 0;
    g->framerate = 60;

    return g;
}

/* TODO: load assets from an asset table and initialize them */
void load_assets(game_t *g, const char *table)
{
    add_texture(g, table, "bearded_man", 128, 128, NULL);
}

/* update: update the game. */
void update(game_t *game)
{
    return;
}

/* render: render the game. */
void render(game_t *game)
{
    /* clear the screen */
    SDL_RenderClear(game->renderer);

    /* render textures to the screen */
    render_all_textures(game);
    render_texture(game, "bearded_man");

    /* render to the screen */
    SDL_RenderPresent(game->renderer);
}


/* handle_events: handle only events on the queue. */
void handle_events(game_t *game)
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            game->active = false;
            break;
        case SDL_KEYDOWN: /* handle all key press events */
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
#ifdef ENABLE_ESC_QUIT
                game->active = false;
#endif
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

/* is_active: determine if a game is still active or ready to quit. */
bool is_active(game_t *game)
{
    return game->active;
}

/* quit_game: free all resources and quit the game. */
void quit_game(game_t *game)
{
    SDL_Quit();                             /* quit all SDL subsystems */
    SDL_DestroyRenderer(game->renderer);    /* free the renderer */
    SDL_DestroyWindow(game->window);        /* free the game window */
    free_textures(game);                    /* free texture-associated mem */
    free(game);                             /* frees the game */
}

/* adjust_framerate: slow down the game if necessary. */
void adjust_framerate(game_t *g, unsigned int start, unsigned int end)
{
    unsigned int time;
    unsigned int diff;

    time = 1000/g->framerate;
    diff = end - start;
    if (diff < time)
        SDL_Delay(time-diff);
}
