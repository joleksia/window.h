#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../../window.h"

int main(void) {
    /* init window.h */
    library_t library = 0;
    win_init(&library);

    /* set current API as 'Native' */
    win_set_hints(library, WINDOW_CLIENT_API, WINDOW_API_NATIVE);

    /* create window */
    // window_t window = 0;
    // win_window_create(library, &window, 800, 600, "Hello, window.h - Wayland sample");
    // if (!window) { win_quit(library); return (1); }

    // /* create context */
    // context_t context = 0;
    // win_context_create(library, &context, window);
    // if (!context) { win_quit(library); return (2); }

    // /* map window */
    // win_window_map(library, window);

    // /* update loop */
    // int exit = 0;
    // while (!exit) {
    //     /* poll events */
    //     event_t event = { 0 };
    //     while (win_event_poll(library, &event)) {
    //         switch (event.type) {
    //             case (WINDOW_EVENT_QUIT): {
    //                 printf("WINDOW_EVENT_QUIT\n");
    //                 exit = 1;
    //             } break;
    //         }
    //     }
    // }

    /* quit */
    win_quit(library);
    return (0);
}
