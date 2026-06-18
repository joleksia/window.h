/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  window.h - single-header minimalistic windowing solution for GNU/Linux, unix-like and win32 systems.
 *
 *      - made by: Jakub Oleksiak (yakubofficialmail@gmail.com)
 *      - version: 1.0
 *      - licence: GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007
 *
 *
 *  Configuration (can be defined by user):
 *
 *      #define WINDOW_IMPLEMENTATION
 *          - TYPE: MANDATORY
 *          - DESCRIPTION: Embed the implementation section of the library into the source file.
 *                         NOTE:
 *                             This should be defined only once in the entire codebase.
 *                             Otherwise, defining this option will cause a multiple-definitions error.
 *
 *      #define WINDOW_BACKEND_X11
 *          - TYPE: OPTIONAL
 *          - DESCRIPTION: Force X11 implementation of window.h.
 *                         Defined by default on GNU/Linux and unix-like systems.
 * 
 *      #define WINDOW_BACKEND_WAYLAND
 *          - TYPE: OPTIONAL
 *          - DESCRIPTION: Force wayland implementation of window.h.
 *
 *
 *  Constants (MUST NOT be defined by user):
 *
 *      WINDOW_PLATFORM 
 *          - TYPE: String Literal
 *          - DESCRIPTION: Name of the platform window.h is used on as a string literal.
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if defined (__cplusplus)
# pragma once
#endif
#
#if !defined (_window_h_)
# define _window_h_ 1
#
# /* WINDEF (window.h API) - global functions */
# if !defined (WINDEF)
#  define WINDEF extern
# endif /* WINDEF */
#
# /* WININT (window.h internal API) - internal static functions */
# if !defined (WININT)
#  define WININT static inline
# endif /* WININT */
#
# /* Define platform macros */
# if defined (__linux__)
#  define WINDOW_PLATFORM "linux"
#  define WINDOW_PLATFORM_LINUX 1
#  /* define default backend if none is defined */
#  if !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 */
#  endif
#
#  /* define default backend if WINDOW_API_OPENGL is defined */
#  if defined (WINDOW_API_OPENGL)
#   define WINDOW_BACKEND_GL_EGL 1 /* by default window.h picks EGL */
#  else
#   define WINDOW_API_NONE 1
#  endif 
#
# elif defined (__APPLE__) || defined (__MACH__)
#  define WINDOW_PLATFORM "apple"
#  define WINDOW_PLATFORM_APPLE 1
#
# elif defined (__CYGWIN__) || defined (_WIN32)
#  define WINDOW_PLATFORM "win32"
#  define WINDOW_PLATFORM_WIN32 1
#
#  /* define default backend if WINDOW_API_OPENGL is defined */
#  if defined (WINDOW_API_OPENGL)
#   define WINDOW_BACKEND_GL_WGL 1 /* by default window.h picks WGL */
#  else
#   define WINDOW_API_NONE 1
#  endif 
#
# elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__bsdi__) || defined (__DragonFly__) || defined (__MidnightBSD__)
#  define WINDOW_PLATFORM "bsd"
#  define WINDOW_PLATFORM_BSD 1
#  /* define default backend if none is defined */
#  if !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 */
#  endif
#
#  /* define default backend if WINDOW_API_OPENGL is defined */
#  if defined (WINDOW_API_OPENGL)
#   define WINDOW_BACKEND_GL_EGL 1 /* by default window.h picks EGL */
#  else
#   define WINDOW_API_NONE 1
#  endif 
#
# else
#  error /* No valid platform found */
# endif
#
# /* Preprocessor configuration */
#
# if !defined (WINDOW_EVENT_QUEUE_CAPACITY)
#  define WINDOW_EVENT_QUEUE_CAPACITY 1024
# endif /* WINDOW_EVENT_QUEUE_CAPACITY */
#
# include <stddef.h>
# include <stdint.h>

/* inputs */

enum {
    WINDOW_BUTTON_NONE = 0,
# define WINDOW_BUTTON_NONE WINDOW_BUTTON_NONE

    WINDOW_BUTTON_LEFT,
# define WINDOW_BUTTON_LEFT WINDOW_BUTTON_LEFT

    WINDOW_BUTTON_RIGHT,
# define WINDOW_BUTTON_RIGHT WINDOW_BUTTON_RIGHT

    WINDOW_BUTTON_MIDDLE,
# define WINDOW_BUTTON_MIDDLE WINDOW_BUTTON_MIDDLE

    /* ... */
};


enum {
    WINDOW_KEYCODE_NONE = 0,
# define WINDOW_KEYCODE_NONE WINDOW_KEYCODE_NONE

    WINDOW_KEYCODE_ESCAPE = 0x100,
# define WINDOW_KEYCODE_ESCAPE WINDOW_KEYCODE_ESCAPE

    WINDOW_KEYCODE_F1 = 0x101,
# define WINDOW_KEYCODE_F1 WINDOW_KEYCODE_F1

    WINDOW_KEYCODE_F2 = 0x102,
# define WINDOW_KEYCODE_F2 WINDOW_KEYCODE_F2

    WINDOW_KEYCODE_F3 = 0x103,
# define WINDOW_KEYCODE_F3 WINDOW_KEYCODE_F3

    WINDOW_KEYCODE_F4 = 0x104,
# define WINDOW_KEYCODE_F4 WINDOW_KEYCODE_F4

    WINDOW_KEYCODE_F5 = 0x105,
# define WINDOW_KEYCODE_F5 WINDOW_KEYCODE_F5

    WINDOW_KEYCODE_F6 = 0x106,
# define WINDOW_KEYCODE_F6 WINDOW_KEYCODE_F6

    WINDOW_KEYCODE_F7 = 0x107,
# define WINDOW_KEYCODE_F7 WINDOW_KEYCODE_F7

    WINDOW_KEYCODE_F8 = 0x108,
# define WINDOW_KEYCODE_F8 WINDOW_KEYCODE_F8

    WINDOW_KEYCODE_F9 = 0x109,
# define WINDOW_KEYCODE_F9 WINDOW_KEYCODE_F9

    WINDOW_KEYCODE_F10 = 0x10A,
# define WINDOW_KEYCODE_F10 WINDOW_KEYCODE_F10

    WINDOW_KEYCODE_F11 = 0x10B,
# define WINDOW_KEYCODE_F11 WINDOW_KEYCODE_F11

    WINDOW_KEYCODE_F12 = 0x10C,
# define WINDOW_KEYCODE_F12 WINDOW_KEYCODE_F12

    WINDOW_KEYCODE_GRAVE = 0x60,
# define WINDOW_KEYCODE_GRAVE WINDOW_KEYCODE_GRAVE

    WINDOW_KEYCODE_ONE = 0x31,
# define WINDOW_KEYCODE_ONE WINDOW_KEYCODE_ONE

    WINDOW_KEYCODE_TWO = 0x32,
# define WINDOW_KEYCODE_TWO WINDOW_KEYCODE_TWO

    WINDOW_KEYCODE_THREE = 0x33,
# define WINDOW_KEYCODE_THREE WINDOW_KEYCODE_THREE

    WINDOW_KEYCODE_FOUR = 0x34,
# define WINDOW_KEYCODE_FOUR WINDOW_KEYCODE_FOUR

    WINDOW_KEYCODE_FIVE = 0x35,
# define WINDOW_KEYCODE_FIVE WINDOW_KEYCODE_FIVE

    WINDOW_KEYCODE_SIX = 0x36,
# define WINDOW_KEYCODE_SIX WINDOW_KEYCODE_SIX

    WINDOW_KEYCODE_SEVEN = 0x37,
# define WINDOW_KEYCODE_SEVEN WINDOW_KEYCODE_SEVEN

    WINDOW_KEYCODE_EIGHT = 0x38,
# define WINDOW_KEYCODE_EIGHT WINDOW_KEYCODE_EIGHT

    WINDOW_KEYCODE_NINE = 0x39,
# define WINDOW_KEYCODE_NINE WINDOW_KEYCODE_NINE

    WINDOW_KEYCODE_ZERO = 0x30,
# define WINDOW_KEYCODE_ZERO WINDOW_KEYCODE_ZERO

    WINDOW_KEYCODE_DASH = 0x2D,
# define WINDOW_KEYCODE_DASH WINDOW_KEYCODE_DASH

    WINDOW_KEYCODE_EQUAL = 0x3D,
# define WINDOW_KEYCODE_EQUAL WINDOW_KEYCODE_EQUAL

    WINDOW_KEYCODE_BACKSPACE = 0x08,
# define WINDOW_KEYCODE_BACKSPACE WINDOW_KEYCODE_BACKSPACE

    WINDOW_KEYCODE_TAB = 0x09,
# define WINDOW_KEYCODE_TAB WINDOW_KEYCODE_TAB

    WINDOW_KEYCODE_Q = 0x51,
# define WINDOW_KEYCODE_Q WINDOW_KEYCODE_Q

    WINDOW_KEYCODE_W = 0x57,
# define WINDOW_KEYCODE_W WINDOW_KEYCODE_W

    WINDOW_KEYCODE_E = 0x45,
# define WINDOW_KEYCODE_E WINDOW_KEYCODE_E

    WINDOW_KEYCODE_R = 0x52,
# define WINDOW_KEYCODE_R WINDOW_KEYCODE_R

    WINDOW_KEYCODE_T = 0x54,
# define WINDOW_KEYCODE_T WINDOW_KEYCODE_T

    WINDOW_KEYCODE_Y = 0x59,
# define WINDOW_KEYCODE_Y WINDOW_KEYCODE_Y

    WINDOW_KEYCODE_U = 0x55,
# define WINDOW_KEYCODE_U WINDOW_KEYCODE_U

    WINDOW_KEYCODE_I = 0x49,
# define WINDOW_KEYCODE_I WINDOW_KEYCODE_I

    WINDOW_KEYCODE_O = 0x4F,
# define WINDOW_KEYCODE_O WINDOW_KEYCODE_O

    WINDOW_KEYCODE_P = 0x50,
# define WINDOW_KEYCODE_P WINDOW_KEYCODE_P

    WINDOW_KEYCODE_OBRACE = 0x5B,
# define WINDOW_KEYCODE_OBRACE WINDOW_KEYCODE_OBRACE

    WINDOW_KEYCODE_CBRACE = 0x5D,
# define WINDOW_KEYCODE_CBRACE WINDOW_KEYCODE_CBRACE

    WINDOW_KEYCODE_CAPSLOCK = 0,
# define WINDOW_KEYCODE_CAPSLOCK WINDOW_KEYCODE_CAPSLOCK

    WINDOW_KEYCODE_A = 0x41,
# define WINDOW_KEYCODE_A WINDOW_KEYCODE_A

    WINDOW_KEYCODE_S = 0x53,
# define WINDOW_KEYCODE_S WINDOW_KEYCODE_S

    WINDOW_KEYCODE_D = 0x44,
# define WINDOW_KEYCODE_D WINDOW_KEYCODE_D

    WINDOW_KEYCODE_F = 0x46,
# define WINDOW_KEYCODE_F WINDOW_KEYCODE_F

    WINDOW_KEYCODE_G = 0x47,
# define WINDOW_KEYCODE_G WINDOW_KEYCODE_G

    WINDOW_KEYCODE_H = 0x48,
# define WINDOW_KEYCODE_H WINDOW_KEYCODE_H

    WINDOW_KEYCODE_J = 0x4A,
# define WINDOW_KEYCODE_J WINDOW_KEYCODE_J

    WINDOW_KEYCODE_K = 0x4B,
# define WINDOW_KEYCODE_K WINDOW_KEYCODE_K

    WINDOW_KEYCODE_L = 0x4C,
# define WINDOW_KEYCODE_L WINDOW_KEYCODE_L

    WINDOW_KEYCODE_SEMICOLON = 0x3B,
# define WINDOW_KEYCODE_SEMICOLON WINDOW_KEYCODE_SEMICOLON

    WINDOW_KEYCODE_QUOTE = 0x27,
# define WINDOW_KEYCODE_QUOTE WINDOW_KEYCODE_QUOTE

    WINDOW_KEYCODE_BACKSLASH = 0x5C,
# define WINDOW_KEYCODE_BACKSLASH WINDOW_KEYCODE_BACKSLASH

    WINDOW_KEYCODE_ENTER = 0x0D,
# define WINDOW_KEYCODE_ENTER WINDOW_KEYCODE_ENTER

    WINDOW_KEYCODE_LSHIFT = 0x120,
# define WINDOW_KEYCODE_LSHIFT WINDOW_KEYCODE_LSHIFT

    WINDOW_KEYCODE_Z = 0x5A,
# define WINDOW_KEYCODE_Z WINDOW_KEYCODE_Z

    WINDOW_KEYCODE_X = 0x58,
# define WINDOW_KEYCODE_X WINDOW_KEYCODE_X

    WINDOW_KEYCODE_C = 0x43,
# define WINDOW_KEYCODE_C WINDOW_KEYCODE_C

    WINDOW_KEYCODE_V = 0x56,
# define WINDOW_KEYCODE_V WINDOW_KEYCODE_V

    WINDOW_KEYCODE_B = 0x42,
# define WINDOW_KEYCODE_B WINDOW_KEYCODE_B

    WINDOW_KEYCODE_N = 0x4E,
# define WINDOW_KEYCODE_N WINDOW_KEYCODE_N

    WINDOW_KEYCODE_M = 0x4D,
# define WINDOW_KEYCODE_M WINDOW_KEYCODE_M

    WINDOW_KEYCODE_COMMA = 0x2C,
# define WINDOW_KEYCODE_COMMA WINDOW_KEYCODE_COMMA

    WINDOW_KEYCODE_PERIOD = 0x2E,
# define WINDOW_KEYCODE_PERIOD WINDOW_KEYCODE_PERIOD

    WINDOW_KEYCODE_SLASH = 0x2F,
# define WINDOW_KEYCODE_SLASH WINDOW_KEYCODE_SLASH

    WINDOW_KEYCODE_RSHIFT = 0x121,
# define WINDOW_KEYCODE_RSHIFT WINDOW_KEYCODE_RSHIFT

    WINDOW_KEYCODE_LCTRL = 0x122,
# define WINDOW_KEYCODE_LCTRL WINDOW_KEYCODE_LCTRL

    WINDOW_KEYCODE_MOD = 0x123,
# define WINDOW_KEYCODE_MOD WINDOW_KEYCODE_MOD

    WINDOW_KEYCODE_LALT = 0x124,
# define WINDOW_KEYCODE_LALT WINDOW_KEYCODE_LALT

    WINDOW_KEYCODE_SPACE = 0x20,
# define WINDOW_KEYCODE_SPACE WINDOW_KEYCODE_SPACE

    WINDOW_KEYCODE_RALT = 0x125,
# define WINDOW_KEYCODE_RALT WINDOW_KEYCODE_RALT

    WINDOW_KEYCODE_RCTRL = 0x126,
# define WINDOW_KEYCODE_RCTRL WINDOW_KEYCODE_RCTRL

    WINDOW_KEYCODE_PRINTSCREEN = 0x127,
# define WINDOW_KEYCODE_PRINTSCREEN WINDOW_KEYCODE_PRINTSCREEN

    WINDOW_KEYCODE_SCROLLLOCK = 0x128,
# define WINDOW_KEYCODE_SCROLLLOCK WINDOW_KEYCODE_SCROLLLOCK

    WINDOW_KEYCODE_PAUSE = 0x129,
# define WINDOW_KEYCODE_PAUSE WINDOW_KEYCODE_PAUSE

    WINDOW_KEYCODE_INSERT = 0x144,
# define WINDOW_KEYCODE_INSERT WINDOW_KEYCODE_INSERT

    WINDOW_KEYCODE_HOME = 0x145,
# define WINDOW_KEYCODE_HOME WINDOW_KEYCODE_HOME

    WINDOW_KEYCODE_PAGEUP = 0x146,
# define WINDOW_KEYCODE_PAGEUP WINDOW_KEYCODE_PAGEUP

    WINDOW_KEYCODE_DELETE = 0x147,
# define WINDOW_KEYCODE_DELETE WINDOW_KEYCODE_DELETE

    WINDOW_KEYCODE_END = 0x148,
# define WINDOW_KEYCODE_END WINDOW_KEYCODE_END

    WINDOW_KEYCODE_PAGEDOWN = 0x149,
# define WINDOW_KEYCODE_PAGEDOWN WINDOW_KEYCODE_PAGEDOWN

    WINDOW_KEYCODE_UP = 0x140,
# define WINDOW_KEYCODE_UP WINDOW_KEYCODE_UP

    WINDOW_KEYCODE_LEFT = 0x141,
# define WINDOW_KEYCODE_LEFT WINDOW_KEYCODE_LEFT

    WINDOW_KEYCODE_DOWN = 0x142,
# define WINDOW_KEYCODE_DOWN WINDOW_KEYCODE_DOWN

    WINDOW_KEYCODE_RIGHT = 0x143,
# define WINDOW_KEYCODE_RIGHT WINDOW_KEYCODE_RIGHT

    WINDOW_KEYCODE_NUMLOCK = 0x12A,
# define WINDOW_KEYCODE_NUMLOCK WINDOW_KEYCODE_NUMLOCK

    WINDOW_KEYCODE_NUMSLASH = 0x16A,
# define WINDOW_KEYCODE_NUMSLASH WINDOW_KEYCODE_NUMSLASH

    WINDOW_KEYCODE_NUMSTAR = 0x16B,
# define WINDOW_KEYCODE_NUMSTAR WINDOW_KEYCODE_NUMSTAR

    WINDOW_KEYCODE_NUMDASH = 0x16C,
# define WINDOW_KEYCODE_NUMDASH WINDOW_KEYCODE_NUMDASH

    WINDOW_KEYCODE_NUM7 = 0x167,
# define WINDOW_KEYCODE_NUM7 WINDOW_KEYCODE_NUM7

    WINDOW_KEYCODE_NUM8 = 0x168,
# define WINDOW_KEYCODE_NUM8 WINDOW_KEYCODE_NUM8

    WINDOW_KEYCODE_NUM9 = 0x169,
# define WINDOW_KEYCODE_NUM9 WINDOW_KEYCODE_NUM9

    WINDOW_KEYCODE_NUM4 = 0x164,
# define WINDOW_KEYCODE_NUM4 WINDOW_KEYCODE_NUM4

    WINDOW_KEYCODE_NUM5 = 0x165,
# define WINDOW_KEYCODE_NUM5 WINDOW_KEYCODE_NUM5

