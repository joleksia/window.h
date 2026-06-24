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

    int exit = 0;
    while (!exit) {
        /* poll events */
        t_event event = { 0 };
        while (winPollEvents(&event)) {
            printf("Event ID.: %d\n", event.type);

            if (event.type == WINDOW_EVENT_MOUSE_BUTTON) {
                if (event.mouse.btn == 1 && event.mouse.state) {
                    char *paste = 0;
                    if (winPasteClipboard(&paste)) {
                        printf("%s\n", paste);
                        free(paste);
                    }
                }
                if (event.mouse.btn == 2 && event.mouse.state) {
                    char *copy = "Hello, world!";
                    winCopyClipboard(copy);
                }
            }

            /* handle exit */
            if (event.type == WINDOW_EVENT_QUIT) {
                exit = 1;
            }
        }
    }

    /* quit */
    winQuit();
    return (0);
}
