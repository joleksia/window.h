#include <stdio.h>
#include <GL/gl.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    library_t library = 0;
    winInit(&library);

    winSetHints(library, WINDOW_CLIENT_API, WINDOW_API_OPENGL);

    window_t window;
    winCreateWindow(library, &window, 800, 600, "Hello, window.h - Sample 02. OpenGL");

    context_t context;
    winCreateContext(library, &context, window);

    winMapWindow(library, window);
    winGLMakeCurrent(library, context);
    winGLSwapInterval(library, context, 1);

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
        winGLSwapBuffers(library, context);
        event_t event = { 0 };
        while (winPollEvents(library, &event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    exit = 1;
                } break;

                case (WINDOW_EVENT_WINDOW_RESIZE): {
                    glViewport(0, 0, event.window.data1, event.window.data2);
                } break;
            }
        }
    }

    /* quit */
    winQuit(library);
    return (0);
}
