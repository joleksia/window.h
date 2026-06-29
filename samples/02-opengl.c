#include <stdio.h>
#include <GL/gl.h>
#
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
    winGLSetAttribute(WINDOW_GL_CONTEXT_PROFILE_MASK, 2);

    window_t win;
    winCreateWindow(&win, 800, 600, "Hello, window.h - Sample 02. OpenGL", WINDOW_FLAG_API_OPENGL);

    context_t ctx;
    winCreateContext(&ctx, win);

    winMapWindow(win);
    winGLMakeCurrent(ctx);
    winGLSwapInterval(ctx, 1);

    printf("%s\n", glGetString(GL_VERSION));

    int exit = 0;
    while (!exit) {
        /* render */
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
            glVertex2f(-0.5,-0.5);
            glVertex2f(-0.5, 0.5);
            glVertex2f( 0.5, 0.5);
            glVertex2f( 0.5,-0.5);
        glEnd();

        /* poll events */
        winGLSwapBuffers(ctx);
        t_event event = { 0 };
        while (winPollEvents(&event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    printf("WINDOW_EVENT_QUIT\n");
                    exit = 1;
                } break;

                case (WINDOW_EVENT_WINDOW_RESIZE): {
                    printf("WINDOW_EVENT_WINDOW_RESIZE\n");
                    glViewport(0, 0, event.window.data1, event.window.data2);
                } break;
            }
        }
    }

    /* quit */
    winQuit();
    return (0);
}
