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
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 for *nix platforms */
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
# elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__bsdi__) || defined (__DragonFly__) || defined (__MidnightBSD__)
#  define WINDOW_PLATFORM "bsd"
#  define WINDOW_PLATFORM_BSD 1
#  /* define default backend if none is defined */
#  if !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   define WINDOW_BACKEND_X11 1 /* by default window.h picks X11 for *nix platforms */
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
    WINDOW_KEY_NONE = 0,
# define WINDOW_KEY_NONE WINDOW_KEY_NONE

    WINDOW_KEY_ESCAPE = 0x100,
# define WINDOW_KEY_ESCAPE WINDOW_KEY_ESCAPE

    WINDOW_KEY_F1 = 0x101,
# define WINDOW_KEY_F1 WINDOW_KEY_F1

    WINDOW_KEY_F2 = 0x102,
# define WINDOW_KEY_F2 WINDOW_KEY_F2

    WINDOW_KEY_F3 = 0x103,
# define WINDOW_KEY_F3 WINDOW_KEY_F3

    WINDOW_KEY_F4 = 0x104,
# define WINDOW_KEY_F4 WINDOW_KEY_F4

    WINDOW_KEY_F5 = 0x105,
# define WINDOW_KEY_F5 WINDOW_KEY_F5

    WINDOW_KEY_F6 = 0x106,
# define WINDOW_KEY_F6 WINDOW_KEY_F6

    WINDOW_KEY_F7 = 0x107,
# define WINDOW_KEY_F7 WINDOW_KEY_F7

    WINDOW_KEY_F8 = 0x108,
# define WINDOW_KEY_F8 WINDOW_KEY_F8

    WINDOW_KEY_F9 = 0x109,
# define WINDOW_KEY_F9 WINDOW_KEY_F9

    WINDOW_KEY_F10 = 0x10A,
# define WINDOW_KEY_F10 WINDOW_KEY_F10

    WINDOW_KEY_F11 = 0x10B,
# define WINDOW_KEY_F11 WINDOW_KEY_F11

    WINDOW_KEY_F12 = 0x10C,
# define WINDOW_KEY_F12 WINDOW_KEY_F12

    WINDOW_KEY_GRAVE = 0x60,
# define WINDOW_KEY_GRAVE WINDOW_KEY_GRAVE

    WINDOW_KEY_ONE = 0x31,
# define WINDOW_KEY_ONE WINDOW_KEY_ONE

    WINDOW_KEY_TWO = 0x32,
# define WINDOW_KEY_TWO WINDOW_KEY_TWO

    WINDOW_KEY_THREE = 0x33,
# define WINDOW_KEY_THREE WINDOW_KEY_THREE

    WINDOW_KEY_FOUR = 0x34,
# define WINDOW_KEY_FOUR WINDOW_KEY_FOUR

    WINDOW_KEY_FIVE = 0x35,
# define WINDOW_KEY_FIVE WINDOW_KEY_FIVE

    WINDOW_KEY_SIX = 0x36,
# define WINDOW_KEY_SIX WINDOW_KEY_SIX

    WINDOW_KEY_SEVEN = 0x37,
# define WINDOW_KEY_SEVEN WINDOW_KEY_SEVEN

    WINDOW_KEY_EIGHT = 0x38,
# define WINDOW_KEY_EIGHT WINDOW_KEY_EIGHT

    WINDOW_KEY_NINE = 0x39,
# define WINDOW_KEY_NINE WINDOW_KEY_NINE

    WINDOW_KEY_ZERO = 0x30,
# define WINDOW_KEY_ZERO WINDOW_KEY_ZERO

    WINDOW_KEY_DASH = 0x2D,
# define WINDOW_KEY_DASH WINDOW_KEY_DASH

    WINDOW_KEY_EQUAL = 0x3D,
# define WINDOW_KEY_EQUAL WINDOW_KEY_EQUAL

    WINDOW_KEY_BACKSPACE = 0x08,
