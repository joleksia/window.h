#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* intialize window.h */
    winInit();

    /* create window.h window */
    t_window window = 0;
    winCreateWindow(&window, 800, 600, "Hello, window.h - Sample 01. Basic", 0);
    winMapWindow(window);

    char *paste = 0;
    winCopyClipboard(window, "Hello, window.h!");
    printf("winCopyClipboard()\n");
    winPasteClipboard(window, &paste);
    printf("winPasteClipboard()\n");
    printf("%s\n", paste); free(paste);

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
