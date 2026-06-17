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

    int exit = 0;
    while (!exit) {
        /* poll events */
        t_event event = { 0 };
        while (winPollEvents(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    exit = 1;
                } break;
            }
        }
    }

    /* quit */
    winQuit();
    return (0);
}
