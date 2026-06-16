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
    winCreateWindow(&win, 800, 600, "Hello, window.h", WINDOW_FLAG_API_OPENGL);

    t_glcontext ctx;
    winGLCreate(&ctx, win);

    winGLMakeCurrent(ctx, win);
    winMapWindow(win);

    int exit = 0;
    while (!exit) {
        /* render */
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        /* poll events */
        winGLSwapBuffers(ctx, win);
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
