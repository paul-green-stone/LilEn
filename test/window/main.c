#include "../../LilEn.h"

int main(int argc, char** argv) {

    Window_t window = NULL;
    int running = 1;
    SDL_Event e;

    char fps_buffer[16];

    Text_t t = NULL;

    SDL_Rect r = {50, 50, 100, 120};

    if (LilEn_init("core.json") == EXIT_FAILURE) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    if ((window = Window_new("Window", 640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) == NULL) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    printf("Current audio driver: %s\n", SDL_GetCurrentAudioDriver());


    TTF_Font* font = Font_load("montserrat.regular.ttf", 16);

    t = Text_new("FPS:", font);
    t->position.x = 640 / 2;
    t->position.y = 480 / 2;

    if (t != NULL) {
        printf("OK\n");
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

            sprintf(fps_buffer, "FPS: %.1f", 1.0f / g_timer->acc);

            Window_clear(NULL);

            LilEn_set_colorHEX(0xff0000);
            Text_update(t, fps_buffer, font);

            t->position.x = 640 - (t->position.w + 16);
            t->position.y = 480 - (t->position.h + 16);

            //LilEn_log_FPS();

            // Window_display_grid(NULL, 5);
            //draw_rect(&r);

            Text_display(t, NULL);

            Window_update(NULL);

            Timer_reset(g_timer);
        }
    }

    Text_destroy(&t);

    Font_unload(font);
    LilEn_quit();

    return EXIT_SUCCESS;
}