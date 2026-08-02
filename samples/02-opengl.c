#include <stdio.h>
#include <GL/gl.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../window.h"

int main(void) {
    /* initialize window.h */
    library_t library = 0;
    winInit(&library);

    /* set current API as 'OpenGL' */
    winSetHints(library, WINDOW_CLIENT_API, WINDOW_API_OPENGL);

    /* configure OpenGL hints */
    winSetHints(library, WINDOW_GL_CONTEXT_VERSION_MAJOR, 1);
    winSetHints(library, WINDOW_GL_CONTEXT_VERSION_MINOR, 0);
    winSetHints(library, WINDOW_GL_CONTEXT_PROFILE, WINDOW_GL_CONTEXT_PROFILE_COMPATIBILITY);

    /* create window */
    window_t window = 0;
    winCreateWindow(library, &window, 800, 600, "Hello, window.h - Sample 02. OpenGL");
    if (!window) { winQuit(library); return (1); }

    /* create context */
    context_t context = 0;
    winCreateContext(library, &context, window);
    if (!context) { winQuit(library); return (2); }

    winMapWindow(library, window);
    winGLMakeCurrent(library, context);
    winGLSwapInterval(library, context, 1);

    /* print OpenGL info */
    printf("- Vendor: %s\n", glGetString(GL_VENDOR));
    printf("- Version: %s\n", glGetString(GL_VERSION));
    printf("- Renderer: %s\n", glGetString(GL_RENDERER));
    printf("- GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    /* update-render loop */
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

        if (!winGLSwapBuffers(library, context)) {
            /* 'winGLSwapBuffers' failed: fall-back to 'glFlush' */
            glFlush();
        }

        /* poll events */
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
