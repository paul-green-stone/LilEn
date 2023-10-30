#include "../../source/include.h"

int main(int argc, char** argv) {

    Window_t window = NULL;
    int running = 1;
    SDL_Event e;

    if (LilEn_init() == EXIT_FAILURE) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    if ((window = Window_new("Window", 640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) == NULL) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    while (running) {

        Timer_tick(g_timer);

        while (SDL_PollEvent(&e)) {

            switch (e.type) {

                case SDL_QUIT:

                    running = !running;

                    break ;
            }
        }

        if (Timer_is_ready(g_timer)) {

            LilEn_log_FPS();

            SDL_RenderPresent(g_window->renderer);

            Timer_reset(g_timer);
        }
    }

    Window_destroy(&window);

    LilEn_quit();

    return EXIT_SUCCESS;
}