# define WINDOW_KEY_BACKSPACE WINDOW_KEY_BACKSPACE

    WINDOW_KEY_TAB = 0x09,
# define WINDOW_KEY_TAB WINDOW_KEY_TAB

    WINDOW_KEY_Q = 0x51,
# define WINDOW_KEY_Q WINDOW_KEY_Q

    WINDOW_KEY_W = 0x57,
# define WINDOW_KEY_W WINDOW_KEY_W

    WINDOW_KEY_E = 0x45,
# define WINDOW_KEY_E WINDOW_KEY_E

    WINDOW_KEY_R = 0x52,
# define WINDOW_KEY_R WINDOW_KEY_R

    WINDOW_KEY_T = 0x54,
# define WINDOW_KEY_T WINDOW_KEY_T

    WINDOW_KEY_Y = 0x59,
# define WINDOW_KEY_Y WINDOW_KEY_Y

    WINDOW_KEY_U = 0x55,
# define WINDOW_KEY_U WINDOW_KEY_U

    WINDOW_KEY_I = 0x49,
# define WINDOW_KEY_I WINDOW_KEY_I

    WINDOW_KEY_O = 0x4F,
# define WINDOW_KEY_O WINDOW_KEY_O

    WINDOW_KEY_P = 0x50,
# define WINDOW_KEY_P WINDOW_KEY_P

    WINDOW_KEY_OBRACE = 0x5B,
# define WINDOW_KEY_OBRACE WINDOW_KEY_OBRACE

    WINDOW_KEY_CBRACE = 0x5D,
# define WINDOW_KEY_CBRACE WINDOW_KEY_CBRACE

    WINDOW_KEY_CAPSLOCK = 0,
# define WINDOW_KEY_CAPSLOCK WINDOW_KEY_CAPSLOCK

    WINDOW_KEY_A = 0x41,
# define WINDOW_KEY_A WINDOW_KEY_A

    WINDOW_KEY_S = 0x53,
# define WINDOW_KEY_S WINDOW_KEY_S

    WINDOW_KEY_D = 0x44,
# define WINDOW_KEY_D WINDOW_KEY_D

    WINDOW_KEY_F = 0x46,
# define WINDOW_KEY_F WINDOW_KEY_F

    WINDOW_KEY_G = 0x47,
# define WINDOW_KEY_G WINDOW_KEY_G

    WINDOW_KEY_H = 0x48,
# define WINDOW_KEY_H WINDOW_KEY_H

    WINDOW_KEY_J = 0x4A,
# define WINDOW_KEY_J WINDOW_KEY_J

    WINDOW_KEY_K = 0x4B,
# define WINDOW_KEY_K WINDOW_KEY_K

    WINDOW_KEY_L = 0x4C,
# define WINDOW_KEY_L WINDOW_KEY_L

    WINDOW_KEY_SEMICOLON = 0x3B,
# define WINDOW_KEY_SEMICOLON WINDOW_KEY_SEMICOLON

    WINDOW_KEY_QUOTE = 0x27,
# define WINDOW_KEY_QUOTE WINDOW_KEY_QUOTE

    WINDOW_KEY_BACKSLASH = 0x5C,
# define WINDOW_KEY_BACKSLASH WINDOW_KEY_BACKSLASH

    WINDOW_KEY_ENTER = 0x0D,
# define WINDOW_KEY_ENTER WINDOW_KEY_ENTER

    WINDOW_KEY_LSHIFT = 0x120,
# define WINDOW_KEY_LSHIFT WINDOW_KEY_LSHIFT

    WINDOW_KEY_Z = 0x5A,
# define WINDOW_KEY_Z WINDOW_KEY_Z

    WINDOW_KEY_X = 0x58,
# define WINDOW_KEY_X WINDOW_KEY_X

    WINDOW_KEY_C = 0x43,
# define WINDOW_KEY_C WINDOW_KEY_C

    WINDOW_KEY_V = 0x56,
# define WINDOW_KEY_V WINDOW_KEY_V

    WINDOW_KEY_B = 0x42,
