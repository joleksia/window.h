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

    WINDOW_EVENT_QUIT = 0x1000,
# define WINDOW_EVENT_QUIT WINDOW_EVENT_QUIT

    WINDOW_EVENT_MOUSE_MOTION = 0x2000,
# define WINDOW_EVENT_MOUSE_MOTION WINDOW_EVENT_MOUSE_MOTION

    WINDOW_EVENT_MOUSE_BUTTON,
# define WINDOW_EVENT_MOUSE_BUTTON WINDOW_EVENT_MOUSE_BUTTON

    WINDOW_EVENT_MOUSE_SCROLL,
# define WINDOW_EVENT_MOUSE_SCROLL WINDOW_EVENT_MOUSE_SCROLL

    WINDOW_EVENT_MOUSE_ADDED,
# define WINDOW_EVENT_MOUSE_ADDED WINDOW_EVENT_MOUSE_ADDED

    WINDOW_EVENT_MOUSE_REMOVED,
# define WINDOW_EVENT_MOUSE_REMOVED WINDOW_EVENT_MOUSE_REMOVED

    WINDOW_EVENT_KEYBOARD_KEY = 0x3000,
# define WINDOW_EVENT_KEYBOARD_KEY WINDOW_EVENT_KEYBOARD_KEY

    WINDOW_EVENT_KEYBOARD_ADDED,
# define WINDOW_EVENT_KEYBOARD_ADDED WINDOW_EVENT_KEYBOARD_ADDED

    WINDOW_EVENT_KEYBOARD_REMOVED,
# define WINDOW_EVENT_KEYBOARD_REMOVED WINDOW_EVENT_KEYBOARD_REMOVED

    WINDOW_EVENT_WINDOW_CREATE = 0x4000,
# define WINDOW_EVENT_WINDOW_CREATE WINDOW_EVENT_WINDOW_CREATE
    
    WINDOW_EVENT_WINDOW_DESTROY,
# define WINDOW_EVENT_WINDOW_DESTROY WINDOW_EVENT_WINDOW_DESTROY

    WINDOW_EVENT_WINDOW_MAP,
# define WINDOW_EVENT_WINDOW_MAPPED WINDOW_EVENT_WINDOW_MAPPED

    WINDOW_EVENT_WINDOW_UNMAP,
# define WINDOW_EVENT_WINDOW_UNMAPPED WINDOW_EVENT_WINDOW_UNMAPPED

    WINDOW_EVENT_WINDOW_RESIZE,
# define WINDOW_EVENT_WINDOW_RESIZE WINDOW_EVENT_WINDOW_RESIZE

    WINDOW_EVENT_WINDOW_MOTION,
# define WINDOW_EVENT_WINDOW_MOTION WINDOW_EVENT_WINDOW_MOTION
    
    WINDOW_EVENT_WINDOW_ENTER,
# define WINDOW_EVENT_WINDOW_ENTER WINDOW_EVENT_WINDOW_ENTER
    
    WINDOW_EVENT_WINDOW_LEAVE,
# define WINDOW_EVENT_WINDOW_LEAVE WINDOW_EVENT_WINDOW_LEAVE
    
    WINDOW_EVENT_WINDOW_MAXIMIZE,
# define WINDOW_EVENT_WINDOW_MAXIMIZE WINDOW_EVENT_WINDOW_MAXIMIZE
    
    WINDOW_EVENT_WINDOW_MINIMIZE,
# define WINDOW_EVENT_WINDOW_MINIMIZE WINDOW_EVENT_WINDOW_MINIMIZE

    /* ... */

    WINDOW_EVENT_USER = 0xf000,
# define WINDOW_EVENT_USER WINDOW_EVENT_USER

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

    WINDOW_GL_CONTEXT_PROFILE_MASK,
# define WINDOW_GL_CONTEXT_PROFILE_MASK WINDOW_GL_CONTEXT_PROFILE_MASK

    WINDOW_GL_CONTEXT_DEBUG,
# define WINDOW_GL_CONTEXT_DEBUG WINDOW_GL_CONTEXT_DEBUG

    /* ... */
};


typedef struct s_window *t_window;


typedef struct s_glcontext *t_glcontext;


typedef struct s_eventCommon t_eventCommon;

struct s_eventCommon {
    uint32_t type;
    uint64_t time;
};


typedef struct s_eventQuit t_eventQuit;

struct s_eventQuit {
    uint32_t type;
    uint64_t time;
};


typedef struct s_eventMouse t_eventMouse;

struct s_eventMouse {
    uint32_t type;      /* WINDOW_EVENT_MOUSE_ */
    uint64_t time;      /* event timestampt */

    t_window window;    /* window with mouse focus (if any) */
    uint64_t which;     /* mouse instance ID (if any) */ 

    /* WINDOW_EVENT_MOUSE_MOTION */
    int32_t x, xrel;    /* absolute and relative X position */
    int32_t y, yrel;    /* absolute and relative Y position */

    /* WINDOW_EVENT_MOUSE_BUTTON */
    uint8_t btn;        /* */
    uint8_t state;      /* input state (1.: PRESS, 0.: RELEASE) */

    /* WINDOW_EVENT_MOUSE_SCROLL */
    int32_t scroll_x;   /* Horizontal scroll (scroll_x < 0: LEFT, scroll_x > 0: RIGHT) */
    int32_t scroll_y;   /* Vertical scroll (scroll_y < 0: UP, scroll_y > 0: DOWN) */
};


typedef struct s_eventMouseDevice t_eventMouseDevice;

struct s_eventMouseDevice {
    uint32_t type;      /* WINDOW_EVENT_MOUSE_ADD, WINDOW_EVENT_MOUSE_REMOVE */
    uint64_t time;      /* event timestampt */

    uint64_t which;     /* mouse instance ID */ 
};


typedef struct s_eventKeyboard t_eventKeyboard;

struct s_eventKeyboard {
    uint32_t type;      /* WINDOW_EVENT_KEYBOARD_ */
    uint64_t time;      /* event timestampt */

    t_window window;    /* window with keyboard focus (if any) */
    uint64_t which;     /* keyboard instance ID */ 
    uint32_t keysym;    /* symbolic window.h keyboard key */
    uint32_t keycode;   /* physical window.h keyboard key */
    uint32_t keymod;    /* window.h current modifier key */
    uint32_t keyraw;    /* platform-specific raw input */
    uint8_t  state;     /* input state (1.: PRESS, 0.: RELEASE) */
    uint8_t  repeat;    /* key repeat state (1.: REPEATING) */
};


typedef struct s_eventKeyboardDevice t_eventKeyboardDevice;

struct s_eventKeyboardDevice {
    uint32_t type;      /* WINDOW_EVENT_KEYBOARD_ADD, WINDOW_EVENT_KEYBOARD_REMOVE */
    uint64_t time;      /* event timestampt */

    uint64_t which;     /* keyboard instance ID */ 
};


typedef struct s_eventWindow t_eventWindow;

struct s_eventWindow {
    uint32_t type;      /* WINDOW_EVENT_WINDOW_ */
    uint64_t time;      /* event timestampt */

    t_window window;    /* which window sends the event */
    uint32_t data1;
    uint32_t data2;
};


typedef union u_event t_event;

union u_event {
    /* default event data */
    struct {
        uint32_t type;  /* WINDOW_EVENT_ */
        uint64_t time;  /* event timestamp */
    };

    /* WINDOW_EVENT_QUIT */
    t_eventQuit quit;

    /* WINDOW_EVENT_MOUSE_ */
    t_eventMouse mouse;

    /* WINDOW_EVENT_MOUSE_ADD, WINDOW_EVENT_MOUSE_REMOVE */
    t_eventMouseDevice mouse_device;

    /* WINDOW_EVENT_KEYBOARD_ */
    t_eventKeyboard keyboard;

    /* WINDOW_EVENT_KEYBOARD_ADD, WINDOW_EVENT_KEYBOARD_REMOVE */
    t_eventKeyboardDevice keyboard_device;

