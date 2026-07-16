#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* init window.h */
    if (!winInit()) {
        fprintf(stderr, "winInit() failed\n");
        return (1);
    }

    winSetHints(WINDOW_CLIENT_API, WINDOW_API_NONE);

    window_t window = 0;
    winCreateWindow(&window, 800, 600, "Hello, window.h - Sample 01. Basic");
    winMapWindow(window);

    context_t context = 0;
    winCreateContext(&context, window);

    int exit = 0;
    while (!exit) {
        event_t event = { 0 };
        while (winPollEvents(&event)) {
            if (event.type == WINDOW_EVENT_QUIT) { exit = 1; }

            if (event.type == WINDOW_EVENT_KEYBOARD_KEY) {
                if (event.keyboard.keymod == WINDOW_KEYMOD_CTRL) {
                    /* write / copy */
                    if (event.keyboard.keycode == WINDOW_KEYCODE_C) {
                        char   *str = "Hello, window.h!";
                        size_t size = strlen(str);
                        winCopy(WINDOW_SELECTION_CLIPBOARD, (void *) str, size);
                    }
                    /* read / paste */
                    if (event.keyboard.keycode == WINDOW_KEYCODE_V) {
                        char  *str;
                        size_t size;
                        winPaste(WINDOW_SELECTION_CLIPBOARD, (void **) &str, &size);
                        printf("%.*s\n", (int) size, str);
                        free(str);
                    }
                }
            }

            printf("%x\n", event.type);
        }
    }

    /* quit window.h */
    winQuit();
    return (0);
}
