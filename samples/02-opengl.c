#include <stdio.h>
#include <GL/gl.h>
#
#define WINDOW_API_OPENGL
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    if (!winInit()) {
        fprintf(stderr, "win_init() failed\n");
        return (1);
    }

    winGLSetAttribute(WINDOW_GL_CONTEXT_MAJOR_VERSION, 4);
    winGLSetAttribute(WINDOW_GL_CONTEXT_MINOR_VERSION, 6);
    winGLSetAttribute(WINDOW_GL_CONTEXT_PROFILE, 1);

    t_window win;
    winCreateWindow(&win, 800, 600, "Hello, window.h - Sample 02. OpenGL", 0);

    t_glcontext ctx;
    winGLCreateContext(&ctx, win);

    winMapWindow(win);
    winGLMakeCurrent(ctx, win);
    winGLSwapInterval(ctx, 1);

    printf("%s\n", glGetString(GL_VERSION));

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
            }
        }
    }

    /* quit */
    winGLDestroyContext(ctx, win);
    winDestroyWindow(win);

    winQuit();
    return (0);
}
