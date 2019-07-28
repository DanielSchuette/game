/* game.c: functions handling the game. */
#include "game.h"
#include "texture.h"
#include "utils.h"

bool llama_up = true;

/* init_game: create a new game. */
game_t *init_game(const char *title, int x_pos, int y_pos,
                 int width, int height, bool fullscreen, unsigned int framerate)
{
    int wflags, rflags;
    SDL_Window *w;
    SDL_Renderer *r;
    game_t *g;
    hashmap_t *hm;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) /* SDL_INIT_EVERYTHING ? */
        fail("%s (%d): failed to initialize SDL: %s", ORIGIN, SDL_GetError());

    wflags = SDL_WINDOW_SHOWN;
    if (fullscreen) wflags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    w = SDL_CreateWindow(title, x_pos, y_pos, width, height, wflags);
    if (!w) fail("%s (%d): failed to create window", ORIGIN);

    rflags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    r = SDL_CreateRenderer(w, -1, rflags);
    if (!r) fail("%s (%d): failed to create renderer", ORIGIN);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

    g = (game_t *)malloc(sizeof(game_t));
    if (!g) {
        fail("%s (%d): failed to allocate game", ORIGIN);
        return NULL; /* never reached */
    }

    hm = (hashmap_t *)malloc(sizeof(hashmap_t));
    init_map(hm);

    /* initialize game state */
    g->active = true;
    g->renderer = r;
    g->window = w;
    g->textures = hm;
    g->num_textures = 0;
    g->framerate = framerate;

    return g;
}

/* TODO: load assets from an asset table and initialize them */
void load_assets(game_t *g, const char *table, const char *name)
{
    add_texture(g, table, name);
}

/* update: update the game. */
void update(game_t *game)
{
    return;
}

/* render: render the game. */
void render(game_t *game)
{
    static int frame = 1;
    SDL_Rect src, dest;

    /* clear the screen */
    SDL_RenderClear(game->renderer);

    /* render textures to the screen */
    switch (frame++) {
    case 5:
        src.x = 1;
        src.y = 2;
        break;
    case 4:
        src.x = 0;
        src.y = 2;
        break;
    case 3:
        src.x = 1;
        src.y = 1;
        break;
    case 2:
        src.x = 0;
        src.y = 1;
        break;
    case 1:
        src.x = 1;
        src.y = 0;
        break;
    case 0:
        src.x = src.y = 0;
        break;
    }
    frame %= 6;

    src.x *= 48;
    src.y *= 48;
    src.w = src.h = 48;

    dest.x = WIDTH/2-24;
    dest.y = HEIGHT/2-24;
    dest.w = dest.h = 48;

    render_texture(game, "llama", &src, &dest);

    /* render to the screen */
    SDL_RenderPresent(game->renderer);
}

/* handle_events: handle all events on the queue. */
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
            case SDLK_UP:
                llama_up = true;
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
#ifdef REPORT_FPS
    float fps = 1000/(diff+1); /* avoid floating point exceptions */
    debug_log("%s (%d): framerate %.3f", ORIGIN, fps);
#endif
}
