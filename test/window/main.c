#include "../../source/include.h"

int main(int argc, char** argv) {

    Window_t window = NULL;
    int running = 1;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0) {

        return EXIT_FAILURE;
    }

    if ((window = Window_new("Window", 640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) == NULL) {

        return EXIT_FAILURE;
    }

    while (running) {

        while (SDL_PollEvent(&e)) {

            switch (e.type) {

                case SDL_QUIT:

                    running = !running;

                    break ;
            }
        }

        SDL_RenderPresent(g_window->renderer);
    }

    Window_destroy(&window);

    if (window == NULL) {
        printf("OK\n");
    }
    SDL_Quit();

    return EXIT_SUCCESS;
}