# define WINDOW_KEY_B WINDOW_KEY_B

    WINDOW_KEY_N = 0x4E,
# define WINDOW_KEY_N WINDOW_KEY_N

    WINDOW_KEY_M = 0x4D,
# define WINDOW_KEY_M WINDOW_KEY_M

    WINDOW_KEY_COMMA = 0x2C,
# define WINDOW_KEY_COMMA WINDOW_KEY_COMMA

    WINDOW_KEY_PERIOD = 0x2E,
# define WINDOW_KEY_PERIOD WINDOW_KEY_PERIOD

    WINDOW_KEY_SLASH = 0x2F,
# define WINDOW_KEY_SLASH WINDOW_KEY_SLASH

    WINDOW_KEY_RSHIFT = 0x121,
# define WINDOW_KEY_RSHIFT WINDOW_KEY_RSHIFT

    WINDOW_KEY_LCTRL = 0x122,
# define WINDOW_KEY_LCTRL WINDOW_KEY_LCTRL

    WINDOW_KEY_MOD = 0x123,
# define WINDOW_KEY_MOD WINDOW_KEY_MOD

    WINDOW_KEY_LALT = 0x124,
# define WINDOW_KEY_LALT WINDOW_KEY_LALT

    WINDOW_KEY_SPACE = 0x20,
# define WINDOW_KEY_SPACE WINDOW_KEY_SPACE

    WINDOW_KEY_RALT = 0x125,
# define WINDOW_KEY_RALT WINDOW_KEY_RALT

    WINDOW_KEY_RCTRL = 0x126,
# define WINDOW_KEY_RCTRL WINDOW_KEY_RCTRL

    WINDOW_KEY_PRINTSCREEN = 0x127,
# define WINDOW_KEY_PRINTSCREEN WINDOW_KEY_PRINTSCREEN

    WINDOW_KEY_SCROLLLOCK = 0x128,
# define WINDOW_KEY_SCROLLLOCK WINDOW_KEY_SCROLLLOCK

    WINDOW_KEY_PAUSE = 0x129,
# define WINDOW_KEY_PAUSE WINDOW_KEY_PAUSE

    WINDOW_KEY_INSERT = 0x144,
# define WINDOW_KEY_INSERT WINDOW_KEY_INSERT

    WINDOW_KEY_HOME = 0x145,
# define WINDOW_KEY_HOME WINDOW_KEY_HOME

    WINDOW_KEY_PAGEUP = 0x146,
# define WINDOW_KEY_PAGEUP WINDOW_KEY_PAGEUP

    WINDOW_KEY_DELETE = 0x147,
# define WINDOW_KEY_DELETE WINDOW_KEY_DELETE

    WINDOW_KEY_END = 0x148,
# define WINDOW_KEY_END WINDOW_KEY_END

    WINDOW_KEY_PAGEDOWN = 0x149,
# define WINDOW_KEY_PAGEDOWN WINDOW_KEY_PAGEDOWN

    WINDOW_KEY_UP = 0x140,
# define WINDOW_KEY_UP WINDOW_KEY_UP

    WINDOW_KEY_LEFT = 0x141,
# define WINDOW_KEY_LEFT WINDOW_KEY_LEFT

    WINDOW_KEY_DOWN = 0x142,
# define WINDOW_KEY_DOWN WINDOW_KEY_DOWN

    WINDOW_KEY_RIGHT = 0x143,
# define WINDOW_KEY_RIGHT WINDOW_KEY_RIGHT

    WINDOW_KEY_NUMLOCK = 0x12A,
# define WINDOW_KEY_NUMLOCK WINDOW_KEY_NUMLOCK

    WINDOW_KEY_NUMSLASH = 0x16A,
# define WINDOW_KEY_NUMSLASH WINDOW_KEY_NUMSLASH

    WINDOW_KEY_NUMSTAR = 0x16B,
# define WINDOW_KEY_NUMSTAR WINDOW_KEY_NUMSTAR

    WINDOW_KEY_NUMDASH = 0x16C,
