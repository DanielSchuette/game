/* main.c: the game's main loop. */
#include "game.h"

char *progname;

int main(int argc, char **argv)
{
    unsigned int start, end;
    game_t *game;
    progname = *argv;

    /* game loop */
    game = init_game("SDL2 game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     WIDTH, HEIGHT, false);
    load_assets(game, "assets/bearded_man-1x.png");
    while (is_active(game)) {
        start = SDL_GetTicks();
        handle_events(game);
        update(game);
        render(game);
        end = SDL_GetTicks();
        adjust_framerate(game, start, end);
    }
    quit_game(game);

    return 0;
}
