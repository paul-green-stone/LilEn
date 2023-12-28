#include "../../source/LilEn.h"

TTF_Font* f = NULL;

static void activate(void* args) {

    Button_t btn = (Button_t) args;

    LilEn_set_colorHEX(0xff0000);

    Text_update(btn->label, btn->text, f);
}

static void deactivate(void* args) {

    Button_t btn = (Button_t) args;

    LilEn_set_colorHEX(0xffffff);

    Text_update(btn->label, btn->text, f);
}

static void quit(void* args) {
    *((int*) args) = !*((int*) args);
}

/* ================================================================ */

int main(int argc, char** argv) {

    Window_t window = NULL;
    int running = 1;
    SDL_Event e;

    SDL_Point position;

    if (LilEn_init(NULL) == EXIT_FAILURE) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    if ((window = Window_new("Window", 640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) == NULL) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    TTF_Font* font = Font_load("PressStart2P-Regular.ttf", 16);
    f = font;

    LilEn_set_colorHEX(0xffffff);
    Button_t start = Button_new_Text(640 / 2 - 120 / 2, 480 / 2 - 140 / 2, 0, 32, "Start", font);
    Button_add_callback(start, ON_MOUSE_ENTER, activate);
    Button_add_callback(start, ON_MOUSE_LEAVE, deactivate);
    Button_bind_mb(start, SDL_BUTTON_LEFT);

    Button_t load = Button_new_Text(640 / 2 - 120 / 2, 480 / 2 - 140 / 2 + 32 + 4, 1, 32, "Load", font);
    Button_add_callback(load, ON_MOUSE_ENTER, activate);
    Button_add_callback(load, ON_MOUSE_LEAVE, deactivate);

    Button_t options = Button_new_Text(640 / 2 - 120 / 2, 480 / 2 - 140 / 2 + 64 + 4, 1, 32, "Options", font);
    Button_add_callback(options, ON_MOUSE_ENTER, activate);
    Button_add_callback(options, ON_MOUSE_LEAVE, deactivate);

    Button_t exit = Button_new_Text(640 / 2 - 120 / 2, 480 / 2 - 140 / 2 + 96 + 4, 1, 32, "Exit", font);
    Button_add_callback(exit, ON_MOUSE_ENTER, activate);
    Button_add_callback(exit, ON_MOUSE_LEAVE, deactivate);
    Button_add_callback(exit, ON_CLICK, quit);
    Button_bind_mb(exit, SDL_BUTTON_LEFT);

    SDL_Rect r = {10, 10, 50, 50};

    while (running) {

        Timer_tick(g_timer);

        while (SDL_PollEvent(&e)) {

            SDL_GetMouseState(&position.x, &position.y);

            switch (e.type) {

                case SDL_QUIT:

                    running = !running;

                    break ;

                case SDL_MOUSEMOTION:

                    Button_hover(start, &position, start);
                    Button_hover(load, &position, load);
                    Button_hover(options, &position, options);
                    Button_hover(exit, &position, exit);

                    break ;

                case SDL_MOUSEBUTTONDOWN:

                    Button_click(exit, &position, e.button, &running);
                    
                    break ;
            }
        }

        if (Timer_is_ready(g_timer)) {

            LilEn_set_colorRGB(0, 0, 0, 255);

            Window_clear(NULL);

            LilEn_set_colorHEX(0x00ff00);

            Button_display(start, NULL);
            Button_display(load, NULL);
            Button_display(options, NULL);
            Button_display(exit, NULL);

            Window_update(NULL);

            Timer_reset(g_timer);
        }
    }

    Button_destroy(&start);
    Button_destroy(&load);
    Button_destroy(&options);
    Button_destroy(&exit);

    Font_unload(font);
    LilEn_quit();

    return EXIT_SUCCESS;
}
