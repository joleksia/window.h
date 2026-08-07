#include <stdio.h>
#
#define WINDOW_X11_EXTENSION_XINPUT2
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

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

    /* set cursor mode */

    /* update loop */
    int exit = 0;
    while (!exit) {
        event_t event = { 0 };
        while (win_event_poll(library, &event)) {
            /* wait for 'quit' event */
            if (event.type == WINDOW_EVENT_QUIT) { exit = 1; }

            if (event.type == WINDOW_EVENT_KEYBOARD_KEY) {
                switch (event.keyboard.keycode) {
                    case (WINDOW_KEYCODE_C): {
                        win_cursor_set_mode(library, window, WINDOW_CURSOR_MODE_CAPTURED);
                    } break;
                    case (WINDOW_KEYCODE_N): {
                        win_cursor_set_mode(library, window, WINDOW_CURSOR_MODE_NORMAL);
                    } break;
                    case (WINDOW_KEYCODE_L): {
                        win_cursor_set_mode(library, window, WINDOW_CURSOR_MODE_CENTERED);
                    } break;
                }
            }
        }
    }

    /* quit */
    win_quit(library);
    return (0);
}