# define WINDOW_KEY_NUMDASH WINDOW_KEY_NUMDASH

    WINDOW_KEY_NUM7 = 0x167,
# define WINDOW_KEY_NUM7 WINDOW_KEY_NUM7

    WINDOW_KEY_NUM8 = 0x168,
# define WINDOW_KEY_NUM8 WINDOW_KEY_NUM8

    WINDOW_KEY_NUM9 = 0x169,
# define WINDOW_KEY_NUM9 WINDOW_KEY_NUM9

    WINDOW_KEY_NUM4 = 0x164,
# define WINDOW_KEY_NUM4 WINDOW_KEY_NUM4

    WINDOW_KEY_NUM5 = 0x165,
# define WINDOW_KEY_NUM5 WINDOW_KEY_NUM5

    WINDOW_KEY_NUM6 = 0x166,
# define WINDOW_KEY_NUM6 WINDOW_KEY_NUM6

    WINDOW_KEY_NUM1 = 0x161,
# define WINDOW_KEY_NUM1 WINDOW_KEY_NUM1

    WINDOW_KEY_NUM2 = 0x162,
# define WINDOW_KEY_NUM2 WINDOW_KEY_NUM2

    WINDOW_KEY_NUM3 = 0x163,
# define WINDOW_KEY_NUM3 WINDOW_KEY_NUM3

    WINDOW_KEY_NUM0 = 0x160,
# define WINDOW_KEY_NUM0 WINDOW_KEY_NUM0

    WINDOW_KEY_NUMSEP = 0x16D,
# define WINDOW_KEY_NUMSEP WINDOW_KEY_NUMSEP

    WINDOW_KEY_NUMPLUS = 0x16E,
# define WINDOW_KEY_NUMPLUS WINDOW_KEY_NUMPLUS

    WINDOW_KEY_NUMENTER = 0x16F,
# define WINDOW_KEY_NUMENTER WINDOW_KEY_NUMENTER

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
    
    WINDOW_FLAG_TRANSPARENT = 0x00000020,
# define WINDOW_FLAG_TRANSPARENT WINDOW_FLAG_TRANSPARENT
    
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

    int32_t key;
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

    /* ... */

};


typedef struct s_glcontext_egl *t_glcontext_egl;

struct s_glcontext {

    /* platform-independent */

    /* ... */

    /* platform-specific */

