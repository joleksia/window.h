<div align="center">

# window.h - minimalistic windowing library 

</div>

`window.h` is a single-header minimalistic windowing solution for GNU/Linux, unix-like and win32 systems.

```c
#include <stdio.h>
#
#define WINDOW_IMPLEMENTATION
#include <window.h>

int main(void) {
    /* init window.h */
    library_t library = 0;
    win_init(&library);
    
    /* create window */
    window_t window = 0;
    win_window_create(library, &window, 800, 600, "Hello, window.h!");
    if (!window) { win_quit(library); return (1); }

    /* map window */
    win_window_map(library, window);

    /* update loop */
    int exit = 0;
    while (!exit) {
        /* poll events */
        event_t event = { 0 };
        while (win_event_poll(library, &event)) {
            switch (event.type) {
                case (WINDOW_EVENT_QUIT): {
                    printf("WINDOW_EVENT_QUIT\n");
                    exit = 1;
                } break;
            }
        }
    }

    /* quit */
    win_quit(library);
    return (0);
}
```

## Contributions

### 1. Contributing new backend.

*TODO: add this section*

## Resources

Resources used in this project:
- [glfw/glfw](https://github.com/glfw/glfw.git)
- [libsdl-org/SDL](https://github.com/libsdl-org/SDL.git)
- [ColleagueRiley/RGFW](https://github.com/ColleagueRiley/RGFW.git)
- [mirror/libX11](https://github.com/mirror/libX11.git)
- [HID Usage Tables FOR Universal Serial Bus (USB)](https://usb.org/sites/default/files/hut1_21.pdf)
- [The X Window system](https://tronche.com/gui/x/)
- [The Xlib Manual](https://tronche.com/gui/x/xlib/)
- [EGL Reference Pages](https://registry.khronos.org/EGL/sdk/docs/man/)

Specific resources used in this project:
- [MaJerle/c-code-style](https://github.com/MaJerle/c-code-style)
- [Create an OpenGL context using Xlib and EGL](https://gist.github.com/pedrominicz/2d81559c5fb66d23d6bb627570956605)
- [RGFW Under the Hood: OpenGL context creation](https://github.com/ColleagueRiley/OpenGL-Context-Creation)
- [exebook/x11clipboard](https://github.com/exebook/x11clipboard)
- [Implementing copy/paste in X11](https://handmade.network/forums/articles/t/8544-implementing_copy_paste_in_x11)
- [QWERTY](https://en.wikipedia.org/wiki/QWERTY)

*(and a bit of ai but it output was mostly trash slop)*

## Licence

This project is licenced under [LGPL-3 Licence](./LICENCE).