    WINDOW_KEYCODE_NUM6 = 0x166,
# define WINDOW_KEYCODE_NUM6 WINDOW_KEYCODE_NUM6

    WINDOW_KEYCODE_NUM1 = 0x161,
# define WINDOW_KEYCODE_NUM1 WINDOW_KEYCODE_NUM1

    WINDOW_KEYCODE_NUM2 = 0x162,
# define WINDOW_KEYCODE_NUM2 WINDOW_KEYCODE_NUM2

    WINDOW_KEYCODE_NUM3 = 0x163,
# define WINDOW_KEYCODE_NUM3 WINDOW_KEYCODE_NUM3

    WINDOW_KEYCODE_NUM0 = 0x160,
# define WINDOW_KEYCODE_NUM0 WINDOW_KEYCODE_NUM0

    WINDOW_KEYCODE_NUMSEP = 0x16D,
# define WINDOW_KEYCODE_NUMSEP WINDOW_KEYCODE_NUMSEP

    WINDOW_KEYCODE_NUMPLUS = 0x16E,
# define WINDOW_KEYCODE_NUMPLUS WINDOW_KEYCODE_NUMPLUS

    WINDOW_KEYCODE_NUMENTER = 0x16F,
# define WINDOW_KEYCODE_NUMENTER WINDOW_KEYCODE_NUMENTER

    /* ... */

};


enum {
    WINDOW_PROP_PLATFORM_NONE = 0,
# define WINDOW_PROP_PLATFORM_NONE WINDOW_PROP_PLATFORM_NONE

    /* X11 properties */

    WINDOW_PROP_PLATFORM_X11_DISPLAY,
# define WINDOW_PROP_PLATFORM_X11_DISPLAY WINDOW_PROP_PLATFORM_X11_DISPLAY

    WINDOW_PROP_PLATFORM_X11_ROOT_ID,
# define WINDOW_PROP_PLATFORM_X11_ROOT_ID WINDOW_PROP_PLATFORM_X11_ROOT_ID

    WINDOW_PROP_PLATFORM_X11_SCREEN_ID,
# define WINDOW_PROP_PLATFORM_X11_SCREEN_ID WINDOW_PROP_PLATFORM_X11_SCREEN_ID

    /* ... */
};


enum {
    WINDOW_PROP_WINDOW_NONE = 0,
# define WINDOW_PROP_WINDOW_NONE WINDOW_PROP_WINDOW_NONE

    /* X11 properties */

    WINDOW_PROP_WINDOW_X11_DISPLAY,
# define WINDOW_PROP_WINDOW_X11_DISPLAY WINDOW_PROP_WINDOW_X11_DISPLAY

    WINDOW_PROP_WINDOW_X11_ROOT_ID,
# define WINDOW_PROP_WINDOW_X11_ROOT_ID WINDOW_PROP_WINDOW_X11_ROOT_ID

    WINDOW_PROP_WINDOW_X11_PARENT_ID,
# define WINDOW_PROP_WINDOW_X11_PARENT_ID WINDOW_PROP_WINDOW_X11_PARENT_ID

    WINDOW_PROP_WINDOW_X11_CLIENT_ID,
# define WINDOW_PROP_WINDOW_X11_CLIENT_ID WINDOW_PROP_WINDOW_X11_CLIENT_ID

    WINDOW_PROP_WINDOW_X11_VISUAL,
# define WINDOW_PROP_WINDOW_X11_VISUAL WINDOW_PROP_WINDOW_X11_VISUAL

    /* ... */
};


enum {

    WINDOW_EVENT_NONE = 0,
# define WINDOW_EVENT_NONE WINDOW_EVENT_NONE

    WINDOW_EVENT_QUIT,
# define WINDOW_EVENT_QUIT WINDOW_EVENT_QUIT

    WINDOW_EVENT_MOUSE_MOTION,
# define WINDOW_EVENT_MOUSE_MOTION WINDOW_EVENT_MOUSE_MOTION

    WINDOW_EVENT_MOUSE_BUTTON,
# define WINDOW_EVENT_MOUSE_BUTTON WINDOW_EVENT_MOUSE_BUTTON

    WINDOW_EVENT_MOUSE_SCROLL,
# define WINDOW_EVENT_MOUSE_SCROLL WINDOW_EVENT_MOUSE_SCROLL

    WINDOW_EVENT_KEYBOARD_KEY,
# define WINDOW_EVENT_KEYBOARD_KEY WINDOW_EVENT_KEYBOARD_KEY

    WINDOW_EVENT_WINDOW_RESIZE,
# define WINDOW_EVENT_WINDOW_RESIZE WINDOW_EVENT_WINDOW_RESIZE

    WINDOW_EVENT_WINDOW_MOTION,
# define WINDOW_EVENT_WINDOW_MOTION WINDOW_EVENT_WINDOW_MOTION

    /* ... */

};


enum {
    
    WINDOW_FLAG_NONE = 0x00000000,
# define WINDOW_FLAG_NONE WINDOW_FLAG_NONE
    
    WINDOW_FLAG_FULLSCREEN = 0x00000001,
# define WINDOW_FLAG_FULLSCREEN WINDOW_FLAG_FULLSCREEN
    
    WINDOW_FLAG_MINIMIZED = 0x00000002,
# define WINDOW_FLAG_MINIMIZED WINDOW_FLAG_MINIMIZED
    
    WINDOW_FLAG_MAXIMIZED = 0x00000004,
# define WINDOW_FLAG_MAXIMIZED WINDOW_FLAG_MAXIMIZED
    
    WINDOW_FLAG_RESIZABLE = 0x00000008,
# define WINDOW_FLAG_RESIZABLE WINDOW_FLAG_RESIZABLE
    
    WINDOW_FLAG_TOPMOST = 0x00000010,
# define WINDOW_FLAG_TOPMOST WINDOW_FLAG_TOPMOST
    
    WINDOW_FLAG_UNDECORATED = 0x00000040,
# define WINDOW_FLAG_UNDECORATED WINDOW_FLAG_UNDECORATED

    /* ... */
};


enum {
    WINDOW_GL_NONE = 0,
# define WINDOW_GL_NONE WINDOW_GL_NONE
    
    WINDOW_GL_DOUBLEBUFFER,
# define WINDOW_GL_DOUBLEBUFFER WINDOW_GL_DOUBLEBUFFER

    WINDOW_GL_RED_SIZE,
# define WINDOW_GL_RED_SIZE WINDOW_GL_RED_SIZE

    WINDOW_GL_GREEN_SIZE,
# define WINDOW_GL_GREEN_SIZE WINDOW_GL_GREEN_SIZE

    WINDOW_GL_BLUE_SIZE,
# define WINDOW_GL_BLUE_SIZE WINDOW_GL_BLUE_SIZE

    WINDOW_GL_ALPHA_SIZE,
# define WINDOW_GL_ALPHA_SIZE WINDOW_GL_ALPHA_SIZE

    WINDOW_GL_DEPTH_SIZE,
# define WINDOW_GL_DEPTH_SIZE WINDOW_GL_DEPTH_SIZE

    WINDOW_GL_STENCIL_SIZE,
# define WINDOW_GL_STENCIL_SIZE WINDOW_GL_STENCIL_SIZE
    
    WINDOW_GL_CONTEXT_MAJOR_VERSION,
# define WINDOW_GL_CONTEXT_MAJOR_VERSION WINDOW_GL_CONTEXT_MAJOR_VERSION

    WINDOW_GL_CONTEXT_MINOR_VERSION,
# define WINDOW_GL_CONTEXT_MINOR_VERSION WINDOW_GL_CONTEXT_MINOR_VERSION

    WINDOW_GL_CONTEXT_PROFILE,
# define WINDOW_GL_CONTEXT_PROFILE WINDOW_GL_CONTEXT_PROFILE

    WINDOW_GL_CONTEXT_DEBUG,
# define WINDOW_GL_CONTEXT_DEBUG WINDOW_GL_CONTEXT_DEBUG

    /* ... */
};


typedef struct s_window *t_window;


typedef struct s_glcontext *t_glcontext;


typedef struct s_eventCommon t_eventCommon;

struct s_eventCommon {
    uint32_t type;
    uint64_t timestamp;
};


typedef struct s_eventQuit t_eventQuit;

struct s_eventQuit {
    uint32_t type;
    uint64_t timestamp;
};


typedef struct s_eventMouseMotion t_eventMouseMotion;

struct s_eventMouseMotion {
    uint32_t type;
    uint64_t timestamp;

    int32_t x, xrel;
    int32_t y, yrel;
};


typedef struct s_eventMouseButton t_eventMouseButton;

struct s_eventMouseButton {
    uint32_t type;
    uint64_t timestamp;

    int8_t btn;
    int8_t state;
};


typedef struct s_eventMouseScroll t_eventMouseScroll;

struct s_eventMouseScroll {
    uint32_t type;
    uint64_t timestamp;

    int8_t scroll;
};


typedef struct s_eventKeyboardKey t_eventKeyboardKey;

struct s_eventKeyboardKey {
    uint32_t type;
    uint64_t timestamp;

    int32_t keysym;
    int32_t keycode;
    int8_t  state;
};


typedef struct s_eventWindow t_eventWindow;

struct s_eventWindow {
    uint32_t type;
    uint64_t timestamp;

    uint32_t x, y;
    uint32_t w, h;
};


typedef union u_event t_event;

union u_event {
    uint32_t type;

    /* common event */
    t_eventCommon common;

    /* mouse event */
    t_eventMouseMotion motion;
    t_eventMouseButton button;

    /* keyboard event */
    t_eventKeyboardKey key;

    /* window event */
    t_eventWindow window;
};


/* library functions */

WINDEF int winInit(void);

WINDEF int winQuit(void);

WINDEF int winGetSize(size_t *, size_t *);

WINDEF void *winGetProperty(const uint32_t);

/* windowing functions */

WINDEF int winCreateWindow(t_window *, const size_t, const size_t, const char *, const uint32_t);

WINDEF int winCreateNestedWindow(t_window *, t_window, const size_t, const size_t, const char *, const uint32_t);

WINDEF int winDestroyWindow(t_window);

WINDEF int winSetWindowFlag(t_window, const uint32_t);

WINDEF void *winGetWindowProperty(t_window, const uint32_t);

WINDEF int winMapWindow(t_window);

WINDEF int winUnmapWindow(t_window);

WINDEF int winGetWindowSize(t_window, size_t *, size_t *);

WINDEF int winSetWindowSize(t_window, const size_t, const size_t);

WINDEF int winSetWindowMinSize(t_window, const size_t, const size_t);

WINDEF int winSetWindowMaxSize(t_window, const size_t, const size_t);

WINDEF int winGetWindowPosition(t_window, size_t *, size_t *);

WINDEF int winSetWindowPosition(t_window, const size_t, const size_t);

WINDEF int winGetWindowTitle(t_window, char **);

WINDEF int winSetWindowTitle(t_window, const char *);

/* opengl context functions */

WINDEF int winGLCreateContext(t_glcontext *, t_window);

WINDEF int winGLDestroyContext(t_glcontext, t_window);

WINDEF int winGLSetAttribute(const int, const int);

WINDEF int winGLMakeCurrent(t_glcontext, t_window);

WINDEF int winGLSwapBuffers(t_glcontext, t_window);

WINDEF int winGLSwapInterval(t_glcontext, const int);

WINDEF void *winGLGetProcAddress(const char *);

/* event functions */

WINDEF int winPollEvents(t_event *);

WINDEF int winWaitEvents(t_event *);

WINDEF int winPushEvent(t_event *);

WINDEF int winPopEvent(t_event *);

WINDEF int winPeekEvent(t_event *);

WINDEF int winFlushEvents(void);

/* timing functions */

WINDEF uint64_t winGetTime(void);

WINDEF int winWaitTime(uint64_t);

# if defined WINDOW_IMPLEMENTATION
#
#  /* include headers */
#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>
#
#  /* include unix headers */
#  if defined (WINDOW_PLATFORM_LINUX) || defined (WINDOW_PLATFORM_APPLE) || defined (WINDOW_PLATFORM_BSD)
#   include <dlfcn.h>
#   include <unistd.h>
#   include <sys/time.h>
#
#  /* include win32 headers*/
#  elif defined (WINDOW_PLATFORM_WIN32)
#   include <windows.h>
#  endif

/* platform-independent */

typedef struct __window_h_eventQueue __window_h_eventQueue;

struct __window_h_eventQueue {
    t_event *bgn, /* beginning of the circular buffer */
            *end, /* end of the circular buffer */
            *arr; /* circular buffer */

    size_t cap, /* circular buffer elements capacity */
           cnt; /* circular buffer elements count */
};

/* platform-specific */

typedef struct __window_h_x11 *__window_h_x11;

typedef struct __window_h_egl *__window_h_egl;

static struct __window_h  {

    /* platform-independent */

    struct s_window *window_list;

    __window_h_eventQueue event_queue;

    /* platform-specific */

    __window_h_x11 x11;

    __window_h_egl egl;

    /* ... */

} __window_h;


typedef struct s_window_x11 *t_window_x11;

typedef struct s_window_win32 *t_window_win32;

struct s_window {

    /* platform-independent */

    struct s_window *next;

    /* config flag data */
    uint32_t flags;

    /* mapping boolean */
    uint8_t mapped;
    
    /* structure data */
    size_t siz_w, siz_h;
    size_t pos_x, pos_y;

    /* platform-specific */

    t_window_x11 x11;

    t_window_win32 win32;

    /* ... */

};


typedef struct s_glcontext_egl *t_glcontext_egl;

typedef struct s_glcontext_wgl *t_glcontext_wgl;

struct s_glcontext {

    /* platform-independent */

    /* ... */

    /* platform-specific */

    t_glcontext_egl egl;
    
    t_glcontext_wgl wgl;

    /* ... */

};

#  /* WINDOW_BACKEND_X11 - Unix X11 implementation layer */
#  if defined (WINDOW_BACKEND_X11)
#
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xutil.h>
#   include <X11/Xatom.h>
#   include <X11/XKBlib.h>
#   include <X11/keysym.h>
#   include <X11/keysymdef.h>
#
#   define _NET_WM_STATE_REMOVE 0
#   define _NET_WM_STATE_ADD    1
#   define _NET_WM_STATE_TOGGLE 2

