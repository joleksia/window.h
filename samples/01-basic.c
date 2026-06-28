#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* intialize window.h */
    winInit();

    /* create window.h window */
    window_t window = 0;
    winCreateWindow(&window, 800, 600, "Hello, window.h - Sample 01. Basic", 0);
    winMapWindow(window);
    
    /* create graphics context */
    context_t context = 0;
    winCreateContext(&context, window);

    /* get pixel buffer from context */
    uint8_t *p_data   = 0;
    size_t   p_width  = 0,
             p_height = 0;
    winGetContextBuffer(context, &p_data, &p_width, &p_height);

    /* clear the screen with 0xff191919 */
    uint32_t *p_data32 = (uint32_t *) p_data;
    for (size_t i = 0; i < p_width * p_height; i++) {
        p_data32[i] = 0xff191919;
    }

    /* draw a rectangle in the middle of the screen */
    size_t sx = p_width / 4,
           sy = p_height / 4;
    size_t ex = sx * 3,
           ey = sy * 3;
    for (size_t y = sy; y < ey; y++) {
        for (size_t x = sx; x < ex; x++) {
            p_data32[y * p_width + x] = 0xffffffff;
        }
    }

    int exit = 0;
    while (!exit) {
        /* update */
        winSetCursorMode(window, WINDOW_CURSOR_MODE_DISABLED);
        
        /* render */
        winDrawBuffer(context);

        /* poll events */
        t_event event = { 0 };
        while (winPollEvents(&event)) {
            /* handle exit */
            if (event.type == WINDOW_EVENT_QUIT) {
                exit = 1;
            }

            if (event.type == WINDOW_EVENT_KEYBOARD_KEY) {
                if (event.keyboard.keycode == WINDOW_KEYCODE_ESCAPE) {
                    exit = 1;
                }
            }
        }
    }

    /* quit */
    winQuit();
    return (0);
}