    t_glcontext_egl egl;

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

/* platform type definitions */

struct s_keymap {
    uint32_t src;
    uint32_t dst;
};

static const struct s_keymap g_keymap[] = {
    
    { XK_Escape, WINDOW_KEY_ESCAPE },
    
    { XK_F1, WINDOW_KEY_F1 },
    
    { XK_F2, WINDOW_KEY_F2 },
    
    { XK_F3, WINDOW_KEY_F3 },
    
    { XK_F4, WINDOW_KEY_F4 },
    
    { XK_F5, WINDOW_KEY_F5 },
    
    { XK_F6, WINDOW_KEY_F6 },
    
    { XK_F7, WINDOW_KEY_F7 },
    
    { XK_F8, WINDOW_KEY_F8 },
    
    { XK_F9, WINDOW_KEY_F9 },
    
    { XK_F10, WINDOW_KEY_F10 },
    
    { XK_F11, WINDOW_KEY_F11 },
    
    { XK_F12, WINDOW_KEY_F12 },
    
    { XK_grave, WINDOW_KEY_GRAVE }, 
    { XK_asciitilde, WINDOW_KEY_GRAVE },
    
    { XK_1, WINDOW_KEY_ONE },       
    { XK_exclam, WINDOW_KEY_ONE },
    
    { XK_2, WINDOW_KEY_TWO },       
    { XK_at, WINDOW_KEY_TWO },
    
    { XK_3, WINDOW_KEY_THREE },     
    { XK_numbersign, WINDOW_KEY_THREE },
    
    { XK_4, WINDOW_KEY_FOUR },      
    { XK_dollar, WINDOW_KEY_FOUR },
    
    { XK_5, WINDOW_KEY_FIVE },      
    { XK_percent, WINDOW_KEY_FIVE },
    
    { XK_6, WINDOW_KEY_SIX },       
    { XK_asciicircum, WINDOW_KEY_SIX },
    
    { XK_7, WINDOW_KEY_SEVEN },     
    { XK_ampersand, WINDOW_KEY_SEVEN },
    
    { XK_8, WINDOW_KEY_EIGHT },     
    { XK_asterisk, WINDOW_KEY_EIGHT },
    
    { XK_9, WINDOW_KEY_NINE },      
    { XK_parenleft, WINDOW_KEY_NINE },
    
    { XK_0, WINDOW_KEY_ZERO },      
    { XK_parenright, WINDOW_KEY_ZERO },
    
    { XK_minus, WINDOW_KEY_DASH },  
    { XK_underscore, WINDOW_KEY_DASH },
    
    { XK_equal, WINDOW_KEY_EQUAL },
    { XK_plus, WINDOW_KEY_EQUAL },
    
    { XK_BackSpace, WINDOW_KEY_BACKSPACE },
    
    { XK_Tab, WINDOW_KEY_TAB },
    
    { XK_Q, WINDOW_KEY_Q },
    { XK_q, WINDOW_KEY_Q },
    
    { XK_W, WINDOW_KEY_W },
    { XK_w, WINDOW_KEY_W },
    
    { XK_E, WINDOW_KEY_E },
    { XK_e, WINDOW_KEY_E },
    
    { XK_R, WINDOW_KEY_R },
    { XK_r, WINDOW_KEY_R },
    
    { XK_T, WINDOW_KEY_T },
    { XK_t, WINDOW_KEY_T },
    
    { XK_Y, WINDOW_KEY_Y },
    { XK_y, WINDOW_KEY_Y },
    
    { XK_U, WINDOW_KEY_U },
    { XK_u, WINDOW_KEY_U },
    
    { XK_I, WINDOW_KEY_I },
    { XK_i, WINDOW_KEY_I },
    
    { XK_O, WINDOW_KEY_O },
    { XK_o, WINDOW_KEY_O },
    
    { XK_P, WINDOW_KEY_P },
    { XK_p, WINDOW_KEY_P },
    
    { XK_bracketleft, WINDOW_KEY_OBRACE },
    { XK_braceleft, WINDOW_KEY_OBRACE },
    
    { XK_bracketright, WINDOW_KEY_CBRACE },
    { XK_braceright, WINDOW_KEY_CBRACE },

    { XK_Caps_Lock, WINDOW_KEY_CAPSLOCK },

    { XK_A, WINDOW_KEY_A },
    { XK_a, WINDOW_KEY_A },

    { XK_S, WINDOW_KEY_S },
    { XK_s, WINDOW_KEY_S },

    { XK_D, WINDOW_KEY_D },
    { XK_d, WINDOW_KEY_D },

    { XK_F, WINDOW_KEY_F },
    { XK_f, WINDOW_KEY_F },

    { XK_G, WINDOW_KEY_G },
    { XK_g, WINDOW_KEY_G },

    { XK_H, WINDOW_KEY_H },
    { XK_h, WINDOW_KEY_H },

    { XK_J, WINDOW_KEY_J },
    { XK_j, WINDOW_KEY_J },

    { XK_K, WINDOW_KEY_K },
    { XK_k, WINDOW_KEY_K },

    { XK_L, WINDOW_KEY_L },
    { XK_l, WINDOW_KEY_L },

    { XK_semicolon, WINDOW_KEY_SEMICOLON },
    { XK_colon, WINDOW_KEY_SEMICOLON },

    { XK_apostrophe, WINDOW_KEY_QUOTE },
    { XK_quotedbl, WINDOW_KEY_QUOTE },

    { XK_backslash, WINDOW_KEY_BACKSLASH },
    { XK_bar, WINDOW_KEY_BACKSLASH },

    { XK_Return, WINDOW_KEY_ENTER },

    { XK_Shift_L, WINDOW_KEY_LSHIFT },
    
    { XK_Z, WINDOW_KEY_Z },
    { XK_z, WINDOW_KEY_Z },
    
    { XK_X, WINDOW_KEY_X },
    { XK_x, WINDOW_KEY_X },
    
    { XK_C, WINDOW_KEY_C },
    { XK_c, WINDOW_KEY_C },
    
    { XK_V, WINDOW_KEY_V },
    { XK_v, WINDOW_KEY_V },
    
    { XK_B, WINDOW_KEY_B },
    { XK_b, WINDOW_KEY_B },
    
    { XK_N, WINDOW_KEY_N },
    { XK_n, WINDOW_KEY_N },
    
    { XK_M, WINDOW_KEY_M },
    { XK_m, WINDOW_KEY_M },
    
    { XK_comma, WINDOW_KEY_COMMA },
    { XK_less, WINDOW_KEY_COMMA },
    
    { XK_period, WINDOW_KEY_PERIOD },
    { XK_greater, WINDOW_KEY_PERIOD },
    
    { XK_slash, WINDOW_KEY_SLASH },
    { XK_question, WINDOW_KEY_SLASH },
    
    { XK_Shift_R, WINDOW_KEY_RSHIFT },
    
    { XK_Control_L, WINDOW_KEY_LCTRL },
    
    { XK_Super_L, WINDOW_KEY_MOD },
    
    { XK_Alt_L, WINDOW_KEY_LALT },
    
    { XK_space, WINDOW_KEY_SPACE },
    
    { XK_Alt_R, WINDOW_KEY_RALT },
    
    { XK_Control_R, WINDOW_KEY_RCTRL },

    { XK_Print, WINDOW_KEY_PRINTSCREEN },
    
    { XK_Scroll_Lock, WINDOW_KEY_SCROLLLOCK },
    
    { XK_Pause, WINDOW_KEY_PAUSE },

    { XK_Insert, WINDOW_KEY_INSERT },
    
    { XK_Home, WINDOW_KEY_HOME },
    
    { XK_Prior, WINDOW_KEY_PAGEUP },

    { XK_Delete, WINDOW_KEY_DELETE },
    
    { XK_End, WINDOW_KEY_END },
    
    { XK_Next, WINDOW_KEY_PAGEDOWN },

    { XK_Up, WINDOW_KEY_UP },
    
    { XK_Left, WINDOW_KEY_LEFT },
    
    { XK_Down, WINDOW_KEY_DOWN },
    
    { XK_Right, WINDOW_KEY_RIGHT },

    { XK_Num_Lock, WINDOW_KEY_NUMLOCK },
    
    { XK_KP_Divide, WINDOW_KEY_NUMSLASH },
    
    { XK_KP_Multiply, WINDOW_KEY_NUMSTAR },
    
    { XK_KP_Subtract, WINDOW_KEY_NUMDASH },
    
    { XK_KP_Home, WINDOW_KEY_NUM7 },
    { XK_KP_7, WINDOW_KEY_NUM7 },
    
    { XK_KP_Up, WINDOW_KEY_NUM8 },
    { XK_KP_8, WINDOW_KEY_NUM8 },
    
    { XK_KP_Prior, WINDOW_KEY_NUM9 },
    { XK_KP_9, WINDOW_KEY_NUM9 },
    
    { XK_KP_Left, WINDOW_KEY_NUM4 },
    { XK_KP_4, WINDOW_KEY_NUM4 },
    
    { XK_KP_Begin, WINDOW_KEY_NUM5 },
    { XK_KP_5, WINDOW_KEY_NUM5 },
    
    { XK_KP_Right, WINDOW_KEY_NUM6 },
    { XK_KP_6, WINDOW_KEY_NUM6 },
    
    { XK_KP_End, WINDOW_KEY_NUM1 },
    { XK_KP_1, WINDOW_KEY_NUM1 },
    
    { XK_KP_Down, WINDOW_KEY_NUM2 },
    { XK_KP_2, WINDOW_KEY_NUM2 },
    
    { XK_KP_Next, WINDOW_KEY_NUM3 },
    { XK_KP_3, WINDOW_KEY_NUM3 },
    
    { XK_KP_Insert, WINDOW_KEY_NUM0 },
    { XK_KP_0, WINDOW_KEY_NUM0 },
    
    { XK_KP_Delete, WINDOW_KEY_NUMSEP },
    
    { XK_KP_Add, WINDOW_KEY_NUMPLUS },
    
    { XK_KP_Enter, WINDOW_KEY_NUMENTER },

    /* ... */

    { 0, WINDOW_KEY_NONE }
};

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
typedef Status (* PFN_XMatchVisualInfo_PROC) (Display *, int, int, int, XVisualInfo *);
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
#   define XMatchVisualInfo __window_h.x11->MatchVisualInfo
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
        Atom _net_wm_window_opacity;
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
    PFN_XMatchVisualInfo_PROC MatchVisualInfo;
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

/* platform functions */

WININT int __winLoadX11(void);

WINDEF int winInit(void) {
    /* initialize '__window_h' object */
    __window_h = (struct __window_h) { 0 };

    /* allocate '__window_h.x11' field */
    __window_h.x11 = calloc(1, sizeof(struct __window_h_x11));
    if (!__window_h.x11) { return (0); }

    /* load libX11 library */
    if (!__winLoadX11()) { return (0); }

    /* initialize '__window_h.x11' members */
    Display *dpy = XOpenDisplay(0);
    if (!dpy) { return (0); }

    Window root = DefaultRootWindow(dpy);
    if (!root) { return (0); }

    /* set '__window_h.x11->xlib' members */ 
    __window_h.x11->xlib.dpy  = dpy;
    __window_h.x11->xlib.root = root;
    
    /* get X11 atoms */ 
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

    Atom _net_wm_window_opacity = XInternAtom(dpy, "_NET_WM_WINDOW_OPACITY", False);
    if (!_net_wm_window_opacity) { return (0); }

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
    __window_h.x11->xatom._net_wm_window_opacity = _net_wm_window_opacity;
    
    /* set keyboard input repeating */
    Bool supported;
    XkbSetDetectableAutoRepeat(dpy, True, &supported);
    if (!supported) { return (0); }

    /* success */
    winFlushEvents();
    return (1);
}

WININT int __winLoadX11(void) {
    const char *names[] = { "libX11.so", "libX11.so.6", 0 };

    /* try to load handle */
    static void *handle = 0;
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

    XMatchVisualInfo = (PFN_XMatchVisualInfo_PROC) dlsym(handle, "XMatchVisualInfo");
    if (!XMatchVisualInfo) { return (0); }

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


WININT int __winUnloadX11(void);

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

    /* release x11 symbols */
    if (!__winUnloadX11()) { return (0); }
    
    /* release x11 */
    free(__window_h.x11), __window_h.x11 = 0;
    
    /* success */
    return (1);
}

WININT int __winUnloadX11(void) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    dlclose(__window_h.x11->handle), __window_h.x11->handle = 0;

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

WININT int __winCreateWindowX11(t_window, Display *, Window, Window, const size_t, const size_t);

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

WININT int __winCreateWindowX11(t_window win, Display *dpy, Window root, Window parent, const size_t w, const size_t h) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* allocate 'win->x11' field */
    win->x11 = calloc(1, sizeof (struct s_window_x11));
    if (!win->x11) { return (0); }