static const struct __window_h_keymap {
    uint32_t src;
    uint32_t kc;
    uint32_t ks;
} __window_h_keymap[] = {
    
    { XK_Escape, WINDOW_KEYCODE_ESCAPE, 0 },
    
    { XK_F1, WINDOW_KEYCODE_F1, 0 },
    
    { XK_F2, WINDOW_KEYCODE_F2, 0 },
    
    { XK_F3, WINDOW_KEYCODE_F3, 0 },
    
    { XK_F4, WINDOW_KEYCODE_F4, 0 },
    
    { XK_F5, WINDOW_KEYCODE_F5, 0 },
    
    { XK_F6, WINDOW_KEYCODE_F6, 0 },
    
    { XK_F7, WINDOW_KEYCODE_F7, 0 },
    
    { XK_F8, WINDOW_KEYCODE_F8, 0 },
    
    { XK_F9, WINDOW_KEYCODE_F9, 0 },
    
    { XK_F10, WINDOW_KEYCODE_F10, 0 },
    
    { XK_F11, WINDOW_KEYCODE_F11, 0 },
    
    { XK_F12, WINDOW_KEYCODE_F12, 0 },
    
    { XK_grave, WINDOW_KEYCODE_GRAVE, 0 }, 
    { XK_asciitilde, WINDOW_KEYCODE_GRAVE, 0 },
    
    { XK_1, WINDOW_KEYCODE_ONE, 0 },       
    { XK_exclam, WINDOW_KEYCODE_ONE, 0 },
    
    { XK_2, WINDOW_KEYCODE_TWO, 0 },       
    { XK_at, WINDOW_KEYCODE_TWO, 0 },
    
    { XK_3, WINDOW_KEYCODE_THREE, 0 },     
    { XK_numbersign, WINDOW_KEYCODE_THREE, 0 },
    
    { XK_4, WINDOW_KEYCODE_FOUR, 0 },      
    { XK_dollar, WINDOW_KEYCODE_FOUR, 0 },
    
    { XK_5, WINDOW_KEYCODE_FIVE, 0 },      
    { XK_percent, WINDOW_KEYCODE_FIVE, 0 },
    
    { XK_6, WINDOW_KEYCODE_SIX, 0 },       
    { XK_asciicircum, WINDOW_KEYCODE_SIX, 0 },
    
    { XK_7, WINDOW_KEYCODE_SEVEN, 0 },     
    { XK_ampersand, WINDOW_KEYCODE_SEVEN, 0 },
    
    { XK_8, WINDOW_KEYCODE_EIGHT, 0 },     
    { XK_asterisk, WINDOW_KEYCODE_EIGHT, 0 },
    
    { XK_9, WINDOW_KEYCODE_NINE, 0 },      
    { XK_parenleft, WINDOW_KEYCODE_NINE, 0 },
    
    { XK_0, WINDOW_KEYCODE_ZERO, 0 },      
    { XK_parenright, WINDOW_KEYCODE_ZERO, 0 },
    
    { XK_minus, WINDOW_KEYCODE_DASH, 0 },  
    { XK_underscore, WINDOW_KEYCODE_DASH, 0 },
    
    { XK_equal, WINDOW_KEYCODE_EQUAL, 0 },
    { XK_plus, WINDOW_KEYCODE_EQUAL, 0 },
    
    { XK_BackSpace, WINDOW_KEYCODE_BACKSPACE, 0 },
    
    { XK_Tab, WINDOW_KEYCODE_TAB, 0 },
    
    { XK_Q, WINDOW_KEYCODE_Q, 0 },
    { XK_q, WINDOW_KEYCODE_Q, 0 },
    
    { XK_W, WINDOW_KEYCODE_W, 0 },
    { XK_w, WINDOW_KEYCODE_W, 0 },
    
    { XK_E, WINDOW_KEYCODE_E, 0 },
    { XK_e, WINDOW_KEYCODE_E, 0 },
    
    { XK_R, WINDOW_KEYCODE_R, 0 },
    { XK_r, WINDOW_KEYCODE_R, 0 },
    
    { XK_T, WINDOW_KEYCODE_T, 0 },
    { XK_t, WINDOW_KEYCODE_T, 0 },
    
    { XK_Y, WINDOW_KEYCODE_Y, 0 },
    { XK_y, WINDOW_KEYCODE_Y, 0 },
    
    { XK_U, WINDOW_KEYCODE_U, 0 },
    { XK_u, WINDOW_KEYCODE_U, 0 },
    
    { XK_I, WINDOW_KEYCODE_I, 0 },
    { XK_i, WINDOW_KEYCODE_I, 0 },
    
    { XK_O, WINDOW_KEYCODE_O, 0 },
    { XK_o, WINDOW_KEYCODE_O, 0 },
    
    { XK_P, WINDOW_KEYCODE_P, 0 },
    { XK_p, WINDOW_KEYCODE_P, 0 },
    
    { XK_bracketleft, WINDOW_KEYCODE_OBRACE, 0 },
    { XK_braceleft, WINDOW_KEYCODE_OBRACE, 0 },
    
    { XK_bracketright, WINDOW_KEYCODE_CBRACE, 0 },
    { XK_braceright, WINDOW_KEYCODE_CBRACE, 0 },

    { XK_Caps_Lock, WINDOW_KEYCODE_CAPSLOCK, 0 },

    { XK_A, WINDOW_KEYCODE_A, 0 },
    { XK_a, WINDOW_KEYCODE_A, 0 },

    { XK_S, WINDOW_KEYCODE_S, 0 },
    { XK_s, WINDOW_KEYCODE_S, 0 },

    { XK_D, WINDOW_KEYCODE_D, 0 },
    { XK_d, WINDOW_KEYCODE_D, 0 },

    { XK_F, WINDOW_KEYCODE_F, 0 },
    { XK_f, WINDOW_KEYCODE_F, 0 },

    { XK_G, WINDOW_KEYCODE_G, 0 },
    { XK_g, WINDOW_KEYCODE_G, 0 },

    { XK_H, WINDOW_KEYCODE_H, 0 },
    { XK_h, WINDOW_KEYCODE_H, 0 },

    { XK_J, WINDOW_KEYCODE_J, 0 },
    { XK_j, WINDOW_KEYCODE_J, 0 },

    { XK_K, WINDOW_KEYCODE_K, 0 },
    { XK_k, WINDOW_KEYCODE_K, 0 },

    { XK_L, WINDOW_KEYCODE_L, 0 },
    { XK_l, WINDOW_KEYCODE_L, 0 },

    { XK_semicolon, WINDOW_KEYCODE_SEMICOLON, 0 },
    { XK_colon, WINDOW_KEYCODE_SEMICOLON, 0 },

    { XK_apostrophe, WINDOW_KEYCODE_QUOTE, 0 },
    { XK_quotedbl, WINDOW_KEYCODE_QUOTE, 0 },

    { XK_backslash, WINDOW_KEYCODE_BACKSLASH, 0 },
    { XK_bar, WINDOW_KEYCODE_BACKSLASH, 0 },

    { XK_Return, WINDOW_KEYCODE_ENTER, 0 },

    { XK_Shift_L, WINDOW_KEYCODE_LSHIFT, 0 },
    
    { XK_Z, WINDOW_KEYCODE_Z, 0 },
    { XK_z, WINDOW_KEYCODE_Z, 0 },
    
    { XK_X, WINDOW_KEYCODE_X, 0 },
    { XK_x, WINDOW_KEYCODE_X, 0 },
    
    { XK_C, WINDOW_KEYCODE_C, 0 },
    { XK_c, WINDOW_KEYCODE_C, 0 },
    
    { XK_V, WINDOW_KEYCODE_V, 0 },
    { XK_v, WINDOW_KEYCODE_V, 0 },
    
    { XK_B, WINDOW_KEYCODE_B, 0 },
    { XK_b, WINDOW_KEYCODE_B, 0 },
    
    { XK_N, WINDOW_KEYCODE_N, 0 },
    { XK_n, WINDOW_KEYCODE_N, 0 },
    
    { XK_M, WINDOW_KEYCODE_M, 0 },
    { XK_m, WINDOW_KEYCODE_M, 0 },
    
    { XK_comma, WINDOW_KEYCODE_COMMA, 0 },
    { XK_less, WINDOW_KEYCODE_COMMA, 0 },
    
    { XK_period, WINDOW_KEYCODE_PERIOD, 0 },
    { XK_greater, WINDOW_KEYCODE_PERIOD, 0 },
    
    { XK_slash, WINDOW_KEYCODE_SLASH, 0 },
    { XK_question, WINDOW_KEYCODE_SLASH, 0 },
    
    { XK_Shift_R, WINDOW_KEYCODE_RSHIFT, 0 },
    
    { XK_Control_L, WINDOW_KEYCODE_LCTRL, 0 },
    
    { XK_Super_L, WINDOW_KEYCODE_MOD, 0 },
    
    { XK_Alt_L, WINDOW_KEYCODE_LALT, 0 },
    
    { XK_space, WINDOW_KEYCODE_SPACE, 0 },
    
    { XK_Alt_R, WINDOW_KEYCODE_RALT, 0 },
    
    { XK_Control_R, WINDOW_KEYCODE_RCTRL, 0 },

    { XK_Print, WINDOW_KEYCODE_PRINTSCREEN, 0 },
    
    { XK_Scroll_Lock, WINDOW_KEYCODE_SCROLLLOCK, 0 },
    
    { XK_Pause, WINDOW_KEYCODE_PAUSE, 0 },

    { XK_Insert, WINDOW_KEYCODE_INSERT, 0 },
    
    { XK_Home, WINDOW_KEYCODE_HOME, 0 },
    
    { XK_Prior, WINDOW_KEYCODE_PAGEUP, 0 },

    { XK_Delete, WINDOW_KEYCODE_DELETE, 0 },
    
    { XK_End, WINDOW_KEYCODE_END, 0 },
    
    { XK_Next, WINDOW_KEYCODE_PAGEDOWN, 0 },

    { XK_Up, WINDOW_KEYCODE_UP, 0 },
    
    { XK_Left, WINDOW_KEYCODE_LEFT, 0 },
    
    { XK_Down, WINDOW_KEYCODE_DOWN, 0 },
    
    { XK_Right, WINDOW_KEYCODE_RIGHT, 0 },

    { XK_Num_Lock, WINDOW_KEYCODE_NUMLOCK, 0 },
    
    { XK_KP_Divide, WINDOW_KEYCODE_NUMSLASH, 0 },
    
    { XK_KP_Multiply, WINDOW_KEYCODE_NUMSTAR, 0 },
    
    { XK_KP_Subtract, WINDOW_KEYCODE_NUMDASH, 0 },
    
    { XK_KP_Home, WINDOW_KEYCODE_NUM7, 0 },
    { XK_KP_7, WINDOW_KEYCODE_NUM7, 0 },
    
    { XK_KP_Up, WINDOW_KEYCODE_NUM8, 0 },
    { XK_KP_8, WINDOW_KEYCODE_NUM8, 0 },
    
    { XK_KP_Prior, WINDOW_KEYCODE_NUM9, 0 },
    { XK_KP_9, WINDOW_KEYCODE_NUM9, 0 },
    
    { XK_KP_Left, WINDOW_KEYCODE_NUM4, 0 },
    { XK_KP_4, WINDOW_KEYCODE_NUM4, 0 },
    
    { XK_KP_Begin, WINDOW_KEYCODE_NUM5, 0 },
    { XK_KP_5, WINDOW_KEYCODE_NUM5, 0 },
    
    { XK_KP_Right, WINDOW_KEYCODE_NUM6, 0 },
    { XK_KP_6, WINDOW_KEYCODE_NUM6, 0 },
    
    { XK_KP_End, WINDOW_KEYCODE_NUM1, 0 },
    { XK_KP_1, WINDOW_KEYCODE_NUM1, 0 },
    
    { XK_KP_Down, WINDOW_KEYCODE_NUM2, 0 },
    { XK_KP_2, WINDOW_KEYCODE_NUM2, 0 },
    
    { XK_KP_Next, WINDOW_KEYCODE_NUM3, 0 },
    { XK_KP_3, WINDOW_KEYCODE_NUM3, 0 },
    
    { XK_KP_Insert, WINDOW_KEYCODE_NUM0, 0 },
    { XK_KP_0, WINDOW_KEYCODE_NUM0, 0 },
    
    { XK_KP_Delete, WINDOW_KEYCODE_NUMSEP, 0 },
    
    { XK_KP_Add, WINDOW_KEYCODE_NUMPLUS, 0 },
    
    { XK_KP_Enter, WINDOW_KEYCODE_NUMENTER, 0 },

    /* ... */

    { 0, WINDOW_KEYCODE_NONE, 0 }
};


/* internal type declarations */

typedef XClassHint *(* PFN_XAllocClassHint_PROC) (void);
typedef XSizeHints *(* PFN_XAllocSizeHints_PROC) (void);
typedef XWMHints *(* PFN_XAllocWMHints_PROC) (void);
typedef int (* PFN_XChangeProperty_PROC) (Display *, Window, Atom, Atom, int, int, const unsigned char *, int);
typedef int (* PFN_XChangeWindowAttributes_PROC) (Display *, Window, unsigned long, XSetWindowAttributes *);
typedef Bool (* PFN_XCheckIfEvent_PROC) (Display *, XEvent *, Bool(*_PROC) (Display *, XEvent *, XPointer), XPointer);
typedef Bool (* PFN_XCheckTypedWindowEvent_PROC) (Display *, Window, int, XEvent *);
typedef int (* PFN_XCloseDisplay_PROC) (Display *);
typedef int (* PFN_XConvertSelection_PROC) (Display *, Atom, Atom, Atom, Window, Time);
typedef Colormap (* PFN_XCreateColormap_PROC) (Display *, Window, Visual *, int);
typedef Cursor (* PFN_XCreateFontCursor_PROC) (Display *, unsigned int);
typedef Region (* PFN_XCreateRegion_PROC) (void);
typedef Window (* PFN_XCreateWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int, unsigned int, int, unsigned int, Visual *, unsigned long, XSetWindowAttributes *);
typedef int (* PFN_XDefineCursor_PROC) (Display *, Window, Cursor);
typedef int (* PFN_XDeleteContext_PROC) (Display *, XID, XContext);
typedef int (* PFN_XDeleteProperty_PROC) (Display *, Window, Atom);
typedef int (* PFN_XDestroyRegion_PROC) (Region);
typedef int (* PFN_XDestroyWindow_PROC) (Display *, Window);
typedef int (* PFN_XDisplayKeycodes_PROC) (Display *, int *, int *);
typedef int (* PFN_XEventsQueued_PROC) (Display *, int);
typedef Status (* PFN_XFetchName_PROC) (Display *, Window, char **);
typedef Bool (* PFN_XFilterEvent_PROC) (XEvent *, Window);
typedef int (* PFN_XFindContext_PROC) (Display *, XID, XContext, XPointer *);
typedef int (* PFN_XFlush_PROC) (Display *);
typedef int (* PFN_XFree_PROC) (void *);
typedef int (* PFN_XFreeColormap_PROC) (Display *, Colormap);
typedef int (* PFN_XFreeCursor_PROC) (Display *, Cursor);
typedef void (* PFN_XFreeEventData_PROC) (Display *, XGenericEventCookie *);
typedef int (* PFN_XGetErrorText_PROC) (Display *, int, char *, int);
typedef Bool (* PFN_XGetEventData_PROC) (Display *, XGenericEventCookie *);
typedef int (* PFN_XGetInputFocus_PROC) (Display *, Window *, int *);
typedef KeySym *(* PFN_XGetKeyboardMapping_PROC) (Display *, KeyCode, int, int *);
typedef Window (* PFN_XGetSelectionOwner_PROC) (Display *, Atom);
typedef XVisualInfo *(* PFN_XGetVisualInfo_PROC) (Display *, long, XVisualInfo *, int *);
typedef Status (* PFN_XGetWMNormalHints_PROC) (Display *, Window, XSizeHints *, long *);
typedef Status (* PFN_XGetWindowAttributes_PROC) (Display *, Window, XWindowAttributes *);
typedef int (* PFN_XGetWindowProperty_PROC) (Display *, Window, Atom, long, long, Bool, Atom, Atom *, int *, unsigned long *, unsigned long *, unsigned char* *);
typedef int (* PFN_XGrabPointer_PROC) (Display *, Window, Bool, unsigned int, int, int, Window, Cursor, Time);
typedef Status (* PFN_XIconifyWindow_PROC) (Display *, Window, int);
typedef Status (* PFN_XInitThreads_PROC) (void);
typedef Atom (* PFN_XInternAtom_PROC) (Display *, const char *, Bool);
typedef int (* PFN_XLookupString_PROC) (XKeyEvent *, char *, int, KeySym *, XComposeStatus *);
typedef int (* PFN_XMapRaised_PROC) (Display *, Window);
typedef int (* PFN_XMapWindow_PROC) (Display *, Window);
typedef int (* PFN_XMoveResizeWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int);
typedef int (* PFN_XMoveWindow_PROC) (Display *, Window, int, int);
typedef int (* PFN_XNextEvent_PROC) (Display *, XEvent *);
typedef Display *(* PFN_XOpenDisplay_PROC) (const char *);
typedef int (* PFN_XPeekEvent_PROC) (Display *, XEvent *);
typedef int (* PFN_XPending_PROC) (Display *);
typedef Bool (* PFN_XQueryExtension_PROC) (Display *, const char *, int *, int *, int *);
typedef Bool (* PFN_XQueryPointer_PROC) (Display *, Window, Window *, Window *, int *, int *, int *, int *, unsigned int *);
typedef int (* PFN_XRaiseWindow_PROC) (Display *, Window);
typedef Bool (* PFN_XRegisterIMInstantiateCallback_PROC) (Display *, void *, char *, char *, XIDProc, XPointer);
typedef int (* PFN_XResizeWindow_PROC) (Display *, Window, unsigned int, unsigned int);
typedef int (* PFN_XSaveContext_PROC) (Display *, XID, XContext, const char *);
typedef int (* PFN_XSelectInput_PROC) (Display *, Window, long);
typedef Status (* PFN_XSendEvent_PROC) (Display *, Window, Bool, long, XEvent *);
typedef int (* PFN_XSetClassHint_PROC) (Display *, Window, XClassHint *);
typedef XErrorHandler (* PFN_XSetErrorHandler_PROC) (XErrorHandler);
typedef int (* PFN_XSetInputFocus_PROC) (Display *, Window, int, Time);
typedef char *(* PFN_XSetLocaleModifiers_PROC) (const char *);
typedef int (* PFN_XSetSelectionOwner_PROC) (Display *, Atom, Window, Time);
typedef int (* PFN_XSetWMHints_PROC) (Display *, Window, XWMHints *);
typedef void (* PFN_XSetWMNormalHints_PROC) (Display *, Window, XSizeHints *);
typedef Status (* PFN_XSetWMProtocols_PROC) (Display *, Window, Atom *, int);
typedef int (* PFN_XStoreName_PROC) (Display *, Window, _Xconst char *);
typedef Bool (* PFN_XSupportsLocale_PROC) (void);
typedef int (* PFN_XSync_PROC) (Display *, Bool);
typedef Bool (* PFN_XTranslateCoordinates_PROC) (Display *, Window, Window, int, int, int *, int *, Window *);
typedef int (* PFN_XUndefineCursor_PROC) (Display *, Window);
typedef int (* PFN_XUngrabPointer_PROC) (Display *, Time);
typedef int (* PFN_XUnmapWindow_PROC) (Display *, Window);
typedef VisualID (* PFN_XVisualIDFromVisual_PROC) (Visual *);
typedef int (* PFN_XWarpPointer_PROC) (Display *, Window, Window, int, int, unsigned int, unsigned int, int, int);
typedef int (* PFN_XWindowEvent_PROC) (Display *, Window, long, XEvent *);
typedef KeySym (* PFN_XkbKeycodeToKeysym_PROC) (Display *, KeyCode, int, int);
typedef Bool (* PFN_XkbSetDetectableAutoRepeat_PROC) (Display *, Bool, Bool *);

