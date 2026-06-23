#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    if (!winInit()) {
        fprintf(stderr, "winInit() failed\n");
        return (1);
    }

    t_window window = 0;
    winCreateWindow(&window, 800, 600, "Hello, window.h - Sample 01. Basic", 0);
    winMapWindow(window);

    if (!winCopyClipboard(window, "Hello, window.h!")) {
        fprintf(stderr, "winCopyClipboard() failed\n");
        return (1);
    }

    int exit = 0;
    while (!exit) {
        /* poll events */
        t_event event = { 0 };
        while (winPollEvents(&event)) {
            printf("Event ID.: %d\n", event.type);

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
