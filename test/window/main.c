#include "../../source/LilEn.h"

/* ================================================================ */

static void say_hello_on_hover(void* args) {
    printf("Hello from a button on hover!\n");
}

static void foo(void* btn) {
    Button_t b = NULL;

    b = (Button_t) btn;

    b->dimensions.w = 100;
}

static void say_hello_on_click(void* args) {
    printf("Hello from a button on click!\n");
}

/* ================================================================ */

int main(int argc, char** argv) {

    Window_t window = NULL;
    int running = 1;
    SDL_Event e;

    char fps_buffer[16];

    Text_t t = NULL;

    SDL_Rect r = {50, 50, 100, 120};

    SDL_Point position;

    if (LilEn_init("core.json") == EXIT_FAILURE) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    if ((window = Window_new("Window", 640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) == NULL) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    Button_t button = Button_new(10, 10, 64, 32);
    button->on_hover = foo;
    button->on_click = say_hello_on_click;

    printf("button = %d\n", button != NULL);

    Texture_t bg = Texture_new("bg.jpg", window);

    TTF_Font* font = Font_load("montserrat.regular.ttf", 16);

    t = Text_new("FPS:", font);
    t->position.x = 640 / 2;
    t->position.y = 480 / 2;

    while (running) {

        LilEn_set_colorRGB(255, 255, 255, 255);

        Timer_tick(g_timer);

        while (SDL_PollEvent(&e)) {

            switch (e.type) {

                case SDL_QUIT:

                    running = !running;

                    break ;

                case SDL_MOUSEMOTION:

                    SDL_GetMouseState(&position.x, &position.y);

                    Button_check(button, &e.button, &position, button);

                    break ;

                case SDL_MOUSEBUTTONDOWN:

                    if (e.button.button == SDL_BUTTON_LEFT) {
                        Button_check(button, &e.button, &position, NULL);
                    }

                    break ;    
            }
        }

        if (Timer_is_ready(g_timer)) {

            sprintf(fps_buffer, "FPS: %.1f", 1.0f / g_timer->acc);

            Window_clear(NULL);

            Texture_display(bg, NULL, NULL);

            LilEn_set_colorHEX(0xff0000);
            Text_update(t, fps_buffer, font);

            t->position.x = 640 - (t->position.w + 16);
            t->position.y = 480 - (t->position.h + 16);

            //LilEn_log_FPS();

            // Window_display_grid(NULL, 5);
            //draw_rect(&r);

            LilEn_set_colorRGB(255, 255, 255, 255);
            Button_display(button, NULL);

            //Button_check(button, &e.button, &position);

            Text_display(t, NULL);

            Window_update(NULL);

            Timer_reset(g_timer);
        }
    }

    Text_destroy(&t);
    Texture_destroy(&bg);

    printf("bg == NULL = %d\n", bg == NULL);

    Font_unload(font);
    LilEn_quit();

    return EXIT_SUCCESS;
}