#   define XAllocClassHint __window_h.x11->AllocClassHint
#   define XAllocSizeHints __window_h.x11->AllocSizeHints
#   define XAllocWMHints __window_h.x11->AllocWMHints
#   define XChangeProperty __window_h.x11->ChangeProperty
#   define XChangeWindowAttributes __window_h.x11->ChangeWindowAttributes
#   define XCheckIfEvent __window_h.x11->CheckIfEvent
#   define XCheckTypedWindowEvent __window_h.x11->CheckTypedWindowEvent
#   define XCloseDisplay __window_h.x11->CloseDisplay
#   define XConvertSelection __window_h.x11->ConvertSelection
#   define XCreateColormap __window_h.x11->CreateColormap
#   define XCreateFontCursor __window_h.x11->CreateFontCursor
#   define XCreateRegion __window_h.x11->CreateRegion
#   define XCreateWindow __window_h.x11->CreateWindow
#   define XDefineCursor __window_h.x11->DefineCursor
#   define XDeleteContext __window_h.x11->DeleteContext
#   define XDeleteProperty __window_h.x11->DeleteProperty
#   define XDestroyRegion __window_h.x11->DestroyRegion
#   define XDestroyWindow __window_h.x11->DestroyWindow
#   define XDisplayKeycodes __window_h.x11->DisplayKeycodes
#   define XEventsQueued __window_h.x11->EventsQueued
#   define XFetchName __window_h.x11->FetchName
#   define XFilterEvent __window_h.x11->FilterEvent
#   define XFindContext __window_h.x11->FindContext
#   define XFlush __window_h.x11->Flush
#   define XFree __window_h.x11->Free
#   define XFreeColormap __window_h.x11->FreeColormap
#   define XFreeCursor __window_h.x11->FreeCursor
#   define XFreeEventData __window_h.x11->FreeEventData
#   define XGetErrorText __window_h.x11->GetErrorText
#   define XGetEventData __window_h.x11->GetEventData
#   define XGetInputFocus __window_h.x11->GetInputFocus
#   define XGetKeyboardMapping __window_h.x11->GetKeyboardMapping
#   define XGetSelectionOwner __window_h.x11->GetSelectionOwner
#   define XGetVisualInfo __window_h.x11->GetVisualInfo
#   define XGetWMNormalHints __window_h.x11->GetWMNormalHints
#   define XGetWindowAttributes __window_h.x11->GetWindowAttributes
#   define XGetWindowProperty __window_h.x11->GetWindowProperty
#   define XGrabPointer __window_h.x11->GrabPointer
#   define XIconifyWindow __window_h.x11->IconifyWindow
#   define XInitThreads __window_h.x11->InitThreads
#   define XInternAtom __window_h.x11->InternAtom
#   define XLookupString __window_h.x11->LookupString
#   define XMapRaised __window_h.x11->MapRaised
#   define XMapWindow __window_h.x11->MapWindow
#   define XMoveResizeWindow __window_h.x11->MoveResizeWindow
#   define XMoveWindow __window_h.x11->MoveWindow
#   define XNextEvent __window_h.x11->NextEvent
#   define XOpenDisplay __window_h.x11->OpenDisplay
#   define XPeekEvent __window_h.x11->PeekEvent
#   define XPending __window_h.x11->Pending
#   define XQueryExtension __window_h.x11->QueryExtension
#   define XQueryPointer __window_h.x11->QueryPointer
#   define XRaiseWindow __window_h.x11->RaiseWindow
#   define XRegisterIMInstantiateCallback __window_h.x11->RegisterIMInstantiateCallback
#   define XResizeWindow __window_h.x11->ResizeWindow
#   define XSaveContext __window_h.x11->SaveContext
#   define XSelectInput __window_h.x11->SelectInput
#   define XSendEvent __window_h.x11->SendEvent
#   define XSetClassHint __window_h.x11->SetClassHint
#   define XSetErrorHandler __window_h.x11->SetErrorHandler
#   define XSetInputFocus __window_h.x11->SetInputFocus
#   define XSetLocaleModifiers __window_h.x11->SetLocaleModifiers
#   define XSetSelectionOwner __window_h.x11->SetSelectionOwner
#   define XSetWMHints __window_h.x11->SetWMHints
#   define XSetWMNormalHints __window_h.x11->SetWMNormalHints
#   define XSetWMProtocols __window_h.x11->SetWMProtocols
#   define XStoreName __window_h.x11->StoreName
#   define XSupportsLocale __window_h.x11->SupportsLocale
#   define XSync __window_h.x11->Sync
#   define XTranslateCoordinates __window_h.x11->TranslateCoordinates
#   define XUndefineCursor __window_h.x11->UndefineCursor
#   define XUngrabPointer __window_h.x11->UngrabPointer
#   define XUnmapWindow __window_h.x11->UnmapWindow
#   define XVisualIDFromVisual __window_h.x11->VisualIDFromVisual
#   define XWarpPointer __window_h.x11->WarpPointer
#   define XWindowEvent __window_h.x11->WindowEvent
#   define XkbKeycodeToKeysym __window_h.x11->kbKeycodeToKeysym
#   define XkbSetDetectableAutoRepeat __window_h.x11->kbSetDetectableAutoRepeat

typedef struct __window_h_x11 *__window_h_x11;

struct __window_h_x11 {
    struct {
        Display *dpy;
        Window   root;
    } xlib;

    struct {
        /* Atoms: WM */
        Atom wm_protocols;
        Atom wm_delete_window;

        /* Atoms: MOTIF */
        Atom _motif_wm_hints;

        /* Atoms: EWMH */
        Atom _net_wm_state;
        Atom _net_wm_state_above;
        Atom _net_wm_state_fullscreen;
        Atom _net_wm_state_hidden;
        Atom _net_wm_state_maximized_horz;
        Atom _net_wm_state_maximized_vert;
    } xatom;

    /* libX11 */
    void *handle;
    PFN_XAllocClassHint_PROC AllocClassHint;
    PFN_XAllocSizeHints_PROC AllocSizeHints;
    PFN_XAllocWMHints_PROC AllocWMHints;
    PFN_XChangeProperty_PROC ChangeProperty;
    PFN_XChangeWindowAttributes_PROC ChangeWindowAttributes;
    PFN_XCheckIfEvent_PROC CheckIfEvent;
    PFN_XCheckTypedWindowEvent_PROC CheckTypedWindowEvent;
    PFN_XCloseDisplay_PROC CloseDisplay;
    PFN_XConvertSelection_PROC ConvertSelection;
    PFN_XCreateColormap_PROC CreateColormap;
    PFN_XCreateFontCursor_PROC CreateFontCursor;
    PFN_XCreateRegion_PROC CreateRegion;
    PFN_XCreateWindow_PROC CreateWindow;
    PFN_XDefineCursor_PROC DefineCursor;
    PFN_XDeleteContext_PROC DeleteContext;
    PFN_XDeleteProperty_PROC DeleteProperty;
    PFN_XDestroyRegion_PROC DestroyRegion;
    PFN_XDestroyWindow_PROC DestroyWindow;
    PFN_XDisplayKeycodes_PROC DisplayKeycodes;
    PFN_XEventsQueued_PROC EventsQueued;
    PFN_XFetchName_PROC FetchName;
    PFN_XFilterEvent_PROC FilterEvent;
    PFN_XFindContext_PROC FindContext;
    PFN_XFlush_PROC Flush;
    PFN_XFree_PROC Free;
    PFN_XFreeColormap_PROC FreeColormap;
    PFN_XFreeCursor_PROC FreeCursor;
    PFN_XFreeEventData_PROC FreeEventData;
    PFN_XGetErrorText_PROC GetErrorText;
    PFN_XGetEventData_PROC GetEventData;
    PFN_XGetInputFocus_PROC GetInputFocus;
    PFN_XGetKeyboardMapping_PROC GetKeyboardMapping;
    PFN_XGetSelectionOwner_PROC GetSelectionOwner;
    PFN_XGetVisualInfo_PROC GetVisualInfo;
    PFN_XGetWMNormalHints_PROC GetWMNormalHints;
    PFN_XGetWindowAttributes_PROC GetWindowAttributes;
    PFN_XGetWindowProperty_PROC GetWindowProperty;
    PFN_XGrabPointer_PROC GrabPointer;
    PFN_XIconifyWindow_PROC IconifyWindow;
    PFN_XInitThreads_PROC InitThreads;
    PFN_XInternAtom_PROC InternAtom;
    PFN_XLookupString_PROC LookupString;
    PFN_XMapRaised_PROC MapRaised;
    PFN_XMapWindow_PROC MapWindow;
    PFN_XMoveResizeWindow_PROC MoveResizeWindow;
    PFN_XMoveWindow_PROC MoveWindow;
    PFN_XNextEvent_PROC NextEvent;
    PFN_XOpenDisplay_PROC OpenDisplay;
    PFN_XPeekEvent_PROC PeekEvent;
    PFN_XPending_PROC Pending;
    PFN_XQueryExtension_PROC QueryExtension;
    PFN_XQueryPointer_PROC QueryPointer;
    PFN_XRaiseWindow_PROC RaiseWindow;
    PFN_XRegisterIMInstantiateCallback_PROC RegisterIMInstantiateCallback;
    PFN_XResizeWindow_PROC ResizeWindow;
    PFN_XSaveContext_PROC SaveContext;
    PFN_XSelectInput_PROC SelectInput;
    PFN_XSendEvent_PROC SendEvent;
    PFN_XSetClassHint_PROC SetClassHint;
    PFN_XSetErrorHandler_PROC SetErrorHandler;
    PFN_XSetInputFocus_PROC SetInputFocus;
    PFN_XSetLocaleModifiers_PROC SetLocaleModifiers;
    PFN_XSetSelectionOwner_PROC SetSelectionOwner;
    PFN_XSetWMHints_PROC SetWMHints;
    PFN_XSetWMNormalHints_PROC SetWMNormalHints;
    PFN_XSetWMProtocols_PROC SetWMProtocols;
    PFN_XStoreName_PROC StoreName;
    PFN_XSupportsLocale_PROC SupportsLocale;
    PFN_XSync_PROC Sync;
    PFN_XTranslateCoordinates_PROC TranslateCoordinates;
    PFN_XUndefineCursor_PROC UndefineCursor;
    PFN_XUngrabPointer_PROC UngrabPointer;
    PFN_XUnmapWindow_PROC UnmapWindow;
    PFN_XVisualIDFromVisual_PROC VisualIDFromVisual;
    PFN_XWarpPointer_PROC WarpPointer;
    PFN_XWindowEvent_PROC WindowEvent;
    PFN_XkbKeycodeToKeysym_PROC kbKeycodeToKeysym;
    PFN_XkbSetDetectableAutoRepeat_PROC kbSetDetectableAutoRepeat;
};

/* window type definitions */

typedef struct s_window_x11 *t_window_x11;

struct s_window_x11 {
    struct {
        Display *dpy;
        Window   root;
        Window   parent;
        Window   client;
    } xlib;
};

/* internal functions (declarations) */

WININT int __winLoadX11(void);

WININT int __winLoadX11Symbols(void);

WININT int __winUnloadX11(void);

/* internal functions (definitions) */

WININT int __winLoadX11(void) {
    /* alloc '__window_h.x11' field */
    if (!__window_h.x11) {
        __window_h.x11 = calloc(1, sizeof(struct __window_h_x11));
        if (!__window_h.x11) {
            return (0);
        }
    }

    /* try to load libX11 symbols */
    if (!__winLoadX11Symbols()) { return (0); }
    
    /* get '__window_h.x11->xlib' members */
    Display *dpy = XOpenDisplay(0);
    if (!dpy) { return (0); }
    Window root = DefaultRootWindow(dpy);
    if (!root) { return (0); }

    /* set '__window_h.x11->xlib' members */ 
    __window_h.x11->xlib.dpy  = dpy;
    __window_h.x11->xlib.root = root;
    
    /* get '__window_h.x11->xatom' members  */ 
    Atom wm_protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
    if (!wm_protocols) { return (0); }
    
    Atom wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    if (!wm_delete_window) { return (0); }
    
    Atom _motif_wm_hints = XInternAtom(dpy, "_MOTIF_WM_HINTS", False);
    if (!_motif_wm_hints) { return (0); }

    Atom _net_wm_state = XInternAtom(dpy, "_NET_WM_STATE", False);
    if (!_net_wm_state) { return (0); }

    Atom _net_wm_state_above = XInternAtom(dpy, "_NET_WM_STATE_ABOVE", False);
    if (!_net_wm_state_above) { return (0); }

    Atom _net_wm_state_fullscreen = XInternAtom(dpy, "_NET_WM_STATE_FULLSCREEN", False);
    if (!_net_wm_state_fullscreen) { return (0); }

    Atom _net_wm_state_hidden = XInternAtom(dpy, "_NET_WM_STATE_HIDDEN", False);
    if (!_net_wm_state_hidden) { return (0); }

    Atom _net_wm_state_maximized_horz = XInternAtom(dpy, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    if (!_net_wm_state_maximized_horz) { return (0); }

    Atom _net_wm_state_maximized_vert = XInternAtom(dpy, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    if (!_net_wm_state_maximized_vert) { return (0); }

    /* set '__window_h.x11->xatom' members */ 
    __window_h.x11->xatom.wm_protocols = wm_protocols;
    __window_h.x11->xatom.wm_delete_window = wm_delete_window;
    __window_h.x11->xatom._motif_wm_hints = _motif_wm_hints;
    __window_h.x11->xatom._net_wm_state = _net_wm_state;
    __window_h.x11->xatom._net_wm_state_above = _net_wm_state_above;
    __window_h.x11->xatom._net_wm_state_fullscreen = _net_wm_state_fullscreen;
    __window_h.x11->xatom._net_wm_state_hidden = _net_wm_state_hidden;
    __window_h.x11->xatom._net_wm_state_maximized_horz = _net_wm_state_maximized_horz;
    __window_h.x11->xatom._net_wm_state_maximized_vert = _net_wm_state_maximized_vert;

    /* success */
    return (1);
}


WININT int __winLoadX11Symbols(void) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* try to load handle */
    const char  *names[] = { "libX11.so", "libX11.so.6", 0 };
    static void *handle  = 0;
    if (!handle) {
        for (const char **name = names; *name; name++) {
            handle = dlopen(*name, RTLD_NOW | RTLD_GLOBAL);
            if (handle) { break; }
        }

        /* check if handle loaded */
        if (!handle) { return (0); }
    }

    /* load libX11 symbols */
    XAllocClassHint = (PFN_XAllocClassHint_PROC) dlsym(handle, "XAllocClassHint");
    if (!XAllocClassHint) { return (0); }

    XAllocSizeHints = (PFN_XAllocSizeHints_PROC) dlsym(handle, "XAllocSizeHints");
    if (!XAllocSizeHints) { return (0); }

    XAllocWMHints = (PFN_XAllocWMHints_PROC) dlsym(handle, "XAllocWMHints");
    if (!XAllocWMHints) { return (0); }

    XChangeProperty = (PFN_XChangeProperty_PROC) dlsym(handle, "XChangeProperty");
    if (!XChangeProperty) { return (0); }

    XChangeWindowAttributes = (PFN_XChangeWindowAttributes_PROC) dlsym(handle, "XChangeWindowAttributes");
    if (!XChangeWindowAttributes) { return (0); }

    XCheckIfEvent = (PFN_XCheckIfEvent_PROC) dlsym(handle, "XCheckIfEvent");
    if (!XCheckIfEvent) { return (0); }

    XCheckTypedWindowEvent = (PFN_XCheckTypedWindowEvent_PROC) dlsym(handle, "XCheckTypedWindowEvent");
    if (!XCheckTypedWindowEvent) { return (0); }

    XCloseDisplay = (PFN_XCloseDisplay_PROC) dlsym(handle, "XCloseDisplay");
    if (!XCloseDisplay) { return (0); }

    XConvertSelection = (PFN_XConvertSelection_PROC) dlsym(handle, "XConvertSelection");
    if (!XConvertSelection) { return (0); }

    XCreateColormap = (PFN_XCreateColormap_PROC) dlsym(handle, "XCreateColormap");
    if (!XCreateColormap) { return (0); }

    XCreateFontCursor = (PFN_XCreateFontCursor_PROC) dlsym(handle, "XCreateFontCursor");
    if (!XCreateFontCursor) { return (0); }

    XCreateRegion = (PFN_XCreateRegion_PROC) dlsym(handle, "XCreateRegion");
    if (!XCreateRegion) { return (0); }

    XCreateWindow = (PFN_XCreateWindow_PROC) dlsym(handle, "XCreateWindow");
    if (!XCreateWindow) { return (0); }

    XDefineCursor = (PFN_XDefineCursor_PROC) dlsym(handle, "XDefineCursor");
    if (!XDefineCursor) { return (0); }

    XDeleteContext = (PFN_XDeleteContext_PROC) dlsym(handle, "XDeleteContext");
    if (!XDeleteContext) { return (0); }

    XDeleteProperty = (PFN_XDeleteProperty_PROC) dlsym(handle, "XDeleteProperty");
    if (!XDeleteProperty) { return (0); }

    XDestroyRegion = (PFN_XDestroyRegion_PROC) dlsym(handle, "XDestroyRegion");
    if (!XDestroyRegion) { return (0); }

    XDestroyWindow = (PFN_XDestroyWindow_PROC) dlsym(handle, "XDestroyWindow");
    if (!XDestroyWindow) { return (0); }

    XDisplayKeycodes = (PFN_XDisplayKeycodes_PROC) dlsym(handle, "XDisplayKeycodes");
    if (!XDisplayKeycodes) { return (0); }

    XEventsQueued = (PFN_XEventsQueued_PROC) dlsym(handle, "XEventsQueued");
    if (!XEventsQueued) { return (0); }

    XFetchName = (PFN_XFetchName_PROC) dlsym(handle, "XFetchName");
    if (!XFetchName) { return (0); }

    XFilterEvent = (PFN_XFilterEvent_PROC) dlsym(handle, "XFilterEvent");
    if (!XFilterEvent) { return (0); }

    XFindContext = (PFN_XFindContext_PROC) dlsym(handle, "XFindContext");
    if (!XFindContext) { return (0); }

    XFlush = (PFN_XFlush_PROC) dlsym(handle, "XFlush");
    if (!XFlush) { return (0); }

    XFree = (PFN_XFree_PROC) dlsym(handle, "XFree");
    if (!XFree) { return (0); }

    XFreeColormap = (PFN_XFreeColormap_PROC) dlsym(handle, "XFreeColormap");
    if (!XFreeColormap) { return (0); }

    XFreeCursor = (PFN_XFreeCursor_PROC) dlsym(handle, "XFreeCursor");
    if (!XFreeCursor) { return (0); }

    XFreeEventData = (PFN_XFreeEventData_PROC) dlsym(handle, "XFreeEventData");
    if (!XFreeEventData) { return (0); }

    XGetErrorText = (PFN_XGetErrorText_PROC) dlsym(handle, "XGetErrorText");
    if (!XGetErrorText) { return (0); }

    XGetEventData = (PFN_XGetEventData_PROC) dlsym(handle, "XGetEventData");
    if (!XGetEventData) { return (0); }

    XGetInputFocus = (PFN_XGetInputFocus_PROC) dlsym(handle, "XGetInputFocus");
    if (!XGetInputFocus) { return (0); }

    XGetKeyboardMapping = (PFN_XGetKeyboardMapping_PROC) dlsym(handle, "XGetKeyboardMapping");
    if (!XGetKeyboardMapping) { return (0); }

    XGetSelectionOwner = (PFN_XGetSelectionOwner_PROC) dlsym(handle, "XGetSelectionOwner");
    if (!XGetSelectionOwner) { return (0); }

    XGetVisualInfo = (PFN_XGetVisualInfo_PROC) dlsym(handle, "XGetVisualInfo");
    if (!XGetVisualInfo) { return (0); }

    XGetWMNormalHints = (PFN_XGetWMNormalHints_PROC) dlsym(handle, "XGetWMNormalHints");
    if (!XGetWMNormalHints) { return (0); }

    XGetWindowAttributes = (PFN_XGetWindowAttributes_PROC) dlsym(handle, "XGetWindowAttributes");
    if (!XGetWindowAttributes) { return (0); }

    XGetWindowProperty = (PFN_XGetWindowProperty_PROC) dlsym(handle, "XGetWindowProperty");
    if (!XGetWindowProperty) { return (0); }

    XGrabPointer = (PFN_XGrabPointer_PROC) dlsym(handle, "XGrabPointer");
    if (!XGrabPointer) { return (0); }

    XIconifyWindow = (PFN_XIconifyWindow_PROC) dlsym(handle, "XIconifyWindow");
    if (!XIconifyWindow) { return (0); }

    XInitThreads = (PFN_XInitThreads_PROC) dlsym(handle, "XInitThreads");
    if (!XInitThreads) { return (0); }

    XInternAtom = (PFN_XInternAtom_PROC) dlsym(handle, "XInternAtom");
    if (!XInternAtom) { return (0); }

    XLookupString = (PFN_XLookupString_PROC) dlsym(handle, "XLookupString");
    if (!XLookupString) { return (0); }

    XMapRaised = (PFN_XMapRaised_PROC) dlsym(handle, "XMapRaised");
    if (!XMapRaised) { return (0); }

    XMapWindow = (PFN_XMapWindow_PROC) dlsym(handle, "XMapWindow");
    if (!XMapWindow) { return (0); }

    XMoveResizeWindow = (PFN_XMoveResizeWindow_PROC) dlsym(handle, "XMoveResizeWindow");
    if (!XMoveResizeWindow) { return (0); }

    XMoveWindow = (PFN_XMoveWindow_PROC) dlsym(handle, "XMoveWindow");
    if (!XMoveWindow) { return (0); }

    XNextEvent = (PFN_XNextEvent_PROC) dlsym(handle, "XNextEvent");
    if (!XNextEvent) { return (0); }

    XOpenDisplay = (PFN_XOpenDisplay_PROC) dlsym(handle, "XOpenDisplay");
    if (!XOpenDisplay) { return (0); }

    XPeekEvent = (PFN_XPeekEvent_PROC) dlsym(handle, "XPeekEvent");
    if (!XPeekEvent) { return (0); }

    XPending = (PFN_XPending_PROC) dlsym(handle, "XPending");
    if (!XPending) { return (0); }

    XQueryExtension = (PFN_XQueryExtension_PROC) dlsym(handle, "XQueryExtension");
    if (!XQueryExtension) { return (0); }

    XQueryPointer = (PFN_XQueryPointer_PROC) dlsym(handle, "XQueryPointer");
    if (!XQueryPointer) { return (0); }

    XRaiseWindow = (PFN_XRaiseWindow_PROC) dlsym(handle, "XRaiseWindow");
    if (!XRaiseWindow) { return (0); }

    XRegisterIMInstantiateCallback = (PFN_XRegisterIMInstantiateCallback_PROC) dlsym(handle, "XRegisterIMInstantiateCallback");
    if (!XRegisterIMInstantiateCallback) { return (0); }

    XResizeWindow = (PFN_XResizeWindow_PROC) dlsym(handle, "XResizeWindow");
    if (!XResizeWindow) { return (0); }

    XSaveContext = (PFN_XSaveContext_PROC) dlsym(handle, "XSaveContext");
    if (!XSaveContext) { return (0); }

    XSelectInput = (PFN_XSelectInput_PROC) dlsym(handle, "XSelectInput");
    if (!XSelectInput) { return (0); }

    XSendEvent = (PFN_XSendEvent_PROC) dlsym(handle, "XSendEvent");
    if (!XSendEvent) { return (0); }

    XSetClassHint = (PFN_XSetClassHint_PROC) dlsym(handle, "XSetClassHint");
    if (!XSetClassHint) { return (0); }

    XSetErrorHandler = (PFN_XSetErrorHandler_PROC) dlsym(handle, "XSetErrorHandler");
    if (!XSetErrorHandler) { return (0); }

    XSetInputFocus = (PFN_XSetInputFocus_PROC) dlsym(handle, "XSetInputFocus");
    if (!XSetInputFocus) { return (0); }

    XSetLocaleModifiers = (PFN_XSetLocaleModifiers_PROC) dlsym(handle, "XSetLocaleModifiers");
    if (!XSetLocaleModifiers) { return (0); }

    XSetSelectionOwner = (PFN_XSetSelectionOwner_PROC) dlsym(handle, "XSetSelectionOwner");
    if (!XSetSelectionOwner) { return (0); }

    XSetWMHints = (PFN_XSetWMHints_PROC) dlsym(handle, "XSetWMHints");
    if (!XSetWMHints) { return (0); }

    XSetWMNormalHints = (PFN_XSetWMNormalHints_PROC) dlsym(handle, "XSetWMNormalHints");
    if (!XSetWMNormalHints) { return (0); }

    XSetWMProtocols = (PFN_XSetWMProtocols_PROC) dlsym(handle, "XSetWMProtocols");
    if (!XSetWMProtocols) { return (0); }

    XStoreName = (PFN_XStoreName_PROC) dlsym(handle, "XStoreName");
    if (!XStoreName) { return (0); }

    XSupportsLocale = (PFN_XSupportsLocale_PROC) dlsym(handle, "XSupportsLocale");
    if (!XSupportsLocale) { return (0); }

    XSync = (PFN_XSync_PROC) dlsym(handle, "XSync");
    if (!XSync) { return (0); }

    XTranslateCoordinates = (PFN_XTranslateCoordinates_PROC) dlsym(handle, "XTranslateCoordinates");
    if (!XTranslateCoordinates) { return (0); }

    XUndefineCursor = (PFN_XUndefineCursor_PROC) dlsym(handle, "XUndefineCursor");
    if (!XUndefineCursor) { return (0); }

    XUngrabPointer = (PFN_XUngrabPointer_PROC) dlsym(handle, "XUngrabPointer");
    if (!XUngrabPointer) { return (0); }

    XUnmapWindow = (PFN_XUnmapWindow_PROC) dlsym(handle, "XUnmapWindow");
    if (!XUnmapWindow) { return (0); }

    XVisualIDFromVisual = (PFN_XVisualIDFromVisual_PROC) dlsym(handle, "XVisualIDFromVisual");
    if (!XVisualIDFromVisual) { return (0); }

    XWarpPointer = (PFN_XWarpPointer_PROC) dlsym(handle, "XWarpPointer");
    if (!XWarpPointer) { return (0); }

    XWindowEvent = (PFN_XWindowEvent_PROC) dlsym(handle, "XWindowEvent");
    if (!XWindowEvent) { return (0); }

    XkbKeycodeToKeysym = (PFN_XkbKeycodeToKeysym_PROC) dlsym(handle, "XkbKeycodeToKeysym");
    if (!XkbKeycodeToKeysym) { return (0); }

    XkbSetDetectableAutoRepeat = (PFN_XkbSetDetectableAutoRepeat_PROC) dlsym(handle, "XkbSetDetectableAutoRepeat");
    if (!XkbSetDetectableAutoRepeat) { return (0); }

    /* set '__window_h.x11->handle' member */ 
    __window_h.x11->handle = handle;

    /* success */
    return (1);
}


WININT int __winUnloadX11(void) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* release '__window_h.x11->handle' field */
    dlclose(__window_h.x11->handle), __window_h.x11->handle = 0;

    /* release '__window_h.x11' */
    free(__window_h.x11);

    /* success */
    return (1);
}