    /* get screen index */
    int screen = DefaultScreen(dpy);

    /* create visual info */
    XVisualInfo visual_info = { 0 };
    if (!XMatchVisualInfo(dpy, screen, 24, TrueColor, &visual_info)) {
        return (0);
    }

    int      depth = visual_info.depth;
    Visual *visual = visual_info.visual;

    /* create XSetWindowAttributes */
    XSetWindowAttributes attr = { 0 };
    attr.colormap = XCreateColormap(dpy, root, visual_info.visual, AllocNone);
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


WININT int __winUpdateWindowFlagsX11(t_window);

WINDEF int winSetWindowFlag(t_window win, const uint32_t f) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
   
    /* set flags */
    win->flags = f;
    __winUpdateWindowFlagsX11(win);

    /* success */
    return (1);
}

WININT int __winSendClientEventX11(t_window, Atom, Atom, Atom);

WININT int __winUpdateWindowFlagsX11(t_window win) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    
    /* xatom references */
    Atom     _NET_WM_STATE_FULLSCREEN = __window_h.x11->xatom._net_wm_state_fullscreen;
    Atom         _NET_WM_STATE_HIDDEN = __window_h.x11->xatom._net_wm_state_hidden;
    Atom _NET_WM_STATE_MAXIMIZED_HORZ = __window_h.x11->xatom._net_wm_state_maximized_horz;
    Atom _NET_WM_STATE_MAXIMIZED_VERT = __window_h.x11->xatom._net_wm_state_maximized_vert;
    Atom          _NET_WM_STATE_ABOVE = __window_h.x11->xatom._net_wm_state_above;
    
    /* properties that requires the window to be mapped */
    if (win->mapped) {
        /* WINDOW_FLAG_FULLSCREEN */
        if (win->flags & WINDOW_FLAG_FULLSCREEN) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_FULLSCREEN, 0);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_FULLSCREEN, 0);
        }

        /* WINDOW_FLAG_MINIMIZED */
        if (win->flags & WINDOW_FLAG_MINIMIZED) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_HIDDEN, 0);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_HIDDEN, 0);
        }

        /* WINDOW_FLAG_MAXIMIZED */
        if (win->flags & WINDOW_FLAG_MAXIMIZED) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_MAXIMIZED_HORZ, _NET_WM_STATE_MAXIMIZED_VERT);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_MAXIMIZED_HORZ, _NET_WM_STATE_MAXIMIZED_VERT);
        }

        /* WINDOW_FLAG_TOPMOST */
        if (win->flags & WINDOW_FLAG_TOPMOST) {
            __winSendClientEventX11(win, _NET_WM_STATE_ADD, _NET_WM_STATE_ABOVE, 0);
        } else {
            __winSendClientEventX11(win, _NET_WM_STATE_REMOVE, _NET_WM_STATE_ABOVE, 0);
        }
    }
    
    /* properties that doesn't require the window to be mapped */
    
    /* WINDOW_FLAG_RESIZABLE */
    if (win->flags & WINDOW_FLAG_RESIZABLE) {
        winSetWindowMinSize(win, 1, 1);
        winSetWindowMaxSize(win, 0x10000000, 0x10000000);
    } else {
        size_t w = 0,
               h = 0;
        winGetWindowSize(win, &w, &h);
        winSetWindowMinSize(win, w, h);
        winSetWindowMaxSize(win, w, h);
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

/* event functions */

WININT int __winPollEvents(void);

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
    
WININT int __winPollEvents(void) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    
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
                uint8_t  state   = (xevent.type == KeyPress) ? 1 : 0;
                uint64_t keycode = xevent.xkey.keycode;
                uint64_t keysym  = XkbKeycodeToKeysym(__window_h.x11->xlib.dpy, keycode, 0, state);

                uint32_t key = 0;
                for (size_t i = 0; g_keymap[i].src; i++) {
                    if (keysym == g_keymap[i].src) {
                        key = g_keymap[i].dst;
                        break;
                    }
                }

                /* invalid button */
                if (key == 0) { break; }

                t_eventKeyboardKey event = (t_eventKeyboardKey) {
                    .type = WINDOW_EVENT_KEYBOARD_KEY,
                    .timestamp = winGetTime(),
                    .key = key,
                    .state = state
                };
                winPushEvent((t_event *) &event);
            } break;
        }
    }

    /* success */
    return (1);
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
