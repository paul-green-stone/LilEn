#include "../../source/LilEn.h"

TTF_Font* f;

/* ================================================================ */

static void left(void* args) {
    printf("The left button has been clicked\n");
}

static void right(void* args) {
    printf("The right button has been clicked\n");
}

static void foo(void* args) {

    Button_t b = NULL;

    SDL_Color old = *g_color;

    b = (Button_t) args;

    LilEn_set_colorRGB(255, 255, 255, 255);

    Text_update(b->label, b->text, f);

    LilEn_set_colorRGB(old.r, old.g, old.b, old.a);
}

static void goo(void* args) {

    Button_t b = NULL;

    SDL_Color old = *g_color;

    b = (Button_t) args;

    LilEn_set_colorRGB(255, 0, 0, 255);

    Text_update(b->label, "Left", f);

    LilEn_set_colorRGB(old.r, old.g, old.b, old.a);
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

    if (LilEn_init(NULL) == EXIT_FAILURE) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    if ((window = Window_new("Window", 640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) == NULL) {

        LilEn_print_error();

        return EXIT_FAILURE;
    }

    Texture_t bg = Texture_new("bg.jpg", window);

    TTF_Font* font = Font_load("PressStart2P-Regular.ttf", 12);
    f = font;

    LilEn_set_colorHEX(0xff0000);
    Button_t button = Button_new_Text(10, 10, 64, 32, "Left", font);
    Button_add_callback(button, ON_CLICK, left);
    Button_add_callback(button, ON_MOUSE_ENTER, foo);
    Button_add_callback(button, ON_MOUSE_LEAVE, goo);
    Button_bind_mb(button, SDL_BUTTON_LEFT);

    LilEn_set_colorHEX(0x00ff00);
    Button_t rb = Button_new_Text(640 - 74, 10, 64, 32, "Right", font);
    Button_add_callback(rb, ON_CLICK, right);
    Button_bind_mb(rb, SDL_BUTTON_RIGHT);

    t = Text_new("FPS:", font);
    t->position.x = 640 / 2;
    t->position.y = 480 / 2;

    printf("%p\n", button->label->t);

    while (running) {

        LilEn_set_colorRGB(255, 255, 255, 255);

        Timer_tick(g_timer);

        while (SDL_PollEvent(&e)) {

            SDL_GetMouseState(&position.x, &position.y);

            switch (e.type) {

                case SDL_QUIT:

                    running = !running;

                    break ;

                case SDL_MOUSEMOTION:

                    Button_hover(button, &position, button);
                    

                    break ;

                case SDL_MOUSEBUTTONDOWN:

                    Button_click(button, &position, e.button, NULL);
                    Button_click(rb, &position, e.button, NULL);
                    
                    break ;

                case SDL_MOUSEBUTTONUP:

                    if (e.button.button == SDL_BUTTON_LEFT) {
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
            Button_display(rb, NULL);

            Text_display(t, NULL);

            Window_update(NULL);

            Timer_reset(g_timer);
        }
    }

    Text_destroy(&t);
    Texture_destroy(&bg);

    Button_destroy(&button);
    Button_destroy(&rb);

    printf("bg == NULL = %d\n", bg == NULL);

    Font_unload(font);
    LilEn_quit();

    return EXIT_SUCCESS;
}
