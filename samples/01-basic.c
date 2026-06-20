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
                    printf("Mouse Motion: %d %d\n", event.mouse.x, event.mouse.y);
                } break;

                case (WINDOW_EVENT_MOUSE_BUTTON): {
                    printf("Mouse Button Press: %d %d\n", event.mouse.btn, event.mouse.state);

                    if (event.mouse.btn == WINDOW_BUTTON_RIGHT) {
                        winToggleWindowFlags(window, WINDOW_FLAG_FULLSCREEN);
                    }
                } break;

                case (WINDOW_EVENT_MOUSE_SCROLL): {
                    printf("Mouse Scroll: %d %d\n", event.mouse.scroll_x, event.mouse.scroll_y);
                } break;

                case (WINDOW_EVENT_WINDOW_FULLSCREEN):
                case (WINDOW_EVENT_WINDOW_MAXIMIZE):
                case (WINDOW_EVENT_WINDOW_MINIMIZE): {
                    printf("Window Property Changed: %d %d\n", event.window.type, event.window.data1);
                } break;
            }
        }
    }

    /* quit */
    winQuit();
    return (0);
}