#  endif /* WINDOW_BACKEND_X11 */
#
#  /* WINDOW_BACKEND_WAYLAND - Unix Wayland implementation layer */
#  if defined (WINDOW_BACKEND_WAYLAND)
#   include <unistd.h>
#   include <sys/time.h>
#
#   include <wayland-util.h>
#   include <wayland-version.h>
#   include <wayland-client.h>
#   include <wayland-client-core.h>
#   include <wayland-client-protocol.h>

/* ... */

#  endif /* WINDOW_BACKEND_WAYLAND */
#
#  /* WINDOW_PLATFORM_WIN32 - Windows Win32 implementation layer */
#  if defined (WINDOW_PLATFORM_WIN32)
#   include <windows.h>

/* ... */

#  endif /* WINDOW_PLATFORM_WIN32 */
#
#  /* WINDOW_BACKEND_GL_EGL - EGL implementation layer */
#  if defined (WINDOW_BACKEND_GL_EGL)

typedef Display *EGLNativeDisplayType;
typedef Pixmap   EGLNativePixmapType;
typedef Window   EGLNativeWindowType;

typedef EGLNativeDisplayType NativeDisplayType;
typedef EGLNativePixmapType  NativePixmapType;
typedef EGLNativeWindowType  NativeWindowType;

typedef int32_t EGLint;

#   if !defined (EGL_VERSION_1_0)
#    define EGL_VERSION_1_0 1
#
#    define EGL_ALPHA_SIZE 0x3021
#    define EGL_BAD_ACCESS 0x3002
#    define EGL_BAD_ALLOC 0x3003
#    define EGL_BAD_ATTRIBUTE 0x3004
#    define EGL_BAD_CONFIG 0x3005
#    define EGL_BAD_CONTEXT 0x3006
#    define EGL_BAD_CURRENT_SURFACE 0x3007
#    define EGL_BAD_DISPLAY 0x3008
#    define EGL_BAD_MATCH 0x3009
#    define EGL_BAD_NATIVE_PIXMAP 0x300A
#    define EGL_BAD_NATIVE_WINDOW 0x300B
#    define EGL_BAD_PARAMETER 0x300C
#    define EGL_BAD_SURFACE 0x300D
#    define EGL_BLUE_SIZE 0x3022
#    define EGL_BUFFER_SIZE 0x3020
#    define EGL_CONFIG_CAVEAT 0x3027
#    define EGL_CONFIG_ID 0x3028
#    define EGL_CORE_NATIVE_ENGINE 0x305B
#    define EGL_DEPTH_SIZE 0x3025
#    define EGL_DONT_CARE ((EGLint) -1)
#    define EGL_DRAW 0x3059
#    define EGL_EXTENSIONS 0x3055
#    define EGL_FALSE 0
#    define EGL_GREEN_SIZE 0x3023
#    define EGL_HEIGHT 0x3056
#    define EGL_LARGEST_PBUFFER 0x3058
#    define EGL_LEVEL 0x3029
#    define EGL_MAX_PBUFFER_HEIGHT 0x302A
#    define EGL_MAX_PBUFFER_PIXELS 0x302B
#    define EGL_MAX_PBUFFER_WIDTH 0x302C
#    define EGL_NATIVE_RENDERABLE 0x302D
#    define EGL_NATIVE_VISUAL_ID 0x302E
#    define EGL_NATIVE_VISUAL_TYPE 0x302F
#    define EGL_NONE 0x3038
#    define EGL_NON_CONFORMANT_CONFIG 0x3051
#    define EGL_NOT_INITIALIZED 0x3001
#    define EGL_NO_CONTEXT ((EGLContext) 0)
#    define EGL_NO_DISPLAY ((EGLDisplay) 0)
#    define EGL_NO_SURFACE ((EGLSurface) 0)
#    define EGL_PBUFFER_BIT 0x0001
#    define EGL_PIXMAP_BIT 0x0002
#    define EGL_READ 0x305A
#    define EGL_RED_SIZE 0x3024
#    define EGL_SAMPLES 0x3031
#    define EGL_SAMPLE_BUFFERS 0x3032
#    define EGL_SLOW_CONFIG 0x3050
#    define EGL_STENCIL_SIZE 0x3026
#    define EGL_SUCCESS 0x3000
#    define EGL_SURFACE_TYPE 0x3033
#    define EGL_TRANSPARENT_BLUE_VALUE 0x3035
#    define EGL_TRANSPARENT_GREEN_VALUE 0x3036
#    define EGL_TRANSPARENT_RED_VALUE 0x3037
#    define EGL_TRANSPARENT_RGB 0x3052
#    define EGL_TRANSPARENT_TYPE 0x3034
#    define EGL_TRUE 1
#    define EGL_VENDOR 0x3053
#    define EGL_VERSION 0x3054
#    define EGL_WIDTH 0x3057
#    define EGL_WINDOW_BIT 0x0004

typedef unsigned int EGLBoolean;
typedef void *EGLDisplay;
typedef void *EGLConfig;
typedef void *EGLSurface;
typedef void *EGLContext;
typedef void (*__eglMustCastToProperFunctionPointerType)(void);

typedef EGLBoolean (* PFN_eglChooseConfig_PROC) (EGLDisplay, const EGLint *, EGLConfig *, EGLint, EGLint *);
typedef EGLBoolean (* PFN_eglCopyBuffers_PROC) (EGLDisplay, EGLSurface, EGLNativePixmapType);
typedef EGLContext (* PFN_eglCreateContext_PROC) (EGLDisplay, EGLConfig, EGLContext, const EGLint *);
typedef EGLSurface (* PFN_eglCreatePbufferSurface_PROC) (EGLDisplay, EGLConfig, const EGLint *);
typedef EGLSurface (* PFN_eglCreatePixmapSurface_PROC) (EGLDisplay, EGLConfig, EGLNativePixmapType, const EGLint *);
typedef EGLSurface (* PFN_eglCreateWindowSurface_PROC) (EGLDisplay, EGLConfig, EGLNativeWindowType, const EGLint *);
typedef EGLBoolean (* PFN_eglDestroyContext_PROC) (EGLDisplay, EGLContext);
typedef EGLBoolean (* PFN_eglDestroySurface_PROC) (EGLDisplay, EGLSurface);
typedef EGLBoolean (* PFN_eglGetConfigAttrib_PROC) (EGLDisplay, EGLConfig, EGLint, EGLint *);
typedef EGLBoolean (* PFN_eglGetConfigs_PROC) (EGLDisplay, EGLConfig *configs, EGLint, EGLint *);
typedef EGLDisplay (* PFN_eglGetCurrentDisplay_PROC) (void);
typedef EGLSurface (* PFN_eglGetCurrentSurface_PROC) (EGLint);
typedef EGLDisplay (* PFN_eglGetDisplay_PROC) (EGLNativeDisplayType);
typedef EGLint (* PFN_eglGetError_PROC) (void);
typedef __eglMustCastToProperFunctionPointerType (* PFN_eglGetProcAddress_PROC) (const char *);
typedef EGLBoolean (* PFN_eglInitialize_PROC) (EGLDisplay, EGLint *, EGLint *);
typedef EGLBoolean (* PFN_eglMakeCurrent_PROC) (EGLDisplay, EGLSurface, EGLSurface, EGLContext);
typedef EGLBoolean (* PFN_eglQueryContext_PROC) (EGLDisplay, EGLContext, EGLint, EGLint *);
typedef const char *(* PFN_eglQueryString_PROC) (EGLDisplay, EGLint);
typedef EGLBoolean (* PFN_eglQuerySurface_PROC) (EGLDisplay, EGLSurface, EGLint, EGLint *);
typedef EGLBoolean (* PFN_eglSwapBuffers_PROC) (EGLDisplay, EGLSurface);
typedef EGLBoolean (* PFN_eglTerminate_PROC) (EGLDisplay);
typedef EGLBoolean (* PFN_eglWaitGL_PROC) (void);
typedef EGLBoolean (* PFN_eglWaitNative_PROC) (EGLint);

#    define eglChooseConfig __window_h.egl->ChooseConfig
#    define eglCopyBuffers __window_h.egl->CopyBuffers
#    define eglCreateContext __window_h.egl->CreateContext
#    define eglCreatePbufferSurface __window_h.egl->CreatePbufferSurface
#    define eglCreatePixmapSurface __window_h.egl->CreatePixmapSurface
#    define eglCreateWindowSurface __window_h.egl->CreateWindowSurface
#    define eglDestroyContext __window_h.egl->DestroyContext
#    define eglDestroySurface __window_h.egl->DestroySurface
#    define eglGetConfigAttrib __window_h.egl->GetConfigAttrib
#    define eglGetConfigs __window_h.egl->GetConfigs
#    define eglGetCurrentDisplay __window_h.egl->GetCurrentDisplay
#    define eglGetCurrentSurface __window_h.egl->GetCurrentSurface
#    define eglGetDisplay __window_h.egl->GetDisplay
#    define eglGetError __window_h.egl->GetError
#    define eglGetProcAddress __window_h.egl->GetProcAddress
#    define eglInitialize __window_h.egl->Initialize
#    define eglMakeCurrent __window_h.egl->MakeCurrent
#    define eglQueryContext __window_h.egl->QueryContext
#    define eglQueryString __window_h.egl->QueryString
#    define eglQuerySurface __window_h.egl->QuerySurface
#    define eglSwapBuffers __window_h.egl->SwapBuffers
#    define eglTerminate __window_h.egl->Terminate
#    define eglWaitGL __window_h.egl->WaitGL
#    define eglWaitNative __window_h.egl->WaitNative
#
#   endif /* EGL_VERSION_1_0 */
#
#   if !defined (EGL_VERSION_1_1)
#    define EGL_VERSION_1_1 1
#
#    define EGL_BACK_BUFFER 0x3084
#    define EGL_BIND_TO_TEXTURE_RGB 0x3039
#    define EGL_BIND_TO_TEXTURE_RGBA 0x303A
#    define EGL_CONTEXT_LOST 0x300E
#    define EGL_MIN_SWAP_INTERVAL 0x303B
#    define EGL_MAX_SWAP_INTERVAL 0x303C
#    define EGL_MIPMAP_TEXTURE 0x3082
#    define EGL_MIPMAP_LEVEL 0x3083
#    define EGL_NO_TEXTURE 0x305C
#    define EGL_TEXTURE_2D 0x305F
#    define EGL_TEXTURE_FORMAT 0x3080
#    define EGL_TEXTURE_RGB 0x305D
#    define EGL_TEXTURE_RGBA 0x305E
#    define EGL_TEXTURE_TARGET 0x3081

typedef EGLBoolean (* PFN_eglBindTexImage_PROC) (EGLDisplay, EGLSurface, EGLint);
typedef EGLBoolean (* PFN_eglReleaseTexImage_PROC) (EGLDisplay, EGLSurface, EGLint);
typedef EGLBoolean (* PFN_eglSurfaceAttrib_PROC) (EGLDisplay, EGLSurface, EGLint, EGLint);
typedef EGLBoolean (* PFN_eglSwapInterval_PROC) (EGLDisplay, EGLint);

