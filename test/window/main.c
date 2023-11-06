#include "../../source/LilEn.h"

int main(int argc, char** argv) {

    Window_t window = NULL;
    int running = 1;
    SDL_Event e;

    if (LilEn_init(NULL) == EXIT_FAILURE) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    if ((window = Window_new("Window", 640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) == NULL) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    while (running) {

        LilEn_set_colorRGB(255, 255, 255, 255);

        Timer_tick(g_timer);

        while (SDL_PollEvent(&e)) {

            switch (e.type) {

                case SDL_QUIT:

                    running = !running;

                    break ;
            }
        }

        if (Timer_is_ready(g_timer)) {

            Window_clear(NULL);

            LilEn_set_colorHEX(0x000000);

            LilEn_log_FPS();

            Window_display_grid(NULL, 5);

            Window_update(NULL);

            Timer_reset(g_timer);
        }
    }

    LilEn_quit();

    return EXIT_SUCCESS;
}