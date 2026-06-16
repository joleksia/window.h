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

    t_window win;
    winCreateWindow(&win, 800, 600, "Hello, window.h - Sample 01. Basic", WINDOW_FLAG_TOPMOST);
    winMapWindow(win);

    int exit = 0;
    while (!exit) {
        /* poll events */
        t_event event = { 0 };
        while (winPollEvents(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    printf("WINDOW_EVENT_QUIT\n");
                    exit = 1;
                } break;
                case (WINDOW_EVENT_KEYBOARD_KEY): {
                    if (event.key.key == WINDOW_KEY_SPACE) {
                        winSetWindowFlag(win, WINDOW_FLAG_FULLSCREEN);
                    }
                } break;
            }
        }
    }

    /* quit */
    winQuit();
    return (0);
}