#    define eglBindTexImage __window_h.egl->BindTexImage
#    define eglReleaseTexImage __window_h.egl->ReleaseTexImage
#    define eglSurfaceAttrib __window_h.egl->SurfaceAttrib
#    define eglSwapInterval __window_h.egl->SwapInterval
#
#   endif /* EGL_VERSION_1_1 */
#
#   if !defined (EGL_VERSION_1_2)
#    define EGL_VERSION_1_2 1
#
#    define EGL_ALPHA_FORMAT 0x3088
#    define EGL_ALPHA_FORMAT_NONPRE 0x308B
#    define EGL_ALPHA_FORMAT_PRE 0x308C
#    define EGL_ALPHA_MASK_SIZE 0x303E
#    define EGL_BUFFER_PRESERVED 0x3094
#    define EGL_BUFFER_DESTROYED 0x3095
#    define EGL_CLIENT_APIS 0x308D
#    define EGL_COLORSPACE 0x3087
#    define EGL_COLORSPACE_sRGB 0x3089
#    define EGL_COLORSPACE_LINEAR 0x308A
#    define EGL_COLOR_BUFFER_TYPE 0x303F
#    define EGL_CONTEXT_CLIENT_TYPE 0x3097
#    define EGL_DISPLAY_SCALING 10000
#    define EGL_HORIZONTAL_RESOLUTION 0x3090
#    define EGL_LUMINANCE_BUFFER 0x308F
#    define EGL_LUMINANCE_SIZE 0x303D
#    define EGL_OPENGL_ES_BIT 0x0001
#    define EGL_OPENVG_BIT 0x0002
#    define EGL_OPENGL_ES_API 0x30A0
#    define EGL_OPENVG_API 0x30A1
#    define EGL_OPENVG_IMAGE 0x3096
#    define EGL_PIXEL_ASPECT_RATIO 0x3092
#    define EGL_RENDERABLE_TYPE 0x3040
#    define EGL_RENDER_BUFFER 0x3086
#    define EGL_RGB_BUFFER 0x308E
#    define EGL_SINGLE_BUFFER 0x3085
#    define EGL_SWAP_BEHAVIOR 0x3093
#    define EGL_UNKNOWN ((EGLint) -1)
#    define EGL_VERTICAL_RESOLUTION 0x3091

typedef unsigned int EGLenum;
typedef void *EGLClientBuffer;

typedef EGLBoolean (* PFN_eglBindAPI_PROC) (EGLenum);
typedef EGLenum (* PFN_eglQueryAPI_PROC) (void);
typedef EGLSurface (* PFN_eglCreatePbufferFromClientBuffer_PROC) (EGLDisplay, EGLenum, EGLClientBuffer, EGLConfig, const EGLint *);
typedef EGLBoolean (* PFN_eglReleaseThread_PROC) (void);
typedef EGLBoolean (* PFN_eglWaitClient_PROC) (void);

#    define eglBindAPI __window_h.egl->BindAPI
#    define eglQueryAPI __window_h.egl->QueryAPI
#    define eglCreatePbufferFromClientBuffer __window_h.egl->CreatePbufferFromClientBuffer
#    define eglReleaseThread __window_h.egl->ReleaseThread
#    define eglWaitClient __window_h.egl->WaitClient
#
#   endif /* EGL_VERSION_1_2 */
#
#   if !defined (EGL_VERSION_1_3)
#    define EGL_VERSION_1_3 1
#
#    define EGL_CONFORMANT 0x3042
#    define EGL_CONTEXT_CLIENT_VERSION 0x3098
#    define EGL_MATCH_NATIVE_PIXMAP 0x3041
#    define EGL_OPENGL_ES2_BIT 0x0004
#    define EGL_VG_ALPHA_FORMAT 0x3088
#    define EGL_VG_ALPHA_FORMAT_NONPRE 0x308B
#    define EGL_VG_ALPHA_FORMAT_PRE 0x308C
#    define EGL_VG_ALPHA_FORMAT_PRE_BIT 0x0040
#    define EGL_VG_COLORSPACE 0x3087
#    define EGL_VG_COLORSPACE_sRGB 0x3089
#    define EGL_VG_COLORSPACE_LINEAR 0x308A
#    define EGL_VG_COLORSPACE_LINEAR_BIT 0x0020
#
#   endif /* EGL_VERSION_1_3 */
#
#   if !defined (EGL_VERSION_1_4)
#    define EGL_VERSION_1_4 1
#
#    define EGL_DEFAULT_DISPLAY ((EGLNativeDisplayType) 0)
#    define EGL_MULTISAMPLE_RESOLVE_BOX_BIT 0x0200
#    define EGL_MULTISAMPLE_RESOLVE 0x3099
#    define EGL_MULTISAMPLE_RESOLVE_DEFAULT 0x309A
#    define EGL_MULTISAMPLE_RESOLVE_BOX 0x309B
#    define EGL_OPENGL_API 0x30A2
#    define EGL_OPENGL_BIT 0x0008
#    define EGL_SWAP_BEHAVIOR_PRESERVED_BIT 0x0400

typedef EGLContext (* PFN_eglGetCurrentContext_PROC) (void);

#    define eglGetCurrentContext __window_h.egl->GetCurrentContext
#
#   endif /* EGL_VERSION_1_4 */
#
#   if !defined (EGL_VERSION_1_5)
#    define EGL_VERSION_1_5 1
#
#    define EGL_CONTEXT_MAJOR_VERSION 0x3098
#    define EGL_CONTEXT_MINOR_VERSION 0x30FB
#    define EGL_CONTEXT_OPENGL_PROFILE_MASK 0x30FD
#    define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#    define EGL_NO_RESET_NOTIFICATION 0x31BE
#    define EGL_LOSE_CONTEXT_ON_RESET 0x31BF
#    define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#    define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#    define EGL_CONTEXT_OPENGL_DEBUG 0x31B0
#    define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#    define EGL_CONTEXT_OPENGL_ROBUST_ACCESS 0x31B2
#    define EGL_OPENGL_ES3_BIT 0x00000040
#    define EGL_CL_EVENT_HANDLE 0x309C
#    define EGL_SYNC_CL_EVENT 0x30FE
#    define EGL_SYNC_CL_EVENT_COMPLETE 0x30FF
#    define EGL_SYNC_PRIOR_COMMANDS_COMPLETE 0x30F0
#    define EGL_SYNC_TYPE 0x30F7
#    define EGL_SYNC_STATUS 0x30F1
#    define EGL_SYNC_CONDITION 0x30F8
#    define EGL_SIGNALED 0x30F2
#    define EGL_UNSIGNALED 0x30F3
#    define EGL_SYNC_FLUSH_COMMANDS_BIT 0x0001
#    define EGL_FOREVER 0xFFFFFFFFFFFFFFFFull
#    define EGL_TIMEOUT_EXPIRED 0x30F5
#    define EGL_CONDITION_SATISFIED 0x30F6
#    define EGL_NO_SYNC ((EGLSync) 0)
#    define EGL_SYNC_FENCE 0x30F9
#    define EGL_GL_COLORSPACE 0x309D
#    define EGL_GL_COLORSPACE_SRGB 0x3089
#    define EGL_GL_COLORSPACE_LINEAR 0x308A
#    define EGL_GL_RENDERBUFFER 0x30B9
#    define EGL_GL_TEXTURE_2D 0x30B1
#    define EGL_GL_TEXTURE_LEVEL 0x30BC
#    define EGL_GL_TEXTURE_3D 0x30B2
#    define EGL_GL_TEXTURE_ZOFFSET 0x30BD
#    define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x30B3
#    define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#    define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x30B5
#    define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#    define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x30B7
#    define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#    define EGL_IMAGE_PRESERVED 0x30D2
#    define EGL_NO_IMAGE ((EGLImage) 0)

typedef void *EGLSync;
typedef intptr_t EGLAttrib;
typedef khronos_utime_nanoseconds_t EGLTime;
typedef void *EGLImage;

typedef EGLSync (* PFN_eglCreateSync_PROC) (EGLDisplay, EGLenum, const EGLAttrib *);
typedef EGLBoolean (* PFN_eglDestroySync_PROC) (EGLDisplay, EGLSync);
typedef EGLint (* PFN_eglClientWaitSync_PROC) (EGLDisplay, EGLSync, EGLint, EGLTime);
typedef EGLBoolean (* PFN_eglGetSyncAttrib_PROC) (EGLDisplay, EGLSync, EGLint, EGLAttrib *);
typedef EGLImage (* PFN_eglCreateImage_PROC) (EGLDisplay, EGLContext, EGLenum, EGLClientBuffer, const EGLAttrib *);
typedef EGLBoolean (* PFN_eglDestroyImage_PROC) (EGLDisplay, EGLImage);
typedef EGLDisplay (* PFN_eglGetPlatformDisplay_PROC) (EGLenum, void *, const EGLAttrib *);
typedef EGLSurface (* PFN_eglCreatePlatformWindowSurface_PROC) (EGLDisplay, EGLConfig, void *, const EGLAttrib *);
typedef EGLSurface (* PFN_eglCreatePlatformPixmapSurface_PROC) (EGLDisplay, EGLConfig, void *, const EGLAttrib *);
typedef EGLBoolean (* PFN_eglWaitSync_PROC) (EGLDisplay, EGLSync, EGLint);

#    define eglCreateSync __window_h.egl->CreateSync
#    define eglDestroySync __window_h.egl->DestroySync
#    define eglClientWaitSync __window_h.egl->ClientWaitSync
#    define eglGetSyncAttrib __window_h.egl->GetSyncAttrib
#    define eglCreateImage __window_h.egl->CreateImage
#    define eglDestroyImage __window_h.egl->DestroyImage
#    define eglGetPlatformDisplay __window_h.egl->GetPlatformDisplay
#    define eglCreatePlatformWindowSurface __window_h.egl->CreatePlatformWindowSurface
#    define eglCreatePlatformPixmapSurface __window_h.egl->CreatePlatformPixmapSurface
#    define eglWaitSync __window_h.egl->WaitSync
#
#   endif /* EGL_VERSION_1_5 */

typedef struct __window_h_egl *__window_h_egl;

struct __window_h_egl {
    EGLDisplay dpy;

    struct {
        int surface[16];
        int context[32];
        int  config[64];
    } attr;

    /* libEGL */
    void *handle;
    PFN_eglChooseConfig_PROC ChooseConfig;
    PFN_eglCopyBuffers_PROC CopyBuffers;
    PFN_eglCreateContext_PROC CreateContext;
    PFN_eglCreatePbufferSurface_PROC CreatePbufferSurface;
    PFN_eglCreatePixmapSurface_PROC CreatePixmapSurface;
    PFN_eglCreateWindowSurface_PROC CreateWindowSurface;
    PFN_eglDestroyContext_PROC DestroyContext;
    PFN_eglDestroySurface_PROC DestroySurface;
    PFN_eglGetConfigAttrib_PROC GetConfigAttrib;
    PFN_eglGetConfigs_PROC GetConfigs;
    PFN_eglGetCurrentDisplay_PROC GetCurrentDisplay;
    PFN_eglGetCurrentSurface_PROC GetCurrentSurface;
    PFN_eglGetDisplay_PROC GetDisplay;
    PFN_eglGetError_PROC GetError;
    PFN_eglGetProcAddress_PROC GetProcAddress;
    PFN_eglInitialize_PROC Initialize;
    PFN_eglMakeCurrent_PROC MakeCurrent;
    PFN_eglQueryContext_PROC QueryContext;
    PFN_eglQueryString_PROC QueryString;
    PFN_eglQuerySurface_PROC QuerySurface;
    PFN_eglSwapBuffers_PROC SwapBuffers;
    PFN_eglTerminate_PROC Terminate;
    PFN_eglWaitGL_PROC WaitGL;
    PFN_eglWaitNative_PROC WaitNative;
    PFN_eglBindTexImage_PROC BindTexImage;
    PFN_eglReleaseTexImage_PROC ReleaseTexImage;
    PFN_eglSurfaceAttrib_PROC SurfaceAttrib;
    PFN_eglSwapInterval_PROC SwapInterval;
    PFN_eglBindAPI_PROC BindAPI;
    PFN_eglQueryAPI_PROC QueryAPI;
    PFN_eglCreatePbufferFromClientBuffer_PROC CreatePbufferFromClientBuffer;
    PFN_eglReleaseThread_PROC ReleaseThread;
    PFN_eglWaitClient_PROC WaitClient;
    PFN_eglGetCurrentContext_PROC GetCurrentContext;
    PFN_eglCreateSync_PROC CreateSync;
    PFN_eglDestroySync_PROC DestroySync;
    PFN_eglClientWaitSync_PROC ClientWaitSync;
    PFN_eglGetSyncAttrib_PROC GetSyncAttrib;
    PFN_eglCreateImage_PROC CreateImage;
    PFN_eglDestroyImage_PROC DestroyImage;
    PFN_eglGetPlatformDisplay_PROC GetPlatformDisplay;
    PFN_eglCreatePlatformWindowSurface_PROC CreatePlatformWindowSurface;
    PFN_eglCreatePlatformPixmapSurface_PROC CreatePlatformPixmapSurface;
    PFN_eglWaitSync_PROC WaitSync;
};


typedef struct s_glcontext_egl *t_glcontext_egl;

struct s_glcontext_egl {
    EGLDisplay dpy;
    EGLConfig  config;
    EGLSurface surface;
    EGLContext context;
};

/* internal functions (declarations) */

WININT int __winLoadEGL(void);

WININT int __winLoadEGLSymbols(void);

WININT int __winUnloadEGL(void);

/* internal functions (definitions) */

WININT int __winLoadEGL(void) {
    /* alloc '__window_h.egl' field */
    if (!__window_h.egl) {
        __window_h.egl = calloc(1, sizeof(struct __window_h_egl));
        if (!__window_h.egl) {
            return (0);
        }
    }

    /* try to load libEGL symbols */
    if (!__winLoadEGLSymbols()) { return (0); }
    
    /* get '__window_h.egl' members */
    EGLDisplay dpy = eglGetDisplay(__window_h.x11->xlib.dpy);
    if (dpy == EGL_NO_DISPLAY) { return (0); }

    /* set '__window_h.egl' members */
    __window_h.egl->dpy = dpy;

    /* set '__window_h.egl->attr' defaults */
    int attr_surface[16] = { EGL_NONE };

    memcpy(__window_h.egl->attr.surface, attr_surface, sizeof(attr_surface));
    
    int attr_context[32] = { EGL_CONTEXT_MAJOR_VERSION, 1,
                             EGL_CONTEXT_MINOR_VERSION, 0,
                             EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
                             EGL_CONTEXT_OPENGL_DEBUG, EGL_FALSE,
                             EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE, EGL_FALSE,
                             EGL_CONTEXT_OPENGL_ROBUST_ACCESS, EGL_FALSE,
                             EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY, EGL_NO_RESET_NOTIFICATION,
                             EGL_NONE };

    memcpy(__window_h.egl->attr.context, attr_context, sizeof(attr_context));
    
    int attr_config[64] = { EGL_ALPHA_MASK_SIZE, 0,
                            EGL_ALPHA_SIZE, 0,
                            EGL_BIND_TO_TEXTURE_RGB, EGL_DONT_CARE,
                            EGL_BIND_TO_TEXTURE_RGBA, EGL_DONT_CARE,
                            EGL_BLUE_SIZE, 0,
                            EGL_BUFFER_SIZE, 0,
                            EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
                            EGL_CONFIG_CAVEAT, EGL_DONT_CARE,
                            EGL_CONFIG_ID, EGL_DONT_CARE,
                            EGL_CONFORMANT, 0,
                            EGL_DEPTH_SIZE, 0,
                            EGL_GREEN_SIZE, 0,
                            EGL_LEVEL, 0,
                            EGL_LUMINANCE_SIZE, 0,
                            EGL_MATCH_NATIVE_PIXMAP, EGL_NONE,
                            EGL_NATIVE_RENDERABLE, EGL_DONT_CARE,
                            EGL_MAX_SWAP_INTERVAL, EGL_DONT_CARE,
                            EGL_MIN_SWAP_INTERVAL, EGL_DONT_CARE,
                            EGL_RED_SIZE, 0,
                            EGL_SAMPLE_BUFFERS, 0,
                            EGL_SAMPLES, 0,
                            EGL_STENCIL_SIZE, 0,
                            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
                            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                            EGL_TRANSPARENT_TYPE, EGL_NONE,
                            EGL_TRANSPARENT_RED_VALUE, EGL_DONT_CARE,
                            EGL_TRANSPARENT_GREEN_VALUE, EGL_DONT_CARE,
                            EGL_TRANSPARENT_BLUE_VALUE, EGL_DONT_CARE,
                            EGL_NONE };

    memcpy(__window_h.egl->attr.config, attr_config, sizeof(attr_config));

    /* success */
    return (1);
}


