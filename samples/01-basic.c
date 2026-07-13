#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* init window.h */
    winInit();

    window_t window = 0;
    winCreateWindow(&window, 800, 600, "Hello, window.h - Sample 01. Basic", 0);
    winMapWindow(window);

    context_t context = 0;
    winCreateContext(&context, window);

    int exit = 0;
    while (!exit) {
        event_t event = { 0 };
        while (winPollEvents(&event)) {
            if (event.type == WINDOW_EVENT_QUIT) { exit = 1; }
        }
    }

    /* quit window.h */
    winQuit();
    return (0);
}