    /* WINDOW_EVENT_WINDOW_ */
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

WINDEF int winGetWindowFlags(t_window, uint32_t *);

WINDEF int winSetWindowFlags(t_window, const uint32_t);

WINDEF int winToggleWindowFlags(t_window, const uint32_t);

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
#  include <stdarg.h> 
#  include <assert.h>
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

#  /* WINDOW_BACKEND_X11 - X11 implementation */
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

/* libX11: Xlib.h */

typedef int (* PFN_XActivateScreenSaver_PROC) (Display *);
PFN_XActivateScreenSaver_PROC XActivateScreenSaver_PROC = 0;
#   define XActivateScreenSaver (assert(XActivateScreenSaver_PROC != 0), XActivateScreenSaver_PROC)

typedef int (* PFN_XAddConnectionWatch_PROC) (Display *, XConnectionWatchProc, XPointer);
PFN_XAddConnectionWatch_PROC XAddConnectionWatch_PROC = 0;
#   define XAddConnectionWatch (assert(XAddConnectionWatch_PROC != 0), XAddConnectionWatch_PROC)

typedef XExtCodes *(* PFN_XAddExtension_PROC) (Display *);
PFN_XAddExtension_PROC XAddExtension_PROC = 0;
#   define XAddExtension (assert(XAddExtension_PROC != 0), XAddExtension_PROC)

typedef int (* PFN_XAddHost_PROC) (Display *, XHostAddress *);
PFN_XAddHost_PROC XAddHost_PROC = 0;
#   define XAddHost (assert(XAddHost_PROC != 0), XAddHost_PROC)

typedef int (* PFN_XAddHosts_PROC) (Display *, XHostAddress *, int);
PFN_XAddHosts_PROC XAddHosts_PROC = 0;
#   define XAddHosts (assert(XAddHosts_PROC != 0), XAddHosts_PROC)

typedef int (* PFN_XAddToExtensionList_PROC) (struct _XExtData **, XExtData *);
PFN_XAddToExtensionList_PROC XAddToExtensionList_PROC = 0;
#   define XAddToExtensionList (assert(XAddToExtensionList_PROC != 0), XAddToExtensionList_PROC)

typedef int (* PFN_XAddToSaveSet_PROC) (Display *, Window);
PFN_XAddToSaveSet_PROC XAddToSaveSet_PROC = 0;
#   define XAddToSaveSet (assert(XAddToSaveSet_PROC != 0), XAddToSaveSet_PROC)

typedef unsigned long (* PFN_XAllPlanes_PROC) (void);
PFN_XAllPlanes_PROC XAllPlanes_PROC = 0;
#   define XAllPlanes (assert(XAllPlanes_PROC != 0), XAllPlanes_PROC)

typedef int (* PFN_XAllocColor_PROC) (Display *, Colormap, XColor *);
PFN_XAllocColor_PROC XAllocColor_PROC = 0;
#   define XAllocColor (assert(XAllocColor_PROC != 0), XAllocColor_PROC)

typedef int (* PFN_XAllocColorCells_PROC) (Display *, Colormap, int, unsigned long *, unsigned int, unsigned long *, unsigned int);
PFN_XAllocColorCells_PROC XAllocColorCells_PROC = 0;
#   define XAllocColorCells (assert(XAllocColorCells_PROC != 0), XAllocColorCells_PROC)

typedef int (* PFN_XAllocColorPlanes_PROC) (Display *, Colormap, int, unsigned long *, int, int, int, int, unsigned long *, unsigned long *, unsigned long *);
PFN_XAllocColorPlanes_PROC XAllocColorPlanes_PROC = 0;
#   define XAllocColorPlanes (assert(XAllocColorPlanes_PROC != 0), XAllocColorPlanes_PROC)

typedef int (* PFN_XAllocNamedColor_PROC) (Display *, Colormap, const char *, XColor *, XColor *);
PFN_XAllocNamedColor_PROC XAllocNamedColor_PROC = 0;
#   define XAllocNamedColor (assert(XAllocNamedColor_PROC != 0), XAllocNamedColor_PROC)

typedef int (* PFN_XAllowEvents_PROC) (Display *, int, Time);
PFN_XAllowEvents_PROC XAllowEvents_PROC = 0;
#   define XAllowEvents (assert(XAllowEvents_PROC != 0), XAllowEvents_PROC)

typedef int (* PFN_XAutoRepeatOff_PROC) (Display *);
PFN_XAutoRepeatOff_PROC XAutoRepeatOff_PROC = 0;
#   define XAutoRepeatOff (assert(XAutoRepeatOff_PROC != 0), XAutoRepeatOff_PROC)

typedef int (* PFN_XAutoRepeatOn_PROC) (Display *);
PFN_XAutoRepeatOn_PROC XAutoRepeatOn_PROC = 0;
#   define XAutoRepeatOn (assert(XAutoRepeatOn_PROC != 0), XAutoRepeatOn_PROC)

typedef char *(* PFN_XBaseFontNameListOfFontSet_PROC) (XFontSet);
PFN_XBaseFontNameListOfFontSet_PROC XBaseFontNameListOfFontSet_PROC = 0;
#   define XBaseFontNameListOfFontSet (assert(XBaseFontNameListOfFontSet_PROC != 0), XBaseFontNameListOfFontSet_PROC)

typedef int (* PFN_XBell_PROC) (Display *, int);
PFN_XBell_PROC XBell_PROC = 0;
#   define XBell (assert(XBell_PROC != 0), XBell_PROC)

typedef int (* PFN_XBitmapBitOrder_PROC) (Display *);
PFN_XBitmapBitOrder_PROC XBitmapBitOrder_PROC = 0;
#   define XBitmapBitOrder (assert(XBitmapBitOrder_PROC != 0), XBitmapBitOrder_PROC)

typedef int (* PFN_XBitmapPad_PROC) (Display *);
PFN_XBitmapPad_PROC XBitmapPad_PROC = 0;
#   define XBitmapPad (assert(XBitmapPad_PROC != 0), XBitmapPad_PROC)

typedef int (* PFN_XBitmapUnit_PROC) (Display *);
PFN_XBitmapUnit_PROC XBitmapUnit_PROC = 0;
#   define XBitmapUnit (assert(XBitmapUnit_PROC != 0), XBitmapUnit_PROC)

typedef unsigned long (* PFN_XBlackPixel_PROC) (Display *, int);
PFN_XBlackPixel_PROC XBlackPixel_PROC = 0;
#   define XBlackPixel (assert(XBlackPixel_PROC != 0), XBlackPixel_PROC)

typedef unsigned long (* PFN_XBlackPixelOfScreen_PROC) (Screen *);
PFN_XBlackPixelOfScreen_PROC XBlackPixelOfScreen_PROC = 0;
#   define XBlackPixelOfScreen (assert(XBlackPixelOfScreen_PROC != 0), XBlackPixelOfScreen_PROC)

typedef int (* PFN_XCellsOfScreen_PROC) (Screen *);
PFN_XCellsOfScreen_PROC XCellsOfScreen_PROC = 0;
#   define XCellsOfScreen (assert(XCellsOfScreen_PROC != 0), XCellsOfScreen_PROC)

typedef int (* PFN_XChangeActivePointerGrab_PROC) (Display *, unsigned int, Cursor, Time);
PFN_XChangeActivePointerGrab_PROC XChangeActivePointerGrab_PROC = 0;
#   define XChangeActivePointerGrab (assert(XChangeActivePointerGrab_PROC != 0), XChangeActivePointerGrab_PROC)

typedef int (* PFN_XChangeGC_PROC) (Display *, GC, unsigned long, XGCValues *);
PFN_XChangeGC_PROC XChangeGC_PROC = 0;
#   define XChangeGC (assert(XChangeGC_PROC != 0), XChangeGC_PROC)

typedef int (* PFN_XChangeKeyboardControl_PROC) (Display *, unsigned long, XKeyboardControl *);
PFN_XChangeKeyboardControl_PROC XChangeKeyboardControl_PROC = 0;
#   define XChangeKeyboardControl (assert(XChangeKeyboardControl_PROC != 0), XChangeKeyboardControl_PROC)

typedef int (* PFN_XChangeKeyboardMapping_PROC) (Display *, int, int, KeySym *, int);
PFN_XChangeKeyboardMapping_PROC XChangeKeyboardMapping_PROC = 0;
#   define XChangeKeyboardMapping (assert(XChangeKeyboardMapping_PROC != 0), XChangeKeyboardMapping_PROC)

typedef int (* PFN_XChangePointerControl_PROC) (Display *, int, int, int, int, int);
PFN_XChangePointerControl_PROC XChangePointerControl_PROC = 0;
#   define XChangePointerControl (assert(XChangePointerControl_PROC != 0), XChangePointerControl_PROC)

typedef int (* PFN_XChangeProperty_PROC) (Display *, Window, Atom, Atom, int, int, const unsigned char *, int);
PFN_XChangeProperty_PROC XChangeProperty_PROC = 0;
#   define XChangeProperty (assert(XChangeProperty_PROC != 0), XChangeProperty_PROC)

typedef int (* PFN_XChangeSaveSet_PROC) (Display *, Window, int);
PFN_XChangeSaveSet_PROC XChangeSaveSet_PROC = 0;
#   define XChangeSaveSet (assert(XChangeSaveSet_PROC != 0), XChangeSaveSet_PROC)

typedef int (* PFN_XChangeWindowAttributes_PROC) (Display *, Window, unsigned long, XSetWindowAttributes *);
PFN_XChangeWindowAttributes_PROC XChangeWindowAttributes_PROC = 0;
#   define XChangeWindowAttributes (assert(XChangeWindowAttributes_PROC != 0), XChangeWindowAttributes_PROC)

typedef int (* PFN_XCheckIfEvent_PROC) (Display *, XEvent *, int (*)(Display *, XEvent *, XPointer), XPointer);
PFN_XCheckIfEvent_PROC XCheckIfEvent_PROC = 0;
#   define XCheckIfEvent (assert(XCheckIfEvent_PROC != 0), XCheckIfEvent_PROC)

typedef int (* PFN_XCheckMaskEvent_PROC) (Display *, long, XEvent *);
PFN_XCheckMaskEvent_PROC XCheckMaskEvent_PROC = 0;
#   define XCheckMaskEvent (assert(XCheckMaskEvent_PROC != 0), XCheckMaskEvent_PROC)

typedef int (* PFN_XCheckTypedEvent_PROC) (Display *, int, XEvent *);
PFN_XCheckTypedEvent_PROC XCheckTypedEvent_PROC = 0;
#   define XCheckTypedEvent (assert(XCheckTypedEvent_PROC != 0), XCheckTypedEvent_PROC)

typedef int (* PFN_XCheckTypedWindowEvent_PROC) (Display *, Window, int, XEvent *);
PFN_XCheckTypedWindowEvent_PROC XCheckTypedWindowEvent_PROC = 0;
#   define XCheckTypedWindowEvent (assert(XCheckTypedWindowEvent_PROC != 0), XCheckTypedWindowEvent_PROC)

typedef int (* PFN_XCheckWindowEvent_PROC) (Display *, Window, long, XEvent *);
PFN_XCheckWindowEvent_PROC XCheckWindowEvent_PROC = 0;
#   define XCheckWindowEvent (assert(XCheckWindowEvent_PROC != 0), XCheckWindowEvent_PROC)

typedef int (* PFN_XCirculateSubwindows_PROC) (Display *, Window, int);
PFN_XCirculateSubwindows_PROC XCirculateSubwindows_PROC = 0;
#   define XCirculateSubwindows (assert(XCirculateSubwindows_PROC != 0), XCirculateSubwindows_PROC)

typedef int (* PFN_XCirculateSubwindowsDown_PROC) (Display *, Window);
PFN_XCirculateSubwindowsDown_PROC XCirculateSubwindowsDown_PROC = 0;
#   define XCirculateSubwindowsDown (assert(XCirculateSubwindowsDown_PROC != 0), XCirculateSubwindowsDown_PROC)

typedef int (* PFN_XCirculateSubwindowsUp_PROC) (Display *, Window);
PFN_XCirculateSubwindowsUp_PROC XCirculateSubwindowsUp_PROC = 0;
#   define XCirculateSubwindowsUp (assert(XCirculateSubwindowsUp_PROC != 0), XCirculateSubwindowsUp_PROC)

typedef int (* PFN_XClearArea_PROC) (Display *, Window, int, int, unsigned int, unsigned int, int);
PFN_XClearArea_PROC XClearArea_PROC = 0;
#   define XClearArea (assert(XClearArea_PROC != 0), XClearArea_PROC)

typedef int (* PFN_XClearWindow_PROC) (Display *, Window);
PFN_XClearWindow_PROC XClearWindow_PROC = 0;
#   define XClearWindow (assert(XClearWindow_PROC != 0), XClearWindow_PROC)

typedef int (* PFN_XCloseDisplay_PROC) (Display *);
PFN_XCloseDisplay_PROC XCloseDisplay_PROC = 0;
#   define XCloseDisplay (assert(XCloseDisplay_PROC != 0), XCloseDisplay_PROC)

typedef int (* PFN_XCloseIM_PROC) (XIM);
PFN_XCloseIM_PROC XCloseIM_PROC = 0;
#   define XCloseIM (assert(XCloseIM_PROC != 0), XCloseIM_PROC)

typedef int (* PFN_XCloseOM_PROC) (XOM);
PFN_XCloseOM_PROC XCloseOM_PROC = 0;
#   define XCloseOM (assert(XCloseOM_PROC != 0), XCloseOM_PROC)

typedef int (* PFN_XConfigureWindow_PROC) (Display *, Window, unsigned int, XWindowChanges *);
PFN_XConfigureWindow_PROC XConfigureWindow_PROC = 0;
#   define XConfigureWindow (assert(XConfigureWindow_PROC != 0), XConfigureWindow_PROC)

typedef int (* PFN_XConnectionNumber_PROC) (Display *);
PFN_XConnectionNumber_PROC XConnectionNumber_PROC = 0;
#   define XConnectionNumber (assert(XConnectionNumber_PROC != 0), XConnectionNumber_PROC)

typedef int (* PFN_XContextDependentDrawing_PROC) (XFontSet);
PFN_XContextDependentDrawing_PROC XContextDependentDrawing_PROC = 0;
#   define XContextDependentDrawing (assert(XContextDependentDrawing_PROC != 0), XContextDependentDrawing_PROC)

typedef int (* PFN_XContextualDrawing_PROC) (XFontSet);
PFN_XContextualDrawing_PROC XContextualDrawing_PROC = 0;
#   define XContextualDrawing (assert(XContextualDrawing_PROC != 0), XContextualDrawing_PROC)

typedef int (* PFN_XConvertSelection_PROC) (Display *, Atom, Atom, Atom, Window, Time);
PFN_XConvertSelection_PROC XConvertSelection_PROC = 0;
#   define XConvertSelection (assert(XConvertSelection_PROC != 0), XConvertSelection_PROC)

typedef int (* PFN_XCopyArea_PROC) (Display *, Drawable, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
PFN_XCopyArea_PROC XCopyArea_PROC = 0;
#   define XCopyArea (assert(XCopyArea_PROC != 0), XCopyArea_PROC)

typedef Colormap (* PFN_XCopyColormapAndFree_PROC) (Display *, Colormap);
PFN_XCopyColormapAndFree_PROC XCopyColormapAndFree_PROC = 0;
#   define XCopyColormapAndFree (assert(XCopyColormapAndFree_PROC != 0), XCopyColormapAndFree_PROC)

typedef int (* PFN_XCopyGC_PROC) (Display *, GC, unsigned long, GC);
PFN_XCopyGC_PROC XCopyGC_PROC = 0;
#   define XCopyGC (assert(XCopyGC_PROC != 0), XCopyGC_PROC)

typedef int (* PFN_XCopyPlane_PROC) (Display *, Drawable, Drawable, GC, int, int, unsigned int, unsigned int, int, int, unsigned long);
PFN_XCopyPlane_PROC XCopyPlane_PROC = 0;
#   define XCopyPlane (assert(XCopyPlane_PROC != 0), XCopyPlane_PROC)

typedef Pixmap (* PFN_XCreateBitmapFromData_PROC) (Display *, Drawable, const char *, unsigned int, unsigned int);
PFN_XCreateBitmapFromData_PROC XCreateBitmapFromData_PROC = 0;
#   define XCreateBitmapFromData (assert(XCreateBitmapFromData_PROC != 0), XCreateBitmapFromData_PROC)

typedef Colormap (* PFN_XCreateColormap_PROC) (Display *, Window, Visual *, int);
PFN_XCreateColormap_PROC XCreateColormap_PROC = 0;
#   define XCreateColormap (assert(XCreateColormap_PROC != 0), XCreateColormap_PROC)

typedef Cursor (* PFN_XCreateFontCursor_PROC) (Display *, unsigned int);
PFN_XCreateFontCursor_PROC XCreateFontCursor_PROC = 0;
#   define XCreateFontCursor (assert(XCreateFontCursor_PROC != 0), XCreateFontCursor_PROC)

typedef XFontSet (* PFN_XCreateFontSet_PROC) (Display *, const char *, char ***, int *, char **);
PFN_XCreateFontSet_PROC XCreateFontSet_PROC = 0;
#   define XCreateFontSet (assert(XCreateFontSet_PROC != 0), XCreateFontSet_PROC)

typedef GC (* PFN_XCreateGC_PROC) (Display *, Drawable, unsigned long, XGCValues *);
PFN_XCreateGC_PROC XCreateGC_PROC = 0;
#   define XCreateGC (assert(XCreateGC_PROC != 0), XCreateGC_PROC)

typedef Cursor (* PFN_XCreateGlyphCursor_PROC) (Display *, Font, Font, unsigned int, unsigned int, const XColor *, const XColor *);
PFN_XCreateGlyphCursor_PROC XCreateGlyphCursor_PROC = 0;
#   define XCreateGlyphCursor (assert(XCreateGlyphCursor_PROC != 0), XCreateGlyphCursor_PROC)

typedef XIC (* PFN_XCreateIC_PROC) (XIM, ...);
PFN_XCreateIC_PROC XCreateIC_PROC = 0;
#   define XCreateIC (assert(XCreateIC_PROC != 0), XCreateIC_PROC)

typedef XImage *(* PFN_XCreateImage_PROC) (Display *, Visual *, unsigned int, int, int, char *, unsigned int, unsigned int, int, int);
PFN_XCreateImage_PROC XCreateImage_PROC = 0;
#   define XCreateImage (assert(XCreateImage_PROC != 0), XCreateImage_PROC)

typedef XOC (* PFN_XCreateOC_PROC) (XOM, ...);
PFN_XCreateOC_PROC XCreateOC_PROC = 0;
#   define XCreateOC (assert(XCreateOC_PROC != 0), XCreateOC_PROC)

typedef Pixmap (* PFN_XCreatePixmap_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int);
PFN_XCreatePixmap_PROC XCreatePixmap_PROC = 0;
#   define XCreatePixmap (assert(XCreatePixmap_PROC != 0), XCreatePixmap_PROC)

typedef Cursor (* PFN_XCreatePixmapCursor_PROC) (Display *, Pixmap, Pixmap, XColor *, XColor *, unsigned int, unsigned int);
PFN_XCreatePixmapCursor_PROC XCreatePixmapCursor_PROC = 0;
#   define XCreatePixmapCursor (assert(XCreatePixmapCursor_PROC != 0), XCreatePixmapCursor_PROC)

typedef Pixmap (* PFN_XCreatePixmapFromBitmapData_PROC) (Display *, Drawable, char *, unsigned int, unsigned int, unsigned long, unsigned long, unsigned int);
PFN_XCreatePixmapFromBitmapData_PROC XCreatePixmapFromBitmapData_PROC = 0;
#   define XCreatePixmapFromBitmapData (assert(XCreatePixmapFromBitmapData_PROC != 0), XCreatePixmapFromBitmapData_PROC)

typedef Window (* PFN_XCreateSimpleWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int, unsigned int, unsigned long, unsigned long);
PFN_XCreateSimpleWindow_PROC XCreateSimpleWindow_PROC = 0;
#   define XCreateSimpleWindow (assert(XCreateSimpleWindow_PROC != 0), XCreateSimpleWindow_PROC)

typedef Window (* PFN_XCreateWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int, unsigned int, int, unsigned int, Visual *, unsigned long, XSetWindowAttributes *);
PFN_XCreateWindow_PROC XCreateWindow_PROC = 0;
#   define XCreateWindow (assert(XCreateWindow_PROC != 0), XCreateWindow_PROC)

typedef Colormap (* PFN_XDefaultColormap_PROC) (Display *, int);
PFN_XDefaultColormap_PROC XDefaultColormap_PROC = 0;
#   define XDefaultColormap (assert(XDefaultColormap_PROC != 0), XDefaultColormap_PROC)

typedef Colormap (* PFN_XDefaultColormapOfScreen_PROC) (Screen *);
PFN_XDefaultColormapOfScreen_PROC XDefaultColormapOfScreen_PROC = 0;
#   define XDefaultColormapOfScreen (assert(XDefaultColormapOfScreen_PROC != 0), XDefaultColormapOfScreen_PROC)

typedef int (* PFN_XDefaultDepth_PROC) (Display *, int);
PFN_XDefaultDepth_PROC XDefaultDepth_PROC = 0;
#   define XDefaultDepth (assert(XDefaultDepth_PROC != 0), XDefaultDepth_PROC)

typedef int (* PFN_XDefaultDepthOfScreen_PROC) (Screen *);
PFN_XDefaultDepthOfScreen_PROC XDefaultDepthOfScreen_PROC = 0;
#   define XDefaultDepthOfScreen (assert(XDefaultDepthOfScreen_PROC != 0), XDefaultDepthOfScreen_PROC)

typedef GC (* PFN_XDefaultGC_PROC) (Display *, int);
PFN_XDefaultGC_PROC XDefaultGC_PROC = 0;
#   define XDefaultGC (assert(XDefaultGC_PROC != 0), XDefaultGC_PROC)

typedef GC (* PFN_XDefaultGCOfScreen_PROC) (Screen *);
PFN_XDefaultGCOfScreen_PROC XDefaultGCOfScreen_PROC = 0;
#   define XDefaultGCOfScreen (assert(XDefaultGCOfScreen_PROC != 0), XDefaultGCOfScreen_PROC)

typedef Window (* PFN_XDefaultRootWindow_PROC) (Display *);
PFN_XDefaultRootWindow_PROC XDefaultRootWindow_PROC = 0;
#   define XDefaultRootWindow (assert(XDefaultRootWindow_PROC != 0), XDefaultRootWindow_PROC)

typedef int (* PFN_XDefaultScreen_PROC) (Display *);
PFN_XDefaultScreen_PROC XDefaultScreen_PROC = 0;
#   define XDefaultScreen (assert(XDefaultScreen_PROC != 0), XDefaultScreen_PROC)

typedef Screen *(* PFN_XDefaultScreenOfDisplay_PROC) (Display *);
PFN_XDefaultScreenOfDisplay_PROC XDefaultScreenOfDisplay_PROC = 0;
#   define XDefaultScreenOfDisplay (assert(XDefaultScreenOfDisplay_PROC != 0), XDefaultScreenOfDisplay_PROC)

typedef Visual *(* PFN_XDefaultVisual_PROC) (Display *, int);
PFN_XDefaultVisual_PROC XDefaultVisual_PROC = 0;
#   define XDefaultVisual (assert(XDefaultVisual_PROC != 0), XDefaultVisual_PROC)

typedef Visual *(* PFN_XDefaultVisualOfScreen_PROC) (Screen *);
PFN_XDefaultVisualOfScreen_PROC XDefaultVisualOfScreen_PROC = 0;
#   define XDefaultVisualOfScreen (assert(XDefaultVisualOfScreen_PROC != 0), XDefaultVisualOfScreen_PROC)

typedef int (* PFN_XDefineCursor_PROC) (Display *, Window, Cursor);
PFN_XDefineCursor_PROC XDefineCursor_PROC = 0;
#   define XDefineCursor (assert(XDefineCursor_PROC != 0), XDefineCursor_PROC)

typedef XModifierKeymap *(* PFN_XDeleteModifiermapEntry_PROC) (XModifierKeymap *, KeyCode, int);
PFN_XDeleteModifiermapEntry_PROC XDeleteModifiermapEntry_PROC = 0;
#   define XDeleteModifiermapEntry (assert(XDeleteModifiermapEntry_PROC != 0), XDeleteModifiermapEntry_PROC)

typedef int (* PFN_XDeleteProperty_PROC) (Display *, Window, Atom);
PFN_XDeleteProperty_PROC XDeleteProperty_PROC = 0;
#   define XDeleteProperty (assert(XDeleteProperty_PROC != 0), XDeleteProperty_PROC)

typedef void (* PFN_XDestroyIC_PROC) (XIC);
PFN_XDestroyIC_PROC XDestroyIC_PROC = 0;
#   define XDestroyIC (assert(XDestroyIC_PROC != 0), XDestroyIC_PROC)

typedef void (* PFN_XDestroyOC_PROC) (XOC);
PFN_XDestroyOC_PROC XDestroyOC_PROC = 0;
#   define XDestroyOC (assert(XDestroyOC_PROC != 0), XDestroyOC_PROC)

typedef int (* PFN_XDestroySubwindows_PROC) (Display *, Window);
PFN_XDestroySubwindows_PROC XDestroySubwindows_PROC = 0;
#   define XDestroySubwindows (assert(XDestroySubwindows_PROC != 0), XDestroySubwindows_PROC)

typedef int (* PFN_XDestroyWindow_PROC) (Display *, Window);
PFN_XDestroyWindow_PROC XDestroyWindow_PROC = 0;
#   define XDestroyWindow (assert(XDestroyWindow_PROC != 0), XDestroyWindow_PROC)

typedef int (* PFN_XDirectionalDependentDrawing_PROC) (XFontSet);
PFN_XDirectionalDependentDrawing_PROC XDirectionalDependentDrawing_PROC = 0;
#   define XDirectionalDependentDrawing (assert(XDirectionalDependentDrawing_PROC != 0), XDirectionalDependentDrawing_PROC)

typedef int (* PFN_XDisableAccessControl_PROC) (Display *);
PFN_XDisableAccessControl_PROC XDisableAccessControl_PROC = 0;
#   define XDisableAccessControl (assert(XDisableAccessControl_PROC != 0), XDisableAccessControl_PROC)

typedef int (* PFN_XDisplayCells_PROC) (Display *, int);
PFN_XDisplayCells_PROC XDisplayCells_PROC = 0;
#   define XDisplayCells (assert(XDisplayCells_PROC != 0), XDisplayCells_PROC)

typedef int (* PFN_XDisplayHeight_PROC) (Display *, int);
PFN_XDisplayHeight_PROC XDisplayHeight_PROC = 0;
#   define XDisplayHeight (assert(XDisplayHeight_PROC != 0), XDisplayHeight_PROC)

typedef int (* PFN_XDisplayHeightMM_PROC) (Display *, int);
PFN_XDisplayHeightMM_PROC XDisplayHeightMM_PROC = 0;
#   define XDisplayHeightMM (assert(XDisplayHeightMM_PROC != 0), XDisplayHeightMM_PROC)

typedef int (* PFN_XDisplayKeycodes_PROC) (Display *, int *, int *);
PFN_XDisplayKeycodes_PROC XDisplayKeycodes_PROC = 0;
#   define XDisplayKeycodes (assert(XDisplayKeycodes_PROC != 0), XDisplayKeycodes_PROC)

typedef unsigned long (* PFN_XDisplayMotionBufferSize_PROC) (Display *);
PFN_XDisplayMotionBufferSize_PROC XDisplayMotionBufferSize_PROC = 0;
#   define XDisplayMotionBufferSize (assert(XDisplayMotionBufferSize_PROC != 0), XDisplayMotionBufferSize_PROC)

typedef char *(* PFN_XDisplayName_PROC) (const char *);
PFN_XDisplayName_PROC XDisplayName_PROC = 0;
#   define XDisplayName (assert(XDisplayName_PROC != 0), XDisplayName_PROC)

typedef Display *(* PFN_XDisplayOfIM_PROC) (XIM);
PFN_XDisplayOfIM_PROC XDisplayOfIM_PROC = 0;
#   define XDisplayOfIM (assert(XDisplayOfIM_PROC != 0), XDisplayOfIM_PROC)

typedef Display *(* PFN_XDisplayOfOM_PROC) (XOM);
PFN_XDisplayOfOM_PROC XDisplayOfOM_PROC = 0;
#   define XDisplayOfOM (assert(XDisplayOfOM_PROC != 0), XDisplayOfOM_PROC)

typedef Display *(* PFN_XDisplayOfScreen_PROC) (Screen *);
PFN_XDisplayOfScreen_PROC XDisplayOfScreen_PROC = 0;
#   define XDisplayOfScreen (assert(XDisplayOfScreen_PROC != 0), XDisplayOfScreen_PROC)

typedef int (* PFN_XDisplayPlanes_PROC) (Display *, int);
PFN_XDisplayPlanes_PROC XDisplayPlanes_PROC = 0;
#   define XDisplayPlanes (assert(XDisplayPlanes_PROC != 0), XDisplayPlanes_PROC)

typedef char *(* PFN_XDisplayString_PROC) (Display *);
PFN_XDisplayString_PROC XDisplayString_PROC = 0;
#   define XDisplayString (assert(XDisplayString_PROC != 0), XDisplayString_PROC)

typedef int (* PFN_XDisplayWidth_PROC) (Display *, int);
PFN_XDisplayWidth_PROC XDisplayWidth_PROC = 0;
#   define XDisplayWidth (assert(XDisplayWidth_PROC != 0), XDisplayWidth_PROC)

typedef int (* PFN_XDisplayWidthMM_PROC) (Display *, int);
PFN_XDisplayWidthMM_PROC XDisplayWidthMM_PROC = 0;
#   define XDisplayWidthMM (assert(XDisplayWidthMM_PROC != 0), XDisplayWidthMM_PROC)

typedef int (* PFN_XDoesBackingStore_PROC) (Screen *);
PFN_XDoesBackingStore_PROC XDoesBackingStore_PROC = 0;
#   define XDoesBackingStore (assert(XDoesBackingStore_PROC != 0), XDoesBackingStore_PROC)

typedef int (* PFN_XDoesSaveUnders_PROC) (Screen *);
PFN_XDoesSaveUnders_PROC XDoesSaveUnders_PROC = 0;
#   define XDoesSaveUnders (assert(XDoesSaveUnders_PROC != 0), XDoesSaveUnders_PROC)

typedef int (* PFN_XDrawArc_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
PFN_XDrawArc_PROC XDrawArc_PROC = 0;
#   define XDrawArc (assert(XDrawArc_PROC != 0), XDrawArc_PROC)

typedef int (* PFN_XDrawArcs_PROC) (Display *, Drawable, GC, XArc *, int);
PFN_XDrawArcs_PROC XDrawArcs_PROC = 0;
#   define XDrawArcs (assert(XDrawArcs_PROC != 0), XDrawArcs_PROC)

typedef int (* PFN_XDrawImageString_PROC) (Display *, Drawable, GC, int, int, const char *, int);
PFN_XDrawImageString_PROC XDrawImageString_PROC = 0;
#   define XDrawImageString (assert(XDrawImageString_PROC != 0), XDrawImageString_PROC)

typedef int (* PFN_XDrawImageString16_PROC) (Display *, Drawable, GC, int, int, const XChar2b *, int);
PFN_XDrawImageString16_PROC XDrawImageString16_PROC = 0;
#   define XDrawImageString16 (assert(XDrawImageString16_PROC != 0), XDrawImageString16_PROC)

typedef int (* PFN_XDrawLine_PROC) (Display *, Drawable, GC, int, int, int, int);
PFN_XDrawLine_PROC XDrawLine_PROC = 0;
#   define XDrawLine (assert(XDrawLine_PROC != 0), XDrawLine_PROC)

typedef int (* PFN_XDrawLines_PROC) (Display *, Drawable, GC, XPoint *, int, int);
PFN_XDrawLines_PROC XDrawLines_PROC = 0;
#   define XDrawLines (assert(XDrawLines_PROC != 0), XDrawLines_PROC)

typedef int (* PFN_XDrawPoint_PROC) (Display *, Drawable, GC, int, int);
PFN_XDrawPoint_PROC XDrawPoint_PROC = 0;
#   define XDrawPoint (assert(XDrawPoint_PROC != 0), XDrawPoint_PROC)

typedef int (* PFN_XDrawPoints_PROC) (Display *, Drawable, GC, XPoint *, int, int);
PFN_XDrawPoints_PROC XDrawPoints_PROC = 0;
#   define XDrawPoints (assert(XDrawPoints_PROC != 0), XDrawPoints_PROC)

typedef int (* PFN_XDrawRectangle_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int);
PFN_XDrawRectangle_PROC XDrawRectangle_PROC = 0;
#   define XDrawRectangle (assert(XDrawRectangle_PROC != 0), XDrawRectangle_PROC)

typedef int (* PFN_XDrawRectangles_PROC) (Display *, Drawable, GC, XRectangle *, int);
PFN_XDrawRectangles_PROC XDrawRectangles_PROC = 0;
#   define XDrawRectangles (assert(XDrawRectangles_PROC != 0), XDrawRectangles_PROC)

typedef int (* PFN_XDrawSegments_PROC) (Display *, Drawable, GC, XSegment *, int);
PFN_XDrawSegments_PROC XDrawSegments_PROC = 0;
#   define XDrawSegments (assert(XDrawSegments_PROC != 0), XDrawSegments_PROC)

typedef int (* PFN_XDrawString_PROC) (Display *, Drawable, GC, int, int, const char *, int);
PFN_XDrawString_PROC XDrawString_PROC = 0;
#   define XDrawString (assert(XDrawString_PROC != 0), XDrawString_PROC)

typedef int (* PFN_XDrawString16_PROC) (Display *, Drawable, GC, int, int, const XChar2b *, int);
PFN_XDrawString16_PROC XDrawString16_PROC = 0;
#   define XDrawString16 (assert(XDrawString16_PROC != 0), XDrawString16_PROC)

typedef int (* PFN_XDrawText_PROC) (Display *, Drawable, GC, int, int, XTextItem *, int);
PFN_XDrawText_PROC XDrawText_PROC = 0;
#   define XDrawText (assert(XDrawText_PROC != 0), XDrawText_PROC)

typedef int (* PFN_XDrawText16_PROC) (Display *, Drawable, GC, int, int, XTextItem16 *, int);
PFN_XDrawText16_PROC XDrawText16_PROC = 0;
#   define XDrawText16 (assert(XDrawText16_PROC != 0), XDrawText16_PROC)

typedef XExtData **(* PFN_XEHeadOfExtensionList_PROC) (XEDataObject);
PFN_XEHeadOfExtensionList_PROC XEHeadOfExtensionList_PROC = 0;
#   define XEHeadOfExtensionList (assert(XEHeadOfExtensionList_PROC != 0), XEHeadOfExtensionList_PROC)

typedef int (* PFN_XEnableAccessControl_PROC) (Display *);
PFN_XEnableAccessControl_PROC XEnableAccessControl_PROC = 0;
#   define XEnableAccessControl (assert(XEnableAccessControl_PROC != 0), XEnableAccessControl_PROC)

typedef long (* PFN_XEventMaskOfScreen_PROC) (Screen *);
PFN_XEventMaskOfScreen_PROC XEventMaskOfScreen_PROC = 0;
#   define XEventMaskOfScreen (assert(XEventMaskOfScreen_PROC != 0), XEventMaskOfScreen_PROC)

typedef int (* PFN_XEventsQueued_PROC) (Display *, int);
PFN_XEventsQueued_PROC XEventsQueued_PROC = 0;
#   define XEventsQueued (assert(XEventsQueued_PROC != 0), XEventsQueued_PROC)

typedef long (* PFN_XExtendedMaxRequestSize_PROC) (Display *);
PFN_XExtendedMaxRequestSize_PROC XExtendedMaxRequestSize_PROC = 0;
#   define XExtendedMaxRequestSize (assert(XExtendedMaxRequestSize_PROC != 0), XExtendedMaxRequestSize_PROC)

typedef XFontSetExtents *(* PFN_XExtentsOfFontSet_PROC) (XFontSet);
PFN_XExtentsOfFontSet_PROC XExtentsOfFontSet_PROC = 0;
#   define XExtentsOfFontSet (assert(XExtentsOfFontSet_PROC != 0), XExtentsOfFontSet_PROC)

typedef char *(* PFN_XFetchBuffer_PROC) (Display *, int *, int);
PFN_XFetchBuffer_PROC XFetchBuffer_PROC = 0;
#   define XFetchBuffer (assert(XFetchBuffer_PROC != 0), XFetchBuffer_PROC)

typedef char *(* PFN_XFetchBytes_PROC) (Display *, int *);
PFN_XFetchBytes_PROC XFetchBytes_PROC = 0;
#   define XFetchBytes (assert(XFetchBytes_PROC != 0), XFetchBytes_PROC)

typedef int (* PFN_XFetchName_PROC) (Display *, Window, char **);
PFN_XFetchName_PROC XFetchName_PROC = 0;
#   define XFetchName (assert(XFetchName_PROC != 0), XFetchName_PROC)

typedef int (* PFN_XFillArc_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
PFN_XFillArc_PROC XFillArc_PROC = 0;
#   define XFillArc (assert(XFillArc_PROC != 0), XFillArc_PROC)

typedef int (* PFN_XFillArcs_PROC) (Display *, Drawable, GC, XArc *, int);
PFN_XFillArcs_PROC XFillArcs_PROC = 0;
#   define XFillArcs (assert(XFillArcs_PROC != 0), XFillArcs_PROC)

typedef int (* PFN_XFillPolygon_PROC) (Display *, Drawable, GC, XPoint *, int, int, int);
PFN_XFillPolygon_PROC XFillPolygon_PROC = 0;
#   define XFillPolygon (assert(XFillPolygon_PROC != 0), XFillPolygon_PROC)

typedef int (* PFN_XFillRectangle_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int);
PFN_XFillRectangle_PROC XFillRectangle_PROC = 0;
#   define XFillRectangle (assert(XFillRectangle_PROC != 0), XFillRectangle_PROC)

typedef int (* PFN_XFillRectangles_PROC) (Display *, Drawable, GC, XRectangle *, int);
PFN_XFillRectangles_PROC XFillRectangles_PROC = 0;
#   define XFillRectangles (assert(XFillRectangles_PROC != 0), XFillRectangles_PROC)

typedef int (* PFN_XFilterEvent_PROC) (XEvent *, Window);
PFN_XFilterEvent_PROC XFilterEvent_PROC = 0;
#   define XFilterEvent (assert(XFilterEvent_PROC != 0), XFilterEvent_PROC)

typedef XExtData *(* PFN_XFindOnExtensionList_PROC) (XExtData **, int);
PFN_XFindOnExtensionList_PROC XFindOnExtensionList_PROC = 0;
#   define XFindOnExtensionList (assert(XFindOnExtensionList_PROC != 0), XFindOnExtensionList_PROC)

typedef int (* PFN_XFlush_PROC) (Display *);
PFN_XFlush_PROC XFlush_PROC = 0;
#   define XFlush (assert(XFlush_PROC != 0), XFlush_PROC)

typedef void (* PFN_XFlushGC_PROC) (Display *, GC);
PFN_XFlushGC_PROC XFlushGC_PROC = 0;
#   define XFlushGC (assert(XFlushGC_PROC != 0), XFlushGC_PROC)

typedef int (* PFN_XFontsOfFontSet_PROC) (XFontSet, XFontStruct ***, char ***);
PFN_XFontsOfFontSet_PROC XFontsOfFontSet_PROC = 0;
#   define XFontsOfFontSet (assert(XFontsOfFontSet_PROC != 0), XFontsOfFontSet_PROC)

typedef int (* PFN_XForceScreenSaver_PROC) (Display *, int);
PFN_XForceScreenSaver_PROC XForceScreenSaver_PROC = 0;
#   define XForceScreenSaver (assert(XForceScreenSaver_PROC != 0), XForceScreenSaver_PROC)

typedef int (* PFN_XFree_PROC) (void *);
PFN_XFree_PROC XFree_PROC = 0;
#   define XFree (assert(XFree_PROC != 0), XFree_PROC)

typedef int (* PFN_XFreeColormap_PROC) (Display *, Colormap);
PFN_XFreeColormap_PROC XFreeColormap_PROC = 0;
#   define XFreeColormap (assert(XFreeColormap_PROC != 0), XFreeColormap_PROC)

typedef int (* PFN_XFreeColors_PROC) (Display *, Colormap, unsigned long *, int, unsigned long);
PFN_XFreeColors_PROC XFreeColors_PROC = 0;
#   define XFreeColors (assert(XFreeColors_PROC != 0), XFreeColors_PROC)

typedef int (* PFN_XFreeCursor_PROC) (Display *, Cursor);
PFN_XFreeCursor_PROC XFreeCursor_PROC = 0;
#   define XFreeCursor (assert(XFreeCursor_PROC != 0), XFreeCursor_PROC)

typedef void (* PFN_XFreeEventData_PROC) (Display *, XGenericEventCookie *);
PFN_XFreeEventData_PROC XFreeEventData_PROC = 0;
#   define XFreeEventData (assert(XFreeEventData_PROC != 0), XFreeEventData_PROC)

typedef int (* PFN_XFreeExtensionList_PROC) (char **);
PFN_XFreeExtensionList_PROC XFreeExtensionList_PROC = 0;
#   define XFreeExtensionList (assert(XFreeExtensionList_PROC != 0), XFreeExtensionList_PROC)

typedef int (* PFN_XFreeFont_PROC) (Display *, XFontStruct *);
PFN_XFreeFont_PROC XFreeFont_PROC = 0;
#   define XFreeFont (assert(XFreeFont_PROC != 0), XFreeFont_PROC)

typedef int (* PFN_XFreeFontInfo_PROC) (char **, XFontStruct *, int);
PFN_XFreeFontInfo_PROC XFreeFontInfo_PROC = 0;
#   define XFreeFontInfo (assert(XFreeFontInfo_PROC != 0), XFreeFontInfo_PROC)

typedef int (* PFN_XFreeFontNames_PROC) (char **);
PFN_XFreeFontNames_PROC XFreeFontNames_PROC = 0;
#   define XFreeFontNames (assert(XFreeFontNames_PROC != 0), XFreeFontNames_PROC)

typedef int (* PFN_XFreeFontPath_PROC) (char **);
PFN_XFreeFontPath_PROC XFreeFontPath_PROC = 0;
#   define XFreeFontPath (assert(XFreeFontPath_PROC != 0), XFreeFontPath_PROC)

typedef void (* PFN_XFreeFontSet_PROC) (Display *, XFontSet);
PFN_XFreeFontSet_PROC XFreeFontSet_PROC = 0;
#   define XFreeFontSet (assert(XFreeFontSet_PROC != 0), XFreeFontSet_PROC)

typedef int (* PFN_XFreeGC_PROC) (Display *, GC);
PFN_XFreeGC_PROC XFreeGC_PROC = 0;
#   define XFreeGC (assert(XFreeGC_PROC != 0), XFreeGC_PROC)

typedef int (* PFN_XFreeModifiermap_PROC) (XModifierKeymap *);
PFN_XFreeModifiermap_PROC XFreeModifiermap_PROC = 0;
#   define XFreeModifiermap (assert(XFreeModifiermap_PROC != 0), XFreeModifiermap_PROC)

typedef int (* PFN_XFreePixmap_PROC) (Display *, Pixmap);
PFN_XFreePixmap_PROC XFreePixmap_PROC = 0;
#   define XFreePixmap (assert(XFreePixmap_PROC != 0), XFreePixmap_PROC)

typedef void (* PFN_XFreeStringList_PROC) (char **);
PFN_XFreeStringList_PROC XFreeStringList_PROC = 0;
#   define XFreeStringList (assert(XFreeStringList_PROC != 0), XFreeStringList_PROC)

typedef int (* PFN_XFreeThreads_PROC) (void);
PFN_XFreeThreads_PROC XFreeThreads_PROC = 0;
#   define XFreeThreads (assert(XFreeThreads_PROC != 0), XFreeThreads_PROC)

typedef GContext (* PFN_XGContextFromGC_PROC) (GC);
PFN_XGContextFromGC_PROC XGContextFromGC_PROC = 0;
#   define XGContextFromGC (assert(XGContextFromGC_PROC != 0), XGContextFromGC_PROC)

typedef int (* PFN_XGeometry_PROC) (Display *, int, const char *, const char *, unsigned int, unsigned int, unsigned int, int, int, int *, int *, int *, int *);
PFN_XGeometry_PROC XGeometry_PROC = 0;
#   define XGeometry (assert(XGeometry_PROC != 0), XGeometry_PROC)

typedef char *(* PFN_XGetAtomName_PROC) (Display *, Atom);
PFN_XGetAtomName_PROC XGetAtomName_PROC = 0;
#   define XGetAtomName (assert(XGetAtomName_PROC != 0), XGetAtomName_PROC)

typedef int (* PFN_XGetAtomNames_PROC) (Display *, Atom *, int, char **);
PFN_XGetAtomNames_PROC XGetAtomNames_PROC = 0;
#   define XGetAtomNames (assert(XGetAtomNames_PROC != 0), XGetAtomNames_PROC)

typedef int (* PFN_XGetCommand_PROC) (Display *, Window, char ***, int *);
PFN_XGetCommand_PROC XGetCommand_PROC = 0;
#   define XGetCommand (assert(XGetCommand_PROC != 0), XGetCommand_PROC)

typedef char *(* PFN_XGetDefault_PROC) (Display *, const char *, const char *);
PFN_XGetDefault_PROC XGetDefault_PROC = 0;
#   define XGetDefault (assert(XGetDefault_PROC != 0), XGetDefault_PROC)

typedef int (* PFN_XGetErrorDatabaseText_PROC) (Display *, const char *, const char *, const char *, char *, int);
PFN_XGetErrorDatabaseText_PROC XGetErrorDatabaseText_PROC = 0;
#   define XGetErrorDatabaseText (assert(XGetErrorDatabaseText_PROC != 0), XGetErrorDatabaseText_PROC)

typedef int (* PFN_XGetErrorText_PROC) (Display *, int, char *, int);
PFN_XGetErrorText_PROC XGetErrorText_PROC = 0;
#   define XGetErrorText (assert(XGetErrorText_PROC != 0), XGetErrorText_PROC)

typedef int (* PFN_XGetEventData_PROC) (Display *, XGenericEventCookie *);
PFN_XGetEventData_PROC XGetEventData_PROC = 0;
#   define XGetEventData (assert(XGetEventData_PROC != 0), XGetEventData_PROC)

typedef char **(* PFN_XGetFontPath_PROC) (Display *, int *);
PFN_XGetFontPath_PROC XGetFontPath_PROC = 0;
#   define XGetFontPath (assert(XGetFontPath_PROC != 0), XGetFontPath_PROC)

typedef int (* PFN_XGetFontProperty_PROC) (XFontStruct *, Atom, unsigned long *);
PFN_XGetFontProperty_PROC XGetFontProperty_PROC = 0;
#   define XGetFontProperty (assert(XGetFontProperty_PROC != 0), XGetFontProperty_PROC)

typedef int (* PFN_XGetGCValues_PROC) (Display *, GC, unsigned long, XGCValues *);
PFN_XGetGCValues_PROC XGetGCValues_PROC = 0;
#   define XGetGCValues (assert(XGetGCValues_PROC != 0), XGetGCValues_PROC)

typedef int (* PFN_XGetGeometry_PROC) (Display *, Drawable, Window *, int *, int *, unsigned int *, unsigned int *, unsigned int *, unsigned int *);
PFN_XGetGeometry_PROC XGetGeometry_PROC = 0;
#   define XGetGeometry (assert(XGetGeometry_PROC != 0), XGetGeometry_PROC)

typedef char *(* PFN_XGetICValues_PROC) (XIC, ...);
PFN_XGetICValues_PROC XGetICValues_PROC = 0;
#   define XGetICValues (assert(XGetICValues_PROC != 0), XGetICValues_PROC)

typedef char *(* PFN_XGetIMValues_PROC) (XIM, ...);
PFN_XGetIMValues_PROC XGetIMValues_PROC = 0;
#   define XGetIMValues (assert(XGetIMValues_PROC != 0), XGetIMValues_PROC)

typedef int (* PFN_XGetIconName_PROC) (Display *, Window, char **);
PFN_XGetIconName_PROC XGetIconName_PROC = 0;
#   define XGetIconName (assert(XGetIconName_PROC != 0), XGetIconName_PROC)

typedef XImage *(* PFN_XGetImage_PROC) (Display *, Drawable, int, int, unsigned int, unsigned int, unsigned long, int);
PFN_XGetImage_PROC XGetImage_PROC = 0;
#   define XGetImage (assert(XGetImage_PROC != 0), XGetImage_PROC)

typedef int (* PFN_XGetInputFocus_PROC) (Display *, Window *, int *);
PFN_XGetInputFocus_PROC XGetInputFocus_PROC = 0;
#   define XGetInputFocus (assert(XGetInputFocus_PROC != 0), XGetInputFocus_PROC)

typedef int (* PFN_XGetKeyboardControl_PROC) (Display *, XKeyboardState *);
PFN_XGetKeyboardControl_PROC XGetKeyboardControl_PROC = 0;
#   define XGetKeyboardControl (assert(XGetKeyboardControl_PROC != 0), XGetKeyboardControl_PROC)

typedef KeySym *(* PFN_XGetKeyboardMapping_PROC) (Display *, KeyCode, int, int *);
PFN_XGetKeyboardMapping_PROC XGetKeyboardMapping_PROC = 0;
#   define XGetKeyboardMapping (assert(XGetKeyboardMapping_PROC != 0), XGetKeyboardMapping_PROC)

typedef XModifierKeymap *(* PFN_XGetModifierMapping_PROC) (Display *);
PFN_XGetModifierMapping_PROC XGetModifierMapping_PROC = 0;
#   define XGetModifierMapping (assert(XGetModifierMapping_PROC != 0), XGetModifierMapping_PROC)

typedef XTimeCoord *(* PFN_XGetMotionEvents_PROC) (Display *, Window, Time, Time, int *);
PFN_XGetMotionEvents_PROC XGetMotionEvents_PROC = 0;
#   define XGetMotionEvents (assert(XGetMotionEvents_PROC != 0), XGetMotionEvents_PROC)

typedef char *(* PFN_XGetOCValues_PROC) (XOC, ...);
PFN_XGetOCValues_PROC XGetOCValues_PROC = 0;
#   define XGetOCValues (assert(XGetOCValues_PROC != 0), XGetOCValues_PROC)

typedef char *(* PFN_XGetOMValues_PROC) (XOM, ...);
PFN_XGetOMValues_PROC XGetOMValues_PROC = 0;
#   define XGetOMValues (assert(XGetOMValues_PROC != 0), XGetOMValues_PROC)

typedef int (* PFN_XGetPointerControl_PROC) (Display *, int *, int *, int *);
PFN_XGetPointerControl_PROC XGetPointerControl_PROC = 0;
#   define XGetPointerControl (assert(XGetPointerControl_PROC != 0), XGetPointerControl_PROC)

typedef int (* PFN_XGetPointerMapping_PROC) (Display *, unsigned char *, int);
PFN_XGetPointerMapping_PROC XGetPointerMapping_PROC = 0;
#   define XGetPointerMapping (assert(XGetPointerMapping_PROC != 0), XGetPointerMapping_PROC)

typedef int (* PFN_XGetScreenSaver_PROC) (Display *, int *, int *, int *, int *);
PFN_XGetScreenSaver_PROC XGetScreenSaver_PROC = 0;
#   define XGetScreenSaver (assert(XGetScreenSaver_PROC != 0), XGetScreenSaver_PROC)

typedef Window (* PFN_XGetSelectionOwner_PROC) (Display *, Atom);
PFN_XGetSelectionOwner_PROC XGetSelectionOwner_PROC = 0;
#   define XGetSelectionOwner (assert(XGetSelectionOwner_PROC != 0), XGetSelectionOwner_PROC)

typedef XImage *(* PFN_XGetSubImage_PROC) (Display *, Drawable, int, int, unsigned int, unsigned int, unsigned long, int, XImage *, int, int);
PFN_XGetSubImage_PROC XGetSubImage_PROC = 0;
#   define XGetSubImage (assert(XGetSubImage_PROC != 0), XGetSubImage_PROC)

typedef int (* PFN_XGetTransientForHint_PROC) (Display *, Window, Window *);
PFN_XGetTransientForHint_PROC XGetTransientForHint_PROC = 0;
#   define XGetTransientForHint (assert(XGetTransientForHint_PROC != 0), XGetTransientForHint_PROC)

typedef int (* PFN_XGetWMColormapWindows_PROC) (Display *, Window, Window **, int *);
PFN_XGetWMColormapWindows_PROC XGetWMColormapWindows_PROC = 0;
#   define XGetWMColormapWindows (assert(XGetWMColormapWindows_PROC != 0), XGetWMColormapWindows_PROC)

typedef int (* PFN_XGetWMProtocols_PROC) (Display *, Window, Atom **, int *);
PFN_XGetWMProtocols_PROC XGetWMProtocols_PROC = 0;
#   define XGetWMProtocols (assert(XGetWMProtocols_PROC != 0), XGetWMProtocols_PROC)

typedef int (* PFN_XGetWindowAttributes_PROC) (Display *, Window, XWindowAttributes *);
PFN_XGetWindowAttributes_PROC XGetWindowAttributes_PROC = 0;
#   define XGetWindowAttributes (assert(XGetWindowAttributes_PROC != 0), XGetWindowAttributes_PROC)

typedef int (* PFN_XGetWindowProperty_PROC) (Display *, Window, Atom, long, long, int, Atom, Atom *, int *, unsigned long *, unsigned long *, unsigned char **);
PFN_XGetWindowProperty_PROC XGetWindowProperty_PROC = 0;
#   define XGetWindowProperty (assert(XGetWindowProperty_PROC != 0), XGetWindowProperty_PROC)

typedef int (* PFN_XGrabButton_PROC) (Display *, unsigned int, unsigned int, Window, int, unsigned int, int, int, Window, Cursor);
PFN_XGrabButton_PROC XGrabButton_PROC = 0;
#   define XGrabButton (assert(XGrabButton_PROC != 0), XGrabButton_PROC)

typedef int (* PFN_XGrabKey_PROC) (Display *, int, unsigned int, Window, int, int, int);
PFN_XGrabKey_PROC XGrabKey_PROC = 0;
#   define XGrabKey (assert(XGrabKey_PROC != 0), XGrabKey_PROC)

typedef int (* PFN_XGrabKeyboard_PROC) (Display *, Window, int, int, int, Time);
PFN_XGrabKeyboard_PROC XGrabKeyboard_PROC = 0;
#   define XGrabKeyboard (assert(XGrabKeyboard_PROC != 0), XGrabKeyboard_PROC)

typedef int (* PFN_XGrabPointer_PROC) (Display *, Window, int, unsigned int, int, int, Window, Cursor, Time);
PFN_XGrabPointer_PROC XGrabPointer_PROC = 0;
#   define XGrabPointer (assert(XGrabPointer_PROC != 0), XGrabPointer_PROC)

typedef int (* PFN_XGrabServer_PROC) (Display *);
PFN_XGrabServer_PROC XGrabServer_PROC = 0;
#   define XGrabServer (assert(XGrabServer_PROC != 0), XGrabServer_PROC)

typedef int (* PFN_XHeightMMOfScreen_PROC) (Screen *);
PFN_XHeightMMOfScreen_PROC XHeightMMOfScreen_PROC = 0;
#   define XHeightMMOfScreen (assert(XHeightMMOfScreen_PROC != 0), XHeightMMOfScreen_PROC)

typedef int (* PFN_XHeightOfScreen_PROC) (Screen *);
PFN_XHeightOfScreen_PROC XHeightOfScreen_PROC = 0;
#   define XHeightOfScreen (assert(XHeightOfScreen_PROC != 0), XHeightOfScreen_PROC)

typedef XIM (* PFN_XIMOfIC_PROC) (XIC);
PFN_XIMOfIC_PROC XIMOfIC_PROC = 0;
#   define XIMOfIC (assert(XIMOfIC_PROC != 0), XIMOfIC_PROC)

typedef int (* PFN_XIconifyWindow_PROC) (Display *, Window, int);
PFN_XIconifyWindow_PROC XIconifyWindow_PROC = 0;
#   define XIconifyWindow (assert(XIconifyWindow_PROC != 0), XIconifyWindow_PROC)

typedef int (* PFN_XIfEvent_PROC) (Display *, XEvent *, int (*)(Display *, XEvent *, XPointer), XPointer);
PFN_XIfEvent_PROC XIfEvent_PROC = 0;
#   define XIfEvent (assert(XIfEvent_PROC != 0), XIfEvent_PROC)

typedef int (* PFN_XImageByteOrder_PROC) (Display *);
PFN_XImageByteOrder_PROC XImageByteOrder_PROC = 0;
#   define XImageByteOrder (assert(XImageByteOrder_PROC != 0), XImageByteOrder_PROC)

typedef XExtCodes *(* PFN_XInitExtension_PROC) (Display *, const char *);
PFN_XInitExtension_PROC XInitExtension_PROC = 0;
#   define XInitExtension (assert(XInitExtension_PROC != 0), XInitExtension_PROC)

typedef int (* PFN_XInitImage_PROC) (XImage *);
PFN_XInitImage_PROC XInitImage_PROC = 0;
#   define XInitImage (assert(XInitImage_PROC != 0), XInitImage_PROC)

typedef int (* PFN_XInitThreads_PROC) (void);
PFN_XInitThreads_PROC XInitThreads_PROC = 0;
#   define XInitThreads (assert(XInitThreads_PROC != 0), XInitThreads_PROC)

typedef XModifierKeymap *(* PFN_XInsertModifiermapEntry_PROC) (XModifierKeymap *, KeyCode, int);
PFN_XInsertModifiermapEntry_PROC XInsertModifiermapEntry_PROC = 0;
#   define XInsertModifiermapEntry (assert(XInsertModifiermapEntry_PROC != 0), XInsertModifiermapEntry_PROC)

typedef int (* PFN_XInstallColormap_PROC) (Display *, Colormap);
PFN_XInstallColormap_PROC XInstallColormap_PROC = 0;
#   define XInstallColormap (assert(XInstallColormap_PROC != 0), XInstallColormap_PROC)

typedef Atom (* PFN_XInternAtom_PROC) (Display *, const char *, int);
PFN_XInternAtom_PROC XInternAtom_PROC = 0;
#   define XInternAtom (assert(XInternAtom_PROC != 0), XInternAtom_PROC)

typedef int (* PFN_XInternAtoms_PROC) (Display *, char **, int, int, Atom *);
PFN_XInternAtoms_PROC XInternAtoms_PROC = 0;
#   define XInternAtoms (assert(XInternAtoms_PROC != 0), XInternAtoms_PROC)

typedef int (* PFN_XInternalConnectionNumbers_PROC) (Display *, int **, int *);
PFN_XInternalConnectionNumbers_PROC XInternalConnectionNumbers_PROC = 0;
#   define XInternalConnectionNumbers (assert(XInternalConnectionNumbers_PROC != 0), XInternalConnectionNumbers_PROC)

typedef KeySym (* PFN_XKeycodeToKeysym_PROC) (Display *, KeyCode, int);
PFN_XKeycodeToKeysym_PROC XKeycodeToKeysym_PROC = 0;
#   define XKeycodeToKeysym (assert(XKeycodeToKeysym_PROC != 0), XKeycodeToKeysym_PROC)

typedef KeyCode (* PFN_XKeysymToKeycode_PROC) (Display *, KeySym);
PFN_XKeysymToKeycode_PROC XKeysymToKeycode_PROC = 0;
#   define XKeysymToKeycode (assert(XKeysymToKeycode_PROC != 0), XKeysymToKeycode_PROC)

typedef char *(* PFN_XKeysymToString_PROC) (KeySym);
PFN_XKeysymToString_PROC XKeysymToString_PROC = 0;
#   define XKeysymToString (assert(XKeysymToString_PROC != 0), XKeysymToString_PROC)

typedef int (* PFN_XKillClient_PROC) (Display *, XID);
PFN_XKillClient_PROC XKillClient_PROC = 0;
#   define XKillClient (assert(XKillClient_PROC != 0), XKillClient_PROC)

typedef unsigned long (* PFN_XLastKnownRequestProcessed_PROC) (Display *);
PFN_XLastKnownRequestProcessed_PROC XLastKnownRequestProcessed_PROC = 0;
#   define XLastKnownRequestProcessed (assert(XLastKnownRequestProcessed_PROC != 0), XLastKnownRequestProcessed_PROC)

typedef int *(* PFN_XListDepths_PROC) (Display *, int, int *);
PFN_XListDepths_PROC XListDepths_PROC = 0;
#   define XListDepths (assert(XListDepths_PROC != 0), XListDepths_PROC)

typedef char **(* PFN_XListExtensions_PROC) (Display *, int *);
PFN_XListExtensions_PROC XListExtensions_PROC = 0;
#   define XListExtensions (assert(XListExtensions_PROC != 0), XListExtensions_PROC)

typedef char **(* PFN_XListFonts_PROC) (Display *, const char *, int, int *);
PFN_XListFonts_PROC XListFonts_PROC = 0;
#   define XListFonts (assert(XListFonts_PROC != 0), XListFonts_PROC)

typedef char **(* PFN_XListFontsWithInfo_PROC) (Display *, const char *, int, int *, XFontStruct **);
PFN_XListFontsWithInfo_PROC XListFontsWithInfo_PROC = 0;
#   define XListFontsWithInfo (assert(XListFontsWithInfo_PROC != 0), XListFontsWithInfo_PROC)

typedef XHostAddress *(* PFN_XListHosts_PROC) (Display *, int *, int *);
PFN_XListHosts_PROC XListHosts_PROC = 0;
#   define XListHosts (assert(XListHosts_PROC != 0), XListHosts_PROC)

typedef Colormap *(* PFN_XListInstalledColormaps_PROC) (Display *, Window, int *);
PFN_XListInstalledColormaps_PROC XListInstalledColormaps_PROC = 0;
#   define XListInstalledColormaps (assert(XListInstalledColormaps_PROC != 0), XListInstalledColormaps_PROC)

typedef XPixmapFormatValues *(* PFN_XListPixmapFormats_PROC) (Display *, int *);
PFN_XListPixmapFormats_PROC XListPixmapFormats_PROC = 0;
#   define XListPixmapFormats (assert(XListPixmapFormats_PROC != 0), XListPixmapFormats_PROC)

typedef Atom *(* PFN_XListProperties_PROC) (Display *, Window, int *);
PFN_XListProperties_PROC XListProperties_PROC = 0;
#   define XListProperties (assert(XListProperties_PROC != 0), XListProperties_PROC)

typedef Font (* PFN_XLoadFont_PROC) (Display *, const char *);
PFN_XLoadFont_PROC XLoadFont_PROC = 0;
#   define XLoadFont (assert(XLoadFont_PROC != 0), XLoadFont_PROC)

typedef XFontStruct *(* PFN_XLoadQueryFont_PROC) (Display *, const char *);
PFN_XLoadQueryFont_PROC XLoadQueryFont_PROC = 0;
#   define XLoadQueryFont (assert(XLoadQueryFont_PROC != 0), XLoadQueryFont_PROC)

typedef char *(* PFN_XLocaleOfFontSet_PROC) (XFontSet);
PFN_XLocaleOfFontSet_PROC XLocaleOfFontSet_PROC = 0;
#   define XLocaleOfFontSet (assert(XLocaleOfFontSet_PROC != 0), XLocaleOfFontSet_PROC)

typedef char *(* PFN_XLocaleOfIM_PROC) (XIM);
PFN_XLocaleOfIM_PROC XLocaleOfIM_PROC = 0;
#   define XLocaleOfIM (assert(XLocaleOfIM_PROC != 0), XLocaleOfIM_PROC)

typedef char *(* PFN_XLocaleOfOM_PROC) (XOM);
PFN_XLocaleOfOM_PROC XLocaleOfOM_PROC = 0;
#   define XLocaleOfOM (assert(XLocaleOfOM_PROC != 0), XLocaleOfOM_PROC)

typedef void (* PFN_XLockDisplay_PROC) (Display *);
PFN_XLockDisplay_PROC XLockDisplay_PROC = 0;
#   define XLockDisplay (assert(XLockDisplay_PROC != 0), XLockDisplay_PROC)

typedef int (* PFN_XLookupColor_PROC) (Display *, Colormap, const char *, XColor *, XColor *);
PFN_XLookupColor_PROC XLookupColor_PROC = 0;
#   define XLookupColor (assert(XLookupColor_PROC != 0), XLookupColor_PROC)

typedef KeySym (* PFN_XLookupKeysym_PROC) (XKeyEvent *, int);
PFN_XLookupKeysym_PROC XLookupKeysym_PROC = 0;
#   define XLookupKeysym (assert(XLookupKeysym_PROC != 0), XLookupKeysym_PROC)

typedef int (* PFN_XLowerWindow_PROC) (Display *, Window);
PFN_XLowerWindow_PROC XLowerWindow_PROC = 0;
#   define XLowerWindow (assert(XLowerWindow_PROC != 0), XLowerWindow_PROC)

typedef int (* PFN_XMapRaised_PROC) (Display *, Window);
PFN_XMapRaised_PROC XMapRaised_PROC = 0;
#   define XMapRaised (assert(XMapRaised_PROC != 0), XMapRaised_PROC)

typedef int (* PFN_XMapSubwindows_PROC) (Display *, Window);
PFN_XMapSubwindows_PROC XMapSubwindows_PROC = 0;
#   define XMapSubwindows (assert(XMapSubwindows_PROC != 0), XMapSubwindows_PROC)

typedef int (* PFN_XMapWindow_PROC) (Display *, Window);
PFN_XMapWindow_PROC XMapWindow_PROC = 0;
#   define XMapWindow (assert(XMapWindow_PROC != 0), XMapWindow_PROC)

typedef int (* PFN_XMaskEvent_PROC) (Display *, long, XEvent *);
PFN_XMaskEvent_PROC XMaskEvent_PROC = 0;
#   define XMaskEvent (assert(XMaskEvent_PROC != 0), XMaskEvent_PROC)

typedef int (* PFN_XMaxCmapsOfScreen_PROC) (Screen *);
PFN_XMaxCmapsOfScreen_PROC XMaxCmapsOfScreen_PROC = 0;
#   define XMaxCmapsOfScreen (assert(XMaxCmapsOfScreen_PROC != 0), XMaxCmapsOfScreen_PROC)

typedef long (* PFN_XMaxRequestSize_PROC) (Display *);
PFN_XMaxRequestSize_PROC XMaxRequestSize_PROC = 0;
#   define XMaxRequestSize (assert(XMaxRequestSize_PROC != 0), XMaxRequestSize_PROC)

typedef int (* PFN_XMinCmapsOfScreen_PROC) (Screen *);
PFN_XMinCmapsOfScreen_PROC XMinCmapsOfScreen_PROC = 0;
#   define XMinCmapsOfScreen (assert(XMinCmapsOfScreen_PROC != 0), XMinCmapsOfScreen_PROC)

typedef int (* PFN_XMoveResizeWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int);
PFN_XMoveResizeWindow_PROC XMoveResizeWindow_PROC = 0;
#   define XMoveResizeWindow (assert(XMoveResizeWindow_PROC != 0), XMoveResizeWindow_PROC)

typedef int (* PFN_XMoveWindow_PROC) (Display *, Window, int, int);
PFN_XMoveWindow_PROC XMoveWindow_PROC = 0;
#   define XMoveWindow (assert(XMoveWindow_PROC != 0), XMoveWindow_PROC)

typedef XModifierKeymap *(* PFN_XNewModifiermap_PROC) (int);
PFN_XNewModifiermap_PROC XNewModifiermap_PROC = 0;
#   define XNewModifiermap (assert(XNewModifiermap_PROC != 0), XNewModifiermap_PROC)

typedef int (* PFN_XNextEvent_PROC) (Display *, XEvent *);
PFN_XNextEvent_PROC XNextEvent_PROC = 0;
#   define XNextEvent (assert(XNextEvent_PROC != 0), XNextEvent_PROC)

typedef unsigned long (* PFN_XNextRequest_PROC) (Display *);
PFN_XNextRequest_PROC XNextRequest_PROC = 0;
#   define XNextRequest (assert(XNextRequest_PROC != 0), XNextRequest_PROC)

typedef int (* PFN_XNoOp_PROC) (Display *);
PFN_XNoOp_PROC XNoOp_PROC = 0;
#   define XNoOp (assert(XNoOp_PROC != 0), XNoOp_PROC)

typedef XOM (* PFN_XOMOfOC_PROC) (XOC);
PFN_XOMOfOC_PROC XOMOfOC_PROC = 0;
#   define XOMOfOC (assert(XOMOfOC_PROC != 0), XOMOfOC_PROC)

typedef Display *(* PFN_XOpenDisplay_PROC) (const char *);
PFN_XOpenDisplay_PROC XOpenDisplay_PROC = 0;
#   define XOpenDisplay (assert(XOpenDisplay_PROC != 0), XOpenDisplay_PROC)

typedef XIM (* PFN_XOpenIM_PROC) (Display *, struct _XrmHashBucketRec *, char *, char *);
PFN_XOpenIM_PROC XOpenIM_PROC = 0;
#   define XOpenIM (assert(XOpenIM_PROC != 0), XOpenIM_PROC)

typedef XOM (* PFN_XOpenOM_PROC) (Display *, struct _XrmHashBucketRec *, const char *, const char *);
PFN_XOpenOM_PROC XOpenOM_PROC = 0;
#   define XOpenOM (assert(XOpenOM_PROC != 0), XOpenOM_PROC)

typedef int (* PFN_XParseColor_PROC) (Display *, Colormap, const char *, XColor *);
PFN_XParseColor_PROC XParseColor_PROC = 0;
#   define XParseColor (assert(XParseColor_PROC != 0), XParseColor_PROC)

typedef int (* PFN_XParseGeometry_PROC) (const char *, int *, int *, unsigned int *, unsigned int *);
PFN_XParseGeometry_PROC XParseGeometry_PROC = 0;
#   define XParseGeometry (assert(XParseGeometry_PROC != 0), XParseGeometry_PROC)

typedef int (* PFN_XPeekEvent_PROC) (Display *, XEvent *);
PFN_XPeekEvent_PROC XPeekEvent_PROC = 0;
#   define XPeekEvent (assert(XPeekEvent_PROC != 0), XPeekEvent_PROC)

typedef int (* PFN_XPeekIfEvent_PROC) (Display *, XEvent *, int (*)(Display *, XEvent *, XPointer), XPointer);
PFN_XPeekIfEvent_PROC XPeekIfEvent_PROC = 0;
#   define XPeekIfEvent (assert(XPeekIfEvent_PROC != 0), XPeekIfEvent_PROC)

typedef int (* PFN_XPending_PROC) (Display *);
PFN_XPending_PROC XPending_PROC = 0;
#   define XPending (assert(XPending_PROC != 0), XPending_PROC)

typedef int (* PFN_XPlanesOfScreen_PROC) (Screen *);
PFN_XPlanesOfScreen_PROC XPlanesOfScreen_PROC = 0;
#   define XPlanesOfScreen (assert(XPlanesOfScreen_PROC != 0), XPlanesOfScreen_PROC)

typedef void (* PFN_XProcessInternalConnection_PROC) (Display *, int);
PFN_XProcessInternalConnection_PROC XProcessInternalConnection_PROC = 0;
#   define XProcessInternalConnection (assert(XProcessInternalConnection_PROC != 0), XProcessInternalConnection_PROC)

typedef int (* PFN_XProtocolRevision_PROC) (Display *);
PFN_XProtocolRevision_PROC XProtocolRevision_PROC = 0;
#   define XProtocolRevision (assert(XProtocolRevision_PROC != 0), XProtocolRevision_PROC)

typedef int (* PFN_XProtocolVersion_PROC) (Display *);
PFN_XProtocolVersion_PROC XProtocolVersion_PROC = 0;
#   define XProtocolVersion (assert(XProtocolVersion_PROC != 0), XProtocolVersion_PROC)

typedef int (* PFN_XPutBackEvent_PROC) (Display *, XEvent *);
PFN_XPutBackEvent_PROC XPutBackEvent_PROC = 0;
#   define XPutBackEvent (assert(XPutBackEvent_PROC != 0), XPutBackEvent_PROC)

typedef int (* PFN_XPutImage_PROC) (Display *, Drawable, GC, XImage *, int, int, int, int, unsigned int, unsigned int);
PFN_XPutImage_PROC XPutImage_PROC = 0;
#   define XPutImage (assert(XPutImage_PROC != 0), XPutImage_PROC)

typedef int (* PFN_XQLength_PROC) (Display *);
PFN_XQLength_PROC XQLength_PROC = 0;
#   define XQLength (assert(XQLength_PROC != 0), XQLength_PROC)

typedef int (* PFN_XQueryBestCursor_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestCursor_PROC XQueryBestCursor_PROC = 0;
#   define XQueryBestCursor (assert(XQueryBestCursor_PROC != 0), XQueryBestCursor_PROC)

typedef int (* PFN_XQueryBestSize_PROC) (Display *, int, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestSize_PROC XQueryBestSize_PROC = 0;
#   define XQueryBestSize (assert(XQueryBestSize_PROC != 0), XQueryBestSize_PROC)

typedef int (* PFN_XQueryBestStipple_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestStipple_PROC XQueryBestStipple_PROC = 0;
#   define XQueryBestStipple (assert(XQueryBestStipple_PROC != 0), XQueryBestStipple_PROC)

typedef int (* PFN_XQueryBestTile_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestTile_PROC XQueryBestTile_PROC = 0;
#   define XQueryBestTile (assert(XQueryBestTile_PROC != 0), XQueryBestTile_PROC)

typedef int (* PFN_XQueryColor_PROC) (Display *, Colormap, XColor *);
PFN_XQueryColor_PROC XQueryColor_PROC = 0;
#   define XQueryColor (assert(XQueryColor_PROC != 0), XQueryColor_PROC)

typedef int (* PFN_XQueryColors_PROC) (Display *, Colormap, XColor *, int);
PFN_XQueryColors_PROC XQueryColors_PROC = 0;
#   define XQueryColors (assert(XQueryColors_PROC != 0), XQueryColors_PROC)

typedef int (* PFN_XQueryExtension_PROC) (Display *, const char *, int *, int *, int *);
PFN_XQueryExtension_PROC XQueryExtension_PROC = 0;
#   define XQueryExtension (assert(XQueryExtension_PROC != 0), XQueryExtension_PROC)

typedef XFontStruct *(* PFN_XQueryFont_PROC) (Display *, XID);
PFN_XQueryFont_PROC XQueryFont_PROC = 0;
#   define XQueryFont (assert(XQueryFont_PROC != 0), XQueryFont_PROC)

typedef int (* PFN_XQueryKeymap_PROC) (Display *, char[32]);
PFN_XQueryKeymap_PROC XQueryKeymap_PROC = 0;
#   define XQueryKeymap (assert(XQueryKeymap_PROC != 0), XQueryKeymap_PROC)

typedef int (* PFN_XQueryPointer_PROC) (Display *, Window, Window *, Window *, int *, int *, int *, int *, unsigned int *);
PFN_XQueryPointer_PROC XQueryPointer_PROC = 0;
#   define XQueryPointer (assert(XQueryPointer_PROC != 0), XQueryPointer_PROC)

typedef int (* PFN_XQueryTextExtents_PROC) (Display *, XID, const char *, int, int *, int *, int *, XCharStruct *);
PFN_XQueryTextExtents_PROC XQueryTextExtents_PROC = 0;
#   define XQueryTextExtents (assert(XQueryTextExtents_PROC != 0), XQueryTextExtents_PROC)

typedef int (* PFN_XQueryTextExtents16_PROC) (Display *, XID, const XChar2b *, int, int *, int *, int *, XCharStruct *);
PFN_XQueryTextExtents16_PROC XQueryTextExtents16_PROC = 0;
#   define XQueryTextExtents16 (assert(XQueryTextExtents16_PROC != 0), XQueryTextExtents16_PROC)

typedef int (* PFN_XQueryTree_PROC) (Display *, Window, Window *, Window *, Window **, unsigned int *);
PFN_XQueryTree_PROC XQueryTree_PROC = 0;
#   define XQueryTree (assert(XQueryTree_PROC != 0), XQueryTree_PROC)

typedef int (* PFN_XRaiseWindow_PROC) (Display *, Window);
PFN_XRaiseWindow_PROC XRaiseWindow_PROC = 0;
#   define XRaiseWindow (assert(XRaiseWindow_PROC != 0), XRaiseWindow_PROC)

typedef int (* PFN_XReadBitmapFile_PROC) (Display *, Drawable, const char *, unsigned int *, unsigned int *, Pixmap *, int *, int *);
PFN_XReadBitmapFile_PROC XReadBitmapFile_PROC = 0;
#   define XReadBitmapFile (assert(XReadBitmapFile_PROC != 0), XReadBitmapFile_PROC)

typedef int (* PFN_XReadBitmapFileData_PROC) (const char *, unsigned int *, unsigned int *, unsigned char **, int *, int *);
PFN_XReadBitmapFileData_PROC XReadBitmapFileData_PROC = 0;
#   define XReadBitmapFileData (assert(XReadBitmapFileData_PROC != 0), XReadBitmapFileData_PROC)

typedef int (* PFN_XRebindKeysym_PROC) (Display *, KeySym, KeySym *, int, const unsigned char *, int);
PFN_XRebindKeysym_PROC XRebindKeysym_PROC = 0;
#   define XRebindKeysym (assert(XRebindKeysym_PROC != 0), XRebindKeysym_PROC)

typedef int (* PFN_XRecolorCursor_PROC) (Display *, Cursor, XColor *, XColor *);
PFN_XRecolorCursor_PROC XRecolorCursor_PROC = 0;
#   define XRecolorCursor (assert(XRecolorCursor_PROC != 0), XRecolorCursor_PROC)

typedef int (* PFN_XReconfigureWMWindow_PROC) (Display *, Window, int, unsigned int, XWindowChanges *);
PFN_XReconfigureWMWindow_PROC XReconfigureWMWindow_PROC = 0;
#   define XReconfigureWMWindow (assert(XReconfigureWMWindow_PROC != 0), XReconfigureWMWindow_PROC)

typedef int (* PFN_XRefreshKeyboardMapping_PROC) (XMappingEvent *);
PFN_XRefreshKeyboardMapping_PROC XRefreshKeyboardMapping_PROC = 0;
#   define XRefreshKeyboardMapping (assert(XRefreshKeyboardMapping_PROC != 0), XRefreshKeyboardMapping_PROC)

typedef int (* PFN_XRegisterIMInstantiateCallback_PROC) (Display *, struct _XrmHashBucketRec *, char *, char *, XIDProc, XPointer);
PFN_XRegisterIMInstantiateCallback_PROC XRegisterIMInstantiateCallback_PROC = 0;
#   define XRegisterIMInstantiateCallback (assert(XRegisterIMInstantiateCallback_PROC != 0), XRegisterIMInstantiateCallback_PROC)

typedef void (* PFN_XRemoveConnectionWatch_PROC) (Display *, XConnectionWatchProc, XPointer);
PFN_XRemoveConnectionWatch_PROC XRemoveConnectionWatch_PROC = 0;
#   define XRemoveConnectionWatch (assert(XRemoveConnectionWatch_PROC != 0), XRemoveConnectionWatch_PROC)

typedef int (* PFN_XRemoveFromSaveSet_PROC) (Display *, Window);
PFN_XRemoveFromSaveSet_PROC XRemoveFromSaveSet_PROC = 0;
#   define XRemoveFromSaveSet (assert(XRemoveFromSaveSet_PROC != 0), XRemoveFromSaveSet_PROC)

typedef int (* PFN_XRemoveHost_PROC) (Display *, XHostAddress *);
PFN_XRemoveHost_PROC XRemoveHost_PROC = 0;
#   define XRemoveHost (assert(XRemoveHost_PROC != 0), XRemoveHost_PROC)

typedef int (* PFN_XRemoveHosts_PROC) (Display *, XHostAddress *, int);
PFN_XRemoveHosts_PROC XRemoveHosts_PROC = 0;
#   define XRemoveHosts (assert(XRemoveHosts_PROC != 0), XRemoveHosts_PROC)

typedef int (* PFN_XReparentWindow_PROC) (Display *, Window, Window, int, int);
PFN_XReparentWindow_PROC XReparentWindow_PROC = 0;
#   define XReparentWindow (assert(XReparentWindow_PROC != 0), XReparentWindow_PROC)

typedef int (* PFN_XResetScreenSaver_PROC) (Display *);
PFN_XResetScreenSaver_PROC XResetScreenSaver_PROC = 0;
#   define XResetScreenSaver (assert(XResetScreenSaver_PROC != 0), XResetScreenSaver_PROC)

typedef int (* PFN_XResizeWindow_PROC) (Display *, Window, unsigned int, unsigned int);
PFN_XResizeWindow_PROC XResizeWindow_PROC = 0;
#   define XResizeWindow (assert(XResizeWindow_PROC != 0), XResizeWindow_PROC)

typedef char *(* PFN_XResourceManagerString_PROC) (Display *);
PFN_XResourceManagerString_PROC XResourceManagerString_PROC = 0;
#   define XResourceManagerString (assert(XResourceManagerString_PROC != 0), XResourceManagerString_PROC)

typedef int (* PFN_XRestackWindows_PROC) (Display *, Window *, int);
PFN_XRestackWindows_PROC XRestackWindows_PROC = 0;
#   define XRestackWindows (assert(XRestackWindows_PROC != 0), XRestackWindows_PROC)

typedef Window (* PFN_XRootWindow_PROC) (Display *, int);
PFN_XRootWindow_PROC XRootWindow_PROC = 0;
#   define XRootWindow (assert(XRootWindow_PROC != 0), XRootWindow_PROC)

typedef Window (* PFN_XRootWindowOfScreen_PROC) (Screen *);
PFN_XRootWindowOfScreen_PROC XRootWindowOfScreen_PROC = 0;
#   define XRootWindowOfScreen (assert(XRootWindowOfScreen_PROC != 0), XRootWindowOfScreen_PROC)

typedef int (* PFN_XRotateBuffers_PROC) (Display *, int);
PFN_XRotateBuffers_PROC XRotateBuffers_PROC = 0;
#   define XRotateBuffers (assert(XRotateBuffers_PROC != 0), XRotateBuffers_PROC)

typedef int (* PFN_XRotateWindowProperties_PROC) (Display *, Window, Atom *, int, int);
PFN_XRotateWindowProperties_PROC XRotateWindowProperties_PROC = 0;
#   define XRotateWindowProperties (assert(XRotateWindowProperties_PROC != 0), XRotateWindowProperties_PROC)

typedef int (* PFN_XScreenCount_PROC) (Display *);
PFN_XScreenCount_PROC XScreenCount_PROC = 0;
#   define XScreenCount (assert(XScreenCount_PROC != 0), XScreenCount_PROC)

typedef int (* PFN_XScreenNumberOfScreen_PROC) (Screen *);
PFN_XScreenNumberOfScreen_PROC XScreenNumberOfScreen_PROC = 0;
#   define XScreenNumberOfScreen (assert(XScreenNumberOfScreen_PROC != 0), XScreenNumberOfScreen_PROC)

typedef Screen *(* PFN_XScreenOfDisplay_PROC) (Display *, int);
PFN_XScreenOfDisplay_PROC XScreenOfDisplay_PROC = 0;
#   define XScreenOfDisplay (assert(XScreenOfDisplay_PROC != 0), XScreenOfDisplay_PROC)

typedef char *(* PFN_XScreenResourceString_PROC) (Screen *);
PFN_XScreenResourceString_PROC XScreenResourceString_PROC = 0;
#   define XScreenResourceString (assert(XScreenResourceString_PROC != 0), XScreenResourceString_PROC)

typedef int (* PFN_XSelectInput_PROC) (Display *, Window, long);
PFN_XSelectInput_PROC XSelectInput_PROC = 0;
#   define XSelectInput (assert(XSelectInput_PROC != 0), XSelectInput_PROC)

typedef int (* PFN_XSendEvent_PROC) (Display *, Window, int, long, XEvent *);
PFN_XSendEvent_PROC XSendEvent_PROC = 0;
#   define XSendEvent (assert(XSendEvent_PROC != 0), XSendEvent_PROC)

typedef char *(* PFN_XServerVendor_PROC) (Display *);
PFN_XServerVendor_PROC XServerVendor_PROC = 0;
#   define XServerVendor (assert(XServerVendor_PROC != 0), XServerVendor_PROC)

typedef int (* PFN_XSetAccessControl_PROC) (Display *, int);
PFN_XSetAccessControl_PROC XSetAccessControl_PROC = 0;
#   define XSetAccessControl (assert(XSetAccessControl_PROC != 0), XSetAccessControl_PROC)

typedef int (* PFN_XSetArcMode_PROC) (Display *, GC, int);
PFN_XSetArcMode_PROC XSetArcMode_PROC = 0;
#   define XSetArcMode (assert(XSetArcMode_PROC != 0), XSetArcMode_PROC)

typedef void (* PFN_XSetAuthorization_PROC) (char *, int, char *, int);
PFN_XSetAuthorization_PROC XSetAuthorization_PROC = 0;
#   define XSetAuthorization (assert(XSetAuthorization_PROC != 0), XSetAuthorization_PROC)

typedef int (* PFN_XSetBackground_PROC) (Display *, GC, unsigned long);
PFN_XSetBackground_PROC XSetBackground_PROC = 0;
#   define XSetBackground (assert(XSetBackground_PROC != 0), XSetBackground_PROC)

typedef int (* PFN_XSetClipMask_PROC) (Display *, GC, Pixmap);
PFN_XSetClipMask_PROC XSetClipMask_PROC = 0;
#   define XSetClipMask (assert(XSetClipMask_PROC != 0), XSetClipMask_PROC)

typedef int (* PFN_XSetClipOrigin_PROC) (Display *, GC, int, int);
PFN_XSetClipOrigin_PROC XSetClipOrigin_PROC = 0;
#   define XSetClipOrigin (assert(XSetClipOrigin_PROC != 0), XSetClipOrigin_PROC)

typedef int (* PFN_XSetClipRectangles_PROC) (Display *, GC, int, int, XRectangle *, int, int);
PFN_XSetClipRectangles_PROC XSetClipRectangles_PROC = 0;
#   define XSetClipRectangles (assert(XSetClipRectangles_PROC != 0), XSetClipRectangles_PROC)

typedef int (* PFN_XSetCloseDownMode_PROC) (Display *, int);
PFN_XSetCloseDownMode_PROC XSetCloseDownMode_PROC = 0;
#   define XSetCloseDownMode (assert(XSetCloseDownMode_PROC != 0), XSetCloseDownMode_PROC)

typedef int (* PFN_XSetCommand_PROC) (Display *, Window, char **, int);
PFN_XSetCommand_PROC XSetCommand_PROC = 0;
#   define XSetCommand (assert(XSetCommand_PROC != 0), XSetCommand_PROC)

typedef int (* PFN_XSetDashes_PROC) (Display *, GC, int, const char *, int);
PFN_XSetDashes_PROC XSetDashes_PROC = 0;
#   define XSetDashes (assert(XSetDashes_PROC != 0), XSetDashes_PROC)

typedef XErrorHandler (* PFN_XSetErrorHandler_PROC) (XErrorHandler);
PFN_XSetErrorHandler_PROC XSetErrorHandler_PROC = 0;
#   define XSetErrorHandler (assert(XSetErrorHandler_PROC != 0), XSetErrorHandler_PROC)

typedef int (* PFN_XSetFillRule_PROC) (Display *, GC, int);
PFN_XSetFillRule_PROC XSetFillRule_PROC = 0;
#   define XSetFillRule (assert(XSetFillRule_PROC != 0), XSetFillRule_PROC)

typedef int (* PFN_XSetFillStyle_PROC) (Display *, GC, int);
PFN_XSetFillStyle_PROC XSetFillStyle_PROC = 0;
#   define XSetFillStyle (assert(XSetFillStyle_PROC != 0), XSetFillStyle_PROC)

typedef int (* PFN_XSetFont_PROC) (Display *, GC, Font);
PFN_XSetFont_PROC XSetFont_PROC = 0;
#   define XSetFont (assert(XSetFont_PROC != 0), XSetFont_PROC)

typedef int (* PFN_XSetFontPath_PROC) (Display *, char **, int);
PFN_XSetFontPath_PROC XSetFontPath_PROC = 0;
#   define XSetFontPath (assert(XSetFontPath_PROC != 0), XSetFontPath_PROC)

typedef int (* PFN_XSetForeground_PROC) (Display *, GC, unsigned long);
PFN_XSetForeground_PROC XSetForeground_PROC = 0;
#   define XSetForeground (assert(XSetForeground_PROC != 0), XSetForeground_PROC)

typedef int (* PFN_XSetFunction_PROC) (Display *, GC, int);
PFN_XSetFunction_PROC XSetFunction_PROC = 0;
#   define XSetFunction (assert(XSetFunction_PROC != 0), XSetFunction_PROC)

typedef int (* PFN_XSetGraphicsExposures_PROC) (Display *, GC, int);
PFN_XSetGraphicsExposures_PROC XSetGraphicsExposures_PROC = 0;
#   define XSetGraphicsExposures (assert(XSetGraphicsExposures_PROC != 0), XSetGraphicsExposures_PROC)

typedef void (* PFN_XSetICFocus_PROC) (XIC);
PFN_XSetICFocus_PROC XSetICFocus_PROC = 0;
#   define XSetICFocus (assert(XSetICFocus_PROC != 0), XSetICFocus_PROC)

typedef char *(* PFN_XSetICValues_PROC) (XIC, ...);
PFN_XSetICValues_PROC XSetICValues_PROC = 0;
#   define XSetICValues (assert(XSetICValues_PROC != 0), XSetICValues_PROC)

typedef char *(* PFN_XSetIMValues_PROC) (XIM, ...);
PFN_XSetIMValues_PROC XSetIMValues_PROC = 0;
#   define XSetIMValues (assert(XSetIMValues_PROC != 0), XSetIMValues_PROC)

typedef void (* PFN_XSetIOErrorExitHandler_PROC) (Display *, XIOErrorExitHandler, void *);
PFN_XSetIOErrorExitHandler_PROC XSetIOErrorExitHandler_PROC = 0;
#   define XSetIOErrorExitHandler (assert(XSetIOErrorExitHandler_PROC != 0), XSetIOErrorExitHandler_PROC)

typedef XIOErrorHandler (* PFN_XSetIOErrorHandler_PROC) (XIOErrorHandler);
PFN_XSetIOErrorHandler_PROC XSetIOErrorHandler_PROC = 0;
#   define XSetIOErrorHandler (assert(XSetIOErrorHandler_PROC != 0), XSetIOErrorHandler_PROC)

typedef int (* PFN_XSetIconName_PROC) (Display *, Window, const char *);
PFN_XSetIconName_PROC XSetIconName_PROC = 0;
#   define XSetIconName (assert(XSetIconName_PROC != 0), XSetIconName_PROC)

typedef int (* PFN_XSetInputFocus_PROC) (Display *, Window, int, Time);
PFN_XSetInputFocus_PROC XSetInputFocus_PROC = 0;
#   define XSetInputFocus (assert(XSetInputFocus_PROC != 0), XSetInputFocus_PROC)

typedef int (* PFN_XSetLineAttributes_PROC) (Display *, GC, unsigned int, int, int, int);
PFN_XSetLineAttributes_PROC XSetLineAttributes_PROC = 0;
#   define XSetLineAttributes (assert(XSetLineAttributes_PROC != 0), XSetLineAttributes_PROC)

typedef char *(* PFN_XSetLocaleModifiers_PROC) (const char *);
PFN_XSetLocaleModifiers_PROC XSetLocaleModifiers_PROC = 0;
#   define XSetLocaleModifiers (assert(XSetLocaleModifiers_PROC != 0), XSetLocaleModifiers_PROC)

typedef int (* PFN_XSetModifierMapping_PROC) (Display *, XModifierKeymap *);
PFN_XSetModifierMapping_PROC XSetModifierMapping_PROC = 0;
#   define XSetModifierMapping (assert(XSetModifierMapping_PROC != 0), XSetModifierMapping_PROC)

typedef char *(* PFN_XSetOCValues_PROC) (XOC, ...);
PFN_XSetOCValues_PROC XSetOCValues_PROC = 0;
#   define XSetOCValues (assert(XSetOCValues_PROC != 0), XSetOCValues_PROC)

typedef char *(* PFN_XSetOMValues_PROC) (XOM, ...);
PFN_XSetOMValues_PROC XSetOMValues_PROC = 0;
#   define XSetOMValues (assert(XSetOMValues_PROC != 0), XSetOMValues_PROC)

typedef int (* PFN_XSetPlaneMask_PROC) (Display *, GC, unsigned long);
PFN_XSetPlaneMask_PROC XSetPlaneMask_PROC = 0;
#   define XSetPlaneMask (assert(XSetPlaneMask_PROC != 0), XSetPlaneMask_PROC)

typedef int (* PFN_XSetPointerMapping_PROC) (Display *, const unsigned char *, int);
PFN_XSetPointerMapping_PROC XSetPointerMapping_PROC = 0;
#   define XSetPointerMapping (assert(XSetPointerMapping_PROC != 0), XSetPointerMapping_PROC)

typedef int (* PFN_XSetScreenSaver_PROC) (Display *, int, int, int, int);
PFN_XSetScreenSaver_PROC XSetScreenSaver_PROC = 0;
#   define XSetScreenSaver (assert(XSetScreenSaver_PROC != 0), XSetScreenSaver_PROC)

typedef int (* PFN_XSetSelectionOwner_PROC) (Display *, Atom, Window, Time);
PFN_XSetSelectionOwner_PROC XSetSelectionOwner_PROC = 0;
#   define XSetSelectionOwner (assert(XSetSelectionOwner_PROC != 0), XSetSelectionOwner_PROC)

typedef int (* PFN_XSetState_PROC) (Display *, GC, unsigned long, unsigned long, int, unsigned long);
PFN_XSetState_PROC XSetState_PROC = 0;
#   define XSetState (assert(XSetState_PROC != 0), XSetState_PROC)

typedef int (* PFN_XSetStipple_PROC) (Display *, GC, Pixmap);
PFN_XSetStipple_PROC XSetStipple_PROC = 0;
#   define XSetStipple (assert(XSetStipple_PROC != 0), XSetStipple_PROC)

typedef int (* PFN_XSetSubwindowMode_PROC) (Display *, GC, int);
PFN_XSetSubwindowMode_PROC XSetSubwindowMode_PROC = 0;
#   define XSetSubwindowMode (assert(XSetSubwindowMode_PROC != 0), XSetSubwindowMode_PROC)

typedef int (* PFN_XSetTSOrigin_PROC) (Display *, GC, int, int);
PFN_XSetTSOrigin_PROC XSetTSOrigin_PROC = 0;
#   define XSetTSOrigin (assert(XSetTSOrigin_PROC != 0), XSetTSOrigin_PROC)

typedef int (* PFN_XSetTile_PROC) (Display *, GC, Pixmap);
PFN_XSetTile_PROC XSetTile_PROC = 0;
#   define XSetTile (assert(XSetTile_PROC != 0), XSetTile_PROC)

typedef int (* PFN_XSetTransientForHint_PROC) (Display *, Window, Window);
PFN_XSetTransientForHint_PROC XSetTransientForHint_PROC = 0;
#   define XSetTransientForHint (assert(XSetTransientForHint_PROC != 0), XSetTransientForHint_PROC)

typedef int (* PFN_XSetWMColormapWindows_PROC) (Display *, Window, Window *, int);
PFN_XSetWMColormapWindows_PROC XSetWMColormapWindows_PROC = 0;
#   define XSetWMColormapWindows (assert(XSetWMColormapWindows_PROC != 0), XSetWMColormapWindows_PROC)

typedef int (* PFN_XSetWMProtocols_PROC) (Display *, Window, Atom *, int);
PFN_XSetWMProtocols_PROC XSetWMProtocols_PROC = 0;
#   define XSetWMProtocols (assert(XSetWMProtocols_PROC != 0), XSetWMProtocols_PROC)

typedef int (* PFN_XSetWindowBackground_PROC) (Display *, Window, unsigned long);
PFN_XSetWindowBackground_PROC XSetWindowBackground_PROC = 0;
#   define XSetWindowBackground (assert(XSetWindowBackground_PROC != 0), XSetWindowBackground_PROC)

typedef int (* PFN_XSetWindowBackgroundPixmap_PROC) (Display *, Window, Pixmap);
PFN_XSetWindowBackgroundPixmap_PROC XSetWindowBackgroundPixmap_PROC = 0;
#   define XSetWindowBackgroundPixmap (assert(XSetWindowBackgroundPixmap_PROC != 0), XSetWindowBackgroundPixmap_PROC)

typedef int (* PFN_XSetWindowBorder_PROC) (Display *, Window, unsigned long);
PFN_XSetWindowBorder_PROC XSetWindowBorder_PROC = 0;
#   define XSetWindowBorder (assert(XSetWindowBorder_PROC != 0), XSetWindowBorder_PROC)

typedef int (* PFN_XSetWindowBorderPixmap_PROC) (Display *, Window, Pixmap);
PFN_XSetWindowBorderPixmap_PROC XSetWindowBorderPixmap_PROC = 0;
#   define XSetWindowBorderPixmap (assert(XSetWindowBorderPixmap_PROC != 0), XSetWindowBorderPixmap_PROC)

typedef int (* PFN_XSetWindowBorderWidth_PROC) (Display *, Window, unsigned int);
PFN_XSetWindowBorderWidth_PROC XSetWindowBorderWidth_PROC = 0;
#   define XSetWindowBorderWidth (assert(XSetWindowBorderWidth_PROC != 0), XSetWindowBorderWidth_PROC)

typedef int (* PFN_XSetWindowColormap_PROC) (Display *, Window, Colormap);
PFN_XSetWindowColormap_PROC XSetWindowColormap_PROC = 0;
#   define XSetWindowColormap (assert(XSetWindowColormap_PROC != 0), XSetWindowColormap_PROC)

typedef int (* PFN_XStoreBuffer_PROC) (Display *, const char *, int, int);
PFN_XStoreBuffer_PROC XStoreBuffer_PROC = 0;
#   define XStoreBuffer (assert(XStoreBuffer_PROC != 0), XStoreBuffer_PROC)

typedef int (* PFN_XStoreBytes_PROC) (Display *, const char *, int);
PFN_XStoreBytes_PROC XStoreBytes_PROC = 0;
#   define XStoreBytes (assert(XStoreBytes_PROC != 0), XStoreBytes_PROC)

typedef int (* PFN_XStoreColor_PROC) (Display *, Colormap, XColor *);
PFN_XStoreColor_PROC XStoreColor_PROC = 0;
#   define XStoreColor (assert(XStoreColor_PROC != 0), XStoreColor_PROC)

typedef int (* PFN_XStoreColors_PROC) (Display *, Colormap, XColor *, int);
PFN_XStoreColors_PROC XStoreColors_PROC = 0;
#   define XStoreColors (assert(XStoreColors_PROC != 0), XStoreColors_PROC)

typedef int (* PFN_XStoreName_PROC) (Display *, Window, const char *);
PFN_XStoreName_PROC XStoreName_PROC = 0;
#   define XStoreName (assert(XStoreName_PROC != 0), XStoreName_PROC)

typedef int (* PFN_XStoreNamedColor_PROC) (Display *, Colormap, const char *, unsigned long, int);
PFN_XStoreNamedColor_PROC XStoreNamedColor_PROC = 0;
#   define XStoreNamedColor (assert(XStoreNamedColor_PROC != 0), XStoreNamedColor_PROC)

typedef KeySym (* PFN_XStringToKeysym_PROC) (const char *);
PFN_XStringToKeysym_PROC XStringToKeysym_PROC = 0;
#   define XStringToKeysym (assert(XStringToKeysym_PROC != 0), XStringToKeysym_PROC)

typedef int (* PFN_XSupportsLocale_PROC) (void);
PFN_XSupportsLocale_PROC XSupportsLocale_PROC = 0;
#   define XSupportsLocale (assert(XSupportsLocale_PROC != 0), XSupportsLocale_PROC)

typedef int (* PFN_XSync_PROC) (Display *, int);
PFN_XSync_PROC XSync_PROC = 0;
#   define XSync (assert(XSync_PROC != 0), XSync_PROC)

typedef int (* PFN_XTextExtents_PROC) (XFontStruct *, const char *, int, int *, int *, int *, XCharStruct *);
PFN_XTextExtents_PROC XTextExtents_PROC = 0;
#   define XTextExtents (assert(XTextExtents_PROC != 0), XTextExtents_PROC)

typedef int (* PFN_XTextExtents16_PROC) (XFontStruct *, const XChar2b *, int, int *, int *, int *, XCharStruct *);
PFN_XTextExtents16_PROC XTextExtents16_PROC = 0;
#   define XTextExtents16 (assert(XTextExtents16_PROC != 0), XTextExtents16_PROC)

typedef int (* PFN_XTextWidth_PROC) (XFontStruct *, const char *, int);
PFN_XTextWidth_PROC XTextWidth_PROC = 0;
#   define XTextWidth (assert(XTextWidth_PROC != 0), XTextWidth_PROC)

typedef int (* PFN_XTextWidth16_PROC) (XFontStruct *, const XChar2b *, int);
PFN_XTextWidth16_PROC XTextWidth16_PROC = 0;
#   define XTextWidth16 (assert(XTextWidth16_PROC != 0), XTextWidth16_PROC)

typedef int (* PFN_XTranslateCoordinates_PROC) (Display *, Window, Window, int, int, int *, int *, Window *);
PFN_XTranslateCoordinates_PROC XTranslateCoordinates_PROC = 0;
#   define XTranslateCoordinates (assert(XTranslateCoordinates_PROC != 0), XTranslateCoordinates_PROC)

typedef int (* PFN_XUndefineCursor_PROC) (Display *, Window);
PFN_XUndefineCursor_PROC XUndefineCursor_PROC = 0;
#   define XUndefineCursor (assert(XUndefineCursor_PROC != 0), XUndefineCursor_PROC)

typedef int (* PFN_XUngrabButton_PROC) (Display *, unsigned int, unsigned int, Window);
PFN_XUngrabButton_PROC XUngrabButton_PROC = 0;
#   define XUngrabButton (assert(XUngrabButton_PROC != 0), XUngrabButton_PROC)

typedef int (* PFN_XUngrabKey_PROC) (Display *, int, unsigned int, Window);
PFN_XUngrabKey_PROC XUngrabKey_PROC = 0;
#   define XUngrabKey (assert(XUngrabKey_PROC != 0), XUngrabKey_PROC)

typedef int (* PFN_XUngrabKeyboard_PROC) (Display *, Time);
PFN_XUngrabKeyboard_PROC XUngrabKeyboard_PROC = 0;
#   define XUngrabKeyboard (assert(XUngrabKeyboard_PROC != 0), XUngrabKeyboard_PROC)

typedef int (* PFN_XUngrabPointer_PROC) (Display *, Time);
PFN_XUngrabPointer_PROC XUngrabPointer_PROC = 0;
#   define XUngrabPointer (assert(XUngrabPointer_PROC != 0), XUngrabPointer_PROC)

typedef int (* PFN_XUngrabServer_PROC) (Display *);
PFN_XUngrabServer_PROC XUngrabServer_PROC = 0;
#   define XUngrabServer (assert(XUngrabServer_PROC != 0), XUngrabServer_PROC)

typedef int (* PFN_XUninstallColormap_PROC) (Display *, Colormap);
PFN_XUninstallColormap_PROC XUninstallColormap_PROC = 0;
#   define XUninstallColormap (assert(XUninstallColormap_PROC != 0), XUninstallColormap_PROC)

typedef int (* PFN_XUnloadFont_PROC) (Display *, Font);
PFN_XUnloadFont_PROC XUnloadFont_PROC = 0;
#   define XUnloadFont (assert(XUnloadFont_PROC != 0), XUnloadFont_PROC)

typedef void (* PFN_XUnlockDisplay_PROC) (Display *);
PFN_XUnlockDisplay_PROC XUnlockDisplay_PROC = 0;
#   define XUnlockDisplay (assert(XUnlockDisplay_PROC != 0), XUnlockDisplay_PROC)

typedef int (* PFN_XUnmapSubwindows_PROC) (Display *, Window);
PFN_XUnmapSubwindows_PROC XUnmapSubwindows_PROC = 0;
#   define XUnmapSubwindows (assert(XUnmapSubwindows_PROC != 0), XUnmapSubwindows_PROC)

typedef int (* PFN_XUnmapWindow_PROC) (Display *, Window);
PFN_XUnmapWindow_PROC XUnmapWindow_PROC = 0;
#   define XUnmapWindow (assert(XUnmapWindow_PROC != 0), XUnmapWindow_PROC)

typedef int (* PFN_XUnregisterIMInstantiateCallback_PROC) (Display *, struct _XrmHashBucketRec *, char *, char *, XIDProc, XPointer);
PFN_XUnregisterIMInstantiateCallback_PROC XUnregisterIMInstantiateCallback_PROC = 0;
#   define XUnregisterIMInstantiateCallback (assert(XUnregisterIMInstantiateCallback_PROC != 0), XUnregisterIMInstantiateCallback_PROC)

typedef void (* PFN_XUnsetICFocus_PROC) (XIC);
PFN_XUnsetICFocus_PROC XUnsetICFocus_PROC = 0;
#   define XUnsetICFocus (assert(XUnsetICFocus_PROC != 0), XUnsetICFocus_PROC)

typedef XVaNestedList (* PFN_XVaCreateNestedList_PROC) (int, ...);
PFN_XVaCreateNestedList_PROC XVaCreateNestedList_PROC = 0;
#   define XVaCreateNestedList (assert(XVaCreateNestedList_PROC != 0), XVaCreateNestedList_PROC)

typedef int (* PFN_XVendorRelease_PROC) (Display *);
PFN_XVendorRelease_PROC XVendorRelease_PROC = 0;
#   define XVendorRelease (assert(XVendorRelease_PROC != 0), XVendorRelease_PROC)

typedef VisualID (* PFN_XVisualIDFromVisual_PROC) (Visual *);
PFN_XVisualIDFromVisual_PROC XVisualIDFromVisual_PROC = 0;
#   define XVisualIDFromVisual (assert(XVisualIDFromVisual_PROC != 0), XVisualIDFromVisual_PROC)

typedef int (* PFN_XWarpPointer_PROC) (Display *, Window, Window, int, int, unsigned int, unsigned int, int, int);
PFN_XWarpPointer_PROC XWarpPointer_PROC = 0;
#   define XWarpPointer (assert(XWarpPointer_PROC != 0), XWarpPointer_PROC)

typedef unsigned long (* PFN_XWhitePixel_PROC) (Display *, int);
PFN_XWhitePixel_PROC XWhitePixel_PROC = 0;
#   define XWhitePixel (assert(XWhitePixel_PROC != 0), XWhitePixel_PROC)

typedef unsigned long (* PFN_XWhitePixelOfScreen_PROC) (Screen *);
PFN_XWhitePixelOfScreen_PROC XWhitePixelOfScreen_PROC = 0;
#   define XWhitePixelOfScreen (assert(XWhitePixelOfScreen_PROC != 0), XWhitePixelOfScreen_PROC)

typedef int (* PFN_XWidthMMOfScreen_PROC) (Screen *);
PFN_XWidthMMOfScreen_PROC XWidthMMOfScreen_PROC = 0;
#   define XWidthMMOfScreen (assert(XWidthMMOfScreen_PROC != 0), XWidthMMOfScreen_PROC)

typedef int (* PFN_XWidthOfScreen_PROC) (Screen *);
PFN_XWidthOfScreen_PROC XWidthOfScreen_PROC = 0;
#   define XWidthOfScreen (assert(XWidthOfScreen_PROC != 0), XWidthOfScreen_PROC)

typedef int (* PFN_XWindowEvent_PROC) (Display *, Window, long, XEvent *);
PFN_XWindowEvent_PROC XWindowEvent_PROC = 0;
#   define XWindowEvent (assert(XWindowEvent_PROC != 0), XWindowEvent_PROC)

typedef int (* PFN_XWithdrawWindow_PROC) (Display *, Window, int);
PFN_XWithdrawWindow_PROC XWithdrawWindow_PROC = 0;
#   define XWithdrawWindow (assert(XWithdrawWindow_PROC != 0), XWithdrawWindow_PROC)

typedef int (* PFN_XWriteBitmapFile_PROC) (Display *, const char *, Pixmap, unsigned int, unsigned int, int, int);
PFN_XWriteBitmapFile_PROC XWriteBitmapFile_PROC = 0;
#   define XWriteBitmapFile (assert(XWriteBitmapFile_PROC != 0), XWriteBitmapFile_PROC)

typedef void (* PFN_XmbDrawImageString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_XmbDrawImageString_PROC XmbDrawImageString_PROC = 0;
#   define XmbDrawImageString (assert(XmbDrawImageString_PROC != 0), XmbDrawImageString_PROC)

typedef void (* PFN_XmbDrawString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_XmbDrawString_PROC XmbDrawString_PROC = 0;
#   define XmbDrawString (assert(XmbDrawString_PROC != 0), XmbDrawString_PROC)

typedef void (* PFN_XmbDrawText_PROC) (Display *, Drawable, GC, int, int, XmbTextItem *, int);
PFN_XmbDrawText_PROC XmbDrawText_PROC = 0;
#   define XmbDrawText (assert(XmbDrawText_PROC != 0), XmbDrawText_PROC)

typedef int (* PFN_XmbLookupString_PROC) (XIC, XKeyPressedEvent *, char *, int, KeySym *, int *);
PFN_XmbLookupString_PROC XmbLookupString_PROC = 0;
#   define XmbLookupString (assert(XmbLookupString_PROC != 0), XmbLookupString_PROC)

typedef char *(* PFN_XmbResetIC_PROC) (XIC);
PFN_XmbResetIC_PROC XmbResetIC_PROC = 0;
#   define XmbResetIC (assert(XmbResetIC_PROC != 0), XmbResetIC_PROC)

typedef int (* PFN_XmbTextEscapement_PROC) (XFontSet, const char *, int);
PFN_XmbTextEscapement_PROC XmbTextEscapement_PROC = 0;
#   define XmbTextEscapement (assert(XmbTextEscapement_PROC != 0), XmbTextEscapement_PROC)

typedef int (* PFN_XmbTextExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *);
PFN_XmbTextExtents_PROC XmbTextExtents_PROC = 0;
#   define XmbTextExtents (assert(XmbTextExtents_PROC != 0), XmbTextExtents_PROC)

typedef int (* PFN_XmbTextPerCharExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *, int, int *, XRectangle *, XRectangle *);
PFN_XmbTextPerCharExtents_PROC XmbTextPerCharExtents_PROC = 0;
#   define XmbTextPerCharExtents (assert(XmbTextPerCharExtents_PROC != 0), XmbTextPerCharExtents_PROC)

typedef void (* PFN_XrmInitialize_PROC) (void);
PFN_XrmInitialize_PROC XrmInitialize_PROC = 0;
#   define XrmInitialize (assert(XrmInitialize_PROC != 0), XrmInitialize_PROC)

typedef void (* PFN_Xutf8DrawImageString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_Xutf8DrawImageString_PROC Xutf8DrawImageString_PROC = 0;
#   define Xutf8DrawImageString (assert(Xutf8DrawImageString_PROC != 0), Xutf8DrawImageString_PROC)

typedef void (* PFN_Xutf8DrawString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_Xutf8DrawString_PROC Xutf8DrawString_PROC = 0;
#   define Xutf8DrawString (assert(Xutf8DrawString_PROC != 0), Xutf8DrawString_PROC)

typedef void (* PFN_Xutf8DrawText_PROC) (Display *, Drawable, GC, int, int, XmbTextItem *, int);
PFN_Xutf8DrawText_PROC Xutf8DrawText_PROC = 0;
#   define Xutf8DrawText (assert(Xutf8DrawText_PROC != 0), Xutf8DrawText_PROC)

typedef int (* PFN_Xutf8LookupString_PROC) (XIC, XKeyPressedEvent *, char *, int, KeySym *, int *);
PFN_Xutf8LookupString_PROC Xutf8LookupString_PROC = 0;
#   define Xutf8LookupString (assert(Xutf8LookupString_PROC != 0), Xutf8LookupString_PROC)

typedef char *(* PFN_Xutf8ResetIC_PROC) (XIC);
PFN_Xutf8ResetIC_PROC Xutf8ResetIC_PROC = 0;
#   define Xutf8ResetIC (assert(Xutf8ResetIC_PROC != 0), Xutf8ResetIC_PROC)

typedef int (* PFN_Xutf8TextEscapement_PROC) (XFontSet, const char *, int);
PFN_Xutf8TextEscapement_PROC Xutf8TextEscapement_PROC = 0;
#   define Xutf8TextEscapement (assert(Xutf8TextEscapement_PROC != 0), Xutf8TextEscapement_PROC)

typedef int (* PFN_Xutf8TextExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *);
PFN_Xutf8TextExtents_PROC Xutf8TextExtents_PROC = 0;
#   define Xutf8TextExtents (assert(Xutf8TextExtents_PROC != 0), Xutf8TextExtents_PROC)

typedef int (* PFN_Xutf8TextPerCharExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *, int, int *, XRectangle *, XRectangle *);
PFN_Xutf8TextPerCharExtents_PROC Xutf8TextPerCharExtents_PROC = 0;
#   define Xutf8TextPerCharExtents (assert(Xutf8TextPerCharExtents_PROC != 0), Xutf8TextPerCharExtents_PROC)

typedef void (* PFN_XwcDrawImageString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const wchar_t *, int);
PFN_XwcDrawImageString_PROC XwcDrawImageString_PROC = 0;
#   define XwcDrawImageString (assert(XwcDrawImageString_PROC != 0), XwcDrawImageString_PROC)

typedef void (* PFN_XwcDrawString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const wchar_t *, int);
PFN_XwcDrawString_PROC XwcDrawString_PROC = 0;
#   define XwcDrawString (assert(XwcDrawString_PROC != 0), XwcDrawString_PROC)

typedef void (* PFN_XwcDrawText_PROC) (Display *, Drawable, GC, int, int, XwcTextItem *, int);
PFN_XwcDrawText_PROC XwcDrawText_PROC = 0;
#   define XwcDrawText (assert(XwcDrawText_PROC != 0), XwcDrawText_PROC)

typedef int (* PFN_XwcLookupString_PROC) (XIC, XKeyPressedEvent *, wchar_t *, int, KeySym *, int *);
PFN_XwcLookupString_PROC XwcLookupString_PROC = 0;
#   define XwcLookupString (assert(XwcLookupString_PROC != 0), XwcLookupString_PROC)

typedef wchar_t *(* PFN_XwcResetIC_PROC) (XIC);
PFN_XwcResetIC_PROC XwcResetIC_PROC = 0;
#   define XwcResetIC (assert(XwcResetIC_PROC != 0), XwcResetIC_PROC)

typedef int (* PFN_XwcTextEscapement_PROC) (XFontSet, const wchar_t *, int);
PFN_XwcTextEscapement_PROC XwcTextEscapement_PROC = 0;
#   define XwcTextEscapement (assert(XwcTextEscapement_PROC != 0), XwcTextEscapement_PROC)

typedef int (* PFN_XwcTextExtents_PROC) (XFontSet, const wchar_t *, int, XRectangle *, XRectangle *);
PFN_XwcTextExtents_PROC XwcTextExtents_PROC = 0;
#   define XwcTextExtents (assert(XwcTextExtents_PROC != 0), XwcTextExtents_PROC)

typedef int (* PFN_XwcTextPerCharExtents_PROC) (XFontSet, const wchar_t *, int, XRectangle *, XRectangle *, int, int *, XRectangle *, XRectangle *);
PFN_XwcTextPerCharExtents_PROC XwcTextPerCharExtents_PROC = 0;
#   define XwcTextPerCharExtents (assert(XwcTextPerCharExtents_PROC != 0), XwcTextPerCharExtents_PROC)

typedef int (* PFN__Xmblen_PROC) (char *, int);
PFN__Xmblen_PROC _Xmblen_PROC = 0;
#   define _Xmblen (assert(_Xmblen_PROC != 0), _Xmblen_PROC)

typedef int (* PFN__Xmbtowc_PROC) (wchar_t *, char *, int);
PFN__Xmbtowc_PROC _Xmbtowc_PROC = 0;
#   define _Xmbtowc (assert(_Xmbtowc_PROC != 0), _Xmbtowc_PROC)

typedef int (* PFN__Xwctomb_PROC) (char *, wchar_t);
PFN__Xwctomb_PROC _Xwctomb_PROC = 0;
#   define _Xwctomb (assert(_Xwctomb_PROC != 0), _Xwctomb_PROC)

/* libX11: Xutil.h */

typedef XClassHint *(* PFN_XAllocClassHint_PROC) (void);
PFN_XAllocClassHint_PROC XAllocClassHint_PROC = 0;
#   define XAllocClassHint (assert(XAllocClassHint_PROC != 0), XAllocClassHint_PROC)

typedef XIconSize *(* PFN_XAllocIconSize_PROC) (void);
PFN_XAllocIconSize_PROC XAllocIconSize_PROC = 0;
#   define XAllocIconSize (assert(XAllocIconSize_PROC != 0), XAllocIconSize_PROC)

typedef XSizeHints *(* PFN_XAllocSizeHints_PROC) (void);
PFN_XAllocSizeHints_PROC XAllocSizeHints_PROC = 0;
#   define XAllocSizeHints (assert(XAllocSizeHints_PROC != 0), XAllocSizeHints_PROC)

typedef XStandardColormap *(* PFN_XAllocStandardColormap_PROC) (void);
PFN_XAllocStandardColormap_PROC XAllocStandardColormap_PROC = 0;
#   define XAllocStandardColormap (assert(XAllocStandardColormap_PROC != 0), XAllocStandardColormap_PROC)

typedef XWMHints *(* PFN_XAllocWMHints_PROC) (void);
PFN_XAllocWMHints_PROC XAllocWMHints_PROC = 0;
#   define XAllocWMHints (assert(XAllocWMHints_PROC != 0), XAllocWMHints_PROC)

typedef int (* PFN_XClipBox_PROC) (Region, XRectangle *);
PFN_XClipBox_PROC XClipBox_PROC = 0;
#   define XClipBox (assert(XClipBox_PROC != 0), XClipBox_PROC)

typedef void (* PFN_XConvertCase_PROC) (KeySym, KeySym *, KeySym *);
PFN_XConvertCase_PROC XConvertCase_PROC = 0;
#   define XConvertCase (assert(XConvertCase_PROC != 0), XConvertCase_PROC)

typedef Region (* PFN_XCreateRegion_PROC) (void);
PFN_XCreateRegion_PROC XCreateRegion_PROC = 0;
#   define XCreateRegion (assert(XCreateRegion_PROC != 0), XCreateRegion_PROC)

typedef const char *(* PFN_XDefaultString_PROC) (void);
PFN_XDefaultString_PROC XDefaultString_PROC = 0;
#   define XDefaultString (assert(XDefaultString_PROC != 0), XDefaultString_PROC)

typedef int (* PFN_XDeleteContext_PROC) (Display *, XID, XContext);
PFN_XDeleteContext_PROC XDeleteContext_PROC = 0;
#   define XDeleteContext (assert(XDeleteContext_PROC != 0), XDeleteContext_PROC)

typedef int (* PFN_XDestroyRegion_PROC) (Region);
PFN_XDestroyRegion_PROC XDestroyRegion_PROC = 0;
#   define XDestroyRegion (assert(XDestroyRegion_PROC != 0), XDestroyRegion_PROC)

typedef int (* PFN_XEmptyRegion_PROC) (Region);
PFN_XEmptyRegion_PROC XEmptyRegion_PROC = 0;
#   define XEmptyRegion (assert(XEmptyRegion_PROC != 0), XEmptyRegion_PROC)

typedef int (* PFN_XEqualRegion_PROC) (Region, Region);
PFN_XEqualRegion_PROC XEqualRegion_PROC = 0;
#   define XEqualRegion (assert(XEqualRegion_PROC != 0), XEqualRegion_PROC)

typedef int (* PFN_XFindContext_PROC) (Display *, XID, XContext, XPointer *);
PFN_XFindContext_PROC XFindContext_PROC = 0;
#   define XFindContext (assert(XFindContext_PROC != 0), XFindContext_PROC)

typedef int (* PFN_XGetClassHint_PROC) (Display *, Window, XClassHint *);
PFN_XGetClassHint_PROC XGetClassHint_PROC = 0;
#   define XGetClassHint (assert(XGetClassHint_PROC != 0), XGetClassHint_PROC)

typedef int (* PFN_XGetIconSizes_PROC) (Display *, Window, XIconSize **, int *);
PFN_XGetIconSizes_PROC XGetIconSizes_PROC = 0;
#   define XGetIconSizes (assert(XGetIconSizes_PROC != 0), XGetIconSizes_PROC)

typedef int (* PFN_XGetNormalHints_PROC) (Display *, Window, XSizeHints *);
PFN_XGetNormalHints_PROC XGetNormalHints_PROC = 0;
#   define XGetNormalHints (assert(XGetNormalHints_PROC != 0), XGetNormalHints_PROC)

typedef int (* PFN_XGetRGBColormaps_PROC) (Display *, Window, XStandardColormap **, int *, Atom);
PFN_XGetRGBColormaps_PROC XGetRGBColormaps_PROC = 0;
#   define XGetRGBColormaps (assert(XGetRGBColormaps_PROC != 0), XGetRGBColormaps_PROC)

typedef int (* PFN_XGetSizeHints_PROC) (Display *, Window, XSizeHints *, Atom);
PFN_XGetSizeHints_PROC XGetSizeHints_PROC = 0;
#   define XGetSizeHints (assert(XGetSizeHints_PROC != 0), XGetSizeHints_PROC)

typedef int (* PFN_XGetStandardColormap_PROC) (Display *, Window, XStandardColormap *, Atom);
PFN_XGetStandardColormap_PROC XGetStandardColormap_PROC = 0;
#   define XGetStandardColormap (assert(XGetStandardColormap_PROC != 0), XGetStandardColormap_PROC)

typedef int (* PFN_XGetTextProperty_PROC) (Display *, Window, XTextProperty *, Atom);
PFN_XGetTextProperty_PROC XGetTextProperty_PROC = 0;
#   define XGetTextProperty (assert(XGetTextProperty_PROC != 0), XGetTextProperty_PROC)

typedef XVisualInfo *(* PFN_XGetVisualInfo_PROC) (Display *, long, XVisualInfo *, int *);
PFN_XGetVisualInfo_PROC XGetVisualInfo_PROC = 0;
#   define XGetVisualInfo (assert(XGetVisualInfo_PROC != 0), XGetVisualInfo_PROC)

typedef int (* PFN_XGetWMClientMachine_PROC) (Display *, Window, XTextProperty *);
PFN_XGetWMClientMachine_PROC XGetWMClientMachine_PROC = 0;
#   define XGetWMClientMachine (assert(XGetWMClientMachine_PROC != 0), XGetWMClientMachine_PROC)

typedef XWMHints *(* PFN_XGetWMHints_PROC) (Display *, Window);
PFN_XGetWMHints_PROC XGetWMHints_PROC = 0;
#   define XGetWMHints (assert(XGetWMHints_PROC != 0), XGetWMHints_PROC)

typedef int (* PFN_XGetWMIconName_PROC) (Display *, Window, XTextProperty *);
PFN_XGetWMIconName_PROC XGetWMIconName_PROC = 0;
#   define XGetWMIconName (assert(XGetWMIconName_PROC != 0), XGetWMIconName_PROC)

typedef int (* PFN_XGetWMName_PROC) (Display *, Window, XTextProperty *);
PFN_XGetWMName_PROC XGetWMName_PROC = 0;
#   define XGetWMName (assert(XGetWMName_PROC != 0), XGetWMName_PROC)

typedef int (* PFN_XGetWMNormalHints_PROC) (Display *, Window, XSizeHints *, long *);
PFN_XGetWMNormalHints_PROC XGetWMNormalHints_PROC = 0;
#   define XGetWMNormalHints (assert(XGetWMNormalHints_PROC != 0), XGetWMNormalHints_PROC)

typedef int (* PFN_XGetWMSizeHints_PROC) (Display *, Window, XSizeHints *, long *, Atom);
PFN_XGetWMSizeHints_PROC XGetWMSizeHints_PROC = 0;
#   define XGetWMSizeHints (assert(XGetWMSizeHints_PROC != 0), XGetWMSizeHints_PROC)

typedef int (* PFN_XGetZoomHints_PROC) (Display *, Window, XSizeHints *);
PFN_XGetZoomHints_PROC XGetZoomHints_PROC = 0;
#   define XGetZoomHints (assert(XGetZoomHints_PROC != 0), XGetZoomHints_PROC)

typedef int (* PFN_XIntersectRegion_PROC) (Region, Region, Region);
PFN_XIntersectRegion_PROC XIntersectRegion_PROC = 0;
#   define XIntersectRegion (assert(XIntersectRegion_PROC != 0), XIntersectRegion_PROC)

typedef int (* PFN_XLookupString_PROC) (XKeyEvent *, char *, int, KeySym *, XComposeStatus *);
PFN_XLookupString_PROC XLookupString_PROC = 0;
#   define XLookupString (assert(XLookupString_PROC != 0), XLookupString_PROC)

typedef int (* PFN_XMatchVisualInfo_PROC) (Display *, int, int, int, XVisualInfo *);
PFN_XMatchVisualInfo_PROC XMatchVisualInfo_PROC = 0;
#   define XMatchVisualInfo (assert(XMatchVisualInfo_PROC != 0), XMatchVisualInfo_PROC)

typedef int (* PFN_XOffsetRegion_PROC) (Region, int, int);
PFN_XOffsetRegion_PROC XOffsetRegion_PROC = 0;
#   define XOffsetRegion (assert(XOffsetRegion_PROC != 0), XOffsetRegion_PROC)

typedef int (* PFN_XPointInRegion_PROC) (Region, int, int);
PFN_XPointInRegion_PROC XPointInRegion_PROC = 0;
#   define XPointInRegion (assert(XPointInRegion_PROC != 0), XPointInRegion_PROC)

typedef Region (* PFN_XPolygonRegion_PROC) (XPoint *, int, int);
PFN_XPolygonRegion_PROC XPolygonRegion_PROC = 0;
#   define XPolygonRegion (assert(XPolygonRegion_PROC != 0), XPolygonRegion_PROC)

typedef int (* PFN_XRectInRegion_PROC) (Region, int, int, unsigned int, unsigned int);
PFN_XRectInRegion_PROC XRectInRegion_PROC = 0;
#   define XRectInRegion (assert(XRectInRegion_PROC != 0), XRectInRegion_PROC)

typedef int (* PFN_XSaveContext_PROC) (Display *, XID, XContext, const char *);
PFN_XSaveContext_PROC XSaveContext_PROC = 0;
#   define XSaveContext (assert(XSaveContext_PROC != 0), XSaveContext_PROC)

typedef int (* PFN_XSetClassHint_PROC) (Display *, Window, XClassHint *);
PFN_XSetClassHint_PROC XSetClassHint_PROC = 0;
#   define XSetClassHint (assert(XSetClassHint_PROC != 0), XSetClassHint_PROC)

typedef int (* PFN_XSetIconSizes_PROC) (Display *, Window, XIconSize *, int);
PFN_XSetIconSizes_PROC XSetIconSizes_PROC = 0;
#   define XSetIconSizes (assert(XSetIconSizes_PROC != 0), XSetIconSizes_PROC)

typedef int (* PFN_XSetNormalHints_PROC) (Display *, Window, XSizeHints *);
PFN_XSetNormalHints_PROC XSetNormalHints_PROC = 0;
#   define XSetNormalHints (assert(XSetNormalHints_PROC != 0), XSetNormalHints_PROC)

typedef void (* PFN_XSetRGBColormaps_PROC) (Display *, Window, XStandardColormap *, int, Atom);
PFN_XSetRGBColormaps_PROC XSetRGBColormaps_PROC = 0;
#   define XSetRGBColormaps (assert(XSetRGBColormaps_PROC != 0), XSetRGBColormaps_PROC)

typedef int (* PFN_XSetRegion_PROC) (Display *, GC, Region);
PFN_XSetRegion_PROC XSetRegion_PROC = 0;
#   define XSetRegion (assert(XSetRegion_PROC != 0), XSetRegion_PROC)

typedef int (* PFN_XSetSizeHints_PROC) (Display *, Window, XSizeHints *, Atom);
PFN_XSetSizeHints_PROC XSetSizeHints_PROC = 0;
#   define XSetSizeHints (assert(XSetSizeHints_PROC != 0), XSetSizeHints_PROC)

typedef void (* PFN_XSetStandardColormap_PROC) (Display *, Window, XStandardColormap *, Atom);
PFN_XSetStandardColormap_PROC XSetStandardColormap_PROC = 0;
#   define XSetStandardColormap (assert(XSetStandardColormap_PROC != 0), XSetStandardColormap_PROC)

typedef int (* PFN_XSetStandardProperties_PROC) (Display *, Window, const char *, const char *, Pixmap, char **, int, XSizeHints *);
PFN_XSetStandardProperties_PROC XSetStandardProperties_PROC = 0;
#   define XSetStandardProperties (assert(XSetStandardProperties_PROC != 0), XSetStandardProperties_PROC)

typedef void (* PFN_XSetTextProperty_PROC) (Display *, Window, XTextProperty *, Atom);
PFN_XSetTextProperty_PROC XSetTextProperty_PROC = 0;
#   define XSetTextProperty (assert(XSetTextProperty_PROC != 0), XSetTextProperty_PROC)

typedef void (* PFN_XSetWMClientMachine_PROC) (Display *, Window, XTextProperty *);
PFN_XSetWMClientMachine_PROC XSetWMClientMachine_PROC = 0;
#   define XSetWMClientMachine (assert(XSetWMClientMachine_PROC != 0), XSetWMClientMachine_PROC)

typedef int (* PFN_XSetWMHints_PROC) (Display *, Window, XWMHints *);
PFN_XSetWMHints_PROC XSetWMHints_PROC = 0;
#   define XSetWMHints (assert(XSetWMHints_PROC != 0), XSetWMHints_PROC)

typedef void (* PFN_XSetWMIconName_PROC) (Display *, Window, XTextProperty *);
PFN_XSetWMIconName_PROC XSetWMIconName_PROC = 0;
#   define XSetWMIconName (assert(XSetWMIconName_PROC != 0), XSetWMIconName_PROC)

typedef void (* PFN_XSetWMName_PROC) (Display *, Window, XTextProperty *);
PFN_XSetWMName_PROC XSetWMName_PROC = 0;
#   define XSetWMName (assert(XSetWMName_PROC != 0), XSetWMName_PROC)

typedef void (* PFN_XSetWMNormalHints_PROC) (Display *, Window, XSizeHints *);
PFN_XSetWMNormalHints_PROC XSetWMNormalHints_PROC = 0;
#   define XSetWMNormalHints (assert(XSetWMNormalHints_PROC != 0), XSetWMNormalHints_PROC)

typedef void (* PFN_XSetWMProperties_PROC) (Display *, Window, XTextProperty *, XTextProperty *, char **, int, XSizeHints *, XWMHints *, XClassHint *);
PFN_XSetWMProperties_PROC XSetWMProperties_PROC = 0;
#   define XSetWMProperties (assert(XSetWMProperties_PROC != 0), XSetWMProperties_PROC)

typedef void (* PFN_XSetWMSizeHints_PROC) (Display *, Window, XSizeHints *, Atom);
PFN_XSetWMSizeHints_PROC XSetWMSizeHints_PROC = 0;
#   define XSetWMSizeHints (assert(XSetWMSizeHints_PROC != 0), XSetWMSizeHints_PROC)

typedef int (* PFN_XSetZoomHints_PROC) (Display *, Window, XSizeHints *);
PFN_XSetZoomHints_PROC XSetZoomHints_PROC = 0;
#   define XSetZoomHints (assert(XSetZoomHints_PROC != 0), XSetZoomHints_PROC)

typedef int (* PFN_XShrinkRegion_PROC) (Region, int, int);
PFN_XShrinkRegion_PROC XShrinkRegion_PROC = 0;
#   define XShrinkRegion (assert(XShrinkRegion_PROC != 0), XShrinkRegion_PROC)

typedef int (* PFN_XStringListToTextProperty_PROC) (char **, int, XTextProperty *);
PFN_XStringListToTextProperty_PROC XStringListToTextProperty_PROC = 0;
#   define XStringListToTextProperty (assert(XStringListToTextProperty_PROC != 0), XStringListToTextProperty_PROC)

typedef int (* PFN_XSubtractRegion_PROC) (Region, Region, Region);
PFN_XSubtractRegion_PROC XSubtractRegion_PROC = 0;
#   define XSubtractRegion (assert(XSubtractRegion_PROC != 0), XSubtractRegion_PROC)

typedef int (* PFN_XTextPropertyToStringList_PROC) (XTextProperty *, char ***, int *);
PFN_XTextPropertyToStringList_PROC XTextPropertyToStringList_PROC = 0;
#   define XTextPropertyToStringList (assert(XTextPropertyToStringList_PROC != 0), XTextPropertyToStringList_PROC)

typedef int (* PFN_XUnionRectWithRegion_PROC) (XRectangle *, Region, Region);
PFN_XUnionRectWithRegion_PROC XUnionRectWithRegion_PROC = 0;
#   define XUnionRectWithRegion (assert(XUnionRectWithRegion_PROC != 0), XUnionRectWithRegion_PROC)

typedef int (* PFN_XUnionRegion_PROC) (Region, Region, Region);
PFN_XUnionRegion_PROC XUnionRegion_PROC = 0;
#   define XUnionRegion (assert(XUnionRegion_PROC != 0), XUnionRegion_PROC)

typedef int (* PFN_XWMGeometry_PROC) (Display *, int, const char *, const char *, unsigned int, XSizeHints *, int *, int *, int *, int *, int *);
PFN_XWMGeometry_PROC XWMGeometry_PROC = 0;
#   define XWMGeometry (assert(XWMGeometry_PROC != 0), XWMGeometry_PROC)

typedef int (* PFN_XXorRegion_PROC) (Region, Region, Region);
PFN_XXorRegion_PROC XXorRegion_PROC = 0;
#   define XXorRegion (assert(XXorRegion_PROC != 0), XXorRegion_PROC)

typedef void (* PFN_XmbSetWMProperties_PROC) (Display *, Window, const char *, const char *, char **, int, XSizeHints *, XWMHints *, XClassHint *);
PFN_XmbSetWMProperties_PROC XmbSetWMProperties_PROC = 0;
#   define XmbSetWMProperties (assert(XmbSetWMProperties_PROC != 0), XmbSetWMProperties_PROC)

typedef int (* PFN_XmbTextListToTextProperty_PROC) (Display *, char **, int, XICCEncodingStyle, XTextProperty *);
PFN_XmbTextListToTextProperty_PROC XmbTextListToTextProperty_PROC = 0;
#   define XmbTextListToTextProperty (assert(XmbTextListToTextProperty_PROC != 0), XmbTextListToTextProperty_PROC)

typedef int (* PFN_XmbTextPropertyToTextList_PROC) (Display *, const XTextProperty *, char ***, int *);
PFN_XmbTextPropertyToTextList_PROC XmbTextPropertyToTextList_PROC = 0;
#   define XmbTextPropertyToTextList (assert(XmbTextPropertyToTextList_PROC != 0), XmbTextPropertyToTextList_PROC)

typedef void (* PFN_Xutf8SetWMProperties_PROC) (Display *, Window, const char *, const char *, char **, int, XSizeHints *, XWMHints *, XClassHint *);
PFN_Xutf8SetWMProperties_PROC Xutf8SetWMProperties_PROC = 0;
#   define Xutf8SetWMProperties (assert(Xutf8SetWMProperties_PROC != 0), Xutf8SetWMProperties_PROC)

typedef int (* PFN_Xutf8TextListToTextProperty_PROC) (Display *, char **, int, XICCEncodingStyle, XTextProperty *);
PFN_Xutf8TextListToTextProperty_PROC Xutf8TextListToTextProperty_PROC = 0;
#   define Xutf8TextListToTextProperty (assert(Xutf8TextListToTextProperty_PROC != 0), Xutf8TextListToTextProperty_PROC)

typedef int (* PFN_Xutf8TextPropertyToTextList_PROC) (Display *, const XTextProperty *, char ***, int *);
PFN_Xutf8TextPropertyToTextList_PROC Xutf8TextPropertyToTextList_PROC = 0;
#   define Xutf8TextPropertyToTextList (assert(Xutf8TextPropertyToTextList_PROC != 0), Xutf8TextPropertyToTextList_PROC)

typedef void (* PFN_XwcFreeStringList_PROC) (wchar_t **);
PFN_XwcFreeStringList_PROC XwcFreeStringList_PROC = 0;
#   define XwcFreeStringList (assert(XwcFreeStringList_PROC != 0), XwcFreeStringList_PROC)

typedef int (* PFN_XwcTextListToTextProperty_PROC) (Display *, wchar_t **, int, XICCEncodingStyle, XTextProperty *);
PFN_XwcTextListToTextProperty_PROC XwcTextListToTextProperty_PROC = 0;
#   define XwcTextListToTextProperty (assert(XwcTextListToTextProperty_PROC != 0), XwcTextListToTextProperty_PROC)

typedef int (* PFN_XwcTextPropertyToTextList_PROC) (Display *, const XTextProperty *, wchar_t ***, int *);
PFN_XwcTextPropertyToTextList_PROC XwcTextPropertyToTextList_PROC = 0;
#   define XwcTextPropertyToTextList (assert(XwcTextPropertyToTextList_PROC != 0), XwcTextPropertyToTextList_PROC)

/* libX11: XKBlib.h */

typedef XkbDeviceLedInfoPtr (* PFN_XkbAddDeviceLedInfo_PROC) (XkbDeviceInfoPtr, unsigned int, unsigned int);
PFN_XkbAddDeviceLedInfo_PROC XkbAddDeviceLedInfo_PROC = 0;
#   define XkbAddDeviceLedInfo (assert(XkbAddDeviceLedInfo_PROC != 0), XkbAddDeviceLedInfo_PROC)

typedef XkbKeyTypePtr (* PFN_XkbAddKeyType_PROC) (XkbDescPtr, Atom, int, int, int);
PFN_XkbAddKeyType_PROC XkbAddKeyType_PROC = 0;
#   define XkbAddKeyType (assert(XkbAddKeyType_PROC != 0), XkbAddKeyType_PROC)

typedef int (* PFN_XkbAllocClientMap_PROC) (XkbDescPtr, unsigned int, unsigned int);
PFN_XkbAllocClientMap_PROC XkbAllocClientMap_PROC = 0;
#   define XkbAllocClientMap (assert(XkbAllocClientMap_PROC != 0), XkbAllocClientMap_PROC)

typedef int (* PFN_XkbAllocCompatMap_PROC) (XkbDescPtr, unsigned int, unsigned int);
PFN_XkbAllocCompatMap_PROC XkbAllocCompatMap_PROC = 0;
#   define XkbAllocCompatMap (assert(XkbAllocCompatMap_PROC != 0), XkbAllocCompatMap_PROC)

typedef int (* PFN_XkbAllocControls_PROC) (XkbDescPtr, unsigned int);
PFN_XkbAllocControls_PROC XkbAllocControls_PROC = 0;
#   define XkbAllocControls (assert(XkbAllocControls_PROC != 0), XkbAllocControls_PROC)

typedef XkbDeviceInfoPtr (* PFN_XkbAllocDeviceInfo_PROC) (unsigned int, unsigned int, unsigned int);
PFN_XkbAllocDeviceInfo_PROC XkbAllocDeviceInfo_PROC = 0;
#   define XkbAllocDeviceInfo (assert(XkbAllocDeviceInfo_PROC != 0), XkbAllocDeviceInfo_PROC)

typedef int (* PFN_XkbAllocIndicatorMaps_PROC) (XkbDescPtr);
PFN_XkbAllocIndicatorMaps_PROC XkbAllocIndicatorMaps_PROC = 0;
#   define XkbAllocIndicatorMaps (assert(XkbAllocIndicatorMaps_PROC != 0), XkbAllocIndicatorMaps_PROC)

typedef XkbDescPtr (* PFN_XkbAllocKeyboard_PROC) (void);
PFN_XkbAllocKeyboard_PROC XkbAllocKeyboard_PROC = 0;
#   define XkbAllocKeyboard (assert(XkbAllocKeyboard_PROC != 0), XkbAllocKeyboard_PROC)

typedef int (* PFN_XkbAllocNames_PROC) (XkbDescPtr, unsigned int, int, int);
PFN_XkbAllocNames_PROC XkbAllocNames_PROC = 0;
#   define XkbAllocNames (assert(XkbAllocNames_PROC != 0), XkbAllocNames_PROC)

typedef int (* PFN_XkbAllocServerMap_PROC) (XkbDescPtr, unsigned int, unsigned int);
PFN_XkbAllocServerMap_PROC XkbAllocServerMap_PROC = 0;
#   define XkbAllocServerMap (assert(XkbAllocServerMap_PROC != 0), XkbAllocServerMap_PROC)

typedef int (* PFN_XkbApplyCompatMapToKey_PROC) (XkbDescPtr, KeyCode, XkbChangesPtr);
PFN_XkbApplyCompatMapToKey_PROC XkbApplyCompatMapToKey_PROC = 0;
#   define XkbApplyCompatMapToKey (assert(XkbApplyCompatMapToKey_PROC != 0), XkbApplyCompatMapToKey_PROC)

typedef int (* PFN_XkbApplyVirtualModChanges_PROC) (XkbDescPtr, unsigned int, XkbChangesPtr);
PFN_XkbApplyVirtualModChanges_PROC XkbApplyVirtualModChanges_PROC = 0;
#   define XkbApplyVirtualModChanges (assert(XkbApplyVirtualModChanges_PROC != 0), XkbApplyVirtualModChanges_PROC)

typedef int (* PFN_XkbBell_PROC) (Display *, Window, int, Atom);
PFN_XkbBell_PROC XkbBell_PROC = 0;
#   define XkbBell (assert(XkbBell_PROC != 0), XkbBell_PROC)

typedef int (* PFN_XkbBellEvent_PROC) (Display *, Window, int, Atom);
PFN_XkbBellEvent_PROC XkbBellEvent_PROC = 0;
#   define XkbBellEvent (assert(XkbBellEvent_PROC != 0), XkbBellEvent_PROC)

typedef int (* PFN_XkbChangeDeviceInfo_PROC) (Display *, XkbDeviceInfoPtr, XkbDeviceChangesPtr);
PFN_XkbChangeDeviceInfo_PROC XkbChangeDeviceInfo_PROC = 0;
#   define XkbChangeDeviceInfo (assert(XkbChangeDeviceInfo_PROC != 0), XkbChangeDeviceInfo_PROC)

typedef int (* PFN_XkbChangeEnabledControls_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbChangeEnabledControls_PROC XkbChangeEnabledControls_PROC = 0;
#   define XkbChangeEnabledControls (assert(XkbChangeEnabledControls_PROC != 0), XkbChangeEnabledControls_PROC)

typedef int (* PFN_XkbChangeKeycodeRange_PROC) (XkbDescPtr, int, int, XkbChangesPtr);
PFN_XkbChangeKeycodeRange_PROC XkbChangeKeycodeRange_PROC = 0;
#   define XkbChangeKeycodeRange (assert(XkbChangeKeycodeRange_PROC != 0), XkbChangeKeycodeRange_PROC)

typedef int (* PFN_XkbChangeMap_PROC) (Display *, XkbDescPtr, XkbMapChangesPtr);
PFN_XkbChangeMap_PROC XkbChangeMap_PROC = 0;
#   define XkbChangeMap (assert(XkbChangeMap_PROC != 0), XkbChangeMap_PROC)

typedef int (* PFN_XkbChangeNames_PROC) (Display *, XkbDescPtr, XkbNameChangesPtr);
PFN_XkbChangeNames_PROC XkbChangeNames_PROC = 0;
#   define XkbChangeNames (assert(XkbChangeNames_PROC != 0), XkbChangeNames_PROC)

typedef int (* PFN_XkbChangeTypesOfKey_PROC) (XkbDescPtr, int, int, unsigned int, int *, XkbMapChangesPtr);
PFN_XkbChangeTypesOfKey_PROC XkbChangeTypesOfKey_PROC = 0;
#   define XkbChangeTypesOfKey (assert(XkbChangeTypesOfKey_PROC != 0), XkbChangeTypesOfKey_PROC)

typedef int (* PFN_XkbComputeEffectiveMap_PROC) (XkbDescPtr, XkbKeyTypePtr, unsigned char *);
PFN_XkbComputeEffectiveMap_PROC XkbComputeEffectiveMap_PROC = 0;
#   define XkbComputeEffectiveMap (assert(XkbComputeEffectiveMap_PROC != 0), XkbComputeEffectiveMap_PROC)

typedef int (* PFN_XkbCopyKeyType_PROC) (XkbKeyTypePtr, XkbKeyTypePtr);
PFN_XkbCopyKeyType_PROC XkbCopyKeyType_PROC = 0;
#   define XkbCopyKeyType (assert(XkbCopyKeyType_PROC != 0), XkbCopyKeyType_PROC)

typedef int (* PFN_XkbCopyKeyTypes_PROC) (XkbKeyTypePtr, XkbKeyTypePtr, int);
PFN_XkbCopyKeyTypes_PROC XkbCopyKeyTypes_PROC = 0;
#   define XkbCopyKeyTypes (assert(XkbCopyKeyTypes_PROC != 0), XkbCopyKeyTypes_PROC)

typedef int (* PFN_XkbDeviceBell_PROC) (Display *, Window, int, int, int, int, Atom);
PFN_XkbDeviceBell_PROC XkbDeviceBell_PROC = 0;
#   define XkbDeviceBell (assert(XkbDeviceBell_PROC != 0), XkbDeviceBell_PROC)

typedef int (* PFN_XkbDeviceBellEvent_PROC) (Display *, Window, int, int, int, int, Atom);
PFN_XkbDeviceBellEvent_PROC XkbDeviceBellEvent_PROC = 0;
#   define XkbDeviceBellEvent (assert(XkbDeviceBellEvent_PROC != 0), XkbDeviceBellEvent_PROC)

typedef int (* PFN_XkbForceBell_PROC) (Display *, int);
PFN_XkbForceBell_PROC XkbForceBell_PROC = 0;
#   define XkbForceBell (assert(XkbForceBell_PROC != 0), XkbForceBell_PROC)

typedef int (* PFN_XkbForceDeviceBell_PROC) (Display *, int, int, int, int);
PFN_XkbForceDeviceBell_PROC XkbForceDeviceBell_PROC = 0;
#   define XkbForceDeviceBell (assert(XkbForceDeviceBell_PROC != 0), XkbForceDeviceBell_PROC)

typedef void (* PFN_XkbFreeClientMap_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeClientMap_PROC XkbFreeClientMap_PROC = 0;
#   define XkbFreeClientMap (assert(XkbFreeClientMap_PROC != 0), XkbFreeClientMap_PROC)

typedef void (* PFN_XkbFreeCompatMap_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeCompatMap_PROC XkbFreeCompatMap_PROC = 0;
#   define XkbFreeCompatMap (assert(XkbFreeCompatMap_PROC != 0), XkbFreeCompatMap_PROC)

typedef void (* PFN_XkbFreeComponentList_PROC) (XkbComponentListPtr);
PFN_XkbFreeComponentList_PROC XkbFreeComponentList_PROC = 0;
#   define XkbFreeComponentList (assert(XkbFreeComponentList_PROC != 0), XkbFreeComponentList_PROC)

typedef void (* PFN_XkbFreeControls_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeControls_PROC XkbFreeControls_PROC = 0;
#   define XkbFreeControls (assert(XkbFreeControls_PROC != 0), XkbFreeControls_PROC)

typedef void (* PFN_XkbFreeDeviceInfo_PROC) (XkbDeviceInfoPtr, unsigned int, int);
PFN_XkbFreeDeviceInfo_PROC XkbFreeDeviceInfo_PROC = 0;
#   define XkbFreeDeviceInfo (assert(XkbFreeDeviceInfo_PROC != 0), XkbFreeDeviceInfo_PROC)

typedef void (* PFN_XkbFreeIndicatorMaps_PROC) (XkbDescPtr);
PFN_XkbFreeIndicatorMaps_PROC XkbFreeIndicatorMaps_PROC = 0;
#   define XkbFreeIndicatorMaps (assert(XkbFreeIndicatorMaps_PROC != 0), XkbFreeIndicatorMaps_PROC)

typedef void (* PFN_XkbFreeKeyboard_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeKeyboard_PROC XkbFreeKeyboard_PROC = 0;
#   define XkbFreeKeyboard (assert(XkbFreeKeyboard_PROC != 0), XkbFreeKeyboard_PROC)

typedef void (* PFN_XkbFreeNames_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeNames_PROC XkbFreeNames_PROC = 0;
#   define XkbFreeNames (assert(XkbFreeNames_PROC != 0), XkbFreeNames_PROC)

typedef void (* PFN_XkbFreeServerMap_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeServerMap_PROC XkbFreeServerMap_PROC = 0;
#   define XkbFreeServerMap (assert(XkbFreeServerMap_PROC != 0), XkbFreeServerMap_PROC)

typedef int (* PFN_XkbGetAutoRepeatRate_PROC) (Display *, unsigned int, unsigned int *, unsigned int *);
PFN_XkbGetAutoRepeatRate_PROC XkbGetAutoRepeatRate_PROC = 0;
#   define XkbGetAutoRepeatRate (assert(XkbGetAutoRepeatRate_PROC != 0), XkbGetAutoRepeatRate_PROC)

typedef int (* PFN_XkbGetAutoResetControls_PROC) (Display *, unsigned int *, unsigned int *);
PFN_XkbGetAutoResetControls_PROC XkbGetAutoResetControls_PROC = 0;
#   define XkbGetAutoResetControls (assert(XkbGetAutoResetControls_PROC != 0), XkbGetAutoResetControls_PROC)

typedef int (* PFN_XkbGetCompatMap_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetCompatMap_PROC XkbGetCompatMap_PROC = 0;
#   define XkbGetCompatMap (assert(XkbGetCompatMap_PROC != 0), XkbGetCompatMap_PROC)

typedef int (* PFN_XkbGetControls_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbGetControls_PROC XkbGetControls_PROC = 0;
#   define XkbGetControls (assert(XkbGetControls_PROC != 0), XkbGetControls_PROC)

typedef int (* PFN_XkbGetDetectableAutoRepeat_PROC) (Display *, int *);
PFN_XkbGetDetectableAutoRepeat_PROC XkbGetDetectableAutoRepeat_PROC = 0;
#   define XkbGetDetectableAutoRepeat (assert(XkbGetDetectableAutoRepeat_PROC != 0), XkbGetDetectableAutoRepeat_PROC)

typedef int (* PFN_XkbGetDeviceButtonActions_PROC) (Display *, XkbDeviceInfoPtr, int, unsigned int, unsigned int);
PFN_XkbGetDeviceButtonActions_PROC XkbGetDeviceButtonActions_PROC = 0;
#   define XkbGetDeviceButtonActions (assert(XkbGetDeviceButtonActions_PROC != 0), XkbGetDeviceButtonActions_PROC)

typedef XkbDeviceInfoPtr (* PFN_XkbGetDeviceInfo_PROC) (Display *, unsigned int, unsigned int, unsigned int, unsigned int);
PFN_XkbGetDeviceInfo_PROC XkbGetDeviceInfo_PROC = 0;
#   define XkbGetDeviceInfo (assert(XkbGetDeviceInfo_PROC != 0), XkbGetDeviceInfo_PROC)

typedef int (* PFN_XkbGetDeviceInfoChanges_PROC) (Display *, XkbDeviceInfoPtr, XkbDeviceChangesPtr);
PFN_XkbGetDeviceInfoChanges_PROC XkbGetDeviceInfoChanges_PROC = 0;
#   define XkbGetDeviceInfoChanges (assert(XkbGetDeviceInfoChanges_PROC != 0), XkbGetDeviceInfoChanges_PROC)

typedef int (* PFN_XkbGetDeviceLedInfo_PROC) (Display *, XkbDeviceInfoPtr, unsigned int, unsigned int, unsigned int);
PFN_XkbGetDeviceLedInfo_PROC XkbGetDeviceLedInfo_PROC = 0;
#   define XkbGetDeviceLedInfo (assert(XkbGetDeviceLedInfo_PROC != 0), XkbGetDeviceLedInfo_PROC)

typedef int (* PFN_XkbGetIndicatorMap_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbGetIndicatorMap_PROC XkbGetIndicatorMap_PROC = 0;
#   define XkbGetIndicatorMap (assert(XkbGetIndicatorMap_PROC != 0), XkbGetIndicatorMap_PROC)

typedef int (* PFN_XkbGetIndicatorState_PROC) (Display *, unsigned int, unsigned int *);
PFN_XkbGetIndicatorState_PROC XkbGetIndicatorState_PROC = 0;
#   define XkbGetIndicatorState (assert(XkbGetIndicatorState_PROC != 0), XkbGetIndicatorState_PROC)

typedef int (* PFN_XkbGetKeyActions_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyActions_PROC XkbGetKeyActions_PROC = 0;
#   define XkbGetKeyActions (assert(XkbGetKeyActions_PROC != 0), XkbGetKeyActions_PROC)

typedef int (* PFN_XkbGetKeyBehaviors_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyBehaviors_PROC XkbGetKeyBehaviors_PROC = 0;
#   define XkbGetKeyBehaviors (assert(XkbGetKeyBehaviors_PROC != 0), XkbGetKeyBehaviors_PROC)

typedef int (* PFN_XkbGetKeyExplicitComponents_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyExplicitComponents_PROC XkbGetKeyExplicitComponents_PROC = 0;
#   define XkbGetKeyExplicitComponents (assert(XkbGetKeyExplicitComponents_PROC != 0), XkbGetKeyExplicitComponents_PROC)

typedef int (* PFN_XkbGetKeyModifierMap_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyModifierMap_PROC XkbGetKeyModifierMap_PROC = 0;
#   define XkbGetKeyModifierMap (assert(XkbGetKeyModifierMap_PROC != 0), XkbGetKeyModifierMap_PROC)

typedef int (* PFN_XkbGetKeySyms_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeySyms_PROC XkbGetKeySyms_PROC = 0;
#   define XkbGetKeySyms (assert(XkbGetKeySyms_PROC != 0), XkbGetKeySyms_PROC)

typedef int (* PFN_XkbGetKeyTypes_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyTypes_PROC XkbGetKeyTypes_PROC = 0;
#   define XkbGetKeyTypes (assert(XkbGetKeyTypes_PROC != 0), XkbGetKeyTypes_PROC)

typedef int (* PFN_XkbGetKeyVirtualModMap_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyVirtualModMap_PROC XkbGetKeyVirtualModMap_PROC = 0;
#   define XkbGetKeyVirtualModMap (assert(XkbGetKeyVirtualModMap_PROC != 0), XkbGetKeyVirtualModMap_PROC)

typedef XkbDescPtr (* PFN_XkbGetKeyboard_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbGetKeyboard_PROC XkbGetKeyboard_PROC = 0;
#   define XkbGetKeyboard (assert(XkbGetKeyboard_PROC != 0), XkbGetKeyboard_PROC)

typedef XkbDescPtr (* PFN_XkbGetKeyboardByName_PROC) (Display *, unsigned int, XkbComponentNamesPtr, unsigned int, unsigned int, int);
PFN_XkbGetKeyboardByName_PROC XkbGetKeyboardByName_PROC = 0;
#   define XkbGetKeyboardByName (assert(XkbGetKeyboardByName_PROC != 0), XkbGetKeyboardByName_PROC)

typedef XkbDescPtr (* PFN_XkbGetMap_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbGetMap_PROC XkbGetMap_PROC = 0;
#   define XkbGetMap (assert(XkbGetMap_PROC != 0), XkbGetMap_PROC)

typedef int (* PFN_XkbGetMapChanges_PROC) (Display *, XkbDescPtr, XkbMapChangesPtr);
PFN_XkbGetMapChanges_PROC XkbGetMapChanges_PROC = 0;
#   define XkbGetMapChanges (assert(XkbGetMapChanges_PROC != 0), XkbGetMapChanges_PROC)

typedef int (* PFN_XkbGetNamedDeviceIndicator_PROC) (Display *, unsigned int, unsigned int, unsigned int, Atom, int *, int *, XkbIndicatorMapPtr, int *);
PFN_XkbGetNamedDeviceIndicator_PROC XkbGetNamedDeviceIndicator_PROC = 0;
#   define XkbGetNamedDeviceIndicator (assert(XkbGetNamedDeviceIndicator_PROC != 0), XkbGetNamedDeviceIndicator_PROC)

typedef int (* PFN_XkbGetNamedIndicator_PROC) (Display *, Atom, int *, int *, XkbIndicatorMapPtr, int *);
PFN_XkbGetNamedIndicator_PROC XkbGetNamedIndicator_PROC = 0;
#   define XkbGetNamedIndicator (assert(XkbGetNamedIndicator_PROC != 0), XkbGetNamedIndicator_PROC)

typedef int (* PFN_XkbGetNames_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetNames_PROC XkbGetNames_PROC = 0;
#   define XkbGetNames (assert(XkbGetNames_PROC != 0), XkbGetNames_PROC)

typedef int (* PFN_XkbGetPerClientControls_PROC) (Display *, unsigned int *);
PFN_XkbGetPerClientControls_PROC XkbGetPerClientControls_PROC = 0;
#   define XkbGetPerClientControls (assert(XkbGetPerClientControls_PROC != 0), XkbGetPerClientControls_PROC)

typedef int (* PFN_XkbGetState_PROC) (Display *, unsigned int, XkbStatePtr);
PFN_XkbGetState_PROC XkbGetState_PROC = 0;
#   define XkbGetState (assert(XkbGetState_PROC != 0), XkbGetState_PROC)

typedef int (* PFN_XkbGetUpdatedMap_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetUpdatedMap_PROC XkbGetUpdatedMap_PROC = 0;
#   define XkbGetUpdatedMap (assert(XkbGetUpdatedMap_PROC != 0), XkbGetUpdatedMap_PROC)

typedef int (* PFN_XkbGetVirtualMods_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetVirtualMods_PROC XkbGetVirtualMods_PROC = 0;
#   define XkbGetVirtualMods (assert(XkbGetVirtualMods_PROC != 0), XkbGetVirtualMods_PROC)

typedef unsigned int (* PFN_XkbGetXlibControls_PROC) (Display *);
PFN_XkbGetXlibControls_PROC XkbGetXlibControls_PROC = 0;
#   define XkbGetXlibControls (assert(XkbGetXlibControls_PROC != 0), XkbGetXlibControls_PROC)

typedef int (* PFN_XkbIgnoreExtension_PROC) (int);
PFN_XkbIgnoreExtension_PROC XkbIgnoreExtension_PROC = 0;
#   define XkbIgnoreExtension (assert(XkbIgnoreExtension_PROC != 0), XkbIgnoreExtension_PROC)

typedef int (* PFN_XkbInitCanonicalKeyTypes_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbInitCanonicalKeyTypes_PROC XkbInitCanonicalKeyTypes_PROC = 0;
#   define XkbInitCanonicalKeyTypes (assert(XkbInitCanonicalKeyTypes_PROC != 0), XkbInitCanonicalKeyTypes_PROC)

typedef int (* PFN_XkbKeyTypesForCoreSymbols_PROC) (XkbDescPtr, int, KeySym *, unsigned int, int *, KeySym *);
PFN_XkbKeyTypesForCoreSymbols_PROC XkbKeyTypesForCoreSymbols_PROC = 0;
#   define XkbKeyTypesForCoreSymbols (assert(XkbKeyTypesForCoreSymbols_PROC != 0), XkbKeyTypesForCoreSymbols_PROC)

typedef KeySym (* PFN_XkbKeycodeToKeysym_PROC) (Display *, KeyCode, int, int);
PFN_XkbKeycodeToKeysym_PROC XkbKeycodeToKeysym_PROC = 0;
#   define XkbKeycodeToKeysym (assert(XkbKeycodeToKeysym_PROC != 0), XkbKeycodeToKeysym_PROC)

typedef unsigned int (* PFN_XkbKeysymToModifiers_PROC) (Display *, KeySym);
PFN_XkbKeysymToModifiers_PROC XkbKeysymToModifiers_PROC = 0;
#   define XkbKeysymToModifiers (assert(XkbKeysymToModifiers_PROC != 0), XkbKeysymToModifiers_PROC)

typedef int (* PFN_XkbLatchGroup_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbLatchGroup_PROC XkbLatchGroup_PROC = 0;
#   define XkbLatchGroup (assert(XkbLatchGroup_PROC != 0), XkbLatchGroup_PROC)

typedef int (* PFN_XkbLatchModifiers_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbLatchModifiers_PROC XkbLatchModifiers_PROC = 0;
#   define XkbLatchModifiers (assert(XkbLatchModifiers_PROC != 0), XkbLatchModifiers_PROC)

typedef int (* PFN_XkbLibraryVersion_PROC) (int *, int *);
PFN_XkbLibraryVersion_PROC XkbLibraryVersion_PROC = 0;
#   define XkbLibraryVersion (assert(XkbLibraryVersion_PROC != 0), XkbLibraryVersion_PROC)

typedef XkbComponentListPtr (* PFN_XkbListComponents_PROC) (Display *, unsigned int, XkbComponentNamesPtr, int *);
PFN_XkbListComponents_PROC XkbListComponents_PROC = 0;
#   define XkbListComponents (assert(XkbListComponents_PROC != 0), XkbListComponents_PROC)

typedef int (* PFN_XkbLockGroup_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbLockGroup_PROC XkbLockGroup_PROC = 0;
#   define XkbLockGroup (assert(XkbLockGroup_PROC != 0), XkbLockGroup_PROC)

typedef int (* PFN_XkbLockModifiers_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbLockModifiers_PROC XkbLockModifiers_PROC = 0;
#   define XkbLockModifiers (assert(XkbLockModifiers_PROC != 0), XkbLockModifiers_PROC)

typedef int (* PFN_XkbLookupKeyBinding_PROC) (Display *, KeySym, unsigned int, char *, int, int *);
PFN_XkbLookupKeyBinding_PROC XkbLookupKeyBinding_PROC = 0;
#   define XkbLookupKeyBinding (assert(XkbLookupKeyBinding_PROC != 0), XkbLookupKeyBinding_PROC)

typedef int (* PFN_XkbLookupKeySym_PROC) (Display *, KeyCode, unsigned int, unsigned int *, KeySym *);
PFN_XkbLookupKeySym_PROC XkbLookupKeySym_PROC = 0;
#   define XkbLookupKeySym (assert(XkbLookupKeySym_PROC != 0), XkbLookupKeySym_PROC)

typedef void (* PFN_XkbNoteControlsChanges_PROC) (XkbControlsChangesPtr, XkbControlsNotifyEvent *, unsigned int);
PFN_XkbNoteControlsChanges_PROC XkbNoteControlsChanges_PROC = 0;
#   define XkbNoteControlsChanges (assert(XkbNoteControlsChanges_PROC != 0), XkbNoteControlsChanges_PROC)

typedef void (* PFN_XkbNoteDeviceChanges_PROC) (XkbDeviceChangesPtr, XkbExtensionDeviceNotifyEvent *, unsigned int);
PFN_XkbNoteDeviceChanges_PROC XkbNoteDeviceChanges_PROC = 0;
#   define XkbNoteDeviceChanges (assert(XkbNoteDeviceChanges_PROC != 0), XkbNoteDeviceChanges_PROC)

typedef void (* PFN_XkbNoteMapChanges_PROC) (XkbMapChangesPtr, XkbMapNotifyEvent *, unsigned int);
PFN_XkbNoteMapChanges_PROC XkbNoteMapChanges_PROC = 0;
#   define XkbNoteMapChanges (assert(XkbNoteMapChanges_PROC != 0), XkbNoteMapChanges_PROC)

typedef void (* PFN_XkbNoteNameChanges_PROC) (XkbNameChangesPtr, XkbNamesNotifyEvent *, unsigned int);
PFN_XkbNoteNameChanges_PROC XkbNoteNameChanges_PROC = 0;
#   define XkbNoteNameChanges (assert(XkbNoteNameChanges_PROC != 0), XkbNoteNameChanges_PROC)

typedef Display *(* PFN_XkbOpenDisplay_PROC) (const char *, int *, int *, int *, int *, int *);
PFN_XkbOpenDisplay_PROC XkbOpenDisplay_PROC = 0;
#   define XkbOpenDisplay (assert(XkbOpenDisplay_PROC != 0), XkbOpenDisplay_PROC)

typedef int (* PFN_XkbQueryExtension_PROC) (Display *, int *, int *, int *, int *, int *);
PFN_XkbQueryExtension_PROC XkbQueryExtension_PROC = 0;
#   define XkbQueryExtension (assert(XkbQueryExtension_PROC != 0), XkbQueryExtension_PROC)

typedef int (* PFN_XkbRefreshKeyboardMapping_PROC) (XkbMapNotifyEvent *);
PFN_XkbRefreshKeyboardMapping_PROC XkbRefreshKeyboardMapping_PROC = 0;
#   define XkbRefreshKeyboardMapping (assert(XkbRefreshKeyboardMapping_PROC != 0), XkbRefreshKeyboardMapping_PROC)

typedef int (* PFN_XkbResizeDeviceButtonActions_PROC) (XkbDeviceInfoPtr, unsigned int);
PFN_XkbResizeDeviceButtonActions_PROC XkbResizeDeviceButtonActions_PROC = 0;
#   define XkbResizeDeviceButtonActions (assert(XkbResizeDeviceButtonActions_PROC != 0), XkbResizeDeviceButtonActions_PROC)

typedef XkbAction *(* PFN_XkbResizeKeyActions_PROC) (XkbDescPtr, int, int);
PFN_XkbResizeKeyActions_PROC XkbResizeKeyActions_PROC = 0;
#   define XkbResizeKeyActions (assert(XkbResizeKeyActions_PROC != 0), XkbResizeKeyActions_PROC)

typedef KeySym *(* PFN_XkbResizeKeySyms_PROC) (XkbDescPtr, int, int);
PFN_XkbResizeKeySyms_PROC XkbResizeKeySyms_PROC = 0;
#   define XkbResizeKeySyms (assert(XkbResizeKeySyms_PROC != 0), XkbResizeKeySyms_PROC)

typedef int (* PFN_XkbResizeKeyType_PROC) (XkbDescPtr, int, int, int, int);
PFN_XkbResizeKeyType_PROC XkbResizeKeyType_PROC = 0;
#   define XkbResizeKeyType (assert(XkbResizeKeyType_PROC != 0), XkbResizeKeyType_PROC)

typedef int (* PFN_XkbSelectEventDetails_PROC) (Display *, unsigned int, unsigned int, unsigned long, unsigned long);
PFN_XkbSelectEventDetails_PROC XkbSelectEventDetails_PROC = 0;
#   define XkbSelectEventDetails (assert(XkbSelectEventDetails_PROC != 0), XkbSelectEventDetails_PROC)

typedef int (* PFN_XkbSelectEvents_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbSelectEvents_PROC XkbSelectEvents_PROC = 0;
#   define XkbSelectEvents (assert(XkbSelectEvents_PROC != 0), XkbSelectEvents_PROC)

typedef void (* PFN_XkbSetAtomFuncs_PROC) (XkbInternAtomFunc, XkbGetAtomNameFunc);
PFN_XkbSetAtomFuncs_PROC XkbSetAtomFuncs_PROC = 0;
#   define XkbSetAtomFuncs (assert(XkbSetAtomFuncs_PROC != 0), XkbSetAtomFuncs_PROC)

typedef int (* PFN_XkbSetAutoRepeatRate_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbSetAutoRepeatRate_PROC XkbSetAutoRepeatRate_PROC = 0;
#   define XkbSetAutoRepeatRate (assert(XkbSetAutoRepeatRate_PROC != 0), XkbSetAutoRepeatRate_PROC)

typedef int (* PFN_XkbSetAutoResetControls_PROC) (Display *, unsigned int, unsigned int *, unsigned int *);
PFN_XkbSetAutoResetControls_PROC XkbSetAutoResetControls_PROC = 0;
#   define XkbSetAutoResetControls (assert(XkbSetAutoResetControls_PROC != 0), XkbSetAutoResetControls_PROC)

typedef int (* PFN_XkbSetCompatMap_PROC) (Display *, unsigned int, XkbDescPtr, int);
PFN_XkbSetCompatMap_PROC XkbSetCompatMap_PROC = 0;
#   define XkbSetCompatMap (assert(XkbSetCompatMap_PROC != 0), XkbSetCompatMap_PROC)

typedef int (* PFN_XkbSetControls_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbSetControls_PROC XkbSetControls_PROC = 0;
#   define XkbSetControls (assert(XkbSetControls_PROC != 0), XkbSetControls_PROC)

typedef int (* PFN_XkbSetDebuggingFlags_PROC) (Display *, unsigned int, unsigned int, char *, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XkbSetDebuggingFlags_PROC XkbSetDebuggingFlags_PROC = 0;
#   define XkbSetDebuggingFlags (assert(XkbSetDebuggingFlags_PROC != 0), XkbSetDebuggingFlags_PROC)

typedef int (* PFN_XkbSetDetectableAutoRepeat_PROC) (Display *, int, int *);
PFN_XkbSetDetectableAutoRepeat_PROC XkbSetDetectableAutoRepeat_PROC = 0;
#   define XkbSetDetectableAutoRepeat (assert(XkbSetDetectableAutoRepeat_PROC != 0), XkbSetDetectableAutoRepeat_PROC)

typedef int (* PFN_XkbSetDeviceButtonActions_PROC) (Display *, XkbDeviceInfoPtr, unsigned int, unsigned int);
PFN_XkbSetDeviceButtonActions_PROC XkbSetDeviceButtonActions_PROC = 0;
#   define XkbSetDeviceButtonActions (assert(XkbSetDeviceButtonActions_PROC != 0), XkbSetDeviceButtonActions_PROC)

typedef int (* PFN_XkbSetDeviceInfo_PROC) (Display *, unsigned int, XkbDeviceInfoPtr);
PFN_XkbSetDeviceInfo_PROC XkbSetDeviceInfo_PROC = 0;
#   define XkbSetDeviceInfo (assert(XkbSetDeviceInfo_PROC != 0), XkbSetDeviceInfo_PROC)

typedef int (* PFN_XkbSetDeviceLedInfo_PROC) (Display *, XkbDeviceInfoPtr, unsigned int, unsigned int, unsigned int);
PFN_XkbSetDeviceLedInfo_PROC XkbSetDeviceLedInfo_PROC = 0;
#   define XkbSetDeviceLedInfo (assert(XkbSetDeviceLedInfo_PROC != 0), XkbSetDeviceLedInfo_PROC)

typedef int (* PFN_XkbSetIgnoreLockMods_PROC) (Display *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
PFN_XkbSetIgnoreLockMods_PROC XkbSetIgnoreLockMods_PROC = 0;
#   define XkbSetIgnoreLockMods (assert(XkbSetIgnoreLockMods_PROC != 0), XkbSetIgnoreLockMods_PROC)

typedef int (* PFN_XkbSetIndicatorMap_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbSetIndicatorMap_PROC XkbSetIndicatorMap_PROC = 0;
#   define XkbSetIndicatorMap (assert(XkbSetIndicatorMap_PROC != 0), XkbSetIndicatorMap_PROC)

typedef int (* PFN_XkbSetMap_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbSetMap_PROC XkbSetMap_PROC = 0;
#   define XkbSetMap (assert(XkbSetMap_PROC != 0), XkbSetMap_PROC)

typedef int (* PFN_XkbSetNamedDeviceIndicator_PROC) (Display *, unsigned int, unsigned int, unsigned int, Atom, int, int, int, XkbIndicatorMapPtr);
PFN_XkbSetNamedDeviceIndicator_PROC XkbSetNamedDeviceIndicator_PROC = 0;
#   define XkbSetNamedDeviceIndicator (assert(XkbSetNamedDeviceIndicator_PROC != 0), XkbSetNamedDeviceIndicator_PROC)

typedef int (* PFN_XkbSetNamedIndicator_PROC) (Display *, Atom, int, int, int, XkbIndicatorMapPtr);
PFN_XkbSetNamedIndicator_PROC XkbSetNamedIndicator_PROC = 0;
#   define XkbSetNamedIndicator (assert(XkbSetNamedIndicator_PROC != 0), XkbSetNamedIndicator_PROC)

typedef int (* PFN_XkbSetNames_PROC) (Display *, unsigned int, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbSetNames_PROC XkbSetNames_PROC = 0;
#   define XkbSetNames (assert(XkbSetNames_PROC != 0), XkbSetNames_PROC)

typedef int (* PFN_XkbSetPerClientControls_PROC) (Display *, unsigned int, unsigned int *);
PFN_XkbSetPerClientControls_PROC XkbSetPerClientControls_PROC = 0;
#   define XkbSetPerClientControls (assert(XkbSetPerClientControls_PROC != 0), XkbSetPerClientControls_PROC)

typedef int (* PFN_XkbSetServerInternalMods_PROC) (Display *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
PFN_XkbSetServerInternalMods_PROC XkbSetServerInternalMods_PROC = 0;
#   define XkbSetServerInternalMods (assert(XkbSetServerInternalMods_PROC != 0), XkbSetServerInternalMods_PROC)

typedef unsigned int (* PFN_XkbSetXlibControls_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbSetXlibControls_PROC XkbSetXlibControls_PROC = 0;
#   define XkbSetXlibControls (assert(XkbSetXlibControls_PROC != 0), XkbSetXlibControls_PROC)

typedef char (* PFN_XkbToControl_PROC) (char);
PFN_XkbToControl_PROC XkbToControl_PROC = 0;
#   define XkbToControl (assert(XkbToControl_PROC != 0), XkbToControl_PROC)

typedef int (* PFN_XkbTranslateKeyCode_PROC) (XkbDescPtr, KeyCode, unsigned int, unsigned int *, KeySym *);
PFN_XkbTranslateKeyCode_PROC XkbTranslateKeyCode_PROC = 0;
#   define XkbTranslateKeyCode (assert(XkbTranslateKeyCode_PROC != 0), XkbTranslateKeyCode_PROC)

typedef int (* PFN_XkbTranslateKeySym_PROC) (Display *, KeySym *, unsigned int, char *, int, int *);
PFN_XkbTranslateKeySym_PROC XkbTranslateKeySym_PROC = 0;
#   define XkbTranslateKeySym (assert(XkbTranslateKeySym_PROC != 0), XkbTranslateKeySym_PROC)

typedef int (* PFN_XkbUpdateActionVirtualMods_PROC) (XkbDescPtr, XkbAction *, unsigned int);
PFN_XkbUpdateActionVirtualMods_PROC XkbUpdateActionVirtualMods_PROC = 0;
#   define XkbUpdateActionVirtualMods (assert(XkbUpdateActionVirtualMods_PROC != 0), XkbUpdateActionVirtualMods_PROC)

typedef void (* PFN_XkbUpdateKeyTypeVirtualMods_PROC) (XkbDescPtr, XkbKeyTypePtr, unsigned int, XkbChangesPtr);
PFN_XkbUpdateKeyTypeVirtualMods_PROC XkbUpdateKeyTypeVirtualMods_PROC = 0;
#   define XkbUpdateKeyTypeVirtualMods (assert(XkbUpdateKeyTypeVirtualMods_PROC != 0), XkbUpdateKeyTypeVirtualMods_PROC)

typedef int (* PFN_XkbUpdateMapFromCore_PROC) (XkbDescPtr, KeyCode, int, int, KeySym *, XkbChangesPtr);
PFN_XkbUpdateMapFromCore_PROC XkbUpdateMapFromCore_PROC = 0;
#   define XkbUpdateMapFromCore (assert(XkbUpdateMapFromCore_PROC != 0), XkbUpdateMapFromCore_PROC)

typedef int (* PFN_XkbUseExtension_PROC) (Display *, int *, int *);
PFN_XkbUseExtension_PROC XkbUseExtension_PROC = 0;
#   define XkbUseExtension (assert(XkbUseExtension_PROC != 0), XkbUseExtension_PROC)

typedef int (* PFN_XkbVirtualModsToReal_PROC) (XkbDescPtr, unsigned int, unsigned int *);
PFN_XkbVirtualModsToReal_PROC XkbVirtualModsToReal_PROC = 0;
#   define XkbVirtualModsToReal (assert(XkbVirtualModsToReal_PROC != 0), XkbVirtualModsToReal_PROC)

typedef unsigned int (* PFN_XkbXlibControlsImplemented_PROC) (void);
PFN_XkbXlibControlsImplemented_PROC XkbXlibControlsImplemented_PROC = 0;
#   define XkbXlibControlsImplemented (assert(XkbXlibControlsImplemented_PROC != 0), XkbXlibControlsImplemented_PROC)


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

    /* libX11: Xlib.h */
    XActivateScreenSaver_PROC = (PFN_XActivateScreenSaver_PROC) dlsym(handle, "XActivateScreenSaver");
    XAddConnectionWatch_PROC = (PFN_XAddConnectionWatch_PROC) dlsym(handle, "XAddConnectionWatch");
    XAddExtension_PROC = (PFN_XAddExtension_PROC) dlsym(handle, "XAddExtension");
    XAddHost_PROC = (PFN_XAddHost_PROC) dlsym(handle, "XAddHost");
    XAddHosts_PROC = (PFN_XAddHosts_PROC) dlsym(handle, "XAddHosts");
    XAddToExtensionList_PROC = (PFN_XAddToExtensionList_PROC) dlsym(handle, "XAddToExtensionList");
    XAddToSaveSet_PROC = (PFN_XAddToSaveSet_PROC) dlsym(handle, "XAddToSaveSet");
    XAllPlanes_PROC = (PFN_XAllPlanes_PROC) dlsym(handle, "XAllPlanes");
    XAllocColor_PROC = (PFN_XAllocColor_PROC) dlsym(handle, "XAllocColor");
    XAllocColorCells_PROC = (PFN_XAllocColorCells_PROC) dlsym(handle, "XAllocColorCells");
    XAllocColorPlanes_PROC = (PFN_XAllocColorPlanes_PROC) dlsym(handle, "XAllocColorPlanes");
    XAllocNamedColor_PROC = (PFN_XAllocNamedColor_PROC) dlsym(handle, "XAllocNamedColor");
    XAllowEvents_PROC = (PFN_XAllowEvents_PROC) dlsym(handle, "XAllowEvents");
    XAutoRepeatOff_PROC = (PFN_XAutoRepeatOff_PROC) dlsym(handle, "XAutoRepeatOff");
    XAutoRepeatOn_PROC = (PFN_XAutoRepeatOn_PROC) dlsym(handle, "XAutoRepeatOn");
    XBaseFontNameListOfFontSet_PROC = (PFN_XBaseFontNameListOfFontSet_PROC) dlsym(handle, "XBaseFontNameListOfFontSet");
    XBell_PROC = (PFN_XBell_PROC) dlsym(handle, "XBell");
    XBitmapBitOrder_PROC = (PFN_XBitmapBitOrder_PROC) dlsym(handle, "XBitmapBitOrder");
    XBitmapPad_PROC = (PFN_XBitmapPad_PROC) dlsym(handle, "XBitmapPad");
    XBitmapUnit_PROC = (PFN_XBitmapUnit_PROC) dlsym(handle, "XBitmapUnit");
    XBlackPixel_PROC = (PFN_XBlackPixel_PROC) dlsym(handle, "XBlackPixel");
    XBlackPixelOfScreen_PROC = (PFN_XBlackPixelOfScreen_PROC) dlsym(handle, "XBlackPixelOfScreen");
    XCellsOfScreen_PROC = (PFN_XCellsOfScreen_PROC) dlsym(handle, "XCellsOfScreen");
    XChangeActivePointerGrab_PROC = (PFN_XChangeActivePointerGrab_PROC) dlsym(handle, "XChangeActivePointerGrab");
    XChangeGC_PROC = (PFN_XChangeGC_PROC) dlsym(handle, "XChangeGC");
    XChangeKeyboardControl_PROC = (PFN_XChangeKeyboardControl_PROC) dlsym(handle, "XChangeKeyboardControl");
    XChangeKeyboardMapping_PROC = (PFN_XChangeKeyboardMapping_PROC) dlsym(handle, "XChangeKeyboardMapping");
    XChangePointerControl_PROC = (PFN_XChangePointerControl_PROC) dlsym(handle, "XChangePointerControl");
    XChangeProperty_PROC = (PFN_XChangeProperty_PROC) dlsym(handle, "XChangeProperty");
    XChangeSaveSet_PROC = (PFN_XChangeSaveSet_PROC) dlsym(handle, "XChangeSaveSet");
    XChangeWindowAttributes_PROC = (PFN_XChangeWindowAttributes_PROC) dlsym(handle, "XChangeWindowAttributes");
    XCheckIfEvent_PROC = (PFN_XCheckIfEvent_PROC) dlsym(handle, "XCheckIfEvent");
    XCheckMaskEvent_PROC = (PFN_XCheckMaskEvent_PROC) dlsym(handle, "XCheckMaskEvent");
    XCheckTypedEvent_PROC = (PFN_XCheckTypedEvent_PROC) dlsym(handle, "XCheckTypedEvent");
    XCheckTypedWindowEvent_PROC = (PFN_XCheckTypedWindowEvent_PROC) dlsym(handle, "XCheckTypedWindowEvent");
    XCheckWindowEvent_PROC = (PFN_XCheckWindowEvent_PROC) dlsym(handle, "XCheckWindowEvent");
    XCirculateSubwindows_PROC = (PFN_XCirculateSubwindows_PROC) dlsym(handle, "XCirculateSubwindows");
    XCirculateSubwindowsDown_PROC = (PFN_XCirculateSubwindowsDown_PROC) dlsym(handle, "XCirculateSubwindowsDown");
    XCirculateSubwindowsUp_PROC = (PFN_XCirculateSubwindowsUp_PROC) dlsym(handle, "XCirculateSubwindowsUp");
    XClearArea_PROC = (PFN_XClearArea_PROC) dlsym(handle, "XClearArea");
    XClearWindow_PROC = (PFN_XClearWindow_PROC) dlsym(handle, "XClearWindow");
    XCloseDisplay_PROC = (PFN_XCloseDisplay_PROC) dlsym(handle, "XCloseDisplay");
    XCloseIM_PROC = (PFN_XCloseIM_PROC) dlsym(handle, "XCloseIM");
    XCloseOM_PROC = (PFN_XCloseOM_PROC) dlsym(handle, "XCloseOM");
    XConfigureWindow_PROC = (PFN_XConfigureWindow_PROC) dlsym(handle, "XConfigureWindow");
    XConnectionNumber_PROC = (PFN_XConnectionNumber_PROC) dlsym(handle, "XConnectionNumber");
    XContextDependentDrawing_PROC = (PFN_XContextDependentDrawing_PROC) dlsym(handle, "XContextDependentDrawing");
    XContextualDrawing_PROC = (PFN_XContextualDrawing_PROC) dlsym(handle, "XContextualDrawing");
    XConvertSelection_PROC = (PFN_XConvertSelection_PROC) dlsym(handle, "XConvertSelection");
    XCopyArea_PROC = (PFN_XCopyArea_PROC) dlsym(handle, "XCopyArea");
    XCopyColormapAndFree_PROC = (PFN_XCopyColormapAndFree_PROC) dlsym(handle, "XCopyColormapAndFree");
    XCopyGC_PROC = (PFN_XCopyGC_PROC) dlsym(handle, "XCopyGC");
    XCopyPlane_PROC = (PFN_XCopyPlane_PROC) dlsym(handle, "XCopyPlane");
    XCreateBitmapFromData_PROC = (PFN_XCreateBitmapFromData_PROC) dlsym(handle, "XCreateBitmapFromData");
    XCreateColormap_PROC = (PFN_XCreateColormap_PROC) dlsym(handle, "XCreateColormap");
    XCreateFontCursor_PROC = (PFN_XCreateFontCursor_PROC) dlsym(handle, "XCreateFontCursor");
    XCreateFontSet_PROC = (PFN_XCreateFontSet_PROC) dlsym(handle, "XCreateFontSet");
    XCreateGC_PROC = (PFN_XCreateGC_PROC) dlsym(handle, "XCreateGC");
    XCreateGlyphCursor_PROC = (PFN_XCreateGlyphCursor_PROC) dlsym(handle, "XCreateGlyphCursor");
    XCreateIC_PROC = (PFN_XCreateIC_PROC) dlsym(handle, "XCreateIC");
    XCreateImage_PROC = (PFN_XCreateImage_PROC) dlsym(handle, "XCreateImage");
    XCreateOC_PROC = (PFN_XCreateOC_PROC) dlsym(handle, "XCreateOC");
    XCreatePixmap_PROC = (PFN_XCreatePixmap_PROC) dlsym(handle, "XCreatePixmap");
    XCreatePixmapCursor_PROC = (PFN_XCreatePixmapCursor_PROC) dlsym(handle, "XCreatePixmapCursor");
    XCreatePixmapFromBitmapData_PROC = (PFN_XCreatePixmapFromBitmapData_PROC) dlsym(handle, "XCreatePixmapFromBitmapData");
    XCreateSimpleWindow_PROC = (PFN_XCreateSimpleWindow_PROC) dlsym(handle, "XCreateSimpleWindow");
    XCreateWindow_PROC = (PFN_XCreateWindow_PROC) dlsym(handle, "XCreateWindow");
    XDefaultColormap_PROC = (PFN_XDefaultColormap_PROC) dlsym(handle, "XDefaultColormap");
    XDefaultColormapOfScreen_PROC = (PFN_XDefaultColormapOfScreen_PROC) dlsym(handle, "XDefaultColormapOfScreen");
    XDefaultDepth_PROC = (PFN_XDefaultDepth_PROC) dlsym(handle, "XDefaultDepth");
    XDefaultDepthOfScreen_PROC = (PFN_XDefaultDepthOfScreen_PROC) dlsym(handle, "XDefaultDepthOfScreen");
    XDefaultGC_PROC = (PFN_XDefaultGC_PROC) dlsym(handle, "XDefaultGC");
    XDefaultGCOfScreen_PROC = (PFN_XDefaultGCOfScreen_PROC) dlsym(handle, "XDefaultGCOfScreen");
    XDefaultRootWindow_PROC = (PFN_XDefaultRootWindow_PROC) dlsym(handle, "XDefaultRootWindow");
    XDefaultScreen_PROC = (PFN_XDefaultScreen_PROC) dlsym(handle, "XDefaultScreen");
    XDefaultScreenOfDisplay_PROC = (PFN_XDefaultScreenOfDisplay_PROC) dlsym(handle, "XDefaultScreenOfDisplay");
    XDefaultVisual_PROC = (PFN_XDefaultVisual_PROC) dlsym(handle, "XDefaultVisual");
    XDefaultVisualOfScreen_PROC = (PFN_XDefaultVisualOfScreen_PROC) dlsym(handle, "XDefaultVisualOfScreen");
    XDefineCursor_PROC = (PFN_XDefineCursor_PROC) dlsym(handle, "XDefineCursor");
    XDeleteModifiermapEntry_PROC = (PFN_XDeleteModifiermapEntry_PROC) dlsym(handle, "XDeleteModifiermapEntry");
    XDeleteProperty_PROC = (PFN_XDeleteProperty_PROC) dlsym(handle, "XDeleteProperty");
    XDestroyIC_PROC = (PFN_XDestroyIC_PROC) dlsym(handle, "XDestroyIC");
    XDestroyOC_PROC = (PFN_XDestroyOC_PROC) dlsym(handle, "XDestroyOC");
    XDestroySubwindows_PROC = (PFN_XDestroySubwindows_PROC) dlsym(handle, "XDestroySubwindows");
    XDestroyWindow_PROC = (PFN_XDestroyWindow_PROC) dlsym(handle, "XDestroyWindow");
    XDirectionalDependentDrawing_PROC = (PFN_XDirectionalDependentDrawing_PROC) dlsym(handle, "XDirectionalDependentDrawing");
    XDisableAccessControl_PROC = (PFN_XDisableAccessControl_PROC) dlsym(handle, "XDisableAccessControl");
    XDisplayCells_PROC = (PFN_XDisplayCells_PROC) dlsym(handle, "XDisplayCells");
    XDisplayHeight_PROC = (PFN_XDisplayHeight_PROC) dlsym(handle, "XDisplayHeight");
    XDisplayHeightMM_PROC = (PFN_XDisplayHeightMM_PROC) dlsym(handle, "XDisplayHeightMM");
    XDisplayKeycodes_PROC = (PFN_XDisplayKeycodes_PROC) dlsym(handle, "XDisplayKeycodes");
    XDisplayMotionBufferSize_PROC = (PFN_XDisplayMotionBufferSize_PROC) dlsym(handle, "XDisplayMotionBufferSize");
    XDisplayName_PROC = (PFN_XDisplayName_PROC) dlsym(handle, "XDisplayName");
    XDisplayOfIM_PROC = (PFN_XDisplayOfIM_PROC) dlsym(handle, "XDisplayOfIM");
    XDisplayOfOM_PROC = (PFN_XDisplayOfOM_PROC) dlsym(handle, "XDisplayOfOM");
    XDisplayOfScreen_PROC = (PFN_XDisplayOfScreen_PROC) dlsym(handle, "XDisplayOfScreen");
    XDisplayPlanes_PROC = (PFN_XDisplayPlanes_PROC) dlsym(handle, "XDisplayPlanes");
    XDisplayString_PROC = (PFN_XDisplayString_PROC) dlsym(handle, "XDisplayString");
    XDisplayWidth_PROC = (PFN_XDisplayWidth_PROC) dlsym(handle, "XDisplayWidth");
    XDisplayWidthMM_PROC = (PFN_XDisplayWidthMM_PROC) dlsym(handle, "XDisplayWidthMM");
    XDoesBackingStore_PROC = (PFN_XDoesBackingStore_PROC) dlsym(handle, "XDoesBackingStore");
    XDoesSaveUnders_PROC = (PFN_XDoesSaveUnders_PROC) dlsym(handle, "XDoesSaveUnders");
    XDrawArc_PROC = (PFN_XDrawArc_PROC) dlsym(handle, "XDrawArc");
    XDrawArcs_PROC = (PFN_XDrawArcs_PROC) dlsym(handle, "XDrawArcs");
    XDrawImageString_PROC = (PFN_XDrawImageString_PROC) dlsym(handle, "XDrawImageString");
    XDrawImageString16_PROC = (PFN_XDrawImageString16_PROC) dlsym(handle, "XDrawImageString16");
    XDrawLine_PROC = (PFN_XDrawLine_PROC) dlsym(handle, "XDrawLine");
    XDrawLines_PROC = (PFN_XDrawLines_PROC) dlsym(handle, "XDrawLines");
    XDrawPoint_PROC = (PFN_XDrawPoint_PROC) dlsym(handle, "XDrawPoint");
    XDrawPoints_PROC = (PFN_XDrawPoints_PROC) dlsym(handle, "XDrawPoints");
    XDrawRectangle_PROC = (PFN_XDrawRectangle_PROC) dlsym(handle, "XDrawRectangle");
    XDrawRectangles_PROC = (PFN_XDrawRectangles_PROC) dlsym(handle, "XDrawRectangles");
    XDrawSegments_PROC = (PFN_XDrawSegments_PROC) dlsym(handle, "XDrawSegments");
    XDrawString_PROC = (PFN_XDrawString_PROC) dlsym(handle, "XDrawString");
    XDrawString16_PROC = (PFN_XDrawString16_PROC) dlsym(handle, "XDrawString16");
    XDrawText_PROC = (PFN_XDrawText_PROC) dlsym(handle, "XDrawText");
    XDrawText16_PROC = (PFN_XDrawText16_PROC) dlsym(handle, "XDrawText16");
    XEHeadOfExtensionList_PROC = (PFN_XEHeadOfExtensionList_PROC) dlsym(handle, "XEHeadOfExtensionList");
    XEnableAccessControl_PROC = (PFN_XEnableAccessControl_PROC) dlsym(handle, "XEnableAccessControl");
    XEventMaskOfScreen_PROC = (PFN_XEventMaskOfScreen_PROC) dlsym(handle, "XEventMaskOfScreen");
    XEventsQueued_PROC = (PFN_XEventsQueued_PROC) dlsym(handle, "XEventsQueued");
    XExtendedMaxRequestSize_PROC = (PFN_XExtendedMaxRequestSize_PROC) dlsym(handle, "XExtendedMaxRequestSize");
    XExtentsOfFontSet_PROC = (PFN_XExtentsOfFontSet_PROC) dlsym(handle, "XExtentsOfFontSet");
    XFetchBuffer_PROC = (PFN_XFetchBuffer_PROC) dlsym(handle, "XFetchBuffer");
    XFetchBytes_PROC = (PFN_XFetchBytes_PROC) dlsym(handle, "XFetchBytes");
    XFetchName_PROC = (PFN_XFetchName_PROC) dlsym(handle, "XFetchName");
    XFillArc_PROC = (PFN_XFillArc_PROC) dlsym(handle, "XFillArc");
    XFillArcs_PROC = (PFN_XFillArcs_PROC) dlsym(handle, "XFillArcs");
    XFillPolygon_PROC = (PFN_XFillPolygon_PROC) dlsym(handle, "XFillPolygon");
    XFillRectangle_PROC = (PFN_XFillRectangle_PROC) dlsym(handle, "XFillRectangle");
    XFillRectangles_PROC = (PFN_XFillRectangles_PROC) dlsym(handle, "XFillRectangles");
    XFilterEvent_PROC = (PFN_XFilterEvent_PROC) dlsym(handle, "XFilterEvent");
    XFindOnExtensionList_PROC = (PFN_XFindOnExtensionList_PROC) dlsym(handle, "XFindOnExtensionList");
    XFlush_PROC = (PFN_XFlush_PROC) dlsym(handle, "XFlush");
    XFlushGC_PROC = (PFN_XFlushGC_PROC) dlsym(handle, "XFlushGC");
    XFontsOfFontSet_PROC = (PFN_XFontsOfFontSet_PROC) dlsym(handle, "XFontsOfFontSet");
    XForceScreenSaver_PROC = (PFN_XForceScreenSaver_PROC) dlsym(handle, "XForceScreenSaver");
    XFree_PROC = (PFN_XFree_PROC) dlsym(handle, "XFree");
    XFreeColormap_PROC = (PFN_XFreeColormap_PROC) dlsym(handle, "XFreeColormap");
    XFreeColors_PROC = (PFN_XFreeColors_PROC) dlsym(handle, "XFreeColors");
    XFreeCursor_PROC = (PFN_XFreeCursor_PROC) dlsym(handle, "XFreeCursor");
    XFreeEventData_PROC = (PFN_XFreeEventData_PROC) dlsym(handle, "XFreeEventData");
    XFreeExtensionList_PROC = (PFN_XFreeExtensionList_PROC) dlsym(handle, "XFreeExtensionList");
    XFreeFont_PROC = (PFN_XFreeFont_PROC) dlsym(handle, "XFreeFont");
    XFreeFontInfo_PROC = (PFN_XFreeFontInfo_PROC) dlsym(handle, "XFreeFontInfo");
    XFreeFontNames_PROC = (PFN_XFreeFontNames_PROC) dlsym(handle, "XFreeFontNames");
    XFreeFontPath_PROC = (PFN_XFreeFontPath_PROC) dlsym(handle, "XFreeFontPath");
    XFreeFontSet_PROC = (PFN_XFreeFontSet_PROC) dlsym(handle, "XFreeFontSet");
    XFreeGC_PROC = (PFN_XFreeGC_PROC) dlsym(handle, "XFreeGC");
    XFreeModifiermap_PROC = (PFN_XFreeModifiermap_PROC) dlsym(handle, "XFreeModifiermap");
    XFreePixmap_PROC = (PFN_XFreePixmap_PROC) dlsym(handle, "XFreePixmap");
    XFreeStringList_PROC = (PFN_XFreeStringList_PROC) dlsym(handle, "XFreeStringList");
    XFreeThreads_PROC = (PFN_XFreeThreads_PROC) dlsym(handle, "XFreeThreads");
    XGContextFromGC_PROC = (PFN_XGContextFromGC_PROC) dlsym(handle, "XGContextFromGC");
    XGeometry_PROC = (PFN_XGeometry_PROC) dlsym(handle, "XGeometry");
    XGetAtomName_PROC = (PFN_XGetAtomName_PROC) dlsym(handle, "XGetAtomName");
    XGetAtomNames_PROC = (PFN_XGetAtomNames_PROC) dlsym(handle, "XGetAtomNames");
    XGetCommand_PROC = (PFN_XGetCommand_PROC) dlsym(handle, "XGetCommand");
    XGetDefault_PROC = (PFN_XGetDefault_PROC) dlsym(handle, "XGetDefault");
    XGetErrorDatabaseText_PROC = (PFN_XGetErrorDatabaseText_PROC) dlsym(handle, "XGetErrorDatabaseText");
    XGetErrorText_PROC = (PFN_XGetErrorText_PROC) dlsym(handle, "XGetErrorText");
    XGetEventData_PROC = (PFN_XGetEventData_PROC) dlsym(handle, "XGetEventData");
    XGetFontPath_PROC = (PFN_XGetFontPath_PROC) dlsym(handle, "XGetFontPath");
    XGetFontProperty_PROC = (PFN_XGetFontProperty_PROC) dlsym(handle, "XGetFontProperty");
    XGetGCValues_PROC = (PFN_XGetGCValues_PROC) dlsym(handle, "XGetGCValues");
    XGetGeometry_PROC = (PFN_XGetGeometry_PROC) dlsym(handle, "XGetGeometry");
    XGetICValues_PROC = (PFN_XGetICValues_PROC) dlsym(handle, "XGetICValues");
    XGetIMValues_PROC = (PFN_XGetIMValues_PROC) dlsym(handle, "XGetIMValues");
    XGetIconName_PROC = (PFN_XGetIconName_PROC) dlsym(handle, "XGetIconName");
    XGetImage_PROC = (PFN_XGetImage_PROC) dlsym(handle, "XGetImage");
    XGetInputFocus_PROC = (PFN_XGetInputFocus_PROC) dlsym(handle, "XGetInputFocus");
    XGetKeyboardControl_PROC = (PFN_XGetKeyboardControl_PROC) dlsym(handle, "XGetKeyboardControl");
    XGetKeyboardMapping_PROC = (PFN_XGetKeyboardMapping_PROC) dlsym(handle, "XGetKeyboardMapping");
    XGetModifierMapping_PROC = (PFN_XGetModifierMapping_PROC) dlsym(handle, "XGetModifierMapping");
    XGetMotionEvents_PROC = (PFN_XGetMotionEvents_PROC) dlsym(handle, "XGetMotionEvents");
    XGetOCValues_PROC = (PFN_XGetOCValues_PROC) dlsym(handle, "XGetOCValues");
    XGetOMValues_PROC = (PFN_XGetOMValues_PROC) dlsym(handle, "XGetOMValues");
    XGetPointerControl_PROC = (PFN_XGetPointerControl_PROC) dlsym(handle, "XGetPointerControl");
    XGetPointerMapping_PROC = (PFN_XGetPointerMapping_PROC) dlsym(handle, "XGetPointerMapping");
    XGetScreenSaver_PROC = (PFN_XGetScreenSaver_PROC) dlsym(handle, "XGetScreenSaver");
    XGetSelectionOwner_PROC = (PFN_XGetSelectionOwner_PROC) dlsym(handle, "XGetSelectionOwner");
    XGetSubImage_PROC = (PFN_XGetSubImage_PROC) dlsym(handle, "XGetSubImage");
    XGetTransientForHint_PROC = (PFN_XGetTransientForHint_PROC) dlsym(handle, "XGetTransientForHint");
    XGetWMColormapWindows_PROC = (PFN_XGetWMColormapWindows_PROC) dlsym(handle, "XGetWMColormapWindows");
    XGetWMProtocols_PROC = (PFN_XGetWMProtocols_PROC) dlsym(handle, "XGetWMProtocols");
    XGetWindowAttributes_PROC = (PFN_XGetWindowAttributes_PROC) dlsym(handle, "XGetWindowAttributes");
    XGetWindowProperty_PROC = (PFN_XGetWindowProperty_PROC) dlsym(handle, "XGetWindowProperty");
    XGrabButton_PROC = (PFN_XGrabButton_PROC) dlsym(handle, "XGrabButton");
    XGrabKey_PROC = (PFN_XGrabKey_PROC) dlsym(handle, "XGrabKey");
    XGrabKeyboard_PROC = (PFN_XGrabKeyboard_PROC) dlsym(handle, "XGrabKeyboard");
    XGrabPointer_PROC = (PFN_XGrabPointer_PROC) dlsym(handle, "XGrabPointer");
    XGrabServer_PROC = (PFN_XGrabServer_PROC) dlsym(handle, "XGrabServer");
    XHeightMMOfScreen_PROC = (PFN_XHeightMMOfScreen_PROC) dlsym(handle, "XHeightMMOfScreen");
    XHeightOfScreen_PROC = (PFN_XHeightOfScreen_PROC) dlsym(handle, "XHeightOfScreen");
    XIMOfIC_PROC = (PFN_XIMOfIC_PROC) dlsym(handle, "XIMOfIC");
    XIconifyWindow_PROC = (PFN_XIconifyWindow_PROC) dlsym(handle, "XIconifyWindow");
    XIfEvent_PROC = (PFN_XIfEvent_PROC) dlsym(handle, "XIfEvent");
    XImageByteOrder_PROC = (PFN_XImageByteOrder_PROC) dlsym(handle, "XImageByteOrder");
    XInitExtension_PROC = (PFN_XInitExtension_PROC) dlsym(handle, "XInitExtension");
    XInitImage_PROC = (PFN_XInitImage_PROC) dlsym(handle, "XInitImage");
    XInitThreads_PROC = (PFN_XInitThreads_PROC) dlsym(handle, "XInitThreads");
    XInsertModifiermapEntry_PROC = (PFN_XInsertModifiermapEntry_PROC) dlsym(handle, "XInsertModifiermapEntry");
    XInstallColormap_PROC = (PFN_XInstallColormap_PROC) dlsym(handle, "XInstallColormap");
    XInternAtom_PROC = (PFN_XInternAtom_PROC) dlsym(handle, "XInternAtom");
    XInternAtoms_PROC = (PFN_XInternAtoms_PROC) dlsym(handle, "XInternAtoms");
    XInternalConnectionNumbers_PROC = (PFN_XInternalConnectionNumbers_PROC) dlsym(handle, "XInternalConnectionNumbers");
    XKeycodeToKeysym_PROC = (PFN_XKeycodeToKeysym_PROC) dlsym(handle, "XKeycodeToKeysym");
    XKeysymToKeycode_PROC = (PFN_XKeysymToKeycode_PROC) dlsym(handle, "XKeysymToKeycode");
    XKeysymToString_PROC = (PFN_XKeysymToString_PROC) dlsym(handle, "XKeysymToString");
    XKillClient_PROC = (PFN_XKillClient_PROC) dlsym(handle, "XKillClient");
    XLastKnownRequestProcessed_PROC = (PFN_XLastKnownRequestProcessed_PROC) dlsym(handle, "XLastKnownRequestProcessed");
    XListDepths_PROC = (PFN_XListDepths_PROC) dlsym(handle, "XListDepths");
    XListExtensions_PROC = (PFN_XListExtensions_PROC) dlsym(handle, "XListExtensions");
    XListFonts_PROC = (PFN_XListFonts_PROC) dlsym(handle, "XListFonts");
    XListFontsWithInfo_PROC = (PFN_XListFontsWithInfo_PROC) dlsym(handle, "XListFontsWithInfo");
    XListHosts_PROC = (PFN_XListHosts_PROC) dlsym(handle, "XListHosts");
    XListInstalledColormaps_PROC = (PFN_XListInstalledColormaps_PROC) dlsym(handle, "XListInstalledColormaps");
    XListPixmapFormats_PROC = (PFN_XListPixmapFormats_PROC) dlsym(handle, "XListPixmapFormats");
    XListProperties_PROC = (PFN_XListProperties_PROC) dlsym(handle, "XListProperties");
    XLoadFont_PROC = (PFN_XLoadFont_PROC) dlsym(handle, "XLoadFont");
    XLoadQueryFont_PROC = (PFN_XLoadQueryFont_PROC) dlsym(handle, "XLoadQueryFont");
    XLocaleOfFontSet_PROC = (PFN_XLocaleOfFontSet_PROC) dlsym(handle, "XLocaleOfFontSet");
    XLocaleOfIM_PROC = (PFN_XLocaleOfIM_PROC) dlsym(handle, "XLocaleOfIM");
    XLocaleOfOM_PROC = (PFN_XLocaleOfOM_PROC) dlsym(handle, "XLocaleOfOM");
    XLockDisplay_PROC = (PFN_XLockDisplay_PROC) dlsym(handle, "XLockDisplay");
    XLookupColor_PROC = (PFN_XLookupColor_PROC) dlsym(handle, "XLookupColor");
    XLookupKeysym_PROC = (PFN_XLookupKeysym_PROC) dlsym(handle, "XLookupKeysym");
    XLowerWindow_PROC = (PFN_XLowerWindow_PROC) dlsym(handle, "XLowerWindow");
    XMapRaised_PROC = (PFN_XMapRaised_PROC) dlsym(handle, "XMapRaised");
    XMapSubwindows_PROC = (PFN_XMapSubwindows_PROC) dlsym(handle, "XMapSubwindows");
    XMapWindow_PROC = (PFN_XMapWindow_PROC) dlsym(handle, "XMapWindow");
    XMaskEvent_PROC = (PFN_XMaskEvent_PROC) dlsym(handle, "XMaskEvent");
    XMaxCmapsOfScreen_PROC = (PFN_XMaxCmapsOfScreen_PROC) dlsym(handle, "XMaxCmapsOfScreen");
    XMaxRequestSize_PROC = (PFN_XMaxRequestSize_PROC) dlsym(handle, "XMaxRequestSize");
    XMinCmapsOfScreen_PROC = (PFN_XMinCmapsOfScreen_PROC) dlsym(handle, "XMinCmapsOfScreen");
    XMoveResizeWindow_PROC = (PFN_XMoveResizeWindow_PROC) dlsym(handle, "XMoveResizeWindow");
    XMoveWindow_PROC = (PFN_XMoveWindow_PROC) dlsym(handle, "XMoveWindow");
    XNewModifiermap_PROC = (PFN_XNewModifiermap_PROC) dlsym(handle, "XNewModifiermap");
    XNextEvent_PROC = (PFN_XNextEvent_PROC) dlsym(handle, "XNextEvent");
    XNextRequest_PROC = (PFN_XNextRequest_PROC) dlsym(handle, "XNextRequest");
    XNoOp_PROC = (PFN_XNoOp_PROC) dlsym(handle, "XNoOp");
    XOMOfOC_PROC = (PFN_XOMOfOC_PROC) dlsym(handle, "XOMOfOC");
    XOpenDisplay_PROC = (PFN_XOpenDisplay_PROC) dlsym(handle, "XOpenDisplay");
    XOpenIM_PROC = (PFN_XOpenIM_PROC) dlsym(handle, "XOpenIM");
    XOpenOM_PROC = (PFN_XOpenOM_PROC) dlsym(handle, "XOpenOM");
    XParseColor_PROC = (PFN_XParseColor_PROC) dlsym(handle, "XParseColor");
    XParseGeometry_PROC = (PFN_XParseGeometry_PROC) dlsym(handle, "XParseGeometry");
    XPeekEvent_PROC = (PFN_XPeekEvent_PROC) dlsym(handle, "XPeekEvent");
    XPeekIfEvent_PROC = (PFN_XPeekIfEvent_PROC) dlsym(handle, "XPeekIfEvent");
    XPending_PROC = (PFN_XPending_PROC) dlsym(handle, "XPending");
    XPlanesOfScreen_PROC = (PFN_XPlanesOfScreen_PROC) dlsym(handle, "XPlanesOfScreen");
    XProcessInternalConnection_PROC = (PFN_XProcessInternalConnection_PROC) dlsym(handle, "XProcessInternalConnection");
    XProtocolRevision_PROC = (PFN_XProtocolRevision_PROC) dlsym(handle, "XProtocolRevision");
    XProtocolVersion_PROC = (PFN_XProtocolVersion_PROC) dlsym(handle, "XProtocolVersion");
    XPutBackEvent_PROC = (PFN_XPutBackEvent_PROC) dlsym(handle, "XPutBackEvent");
    XPutImage_PROC = (PFN_XPutImage_PROC) dlsym(handle, "XPutImage");
    XQLength_PROC = (PFN_XQLength_PROC) dlsym(handle, "XQLength");
    XQueryBestCursor_PROC = (PFN_XQueryBestCursor_PROC) dlsym(handle, "XQueryBestCursor");
    XQueryBestSize_PROC = (PFN_XQueryBestSize_PROC) dlsym(handle, "XQueryBestSize");
    XQueryBestStipple_PROC = (PFN_XQueryBestStipple_PROC) dlsym(handle, "XQueryBestStipple");
    XQueryBestTile_PROC = (PFN_XQueryBestTile_PROC) dlsym(handle, "XQueryBestTile");
    XQueryColor_PROC = (PFN_XQueryColor_PROC) dlsym(handle, "XQueryColor");
    XQueryColors_PROC = (PFN_XQueryColors_PROC) dlsym(handle, "XQueryColors");
    XQueryExtension_PROC = (PFN_XQueryExtension_PROC) dlsym(handle, "XQueryExtension");
    XQueryFont_PROC = (PFN_XQueryFont_PROC) dlsym(handle, "XQueryFont");
    XQueryKeymap_PROC = (PFN_XQueryKeymap_PROC) dlsym(handle, "XQueryKeymap");
    XQueryPointer_PROC = (PFN_XQueryPointer_PROC) dlsym(handle, "XQueryPointer");
    XQueryTextExtents_PROC = (PFN_XQueryTextExtents_PROC) dlsym(handle, "XQueryTextExtents");
    XQueryTextExtents16_PROC = (PFN_XQueryTextExtents16_PROC) dlsym(handle, "XQueryTextExtents16");
    XQueryTree_PROC = (PFN_XQueryTree_PROC) dlsym(handle, "XQueryTree");
    XRaiseWindow_PROC = (PFN_XRaiseWindow_PROC) dlsym(handle, "XRaiseWindow");
    XReadBitmapFile_PROC = (PFN_XReadBitmapFile_PROC) dlsym(handle, "XReadBitmapFile");
    XReadBitmapFileData_PROC = (PFN_XReadBitmapFileData_PROC) dlsym(handle, "XReadBitmapFileData");
    XRebindKeysym_PROC = (PFN_XRebindKeysym_PROC) dlsym(handle, "XRebindKeysym");
    XRecolorCursor_PROC = (PFN_XRecolorCursor_PROC) dlsym(handle, "XRecolorCursor");
    XReconfigureWMWindow_PROC = (PFN_XReconfigureWMWindow_PROC) dlsym(handle, "XReconfigureWMWindow");
    XRefreshKeyboardMapping_PROC = (PFN_XRefreshKeyboardMapping_PROC) dlsym(handle, "XRefreshKeyboardMapping");
    XRegisterIMInstantiateCallback_PROC = (PFN_XRegisterIMInstantiateCallback_PROC) dlsym(handle, "XRegisterIMInstantiateCallback");
    XRemoveConnectionWatch_PROC = (PFN_XRemoveConnectionWatch_PROC) dlsym(handle, "XRemoveConnectionWatch");
    XRemoveFromSaveSet_PROC = (PFN_XRemoveFromSaveSet_PROC) dlsym(handle, "XRemoveFromSaveSet");
    XRemoveHost_PROC = (PFN_XRemoveHost_PROC) dlsym(handle, "XRemoveHost");
    XRemoveHosts_PROC = (PFN_XRemoveHosts_PROC) dlsym(handle, "XRemoveHosts");
    XReparentWindow_PROC = (PFN_XReparentWindow_PROC) dlsym(handle, "XReparentWindow");
    XResetScreenSaver_PROC = (PFN_XResetScreenSaver_PROC) dlsym(handle, "XResetScreenSaver");
    XResizeWindow_PROC = (PFN_XResizeWindow_PROC) dlsym(handle, "XResizeWindow");
    XResourceManagerString_PROC = (PFN_XResourceManagerString_PROC) dlsym(handle, "XResourceManagerString");
    XRestackWindows_PROC = (PFN_XRestackWindows_PROC) dlsym(handle, "XRestackWindows");
    XRootWindow_PROC = (PFN_XRootWindow_PROC) dlsym(handle, "XRootWindow");
    XRootWindowOfScreen_PROC = (PFN_XRootWindowOfScreen_PROC) dlsym(handle, "XRootWindowOfScreen");
    XRotateBuffers_PROC = (PFN_XRotateBuffers_PROC) dlsym(handle, "XRotateBuffers");
    XRotateWindowProperties_PROC = (PFN_XRotateWindowProperties_PROC) dlsym(handle, "XRotateWindowProperties");
    XScreenCount_PROC = (PFN_XScreenCount_PROC) dlsym(handle, "XScreenCount");
    XScreenNumberOfScreen_PROC = (PFN_XScreenNumberOfScreen_PROC) dlsym(handle, "XScreenNumberOfScreen");
    XScreenOfDisplay_PROC = (PFN_XScreenOfDisplay_PROC) dlsym(handle, "XScreenOfDisplay");
    XScreenResourceString_PROC = (PFN_XScreenResourceString_PROC) dlsym(handle, "XScreenResourceString");
    XSelectInput_PROC = (PFN_XSelectInput_PROC) dlsym(handle, "XSelectInput");
    XSendEvent_PROC = (PFN_XSendEvent_PROC) dlsym(handle, "XSendEvent");
    XServerVendor_PROC = (PFN_XServerVendor_PROC) dlsym(handle, "XServerVendor");
    XSetAccessControl_PROC = (PFN_XSetAccessControl_PROC) dlsym(handle, "XSetAccessControl");
    XSetArcMode_PROC = (PFN_XSetArcMode_PROC) dlsym(handle, "XSetArcMode");
    XSetAuthorization_PROC = (PFN_XSetAuthorization_PROC) dlsym(handle, "XSetAuthorization");
    XSetBackground_PROC = (PFN_XSetBackground_PROC) dlsym(handle, "XSetBackground");
    XSetClipMask_PROC = (PFN_XSetClipMask_PROC) dlsym(handle, "XSetClipMask");
    XSetClipOrigin_PROC = (PFN_XSetClipOrigin_PROC) dlsym(handle, "XSetClipOrigin");
    XSetClipRectangles_PROC = (PFN_XSetClipRectangles_PROC) dlsym(handle, "XSetClipRectangles");
    XSetCloseDownMode_PROC = (PFN_XSetCloseDownMode_PROC) dlsym(handle, "XSetCloseDownMode");
    XSetCommand_PROC = (PFN_XSetCommand_PROC) dlsym(handle, "XSetCommand");
    XSetDashes_PROC = (PFN_XSetDashes_PROC) dlsym(handle, "XSetDashes");
    XSetErrorHandler_PROC = (PFN_XSetErrorHandler_PROC) dlsym(handle, "XSetErrorHandler");
    XSetFillRule_PROC = (PFN_XSetFillRule_PROC) dlsym(handle, "XSetFillRule");
    XSetFillStyle_PROC = (PFN_XSetFillStyle_PROC) dlsym(handle, "XSetFillStyle");
    XSetFont_PROC = (PFN_XSetFont_PROC) dlsym(handle, "XSetFont");
    XSetFontPath_PROC = (PFN_XSetFontPath_PROC) dlsym(handle, "XSetFontPath");
    XSetForeground_PROC = (PFN_XSetForeground_PROC) dlsym(handle, "XSetForeground");
    XSetFunction_PROC = (PFN_XSetFunction_PROC) dlsym(handle, "XSetFunction");
    XSetGraphicsExposures_PROC = (PFN_XSetGraphicsExposures_PROC) dlsym(handle, "XSetGraphicsExposures");
    XSetICFocus_PROC = (PFN_XSetICFocus_PROC) dlsym(handle, "XSetICFocus");
    XSetICValues_PROC = (PFN_XSetICValues_PROC) dlsym(handle, "XSetICValues");
    XSetIMValues_PROC = (PFN_XSetIMValues_PROC) dlsym(handle, "XSetIMValues");
    XSetIOErrorExitHandler_PROC = (PFN_XSetIOErrorExitHandler_PROC) dlsym(handle, "XSetIOErrorExitHandler");
    XSetIOErrorHandler_PROC = (PFN_XSetIOErrorHandler_PROC) dlsym(handle, "XSetIOErrorHandler");
    XSetIconName_PROC = (PFN_XSetIconName_PROC) dlsym(handle, "XSetIconName");
    XSetInputFocus_PROC = (PFN_XSetInputFocus_PROC) dlsym(handle, "XSetInputFocus");
    XSetLineAttributes_PROC = (PFN_XSetLineAttributes_PROC) dlsym(handle, "XSetLineAttributes");
    XSetLocaleModifiers_PROC = (PFN_XSetLocaleModifiers_PROC) dlsym(handle, "XSetLocaleModifiers");
    XSetModifierMapping_PROC = (PFN_XSetModifierMapping_PROC) dlsym(handle, "XSetModifierMapping");
    XSetOCValues_PROC = (PFN_XSetOCValues_PROC) dlsym(handle, "XSetOCValues");
    XSetOMValues_PROC = (PFN_XSetOMValues_PROC) dlsym(handle, "XSetOMValues");
    XSetPlaneMask_PROC = (PFN_XSetPlaneMask_PROC) dlsym(handle, "XSetPlaneMask");
    XSetPointerMapping_PROC = (PFN_XSetPointerMapping_PROC) dlsym(handle, "XSetPointerMapping");
    XSetScreenSaver_PROC = (PFN_XSetScreenSaver_PROC) dlsym(handle, "XSetScreenSaver");
    XSetSelectionOwner_PROC = (PFN_XSetSelectionOwner_PROC) dlsym(handle, "XSetSelectionOwner");
    XSetState_PROC = (PFN_XSetState_PROC) dlsym(handle, "XSetState");
    XSetStipple_PROC = (PFN_XSetStipple_PROC) dlsym(handle, "XSetStipple");
    XSetSubwindowMode_PROC = (PFN_XSetSubwindowMode_PROC) dlsym(handle, "XSetSubwindowMode");
    XSetTSOrigin_PROC = (PFN_XSetTSOrigin_PROC) dlsym(handle, "XSetTSOrigin");
    XSetTile_PROC = (PFN_XSetTile_PROC) dlsym(handle, "XSetTile");
    XSetTransientForHint_PROC = (PFN_XSetTransientForHint_PROC) dlsym(handle, "XSetTransientForHint");
    XSetWMColormapWindows_PROC = (PFN_XSetWMColormapWindows_PROC) dlsym(handle, "XSetWMColormapWindows");
    XSetWMProtocols_PROC = (PFN_XSetWMProtocols_PROC) dlsym(handle, "XSetWMProtocols");
    XSetWindowBackground_PROC = (PFN_XSetWindowBackground_PROC) dlsym(handle, "XSetWindowBackground");
    XSetWindowBackgroundPixmap_PROC = (PFN_XSetWindowBackgroundPixmap_PROC) dlsym(handle, "XSetWindowBackgroundPixmap");
    XSetWindowBorder_PROC = (PFN_XSetWindowBorder_PROC) dlsym(handle, "XSetWindowBorder");
    XSetWindowBorderPixmap_PROC = (PFN_XSetWindowBorderPixmap_PROC) dlsym(handle, "XSetWindowBorderPixmap");
    XSetWindowBorderWidth_PROC = (PFN_XSetWindowBorderWidth_PROC) dlsym(handle, "XSetWindowBorderWidth");
    XSetWindowColormap_PROC = (PFN_XSetWindowColormap_PROC) dlsym(handle, "XSetWindowColormap");
    XStoreBuffer_PROC = (PFN_XStoreBuffer_PROC) dlsym(handle, "XStoreBuffer");
    XStoreBytes_PROC = (PFN_XStoreBytes_PROC) dlsym(handle, "XStoreBytes");
    XStoreColor_PROC = (PFN_XStoreColor_PROC) dlsym(handle, "XStoreColor");
    XStoreColors_PROC = (PFN_XStoreColors_PROC) dlsym(handle, "XStoreColors");
    XStoreName_PROC = (PFN_XStoreName_PROC) dlsym(handle, "XStoreName");
    XStoreNamedColor_PROC = (PFN_XStoreNamedColor_PROC) dlsym(handle, "XStoreNamedColor");
    XStringToKeysym_PROC = (PFN_XStringToKeysym_PROC) dlsym(handle, "XStringToKeysym");
    XSupportsLocale_PROC = (PFN_XSupportsLocale_PROC) dlsym(handle, "XSupportsLocale");
    XSync_PROC = (PFN_XSync_PROC) dlsym(handle, "XSync");
    XTextExtents_PROC = (PFN_XTextExtents_PROC) dlsym(handle, "XTextExtents");
    XTextExtents16_PROC = (PFN_XTextExtents16_PROC) dlsym(handle, "XTextExtents16");
    XTextWidth_PROC = (PFN_XTextWidth_PROC) dlsym(handle, "XTextWidth");
    XTextWidth16_PROC = (PFN_XTextWidth16_PROC) dlsym(handle, "XTextWidth16");
    XTranslateCoordinates_PROC = (PFN_XTranslateCoordinates_PROC) dlsym(handle, "XTranslateCoordinates");
    XUndefineCursor_PROC = (PFN_XUndefineCursor_PROC) dlsym(handle, "XUndefineCursor");
    XUngrabButton_PROC = (PFN_XUngrabButton_PROC) dlsym(handle, "XUngrabButton");
    XUngrabKey_PROC = (PFN_XUngrabKey_PROC) dlsym(handle, "XUngrabKey");
    XUngrabKeyboard_PROC = (PFN_XUngrabKeyboard_PROC) dlsym(handle, "XUngrabKeyboard");
    XUngrabPointer_PROC = (PFN_XUngrabPointer_PROC) dlsym(handle, "XUngrabPointer");
    XUngrabServer_PROC = (PFN_XUngrabServer_PROC) dlsym(handle, "XUngrabServer");
    XUninstallColormap_PROC = (PFN_XUninstallColormap_PROC) dlsym(handle, "XUninstallColormap");
    XUnloadFont_PROC = (PFN_XUnloadFont_PROC) dlsym(handle, "XUnloadFont");
    XUnlockDisplay_PROC = (PFN_XUnlockDisplay_PROC) dlsym(handle, "XUnlockDisplay");
    XUnmapSubwindows_PROC = (PFN_XUnmapSubwindows_PROC) dlsym(handle, "XUnmapSubwindows");
    XUnmapWindow_PROC = (PFN_XUnmapWindow_PROC) dlsym(handle, "XUnmapWindow");
    XUnregisterIMInstantiateCallback_PROC = (PFN_XUnregisterIMInstantiateCallback_PROC) dlsym(handle, "XUnregisterIMInstantiateCallback");
    XUnsetICFocus_PROC = (PFN_XUnsetICFocus_PROC) dlsym(handle, "XUnsetICFocus");
    XVaCreateNestedList_PROC = (PFN_XVaCreateNestedList_PROC) dlsym(handle, "XVaCreateNestedList");
    XVendorRelease_PROC = (PFN_XVendorRelease_PROC) dlsym(handle, "XVendorRelease");
    XVisualIDFromVisual_PROC = (PFN_XVisualIDFromVisual_PROC) dlsym(handle, "XVisualIDFromVisual");
    XWarpPointer_PROC = (PFN_XWarpPointer_PROC) dlsym(handle, "XWarpPointer");
    XWhitePixel_PROC = (PFN_XWhitePixel_PROC) dlsym(handle, "XWhitePixel");
    XWhitePixelOfScreen_PROC = (PFN_XWhitePixelOfScreen_PROC) dlsym(handle, "XWhitePixelOfScreen");
    XWidthMMOfScreen_PROC = (PFN_XWidthMMOfScreen_PROC) dlsym(handle, "XWidthMMOfScreen");
    XWidthOfScreen_PROC = (PFN_XWidthOfScreen_PROC) dlsym(handle, "XWidthOfScreen");
    XWindowEvent_PROC = (PFN_XWindowEvent_PROC) dlsym(handle, "XWindowEvent");
    XWithdrawWindow_PROC = (PFN_XWithdrawWindow_PROC) dlsym(handle, "XWithdrawWindow");
    XWriteBitmapFile_PROC = (PFN_XWriteBitmapFile_PROC) dlsym(handle, "XWriteBitmapFile");
    XmbDrawImageString_PROC = (PFN_XmbDrawImageString_PROC) dlsym(handle, "XmbDrawImageString");
    XmbDrawString_PROC = (PFN_XmbDrawString_PROC) dlsym(handle, "XmbDrawString");
    XmbDrawText_PROC = (PFN_XmbDrawText_PROC) dlsym(handle, "XmbDrawText");
    XmbLookupString_PROC = (PFN_XmbLookupString_PROC) dlsym(handle, "XmbLookupString");
    XmbResetIC_PROC = (PFN_XmbResetIC_PROC) dlsym(handle, "XmbResetIC");
    XmbTextEscapement_PROC = (PFN_XmbTextEscapement_PROC) dlsym(handle, "XmbTextEscapement");
    XmbTextExtents_PROC = (PFN_XmbTextExtents_PROC) dlsym(handle, "XmbTextExtents");
    XmbTextPerCharExtents_PROC = (PFN_XmbTextPerCharExtents_PROC) dlsym(handle, "XmbTextPerCharExtents");
    XrmInitialize_PROC = (PFN_XrmInitialize_PROC) dlsym(handle, "XrmInitialize");
    Xutf8DrawImageString_PROC = (PFN_Xutf8DrawImageString_PROC) dlsym(handle, "Xutf8DrawImageString");
    Xutf8DrawString_PROC = (PFN_Xutf8DrawString_PROC) dlsym(handle, "Xutf8DrawString");
    Xutf8DrawText_PROC = (PFN_Xutf8DrawText_PROC) dlsym(handle, "Xutf8DrawText");
    Xutf8LookupString_PROC = (PFN_Xutf8LookupString_PROC) dlsym(handle, "Xutf8LookupString");
    Xutf8ResetIC_PROC = (PFN_Xutf8ResetIC_PROC) dlsym(handle, "Xutf8ResetIC");
    Xutf8TextEscapement_PROC = (PFN_Xutf8TextEscapement_PROC) dlsym(handle, "Xutf8TextEscapement");
    Xutf8TextExtents_PROC = (PFN_Xutf8TextExtents_PROC) dlsym(handle, "Xutf8TextExtents");
    Xutf8TextPerCharExtents_PROC = (PFN_Xutf8TextPerCharExtents_PROC) dlsym(handle, "Xutf8TextPerCharExtents");
    XwcDrawImageString_PROC = (PFN_XwcDrawImageString_PROC) dlsym(handle, "XwcDrawImageString");
    XwcDrawString_PROC = (PFN_XwcDrawString_PROC) dlsym(handle, "XwcDrawString");
    XwcDrawText_PROC = (PFN_XwcDrawText_PROC) dlsym(handle, "XwcDrawText");
    XwcLookupString_PROC = (PFN_XwcLookupString_PROC) dlsym(handle, "XwcLookupString");
    XwcResetIC_PROC = (PFN_XwcResetIC_PROC) dlsym(handle, "XwcResetIC");
    XwcTextEscapement_PROC = (PFN_XwcTextEscapement_PROC) dlsym(handle, "XwcTextEscapement");
    XwcTextExtents_PROC = (PFN_XwcTextExtents_PROC) dlsym(handle, "XwcTextExtents");
    XwcTextPerCharExtents_PROC = (PFN_XwcTextPerCharExtents_PROC) dlsym(handle, "XwcTextPerCharExtents");
    _Xmblen_PROC = (PFN__Xmblen_PROC) dlsym(handle, "_Xmblen");
    _Xmbtowc_PROC = (PFN__Xmbtowc_PROC) dlsym(handle, "_Xmbtowc");
    _Xwctomb_PROC = (PFN__Xwctomb_PROC) dlsym(handle, "_Xwctomb");

    /*_PROC libX11: Xutil.h */
    XAllocClassHint_PROC = (PFN_XAllocClassHint_PROC) dlsym(handle, "XAllocClassHint");
    XAllocIconSize_PROC = (PFN_XAllocIconSize_PROC) dlsym(handle, "XAllocIconSize");
    XAllocSizeHints_PROC = (PFN_XAllocSizeHints_PROC) dlsym(handle, "XAllocSizeHints");
    XAllocStandardColormap_PROC = (PFN_XAllocStandardColormap_PROC) dlsym(handle, "XAllocStandardColormap");
    XAllocWMHints_PROC = (PFN_XAllocWMHints_PROC) dlsym(handle, "XAllocWMHints");
    XClipBox_PROC = (PFN_XClipBox_PROC) dlsym(handle, "XClipBox");
    XConvertCase_PROC = (PFN_XConvertCase_PROC) dlsym(handle, "XConvertCase");
    XCreateRegion_PROC = (PFN_XCreateRegion_PROC) dlsym(handle, "XCreateRegion");
    XDefaultString_PROC = (PFN_XDefaultString_PROC) dlsym(handle, "XDefaultString");
    XDeleteContext_PROC = (PFN_XDeleteContext_PROC) dlsym(handle, "XDeleteContext");
    XDestroyRegion_PROC = (PFN_XDestroyRegion_PROC) dlsym(handle, "XDestroyRegion");
    XEmptyRegion_PROC = (PFN_XEmptyRegion_PROC) dlsym(handle, "XEmptyRegion");
    XEqualRegion_PROC = (PFN_XEqualRegion_PROC) dlsym(handle, "XEqualRegion");
    XFindContext_PROC = (PFN_XFindContext_PROC) dlsym(handle, "XFindContext");
    XGetClassHint_PROC = (PFN_XGetClassHint_PROC) dlsym(handle, "XGetClassHint");
    XGetIconSizes_PROC = (PFN_XGetIconSizes_PROC) dlsym(handle, "XGetIconSizes");
    XGetNormalHints_PROC = (PFN_XGetNormalHints_PROC) dlsym(handle, "XGetNormalHints");
    XGetRGBColormaps_PROC = (PFN_XGetRGBColormaps_PROC) dlsym(handle, "XGetRGBColormaps");
    XGetSizeHints_PROC = (PFN_XGetSizeHints_PROC) dlsym(handle, "XGetSizeHints");
    XGetStandardColormap_PROC = (PFN_XGetStandardColormap_PROC) dlsym(handle, "XGetStandardColormap");
    XGetTextProperty_PROC = (PFN_XGetTextProperty_PROC) dlsym(handle, "XGetTextProperty");
    XGetVisualInfo_PROC = (PFN_XGetVisualInfo_PROC) dlsym(handle, "XGetVisualInfo");
    XGetWMClientMachine_PROC = (PFN_XGetWMClientMachine_PROC) dlsym(handle, "XGetWMClientMachine");
    XGetWMHints_PROC = (PFN_XGetWMHints_PROC) dlsym(handle, "XGetWMHints");
    XGetWMIconName_PROC = (PFN_XGetWMIconName_PROC) dlsym(handle, "XGetWMIconName");
    XGetWMName_PROC = (PFN_XGetWMName_PROC) dlsym(handle, "XGetWMName");
    XGetWMNormalHints_PROC = (PFN_XGetWMNormalHints_PROC) dlsym(handle, "XGetWMNormalHints");
    XGetWMSizeHints_PROC = (PFN_XGetWMSizeHints_PROC) dlsym(handle, "XGetWMSizeHints");
    XGetZoomHints_PROC = (PFN_XGetZoomHints_PROC) dlsym(handle, "XGetZoomHints");
    XIntersectRegion_PROC = (PFN_XIntersectRegion_PROC) dlsym(handle, "XIntersectRegion");
    XLookupString_PROC = (PFN_XLookupString_PROC) dlsym(handle, "XLookupString");
    XMatchVisualInfo_PROC = (PFN_XMatchVisualInfo_PROC) dlsym(handle, "XMatchVisualInfo");
    XOffsetRegion_PROC = (PFN_XOffsetRegion_PROC) dlsym(handle, "XOffsetRegion");
    XPointInRegion_PROC = (PFN_XPointInRegion_PROC) dlsym(handle, "XPointInRegion");
    XPolygonRegion_PROC = (PFN_XPolygonRegion_PROC) dlsym(handle, "XPolygonRegion");
    XRectInRegion_PROC = (PFN_XRectInRegion_PROC) dlsym(handle, "XRectInRegion");
    XSaveContext_PROC = (PFN_XSaveContext_PROC) dlsym(handle, "XSaveContext");
    XSetClassHint_PROC = (PFN_XSetClassHint_PROC) dlsym(handle, "XSetClassHint");
    XSetIconSizes_PROC = (PFN_XSetIconSizes_PROC) dlsym(handle, "XSetIconSizes");
    XSetNormalHints_PROC = (PFN_XSetNormalHints_PROC) dlsym(handle, "XSetNormalHints");
    XSetRGBColormaps_PROC = (PFN_XSetRGBColormaps_PROC) dlsym(handle, "XSetRGBColormaps");
    XSetRegion_PROC = (PFN_XSetRegion_PROC) dlsym(handle, "XSetRegion");
    XSetSizeHints_PROC = (PFN_XSetSizeHints_PROC) dlsym(handle, "XSetSizeHints");
    XSetStandardColormap_PROC = (PFN_XSetStandardColormap_PROC) dlsym(handle, "XSetStandardColormap");
    XSetStandardProperties_PROC = (PFN_XSetStandardProperties_PROC) dlsym(handle, "XSetStandardProperties");
    XSetTextProperty_PROC = (PFN_XSetTextProperty_PROC) dlsym(handle, "XSetTextProperty");
    XSetWMClientMachine_PROC = (PFN_XSetWMClientMachine_PROC) dlsym(handle, "XSetWMClientMachine");
    XSetWMHints_PROC = (PFN_XSetWMHints_PROC) dlsym(handle, "XSetWMHints");
    XSetWMIconName_PROC = (PFN_XSetWMIconName_PROC) dlsym(handle, "XSetWMIconName");
    XSetWMName_PROC = (PFN_XSetWMName_PROC) dlsym(handle, "XSetWMName");
    XSetWMNormalHints_PROC = (PFN_XSetWMNormalHints_PROC) dlsym(handle, "XSetWMNormalHints");
    XSetWMProperties_PROC = (PFN_XSetWMProperties_PROC) dlsym(handle, "XSetWMProperties");
    XSetWMSizeHints_PROC = (PFN_XSetWMSizeHints_PROC) dlsym(handle, "XSetWMSizeHints");
    XSetZoomHints_PROC = (PFN_XSetZoomHints_PROC) dlsym(handle, "XSetZoomHints");
    XShrinkRegion_PROC = (PFN_XShrinkRegion_PROC) dlsym(handle, "XShrinkRegion");
    XStringListToTextProperty_PROC = (PFN_XStringListToTextProperty_PROC) dlsym(handle, "XStringListToTextProperty");
    XSubtractRegion_PROC = (PFN_XSubtractRegion_PROC) dlsym(handle, "XSubtractRegion");
    XTextPropertyToStringList_PROC = (PFN_XTextPropertyToStringList_PROC) dlsym(handle, "XTextPropertyToStringList");
    XUnionRectWithRegion_PROC = (PFN_XUnionRectWithRegion_PROC) dlsym(handle, "XUnionRectWithRegion");
    XUnionRegion_PROC = (PFN_XUnionRegion_PROC) dlsym(handle, "XUnionRegion");
    XWMGeometry_PROC = (PFN_XWMGeometry_PROC) dlsym(handle, "XWMGeometry");
    XXorRegion_PROC = (PFN_XXorRegion_PROC) dlsym(handle, "XXorRegion");
    XmbSetWMProperties_PROC = (PFN_XmbSetWMProperties_PROC) dlsym(handle, "XmbSetWMProperties");
    XmbTextListToTextProperty_PROC = (PFN_XmbTextListToTextProperty_PROC) dlsym(handle, "XmbTextListToTextProperty");
    XmbTextPropertyToTextList_PROC = (PFN_XmbTextPropertyToTextList_PROC) dlsym(handle, "XmbTextPropertyToTextList");
    Xutf8SetWMProperties_PROC = (PFN_Xutf8SetWMProperties_PROC) dlsym(handle, "Xutf8SetWMProperties");
    Xutf8TextListToTextProperty_PROC = (PFN_Xutf8TextListToTextProperty_PROC) dlsym(handle, "Xutf8TextListToTextProperty");
    Xutf8TextPropertyToTextList_PROC = (PFN_Xutf8TextPropertyToTextList_PROC) dlsym(handle, "Xutf8TextPropertyToTextList");
    XwcFreeStringList_PROC = (PFN_XwcFreeStringList_PROC) dlsym(handle, "XwcFreeStringList");
    XwcTextListToTextProperty_PROC = (PFN_XwcTextListToTextProperty_PROC) dlsym(handle, "XwcTextListToTextProperty");
    XwcTextPropertyToTextList_PROC = (PFN_XwcTextPropertyToTextList_PROC) dlsym(handle, "XwcTextPropertyToTextList");

    /*_PROC libX11: XKBlib.h */
    XkbAddDeviceLedInfo_PROC = (PFN_XkbAddDeviceLedInfo_PROC) dlsym(handle, "XkbAddDeviceLedInfo");
    XkbAddKeyType_PROC = (PFN_XkbAddKeyType_PROC) dlsym(handle, "XkbAddKeyType");
    XkbAllocClientMap_PROC = (PFN_XkbAllocClientMap_PROC) dlsym(handle, "XkbAllocClientMap");
    XkbAllocCompatMap_PROC = (PFN_XkbAllocCompatMap_PROC) dlsym(handle, "XkbAllocCompatMap");
    XkbAllocControls_PROC = (PFN_XkbAllocControls_PROC) dlsym(handle, "XkbAllocControls");
    XkbAllocDeviceInfo_PROC = (PFN_XkbAllocDeviceInfo_PROC) dlsym(handle, "XkbAllocDeviceInfo");
    XkbAllocIndicatorMaps_PROC = (PFN_XkbAllocIndicatorMaps_PROC) dlsym(handle, "XkbAllocIndicatorMaps");
    XkbAllocKeyboard_PROC = (PFN_XkbAllocKeyboard_PROC) dlsym(handle, "XkbAllocKeyboard");
    XkbAllocNames_PROC = (PFN_XkbAllocNames_PROC) dlsym(handle, "XkbAllocNames");
    XkbAllocServerMap_PROC = (PFN_XkbAllocServerMap_PROC) dlsym(handle, "XkbAllocServerMap");
    XkbApplyCompatMapToKey_PROC = (PFN_XkbApplyCompatMapToKey_PROC) dlsym(handle, "XkbApplyCompatMapToKey");
    XkbApplyVirtualModChanges_PROC = (PFN_XkbApplyVirtualModChanges_PROC) dlsym(handle, "XkbApplyVirtualModChanges");
    XkbBell_PROC = (PFN_XkbBell_PROC) dlsym(handle, "XkbBell");
    XkbBellEvent_PROC = (PFN_XkbBellEvent_PROC) dlsym(handle, "XkbBellEvent");
    XkbChangeDeviceInfo_PROC = (PFN_XkbChangeDeviceInfo_PROC) dlsym(handle, "XkbChangeDeviceInfo");
    XkbChangeEnabledControls_PROC = (PFN_XkbChangeEnabledControls_PROC) dlsym(handle, "XkbChangeEnabledControls");
    XkbChangeKeycodeRange_PROC = (PFN_XkbChangeKeycodeRange_PROC) dlsym(handle, "XkbChangeKeycodeRange");
    XkbChangeMap_PROC = (PFN_XkbChangeMap_PROC) dlsym(handle, "XkbChangeMap");
    XkbChangeNames_PROC = (PFN_XkbChangeNames_PROC) dlsym(handle, "XkbChangeNames");
    XkbChangeTypesOfKey_PROC = (PFN_XkbChangeTypesOfKey_PROC) dlsym(handle, "XkbChangeTypesOfKey");
    XkbComputeEffectiveMap_PROC = (PFN_XkbComputeEffectiveMap_PROC) dlsym(handle, "XkbComputeEffectiveMap");
    XkbCopyKeyType_PROC = (PFN_XkbCopyKeyType_PROC) dlsym(handle, "XkbCopyKeyType");
    XkbCopyKeyTypes_PROC = (PFN_XkbCopyKeyTypes_PROC) dlsym(handle, "XkbCopyKeyTypes");
    XkbDeviceBell_PROC = (PFN_XkbDeviceBell_PROC) dlsym(handle, "XkbDeviceBell");
    XkbDeviceBellEvent_PROC = (PFN_XkbDeviceBellEvent_PROC) dlsym(handle, "XkbDeviceBellEvent");
    XkbForceBell_PROC = (PFN_XkbForceBell_PROC) dlsym(handle, "XkbForceBell");
    XkbForceDeviceBell_PROC = (PFN_XkbForceDeviceBell_PROC) dlsym(handle, "XkbForceDeviceBell");
    XkbFreeClientMap_PROC = (PFN_XkbFreeClientMap_PROC) dlsym(handle, "XkbFreeClientMap");
    XkbFreeCompatMap_PROC = (PFN_XkbFreeCompatMap_PROC) dlsym(handle, "XkbFreeCompatMap");
    XkbFreeComponentList_PROC = (PFN_XkbFreeComponentList_PROC) dlsym(handle, "XkbFreeComponentList");
    XkbFreeControls_PROC = (PFN_XkbFreeControls_PROC) dlsym(handle, "XkbFreeControls");
    XkbFreeDeviceInfo_PROC = (PFN_XkbFreeDeviceInfo_PROC) dlsym(handle, "XkbFreeDeviceInfo");
    XkbFreeIndicatorMaps_PROC = (PFN_XkbFreeIndicatorMaps_PROC) dlsym(handle, "XkbFreeIndicatorMaps");
    XkbFreeKeyboard_PROC = (PFN_XkbFreeKeyboard_PROC) dlsym(handle, "XkbFreeKeyboard");
    XkbFreeNames_PROC = (PFN_XkbFreeNames_PROC) dlsym(handle, "XkbFreeNames");
    XkbFreeServerMap_PROC = (PFN_XkbFreeServerMap_PROC) dlsym(handle, "XkbFreeServerMap");
    XkbGetAutoRepeatRate_PROC = (PFN_XkbGetAutoRepeatRate_PROC) dlsym(handle, "XkbGetAutoRepeatRate");
    XkbGetAutoResetControls_PROC = (PFN_XkbGetAutoResetControls_PROC) dlsym(handle, "XkbGetAutoResetControls");
    XkbGetCompatMap_PROC = (PFN_XkbGetCompatMap_PROC) dlsym(handle, "XkbGetCompatMap");
    XkbGetControls_PROC = (PFN_XkbGetControls_PROC) dlsym(handle, "XkbGetControls");
    XkbGetDetectableAutoRepeat_PROC = (PFN_XkbGetDetectableAutoRepeat_PROC) dlsym(handle, "XkbGetDetectableAutoRepeat");
    XkbGetDeviceButtonActions_PROC = (PFN_XkbGetDeviceButtonActions_PROC) dlsym(handle, "XkbGetDeviceButtonActions");
    XkbGetDeviceInfo_PROC = (PFN_XkbGetDeviceInfo_PROC) dlsym(handle, "XkbGetDeviceInfo");
    XkbGetDeviceInfoChanges_PROC = (PFN_XkbGetDeviceInfoChanges_PROC) dlsym(handle, "XkbGetDeviceInfoChanges");
    XkbGetDeviceLedInfo_PROC = (PFN_XkbGetDeviceLedInfo_PROC) dlsym(handle, "XkbGetDeviceLedInfo");
    XkbGetIndicatorMap_PROC = (PFN_XkbGetIndicatorMap_PROC) dlsym(handle, "XkbGetIndicatorMap");
    XkbGetIndicatorState_PROC = (PFN_XkbGetIndicatorState_PROC) dlsym(handle, "XkbGetIndicatorState");
    XkbGetKeyActions_PROC = (PFN_XkbGetKeyActions_PROC) dlsym(handle, "XkbGetKeyActions");
    XkbGetKeyBehaviors_PROC = (PFN_XkbGetKeyBehaviors_PROC) dlsym(handle, "XkbGetKeyBehaviors");
    XkbGetKeyExplicitComponents_PROC = (PFN_XkbGetKeyExplicitComponents_PROC) dlsym(handle, "XkbGetKeyExplicitComponents");
    XkbGetKeyModifierMap_PROC = (PFN_XkbGetKeyModifierMap_PROC) dlsym(handle, "XkbGetKeyModifierMap");
    XkbGetKeySyms_PROC = (PFN_XkbGetKeySyms_PROC) dlsym(handle, "XkbGetKeySyms");
    XkbGetKeyTypes_PROC = (PFN_XkbGetKeyTypes_PROC) dlsym(handle, "XkbGetKeyTypes");
    XkbGetKeyVirtualModMap_PROC = (PFN_XkbGetKeyVirtualModMap_PROC) dlsym(handle, "XkbGetKeyVirtualModMap");
    XkbGetKeyboard_PROC = (PFN_XkbGetKeyboard_PROC) dlsym(handle, "XkbGetKeyboard");
    XkbGetKeyboardByName_PROC = (PFN_XkbGetKeyboardByName_PROC) dlsym(handle, "XkbGetKeyboardByName");
    XkbGetMap_PROC = (PFN_XkbGetMap_PROC) dlsym(handle, "XkbGetMap");
    XkbGetMapChanges_PROC = (PFN_XkbGetMapChanges_PROC) dlsym(handle, "XkbGetMapChanges");
    XkbGetNamedDeviceIndicator_PROC = (PFN_XkbGetNamedDeviceIndicator_PROC) dlsym(handle, "XkbGetNamedDeviceIndicator");
    XkbGetNamedIndicator_PROC = (PFN_XkbGetNamedIndicator_PROC) dlsym(handle, "XkbGetNamedIndicator");
    XkbGetNames_PROC = (PFN_XkbGetNames_PROC) dlsym(handle, "XkbGetNames");
    XkbGetPerClientControls_PROC = (PFN_XkbGetPerClientControls_PROC) dlsym(handle, "XkbGetPerClientControls");
    XkbGetState_PROC = (PFN_XkbGetState_PROC) dlsym(handle, "XkbGetState");
    XkbGetUpdatedMap_PROC = (PFN_XkbGetUpdatedMap_PROC) dlsym(handle, "XkbGetUpdatedMap");
    XkbGetVirtualMods_PROC = (PFN_XkbGetVirtualMods_PROC) dlsym(handle, "XkbGetVirtualMods");
    XkbGetXlibControls_PROC = (PFN_XkbGetXlibControls_PROC) dlsym(handle, "XkbGetXlibControls");
    XkbIgnoreExtension_PROC = (PFN_XkbIgnoreExtension_PROC) dlsym(handle, "XkbIgnoreExtension");
    XkbInitCanonicalKeyTypes_PROC = (PFN_XkbInitCanonicalKeyTypes_PROC) dlsym(handle, "XkbInitCanonicalKeyTypes");
    XkbKeyTypesForCoreSymbols_PROC = (PFN_XkbKeyTypesForCoreSymbols_PROC) dlsym(handle, "XkbKeyTypesForCoreSymbols");
    XkbKeycodeToKeysym_PROC = (PFN_XkbKeycodeToKeysym_PROC) dlsym(handle, "XkbKeycodeToKeysym");
    XkbKeysymToModifiers_PROC = (PFN_XkbKeysymToModifiers_PROC) dlsym(handle, "XkbKeysymToModifiers");
    XkbLatchGroup_PROC = (PFN_XkbLatchGroup_PROC) dlsym(handle, "XkbLatchGroup");
    XkbLatchModifiers_PROC = (PFN_XkbLatchModifiers_PROC) dlsym(handle, "XkbLatchModifiers");
    XkbLibraryVersion_PROC = (PFN_XkbLibraryVersion_PROC) dlsym(handle, "XkbLibraryVersion");
    XkbListComponents_PROC = (PFN_XkbListComponents_PROC) dlsym(handle, "XkbListComponents");
    XkbLockGroup_PROC = (PFN_XkbLockGroup_PROC) dlsym(handle, "XkbLockGroup");
    XkbLockModifiers_PROC = (PFN_XkbLockModifiers_PROC) dlsym(handle, "XkbLockModifiers");
    XkbLookupKeyBinding_PROC = (PFN_XkbLookupKeyBinding_PROC) dlsym(handle, "XkbLookupKeyBinding");
    XkbLookupKeySym_PROC = (PFN_XkbLookupKeySym_PROC) dlsym(handle, "XkbLookupKeySym");
    XkbNoteControlsChanges_PROC = (PFN_XkbNoteControlsChanges_PROC) dlsym(handle, "XkbNoteControlsChanges");
    XkbNoteDeviceChanges_PROC = (PFN_XkbNoteDeviceChanges_PROC) dlsym(handle, "XkbNoteDeviceChanges");
    XkbNoteMapChanges_PROC = (PFN_XkbNoteMapChanges_PROC) dlsym(handle, "XkbNoteMapChanges");
    XkbNoteNameChanges_PROC = (PFN_XkbNoteNameChanges_PROC) dlsym(handle, "XkbNoteNameChanges");
    XkbOpenDisplay_PROC = (PFN_XkbOpenDisplay_PROC) dlsym(handle, "XkbOpenDisplay");
    XkbQueryExtension_PROC = (PFN_XkbQueryExtension_PROC) dlsym(handle, "XkbQueryExtension");
    XkbRefreshKeyboardMapping_PROC = (PFN_XkbRefreshKeyboardMapping_PROC) dlsym(handle, "XkbRefreshKeyboardMapping");
    XkbResizeDeviceButtonActions_PROC = (PFN_XkbResizeDeviceButtonActions_PROC) dlsym(handle, "XkbResizeDeviceButtonActions");
    XkbResizeKeyActions_PROC = (PFN_XkbResizeKeyActions_PROC) dlsym(handle, "XkbResizeKeyActions");
    XkbResizeKeySyms_PROC = (PFN_XkbResizeKeySyms_PROC) dlsym(handle, "XkbResizeKeySyms");
    XkbResizeKeyType_PROC = (PFN_XkbResizeKeyType_PROC) dlsym(handle, "XkbResizeKeyType");
    XkbSelectEventDetails_PROC = (PFN_XkbSelectEventDetails_PROC) dlsym(handle, "XkbSelectEventDetails");
    XkbSelectEvents_PROC = (PFN_XkbSelectEvents_PROC) dlsym(handle, "XkbSelectEvents");
    XkbSetAtomFuncs_PROC = (PFN_XkbSetAtomFuncs_PROC) dlsym(handle, "XkbSetAtomFuncs");
    XkbSetAutoRepeatRate_PROC = (PFN_XkbSetAutoRepeatRate_PROC) dlsym(handle, "XkbSetAutoRepeatRate");
    XkbSetAutoResetControls_PROC = (PFN_XkbSetAutoResetControls_PROC) dlsym(handle, "XkbSetAutoResetControls");
    XkbSetCompatMap_PROC = (PFN_XkbSetCompatMap_PROC) dlsym(handle, "XkbSetCompatMap");
    XkbSetControls_PROC = (PFN_XkbSetControls_PROC) dlsym(handle, "XkbSetControls");
    XkbSetDebuggingFlags_PROC = (PFN_XkbSetDebuggingFlags_PROC) dlsym(handle, "XkbSetDebuggingFlags");
    XkbSetDetectableAutoRepeat_PROC = (PFN_XkbSetDetectableAutoRepeat_PROC) dlsym(handle, "XkbSetDetectableAutoRepeat");
    XkbSetDeviceButtonActions_PROC = (PFN_XkbSetDeviceButtonActions_PROC) dlsym(handle, "XkbSetDeviceButtonActions");
    XkbSetDeviceInfo_PROC = (PFN_XkbSetDeviceInfo_PROC) dlsym(handle, "XkbSetDeviceInfo");
    XkbSetDeviceLedInfo_PROC = (PFN_XkbSetDeviceLedInfo_PROC) dlsym(handle, "XkbSetDeviceLedInfo");
    XkbSetIgnoreLockMods_PROC = (PFN_XkbSetIgnoreLockMods_PROC) dlsym(handle, "XkbSetIgnoreLockMods");
    XkbSetIndicatorMap_PROC = (PFN_XkbSetIndicatorMap_PROC) dlsym(handle, "XkbSetIndicatorMap");
    XkbSetMap_PROC = (PFN_XkbSetMap_PROC) dlsym(handle, "XkbSetMap");
    XkbSetNamedDeviceIndicator_PROC = (PFN_XkbSetNamedDeviceIndicator_PROC) dlsym(handle, "XkbSetNamedDeviceIndicator");
    XkbSetNamedIndicator_PROC = (PFN_XkbSetNamedIndicator_PROC) dlsym(handle, "XkbSetNamedIndicator");
    XkbSetNames_PROC = (PFN_XkbSetNames_PROC) dlsym(handle, "XkbSetNames");
    XkbSetPerClientControls_PROC = (PFN_XkbSetPerClientControls_PROC) dlsym(handle, "XkbSetPerClientControls");
    XkbSetServerInternalMods_PROC = (PFN_XkbSetServerInternalMods_PROC) dlsym(handle, "XkbSetServerInternalMods");
    XkbSetXlibControls_PROC = (PFN_XkbSetXlibControls_PROC) dlsym(handle, "XkbSetXlibControls");
    XkbToControl_PROC = (PFN_XkbToControl_PROC) dlsym(handle, "XkbToControl");
    XkbTranslateKeyCode_PROC = (PFN_XkbTranslateKeyCode_PROC) dlsym(handle, "XkbTranslateKeyCode");
    XkbTranslateKeySym_PROC = (PFN_XkbTranslateKeySym_PROC) dlsym(handle, "XkbTranslateKeySym");
    XkbUpdateActionVirtualMods_PROC = (PFN_XkbUpdateActionVirtualMods_PROC) dlsym(handle, "XkbUpdateActionVirtualMods");
    XkbUpdateKeyTypeVirtualMods_PROC = (PFN_XkbUpdateKeyTypeVirtualMods_PROC) dlsym(handle, "XkbUpdateKeyTypeVirtualMods");
    XkbUpdateMapFromCore_PROC = (PFN_XkbUpdateMapFromCore_PROC) dlsym(handle, "XkbUpdateMapFromCore");
    XkbUseExtension_PROC = (PFN_XkbUseExtension_PROC) dlsym(handle, "XkbUseExtension");
    XkbVirtualModsToReal_PROC = (PFN_XkbVirtualModsToReal_PROC) dlsym(handle, "XkbVirtualModsToReal");
    XkbXlibControlsImplemented_PROC = (PFN_XkbXlibControlsImplemented_PROC) dlsym(handle, "XkbXlibControlsImplemented");

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
#  /* WINDOW_BACKEND_WAYLAND - Wayland implementation */
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
#  /* WINDOW_PLATFORM_WIN32 - Win32 implementation */
#  if defined (WINDOW_PLATFORM_WIN32)
#   include <windows.h>

/* ... */

#  endif /* WINDOW_PLATFORM_WIN32 */
#
#  /* WINDOW_BACKEND_GL_EGL - EGL implementation layer */
#  if defined (WINDOW_BACKEND_GL_EGL)

/* libEGL: egl.h */

typedef Display *EGLNativeDisplayType;
typedef Pixmap   EGLNativePixmapType;
typedef Window   EGLNativeWindowType;

typedef EGLNativeDisplayType NativeDisplayType;
typedef EGLNativePixmapType  NativePixmapType;
typedef EGLNativeWindowType  NativeWindowType;

typedef void *EGLDisplay;
typedef void *EGLConfig;
typedef void *EGLSurface;
typedef void *EGLContext;
typedef void *EGLClientBuffer;
typedef void *EGLSync;
typedef void *EGLImage;

typedef int32_t EGLint;
typedef unsigned int EGLBoolean;
typedef unsigned int EGLenum;
typedef intptr_t EGLAttrib;

typedef void (*__eglMustCastToProperFunctionPointerType)(void);

typedef uint64_t EGLTime;

#   define EGL_ALPHA_SIZE 0x3021
#   define EGL_BAD_ACCESS 0x3002
#   define EGL_BAD_ALLOC 0x3003
#   define EGL_BAD_ATTRIBUTE 0x3004
#   define EGL_BAD_CONFIG 0x3005
#   define EGL_BAD_CONTEXT 0x3006
#   define EGL_BAD_CURRENT_SURFACE 0x3007
#   define EGL_BAD_DISPLAY 0x3008
#   define EGL_BAD_MATCH 0x3009
#   define EGL_BAD_NATIVE_PIXMAP 0x300A
#   define EGL_BAD_NATIVE_WINDOW 0x300B
#   define EGL_BAD_PARAMETER 0x300C
#   define EGL_BAD_SURFACE 0x300D
#   define EGL_BLUE_SIZE 0x3022
#   define EGL_BUFFER_SIZE 0x3020
#   define EGL_CONFIG_CAVEAT 0x3027
#   define EGL_CONFIG_ID 0x3028
#   define EGL_CORE_NATIVE_ENGINE 0x305B
#   define EGL_DEPTH_SIZE 0x3025
#   define EGL_DONT_CARE ((EGLint) -1)
#   define EGL_DRAW 0x3059
#   define EGL_EXTENSIONS 0x3055
#   define EGL_FALSE 0
#   define EGL_GREEN_SIZE 0x3023
#   define EGL_HEIGHT 0x3056
#   define EGL_LARGEST_PBUFFER 0x3058
#   define EGL_LEVEL 0x3029
#   define EGL_MAX_PBUFFER_HEIGHT 0x302A
#   define EGL_MAX_PBUFFER_PIXELS 0x302B
#   define EGL_MAX_PBUFFER_WIDTH 0x302C
#   define EGL_NATIVE_RENDERABLE 0x302D
#   define EGL_NATIVE_VISUAL_ID 0x302E
#   define EGL_NATIVE_VISUAL_TYPE 0x302F
#   define EGL_NONE 0x3038
#   define EGL_NON_CONFORMANT_CONFIG 0x3051
#   define EGL_NOT_INITIALIZED 0x3001
#   define EGL_NO_CONTEXT ((EGLContext) 0)
#   define EGL_NO_DISPLAY ((EGLDisplay) 0)
#   define EGL_NO_SURFACE ((EGLSurface) 0)
#   define EGL_PBUFFER_BIT 0x0001
#   define EGL_PIXMAP_BIT 0x0002
#   define EGL_READ 0x305A
#   define EGL_RED_SIZE 0x3024
#   define EGL_SAMPLES 0x3031
#   define EGL_SAMPLE_BUFFERS 0x3032
#   define EGL_SLOW_CONFIG 0x3050
#   define EGL_STENCIL_SIZE 0x3026
#   define EGL_SUCCESS 0x3000
#   define EGL_SURFACE_TYPE 0x3033
#   define EGL_TRANSPARENT_BLUE_VALUE 0x3035
#   define EGL_TRANSPARENT_GREEN_VALUE 0x3036
#   define EGL_TRANSPARENT_RED_VALUE 0x3037
#   define EGL_TRANSPARENT_RGB 0x3052
#   define EGL_TRANSPARENT_TYPE 0x3034
#   define EGL_TRUE 1
#   define EGL_VENDOR 0x3053
#   define EGL_VERSION 0x3054
#   define EGL_WIDTH 0x3057
#   define EGL_WINDOW_BIT 0x0004
#   define EGL_BACK_BUFFER 0x3084
#   define EGL_BIND_TO_TEXTURE_RGB 0x3039
#   define EGL_BIND_TO_TEXTURE_RGBA 0x303A
#   define EGL_CONTEXT_LOST 0x300E
#   define EGL_MIN_SWAP_INTERVAL 0x303B
#   define EGL_MAX_SWAP_INTERVAL 0x303C
#   define EGL_MIPMAP_TEXTURE 0x3082
#   define EGL_MIPMAP_LEVEL 0x3083
#   define EGL_NO_TEXTURE 0x305C
#   define EGL_TEXTURE_2D 0x305F
#   define EGL_TEXTURE_FORMAT 0x3080
#   define EGL_TEXTURE_RGB 0x305D
#   define EGL_TEXTURE_RGBA 0x305E
#   define EGL_TEXTURE_TARGET 0x3081
#   define EGL_ALPHA_FORMAT 0x3088
#   define EGL_ALPHA_FORMAT_NONPRE 0x308B
#   define EGL_ALPHA_FORMAT_PRE 0x308C
#   define EGL_ALPHA_MASK_SIZE 0x303E
#   define EGL_BUFFER_PRESERVED 0x3094
#   define EGL_BUFFER_DESTROYED 0x3095
#   define EGL_CLIENT_APIS 0x308D
#   define EGL_COLORSPACE 0x3087
#   define EGL_COLORSPACE_sRGB 0x3089
#   define EGL_COLORSPACE_LINEAR 0x308A
#   define EGL_COLOR_BUFFER_TYPE 0x303F
#   define EGL_CONTEXT_CLIENT_TYPE 0x3097
#   define EGL_DISPLAY_SCALING 10000
#   define EGL_HORIZONTAL_RESOLUTION 0x3090
#   define EGL_LUMINANCE_BUFFER 0x308F
#   define EGL_LUMINANCE_SIZE 0x303D
#   define EGL_OPENGL_ES_BIT 0x0001
#   define EGL_OPENVG_BIT 0x0002
#   define EGL_OPENGL_ES_API 0x30A0
#   define EGL_OPENVG_API 0x30A1
#   define EGL_OPENVG_IMAGE 0x3096
#   define EGL_PIXEL_ASPECT_RATIO 0x3092
#   define EGL_RENDERABLE_TYPE 0x3040
#   define EGL_RENDER_BUFFER 0x3086
#   define EGL_RGB_BUFFER 0x308E
#   define EGL_SINGLE_BUFFER 0x3085
#   define EGL_SWAP_BEHAVIOR 0x3093
#   define EGL_UNKNOWN ((EGLint) -1)
#   define EGL_VERTICAL_RESOLUTION 0x3091
#   define EGL_CONFORMANT 0x3042
#   define EGL_CONTEXT_CLIENT_VERSION 0x3098
#   define EGL_MATCH_NATIVE_PIXMAP 0x3041
#   define EGL_OPENGL_ES2_BIT 0x0004
#   define EGL_VG_ALPHA_FORMAT 0x3088
#   define EGL_VG_ALPHA_FORMAT_NONPRE 0x308B
#   define EGL_VG_ALPHA_FORMAT_PRE 0x308C
#   define EGL_VG_ALPHA_FORMAT_PRE_BIT 0x0040
#   define EGL_VG_COLORSPACE 0x3087
#   define EGL_VG_COLORSPACE_sRGB 0x3089
#   define EGL_VG_COLORSPACE_LINEAR 0x308A
#   define EGL_VG_COLORSPACE_LINEAR_BIT 0x0020
#   define EGL_DEFAULT_DISPLAY ((EGLNativeDisplayType) 0)
#   define EGL_MULTISAMPLE_RESOLVE_BOX_BIT 0x0200
#   define EGL_MULTISAMPLE_RESOLVE 0x3099
#   define EGL_MULTISAMPLE_RESOLVE_DEFAULT 0x309A
#   define EGL_MULTISAMPLE_RESOLVE_BOX 0x309B
#   define EGL_OPENGL_API 0x30A2
#   define EGL_OPENGL_BIT 0x0008
#   define EGL_SWAP_BEHAVIOR_PRESERVED_BIT 0x0400
#   define EGL_CONTEXT_MAJOR_VERSION 0x3098
#   define EGL_CONTEXT_MINOR_VERSION 0x30FB
#   define EGL_CONTEXT_OPENGL_PROFILE_MASK 0x30FD
#   define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#   define EGL_NO_RESET_NOTIFICATION 0x31BE
#   define EGL_LOSE_CONTEXT_ON_RESET 0x31BF
#   define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#   define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#   define EGL_CONTEXT_OPENGL_DEBUG 0x31B0
#   define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#   define EGL_CONTEXT_OPENGL_ROBUST_ACCESS 0x31B2
#   define EGL_OPENGL_ES3_BIT 0x00000040
#   define EGL_CL_EVENT_HANDLE 0x309C
#   define EGL_SYNC_CL_EVENT 0x30FE
#   define EGL_SYNC_CL_EVENT_COMPLETE 0x30FF
#   define EGL_SYNC_PRIOR_COMMANDS_COMPLETE 0x30F0
#   define EGL_SYNC_TYPE 0x30F7
#   define EGL_SYNC_STATUS 0x30F1
#   define EGL_SYNC_CONDITION 0x30F8
#   define EGL_SIGNALED 0x30F2
#   define EGL_UNSIGNALED 0x30F3
#   define EGL_SYNC_FLUSH_COMMANDS_BIT 0x0001
#   define EGL_FOREVER 0xFFFFFFFFFFFFFFFFull
#   define EGL_TIMEOUT_EXPIRED 0x30F5
#   define EGL_CONDITION_SATISFIED 0x30F6
#   define EGL_NO_SYNC ((EGLSync) 0)
#   define EGL_SYNC_FENCE 0x30F9
#   define EGL_GL_COLORSPACE 0x309D
#   define EGL_GL_COLORSPACE_SRGB 0x3089
#   define EGL_GL_COLORSPACE_LINEAR 0x308A
#   define EGL_GL_RENDERBUFFER 0x30B9
#   define EGL_GL_TEXTURE_2D 0x30B1
#   define EGL_GL_TEXTURE_LEVEL 0x30BC
#   define EGL_GL_TEXTURE_3D 0x30B2
#   define EGL_GL_TEXTURE_ZOFFSET 0x30BD
#   define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x30B3
#   define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#   define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x30B5
#   define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#   define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x30B7
#   define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#   define EGL_IMAGE_PRESERVED 0x30D2
#   define EGL_NO_IMAGE ((EGLImage) 0)

typedef EGLBoolean (* PFN_eglBindAPI_PROC) (EGLenum);
PFN_eglBindAPI_PROC eglBindAPI_PROC = 0;
#   define eglBindAPI (assert(eglBindAPI_PROC != 0), eglBindAPI_PROC)

typedef EGLBoolean (* PFN_eglBindTexImage_PROC) (EGLDisplay, EGLSurface, EGLint);
PFN_eglBindTexImage_PROC eglBindTexImage_PROC = 0;
#   define eglBindTexImage (assert(eglBindTexImage_PROC != 0), eglBindTexImage_PROC)

typedef EGLBoolean (* PFN_eglChooseConfig_PROC) (EGLDisplay, const EGLint *, EGLConfig *, EGLint, EGLint *);
PFN_eglChooseConfig_PROC eglChooseConfig_PROC = 0;
#   define eglChooseConfig (assert(eglChooseConfig_PROC != 0), eglChooseConfig_PROC)

typedef EGLint (* PFN_eglClientWaitSync_PROC) (EGLDisplay, EGLSync, EGLint, EGLTime);
PFN_eglClientWaitSync_PROC eglClientWaitSync_PROC = 0;
#   define eglClientWaitSync (assert(eglClientWaitSync_PROC != 0), eglClientWaitSync_PROC)

typedef EGLBoolean (* PFN_eglCopyBuffers_PROC) (EGLDisplay, EGLSurface, EGLNativePixmapType);
PFN_eglCopyBuffers_PROC eglCopyBuffers_PROC = 0;
#   define eglCopyBuffers (assert(eglCopyBuffers_PROC != 0), eglCopyBuffers_PROC)

typedef EGLContext (* PFN_eglCreateContext_PROC) (EGLDisplay, EGLConfig, EGLContext, const EGLint *);
PFN_eglCreateContext_PROC eglCreateContext_PROC = 0;
#   define eglCreateContext (assert(eglCreateContext_PROC != 0), eglCreateContext_PROC)

typedef EGLImage (* PFN_eglCreateImage_PROC) (EGLDisplay, EGLContext, EGLenum, EGLClientBuffer, const EGLAttrib *);
PFN_eglCreateImage_PROC eglCreateImage_PROC = 0;
#   define eglCreateImage (assert(eglCreateImage_PROC != 0), eglCreateImage_PROC)

typedef EGLSurface (* PFN_eglCreatePbufferFromClientBuffer_PROC) (EGLDisplay, EGLenum, EGLClientBuffer, EGLConfig, const EGLint *);
PFN_eglCreatePbufferFromClientBuffer_PROC eglCreatePbufferFromClientBuffer_PROC = 0;
#   define eglCreatePbufferFromClientBuffer (assert(eglCreatePbufferFromClientBuffer_PROC != 0), eglCreatePbufferFromClientBuffer_PROC)

typedef EGLSurface (* PFN_eglCreatePbufferSurface_PROC) (EGLDisplay, EGLConfig, const EGLint *);
PFN_eglCreatePbufferSurface_PROC eglCreatePbufferSurface_PROC = 0;
#   define eglCreatePbufferSurface (assert(eglCreatePbufferSurface_PROC != 0), eglCreatePbufferSurface_PROC)

typedef EGLSurface (* PFN_eglCreatePixmapSurface_PROC) (EGLDisplay, EGLConfig, EGLNativePixmapType, const EGLint *);
PFN_eglCreatePixmapSurface_PROC eglCreatePixmapSurface_PROC = 0;
#   define eglCreatePixmapSurface (assert(eglCreatePixmapSurface_PROC != 0), eglCreatePixmapSurface_PROC)

typedef EGLSurface (* PFN_eglCreatePlatformPixmapSurface_PROC) (EGLDisplay, EGLConfig, void *, const EGLAttrib *);
PFN_eglCreatePlatformPixmapSurface_PROC eglCreatePlatformPixmapSurface_PROC = 0;
#   define eglCreatePlatformPixmapSurface (assert(eglCreatePlatformPixmapSurface_PROC != 0), eglCreatePlatformPixmapSurface_PROC)

typedef EGLSurface (* PFN_eglCreatePlatformWindowSurface_PROC) (EGLDisplay, EGLConfig, void *, const EGLAttrib *);
PFN_eglCreatePlatformWindowSurface_PROC eglCreatePlatformWindowSurface_PROC = 0;
#   define eglCreatePlatformWindowSurface (assert(eglCreatePlatformWindowSurface_PROC != 0), eglCreatePlatformWindowSurface_PROC)

typedef EGLSync (* PFN_eglCreateSync_PROC) (EGLDisplay, EGLenum, const EGLAttrib *);
PFN_eglCreateSync_PROC eglCreateSync_PROC = 0;
#   define eglCreateSync (assert(eglCreateSync_PROC != 0), eglCreateSync_PROC)

typedef EGLSurface (* PFN_eglCreateWindowSurface_PROC) (EGLDisplay, EGLConfig, EGLNativeWindowType, const EGLint *);
PFN_eglCreateWindowSurface_PROC eglCreateWindowSurface_PROC = 0;
#   define eglCreateWindowSurface (assert(eglCreateWindowSurface_PROC != 0), eglCreateWindowSurface_PROC)

typedef EGLBoolean (* PFN_eglDestroyContext_PROC) (EGLDisplay, EGLContext);
PFN_eglDestroyContext_PROC eglDestroyContext_PROC = 0;
#   define eglDestroyContext (assert(eglDestroyContext_PROC != 0), eglDestroyContext_PROC)

typedef EGLBoolean (* PFN_eglDestroyImage_PROC) (EGLDisplay, EGLImage);
PFN_eglDestroyImage_PROC eglDestroyImage_PROC = 0;
#   define eglDestroyImage (assert(eglDestroyImage_PROC != 0), eglDestroyImage_PROC)

typedef EGLBoolean (* PFN_eglDestroySurface_PROC) (EGLDisplay, EGLSurface);
PFN_eglDestroySurface_PROC eglDestroySurface_PROC = 0;
#   define eglDestroySurface (assert(eglDestroySurface_PROC != 0), eglDestroySurface_PROC)

typedef EGLBoolean (* PFN_eglDestroySync_PROC) (EGLDisplay, EGLSync);
PFN_eglDestroySync_PROC eglDestroySync_PROC = 0;
#   define eglDestroySync (assert(eglDestroySync_PROC != 0), eglDestroySync_PROC)

typedef EGLBoolean (* PFN_eglGetConfigAttrib_PROC) (EGLDisplay, EGLConfig, EGLint, EGLint *);
PFN_eglGetConfigAttrib_PROC eglGetConfigAttrib_PROC = 0;
#   define eglGetConfigAttrib (assert(eglGetConfigAttrib_PROC != 0), eglGetConfigAttrib_PROC)

typedef EGLBoolean (* PFN_eglGetConfigs_PROC) (EGLDisplay, EGLConfig *, EGLint, EGLint *);
PFN_eglGetConfigs_PROC eglGetConfigs_PROC = 0;
#   define eglGetConfigs (assert(eglGetConfigs_PROC != 0), eglGetConfigs_PROC)

typedef EGLContext (* PFN_eglGetCurrentContext_PROC) (void);
PFN_eglGetCurrentContext_PROC eglGetCurrentContext_PROC = 0;
#   define eglGetCurrentContext (assert(eglGetCurrentContext_PROC != 0), eglGetCurrentContext_PROC)

typedef EGLDisplay (* PFN_eglGetCurrentDisplay_PROC) (void);
PFN_eglGetCurrentDisplay_PROC eglGetCurrentDisplay_PROC = 0;
#   define eglGetCurrentDisplay (assert(eglGetCurrentDisplay_PROC != 0), eglGetCurrentDisplay_PROC)

typedef EGLSurface (* PFN_eglGetCurrentSurface_PROC) (EGLint);
PFN_eglGetCurrentSurface_PROC eglGetCurrentSurface_PROC = 0;
#   define eglGetCurrentSurface (assert(eglGetCurrentSurface_PROC != 0), eglGetCurrentSurface_PROC)

typedef EGLDisplay (* PFN_eglGetDisplay_PROC) (EGLNativeDisplayType);
PFN_eglGetDisplay_PROC eglGetDisplay_PROC = 0;
#   define eglGetDisplay (assert(eglGetDisplay_PROC != 0), eglGetDisplay_PROC)

typedef EGLint (* PFN_eglGetError_PROC) (void);
PFN_eglGetError_PROC eglGetError_PROC = 0;
#   define eglGetError (assert(eglGetError_PROC != 0), eglGetError_PROC)

typedef EGLDisplay (* PFN_eglGetPlatformDisplay_PROC) (EGLenum, void *, const EGLAttrib *);
PFN_eglGetPlatformDisplay_PROC eglGetPlatformDisplay_PROC = 0;
#   define eglGetPlatformDisplay (assert(eglGetPlatformDisplay_PROC != 0), eglGetPlatformDisplay_PROC)

typedef __eglMustCastToProperFunctionPointerType (* PFN_eglGetProcAddress_PROC) (const char *);
PFN_eglGetProcAddress_PROC eglGetProcAddress_PROC = 0;
#   define eglGetProcAddress (assert(eglGetProcAddress_PROC != 0), eglGetProcAddress_PROC)

typedef EGLBoolean (* PFN_eglGetSyncAttrib_PROC) (EGLDisplay, EGLSync, EGLint, EGLAttrib *);
PFN_eglGetSyncAttrib_PROC eglGetSyncAttrib_PROC = 0;
#   define eglGetSyncAttrib (assert(eglGetSyncAttrib_PROC != 0), eglGetSyncAttrib_PROC)

typedef EGLBoolean (* PFN_eglInitialize_PROC) (EGLDisplay, EGLint *, EGLint *);
PFN_eglInitialize_PROC eglInitialize_PROC = 0;
#   define eglInitialize (assert(eglInitialize_PROC != 0), eglInitialize_PROC)

typedef EGLBoolean (* PFN_eglMakeCurrent_PROC) (EGLDisplay, EGLSurface, EGLSurface, EGLContext);
PFN_eglMakeCurrent_PROC eglMakeCurrent_PROC = 0;
#   define eglMakeCurrent (assert(eglMakeCurrent_PROC != 0), eglMakeCurrent_PROC)

typedef EGLenum (* PFN_eglQueryAPI_PROC) (void);
PFN_eglQueryAPI_PROC eglQueryAPI_PROC = 0;
#   define eglQueryAPI (assert(eglQueryAPI_PROC != 0), eglQueryAPI_PROC)

typedef EGLBoolean (* PFN_eglQueryContext_PROC) (EGLDisplay, EGLContext, EGLint, EGLint *);
PFN_eglQueryContext_PROC eglQueryContext_PROC = 0;
#   define eglQueryContext (assert(eglQueryContext_PROC != 0), eglQueryContext_PROC)

typedef const char *(* PFN_eglQueryString_PROC) (EGLDisplay, EGLint);
PFN_eglQueryString_PROC eglQueryString_PROC = 0;
#   define eglQueryString (assert(eglQueryString_PROC != 0), eglQueryString_PROC)

typedef EGLBoolean (* PFN_eglQuerySurface_PROC) (EGLDisplay, EGLSurface, EGLint, EGLint *);
PFN_eglQuerySurface_PROC eglQuerySurface_PROC = 0;
#   define eglQuerySurface (assert(eglQuerySurface_PROC != 0), eglQuerySurface_PROC)

typedef EGLBoolean (* PFN_eglReleaseTexImage_PROC) (EGLDisplay, EGLSurface, EGLint);
PFN_eglReleaseTexImage_PROC eglReleaseTexImage_PROC = 0;
#   define eglReleaseTexImage (assert(eglReleaseTexImage_PROC != 0), eglReleaseTexImage_PROC)

typedef EGLBoolean (* PFN_eglReleaseThread_PROC) (void);
PFN_eglReleaseThread_PROC eglReleaseThread_PROC = 0;
#   define eglReleaseThread (assert(eglReleaseThread_PROC != 0), eglReleaseThread_PROC)

typedef EGLBoolean (* PFN_eglSurfaceAttrib_PROC) (EGLDisplay, EGLSurface, EGLint, EGLint);
PFN_eglSurfaceAttrib_PROC eglSurfaceAttrib_PROC = 0;
#   define eglSurfaceAttrib (assert(eglSurfaceAttrib_PROC != 0), eglSurfaceAttrib_PROC)

typedef EGLBoolean (* PFN_eglSwapBuffers_PROC) (EGLDisplay, EGLSurface);
PFN_eglSwapBuffers_PROC eglSwapBuffers_PROC = 0;
#   define eglSwapBuffers (assert(eglSwapBuffers_PROC != 0), eglSwapBuffers_PROC)

typedef EGLBoolean (* PFN_eglSwapInterval_PROC) (EGLDisplay, EGLint);
PFN_eglSwapInterval_PROC eglSwapInterval_PROC = 0;
#   define eglSwapInterval (assert(eglSwapInterval_PROC != 0), eglSwapInterval_PROC)

typedef EGLBoolean (* PFN_eglTerminate_PROC) (EGLDisplay);
PFN_eglTerminate_PROC eglTerminate_PROC = 0;
#   define eglTerminate (assert(eglTerminate_PROC != 0), eglTerminate_PROC)

typedef EGLBoolean (* PFN_eglWaitClient_PROC) (void);
PFN_eglWaitClient_PROC eglWaitClient_PROC = 0;
#   define eglWaitClient (assert(eglWaitClient_PROC != 0), eglWaitClient_PROC)

typedef EGLBoolean (* PFN_eglWaitGL_PROC) (void);
PFN_eglWaitGL_PROC eglWaitGL_PROC = 0;
#   define eglWaitGL (assert(eglWaitGL_PROC != 0), eglWaitGL_PROC)

typedef EGLBoolean (* PFN_eglWaitNative_PROC) (EGLint);
PFN_eglWaitNative_PROC eglWaitNative_PROC = 0;
#   define eglWaitNative (assert(eglWaitNative_PROC != 0), eglWaitNative_PROC)

typedef EGLBoolean (* PFN_eglWaitSync_PROC) (EGLDisplay, EGLSync, EGLint);
PFN_eglWaitSync_PROC eglWaitSync_PROC = 0;
#   define eglWaitSync (assert(eglWaitSync_PROC != 0), eglWaitSync_PROC)


static const struct __window_h_egl_attrmap {
    uint32_t src;
    uint32_t dst;
} __window_h_egl_attrmap[] = {
    
    { EGL_RENDER_BUFFER, WINDOW_GL_DOUBLEBUFFER },
    
    { EGL_RED_SIZE, WINDOW_GL_RED_SIZE },
    
    { EGL_GREEN_SIZE, WINDOW_GL_GREEN_SIZE },
    
    { EGL_BLUE_SIZE, WINDOW_GL_BLUE_SIZE },
    
    { EGL_ALPHA_SIZE, WINDOW_GL_ALPHA_SIZE },
    
    { EGL_DEPTH_SIZE, WINDOW_GL_DEPTH_SIZE },
    
    { EGL_STENCIL_SIZE, WINDOW_GL_STENCIL_SIZE },
    
    { EGL_CONTEXT_MAJOR_VERSION, WINDOW_GL_CONTEXT_MAJOR_VERSION },
    
    { EGL_CONTEXT_MINOR_VERSION, WINDOW_GL_CONTEXT_MINOR_VERSION },
    
    { EGL_CONTEXT_OPENGL_PROFILE_MASK, WINDOW_GL_CONTEXT_PROFILE_MASK },
    
    { EGL_CONTEXT_OPENGL_DEBUG, WINDOW_GL_CONTEXT_DEBUG },

    /* ... */

    { EGL_NONE, WINDOW_GL_NONE }

};


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
    int attr_surface[16] = { EGL_RENDER_BUFFER, EGL_SINGLE_BUFFER,
                             EGL_NONE };

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

    /* libEGL: egl.h */
    eglBindAPI_PROC = (PFN_eglBindAPI_PROC) dlsym(handle, "eglBindAPI");
    eglBindTexImage_PROC = (PFN_eglBindTexImage_PROC) dlsym(handle, "eglBindTexImage");
    eglChooseConfig_PROC = (PFN_eglChooseConfig_PROC) dlsym(handle, "eglChooseConfig");
    eglClientWaitSync_PROC = (PFN_eglClientWaitSync_PROC) dlsym(handle, "eglClientWaitSync");
    eglCopyBuffers_PROC = (PFN_eglCopyBuffers_PROC) dlsym(handle, "eglCopyBuffers");
    eglCreateContext_PROC = (PFN_eglCreateContext_PROC) dlsym(handle, "eglCreateContext");
    eglCreateImage_PROC = (PFN_eglCreateImage_PROC) dlsym(handle, "eglCreateImage");
    eglCreatePbufferFromClientBuffer_PROC = (PFN_eglCreatePbufferFromClientBuffer_PROC) dlsym(handle, "eglCreatePbufferFromClientBuffer");
    eglCreatePbufferSurface_PROC = (PFN_eglCreatePbufferSurface_PROC) dlsym(handle, "eglCreatePbufferSurface");
    eglCreatePixmapSurface_PROC = (PFN_eglCreatePixmapSurface_PROC) dlsym(handle, "eglCreatePixmapSurface");
    eglCreatePlatformPixmapSurface_PROC = (PFN_eglCreatePlatformPixmapSurface_PROC) dlsym(handle, "eglCreatePlatformPixmapSurface");
    eglCreatePlatformWindowSurface_PROC = (PFN_eglCreatePlatformWindowSurface_PROC) dlsym(handle, "eglCreatePlatformWindowSurface");
    eglCreateSync_PROC = (PFN_eglCreateSync_PROC) dlsym(handle, "eglCreateSync");
    eglCreateWindowSurface_PROC = (PFN_eglCreateWindowSurface_PROC) dlsym(handle, "eglCreateWindowSurface");
    eglDestroyContext_PROC = (PFN_eglDestroyContext_PROC) dlsym(handle, "eglDestroyContext");
    eglDestroyImage_PROC = (PFN_eglDestroyImage_PROC) dlsym(handle, "eglDestroyImage");
    eglDestroySurface_PROC = (PFN_eglDestroySurface_PROC) dlsym(handle, "eglDestroySurface");
    eglDestroySync_PROC = (PFN_eglDestroySync_PROC) dlsym(handle, "eglDestroySync");
    eglGetConfigAttrib_PROC = (PFN_eglGetConfigAttrib_PROC) dlsym(handle, "eglGetConfigAttrib");
    eglGetConfigs_PROC = (PFN_eglGetConfigs_PROC) dlsym(handle, "eglGetConfigs");
    eglGetCurrentContext_PROC = (PFN_eglGetCurrentContext_PROC) dlsym(handle, "eglGetCurrentContext");
    eglGetCurrentDisplay_PROC = (PFN_eglGetCurrentDisplay_PROC) dlsym(handle, "eglGetCurrentDisplay");
    eglGetCurrentSurface_PROC = (PFN_eglGetCurrentSurface_PROC) dlsym(handle, "eglGetCurrentSurface");
    eglGetDisplay_PROC = (PFN_eglGetDisplay_PROC) dlsym(handle, "eglGetDisplay");
    eglGetError_PROC = (PFN_eglGetError_PROC) dlsym(handle, "eglGetError");
    eglGetPlatformDisplay_PROC = (PFN_eglGetPlatformDisplay_PROC) dlsym(handle, "eglGetPlatformDisplay");
    eglGetProcAddress_PROC = (PFN_eglGetProcAddress_PROC) dlsym(handle, "eglGetProcAddress");
    eglGetSyncAttrib_PROC = (PFN_eglGetSyncAttrib_PROC) dlsym(handle, "eglGetSyncAttrib");
    eglInitialize_PROC = (PFN_eglInitialize_PROC) dlsym(handle, "eglInitialize");
    eglMakeCurrent_PROC = (PFN_eglMakeCurrent_PROC) dlsym(handle, "eglMakeCurrent");
    eglQueryAPI_PROC = (PFN_eglQueryAPI_PROC) dlsym(handle, "eglQueryAPI");
    eglQueryContext_PROC = (PFN_eglQueryContext_PROC) dlsym(handle, "eglQueryContext");
    eglQueryString_PROC = (PFN_eglQueryString_PROC) dlsym(handle, "eglQueryString");
    eglQuerySurface_PROC = (PFN_eglQuerySurface_PROC) dlsym(handle, "eglQuerySurface");
    eglReleaseTexImage_PROC = (PFN_eglReleaseTexImage_PROC) dlsym(handle, "eglReleaseTexImage");
    eglReleaseThread_PROC = (PFN_eglReleaseThread_PROC) dlsym(handle, "eglReleaseThread");
    eglSurfaceAttrib_PROC = (PFN_eglSurfaceAttrib_PROC) dlsym(handle, "eglSurfaceAttrib");
    eglSwapBuffers_PROC = (PFN_eglSwapBuffers_PROC) dlsym(handle, "eglSwapBuffers");
    eglSwapInterval_PROC = (PFN_eglSwapInterval_PROC) dlsym(handle, "eglSwapInterval");
    eglTerminate_PROC = (PFN_eglTerminate_PROC) dlsym(handle, "eglTerminate");
    eglWaitClient_PROC = (PFN_eglWaitClient_PROC) dlsym(handle, "eglWaitClient");
    eglWaitGL_PROC = (PFN_eglWaitGL_PROC) dlsym(handle, "eglWaitGL");
    eglWaitNative_PROC = (PFN_eglWaitNative_PROC) dlsym(handle, "eglWaitNative");
    eglWaitSync_PROC = (PFN_eglWaitSync_PROC) dlsym(handle, "eglWaitSync");

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
#   include <WGL/wgl.h>

/* opengl32: wgl.h */

typedef struct __window_h_wgl *__window_h_wgl;

struct __window_h_wgl {

    /* ... */

    /* opengl32 */
    void *handle;
};


typedef struct s_glcontext_wgl *t_glcontext_wgl;

struct s_glcontext_wgl {

    /* ... */

};

/* internal functions (declarations) */

WININT int __winLoadWGL(void);

WININT int __winLoadWGLSymbols(void);

WININT int __winUnloadWGL(void);

/* internal functions (definitions) */

WININT int __winLoadWGL(void) {
    /* alloc '__window_h.wgl' field */
    if (!__window_h.wgl) {
        __window_h.wgl = calloc(1, sizeof(struct __window_h_wgl));
        if (!__window_h.wgl) {
            return (0);
        }
    }

    /* try to load opengl32 symbols */
    if (!__winLoadWGLSymbols()) { return (0); }
   
    /* ... */

    /* success */
    return (1);
}


WININT int __winLoadWGLSymbols(void) {
    /* null-check */
    if (!__window_h.wgl) { return (0); }

    /* try to load handle */
    static void *handle  = 0;

    /* ... */

    /* set '__window_h.wgl->handle' member */ 
    __window_h.wgl->handle = handle;

    /* success */
    return (1);
}


WININT int __winUnloadWGL(void) {
    /* null-check */
    if (!__window_h.wgl) { return (0); }

    /* release '__window_h.wgl->handle' field */
    /* ... */

    /* release '__window_h.wgl' */
    free(__window_h.wgl);

    /* success */
    return (1);
}

#  endif /* WINDOW_BACKEND_GL_WGL */
#
#
#
#  /* WINDOW_BACKEND_X11 - X11 implementation */
#  if defined (WINDOW_BACKEND_X11)

/* internal functions (declarations) */

WININT int __winCreateWindowX11(t_window, Display *, Window, Window, const size_t, const size_t);

WININT int __winUpdateWindowFlagsX11(t_window);

WININT int __winSendClientEventX11(t_window, Atom, Atom, Atom);

WININT int __winPollEvents(void);

WININT int __winSendEvent(uint32_t, ...);

WININT int __winGetWindowFromIDX11(t_window *, XID);

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
    winSetWindowFlags(result, f);

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
    winSetWindowFlags(result, f);

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


WINDEF int winGetWindowFlags(t_window win, uint32_t *f_ptr) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
   
    /* set flags */
    if (f_ptr) { *f_ptr = win->flags; }

    /* success */
    return (1);
}


WINDEF int winSetWindowFlags(t_window win, const uint32_t f) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
   
    /* set flags */
    win->flags = f;
    __winUpdateWindowFlagsX11(win);

    /* success */
    return (1);
}


WINDEF int winToggleWindowFlags(t_window win, const uint32_t f) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
   
    /* toggle flags */
    win->flags ^= f;
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

    /* get EGL attribute from 'attr' */
    int eglattr = 0;
    for (size_t i = 0; __window_h_egl_attrmap[i].src; i++) {
        if (__window_h_egl_attrmap[i].dst == (uint32_t) attr) {
            eglattr = __window_h_egl_attrmap[i].src;
            break;
        }
    }

    /* no attribute match */
    if (!eglattr) { return (0); }

    /* search '__window_h.egl->attr.surface' for 'eglattr' */
    int *attrl = __window_h.egl->attr.surface;
    for (size_t i = 0; attrl[i]; i += 2) {
        if (attrl[i] == eglattr) {
            attrl[i + 1] = value;

            /* success */
            return (1);
        }
    }
    
    /* search '__window_h.egl->attr.context' for 'eglattr' */
    attrl = __window_h.egl->attr.context;
    for (size_t i = 0; attrl[i]; i += 2) {
        if (attrl[i] == eglattr) {
            attrl[i + 1] = value;

            /* success */
            return (1);
        }
    }
    /* search '__window_h.egl->attr.config' for 'eglattr' */
    attrl = __window_h.egl->attr.config;
    for (size_t i = 0; attrl[i]; i += 2) {
        if (attrl[i] == eglattr) {
            attrl[i + 1] = value;

            /* success */
            return (1);
        }
    }
    

    /* failure  */
    return (0);
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
    while (XPending(dpy)) {
        XNextEvent(dpy, &xevent);
        
        switch (xevent.type) {
            case (ClientMessage): {
                /* get the specific event */
                XClientMessageEvent xclient = xevent.xclient;

                /* xatom references */
                Atom WM_PROTOCOLS     = __window_h.x11->xatom.wm_protocols;
                Atom WM_DELETE_WINDOW = __window_h.x11->xatom.wm_delete_window;

                /* process different kind of client events */
                const Atom message_type = xclient.message_type;
                if (message_type == WM_PROTOCOLS) {
                    /* get the received atom */
                    const Atom data = xclient.data.l[0];

                    /* WINDOW_EVENT_QUIT */
                    if (data == WM_DELETE_WINDOW) {
                        __winSendEvent(WINDOW_EVENT_QUIT);
                    }
                }
            } break;

            case (MotionNotify): {
                /* get the specific event */
                XMotionEvent xmotion = xevent.xmotion;

                /* WINDOW_EVENT_MOUSE_ members layout */
                t_window window;
                uint64_t which;
                
                /* WINDOW_EVENT_MOUSE_MOTION members layout */
                int32_t x, xrel;
                int32_t y, yrel;

                __winGetWindowFromIDX11(&window, xmotion.window);
                which = 0; /* TODO: get the mouse ID */
                x = xevent.xmotion.x, xrel = xmotion.x_root,
                y = xevent.xmotion.y, yrel = xmotion.y_root;
                __winSendEvent(WINDOW_EVENT_MOUSE_MOTION, window, which, x, xrel, y, yrel);

            } break;

            case (ButtonPress):
            case (ButtonRelease): {

            } break;
        }
    }

    /* success */
    return (1);
}


/* __winSendEvent:
 *  
 *  This function accepts a variadic argument list of parameters which MUST follows
 *  the layout of members of the desired event.
 *
 *  Let's say we're passing a list of data for 'WINDOW_EVENT_WINDOW_' event.
 *  With it's layout:
 *  - t_window window,
 *  - uint32_t data1,
 *  - uint32_t data2,
 *  ... va_list should be constructed of: t_window, uint32_t, uint32_.
 * */
WININT int __winSendEvent(uint32_t type, ...) {
    /* null-check */
    if (!__window_h.x11) { return (0); }

    /* default 'event' object */
    t_event event = {
        .type = type,
        .time = winGetTime()
    };

    /* intialize variadic list */
    va_list va;
    va_start(va, 0);
    switch (type) {

        case (WINDOW_EVENT_QUIT): { } break;

        /* Mouse events */

        case (WINDOW_EVENT_MOUSE_MOTION): {
            event.mouse.window = va_arg(va, t_window);
            event.mouse.which  = va_arg(va, uint64_t);
            event.mouse.x    = va_arg(va, int32_t);
            event.mouse.xrel = va_arg(va, int32_t);
            event.mouse.y    = va_arg(va, int32_t);
            event.mouse.yrel = va_arg(va, int32_t);
        } break;

        case (WINDOW_EVENT_MOUSE_BUTTON): { } break;

        case (WINDOW_EVENT_MOUSE_SCROLL): { } break;

        case (WINDOW_EVENT_MOUSE_ADDED): { } break;

        case (WINDOW_EVENT_MOUSE_REMOVED): { } break;

        /* Keyboard events */

        case (WINDOW_EVENT_KEYBOARD_KEY): { } break;

        case (WINDOW_EVENT_KEYBOARD_ADDED): { } break;

        case (WINDOW_EVENT_KEYBOARD_REMOVED): { } break;

        /* Window events */

        case (WINDOW_EVENT_WINDOW_CREATE): { } break;

        case (WINDOW_EVENT_WINDOW_DESTROY): { } break;

        case (WINDOW_EVENT_WINDOW_MAP): { } break;

        case (WINDOW_EVENT_WINDOW_UNMAP): { } break;

        case (WINDOW_EVENT_WINDOW_RESIZE): { } break;

        case (WINDOW_EVENT_WINDOW_MOTION): { } break;

        case (WINDOW_EVENT_WINDOW_ENTER): { } break;

        case (WINDOW_EVENT_WINDOW_LEAVE): { } break;

        case (WINDOW_EVENT_WINDOW_MAXIMIZE): { } break;

        case (WINDOW_EVENT_WINDOW_MINIMIZE): { } break;

        /* ... */

        default: { } break;
    }

    /* release variadic list */
    va_end(va);

    /* status based on result of 'winPushEvent' */
    return (winPushEvent(&event));
}


WININT int __winGetWindowFromIDX11(t_window *win, XID id) {
    /* null-check */
    if (!__window_h.x11) { return (0); }
    
    /* iterate over the list of windows */
    *win = 0;
    for (t_window node = __window_h.window_list; node; node = node->next) {
        if (node->x11->xlib.client == id) {
            *win = node;
            break;
        }
    }

    /* check if window was found */
    if (!(*win)) {
        return (0);
    }

    /* success */
    return (1);
}

#  endif /* WINDOW_BACKEND_X11 */
#
#  /* WINDOW_BACKEND_WAYLAND - Wayland implementation */
#  if defined (WINDOW_BACKEND_WAYLAND)

/* ... */

#  endif /* WINDOW_BACKEND_WAYLAND */
#
#  /* WINDOW_PLATFORM_WIN32 - Win32 implementation */
#  if defined (WINDOW_PLATFORM_WIN32)

/* ... */

#  endif /* WINDOW_PLATFORM_WIN32 */
# endif /* WINDOW_IMPLEMENTATION */
#endif /* _window_h_ */