WININT int __winLoadEGLSymbols(void) {
    /* null-check */
    if (!__window_h.egl) { return (0); }

    /* try to load handle */
    const char  *names[] = { "libEGL.so", "libEGL.so.1, libEGL.so.1.1.0", 0 };
    static void *handle  = 0;
    if (!handle) {
        for (const char **name = names; *name; name++) {
            handle = dlopen(*name, RTLD_NOW | RTLD_GLOBAL);
            if (handle) { break; }
        }

        /* check if handle loaded */
        if (!handle) { return (0); }
    }

    /* load libEGL symbols */
    eglChooseConfig = (PFN_eglChooseConfig_PROC) dlsym(handle, "eglChooseConfig");
    if (!eglChooseConfig) { return (0); }

    eglCopyBuffers = (PFN_eglCopyBuffers_PROC) dlsym(handle, "eglCopyBuffers");
    if (!eglCopyBuffers) { return (0); }

    eglCreateContext = (PFN_eglCreateContext_PROC) dlsym(handle, "eglCreateContext");
    if (!eglCreateContext) { return (0); }

    eglCreatePbufferSurface = (PFN_eglCreatePbufferSurface_PROC) dlsym(handle, "eglCreatePbufferSurface");
    if (!eglCreatePbufferSurface) { return (0); }

    eglCreatePixmapSurface = (PFN_eglCreatePixmapSurface_PROC) dlsym(handle, "eglCreatePixmapSurface");
    if (!eglCreatePixmapSurface) { return (0); }

    eglCreateWindowSurface = (PFN_eglCreateWindowSurface_PROC) dlsym(handle, "eglCreateWindowSurface");
    if (!eglCreateWindowSurface) { return (0); }

    eglDestroyContext = (PFN_eglDestroyContext_PROC) dlsym(handle, "eglDestroyContext");
    if (!eglDestroyContext) { return (0); }

    eglDestroySurface = (PFN_eglDestroySurface_PROC) dlsym(handle, "eglDestroySurface");
    if (!eglDestroySurface) { return (0); }

    eglGetConfigAttrib = (PFN_eglGetConfigAttrib_PROC) dlsym(handle, "eglGetConfigAttrib");
    if (!eglGetConfigAttrib) { return (0); }

    eglGetConfigs = (PFN_eglGetConfigs_PROC) dlsym(handle, "eglGetConfigs");
    if (!eglGetConfigs) { return (0); }

    eglGetCurrentDisplay = (PFN_eglGetCurrentDisplay_PROC) dlsym(handle, "eglGetCurrentDisplay");
    if (!eglGetCurrentDisplay) { return (0); }

    eglGetCurrentSurface = (PFN_eglGetCurrentSurface_PROC) dlsym(handle, "eglGetCurrentSurface");
    if (!eglGetCurrentSurface) { return (0); }

    eglGetDisplay = (PFN_eglGetDisplay_PROC) dlsym(handle, "eglGetDisplay");
    if (!eglGetDisplay) { return (0); }

    eglGetError = (PFN_eglGetError_PROC) dlsym(handle, "eglGetError");
    if (!eglGetError) { return (0); }

    eglGetProcAddress = (PFN_eglGetProcAddress_PROC) dlsym(handle, "eglGetProcAddress");
    if (!eglGetProcAddress) { return (0); }

    eglInitialize = (PFN_eglInitialize_PROC) dlsym(handle, "eglInitialize");
    if (!eglInitialize) { return (0); }

    eglMakeCurrent = (PFN_eglMakeCurrent_PROC) dlsym(handle, "eglMakeCurrent");
    if (!eglMakeCurrent) { return (0); }

    eglQueryContext = (PFN_eglQueryContext_PROC) dlsym(handle, "eglQueryContext");
    if (!eglQueryContext) { return (0); }

    eglQueryString = (PFN_eglQueryString_PROC) dlsym(handle, "eglQueryString");
    if (!eglQueryString) { return (0); }

    eglQuerySurface = (PFN_eglQuerySurface_PROC) dlsym(handle, "eglQuerySurface");
    if (!eglQuerySurface) { return (0); }

    eglSwapBuffers = (PFN_eglSwapBuffers_PROC) dlsym(handle, "eglSwapBuffers");
    if (!eglSwapBuffers) { return (0); }

    eglTerminate = (PFN_eglTerminate_PROC) dlsym(handle, "eglTerminate");
    if (!eglTerminate) { return (0); }

    eglWaitGL = (PFN_eglWaitGL_PROC) dlsym(handle, "eglWaitGL");
    if (!eglWaitGL) { return (0); }

    eglWaitNative = (PFN_eglWaitNative_PROC) dlsym(handle, "eglWaitNative");
    if (!eglWaitNative) { return (0); }

    eglBindTexImage = (PFN_eglBindTexImage_PROC) dlsym(handle, "eglBindTexImage");
    if (!eglBindTexImage) { return (0); }

    eglReleaseTexImage = (PFN_eglReleaseTexImage_PROC) dlsym(handle, "eglReleaseTexImage");
    if (!eglReleaseTexImage) { return (0); }

    eglSurfaceAttrib = (PFN_eglSurfaceAttrib_PROC) dlsym(handle, "eglSurfaceAttrib");
    if (!eglSurfaceAttrib) { return (0); }

    eglSwapInterval = (PFN_eglSwapInterval_PROC) dlsym(handle, "eglSwapInterval");
    if (!eglSwapInterval) { return (0); }

    eglBindAPI = (PFN_eglBindAPI_PROC) dlsym(handle, "eglBindAPI");
    if (!eglBindAPI) { return (0); }

    eglQueryAPI = (PFN_eglQueryAPI_PROC) dlsym(handle, "eglQueryAPI");
    if (!eglQueryAPI) { return (0); }

    eglCreatePbufferFromClientBuffer = (PFN_eglCreatePbufferFromClientBuffer_PROC) dlsym(handle, "eglCreatePbufferFromClientBuffer");
    if (!eglCreatePbufferFromClientBuffer) { return (0); }

    eglReleaseThread = (PFN_eglReleaseThread_PROC) dlsym(handle, "eglReleaseThread");
    if (!eglReleaseThread) { return (0); }

    eglWaitClient = (PFN_eglWaitClient_PROC) dlsym(handle, "eglWaitClient");
    if (!eglWaitClient) { return (0); }

    eglGetCurrentContext = (PFN_eglGetCurrentContext_PROC) dlsym(handle, "eglGetCurrentContext");
    if (!eglGetCurrentContext) { return (0); }

    eglCreateSync = (PFN_eglCreateSync_PROC) dlsym(handle, "eglCreateSync");
    if (!eglCreateSync) { return (0); }

    eglDestroySync = (PFN_eglDestroySync_PROC) dlsym(handle, "eglDestroySync");
    if (!eglDestroySync) { return (0); }

    eglClientWaitSync = (PFN_eglClientWaitSync_PROC) dlsym(handle, "eglClientWaitSync");
    if (!eglClientWaitSync) { return (0); }

    eglGetSyncAttrib = (PFN_eglGetSyncAttrib_PROC) dlsym(handle, "eglGetSyncAttrib");
    if (!eglGetSyncAttrib) { return (0); }

    eglCreateImage = (PFN_eglCreateImage_PROC) dlsym(handle, "eglCreateImage");
    if (!eglCreateImage) { return (0); }

    eglDestroyImage = (PFN_eglDestroyImage_PROC) dlsym(handle, "eglDestroyImage");
    if (!eglDestroyImage) { return (0); }

    eglGetPlatformDisplay = (PFN_eglGetPlatformDisplay_PROC) dlsym(handle, "eglGetPlatformDisplay");
    if (!eglGetPlatformDisplay) { return (0); }

    eglCreatePlatformWindowSurface = (PFN_eglCreatePlatformWindowSurface_PROC) dlsym(handle, "eglCreatePlatformWindowSurface");
    if (!eglCreatePlatformWindowSurface) { return (0); }

    eglCreatePlatformPixmapSurface = (PFN_eglCreatePlatformPixmapSurface_PROC) dlsym(handle, "eglCreatePlatformPixmapSurface");
    if (!eglCreatePlatformPixmapSurface) { return (0); }

    eglWaitSync = (PFN_eglWaitSync_PROC) dlsym(handle, "eglWaitSync");
    if (!eglWaitSync) { return (0); }

    /* set '__window_h.egl->handle' member */ 
    __window_h.egl->handle = handle;

    /* success */
    return (1);
}


WININT int __winUnloadEGL(void) {
    /* null-check */
    if (!__window_h.egl) { return (0); }

    /* release '__window_h.egl->handle' field */
    dlclose(__window_h.egl->handle), __window_h.egl->handle = 0;

    /* release '__window_h.egl' */
    free(__window_h.egl);

    /* success */
    return (1);
}

#  endif /* WINDOW_BACKEND_GL_EGL */
#
#  /* WINDOW_BACKEND_GL_WGL - WGL implementation layer */
#  if defined (WINDOW_BACKEND_GL_WGL)

/* internal type declarations */

typedef struct s_glcontext_wgl *t_glcontext_wgl;

struct s_glcontext_wgl {

    /* ... */

};

#  endif /* WINDOW_BACKEND_GL_WGL */
#
#  /* WINDOW_BACKEND_X11 - X11 implementation */
#  if defined (WINDOW_BACKEND_X11)

/* internal functions (declarations) */

WININT int __winCreateWindowX11(t_window, Display *, Window, Window, const size_t, const size_t);

WININT int __winUpdateWindowFlagsX11(t_window);

WININT int __winSendClientEventX11(t_window, Atom, Atom, Atom);

WININT int __winPollEvents(void);

/* platform functions */

WINDEF int winInit(void) {
    /* initialize '__window_h' object */
    __window_h = (struct __window_h) { 0 };

    /* load '__window_h.x11' */
    if (!__winLoadX11()) { return (0); }

	/* xlib references */
	Display *dpy = __window_h.x11->xlib.dpy;
    
    /* set keyboard input repeating */
    Bool supported;
    XkbSetDetectableAutoRepeat(dpy, True, &supported);
    if (!supported) { return (0); }
    
#   if defined (WINDOW_API_OPENGL)
#    if defined (WINDOW_BACKEND_GL_EGL)
    /* load '__window_h.x11' */
    if (!__winLoadEGL()) { return (0); }
  
    /* egl references */
    EGLDisplay egldpy = __window_h.egl->dpy;

    /* initialize EGL */
    if (!eglInitialize(egldpy, 0, 0)) { return (0); }
    if (!eglBindAPI(EGL_OPENGL_API))  { return (0); }
#    endif /* WINDOW_BACKEND_GL_EGL */
#   endif /* WINDOW_API_OPENGL */

    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winQuit(void) {
    /* close all the open windows */
    t_window curr = __window_h.window_list,
             next = 0;
    while (curr) {
        next = curr->next;
        winDestroyWindow(curr);
        curr = next;
    }

    /* release event queue */
    free(__window_h.event_queue.arr);
    __window_h.event_queue = (struct __window_h_eventQueue) { 0 };

    /* release xlib resources */
    XCloseDisplay(__window_h.x11->xlib.dpy);

#   if defined (WINDOW_API_OPENGL)
#    if defined (WINDOW_BACKEND_GL_EGL)
    /* unload '__window_h.egl' */
    if (!__winUnloadEGL()) { return (0); }
#    endif /* WINDOW_BACKEND_GL_EGL */
#   endif /* WINDOW_API_OPENGL */
    
    /* unload '__window_h.x11' */
    if (!__winUnloadX11()) { return (0); }
    
    /* success */
    return (1);
}


WINDEF int winGetSize(size_t *w_ptr, size_t *h_ptr) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* references */
    Display *dpy = __window_h.x11->xlib.dpy;
    Window  root = __window_h.x11->xlib.root;

    /* query attributes */
    XWindowAttributes attr;
    if (!XGetWindowAttributes(dpy, root, &attr)) { return (0); }
    
    /* assign values */
    if (w_ptr) { *w_ptr = attr.width; }
    if (h_ptr) { *h_ptr = attr.height; }

    /* success */
    return (1);
}


WINDEF void *winGetProperty(const uint32_t prop) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    switch (prop) {
        case (WINDOW_PROP_PLATFORM_X11_DISPLAY): { return (__window_h.x11->xlib.dpy); }
        case (WINDOW_PROP_PLATFORM_X11_ROOT_ID): { return (&__window_h.x11->xlib.root); }

        default: { } break;
    }

    /* return nothing */
    return (0);
}

/* windowing functions */

WINDEF int winCreateWindow(t_window *win, const size_t w, const size_t h, const char *t, const uint32_t f) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* alloc new window object */
    t_window result = calloc(1, sizeof(struct s_window));
    if (!result) { return (0); }

    /* process 'result' window object */
    if (!__winCreateWindowX11(result, __window_h.x11->xlib.dpy,
                                      __window_h.x11->xlib.root,
                                      __window_h.x11->xlib.root, w, h)
    ) {
        return (0);
    }

    /* update window flags */
    winSetWindowFlag(result, f);

    /* set window title */ 
    winSetWindowTitle(result, t);

    /* update window dimension properites */
    winGetWindowPosition(result, &result->pos_x, &result->pos_y);
    winGetWindowSize(result, &result->siz_w, &result->siz_h);

    /* add the result to the '__window_h.window_list' linked list */
    result->next = __window_h.window_list;
    __window_h.window_list = result;

    /* and return the result */
    *win = result;

    /* success */
    return (1);
}


WINDEF int winCreateNestedWindow(t_window *win, t_window parent, const size_t w, const size_t h, const char *t, const uint32_t f) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* alloc new window object */
    t_window result = calloc(1, sizeof(struct s_window));
    if (!result) { return (0); }

    /* process 'result' window object */
    if (!__winCreateWindowX11(result, __window_h.x11->xlib.dpy,
                                      __window_h.x11->xlib.root,
                                      parent->x11->xlib.client, w, h)
    ) {
        return (0);
    }

    /* update window flags */
    winSetWindowFlag(result, f);

    /* set window title */ 
    winSetWindowTitle(result, t);

    /* update window dimension properites */
    winGetWindowPosition(result, &result->pos_x, &result->pos_y);
    winGetWindowSize(result, &result->siz_w, &result->siz_h);

    /* add the result to the '__window_h.window_list' linked list */
    result->next = __window_h.window_list;
    __window_h.window_list = result;

    /* and return the result */
    *win = result;

    /* success */
    return (1);
}


WINDEF int winDestroyWindow(t_window win) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* unlink 'win' from '__window_h.window_list' */
    t_window *curr = &__window_h.window_list;
    /* case when 'win' is the first node of '__window_h.window_list' */
    if (win == (*curr)) {
        __window_h.window_list = (*curr)->next;
    }
    /* case when 'win' is not the first node of '__window_h.window_list' */
    else {
        /* search for prepending window for 'win' */
        while ((*curr) && (*curr)->next != win) {
            (*curr) = (*curr)->next;
        }

        if (!(*curr)) { return (0); }
        (*curr) = win->next;
    }

    /* destroy client */
    XDestroyWindow(win->x11->xlib.dpy,
                   win->x11->xlib.client);
                        
    /* deallocate window object */
    free(win->x11);
    free(win);

    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winSetWindowFlag(t_window win, const uint32_t f) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
   
    /* set flags */
    win->flags = f;
    __winUpdateWindowFlagsX11(win);

    /* success */
    return (1);
}


WINDEF void *winGetWindowProperty(t_window win, const uint32_t prop) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    switch (prop) {
        case (WINDOW_PROP_WINDOW_X11_DISPLAY): { return (win->x11->xlib.dpy); }
        case (WINDOW_PROP_WINDOW_X11_ROOT_ID): { return (&win->x11->xlib.root); }
        case (WINDOW_PROP_WINDOW_X11_PARENT_ID): { return (&win->x11->xlib.parent); }
        case (WINDOW_PROP_WINDOW_X11_CLIENT_ID): { return (&win->x11->xlib.client); }

        default: { } break;
    }

    /* return nothing */
    return (0);
}


WINDEF int winMapWindow(t_window win) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* map window */
    XMapWindow(dpy, client);
    winFlushEvents();

    /* wait for 'MapNotify' to arrive */ 
    XEvent xevent = { 0 };
    do {
        XWindowEvent(dpy, client, StructureNotifyMask, &xevent);
    } while (xevent.type != MapNotify);
    win->mapped = 1;

    /* lastly, update all the configs that required mapping */
    if (!__winUpdateWindowFlagsX11(win)) {
        return (0);
    }

    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winUnmapWindow(t_window win) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* map window */
    XUnmapWindow(dpy, client);
    winFlushEvents();

    /* wait for 'MapNotify' to arrive */ 
    XEvent xevent = { 0 };
    do {
        XWindowEvent(dpy, client, StructureNotifyMask, &xevent);
    } while (xevent.type != MapNotify);
    win->mapped = 0;

    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winGetWindowSize(t_window win, size_t *w_ptr, size_t *h_ptr) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* get window attributes */
    XWindowAttributes attr = { 0 };
    if (!XGetWindowAttributes(dpy, client, &attr)) { return (0); }

    /* return values */
    if (w_ptr) { *w_ptr = attr.width; }
    if (h_ptr) { *h_ptr = attr.height; }
    
    /* success */
    return (1);
}


WINDEF int winSetWindowSize(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* resize window */
    if (!XResizeWindow(dpy, client, w, h)) { return (0); }
    
    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winSetWindowMinSize(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(dpy, client, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags |= PMinSize;
    hints.min_width  = w;
    hints.min_height = h;
    XSetWMNormalHints(dpy, client, &hints);

    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winSetWindowMaxSize(t_window win, const size_t w, const size_t h) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(dpy, client, &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags |= PMaxSize;
    hints.max_width  = w;
    hints.max_height = h;
    XSetWMNormalHints(dpy, client, &hints);

    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winGetWindowPosition(t_window win, size_t *x_ptr, size_t *y_ptr) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* get window attributes */
    XWindowAttributes attr = { 0 };
    if (!XGetWindowAttributes(dpy, client, &attr)) { return (0); }

    /* return values */
    if (x_ptr) { *x_ptr = attr.x; }
    if (y_ptr) { *y_ptr = attr.y; }
    
    /* success */
    return (1);
}


WINDEF int winSetWindowPosition(t_window win, const size_t x, const size_t y) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* resize window */
    if (!XMoveWindow(dpy, client, x, y)) { return (0); }
    
    /* success */
    winFlushEvents();
    return (1);
}


WINDEF int winGetWindowTitle(t_window win, char **t_ptr) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* fetch window title */
    if (!XFetchName(dpy, client, t_ptr)) { return (0); }

    /* success */
    return (1);
}


WINDEF int winSetWindowTitle(t_window win, const char *t) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display *dpy   = win->x11->xlib.dpy;
    Window  client = win->x11->xlib.client;

    /* fetch window title */
    if (!XStoreName(dpy, client, t)) { return (0); }
    
    /* success */
    return (1);
}

/* opengl context functions */

WINDEF int winGLCreateContext(t_glcontext *ctx, t_window win) {

/* check if 'WINDOW_API_OPENGL' is defined  */
#   if !defined (WINDOW_API_OPENGL)
    (void) ctx;
    (void) win;
    return (0);
#   else
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!__window_h.egl) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }

    /* references */
    EGLDisplay dpy = __window_h.egl->dpy;
    
    /* alloc new context object */
    t_glcontext result = calloc(1, sizeof(struct s_glcontext));
    if (!result) { return (0); }

    result->egl = calloc(1, sizeof(struct s_glcontext_egl));
    if (!result->egl) { return (0); }

    /* get EGLConfig object */
    int num_config   = 0;
    EGLConfig config = 0;
    if (!eglChooseConfig(dpy, __window_h.egl->attr.config, &config, 1, &num_config)) { return (0); }

    /* get EGLSurface object */
    EGLSurface surface = eglCreateWindowSurface(dpy, config, win->x11->xlib.client, __window_h.egl->attr.surface);
    if (surface == EGL_NO_SURFACE) { return (0); }

    /* get EGLContext object */
    EGLContext context = eglCreateContext(dpy, config, EGL_NO_CONTEXT, __window_h.egl->attr.context);
    if (context == EGL_NO_CONTEXT) { return (0); }
    
    /* set 'result->egl' members */
    if (!dpy) { return (0); }
    result->egl->dpy = dpy;

    if (!config) { return (0); }
    result->egl->config = config;

    if (!surface) { return (0); }
    result->egl->surface = surface;

    if (!context) { return (0); }
    result->egl->context = context;

    /* and return the result */
    *ctx = result;

    /* success */
    return (1);
#   endif

}

