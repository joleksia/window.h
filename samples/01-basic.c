#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    if (!winInit()) {
        fprintf(stderr, "win_init() failed\n");
        return (1);
    }

    t_window window = 0;
    winCreateWindow(&window, 800, 600, "Hello, window.h - Sample 01. Basic", 0);
    winMapWindow(window);

    int exit = 0;
    while (!exit) {
        /* poll events */
        t_event event = { 0 };
        while (winPollEvents(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    exit = 1;
                } break;

                case (WINDOW_EVENT_MOUSE_MOTION): {
                    printf("%d %d\n", event.mouse.x, event.mouse.y);
                } break;
            }
        }
    }

    /* quit */
    winQuit();
    return (0);
}
