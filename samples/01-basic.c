#include <stdio.h>
#
#define WINDOW_X11_EXTENSION_XINPUT2
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* init window.h */
    library_t library = 0;
    winInit(&library);

    /* set current API as 'Native' */
    winSetHints(library, WINDOW_CLIENT_API, WINDOW_API_NATIVE);

    /* create window */
    window_t window = 0;
    winCreateWindow(library, &window, 800, 600, "Hello, window.h - Sample 01. Basic");
    if (!window) { winQuit(library); return (1); }

    /* create context */
    context_t context = 0;
    winCreateContext(library, &context, window);
    if (!context) { winQuit(library); return (2); }

    /* map window */
    winMapWindow(library, window);

    /* set cursor mode */

    /* update loop */
    int exit = 0;
    while (!exit) {
        event_t event = { 0 };
        while (winPollEvents(library, &event)) {
            /* wait for 'quit' event */
            if (event.type == WINDOW_EVENT_QUIT) { exit = 1; }

            if (event.type == WINDOW_EVENT_KEYBOARD_KEY) {
                switch (event.keyboard.keycode) {
                    case (WINDOW_KEYCODE_C): {
                        winSetCursorMode(library, window, WINDOW_CURSOR_MODE_CAPTURED);
                    } break;
                    case (WINDOW_KEYCODE_N): {
                        winSetCursorMode(library, window, WINDOW_CURSOR_MODE_NORMAL);
                    } break;
                    case (WINDOW_KEYCODE_L): {
                        winSetCursorMode(library, window, WINDOW_CURSOR_MODE_CENTERED);
                    } break;
                }
            }
        }
    }

    /* quit */
    winQuit(library);
    return (0);
}