WINDEF int winGLDestroyContext(t_glcontext ctx, t_window win) {

/* check if 'WINDOW_API_OPENGL' is defined  */
#   if !defined (WINDOW_API_OPENGL)
    (void) ctx;
    (void) win;
    return (0);
#   else
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!__window_h.egl) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }

    /* references */
    EGLDisplay dpy = ctx->egl->dpy;
    EGLSurface surface = ctx->egl->surface;
    EGLContext context = ctx->egl->context;

    eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (context) { eglDestroyContext(dpy, context); }
    if (surface) { eglDestroySurface(dpy, surface); }
 
    /* deallocate window object */
    free(ctx->egl);
    free(ctx);

    /* success */
    return (1);
#   endif

}

WINDEF int winGLSetAttribute(const int attr, const int value) {

/* check if 'WINDOW_API_OPENGL' is defined  */
#   if !defined (WINDOW_API_OPENGL)
    (void) attr;
    (void) value;
    return (0);
#   else
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!__window_h.egl) { return (0); }

    (void) attr;
    (void) value;
    
    /* success */
    return (1);
#   endif

}

WINDEF int winGLMakeCurrent(t_glcontext ctx, t_window win) {

/* check if 'WINDOW_API_OPENGL' is defined  */
#   if !defined (WINDOW_API_OPENGL)
    (void) ctx;
    (void) win;
    return (0);
#   else
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!__window_h.egl) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }
    
    /* references */
    EGLDisplay dpy = ctx->egl->dpy;
    EGLSurface surface = ctx->egl->surface;
    EGLContext context = ctx->egl->context;

    (void) win;
    if (!eglMakeCurrent(dpy, surface, surface, context)) {
        return (0);
    }

    /* success */
    return (1);
#   endif

}

WINDEF int winGLSwapBuffers(t_glcontext ctx, t_window win) {

/* check if 'WINDOW_API_OPENGL' is defined  */
#   if !defined (WINDOW_API_OPENGL)
    (void) ctx;
    (void) win;
    return (0);
#   else
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!__window_h.egl) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }
    
    /* references */
    EGLDisplay dpy = ctx->egl->dpy;
    EGLSurface surface = ctx->egl->surface;

    eglSwapBuffers(dpy, surface);

    /* success */
    return (1);
#   endif

}

WINDEF int winGLSwapInterval(t_glcontext ctx, const int interval) {

/* check if 'WINDOW_API_OPENGL' is defined  */
#   if !defined (WINDOW_API_OPENGL)
    (void) ctx;
    (void) interval;
    return (0);
#   else
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!__window_h.egl) { return (0); }
    if (!ctx) { return (0); }
    
    /* references */
    EGLDisplay dpy = ctx->egl->dpy;

    eglSwapInterval(dpy, interval);

    /* success */
    return (1);
#   endif

}

WINDEF void *winGLGetProcAddress(const char *proc) {

/* check if 'WINDOW_API_OPENGL' is defined  */
#   if !defined (WINDOW_API_OPENGL)
    (void) proc;
    return (0);
#   else
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!__window_h.egl) { return (0); }

    /* success */
    return (eglGetProcAddress(proc));
#   endif

}

/* event functions */

WINDEF int winPollEvents(t_event *event) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!event)  		 { return (0); }

    /* poll events from platform queue */
    if (winPopEvent(event)) { return (1); }

    /* handle platform events */
    __winPollEvents();

    /* queue filled, return WINDOW_EVENT_NONE */
    *event = (t_event) { 0 };
    return (0);
}


WINDEF int winWaitEvents(t_event *event) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    if (!event)  		 { return (0); }

    /* success */
    return (1);
}


WINDEF int winPushEvent(t_event *event) {
    /* null-check */
    if (!event)  { return (0); }
    
    /* alloc new `arr` if needed */
    if (!__window_h.event_queue.arr) {
        t_event *arr = malloc(WINDOW_EVENT_QUEUE_CAPACITY * sizeof(t_event));
        if (!arr) { return (0); }

        __window_h.event_queue.arr = __window_h.event_queue.bgn = __window_h.event_queue.end = arr;
        __window_h.event_queue.cap = WINDOW_EVENT_QUEUE_CAPACITY;
        __window_h.event_queue.cnt = 0;
    }

    /* bound check */
    if (__window_h.event_queue.cnt >= __window_h.event_queue.cap) {
        /* consider resizing
         * for now returning
         * */
        return (0);
    }

    /* assign the object to the last `arr` element */
    *__window_h.event_queue.end = *event;
    /* move the last element by one */
    __window_h.event_queue.end++;
    /* boundary check
     * if exceeds the `arr`, return back to start
     * */
    size_t end = __window_h.event_queue.end - __window_h.event_queue.arr;
    if (end >= __window_h.event_queue.cap) {
        __window_h.event_queue.end = __window_h.event_queue.arr;
    }

    /* increment the count */
    __window_h.event_queue.cnt++;

    /* success */
    return (1);
}


WINDEF int winPopEvent(t_event *event) {
    /* null-check */
    if (!event)  { return (0); }

    /* check if event queue exists */
    if (!__window_h.event_queue.arr) { return (0); }

    /* check if there's anything in the queue */
    if (__window_h.event_queue.cnt == 0) { return (0); }

    /* assign the first element to the reference */
    *event = *__window_h.event_queue.bgn;
    /* zero-down the first element (safety matter) */
    *__window_h.event_queue.bgn = (t_event) { 0 };
    /* move the first element by one */
    __window_h.event_queue.bgn++;
    /* boundary check
     * if exceeds the `arr`, return back to start
     * */
    size_t bgn = __window_h.event_queue.bgn - __window_h.event_queue.arr;
    if (bgn >= __window_h.event_queue.cap) {
        __window_h.event_queue.bgn = __window_h.event_queue.arr;
    }

    /* decrement the count */
    __window_h.event_queue.cnt--;

    /* success */
    return (1);
}


WINDEF int winPeekEvent(t_event *event) {
    /* null-check */
    if (!event)  { return (0); }

    /* zero-down the event */
    *event = (t_event) { 0 };

    /* check if event queue exists */
    if (!__window_h.event_queue.arr) { return (0); }

    /* check if there's anything in the queue */
    if (__window_h.event_queue.cnt == 0) { return (0); }

    /* assign the first element to the reference */
    *event = *__window_h.event_queue.bgn;

    /* success */
    return (1);
}


WINDEF int winFlushEvents(void) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    
    /* flush */
    if (!XFlush(__window_h.x11->xlib.dpy)) { return (0); }

    /* success */
    return (1);
}

/* timing functions */

WINDEF uint64_t winGetTime(void) {
    struct timeval t;
    if (gettimeofday(&t, 0) == -1) {
        return (0);
    }

    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}


WINDEF int winWaitTime(uint64_t ms) {
    uint64_t t = winGetTime();
    if (t == 0) { return (0); }

    while ((winGetTime() - t) < ms);
    return (1);
}

/* internal functions (definitions) */

WININT int __winCreateWindowX11(t_window win, Display *dpy, Window root, Window parent, const size_t w, const size_t h) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

#   if defined (WINDOW_API_OPENGL)
    if (!__window_h.egl) { return (0); }
#   endif

    /* allocate 'win->x11' field */
    win->x11 = calloc(1, sizeof (struct s_window_x11));
    if (!win->x11) { return (0); }

    /* get screen index */
    int screen = DefaultScreen(dpy);

    /* get visual and depth */
#   if defined (WINDOW_API_NONE)
    /* get default visual from display and screen */
    Visual *visual = DefaultVisual(dpy, screen);
    
    /* get default depth value from display and screen */
    int depth = DefaultDepth(dpy, screen);
#   elif defined (WINDOW_API_OPENGL)
    /* get EGLConfig object */
    int num_config   = 0;
    EGLConfig config = 0;
    if (!eglChooseConfig(__window_h.egl->dpy, __window_h.egl->attr.config, &config, 1, &num_config)) { return (0); }

    /* get visual ID based on EGLConfig */
    int visualid = 0;
    eglGetConfigAttrib(__window_h.egl->dpy, config, EGL_NATIVE_VISUAL_ID, &visualid);

    /* create desired XVisualInfo */
    XVisualInfo desired = {
        .visualid = visualid,
        .screen = screen
    };

    /* get XVisualInfo based on 'desired' */
    int count = 0;
    XVisualInfo *vi = XGetVisualInfo(dpy, VisualScreenMask | VisualIDMask, &desired, &count);
    if (!vi) { return (0); }

    /* get visual from 'vi' */
    Visual *visual = vi->visual; 
    
    /* get depth value from 'vi' */
    int depth = vi->depth; 

    /* release 'vi' */
    XFree(vi), vi = 0;
#   else
    /* ... */
#   endif

    /* create XSetWindowAttributes */
    XSetWindowAttributes attr = { 0 };
    attr.colormap = XCreateColormap(dpy, root, visual, AllocNone);
    attr.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask |
                      PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                      ExposureMask | FocusChangeMask | VisibilityChangeMask |
                      EnterWindowMask | LeaveWindowMask | PropertyChangeMask;

    /* create window */
    Window client = XCreateWindow(dpy, parent, 0, 0, w, h, 0, depth, InputOutput, visual, CWBorderPixel | CWColormap | CWEventMask | CWBackPixel, &attr);
    if (!client) { return (0); }

    /* select input */
    XSelectInput(dpy, client, attr.event_mask);

    /* set WM protocols atoms */
    XSetWMProtocols(dpy, client, &__window_h.x11->xatom.wm_protocols, 1);
    XSetWMProtocols(dpy, client, &__window_h.x11->xatom.wm_delete_window, 1);

    /* set 'win.x11->xlib' members */
    if (!dpy) { return (0); }
    win->x11->xlib.dpy = dpy;
    
    if (!root) { return (0); }
    win->x11->xlib.root = root;
    
    if (!parent) { return (0); }
    win->x11->xlib.parent = parent;
    
    if (!client) { return (0); }
    win->x11->xlib.client = client;

    /* success */
    winFlushEvents();
    return (1);
}


WININT int __winUpdateWindowFlagsX11(t_window win) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* attr references */
    uint8_t mapped = win->mapped;
    uint32_t flags = win->flags;

	/* xlib references */
	Display  *dpy = win->x11->xlib.dpy;
    Window client = win->x11->xlib.client;

    /* xatom references */
    Atom              _MOTIF_WM_HINTS = __window_h.x11->xatom._motif_wm_hints;
    Atom     _NET_WM_STATE_FULLSCREEN = __window_h.x11->xatom._net_wm_state_fullscreen;
    Atom         _NET_WM_STATE_HIDDEN = __window_h.x11->xatom._net_wm_state_hidden;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = __window_h.x11->xatom._net_wm_state_maximized_horz;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = __window_h.x11->xatom._net_wm_state_maximized_vert;
    Atom          _NET_WM_STATE_ABOVE = __window_h.x11->xatom._net_wm_state_above;
    
    /* properties that requires the window to be mapped */
    if (mapped) {
        /* WINDOW_FLAG_FULLSCREEN */
        if (flags & WINDOW_FLAG_FULLSCREEN) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_FULLSCREEN, 0);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_FULLSCREEN, 0);
        }

        /* WINDOW_FLAG_MINIMIZED */
        if (flags & WINDOW_FLAG_MINIMIZED) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_HIDDEN, 0);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_HIDDEN, 0);
        }

        /* WINDOW_FLAG_MAXIMIZED */
        if (flags & WINDOW_FLAG_MAXIMIZED) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_MAXIMIZED_HORZ, _NET_WM_STATE_MAXIMIZED_VERT);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_MAXIMIZED_HORZ, _NET_WM_STATE_MAXIMIZED_VERT);
        }

        /* WINDOW_FLAG_TOPMOST */
        if (flags & WINDOW_FLAG_TOPMOST) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_ABOVE, 0);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_ABOVE, 0);
        }
    }
    
    /* properties that doesn't require the window to be mapped */
    
    /* WINDOW_FLAG_RESIZABLE */
    if (flags & WINDOW_FLAG_RESIZABLE) {
        XSizeHints hints; int64_t supp;
        XGetWMNormalHints(dpy, client, &hints, &supp);

        hints.flags &= ~PMinSize & ~PMaxSize;
        XSetWMNormalHints(dpy, client, &hints);
    } else {
        size_t w = 0,
               h = 0;
        winGetWindowSize(win, &w, &h);
        winSetWindowMinSize(win, w, h);
        winSetWindowMaxSize(win, w, h);
    }

    /* WINDOW_FLAG_UNDECORATED*/
    if (flags & WINDOW_FLAG_UNDECORATED) {
        long mwmhints[8] = { 0 };
        mwmhints[0] = (1L << 1);
        mwmhints[2] = _NET_WM_STATE_REMOVE;
        XChangeProperty(dpy, client, _MOTIF_WM_HINTS, _MOTIF_WM_HINTS, 32, PropModeReplace, (uint8_t *) mwmhints, 8);
    } else {
        long mwmhints[8] = { 0 };
        mwmhints[0] = (1L << 1);
        mwmhints[2] = _NET_WM_STATE_ADD;
        XChangeProperty(dpy, client, _MOTIF_WM_HINTS, _MOTIF_WM_HINTS, 32, PropModeReplace, (uint8_t *) mwmhints, 8);
    }

    /* success */
    return (1);
}


WININT int __winSendClientEventX11(t_window win, Atom a0, Atom a1, Atom a2) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

	/* xlib references */
	Display  *dpy = win->x11->xlib.dpy;
    Window   root = win->x11->xlib.root;
    Window client = win->x11->xlib.client;
	
    /* xatom references */
    Atom _NET_WM_STATE = __window_h.x11->xatom._net_wm_state;

    /* create client event */
    XClientMessageEvent xclient = {
        .type = ClientMessage,
        .display = dpy,
        .window = client,
        .message_type = _NET_WM_STATE,
        .format = 32,
        .data = { .l = {
                [0] = a0,
                [1] = a1,
                [2] = a2
            }
        }
    };

    /* send event */
    XSendEvent(dpy, root, 0, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *) &xclient);

    /* success */
    winFlushEvents();
    return (1);
}


WININT int __winPollEvents(void) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
	
    /* xlib references */
	Display *dpy = __window_h.x11->xlib.dpy; 
    
    XEvent xevent = { 0 };
    while (XPending(__window_h.x11->xlib.dpy)) {
        XNextEvent(__window_h.x11->xlib.dpy, &xevent);
        
        switch (xevent.type) {
            case (ClientMessage): {
                if (xevent.xclient.message_type == __window_h.x11->xatom.wm_protocols) {
                    const Atom data = xevent.xclient.data.l[0];

                    if (data == __window_h.x11->xatom.wm_delete_window) {
                        t_eventQuit event = (t_eventQuit) {
                            .type = WINDOW_EVENT_QUIT,
                            .timestamp = winGetTime()
                        };
                        winPushEvent((t_event *) &event);
                    }
                }
            } break;

            case (MotionNotify): {
                t_eventMouseMotion event = (t_eventMouseMotion) {
                    .type = WINDOW_EVENT_MOUSE_MOTION,
                    .timestamp = winGetTime(),
                    .x = xevent.xmotion.x, .xrel = xevent.xmotion.x_root,
                    .y = xevent.xmotion.y, .yrel = xevent.xmotion.y_root,
                };
                winPushEvent((t_event *) &event);
            } break;

            case (ButtonPress):
            case (ButtonRelease): {
                uint8_t btn = 0;
                switch (xevent.xbutton.button) {
                    /* key press / relese */
                    case (1): { btn = WINDOW_BUTTON_LEFT;   } break; /* left */
                    case (2): { btn = WINDOW_BUTTON_MIDDLE; } break; /* middle */
                    case (3): { btn = WINDOW_BUTTON_RIGHT;  } break; /* right */

                    /* scroll up / down */
                    case (4): { btn = 4; } break; /* scroll up */
                    case (5): { btn = 5; } break; /* scroll down */
                }

                /* invalid button */
                if (btn == 0) { break; }

                /* mouse button presses / releases */
                else if (btn >= 1 && btn <= 3) {
                    uint8_t state = (xevent.type == ButtonPress) ? 1 : 0;

                    t_eventMouseButton event = (t_eventMouseButton) {
                        .type = WINDOW_EVENT_MOUSE_BUTTON,
                        .timestamp = winGetTime(),
                        .btn = btn,
                        .state = state
                    };
                    winPushEvent((t_event *) &event);
                }

                /* scroll up / down */
                else if (btn >= 4 && btn <= 5) {
                    if (xevent.type == ButtonRelease) { break; }

                    t_eventMouseScroll event = (t_eventMouseScroll) {
                        .type = WINDOW_EVENT_MOUSE_SCROLL,
                        .timestamp = winGetTime(),
                        .scroll = (btn == 4) ? 1 : -1
                    };
                    winPushEvent((t_event *) &event);
                }
            } break;

            case (KeyPress):
            case (KeyRelease): {
                int8_t  state = (xevent.type == KeyPress) ? 1 : 0;
                int64_t  x_kc = xevent.xkey.keycode;
                int64_t  x_ks = XkbKeycodeToKeysym(dpy, x_kc, 0, 0);

                /* get keycode */
                int32_t keycode = 0;
                for (size_t i = 0; __window_h_keymap[i].src; i++) {
                    if (x_ks == __window_h_keymap[i].src) {
                        keycode = __window_h_keymap[i].kc;
                        break;
                    }
                }

                /* get keysym */
                int32_t keysym = x_ks;

                t_eventKeyboardKey event = (t_eventKeyboardKey) {
                    .type = WINDOW_EVENT_KEYBOARD_KEY,
                    .timestamp = winGetTime(),
                    .keysym = keysym,
                    .keycode = keycode,
                    .state = state
                };
                winPushEvent((t_event *) &event);
            } break;
        }
    }

    /* success */
    return (1);
}

#  endif /* WINDOW_BACKEND_X11 */
#
#  /* WINDOW_BACKEND_WAYLAND - Unix Wayland implementation layer */
#  if defined (WINDOW_BACKEND_WAYLAND)
#   include <unistd.h>
#   include <sys/time.h>
#
#   include <wayland-util.h>
#   include <wayland-version.h>
#   include <wayland-client.h>
#   include <wayland-client-core.h>
#   include <wayland-client-protocol.h>

/* ... */

#  endif /* WINDOW_BACKEND_WAYLAND */
#
#  /* WINDOW_PLATFORM_WIN32 - Windows Win32 implementation layer */
#  if defined (WINDOW_PLATFORM_WIN32)
#   include <windows.h>

/* ... */

#  endif /* WINDOW_PLATFORM_WIN32 */
# endif /* WINDOW_IMPLEMENTATION */
#endif /* _window_h_ */
