#include <stdio.h>
#include <GL/gl.h>
#
#define WINDOW_IMPLEMENTATION
#include "./../../window.h"

int main(void) {
    /* init window.h */
    library_t library = 0;
    win_init(&library);

    /* set current API as 'OpenGL' */
    win_set_hints(library, WINDOW_CLIENT_API, WINDOW_API_OPENGL);

//     /* configure OpenGL hints */
//     win_set_hints(library, WINDOW_GL_CONTEXT_VERSION_MAJOR, 1);
//     win_set_hints(library, WINDOW_GL_CONTEXT_VERSION_MINOR, 0);
//     win_set_hints(library, WINDOW_GL_CONTEXT_PROFILE, WINDOW_GL_CONTEXT_PROFILE_COMPATIBILITY);
// 
//     /* create window */
//     window_t window = 0;
//     win_window_create(library, &window, 800, 600, "Hello, window.h - Sample 02. OpenGL");
//     if (!window) { win_quit(library); return (1); }
// 
//     /* create context */
//     context_t context = 0;
//     win_context_create(library, &context, window);
//     if (!context) { win_quit(library); return (2); }
// 
//     /* map window */
//     win_window_map(library, window);
//     win_gl_make_current(library, context);
//     win_gl_swap_interval(library, context, 1);
// 
//     /* print OpenGL info */
//     printf("- Vendor: %s\n", glGetString(GL_VENDOR));
//     printf("- Version: %s\n", glGetString(GL_VERSION));
//     printf("- Renderer: %s\n", glGetString(GL_RENDERER));
// 
//     /* update-render loop */
//     int exit = 0;
//     while (!exit) {
//         /* render */
//         glClearColor(0.1, 0.1, 0.1, 1.0);
//         glClear(GL_COLOR_BUFFER_BIT);
//         glBegin(GL_QUADS);
//             glVertex2f(-0.5,-0.5);
//             glVertex2f(-0.5, 0.5);
//             glVertex2f( 0.5, 0.5);
//             glVertex2f( 0.5,-0.5);
//         glEnd();
// 
//         if (!win_gl_swap_buffers(library, context)) {
//             /* 'win_gl_swap_buffers' failed: fall-back to 'glFlush' */
//             glFlush();
//         }
// 
//         /* poll events */
//         event_t event = { 0 };
//         while (win_event_poll(library, &event)) {
//             switch (event.type) {
//                 case (WINDOW_EVENT_QUIT): {
//                     exit = 1;
//                 } break;
// 
//                 case (WINDOW_EVENT_WINDOW_RESIZE): {
//                     glViewport(0, 0, event.window.data1, event.window.data2);
//                 } break;
//             }
//         }
//     }

    /* quit */
    win_quit(library);
    return (0);
}
