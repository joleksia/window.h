#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../../window.h"

int main(void) {
    /* init window.h */
    library_t library = 0;
    win_init(&library);

    /* set current API as 'Native' */
    win_set_hints(library, WINDOW_CLIENT_API, WINDOW_API_NATIVE);

    /* create window */
    window_t window = 0;
    win_window_create(library, &window, 800, 600, "Hello, window.h - Sample 01. Basic");
    if (!window) { win_quit(library); return (1); }

    /* create context */
    context_t context = 0;
    win_context_create(library, &context, window);
    if (!context) { win_quit(library); return (2); }

    /* map window */
    win_window_map(library, window);

    /* update loop */
    int exit = 0;
    while (!exit) {
        /* poll events */
        event_t event = { 0 };
        while (win_event_poll(library, &event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    printf("WINDOW_EVENT_QUIT\n");
                    exit = 1;
                } break;

                case (WINDOW_EVENT_KEYBOARD_KEY): {
                    if (event.keyboard.keycode == WINDOW_KEYCODE_N) {
                        win_cursor_set_mode(library, window, WINDOW_CURSOR_MODE_NORMAL);
                    }
                    else if (event.keyboard.keycode == WINDOW_KEYCODE_L) {
                        win_cursor_set_mode(library, window, WINDOW_CURSOR_MODE_CENTERED);
                    }
                } break;

                case (WINDOW_EVENT_MOUSE_MOTION): {
                    printf("motion: %d %d\n", event.mouse.motion.x, event.mouse.motion.y);
                } break;
            }
        }
    }

    /* quit */
    win_quit(library);
    return (0);
}
