#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* init window.h */
    library_t library = 0;
    winInit(&library);

    winSetHints(library, WINDOW_CLIENT_API, WINDOW_API_NATIVE);

    window_t window = 0;
    winCreateWindow(library, &window, 800, 600, "Hello, window.h - Sample 01. Basic");
    winMapWindow(library, window);

    context_t context = 0;
    winCreateContext(library, &context, window);

    int exit = 0;
    while (!exit) {
        event_t event = { 0 };
        while (winPollEvents(library, &event)) {
            /* wait for 'quit' event */
            if (event.type == WINDOW_EVENT_QUIT) { exit = 1; }

            /* output the event name to stdout */
            if (event.type == WINDOW_EVENT_NONE) { printf("WINDOW_EVENT_NONE\n"); }
            
            else if (event.type == WINDOW_EVENT_QUIT) { printf("WINDOW_EVENT_QUIT\n"); }
            
            else if (event.type == WINDOW_EVENT_MOUSE_MOTION) { printf("WINDOW_EVENT_MOUSE_MOTION\n"); }
            else if (event.type == WINDOW_EVENT_MOUSE_BUTTON) { printf("WINDOW_EVENT_MOUSE_BUTTON\n"); }
            else if (event.type == WINDOW_EVENT_MOUSE_SCROLL) { printf("WINDOW_EVENT_MOUSE_SCROLL\n"); }
            else if (event.type == WINDOW_EVENT_MOUSE_ADDED) { printf("WINDOW_EVENT_MOUSE_ADDED\n"); }
            else if (event.type == WINDOW_EVENT_MOUSE_REMOVED) { printf("WINDOW_EVENT_MOUSE_REMOVED\n"); }
            
            else if (event.type == WINDOW_EVENT_KEYBOARD_KEY) { printf("WINDOW_EVENT_KEYBOARD_KEY\n"); }
            else if (event.type == WINDOW_EVENT_KEYBOARD_ADDED) { printf("WINDOW_EVENT_KEYBOARD_ADDED\n"); }
            else if (event.type == WINDOW_EVENT_KEYBOARD_REMOVED) { printf("WINDOW_EVENT_KEYBOARD_REMOVED\n"); }
            
            else if (event.type == WINDOW_EVENT_WINDOW_CREATE) { printf("WINDOW_EVENT_WINDOW_CREATE\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_DESTROY) { printf("WINDOW_EVENT_WINDOW_DESTROY\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_MAP) { printf("WINDOW_EVENT_WINDOW_MAP\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_UNMAP) { printf("WINDOW_EVENT_WINDOW_UNMAP\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_RESIZE) { printf("WINDOW_EVENT_WINDOW_RESIZE\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_MOTION) { printf("WINDOW_EVENT_WINDOW_MOTION\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_ENTER) { printf("WINDOW_EVENT_WINDOW_ENTER\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_LEAVE) { printf("WINDOW_EVENT_WINDOW_LEAVE\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_MAXIMIZE) { printf("WINDOW_EVENT_WINDOW_MAXIMIZE\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_MINIMIZE) { printf("WINDOW_EVENT_WINDOW_MINIMIZE\n"); }
            else if (event.type == WINDOW_EVENT_WINDOW_FULLSCREEN) { printf("WINDOW_EVENT_WINDOW_FULLSCREEN\n"); }

            else if (event.type == WINDOW_EVENT_SELECTION_COPY) { printf("WINDOW_EVENT_SELECTION_COPY\n"); }
            else if (event.type == WINDOW_EVENT_SELECTION_PASTE) { printf("WINDOW_EVENT_SELECTION_PASTE\n"); }
            else if (event.type == WINDOW_EVENT_SELECTION_CLEAR) { printf("WINDOW_EVENT_SELECTION_CLEAR\n"); }
        }
    }

    /* quit window.h */
    winQuit(library);
    return (0);
}
