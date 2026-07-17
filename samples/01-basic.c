#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* init window.h */
    library_t library = 0;
    winInit(&library);

    winSetHints(library, WINDOW_CLIENT_API, WINDOW_API_NONE);

    window_t window = 0;
    winCreateWindow(library, &window, 800, 600, "Hello, window.h - Sample 01. Basic");
    winMapWindow(library, window);

    context_t context = 0;
    winCreateContext(library, &context, window);

    int exit = 0;
    while (!exit) {
        event_t event = { 0 };
        while (winPollEvents(library, &event)) {
            if (event.type == WINDOW_EVENT_QUIT) { exit = 1; }

            if (event.type == WINDOW_EVENT_KEYBOARD_KEY) {
                if (event.keyboard.keymod == WINDOW_KEYMOD_CTRL) {
                    /* write / copy */
                    if (event.keyboard.keycode == WINDOW_KEYCODE_C) {
                        char   *str = "Hello, window.h!";
                        size_t size = strlen(str);
                        winCopy(library, WINDOW_SELECTION_CLIPBOARD, (void *) str, size);
                    }
                    /* read / paste */
                    if (event.keyboard.keycode == WINDOW_KEYCODE_V) {
                        char  *str;
                        size_t size;
                        winPaste(library, WINDOW_SELECTION_CLIPBOARD, (void **) &str, &size);
                        printf("%.*s\n", (int) size, str);
                        free(str);
                    }
                }
            }

            printf("%x\n", event.type);
        }
    }

    /* quit window.h */
    winQuit(library);
    return (0);
}
