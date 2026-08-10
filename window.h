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
# /* "linux" platform preprocessor */
# if defined (__linux__)
# /* {{{ */
#  define WINDOW_PLATFORM "linux"
#  define WINDOW_PLATFORM_LINUX 1
#
#  /* ensure 'WINDOW_BACKEND_X11' equals to '1' */
#  if defined (WINDOW_BACKEND_X11)
#   undef  WINDOW_BACKEND_X11
#   define WINDOW_BACKEND_X11 1
#
#  /* ensure 'WINDOW_BACKEND_WAYLAND' equals to '2' */
#  elif defined (WINDOW_BACKEND_WAYLAND)
#   undef  WINDOW_BACKEND_WAYLAND
#   define WINDOW_BACKEND_WAYLAND 2
#
#  /* "no backend selected" scenario */
#  elif !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   /* pick X11 by default */
#   define WINDOW_BACKEND_X11 1
#  endif
# /* }}} */
#
# /* "bsd" platform preprocessor */
# elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__bsdi__) || defined (__DragonFly__) || defined (__MidnightBSD__)
# /* {{{ */
#  define WINDOW_PLATFORM "bsd"
#  define WINDOW_PLATFORM_BSD 1
#
#  /* ensure 'WINDOW_BACKEND_X11' equals to '1' */
#  if defined (WINDOW_BACKEND_X11)
#   undef  WINDOW_BACKEND_X11
#   define WINDOW_BACKEND_X11 1
#
#  /* ensure 'WINDOW_BACKEND_WAYLAND' equals to '2' */
#  elif defined (WINDOW_BACKEND_WAYLAND)
#   undef  WINDOW_BACKEND_WAYLAND
#   define WINDOW_BACKEND_WAYLAND 2
#
#  /* "no backend selected" scenario */
#  elif !defined (WINDOW_BACKEND_X11) && !defined (WINDOW_BACKEND_WAYLAND)
#   /* pick X11 by default */
#   define WINDOW_BACKEND_X11 1
#  endif
# /* }}} */
#
# /* "win32" platform preprocessor */
# elif defined (__CYGWIN__) || defined (_WIN32)
# /* {{{ */
#  define WINDOW_PLATFORM "win32"
#  define WINDOW_PLATFORM_WIN32 1
#
#  /* ensure 'WINDOW_BACKEND_WIN32' equals to '3' */
#  if defined (WINDOW_BACKEND_WIN32)
#   undef  WINDOW_BACKEND_WIN32
#   define WINDOW_BACKEND_WIN32 3
#
#  /* "no backend selected" scenario */
#  elif !defined (WINDOW_BACKEND_WIN32)
#   /* pick Win32 by default */
#   define WINDOW_BACKEND_WIN32 3
#  endif
# /* }}} */
#
# /* "apple" platform preprocessor */
# elif defined (__APPLE__) || defined (__MACH__)
# /* {{{ */
#  define WINDOW_PLATFORM "apple"
#  define WINDOW_PLATFORM_APPLE 1
#
#  /* ensure 'WINDOW_BACKEND_COCOA' equals to '4' */
#  if defined (WINDOW_BACKEND_COCOA)
#   undef  WINDOW_BACKEND_COCOA
#   define WINDOW_BACKEND_COCOA 4
#
#  /* "no backend selected" scenario */
#  elif !defined (WINDOW_BACKEND_COCOA)
#   /* pick Cocoa by default */
#   define WINDOW_BACKEND_COCOA 4
#  endif
#
#  error /* platform not supported right now */
# /* }}} */
#
# else
#  error /* no valid backend found */
# endif
#
# /* "linux" graphics API preprocessor */
# if defined (WINDOW_PLATFORM_LINUX)
# /* {{{ */
#
#  /* ensure 'WINDOW_BACKEND_GLX' equals to '1' */
#  if defined (WINDOW_BACKEND_GLX)
#   undef  WINDOW_BACKEND_GLX
#   define WINDOW_BACKEND_GLX 1
#
#  /* ensure 'WINDOW_BACKEND_EGL' equals to '2' */
#  elif defined (WINDOW_BACKEND_EGL)
#   undef  WINDOW_BACKEND_EGL
#   define WINDOW_BACKEND_EGL 2
#
#  /* "no backend selected" scenario */
#  elif !defined (WINDOW_BACKEND_GLX) && !defined (WINDOW_BACKEND_EGL)
#   if defined (WINDOW_BACKEND_X11)
#    /* pick GLX by default for X11 */
#    define WINDOW_BACKEND_GLX 1
#
#   elif defined (WINDOW_BACKEND_WAYLAND)
#    /* pick EGL by default for wayland */
#    define WINDOW_BACKEND_EGL 1
#
#   else
#    error
#   endif
#  endif
# /* }}} */
#
# /* "bsd" graphics API preprocessor */
# elif defined (WINDOW_PLATFORM_BSD)
# /* {{{ */
#
#  /* ensure 'WINDOW_BACKEND_GLX' equals to '1' */
#  if defined (WINDOW_BACKEND_GLX)
#   undef  WINDOW_BACKEND_GLX
#   define WINDOW_BACKEND_GLX 1
#
#  /* ensure 'WINDOW_BACKEND_EGL' equals to '2' */
#  elif defined (WINDOW_BACKEND_EGL)
#   undef  WINDOW_BACKEND_EGL
#   define WINDOW_BACKEND_EGL 2
#
#  /* "no backend selected" scenario */
#  elif !defined (WINDOW_BACKEND_GLX) && !defined (WINDOW_BACKEND_EGL)
#   if defined (WINDOW_BACKEND_X11)
#    /* pick GLX by default for X11 */
#    define WINDOW_BACKEND_GLX 1
#
#   elif defined (WINDOW_BACKEND_WAYLAND)
#    /* pick EGL by default for wayland */
#    define WINDOW_BACKEND_EGL 1
#
#   else
#    error
#   endif
#  endif
# /* }}} */
#
# /* "win32" graphics API preprocessor */
# elif defined (WINDOW_PLATFORM_WIN32)
# /* {{{ */
#
#  /* ensure 'WINDOW_BACKEND_WGL' equals to '3' */
#  if defined (WINDOW_BACKEND_WGL)
#   undef  WINDOW_BACKEND_WGL
#   define WINDOW_BACKEND_WGL 1
#
#  /* "no backend selected" scenario */
#  elif !defined (WINDOW_BACKEND_WGL)
#   /* pick WGL by default */
#   define WINDOW_BACKEND_WGL 1
#  endif
# /* }}} */
#
# /* "apple" graphics API preprocessor */
# elif defined (WINDOW_PLATFORM_APPLE)
# /* {{{ */
#  warn /* OpenGL is depracated at MacOS */
#  warn /* TODO: consider implementing OpenGL handling for MacOS */
# /* }}} */
#
# else
#  error /* invalid backend */
# endif
#
# include <stddef.h>
# include <stdint.h>

/* inputs */

enum {
    WINDOW_BUTTON_NONE = 0,
    WINDOW_BUTTON_LEFT,
    WINDOW_BUTTON_RIGHT,
    WINDOW_BUTTON_MIDDLE,
    /* ... */
};


/* WINDOW_KEYCODE:
 *  Physical keyboard representation.
 *
 *  This keycode layout follows the "HID Usage Tables FOR Universal Serial Bus (USB)" (Version 1.21):
 *      https://usb.org/sites/default/files/hut1_21.pdf
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
enum {
    WINDOW_KEYCODE_NONE = 0x0000,

/* {{{ */

/*  
 *  Keyboard/Keypad Page (0x07)
 *      https://usb.org/sites/default/files/hut1_21.pdf#chapter.10
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    /* 0x0000 - 0x0003: reserved */

    WINDOW_KEYCODE_A = 0x0004,
    WINDOW_KEYCODE_B = 0x0005,
    WINDOW_KEYCODE_C = 0x0006,
    WINDOW_KEYCODE_D = 0x0007,
    WINDOW_KEYCODE_E = 0x0008,
    WINDOW_KEYCODE_F = 0x0009,
    WINDOW_KEYCODE_G = 0x000a,
    WINDOW_KEYCODE_H = 0x000b,
    WINDOW_KEYCODE_I = 0x000c,
    WINDOW_KEYCODE_J = 0x000d,
    WINDOW_KEYCODE_K = 0x000e,
    WINDOW_KEYCODE_L = 0x000f,
    WINDOW_KEYCODE_M = 0x0010,
    WINDOW_KEYCODE_N = 0x0011,
    WINDOW_KEYCODE_O = 0x0012,
    WINDOW_KEYCODE_P = 0x0013,
    WINDOW_KEYCODE_Q = 0x0014,
    WINDOW_KEYCODE_R = 0x0015,
    WINDOW_KEYCODE_S = 0x0016,
    WINDOW_KEYCODE_T = 0x0017,
    WINDOW_KEYCODE_U = 0x0018,
    WINDOW_KEYCODE_V = 0x0019,
    WINDOW_KEYCODE_W = 0x001a,
    WINDOW_KEYCODE_X = 0x001b,
    WINDOW_KEYCODE_Y = 0x001c,
    WINDOW_KEYCODE_Z = 0x001d,
    WINDOW_KEYCODE_1 = 0x001e,
    WINDOW_KEYCODE_2 = 0x001f,
    WINDOW_KEYCODE_3 = 0x0020,
    WINDOW_KEYCODE_4 = 0x0021,
    WINDOW_KEYCODE_5 = 0x0022,
    WINDOW_KEYCODE_6 = 0x0023,
    WINDOW_KEYCODE_7 = 0x0024,
    WINDOW_KEYCODE_8 = 0x0025,
    WINDOW_KEYCODE_9 = 0x0026,
    WINDOW_KEYCODE_0 = 0x0027,
    WINDOW_KEYCODE_RETURN = 0x0028,
    WINDOW_KEYCODE_ESCAPE = 0x0029,
    WINDOW_KEYCODE_BACKSPACE = 0x002a,
    WINDOW_KEYCODE_TAB = 0x002b,
    WINDOW_KEYCODE_SPACE = 0x002c,
    WINDOW_KEYCODE_MINUS = 0x002d,
    WINDOW_KEYCODE_EQUAL = 0x002e,
    WINDOW_KEYCODE_OPENBRACKET = 0x002f,
    WINDOW_KEYCODE_CLOSEBRACKET = 0x0030,
    WINDOW_KEYCODE_BACKSLASH = 0x0031,
    WINDOW_KEYCODE_NONUSHASH = 0x0032,
    WINDOW_KEYCODE_SEMICOLON = 0x0033,
    WINDOW_KEYCODE_QUOTE = 0x0034,
    WINDOW_KEYCODE_GRAVE = 0x0035,
    WINDOW_KEYCODE_COMMA = 0x0036,
    WINDOW_KEYCODE_PERIOD = 0x0037,
    WINDOW_KEYCODE_SLASH = 0x0038,
    WINDOW_KEYCODE_CAPSLOCK = 0x0039,
    WINDOW_KEYCODE_F1 = 0x003a,
    WINDOW_KEYCODE_F2 = 0x003b,
    WINDOW_KEYCODE_F3 = 0x003c,
    WINDOW_KEYCODE_F4 = 0x003d,
    WINDOW_KEYCODE_F5 = 0x003e,
    WINDOW_KEYCODE_F6 = 0x003f,
    WINDOW_KEYCODE_F7 = 0x0040,
    WINDOW_KEYCODE_F8 = 0x0041,
    WINDOW_KEYCODE_F9 = 0x0042,
    WINDOW_KEYCODE_F10 = 0x0043,
    WINDOW_KEYCODE_F11 = 0x0044,
    WINDOW_KEYCODE_F12 = 0x0045,
    WINDOW_KEYCODE_PRINTSCREEN = 0x0046,
    WINDOW_KEYCODE_SCROLLLOCK = 0x0047,
    WINDOW_KEYCODE_PAUSE = 0x0048,
    WINDOW_KEYCODE_INSERT = 0x0049,
    WINDOW_KEYCODE_HOME = 0x004a,
    WINDOW_KEYCODE_PAGEUP = 0x004b,
    WINDOW_KEYCODE_DELETE = 0x004c,
    WINDOW_KEYCODE_END = 0x004d,
    WINDOW_KEYCODE_PAGEDOWN = 0x004e,
    WINDOW_KEYCODE_RIGHT = 0x004f,
    WINDOW_KEYCODE_LEFT = 0x0050,
    WINDOW_KEYCODE_DOWN = 0x0051,
    WINDOW_KEYCODE_UP = 0x0052,
    WINDOW_KEYCODE_NUMLOCK = 0x0053,
    WINDOW_KEYCODE_KP_SLASH = 0x0054,
    WINDOW_KEYCODE_KP_ASTERISK = 0x0055,
    WINDOW_KEYCODE_KP_MINUS = 0x0056,
    WINDOW_KEYCODE_KP_PLUS = 0x0057,
    WINDOW_KEYCODE_KP_ENTER = 0x0058,
    WINDOW_KEYCODE_KP_1 = 0x0059,
    WINDOW_KEYCODE_KP_2 = 0x005a,
    WINDOW_KEYCODE_KP_3 = 0x005b,
    WINDOW_KEYCODE_KP_4 = 0x005c,
    WINDOW_KEYCODE_KP_5 = 0x005d,
    WINDOW_KEYCODE_KP_6 = 0x005e,
    WINDOW_KEYCODE_KP_7 = 0x005f,
    WINDOW_KEYCODE_KP_8 = 0x0060,
    WINDOW_KEYCODE_KP_9 = 0x0061,
    WINDOW_KEYCODE_KP_0 = 0x0062,
    WINDOW_KEYCODE_KP_DELETE = 0x0063,
    WINDOW_KEYCODE_NONUSSLASH = 0x0064,
    WINDOW_KEYCODE_APPLICATION = 0x0065,
    WINDOW_KEYCODE_POWER = 0x0066,
    WINDOW_KEYCODE_KP_EQUAL = 0x0067,
    WINDOW_KEYCODE_F13 = 0x0068,
    WINDOW_KEYCODE_F14 = 0x0069,
    WINDOW_KEYCODE_F15 = 0x006a,
    WINDOW_KEYCODE_F16 = 0x006b,
    WINDOW_KEYCODE_F17 = 0x006c,
    WINDOW_KEYCODE_F18 = 0x006d,
    WINDOW_KEYCODE_F19 = 0x006e,
    WINDOW_KEYCODE_F20 = 0x006f,
    WINDOW_KEYCODE_F21 = 0x0070,
    WINDOW_KEYCODE_F22 = 0x0071,
    WINDOW_KEYCODE_F23 = 0x0072,
    WINDOW_KEYCODE_F24 = 0x0073,
    WINDOW_KEYCODE_EXECUTE = 0x0074,
    WINDOW_KEYCODE_HELP = 0x0075,
    WINDOW_KEYCODE_MENU = 0x0076,
    WINDOW_KEYCODE_SELECT = 0x0077,
    WINDOW_KEYCODE_STOP = 0x0078,
    WINDOW_KEYCODE_AGAIN = 0x0079,
    WINDOW_KEYCODE_UNDO = 0x007a,
    WINDOW_KEYCODE_CUT = 0x007b,
    WINDOW_KEYCODE_COPY = 0x007c,
    WINDOW_KEYCODE_PASTE = 0x007d,
    WINDOW_KEYCODE_FIND = 0x007e,
    WINDOW_KEYCODE_MUTE = 0x007f,
    WINDOW_KEYCODE_VOLUMEUP = 0x0080,
    WINDOW_KEYCODE_VOLUMEDOWN = 0x0081,
    WINDOW_KEYCODE_LOCKING_CAPSLOCK = 0x0082,
    WINDOW_KEYCODE_LOCKING_NUMLOCK = 0x0083,
    WINDOW_KEYCODE_LOCKING_SCROLLLOCK = 0x0084,
    WINDOW_KEYCODE_KP_COMMA = 0x0085,
    WINDOW_KEYCODE_EQUALSIGN = 0x0086,
    WINDOW_KEYCODE_INTERNATIONAL1 = 0x0087,
    WINDOW_KEYCODE_INTERNATIONAL2 = 0x0088,
    WINDOW_KEYCODE_INTERNATIONAL3 = 0x0089,
    WINDOW_KEYCODE_INTERNATIONAL4 = 0x008a,
    WINDOW_KEYCODE_INTERNATIONAL5 = 0x008b,
    WINDOW_KEYCODE_INTERNATIONAL6 = 0x008c,
    WINDOW_KEYCODE_INTERNATIONAL7 = 0x008d,
    WINDOW_KEYCODE_INTERNATIONAL8 = 0x008e,
    WINDOW_KEYCODE_INTERNATIONAL9 = 0x008f,
    WINDOW_KEYCODE_LANG1 = 0x0090,
    WINDOW_KEYCODE_LANG2 = 0x0091,
    WINDOW_KEYCODE_LANG3 = 0x0092,
    WINDOW_KEYCODE_LANG4 = 0x0093,
    WINDOW_KEYCODE_LANG5 = 0x0094,
    WINDOW_KEYCODE_LANG6 = 0x0095,
    WINDOW_KEYCODE_LANG7 = 0x0096,
    WINDOW_KEYCODE_LANG8 = 0x0097,
    WINDOW_KEYCODE_LANG9 = 0x0098,
    WINDOW_KEYCODE_ALTENRATEERASE = 0x0099,
    WINDOW_KEYCODE_SYSREQ = 0x009a,
    WINDOW_KEYCODE_CANCEL = 0x009b,
    WINDOW_KEYCODE_CLEAR = 0x009c,
    WINDOW_KEYCODE_PRIOR = 0x009d,
    WINDOW_KEYCODE_RETURN2 = 0x009e,
    WINDOW_KEYCODE_SEPARATOR = 0x009f,
    WINDOW_KEYCODE_OUT = 0x00a0,
    WINDOW_KEYCODE_OPER = 0x00a1,
    WINDOW_KEYCODE_CLEARAGAIN = 0x00a2,
    WINDOW_KEYCODE_CRSEL = 0x00a3,
    WINDOW_KEYCODE_EXSEL = 0x00a4,
    
    /* 0x00a5 - 0x00af: reserved */

    WINDOW_KEYCODE_KP_00 = 0x00b0,
    WINDOW_KEYCODE_KP_000 = 0x00b1,
    WINDOW_KEYCODE_SEPARATOR_THOUSANDS = 0x00b2,
    WINDOW_KEYCODE_SEPARATOR_DECIMAL = 0x00b3,
    WINDOW_KEYCODE_CURRENCY_UNIT = 0x00b4,
    WINDOW_KEYCODE_CURRENCY_SUBUNIT = 0x00b5,
    WINDOW_KEYCODE_KP_OPENPAREN = 0x00b6,
    WINDOW_KEYCODE_KP_CLOSEPAREN = 0x00b7,
    WINDOW_KEYCODE_KP_OPENCURLY = 0x00b8,
    WINDOW_KEYCODE_KP_CLOSECURLY = 0x00b9,
    WINDOW_KEYCODE_KP_TAB = 0x00ba,
    WINDOW_KEYCODE_KP_BACKSPACE = 0x00bb,
    WINDOW_KEYCODE_KP_A = 0x00bc,
    WINDOW_KEYCODE_KP_B = 0x00bd,
    WINDOW_KEYCODE_KP_C = 0x00be,
    WINDOW_KEYCODE_KP_D = 0x00bf,
    WINDOW_KEYCODE_KP_E = 0x00c0,
    WINDOW_KEYCODE_KP_F = 0x00c1,
    WINDOW_KEYCODE_KP_XOR = 0x00c2,
    WINDOW_KEYCODE_KP_CARET = 0x00c3,
    WINDOW_KEYCODE_KP_PERCENT = 0x00c4,
    WINDOW_KEYCODE_KP_LESS = 0x00c5,
    WINDOW_KEYCODE_KP_GREAT = 0x00c6,
    WINDOW_KEYCODE_KP_BITAND = 0x00c7,
    WINDOW_KEYCODE_KP_LOGICAND = 0x00c8,
    WINDOW_KEYCODE_KP_BITOR = 0x00c9,
    WINDOW_KEYCODE_KP_LOGICOR = 0x00ca,
    WINDOW_KEYCODE_KP_COLON = 0x00cb,
    WINDOW_KEYCODE_KP_HASH = 0x00cc,
    WINDOW_KEYCODE_KP_SPACE = 0x00cd,
    WINDOW_KEYCODE_KP_AT = 0x00ce,
    WINDOW_KEYCODE_KP_EXCLAIM = 0x00cf,
    WINDOW_KEYCODE_KP_MEMORYSTORE = 0x00d0,
    WINDOW_KEYCODE_KP_MEMORYRECALL = 0x00d1,
    WINDOW_KEYCODE_KP_MEMORYCLEAR = 0x00d2,
    WINDOW_KEYCODE_KP_MEMORYADD = 0x00d3,
    WINDOW_KEYCODE_KP_MEMORYSUBSTRACT = 0x00d4,
    WINDOW_KEYCODE_KP_MEMORYMULTIPLY = 0x00d5,
    WINDOW_KEYCODE_KP_MEMORYDIVIDE = 0x00d6,
    WINDOW_KEYCODE_KP_PLUSMINUS = 0x00d7,
    WINDOW_KEYCODE_KP_CLEAR = 0x00d8,
    WINDOW_KEYCODE_KP_CLEARENTRY = 0x00d9,
    WINDOW_KEYCODE_KP_BINARY = 0x00da,
    WINDOW_KEYCODE_KP_OCTAL = 0x00db,
    WINDOW_KEYCODE_KP_DECIMAL = 0x00dc,
    WINDOW_KEYCODE_KP_HEXADECIMAL = 0x00dd,
    
    /* 0x00de - 0x00df: reserved */

    WINDOW_KEYCODE_LEFTCTRL = 0x00e0,
    WINDOW_KEYCODE_LEFTSHIFT = 0x00e1,
    WINDOW_KEYCODE_LEFTALT = 0x00e2,
    WINDOW_KEYCODE_LEFTGUI = 0x00e3,
    WINDOW_KEYCODE_RIGHTCTRL = 0x00e4,
    WINDOW_KEYCODE_RIGHTSHIFT = 0x00e5,
    WINDOW_KEYCODE_RIGHTALT = 0x00e6,
    WINDOW_KEYCODE_RIGHTGUI = 0x00e7,

/* }}} */

    /* 0x00e8 - 0xffff: reserved */

    /* ... */

};


/* WINDOW_KEYSYM:
 *  Virtual keyboard representation.
 * * * * * * * * * * * * * * * * * * */
# define WINDOW_KEYSYM_KEYCODE_MASK (1 << 30)
# define WINDOW_KEYCODE_TO_KEYSYM(i) ((i) | WINDOW_KEYSYM_KEYCODE_MASK)
enum {
    WINDOW_KEYSYM_NONE = 0x0000,
   
/* {{{ */

/*
 *  ASCII-compliant keysym table
 *
 * * * * * * * * * * * * * * * * */

    WINDOW_KEYSYM_BACKSPACE = 0x0008,
    WINDOW_KEYSYM_TAB = 0x0009,
    WINDOW_KEYSYM_RETURN = 0x000d,
    WINDOW_KEYSYM_ESCAPE = 0x001b,
    WINDOW_KEYSYM_SPACE = 0x0020,
    WINDOW_KEYSYM_EXCLAIM = 0x0021,
    WINDOW_KEYSYM_DOUBLEQUOTE = 0x0022,
    WINDOW_KEYSYM_HASH = 0x0023,
    WINDOW_KEYSYM_DOLLAR = 0x0024,
    WINDOW_KEYSYM_PERCENT = 0x0025,
    WINDOW_KEYSYM_AMPERSAND = 0x0026,
    WINDOW_KEYSYM_QUOTE = 0x0027,
    WINDOW_KEYSYM_OPENPAREN = 0x0028,
    WINDOW_KEYSYM_CLOSEPAREN = 0x0029,
    WINDOW_KEYSYM_ASTERISK = 0x002a,
    WINDOW_KEYSYM_PLUS = 0x002b,
    WINDOW_KEYSYM_COMMA = 0x002c,
    WINDOW_KEYSYM_MINUS = 0x002d,
    WINDOW_KEYSYM_PERIOD = 0x002e,
    WINDOW_KEYSYM_SLASH = 0x002f,
    WINDOW_KEYSYM_0 = 0x0030,
    WINDOW_KEYSYM_1 = 0x0031,
    WINDOW_KEYSYM_2 = 0x0032,
    WINDOW_KEYSYM_3 = 0x0033,
    WINDOW_KEYSYM_4 = 0x0034,
    WINDOW_KEYSYM_5 = 0x0035,
    WINDOW_KEYSYM_6 = 0x0036,
    WINDOW_KEYSYM_7 = 0x0037,
    WINDOW_KEYSYM_8 = 0x0038,
    WINDOW_KEYSYM_9 = 0x0039,
    WINDOW_KEYSYM_COLON = 0x003a,
    WINDOW_KEYSYM_SEMICOLON = 0x003b,
    WINDOW_KEYSYM_LESS = 0x003c,
    WINDOW_KEYSYM_EQUAL = 0x003d,
    WINDOW_KEYSYM_GREATER = 0x003e,
    WINDOW_KEYSYM_QUESTION = 0x003f,
    WINDOW_KEYSYM_AT = 0x0040,
    WINDOW_KEYSYM_A = 0x0041,
    WINDOW_KEYSYM_B = 0x0042,
    WINDOW_KEYSYM_C = 0x0043,
    WINDOW_KEYSYM_D = 0x0044,
    WINDOW_KEYSYM_E = 0x0045,
    WINDOW_KEYSYM_F = 0x0046,
    WINDOW_KEYSYM_G = 0x0047,
    WINDOW_KEYSYM_H = 0x0048,
    WINDOW_KEYSYM_I = 0x0049,
    WINDOW_KEYSYM_J = 0x004a,
    WINDOW_KEYSYM_K = 0x004b,
    WINDOW_KEYSYM_L = 0x004c,
    WINDOW_KEYSYM_M = 0x004d,
    WINDOW_KEYSYM_N = 0x004e,
    WINDOW_KEYSYM_O = 0x004f,
    WINDOW_KEYSYM_P = 0x0050,
    WINDOW_KEYSYM_Q = 0x0051,
    WINDOW_KEYSYM_R = 0x0052,
    WINDOW_KEYSYM_S = 0x0053,
    WINDOW_KEYSYM_T = 0x0054,
    WINDOW_KEYSYM_U = 0x0055,
    WINDOW_KEYSYM_V = 0x0056,
    WINDOW_KEYSYM_W = 0x0057,
    WINDOW_KEYSYM_X = 0x0058,
    WINDOW_KEYSYM_Y = 0x0059,
    WINDOW_KEYSYM_Z = 0x005a,
    WINDOW_KEYSYM_OPENBRACKET = 0x005b,
    WINDOW_KEYSYM_BACKSLASH = 0x005c,
    WINDOW_KEYSYM_CLOSEBRACKET = 0x005d,
    WINDOW_KEYSYM_CARET = 0x005e,
    WINDOW_KEYSYM_UNDERSCORE = 0x005f,
    WINDOW_KEYSYM_GRAVE = 0x0060,
    WINDOW_KEYSYM_LOWER_A = 0x0061,
    WINDOW_KEYSYM_LOWER_B = 0x0062,
    WINDOW_KEYSYM_LOWER_C = 0x0063,
    WINDOW_KEYSYM_LOWER_D = 0x0064,
    WINDOW_KEYSYM_LOWER_E = 0x0065,
    WINDOW_KEYSYM_LOWER_F = 0x0066,
    WINDOW_KEYSYM_LOWER_G = 0x0067,
    WINDOW_KEYSYM_LOWER_H = 0x0068,
    WINDOW_KEYSYM_LOWER_I = 0x0069,
    WINDOW_KEYSYM_LOWER_J = 0x006a,
    WINDOW_KEYSYM_LOWER_K = 0x006b,
    WINDOW_KEYSYM_LOWER_L = 0x006c,
    WINDOW_KEYSYM_LOWER_M = 0x006d,
    WINDOW_KEYSYM_LOWER_N = 0x006e,
    WINDOW_KEYSYM_LOWER_O = 0x006f,
    WINDOW_KEYSYM_LOWER_P = 0x0070,
    WINDOW_KEYSYM_LOWER_Q = 0x0071,
    WINDOW_KEYSYM_LOWER_R = 0x0072,
    WINDOW_KEYSYM_LOWER_S = 0x0073,
    WINDOW_KEYSYM_LOWER_T = 0x0074,
    WINDOW_KEYSYM_LOWER_U = 0x0075,
    WINDOW_KEYSYM_LOWER_V = 0x0076,
    WINDOW_KEYSYM_LOWER_W = 0x0077,
    WINDOW_KEYSYM_LOWER_X = 0x0078,
    WINDOW_KEYSYM_LOWER_Y = 0x0079,
    WINDOW_KEYSYM_LOWER_Z = 0x007a,
    WINDOW_KEYSYM_OPENCURLY = 0x007b,
    WINDOW_KEYSYM_PIPE = 0x007c,
    WINDOW_KEYSYM_CLOSECURLY = 0x007d,
    WINDOW_KEYSYM_TILDE = 0x007e,
    WINDOW_KEYSYM_DELETE = 0x007f,

/*
 *  ASCII-extended keysym table
 *
 * * * * * * * * * * * * * * * * */

    WINDOW_KEYSYM_CAPSLOCK = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_CAPSLOCK),
    WINDOW_KEYSYM_F1 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F1),
    WINDOW_KEYSYM_F2 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F2),
    WINDOW_KEYSYM_F3 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F3),
    WINDOW_KEYSYM_F4 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F4),
    WINDOW_KEYSYM_F5 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F5),
    WINDOW_KEYSYM_F6 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F6),
    WINDOW_KEYSYM_F7 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F7),
    WINDOW_KEYSYM_F8 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F8),
    WINDOW_KEYSYM_F9 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F9),
    WINDOW_KEYSYM_F10 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F10),
    WINDOW_KEYSYM_F11 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F11),
    WINDOW_KEYSYM_F12 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_F12),
    WINDOW_KEYSYM_PRINTSCREEN = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_PRINTSCREEN),
    WINDOW_KEYSYM_SCROLLLOCK = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_SCROLLLOCK),
    WINDOW_KEYSYM_PAUSE = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_PAUSE),
    WINDOW_KEYSYM_INSERT = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_INSERT),
    WINDOW_KEYSYM_HOME = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_HOME),
    WINDOW_KEYSYM_PAGEUP = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_PAGEUP),
    WINDOW_KEYSYM_END = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_END),
    WINDOW_KEYSYM_PAGEDOWN = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_PAGEDOWN),
    WINDOW_KEYSYM_RIGHT = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_RIGHT),
    WINDOW_KEYSYM_LEFT = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_LEFT),
    WINDOW_KEYSYM_DOWN = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_DOWN),
    WINDOW_KEYSYM_UP = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_UP),
    WINDOW_KEYSYM_NUMLOCK = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_NUMLOCK),
    WINDOW_KEYSYM_KP_SLASH = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_SLASH),
    WINDOW_KEYSYM_KP_ASTERISK = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_ASTERISK),
    WINDOW_KEYSYM_KP_MINUS = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_MINUS),
    WINDOW_KEYSYM_KP_PLUS = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_PLUS),
    WINDOW_KEYSYM_KP_ENTER = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_ENTER),
    WINDOW_KEYSYM_KP_1 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_1),
    WINDOW_KEYSYM_KP_2 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_2),
    WINDOW_KEYSYM_KP_3 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_3),
    WINDOW_KEYSYM_KP_4 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_4),
    WINDOW_KEYSYM_KP_5 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_5),
    WINDOW_KEYSYM_KP_6 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_6),
    WINDOW_KEYSYM_KP_7 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_7),
    WINDOW_KEYSYM_KP_8 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_8),
    WINDOW_KEYSYM_KP_9 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_9),
    WINDOW_KEYSYM_KP_0 = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_KP_0),
    WINDOW_KEYSYM_LEFTCTRL = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_LEFTCTRL),
    WINDOW_KEYSYM_LEFTSHIFT = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_LEFTSHIFT),
    WINDOW_KEYSYM_LEFTALT = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_LEFTALT),
    WINDOW_KEYSYM_LEFTGUI = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_LEFTGUI),
    WINDOW_KEYSYM_RIGHTCTRL = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_RIGHTCTRL),
    WINDOW_KEYSYM_RIGHTSHIFT = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_RIGHTSHIFT),
    WINDOW_KEYSYM_RIGHTALT = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_RIGHTALT),
    WINDOW_KEYSYM_RIGHTGUI = WINDOW_KEYCODE_TO_KEYSYM(WINDOW_KEYCODE_RIGHTGUI),

    /* ... */

/* }}} */

};


/* WINDOW_KEYMOD:
 *  Valid key modifiers (solo + combined)
 * * * * * * * * * * * * * * * * * * * * */
enum {
    WINDOW_KEYMOD_NONE = 0x0000,
    WINDOW_KEYMOD_LEFTCTRL = 0x0001,
    WINDOW_KEYMOD_LEFTSHIFT = 0x0002,
    WINDOW_KEYMOD_LEFTALT = 0x0004,
    WINDOW_KEYMOD_LEFTGUI = 0x0008,
    WINDOW_KEYMOD_RIGHTCTRL = 0x0010,
    WINDOW_KEYMOD_RIGHTSHIFT = 0x0020,
    WINDOW_KEYMOD_RIGHTALT = 0x0010,
    WINDOW_KEYMOD_RIGHTGUI = 0x0020,
    WINDOW_KEYMOD_NUMLOCK = 0x0100,
    WINDOW_KEYMOD_SCROLLLOCK = 0x0200,
    WINDOW_KEYMOD_MODE = 0x0400,
    WINDOW_KEYMOD_CAPSLOCK = 0x0800,
    WINDOW_KEYMOD_CTRL = (WINDOW_KEYMOD_LEFTCTRL | WINDOW_KEYMOD_RIGHTCTRL),
    WINDOW_KEYMOD_SHIFT = (WINDOW_KEYMOD_LEFTSHIFT | WINDOW_KEYMOD_RIGHTSHIFT),
    WINDOW_KEYMOD_ALT = (WINDOW_KEYMOD_LEFTALT | WINDOW_KEYMOD_RIGHTALT),
    WINDOW_KEYMOD_GUI = (WINDOW_KEYMOD_LEFTGUI | WINDOW_KEYMOD_RIGHTGUI),
    
    /* ... */

};


enum {
    WINDOW_CURSOR_MODE_NORMAL = 0,
    WINDOW_CURSOR_MODE_HIDDEN,
    WINDOW_CURSOR_MODE_CAPTURED,
    WINDOW_CURSOR_MODE_CENTERED,
    WINDOW_CURSOR_MODE_DISABLED,
};


enum {

    WINDOW_EVENT_NONE = 0,
    WINDOW_EVENT_QUIT = 0x1000,
    WINDOW_EVENT_MOUSE = 0x2000,
    WINDOW_EVENT_MOUSE_MOTION,
    WINDOW_EVENT_MOUSE_BUTTON,
    WINDOW_EVENT_MOUSE_SCROLL,
    WINDOW_EVENT_MOUSE_DEVICE = 0x2500,
    WINDOW_EVENT_MOUSE_ADDED,
    WINDOW_EVENT_MOUSE_REMOVED,
    WINDOW_EVENTBOARD = 0x3000,
    WINDOW_EVENT_KEYBOARD_KEY,
    WINDOW_EVENT_KEYBOARD_DEVICE = 0x3500,
    WINDOW_EVENT_KEYBOARD_ADDED,
    WINDOW_EVENT_KEYBOARD_REMOVED,
    WINDOW_EVENT_WINDOW = 0x4000,
    WINDOW_EVENT_WINDOW_CREATE,
    WINDOW_EVENT_WINDOW_DESTROY,
    WINDOW_EVENT_WINDOW_MAP,
    WINDOW_EVENT_WINDOW_UNMAP,
    WINDOW_EVENT_WINDOW_RESIZE,
    WINDOW_EVENT_WINDOW_MOTION,
    WINDOW_EVENT_WINDOW_ENTER,
    WINDOW_EVENT_WINDOW_LEAVE,
    WINDOW_EVENT_WINDOW_MAXIMIZE,
    WINDOW_EVENT_WINDOW_MINIMIZE,
    WINDOW_EVENT_WINDOW_FULLSCREEN,
    WINDOW_EVENT_SELECTION = 0x5000,
    WINDOW_EVENT_SELECTION_COPY,
    WINDOW_EVENT_SELECTION_WRITE = WINDOW_EVENT_SELECTION_COPY,
    WINDOW_EVENT_SELECTION_PASTE,
    WINDOW_EVENT_SELECTION_READ = WINDOW_EVENT_SELECTION_PASTE,
    WINDOW_EVENT_SELECTION_CLEAR,
    
    /* ... */

    WINDOW_EVENT_USER = 0xf000,
};


enum {
    
    WINDOW_CLIENT_API = 0x00000010,
    WINDOW_API_NATIVE,
    WINDOW_API_OPENGL,
    WINDOW_API_OPENGLES,
    WINDOW_API_VULKAN,
    WINDOW_API_DIRECTX,
    WINDOW_API_METAL,

    /* ... */

};


enum {
    WINDOW_GL_NONE = 0,

    WINDOW_GL_RED,
    WINDOW_GL_GREEN,
    WINDOW_GL_BLUE,
    WINDOW_GL_ALPHA,
    WINDOW_GL_DEPTH,
    WINDOW_GL_STENCIL,
    
    WINDOW_GL_DOUBLEBUFFER,

    WINDOW_GL_CONTEXT_VERSION_MAJOR,
    WINDOW_GL_CONTEXT_VERSION_MINOR,
   
    /* 'WINDOW_GL_CONTEXT_PROFILE_' values matches how GLX, EGL and WGL match their 'CORE' and 'COMPATIBILITY' profiles */
    WINDOW_GL_CONTEXT_PROFILE,
    WINDOW_GL_CONTEXT_PROFILE_CORE          = 0x00000001,
    WINDOW_GL_CONTEXT_PROFILE_COMPATIBILITY = 0x00000002,
    
    /* ... */
};


enum {
    WINDOW_SELECTION_PRIMARY = 1,
    WINDOW_SELECTION_SECONDARY,
    WINDOW_SELECTION_CLIPBOARD
};


typedef void *library_t;


typedef void *window_t;


typedef void *context_t;


typedef void *cursor_t;


typedef struct event_common_s event_common_t;

struct event_common_s {
    uint32_t type;
    uint64_t time;
    window_t window;
};


typedef struct event_quit_s event_quit_t;

struct event_quit_s {
    uint32_t type;
    uint64_t time;
    window_t window;
};


typedef struct event_mouse_s event_mouse_t;

struct event_mouse_s {
    uint32_t type;
    uint64_t time;
    window_t window;

    struct {
        int32_t x;
        int32_t y;
    } motion;

    struct {
        uint8_t btn;
        uint8_t state;
    } input;

    struct {
        int32_t x;
        int32_t y;
    } scroll;
};


typedef struct event_mouseDevice_s event_mouseDevice_t;

struct event_mouseDevice_s {
    uint32_t type;
    uint64_t time;
    window_t window;
};


typedef struct event_keyboard_s event_keyboard_t;

struct event_keyboard_s {
    uint32_t type;
    uint64_t time;
    window_t window;
    
    uint32_t keysym;
    uint32_t keycode;
    uint32_t keymod;
    uint32_t keyraw;
    uint8_t  state;
    uint8_t  repeat;
};


typedef struct event_keyboardDevice_s event_keyboardDevice_t;

struct event_keyboardDevice_s {
    uint32_t type;
    uint64_t time;
    window_t window;
};


typedef struct event_window_s event_window_t;

struct event_window_s {
    uint32_t type;
    uint64_t time;
    window_t window;

    uint32_t data1;
    uint32_t data2;
};


typedef struct event_selection_s event_selection_t;

struct event_selection_s {
    uint32_t type;
    uint64_t time;
    window_t window;

    void  *data;
    size_t size;
    uint32_t selection;
};


typedef union event_u event_t;

union event_u {
    uint32_t type;
    event_common_t      common;
    event_quit_t        quit;
    event_mouse_t       mouse;
    event_keyboard_t    keyboard;
    event_window_t      window;
    event_selection_t   clipboard;
};


/* platform functions */

WINDEF int win_init(library_t *);

WINDEF int win_quit(library_t);

WINDEF int win_set_hints(library_t, const uint32_t, const int32_t);

/* windowing functions */

WINDEF int win_window_create(library_t, window_t *, const size_t, const size_t, const char *);

WINDEF int win_window_destroy(library_t, window_t);

WINDEF int win_window_set_attributes(library_t, window_t, const uint32_t);

WINDEF int win_window_map(library_t, window_t);

WINDEF int win_window_unmap(library_t, window_t);

WINDEF int win_window_get_size(library_t, window_t, size_t *, size_t *);

WINDEF int win_window_set_size(library_t, window_t, const size_t, const size_t);

WINDEF int win_window_set_size_min(library_t, window_t, const size_t, const size_t);

WINDEF int win_window_set_size_max(library_t, window_t, const size_t, const size_t);

WINDEF int win_window_get_position(library_t, window_t, size_t *, size_t *);

WINDEF int win_window_set_position(library_t, window_t, const size_t, const size_t);

WINDEF int win_window_get_title(library_t, window_t, char **);

WINDEF int win_window_set_title(library_t, window_t, const char *);

WINDEF int win_window_get_context(library_t, window_t, context_t *);

WINDEF int win_window_set_context(library_t, window_t, context_t);

/* context functions */

WINDEF int win_context_create(library_t, context_t *, window_t);

WINDEF int win_context_destroy(library_t, context_t);

WINDEF int win_context_get_window(library_t, context_t, window_t *);

WINDEF int win_context_set_window(library_t, context_t, window_t);

/* opengl context functions */

WINDEF int win_gl_make_current(library_t, context_t);

WINDEF int win_gl_swap_buffers(library_t, context_t);

WINDEF int win_gl_swap_interval(library_t, context_t, const int);

WINDEF void *win_gl_get_proc_address(const char *);

/* cursor functions */

WINDEF int win_cursor_create(library_t, cursor_t *, const uint8_t *, const size_t, const size_t, const int, const int);

WINDEF int win_cursor_destroy(library_t, cursor_t);

WINDEF int win_cursor_get_position(library_t, window_t, size_t *, size_t *);

WINDEF int win_cursor_set_position(library_t, window_t, const size_t, const size_t);

WINDEF int win_cursor_set_position_center(library_t, window_t);

WINDEF int win_cursor_get_mode(library_t, window_t, uint32_t *);

WINDEF int win_cursor_set_mode(library_t, window_t, const uint32_t);

/* event functions */

WINDEF int win_event_poll(library_t, event_t *);

WINDEF int win_event_wait(library_t, event_t *);

WINDEF int win_event_push(library_t, event_t *);

WINDEF int win_event_pop(library_t, event_t *);

WINDEF int win_event_send(library_t, window_t, uint32_t, ...);

WINDEF int win_event_head(library_t, event_t *);

/* clipboard functions */

WINDEF int win_copy(library_t, const uint32_t, const void *, const size_t);

WINDEF int win_paste(library_t, const uint32_t, void **, size_t *);

/* timing functions */

WINDEF uint64_t win_time_get(void);

WINDEF int win_time_wait(uint64_t);

#endif /* _window_h_ */
#
#if defined (WINDOW_IMPLEMENTATION)
#
# /* include headers */
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h> 
# include <assert.h>
# include <string.h>
#
# /* include unix headers */
# if defined (WINDOW_PLATFORM_LINUX) || \
      defined (WINDOW_PLATFORM_APPLE) || \
      defined (WINDOW_PLATFORM_BSD)
#  include <dlfcn.h>
#  include <unistd.h>
#  include <sys/time.h>
#
# /* include win32 headers */
# elif defined (WINDOW_BACKEND_WIN32)
#  include <windows.h>
#
# else
#  error /* invalid platform */
# endif
#
# /* include X11 headers */
# if defined (WINDOW_BACKEND_X11)
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
#  include <X11/Xatom.h>
#  include <X11/XKBlib.h>
#  include <X11/keysym.h>
#  include <X11/keysymdef.h>
#
# /* include wayland headers */
# elif defined (WINDOW_BACKEND_WAYLAND)
#  include <wayland-util.h>
#  include <wayland-version.h>
#  include <wayland-client.h>
#  include <wayland-client-core.h>
#  include <wayland-client-protocol.h>
#
# /* include win32 headers */
# elif defined (WINDOW_BACKEND_WIN32)
#  include <windows.h>
#
# else
#  error /* invalid backend */
# endif

/* window.h definition layer */
/* {{{ */

/* _window_h_event: event queue struct */
struct _window_h_event;

/* _window_h_selection: copy'n'paste selection struct */
struct _window_h_selection;

/* _window_h_platform: platform structure containing API callbacks */
struct _window_h_platform;

/* _window_h_hints: window and context configuration hints */
struct _window_h_hints;

/* _window_h_error: library's error struct */
struct _window_h_error;

/* _window_h_window: generic, type-agnostic window struct */
struct _window_h_window;

/* __context_h_context: generic, type-agnostic context struct */
struct _window_h_context;

/* __cursor_h_cursor: generic, type-agnostic cursor struct */
struct _window_h_cursor;


/* _window_h: global window.h struct */
struct _window_h;


struct _window_h_event {
    void *next;
    event_t event;
};


struct _window_h_selection {
    struct {
        void  *data;
        size_t size;
    } primary;
    
    struct {
        void  *data;
        size_t size;
    } secondary;
    
    struct {
        void  *data;
        size_t size;
    } clipboard;
};


struct _window_h_platform {
    uint32_t id; /* ID of the platform */
   
    /* library functions */

    int (*init) (struct _window_h *);
    int (*load) (struct _window_h *);
    int (*quit) (struct _window_h *);
    int (*unload) (struct _window_h *);

    /* window functions */

    int (*window_create) (struct _window_h *, struct _window_h_window *, const size_t, const size_t, const char *);
    int (*window_destroy) (struct _window_h *, struct _window_h_window *);
    int (*window_update_flags) (struct _window_h *, struct _window_h_window *);
    int (*window_map) (struct _window_h *, struct _window_h_window *);
    int (*window_unmap) (struct _window_h *, struct _window_h_window *);
    int (*window_get_size) (struct _window_h *, struct _window_h_window *, size_t *, size_t *);
    int (*window_set_size) (struct _window_h *, struct _window_h_window *, const size_t, const size_t);
    int (*window_set_size_min) (struct _window_h *, struct _window_h_window *, const size_t, const size_t);
    int (*window_set_size_max) (struct _window_h *, struct _window_h_window *, const size_t, const size_t);
    int (*window_get_position) (struct _window_h *, struct _window_h_window *, size_t *, size_t *);
    int (*window_set_position) (struct _window_h *, struct _window_h_window *, const size_t, const size_t);
    int (*window_get_title) (struct _window_h *, struct _window_h_window *, char **);
    int (*window_set_title) (struct _window_h *, struct _window_h_window *, const char *);

    /* context functions */

    int (*context_create) (struct _window_h *, struct _window_h_context *, struct _window_h_window *);
    int (*context_destroy) (struct _window_h *, struct _window_h_context *);

    /* cursor functions */

    int (*cursor_create) (struct _window_h *, struct _window_h_cursor *, const uint8_t *, const size_t, const size_t, const int, const int);
    int (*cursor_destroy) (struct _window_h *, struct _window_h_cursor *);
    int (*cursor_get_position) (struct _window_h *, struct _window_h_window *, size_t *, size_t *);
    int (*cursor_set_position) (struct _window_h *, struct _window_h_window *, const size_t, const size_t);
    int (*cursor_set_mode) (struct _window_h *, struct _window_h_window *, const uint32_t);

    /* event functions */

    int (*event_poll) (struct _window_h *);
    int (*event_wait) (struct _window_h *);

    /* clipboard functions */

    int (*copy) (struct _window_h *, const uint32_t, const void *, const size_t);
    int (*paste) (struct _window_h *, const uint32_t, void **, size_t *);

    /* opengl context functions */

    int (*gl_init) (struct _window_h *, void *);
    int (*gl_load) (struct _window_h *);
    int (*gl_unload) (struct _window_h *);
    int (*gl_context_create) (struct _window_h *, struct _window_h_context *, struct _window_h_window *);
    int (*gl_context_destroy) (struct _window_h *, struct _window_h_context *);
    int (*gl_make_current) (struct _window_h *, struct _window_h_context *);
    int (*gl_swap_buffers) (struct _window_h *, struct _window_h_context *);
    int (*gl_swap_interval) (struct _window_h *, struct _window_h_context *, const int);
    int (*gl_choose_config) (struct _window_h *);
    int (*gl_get_visual) (struct _window_h *, int *);
};


struct _window_h_error {
    struct _window_h_error *next;
    uint32_t code;
};


struct _window_h_window_x11;

struct _window_h_window_win32;

struct _window_h_window {

    /* pointer to the 'next' node in linked-list of window */
    struct _window_h_window *next;


    struct {
        /* 'handle' to this window's context */
        struct _window_h_context *handle;
    } context;


    struct {
        /* 'handle' to this window's cursor */
        struct _window_h_cursor *handle;

        struct {
            /* delta accumulation vector */
            struct {
                int32_t x;
                int32_t y;
            } accum;

            /* last position vector */
            struct {
                int32_t x;
                int32_t y;
            } last;

            /* cursor 'mode' */
            uint32_t mode;

            /* 'warp' pending boolean */
            uint8_t warp;
        } attrib;
    } cursor;


    /* numeric handle to the window instance */
    uint64_t handle;


    struct _window_h_window_x11 *x11;

    struct _window_h_window_win32 *win32;


    /* struct of window attributes */
    struct {
        /* window frame size vector */
        struct {
            int32_t x;
            int32_t y;
        } size;
        
        /* window frame position vector */
        struct {
            int32_t x;
            int32_t y;
        } position ;

        uint32_t api;

        uint8_t mapped;

        uint8_t resizable;

        uint8_t focused;

        uint8_t maximized;

        uint8_t minimized;

        uint8_t fullscreen;
    } attrib;

};


struct _window_h_context_x11;

struct _window_h_context_win32;

struct _window_h_context_egl;

struct _window_h_context_wgl;

struct _window_h_context {

    /* pointer to the 'next' node in linked-list of context */
    struct _window_h_context *next;

    struct {
        struct _window_h_window *current;
    } window;

    struct {
        uint32_t api;
    } attrib;


    /* WINDOW_API_NATIVE */
    struct _window_h_context_x11 *x11;

    /* WINDOW_API_NATIVE */
    struct _window_h_context_win32 *win32;

    /* WINDOW_API_OPENGL */
    struct _window_h_context_glx *glx;

    /* WINDOW_API_OPENGL */
    struct _window_h_context_egl *egl;

    /* WINDOW_API_OPENGL */
    struct _window_h_context_wgl *wgl;

};


struct _window_h_cursor_x11;

struct _window_h_cursor_win32;

struct _window_h_cursor {

    /* pointer to the 'next' node in linked-list of cursor */
    struct _window_h_cursor *next;


    /* numeric handle to the cursor instance */
    uint64_t handle;


    struct _window_h_cursor_x11 *x11;

    struct _window_h_cursor_win32 *win32;
};


struct _window_h_x11;

struct _window_h_win32;

struct _window_h_glx;

struct _window_h_egl;

struct _window_h_wgl;

struct _window_h {

    /* connection handle */
    void *handle;

    struct {
        /* linked-list of all the created windows */
        struct _window_h_window *list;
    } window;

    struct {
        /* linked-list of all the created contexts */
        struct _window_h_context *list;
    } context;

    struct {
        /* linked-list of all the created cursors */
        struct _window_h_cursor *list;

        /* handle to 'blank' cursor handle */
        struct _window_h_cursor *blank;
    } cursor;

    struct {
        /* linked-list'ish queue of events processed by program */
        struct _window_h_event *queue;
    } event;

    struct {
        uint32_t api;

        struct {
            /* resizable boolean */
            uint8_t resize;
        
            /* decorations boolean */
            uint8_t decor;
        } window;

        struct {
            /* 'red' channel size */
            uint32_t red;
            
            /* 'green' channel size */
            uint32_t green;
            
            /* 'blue' channel size */
            uint32_t blue;
            
            /* 'alpha' channel size */
            uint32_t alpha;
            
            /* 'depth' buffer size */
            uint32_t depth;
            
            /* 'stencil' buffer size */
            uint32_t stencil;

            /* doublebuffer boolean */
            uint8_t dblbuf;

            /* 'major' OpenGL version */
            uint8_t major;

            /* 'minor' OpenGL version */
            uint8_t minor;
            
            /* OpenGL 'profile' */
            uint8_t profile;
        } gl;
    } hints;

    /* selections */
    struct _window_h_selection selection;

    /* platform */
    struct _window_h_platform platform;

    /* x11-implementation of window.h */
    struct _window_h_x11 *x11;

    /* win32-implementation of window.h */
    struct _window_h_win32 *win32;

    /* glx-implementation of window.h */
    struct _window_h_glx *glx;

    /* egl-implementation of window.h */
    struct _window_h_egl *egl;

    /* wgl-implementation of window.h */
    struct _window_h_wgl *wgl;

    /* ... */

};

/* }}} */

# /* WINDOW_BACKEND_GLX - GLX definitions layer */
# if defined (WINDOW_BACKEND_GLX)
/* {{{ */

/* {{{ */

typedef struct __GLXcontextRec *GLXContext;
typedef XID GLXPixmap;
typedef XID GLXDrawable;
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXFBConfigID;
typedef XID GLXContextID;
typedef XID GLXWindow;
typedef XID GLXPbuffer;

typedef XID GLXContextID;
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXWindow;
typedef XID GLXPbuffer;

typedef void ( *__GLXextFuncPtr)(void);

/* }}} */
/* {{{ */

#  define GLX_VERSION_1_1 1
#  define GLX_VERSION_1_2 1
#  define GLX_VERSION_1_3 1
#  define GLX_VERSION_1_4 1
#  define GLX_EXTENSION_NAME "GLX"
#  define GLX_USE_GL 1
#  define GLX_BUFFER_SIZE 2
#  define GLX_LEVEL 3
#  define GLX_RGBA 4
#  define GLX_DOUBLEBUFFER 5
#  define GLX_STEREO 6
#  define GLX_AUX_BUFFERS 7
#  define GLX_RED_SIZE 8
#  define GLX_GREEN_SIZE 9
#  define GLX_BLUE_SIZE 10
#  define GLX_ALPHA_SIZE 11
#  define GLX_DEPTH_SIZE 12
#  define GLX_STENCIL_SIZE 13
#  define GLX_ACCUM_RED_SIZE 14
#  define GLX_ACCUM_GREEN_SIZE 15
#  define GLX_ACCUM_BLUE_SIZE 16
#  define GLX_ACCUM_ALPHA_SIZE 17
#  define GLX_BAD_SCREEN 1
#  define GLX_BAD_ATTRIBUTE 2
#  define GLX_NO_EXTENSION 3
#  define GLX_BAD_VISUAL 4
#  define GLX_BAD_CONTEXT 5
#  define GLX_BAD_VALUE 6
#  define GLX_BAD_ENUM 7
#  define GLX_VENDOR 1
#  define GLX_VERSION 2
#  define GLX_EXTENSIONS 3
#  define GLX_CONFIG_CAVEAT 0x20
#  define GLX_DONT_CARE 0xffffffff
#  define GLX_X_VISUAL_TYPE 0x22
#  define GLX_TRANSPARENT_TYPE 0x23
#  define GLX_TRANSPARENT_INDEX_VALUE 0x24
#  define GLX_TRANSPARENT_RED_VALUE 0x25
#  define GLX_TRANSPARENT_GREEN_VALUE 0x26
#  define GLX_TRANSPARENT_BLUE_VALUE 0x27
#  define GLX_TRANSPARENT_ALPHA_VALUE 0x28
#  define GLX_WINDOW_BIT 0x00000001
#  define GLX_PIXMAP_BIT 0x00000002
#  define GLX_PBUFFER_BIT 0x00000004
#  define GLX_AUX_BUFFERS_BIT 0x00000010
#  define GLX_FRONT_LEFT_BUFFER_BIT 0x00000001
#  define GLX_FRONT_RIGHT_BUFFER_BIT 0x00000002
#  define GLX_BACK_LEFT_BUFFER_BIT 0x00000004
#  define GLX_BACK_RIGHT_BUFFER_BIT 0x00000008
#  define GLX_DEPTH_BUFFER_BIT 0x00000020
#  define GLX_STENCIL_BUFFER_BIT 0x00000040
#  define GLX_ACCUM_BUFFER_BIT 0x00000080
#  define GLX_NONE 0x8000
#  define GLX_SLOW_CONFIG 0x8001
#  define GLX_TRUE_COLOR 0x8002
#  define GLX_DIRECT_COLOR 0x8003
#  define GLX_PSEUDO_COLOR 0x8004
#  define GLX_STATIC_COLOR 0x8005
#  define GLX_GRAY_SCALE 0x8006
#  define GLX_STATIC_GRAY 0x8007
#  define GLX_TRANSPARENT_RGB 0x8008
#  define GLX_TRANSPARENT_INDEX 0x8009
#  define GLX_VISUAL_ID 0x800b
#  define GLX_SCREEN 0x800c
#  define GLX_NON_CONFORMANT_CONFIG 0x800d
#  define GLX_DRAWABLE_TYPE 0x8010
#  define GLX_RENDER_TYPE 0x8011
#  define GLX_X_RENDERABLE 0x8012
#  define GLX_FBCONFIG_ID 0x8013
#  define GLX_RGBA_TYPE 0x8014
#  define GLX_COLOR_INDEX_TYPE 0x8015
#  define GLX_MAX_PBUFFER_WIDTH 0x8016
#  define GLX_MAX_PBUFFER_HEIGHT 0x8017
#  define GLX_MAX_PBUFFER_PIXELS 0x8018
#  define GLX_PRESERVED_CONTENTS 0x801b
#  define GLX_LARGEST_PBUFFER 0x801c
#  define GLX_WIDTH 0x801d
#  define GLX_HEIGHT 0x801e
#  define GLX_EVENT_MASK 0x801f
#  define GLX_DAMAGED 0x8020
#  define GLX_SAVED 0x8021
#  define GLX_WINDOW 0x8022
#  define GLX_PBUFFER 0x8023
#  define GLX_PBUFFER_HEIGHT 0x8040
#  define GLX_PBUFFER_WIDTH 0x8041
#  define GLX_RGBA_BIT 0x00000001
#  define GLX_COLOR_INDEX_BIT 0x00000002
#  define GLX_PBUFFER_CLOBBER_MASK 0x08000000
#  define GLX_WINDOW_BIT 0x00000001
#  define GLX_PIXMAP_BIT 0x00000002
#  define GLX_PBUFFER_BIT 0x00000004
#  define GLX_RGBA_BIT 0x00000001
#  define GLX_COLOR_INDEX_BIT 0x00000002
#  define GLX_PBUFFER_CLOBBER_MASK 0x08000000
#  define GLX_FRONT_LEFT_BUFFER_BIT 0x00000001
#  define GLX_FRONT_RIGHT_BUFFER_BIT 0x00000002
#  define GLX_BACK_LEFT_BUFFER_BIT 0x00000004
#  define GLX_BACK_RIGHT_BUFFER_BIT 0x00000008
#  define GLX_AUX_BUFFERS_BIT 0x00000010
#  define GLX_DEPTH_BUFFER_BIT 0x00000020
#  define GLX_STENCIL_BUFFER_BIT 0x00000040
#  define GLX_ACCUM_BUFFER_BIT 0x00000080
#  define GLX_CONFIG_CAVEAT 0x20
#  define GLX_X_VISUAL_TYPE 0x22
#  define GLX_TRANSPARENT_TYPE 0x23
#  define GLX_TRANSPARENT_INDEX_VALUE 0x24
#  define GLX_TRANSPARENT_RED_VALUE 0x25
#  define GLX_TRANSPARENT_GREEN_VALUE 0x26
#  define GLX_TRANSPARENT_BLUE_VALUE 0x27
#  define GLX_TRANSPARENT_ALPHA_VALUE 0x28
#  define GLX_DONT_CARE 0xffffffff
#  define GLX_NONE 0x8000
#  define GLX_SLOW_CONFIG 0x8001
#  define GLX_TRUE_COLOR 0x8002
#  define GLX_DIRECT_COLOR 0x8003
#  define GLX_PSEUDO_COLOR 0x8004
#  define GLX_STATIC_COLOR 0x8005
#  define GLX_GRAY_SCALE 0x8006
#  define GLX_STATIC_GRAY 0x8007
#  define GLX_TRANSPARENT_RGB 0x8008
#  define GLX_TRANSPARENT_INDEX 0x8009
#  define GLX_VISUAL_ID 0x800b
#  define GLX_SCREEN 0x800c
#  define GLX_NON_CONFORMANT_CONFIG 0x800d
#  define GLX_DRAWABLE_TYPE 0x8010
#  define GLX_RENDER_TYPE 0x8011
#  define GLX_X_RENDERABLE 0x8012
#  define GLX_FBCONFIG_ID 0x8013
#  define GLX_RGBA_TYPE 0x8014
#  define GLX_COLOR_INDEX_TYPE 0x8015
#  define GLX_MAX_PBUFFER_WIDTH 0x8016
#  define GLX_MAX_PBUFFER_HEIGHT 0x8017
#  define GLX_MAX_PBUFFER_PIXELS 0x8018
#  define GLX_PRESERVED_CONTENTS 0x801b
#  define GLX_LARGEST_PBUFFER 0x801c
#  define GLX_WIDTH 0x801d
#  define GLX_HEIGHT 0x801e
#  define GLX_EVENT_MASK 0x801f
#  define GLX_DAMAGED 0x8020
#  define GLX_SAVED 0x8021
#  define GLX_WINDOW 0x8022
#  define GLX_PBUFFER 0x8023
#  define GLX_PBUFFER_HEIGHT 0x8040
#  define GLX_PBUFFER_WIDTH 0x8041
#  define GLX_SAMPLE_BUFFERS 100000
#  define GLX_SAMPLES 100001
#  define GLX_CONTEXT_DEBUG_BIT_ARB 0x00000001
#  define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#  define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#  define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
#  define GLX_CONTEXT_FLAGS_ARB 0x2094
#  define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#  define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#  define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126

/* }}} */
/* {{{ */

typedef XVisualInfo *(* PFN_glXChooseVisual_PROC) (Display *, int, int *);
PFN_glXChooseVisual_PROC glXChooseVisual_PROC = 0;
#  define glXChooseVisual (assert(glXChooseVisual_PROC), glXChooseVisual_PROC)

typedef GLXContext (* PFN_glXCreateContext_PROC) (Display *, XVisualInfo *, GLXContext, int);
PFN_glXCreateContext_PROC glXCreateContext_PROC = 0;
#  define glXCreateContext (assert(glXCreateContext_PROC), glXCreateContext_PROC)

typedef void (* PFN_glXDestroyContext_PROC) (Display *, GLXContext);
PFN_glXDestroyContext_PROC glXDestroyContext_PROC = 0;
#  define glXDestroyContext (assert(glXDestroyContext_PROC), glXDestroyContext_PROC)

typedef int (* PFN_glXMakeCurrent_PROC) (Display *, GLXDrawable, GLXContext);
PFN_glXMakeCurrent_PROC glXMakeCurrent_PROC = 0;
#  define glXMakeCurrent (assert(glXMakeCurrent_PROC), glXMakeCurrent_PROC)

typedef void (* PFN_glXCopyContext_PROC) (Display *, GLXContext, GLXContext, unsigned long);
PFN_glXCopyContext_PROC glXCopyContext_PROC = 0;
#  define glXCopyContext (assert(glXCopyContext_PROC), glXCopyContext_PROC)

typedef void (* PFN_glXSwapBuffers_PROC) (Display *, GLXDrawable);
PFN_glXSwapBuffers_PROC glXSwapBuffers_PROC = 0;
#  define glXSwapBuffers (assert(glXSwapBuffers_PROC), glXSwapBuffers_PROC)

typedef GLXPixmap (* PFN_glXCreateGLXPixmap_PROC) (Display *, XVisualInfo *, Pixmap);
PFN_glXCreateGLXPixmap_PROC glXCreateGLXPixmap_PROC = 0;
#  define glXCreateGLXPixmap (assert(glXCreateGLXPixmap_PROC), glXCreateGLXPixmap_PROC)

typedef void (* PFN_glXDestroyGLXPixmap_PROC) (Display *, GLXPixmap);
PFN_glXDestroyGLXPixmap_PROC glXDestroyGLXPixmap_PROC = 0;
#  define glXDestroyGLXPixmap (assert(glXDestroyGLXPixmap_PROC), glXDestroyGLXPixmap_PROC)

typedef int (* PFN_glXQueryExtension_PROC) (Display *, int *, int *);
PFN_glXQueryExtension_PROC glXQueryExtension_PROC = 0;
#  define glXQueryExtension (assert(glXQueryExtension_PROC), glXQueryExtension_PROC)

typedef int (* PFN_glXQueryVersion_PROC) (Display *, int *, int *);
PFN_glXQueryVersion_PROC glXQueryVersion_PROC = 0;
#  define glXQueryVersion (assert(glXQueryVersion_PROC), glXQueryVersion_PROC)

typedef int (* PFN_glXIsDirect_PROC) (Display *, GLXContext);
PFN_glXIsDirect_PROC glXIsDirect_PROC = 0;
#  define glXIsDirect (assert(glXIsDirect_PROC), glXIsDirect_PROC)

typedef int (* PFN_glXGetConfig_PROC) (Display *, XVisualInfo *, int, int *);
PFN_glXGetConfig_PROC glXGetConfig_PROC = 0;
#  define glXGetConfig (assert(glXGetConfig_PROC), glXGetConfig_PROC)

typedef GLXContext (* PFN_glXGetCurrentContext_PROC) (void);
PFN_glXGetCurrentContext_PROC glXGetCurrentContext_PROC = 0;
#  define glXGetCurrentContext (assert(glXGetCurrentContext_PROC), glXGetCurrentContext_PROC)

typedef GLXDrawable (* PFN_glXGetCurrentDrawable_PROC) (void);
PFN_glXGetCurrentDrawable_PROC glXGetCurrentDrawable_PROC = 0;
#  define glXGetCurrentDrawable (assert(glXGetCurrentDrawable_PROC), glXGetCurrentDrawable_PROC)

typedef void (* PFN_glXWaitGL_PROC) (void);
PFN_glXWaitGL_PROC glXWaitGL_PROC = 0;
#  define glXWaitGL (assert(glXWaitGL_PROC), glXWaitGL_PROC)

typedef void (* PFN_glXWaitX_PROC) (void);
PFN_glXWaitX_PROC glXWaitX_PROC = 0;
#  define glXWaitX (assert(glXWaitX_PROC), glXWaitX_PROC)

typedef void (* PFN_glXUseXFont_PROC) (Font, int, int, int);
PFN_glXUseXFont_PROC glXUseXFont_PROC = 0;
#  define glXUseXFont (assert(glXUseXFont_PROC), glXUseXFont_PROC)

typedef const char *(* PFN_glXQueryExtensionsString_PROC) (Display *, int);
PFN_glXQueryExtensionsString_PROC glXQueryExtensionsString_PROC = 0;
#  define glXQueryExtensionsString (assert(glXQueryExtensionsString_PROC), glXQueryExtensionsString_PROC)

typedef const char *(* PFN_glXQueryServerString_PROC) (Display *, int, int);
PFN_glXQueryServerString_PROC glXQueryServerString_PROC = 0;
#  define glXQueryServerString (assert(glXQueryServerString_PROC), glXQueryServerString_PROC)

typedef const char *(* PFN_glXGetClientString_PROC) (Display *, int);
PFN_glXGetClientString_PROC glXGetClientString_PROC = 0;
#  define glXGetClientString (assert(glXGetClientString_PROC), glXGetClientString_PROC)

typedef Display *(* PFN_glXGetCurrentDisplay_PROC) (void);
PFN_glXGetCurrentDisplay_PROC glXGetCurrentDisplay_PROC = 0;
#  define glXGetCurrentDisplay (assert(glXGetCurrentDisplay_PROC), glXGetCurrentDisplay_PROC)

typedef GLXFBConfig *(* PFN_glXChooseFBConfig_PROC) (Display *, int, const int *, int *);
PFN_glXChooseFBConfig_PROC glXChooseFBConfig_PROC = 0;
#  define glXChooseFBConfig (assert(glXChooseFBConfig_PROC), glXChooseFBConfig_PROC)

typedef int (* PFN_glXGetFBConfigAttrib_PROC) (Display *, GLXFBConfig, int, int *);
PFN_glXGetFBConfigAttrib_PROC glXGetFBConfigAttrib_PROC = 0;
#  define glXGetFBConfigAttrib (assert(glXGetFBConfigAttrib_PROC), glXGetFBConfigAttrib_PROC)

typedef GLXFBConfig *(* PFN_glXGetFBConfigs_PROC) (Display *, int, int *);
PFN_glXGetFBConfigs_PROC glXGetFBConfigs_PROC = 0;
#  define glXGetFBConfigs (assert(glXGetFBConfigs_PROC), glXGetFBConfigs_PROC)

typedef XVisualInfo *(* PFN_glXGetVisualFromFBConfig_PROC) (Display *, GLXFBConfig);
PFN_glXGetVisualFromFBConfig_PROC glXGetVisualFromFBConfig_PROC = 0;
#  define glXGetVisualFromFBConfig (assert(glXGetVisualFromFBConfig_PROC), glXGetVisualFromFBConfig_PROC)

typedef GLXWindow (* PFN_glXCreateWindow_PROC) (Display *, GLXFBConfig, Window, const int *);
PFN_glXCreateWindow_PROC glXCreateWindow_PROC = 0;
#  define glXCreateWindow (assert(glXCreateWindow_PROC), glXCreateWindow_PROC)

typedef void (* PFN_glXDestroyWindow_PROC) (Display *, GLXWindow);
PFN_glXDestroyWindow_PROC glXDestroyWindow_PROC = 0;
#  define glXDestroyWindow (assert(glXDestroyWindow_PROC), glXDestroyWindow_PROC)

typedef GLXPixmap (* PFN_glXCreatePixmap_PROC) (Display *, GLXFBConfig, Pixmap, const int *);
PFN_glXCreatePixmap_PROC glXCreatePixmap_PROC = 0;
#  define glXCreatePixmap (assert(glXCreatePixmap_PROC), glXCreatePixmap_PROC)

typedef void (* PFN_glXDestroyPixmap_PROC) (Display *, GLXPixmap);
PFN_glXDestroyPixmap_PROC glXDestroyPixmap_PROC = 0;
#  define glXDestroyPixmap (assert(glXDestroyPixmap_PROC), glXDestroyPixmap_PROC)

typedef GLXPbuffer (* PFN_glXCreatePbuffer_PROC) (Display *, GLXFBConfig, const int *);
PFN_glXCreatePbuffer_PROC glXCreatePbuffer_PROC = 0;
#  define glXCreatePbuffer (assert(glXCreatePbuffer_PROC), glXCreatePbuffer_PROC)

typedef void (* PFN_glXDestroyPbuffer_PROC) (Display *, GLXPbuffer);
PFN_glXDestroyPbuffer_PROC glXDestroyPbuffer_PROC = 0;
#  define glXDestroyPbuffer (assert(glXDestroyPbuffer_PROC), glXDestroyPbuffer_PROC)

typedef void (* PFN_glXQueryDrawable_PROC) (Display *, GLXDrawable, int, unsigned int *);
PFN_glXQueryDrawable_PROC glXQueryDrawable_PROC = 0;
#  define glXQueryDrawable (assert(glXQueryDrawable_PROC), glXQueryDrawable_PROC)

typedef GLXContext (* PFN_glXCreateNewContext_PROC) (Display *, GLXFBConfig, int, GLXContext, int);
PFN_glXCreateNewContext_PROC glXCreateNewContext_PROC = 0;
#  define glXCreateNewContext (assert(glXCreateNewContext_PROC), glXCreateNewContext_PROC)

typedef int (* PFN_glXMakeContextCurrent_PROC) (Display *, GLXDrawable, GLXDrawable, GLXContext);
PFN_glXMakeContextCurrent_PROC glXMakeContextCurrent_PROC = 0;
#  define glXMakeContextCurrent (assert(glXMakeContextCurrent_PROC), glXMakeContextCurrent_PROC)

typedef GLXDrawable (* PFN_glXGetCurrentReadDrawable_PROC) (void);
PFN_glXGetCurrentReadDrawable_PROC glXGetCurrentReadDrawable_PROC = 0;
#  define glXGetCurrentReadDrawable (assert(glXGetCurrentReadDrawable_PROC), glXGetCurrentReadDrawable_PROC)

typedef int (* PFN_glXQueryContext_PROC) (Display *, GLXContext, int, int *);
PFN_glXQueryContext_PROC glXQueryContext_PROC = 0;
#  define glXQueryContext (assert(glXQueryContext_PROC), glXQueryContext_PROC)

typedef void (* PFN_glXSelectEvent_PROC) (Display *, GLXDrawable, unsigned long);
PFN_glXSelectEvent_PROC glXSelectEvent_PROC = 0;
#  define glXSelectEvent (assert(glXSelectEvent_PROC), glXSelectEvent_PROC)

typedef void (* PFN_glXGetSelectedEvent_PROC) (Display *, GLXDrawable, unsigned long *);
PFN_glXGetSelectedEvent_PROC glXGetSelectedEvent_PROC = 0;
#  define glXGetSelectedEvent (assert(glXGetSelectedEvent_PROC), glXGetSelectedEvent_PROC)

typedef __GLXextFuncPtr (* PFN_glXGetProcAddressARB_PROC) (const unsigned char *);
PFN_glXGetProcAddressARB_PROC glXGetProcAddressARB_PROC = 0;
#  define glXGetProcAddressARB (assert(glXGetProcAddressARB_PROC), glXGetProcAddressARB_PROC)

typedef __GLXextFuncPtr (* PFN_glXGetProcAddress_PROC) (const unsigned char *);
PFN_glXGetProcAddress_PROC glXGetProcAddress_PROC = 0;
#  define glXGetProcAddress (assert(glXGetProcAddress_PROC), glXGetProcAddress_PROC)

typedef GLXContext (* PFN_glXCreateContextAttribsARB_PROC) (Display *, GLXFBConfig, GLXContext, Bool, const int *);
PFN_glXCreateContextAttribsARB_PROC glXCreateContextAttribsARB_PROC = 0;
#  define glXCreateContextAttribsARB (assert(glXCreateContextAttribsARB_PROC), glXCreateContextAttribsARB_PROC)

typedef void (* PFN_glXSwapIntervalEXT_PROC) (Display *, GLXDrawable, int);
PFN_glXSwapIntervalEXT_PROC glXSwapIntervalEXT_PROC = 0;
#  define glXSwapIntervalEXT (assert(glXSwapIntervalEXT_PROC), glXSwapIntervalEXT_PROC)

/* }}} */

typedef struct _window_h_context_glx *context_t_glx;

struct _window_h_context_glx {
    GLXWindow  window;
    GLXContext context;
};


typedef struct _window_h_glx *_window_h_glx;

struct _window_h_glx {
    /* handle do shared object */
    void *handle;

    /* handle to X11's display object */
    Display *dpy;

    /* best GLXFBConfig object */
    GLXFBConfig fbconfig;
    
    struct {
        /* config hints */
        int *config;
        
        /* context hints */
        int *context;
    } attr;
};

/* }}} */
# endif /* WINDOW_BACKEND_GLX */
#
# /* WINDOW_BACKEND_EGL - EGL definitions layer */
# if defined (WINDOW_BACKEND_EGL)
/* {{{ */

/* {{{ */

typedef void *EGLNativeDisplayType;
typedef uint64_t EGLNativePixmapType;
typedef uint64_t EGLNativeWindowType;

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

/* }}} */
/* {{{ */

#  define EGL_ALPHA_SIZE 0x3021
#  define EGL_BAD_ACCESS 0x3002
#  define EGL_BAD_ALLOC 0x3003
#  define EGL_BAD_ATTRIBUTE 0x3004
#  define EGL_BAD_CONFIG 0x3005
#  define EGL_BAD_CONTEXT 0x3006
#  define EGL_BAD_CURRENT_SURFACE 0x3007
#  define EGL_BAD_DISPLAY 0x3008
#  define EGL_BAD_MATCH 0x3009
#  define EGL_BAD_NATIVE_PIXMAP 0x300A
#  define EGL_BAD_NATIVE_WINDOW 0x300B
#  define EGL_BAD_PARAMETER 0x300C
#  define EGL_BAD_SURFACE 0x300D
#  define EGL_BLUE_SIZE 0x3022
#  define EGL_BUFFER_SIZE 0x3020
#  define EGL_CONFIG_CAVEAT 0x3027
#  define EGL_CONFIG_ID 0x3028
#  define EGL_CORE_NATIVE_ENGINE 0x305B
#  define EGL_DEPTH_SIZE 0x3025
#  define EGL_DONT_CARE ((int) -1)
#  define EGL_DRAW 0x3059
#  define EGL_EXTENSIONS 0x3055
#  define EGL_FALSE 0
#  define EGL_GREEN_SIZE 0x3023
#  define EGL_HEIGHT 0x3056
#  define EGL_LARGEST_PBUFFER 0x3058
#  define EGL_LEVEL 0x3029
#  define EGL_MAX_PBUFFER_HEIGHT 0x302A
#  define EGL_MAX_PBUFFER_PIXELS 0x302B
#  define EGL_MAX_PBUFFER_WIDTH 0x302C
#  define EGL_NATIVE_RENDERABLE 0x302D
#  define EGL_NATIVE_VISUAL_ID 0x302E
#  define EGL_NATIVE_VISUAL_TYPE 0x302F
#  define EGL_NONE 0x3038
#  define EGL_NON_CONFORMANT_CONFIG 0x3051
#  define EGL_NOT_INITIALIZED 0x3001
#  define EGL_NO_CONTEXT ((EGLContext) 0)
#  define EGL_NO_DISPLAY ((EGLDisplay) 0)
#  define EGL_NO_SURFACE ((EGLSurface) 0)
#  define EGL_PBUFFER_BIT 0x0001
#  define EGL_PIXMAP_BIT 0x0002
#  define EGL_READ 0x305A
#  define EGL_RED_SIZE 0x3024
#  define EGL_SAMPLES 0x3031
#  define EGL_SAMPLE_BUFFERS 0x3032
#  define EGL_SLOW_CONFIG 0x3050
#  define EGL_STENCIL_SIZE 0x3026
#  define EGL_SUCCESS 0x3000
#  define EGL_SURFACE_TYPE 0x3033
#  define EGL_TRANSPARENT_BLUE_VALUE 0x3035
#  define EGL_TRANSPARENT_GREEN_VALUE 0x3036
#  define EGL_TRANSPARENT_RED_VALUE 0x3037
#  define EGL_TRANSPARENT_RGB 0x3052
#  define EGL_TRANSPARENT_TYPE 0x3034
#  define EGL_TRUE 1
#  define EGL_VENDOR 0x3053
#  define EGL_VERSION 0x3054
#  define EGL_WIDTH 0x3057
#  define EGL_WINDOW_BIT 0x0004
#  define EGL_BACK_BUFFER 0x3084
#  define EGL_BIND_TO_TEXTURE_RGB 0x3039
#  define EGL_BIND_TO_TEXTURE_RGBA 0x303A
#  define EGL_CONTEXT_LOST 0x300E
#  define EGL_MIN_SWAP_INTERVAL 0x303B
#  define EGL_MAX_SWAP_INTERVAL 0x303C
#  define EGL_MIPMAP_TEXTURE 0x3082
#  define EGL_MIPMAP_LEVEL 0x3083
#  define EGL_NO_TEXTURE 0x305C
#  define EGL_TEXTURE_2D 0x305F
#  define EGL_TEXTURE_FORMAT 0x3080
#  define EGL_TEXTURE_RGB 0x305D
#  define EGL_TEXTURE_RGBA 0x305E
#  define EGL_TEXTURE_TARGET 0x3081
#  define EGL_ALPHA_FORMAT 0x3088
#  define EGL_ALPHA_FORMAT_NONPRE 0x308B
#  define EGL_ALPHA_FORMAT_PRE 0x308C
#  define EGL_ALPHA_MASK_SIZE 0x303E
#  define EGL_BUFFER_PRESERVED 0x3094
#  define EGL_BUFFER_DESTROYED 0x3095
#  define EGL_CLIENT_APIS 0x308D
#  define EGL_COLORSPACE 0x3087
#  define EGL_COLORSPACE_sRGB 0x3089
#  define EGL_COLORSPACE_LINEAR 0x308A
#  define EGL_COLOR_BUFFER_TYPE 0x303F
#  define EGL_CONTEXT_CLIENT_TYPE 0x3097
#  define EGL_DISPLAY_SCALING 10000
#  define EGL_HORIZONTAL_RESOLUTION 0x3090
#  define EGL_LUMINANCE_BUFFER 0x308F
#  define EGL_LUMINANCE_SIZE 0x303D
#  define EGL_OPENGL_ES_BIT 0x0001
#  define EGL_OPENVG_BIT 0x0002
#  define EGL_OPENGL_ES_API 0x30A0
#  define EGL_OPENVG_API 0x30A1
#  define EGL_OPENVG_IMAGE 0x3096
#  define EGL_PIXEL_ASPECT_RATIO 0x3092
#  define EGL_RENDERABLE_TYPE 0x3040
#  define EGL_RENDER_BUFFER 0x3086
#  define EGL_RGB_BUFFER 0x308E
#  define EGL_SINGLE_BUFFER 0x3085
#  define EGL_SWAP_BEHAVIOR 0x3093
#  define EGL_UNKNOWN ((int) -1)
#  define EGL_VERTICAL_RESOLUTION 0x3091
#  define EGL_CONFORMANT 0x3042
#  define EGL_CONTEXT_CLIENT_VERSION 0x3098
#  define EGL_MATCH_NATIVE_PIXMAP 0x3041
#  define EGL_OPENGL_ES2_BIT 0x0004
#  define EGL_VG_ALPHA_FORMAT 0x3088
#  define EGL_VG_ALPHA_FORMAT_NONPRE 0x308B
#  define EGL_VG_ALPHA_FORMAT_PRE 0x308C
#  define EGL_VG_ALPHA_FORMAT_PRE_BIT 0x0040
#  define EGL_VG_COLORSPACE 0x3087
#  define EGL_VG_COLORSPACE_sRGB 0x3089
#  define EGL_VG_COLORSPACE_LINEAR 0x308A
#  define EGL_VG_COLORSPACE_LINEAR_BIT 0x0020
#  define EGL_DEFAULT_DISPLAY ((EGLNativeDisplayType) 0)
#  define EGL_MULTISAMPLE_RESOLVE_BOX_BIT 0x0200
#  define EGL_MULTISAMPLE_RESOLVE 0x3099
#  define EGL_MULTISAMPLE_RESOLVE_DEFAULT 0x309A
#  define EGL_MULTISAMPLE_RESOLVE_BOX 0x309B
#  define EGL_OPENGL_API 0x30A2
#  define EGL_OPENGL_BIT 0x0008
#  define EGL_SWAP_BEHAVIOR_PRESERVED_BIT 0x0400
#  define EGL_CONTEXT_MAJOR_VERSION 0x3098
#  define EGL_CONTEXT_MINOR_VERSION 0x30FB
#  define EGL_CONTEXT_OPENGL_PROFILE_MASK 0x30FD
#  define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY 0x31BD
#  define EGL_NO_RESET_NOTIFICATION 0x31BE
#  define EGL_LOSE_CONTEXT_ON_RESET 0x31BF
#  define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT 0x00000001
#  define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT 0x00000002
#  define EGL_CONTEXT_OPENGL_DEBUG 0x31B0
#  define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE 0x31B1
#  define EGL_CONTEXT_OPENGL_ROBUST_ACCESS 0x31B2
#  define EGL_OPENGL_ES3_BIT 0x00000040
#  define EGL_CL_EVENT_HANDLE 0x309C
#  define EGL_SYNC_CL_EVENT 0x30FE
#  define EGL_SYNC_CL_EVENT_COMPLETE 0x30FF
#  define EGL_SYNC_PRIOR_COMMANDS_COMPLETE 0x30F0
#  define EGL_SYNC_TYPE 0x30F7
#  define EGL_SYNC_STATUS 0x30F1
#  define EGL_SYNC_CONDITION 0x30F8
#  define EGL_SIGNALED 0x30F2
#  define EGL_UNSIGNALED 0x30F3
#  define EGL_SYNC_FLUSH_COMMANDS_BIT 0x0001
#  define EGL_FOREVER 0xFFFFFFFFFFFFFFFFull
#  define EGL_TIMEOUT_EXPIRED 0x30F5
#  define EGL_CONDITION_SATISFIED 0x30F6
#  define EGL_NO_SYNC ((EGLSync) 0)
#  define EGL_SYNC_FENCE 0x30F9
#  define EGL_GL_COLORSPACE 0x309D
#  define EGL_GL_COLORSPACE_SRGB 0x3089
#  define EGL_GL_COLORSPACE_LINEAR 0x308A
#  define EGL_GL_RENDERBUFFER 0x30B9
#  define EGL_GL_TEXTURE_2D 0x30B1
#  define EGL_GL_TEXTURE_LEVEL 0x30BC
#  define EGL_GL_TEXTURE_3D 0x30B2
#  define EGL_GL_TEXTURE_ZOFFSET 0x30BD
#  define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x30B3
#  define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x30B4
#  define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x30B5
#  define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x30B6
#  define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x30B7
#  define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x30B8
#  define EGL_IMAGE_PRESERVED 0x30D2
#  define EGL_NO_IMAGE ((EGLImage) 0)

/* }}} */
/* {{{ */

typedef EGLBoolean (* PFN_eglBindAPI_PROC) (EGLenum);
PFN_eglBindAPI_PROC eglBindAPI_PROC = 0;
#  define eglBindAPI (assert(eglBindAPI_PROC != 0), eglBindAPI_PROC)

typedef EGLBoolean (* PFN_eglBindTexImage_PROC) (EGLDisplay, EGLSurface, int);
PFN_eglBindTexImage_PROC eglBindTexImage_PROC = 0;
#  define eglBindTexImage (assert(eglBindTexImage_PROC != 0), eglBindTexImage_PROC)

typedef EGLBoolean (* PFN_eglChooseConfig_PROC) (EGLDisplay, const int *, EGLConfig *, int, int *);
PFN_eglChooseConfig_PROC eglChooseConfig_PROC = 0;
#  define eglChooseConfig (assert(eglChooseConfig_PROC != 0), eglChooseConfig_PROC)

typedef int (* PFN_eglClientWaitSync_PROC) (EGLDisplay, EGLSync, int, EGLTime);
PFN_eglClientWaitSync_PROC eglClientWaitSync_PROC = 0;
#  define eglClientWaitSync (assert(eglClientWaitSync_PROC != 0), eglClientWaitSync_PROC)

typedef EGLBoolean (* PFN_eglCopyBuffers_PROC) (EGLDisplay, EGLSurface, EGLNativePixmapType);
PFN_eglCopyBuffers_PROC eglCopyBuffers_PROC = 0;
#  define eglCopyBuffers (assert(eglCopyBuffers_PROC != 0), eglCopyBuffers_PROC)

typedef EGLContext (* PFN_eglCreateContext_PROC) (EGLDisplay, EGLConfig, EGLContext, const int *);
PFN_eglCreateContext_PROC eglCreateContext_PROC = 0;
#  define eglCreateContext (assert(eglCreateContext_PROC != 0), eglCreateContext_PROC)

typedef EGLImage (* PFN_eglCreateImage_PROC) (EGLDisplay, EGLContext, EGLenum, EGLClientBuffer, const EGLAttrib *);
PFN_eglCreateImage_PROC eglCreateImage_PROC = 0;
#  define eglCreateImage (assert(eglCreateImage_PROC != 0), eglCreateImage_PROC)

typedef EGLSurface (* PFN_eglCreatePbufferFromClientBuffer_PROC) (EGLDisplay, EGLenum, EGLClientBuffer, EGLConfig, const int *);
PFN_eglCreatePbufferFromClientBuffer_PROC eglCreatePbufferFromClientBuffer_PROC = 0;
#  define eglCreatePbufferFromClientBuffer (assert(eglCreatePbufferFromClientBuffer_PROC != 0), eglCreatePbufferFromClientBuffer_PROC)

typedef EGLSurface (* PFN_eglCreatePbufferSurface_PROC) (EGLDisplay, EGLConfig, const int *);
PFN_eglCreatePbufferSurface_PROC eglCreatePbufferSurface_PROC = 0;
#  define eglCreatePbufferSurface (assert(eglCreatePbufferSurface_PROC != 0), eglCreatePbufferSurface_PROC)

typedef EGLSurface (* PFN_eglCreatePixmapSurface_PROC) (EGLDisplay, EGLConfig, EGLNativePixmapType, const int *);
PFN_eglCreatePixmapSurface_PROC eglCreatePixmapSurface_PROC = 0;
#  define eglCreatePixmapSurface (assert(eglCreatePixmapSurface_PROC != 0), eglCreatePixmapSurface_PROC)

typedef EGLSurface (* PFN_eglCreatePlatformPixmapSurface_PROC) (EGLDisplay, EGLConfig, void *, const EGLAttrib *);
PFN_eglCreatePlatformPixmapSurface_PROC eglCreatePlatformPixmapSurface_PROC = 0;
#  define eglCreatePlatformPixmapSurface (assert(eglCreatePlatformPixmapSurface_PROC != 0), eglCreatePlatformPixmapSurface_PROC)

typedef EGLSurface (* PFN_eglCreatePlatformWindowSurface_PROC) (EGLDisplay, EGLConfig, void *, const EGLAttrib *);
PFN_eglCreatePlatformWindowSurface_PROC eglCreatePlatformWindowSurface_PROC = 0;
#  define eglCreatePlatformWindowSurface (assert(eglCreatePlatformWindowSurface_PROC != 0), eglCreatePlatformWindowSurface_PROC)

typedef EGLSync (* PFN_eglCreateSync_PROC) (EGLDisplay, EGLenum, const EGLAttrib *);
PFN_eglCreateSync_PROC eglCreateSync_PROC = 0;
#  define eglCreateSync (assert(eglCreateSync_PROC != 0), eglCreateSync_PROC)

typedef EGLSurface (* PFN_eglCreateWindowSurface_PROC) (EGLDisplay, EGLConfig, EGLNativeWindowType, const int *);
PFN_eglCreateWindowSurface_PROC eglCreateWindowSurface_PROC = 0;
#  define eglCreateWindowSurface (assert(eglCreateWindowSurface_PROC != 0), eglCreateWindowSurface_PROC)

typedef EGLBoolean (* PFN_eglDestroyContext_PROC) (EGLDisplay, EGLContext);
PFN_eglDestroyContext_PROC eglDestroyContext_PROC = 0;
#  define eglDestroyContext (assert(eglDestroyContext_PROC != 0), eglDestroyContext_PROC)

typedef EGLBoolean (* PFN_eglDestroyImage_PROC) (EGLDisplay, EGLImage);
PFN_eglDestroyImage_PROC eglDestroyImage_PROC = 0;
#  define eglDestroyImage (assert(eglDestroyImage_PROC != 0), eglDestroyImage_PROC)

typedef EGLBoolean (* PFN_eglDestroySurface_PROC) (EGLDisplay, EGLSurface);
PFN_eglDestroySurface_PROC eglDestroySurface_PROC = 0;
#  define eglDestroySurface (assert(eglDestroySurface_PROC != 0), eglDestroySurface_PROC)

typedef EGLBoolean (* PFN_eglDestroySync_PROC) (EGLDisplay, EGLSync);
PFN_eglDestroySync_PROC eglDestroySync_PROC = 0;
#  define eglDestroySync (assert(eglDestroySync_PROC != 0), eglDestroySync_PROC)

typedef EGLBoolean (* PFN_eglGetConfigAttrib_PROC) (EGLDisplay, EGLConfig, int, int *);
PFN_eglGetConfigAttrib_PROC eglGetConfigAttrib_PROC = 0;
#  define eglGetConfigAttrib (assert(eglGetConfigAttrib_PROC != 0), eglGetConfigAttrib_PROC)

typedef EGLBoolean (* PFN_eglGetConfigs_PROC) (EGLDisplay, EGLConfig *, int, int *);
PFN_eglGetConfigs_PROC eglGetConfigs_PROC = 0;
#  define eglGetConfigs (assert(eglGetConfigs_PROC != 0), eglGetConfigs_PROC)

typedef EGLContext (* PFN_eglGetCurrentContext_PROC) (void);
PFN_eglGetCurrentContext_PROC eglGetCurrentContext_PROC = 0;
#  define eglGetCurrentContext (assert(eglGetCurrentContext_PROC != 0), eglGetCurrentContext_PROC)

typedef EGLDisplay (* PFN_eglGetCurrentDisplay_PROC) (void);
PFN_eglGetCurrentDisplay_PROC eglGetCurrentDisplay_PROC = 0;
#  define eglGetCurrentDisplay (assert(eglGetCurrentDisplay_PROC != 0), eglGetCurrentDisplay_PROC)

typedef EGLSurface (* PFN_eglGetCurrentSurface_PROC) (int);
PFN_eglGetCurrentSurface_PROC eglGetCurrentSurface_PROC = 0;
#  define eglGetCurrentSurface (assert(eglGetCurrentSurface_PROC != 0), eglGetCurrentSurface_PROC)

typedef EGLDisplay (* PFN_eglGetDisplay_PROC) (EGLNativeDisplayType);
PFN_eglGetDisplay_PROC eglGetDisplay_PROC = 0;
#  define eglGetDisplay (assert(eglGetDisplay_PROC != 0), eglGetDisplay_PROC)

typedef int (* PFN_eglGetError_PROC) (void);
PFN_eglGetError_PROC eglGetError_PROC = 0;
#  define eglGetError (assert(eglGetError_PROC != 0), eglGetError_PROC)

typedef EGLDisplay (* PFN_eglGetPlatformDisplay_PROC) (EGLenum, void *, const EGLAttrib *);
PFN_eglGetPlatformDisplay_PROC eglGetPlatformDisplay_PROC = 0;
#  define eglGetPlatformDisplay (assert(eglGetPlatformDisplay_PROC != 0), eglGetPlatformDisplay_PROC)

typedef __eglMustCastToProperFunctionPointerType (* PFN_eglGetProcAddress_PROC) (const char *);
PFN_eglGetProcAddress_PROC eglGetProcAddress_PROC = 0;
#  define eglGetProcAddress (assert(eglGetProcAddress_PROC != 0), eglGetProcAddress_PROC)

typedef EGLBoolean (* PFN_eglGetSyncAttrib_PROC) (EGLDisplay, EGLSync, int, EGLAttrib *);
PFN_eglGetSyncAttrib_PROC eglGetSyncAttrib_PROC = 0;
#  define eglGetSyncAttrib (assert(eglGetSyncAttrib_PROC != 0), eglGetSyncAttrib_PROC)

typedef EGLBoolean (* PFN_eglInitialize_PROC) (EGLDisplay, int *, int *);
PFN_eglInitialize_PROC eglInitialize_PROC = 0;
#  define eglInitialize (assert(eglInitialize_PROC != 0), eglInitialize_PROC)

typedef EGLBoolean (* PFN_eglMakeCurrent_PROC) (EGLDisplay, EGLSurface, EGLSurface, EGLContext);
PFN_eglMakeCurrent_PROC eglMakeCurrent_PROC = 0;
#  define eglMakeCurrent (assert(eglMakeCurrent_PROC != 0), eglMakeCurrent_PROC)

typedef EGLenum (* PFN_eglQueryAPI_PROC) (void);
PFN_eglQueryAPI_PROC eglQueryAPI_PROC = 0;
#  define eglQueryAPI (assert(eglQueryAPI_PROC != 0), eglQueryAPI_PROC)

typedef EGLBoolean (* PFN_eglQueryContext_PROC) (EGLDisplay, EGLContext, int, int *);
PFN_eglQueryContext_PROC eglQueryContext_PROC = 0;
#  define eglQueryContext (assert(eglQueryContext_PROC != 0), eglQueryContext_PROC)

typedef const char *(* PFN_eglQueryString_PROC) (EGLDisplay, int);
PFN_eglQueryString_PROC eglQueryString_PROC = 0;
#  define eglQueryString (assert(eglQueryString_PROC != 0), eglQueryString_PROC)

typedef EGLBoolean (* PFN_eglQuerySurface_PROC) (EGLDisplay, EGLSurface, int, int *);
PFN_eglQuerySurface_PROC eglQuerySurface_PROC = 0;
#  define eglQuerySurface (assert(eglQuerySurface_PROC != 0), eglQuerySurface_PROC)

typedef EGLBoolean (* PFN_eglReleaseTexImage_PROC) (EGLDisplay, EGLSurface, int);
PFN_eglReleaseTexImage_PROC eglReleaseTexImage_PROC = 0;
#  define eglReleaseTexImage (assert(eglReleaseTexImage_PROC != 0), eglReleaseTexImage_PROC)

typedef EGLBoolean (* PFN_eglReleaseThread_PROC) (void);
PFN_eglReleaseThread_PROC eglReleaseThread_PROC = 0;
#  define eglReleaseThread (assert(eglReleaseThread_PROC != 0), eglReleaseThread_PROC)

typedef EGLBoolean (* PFN_eglSurfaceAttrib_PROC) (EGLDisplay, EGLSurface, int, int);
PFN_eglSurfaceAttrib_PROC eglSurfaceAttrib_PROC = 0;
#  define eglSurfaceAttrib (assert(eglSurfaceAttrib_PROC != 0), eglSurfaceAttrib_PROC)

typedef EGLBoolean (* PFN_eglSwapBuffers_PROC) (EGLDisplay, EGLSurface);
PFN_eglSwapBuffers_PROC eglSwapBuffers_PROC = 0;
#  define eglSwapBuffers (assert(eglSwapBuffers_PROC != 0), eglSwapBuffers_PROC)

typedef EGLBoolean (* PFN_eglSwapInterval_PROC) (EGLDisplay, int);
PFN_eglSwapInterval_PROC eglSwapInterval_PROC = 0;
#  define eglSwapInterval (assert(eglSwapInterval_PROC != 0), eglSwapInterval_PROC)

typedef EGLBoolean (* PFN_eglTerminate_PROC) (EGLDisplay);
PFN_eglTerminate_PROC eglTerminate_PROC = 0;
#  define eglTerminate (assert(eglTerminate_PROC != 0), eglTerminate_PROC)

typedef EGLBoolean (* PFN_eglWaitClient_PROC) (void);
PFN_eglWaitClient_PROC eglWaitClient_PROC = 0;
#  define eglWaitClient (assert(eglWaitClient_PROC != 0), eglWaitClient_PROC)

typedef EGLBoolean (* PFN_eglWaitGL_PROC) (void);
PFN_eglWaitGL_PROC eglWaitGL_PROC = 0;
#  define eglWaitGL (assert(eglWaitGL_PROC != 0), eglWaitGL_PROC)

typedef EGLBoolean (* PFN_eglWaitNative_PROC) (int);
PFN_eglWaitNative_PROC eglWaitNative_PROC = 0;
#  define eglWaitNative (assert(eglWaitNative_PROC != 0), eglWaitNative_PROC)

typedef EGLBoolean (* PFN_eglWaitSync_PROC) (EGLDisplay, EGLSync, int);
PFN_eglWaitSync_PROC eglWaitSync_PROC = 0;
#  define eglWaitSync (assert(eglWaitSync_PROC != 0), eglWaitSync_PROC)

/* }}} */

typedef struct _window_h_context_egl *context_t_egl;

struct _window_h_context_egl {
    EGLSurface surface;
    EGLContext context;
};


typedef struct _window_h_egl *_window_h_egl;

struct _window_h_egl {
    /* handle do shared object */
    void *handle;

    /* handle to EGL's display object */
    EGLDisplay dpy;

    /* best EGLConfig object */
    EGLConfig config;

    struct {
        /* surface hints */
        int *surface;
        
        /* context hints */
        int *context;
        
        /* config hints */
        int *config;
    } attr;
};

/* }}} */
# endif /* WINDOW_BACKEND_EGL */
#
# /* WINDOW_BACKEND_WGL - WGL definitions layer */
# if defined (WINDOW_BACKEND_WGL)
/* {{{ */

typedef struct _window_h_context_wgl *context_t_wgl;

struct _window_h_context_wgl {

    /* ... */

};


typedef struct _window_h_wgl *_window_h_wgl;

struct _window_h_wgl {
    /* handle do shared object */
    void *handle;

    /* ... */
};

/* }}} */
# endif /* WINDOW_BACKEND_WGL */
#
# /* WINDOW_BACKEND_X11 - X11 definitions layer */
# if defined (WINDOW_BACKEND_X11)
/* {{{ */

/* libX11.so */
/* {{{ */
typedef int (* PFN_XActivateScreenSaver_PROC) (Display *);
PFN_XActivateScreenSaver_PROC XActivateScreenSaver_PROC = 0;
#  define XActivateScreenSaver (assert(XActivateScreenSaver_PROC != 0), XActivateScreenSaver_PROC)

typedef int (* PFN_XAddConnectionWatch_PROC) (Display *, XConnectionWatchProc, XPointer);
PFN_XAddConnectionWatch_PROC XAddConnectionWatch_PROC = 0;
#  define XAddConnectionWatch (assert(XAddConnectionWatch_PROC != 0), XAddConnectionWatch_PROC)

typedef XExtCodes *(* PFN_XAddExtension_PROC) (Display *);
PFN_XAddExtension_PROC XAddExtension_PROC = 0;
#  define XAddExtension (assert(XAddExtension_PROC != 0), XAddExtension_PROC)

typedef int (* PFN_XAddHost_PROC) (Display *, XHostAddress *);
PFN_XAddHost_PROC XAddHost_PROC = 0;
#  define XAddHost (assert(XAddHost_PROC != 0), XAddHost_PROC)

typedef int (* PFN_XAddHosts_PROC) (Display *, XHostAddress *, int);
PFN_XAddHosts_PROC XAddHosts_PROC = 0;
#  define XAddHosts (assert(XAddHosts_PROC != 0), XAddHosts_PROC)

typedef int (* PFN_XAddToExtensionList_PROC) (struct _XExtData **, XExtData *);
PFN_XAddToExtensionList_PROC XAddToExtensionList_PROC = 0;
#  define XAddToExtensionList (assert(XAddToExtensionList_PROC != 0), XAddToExtensionList_PROC)

typedef int (* PFN_XAddToSaveSet_PROC) (Display *, Window);
PFN_XAddToSaveSet_PROC XAddToSaveSet_PROC = 0;
#  define XAddToSaveSet (assert(XAddToSaveSet_PROC != 0), XAddToSaveSet_PROC)

typedef unsigned long (* PFN_XAllPlanes_PROC) (void);
PFN_XAllPlanes_PROC XAllPlanes_PROC = 0;
#  define XAllPlanes (assert(XAllPlanes_PROC != 0), XAllPlanes_PROC)

typedef int (* PFN_XAllocColor_PROC) (Display *, Colormap, XColor *);
PFN_XAllocColor_PROC XAllocColor_PROC = 0;
#  define XAllocColor (assert(XAllocColor_PROC != 0), XAllocColor_PROC)

typedef int (* PFN_XAllocColorCells_PROC) (Display *, Colormap, int, unsigned long *, unsigned int, unsigned long *, unsigned int);
PFN_XAllocColorCells_PROC XAllocColorCells_PROC = 0;
#  define XAllocColorCells (assert(XAllocColorCells_PROC != 0), XAllocColorCells_PROC)

typedef int (* PFN_XAllocColorPlanes_PROC) (Display *, Colormap, int, unsigned long *, int, int, int, int, unsigned long *, unsigned long *, unsigned long *);
PFN_XAllocColorPlanes_PROC XAllocColorPlanes_PROC = 0;
#  define XAllocColorPlanes (assert(XAllocColorPlanes_PROC != 0), XAllocColorPlanes_PROC)

typedef int (* PFN_XAllocNamedColor_PROC) (Display *, Colormap, const char *, XColor *, XColor *);
PFN_XAllocNamedColor_PROC XAllocNamedColor_PROC = 0;
#  define XAllocNamedColor (assert(XAllocNamedColor_PROC != 0), XAllocNamedColor_PROC)

typedef int (* PFN_XAllowEvents_PROC) (Display *, int, Time);
PFN_XAllowEvents_PROC XAllowEvents_PROC = 0;
#  define XAllowEvents (assert(XAllowEvents_PROC != 0), XAllowEvents_PROC)

typedef int (* PFN_XAutoRepeatOff_PROC) (Display *);
PFN_XAutoRepeatOff_PROC XAutoRepeatOff_PROC = 0;
#  define XAutoRepeatOff (assert(XAutoRepeatOff_PROC != 0), XAutoRepeatOff_PROC)

typedef int (* PFN_XAutoRepeatOn_PROC) (Display *);
PFN_XAutoRepeatOn_PROC XAutoRepeatOn_PROC = 0;
#  define XAutoRepeatOn (assert(XAutoRepeatOn_PROC != 0), XAutoRepeatOn_PROC)

typedef char *(* PFN_XBaseFontNameListOfFontSet_PROC) (XFontSet);
PFN_XBaseFontNameListOfFontSet_PROC XBaseFontNameListOfFontSet_PROC = 0;
#  define XBaseFontNameListOfFontSet (assert(XBaseFontNameListOfFontSet_PROC != 0), XBaseFontNameListOfFontSet_PROC)

typedef int (* PFN_XBell_PROC) (Display *, int);
PFN_XBell_PROC XBell_PROC = 0;
#  define XBell (assert(XBell_PROC != 0), XBell_PROC)

typedef int (* PFN_XBitmapBitOrder_PROC) (Display *);
PFN_XBitmapBitOrder_PROC XBitmapBitOrder_PROC = 0;
#  define XBitmapBitOrder (assert(XBitmapBitOrder_PROC != 0), XBitmapBitOrder_PROC)

typedef int (* PFN_XBitmapPad_PROC) (Display *);
PFN_XBitmapPad_PROC XBitmapPad_PROC = 0;
#  define XBitmapPad (assert(XBitmapPad_PROC != 0), XBitmapPad_PROC)

typedef int (* PFN_XBitmapUnit_PROC) (Display *);
PFN_XBitmapUnit_PROC XBitmapUnit_PROC = 0;
#  define XBitmapUnit (assert(XBitmapUnit_PROC != 0), XBitmapUnit_PROC)

typedef unsigned long (* PFN_XBlackPixel_PROC) (Display *, int);
PFN_XBlackPixel_PROC XBlackPixel_PROC = 0;
#  define XBlackPixel (assert(XBlackPixel_PROC != 0), XBlackPixel_PROC)

typedef unsigned long (* PFN_XBlackPixelOfScreen_PROC) (Screen *);
PFN_XBlackPixelOfScreen_PROC XBlackPixelOfScreen_PROC = 0;
#  define XBlackPixelOfScreen (assert(XBlackPixelOfScreen_PROC != 0), XBlackPixelOfScreen_PROC)

typedef int (* PFN_XCellsOfScreen_PROC) (Screen *);
PFN_XCellsOfScreen_PROC XCellsOfScreen_PROC = 0;
#  define XCellsOfScreen (assert(XCellsOfScreen_PROC != 0), XCellsOfScreen_PROC)

typedef int (* PFN_XChangeActivePointerGrab_PROC) (Display *, unsigned int, Cursor, Time);
PFN_XChangeActivePointerGrab_PROC XChangeActivePointerGrab_PROC = 0;
#  define XChangeActivePointerGrab (assert(XChangeActivePointerGrab_PROC != 0), XChangeActivePointerGrab_PROC)

typedef int (* PFN_XChangeGC_PROC) (Display *, GC, unsigned long, XGCValues *);
PFN_XChangeGC_PROC XChangeGC_PROC = 0;
#  define XChangeGC (assert(XChangeGC_PROC != 0), XChangeGC_PROC)

typedef int (* PFN_XChangeKeyboardControl_PROC) (Display *, unsigned long, XKeyboardControl *);
PFN_XChangeKeyboardControl_PROC XChangeKeyboardControl_PROC = 0;
#  define XChangeKeyboardControl (assert(XChangeKeyboardControl_PROC != 0), XChangeKeyboardControl_PROC)

typedef int (* PFN_XChangeKeyboardMapping_PROC) (Display *, int, int, KeySym *, int);
PFN_XChangeKeyboardMapping_PROC XChangeKeyboardMapping_PROC = 0;
#  define XChangeKeyboardMapping (assert(XChangeKeyboardMapping_PROC != 0), XChangeKeyboardMapping_PROC)

typedef int (* PFN_XChangePointerControl_PROC) (Display *, int, int, int, int, int);
PFN_XChangePointerControl_PROC XChangePointerControl_PROC = 0;
#  define XChangePointerControl (assert(XChangePointerControl_PROC != 0), XChangePointerControl_PROC)

typedef int (* PFN_XChangeProperty_PROC) (Display *, Window, Atom, Atom, int, int, const unsigned char *, int);
PFN_XChangeProperty_PROC XChangeProperty_PROC = 0;
#  define XChangeProperty (assert(XChangeProperty_PROC != 0), XChangeProperty_PROC)

typedef int (* PFN_XChangeSaveSet_PROC) (Display *, Window, int);
PFN_XChangeSaveSet_PROC XChangeSaveSet_PROC = 0;
#  define XChangeSaveSet (assert(XChangeSaveSet_PROC != 0), XChangeSaveSet_PROC)

typedef int (* PFN_XChangeWindowAttributes_PROC) (Display *, Window, unsigned long, XSetWindowAttributes *);
PFN_XChangeWindowAttributes_PROC XChangeWindowAttributes_PROC = 0;
#  define XChangeWindowAttributes (assert(XChangeWindowAttributes_PROC != 0), XChangeWindowAttributes_PROC)

typedef int (* PFN_XCheckIfEvent_PROC) (Display *, XEvent *, int (*)(Display *, XEvent *, XPointer), XPointer);
PFN_XCheckIfEvent_PROC XCheckIfEvent_PROC = 0;
#  define XCheckIfEvent (assert(XCheckIfEvent_PROC != 0), XCheckIfEvent_PROC)

typedef int (* PFN_XCheckMaskEvent_PROC) (Display *, long, XEvent *);
PFN_XCheckMaskEvent_PROC XCheckMaskEvent_PROC = 0;
#  define XCheckMaskEvent (assert(XCheckMaskEvent_PROC != 0), XCheckMaskEvent_PROC)

typedef int (* PFN_XCheckTypedEvent_PROC) (Display *, int, XEvent *);
PFN_XCheckTypedEvent_PROC XCheckTypedEvent_PROC = 0;
#  define XCheckTypedEvent (assert(XCheckTypedEvent_PROC != 0), XCheckTypedEvent_PROC)

typedef int (* PFN_XCheckTypedWindowEvent_PROC) (Display *, Window, int, XEvent *);
PFN_XCheckTypedWindowEvent_PROC XCheckTypedWindowEvent_PROC = 0;
#  define XCheckTypedWindowEvent (assert(XCheckTypedWindowEvent_PROC != 0), XCheckTypedWindowEvent_PROC)

typedef int (* PFN_XCheckWindowEvent_PROC) (Display *, Window, long, XEvent *);
PFN_XCheckWindowEvent_PROC XCheckWindowEvent_PROC = 0;
#  define XCheckWindowEvent (assert(XCheckWindowEvent_PROC != 0), XCheckWindowEvent_PROC)

typedef int (* PFN_XCirculateSubwindows_PROC) (Display *, Window, int);
PFN_XCirculateSubwindows_PROC XCirculateSubwindows_PROC = 0;
#  define XCirculateSubwindows (assert(XCirculateSubwindows_PROC != 0), XCirculateSubwindows_PROC)

typedef int (* PFN_XCirculateSubwindowsDown_PROC) (Display *, Window);
PFN_XCirculateSubwindowsDown_PROC XCirculateSubwindowsDown_PROC = 0;
#  define XCirculateSubwindowsDown (assert(XCirculateSubwindowsDown_PROC != 0), XCirculateSubwindowsDown_PROC)

typedef int (* PFN_XCirculateSubwindowsUp_PROC) (Display *, Window);
PFN_XCirculateSubwindowsUp_PROC XCirculateSubwindowsUp_PROC = 0;
#  define XCirculateSubwindowsUp (assert(XCirculateSubwindowsUp_PROC != 0), XCirculateSubwindowsUp_PROC)

typedef int (* PFN_XClearArea_PROC) (Display *, Window, int, int, unsigned int, unsigned int, int);
PFN_XClearArea_PROC XClearArea_PROC = 0;
#  define XClearArea (assert(XClearArea_PROC != 0), XClearArea_PROC)

typedef int (* PFN_XClearWindow_PROC) (Display *, Window);
PFN_XClearWindow_PROC XClearWindow_PROC = 0;
#  define XClearWindow (assert(XClearWindow_PROC != 0), XClearWindow_PROC)

typedef int (* PFN_XCloseDisplay_PROC) (Display *);
PFN_XCloseDisplay_PROC XCloseDisplay_PROC = 0;
#  define XCloseDisplay (assert(XCloseDisplay_PROC != 0), XCloseDisplay_PROC)

typedef int (* PFN_XCloseIM_PROC) (XIM);
PFN_XCloseIM_PROC XCloseIM_PROC = 0;
#  define XCloseIM (assert(XCloseIM_PROC != 0), XCloseIM_PROC)

typedef int (* PFN_XCloseOM_PROC) (XOM);
PFN_XCloseOM_PROC XCloseOM_PROC = 0;
#  define XCloseOM (assert(XCloseOM_PROC != 0), XCloseOM_PROC)

typedef int (* PFN_XConfigureWindow_PROC) (Display *, Window, unsigned int, XWindowChanges *);
PFN_XConfigureWindow_PROC XConfigureWindow_PROC = 0;
#  define XConfigureWindow (assert(XConfigureWindow_PROC != 0), XConfigureWindow_PROC)

typedef int (* PFN_XConnectionNumber_PROC) (Display *);
PFN_XConnectionNumber_PROC XConnectionNumber_PROC = 0;
#  define XConnectionNumber (assert(XConnectionNumber_PROC != 0), XConnectionNumber_PROC)

typedef int (* PFN_XContextDependentDrawing_PROC) (XFontSet);
PFN_XContextDependentDrawing_PROC XContextDependentDrawing_PROC = 0;
#  define XContextDependentDrawing (assert(XContextDependentDrawing_PROC != 0), XContextDependentDrawing_PROC)

typedef int (* PFN_XContextualDrawing_PROC) (XFontSet);
PFN_XContextualDrawing_PROC XContextualDrawing_PROC = 0;
#  define XContextualDrawing (assert(XContextualDrawing_PROC != 0), XContextualDrawing_PROC)

typedef int (* PFN_XConvertSelection_PROC) (Display *, Atom, Atom, Atom, Window, Time);
PFN_XConvertSelection_PROC XConvertSelection_PROC = 0;
#  define XConvertSelection (assert(XConvertSelection_PROC != 0), XConvertSelection_PROC)

typedef int (* PFN_XCopyArea_PROC) (Display *, Drawable, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
PFN_XCopyArea_PROC XCopyArea_PROC = 0;
#  define XCopyArea (assert(XCopyArea_PROC != 0), XCopyArea_PROC)

typedef Colormap (* PFN_XCopyColormapAndFree_PROC) (Display *, Colormap);
PFN_XCopyColormapAndFree_PROC XCopyColormapAndFree_PROC = 0;
#  define XCopyColormapAndFree (assert(XCopyColormapAndFree_PROC != 0), XCopyColormapAndFree_PROC)

typedef int (* PFN_XCopyGC_PROC) (Display *, GC, unsigned long, GC);
PFN_XCopyGC_PROC XCopyGC_PROC = 0;
#  define XCopyGC (assert(XCopyGC_PROC != 0), XCopyGC_PROC)

typedef int (* PFN_XCopyPlane_PROC) (Display *, Drawable, Drawable, GC, int, int, unsigned int, unsigned int, int, int, unsigned long);
PFN_XCopyPlane_PROC XCopyPlane_PROC = 0;
#  define XCopyPlane (assert(XCopyPlane_PROC != 0), XCopyPlane_PROC)

typedef Pixmap (* PFN_XCreateBitmapFromData_PROC) (Display *, Drawable, const char *, unsigned int, unsigned int);
PFN_XCreateBitmapFromData_PROC XCreateBitmapFromData_PROC = 0;
#  define XCreateBitmapFromData (assert(XCreateBitmapFromData_PROC != 0), XCreateBitmapFromData_PROC)

typedef Colormap (* PFN_XCreateColormap_PROC) (Display *, Window, Visual *, int);
PFN_XCreateColormap_PROC XCreateColormap_PROC = 0;
#  define XCreateColormap (assert(XCreateColormap_PROC != 0), XCreateColormap_PROC)

typedef Cursor (* PFN_XCreateFontCursor_PROC) (Display *, unsigned int);
PFN_XCreateFontCursor_PROC XCreateFontCursor_PROC = 0;
#  define XCreateFontCursor (assert(XCreateFontCursor_PROC != 0), XCreateFontCursor_PROC)

typedef XFontSet (* PFN_XCreateFontSet_PROC) (Display *, const char *, char ***, int *, char **);
PFN_XCreateFontSet_PROC XCreateFontSet_PROC = 0;
#  define XCreateFontSet (assert(XCreateFontSet_PROC != 0), XCreateFontSet_PROC)

typedef GC (* PFN_XCreateGC_PROC) (Display *, Drawable, unsigned long, XGCValues *);
PFN_XCreateGC_PROC XCreateGC_PROC = 0;
#  define XCreateGC (assert(XCreateGC_PROC != 0), XCreateGC_PROC)

typedef Cursor (* PFN_XCreateGlyphCursor_PROC) (Display *, Font, Font, unsigned int, unsigned int, const XColor *, const XColor *);
PFN_XCreateGlyphCursor_PROC XCreateGlyphCursor_PROC = 0;
#  define XCreateGlyphCursor (assert(XCreateGlyphCursor_PROC != 0), XCreateGlyphCursor_PROC)

typedef XIC (* PFN_XCreateIC_PROC) (XIM, ...);
PFN_XCreateIC_PROC XCreateIC_PROC = 0;
#  define XCreateIC (assert(XCreateIC_PROC != 0), XCreateIC_PROC)

typedef XImage *(* PFN_XCreateImage_PROC) (Display *, Visual *, unsigned int, int, int, char *, unsigned int, unsigned int, int, int);
PFN_XCreateImage_PROC XCreateImage_PROC = 0;
#  define XCreateImage (assert(XCreateImage_PROC != 0), XCreateImage_PROC)

typedef XOC (* PFN_XCreateOC_PROC) (XOM, ...);
PFN_XCreateOC_PROC XCreateOC_PROC = 0;
#  define XCreateOC (assert(XCreateOC_PROC != 0), XCreateOC_PROC)

typedef Pixmap (* PFN_XCreatePixmap_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int);
PFN_XCreatePixmap_PROC XCreatePixmap_PROC = 0;
#  define XCreatePixmap (assert(XCreatePixmap_PROC != 0), XCreatePixmap_PROC)

typedef Cursor (* PFN_XCreatePixmapCursor_PROC) (Display *, Pixmap, Pixmap, XColor *, XColor *, unsigned int, unsigned int);
PFN_XCreatePixmapCursor_PROC XCreatePixmapCursor_PROC = 0;
#  define XCreatePixmapCursor (assert(XCreatePixmapCursor_PROC != 0), XCreatePixmapCursor_PROC)

typedef Pixmap (* PFN_XCreatePixmapFromBitmapData_PROC) (Display *, Drawable, char *, unsigned int, unsigned int, unsigned long, unsigned long, unsigned int);
PFN_XCreatePixmapFromBitmapData_PROC XCreatePixmapFromBitmapData_PROC = 0;
#  define XCreatePixmapFromBitmapData (assert(XCreatePixmapFromBitmapData_PROC != 0), XCreatePixmapFromBitmapData_PROC)

typedef Window (* PFN_XCreateSimpleWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int, unsigned int, unsigned long, unsigned long);
PFN_XCreateSimpleWindow_PROC XCreateSimpleWindow_PROC = 0;
#  define XCreateSimpleWindow (assert(XCreateSimpleWindow_PROC != 0), XCreateSimpleWindow_PROC)

typedef Window (* PFN_XCreateWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int, unsigned int, int, unsigned int, Visual *, unsigned long, XSetWindowAttributes *);
PFN_XCreateWindow_PROC XCreateWindow_PROC = 0;
#  define XCreateWindow (assert(XCreateWindow_PROC != 0), XCreateWindow_PROC)

typedef Colormap (* PFN_XDefaultColormap_PROC) (Display *, int);
PFN_XDefaultColormap_PROC XDefaultColormap_PROC = 0;
#  define XDefaultColormap (assert(XDefaultColormap_PROC != 0), XDefaultColormap_PROC)

typedef Colormap (* PFN_XDefaultColormapOfScreen_PROC) (Screen *);
PFN_XDefaultColormapOfScreen_PROC XDefaultColormapOfScreen_PROC = 0;
#  define XDefaultColormapOfScreen (assert(XDefaultColormapOfScreen_PROC != 0), XDefaultColormapOfScreen_PROC)

typedef int (* PFN_XDefaultDepth_PROC) (Display *, int);
PFN_XDefaultDepth_PROC XDefaultDepth_PROC = 0;
#  define XDefaultDepth (assert(XDefaultDepth_PROC != 0), XDefaultDepth_PROC)

typedef int (* PFN_XDefaultDepthOfScreen_PROC) (Screen *);
PFN_XDefaultDepthOfScreen_PROC XDefaultDepthOfScreen_PROC = 0;
#  define XDefaultDepthOfScreen (assert(XDefaultDepthOfScreen_PROC != 0), XDefaultDepthOfScreen_PROC)

typedef GC (* PFN_XDefaultGC_PROC) (Display *, int);
PFN_XDefaultGC_PROC XDefaultGC_PROC = 0;
#  define XDefaultGC (assert(XDefaultGC_PROC != 0), XDefaultGC_PROC)

typedef GC (* PFN_XDefaultGCOfScreen_PROC) (Screen *);
PFN_XDefaultGCOfScreen_PROC XDefaultGCOfScreen_PROC = 0;
#  define XDefaultGCOfScreen (assert(XDefaultGCOfScreen_PROC != 0), XDefaultGCOfScreen_PROC)

typedef Window (* PFN_XDefaultRootWindow_PROC) (Display *);
PFN_XDefaultRootWindow_PROC XDefaultRootWindow_PROC = 0;
#  define XDefaultRootWindow (assert(XDefaultRootWindow_PROC != 0), XDefaultRootWindow_PROC)

typedef int (* PFN_XDefaultScreen_PROC) (Display *);
PFN_XDefaultScreen_PROC XDefaultScreen_PROC = 0;
#  define XDefaultScreen (assert(XDefaultScreen_PROC != 0), XDefaultScreen_PROC)

typedef Screen *(* PFN_XDefaultScreenOfDisplay_PROC) (Display *);
PFN_XDefaultScreenOfDisplay_PROC XDefaultScreenOfDisplay_PROC = 0;
#  define XDefaultScreenOfDisplay (assert(XDefaultScreenOfDisplay_PROC != 0), XDefaultScreenOfDisplay_PROC)

typedef Visual *(* PFN_XDefaultVisual_PROC) (Display *, int);
PFN_XDefaultVisual_PROC XDefaultVisual_PROC = 0;
#  define XDefaultVisual (assert(XDefaultVisual_PROC != 0), XDefaultVisual_PROC)

typedef Visual *(* PFN_XDefaultVisualOfScreen_PROC) (Screen *);
PFN_XDefaultVisualOfScreen_PROC XDefaultVisualOfScreen_PROC = 0;
#  define XDefaultVisualOfScreen (assert(XDefaultVisualOfScreen_PROC != 0), XDefaultVisualOfScreen_PROC)

typedef int (* PFN_XDefineCursor_PROC) (Display *, Window, Cursor);
PFN_XDefineCursor_PROC XDefineCursor_PROC = 0;
#  define XDefineCursor (assert(XDefineCursor_PROC != 0), XDefineCursor_PROC)

typedef XModifierKeymap *(* PFN_XDeleteModifiermapEntry_PROC) (XModifierKeymap *, KeyCode, int);
PFN_XDeleteModifiermapEntry_PROC XDeleteModifiermapEntry_PROC = 0;
#  define XDeleteModifiermapEntry (assert(XDeleteModifiermapEntry_PROC != 0), XDeleteModifiermapEntry_PROC)

typedef int (* PFN_XDeleteProperty_PROC) (Display *, Window, Atom);
PFN_XDeleteProperty_PROC XDeleteProperty_PROC = 0;
#  define XDeleteProperty (assert(XDeleteProperty_PROC != 0), XDeleteProperty_PROC)

typedef void (* PFN_XDestroyIC_PROC) (XIC);
PFN_XDestroyIC_PROC XDestroyIC_PROC = 0;
#  define XDestroyIC (assert(XDestroyIC_PROC != 0), XDestroyIC_PROC)

typedef void (* PFN_XDestroyOC_PROC) (XOC);
PFN_XDestroyOC_PROC XDestroyOC_PROC = 0;
#  define XDestroyOC (assert(XDestroyOC_PROC != 0), XDestroyOC_PROC)

typedef int (* PFN_XDestroySubwindows_PROC) (Display *, Window);
PFN_XDestroySubwindows_PROC XDestroySubwindows_PROC = 0;
#  define XDestroySubwindows (assert(XDestroySubwindows_PROC != 0), XDestroySubwindows_PROC)

typedef int (* PFN_XDestroyWindow_PROC) (Display *, Window);
PFN_XDestroyWindow_PROC XDestroyWindow_PROC = 0;
#  define XDestroyWindow (assert(XDestroyWindow_PROC != 0), XDestroyWindow_PROC)

typedef int (* PFN_XDirectionalDependentDrawing_PROC) (XFontSet);
PFN_XDirectionalDependentDrawing_PROC XDirectionalDependentDrawing_PROC = 0;
#  define XDirectionalDependentDrawing (assert(XDirectionalDependentDrawing_PROC != 0), XDirectionalDependentDrawing_PROC)

typedef int (* PFN_XDisableAccessControl_PROC) (Display *);
PFN_XDisableAccessControl_PROC XDisableAccessControl_PROC = 0;
#  define XDisableAccessControl (assert(XDisableAccessControl_PROC != 0), XDisableAccessControl_PROC)

typedef int (* PFN_XDisplayCells_PROC) (Display *, int);
PFN_XDisplayCells_PROC XDisplayCells_PROC = 0;
#  define XDisplayCells (assert(XDisplayCells_PROC != 0), XDisplayCells_PROC)

typedef int (* PFN_XDisplayHeight_PROC) (Display *, int);
PFN_XDisplayHeight_PROC XDisplayHeight_PROC = 0;
#  define XDisplayHeight (assert(XDisplayHeight_PROC != 0), XDisplayHeight_PROC)

typedef int (* PFN_XDisplayHeightMM_PROC) (Display *, int);
PFN_XDisplayHeightMM_PROC XDisplayHeightMM_PROC = 0;
#  define XDisplayHeightMM (assert(XDisplayHeightMM_PROC != 0), XDisplayHeightMM_PROC)

typedef int (* PFN_XDisplayKeycodes_PROC) (Display *, int *, int *);
PFN_XDisplayKeycodes_PROC XDisplayKeycodes_PROC = 0;
#  define XDisplayKeycodes (assert(XDisplayKeycodes_PROC != 0), XDisplayKeycodes_PROC)

typedef unsigned long (* PFN_XDisplayMotionBufferSize_PROC) (Display *);
PFN_XDisplayMotionBufferSize_PROC XDisplayMotionBufferSize_PROC = 0;
#  define XDisplayMotionBufferSize (assert(XDisplayMotionBufferSize_PROC != 0), XDisplayMotionBufferSize_PROC)

typedef char *(* PFN_XDisplayName_PROC) (const char *);
PFN_XDisplayName_PROC XDisplayName_PROC = 0;
#  define XDisplayName (assert(XDisplayName_PROC != 0), XDisplayName_PROC)

typedef Display *(* PFN_XDisplayOfIM_PROC) (XIM);
PFN_XDisplayOfIM_PROC XDisplayOfIM_PROC = 0;
#  define XDisplayOfIM (assert(XDisplayOfIM_PROC != 0), XDisplayOfIM_PROC)

typedef Display *(* PFN_XDisplayOfOM_PROC) (XOM);
PFN_XDisplayOfOM_PROC XDisplayOfOM_PROC = 0;
#  define XDisplayOfOM (assert(XDisplayOfOM_PROC != 0), XDisplayOfOM_PROC)

typedef Display *(* PFN_XDisplayOfScreen_PROC) (Screen *);
PFN_XDisplayOfScreen_PROC XDisplayOfScreen_PROC = 0;
#  define XDisplayOfScreen (assert(XDisplayOfScreen_PROC != 0), XDisplayOfScreen_PROC)

typedef int (* PFN_XDisplayPlanes_PROC) (Display *, int);
PFN_XDisplayPlanes_PROC XDisplayPlanes_PROC = 0;
#  define XDisplayPlanes (assert(XDisplayPlanes_PROC != 0), XDisplayPlanes_PROC)

typedef char *(* PFN_XDisplayString_PROC) (Display *);
PFN_XDisplayString_PROC XDisplayString_PROC = 0;
#  define XDisplayString (assert(XDisplayString_PROC != 0), XDisplayString_PROC)

typedef int (* PFN_XDisplayWidth_PROC) (Display *, int);
PFN_XDisplayWidth_PROC XDisplayWidth_PROC = 0;
#  define XDisplayWidth (assert(XDisplayWidth_PROC != 0), XDisplayWidth_PROC)

typedef int (* PFN_XDisplayWidthMM_PROC) (Display *, int);
PFN_XDisplayWidthMM_PROC XDisplayWidthMM_PROC = 0;
#  define XDisplayWidthMM (assert(XDisplayWidthMM_PROC != 0), XDisplayWidthMM_PROC)

typedef int (* PFN_XDoesBackingStore_PROC) (Screen *);
PFN_XDoesBackingStore_PROC XDoesBackingStore_PROC = 0;
#  define XDoesBackingStore (assert(XDoesBackingStore_PROC != 0), XDoesBackingStore_PROC)

typedef int (* PFN_XDoesSaveUnders_PROC) (Screen *);
PFN_XDoesSaveUnders_PROC XDoesSaveUnders_PROC = 0;
#  define XDoesSaveUnders (assert(XDoesSaveUnders_PROC != 0), XDoesSaveUnders_PROC)

typedef int (* PFN_XDrawArc_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
PFN_XDrawArc_PROC XDrawArc_PROC = 0;
#  define XDrawArc (assert(XDrawArc_PROC != 0), XDrawArc_PROC)

typedef int (* PFN_XDrawArcs_PROC) (Display *, Drawable, GC, XArc *, int);
PFN_XDrawArcs_PROC XDrawArcs_PROC = 0;
#  define XDrawArcs (assert(XDrawArcs_PROC != 0), XDrawArcs_PROC)

typedef int (* PFN_XDrawImageString_PROC) (Display *, Drawable, GC, int, int, const char *, int);
PFN_XDrawImageString_PROC XDrawImageString_PROC = 0;
#  define XDrawImageString (assert(XDrawImageString_PROC != 0), XDrawImageString_PROC)

typedef int (* PFN_XDrawImageString16_PROC) (Display *, Drawable, GC, int, int, const XChar2b *, int);
PFN_XDrawImageString16_PROC XDrawImageString16_PROC = 0;
#  define XDrawImageString16 (assert(XDrawImageString16_PROC != 0), XDrawImageString16_PROC)

typedef int (* PFN_XDrawLine_PROC) (Display *, Drawable, GC, int, int, int, int);
PFN_XDrawLine_PROC XDrawLine_PROC = 0;
#  define XDrawLine (assert(XDrawLine_PROC != 0), XDrawLine_PROC)

typedef int (* PFN_XDrawLines_PROC) (Display *, Drawable, GC, XPoint *, int, int);
PFN_XDrawLines_PROC XDrawLines_PROC = 0;
#  define XDrawLines (assert(XDrawLines_PROC != 0), XDrawLines_PROC)

typedef int (* PFN_XDrawPoint_PROC) (Display *, Drawable, GC, int, int);
PFN_XDrawPoint_PROC XDrawPoint_PROC = 0;
#  define XDrawPoint (assert(XDrawPoint_PROC != 0), XDrawPoint_PROC)

typedef int (* PFN_XDrawPoints_PROC) (Display *, Drawable, GC, XPoint *, int, int);
PFN_XDrawPoints_PROC XDrawPoints_PROC = 0;
#  define XDrawPoints (assert(XDrawPoints_PROC != 0), XDrawPoints_PROC)

typedef int (* PFN_XDrawRectangle_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int);
PFN_XDrawRectangle_PROC XDrawRectangle_PROC = 0;
#  define XDrawRectangle (assert(XDrawRectangle_PROC != 0), XDrawRectangle_PROC)

typedef int (* PFN_XDrawRectangles_PROC) (Display *, Drawable, GC, XRectangle *, int);
PFN_XDrawRectangles_PROC XDrawRectangles_PROC = 0;
#  define XDrawRectangles (assert(XDrawRectangles_PROC != 0), XDrawRectangles_PROC)

typedef int (* PFN_XDrawSegments_PROC) (Display *, Drawable, GC, XSegment *, int);
PFN_XDrawSegments_PROC XDrawSegments_PROC = 0;
#  define XDrawSegments (assert(XDrawSegments_PROC != 0), XDrawSegments_PROC)

typedef int (* PFN_XDrawString_PROC) (Display *, Drawable, GC, int, int, const char *, int);
PFN_XDrawString_PROC XDrawString_PROC = 0;
#  define XDrawString (assert(XDrawString_PROC != 0), XDrawString_PROC)

typedef int (* PFN_XDrawString16_PROC) (Display *, Drawable, GC, int, int, const XChar2b *, int);
PFN_XDrawString16_PROC XDrawString16_PROC = 0;
#  define XDrawString16 (assert(XDrawString16_PROC != 0), XDrawString16_PROC)

typedef int (* PFN_XDrawText_PROC) (Display *, Drawable, GC, int, int, XTextItem *, int);
PFN_XDrawText_PROC XDrawText_PROC = 0;
#  define XDrawText (assert(XDrawText_PROC != 0), XDrawText_PROC)

typedef int (* PFN_XDrawText16_PROC) (Display *, Drawable, GC, int, int, XTextItem16 *, int);
PFN_XDrawText16_PROC XDrawText16_PROC = 0;
#  define XDrawText16 (assert(XDrawText16_PROC != 0), XDrawText16_PROC)

typedef XExtData **(* PFN_XEHeadOfExtensionList_PROC) (XEDataObject);
PFN_XEHeadOfExtensionList_PROC XEHeadOfExtensionList_PROC = 0;
#  define XEHeadOfExtensionList (assert(XEHeadOfExtensionList_PROC != 0), XEHeadOfExtensionList_PROC)

typedef int (* PFN_XEnableAccessControl_PROC) (Display *);
PFN_XEnableAccessControl_PROC XEnableAccessControl_PROC = 0;
#  define XEnableAccessControl (assert(XEnableAccessControl_PROC != 0), XEnableAccessControl_PROC)

typedef long (* PFN_XEventMaskOfScreen_PROC) (Screen *);
PFN_XEventMaskOfScreen_PROC XEventMaskOfScreen_PROC = 0;
#  define XEventMaskOfScreen (assert(XEventMaskOfScreen_PROC != 0), XEventMaskOfScreen_PROC)

typedef int (* PFN_XEventsQueued_PROC) (Display *, int);
PFN_XEventsQueued_PROC XEventsQueued_PROC = 0;
#  define XEventsQueued (assert(XEventsQueued_PROC != 0), XEventsQueued_PROC)

typedef long (* PFN_XExtendedMaxRequestSize_PROC) (Display *);
PFN_XExtendedMaxRequestSize_PROC XExtendedMaxRequestSize_PROC = 0;
#  define XExtendedMaxRequestSize (assert(XExtendedMaxRequestSize_PROC != 0), XExtendedMaxRequestSize_PROC)

typedef XFontSetExtents *(* PFN_XExtentsOfFontSet_PROC) (XFontSet);
PFN_XExtentsOfFontSet_PROC XExtentsOfFontSet_PROC = 0;
#  define XExtentsOfFontSet (assert(XExtentsOfFontSet_PROC != 0), XExtentsOfFontSet_PROC)

typedef char *(* PFN_XFetchBuffer_PROC) (Display *, int *, int);
PFN_XFetchBuffer_PROC XFetchBuffer_PROC = 0;
#  define XFetchBuffer (assert(XFetchBuffer_PROC != 0), XFetchBuffer_PROC)

typedef char *(* PFN_XFetchBytes_PROC) (Display *, int *);
PFN_XFetchBytes_PROC XFetchBytes_PROC = 0;
#  define XFetchBytes (assert(XFetchBytes_PROC != 0), XFetchBytes_PROC)

typedef int (* PFN_XFetchName_PROC) (Display *, Window, char **);
PFN_XFetchName_PROC XFetchName_PROC = 0;
#  define XFetchName (assert(XFetchName_PROC != 0), XFetchName_PROC)

typedef int (* PFN_XFillArc_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
PFN_XFillArc_PROC XFillArc_PROC = 0;
#  define XFillArc (assert(XFillArc_PROC != 0), XFillArc_PROC)

typedef int (* PFN_XFillArcs_PROC) (Display *, Drawable, GC, XArc *, int);
PFN_XFillArcs_PROC XFillArcs_PROC = 0;
#  define XFillArcs (assert(XFillArcs_PROC != 0), XFillArcs_PROC)

typedef int (* PFN_XFillPolygon_PROC) (Display *, Drawable, GC, XPoint *, int, int, int);
PFN_XFillPolygon_PROC XFillPolygon_PROC = 0;
#  define XFillPolygon (assert(XFillPolygon_PROC != 0), XFillPolygon_PROC)

typedef int (* PFN_XFillRectangle_PROC) (Display *, Drawable, GC, int, int, unsigned int, unsigned int);
PFN_XFillRectangle_PROC XFillRectangle_PROC = 0;
#  define XFillRectangle (assert(XFillRectangle_PROC != 0), XFillRectangle_PROC)

typedef int (* PFN_XFillRectangles_PROC) (Display *, Drawable, GC, XRectangle *, int);
PFN_XFillRectangles_PROC XFillRectangles_PROC = 0;
#  define XFillRectangles (assert(XFillRectangles_PROC != 0), XFillRectangles_PROC)

typedef int (* PFN_XFilterEvent_PROC) (XEvent *, Window);
PFN_XFilterEvent_PROC XFilterEvent_PROC = 0;
#  define XFilterEvent (assert(XFilterEvent_PROC != 0), XFilterEvent_PROC)

typedef XExtData *(* PFN_XFindOnExtensionList_PROC) (XExtData **, int);
PFN_XFindOnExtensionList_PROC XFindOnExtensionList_PROC = 0;
#  define XFindOnExtensionList (assert(XFindOnExtensionList_PROC != 0), XFindOnExtensionList_PROC)

typedef int (* PFN_XFlush_PROC) (Display *);
PFN_XFlush_PROC XFlush_PROC = 0;
#  define XFlush (assert(XFlush_PROC != 0), XFlush_PROC)

typedef void (* PFN_XFlushGC_PROC) (Display *, GC);
PFN_XFlushGC_PROC XFlushGC_PROC = 0;
#  define XFlushGC (assert(XFlushGC_PROC != 0), XFlushGC_PROC)

typedef int (* PFN_XFontsOfFontSet_PROC) (XFontSet, XFontStruct ***, char ***);
PFN_XFontsOfFontSet_PROC XFontsOfFontSet_PROC = 0;
#  define XFontsOfFontSet (assert(XFontsOfFontSet_PROC != 0), XFontsOfFontSet_PROC)

typedef int (* PFN_XForceScreenSaver_PROC) (Display *, int);
PFN_XForceScreenSaver_PROC XForceScreenSaver_PROC = 0;
#  define XForceScreenSaver (assert(XForceScreenSaver_PROC != 0), XForceScreenSaver_PROC)

typedef int (* PFN_XFree_PROC) (void *);
PFN_XFree_PROC XFree_PROC = 0;
#  define XFree (assert(XFree_PROC != 0), XFree_PROC)

typedef int (* PFN_XFreeColormap_PROC) (Display *, Colormap);
PFN_XFreeColormap_PROC XFreeColormap_PROC = 0;
#  define XFreeColormap (assert(XFreeColormap_PROC != 0), XFreeColormap_PROC)

typedef int (* PFN_XFreeColors_PROC) (Display *, Colormap, unsigned long *, int, unsigned long);
PFN_XFreeColors_PROC XFreeColors_PROC = 0;
#  define XFreeColors (assert(XFreeColors_PROC != 0), XFreeColors_PROC)

typedef int (* PFN_XFreeCursor_PROC) (Display *, Cursor);
PFN_XFreeCursor_PROC XFreeCursor_PROC = 0;
#  define XFreeCursor (assert(XFreeCursor_PROC != 0), XFreeCursor_PROC)

typedef void (* PFN_XFreeEventData_PROC) (Display *, XGenericEventCookie *);
PFN_XFreeEventData_PROC XFreeEventData_PROC = 0;
#  define XFreeEventData (assert(XFreeEventData_PROC != 0), XFreeEventData_PROC)

typedef int (* PFN_XFreeExtensionList_PROC) (char **);
PFN_XFreeExtensionList_PROC XFreeExtensionList_PROC = 0;
#  define XFreeExtensionList (assert(XFreeExtensionList_PROC != 0), XFreeExtensionList_PROC)

typedef int (* PFN_XFreeFont_PROC) (Display *, XFontStruct *);
PFN_XFreeFont_PROC XFreeFont_PROC = 0;
#  define XFreeFont (assert(XFreeFont_PROC != 0), XFreeFont_PROC)

typedef int (* PFN_XFreeFontInfo_PROC) (char **, XFontStruct *, int);
PFN_XFreeFontInfo_PROC XFreeFontInfo_PROC = 0;
#  define XFreeFontInfo (assert(XFreeFontInfo_PROC != 0), XFreeFontInfo_PROC)

typedef int (* PFN_XFreeFontNames_PROC) (char **);
PFN_XFreeFontNames_PROC XFreeFontNames_PROC = 0;
#  define XFreeFontNames (assert(XFreeFontNames_PROC != 0), XFreeFontNames_PROC)

typedef int (* PFN_XFreeFontPath_PROC) (char **);
PFN_XFreeFontPath_PROC XFreeFontPath_PROC = 0;
#  define XFreeFontPath (assert(XFreeFontPath_PROC != 0), XFreeFontPath_PROC)

typedef void (* PFN_XFreeFontSet_PROC) (Display *, XFontSet);
PFN_XFreeFontSet_PROC XFreeFontSet_PROC = 0;
#  define XFreeFontSet (assert(XFreeFontSet_PROC != 0), XFreeFontSet_PROC)

typedef int (* PFN_XFreeGC_PROC) (Display *, GC);
PFN_XFreeGC_PROC XFreeGC_PROC = 0;
#  define XFreeGC (assert(XFreeGC_PROC != 0), XFreeGC_PROC)

typedef int (* PFN_XFreeModifiermap_PROC) (XModifierKeymap *);
PFN_XFreeModifiermap_PROC XFreeModifiermap_PROC = 0;
#  define XFreeModifiermap (assert(XFreeModifiermap_PROC != 0), XFreeModifiermap_PROC)

typedef int (* PFN_XFreePixmap_PROC) (Display *, Pixmap);
PFN_XFreePixmap_PROC XFreePixmap_PROC = 0;
#  define XFreePixmap (assert(XFreePixmap_PROC != 0), XFreePixmap_PROC)

typedef void (* PFN_XFreeStringList_PROC) (char **);
PFN_XFreeStringList_PROC XFreeStringList_PROC = 0;
#  define XFreeStringList (assert(XFreeStringList_PROC != 0), XFreeStringList_PROC)

typedef int (* PFN_XFreeThreads_PROC) (void);
PFN_XFreeThreads_PROC XFreeThreads_PROC = 0;
#  define XFreeThreads (assert(XFreeThreads_PROC != 0), XFreeThreads_PROC)

typedef GContext (* PFN_XGContextFromGC_PROC) (GC);
PFN_XGContextFromGC_PROC XGContextFromGC_PROC = 0;
#  define XGContextFromGC (assert(XGContextFromGC_PROC != 0), XGContextFromGC_PROC)

typedef int (* PFN_XGeometry_PROC) (Display *, int, const char *, const char *, unsigned int, unsigned int, unsigned int, int, int, int *, int *, int *, int *);
PFN_XGeometry_PROC XGeometry_PROC = 0;
#  define XGeometry (assert(XGeometry_PROC != 0), XGeometry_PROC)

typedef char *(* PFN_XGetAtomName_PROC) (Display *, Atom);
PFN_XGetAtomName_PROC XGetAtomName_PROC = 0;
#  define XGetAtomName (assert(XGetAtomName_PROC != 0), XGetAtomName_PROC)

typedef int (* PFN_XGetAtomNames_PROC) (Display *, Atom *, int, char **);
PFN_XGetAtomNames_PROC XGetAtomNames_PROC = 0;
#  define XGetAtomNames (assert(XGetAtomNames_PROC != 0), XGetAtomNames_PROC)

typedef int (* PFN_XGetCommand_PROC) (Display *, Window, char ***, int *);
PFN_XGetCommand_PROC XGetCommand_PROC = 0;
#  define XGetCommand (assert(XGetCommand_PROC != 0), XGetCommand_PROC)

typedef char *(* PFN_XGetDefault_PROC) (Display *, const char *, const char *);
PFN_XGetDefault_PROC XGetDefault_PROC = 0;
#  define XGetDefault (assert(XGetDefault_PROC != 0), XGetDefault_PROC)

typedef int (* PFN_XGetErrorDatabaseText_PROC) (Display *, const char *, const char *, const char *, char *, int);
PFN_XGetErrorDatabaseText_PROC XGetErrorDatabaseText_PROC = 0;
#  define XGetErrorDatabaseText (assert(XGetErrorDatabaseText_PROC != 0), XGetErrorDatabaseText_PROC)

typedef int (* PFN_XGetErrorText_PROC) (Display *, int, char *, int);
PFN_XGetErrorText_PROC XGetErrorText_PROC = 0;
#  define XGetErrorText (assert(XGetErrorText_PROC != 0), XGetErrorText_PROC)

typedef int (* PFN_XGetEventData_PROC) (Display *, XGenericEventCookie *);
PFN_XGetEventData_PROC XGetEventData_PROC = 0;
#  define XGetEventData (assert(XGetEventData_PROC != 0), XGetEventData_PROC)

typedef char **(* PFN_XGetFontPath_PROC) (Display *, int *);
PFN_XGetFontPath_PROC XGetFontPath_PROC = 0;
#  define XGetFontPath (assert(XGetFontPath_PROC != 0), XGetFontPath_PROC)

typedef int (* PFN_XGetFontProperty_PROC) (XFontStruct *, Atom, unsigned long *);
PFN_XGetFontProperty_PROC XGetFontProperty_PROC = 0;
#  define XGetFontProperty (assert(XGetFontProperty_PROC != 0), XGetFontProperty_PROC)

typedef int (* PFN_XGetGCValues_PROC) (Display *, GC, unsigned long, XGCValues *);
PFN_XGetGCValues_PROC XGetGCValues_PROC = 0;
#  define XGetGCValues (assert(XGetGCValues_PROC != 0), XGetGCValues_PROC)

typedef int (* PFN_XGetGeometry_PROC) (Display *, Drawable, Window *, int *, int *, unsigned int *, unsigned int *, unsigned int *, unsigned int *);
PFN_XGetGeometry_PROC XGetGeometry_PROC = 0;
#  define XGetGeometry (assert(XGetGeometry_PROC != 0), XGetGeometry_PROC)

typedef char *(* PFN_XGetICValues_PROC) (XIC, ...);
PFN_XGetICValues_PROC XGetICValues_PROC = 0;
#  define XGetICValues (assert(XGetICValues_PROC != 0), XGetICValues_PROC)

typedef char *(* PFN_XGetIMValues_PROC) (XIM, ...);
PFN_XGetIMValues_PROC XGetIMValues_PROC = 0;
#  define XGetIMValues (assert(XGetIMValues_PROC != 0), XGetIMValues_PROC)

typedef int (* PFN_XGetIconName_PROC) (Display *, Window, char **);
PFN_XGetIconName_PROC XGetIconName_PROC = 0;
#  define XGetIconName (assert(XGetIconName_PROC != 0), XGetIconName_PROC)

typedef XImage *(* PFN_XGetImage_PROC) (Display *, Drawable, int, int, unsigned int, unsigned int, unsigned long, int);
PFN_XGetImage_PROC XGetImage_PROC = 0;
#  define XGetImage (assert(XGetImage_PROC != 0), XGetImage_PROC)

typedef int (* PFN_XGetInputFocus_PROC) (Display *, Window *, int *);
PFN_XGetInputFocus_PROC XGetInputFocus_PROC = 0;
#  define XGetInputFocus (assert(XGetInputFocus_PROC != 0), XGetInputFocus_PROC)

typedef int (* PFN_XGetKeyboardControl_PROC) (Display *, XKeyboardState *);
PFN_XGetKeyboardControl_PROC XGetKeyboardControl_PROC = 0;
#  define XGetKeyboardControl (assert(XGetKeyboardControl_PROC != 0), XGetKeyboardControl_PROC)

typedef KeySym *(* PFN_XGetKeyboardMapping_PROC) (Display *, KeyCode, int, int *);
PFN_XGetKeyboardMapping_PROC XGetKeyboardMapping_PROC = 0;
#  define XGetKeyboardMapping (assert(XGetKeyboardMapping_PROC != 0), XGetKeyboardMapping_PROC)

typedef XModifierKeymap *(* PFN_XGetModifierMapping_PROC) (Display *);
PFN_XGetModifierMapping_PROC XGetModifierMapping_PROC = 0;
#  define XGetModifierMapping (assert(XGetModifierMapping_PROC != 0), XGetModifierMapping_PROC)

typedef XTimeCoord *(* PFN_XGetMotionEvents_PROC) (Display *, Window, Time, Time, int *);
PFN_XGetMotionEvents_PROC XGetMotionEvents_PROC = 0;
#  define XGetMotionEvents (assert(XGetMotionEvents_PROC != 0), XGetMotionEvents_PROC)

typedef char *(* PFN_XGetOCValues_PROC) (XOC, ...);
PFN_XGetOCValues_PROC XGetOCValues_PROC = 0;
#  define XGetOCValues (assert(XGetOCValues_PROC != 0), XGetOCValues_PROC)

typedef char *(* PFN_XGetOMValues_PROC) (XOM, ...);
PFN_XGetOMValues_PROC XGetOMValues_PROC = 0;
#  define XGetOMValues (assert(XGetOMValues_PROC != 0), XGetOMValues_PROC)

typedef int (* PFN_XGetPointerControl_PROC) (Display *, int *, int *, int *);
PFN_XGetPointerControl_PROC XGetPointerControl_PROC = 0;
#  define XGetPointerControl (assert(XGetPointerControl_PROC != 0), XGetPointerControl_PROC)

typedef int (* PFN_XGetPointerMapping_PROC) (Display *, unsigned char *, int);
PFN_XGetPointerMapping_PROC XGetPointerMapping_PROC = 0;
#  define XGetPointerMapping (assert(XGetPointerMapping_PROC != 0), XGetPointerMapping_PROC)

typedef int (* PFN_XGetScreenSaver_PROC) (Display *, int *, int *, int *, int *);
PFN_XGetScreenSaver_PROC XGetScreenSaver_PROC = 0;
#  define XGetScreenSaver (assert(XGetScreenSaver_PROC != 0), XGetScreenSaver_PROC)

typedef Window (* PFN_XGetSelectionOwner_PROC) (Display *, Atom);
PFN_XGetSelectionOwner_PROC XGetSelectionOwner_PROC = 0;
#  define XGetSelectionOwner (assert(XGetSelectionOwner_PROC != 0), XGetSelectionOwner_PROC)

typedef XImage *(* PFN_XGetSubImage_PROC) (Display *, Drawable, int, int, unsigned int, unsigned int, unsigned long, int, XImage *, int, int);
PFN_XGetSubImage_PROC XGetSubImage_PROC = 0;
#  define XGetSubImage (assert(XGetSubImage_PROC != 0), XGetSubImage_PROC)

typedef int (* PFN_XGetTransientForHint_PROC) (Display *, Window, Window *);
PFN_XGetTransientForHint_PROC XGetTransientForHint_PROC = 0;
#  define XGetTransientForHint (assert(XGetTransientForHint_PROC != 0), XGetTransientForHint_PROC)

typedef int (* PFN_XGetWMColorwindow_maps_PROC) (Display *, Window, Window **, int *);
PFN_XGetWMColorwindow_maps_PROC XGetWMColorwindow_maps_PROC = 0;
#  define XGetWMColorwindow_maps (assert(XGetWMColorwindow_maps_PROC != 0), XGetWMColorwindow_maps_PROC)

typedef int (* PFN_XGetWMProtocols_PROC) (Display *, Window, Atom **, int *);
PFN_XGetWMProtocols_PROC XGetWMProtocols_PROC = 0;
#  define XGetWMProtocols (assert(XGetWMProtocols_PROC != 0), XGetWMProtocols_PROC)

typedef int (* PFN_XGetWindowAttributes_PROC) (Display *, Window, XWindowAttributes *);
PFN_XGetWindowAttributes_PROC XGetWindowAttributes_PROC = 0;
#  define XGetWindowAttributes (assert(XGetWindowAttributes_PROC != 0), XGetWindowAttributes_PROC)

typedef int (* PFN_XGetWindowProperty_PROC) (Display *, Window, Atom, long, long, int, Atom, Atom *, int *, unsigned long *, unsigned long *, unsigned char **);
PFN_XGetWindowProperty_PROC XGetWindowProperty_PROC = 0;
#  define XGetWindowProperty (assert(XGetWindowProperty_PROC != 0), XGetWindowProperty_PROC)

typedef int (* PFN_XGrabButton_PROC) (Display *, unsigned int, unsigned int, Window, int, unsigned int, int, int, Window, Cursor);
PFN_XGrabButton_PROC XGrabButton_PROC = 0;
#  define XGrabButton (assert(XGrabButton_PROC != 0), XGrabButton_PROC)

typedef int (* PFN_XGrabKey_PROC) (Display *, int, unsigned int, Window, int, int, int);
PFN_XGrabKey_PROC XGrabKey_PROC = 0;
#  define XGrabKey (assert(XGrabKey_PROC != 0), XGrabKey_PROC)

typedef int (* PFN_XGrabKeyboard_PROC) (Display *, Window, int, int, int, Time);
PFN_XGrabKeyboard_PROC XGrabKeyboard_PROC = 0;
#  define XGrabKeyboard (assert(XGrabKeyboard_PROC != 0), XGrabKeyboard_PROC)

typedef int (* PFN_XGrabPointer_PROC) (Display *, Window, int, unsigned int, int, int, Window, Cursor, Time);
PFN_XGrabPointer_PROC XGrabPointer_PROC = 0;
#  define XGrabPointer (assert(XGrabPointer_PROC != 0), XGrabPointer_PROC)

typedef int (* PFN_XGrabServer_PROC) (Display *);
PFN_XGrabServer_PROC XGrabServer_PROC = 0;
#  define XGrabServer (assert(XGrabServer_PROC != 0), XGrabServer_PROC)

typedef int (* PFN_XHeightMMOfScreen_PROC) (Screen *);
PFN_XHeightMMOfScreen_PROC XHeightMMOfScreen_PROC = 0;
#  define XHeightMMOfScreen (assert(XHeightMMOfScreen_PROC != 0), XHeightMMOfScreen_PROC)

typedef int (* PFN_XHeightOfScreen_PROC) (Screen *);
PFN_XHeightOfScreen_PROC XHeightOfScreen_PROC = 0;
#  define XHeightOfScreen (assert(XHeightOfScreen_PROC != 0), XHeightOfScreen_PROC)

typedef XIM (* PFN_XIMOfIC_PROC) (XIC);
PFN_XIMOfIC_PROC XIMOfIC_PROC = 0;
#  define XIMOfIC (assert(XIMOfIC_PROC != 0), XIMOfIC_PROC)

typedef int (* PFN_XIconifyWindow_PROC) (Display *, Window, int);
PFN_XIconifyWindow_PROC XIconifyWindow_PROC = 0;
#  define XIconifyWindow (assert(XIconifyWindow_PROC != 0), XIconifyWindow_PROC)

typedef int (* PFN_XIfEvent_PROC) (Display *, XEvent *, int (*)(Display *, XEvent *, XPointer), XPointer);
PFN_XIfEvent_PROC XIfEvent_PROC = 0;
#  define XIfEvent (assert(XIfEvent_PROC != 0), XIfEvent_PROC)

typedef int (* PFN_XImageByteOrder_PROC) (Display *);
PFN_XImageByteOrder_PROC XImageByteOrder_PROC = 0;
#  define XImageByteOrder (assert(XImageByteOrder_PROC != 0), XImageByteOrder_PROC)

typedef XExtCodes *(* PFN_XInitExtension_PROC) (Display *, const char *);
PFN_XInitExtension_PROC XInitExtension_PROC = 0;
#  define XInitExtension (assert(XInitExtension_PROC != 0), XInitExtension_PROC)

typedef int (* PFN_XInitImage_PROC) (XImage *);
PFN_XInitImage_PROC XInitImage_PROC = 0;
#  define XInitImage (assert(XInitImage_PROC != 0), XInitImage_PROC)

typedef int (* PFN_XInitThreads_PROC) (void);
PFN_XInitThreads_PROC XInitThreads_PROC = 0;
#  define XInitThreads (assert(XInitThreads_PROC != 0), XInitThreads_PROC)

typedef XModifierKeymap *(* PFN_XInsertModifiermapEntry_PROC) (XModifierKeymap *, KeyCode, int);
PFN_XInsertModifiermapEntry_PROC XInsertModifiermapEntry_PROC = 0;
#  define XInsertModifiermapEntry (assert(XInsertModifiermapEntry_PROC != 0), XInsertModifiermapEntry_PROC)

typedef int (* PFN_XInstallColormap_PROC) (Display *, Colormap);
PFN_XInstallColormap_PROC XInstallColormap_PROC = 0;
#  define XInstallColormap (assert(XInstallColormap_PROC != 0), XInstallColormap_PROC)

typedef Atom (* PFN_XInternAtom_PROC) (Display *, const char *, int);
PFN_XInternAtom_PROC XInternAtom_PROC = 0;
#  define XInternAtom (assert(XInternAtom_PROC != 0), XInternAtom_PROC)

typedef int (* PFN_XInternAtoms_PROC) (Display *, char **, int, int, Atom *);
PFN_XInternAtoms_PROC XInternAtoms_PROC = 0;
#  define XInternAtoms (assert(XInternAtoms_PROC != 0), XInternAtoms_PROC)

typedef int (* PFN_XInternalConnectionNumbers_PROC) (Display *, int **, int *);
PFN_XInternalConnectionNumbers_PROC XInternalConnectionNumbers_PROC = 0;
#  define XInternalConnectionNumbers (assert(XInternalConnectionNumbers_PROC != 0), XInternalConnectionNumbers_PROC)

typedef KeySym (* PFN_XKeycodeToKeysym_PROC) (Display *, KeyCode, int);
PFN_XKeycodeToKeysym_PROC XKeycodeToKeysym_PROC = 0;
#  define XKeycodeToKeysym (assert(XKeycodeToKeysym_PROC != 0), XKeycodeToKeysym_PROC)

typedef KeyCode (* PFN_XKeysymToKeycode_PROC) (Display *, KeySym);
PFN_XKeysymToKeycode_PROC XKeysymToKeycode_PROC = 0;
#  define XKeysymToKeycode (assert(XKeysymToKeycode_PROC != 0), XKeysymToKeycode_PROC)

typedef char *(* PFN_XKeysymToString_PROC) (KeySym);
PFN_XKeysymToString_PROC XKeysymToString_PROC = 0;
#  define XKeysymToString (assert(XKeysymToString_PROC != 0), XKeysymToString_PROC)

typedef int (* PFN_XKillClient_PROC) (Display *, XID);
PFN_XKillClient_PROC XKillClient_PROC = 0;
#  define XKillClient (assert(XKillClient_PROC != 0), XKillClient_PROC)

typedef unsigned long (* PFN_XLastKnownRequestProcessed_PROC) (Display *);
PFN_XLastKnownRequestProcessed_PROC XLastKnownRequestProcessed_PROC = 0;
#  define XLastKnownRequestProcessed (assert(XLastKnownRequestProcessed_PROC != 0), XLastKnownRequestProcessed_PROC)

typedef int *(* PFN_XListDepths_PROC) (Display *, int, int *);
PFN_XListDepths_PROC XListDepths_PROC = 0;
#  define XListDepths (assert(XListDepths_PROC != 0), XListDepths_PROC)

typedef char **(* PFN_XListExtensions_PROC) (Display *, int *);
PFN_XListExtensions_PROC XListExtensions_PROC = 0;
#  define XListExtensions (assert(XListExtensions_PROC != 0), XListExtensions_PROC)

typedef char **(* PFN_XListFonts_PROC) (Display *, const char *, int, int *);
PFN_XListFonts_PROC XListFonts_PROC = 0;
#  define XListFonts (assert(XListFonts_PROC != 0), XListFonts_PROC)

typedef char **(* PFN_XListFontsWithInfo_PROC) (Display *, const char *, int, int *, XFontStruct **);
PFN_XListFontsWithInfo_PROC XListFontsWithInfo_PROC = 0;
#  define XListFontsWithInfo (assert(XListFontsWithInfo_PROC != 0), XListFontsWithInfo_PROC)

typedef XHostAddress *(* PFN_XListHosts_PROC) (Display *, int *, int *);
PFN_XListHosts_PROC XListHosts_PROC = 0;
#  define XListHosts (assert(XListHosts_PROC != 0), XListHosts_PROC)

typedef Colormap *(* PFN_XListInstalledColormaps_PROC) (Display *, Window, int *);
PFN_XListInstalledColormaps_PROC XListInstalledColormaps_PROC = 0;
#  define XListInstalledColormaps (assert(XListInstalledColormaps_PROC != 0), XListInstalledColormaps_PROC)

typedef XPixmapFormatValues *(* PFN_XListPixmapFormats_PROC) (Display *, int *);
PFN_XListPixmapFormats_PROC XListPixmapFormats_PROC = 0;
#  define XListPixmapFormats (assert(XListPixmapFormats_PROC != 0), XListPixmapFormats_PROC)

typedef Atom *(* PFN_XListProperties_PROC) (Display *, Window, int *);
PFN_XListProperties_PROC XListProperties_PROC = 0;
#  define XListProperties (assert(XListProperties_PROC != 0), XListProperties_PROC)

typedef Font (* PFN_XLoadFont_PROC) (Display *, const char *);
PFN_XLoadFont_PROC XLoadFont_PROC = 0;
#  define XLoadFont (assert(XLoadFont_PROC != 0), XLoadFont_PROC)

typedef XFontStruct *(* PFN_XLoadQueryFont_PROC) (Display *, const char *);
PFN_XLoadQueryFont_PROC XLoadQueryFont_PROC = 0;
#  define XLoadQueryFont (assert(XLoadQueryFont_PROC != 0), XLoadQueryFont_PROC)

typedef char *(* PFN_XLocaleOfFontSet_PROC) (XFontSet);
PFN_XLocaleOfFontSet_PROC XLocaleOfFontSet_PROC = 0;
#  define XLocaleOfFontSet (assert(XLocaleOfFontSet_PROC != 0), XLocaleOfFontSet_PROC)

typedef char *(* PFN_XLocaleOfIM_PROC) (XIM);
PFN_XLocaleOfIM_PROC XLocaleOfIM_PROC = 0;
#  define XLocaleOfIM (assert(XLocaleOfIM_PROC != 0), XLocaleOfIM_PROC)

typedef char *(* PFN_XLocaleOfOM_PROC) (XOM);
PFN_XLocaleOfOM_PROC XLocaleOfOM_PROC = 0;
#  define XLocaleOfOM (assert(XLocaleOfOM_PROC != 0), XLocaleOfOM_PROC)

typedef void (* PFN_XLockDisplay_PROC) (Display *);
PFN_XLockDisplay_PROC XLockDisplay_PROC = 0;
#  define XLockDisplay (assert(XLockDisplay_PROC != 0), XLockDisplay_PROC)

typedef int (* PFN_XLookupColor_PROC) (Display *, Colormap, const char *, XColor *, XColor *);
PFN_XLookupColor_PROC XLookupColor_PROC = 0;
#  define XLookupColor (assert(XLookupColor_PROC != 0), XLookupColor_PROC)

typedef KeySym (* PFN_XLookupKeysym_PROC) (XKeyEvent *, int);
PFN_XLookupKeysym_PROC XLookupKeysym_PROC = 0;
#  define XLookupKeysym (assert(XLookupKeysym_PROC != 0), XLookupKeysym_PROC)

typedef int (* PFN_XLowerWindow_PROC) (Display *, Window);
PFN_XLowerWindow_PROC XLowerWindow_PROC = 0;
#  define XLowerWindow (assert(XLowerWindow_PROC != 0), XLowerWindow_PROC)

typedef int (* PFN_XMapRaised_PROC) (Display *, Window);
PFN_XMapRaised_PROC XMapRaised_PROC = 0;
#  define XMapRaised (assert(XMapRaised_PROC != 0), XMapRaised_PROC)

typedef int (* PFN_XMapSubwindows_PROC) (Display *, Window);
PFN_XMapSubwindows_PROC XMapSubwindows_PROC = 0;
#  define XMapSubwindows (assert(XMapSubwindows_PROC != 0), XMapSubwindows_PROC)

typedef int (* PFN_XMapWindow_PROC) (Display *, Window);
PFN_XMapWindow_PROC XMapWindow_PROC = 0;
#  define XMapWindow (assert(XMapWindow_PROC != 0), XMapWindow_PROC)

typedef int (* PFN_XMaskEvent_PROC) (Display *, long, XEvent *);
PFN_XMaskEvent_PROC XMaskEvent_PROC = 0;
#  define XMaskEvent (assert(XMaskEvent_PROC != 0), XMaskEvent_PROC)

typedef int (* PFN_XMaxCmapsOfScreen_PROC) (Screen *);
PFN_XMaxCmapsOfScreen_PROC XMaxCmapsOfScreen_PROC = 0;
#  define XMaxCmapsOfScreen (assert(XMaxCmapsOfScreen_PROC != 0), XMaxCmapsOfScreen_PROC)

typedef long (* PFN_XMaxRequestSize_PROC) (Display *);
PFN_XMaxRequestSize_PROC XMaxRequestSize_PROC = 0;
#  define XMaxRequestSize (assert(XMaxRequestSize_PROC != 0), XMaxRequestSize_PROC)

typedef int (* PFN_XMinCmapsOfScreen_PROC) (Screen *);
PFN_XMinCmapsOfScreen_PROC XMinCmapsOfScreen_PROC = 0;
#  define XMinCmapsOfScreen (assert(XMinCmapsOfScreen_PROC != 0), XMinCmapsOfScreen_PROC)

typedef int (* PFN_XMoveResizeWindow_PROC) (Display *, Window, int, int, unsigned int, unsigned int);
PFN_XMoveResizeWindow_PROC XMoveResizeWindow_PROC = 0;
#  define XMoveResizeWindow (assert(XMoveResizeWindow_PROC != 0), XMoveResizeWindow_PROC)

typedef int (* PFN_XMoveWindow_PROC) (Display *, Window, int, int);
PFN_XMoveWindow_PROC XMoveWindow_PROC = 0;
#  define XMoveWindow (assert(XMoveWindow_PROC != 0), XMoveWindow_PROC)

typedef XModifierKeymap *(* PFN_XNewModifiermap_PROC) (int);
PFN_XNewModifiermap_PROC XNewModifiermap_PROC = 0;
#  define XNewModifiermap (assert(XNewModifiermap_PROC != 0), XNewModifiermap_PROC)

typedef int (* PFN_XNextEvent_PROC) (Display *, XEvent *);
PFN_XNextEvent_PROC XNextEvent_PROC = 0;
#  define XNextEvent (assert(XNextEvent_PROC != 0), XNextEvent_PROC)

typedef unsigned long (* PFN_XNextRequest_PROC) (Display *);
PFN_XNextRequest_PROC XNextRequest_PROC = 0;
#  define XNextRequest (assert(XNextRequest_PROC != 0), XNextRequest_PROC)

typedef int (* PFN_XNoOp_PROC) (Display *);
PFN_XNoOp_PROC XNoOp_PROC = 0;
#  define XNoOp (assert(XNoOp_PROC != 0), XNoOp_PROC)

typedef XOM (* PFN_XOMOfOC_PROC) (XOC);
PFN_XOMOfOC_PROC XOMOfOC_PROC = 0;
#  define XOMOfOC (assert(XOMOfOC_PROC != 0), XOMOfOC_PROC)

typedef Display *(* PFN_XOpenDisplay_PROC) (const char *);
PFN_XOpenDisplay_PROC XOpenDisplay_PROC = 0;
#  define XOpenDisplay (assert(XOpenDisplay_PROC != 0), XOpenDisplay_PROC)

typedef XIM (* PFN_XOpenIM_PROC) (Display *, struct _XrmHashBucketRec *, char *, char *);
PFN_XOpenIM_PROC XOpenIM_PROC = 0;
#  define XOpenIM (assert(XOpenIM_PROC != 0), XOpenIM_PROC)

typedef XOM (* PFN_XOpenOM_PROC) (Display *, struct _XrmHashBucketRec *, const char *, const char *);
PFN_XOpenOM_PROC XOpenOM_PROC = 0;
#  define XOpenOM (assert(XOpenOM_PROC != 0), XOpenOM_PROC)

typedef int (* PFN_XParseColor_PROC) (Display *, Colormap, const char *, XColor *);
PFN_XParseColor_PROC XParseColor_PROC = 0;
#  define XParseColor (assert(XParseColor_PROC != 0), XParseColor_PROC)

typedef int (* PFN_XParseGeometry_PROC) (const char *, int *, int *, unsigned int *, unsigned int *);
PFN_XParseGeometry_PROC XParseGeometry_PROC = 0;
#  define XParseGeometry (assert(XParseGeometry_PROC != 0), XParseGeometry_PROC)

typedef int (* PFN_XPeekEvent_PROC) (Display *, XEvent *);
PFN_XPeekEvent_PROC XPeekEvent_PROC = 0;
#  define XPeekEvent (assert(XPeekEvent_PROC != 0), XPeekEvent_PROC)

typedef int (* PFN_XPeekIfEvent_PROC) (Display *, XEvent *, int (*)(Display *, XEvent *, XPointer), XPointer);
PFN_XPeekIfEvent_PROC XPeekIfEvent_PROC = 0;
#  define XPeekIfEvent (assert(XPeekIfEvent_PROC != 0), XPeekIfEvent_PROC)

typedef int (* PFN_XPending_PROC) (Display *);
PFN_XPending_PROC XPending_PROC = 0;
#  define XPending (assert(XPending_PROC != 0), XPending_PROC)

typedef int (* PFN_XPlanesOfScreen_PROC) (Screen *);
PFN_XPlanesOfScreen_PROC XPlanesOfScreen_PROC = 0;
#  define XPlanesOfScreen (assert(XPlanesOfScreen_PROC != 0), XPlanesOfScreen_PROC)

typedef void (* PFN_XProcessInternalConnection_PROC) (Display *, int);
PFN_XProcessInternalConnection_PROC XProcessInternalConnection_PROC = 0;
#  define XProcessInternalConnection (assert(XProcessInternalConnection_PROC != 0), XProcessInternalConnection_PROC)

typedef int (* PFN_XProtocolRevision_PROC) (Display *);
PFN_XProtocolRevision_PROC XProtocolRevision_PROC = 0;
#  define XProtocolRevision (assert(XProtocolRevision_PROC != 0), XProtocolRevision_PROC)

typedef int (* PFN_XProtocolVersion_PROC) (Display *);
PFN_XProtocolVersion_PROC XProtocolVersion_PROC = 0;
#  define XProtocolVersion (assert(XProtocolVersion_PROC != 0), XProtocolVersion_PROC)

typedef int (* PFN_XPutBackEvent_PROC) (Display *, XEvent *);
PFN_XPutBackEvent_PROC XPutBackEvent_PROC = 0;
#  define XPutBackEvent (assert(XPutBackEvent_PROC != 0), XPutBackEvent_PROC)

typedef int (* PFN_XPutImage_PROC) (Display *, Drawable, GC, XImage *, int, int, int, int, unsigned int, unsigned int);
PFN_XPutImage_PROC XPutImage_PROC = 0;
#  define XPutImage (assert(XPutImage_PROC != 0), XPutImage_PROC)

typedef int (* PFN_XQLength_PROC) (Display *);
PFN_XQLength_PROC XQLength_PROC = 0;
#  define XQLength (assert(XQLength_PROC != 0), XQLength_PROC)

typedef int (* PFN_XQueryBestCursor_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestCursor_PROC XQueryBestCursor_PROC = 0;
#  define XQueryBestCursor (assert(XQueryBestCursor_PROC != 0), XQueryBestCursor_PROC)

typedef int (* PFN_XQueryBestSize_PROC) (Display *, int, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestSize_PROC XQueryBestSize_PROC = 0;
#  define XQueryBestSize (assert(XQueryBestSize_PROC != 0), XQueryBestSize_PROC)

typedef int (* PFN_XQueryBestStipple_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestStipple_PROC XQueryBestStipple_PROC = 0;
#  define XQueryBestStipple (assert(XQueryBestStipple_PROC != 0), XQueryBestStipple_PROC)

typedef int (* PFN_XQueryBestTile_PROC) (Display *, Drawable, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XQueryBestTile_PROC XQueryBestTile_PROC = 0;
#  define XQueryBestTile (assert(XQueryBestTile_PROC != 0), XQueryBestTile_PROC)

typedef int (* PFN_XQueryColor_PROC) (Display *, Colormap, XColor *);
PFN_XQueryColor_PROC XQueryColor_PROC = 0;
#  define XQueryColor (assert(XQueryColor_PROC != 0), XQueryColor_PROC)

typedef int (* PFN_XQueryColors_PROC) (Display *, Colormap, XColor *, int);
PFN_XQueryColors_PROC XQueryColors_PROC = 0;
#  define XQueryColors (assert(XQueryColors_PROC != 0), XQueryColors_PROC)

typedef int (* PFN_XQueryExtension_PROC) (Display *, const char *, int *, int *, int *);
PFN_XQueryExtension_PROC XQueryExtension_PROC = 0;
#  define XQueryExtension (assert(XQueryExtension_PROC != 0), XQueryExtension_PROC)

typedef XFontStruct *(* PFN_XQueryFont_PROC) (Display *, XID);
PFN_XQueryFont_PROC XQueryFont_PROC = 0;
#  define XQueryFont (assert(XQueryFont_PROC != 0), XQueryFont_PROC)

typedef int (* PFN_XQueryKeymap_PROC) (Display *, char[32]);
PFN_XQueryKeymap_PROC XQueryKeymap_PROC = 0;
#  define XQueryKeymap (assert(XQueryKeymap_PROC != 0), XQueryKeymap_PROC)

typedef int (* PFN_XQueryPointer_PROC) (Display *, Window, Window *, Window *, int *, int *, int *, int *, unsigned int *);
PFN_XQueryPointer_PROC XQueryPointer_PROC = 0;
#  define XQueryPointer (assert(XQueryPointer_PROC != 0), XQueryPointer_PROC)

typedef int (* PFN_XQueryTextExtents_PROC) (Display *, XID, const char *, int, int *, int *, int *, XCharStruct *);
PFN_XQueryTextExtents_PROC XQueryTextExtents_PROC = 0;
#  define XQueryTextExtents (assert(XQueryTextExtents_PROC != 0), XQueryTextExtents_PROC)

typedef int (* PFN_XQueryTextExtents16_PROC) (Display *, XID, const XChar2b *, int, int *, int *, int *, XCharStruct *);
PFN_XQueryTextExtents16_PROC XQueryTextExtents16_PROC = 0;
#  define XQueryTextExtents16 (assert(XQueryTextExtents16_PROC != 0), XQueryTextExtents16_PROC)

typedef int (* PFN_XQueryTree_PROC) (Display *, Window, Window *, Window *, Window **, unsigned int *);
PFN_XQueryTree_PROC XQueryTree_PROC = 0;
#  define XQueryTree (assert(XQueryTree_PROC != 0), XQueryTree_PROC)

typedef int (* PFN_XRaiseWindow_PROC) (Display *, Window);
PFN_XRaiseWindow_PROC XRaiseWindow_PROC = 0;
#  define XRaiseWindow (assert(XRaiseWindow_PROC != 0), XRaiseWindow_PROC)

typedef int (* PFN_XReadBitmapFile_PROC) (Display *, Drawable, const char *, unsigned int *, unsigned int *, Pixmap *, int *, int *);
PFN_XReadBitmapFile_PROC XReadBitmapFile_PROC = 0;
#  define XReadBitmapFile (assert(XReadBitmapFile_PROC != 0), XReadBitmapFile_PROC)

typedef int (* PFN_XReadBitmapFileData_PROC) (const char *, unsigned int *, unsigned int *, unsigned char **, int *, int *);
PFN_XReadBitmapFileData_PROC XReadBitmapFileData_PROC = 0;
#  define XReadBitmapFileData (assert(XReadBitmapFileData_PROC != 0), XReadBitmapFileData_PROC)

typedef int (* PFN_XRebindKeysym_PROC) (Display *, KeySym, KeySym *, int, const unsigned char *, int);
PFN_XRebindKeysym_PROC XRebindKeysym_PROC = 0;
#  define XRebindKeysym (assert(XRebindKeysym_PROC != 0), XRebindKeysym_PROC)

typedef int (* PFN_XRecolorCursor_PROC) (Display *, Cursor, XColor *, XColor *);
PFN_XRecolorCursor_PROC XRecolorCursor_PROC = 0;
#  define XRecolorCursor (assert(XRecolorCursor_PROC != 0), XRecolorCursor_PROC)

typedef int (* PFN_XReconfigureWMWindow_PROC) (Display *, Window, int, unsigned int, XWindowChanges *);
PFN_XReconfigureWMWindow_PROC XReconfigureWMWindow_PROC = 0;
#  define XReconfigureWMWindow (assert(XReconfigureWMWindow_PROC != 0), XReconfigureWMWindow_PROC)

typedef int (* PFN_XRefreshKeyboardMapping_PROC) (XMappingEvent *);
PFN_XRefreshKeyboardMapping_PROC XRefreshKeyboardMapping_PROC = 0;
#  define XRefreshKeyboardMapping (assert(XRefreshKeyboardMapping_PROC != 0), XRefreshKeyboardMapping_PROC)

typedef int (* PFN_XRegisterIMInstantiateCallback_PROC) (Display *, struct _XrmHashBucketRec *, char *, char *, XIDProc, XPointer);
PFN_XRegisterIMInstantiateCallback_PROC XRegisterIMInstantiateCallback_PROC = 0;
#  define XRegisterIMInstantiateCallback (assert(XRegisterIMInstantiateCallback_PROC != 0), XRegisterIMInstantiateCallback_PROC)

typedef void (* PFN_XRemoveConnectionWatch_PROC) (Display *, XConnectionWatchProc, XPointer);
PFN_XRemoveConnectionWatch_PROC XRemoveConnectionWatch_PROC = 0;
#  define XRemoveConnectionWatch (assert(XRemoveConnectionWatch_PROC != 0), XRemoveConnectionWatch_PROC)

typedef int (* PFN_XRemoveFromSaveSet_PROC) (Display *, Window);
PFN_XRemoveFromSaveSet_PROC XRemoveFromSaveSet_PROC = 0;
#  define XRemoveFromSaveSet (assert(XRemoveFromSaveSet_PROC != 0), XRemoveFromSaveSet_PROC)

typedef int (* PFN_XRemoveHost_PROC) (Display *, XHostAddress *);
PFN_XRemoveHost_PROC XRemoveHost_PROC = 0;
#  define XRemoveHost (assert(XRemoveHost_PROC != 0), XRemoveHost_PROC)

typedef int (* PFN_XRemoveHosts_PROC) (Display *, XHostAddress *, int);
PFN_XRemoveHosts_PROC XRemoveHosts_PROC = 0;
#  define XRemoveHosts (assert(XRemoveHosts_PROC != 0), XRemoveHosts_PROC)

typedef int (* PFN_XReparentWindow_PROC) (Display *, Window, Window, int, int);
PFN_XReparentWindow_PROC XReparentWindow_PROC = 0;
#  define XReparentWindow (assert(XReparentWindow_PROC != 0), XReparentWindow_PROC)

typedef int (* PFN_XResetScreenSaver_PROC) (Display *);
PFN_XResetScreenSaver_PROC XResetScreenSaver_PROC = 0;
#  define XResetScreenSaver (assert(XResetScreenSaver_PROC != 0), XResetScreenSaver_PROC)

typedef int (* PFN_XResizeWindow_PROC) (Display *, Window, unsigned int, unsigned int);
PFN_XResizeWindow_PROC XResizeWindow_PROC = 0;
#  define XResizeWindow (assert(XResizeWindow_PROC != 0), XResizeWindow_PROC)

typedef char *(* PFN_XResourceManagerString_PROC) (Display *);
PFN_XResourceManagerString_PROC XResourceManagerString_PROC = 0;
#  define XResourceManagerString (assert(XResourceManagerString_PROC != 0), XResourceManagerString_PROC)

typedef int (* PFN_XRestackWindows_PROC) (Display *, Window *, int);
PFN_XRestackWindows_PROC XRestackWindows_PROC = 0;
#  define XRestackWindows (assert(XRestackWindows_PROC != 0), XRestackWindows_PROC)

typedef Window (* PFN_XRootWindow_PROC) (Display *, int);
PFN_XRootWindow_PROC XRootWindow_PROC = 0;
#  define XRootWindow (assert(XRootWindow_PROC != 0), XRootWindow_PROC)

typedef Window (* PFN_XRootWindowOfScreen_PROC) (Screen *);
PFN_XRootWindowOfScreen_PROC XRootWindowOfScreen_PROC = 0;
#  define XRootWindowOfScreen (assert(XRootWindowOfScreen_PROC != 0), XRootWindowOfScreen_PROC)

typedef int (* PFN_XRotateBuffers_PROC) (Display *, int);
PFN_XRotateBuffers_PROC XRotateBuffers_PROC = 0;
#  define XRotateBuffers (assert(XRotateBuffers_PROC != 0), XRotateBuffers_PROC)

typedef int (* PFN_XRotateWindowProperties_PROC) (Display *, Window, Atom *, int, int);
PFN_XRotateWindowProperties_PROC XRotateWindowProperties_PROC = 0;
#  define XRotateWindowProperties (assert(XRotateWindowProperties_PROC != 0), XRotateWindowProperties_PROC)

typedef int (* PFN_XScreenCount_PROC) (Display *);
PFN_XScreenCount_PROC XScreenCount_PROC = 0;
#  define XScreenCount (assert(XScreenCount_PROC != 0), XScreenCount_PROC)

typedef int (* PFN_XScreenNumberOfScreen_PROC) (Screen *);
PFN_XScreenNumberOfScreen_PROC XScreenNumberOfScreen_PROC = 0;
#  define XScreenNumberOfScreen (assert(XScreenNumberOfScreen_PROC != 0), XScreenNumberOfScreen_PROC)

typedef Screen *(* PFN_XScreenOfDisplay_PROC) (Display *, int);
PFN_XScreenOfDisplay_PROC XScreenOfDisplay_PROC = 0;
#  define XScreenOfDisplay (assert(XScreenOfDisplay_PROC != 0), XScreenOfDisplay_PROC)

typedef char *(* PFN_XScreenResourceString_PROC) (Screen *);
PFN_XScreenResourceString_PROC XScreenResourceString_PROC = 0;
#  define XScreenResourceString (assert(XScreenResourceString_PROC != 0), XScreenResourceString_PROC)

typedef int (* PFN_XSelectInput_PROC) (Display *, Window, long);
PFN_XSelectInput_PROC XSelectInput_PROC = 0;
#  define XSelectInput (assert(XSelectInput_PROC != 0), XSelectInput_PROC)

typedef int (* PFN_XSendEvent_PROC) (Display *, Window, int, long, XEvent *);
PFN_XSendEvent_PROC XSendEvent_PROC = 0;
#  define XSendEvent (assert(XSendEvent_PROC != 0), XSendEvent_PROC)

typedef char *(* PFN_XServerVendor_PROC) (Display *);
PFN_XServerVendor_PROC XServerVendor_PROC = 0;
#  define XServerVendor (assert(XServerVendor_PROC != 0), XServerVendor_PROC)

typedef int (* PFN_XSetAccessControl_PROC) (Display *, int);
PFN_XSetAccessControl_PROC XSetAccessControl_PROC = 0;
#  define XSetAccessControl (assert(XSetAccessControl_PROC != 0), XSetAccessControl_PROC)

typedef int (* PFN_XSetArcMode_PROC) (Display *, GC, int);
PFN_XSetArcMode_PROC XSetArcMode_PROC = 0;
#  define XSetArcMode (assert(XSetArcMode_PROC != 0), XSetArcMode_PROC)

typedef void (* PFN_XSetAuthorization_PROC) (char *, int, char *, int);
PFN_XSetAuthorization_PROC XSetAuthorization_PROC = 0;
#  define XSetAuthorization (assert(XSetAuthorization_PROC != 0), XSetAuthorization_PROC)

typedef int (* PFN_XSetBackground_PROC) (Display *, GC, unsigned long);
PFN_XSetBackground_PROC XSetBackground_PROC = 0;
#  define XSetBackground (assert(XSetBackground_PROC != 0), XSetBackground_PROC)

typedef int (* PFN_XSetClipMask_PROC) (Display *, GC, Pixmap);
PFN_XSetClipMask_PROC XSetClipMask_PROC = 0;
#  define XSetClipMask (assert(XSetClipMask_PROC != 0), XSetClipMask_PROC)

typedef int (* PFN_XSetClipOrigin_PROC) (Display *, GC, int, int);
PFN_XSetClipOrigin_PROC XSetClipOrigin_PROC = 0;
#  define XSetClipOrigin (assert(XSetClipOrigin_PROC != 0), XSetClipOrigin_PROC)

typedef int (* PFN_XSetClipRectangles_PROC) (Display *, GC, int, int, XRectangle *, int, int);
PFN_XSetClipRectangles_PROC XSetClipRectangles_PROC = 0;
#  define XSetClipRectangles (assert(XSetClipRectangles_PROC != 0), XSetClipRectangles_PROC)

typedef int (* PFN_XSetCloseDownMode_PROC) (Display *, int);
PFN_XSetCloseDownMode_PROC XSetCloseDownMode_PROC = 0;
#  define XSetCloseDownMode (assert(XSetCloseDownMode_PROC != 0), XSetCloseDownMode_PROC)

typedef int (* PFN_XSetCommand_PROC) (Display *, Window, char **, int);
PFN_XSetCommand_PROC XSetCommand_PROC = 0;
#  define XSetCommand (assert(XSetCommand_PROC != 0), XSetCommand_PROC)

typedef int (* PFN_XSetDashes_PROC) (Display *, GC, int, const char *, int);
PFN_XSetDashes_PROC XSetDashes_PROC = 0;
#  define XSetDashes (assert(XSetDashes_PROC != 0), XSetDashes_PROC)

typedef XErrorHandler (* PFN_XSetErrorHandler_PROC) (XErrorHandler);
PFN_XSetErrorHandler_PROC XSetErrorHandler_PROC = 0;
#  define XSetErrorHandler (assert(XSetErrorHandler_PROC != 0), XSetErrorHandler_PROC)

typedef int (* PFN_XSetFillRule_PROC) (Display *, GC, int);
PFN_XSetFillRule_PROC XSetFillRule_PROC = 0;
#  define XSetFillRule (assert(XSetFillRule_PROC != 0), XSetFillRule_PROC)

typedef int (* PFN_XSetFillStyle_PROC) (Display *, GC, int);
PFN_XSetFillStyle_PROC XSetFillStyle_PROC = 0;
#  define XSetFillStyle (assert(XSetFillStyle_PROC != 0), XSetFillStyle_PROC)

typedef int (* PFN_XSetFont_PROC) (Display *, GC, Font);
PFN_XSetFont_PROC XSetFont_PROC = 0;
#  define XSetFont (assert(XSetFont_PROC != 0), XSetFont_PROC)

typedef int (* PFN_XSetFontPath_PROC) (Display *, char **, int);
PFN_XSetFontPath_PROC XSetFontPath_PROC = 0;
#  define XSetFontPath (assert(XSetFontPath_PROC != 0), XSetFontPath_PROC)

typedef int (* PFN_XSetForeground_PROC) (Display *, GC, unsigned long);
PFN_XSetForeground_PROC XSetForeground_PROC = 0;
#  define XSetForeground (assert(XSetForeground_PROC != 0), XSetForeground_PROC)

typedef int (* PFN_XSetFunction_PROC) (Display *, GC, int);
PFN_XSetFunction_PROC XSetFunction_PROC = 0;
#  define XSetFunction (assert(XSetFunction_PROC != 0), XSetFunction_PROC)

typedef int (* PFN_XSetGraphicsExposures_PROC) (Display *, GC, int);
PFN_XSetGraphicsExposures_PROC XSetGraphicsExposures_PROC = 0;
#  define XSetGraphicsExposures (assert(XSetGraphicsExposures_PROC != 0), XSetGraphicsExposures_PROC)

typedef void (* PFN_XSetICFocus_PROC) (XIC);
PFN_XSetICFocus_PROC XSetICFocus_PROC = 0;
#  define XSetICFocus (assert(XSetICFocus_PROC != 0), XSetICFocus_PROC)

typedef char *(* PFN_XSetICValues_PROC) (XIC, ...);
PFN_XSetICValues_PROC XSetICValues_PROC = 0;
#  define XSetICValues (assert(XSetICValues_PROC != 0), XSetICValues_PROC)

typedef char *(* PFN_XSetIMValues_PROC) (XIM, ...);
PFN_XSetIMValues_PROC XSetIMValues_PROC = 0;
#  define XSetIMValues (assert(XSetIMValues_PROC != 0), XSetIMValues_PROC)

typedef void (* PFN_XSetIOErrorExitHandler_PROC) (Display *, XIOErrorExitHandler, void *);
PFN_XSetIOErrorExitHandler_PROC XSetIOErrorExitHandler_PROC = 0;
#  define XSetIOErrorExitHandler (assert(XSetIOErrorExitHandler_PROC != 0), XSetIOErrorExitHandler_PROC)

typedef XIOErrorHandler (* PFN_XSetIOErrorHandler_PROC) (XIOErrorHandler);
PFN_XSetIOErrorHandler_PROC XSetIOErrorHandler_PROC = 0;
#  define XSetIOErrorHandler (assert(XSetIOErrorHandler_PROC != 0), XSetIOErrorHandler_PROC)

typedef int (* PFN_XSetIconName_PROC) (Display *, Window, const char *);
PFN_XSetIconName_PROC XSetIconName_PROC = 0;
#  define XSetIconName (assert(XSetIconName_PROC != 0), XSetIconName_PROC)

typedef int (* PFN_XSetInputFocus_PROC) (Display *, Window, int, Time);
PFN_XSetInputFocus_PROC XSetInputFocus_PROC = 0;
#  define XSetInputFocus (assert(XSetInputFocus_PROC != 0), XSetInputFocus_PROC)

typedef int (* PFN_XSetLineAttributes_PROC) (Display *, GC, unsigned int, int, int, int);
PFN_XSetLineAttributes_PROC XSetLineAttributes_PROC = 0;
#  define XSetLineAttributes (assert(XSetLineAttributes_PROC != 0), XSetLineAttributes_PROC)

typedef char *(* PFN_XSetLocaleModifiers_PROC) (const char *);
PFN_XSetLocaleModifiers_PROC XSetLocaleModifiers_PROC = 0;
#  define XSetLocaleModifiers (assert(XSetLocaleModifiers_PROC != 0), XSetLocaleModifiers_PROC)

typedef int (* PFN_XSetModifierMapping_PROC) (Display *, XModifierKeymap *);
PFN_XSetModifierMapping_PROC XSetModifierMapping_PROC = 0;
#  define XSetModifierMapping (assert(XSetModifierMapping_PROC != 0), XSetModifierMapping_PROC)

typedef char *(* PFN_XSetOCValues_PROC) (XOC, ...);
PFN_XSetOCValues_PROC XSetOCValues_PROC = 0;
#  define XSetOCValues (assert(XSetOCValues_PROC != 0), XSetOCValues_PROC)

typedef char *(* PFN_XSetOMValues_PROC) (XOM, ...);
PFN_XSetOMValues_PROC XSetOMValues_PROC = 0;
#  define XSetOMValues (assert(XSetOMValues_PROC != 0), XSetOMValues_PROC)

typedef int (* PFN_XSetPlaneMask_PROC) (Display *, GC, unsigned long);
PFN_XSetPlaneMask_PROC XSetPlaneMask_PROC = 0;
#  define XSetPlaneMask (assert(XSetPlaneMask_PROC != 0), XSetPlaneMask_PROC)

typedef int (* PFN_XSetPointerMapping_PROC) (Display *, const unsigned char *, int);
PFN_XSetPointerMapping_PROC XSetPointerMapping_PROC = 0;
#  define XSetPointerMapping (assert(XSetPointerMapping_PROC != 0), XSetPointerMapping_PROC)

typedef int (* PFN_XSetScreenSaver_PROC) (Display *, int, int, int, int);
PFN_XSetScreenSaver_PROC XSetScreenSaver_PROC = 0;
#  define XSetScreenSaver (assert(XSetScreenSaver_PROC != 0), XSetScreenSaver_PROC)

typedef int (* PFN_XSetSelectionOwner_PROC) (Display *, Atom, Window, Time);
PFN_XSetSelectionOwner_PROC XSetSelectionOwner_PROC = 0;
#  define XSetSelectionOwner (assert(XSetSelectionOwner_PROC != 0), XSetSelectionOwner_PROC)

typedef int (* PFN_XSetState_PROC) (Display *, GC, unsigned long, unsigned long, int, unsigned long);
PFN_XSetState_PROC XSetState_PROC = 0;
#  define XSetState (assert(XSetState_PROC != 0), XSetState_PROC)

typedef int (* PFN_XSetStipple_PROC) (Display *, GC, Pixmap);
PFN_XSetStipple_PROC XSetStipple_PROC = 0;
#  define XSetStipple (assert(XSetStipple_PROC != 0), XSetStipple_PROC)

typedef int (* PFN_XSetSubwindowMode_PROC) (Display *, GC, int);
PFN_XSetSubwindowMode_PROC XSetSubwindowMode_PROC = 0;
#  define XSetSubwindowMode (assert(XSetSubwindowMode_PROC != 0), XSetSubwindowMode_PROC)

typedef int (* PFN_XSetTSOrigin_PROC) (Display *, GC, int, int);
PFN_XSetTSOrigin_PROC XSetTSOrigin_PROC = 0;
#  define XSetTSOrigin (assert(XSetTSOrigin_PROC != 0), XSetTSOrigin_PROC)

typedef int (* PFN_XSetTile_PROC) (Display *, GC, Pixmap);
PFN_XSetTile_PROC XSetTile_PROC = 0;
#  define XSetTile (assert(XSetTile_PROC != 0), XSetTile_PROC)

typedef int (* PFN_XSetTransientForHint_PROC) (Display *, Window, Window);
PFN_XSetTransientForHint_PROC XSetTransientForHint_PROC = 0;
#  define XSetTransientForHint (assert(XSetTransientForHint_PROC != 0), XSetTransientForHint_PROC)

typedef int (* PFN_XSetWMColorwindow_maps_PROC) (Display *, Window, Window *, int);
PFN_XSetWMColorwindow_maps_PROC XSetWMColorwindow_maps_PROC = 0;
#  define XSetWMColorwindow_maps (assert(XSetWMColorwindow_maps_PROC != 0), XSetWMColorwindow_maps_PROC)

typedef int (* PFN_XSetWMProtocols_PROC) (Display *, Window, Atom *, int);
PFN_XSetWMProtocols_PROC XSetWMProtocols_PROC = 0;
#  define XSetWMProtocols (assert(XSetWMProtocols_PROC != 0), XSetWMProtocols_PROC)

typedef int (* PFN_XSetWindowBackground_PROC) (Display *, Window, unsigned long);
PFN_XSetWindowBackground_PROC XSetWindowBackground_PROC = 0;
#  define XSetWindowBackground (assert(XSetWindowBackground_PROC != 0), XSetWindowBackground_PROC)

typedef int (* PFN_XSetWindowBackgroundPixmap_PROC) (Display *, Window, Pixmap);
PFN_XSetWindowBackgroundPixmap_PROC XSetWindowBackgroundPixmap_PROC = 0;
#  define XSetWindowBackgroundPixmap (assert(XSetWindowBackgroundPixmap_PROC != 0), XSetWindowBackgroundPixmap_PROC)

typedef int (* PFN_XSetWindowBorder_PROC) (Display *, Window, unsigned long);
PFN_XSetWindowBorder_PROC XSetWindowBorder_PROC = 0;
#  define XSetWindowBorder (assert(XSetWindowBorder_PROC != 0), XSetWindowBorder_PROC)

typedef int (* PFN_XSetWindowBorderPixmap_PROC) (Display *, Window, Pixmap);
PFN_XSetWindowBorderPixmap_PROC XSetWindowBorderPixmap_PROC = 0;
#  define XSetWindowBorderPixmap (assert(XSetWindowBorderPixmap_PROC != 0), XSetWindowBorderPixmap_PROC)

typedef int (* PFN_XSetWindowBorderWidth_PROC) (Display *, Window, unsigned int);
PFN_XSetWindowBorderWidth_PROC XSetWindowBorderWidth_PROC = 0;
#  define XSetWindowBorderWidth (assert(XSetWindowBorderWidth_PROC != 0), XSetWindowBorderWidth_PROC)

typedef int (* PFN_XSetWindowColormap_PROC) (Display *, Window, Colormap);
PFN_XSetWindowColormap_PROC XSetWindowColormap_PROC = 0;
#  define XSetWindowColormap (assert(XSetWindowColormap_PROC != 0), XSetWindowColormap_PROC)

typedef int (* PFN_XStoreBuffer_PROC) (Display *, const char *, int, int);
PFN_XStoreBuffer_PROC XStoreBuffer_PROC = 0;
#  define XStoreBuffer (assert(XStoreBuffer_PROC != 0), XStoreBuffer_PROC)

typedef int (* PFN_XStoreBytes_PROC) (Display *, const char *, int);
PFN_XStoreBytes_PROC XStoreBytes_PROC = 0;
#  define XStoreBytes (assert(XStoreBytes_PROC != 0), XStoreBytes_PROC)

typedef int (* PFN_XStoreColor_PROC) (Display *, Colormap, XColor *);
PFN_XStoreColor_PROC XStoreColor_PROC = 0;
#  define XStoreColor (assert(XStoreColor_PROC != 0), XStoreColor_PROC)

typedef int (* PFN_XStoreColors_PROC) (Display *, Colormap, XColor *, int);
PFN_XStoreColors_PROC XStoreColors_PROC = 0;
#  define XStoreColors (assert(XStoreColors_PROC != 0), XStoreColors_PROC)

typedef int (* PFN_XStoreName_PROC) (Display *, Window, const char *);
PFN_XStoreName_PROC XStoreName_PROC = 0;
#  define XStoreName (assert(XStoreName_PROC != 0), XStoreName_PROC)

typedef int (* PFN_XStoreNamedColor_PROC) (Display *, Colormap, const char *, unsigned long, int);
PFN_XStoreNamedColor_PROC XStoreNamedColor_PROC = 0;
#  define XStoreNamedColor (assert(XStoreNamedColor_PROC != 0), XStoreNamedColor_PROC)

typedef KeySym (* PFN_XStringToKeysym_PROC) (const char *);
PFN_XStringToKeysym_PROC XStringToKeysym_PROC = 0;
#  define XStringToKeysym (assert(XStringToKeysym_PROC != 0), XStringToKeysym_PROC)

typedef int (* PFN_XSupportsLocale_PROC) (void);
PFN_XSupportsLocale_PROC XSupportsLocale_PROC = 0;
#  define XSupportsLocale (assert(XSupportsLocale_PROC != 0), XSupportsLocale_PROC)

typedef int (* PFN_XSync_PROC) (Display *, int);
PFN_XSync_PROC XSync_PROC = 0;
#  define XSync (assert(XSync_PROC != 0), XSync_PROC)

typedef int (* PFN_XTextExtents_PROC) (XFontStruct *, const char *, int, int *, int *, int *, XCharStruct *);
PFN_XTextExtents_PROC XTextExtents_PROC = 0;
#  define XTextExtents (assert(XTextExtents_PROC != 0), XTextExtents_PROC)

typedef int (* PFN_XTextExtents16_PROC) (XFontStruct *, const XChar2b *, int, int *, int *, int *, XCharStruct *);
PFN_XTextExtents16_PROC XTextExtents16_PROC = 0;
#  define XTextExtents16 (assert(XTextExtents16_PROC != 0), XTextExtents16_PROC)

typedef int (* PFN_XTextWidth_PROC) (XFontStruct *, const char *, int);
PFN_XTextWidth_PROC XTextWidth_PROC = 0;
#  define XTextWidth (assert(XTextWidth_PROC != 0), XTextWidth_PROC)

typedef int (* PFN_XTextWidth16_PROC) (XFontStruct *, const XChar2b *, int);
PFN_XTextWidth16_PROC XTextWidth16_PROC = 0;
#  define XTextWidth16 (assert(XTextWidth16_PROC != 0), XTextWidth16_PROC)

typedef int (* PFN_XTranslateCoordinates_PROC) (Display *, Window, Window, int, int, int *, int *, Window *);
PFN_XTranslateCoordinates_PROC XTranslateCoordinates_PROC = 0;
#  define XTranslateCoordinates (assert(XTranslateCoordinates_PROC != 0), XTranslateCoordinates_PROC)

typedef int (* PFN_XUndefineCursor_PROC) (Display *, Window);
PFN_XUndefineCursor_PROC XUndefineCursor_PROC = 0;
#  define XUndefineCursor (assert(XUndefineCursor_PROC != 0), XUndefineCursor_PROC)

typedef int (* PFN_XUngrabButton_PROC) (Display *, unsigned int, unsigned int, Window);
PFN_XUngrabButton_PROC XUngrabButton_PROC = 0;
#  define XUngrabButton (assert(XUngrabButton_PROC != 0), XUngrabButton_PROC)

typedef int (* PFN_XUngrabKey_PROC) (Display *, int, unsigned int, Window);
PFN_XUngrabKey_PROC XUngrabKey_PROC = 0;
#  define XUngrabKey (assert(XUngrabKey_PROC != 0), XUngrabKey_PROC)

typedef int (* PFN_XUngrabKeyboard_PROC) (Display *, Time);
PFN_XUngrabKeyboard_PROC XUngrabKeyboard_PROC = 0;
#  define XUngrabKeyboard (assert(XUngrabKeyboard_PROC != 0), XUngrabKeyboard_PROC)

typedef int (* PFN_XUngrabPointer_PROC) (Display *, Time);
PFN_XUngrabPointer_PROC XUngrabPointer_PROC = 0;
#  define XUngrabPointer (assert(XUngrabPointer_PROC != 0), XUngrabPointer_PROC)

typedef int (* PFN_XUngrabServer_PROC) (Display *);
PFN_XUngrabServer_PROC XUngrabServer_PROC = 0;
#  define XUngrabServer (assert(XUngrabServer_PROC != 0), XUngrabServer_PROC)

typedef int (* PFN_XUninstallColormap_PROC) (Display *, Colormap);
PFN_XUninstallColormap_PROC XUninstallColormap_PROC = 0;
#  define XUninstallColormap (assert(XUninstallColormap_PROC != 0), XUninstallColormap_PROC)

typedef int (* PFN_XUnloadFont_PROC) (Display *, Font);
PFN_XUnloadFont_PROC XUnloadFont_PROC = 0;
#  define XUnloadFont (assert(XUnloadFont_PROC != 0), XUnloadFont_PROC)

typedef void (* PFN_XUnlockDisplay_PROC) (Display *);
PFN_XUnlockDisplay_PROC XUnlockDisplay_PROC = 0;
#  define XUnlockDisplay (assert(XUnlockDisplay_PROC != 0), XUnlockDisplay_PROC)

typedef int (* PFN_XUnmapSubwindows_PROC) (Display *, Window);
PFN_XUnmapSubwindows_PROC XUnmapSubwindows_PROC = 0;
#  define XUnmapSubwindows (assert(XUnmapSubwindows_PROC != 0), XUnmapSubwindows_PROC)

typedef int (* PFN_XUnwindow_map_PROC) (Display *, Window);
PFN_XUnwindow_map_PROC XUnwindow_map_PROC = 0;
#  define XUnwindow_map (assert(XUnwindow_map_PROC != 0), XUnwindow_map_PROC)

typedef int (* PFN_XUnregisterIMInstantiateCallback_PROC) (Display *, struct _XrmHashBucketRec *, char *, char *, XIDProc, XPointer);
PFN_XUnregisterIMInstantiateCallback_PROC XUnregisterIMInstantiateCallback_PROC = 0;
#  define XUnregisterIMInstantiateCallback (assert(XUnregisterIMInstantiateCallback_PROC != 0), XUnregisterIMInstantiateCallback_PROC)

typedef void (* PFN_XUnsetICFocus_PROC) (XIC);
PFN_XUnsetICFocus_PROC XUnsetICFocus_PROC = 0;
#  define XUnsetICFocus (assert(XUnsetICFocus_PROC != 0), XUnsetICFocus_PROC)

typedef XVaNestedList (* PFN_XVaCreateNestedList_PROC) (int, ...);
PFN_XVaCreateNestedList_PROC XVaCreateNestedList_PROC = 0;
#  define XVaCreateNestedList (assert(XVaCreateNestedList_PROC != 0), XVaCreateNestedList_PROC)

typedef int (* PFN_XVendorRelease_PROC) (Display *);
PFN_XVendorRelease_PROC XVendorRelease_PROC = 0;
#  define XVendorRelease (assert(XVendorRelease_PROC != 0), XVendorRelease_PROC)

typedef VisualID (* PFN_XVisualIDFromVisual_PROC) (Visual *);
PFN_XVisualIDFromVisual_PROC XVisualIDFromVisual_PROC = 0;
#  define XVisualIDFromVisual (assert(XVisualIDFromVisual_PROC != 0), XVisualIDFromVisual_PROC)

typedef int (* PFN_XWarpPointer_PROC) (Display *, Window, Window, int, int, unsigned int, unsigned int, int, int);
PFN_XWarpPointer_PROC XWarpPointer_PROC = 0;
#  define XWarpPointer (assert(XWarpPointer_PROC != 0), XWarpPointer_PROC)

typedef unsigned long (* PFN_XWhitePixel_PROC) (Display *, int);
PFN_XWhitePixel_PROC XWhitePixel_PROC = 0;
#  define XWhitePixel (assert(XWhitePixel_PROC != 0), XWhitePixel_PROC)

typedef unsigned long (* PFN_XWhitePixelOfScreen_PROC) (Screen *);
PFN_XWhitePixelOfScreen_PROC XWhitePixelOfScreen_PROC = 0;
#  define XWhitePixelOfScreen (assert(XWhitePixelOfScreen_PROC != 0), XWhitePixelOfScreen_PROC)

typedef int (* PFN_XWidthMMOfScreen_PROC) (Screen *);
PFN_XWidthMMOfScreen_PROC XWidthMMOfScreen_PROC = 0;
#  define XWidthMMOfScreen (assert(XWidthMMOfScreen_PROC != 0), XWidthMMOfScreen_PROC)

typedef int (* PFN_XWidthOfScreen_PROC) (Screen *);
PFN_XWidthOfScreen_PROC XWidthOfScreen_PROC = 0;
#  define XWidthOfScreen (assert(XWidthOfScreen_PROC != 0), XWidthOfScreen_PROC)

typedef int (* PFN_XWindowEvent_PROC) (Display *, Window, long, XEvent *);
PFN_XWindowEvent_PROC XWindowEvent_PROC = 0;
#  define XWindowEvent (assert(XWindowEvent_PROC != 0), XWindowEvent_PROC)

typedef int (* PFN_XWithdrawWindow_PROC) (Display *, Window, int);
PFN_XWithdrawWindow_PROC XWithdrawWindow_PROC = 0;
#  define XWithdrawWindow (assert(XWithdrawWindow_PROC != 0), XWithdrawWindow_PROC)

typedef int (* PFN_XWriteBitmapFile_PROC) (Display *, const char *, Pixmap, unsigned int, unsigned int, int, int);
PFN_XWriteBitmapFile_PROC XWriteBitmapFile_PROC = 0;
#  define XWriteBitmapFile (assert(XWriteBitmapFile_PROC != 0), XWriteBitmapFile_PROC)

typedef void (* PFN_XmbDrawImageString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_XmbDrawImageString_PROC XmbDrawImageString_PROC = 0;
#  define XmbDrawImageString (assert(XmbDrawImageString_PROC != 0), XmbDrawImageString_PROC)

typedef void (* PFN_XmbDrawString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_XmbDrawString_PROC XmbDrawString_PROC = 0;
#  define XmbDrawString (assert(XmbDrawString_PROC != 0), XmbDrawString_PROC)

typedef void (* PFN_XmbDrawText_PROC) (Display *, Drawable, GC, int, int, XmbTextItem *, int);
PFN_XmbDrawText_PROC XmbDrawText_PROC = 0;
#  define XmbDrawText (assert(XmbDrawText_PROC != 0), XmbDrawText_PROC)

typedef int (* PFN_XmbLookupString_PROC) (XIC, XKeyPressedEvent *, char *, int, KeySym *, int *);
PFN_XmbLookupString_PROC XmbLookupString_PROC = 0;
#  define XmbLookupString (assert(XmbLookupString_PROC != 0), XmbLookupString_PROC)

typedef char *(* PFN_XmbResetIC_PROC) (XIC);
PFN_XmbResetIC_PROC XmbResetIC_PROC = 0;
#  define XmbResetIC (assert(XmbResetIC_PROC != 0), XmbResetIC_PROC)

typedef int (* PFN_XmbTextEscapement_PROC) (XFontSet, const char *, int);
PFN_XmbTextEscapement_PROC XmbTextEscapement_PROC = 0;
#  define XmbTextEscapement (assert(XmbTextEscapement_PROC != 0), XmbTextEscapement_PROC)

typedef int (* PFN_XmbTextExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *);
PFN_XmbTextExtents_PROC XmbTextExtents_PROC = 0;
#  define XmbTextExtents (assert(XmbTextExtents_PROC != 0), XmbTextExtents_PROC)

typedef int (* PFN_XmbTextPerCharExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *, int, int *, XRectangle *, XRectangle *);
PFN_XmbTextPerCharExtents_PROC XmbTextPerCharExtents_PROC = 0;
#  define XmbTextPerCharExtents (assert(XmbTextPerCharExtents_PROC != 0), XmbTextPerCharExtents_PROC)

typedef void (* PFN_XrmInitialize_PROC) (void);
PFN_XrmInitialize_PROC XrmInitialize_PROC = 0;
#  define XrmInitialize (assert(XrmInitialize_PROC != 0), XrmInitialize_PROC)

typedef void (* PFN_Xutf8DrawImageString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_Xutf8DrawImageString_PROC Xutf8DrawImageString_PROC = 0;
#  define Xutf8DrawImageString (assert(Xutf8DrawImageString_PROC != 0), Xutf8DrawImageString_PROC)

typedef void (* PFN_Xutf8DrawString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const char *, int);
PFN_Xutf8DrawString_PROC Xutf8DrawString_PROC = 0;
#  define Xutf8DrawString (assert(Xutf8DrawString_PROC != 0), Xutf8DrawString_PROC)

typedef void (* PFN_Xutf8DrawText_PROC) (Display *, Drawable, GC, int, int, XmbTextItem *, int);
PFN_Xutf8DrawText_PROC Xutf8DrawText_PROC = 0;
#  define Xutf8DrawText (assert(Xutf8DrawText_PROC != 0), Xutf8DrawText_PROC)

typedef int (* PFN_Xutf8LookupString_PROC) (XIC, XKeyPressedEvent *, char *, int, KeySym *, int *);
PFN_Xutf8LookupString_PROC Xutf8LookupString_PROC = 0;
#  define Xutf8LookupString (assert(Xutf8LookupString_PROC != 0), Xutf8LookupString_PROC)

typedef char *(* PFN_Xutf8ResetIC_PROC) (XIC);
PFN_Xutf8ResetIC_PROC Xutf8ResetIC_PROC = 0;
#  define Xutf8ResetIC (assert(Xutf8ResetIC_PROC != 0), Xutf8ResetIC_PROC)

typedef int (* PFN_Xutf8TextEscapement_PROC) (XFontSet, const char *, int);
PFN_Xutf8TextEscapement_PROC Xutf8TextEscapement_PROC = 0;
#  define Xutf8TextEscapement (assert(Xutf8TextEscapement_PROC != 0), Xutf8TextEscapement_PROC)

typedef int (* PFN_Xutf8TextExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *);
PFN_Xutf8TextExtents_PROC Xutf8TextExtents_PROC = 0;
#  define Xutf8TextExtents (assert(Xutf8TextExtents_PROC != 0), Xutf8TextExtents_PROC)

typedef int (* PFN_Xutf8TextPerCharExtents_PROC) (XFontSet, const char *, int, XRectangle *, XRectangle *, int, int *, XRectangle *, XRectangle *);
PFN_Xutf8TextPerCharExtents_PROC Xutf8TextPerCharExtents_PROC = 0;
#  define Xutf8TextPerCharExtents (assert(Xutf8TextPerCharExtents_PROC != 0), Xutf8TextPerCharExtents_PROC)

typedef void (* PFN_XwcDrawImageString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const wchar_t *, int);
PFN_XwcDrawImageString_PROC XwcDrawImageString_PROC = 0;
#  define XwcDrawImageString (assert(XwcDrawImageString_PROC != 0), XwcDrawImageString_PROC)

typedef void (* PFN_XwcDrawString_PROC) (Display *, Drawable, XFontSet, GC, int, int, const wchar_t *, int);
PFN_XwcDrawString_PROC XwcDrawString_PROC = 0;
#  define XwcDrawString (assert(XwcDrawString_PROC != 0), XwcDrawString_PROC)

typedef void (* PFN_XwcDrawText_PROC) (Display *, Drawable, GC, int, int, XwcTextItem *, int);
PFN_XwcDrawText_PROC XwcDrawText_PROC = 0;
#  define XwcDrawText (assert(XwcDrawText_PROC != 0), XwcDrawText_PROC)

typedef int (* PFN_XwcLookupString_PROC) (XIC, XKeyPressedEvent *, wchar_t *, int, KeySym *, int *);
PFN_XwcLookupString_PROC XwcLookupString_PROC = 0;
#  define XwcLookupString (assert(XwcLookupString_PROC != 0), XwcLookupString_PROC)

typedef wchar_t *(* PFN_XwcResetIC_PROC) (XIC);
PFN_XwcResetIC_PROC XwcResetIC_PROC = 0;
#  define XwcResetIC (assert(XwcResetIC_PROC != 0), XwcResetIC_PROC)

typedef int (* PFN_XwcTextEscapement_PROC) (XFontSet, const wchar_t *, int);
PFN_XwcTextEscapement_PROC XwcTextEscapement_PROC = 0;
#  define XwcTextEscapement (assert(XwcTextEscapement_PROC != 0), XwcTextEscapement_PROC)

typedef int (* PFN_XwcTextExtents_PROC) (XFontSet, const wchar_t *, int, XRectangle *, XRectangle *);
PFN_XwcTextExtents_PROC XwcTextExtents_PROC = 0;
#  define XwcTextExtents (assert(XwcTextExtents_PROC != 0), XwcTextExtents_PROC)

typedef int (* PFN_XwcTextPerCharExtents_PROC) (XFontSet, const wchar_t *, int, XRectangle *, XRectangle *, int, int *, XRectangle *, XRectangle *);
PFN_XwcTextPerCharExtents_PROC XwcTextPerCharExtents_PROC = 0;
#  define XwcTextPerCharExtents (assert(XwcTextPerCharExtents_PROC != 0), XwcTextPerCharExtents_PROC)

typedef int (* PFN__Xmblen_PROC) (char *, int);
PFN__Xmblen_PROC _Xmblen_PROC = 0;
#  define _Xmblen (assert(_Xmblen_PROC != 0), _Xmblen_PROC)

typedef int (* PFN__Xmbtowc_PROC) (wchar_t *, char *, int);
PFN__Xmbtowc_PROC _Xmbtowc_PROC = 0;
#  define _Xmbtowc (assert(_Xmbtowc_PROC != 0), _Xmbtowc_PROC)

typedef int (* PFN__Xwctomb_PROC) (char *, wchar_t);
PFN__Xwctomb_PROC _Xwctomb_PROC = 0;
#  define _Xwctomb (assert(_Xwctomb_PROC != 0), _Xwctomb_PROC)


/* libX11: Xutil.h */
typedef XClassHint *(* PFN_XAllocClassHint_PROC) (void);
PFN_XAllocClassHint_PROC XAllocClassHint_PROC = 0;
#  define XAllocClassHint (assert(XAllocClassHint_PROC != 0), XAllocClassHint_PROC)

typedef XIconSize *(* PFN_XAllocIconSize_PROC) (void);
PFN_XAllocIconSize_PROC XAllocIconSize_PROC = 0;
#  define XAllocIconSize (assert(XAllocIconSize_PROC != 0), XAllocIconSize_PROC)

typedef XSizeHints *(* PFN_XAllocSizeHints_PROC) (void);
PFN_XAllocSizeHints_PROC XAllocSizeHints_PROC = 0;
#  define XAllocSizeHints (assert(XAllocSizeHints_PROC != 0), XAllocSizeHints_PROC)

typedef XStandardColormap *(* PFN_XAllocStandardColormap_PROC) (void);
PFN_XAllocStandardColormap_PROC XAllocStandardColormap_PROC = 0;
#  define XAllocStandardColormap (assert(XAllocStandardColormap_PROC != 0), XAllocStandardColormap_PROC)

typedef XWMHints *(* PFN_XAllocWMHints_PROC) (void);
PFN_XAllocWMHints_PROC XAllocWMHints_PROC = 0;
#  define XAllocWMHints (assert(XAllocWMHints_PROC != 0), XAllocWMHints_PROC)

typedef int (* PFN_XClipBox_PROC) (Region, XRectangle *);
PFN_XClipBox_PROC XClipBox_PROC = 0;
#  define XClipBox (assert(XClipBox_PROC != 0), XClipBox_PROC)

typedef void (* PFN_XConvertCase_PROC) (KeySym, KeySym *, KeySym *);
PFN_XConvertCase_PROC XConvertCase_PROC = 0;
#  define XConvertCase (assert(XConvertCase_PROC != 0), XConvertCase_PROC)

typedef Region (* PFN_XCreateRegion_PROC) (void);
PFN_XCreateRegion_PROC XCreateRegion_PROC = 0;
#  define XCreateRegion (assert(XCreateRegion_PROC != 0), XCreateRegion_PROC)

typedef const char *(* PFN_XDefaultString_PROC) (void);
PFN_XDefaultString_PROC XDefaultString_PROC = 0;
#  define XDefaultString (assert(XDefaultString_PROC != 0), XDefaultString_PROC)

typedef int (* PFN_XDeleteContext_PROC) (Display *, XID, XContext);
PFN_XDeleteContext_PROC XDeleteContext_PROC = 0;
#  define XDeleteContext (assert(XDeleteContext_PROC != 0), XDeleteContext_PROC)

typedef int (* PFN_XDestroyRegion_PROC) (Region);
PFN_XDestroyRegion_PROC XDestroyRegion_PROC = 0;
#  define XDestroyRegion (assert(XDestroyRegion_PROC != 0), XDestroyRegion_PROC)

typedef int (* PFN_XEmptyRegion_PROC) (Region);
PFN_XEmptyRegion_PROC XEmptyRegion_PROC = 0;
#  define XEmptyRegion (assert(XEmptyRegion_PROC != 0), XEmptyRegion_PROC)

typedef int (* PFN_XEqualRegion_PROC) (Region, Region);
PFN_XEqualRegion_PROC XEqualRegion_PROC = 0;
#  define XEqualRegion (assert(XEqualRegion_PROC != 0), XEqualRegion_PROC)

typedef int (* PFN_XFindContext_PROC) (Display *, XID, XContext, XPointer *);
PFN_XFindContext_PROC XFindContext_PROC = 0;
#  define XFindContext (assert(XFindContext_PROC != 0), XFindContext_PROC)

typedef int (* PFN_XGetClassHint_PROC) (Display *, Window, XClassHint *);
PFN_XGetClassHint_PROC XGetClassHint_PROC = 0;
#  define XGetClassHint (assert(XGetClassHint_PROC != 0), XGetClassHint_PROC)

typedef int (* PFN_XGetIconSizes_PROC) (Display *, Window, XIconSize **, int *);
PFN_XGetIconSizes_PROC XGetIconSizes_PROC = 0;
#  define XGetIconSizes (assert(XGetIconSizes_PROC != 0), XGetIconSizes_PROC)

typedef int (* PFN_XGetNormalHints_PROC) (Display *, Window, XSizeHints *);
PFN_XGetNormalHints_PROC XGetNormalHints_PROC = 0;
#  define XGetNormalHints (assert(XGetNormalHints_PROC != 0), XGetNormalHints_PROC)

typedef int (* PFN_XGetRGBColormaps_PROC) (Display *, Window, XStandardColormap **, int *, Atom);
PFN_XGetRGBColormaps_PROC XGetRGBColormaps_PROC = 0;
#  define XGetRGBColormaps (assert(XGetRGBColormaps_PROC != 0), XGetRGBColormaps_PROC)

typedef int (* PFN_XGetSizeHints_PROC) (Display *, Window, XSizeHints *, Atom);
PFN_XGetSizeHints_PROC XGetSizeHints_PROC = 0;
#  define XGetSizeHints (assert(XGetSizeHints_PROC != 0), XGetSizeHints_PROC)

typedef int (* PFN_XGetStandardColormap_PROC) (Display *, Window, XStandardColormap *, Atom);
PFN_XGetStandardColormap_PROC XGetStandardColormap_PROC = 0;
#  define XGetStandardColormap (assert(XGetStandardColormap_PROC != 0), XGetStandardColormap_PROC)

typedef int (* PFN_XGetTextProperty_PROC) (Display *, Window, XTextProperty *, Atom);
PFN_XGetTextProperty_PROC XGetTextProperty_PROC = 0;
#  define XGetTextProperty (assert(XGetTextProperty_PROC != 0), XGetTextProperty_PROC)

typedef XVisualInfo *(* PFN_XGetVisualInfo_PROC) (Display *, long, XVisualInfo *, int *);
PFN_XGetVisualInfo_PROC XGetVisualInfo_PROC = 0;
#  define XGetVisualInfo (assert(XGetVisualInfo_PROC != 0), XGetVisualInfo_PROC)

typedef int (* PFN_XGetWMClientMachine_PROC) (Display *, Window, XTextProperty *);
PFN_XGetWMClientMachine_PROC XGetWMClientMachine_PROC = 0;
#  define XGetWMClientMachine (assert(XGetWMClientMachine_PROC != 0), XGetWMClientMachine_PROC)

typedef XWMHints *(* PFN_XGetWMHints_PROC) (Display *, Window);
PFN_XGetWMHints_PROC XGetWMHints_PROC = 0;
#  define XGetWMHints (assert(XGetWMHints_PROC != 0), XGetWMHints_PROC)

typedef int (* PFN_XGetWMIconName_PROC) (Display *, Window, XTextProperty *);
PFN_XGetWMIconName_PROC XGetWMIconName_PROC = 0;
#  define XGetWMIconName (assert(XGetWMIconName_PROC != 0), XGetWMIconName_PROC)

typedef int (* PFN_XGetWMName_PROC) (Display *, Window, XTextProperty *);
PFN_XGetWMName_PROC XGetWMName_PROC = 0;
#  define XGetWMName (assert(XGetWMName_PROC != 0), XGetWMName_PROC)

typedef int (* PFN_XGetWMNormalHints_PROC) (Display *, Window, XSizeHints *, long *);
PFN_XGetWMNormalHints_PROC XGetWMNormalHints_PROC = 0;
#  define XGetWMNormalHints (assert(XGetWMNormalHints_PROC != 0), XGetWMNormalHints_PROC)

typedef int (* PFN_XGetWMSizeHints_PROC) (Display *, Window, XSizeHints *, long *, Atom);
PFN_XGetWMSizeHints_PROC XGetWMSizeHints_PROC = 0;
#  define XGetWMSizeHints (assert(XGetWMSizeHints_PROC != 0), XGetWMSizeHints_PROC)

typedef int (* PFN_XGetZoomHints_PROC) (Display *, Window, XSizeHints *);
PFN_XGetZoomHints_PROC XGetZoomHints_PROC = 0;
#  define XGetZoomHints (assert(XGetZoomHints_PROC != 0), XGetZoomHints_PROC)

typedef int (* PFN_XIntersectRegion_PROC) (Region, Region, Region);
PFN_XIntersectRegion_PROC XIntersectRegion_PROC = 0;
#  define XIntersectRegion (assert(XIntersectRegion_PROC != 0), XIntersectRegion_PROC)

typedef int (* PFN_XLookupString_PROC) (XKeyEvent *, char *, int, KeySym *, XComposeStatus *);
PFN_XLookupString_PROC XLookupString_PROC = 0;
#  define XLookupString (assert(XLookupString_PROC != 0), XLookupString_PROC)

typedef int (* PFN_XMatchVisualInfo_PROC) (Display *, int, int, int, XVisualInfo *);
PFN_XMatchVisualInfo_PROC XMatchVisualInfo_PROC = 0;
#  define XMatchVisualInfo (assert(XMatchVisualInfo_PROC != 0), XMatchVisualInfo_PROC)

typedef int (* PFN_XOffsetRegion_PROC) (Region, int, int);
PFN_XOffsetRegion_PROC XOffsetRegion_PROC = 0;
#  define XOffsetRegion (assert(XOffsetRegion_PROC != 0), XOffsetRegion_PROC)

typedef int (* PFN_XPointInRegion_PROC) (Region, int, int);
PFN_XPointInRegion_PROC XPointInRegion_PROC = 0;
#  define XPointInRegion (assert(XPointInRegion_PROC != 0), XPointInRegion_PROC)

typedef Region (* PFN_XPolygonRegion_PROC) (XPoint *, int, int);
PFN_XPolygonRegion_PROC XPolygonRegion_PROC = 0;
#  define XPolygonRegion (assert(XPolygonRegion_PROC != 0), XPolygonRegion_PROC)

typedef int (* PFN_XRectInRegion_PROC) (Region, int, int, unsigned int, unsigned int);
PFN_XRectInRegion_PROC XRectInRegion_PROC = 0;
#  define XRectInRegion (assert(XRectInRegion_PROC != 0), XRectInRegion_PROC)

typedef int (* PFN_XSaveContext_PROC) (Display *, XID, XContext, const char *);
PFN_XSaveContext_PROC XSaveContext_PROC = 0;
#  define XSaveContext (assert(XSaveContext_PROC != 0), XSaveContext_PROC)

typedef int (* PFN_XSetClassHint_PROC) (Display *, Window, XClassHint *);
PFN_XSetClassHint_PROC XSetClassHint_PROC = 0;
#  define XSetClassHint (assert(XSetClassHint_PROC != 0), XSetClassHint_PROC)

typedef int (* PFN_XSetIconSizes_PROC) (Display *, Window, XIconSize *, int);
PFN_XSetIconSizes_PROC XSetIconSizes_PROC = 0;
#  define XSetIconSizes (assert(XSetIconSizes_PROC != 0), XSetIconSizes_PROC)

typedef int (* PFN_XSetNormalHints_PROC) (Display *, Window, XSizeHints *);
PFN_XSetNormalHints_PROC XSetNormalHints_PROC = 0;
#  define XSetNormalHints (assert(XSetNormalHints_PROC != 0), XSetNormalHints_PROC)

typedef void (* PFN_XSetRGBColormaps_PROC) (Display *, Window, XStandardColormap *, int, Atom);
PFN_XSetRGBColormaps_PROC XSetRGBColormaps_PROC = 0;
#  define XSetRGBColormaps (assert(XSetRGBColormaps_PROC != 0), XSetRGBColormaps_PROC)

typedef int (* PFN_XSetRegion_PROC) (Display *, GC, Region);
PFN_XSetRegion_PROC XSetRegion_PROC = 0;
#  define XSetRegion (assert(XSetRegion_PROC != 0), XSetRegion_PROC)

typedef int (* PFN_XSetSizeHints_PROC) (Display *, Window, XSizeHints *, Atom);
PFN_XSetSizeHints_PROC XSetSizeHints_PROC = 0;
#  define XSetSizeHints (assert(XSetSizeHints_PROC != 0), XSetSizeHints_PROC)

typedef void (* PFN_XSetStandardColormap_PROC) (Display *, Window, XStandardColormap *, Atom);
PFN_XSetStandardColormap_PROC XSetStandardColormap_PROC = 0;
#  define XSetStandardColormap (assert(XSetStandardColormap_PROC != 0), XSetStandardColormap_PROC)

typedef int (* PFN_XSetStandardProperties_PROC) (Display *, Window, const char *, const char *, Pixmap, char **, int, XSizeHints *);
PFN_XSetStandardProperties_PROC XSetStandardProperties_PROC = 0;
#  define XSetStandardProperties (assert(XSetStandardProperties_PROC != 0), XSetStandardProperties_PROC)

typedef void (* PFN_XSetTextProperty_PROC) (Display *, Window, XTextProperty *, Atom);
PFN_XSetTextProperty_PROC XSetTextProperty_PROC = 0;
#  define XSetTextProperty (assert(XSetTextProperty_PROC != 0), XSetTextProperty_PROC)

typedef void (* PFN_XSetWMClientMachine_PROC) (Display *, Window, XTextProperty *);
PFN_XSetWMClientMachine_PROC XSetWMClientMachine_PROC = 0;
#  define XSetWMClientMachine (assert(XSetWMClientMachine_PROC != 0), XSetWMClientMachine_PROC)

typedef int (* PFN_XSetWMHints_PROC) (Display *, Window, XWMHints *);
PFN_XSetWMHints_PROC XSetWMHints_PROC = 0;
#  define XSetWMHints (assert(XSetWMHints_PROC != 0), XSetWMHints_PROC)

typedef void (* PFN_XSetWMIconName_PROC) (Display *, Window, XTextProperty *);
PFN_XSetWMIconName_PROC XSetWMIconName_PROC = 0;
#  define XSetWMIconName (assert(XSetWMIconName_PROC != 0), XSetWMIconName_PROC)

typedef void (* PFN_XSetWMName_PROC) (Display *, Window, XTextProperty *);
PFN_XSetWMName_PROC XSetWMName_PROC = 0;
#  define XSetWMName (assert(XSetWMName_PROC != 0), XSetWMName_PROC)

typedef void (* PFN_XSetWMNormalHints_PROC) (Display *, Window, XSizeHints *);
PFN_XSetWMNormalHints_PROC XSetWMNormalHints_PROC = 0;
#  define XSetWMNormalHints (assert(XSetWMNormalHints_PROC != 0), XSetWMNormalHints_PROC)

typedef void (* PFN_XSetWMProperties_PROC) (Display *, Window, XTextProperty *, XTextProperty *, char **, int, XSizeHints *, XWMHints *, XClassHint *);
PFN_XSetWMProperties_PROC XSetWMProperties_PROC = 0;
#  define XSetWMProperties (assert(XSetWMProperties_PROC != 0), XSetWMProperties_PROC)

typedef void (* PFN_XSetWMSizeHints_PROC) (Display *, Window, XSizeHints *, Atom);
PFN_XSetWMSizeHints_PROC XSetWMSizeHints_PROC = 0;
#  define XSetWMSizeHints (assert(XSetWMSizeHints_PROC != 0), XSetWMSizeHints_PROC)

typedef int (* PFN_XSetZoomHints_PROC) (Display *, Window, XSizeHints *);
PFN_XSetZoomHints_PROC XSetZoomHints_PROC = 0;
#  define XSetZoomHints (assert(XSetZoomHints_PROC != 0), XSetZoomHints_PROC)

typedef int (* PFN_XShrinkRegion_PROC) (Region, int, int);
PFN_XShrinkRegion_PROC XShrinkRegion_PROC = 0;
#  define XShrinkRegion (assert(XShrinkRegion_PROC != 0), XShrinkRegion_PROC)

typedef int (* PFN_XStringListToTextProperty_PROC) (char **, int, XTextProperty *);
PFN_XStringListToTextProperty_PROC XStringListToTextProperty_PROC = 0;
#  define XStringListToTextProperty (assert(XStringListToTextProperty_PROC != 0), XStringListToTextProperty_PROC)

typedef int (* PFN_XSubtractRegion_PROC) (Region, Region, Region);
PFN_XSubtractRegion_PROC XSubtractRegion_PROC = 0;
#  define XSubtractRegion (assert(XSubtractRegion_PROC != 0), XSubtractRegion_PROC)

typedef int (* PFN_XTextPropertyToStringList_PROC) (XTextProperty *, char ***, int *);
PFN_XTextPropertyToStringList_PROC XTextPropertyToStringList_PROC = 0;
#  define XTextPropertyToStringList (assert(XTextPropertyToStringList_PROC != 0), XTextPropertyToStringList_PROC)

typedef int (* PFN_XUnionRectWithRegion_PROC) (XRectangle *, Region, Region);
PFN_XUnionRectWithRegion_PROC XUnionRectWithRegion_PROC = 0;
#  define XUnionRectWithRegion (assert(XUnionRectWithRegion_PROC != 0), XUnionRectWithRegion_PROC)

typedef int (* PFN_XUnionRegion_PROC) (Region, Region, Region);
PFN_XUnionRegion_PROC XUnionRegion_PROC = 0;
#  define XUnionRegion (assert(XUnionRegion_PROC != 0), XUnionRegion_PROC)

typedef int (* PFN_XWMGeometry_PROC) (Display *, int, const char *, const char *, unsigned int, XSizeHints *, int *, int *, int *, int *, int *);
PFN_XWMGeometry_PROC XWMGeometry_PROC = 0;
#  define XWMGeometry (assert(XWMGeometry_PROC != 0), XWMGeometry_PROC)

typedef int (* PFN_XXorRegion_PROC) (Region, Region, Region);
PFN_XXorRegion_PROC XXorRegion_PROC = 0;
#  define XXorRegion (assert(XXorRegion_PROC != 0), XXorRegion_PROC)

typedef void (* PFN_XmbSetWMProperties_PROC) (Display *, Window, const char *, const char *, char **, int, XSizeHints *, XWMHints *, XClassHint *);
PFN_XmbSetWMProperties_PROC XmbSetWMProperties_PROC = 0;
#  define XmbSetWMProperties (assert(XmbSetWMProperties_PROC != 0), XmbSetWMProperties_PROC)

typedef int (* PFN_XmbTextListToTextProperty_PROC) (Display *, char **, int, XICCEncodingStyle, XTextProperty *);
PFN_XmbTextListToTextProperty_PROC XmbTextListToTextProperty_PROC = 0;
#  define XmbTextListToTextProperty (assert(XmbTextListToTextProperty_PROC != 0), XmbTextListToTextProperty_PROC)

typedef int (* PFN_XmbTextPropertyToTextList_PROC) (Display *, const XTextProperty *, char ***, int *);
PFN_XmbTextPropertyToTextList_PROC XmbTextPropertyToTextList_PROC = 0;
#  define XmbTextPropertyToTextList (assert(XmbTextPropertyToTextList_PROC != 0), XmbTextPropertyToTextList_PROC)

typedef void (* PFN_Xutf8SetWMProperties_PROC) (Display *, Window, const char *, const char *, char **, int, XSizeHints *, XWMHints *, XClassHint *);
PFN_Xutf8SetWMProperties_PROC Xutf8SetWMProperties_PROC = 0;
#  define Xutf8SetWMProperties (assert(Xutf8SetWMProperties_PROC != 0), Xutf8SetWMProperties_PROC)

typedef int (* PFN_Xutf8TextListToTextProperty_PROC) (Display *, char **, int, XICCEncodingStyle, XTextProperty *);
PFN_Xutf8TextListToTextProperty_PROC Xutf8TextListToTextProperty_PROC = 0;
#  define Xutf8TextListToTextProperty (assert(Xutf8TextListToTextProperty_PROC != 0), Xutf8TextListToTextProperty_PROC)

typedef int (* PFN_Xutf8TextPropertyToTextList_PROC) (Display *, const XTextProperty *, char ***, int *);
PFN_Xutf8TextPropertyToTextList_PROC Xutf8TextPropertyToTextList_PROC = 0;
#  define Xutf8TextPropertyToTextList (assert(Xutf8TextPropertyToTextList_PROC != 0), Xutf8TextPropertyToTextList_PROC)

typedef void (* PFN_XwcFreeStringList_PROC) (wchar_t **);
PFN_XwcFreeStringList_PROC XwcFreeStringList_PROC = 0;
#  define XwcFreeStringList (assert(XwcFreeStringList_PROC != 0), XwcFreeStringList_PROC)

typedef int (* PFN_XwcTextListToTextProperty_PROC) (Display *, wchar_t **, int, XICCEncodingStyle, XTextProperty *);
PFN_XwcTextListToTextProperty_PROC XwcTextListToTextProperty_PROC = 0;
#  define XwcTextListToTextProperty (assert(XwcTextListToTextProperty_PROC != 0), XwcTextListToTextProperty_PROC)

typedef int (* PFN_XwcTextPropertyToTextList_PROC) (Display *, const XTextProperty *, wchar_t ***, int *);
PFN_XwcTextPropertyToTextList_PROC XwcTextPropertyToTextList_PROC = 0;
#  define XwcTextPropertyToTextList (assert(XwcTextPropertyToTextList_PROC != 0), XwcTextPropertyToTextList_PROC)


/* libX11: XKBlib.h */
typedef XkbDeviceLedInfoPtr (* PFN_XkbAddDeviceLedInfo_PROC) (XkbDeviceInfoPtr, unsigned int, unsigned int);
PFN_XkbAddDeviceLedInfo_PROC XkbAddDeviceLedInfo_PROC = 0;
#  define XkbAddDeviceLedInfo (assert(XkbAddDeviceLedInfo_PROC != 0), XkbAddDeviceLedInfo_PROC)

typedef XkbKeyTypePtr (* PFN_XkbAddKeyType_PROC) (XkbDescPtr, Atom, int, int, int);
PFN_XkbAddKeyType_PROC XkbAddKeyType_PROC = 0;
#  define XkbAddKeyType (assert(XkbAddKeyType_PROC != 0), XkbAddKeyType_PROC)

typedef int (* PFN_XkbAllocClientMap_PROC) (XkbDescPtr, unsigned int, unsigned int);
PFN_XkbAllocClientMap_PROC XkbAllocClientMap_PROC = 0;
#  define XkbAllocClientMap (assert(XkbAllocClientMap_PROC != 0), XkbAllocClientMap_PROC)

typedef int (* PFN_XkbAllocCompatMap_PROC) (XkbDescPtr, unsigned int, unsigned int);
PFN_XkbAllocCompatMap_PROC XkbAllocCompatMap_PROC = 0;
#  define XkbAllocCompatMap (assert(XkbAllocCompatMap_PROC != 0), XkbAllocCompatMap_PROC)

typedef int (* PFN_XkbAllocControls_PROC) (XkbDescPtr, unsigned int);
PFN_XkbAllocControls_PROC XkbAllocControls_PROC = 0;
#  define XkbAllocControls (assert(XkbAllocControls_PROC != 0), XkbAllocControls_PROC)

typedef XkbDeviceInfoPtr (* PFN_XkbAllocDeviceInfo_PROC) (unsigned int, unsigned int, unsigned int);
PFN_XkbAllocDeviceInfo_PROC XkbAllocDeviceInfo_PROC = 0;
#  define XkbAllocDeviceInfo (assert(XkbAllocDeviceInfo_PROC != 0), XkbAllocDeviceInfo_PROC)

typedef int (* PFN_XkbAllocIndicatorMaps_PROC) (XkbDescPtr);
PFN_XkbAllocIndicatorMaps_PROC XkbAllocIndicatorMaps_PROC = 0;
#  define XkbAllocIndicatorMaps (assert(XkbAllocIndicatorMaps_PROC != 0), XkbAllocIndicatorMaps_PROC)

typedef XkbDescPtr (* PFN_XkbAllocKeyboard_PROC) (void);
PFN_XkbAllocKeyboard_PROC XkbAllocKeyboard_PROC = 0;
#  define XkbAllocKeyboard (assert(XkbAllocKeyboard_PROC != 0), XkbAllocKeyboard_PROC)

typedef int (* PFN_XkbAllocNames_PROC) (XkbDescPtr, unsigned int, int, int);
PFN_XkbAllocNames_PROC XkbAllocNames_PROC = 0;
#  define XkbAllocNames (assert(XkbAllocNames_PROC != 0), XkbAllocNames_PROC)

typedef int (* PFN_XkbAllocServerMap_PROC) (XkbDescPtr, unsigned int, unsigned int);
PFN_XkbAllocServerMap_PROC XkbAllocServerMap_PROC = 0;
#  define XkbAllocServerMap (assert(XkbAllocServerMap_PROC != 0), XkbAllocServerMap_PROC)

typedef int (* PFN_XkbApplyCompatMapToKey_PROC) (XkbDescPtr, KeyCode, XkbChangesPtr);
PFN_XkbApplyCompatMapToKey_PROC XkbApplyCompatMapToKey_PROC = 0;
#  define XkbApplyCompatMapToKey (assert(XkbApplyCompatMapToKey_PROC != 0), XkbApplyCompatMapToKey_PROC)

typedef int (* PFN_XkbApplyVirtualModChanges_PROC) (XkbDescPtr, unsigned int, XkbChangesPtr);
PFN_XkbApplyVirtualModChanges_PROC XkbApplyVirtualModChanges_PROC = 0;
#  define XkbApplyVirtualModChanges (assert(XkbApplyVirtualModChanges_PROC != 0), XkbApplyVirtualModChanges_PROC)

typedef int (* PFN_XkbBell_PROC) (Display *, Window, int, Atom);
PFN_XkbBell_PROC XkbBell_PROC = 0;
#  define XkbBell (assert(XkbBell_PROC != 0), XkbBell_PROC)

typedef int (* PFN_XkbBellEvent_PROC) (Display *, Window, int, Atom);
PFN_XkbBellEvent_PROC XkbBellEvent_PROC = 0;
#  define XkbBellEvent (assert(XkbBellEvent_PROC != 0), XkbBellEvent_PROC)

typedef int (* PFN_XkbChangeDeviceInfo_PROC) (Display *, XkbDeviceInfoPtr, XkbDeviceChangesPtr);
PFN_XkbChangeDeviceInfo_PROC XkbChangeDeviceInfo_PROC = 0;
#  define XkbChangeDeviceInfo (assert(XkbChangeDeviceInfo_PROC != 0), XkbChangeDeviceInfo_PROC)

typedef int (* PFN_XkbChangeEnabledControls_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbChangeEnabledControls_PROC XkbChangeEnabledControls_PROC = 0;
#  define XkbChangeEnabledControls (assert(XkbChangeEnabledControls_PROC != 0), XkbChangeEnabledControls_PROC)

typedef int (* PFN_XkbChangeKeycodeRange_PROC) (XkbDescPtr, int, int, XkbChangesPtr);
PFN_XkbChangeKeycodeRange_PROC XkbChangeKeycodeRange_PROC = 0;
#  define XkbChangeKeycodeRange (assert(XkbChangeKeycodeRange_PROC != 0), XkbChangeKeycodeRange_PROC)

typedef int (* PFN_XkbChangeMap_PROC) (Display *, XkbDescPtr, XkbMapChangesPtr);
PFN_XkbChangeMap_PROC XkbChangeMap_PROC = 0;
#  define XkbChangeMap (assert(XkbChangeMap_PROC != 0), XkbChangeMap_PROC)

typedef int (* PFN_XkbChangeNames_PROC) (Display *, XkbDescPtr, XkbNameChangesPtr);
PFN_XkbChangeNames_PROC XkbChangeNames_PROC = 0;
#  define XkbChangeNames (assert(XkbChangeNames_PROC != 0), XkbChangeNames_PROC)

typedef int (* PFN_XkbChangeTypesOfKey_PROC) (XkbDescPtr, int, int, unsigned int, int *, XkbMapChangesPtr);
PFN_XkbChangeTypesOfKey_PROC XkbChangeTypesOfKey_PROC = 0;
#  define XkbChangeTypesOfKey (assert(XkbChangeTypesOfKey_PROC != 0), XkbChangeTypesOfKey_PROC)

typedef int (* PFN_XkbComputeEffectiveMap_PROC) (XkbDescPtr, XkbKeyTypePtr, unsigned char *);
PFN_XkbComputeEffectiveMap_PROC XkbComputeEffectiveMap_PROC = 0;
#  define XkbComputeEffectiveMap (assert(XkbComputeEffectiveMap_PROC != 0), XkbComputeEffectiveMap_PROC)

typedef int (* PFN_XkbCopyKeyType_PROC) (XkbKeyTypePtr, XkbKeyTypePtr);
PFN_XkbCopyKeyType_PROC XkbCopyKeyType_PROC = 0;
#  define XkbCopyKeyType (assert(XkbCopyKeyType_PROC != 0), XkbCopyKeyType_PROC)

typedef int (* PFN_XkbCopyKeyTypes_PROC) (XkbKeyTypePtr, XkbKeyTypePtr, int);
PFN_XkbCopyKeyTypes_PROC XkbCopyKeyTypes_PROC = 0;
#  define XkbCopyKeyTypes (assert(XkbCopyKeyTypes_PROC != 0), XkbCopyKeyTypes_PROC)

typedef int (* PFN_XkbDeviceBell_PROC) (Display *, Window, int, int, int, int, Atom);
PFN_XkbDeviceBell_PROC XkbDeviceBell_PROC = 0;
#  define XkbDeviceBell (assert(XkbDeviceBell_PROC != 0), XkbDeviceBell_PROC)

typedef int (* PFN_XkbDeviceBellEvent_PROC) (Display *, Window, int, int, int, int, Atom);
PFN_XkbDeviceBellEvent_PROC XkbDeviceBellEvent_PROC = 0;
#  define XkbDeviceBellEvent (assert(XkbDeviceBellEvent_PROC != 0), XkbDeviceBellEvent_PROC)

typedef int (* PFN_XkbForceBell_PROC) (Display *, int);
PFN_XkbForceBell_PROC XkbForceBell_PROC = 0;
#  define XkbForceBell (assert(XkbForceBell_PROC != 0), XkbForceBell_PROC)

typedef int (* PFN_XkbForceDeviceBell_PROC) (Display *, int, int, int, int);
PFN_XkbForceDeviceBell_PROC XkbForceDeviceBell_PROC = 0;
#  define XkbForceDeviceBell (assert(XkbForceDeviceBell_PROC != 0), XkbForceDeviceBell_PROC)

typedef void (* PFN_XkbFreeClientMap_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeClientMap_PROC XkbFreeClientMap_PROC = 0;
#  define XkbFreeClientMap (assert(XkbFreeClientMap_PROC != 0), XkbFreeClientMap_PROC)

typedef void (* PFN_XkbFreeCompatMap_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeCompatMap_PROC XkbFreeCompatMap_PROC = 0;
#  define XkbFreeCompatMap (assert(XkbFreeCompatMap_PROC != 0), XkbFreeCompatMap_PROC)

typedef void (* PFN_XkbFreeComponentList_PROC) (XkbComponentListPtr);
PFN_XkbFreeComponentList_PROC XkbFreeComponentList_PROC = 0;
#  define XkbFreeComponentList (assert(XkbFreeComponentList_PROC != 0), XkbFreeComponentList_PROC)

typedef void (* PFN_XkbFreeControls_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeControls_PROC XkbFreeControls_PROC = 0;
#  define XkbFreeControls (assert(XkbFreeControls_PROC != 0), XkbFreeControls_PROC)

typedef void (* PFN_XkbFreeDeviceInfo_PROC) (XkbDeviceInfoPtr, unsigned int, int);
PFN_XkbFreeDeviceInfo_PROC XkbFreeDeviceInfo_PROC = 0;
#  define XkbFreeDeviceInfo (assert(XkbFreeDeviceInfo_PROC != 0), XkbFreeDeviceInfo_PROC)

typedef void (* PFN_XkbFreeIndicatorMaps_PROC) (XkbDescPtr);
PFN_XkbFreeIndicatorMaps_PROC XkbFreeIndicatorMaps_PROC = 0;
#  define XkbFreeIndicatorMaps (assert(XkbFreeIndicatorMaps_PROC != 0), XkbFreeIndicatorMaps_PROC)

typedef void (* PFN_XkbFreeKeyboard_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeKeyboard_PROC XkbFreeKeyboard_PROC = 0;
#  define XkbFreeKeyboard (assert(XkbFreeKeyboard_PROC != 0), XkbFreeKeyboard_PROC)

typedef void (* PFN_XkbFreeNames_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeNames_PROC XkbFreeNames_PROC = 0;
#  define XkbFreeNames (assert(XkbFreeNames_PROC != 0), XkbFreeNames_PROC)

typedef void (* PFN_XkbFreeServerMap_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbFreeServerMap_PROC XkbFreeServerMap_PROC = 0;
#  define XkbFreeServerMap (assert(XkbFreeServerMap_PROC != 0), XkbFreeServerMap_PROC)

typedef int (* PFN_XkbGetAutoRepeatRate_PROC) (Display *, unsigned int, unsigned int *, unsigned int *);
PFN_XkbGetAutoRepeatRate_PROC XkbGetAutoRepeatRate_PROC = 0;
#  define XkbGetAutoRepeatRate (assert(XkbGetAutoRepeatRate_PROC != 0), XkbGetAutoRepeatRate_PROC)

typedef int (* PFN_XkbGetAutoResetControls_PROC) (Display *, unsigned int *, unsigned int *);
PFN_XkbGetAutoResetControls_PROC XkbGetAutoResetControls_PROC = 0;
#  define XkbGetAutoResetControls (assert(XkbGetAutoResetControls_PROC != 0), XkbGetAutoResetControls_PROC)

typedef int (* PFN_XkbGetCompatMap_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetCompatMap_PROC XkbGetCompatMap_PROC = 0;
#  define XkbGetCompatMap (assert(XkbGetCompatMap_PROC != 0), XkbGetCompatMap_PROC)

typedef int (* PFN_XkbGetControls_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbGetControls_PROC XkbGetControls_PROC = 0;
#  define XkbGetControls (assert(XkbGetControls_PROC != 0), XkbGetControls_PROC)

typedef int (* PFN_XkbGetDetectableAutoRepeat_PROC) (Display *, int *);
PFN_XkbGetDetectableAutoRepeat_PROC XkbGetDetectableAutoRepeat_PROC = 0;
#  define XkbGetDetectableAutoRepeat (assert(XkbGetDetectableAutoRepeat_PROC != 0), XkbGetDetectableAutoRepeat_PROC)

typedef int (* PFN_XkbGetDeviceButtonActions_PROC) (Display *, XkbDeviceInfoPtr, int, unsigned int, unsigned int);
PFN_XkbGetDeviceButtonActions_PROC XkbGetDeviceButtonActions_PROC = 0;
#  define XkbGetDeviceButtonActions (assert(XkbGetDeviceButtonActions_PROC != 0), XkbGetDeviceButtonActions_PROC)

typedef XkbDeviceInfoPtr (* PFN_XkbGetDeviceInfo_PROC) (Display *, unsigned int, unsigned int, unsigned int, unsigned int);
PFN_XkbGetDeviceInfo_PROC XkbGetDeviceInfo_PROC = 0;
#  define XkbGetDeviceInfo (assert(XkbGetDeviceInfo_PROC != 0), XkbGetDeviceInfo_PROC)

typedef int (* PFN_XkbGetDeviceInfoChanges_PROC) (Display *, XkbDeviceInfoPtr, XkbDeviceChangesPtr);
PFN_XkbGetDeviceInfoChanges_PROC XkbGetDeviceInfoChanges_PROC = 0;
#  define XkbGetDeviceInfoChanges (assert(XkbGetDeviceInfoChanges_PROC != 0), XkbGetDeviceInfoChanges_PROC)

typedef int (* PFN_XkbGetDeviceLedInfo_PROC) (Display *, XkbDeviceInfoPtr, unsigned int, unsigned int, unsigned int);
PFN_XkbGetDeviceLedInfo_PROC XkbGetDeviceLedInfo_PROC = 0;
#  define XkbGetDeviceLedInfo (assert(XkbGetDeviceLedInfo_PROC != 0), XkbGetDeviceLedInfo_PROC)

typedef int (* PFN_XkbGetIndicatorMap_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbGetIndicatorMap_PROC XkbGetIndicatorMap_PROC = 0;
#  define XkbGetIndicatorMap (assert(XkbGetIndicatorMap_PROC != 0), XkbGetIndicatorMap_PROC)

typedef int (* PFN_XkbGetIndicatorState_PROC) (Display *, unsigned int, unsigned int *);
PFN_XkbGetIndicatorState_PROC XkbGetIndicatorState_PROC = 0;
#  define XkbGetIndicatorState (assert(XkbGetIndicatorState_PROC != 0), XkbGetIndicatorState_PROC)

typedef int (* PFN_XkbGetKeyActions_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyActions_PROC XkbGetKeyActions_PROC = 0;
#  define XkbGetKeyActions (assert(XkbGetKeyActions_PROC != 0), XkbGetKeyActions_PROC)

typedef int (* PFN_XkbGetKeyBehaviors_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyBehaviors_PROC XkbGetKeyBehaviors_PROC = 0;
#  define XkbGetKeyBehaviors (assert(XkbGetKeyBehaviors_PROC != 0), XkbGetKeyBehaviors_PROC)

typedef int (* PFN_XkbGetKeyExplicitComponents_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyExplicitComponents_PROC XkbGetKeyExplicitComponents_PROC = 0;
#  define XkbGetKeyExplicitComponents (assert(XkbGetKeyExplicitComponents_PROC != 0), XkbGetKeyExplicitComponents_PROC)

typedef int (* PFN_XkbGetKeyModifierMap_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyModifierMap_PROC XkbGetKeyModifierMap_PROC = 0;
#  define XkbGetKeyModifierMap (assert(XkbGetKeyModifierMap_PROC != 0), XkbGetKeyModifierMap_PROC)

typedef int (* PFN_XkbGetKeySyms_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeySyms_PROC XkbGetKeySyms_PROC = 0;
#  define XkbGetKeySyms (assert(XkbGetKeySyms_PROC != 0), XkbGetKeySyms_PROC)

typedef int (* PFN_XkbGetKeyTypes_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyTypes_PROC XkbGetKeyTypes_PROC = 0;
#  define XkbGetKeyTypes (assert(XkbGetKeyTypes_PROC != 0), XkbGetKeyTypes_PROC)

typedef int (* PFN_XkbGetKeyVirtualModMap_PROC) (Display *, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbGetKeyVirtualModMap_PROC XkbGetKeyVirtualModMap_PROC = 0;
#  define XkbGetKeyVirtualModMap (assert(XkbGetKeyVirtualModMap_PROC != 0), XkbGetKeyVirtualModMap_PROC)

typedef XkbDescPtr (* PFN_XkbGetKeyboard_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbGetKeyboard_PROC XkbGetKeyboard_PROC = 0;
#  define XkbGetKeyboard (assert(XkbGetKeyboard_PROC != 0), XkbGetKeyboard_PROC)

typedef XkbDescPtr (* PFN_XkbGetKeyboardByName_PROC) (Display *, unsigned int, XkbComponentNamesPtr, unsigned int, unsigned int, int);
PFN_XkbGetKeyboardByName_PROC XkbGetKeyboardByName_PROC = 0;
#  define XkbGetKeyboardByName (assert(XkbGetKeyboardByName_PROC != 0), XkbGetKeyboardByName_PROC)

typedef XkbDescPtr (* PFN_XkbGetMap_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbGetMap_PROC XkbGetMap_PROC = 0;
#  define XkbGetMap (assert(XkbGetMap_PROC != 0), XkbGetMap_PROC)

typedef int (* PFN_XkbGetMapChanges_PROC) (Display *, XkbDescPtr, XkbMapChangesPtr);
PFN_XkbGetMapChanges_PROC XkbGetMapChanges_PROC = 0;
#  define XkbGetMapChanges (assert(XkbGetMapChanges_PROC != 0), XkbGetMapChanges_PROC)

typedef int (* PFN_XkbGetNamedDeviceIndicator_PROC) (Display *, unsigned int, unsigned int, unsigned int, Atom, int *, int *, XkbIndicatorMapPtr, int *);
PFN_XkbGetNamedDeviceIndicator_PROC XkbGetNamedDeviceIndicator_PROC = 0;
#  define XkbGetNamedDeviceIndicator (assert(XkbGetNamedDeviceIndicator_PROC != 0), XkbGetNamedDeviceIndicator_PROC)

typedef int (* PFN_XkbGetNamedIndicator_PROC) (Display *, Atom, int *, int *, XkbIndicatorMapPtr, int *);
PFN_XkbGetNamedIndicator_PROC XkbGetNamedIndicator_PROC = 0;
#  define XkbGetNamedIndicator (assert(XkbGetNamedIndicator_PROC != 0), XkbGetNamedIndicator_PROC)

typedef int (* PFN_XkbGetNames_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetNames_PROC XkbGetNames_PROC = 0;
#  define XkbGetNames (assert(XkbGetNames_PROC != 0), XkbGetNames_PROC)

typedef int (* PFN_XkbGetPerClientControls_PROC) (Display *, unsigned int *);
PFN_XkbGetPerClientControls_PROC XkbGetPerClientControls_PROC = 0;
#  define XkbGetPerClientControls (assert(XkbGetPerClientControls_PROC != 0), XkbGetPerClientControls_PROC)

typedef int (* PFN_XkbGetState_PROC) (Display *, unsigned int, XkbStatePtr);
PFN_XkbGetState_PROC XkbGetState_PROC = 0;
#  define XkbGetState (assert(XkbGetState_PROC != 0), XkbGetState_PROC)

typedef int (* PFN_XkbGetUpdatedMap_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetUpdatedMap_PROC XkbGetUpdatedMap_PROC = 0;
#  define XkbGetUpdatedMap (assert(XkbGetUpdatedMap_PROC != 0), XkbGetUpdatedMap_PROC)

typedef int (* PFN_XkbGetVirtualMods_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbGetVirtualMods_PROC XkbGetVirtualMods_PROC = 0;
#  define XkbGetVirtualMods (assert(XkbGetVirtualMods_PROC != 0), XkbGetVirtualMods_PROC)

typedef unsigned int (* PFN_XkbGetXlibControls_PROC) (Display *);
PFN_XkbGetXlibControls_PROC XkbGetXlibControls_PROC = 0;
#  define XkbGetXlibControls (assert(XkbGetXlibControls_PROC != 0), XkbGetXlibControls_PROC)

typedef int (* PFN_XkbIgnoreExtension_PROC) (int);
PFN_XkbIgnoreExtension_PROC XkbIgnoreExtension_PROC = 0;
#  define XkbIgnoreExtension (assert(XkbIgnoreExtension_PROC != 0), XkbIgnoreExtension_PROC)

typedef int (* PFN_XkbInitCanonicalKeyTypes_PROC) (XkbDescPtr, unsigned int, int);
PFN_XkbInitCanonicalKeyTypes_PROC XkbInitCanonicalKeyTypes_PROC = 0;
#  define XkbInitCanonicalKeyTypes (assert(XkbInitCanonicalKeyTypes_PROC != 0), XkbInitCanonicalKeyTypes_PROC)

typedef int (* PFN_XkbKeyTypesForCoreSymbols_PROC) (XkbDescPtr, int, KeySym *, unsigned int, int *, KeySym *);
PFN_XkbKeyTypesForCoreSymbols_PROC XkbKeyTypesForCoreSymbols_PROC = 0;
#  define XkbKeyTypesForCoreSymbols (assert(XkbKeyTypesForCoreSymbols_PROC != 0), XkbKeyTypesForCoreSymbols_PROC)

typedef KeySym (* PFN_XkbKeycodeToKeysym_PROC) (Display *, KeyCode, int, int);
PFN_XkbKeycodeToKeysym_PROC XkbKeycodeToKeysym_PROC = 0;
#  define XkbKeycodeToKeysym (assert(XkbKeycodeToKeysym_PROC != 0), XkbKeycodeToKeysym_PROC)

typedef unsigned int (* PFN_XkbKeysymToModifiers_PROC) (Display *, KeySym);
PFN_XkbKeysymToModifiers_PROC XkbKeysymToModifiers_PROC = 0;
#  define XkbKeysymToModifiers (assert(XkbKeysymToModifiers_PROC != 0), XkbKeysymToModifiers_PROC)

typedef int (* PFN_XkbLatchGroup_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbLatchGroup_PROC XkbLatchGroup_PROC = 0;
#  define XkbLatchGroup (assert(XkbLatchGroup_PROC != 0), XkbLatchGroup_PROC)

typedef int (* PFN_XkbLatchModifiers_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbLatchModifiers_PROC XkbLatchModifiers_PROC = 0;
#  define XkbLatchModifiers (assert(XkbLatchModifiers_PROC != 0), XkbLatchModifiers_PROC)

typedef int (* PFN_XkbLibraryVersion_PROC) (int *, int *);
PFN_XkbLibraryVersion_PROC XkbLibraryVersion_PROC = 0;
#  define XkbLibraryVersion (assert(XkbLibraryVersion_PROC != 0), XkbLibraryVersion_PROC)

typedef XkbComponentListPtr (* PFN_XkbListComponents_PROC) (Display *, unsigned int, XkbComponentNamesPtr, int *);
PFN_XkbListComponents_PROC XkbListComponents_PROC = 0;
#  define XkbListComponents (assert(XkbListComponents_PROC != 0), XkbListComponents_PROC)

typedef int (* PFN_XkbLockGroup_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbLockGroup_PROC XkbLockGroup_PROC = 0;
#  define XkbLockGroup (assert(XkbLockGroup_PROC != 0), XkbLockGroup_PROC)

typedef int (* PFN_XkbLockModifiers_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbLockModifiers_PROC XkbLockModifiers_PROC = 0;
#  define XkbLockModifiers (assert(XkbLockModifiers_PROC != 0), XkbLockModifiers_PROC)

typedef int (* PFN_XkbLookupKeyBinding_PROC) (Display *, KeySym, unsigned int, char *, int, int *);
PFN_XkbLookupKeyBinding_PROC XkbLookupKeyBinding_PROC = 0;
#  define XkbLookupKeyBinding (assert(XkbLookupKeyBinding_PROC != 0), XkbLookupKeyBinding_PROC)

typedef int (* PFN_XkbLookupKeySym_PROC) (Display *, KeyCode, unsigned int, unsigned int *, KeySym *);
PFN_XkbLookupKeySym_PROC XkbLookupKeySym_PROC = 0;
#  define XkbLookupKeySym (assert(XkbLookupKeySym_PROC != 0), XkbLookupKeySym_PROC)

typedef void (* PFN_XkbNoteControlsChanges_PROC) (XkbControlsChangesPtr, XkbControlsNotifyEvent *, unsigned int);
PFN_XkbNoteControlsChanges_PROC XkbNoteControlsChanges_PROC = 0;
#  define XkbNoteControlsChanges (assert(XkbNoteControlsChanges_PROC != 0), XkbNoteControlsChanges_PROC)

typedef void (* PFN_XkbNoteDeviceChanges_PROC) (XkbDeviceChangesPtr, XkbExtensionDeviceNotifyEvent *, unsigned int);
PFN_XkbNoteDeviceChanges_PROC XkbNoteDeviceChanges_PROC = 0;
#  define XkbNoteDeviceChanges (assert(XkbNoteDeviceChanges_PROC != 0), XkbNoteDeviceChanges_PROC)

typedef void (* PFN_XkbNoteMapChanges_PROC) (XkbMapChangesPtr, XkbMapNotifyEvent *, unsigned int);
PFN_XkbNoteMapChanges_PROC XkbNoteMapChanges_PROC = 0;
#  define XkbNoteMapChanges (assert(XkbNoteMapChanges_PROC != 0), XkbNoteMapChanges_PROC)

typedef void (* PFN_XkbNoteNameChanges_PROC) (XkbNameChangesPtr, XkbNamesNotifyEvent *, unsigned int);
PFN_XkbNoteNameChanges_PROC XkbNoteNameChanges_PROC = 0;
#  define XkbNoteNameChanges (assert(XkbNoteNameChanges_PROC != 0), XkbNoteNameChanges_PROC)

typedef Display *(* PFN_XkbOpenDisplay_PROC) (const char *, int *, int *, int *, int *, int *);
PFN_XkbOpenDisplay_PROC XkbOpenDisplay_PROC = 0;
#  define XkbOpenDisplay (assert(XkbOpenDisplay_PROC != 0), XkbOpenDisplay_PROC)

typedef int (* PFN_XkbQueryExtension_PROC) (Display *, int *, int *, int *, int *, int *);
PFN_XkbQueryExtension_PROC XkbQueryExtension_PROC = 0;
#  define XkbQueryExtension (assert(XkbQueryExtension_PROC != 0), XkbQueryExtension_PROC)

typedef int (* PFN_XkbRefreshKeyboardMapping_PROC) (XkbMapNotifyEvent *);
PFN_XkbRefreshKeyboardMapping_PROC XkbRefreshKeyboardMapping_PROC = 0;
#  define XkbRefreshKeyboardMapping (assert(XkbRefreshKeyboardMapping_PROC != 0), XkbRefreshKeyboardMapping_PROC)

typedef int (* PFN_XkbResizeDeviceButtonActions_PROC) (XkbDeviceInfoPtr, unsigned int);
PFN_XkbResizeDeviceButtonActions_PROC XkbResizeDeviceButtonActions_PROC = 0;
#  define XkbResizeDeviceButtonActions (assert(XkbResizeDeviceButtonActions_PROC != 0), XkbResizeDeviceButtonActions_PROC)

typedef XkbAction *(* PFN_XkbResizeKeyActions_PROC) (XkbDescPtr, int, int);
PFN_XkbResizeKeyActions_PROC XkbResizeKeyActions_PROC = 0;
#  define XkbResizeKeyActions (assert(XkbResizeKeyActions_PROC != 0), XkbResizeKeyActions_PROC)

typedef KeySym *(* PFN_XkbResizeKeySyms_PROC) (XkbDescPtr, int, int);
PFN_XkbResizeKeySyms_PROC XkbResizeKeySyms_PROC = 0;
#  define XkbResizeKeySyms (assert(XkbResizeKeySyms_PROC != 0), XkbResizeKeySyms_PROC)

typedef int (* PFN_XkbResizeKeyType_PROC) (XkbDescPtr, int, int, int, int);
PFN_XkbResizeKeyType_PROC XkbResizeKeyType_PROC = 0;
#  define XkbResizeKeyType (assert(XkbResizeKeyType_PROC != 0), XkbResizeKeyType_PROC)

typedef int (* PFN_XkbSelectEventDetails_PROC) (Display *, unsigned int, unsigned int, unsigned long, unsigned long);
PFN_XkbSelectEventDetails_PROC XkbSelectEventDetails_PROC = 0;
#  define XkbSelectEventDetails (assert(XkbSelectEventDetails_PROC != 0), XkbSelectEventDetails_PROC)

typedef int (* PFN_XkbSelectEvents_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbSelectEvents_PROC XkbSelectEvents_PROC = 0;
#  define XkbSelectEvents (assert(XkbSelectEvents_PROC != 0), XkbSelectEvents_PROC)

typedef void (* PFN_XkbSetAtomFuncs_PROC) (XkbInternAtomFunc, XkbGetAtomNameFunc);
PFN_XkbSetAtomFuncs_PROC XkbSetAtomFuncs_PROC = 0;
#  define XkbSetAtomFuncs (assert(XkbSetAtomFuncs_PROC != 0), XkbSetAtomFuncs_PROC)

typedef int (* PFN_XkbSetAutoRepeatRate_PROC) (Display *, unsigned int, unsigned int, unsigned int);
PFN_XkbSetAutoRepeatRate_PROC XkbSetAutoRepeatRate_PROC = 0;
#  define XkbSetAutoRepeatRate (assert(XkbSetAutoRepeatRate_PROC != 0), XkbSetAutoRepeatRate_PROC)

typedef int (* PFN_XkbSetAutoResetControls_PROC) (Display *, unsigned int, unsigned int *, unsigned int *);
PFN_XkbSetAutoResetControls_PROC XkbSetAutoResetControls_PROC = 0;
#  define XkbSetAutoResetControls (assert(XkbSetAutoResetControls_PROC != 0), XkbSetAutoResetControls_PROC)

typedef int (* PFN_XkbSetCompatMap_PROC) (Display *, unsigned int, XkbDescPtr, int);
PFN_XkbSetCompatMap_PROC XkbSetCompatMap_PROC = 0;
#  define XkbSetCompatMap (assert(XkbSetCompatMap_PROC != 0), XkbSetCompatMap_PROC)

typedef int (* PFN_XkbSetControls_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbSetControls_PROC XkbSetControls_PROC = 0;
#  define XkbSetControls (assert(XkbSetControls_PROC != 0), XkbSetControls_PROC)

typedef int (* PFN_XkbSetDebuggingFlags_PROC) (Display *, unsigned int, unsigned int, char *, unsigned int, unsigned int, unsigned int *, unsigned int *);
PFN_XkbSetDebuggingFlags_PROC XkbSetDebuggingFlags_PROC = 0;
#  define XkbSetDebuggingFlags (assert(XkbSetDebuggingFlags_PROC != 0), XkbSetDebuggingFlags_PROC)

typedef int (* PFN_XkbSetDetectableAutoRepeat_PROC) (Display *, int, int *);
PFN_XkbSetDetectableAutoRepeat_PROC XkbSetDetectableAutoRepeat_PROC = 0;
#  define XkbSetDetectableAutoRepeat (assert(XkbSetDetectableAutoRepeat_PROC != 0), XkbSetDetectableAutoRepeat_PROC)

typedef int (* PFN_XkbSetDeviceButtonActions_PROC) (Display *, XkbDeviceInfoPtr, unsigned int, unsigned int);
PFN_XkbSetDeviceButtonActions_PROC XkbSetDeviceButtonActions_PROC = 0;
#  define XkbSetDeviceButtonActions (assert(XkbSetDeviceButtonActions_PROC != 0), XkbSetDeviceButtonActions_PROC)

typedef int (* PFN_XkbSetDeviceInfo_PROC) (Display *, unsigned int, XkbDeviceInfoPtr);
PFN_XkbSetDeviceInfo_PROC XkbSetDeviceInfo_PROC = 0;
#  define XkbSetDeviceInfo (assert(XkbSetDeviceInfo_PROC != 0), XkbSetDeviceInfo_PROC)

typedef int (* PFN_XkbSetDeviceLedInfo_PROC) (Display *, XkbDeviceInfoPtr, unsigned int, unsigned int, unsigned int);
PFN_XkbSetDeviceLedInfo_PROC XkbSetDeviceLedInfo_PROC = 0;
#  define XkbSetDeviceLedInfo (assert(XkbSetDeviceLedInfo_PROC != 0), XkbSetDeviceLedInfo_PROC)

typedef int (* PFN_XkbSetIgnoreLockMods_PROC) (Display *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
PFN_XkbSetIgnoreLockMods_PROC XkbSetIgnoreLockMods_PROC = 0;
#  define XkbSetIgnoreLockMods (assert(XkbSetIgnoreLockMods_PROC != 0), XkbSetIgnoreLockMods_PROC)

typedef int (* PFN_XkbSetIndicatorMap_PROC) (Display *, unsigned long, XkbDescPtr);
PFN_XkbSetIndicatorMap_PROC XkbSetIndicatorMap_PROC = 0;
#  define XkbSetIndicatorMap (assert(XkbSetIndicatorMap_PROC != 0), XkbSetIndicatorMap_PROC)

typedef int (* PFN_XkbSetMap_PROC) (Display *, unsigned int, XkbDescPtr);
PFN_XkbSetMap_PROC XkbSetMap_PROC = 0;
#  define XkbSetMap (assert(XkbSetMap_PROC != 0), XkbSetMap_PROC)

typedef int (* PFN_XkbSetNamedDeviceIndicator_PROC) (Display *, unsigned int, unsigned int, unsigned int, Atom, int, int, int, XkbIndicatorMapPtr);
PFN_XkbSetNamedDeviceIndicator_PROC XkbSetNamedDeviceIndicator_PROC = 0;
#  define XkbSetNamedDeviceIndicator (assert(XkbSetNamedDeviceIndicator_PROC != 0), XkbSetNamedDeviceIndicator_PROC)

typedef int (* PFN_XkbSetNamedIndicator_PROC) (Display *, Atom, int, int, int, XkbIndicatorMapPtr);
PFN_XkbSetNamedIndicator_PROC XkbSetNamedIndicator_PROC = 0;
#  define XkbSetNamedIndicator (assert(XkbSetNamedIndicator_PROC != 0), XkbSetNamedIndicator_PROC)

typedef int (* PFN_XkbSetNames_PROC) (Display *, unsigned int, unsigned int, unsigned int, XkbDescPtr);
PFN_XkbSetNames_PROC XkbSetNames_PROC = 0;
#  define XkbSetNames (assert(XkbSetNames_PROC != 0), XkbSetNames_PROC)

typedef int (* PFN_XkbSetPerClientControls_PROC) (Display *, unsigned int, unsigned int *);
PFN_XkbSetPerClientControls_PROC XkbSetPerClientControls_PROC = 0;
#  define XkbSetPerClientControls (assert(XkbSetPerClientControls_PROC != 0), XkbSetPerClientControls_PROC)

typedef int (* PFN_XkbSetServerInternalMods_PROC) (Display *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
PFN_XkbSetServerInternalMods_PROC XkbSetServerInternalMods_PROC = 0;
#  define XkbSetServerInternalMods (assert(XkbSetServerInternalMods_PROC != 0), XkbSetServerInternalMods_PROC)

typedef unsigned int (* PFN_XkbSetXlibControls_PROC) (Display *, unsigned int, unsigned int);
PFN_XkbSetXlibControls_PROC XkbSetXlibControls_PROC = 0;
#  define XkbSetXlibControls (assert(XkbSetXlibControls_PROC != 0), XkbSetXlibControls_PROC)

typedef char (* PFN_XkbToControl_PROC) (char);
PFN_XkbToControl_PROC XkbToControl_PROC = 0;
#  define XkbToControl (assert(XkbToControl_PROC != 0), XkbToControl_PROC)

typedef int (* PFN_XkbTranslateKeyCode_PROC) (XkbDescPtr, KeyCode, unsigned int, unsigned int *, KeySym *);
PFN_XkbTranslateKeyCode_PROC XkbTranslateKeyCode_PROC = 0;
#  define XkbTranslateKeyCode (assert(XkbTranslateKeyCode_PROC != 0), XkbTranslateKeyCode_PROC)

typedef int (* PFN_XkbTranslateKeySym_PROC) (Display *, KeySym *, unsigned int, char *, int, int *);
PFN_XkbTranslateKeySym_PROC XkbTranslateKeySym_PROC = 0;
#  define XkbTranslateKeySym (assert(XkbTranslateKeySym_PROC != 0), XkbTranslateKeySym_PROC)

typedef int (* PFN_XkbUpdateActionVirtualMods_PROC) (XkbDescPtr, XkbAction *, unsigned int);
PFN_XkbUpdateActionVirtualMods_PROC XkbUpdateActionVirtualMods_PROC = 0;
#  define XkbUpdateActionVirtualMods (assert(XkbUpdateActionVirtualMods_PROC != 0), XkbUpdateActionVirtualMods_PROC)

typedef void (* PFN_XkbUpdateKeyTypeVirtualMods_PROC) (XkbDescPtr, XkbKeyTypePtr, unsigned int, XkbChangesPtr);
PFN_XkbUpdateKeyTypeVirtualMods_PROC XkbUpdateKeyTypeVirtualMods_PROC = 0;
#  define XkbUpdateKeyTypeVirtualMods (assert(XkbUpdateKeyTypeVirtualMods_PROC != 0), XkbUpdateKeyTypeVirtualMods_PROC)

typedef int (* PFN_XkbUpdateMapFromCore_PROC) (XkbDescPtr, KeyCode, int, int, KeySym *, XkbChangesPtr);
PFN_XkbUpdateMapFromCore_PROC XkbUpdateMapFromCore_PROC = 0;
#  define XkbUpdateMapFromCore (assert(XkbUpdateMapFromCore_PROC != 0), XkbUpdateMapFromCore_PROC)

typedef int (* PFN_XkbUseExtension_PROC) (Display *, int *, int *);
PFN_XkbUseExtension_PROC XkbUseExtension_PROC = 0;
#  define XkbUseExtension (assert(XkbUseExtension_PROC != 0), XkbUseExtension_PROC)

typedef int (* PFN_XkbVirtualModsToReal_PROC) (XkbDescPtr, unsigned int, unsigned int *);
PFN_XkbVirtualModsToReal_PROC XkbVirtualModsToReal_PROC = 0;
#  define XkbVirtualModsToReal (assert(XkbVirtualModsToReal_PROC != 0), XkbVirtualModsToReal_PROC)

typedef unsigned int (* PFN_XkbXlibControlsImplemented_PROC) (void);
PFN_XkbXlibControlsImplemented_PROC XkbXlibControlsImplemented_PROC = 0;
#  define XkbXlibControlsImplemented (assert(XkbXlibControlsImplemented_PROC != 0), XkbXlibControlsImplemented_PROC)
/* }}} */

struct _window_h_window_x11 {
    /* client window handle */
    Window handle;

    /* X11 visual object */
    Visual *visual;
};


struct _window_h_context_x11 {
    /* graphics context handle */
    GC handle;
};


struct _window_h_cursor_x11 {
    /* cursor handle */
    Cursor handle;
};


struct _window_h_x11 {
    /* handle do shared object */
    void *handle;

    /* main connection handle */
    Display *dpy;
    
    /* main root window handle*/
    Window root;

    /* inter-process communication window handle */
    Window ipc;

    /* SOURCE: https://xorg.freedesktop.org/releases/X11R7.6/doc/xorg-docs/specs/ICCCM/icccm.html#wm_protocols_property
     * */
    Atom WM_PROTOCOLS;

    /* SOURCE: https://xorg.freedesktop.org/releases/X11R7.6/doc/xorg-docs/specs/ICCCM/icccm.html#window_deletion
     * */
    Atom WM_DELETE_WINDOW;

    /* SOURCE: https://specifications.freedesktop.org/wm/latest/ar01s05.html#id-1.6.8
     * */
    Atom _NET_WM_STATE;

    Atom _NET_WM_STATE_MODAL;
    
    Atom _NET_WM_STATE_STICKY;
    
    Atom _NET_WM_STATE_MAXIMIZED_VERT;
    
    Atom _NET_WM_STATE_MAXIMIZED_HORZ;
    
    Atom _NET_WM_STATE_SHADED;
    
    Atom _NET_WM_STATE_SKIP_TASKBAR;
    
    Atom _NET_WM_STATE_SKIP_PAGER;
    
    Atom _NET_WM_STATE_HIDDEN;
    
    Atom _NET_WM_STATE_FULLSCREEN;
    
    Atom _NET_WM_STATE_ABOVE;
    
    Atom _NET_WM_STATE_BELOW;
    
    Atom _NET_WM_STATE_DEMANDS_ATTENTION;
    
    Atom _NET_WM_STATE_FOCUSED;

    Atom TARGETS;
    
    Atom CLIPBOARD;
    
    Atom UTF8_STRING;
};

/* }}} */
# endif /* WINDOW_BACKEND_X11 */
#
# /* WINDOW_BACKEND_WAYLAND - Wayland definitions layer */
# if defined (WINDOW_BACKEND_WAYLAND)
/* {{{ */

struct _window_h_window_wl {
    struct {
    
        /* ... */

    } wl;

    /* ... */

};


struct _window_h_context_wl {
    struct {
    
        /* ... */

    } wl;

    /* ... */

};


struct _window_h_cursor_wl {
    struct {
    
        /* ... */

    } wl;
};

typedef struct _window_h_wl *_window_h_wl;

struct _window_h_wl {
    /* handle do shared object */
    void *handle;

    struct {
    
        /* ... */

    } wl;

    /* ... */
};

/* }}} */
# endif /* WINDOW_BACKEND_WAYLAND */
#
# /* WINDOW_BACKEND_WIN32 - Win32 definitions layer */
# if defined (WINDOW_BACKEND_WIN32)
/* {{{ */

struct _window_h_window_win32 {
    /* client window handle */
    HWND handle;
};


struct _window_h_context_win32 {
    /* ... */
};


struct _window_h_cursor_win32 {
    /* ... */
};

typedef struct _window_h_win32 *_window_h_win32;

struct _window_h_win32 {
    /* handle do shared object */
    HMODULE handle;

    /* window class object */
    WNDCLASS wndclass;
};

/* }}} */
# endif /* WINDOW_BACKEND_WIN32 */
#
# /* WINDOW_BACKEND_GLX - GLX implementation layer */
# if defined (WINDOW_BACKEND_GLX)
/* {{{ */

/* internal functions (declarations) */

WININT int __win_glx_init(struct _window_h *, void *);

WININT int __win_glx_load(struct _window_h *);

WININT int __win_glx_unload(struct _window_h *);

WININT int __win_glx_create_context(struct _window_h *, struct _window_h_context *, struct _window_h_window *);

WININT int __win_glx_context_destroy(struct _window_h *, struct _window_h_context *);

WININT int __win_glx_make_current(struct _window_h *, struct _window_h_context *);

WININT int __win_glx_swap_buffers(struct _window_h *, struct _window_h_context *);

WININT int __win_glx_swap_interval(struct _window_h *, struct _window_h_context *, const int);

WININT void *__win_glx_get_proc_address(struct _window_h *, const char *);

WININT int __win_glx_choose_config(struct _window_h *);

WININT int __win_glx_get_visual(struct _window_h *, int *);

/* internal functions (definitions) */

WININT int __win_glx_init(struct _window_h *lib, void *display) {
    /* null-check */
    if (!lib) { return (0); }

    /* references */
    struct _window_h_glx *glx = lib->glx; 
    if (!glx) { return (0); }

    /* set 'glx' members */
    glx->dpy = display;

    /* set 'glx->attr' members */
    int attr_config[] = {
        GLX_FBCONFIG_ID,                GLX_DONT_CARE,
        GLX_BUFFER_SIZE,                0,
        GLX_LEVEL,                      0,
        GLX_DOUBLEBUFFER,               lib->hints.gl.dblbuf,
        GLX_STEREO,                     False,
        GLX_AUX_BUFFERS,                0,
        GLX_RED_SIZE,                   lib->hints.gl.red,
        GLX_GREEN_SIZE,                 lib->hints.gl.green,
        GLX_BLUE_SIZE,                  lib->hints.gl.blue,
        GLX_ALPHA_SIZE,                 lib->hints.gl.alpha,
        GLX_DEPTH_SIZE,                 lib->hints.gl.depth,
        GLX_STENCIL_SIZE,               lib->hints.gl.stencil,
        GLX_ACCUM_RED_SIZE,             0,
        GLX_ACCUM_GREEN_SIZE,           0,
        GLX_ACCUM_BLUE_SIZE,            0,
        GLX_ACCUM_ALPHA_SIZE,           0,
        GLX_RENDER_TYPE,                GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE,              GLX_WINDOW_BIT,
        GLX_X_RENDERABLE,               GLX_DONT_CARE,
        GLX_X_VISUAL_TYPE,              GLX_DONT_CARE,
        GLX_CONFIG_CAVEAT,              GLX_DONT_CARE,
        GLX_TRANSPARENT_TYPE,           GLX_NONE,
        GLX_TRANSPARENT_INDEX_VALUE,    GLX_DONT_CARE,
        GLX_TRANSPARENT_RED_VALUE,      GLX_DONT_CARE,
        GLX_TRANSPARENT_GREEN_VALUE,    GLX_DONT_CARE,
        GLX_TRANSPARENT_BLUE_VALUE,     GLX_DONT_CARE,
        GLX_TRANSPARENT_ALPHA_VALUE,    GLX_DONT_CARE,

        /* ... */

        0, 0
    };

    glx->attr.config = calloc(64, sizeof(int));
    if (!glx->attr.config) { return (0); }
    if (!memcpy(glx->attr.config, attr_config, sizeof(attr_config))) { return (0); }
    

    int attr_context[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB,  lib->hints.gl.major,
        GLX_CONTEXT_MINOR_VERSION_ARB,  lib->hints.gl.minor,
        GLX_CONTEXT_PROFILE_MASK_ARB,   lib->hints.gl.profile,

        /* ... */

        0, 0
    };

    glx->attr.context = calloc(64, sizeof(int));
    if (!glx->attr.context) { return (0); }
    if (!memcpy(glx->attr.context, attr_context, sizeof(attr_context))) { return (0); }
    
    /* success */
    return (1);
}


WININT int __win_glx_load(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }
    if (lib->glx) { return (1); }
    
    /* init-check */
    struct _window_h_glx *glx = calloc(1, sizeof(struct _window_h_glx));
    if (!glx) { return (0); }

    void *libglx = 0;
    {
        const char  *names[] = { "libGLX.so", "libGLX.so.0, libGLX.so.0.0.0", 0 };
        for (const char **name = names; *name; name++) {
            libglx = dlopen(*name, RTLD_LAZY | RTLD_LOCAL);
            if (libglx) { break; }
        }

        /* check if libglx loaded */
        if (!libglx) { return (0); }
    }
    
    /* {{{ */
    /* load 'glXGetProcAddress' and 'glXGetProcAddressARB'... */
    glXGetProcAddressARB_PROC = (PFN_glXGetProcAddressARB_PROC) dlsym(libglx, "glXGetProcAddressARB");
    glXGetProcAddress_PROC = (PFN_glXGetProcAddress_PROC) dlsym(libglx, "glXGetProcAddress");

    /* ...and load the rest of the GLX using them! */
    glXChooseVisual_PROC = (PFN_glXChooseVisual_PROC) glXGetProcAddress((const uint8_t *) "glXChooseVisual");
    if (!glXChooseVisual_PROC) {
        glXChooseVisual_PROC = (PFN_glXChooseVisual_PROC) glXGetProcAddressARB((const uint8_t *) "glXChooseVisual");
    }

    glXCreateContext_PROC = (PFN_glXCreateContext_PROC) glXGetProcAddress((const uint8_t *) "glXCreateContext");
    if (!glXCreateContext_PROC) {
        glXCreateContext_PROC = (PFN_glXCreateContext_PROC) glXGetProcAddressARB((const uint8_t *) "glXCreateContext");
    }

    glXDestroyContext_PROC = (PFN_glXDestroyContext_PROC) glXGetProcAddress((const uint8_t *) "glXDestroyContext");
    if (!glXDestroyContext_PROC) {
        glXDestroyContext_PROC = (PFN_glXDestroyContext_PROC) glXGetProcAddressARB((const uint8_t *) "glXDestroyContext");
    }

    glXMakeCurrent_PROC = (PFN_glXMakeCurrent_PROC) glXGetProcAddress((const uint8_t *) "glXMakeCurrent");
    if (!glXMakeCurrent_PROC) {
        glXMakeCurrent_PROC = (PFN_glXMakeCurrent_PROC) glXGetProcAddressARB((const uint8_t *) "glXMakeCurrent");
    }

    glXCopyContext_PROC = (PFN_glXCopyContext_PROC) glXGetProcAddress((const uint8_t *) "glXCopyContext");
    if (!glXCopyContext_PROC) {
        glXCopyContext_PROC = (PFN_glXCopyContext_PROC) glXGetProcAddressARB((const uint8_t *) "glXCopyContext");
    }

    glXSwapBuffers_PROC = (PFN_glXSwapBuffers_PROC) glXGetProcAddress((const uint8_t *) "glXSwapBuffers");
    if (!glXSwapBuffers_PROC) {
        glXSwapBuffers_PROC = (PFN_glXSwapBuffers_PROC) glXGetProcAddressARB((const uint8_t *) "glXSwapBuffers");
    }

    glXCreateGLXPixmap_PROC = (PFN_glXCreateGLXPixmap_PROC) glXGetProcAddress((const uint8_t *) "glXCreateGLXPixmap");
    if (!glXCreateGLXPixmap_PROC) {
        glXCreateGLXPixmap_PROC = (PFN_glXCreateGLXPixmap_PROC) glXGetProcAddressARB((const uint8_t *) "glXCreateGLXPixmap");
    }

    glXDestroyGLXPixmap_PROC = (PFN_glXDestroyGLXPixmap_PROC) glXGetProcAddress((const uint8_t *) "glXDestroyGLXPixmap");
    if (!glXDestroyGLXPixmap_PROC) {
        glXDestroyGLXPixmap_PROC = (PFN_glXDestroyGLXPixmap_PROC) glXGetProcAddressARB((const uint8_t *) "glXDestroyGLXPixmap");
    }

    glXQueryExtension_PROC = (PFN_glXQueryExtension_PROC) glXGetProcAddress((const uint8_t *) "glXQueryExtension");
    if (!glXQueryExtension_PROC) {
        glXQueryExtension_PROC = (PFN_glXQueryExtension_PROC) glXGetProcAddressARB((const uint8_t *) "glXQueryExtension");
    }

    glXQueryVersion_PROC = (PFN_glXQueryVersion_PROC) glXGetProcAddress((const uint8_t *) "glXQueryVersion");
    if (!glXQueryVersion_PROC) {
        glXQueryVersion_PROC = (PFN_glXQueryVersion_PROC) glXGetProcAddressARB((const uint8_t *) "glXQueryVersion");
    }

    glXIsDirect_PROC = (PFN_glXIsDirect_PROC) glXGetProcAddress((const uint8_t *) "glXIsDirect");
    if (!glXIsDirect_PROC) {
        glXIsDirect_PROC = (PFN_glXIsDirect_PROC) glXGetProcAddressARB((const uint8_t *) "glXIsDirect");
    }

    glXGetConfig_PROC = (PFN_glXGetConfig_PROC) glXGetProcAddress((const uint8_t *) "glXGetConfig");
    if (!glXGetConfig_PROC) {
        glXGetConfig_PROC = (PFN_glXGetConfig_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetConfig");
    }

    glXGetCurrentContext_PROC = (PFN_glXGetCurrentContext_PROC) glXGetProcAddress((const uint8_t *) "glXGetCurrentContext");
    if (!glXGetCurrentContext_PROC) {
        glXGetCurrentContext_PROC = (PFN_glXGetCurrentContext_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetCurrentContext");
    }

    glXGetCurrentDrawable_PROC = (PFN_glXGetCurrentDrawable_PROC) glXGetProcAddress((const uint8_t *) "glXGetCurrentDrawable");
    if (!glXGetCurrentDrawable_PROC) {
        glXGetCurrentDrawable_PROC = (PFN_glXGetCurrentDrawable_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetCurrentDrawable");
    }

    glXWaitGL_PROC = (PFN_glXWaitGL_PROC) glXGetProcAddress((const uint8_t *) "glXWaitGL");
    if (!glXWaitGL_PROC) {
        glXWaitGL_PROC = (PFN_glXWaitGL_PROC) glXGetProcAddressARB((const uint8_t *) "glXWaitGL");
    }

    glXWaitX_PROC = (PFN_glXWaitX_PROC) glXGetProcAddress((const uint8_t *) "glXWaitX");
    if (!glXWaitX_PROC) {
        glXWaitX_PROC = (PFN_glXWaitX_PROC) glXGetProcAddressARB((const uint8_t *) "glXWaitX");
    }

    glXUseXFont_PROC = (PFN_glXUseXFont_PROC) glXGetProcAddress((const uint8_t *) "glXUseXFont");
    if (!glXUseXFont_PROC) {
        glXUseXFont_PROC = (PFN_glXUseXFont_PROC) glXGetProcAddressARB((const uint8_t *) "glXUseXFont");
    }

    glXQueryExtensionsString_PROC = (PFN_glXQueryExtensionsString_PROC) glXGetProcAddress((const uint8_t *) "glXQueryExtensionsString");
    if (!glXQueryExtensionsString_PROC) {
        glXQueryExtensionsString_PROC = (PFN_glXQueryExtensionsString_PROC) glXGetProcAddressARB((const uint8_t *) "glXQueryExtensionsString");
    }

    glXQueryServerString_PROC = (PFN_glXQueryServerString_PROC) glXGetProcAddress((const uint8_t *) "glXQueryServerString");
    if (!glXQueryServerString_PROC) {
        glXQueryServerString_PROC = (PFN_glXQueryServerString_PROC) glXGetProcAddressARB((const uint8_t *) "glXQueryServerString");
    }

    glXGetClientString_PROC = (PFN_glXGetClientString_PROC) glXGetProcAddress((const uint8_t *) "glXGetClientString");
    if (!glXGetClientString_PROC) {
        glXGetClientString_PROC = (PFN_glXGetClientString_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetClientString");
    }

    glXGetCurrentDisplay_PROC = (PFN_glXGetCurrentDisplay_PROC) glXGetProcAddress((const uint8_t *) "glXGetCurrentDisplay");
    if (!glXGetCurrentDisplay_PROC) {
        glXGetCurrentDisplay_PROC = (PFN_glXGetCurrentDisplay_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetCurrentDisplay");
    }

    glXChooseFBConfig_PROC = (PFN_glXChooseFBConfig_PROC) glXGetProcAddress((const uint8_t *) "glXChooseFBConfig");
    if (!glXChooseFBConfig_PROC) {
        glXChooseFBConfig_PROC = (PFN_glXChooseFBConfig_PROC) glXGetProcAddressARB((const uint8_t *) "glXChooseFBConfig");
    }

    glXGetFBConfigAttrib_PROC = (PFN_glXGetFBConfigAttrib_PROC) glXGetProcAddress((const uint8_t *) "glXGetFBConfigAttrib");
    if (!glXGetFBConfigAttrib_PROC) {
        glXGetFBConfigAttrib_PROC = (PFN_glXGetFBConfigAttrib_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetFBConfigAttrib");
    }

    glXGetFBConfigs_PROC = (PFN_glXGetFBConfigs_PROC) glXGetProcAddress((const uint8_t *) "glXGetFBConfigs");
    if (!glXGetFBConfigs_PROC) {
        glXGetFBConfigs_PROC = (PFN_glXGetFBConfigs_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetFBConfigs");
    }

    glXGetVisualFromFBConfig_PROC = (PFN_glXGetVisualFromFBConfig_PROC) glXGetProcAddress((const uint8_t *) "glXGetVisualFromFBConfig");
    if (!glXGetVisualFromFBConfig_PROC) {
        glXGetVisualFromFBConfig_PROC = (PFN_glXGetVisualFromFBConfig_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetVisualFromFBConfig");
    }

    glXCreateWindow_PROC = (PFN_glXCreateWindow_PROC) glXGetProcAddress((const uint8_t *) "glXCreateWindow");
    if (!glXCreateWindow_PROC) {
        glXCreateWindow_PROC = (PFN_glXCreateWindow_PROC) glXGetProcAddressARB((const uint8_t *) "glXCreateWindow");
    }

    glXDestroyWindow_PROC = (PFN_glXDestroyWindow_PROC) glXGetProcAddress((const uint8_t *) "glXDestroyWindow");
    if (!glXDestroyWindow_PROC) {
        glXDestroyWindow_PROC = (PFN_glXDestroyWindow_PROC) glXGetProcAddressARB((const uint8_t *) "glXDestroyWindow");
    }

    glXCreatePixmap_PROC = (PFN_glXCreatePixmap_PROC) glXGetProcAddress((const uint8_t *) "glXCreatePixmap");
    if (!glXCreatePixmap_PROC) {
        glXCreatePixmap_PROC = (PFN_glXCreatePixmap_PROC) glXGetProcAddressARB((const uint8_t *) "glXCreatePixmap");
    }

    glXDestroyPixmap_PROC = (PFN_glXDestroyPixmap_PROC) glXGetProcAddress((const uint8_t *) "glXDestroyPixmap");
    if (!glXDestroyPixmap_PROC) {
        glXDestroyPixmap_PROC = (PFN_glXDestroyPixmap_PROC) glXGetProcAddressARB((const uint8_t *) "glXDestroyPixmap");
    }

    glXCreatePbuffer_PROC = (PFN_glXCreatePbuffer_PROC) glXGetProcAddress((const uint8_t *) "glXCreatePbuffer");
    if (!glXCreatePbuffer_PROC) {
        glXCreatePbuffer_PROC = (PFN_glXCreatePbuffer_PROC) glXGetProcAddressARB((const uint8_t *) "glXCreatePbuffer");
    }

    glXDestroyPbuffer_PROC = (PFN_glXDestroyPbuffer_PROC) glXGetProcAddress((const uint8_t *) "glXDestroyPbuffer");
    if (!glXDestroyPbuffer_PROC) {
        glXDestroyPbuffer_PROC = (PFN_glXDestroyPbuffer_PROC) glXGetProcAddressARB((const uint8_t *) "glXDestroyPbuffer");
    }

    glXQueryDrawable_PROC = (PFN_glXQueryDrawable_PROC) glXGetProcAddress((const uint8_t *) "glXQueryDrawable");
    if (!glXQueryDrawable_PROC) {
        glXQueryDrawable_PROC = (PFN_glXQueryDrawable_PROC) glXGetProcAddressARB((const uint8_t *) "glXQueryDrawable");
    }

    glXCreateNewContext_PROC = (PFN_glXCreateNewContext_PROC) glXGetProcAddress((const uint8_t *) "glXCreateNewContext");
    if (!glXCreateNewContext_PROC) {
        glXCreateNewContext_PROC = (PFN_glXCreateNewContext_PROC) glXGetProcAddressARB((const uint8_t *) "glXCreateNewContext");
    }

    glXMakeContextCurrent_PROC = (PFN_glXMakeContextCurrent_PROC) glXGetProcAddress((const uint8_t *) "glXMakeContextCurrent");
    if (!glXMakeContextCurrent_PROC) {
        glXMakeContextCurrent_PROC = (PFN_glXMakeContextCurrent_PROC) glXGetProcAddressARB((const uint8_t *) "glXMakeContextCurrent");
    }

    glXGetCurrentReadDrawable_PROC = (PFN_glXGetCurrentReadDrawable_PROC) glXGetProcAddress((const uint8_t *) "glXGetCurrentReadDrawable");
    if (!glXGetCurrentReadDrawable_PROC) {
        glXGetCurrentReadDrawable_PROC = (PFN_glXGetCurrentReadDrawable_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetCurrentReadDrawable");
    }

    glXQueryContext_PROC = (PFN_glXQueryContext_PROC) glXGetProcAddress((const uint8_t *) "glXQueryContext");
    if (!glXQueryContext_PROC) {
        glXQueryContext_PROC = (PFN_glXQueryContext_PROC) glXGetProcAddressARB((const uint8_t *) "glXQueryContext");
    }

    glXSelectEvent_PROC = (PFN_glXSelectEvent_PROC) glXGetProcAddress((const uint8_t *) "glXSelectEvent");
    if (!glXSelectEvent_PROC) {
        glXSelectEvent_PROC = (PFN_glXSelectEvent_PROC) glXGetProcAddressARB((const uint8_t *) "glXSelectEvent");
    }

    glXGetSelectedEvent_PROC = (PFN_glXGetSelectedEvent_PROC) glXGetProcAddress((const uint8_t *) "glXGetSelectedEvent");
    if (!glXGetSelectedEvent_PROC) {
        glXGetSelectedEvent_PROC = (PFN_glXGetSelectedEvent_PROC) glXGetProcAddressARB((const uint8_t *) "glXGetSelectedEvent");
    }

    glXCreateContextAttribsARB_PROC = (PFN_glXCreateContextAttribsARB_PROC) glXGetProcAddress((const uint8_t *) "glXCreateContextAttribsARB");
    if (!glXCreateContextAttribsARB_PROC) {
        glXCreateContextAttribsARB_PROC = (PFN_glXCreateContextAttribsARB_PROC) glXGetProcAddressARB((const uint8_t *) "glXCreateContextAttribsARB");
    }

    glXSwapIntervalEXT_PROC = (PFN_glXSwapIntervalEXT_PROC) glXGetProcAddress((const uint8_t *) "glXSwapIntervalEXT");
    if (!glXSwapIntervalEXT_PROC) {
        glXSwapIntervalEXT_PROC = (PFN_glXSwapIntervalEXT_PROC) glXGetProcAddressARB((const uint8_t *) "glXSwapIntervalEXT");
    }
    /* }}} */
    glx->handle = libglx;

    /* return the result */
    lib->glx = glx;

    /* success */
    return (1);
}


WININT int __win_glx_unload(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    struct _window_h_glx *glx = lib->glx;
    if (!glx) { return (0); }

    /* release 'glx->attr' members */
    if (glx->attr.config)  { free(glx->attr.config),  glx->attr.config = 0;  }
    if (glx->attr.context) { free(glx->attr.context), glx->attr.context = 0; }

    /* release GLX modules */
    dlclose(glx->handle), glx->handle = 0;

    /* release 'glx' */
    free(glx);

    /* success */
    return (1);
}


WININT int __win_glx_create_context(struct _window_h *lib, struct _window_h_context *ctx, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }
    
    /* alloc new 'glx' object */
    struct _window_h_context_glx *glx = calloc(1, sizeof(struct _window_h_context_glx));
    if (!glx) { return (0); }

    /* set 'glx' members */
    if (glXCreateWindow_PROC) {
        glx->window = glXCreateWindow(lib->glx->dpy,
                                      lib->glx->fbconfig,
                                      win->handle, 0);
        if (!glx->window) {
            free(glx);
            return (0);
        }

    } else {
        /* if 'glXCreateDrawable' is not available... */
        glx->window = (GLXDrawable) win->handle;
    }

    /* modern context query */
    if (glXCreateContextAttribsARB_PROC) {
        /* get GLXContext object */
        glx->context = glXCreateContextAttribsARB(lib->glx->dpy,
                                                  lib->glx->fbconfig,
                                                  0, 1,
                                                  lib->glx->attr.context);
    /* legacy context query */
    } else {
        /* get 'XVisualInfo' from 'GLXFBConfig' */
        XVisualInfo *vi = glXGetVisualFromFBConfig(lib->glx->dpy,
                                                   lib->glx->fbconfig);
        if (!vi) { free(glx); return (0); }

        /* get GLXContext object */
        glx->context = glXCreateContext(lib->glx->dpy, vi, 0, 1);

        /* release 'vi' */
        XFree(vi), vi = 0;
    }

    /* check if context failed to create */
    if (!glx->context) {
        free(glx);
        return (0);
    }

    /* return 'glx' object */
    ctx->glx = glx;

    /* success */
    return (1);
}


WININT int __win_glx_context_destroy(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }

    /* release 'context' */
    glXDestroyContext(lib->glx->dpy,
                      ctx->glx->context);
    
    /* release 'drawawble' */
    glXDestroyWindow(lib->glx->dpy,
                     ctx->glx->window);

    /* release 'glx' */
    free(ctx->glx);

    /* success */
    return (1);
}


WININT int __win_glx_make_current(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    
    /* references */
    struct _window_h_context_glx *glx = (struct _window_h_context_glx *) ctx->glx;
    if (!glx) { return (0); }

    /* set context.handle */
    if (!glXMakeCurrent(lib->glx->dpy,
                        glx->window,
                        glx->context)
    ) {
        return (0);
    }

    /* success */
    return (1);
}


WININT int __win_glx_swap_buffers(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
   
    /* references */
    struct _window_h_context_glx *glx = (struct _window_h_context_glx *) ctx->glx;
    if (!glx) { return (0); }
    
    /* check if "double-buffering" is enabled */
    int glx_doublebuffer = 0;
    glXGetFBConfigAttrib(lib->glx->dpy, lib->glx->fbconfig, GLX_DOUBLEBUFFER, &glx_doublebuffer);
    if (!glx_doublebuffer) {
        return (0);
    }

    /* swap buffers */
    glXSwapBuffers(lib->glx->dpy, glx->window);

    /* success */
    return (1);
}


WININT int __win_glx_swap_interval(struct _window_h *lib, struct _window_h_context *ctx, const int interval) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    
    /* references */
    struct _window_h_context_glx *glx = (struct _window_h_context_glx *) ctx->glx;
    if (!glx) { return (0); }

    /* set swap intervals */
    glXSwapIntervalEXT(lib->glx->dpy, glx->window, interval);

    /* success */
    return (1);
}


WININT void *__win_glx_get_proc_address(struct _window_h *lib, const char *proc) {
    /* null-check */
    if (!lib)  { return (0); }
    if (!proc) { return (0); }
    
    /* success */
    return (glXGetProcAddress((const uint8_t *) proc));
}


WININT int __win_glx_choose_config(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    if (lib->glx->fbconfig) { return (1); }

    /* get 'screen' */
    int screen = DefaultScreen(lib->glx->dpy);
    
    /* get the 'fbconfigs' array */
    int nelements = 0;
    GLXFBConfig *fbconfigs = glXChooseFBConfig(lib->glx->dpy, screen, lib->glx->attr.config, &nelements);
    if (!fbconfigs) { return (0); }
    if (!nelements) { return (0); }

    /* iterate over the 'fbconfigs' list to find the best matching */
    ssize_t fbconfig_best = -1;
    for (size_t i = 0; fbconfig_best == -1 || i < (size_t) nelements; i++) {
        /* check if we can create an 'XVisualInfo' from the current config */
        int glx_visual_id = 0;
        glXGetFBConfigAttrib(lib->glx->dpy, fbconfigs[i], GLX_VISUAL_ID, &glx_visual_id);
        if (!glx_visual_id) { continue; }

        /* get 'GLX_DRAWABLE_TYPE': reject if no 'GLX_WINDOW_BIT' bit set */
        int glx_drawable_type = 0;
        glXGetFBConfigAttrib(lib->glx->dpy, fbconfigs[i], GLX_DRAWABLE_TYPE, &glx_drawable_type);
        if (!(glx_drawable_type & GLX_WINDOW_BIT)) { continue; }
        
        /* set the current 'fbconfig_best' to 'i' */
        fbconfig_best = i;
    }

    /* check if we have any matching */
    if (fbconfig_best == -1) {
        free(fbconfigs);
        return (0);
    }

    /* store the 'fbconfig' in the 'glx' */
    lib->glx->fbconfig = fbconfigs[fbconfig_best];

    /* release 'fbconfigs' */
    free(fbconfigs);

    /* success */
    return (1);
}


WININT int __win_glx_get_visual(struct _window_h *lib, int *v_ptr) {
    /* null-check */
    if (!lib) { return (0); }

    /* check for 'fbconfig' */
    if (!lib->glx->fbconfig) {
        /* first time running: cache the new 'fbconfig' */
        if (!__win_glx_choose_config(lib)) { return (0); }
    }
        
    /* get the value of 'GLX_VISUAL_ID' */
    int glx_visual_id = 0;
    glXGetFBConfigAttrib(lib->glx->dpy,
                         lib->glx->fbconfig,
                         GLX_VISUAL_ID, &glx_visual_id);
    if (!glx_visual_id) { return (0); }

    /* return the result */
    if (v_ptr) { *v_ptr = glx_visual_id; }

    /* success */
    return (1);
}

/* }}} */
# endif /* WINDOW_BACKEND_GLX */
#
# /* WINDOW_BACKEND_EGL - EGL implementation layer */
# if defined (WINDOW_BACKEND_EGL)
/* {{{ */

static const struct _window_h_egl_attrmap {
    uint32_t src;
    uint32_t dst;
} _window_h_egl_attrmap[] = {
    
/* {{{ */
    
    { EGL_CONTEXT_MAJOR_VERSION, WINDOW_GL_CONTEXT_VERSION_MAJOR },
    
    { EGL_CONTEXT_MINOR_VERSION, WINDOW_GL_CONTEXT_VERSION_MINOR },
    
    { EGL_CONTEXT_OPENGL_PROFILE_MASK, WINDOW_GL_CONTEXT_PROFILE },

    /* ... */

    { EGL_NONE, WINDOW_GL_NONE }

/* }}} */

};

/* internal functions (declarations) */

WININT int __win_egl_init(struct _window_h *, void *);

WININT int __win_egl_load(struct _window_h *);

WININT int __win_egl_unload(struct _window_h *);

WININT int __win_egl_create_context(struct _window_h *, struct _window_h_context *, struct _window_h_window *);

WININT int __win_egl_context_destroy(struct _window_h *, struct _window_h_context *);

WININT int __win_egl_make_current(struct _window_h *, struct _window_h_context *);

WININT int __win_egl_swap_buffers(struct _window_h *, struct _window_h_context *);

WININT int __win_egl_swap_interval(struct _window_h *, struct _window_h_context *, const int);

WININT void *__win_egl_get_proc_address(struct _window_h *, const char *);

WININT int __win_egl_choose_config(struct _window_h *);

WININT int __win_egl_get_visual(struct _window_h *, int *);

/* internal functions (definitions) */

WININT int __win_egl_init(struct _window_h *lib, void *display) {
    /* null-check */
    if (!lib) { return (0); }

    /* references */
    struct _window_h_egl *egl = lib->egl; 
    if (!egl) { return (0); }
    if (egl->dpy) { return (1); }

    /* set 'glx' members */
    egl->dpy = eglGetDisplay(display);
    if (egl->dpy == EGL_NO_DISPLAY) {
        return (0);
    }
    
    /* set 'egl->attr' members */
    int attr_config[] = {
        EGL_ALPHA_MASK_SIZE,            0,
        EGL_ALPHA_SIZE,                 lib->hints.gl.alpha,
        EGL_BIND_TO_TEXTURE_RGB,        EGL_DONT_CARE,
        EGL_BIND_TO_TEXTURE_RGBA,       EGL_DONT_CARE,
        EGL_BLUE_SIZE,                  lib->hints.gl.blue,
        EGL_BUFFER_SIZE,                0,
        EGL_COLOR_BUFFER_TYPE,          EGL_RGB_BUFFER,
        EGL_CONFIG_CAVEAT,              EGL_DONT_CARE,
        EGL_CONFIG_ID,                  EGL_DONT_CARE,
        EGL_CONFORMANT,                 0,
        EGL_DEPTH_SIZE,                 lib->hints.gl.depth,
        EGL_GREEN_SIZE,                 lib->hints.gl.green,
        EGL_LEVEL,                      0,
        EGL_LUMINANCE_SIZE,             0,
        EGL_MATCH_NATIVE_PIXMAP,        EGL_NONE,
        EGL_NATIVE_RENDERABLE,          EGL_DONT_CARE,
        EGL_MAX_SWAP_INTERVAL,          EGL_DONT_CARE,
        EGL_MIN_SWAP_INTERVAL,          EGL_DONT_CARE,
        EGL_RED_SIZE,                   lib->hints.gl.red,
        EGL_SAMPLE_BUFFERS,             0,
        EGL_SAMPLES,                    0,
        EGL_STENCIL_SIZE,               lib->hints.gl.stencil,
        EGL_RENDERABLE_TYPE,            EGL_OPENGL_BIT,
        EGL_SURFACE_TYPE,               EGL_WINDOW_BIT,
        EGL_TRANSPARENT_TYPE,           EGL_NONE,
        EGL_TRANSPARENT_RED_VALUE,      EGL_DONT_CARE,
        EGL_TRANSPARENT_GREEN_VALUE,    EGL_DONT_CARE,
        EGL_TRANSPARENT_BLUE_VALUE,     EGL_DONT_CARE,

        /* ... */

        EGL_NONE, EGL_NONE
    };

    egl->attr.config = calloc(64, sizeof(int));
    if (!egl->attr.config) { return (0); }
    if (!memcpy(egl->attr.config, attr_config, sizeof(attr_config))) { return (0); }


    int attr_surface[] = {
        EGL_GL_COLORSPACE,      EGL_GL_COLORSPACE_LINEAR,
        EGL_RENDER_BUFFER,      lib->hints.gl.dblbuf ? EGL_BACK_BUFFER :
                                                       EGL_SINGLE_BUFFER,
        EGL_VG_ALPHA_FORMAT,    EGL_VG_ALPHA_FORMAT_NONPRE,
        EGL_VG_COLORSPACE,      EGL_VG_COLORSPACE_sRGB,

        /* ... */

        EGL_NONE
    };

    egl->attr.surface = calloc(64, sizeof(int));
    if (!egl->attr.surface) { return (0); }
    if (!memcpy(egl->attr.surface, attr_surface, sizeof(attr_surface))) { return (0); }
    

    int attr_context[] = {
        EGL_CONTEXT_MAJOR_VERSION,          lib->hints.gl.major,
        EGL_CONTEXT_MINOR_VERSION,          lib->hints.gl.minor,
        EGL_CONTEXT_OPENGL_PROFILE_MASK,    lib->hints.gl.profile,

        /* ... */

        EGL_NONE, EGL_NONE
    };

    egl->attr.context = calloc(64, sizeof(int));
    if (!egl->attr.context) { return (0); }
    if (!memcpy(egl->attr.context, attr_context, sizeof(attr_context))) { return (0); }
    
    /* initialize EGL */
    if (!eglInitialize(egl->dpy, 0, 0)) { return (0); }
    if (!eglBindAPI(EGL_OPENGL_API)) { return (0); }

    /* success */
    return (1);
}


WININT int __win_egl_load(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }
    if (lib->egl) { return (1); }

    /* init-check */
    struct _window_h_egl *egl = calloc(1, sizeof(struct _window_h_egl));
    if (!egl) { return (0); }

    void *libegl= 0;
    {
        const char  *names[] = { "libEGL.so", "libEGL.so.1, libEGL.so.1.1.0", 0 };
        for (const char **name = names; *name; name++) {
            libegl = dlopen(*name, RTLD_LAZY | RTLD_LOCAL);
            if (libegl) { break; }
        }

        /* check if libegl loaded */
        if (!libegl) { return (0); }
    }

    /* {{{ */
    /* load 'eglGetProcAddress'... */
    eglGetProcAddress_PROC = (PFN_eglGetProcAddress_PROC) dlsym(libegl, "eglGetProcAddress");

    /* ...and load the rest of the EGL using it! */
    eglBindAPI_PROC = (PFN_eglBindAPI_PROC) eglGetProcAddress("eglBindAPI");
    eglBindTexImage_PROC = (PFN_eglBindTexImage_PROC) eglGetProcAddress("eglBindTexImage");
    eglChooseConfig_PROC = (PFN_eglChooseConfig_PROC) eglGetProcAddress("eglChooseConfig");
    eglClientWaitSync_PROC = (PFN_eglClientWaitSync_PROC) eglGetProcAddress("eglClientWaitSync");
    eglCopyBuffers_PROC = (PFN_eglCopyBuffers_PROC) eglGetProcAddress("eglCopyBuffers");
    eglCreateContext_PROC = (PFN_eglCreateContext_PROC) eglGetProcAddress("eglCreateContext");
    eglCreateImage_PROC = (PFN_eglCreateImage_PROC) eglGetProcAddress("eglCreateImage");
    eglCreatePbufferFromClientBuffer_PROC = (PFN_eglCreatePbufferFromClientBuffer_PROC) eglGetProcAddress("eglCreatePbufferFromClientBuffer");
    eglCreatePbufferSurface_PROC = (PFN_eglCreatePbufferSurface_PROC) eglGetProcAddress("eglCreatePbufferSurface");
    eglCreatePixmapSurface_PROC = (PFN_eglCreatePixmapSurface_PROC) eglGetProcAddress("eglCreatePixmapSurface");
    eglCreatePlatformPixmapSurface_PROC = (PFN_eglCreatePlatformPixmapSurface_PROC) eglGetProcAddress("eglCreatePlatformPixmapSurface");
    eglCreatePlatformWindowSurface_PROC = (PFN_eglCreatePlatformWindowSurface_PROC) eglGetProcAddress("eglCreatePlatformWindowSurface");
    eglCreateSync_PROC = (PFN_eglCreateSync_PROC) eglGetProcAddress("eglCreateSync");
    eglCreateWindowSurface_PROC = (PFN_eglCreateWindowSurface_PROC) eglGetProcAddress("eglCreateWindowSurface");
    eglDestroyContext_PROC = (PFN_eglDestroyContext_PROC) eglGetProcAddress("eglDestroyContext");
    eglDestroyImage_PROC = (PFN_eglDestroyImage_PROC) eglGetProcAddress("eglDestroyImage");
    eglDestroySurface_PROC = (PFN_eglDestroySurface_PROC) eglGetProcAddress("eglDestroySurface");
    eglDestroySync_PROC = (PFN_eglDestroySync_PROC) eglGetProcAddress("eglDestroySync");
    eglGetConfigAttrib_PROC = (PFN_eglGetConfigAttrib_PROC) eglGetProcAddress("eglGetConfigAttrib");
    eglGetConfigs_PROC = (PFN_eglGetConfigs_PROC) eglGetProcAddress("eglGetConfigs");
    eglGetCurrentContext_PROC = (PFN_eglGetCurrentContext_PROC) eglGetProcAddress("eglGetCurrentContext");
    eglGetCurrentDisplay_PROC = (PFN_eglGetCurrentDisplay_PROC) eglGetProcAddress("eglGetCurrentDisplay");
    eglGetCurrentSurface_PROC = (PFN_eglGetCurrentSurface_PROC) eglGetProcAddress("eglGetCurrentSurface");
    eglGetDisplay_PROC = (PFN_eglGetDisplay_PROC) eglGetProcAddress("eglGetDisplay");
    eglGetError_PROC = (PFN_eglGetError_PROC) eglGetProcAddress("eglGetError");
    eglGetPlatformDisplay_PROC = (PFN_eglGetPlatformDisplay_PROC) eglGetProcAddress("eglGetPlatformDisplay");
    eglGetSyncAttrib_PROC = (PFN_eglGetSyncAttrib_PROC) eglGetProcAddress("eglGetSyncAttrib");
    eglInitialize_PROC = (PFN_eglInitialize_PROC) eglGetProcAddress("eglInitialize");
    eglMakeCurrent_PROC = (PFN_eglMakeCurrent_PROC) eglGetProcAddress("eglMakeCurrent");
    eglQueryAPI_PROC = (PFN_eglQueryAPI_PROC) eglGetProcAddress("eglQueryAPI");
    eglQueryContext_PROC = (PFN_eglQueryContext_PROC) eglGetProcAddress("eglQueryContext");
    eglQueryString_PROC = (PFN_eglQueryString_PROC) eglGetProcAddress("eglQueryString");
    eglQuerySurface_PROC = (PFN_eglQuerySurface_PROC) eglGetProcAddress("eglQuerySurface");
    eglReleaseTexImage_PROC = (PFN_eglReleaseTexImage_PROC) eglGetProcAddress("eglReleaseTexImage");
    eglReleaseThread_PROC = (PFN_eglReleaseThread_PROC) eglGetProcAddress("eglReleaseThread");
    eglSurfaceAttrib_PROC = (PFN_eglSurfaceAttrib_PROC) eglGetProcAddress("eglSurfaceAttrib");
    eglSwapBuffers_PROC = (PFN_eglSwapBuffers_PROC) eglGetProcAddress("eglSwapBuffers");
    eglSwapInterval_PROC = (PFN_eglSwapInterval_PROC) eglGetProcAddress("eglSwapInterval");
    eglTerminate_PROC = (PFN_eglTerminate_PROC) eglGetProcAddress("eglTerminate");
    eglWaitClient_PROC = (PFN_eglWaitClient_PROC) eglGetProcAddress("eglWaitClient");
    eglWaitGL_PROC = (PFN_eglWaitGL_PROC) eglGetProcAddress("eglWaitGL");
    eglWaitNative_PROC = (PFN_eglWaitNative_PROC) eglGetProcAddress("eglWaitNative");
    eglWaitSync_PROC = (PFN_eglWaitSync_PROC) eglGetProcAddress("eglWaitSync");
    /* }}} */
    egl->handle = libegl;

    /* return the result */
    lib->egl = egl;

    /* success */
    return (1);
}


WININT int __win_egl_unload(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    struct _window_h_egl *egl = lib->egl;
    if (!egl) { return (0); }

    eglTerminate(egl->dpy);

    /* release EGL modules */
    dlclose(egl->handle), egl->handle = 0;

    /* release 'egl' */
    free(egl);

    /* success */
    return (1);
}


WININT int __win_egl_create_context(struct _window_h *lib, struct _window_h_context *ctx, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }

    /* alloc new 'egl' object */
    struct _window_h_context_egl *egl = calloc(1, sizeof(struct _window_h_context_egl));
    if (!egl) { return (0); }
    
    /* get EGLConfig object */
    int num_configs  = 0;
    EGLConfig config = 0;
    if (!eglChooseConfig(lib->egl->dpy,
                         lib->egl->attr.config,
                         &config,
                         1, &num_configs)
    ) {
        free(egl);
        return (0);
    }

    /* get EGLSurface object */
    egl->surface = eglCreateWindowSurface(lib->egl->dpy, config,
                                          win->handle,
                                          lib->egl->attr.surface);
    if (egl->surface == EGL_NO_SURFACE) {
        free(egl);
        return (0);
    }

    /* get EGLContext object */
    egl->context = eglCreateContext(lib->egl->dpy, config,
                                    EGL_NO_CONTEXT,
                                    lib->egl->attr.context);
    if (egl->context == EGL_NO_CONTEXT) {
        eglDestroySurface(lib->egl->dpy, ctx->egl->surface);
        free(egl);
        return (0);
    }

    /* return 'egl' object */
    ctx->egl = egl;

    /* success */
    return (1);
}


WININT int __win_egl_context_destroy(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
            
    /* release 'context' */
    eglDestroyContext(lib->egl->dpy,
                      ctx->egl->context);

    /* release 'surface' */
    eglDestroySurface(lib->egl->dpy,
                      ctx->egl->surface);

    /* release 'egl' */
    free(ctx->egl);

    /* success */
    return (1);
}


WININT int __win_egl_make_current(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    
    /* references */
    struct _window_h_context_egl *egl = (struct _window_h_context_egl *) ctx->egl;
    if (!egl) { return (0); }

    /* set context.handle */
    if (!eglMakeCurrent(lib->egl->dpy,
                        egl->surface,
                        egl->surface,
                        egl->context)
    ) {
        return (0);
    }

    /* success */
    return (1);
}


WININT int __win_egl_swap_buffers(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
   
    /* references */
    struct _window_h_context_egl *egl = (struct _window_h_context_egl *) ctx->egl;
    if (!egl) { return (0); }

    /* check if "double-buffering" is enabled */
    int egl_render_buffer = 0;
    eglQueryContext(lib->egl->dpy, egl->context, EGL_RENDER_BUFFER, &egl_render_buffer);
    if (egl_render_buffer == EGL_SINGLE_BUFFER) {
        return (0);
    }

    /* swap buffers */
    if (!eglSwapBuffers(lib->egl->dpy, egl->surface)) {
        return (0);
    }

    /* success */
    return (1);
}


WININT int __win_egl_swap_interval(struct _window_h *lib, struct _window_h_context *ctx, const int interval) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    
    /* references */
    struct _window_h_context_egl *egl = (struct _window_h_context_egl *) ctx->egl;
    if (!egl) { return (0); }

    /* set swap intervals */
    if (!eglSwapInterval(lib->egl->dpy, interval)) {
        return (0);
    }

    /* success */
    return (1);
}


WININT void *__win_egl_get_proc_address(struct _window_h *lib, const char *proc) {
    /* null-check */
    if (!lib)  { return (0); }
    if (!proc) { return (0); }
    
    /* success */
    return (eglGetProcAddress(proc));
}


WININT int __win_egl_choose_config(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    if (lib->egl->config) { return (1); }
    
    /* get EGLConfig array size */
    int num_config = 0;
    if (!eglChooseConfig(lib->egl->dpy, lib->egl->attr.config, 0, 1, &num_config)) { return (0); }
    if (!num_config) { return (0); }

    /* get EGLConfig array */
    EGLConfig *configs = malloc(num_config * sizeof(EGLConfig));
    if (!eglChooseConfig(lib->egl->dpy, lib->egl->attr.config, configs, num_config, &num_config)) { return (0); }
    if (!configs) { return (0); }

    /* iterate over the 'configs' list to find the best matching */
    int config_best = -1;
    for (size_t i = 0; config_best == -1 || i < (size_t) num_config; i++) {
        /* check if we can create an 'XVisualInfo' from the current config */
        int egl_native_visual_id = 0;
        eglGetConfigAttrib(lib->egl->dpy, configs[i], EGL_NATIVE_VISUAL_ID, &egl_native_visual_id);
        if (!egl_native_visual_id) { continue; }
        
        /* get 'EGL_SURFACE_TYPE': reject if no 'EGL_WINDOW_BIT' bit set */
        int egl_surface_type = 0;
        eglGetConfigAttrib(lib->egl->dpy, configs[i], EGL_SURFACE_TYPE, &egl_surface_type);
        if (!(egl_surface_type & EGL_WINDOW_BIT)) { continue; }

        /* set the current 'config_best' to 'i' */
        config_best = i;
    }

    /* check if we have any matching */
    if (config_best == -1) { 
        free(configs);
        return (0);
    }

    /* store the 'config' in the 'egl' */
    lib->egl->config = configs[config_best];

    /* release 'configs' */
    free(configs);

    /* success */
    return (1);
}


WININT int __win_egl_get_visual(struct _window_h *lib, int *v_ptr) {
    /* null-check */
    if (!lib) { return (0); }

    /* check for 'config' */
    if (!lib->egl->config) {
        /* first time running: cache the new 'fbconfig' */
        if (!__win_egl_choose_config(lib)) { return (0); }
    }
        
    /* get the value of 'EGL_NATIVE_VISUAL_ID' */
    int egl_native_visual_id = 0;
    eglGetConfigAttrib(lib->egl->dpy,
                       lib->egl->config,
                       EGL_NATIVE_VISUAL_ID, &egl_native_visual_id);
    if (!egl_native_visual_id) { return (0); }

    /* return the result */
    if (v_ptr) { *v_ptr = egl_native_visual_id; }

    /* success */
    return (1);
}

/* }}} */
# endif /* WINDOW_BACKEND_EGL */
#
# /* WINDOW_BACKEND_WGL - WGL implementation layer */
# if defined (WINDOW_BACKEND_WGL)
/* {{{ */

/* internal functions (declarations) */

WININT int __win_wgl_init(struct _window_h *, void *);

WININT int __win_wgl_load(struct _window_h *);

WININT int __win_wgl_unload(struct _window_h *);

/* internal functions (definitions) */

WININT int __win_wgl_init(struct _window_h *lib, void *display) {
    /* null-check */
    if (!lib) { return (0); }

    /* references */
    struct _window_h_wgl *wgl = lib->wgl; 
    if (!wgl) { return (0); }

    (void) display;

    /* success */
    return (1);
}


WININT int __win_wgl_load(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }
    if (lib->wgl) { return (1); }

    /* init-check */
    struct _window_h_wgl *wgl = calloc(1, sizeof(struct _window_h_wgl));
    if (!wgl) { return (0); }

    /* return the result */
    lib->wgl = wgl;

    /* success */
    return (1);
}


WININT int __win_wgl_unload(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    struct _window_h_wgl *wgl = lib->wgl;
    if (!wgl) { return (0); }

    /* release 'wgl' */
    free(wgl);

    /* success */
    return (1);
}

/* }}} */
# endif /* WINDOW_BACKEND_WGL */
#
# /* WINDOW_BACKEND_X11 - X11 implementation layer */
# if defined (WINDOW_BACKEND_X11)
/* {{{ */

/* keymap layouts base */
struct _window_h_keymap {
    uint32_t src;
    uint32_t kc;
    uint32_t ks;
};

/*
 *  en-US QWERTY layout:
 *      https://en.wikipedia.org/wiki/QWERTY
 *
 * * * * * * * * * * * * * * * * * * * * * * */
static const struct _window_h_keymap _window_h_keymap_en_us_qwerty[] = {

/* {{{ */

    /* '`' / '~' */ 
    { XK_grave, WINDOW_KEYCODE_GRAVE, WINDOW_KEYSYM_GRAVE },
    { XK_asciitilde, WINDOW_KEYCODE_GRAVE, WINDOW_KEYSYM_TILDE },

    /* '1' / '!' */
    { XK_1, WINDOW_KEYCODE_1, WINDOW_KEYSYM_1 },
    { XK_exclam, WINDOW_KEYCODE_1, WINDOW_KEYSYM_EXCLAIM },

    /* '2' / '@' */
    { XK_2, WINDOW_KEYCODE_2, WINDOW_KEYSYM_2 },
    { XK_at, WINDOW_KEYCODE_2, WINDOW_KEYSYM_AT },

    /* '3' / '#' */
    { XK_3, WINDOW_KEYCODE_3, WINDOW_KEYSYM_3 },
    { XK_numbersign, WINDOW_KEYCODE_3, WINDOW_KEYSYM_HASH },

    /* '4' / '$' */
    { XK_4, WINDOW_KEYCODE_4, WINDOW_KEYSYM_4 },
    { XK_dollar, WINDOW_KEYCODE_5, WINDOW_KEYSYM_DOLLAR },

    /* '5' / '%' */
    { XK_5, WINDOW_KEYCODE_5, WINDOW_KEYSYM_5 },
    { XK_percent, WINDOW_KEYCODE_5, WINDOW_KEYSYM_PERCENT },

    /* '6' / '^' */
    { XK_6, WINDOW_KEYCODE_6, WINDOW_KEYSYM_6 },
    { XK_asciicircum, WINDOW_KEYCODE_6, WINDOW_KEYSYM_CARET },

    /* '7' / '&' */
    { XK_7, WINDOW_KEYCODE_7, WINDOW_KEYSYM_7 },
    { XK_ampersand, WINDOW_KEYCODE_7, WINDOW_KEYSYM_AMPERSAND },

    /* '8' / '*' */
    { XK_8, WINDOW_KEYCODE_8, WINDOW_KEYSYM_8 },
    { XK_asterisk, WINDOW_KEYCODE_8, WINDOW_KEYSYM_ASTERISK },

    /* '9' / '(' */
    { XK_9, WINDOW_KEYCODE_9, WINDOW_KEYSYM_9 },
    { XK_parenleft, WINDOW_KEYCODE_9, WINDOW_KEYSYM_OPENPAREN },

    /* '0' / ')' */
    { XK_0, WINDOW_KEYCODE_0, WINDOW_KEYSYM_0 },
    { XK_parenright, WINDOW_KEYCODE_0, WINDOW_KEYSYM_CLOSEPAREN },

    /* '-' / '_' */
    { XK_minus, WINDOW_KEYCODE_MINUS, WINDOW_KEYSYM_MINUS },
    { XK_underscore, WINDOW_KEYCODE_MINUS, WINDOW_KEYSYM_UNDERSCORE },

    /* '=' / '+' */
    { XK_equal, WINDOW_KEYCODE_EQUAL, WINDOW_KEYSYM_EQUAL },
    { XK_plus, WINDOW_KEYCODE_EQUAL, WINDOW_KEYSYM_PLUS },

    /* '\b' */
    { XK_BackSpace, WINDOW_KEYCODE_BACKSPACE, WINDOW_KEYSYM_BACKSPACE },

    /* '\t' */ 
    { XK_Tab, WINDOW_KEYCODE_TAB, WINDOW_KEYSYM_TAB },

    /* 'Q' / 'q' */
    { XK_Q, WINDOW_KEYCODE_Q, WINDOW_KEYSYM_Q },
    { XK_q, WINDOW_KEYCODE_Q, WINDOW_KEYSYM_LOWER_Q },

    /* 'W' / 'w' */
    { XK_W, WINDOW_KEYCODE_W, WINDOW_KEYSYM_W },
    { XK_w, WINDOW_KEYCODE_W, WINDOW_KEYSYM_LOWER_W },

    /* 'E' / 'e' */
    { XK_E, WINDOW_KEYCODE_E, WINDOW_KEYSYM_E },
    { XK_e, WINDOW_KEYCODE_E, WINDOW_KEYSYM_LOWER_E },

    /* 'R' / 'r' */
    { XK_R, WINDOW_KEYCODE_R, WINDOW_KEYSYM_R },
    { XK_r, WINDOW_KEYCODE_R, WINDOW_KEYSYM_LOWER_R },

    /* 'T' / 't' */
    { XK_T, WINDOW_KEYCODE_T, WINDOW_KEYSYM_T },
    { XK_t, WINDOW_KEYCODE_T, WINDOW_KEYSYM_LOWER_T },

    /* 'Y' / 'y' */
    { XK_Y, WINDOW_KEYCODE_Y, WINDOW_KEYSYM_Y },
    { XK_y, WINDOW_KEYCODE_Y, WINDOW_KEYSYM_LOWER_Y },

    /* 'U' / 'u' */
    { XK_U, WINDOW_KEYCODE_U, WINDOW_KEYSYM_U },
    { XK_u, WINDOW_KEYCODE_U, WINDOW_KEYSYM_LOWER_U },

    /* 'I' / 'i' */
    { XK_I, WINDOW_KEYCODE_I, WINDOW_KEYSYM_I },
    { XK_i, WINDOW_KEYCODE_I, WINDOW_KEYSYM_LOWER_I },

    /* 'O' / 'o' */
    { XK_O, WINDOW_KEYCODE_O, WINDOW_KEYSYM_O },
    { XK_o, WINDOW_KEYCODE_O, WINDOW_KEYSYM_LOWER_O },

    /* 'P' / 'p' */
    { XK_P, WINDOW_KEYCODE_P, WINDOW_KEYSYM_P },
    { XK_p, WINDOW_KEYCODE_P, WINDOW_KEYSYM_LOWER_P },

    /* '[' / '{' */
    { XK_bracketleft, WINDOW_KEYCODE_OPENBRACKET, WINDOW_KEYSYM_OPENBRACKET },
    { XK_braceleft, WINDOW_KEYCODE_OPENBRACKET, WINDOW_KEYSYM_OPENCURLY },

    /* ']' / '}' */
    { XK_bracketright, WINDOW_KEYCODE_CLOSEBRACKET, WINDOW_KEYSYM_CLOSEBRACKET },
    { XK_braceright, WINDOW_KEYCODE_CLOSEBRACKET, WINDOW_KEYSYM_CLOSECURLY },

    /* '\' / '|' */
    { XK_backslash, WINDOW_KEYCODE_BACKSLASH, WINDOW_KEYSYM_BACKSLASH },
    { XK_bar, WINDOW_KEYCODE_BACKSLASH, WINDOW_KEYSYM_PIPE },

    /* Caps-Lock */ 
    { XK_Caps_Lock, WINDOW_KEYCODE_CAPSLOCK, WINDOW_KEYSYM_CAPSLOCK },

    /* 'A' / 'a' */
    { XK_A, WINDOW_KEYCODE_A, WINDOW_KEYSYM_A },
    { XK_a, WINDOW_KEYCODE_A, WINDOW_KEYSYM_LOWER_A },

    /* 'S' / 's' */
    { XK_S, WINDOW_KEYCODE_S, WINDOW_KEYSYM_S },
    { XK_s, WINDOW_KEYCODE_S, WINDOW_KEYSYM_LOWER_S },

    /* 'D' / 'd' */
    { XK_D, WINDOW_KEYCODE_D, WINDOW_KEYSYM_D },
    { XK_d, WINDOW_KEYCODE_D, WINDOW_KEYSYM_LOWER_D },

    /* 'F' / 'f' */
    { XK_F, WINDOW_KEYCODE_F, WINDOW_KEYSYM_F },
    { XK_f, WINDOW_KEYCODE_F, WINDOW_KEYSYM_LOWER_F },

    /* 'G' / 'g' */
    { XK_G, WINDOW_KEYCODE_G, WINDOW_KEYSYM_G },
    { XK_g, WINDOW_KEYCODE_G, WINDOW_KEYSYM_LOWER_G },

    /* 'H' / 'h' */
    { XK_H, WINDOW_KEYCODE_H, WINDOW_KEYSYM_H },
    { XK_h, WINDOW_KEYCODE_H, WINDOW_KEYSYM_LOWER_H },

    /* 'J' / 'j' */
    { XK_J, WINDOW_KEYCODE_J, WINDOW_KEYSYM_J },
    { XK_j, WINDOW_KEYCODE_J, WINDOW_KEYSYM_LOWER_J },

    /* 'K' / 'k' */
    { XK_K, WINDOW_KEYCODE_K, WINDOW_KEYSYM_K },
    { XK_k, WINDOW_KEYCODE_K, WINDOW_KEYSYM_LOWER_K },

    /* 'L' / 'l' */
    { XK_L, WINDOW_KEYCODE_L, WINDOW_KEYSYM_L },
    { XK_l, WINDOW_KEYCODE_L, WINDOW_KEYSYM_LOWER_L },

    /* ';' / ':' */
    { XK_semicolon, WINDOW_KEYCODE_SEMICOLON, WINDOW_KEYSYM_SEMICOLON },
    { XK_colon, WINDOW_KEYCODE_SEMICOLON, WINDOW_KEYSYM_COLON },

    /* '\'' / '\"' */
    { XK_apostrophe, WINDOW_KEYCODE_QUOTE, WINDOW_KEYSYM_QUOTE },
    { XK_quotedbl, WINDOW_KEYCODE_QUOTE, WINDOW_KEYSYM_DOUBLEQUOTE },

    /* '\r' */
    { XK_Return, WINDOW_KEYCODE_RETURN, WINDOW_KEYSYM_RETURN },

    /* Left Shift*/ 
    { XK_Shift_L, WINDOW_KEYCODE_LEFTSHIFT, WINDOW_KEYSYM_LEFTSHIFT },

    /* 'Z' / 'z' */
    { XK_Z, WINDOW_KEYCODE_Z, WINDOW_KEYSYM_Z },
    { XK_z, WINDOW_KEYCODE_Z, WINDOW_KEYSYM_LOWER_Z },

    /* 'X' / 'x' */
    { XK_X, WINDOW_KEYCODE_X, WINDOW_KEYSYM_X },
    { XK_x, WINDOW_KEYCODE_X, WINDOW_KEYSYM_LOWER_X },

    /* 'C' / 'c' */
    { XK_C, WINDOW_KEYCODE_C, WINDOW_KEYSYM_C },
    { XK_c, WINDOW_KEYCODE_C, WINDOW_KEYSYM_LOWER_C },

    /* 'V' / 'v' */
    { XK_V, WINDOW_KEYCODE_V, WINDOW_KEYSYM_V },
    { XK_v, WINDOW_KEYCODE_V, WINDOW_KEYSYM_LOWER_V },

    /* 'B' / 'b' */
    { XK_B, WINDOW_KEYCODE_B, WINDOW_KEYSYM_B },
    { XK_b, WINDOW_KEYCODE_B, WINDOW_KEYSYM_LOWER_B },

    /* 'N' / 'n' */
    { XK_N, WINDOW_KEYCODE_N, WINDOW_KEYSYM_N },
    { XK_n, WINDOW_KEYCODE_N, WINDOW_KEYSYM_LOWER_N },

    /* 'M' / 'm' */
    { XK_M, WINDOW_KEYCODE_M, WINDOW_KEYSYM_M },
    { XK_m, WINDOW_KEYCODE_M, WINDOW_KEYSYM_LOWER_M },

    /* ',' / '<' */
    { XK_comma, WINDOW_KEYCODE_COMMA, WINDOW_KEYSYM_COMMA },
    { XK_less, WINDOW_KEYCODE_COMMA, WINDOW_KEYSYM_LESS },

    /* '.' / '>' */
    { XK_period, WINDOW_KEYCODE_PERIOD, WINDOW_KEYSYM_PERIOD },
    { XK_greater, WINDOW_KEYCODE_PERIOD, WINDOW_KEYSYM_GREATER },

    /* '/' / '?' */
    { XK_slash, WINDOW_KEYCODE_SLASH, WINDOW_KEYSYM_SLASH },
    { XK_question, WINDOW_KEYCODE_SLASH, WINDOW_KEYSYM_QUESTION },

    /* Right Shift */
    { XK_Shift_R, WINDOW_KEYCODE_RIGHTCTRL, WINDOW_KEYSYM_RIGHTCTRL },

    /* Left Control */
    { XK_Control_L, WINDOW_KEYCODE_LEFTCTRL, WINDOW_KEYSYM_LEFTCTRL },

    /* Left Home/GUI */
    { XK_Super_L, WINDOW_KEYCODE_LEFTGUI, WINDOW_KEYSYM_LEFTGUI },

    /* Left Alt */
    { XK_Alt_L, WINDOW_KEYCODE_LEFTALT, WINDOW_KEYSYM_LEFTALT },

    /* ' ' */
    { XK_space, WINDOW_KEYCODE_SPACE, WINDOW_KEYSYM_SPACE },

    /* Right Alt */
    { XK_Alt_R, WINDOW_KEYCODE_RIGHTALT, WINDOW_KEYSYM_RIGHTALT },

    /* Rigth Home/GUI */
    { XK_Super_R, WINDOW_KEYCODE_RIGHTGUI, WINDOW_KEYSYM_RIGHTGUI },

    /* Right Control */
    { XK_Control_R, WINDOW_KEYCODE_RIGHTCTRL, WINDOW_KEYSYM_RIGHTCTRL },

    /* Escape */ 
    { XK_Escape, WINDOW_KEYCODE_ESCAPE, WINDOW_KEYSYM_ESCAPE },

    /* F1 */ 
    { XK_F1, WINDOW_KEYCODE_F1, WINDOW_KEYSYM_F1 },

    /* F2 */ 
    { XK_F2, WINDOW_KEYCODE_F2, WINDOW_KEYSYM_F2 },

    /* F3 */ 
    { XK_F3, WINDOW_KEYCODE_F3, WINDOW_KEYSYM_F3 },

    /* F4 */ 
    { XK_F4, WINDOW_KEYCODE_F4, WINDOW_KEYSYM_F4 },

    /* F5 */ 
    { XK_F5, WINDOW_KEYCODE_F5, WINDOW_KEYSYM_F5 },

    /* F6 */ 
    { XK_F6, WINDOW_KEYCODE_F6, WINDOW_KEYSYM_F6 },

    /* F7 */ 
    { XK_F7, WINDOW_KEYCODE_F7, WINDOW_KEYSYM_F7 },

    /* F8 */ 
    { XK_F8, WINDOW_KEYCODE_F8, WINDOW_KEYSYM_F8 },

    /* F9 */ 
    { XK_F9, WINDOW_KEYCODE_F9, WINDOW_KEYSYM_F9 },

    /* F10 */ 
    { XK_F10, WINDOW_KEYCODE_F10, WINDOW_KEYSYM_F10 },

    /* F11 */ 
    { XK_F11, WINDOW_KEYCODE_F11, WINDOW_KEYSYM_F11 },

    /* F12 */ 
    { XK_F12, WINDOW_KEYCODE_F12, WINDOW_KEYSYM_F12 },

    /* Print-Screen */ 
    { XK_Print, WINDOW_KEYCODE_PRINTSCREEN, WINDOW_KEYSYM_PRINTSCREEN },

    /* Scroll-Lock */ 
    { XK_Scroll_Lock, WINDOW_KEYCODE_SCROLLLOCK, WINDOW_KEYSYM_SCROLLLOCK },

    /* Pause */ 
    { XK_Pause, WINDOW_KEYCODE_PAUSE, WINDOW_KEYSYM_PAUSE },

    /* Insert */ 
    { XK_Insert, WINDOW_KEYCODE_INSERT, WINDOW_KEYSYM_INSERT },

    /* Home */ 
    { XK_Home, WINDOW_KEYCODE_HOME, WINDOW_KEYSYM_HOME },

    /* Page-Up */ 
    { XK_Prior, WINDOW_KEYCODE_PAGEUP, WINDOW_KEYSYM_PAGEUP },

    /* Delete */ 
    { XK_Delete, WINDOW_KEYCODE_DELETE, WINDOW_KEYSYM_DELETE },

    /* End */ 
    { XK_End, WINDOW_KEYCODE_END, WINDOW_KEYSYM_END },

    /* Page-Down */ 
    { XK_Next, WINDOW_KEYCODE_PAGEDOWN, WINDOW_KEYSYM_PAGEDOWN },

    /* Up */ 
    { XK_Up, WINDOW_KEYCODE_UP, WINDOW_KEYSYM_UP },

    /* Left */ 
    { XK_Left, WINDOW_KEYCODE_LEFT, WINDOW_KEYSYM_LEFT },

    /* Down */ 
    { XK_Down, WINDOW_KEYCODE_DOWN, WINDOW_KEYSYM_DOWN },

    /* Right */ 
    { XK_Right, WINDOW_KEYCODE_RIGHT, WINDOW_KEYSYM_RIGHT },

    /* ... */

    { 0, 0, 0 } 

/* }}} */

};

/* internal functions (declarations) */

WININT int __win_x11_event_process(struct _window_h *, XEvent *);

WININT int __win_x11_selection_get(struct _window_h *, const Atom, void **, size_t *);

WININT int __win_x11_selection_set(struct _window_h *, const Atom, const void *, const size_t);

WININT int __win_x11_selection_handle(struct _window_h *, XEvent *);

/* window.h API (declarations) */

WININT int __win_x11_init(struct _window_h *);

WININT int __win_x11_load(struct _window_h *);

WININT int __win_x11_quit(struct _window_h *);

WININT int __win_x11_unload(struct _window_h *);

WININT int __win_x11_window_create(struct _window_h *, struct _window_h_window *, const size_t, const size_t, const char *);

WININT int __win_x11_window_destroy(struct _window_h *, struct _window_h_window *);

WININT int __win_x11_window_map(struct _window_h *, struct _window_h_window *);

WININT int __win_x11_window_unmap(struct _window_h *, struct _window_h_window *);

WININT int __win_x11_window_get_size(struct _window_h *, struct _window_h_window *, size_t *, size_t *);

WININT int __win_x11_window_set_size(struct _window_h *, struct _window_h_window *, const size_t, const size_t);

WININT int __win_x11_window_set_size_min(struct _window_h *, struct _window_h_window *, const size_t, const size_t);

WININT int __win_x11_window_set_size_max(struct _window_h *, struct _window_h_window *, const size_t, const size_t);

WININT int __win_x11_window_get_position(struct _window_h *, struct _window_h_window *, size_t *, size_t *);

WININT int __win_x11_window_set_position(struct _window_h *, struct _window_h_window *, const size_t, const size_t);

WININT int __win_x11_window_get_title(struct _window_h *, struct _window_h_window *, char **);

WININT int __win_x11_window_set_title(struct _window_h *, struct _window_h_window *, const char *);

WININT int __win_x11_context_create(struct _window_h *, struct _window_h_context *, struct _window_h_window *);

WININT int __win_x11_context_destroy(struct _window_h *, struct _window_h_context *);

WININT int __win_x11_cursor_create(struct _window_h *, struct _window_h_cursor *, const uint8_t *, const size_t, const size_t, const int, const int);

WININT int __win_x11_cursor_destroy(struct _window_h *, struct _window_h_cursor *);

WININT int __win_x11_cursor_get_position(struct _window_h *, struct _window_h_window *, size_t *, size_t *);

WININT int __win_x11_cursor_set_position(struct _window_h *, struct _window_h_window *, const size_t, const size_t);

WININT int __win_x11_cursor_get_mode(struct _window_h *, struct _window_h_window *, uint32_t *);

WININT int __win_x11_cursor_set_mode(struct _window_h *, struct _window_h_window *, const uint32_t);

WININT int __win_x11_event_poll(struct _window_h *);

WININT int __win_x11_event_wait(struct _window_h *);

WININT int __win_x11_copy(struct _window_h *, const uint32_t, const void *, const size_t);

WININT int __win_x11_paste(struct _window_h *, const uint32_t, void **, size_t *);

/* internal functions (definitions) */

WININT int __win_x11_event_process(struct _window_h *lib, XEvent *xevent) {
    /* null-check */
    if (!lib)    { return (0); }
    if (!xevent) { return (0); }
    
    /* get 'window_t' from XID */
    struct _window_h_window *win = lib->window.list;
    while (win) {
        if (win->x11->handle == xevent->xany.window) { break; }
        win = win->next;
    }

    switch (xevent->type) {
        case (ClientMessage): {
            XClientMessageEvent xclient = xevent->xclient;

            /* process different kind of client events */
            const Atom message_type = xclient.message_type;
            if (message_type == lib->x11->WM_PROTOCOLS) {
                /* get the received atom */
                const Atom data = xclient.data.l[0];

                /* WINDOW_EVENT_QUIT */
                if (data == lib->x11->WM_DELETE_WINDOW) {
                    win_event_send(lib, win, WINDOW_EVENT_QUIT);
                }
            }

            /* unhandled message type */
            else {
                return (0);
            }
        } break;

        case (CreateNotify): {
            win_event_send(lib, win, WINDOW_EVENT_WINDOW_CREATE, win, 0, 0); 
        } break;

        case (DestroyNotify): {
            win_event_send(lib, win, WINDOW_EVENT_WINDOW_DESTROY, win, 0, 0); 
        } break;

        case (MapNotify): {
            /* update attribute */
            win->attrib.mapped = 1;

            win_event_send(lib, win, WINDOW_EVENT_WINDOW_MAP, win, 0, 0); 
        } break;

        case (UnmapNotify): {
            /* update attribute */
            win->attrib.mapped = 0;

            win_event_send(lib, win, WINDOW_EVENT_WINDOW_UNMAP, win, 0, 0); 
        } break;

        case (EnterNotify): {
            /* update attribute */
            win->attrib.focused = 1;

            win_event_send(lib, win, WINDOW_EVENT_WINDOW_ENTER, win, 0, 0); 
        } break;

        case (LeaveNotify): {
            /* update attribute */
            win->attrib.focused = 0;

            win_event_send(lib, win, WINDOW_EVENT_WINDOW_LEAVE, win, 0, 0);
        } break;

        case (ConfigureNotify): {
            XConfigureEvent xconfigure = xevent->xconfigure;
            
            /* WINDOW_EVENT_WINDOW_RESIZE */
            if (xconfigure.width  != (int) win->attrib.size.x ||
                xconfigure.height != (int) win->attrib.size.y
            ) {
                win->attrib.size.x = xconfigure.width;
                win->attrib.size.y = xconfigure.height;
                win_event_send(lib, win, WINDOW_EVENT_WINDOW_RESIZE, win->attrib.size.x,
                                                                     win->attrib.size.y);
            }
            
            /* WINDOW_EVENT_WINDOW_MOTION */
            if (xconfigure.x != (int) win->attrib.position.x ||
                xconfigure.y != (int) win->attrib.position.y
            ) {
                win->attrib.position.x = xconfigure.x;
                win->attrib.position.y = xconfigure.y;
                win_event_send(lib, win, WINDOW_EVENT_WINDOW_MOTION, win->attrib.position.x,
                                                                     win->attrib.position.y);
            }
        } break;

        case (PropertyNotify): {
            XPropertyEvent xproperty = xevent->xproperty;

            /* property 'atom' */
            Atom atom = xproperty.atom;

            /* _NET_WM_STATE */
            Atom _NET_WM_STATE = lib->x11->_NET_WM_STATE;
            if (atom == _NET_WM_STATE) {
                /* get _NET_WM_STATE properties */
                Atom actual_type_return      = 0;
                int32_t actual_format_return = 0;
                uint64_t nitems_return       = 0;
                uint64_t bytes_after_return  = 0;
                uint8_t *prop_return         = 0;
                if (XGetWindowProperty(xproperty.display,
                                       xproperty.window,
                                       _NET_WM_STATE,
                                       0, ~0L, False, XA_ATOM,
                                       &actual_type_return,
                                       &actual_format_return,
                                       &nitems_return,
                                       &bytes_after_return,
                                       &prop_return)
                ) { return (0); }

                /* get win states */
                Atom *states = (Atom *) prop_return;

                /* iterate over win states */
                for (size_t i = 0; i < (size_t) nitems_return; i++) {
                    /* _NET_WM_STAET_FULLSCREEN */
                    if (states[i] == lib->x11->_NET_WM_STATE_FULLSCREEN) {
                        win->attrib.fullscreen = !win->attrib.fullscreen;
                    }
                    
                    /* _NET_WM_STATE_HIDDEN */
                    else if (states[i] == lib->x11->_NET_WM_STATE_HIDDEN) {
                        win->attrib.minimized = !win->attrib.minimized;
                    }
                    
                    /* _NET_WM_STATE_MAXIMIZED */
                    else if (states[i] == lib->x11->_NET_WM_STATE_MAXIMIZED_VERT ||
                             states[i] == lib->x11->_NET_WM_STATE_MAXIMIZED_HORZ
                    ) {
                        win->attrib.maximized = !win->attrib.maximized;
                    }
                }

                /* release win states  */
                XFree(states);
            }

        } break;

        case (MotionNotify): {
            XMotionEvent xmotion = xevent->xmotion;

            uint32_t x = xmotion.x,
                     y = xmotion.y;

            /* get the window size */
            size_t win_w = 0,
                   win_h = 0;
            win_window_get_size(lib, win, &win_w, &win_h);

            /* absorb pending warp */
            if (win->cursor.attrib.warp) {
                if (x == win_w / 2 &&
                    y == win_h / 2
                ) {
                    win->cursor.attrib.warp = 0;
                    win->cursor.attrib.last.x = x;
                    win->cursor.attrib.last.y = y;
                    break;
                }
            }

            /* centered/disabled cursor */
            if (win->cursor.attrib.mode == WINDOW_CURSOR_MODE_CENTERED ||
                win->cursor.attrib.mode == WINDOW_CURSOR_MODE_DISABLED
            ) {
                int32_t delta_x = x - win->cursor.attrib.last.x,
                        delta_y = y - win->cursor.attrib.last.y;

                win->cursor.attrib.accum.x += delta_x;
                win->cursor.attrib.accum.y += delta_y;
                win->cursor.attrib.last.x = x;
                win->cursor.attrib.last.y = y;
                break;
            }

            win_event_send(lib, win, WINDOW_EVENT_MOUSE_MOTION, x, y);
        } break;

        case (ButtonPress):
        case (ButtonRelease): {
            XButtonEvent xbutton = xevent->xbutton;
            
            /* WINDOW_EVENT_MOUSE_BUTTON */
            if (xbutton.button >= 1 && xbutton.button <= 3) {
                uint8_t btn = 0;
                switch (xbutton.button) {
                    case (1): { btn = WINDOW_BUTTON_LEFT;   } break; /* left */
                    case (2): { btn = WINDOW_BUTTON_MIDDLE; } break; /* middle */
                    case (3): { btn = WINDOW_BUTTON_RIGHT;  } break; /* right */
                }
                uint8_t state = xbutton.type == ButtonPress ? 1 : 0;
                win_event_send(lib, win, WINDOW_EVENT_MOUSE_BUTTON, btn, state);
            }
            
            /* WINDOW_EVENT_MOUSE_SCROLL */
            else if (xbutton.button >= 4 && xbutton.button <= 7) {
                int32_t scroll_x = 0,
                        scroll_y = 0;
                if (xbutton.button == 4)      { scroll_y =  1; }
                else if (xbutton.button == 5) { scroll_y = -1; }
                else if (xbutton.button == 6) { scroll_x =  1; }
                else if (xbutton.button == 7) { scroll_x = -1; }
                win_event_send(lib, win, WINDOW_EVENT_MOUSE_SCROLL, scroll_x, scroll_y);
            }
            
            /* WINDOW_EVENT_MOUSE_BUTTON */
            else {
                uint8_t btn   = xbutton.button - Button1 - 4,
                        state = xbutton.type == ButtonPress ? 1 : 0;
                win_event_send(lib, win, WINDOW_EVENT_MOUSE_BUTTON, btn, state);
            }
        } break;

        case (KeyPress):
        case (KeyRelease): {
            XKeyEvent xkey = xevent->xkey;

            /* get the X11's keysym */
            uint32_t keyraw = XkbKeycodeToKeysym(xkey.display,
                                                 xkey.keycode, 0,
                                                 xkey.state & ShiftMask ? 1 : 0);

            /* Iterate over the keymap to find the matching mapping.
             * As of now we're only processing en-US QWERTY keymap with latin symbols.
             * Other keyboard layout's might not work. However, there're some foudnations
             * to implement layout switching which *might* make it available to layout-switch!
             * */
            uint32_t keycode = 0,
                     keysym  = 0;
            for (size_t i = 0; _window_h_keymap_en_us_qwerty[i].src; i++) {
                if (keyraw == _window_h_keymap_en_us_qwerty[i].src) {
                    keycode = _window_h_keymap_en_us_qwerty[i].kc;
                    keysym  = _window_h_keymap_en_us_qwerty[i].ks;
                    break;
                }
            }

            /* if either 'keycode' or 'keysym' are '0', it's an obvious fail */
            if (!keycode || !keysym) { return (0); }

            /* get the keyboard modes mask */
            uint32_t keymod = 0;
            if (xkey.state & ShiftMask)   { keymod |= WINDOW_KEYMOD_SHIFT; }
            if (xkey.state & ControlMask) { keymod |= WINDOW_KEYMOD_CTRL; }
            if (xkey.state & Mod1Mask)    { keymod |= WINDOW_KEYMOD_ALT; }
            if (xkey.state & Mod2Mask)    { keymod |= WINDOW_KEYMOD_NUMLOCK; }
            if (xkey.state & Mod4Mask)    { keymod |= WINDOW_KEYMOD_GUI; }
            if (xkey.state & LockMask)    { keymod |= WINDOW_KEYMOD_CAPSLOCK; }

            /* get keyboard press/release state */
            uint8_t state = xkey.type == KeyPress ? 1 : 0;

            win_event_send(lib, win, WINDOW_EVENT_KEYBOARD_KEY, keysym, keycode, keymod, keyraw, state, 0);
        } break;

        case (SelectionRequest): {
            /* process selections */
            if (__win_x11_selection_handle(lib, xevent)) {
                win_event_send(lib, win, WINDOW_EVENT_SELECTION_WRITE, lib->selection.clipboard.data,
                                                                       lib->selection.clipboard.size);
            }
        } break;

        case (SelectionNotify): {
            /* process selections */
            if (__win_x11_selection_handle(lib, xevent)) {
                win_event_send(lib, win, WINDOW_EVENT_SELECTION_READ, lib->selection.clipboard.data,
                                                                      lib->selection.clipboard.size);
            }
        } break;

        case (SelectionClear): { } break;
    }

    /* success */
    return (1);
}

WININT int __win_x11_selection_get(struct _window_h *lib, const Atom selection, void **d_ptr, size_t *s_ptr) {
    /* null-check */
    if (!lib) { return (0); }

    /* xlib references */
    Display *dpy = lib->x11->dpy;
    Window   ipc = lib->x11->ipc;

    /* xatom references */
    Atom CLIPBOARD = lib->x11->CLIPBOARD;
    Atom UTF8_STRING = lib->x11->UTF8_STRING;

    /* get globally-stored selection data */
    void  **data = 0;
    size_t *size = 0;
    if (selection == XA_PRIMARY) {
        data = &lib->selection.primary.data;
        size = &lib->selection.primary.size;
    }
    else if (selection == XA_SECONDARY) {
        data = &lib->selection.secondary.data;
        size = &lib->selection.secondary.size;
    }
    else if (selection == CLIPBOARD) {
        data = &lib->selection.clipboard.data;
        size = &lib->selection.clipboard.size;
    }
    else { return (0); }

    /* check if we're the 'selection' owner */
    if (XGetSelectionOwner(dpy, selection) == ipc) {
        /* if so, save some time and straight-up return the string */
        *d_ptr = calloc(*size + 1, sizeof(char));
        *d_ptr = memcpy(*d_ptr, *data, *size);
        *s_ptr = *size;
        return (1);
    }
    
    /* check if the 'selection' owner (clipboard source) even exists */
    if (XGetSelectionOwner(dpy, selection) == None) {
        *d_ptr = 0;
        *s_ptr = 0;
        return (0);
    }

    free(*data);
    *data = 0;
    *size = 0;

    XConvertSelection(dpy, selection, UTF8_STRING, selection, ipc, CurrentTime);

    /* get the 'Selection...' event  */
    XEvent xevent = { 0 };
    do {
        XNextEvent(dpy, &xevent);
    } while (xevent.type != SelectionNotify &&
             xevent.type != SelectionRequest);

    /* perform round-trip */
    if (!__win_x11_selection_handle(lib, &xevent)) { return (0); }

    /* copy the selection data to 'str' */
    if (!*data) { return (0); }
    *d_ptr = calloc(*size + 1, sizeof(char));
    *d_ptr = memcpy(*d_ptr, *data, *size);
    *s_ptr = *size;

    /* success */
    return (1);
}


WININT int __win_x11_selection_set(struct _window_h *lib, const Atom selection, const void *data, const size_t size) {
    /* null-check */
    if (!lib) { return (0); }
    
    /* xlib references */
    Display *dpy = lib->x11->dpy;
    Window   ipc = lib->x11->ipc;

    /* xatom references */
    Atom CLIPBOARD = lib->x11->CLIPBOARD;

    /* set globally-stored selection data */
    if (selection == XA_PRIMARY) {
        free(lib->selection.primary.data);
        lib->selection.primary.data = malloc(size);
        lib->selection.primary.data = memcpy(lib->selection.primary.data, data, size);
        lib->selection.primary.size = size;
    }
    else if (selection == XA_SECONDARY) {
        free(lib->selection.secondary.data);
        lib->selection.secondary.data = malloc(size);
        lib->selection.secondary.data = memcpy(lib->selection.secondary.data, data, size);
        lib->selection.secondary.size = size;
    }
    else if (selection == CLIPBOARD) {
        free(lib->selection.clipboard.data);
        lib->selection.clipboard.data = malloc(size);
        lib->selection.clipboard.data = memcpy(lib->selection.clipboard.data, data, size);
        lib->selection.clipboard.size = size;
    }
    else { return (0); }
    
    /* set the process as the owner of 'selection' selection */
    XSetSelectionOwner(dpy, selection, ipc, CurrentTime);

    /* check if process owns the 'selection' selection */
    if (XGetSelectionOwner(dpy, selection) != ipc) {
        return (0);
    }
    
    /* success */
    return (1);
}


WININT int __win_x11_selection_handle(struct _window_h *lib, XEvent *xevent) {
    /* null-check */
    if (!lib) { return (0); }

    /* xatom references */
    Atom TARGETS = lib->x11->TARGETS;
    Atom CLIPBOARD = lib->x11->CLIPBOARD;
    Atom UTF8_STRING = lib->x11->UTF8_STRING;

    /* request / notify result */
    int result = 0;

    switch (xevent->type) {
        case (SelectionRequest): {
            /* get the event object */
            XSelectionRequestEvent request = xevent->xselectionrequest;

            /* check if property is 'None' */
            if (request.property == None) { return (0); }
            
            /* get the proper selection string */
            void  *data = 0;
            size_t size = 0;
            if (request.selection== XA_PRIMARY) {
                data = lib->selection.primary.data;
                size = lib->selection.primary.size;
            } else if (request.selection == XA_SECONDARY) {
                data = lib->selection.secondary.data;
                size = lib->selection.secondary.size;
            } else if (request.selection == CLIPBOARD) {
                data = lib->selection.clipboard.data;
                size = lib->selection.clipboard.size;
            }

            /* request target list */
            const Atom targets[] = { UTF8_STRING, XA_STRING };
            const size_t target_count = sizeof(targets) / sizeof(*targets);

            if (request.target == TARGETS) {
                const Atom targets[] = { TARGETS, UTF8_STRING, XA_STRING };
                const size_t target_count = sizeof(targets) / sizeof(*targets);

                XChangeProperty(request.display,
                                request.requestor,
                                request.property,
                                XA_ATOM,
                                32, PropModeReplace,
                                (uint8_t *) targets,
                                (size_t) target_count);
            }
            else {
                for (size_t i = 0; i < target_count; i++) {
                    /* check if request matches our target */
                    if (request.target != targets[i]) { continue; }
                    XChangeProperty(request.display,
                                    request.requestor,
                                    request.property,
                                    request.target,
                                    8, PropModeReplace,
                                    (uint8_t *) data,
                                    (size_t)    size);

                    result = 1;
                }
            }
            
            /* reply event */
            XSelectionEvent reply = {
                .type       = SelectionNotify,
                .serial     = request.serial,
                .send_event = request.send_event,
                .display    = request.display,
                .requestor  = request.requestor,
                .selection  = request.selection,
                .target     = request.target,
                .property   = request.property,
                .time       = request.time
            };

            XSendEvent(reply.display,
                       reply.requestor,
                       0, 0,
                       (XEvent *) &reply);

        } return (result);

        case (SelectionNotify): {
            /* get the event object */
            XSelectionEvent notify = xevent->xselection;

            /* check if property is 'None' */
            if (notify.property == None) { return (0); }
            
            /* get the proper selection string */
            void  **data = 0;
            size_t *size = 0;
            if (notify.selection== XA_PRIMARY) {
                data = &lib->selection.primary.data;
                size = &lib->selection.primary.size;
            } else if (notify.selection == XA_SECONDARY) {
                data = &lib->selection.secondary.data;
                size = &lib->selection.secondary.size;
            } else if (notify.selection == CLIPBOARD) {
                data = &lib->selection.clipboard.data;
                size = &lib->selection.clipboard.size;
            }
                        
            /* get window properties */
            Atom actual_type_return      = 0;
            int32_t actual_format_return = 0;
            uint64_t nitems_return       = 0;
            uint64_t bytes_after_return  = 0;
            uint8_t *prop_return         = 0;
            XGetWindowProperty(notify.display,
                               notify.requestor,
                               notify.property,
                               0, ~0L, False,
                               AnyPropertyType,
                               &actual_type_return,
                               &actual_format_return,
                               &nitems_return,
                               &bytes_after_return,
                               &prop_return);

            /* check the return target */
            if (actual_type_return == UTF8_STRING ||
                actual_type_return == XA_STRING
            ) {
                if (*data) { free(*data); }
                *data = (char *) prop_return;
                *size = (size_t) nitems_return;
                result = 1;
            }

            XDeleteProperty(notify.display,
                            notify.requestor,
                            notify.property);

        } return (result);
    }

    /* failure */
    return (0);
}

/* window.h API (declarations) */

WININT int __win_x11_init(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* references */
    struct _window_h_x11 *x11 = lib->x11; 
    if (!x11) { return (0); }
    
    x11->dpy = XOpenDisplay(0);
    if (!x11->dpy) { return (0); }

    x11->root = DefaultRootWindow(x11->dpy);
    if (!x11->root) { return (0); }
    
    XSetWindowAttributes attr = { .event_mask = PropertyChangeMask };
    x11->ipc = XCreateWindow(x11->dpy,
                                  x11->root,
                                  0, 0, 1, 1, 0, 0,
                                  InputOnly,
                                  CopyFromParent,
                                  CWEventMask,
                                  &attr);
    if (!x11->ipc) { return (0); }

    x11->WM_PROTOCOLS = XInternAtom(x11->dpy, "WM_PROTOCOLS", False);

    x11->WM_DELETE_WINDOW = XInternAtom(x11->dpy, "WM_DELETE_WINDOW", False);

    x11->_NET_WM_STATE = XInternAtom(x11->dpy, "_NET_WM_STATE", False);
    
    x11->_NET_WM_STATE_MODAL = XInternAtom(x11->dpy, "_NET_WM_STATE_MODAL", False);

    x11->_NET_WM_STATE_STICKY = XInternAtom(x11->dpy, "_NET_WM_STATE_STICKY", False);

    x11->_NET_WM_STATE_MAXIMIZED_VERT = XInternAtom(x11->dpy, "_NET_WM_STATE_MAXIMIZED_VERT", False);

    x11->_NET_WM_STATE_MAXIMIZED_HORZ = XInternAtom(x11->dpy, "_NET_WM_STATE_MAXIMIZED_HORZ", False);

    x11->_NET_WM_STATE_SHADED = XInternAtom(x11->dpy, "_NET_WM_STATE_SHADED", False);

    x11->_NET_WM_STATE_SKIP_TASKBAR = XInternAtom(x11->dpy, "_NET_WM_STATE_SKIP_TASKBAR", False);

    x11->_NET_WM_STATE_SKIP_PAGER = XInternAtom(x11->dpy, "_NET_WM_STATE_SKIP_PAGER", False);

    x11->_NET_WM_STATE_HIDDEN = XInternAtom(x11->dpy, "_NET_WM_STATE_HIDDEN", False);

    x11->_NET_WM_STATE_FULLSCREEN = XInternAtom(x11->dpy, "_NET_WM_STATE_FULLSCREEN", False);

    x11->_NET_WM_STATE_ABOVE = XInternAtom(x11->dpy, "_NET_WM_STATE_ABOVE", False);

    x11->_NET_WM_STATE_BELOW = XInternAtom(x11->dpy, "_NET_WM_STATE_BELOW", False);

    x11->_NET_WM_STATE_DEMANDS_ATTENTION = XInternAtom(x11->dpy, "_NET_WM_STATE_DEMANDS_ATTENTION", False);

    x11->_NET_WM_STATE_FOCUSED = XInternAtom(x11->dpy, "_NET_WM_STATE_FOCUSED", False);

    x11->TARGETS = XInternAtom(x11->dpy, "TARGETS", False);

    x11->CLIPBOARD = XInternAtom(x11->dpy, "CLIPBOARD", False);

    x11->UTF8_STRING = XInternAtom(x11->dpy, "UTF8_STRING", False);

    /* set the 'lib' members */
    lib->handle = (void *) x11->dpy;

    /* success */
    return (1);
}


WININT int __win_x11_load(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }
    if (lib->x11) { return (1); }

    /* init-check */
    struct _window_h_x11 *x11 = calloc(1, sizeof(struct _window_h_x11));
    if (!x11) { return (0); }

    void *libx11  = 0;
    {
        const char  *names[] = { "libX11.so", "libX11.so.6", "libX11.so.6.4.0", 0 };
        for (const char **name = names; *name; name++) {
            libx11 = dlopen(*name, RTLD_LAZY | RTLD_LOCAL);
            if (libx11) { break; }
        }

        /* check if libx11 is loaded */
        if (!libx11) {
            return (0);
        }
    }

    /* {{{ */

    XActivateScreenSaver_PROC = (PFN_XActivateScreenSaver_PROC) dlsym(libx11, "XActivateScreenSaver");
    XAddConnectionWatch_PROC = (PFN_XAddConnectionWatch_PROC) dlsym(libx11, "XAddConnectionWatch");
    XAddExtension_PROC = (PFN_XAddExtension_PROC) dlsym(libx11, "XAddExtension");
    XAddHost_PROC = (PFN_XAddHost_PROC) dlsym(libx11, "XAddHost");
    XAddHosts_PROC = (PFN_XAddHosts_PROC) dlsym(libx11, "XAddHosts");
    XAddToExtensionList_PROC = (PFN_XAddToExtensionList_PROC) dlsym(libx11, "XAddToExtensionList");
    XAddToSaveSet_PROC = (PFN_XAddToSaveSet_PROC) dlsym(libx11, "XAddToSaveSet");
    XAllPlanes_PROC = (PFN_XAllPlanes_PROC) dlsym(libx11, "XAllPlanes");
    XAllocColor_PROC = (PFN_XAllocColor_PROC) dlsym(libx11, "XAllocColor");
    XAllocColorCells_PROC = (PFN_XAllocColorCells_PROC) dlsym(libx11, "XAllocColorCells");
    XAllocColorPlanes_PROC = (PFN_XAllocColorPlanes_PROC) dlsym(libx11, "XAllocColorPlanes");
    XAllocNamedColor_PROC = (PFN_XAllocNamedColor_PROC) dlsym(libx11, "XAllocNamedColor");
    XAllowEvents_PROC = (PFN_XAllowEvents_PROC) dlsym(libx11, "XAllowEvents");
    XAutoRepeatOff_PROC = (PFN_XAutoRepeatOff_PROC) dlsym(libx11, "XAutoRepeatOff");
    XAutoRepeatOn_PROC = (PFN_XAutoRepeatOn_PROC) dlsym(libx11, "XAutoRepeatOn");
    XBaseFontNameListOfFontSet_PROC = (PFN_XBaseFontNameListOfFontSet_PROC) dlsym(libx11, "XBaseFontNameListOfFontSet");
    XBell_PROC = (PFN_XBell_PROC) dlsym(libx11, "XBell");
    XBitmapBitOrder_PROC = (PFN_XBitmapBitOrder_PROC) dlsym(libx11, "XBitmapBitOrder");
    XBitmapPad_PROC = (PFN_XBitmapPad_PROC) dlsym(libx11, "XBitmapPad");
    XBitmapUnit_PROC = (PFN_XBitmapUnit_PROC) dlsym(libx11, "XBitmapUnit");
    XBlackPixel_PROC = (PFN_XBlackPixel_PROC) dlsym(libx11, "XBlackPixel");
    XBlackPixelOfScreen_PROC = (PFN_XBlackPixelOfScreen_PROC) dlsym(libx11, "XBlackPixelOfScreen");
    XCellsOfScreen_PROC = (PFN_XCellsOfScreen_PROC) dlsym(libx11, "XCellsOfScreen");
    XChangeActivePointerGrab_PROC = (PFN_XChangeActivePointerGrab_PROC) dlsym(libx11, "XChangeActivePointerGrab");
    XChangeGC_PROC = (PFN_XChangeGC_PROC) dlsym(libx11, "XChangeGC");
    XChangeKeyboardControl_PROC = (PFN_XChangeKeyboardControl_PROC) dlsym(libx11, "XChangeKeyboardControl");
    XChangeKeyboardMapping_PROC = (PFN_XChangeKeyboardMapping_PROC) dlsym(libx11, "XChangeKeyboardMapping");
    XChangePointerControl_PROC = (PFN_XChangePointerControl_PROC) dlsym(libx11, "XChangePointerControl");
    XChangeProperty_PROC = (PFN_XChangeProperty_PROC) dlsym(libx11, "XChangeProperty");
    XChangeSaveSet_PROC = (PFN_XChangeSaveSet_PROC) dlsym(libx11, "XChangeSaveSet");
    XChangeWindowAttributes_PROC = (PFN_XChangeWindowAttributes_PROC) dlsym(libx11, "XChangeWindowAttributes");
    XCheckIfEvent_PROC = (PFN_XCheckIfEvent_PROC) dlsym(libx11, "XCheckIfEvent");
    XCheckMaskEvent_PROC = (PFN_XCheckMaskEvent_PROC) dlsym(libx11, "XCheckMaskEvent");
    XCheckTypedEvent_PROC = (PFN_XCheckTypedEvent_PROC) dlsym(libx11, "XCheckTypedEvent");
    XCheckTypedWindowEvent_PROC = (PFN_XCheckTypedWindowEvent_PROC) dlsym(libx11, "XCheckTypedWindowEvent");
    XCheckWindowEvent_PROC = (PFN_XCheckWindowEvent_PROC) dlsym(libx11, "XCheckWindowEvent");
    XCirculateSubwindows_PROC = (PFN_XCirculateSubwindows_PROC) dlsym(libx11, "XCirculateSubwindows");
    XCirculateSubwindowsDown_PROC = (PFN_XCirculateSubwindowsDown_PROC) dlsym(libx11, "XCirculateSubwindowsDown");
    XCirculateSubwindowsUp_PROC = (PFN_XCirculateSubwindowsUp_PROC) dlsym(libx11, "XCirculateSubwindowsUp");
    XClearArea_PROC = (PFN_XClearArea_PROC) dlsym(libx11, "XClearArea");
    XClearWindow_PROC = (PFN_XClearWindow_PROC) dlsym(libx11, "XClearWindow");
    XCloseDisplay_PROC = (PFN_XCloseDisplay_PROC) dlsym(libx11, "XCloseDisplay");
    XCloseIM_PROC = (PFN_XCloseIM_PROC) dlsym(libx11, "XCloseIM");
    XCloseOM_PROC = (PFN_XCloseOM_PROC) dlsym(libx11, "XCloseOM");
    XConfigureWindow_PROC = (PFN_XConfigureWindow_PROC) dlsym(libx11, "XConfigureWindow");
    XConnectionNumber_PROC = (PFN_XConnectionNumber_PROC) dlsym(libx11, "XConnectionNumber");
    XContextDependentDrawing_PROC = (PFN_XContextDependentDrawing_PROC) dlsym(libx11, "XContextDependentDrawing");
    XContextualDrawing_PROC = (PFN_XContextualDrawing_PROC) dlsym(libx11, "XContextualDrawing");
    XConvertSelection_PROC = (PFN_XConvertSelection_PROC) dlsym(libx11, "XConvertSelection");
    XCopyArea_PROC = (PFN_XCopyArea_PROC) dlsym(libx11, "XCopyArea");
    XCopyColormapAndFree_PROC = (PFN_XCopyColormapAndFree_PROC) dlsym(libx11, "XCopyColormapAndFree");
    XCopyGC_PROC = (PFN_XCopyGC_PROC) dlsym(libx11, "XCopyGC");
    XCopyPlane_PROC = (PFN_XCopyPlane_PROC) dlsym(libx11, "XCopyPlane");
    XCreateBitmapFromData_PROC = (PFN_XCreateBitmapFromData_PROC) dlsym(libx11, "XCreateBitmapFromData");
    XCreateColormap_PROC = (PFN_XCreateColormap_PROC) dlsym(libx11, "XCreateColormap");
    XCreateFontCursor_PROC = (PFN_XCreateFontCursor_PROC) dlsym(libx11, "XCreateFontCursor");
    XCreateFontSet_PROC = (PFN_XCreateFontSet_PROC) dlsym(libx11, "XCreateFontSet");
    XCreateGC_PROC = (PFN_XCreateGC_PROC) dlsym(libx11, "XCreateGC");
    XCreateGlyphCursor_PROC = (PFN_XCreateGlyphCursor_PROC) dlsym(libx11, "XCreateGlyphCursor");
    XCreateIC_PROC = (PFN_XCreateIC_PROC) dlsym(libx11, "XCreateIC");
    XCreateImage_PROC = (PFN_XCreateImage_PROC) dlsym(libx11, "XCreateImage");
    XCreateOC_PROC = (PFN_XCreateOC_PROC) dlsym(libx11, "XCreateOC");
    XCreatePixmap_PROC = (PFN_XCreatePixmap_PROC) dlsym(libx11, "XCreatePixmap");
    XCreatePixmapCursor_PROC = (PFN_XCreatePixmapCursor_PROC) dlsym(libx11, "XCreatePixmapCursor");
    XCreatePixmapFromBitmapData_PROC = (PFN_XCreatePixmapFromBitmapData_PROC) dlsym(libx11, "XCreatePixmapFromBitmapData");
    XCreateSimpleWindow_PROC = (PFN_XCreateSimpleWindow_PROC) dlsym(libx11, "XCreateSimpleWindow");
    XCreateWindow_PROC = (PFN_XCreateWindow_PROC) dlsym(libx11, "XCreateWindow");
    XDefaultColormap_PROC = (PFN_XDefaultColormap_PROC) dlsym(libx11, "XDefaultColormap");
    XDefaultColormapOfScreen_PROC = (PFN_XDefaultColormapOfScreen_PROC) dlsym(libx11, "XDefaultColormapOfScreen");
    XDefaultDepth_PROC = (PFN_XDefaultDepth_PROC) dlsym(libx11, "XDefaultDepth");
    XDefaultDepthOfScreen_PROC = (PFN_XDefaultDepthOfScreen_PROC) dlsym(libx11, "XDefaultDepthOfScreen");
    XDefaultGC_PROC = (PFN_XDefaultGC_PROC) dlsym(libx11, "XDefaultGC");
    XDefaultGCOfScreen_PROC = (PFN_XDefaultGCOfScreen_PROC) dlsym(libx11, "XDefaultGCOfScreen");
    XDefaultRootWindow_PROC = (PFN_XDefaultRootWindow_PROC) dlsym(libx11, "XDefaultRootWindow");
    XDefaultScreen_PROC = (PFN_XDefaultScreen_PROC) dlsym(libx11, "XDefaultScreen");
    XDefaultScreenOfDisplay_PROC = (PFN_XDefaultScreenOfDisplay_PROC) dlsym(libx11, "XDefaultScreenOfDisplay");
    XDefaultVisual_PROC = (PFN_XDefaultVisual_PROC) dlsym(libx11, "XDefaultVisual");
    XDefaultVisualOfScreen_PROC = (PFN_XDefaultVisualOfScreen_PROC) dlsym(libx11, "XDefaultVisualOfScreen");
    XDefineCursor_PROC = (PFN_XDefineCursor_PROC) dlsym(libx11, "XDefineCursor");
    XDeleteModifiermapEntry_PROC = (PFN_XDeleteModifiermapEntry_PROC) dlsym(libx11, "XDeleteModifiermapEntry");
    XDeleteProperty_PROC = (PFN_XDeleteProperty_PROC) dlsym(libx11, "XDeleteProperty");
    XDestroyIC_PROC = (PFN_XDestroyIC_PROC) dlsym(libx11, "XDestroyIC");
    XDestroyOC_PROC = (PFN_XDestroyOC_PROC) dlsym(libx11, "XDestroyOC");
    XDestroySubwindows_PROC = (PFN_XDestroySubwindows_PROC) dlsym(libx11, "XDestroySubwindows");
    XDestroyWindow_PROC = (PFN_XDestroyWindow_PROC) dlsym(libx11, "XDestroyWindow");
    XDirectionalDependentDrawing_PROC = (PFN_XDirectionalDependentDrawing_PROC) dlsym(libx11, "XDirectionalDependentDrawing");
    XDisableAccessControl_PROC = (PFN_XDisableAccessControl_PROC) dlsym(libx11, "XDisableAccessControl");
    XDisplayCells_PROC = (PFN_XDisplayCells_PROC) dlsym(libx11, "XDisplayCells");
    XDisplayHeight_PROC = (PFN_XDisplayHeight_PROC) dlsym(libx11, "XDisplayHeight");
    XDisplayHeightMM_PROC = (PFN_XDisplayHeightMM_PROC) dlsym(libx11, "XDisplayHeightMM");
    XDisplayKeycodes_PROC = (PFN_XDisplayKeycodes_PROC) dlsym(libx11, "XDisplayKeycodes");
    XDisplayMotionBufferSize_PROC = (PFN_XDisplayMotionBufferSize_PROC) dlsym(libx11, "XDisplayMotionBufferSize");
    XDisplayName_PROC = (PFN_XDisplayName_PROC) dlsym(libx11, "XDisplayName");
    XDisplayOfIM_PROC = (PFN_XDisplayOfIM_PROC) dlsym(libx11, "XDisplayOfIM");
    XDisplayOfOM_PROC = (PFN_XDisplayOfOM_PROC) dlsym(libx11, "XDisplayOfOM");
    XDisplayOfScreen_PROC = (PFN_XDisplayOfScreen_PROC) dlsym(libx11, "XDisplayOfScreen");
    XDisplayPlanes_PROC = (PFN_XDisplayPlanes_PROC) dlsym(libx11, "XDisplayPlanes");
    XDisplayString_PROC = (PFN_XDisplayString_PROC) dlsym(libx11, "XDisplayString");
    XDisplayWidth_PROC = (PFN_XDisplayWidth_PROC) dlsym(libx11, "XDisplayWidth");
    XDisplayWidthMM_PROC = (PFN_XDisplayWidthMM_PROC) dlsym(libx11, "XDisplayWidthMM");
    XDoesBackingStore_PROC = (PFN_XDoesBackingStore_PROC) dlsym(libx11, "XDoesBackingStore");
    XDoesSaveUnders_PROC = (PFN_XDoesSaveUnders_PROC) dlsym(libx11, "XDoesSaveUnders");
    XDrawArc_PROC = (PFN_XDrawArc_PROC) dlsym(libx11, "XDrawArc");
    XDrawArcs_PROC = (PFN_XDrawArcs_PROC) dlsym(libx11, "XDrawArcs");
    XDrawImageString_PROC = (PFN_XDrawImageString_PROC) dlsym(libx11, "XDrawImageString");
    XDrawImageString16_PROC = (PFN_XDrawImageString16_PROC) dlsym(libx11, "XDrawImageString16");
    XDrawLine_PROC = (PFN_XDrawLine_PROC) dlsym(libx11, "XDrawLine");
    XDrawLines_PROC = (PFN_XDrawLines_PROC) dlsym(libx11, "XDrawLines");
    XDrawPoint_PROC = (PFN_XDrawPoint_PROC) dlsym(libx11, "XDrawPoint");
    XDrawPoints_PROC = (PFN_XDrawPoints_PROC) dlsym(libx11, "XDrawPoints");
    XDrawRectangle_PROC = (PFN_XDrawRectangle_PROC) dlsym(libx11, "XDrawRectangle");
    XDrawRectangles_PROC = (PFN_XDrawRectangles_PROC) dlsym(libx11, "XDrawRectangles");
    XDrawSegments_PROC = (PFN_XDrawSegments_PROC) dlsym(libx11, "XDrawSegments");
    XDrawString_PROC = (PFN_XDrawString_PROC) dlsym(libx11, "XDrawString");
    XDrawString16_PROC = (PFN_XDrawString16_PROC) dlsym(libx11, "XDrawString16");
    XDrawText_PROC = (PFN_XDrawText_PROC) dlsym(libx11, "XDrawText");
    XDrawText16_PROC = (PFN_XDrawText16_PROC) dlsym(libx11, "XDrawText16");
    XEHeadOfExtensionList_PROC = (PFN_XEHeadOfExtensionList_PROC) dlsym(libx11, "XEHeadOfExtensionList");
    XEnableAccessControl_PROC = (PFN_XEnableAccessControl_PROC) dlsym(libx11, "XEnableAccessControl");
    XEventMaskOfScreen_PROC = (PFN_XEventMaskOfScreen_PROC) dlsym(libx11, "XEventMaskOfScreen");
    XEventsQueued_PROC = (PFN_XEventsQueued_PROC) dlsym(libx11, "XEventsQueued");
    XExtendedMaxRequestSize_PROC = (PFN_XExtendedMaxRequestSize_PROC) dlsym(libx11, "XExtendedMaxRequestSize");
    XExtentsOfFontSet_PROC = (PFN_XExtentsOfFontSet_PROC) dlsym(libx11, "XExtentsOfFontSet");
    XFetchBuffer_PROC = (PFN_XFetchBuffer_PROC) dlsym(libx11, "XFetchBuffer");
    XFetchBytes_PROC = (PFN_XFetchBytes_PROC) dlsym(libx11, "XFetchBytes");
    XFetchName_PROC = (PFN_XFetchName_PROC) dlsym(libx11, "XFetchName");
    XFillArc_PROC = (PFN_XFillArc_PROC) dlsym(libx11, "XFillArc");
    XFillArcs_PROC = (PFN_XFillArcs_PROC) dlsym(libx11, "XFillArcs");
    XFillPolygon_PROC = (PFN_XFillPolygon_PROC) dlsym(libx11, "XFillPolygon");
    XFillRectangle_PROC = (PFN_XFillRectangle_PROC) dlsym(libx11, "XFillRectangle");
    XFillRectangles_PROC = (PFN_XFillRectangles_PROC) dlsym(libx11, "XFillRectangles");
    XFilterEvent_PROC = (PFN_XFilterEvent_PROC) dlsym(libx11, "XFilterEvent");
    XFindOnExtensionList_PROC = (PFN_XFindOnExtensionList_PROC) dlsym(libx11, "XFindOnExtensionList");
    XFlush_PROC = (PFN_XFlush_PROC) dlsym(libx11, "XFlush");
    XFlushGC_PROC = (PFN_XFlushGC_PROC) dlsym(libx11, "XFlushGC");
    XFontsOfFontSet_PROC = (PFN_XFontsOfFontSet_PROC) dlsym(libx11, "XFontsOfFontSet");
    XForceScreenSaver_PROC = (PFN_XForceScreenSaver_PROC) dlsym(libx11, "XForceScreenSaver");
    XFree_PROC = (PFN_XFree_PROC) dlsym(libx11, "XFree");
    XFreeColormap_PROC = (PFN_XFreeColormap_PROC) dlsym(libx11, "XFreeColormap");
    XFreeColors_PROC = (PFN_XFreeColors_PROC) dlsym(libx11, "XFreeColors");
    XFreeCursor_PROC = (PFN_XFreeCursor_PROC) dlsym(libx11, "XFreeCursor");
    XFreeEventData_PROC = (PFN_XFreeEventData_PROC) dlsym(libx11, "XFreeEventData");
    XFreeExtensionList_PROC = (PFN_XFreeExtensionList_PROC) dlsym(libx11, "XFreeExtensionList");
    XFreeFont_PROC = (PFN_XFreeFont_PROC) dlsym(libx11, "XFreeFont");
    XFreeFontInfo_PROC = (PFN_XFreeFontInfo_PROC) dlsym(libx11, "XFreeFontInfo");
    XFreeFontNames_PROC = (PFN_XFreeFontNames_PROC) dlsym(libx11, "XFreeFontNames");
    XFreeFontPath_PROC = (PFN_XFreeFontPath_PROC) dlsym(libx11, "XFreeFontPath");
    XFreeFontSet_PROC = (PFN_XFreeFontSet_PROC) dlsym(libx11, "XFreeFontSet");
    XFreeGC_PROC = (PFN_XFreeGC_PROC) dlsym(libx11, "XFreeGC");
    XFreeModifiermap_PROC = (PFN_XFreeModifiermap_PROC) dlsym(libx11, "XFreeModifiermap");
    XFreePixmap_PROC = (PFN_XFreePixmap_PROC) dlsym(libx11, "XFreePixmap");
    XFreeStringList_PROC = (PFN_XFreeStringList_PROC) dlsym(libx11, "XFreeStringList");
    XFreeThreads_PROC = (PFN_XFreeThreads_PROC) dlsym(libx11, "XFreeThreads");
    XGContextFromGC_PROC = (PFN_XGContextFromGC_PROC) dlsym(libx11, "XGContextFromGC");
    XGeometry_PROC = (PFN_XGeometry_PROC) dlsym(libx11, "XGeometry");
    XGetAtomName_PROC = (PFN_XGetAtomName_PROC) dlsym(libx11, "XGetAtomName");
    XGetAtomNames_PROC = (PFN_XGetAtomNames_PROC) dlsym(libx11, "XGetAtomNames");
    XGetCommand_PROC = (PFN_XGetCommand_PROC) dlsym(libx11, "XGetCommand");
    XGetDefault_PROC = (PFN_XGetDefault_PROC) dlsym(libx11, "XGetDefault");
    XGetErrorDatabaseText_PROC = (PFN_XGetErrorDatabaseText_PROC) dlsym(libx11, "XGetErrorDatabaseText");
    XGetErrorText_PROC = (PFN_XGetErrorText_PROC) dlsym(libx11, "XGetErrorText");
    XGetEventData_PROC = (PFN_XGetEventData_PROC) dlsym(libx11, "XGetEventData");
    XGetFontPath_PROC = (PFN_XGetFontPath_PROC) dlsym(libx11, "XGetFontPath");
    XGetFontProperty_PROC = (PFN_XGetFontProperty_PROC) dlsym(libx11, "XGetFontProperty");
    XGetGCValues_PROC = (PFN_XGetGCValues_PROC) dlsym(libx11, "XGetGCValues");
    XGetGeometry_PROC = (PFN_XGetGeometry_PROC) dlsym(libx11, "XGetGeometry");
    XGetICValues_PROC = (PFN_XGetICValues_PROC) dlsym(libx11, "XGetICValues");
    XGetIMValues_PROC = (PFN_XGetIMValues_PROC) dlsym(libx11, "XGetIMValues");
    XGetIconName_PROC = (PFN_XGetIconName_PROC) dlsym(libx11, "XGetIconName");
    XGetImage_PROC = (PFN_XGetImage_PROC) dlsym(libx11, "XGetImage");
    XGetInputFocus_PROC = (PFN_XGetInputFocus_PROC) dlsym(libx11, "XGetInputFocus");
    XGetKeyboardControl_PROC = (PFN_XGetKeyboardControl_PROC) dlsym(libx11, "XGetKeyboardControl");
    XGetKeyboardMapping_PROC = (PFN_XGetKeyboardMapping_PROC) dlsym(libx11, "XGetKeyboardMapping");
    XGetModifierMapping_PROC = (PFN_XGetModifierMapping_PROC) dlsym(libx11, "XGetModifierMapping");
    XGetMotionEvents_PROC = (PFN_XGetMotionEvents_PROC) dlsym(libx11, "XGetMotionEvents");
    XGetOCValues_PROC = (PFN_XGetOCValues_PROC) dlsym(libx11, "XGetOCValues");
    XGetOMValues_PROC = (PFN_XGetOMValues_PROC) dlsym(libx11, "XGetOMValues");
    XGetPointerControl_PROC = (PFN_XGetPointerControl_PROC) dlsym(libx11, "XGetPointerControl");
    XGetPointerMapping_PROC = (PFN_XGetPointerMapping_PROC) dlsym(libx11, "XGetPointerMapping");
    XGetScreenSaver_PROC = (PFN_XGetScreenSaver_PROC) dlsym(libx11, "XGetScreenSaver");
    XGetSelectionOwner_PROC = (PFN_XGetSelectionOwner_PROC) dlsym(libx11, "XGetSelectionOwner");
    XGetSubImage_PROC = (PFN_XGetSubImage_PROC) dlsym(libx11, "XGetSubImage");
    XGetTransientForHint_PROC = (PFN_XGetTransientForHint_PROC) dlsym(libx11, "XGetTransientForHint");
    XGetWMColorwindow_maps_PROC = (PFN_XGetWMColorwindow_maps_PROC) dlsym(libx11, "XGetWMColorwindow_maps");
    XGetWMProtocols_PROC = (PFN_XGetWMProtocols_PROC) dlsym(libx11, "XGetWMProtocols");
    XGetWindowAttributes_PROC = (PFN_XGetWindowAttributes_PROC) dlsym(libx11, "XGetWindowAttributes");
    XGetWindowProperty_PROC = (PFN_XGetWindowProperty_PROC) dlsym(libx11, "XGetWindowProperty");
    XGrabButton_PROC = (PFN_XGrabButton_PROC) dlsym(libx11, "XGrabButton");
    XGrabKey_PROC = (PFN_XGrabKey_PROC) dlsym(libx11, "XGrabKey");
    XGrabKeyboard_PROC = (PFN_XGrabKeyboard_PROC) dlsym(libx11, "XGrabKeyboard");
    XGrabPointer_PROC = (PFN_XGrabPointer_PROC) dlsym(libx11, "XGrabPointer");
    XGrabServer_PROC = (PFN_XGrabServer_PROC) dlsym(libx11, "XGrabServer");
    XHeightMMOfScreen_PROC = (PFN_XHeightMMOfScreen_PROC) dlsym(libx11, "XHeightMMOfScreen");
    XHeightOfScreen_PROC = (PFN_XHeightOfScreen_PROC) dlsym(libx11, "XHeightOfScreen");
    XIMOfIC_PROC = (PFN_XIMOfIC_PROC) dlsym(libx11, "XIMOfIC");
    XIconifyWindow_PROC = (PFN_XIconifyWindow_PROC) dlsym(libx11, "XIconifyWindow");
    XIfEvent_PROC = (PFN_XIfEvent_PROC) dlsym(libx11, "XIfEvent");
    XImageByteOrder_PROC = (PFN_XImageByteOrder_PROC) dlsym(libx11, "XImageByteOrder");
    XInitExtension_PROC = (PFN_XInitExtension_PROC) dlsym(libx11, "XInitExtension");
    XInitImage_PROC = (PFN_XInitImage_PROC) dlsym(libx11, "XInitImage");
    XInitThreads_PROC = (PFN_XInitThreads_PROC) dlsym(libx11, "XInitThreads");
    XInsertModifiermapEntry_PROC = (PFN_XInsertModifiermapEntry_PROC) dlsym(libx11, "XInsertModifiermapEntry");
    XInstallColormap_PROC = (PFN_XInstallColormap_PROC) dlsym(libx11, "XInstallColormap");
    XInternAtom_PROC = (PFN_XInternAtom_PROC) dlsym(libx11, "XInternAtom");
    XInternAtoms_PROC = (PFN_XInternAtoms_PROC) dlsym(libx11, "XInternAtoms");
    XInternalConnectionNumbers_PROC = (PFN_XInternalConnectionNumbers_PROC) dlsym(libx11, "XInternalConnectionNumbers");
    XKeycodeToKeysym_PROC = (PFN_XKeycodeToKeysym_PROC) dlsym(libx11, "XKeycodeToKeysym");
    XKeysymToKeycode_PROC = (PFN_XKeysymToKeycode_PROC) dlsym(libx11, "XKeysymToKeycode");
    XKeysymToString_PROC = (PFN_XKeysymToString_PROC) dlsym(libx11, "XKeysymToString");
    XKillClient_PROC = (PFN_XKillClient_PROC) dlsym(libx11, "XKillClient");
    XLastKnownRequestProcessed_PROC = (PFN_XLastKnownRequestProcessed_PROC) dlsym(libx11, "XLastKnownRequestProcessed");
    XListDepths_PROC = (PFN_XListDepths_PROC) dlsym(libx11, "XListDepths");
    XListExtensions_PROC = (PFN_XListExtensions_PROC) dlsym(libx11, "XListExtensions");
    XListFonts_PROC = (PFN_XListFonts_PROC) dlsym(libx11, "XListFonts");
    XListFontsWithInfo_PROC = (PFN_XListFontsWithInfo_PROC) dlsym(libx11, "XListFontsWithInfo");
    XListHosts_PROC = (PFN_XListHosts_PROC) dlsym(libx11, "XListHosts");
    XListInstalledColormaps_PROC = (PFN_XListInstalledColormaps_PROC) dlsym(libx11, "XListInstalledColormaps");
    XListPixmapFormats_PROC = (PFN_XListPixmapFormats_PROC) dlsym(libx11, "XListPixmapFormats");
    XListProperties_PROC = (PFN_XListProperties_PROC) dlsym(libx11, "XListProperties");
    XLoadFont_PROC = (PFN_XLoadFont_PROC) dlsym(libx11, "XLoadFont");
    XLoadQueryFont_PROC = (PFN_XLoadQueryFont_PROC) dlsym(libx11, "XLoadQueryFont");
    XLocaleOfFontSet_PROC = (PFN_XLocaleOfFontSet_PROC) dlsym(libx11, "XLocaleOfFontSet");
    XLocaleOfIM_PROC = (PFN_XLocaleOfIM_PROC) dlsym(libx11, "XLocaleOfIM");
    XLocaleOfOM_PROC = (PFN_XLocaleOfOM_PROC) dlsym(libx11, "XLocaleOfOM");
    XLockDisplay_PROC = (PFN_XLockDisplay_PROC) dlsym(libx11, "XLockDisplay");
    XLookupColor_PROC = (PFN_XLookupColor_PROC) dlsym(libx11, "XLookupColor");
    XLookupKeysym_PROC = (PFN_XLookupKeysym_PROC) dlsym(libx11, "XLookupKeysym");
    XLowerWindow_PROC = (PFN_XLowerWindow_PROC) dlsym(libx11, "XLowerWindow");
    XMapRaised_PROC = (PFN_XMapRaised_PROC) dlsym(libx11, "XMapRaised");
    XMapSubwindows_PROC = (PFN_XMapSubwindows_PROC) dlsym(libx11, "XMapSubwindows");
    XMapWindow_PROC = (PFN_XMapWindow_PROC) dlsym(libx11, "XMapWindow");
    XMaskEvent_PROC = (PFN_XMaskEvent_PROC) dlsym(libx11, "XMaskEvent");
    XMaxCmapsOfScreen_PROC = (PFN_XMaxCmapsOfScreen_PROC) dlsym(libx11, "XMaxCmapsOfScreen");
    XMaxRequestSize_PROC = (PFN_XMaxRequestSize_PROC) dlsym(libx11, "XMaxRequestSize");
    XMinCmapsOfScreen_PROC = (PFN_XMinCmapsOfScreen_PROC) dlsym(libx11, "XMinCmapsOfScreen");
    XMoveResizeWindow_PROC = (PFN_XMoveResizeWindow_PROC) dlsym(libx11, "XMoveResizeWindow");
    XMoveWindow_PROC = (PFN_XMoveWindow_PROC) dlsym(libx11, "XMoveWindow");
    XNewModifiermap_PROC = (PFN_XNewModifiermap_PROC) dlsym(libx11, "XNewModifiermap");
    XNextEvent_PROC = (PFN_XNextEvent_PROC) dlsym(libx11, "XNextEvent");
    XNextRequest_PROC = (PFN_XNextRequest_PROC) dlsym(libx11, "XNextRequest");
    XNoOp_PROC = (PFN_XNoOp_PROC) dlsym(libx11, "XNoOp");
    XOMOfOC_PROC = (PFN_XOMOfOC_PROC) dlsym(libx11, "XOMOfOC");
    XOpenDisplay_PROC = (PFN_XOpenDisplay_PROC) dlsym(libx11, "XOpenDisplay");
    XOpenIM_PROC = (PFN_XOpenIM_PROC) dlsym(libx11, "XOpenIM");
    XOpenOM_PROC = (PFN_XOpenOM_PROC) dlsym(libx11, "XOpenOM");
    XParseColor_PROC = (PFN_XParseColor_PROC) dlsym(libx11, "XParseColor");
    XParseGeometry_PROC = (PFN_XParseGeometry_PROC) dlsym(libx11, "XParseGeometry");
    XPeekEvent_PROC = (PFN_XPeekEvent_PROC) dlsym(libx11, "XPeekEvent");
    XPeekIfEvent_PROC = (PFN_XPeekIfEvent_PROC) dlsym(libx11, "XPeekIfEvent");
    XPending_PROC = (PFN_XPending_PROC) dlsym(libx11, "XPending");
    XPlanesOfScreen_PROC = (PFN_XPlanesOfScreen_PROC) dlsym(libx11, "XPlanesOfScreen");
    XProcessInternalConnection_PROC = (PFN_XProcessInternalConnection_PROC) dlsym(libx11, "XProcessInternalConnection");
    XProtocolRevision_PROC = (PFN_XProtocolRevision_PROC) dlsym(libx11, "XProtocolRevision");
    XProtocolVersion_PROC = (PFN_XProtocolVersion_PROC) dlsym(libx11, "XProtocolVersion");
    XPutBackEvent_PROC = (PFN_XPutBackEvent_PROC) dlsym(libx11, "XPutBackEvent");
    XPutImage_PROC = (PFN_XPutImage_PROC) dlsym(libx11, "XPutImage");
    XQLength_PROC = (PFN_XQLength_PROC) dlsym(libx11, "XQLength");
    XQueryBestCursor_PROC = (PFN_XQueryBestCursor_PROC) dlsym(libx11, "XQueryBestCursor");
    XQueryBestSize_PROC = (PFN_XQueryBestSize_PROC) dlsym(libx11, "XQueryBestSize");
    XQueryBestStipple_PROC = (PFN_XQueryBestStipple_PROC) dlsym(libx11, "XQueryBestStipple");
    XQueryBestTile_PROC = (PFN_XQueryBestTile_PROC) dlsym(libx11, "XQueryBestTile");
    XQueryColor_PROC = (PFN_XQueryColor_PROC) dlsym(libx11, "XQueryColor");
    XQueryColors_PROC = (PFN_XQueryColors_PROC) dlsym(libx11, "XQueryColors");
    XQueryExtension_PROC = (PFN_XQueryExtension_PROC) dlsym(libx11, "XQueryExtension");
    XQueryFont_PROC = (PFN_XQueryFont_PROC) dlsym(libx11, "XQueryFont");
    XQueryKeymap_PROC = (PFN_XQueryKeymap_PROC) dlsym(libx11, "XQueryKeymap");
    XQueryPointer_PROC = (PFN_XQueryPointer_PROC) dlsym(libx11, "XQueryPointer");
    XQueryTextExtents_PROC = (PFN_XQueryTextExtents_PROC) dlsym(libx11, "XQueryTextExtents");
    XQueryTextExtents16_PROC = (PFN_XQueryTextExtents16_PROC) dlsym(libx11, "XQueryTextExtents16");
    XQueryTree_PROC = (PFN_XQueryTree_PROC) dlsym(libx11, "XQueryTree");
    XRaiseWindow_PROC = (PFN_XRaiseWindow_PROC) dlsym(libx11, "XRaiseWindow");
    XReadBitmapFile_PROC = (PFN_XReadBitmapFile_PROC) dlsym(libx11, "XReadBitmapFile");
    XReadBitmapFileData_PROC = (PFN_XReadBitmapFileData_PROC) dlsym(libx11, "XReadBitmapFileData");
    XRebindKeysym_PROC = (PFN_XRebindKeysym_PROC) dlsym(libx11, "XRebindKeysym");
    XRecolorCursor_PROC = (PFN_XRecolorCursor_PROC) dlsym(libx11, "XRecolorCursor");
    XReconfigureWMWindow_PROC = (PFN_XReconfigureWMWindow_PROC) dlsym(libx11, "XReconfigureWMWindow");
    XRefreshKeyboardMapping_PROC = (PFN_XRefreshKeyboardMapping_PROC) dlsym(libx11, "XRefreshKeyboardMapping");
    XRegisterIMInstantiateCallback_PROC = (PFN_XRegisterIMInstantiateCallback_PROC) dlsym(libx11, "XRegisterIMInstantiateCallback");
    XRemoveConnectionWatch_PROC = (PFN_XRemoveConnectionWatch_PROC) dlsym(libx11, "XRemoveConnectionWatch");
    XRemoveFromSaveSet_PROC = (PFN_XRemoveFromSaveSet_PROC) dlsym(libx11, "XRemoveFromSaveSet");
    XRemoveHost_PROC = (PFN_XRemoveHost_PROC) dlsym(libx11, "XRemoveHost");
    XRemoveHosts_PROC = (PFN_XRemoveHosts_PROC) dlsym(libx11, "XRemoveHosts");
    XReparentWindow_PROC = (PFN_XReparentWindow_PROC) dlsym(libx11, "XReparentWindow");
    XResetScreenSaver_PROC = (PFN_XResetScreenSaver_PROC) dlsym(libx11, "XResetScreenSaver");
    XResizeWindow_PROC = (PFN_XResizeWindow_PROC) dlsym(libx11, "XResizeWindow");
    XResourceManagerString_PROC = (PFN_XResourceManagerString_PROC) dlsym(libx11, "XResourceManagerString");
    XRestackWindows_PROC = (PFN_XRestackWindows_PROC) dlsym(libx11, "XRestackWindows");
    XRootWindow_PROC = (PFN_XRootWindow_PROC) dlsym(libx11, "XRootWindow");
    XRootWindowOfScreen_PROC = (PFN_XRootWindowOfScreen_PROC) dlsym(libx11, "XRootWindowOfScreen");
    XRotateBuffers_PROC = (PFN_XRotateBuffers_PROC) dlsym(libx11, "XRotateBuffers");
    XRotateWindowProperties_PROC = (PFN_XRotateWindowProperties_PROC) dlsym(libx11, "XRotateWindowProperties");
    XScreenCount_PROC = (PFN_XScreenCount_PROC) dlsym(libx11, "XScreenCount");
    XScreenNumberOfScreen_PROC = (PFN_XScreenNumberOfScreen_PROC) dlsym(libx11, "XScreenNumberOfScreen");
    XScreenOfDisplay_PROC = (PFN_XScreenOfDisplay_PROC) dlsym(libx11, "XScreenOfDisplay");
    XScreenResourceString_PROC = (PFN_XScreenResourceString_PROC) dlsym(libx11, "XScreenResourceString");
    XSelectInput_PROC = (PFN_XSelectInput_PROC) dlsym(libx11, "XSelectInput");
    XSendEvent_PROC = (PFN_XSendEvent_PROC) dlsym(libx11, "XSendEvent");
    XServerVendor_PROC = (PFN_XServerVendor_PROC) dlsym(libx11, "XServerVendor");
    XSetAccessControl_PROC = (PFN_XSetAccessControl_PROC) dlsym(libx11, "XSetAccessControl");
    XSetArcMode_PROC = (PFN_XSetArcMode_PROC) dlsym(libx11, "XSetArcMode");
    XSetAuthorization_PROC = (PFN_XSetAuthorization_PROC) dlsym(libx11, "XSetAuthorization");
    XSetBackground_PROC = (PFN_XSetBackground_PROC) dlsym(libx11, "XSetBackground");
    XSetClipMask_PROC = (PFN_XSetClipMask_PROC) dlsym(libx11, "XSetClipMask");
    XSetClipOrigin_PROC = (PFN_XSetClipOrigin_PROC) dlsym(libx11, "XSetClipOrigin");
    XSetClipRectangles_PROC = (PFN_XSetClipRectangles_PROC) dlsym(libx11, "XSetClipRectangles");
    XSetCloseDownMode_PROC = (PFN_XSetCloseDownMode_PROC) dlsym(libx11, "XSetCloseDownMode");
    XSetCommand_PROC = (PFN_XSetCommand_PROC) dlsym(libx11, "XSetCommand");
    XSetDashes_PROC = (PFN_XSetDashes_PROC) dlsym(libx11, "XSetDashes");
    XSetErrorHandler_PROC = (PFN_XSetErrorHandler_PROC) dlsym(libx11, "XSetErrorHandler");
    XSetFillRule_PROC = (PFN_XSetFillRule_PROC) dlsym(libx11, "XSetFillRule");
    XSetFillStyle_PROC = (PFN_XSetFillStyle_PROC) dlsym(libx11, "XSetFillStyle");
    XSetFont_PROC = (PFN_XSetFont_PROC) dlsym(libx11, "XSetFont");
    XSetFontPath_PROC = (PFN_XSetFontPath_PROC) dlsym(libx11, "XSetFontPath");
    XSetForeground_PROC = (PFN_XSetForeground_PROC) dlsym(libx11, "XSetForeground");
    XSetFunction_PROC = (PFN_XSetFunction_PROC) dlsym(libx11, "XSetFunction");
    XSetGraphicsExposures_PROC = (PFN_XSetGraphicsExposures_PROC) dlsym(libx11, "XSetGraphicsExposures");
    XSetICFocus_PROC = (PFN_XSetICFocus_PROC) dlsym(libx11, "XSetICFocus");
    XSetICValues_PROC = (PFN_XSetICValues_PROC) dlsym(libx11, "XSetICValues");
    XSetIMValues_PROC = (PFN_XSetIMValues_PROC) dlsym(libx11, "XSetIMValues");
    XSetIOErrorExitHandler_PROC = (PFN_XSetIOErrorExitHandler_PROC) dlsym(libx11, "XSetIOErrorExitHandler");
    XSetIOErrorHandler_PROC = (PFN_XSetIOErrorHandler_PROC) dlsym(libx11, "XSetIOErrorHandler");
    XSetIconName_PROC = (PFN_XSetIconName_PROC) dlsym(libx11, "XSetIconName");
    XSetInputFocus_PROC = (PFN_XSetInputFocus_PROC) dlsym(libx11, "XSetInputFocus");
    XSetLineAttributes_PROC = (PFN_XSetLineAttributes_PROC) dlsym(libx11, "XSetLineAttributes");
    XSetLocaleModifiers_PROC = (PFN_XSetLocaleModifiers_PROC) dlsym(libx11, "XSetLocaleModifiers");
    XSetModifierMapping_PROC = (PFN_XSetModifierMapping_PROC) dlsym(libx11, "XSetModifierMapping");
    XSetOCValues_PROC = (PFN_XSetOCValues_PROC) dlsym(libx11, "XSetOCValues");
    XSetOMValues_PROC = (PFN_XSetOMValues_PROC) dlsym(libx11, "XSetOMValues");
    XSetPlaneMask_PROC = (PFN_XSetPlaneMask_PROC) dlsym(libx11, "XSetPlaneMask");
    XSetPointerMapping_PROC = (PFN_XSetPointerMapping_PROC) dlsym(libx11, "XSetPointerMapping");
    XSetScreenSaver_PROC = (PFN_XSetScreenSaver_PROC) dlsym(libx11, "XSetScreenSaver");
    XSetSelectionOwner_PROC = (PFN_XSetSelectionOwner_PROC) dlsym(libx11, "XSetSelectionOwner");
    XSetState_PROC = (PFN_XSetState_PROC) dlsym(libx11, "XSetState");
    XSetStipple_PROC = (PFN_XSetStipple_PROC) dlsym(libx11, "XSetStipple");
    XSetSubwindowMode_PROC = (PFN_XSetSubwindowMode_PROC) dlsym(libx11, "XSetSubwindowMode");
    XSetTSOrigin_PROC = (PFN_XSetTSOrigin_PROC) dlsym(libx11, "XSetTSOrigin");
    XSetTile_PROC = (PFN_XSetTile_PROC) dlsym(libx11, "XSetTile");
    XSetTransientForHint_PROC = (PFN_XSetTransientForHint_PROC) dlsym(libx11, "XSetTransientForHint");
    XSetWMColorwindow_maps_PROC = (PFN_XSetWMColorwindow_maps_PROC) dlsym(libx11, "XSetWMColorwindow_maps");
    XSetWMProtocols_PROC = (PFN_XSetWMProtocols_PROC) dlsym(libx11, "XSetWMProtocols");
    XSetWindowBackground_PROC = (PFN_XSetWindowBackground_PROC) dlsym(libx11, "XSetWindowBackground");
    XSetWindowBackgroundPixmap_PROC = (PFN_XSetWindowBackgroundPixmap_PROC) dlsym(libx11, "XSetWindowBackgroundPixmap");
    XSetWindowBorder_PROC = (PFN_XSetWindowBorder_PROC) dlsym(libx11, "XSetWindowBorder");
    XSetWindowBorderPixmap_PROC = (PFN_XSetWindowBorderPixmap_PROC) dlsym(libx11, "XSetWindowBorderPixmap");
    XSetWindowBorderWidth_PROC = (PFN_XSetWindowBorderWidth_PROC) dlsym(libx11, "XSetWindowBorderWidth");
    XSetWindowColormap_PROC = (PFN_XSetWindowColormap_PROC) dlsym(libx11, "XSetWindowColormap");
    XStoreBuffer_PROC = (PFN_XStoreBuffer_PROC) dlsym(libx11, "XStoreBuffer");
    XStoreBytes_PROC = (PFN_XStoreBytes_PROC) dlsym(libx11, "XStoreBytes");
    XStoreColor_PROC = (PFN_XStoreColor_PROC) dlsym(libx11, "XStoreColor");
    XStoreColors_PROC = (PFN_XStoreColors_PROC) dlsym(libx11, "XStoreColors");
    XStoreName_PROC = (PFN_XStoreName_PROC) dlsym(libx11, "XStoreName");
    XStoreNamedColor_PROC = (PFN_XStoreNamedColor_PROC) dlsym(libx11, "XStoreNamedColor");
    XStringToKeysym_PROC = (PFN_XStringToKeysym_PROC) dlsym(libx11, "XStringToKeysym");
    XSupportsLocale_PROC = (PFN_XSupportsLocale_PROC) dlsym(libx11, "XSupportsLocale");
    XSync_PROC = (PFN_XSync_PROC) dlsym(libx11, "XSync");
    XTextExtents_PROC = (PFN_XTextExtents_PROC) dlsym(libx11, "XTextExtents");
    XTextExtents16_PROC = (PFN_XTextExtents16_PROC) dlsym(libx11, "XTextExtents16");
    XTextWidth_PROC = (PFN_XTextWidth_PROC) dlsym(libx11, "XTextWidth");
    XTextWidth16_PROC = (PFN_XTextWidth16_PROC) dlsym(libx11, "XTextWidth16");
    XTranslateCoordinates_PROC = (PFN_XTranslateCoordinates_PROC) dlsym(libx11, "XTranslateCoordinates");
    XUndefineCursor_PROC = (PFN_XUndefineCursor_PROC) dlsym(libx11, "XUndefineCursor");
    XUngrabButton_PROC = (PFN_XUngrabButton_PROC) dlsym(libx11, "XUngrabButton");
    XUngrabKey_PROC = (PFN_XUngrabKey_PROC) dlsym(libx11, "XUngrabKey");
    XUngrabKeyboard_PROC = (PFN_XUngrabKeyboard_PROC) dlsym(libx11, "XUngrabKeyboard");
    XUngrabPointer_PROC = (PFN_XUngrabPointer_PROC) dlsym(libx11, "XUngrabPointer");
    XUngrabServer_PROC = (PFN_XUngrabServer_PROC) dlsym(libx11, "XUngrabServer");
    XUninstallColormap_PROC = (PFN_XUninstallColormap_PROC) dlsym(libx11, "XUninstallColormap");
    XUnloadFont_PROC = (PFN_XUnloadFont_PROC) dlsym(libx11, "XUnloadFont");
    XUnlockDisplay_PROC = (PFN_XUnlockDisplay_PROC) dlsym(libx11, "XUnlockDisplay");
    XUnmapSubwindows_PROC = (PFN_XUnmapSubwindows_PROC) dlsym(libx11, "XUnmapSubwindows");
    XUnwindow_map_PROC = (PFN_XUnwindow_map_PROC) dlsym(libx11, "XUnwindow_map");
    XUnregisterIMInstantiateCallback_PROC = (PFN_XUnregisterIMInstantiateCallback_PROC) dlsym(libx11, "XUnregisterIMInstantiateCallback");
    XUnsetICFocus_PROC = (PFN_XUnsetICFocus_PROC) dlsym(libx11, "XUnsetICFocus");
    XVaCreateNestedList_PROC = (PFN_XVaCreateNestedList_PROC) dlsym(libx11, "XVaCreateNestedList");
    XVendorRelease_PROC = (PFN_XVendorRelease_PROC) dlsym(libx11, "XVendorRelease");
    XVisualIDFromVisual_PROC = (PFN_XVisualIDFromVisual_PROC) dlsym(libx11, "XVisualIDFromVisual");
    XWarpPointer_PROC = (PFN_XWarpPointer_PROC) dlsym(libx11, "XWarpPointer");
    XWhitePixel_PROC = (PFN_XWhitePixel_PROC) dlsym(libx11, "XWhitePixel");
    XWhitePixelOfScreen_PROC = (PFN_XWhitePixelOfScreen_PROC) dlsym(libx11, "XWhitePixelOfScreen");
    XWidthMMOfScreen_PROC = (PFN_XWidthMMOfScreen_PROC) dlsym(libx11, "XWidthMMOfScreen");
    XWidthOfScreen_PROC = (PFN_XWidthOfScreen_PROC) dlsym(libx11, "XWidthOfScreen");
    XWindowEvent_PROC = (PFN_XWindowEvent_PROC) dlsym(libx11, "XWindowEvent");
    XWithdrawWindow_PROC = (PFN_XWithdrawWindow_PROC) dlsym(libx11, "XWithdrawWindow");
    XWriteBitmapFile_PROC = (PFN_XWriteBitmapFile_PROC) dlsym(libx11, "XWriteBitmapFile");
    XmbDrawImageString_PROC = (PFN_XmbDrawImageString_PROC) dlsym(libx11, "XmbDrawImageString");
    XmbDrawString_PROC = (PFN_XmbDrawString_PROC) dlsym(libx11, "XmbDrawString");
    XmbDrawText_PROC = (PFN_XmbDrawText_PROC) dlsym(libx11, "XmbDrawText");
    XmbLookupString_PROC = (PFN_XmbLookupString_PROC) dlsym(libx11, "XmbLookupString");
    XmbResetIC_PROC = (PFN_XmbResetIC_PROC) dlsym(libx11, "XmbResetIC");
    XmbTextEscapement_PROC = (PFN_XmbTextEscapement_PROC) dlsym(libx11, "XmbTextEscapement");
    XmbTextExtents_PROC = (PFN_XmbTextExtents_PROC) dlsym(libx11, "XmbTextExtents");
    XmbTextPerCharExtents_PROC = (PFN_XmbTextPerCharExtents_PROC) dlsym(libx11, "XmbTextPerCharExtents");
    XrmInitialize_PROC = (PFN_XrmInitialize_PROC) dlsym(libx11, "XrmInitialize");
    Xutf8DrawImageString_PROC = (PFN_Xutf8DrawImageString_PROC) dlsym(libx11, "Xutf8DrawImageString");
    Xutf8DrawString_PROC = (PFN_Xutf8DrawString_PROC) dlsym(libx11, "Xutf8DrawString");
    Xutf8DrawText_PROC = (PFN_Xutf8DrawText_PROC) dlsym(libx11, "Xutf8DrawText");
    Xutf8LookupString_PROC = (PFN_Xutf8LookupString_PROC) dlsym(libx11, "Xutf8LookupString");
    Xutf8ResetIC_PROC = (PFN_Xutf8ResetIC_PROC) dlsym(libx11, "Xutf8ResetIC");
    Xutf8TextEscapement_PROC = (PFN_Xutf8TextEscapement_PROC) dlsym(libx11, "Xutf8TextEscapement");
    Xutf8TextExtents_PROC = (PFN_Xutf8TextExtents_PROC) dlsym(libx11, "Xutf8TextExtents");
    Xutf8TextPerCharExtents_PROC = (PFN_Xutf8TextPerCharExtents_PROC) dlsym(libx11, "Xutf8TextPerCharExtents");
    XwcDrawImageString_PROC = (PFN_XwcDrawImageString_PROC) dlsym(libx11, "XwcDrawImageString");
    XwcDrawString_PROC = (PFN_XwcDrawString_PROC) dlsym(libx11, "XwcDrawString");
    XwcDrawText_PROC = (PFN_XwcDrawText_PROC) dlsym(libx11, "XwcDrawText");
    XwcLookupString_PROC = (PFN_XwcLookupString_PROC) dlsym(libx11, "XwcLookupString");
    XwcResetIC_PROC = (PFN_XwcResetIC_PROC) dlsym(libx11, "XwcResetIC");
    XwcTextEscapement_PROC = (PFN_XwcTextEscapement_PROC) dlsym(libx11, "XwcTextEscapement");
    XwcTextExtents_PROC = (PFN_XwcTextExtents_PROC) dlsym(libx11, "XwcTextExtents");
    XwcTextPerCharExtents_PROC = (PFN_XwcTextPerCharExtents_PROC) dlsym(libx11, "XwcTextPerCharExtents");
    _Xmblen_PROC = (PFN__Xmblen_PROC) dlsym(libx11, "_Xmblen");
    _Xmbtowc_PROC = (PFN__Xmbtowc_PROC) dlsym(libx11, "_Xmbtowc");
    _Xwctomb_PROC = (PFN__Xwctomb_PROC) dlsym(libx11, "_Xwctomb");

    /* libX11: Xutil.h */
    XAllocClassHint_PROC = (PFN_XAllocClassHint_PROC) dlsym(libx11, "XAllocClassHint");
    XAllocIconSize_PROC = (PFN_XAllocIconSize_PROC) dlsym(libx11, "XAllocIconSize");
    XAllocSizeHints_PROC = (PFN_XAllocSizeHints_PROC) dlsym(libx11, "XAllocSizeHints");
    XAllocStandardColormap_PROC = (PFN_XAllocStandardColormap_PROC) dlsym(libx11, "XAllocStandardColormap");
    XAllocWMHints_PROC = (PFN_XAllocWMHints_PROC) dlsym(libx11, "XAllocWMHints");
    XClipBox_PROC = (PFN_XClipBox_PROC) dlsym(libx11, "XClipBox");
    XConvertCase_PROC = (PFN_XConvertCase_PROC) dlsym(libx11, "XConvertCase");
    XCreateRegion_PROC = (PFN_XCreateRegion_PROC) dlsym(libx11, "XCreateRegion");
    XDefaultString_PROC = (PFN_XDefaultString_PROC) dlsym(libx11, "XDefaultString");
    XDeleteContext_PROC = (PFN_XDeleteContext_PROC) dlsym(libx11, "XDeleteContext");
    XDestroyRegion_PROC = (PFN_XDestroyRegion_PROC) dlsym(libx11, "XDestroyRegion");
    XEmptyRegion_PROC = (PFN_XEmptyRegion_PROC) dlsym(libx11, "XEmptyRegion");
    XEqualRegion_PROC = (PFN_XEqualRegion_PROC) dlsym(libx11, "XEqualRegion");
    XFindContext_PROC = (PFN_XFindContext_PROC) dlsym(libx11, "XFindContext");
    XGetClassHint_PROC = (PFN_XGetClassHint_PROC) dlsym(libx11, "XGetClassHint");
    XGetIconSizes_PROC = (PFN_XGetIconSizes_PROC) dlsym(libx11, "XGetIconSizes");
    XGetNormalHints_PROC = (PFN_XGetNormalHints_PROC) dlsym(libx11, "XGetNormalHints");
    XGetRGBColormaps_PROC = (PFN_XGetRGBColormaps_PROC) dlsym(libx11, "XGetRGBColormaps");
    XGetSizeHints_PROC = (PFN_XGetSizeHints_PROC) dlsym(libx11, "XGetSizeHints");
    XGetStandardColormap_PROC = (PFN_XGetStandardColormap_PROC) dlsym(libx11, "XGetStandardColormap");
    XGetTextProperty_PROC = (PFN_XGetTextProperty_PROC) dlsym(libx11, "XGetTextProperty");
    XGetVisualInfo_PROC = (PFN_XGetVisualInfo_PROC) dlsym(libx11, "XGetVisualInfo");
    XGetWMClientMachine_PROC = (PFN_XGetWMClientMachine_PROC) dlsym(libx11, "XGetWMClientMachine");
    XGetWMHints_PROC = (PFN_XGetWMHints_PROC) dlsym(libx11, "XGetWMHints");
    XGetWMIconName_PROC = (PFN_XGetWMIconName_PROC) dlsym(libx11, "XGetWMIconName");
    XGetWMName_PROC = (PFN_XGetWMName_PROC) dlsym(libx11, "XGetWMName");
    XGetWMNormalHints_PROC = (PFN_XGetWMNormalHints_PROC) dlsym(libx11, "XGetWMNormalHints");
    XGetWMSizeHints_PROC = (PFN_XGetWMSizeHints_PROC) dlsym(libx11, "XGetWMSizeHints");
    XGetZoomHints_PROC = (PFN_XGetZoomHints_PROC) dlsym(libx11, "XGetZoomHints");
    XIntersectRegion_PROC = (PFN_XIntersectRegion_PROC) dlsym(libx11, "XIntersectRegion");
    XLookupString_PROC = (PFN_XLookupString_PROC) dlsym(libx11, "XLookupString");
    XMatchVisualInfo_PROC = (PFN_XMatchVisualInfo_PROC) dlsym(libx11, "XMatchVisualInfo");
    XOffsetRegion_PROC = (PFN_XOffsetRegion_PROC) dlsym(libx11, "XOffsetRegion");
    XPointInRegion_PROC = (PFN_XPointInRegion_PROC) dlsym(libx11, "XPointInRegion");
    XPolygonRegion_PROC = (PFN_XPolygonRegion_PROC) dlsym(libx11, "XPolygonRegion");
    XRectInRegion_PROC = (PFN_XRectInRegion_PROC) dlsym(libx11, "XRectInRegion");
    XSaveContext_PROC = (PFN_XSaveContext_PROC) dlsym(libx11, "XSaveContext");
    XSetClassHint_PROC = (PFN_XSetClassHint_PROC) dlsym(libx11, "XSetClassHint");
    XSetIconSizes_PROC = (PFN_XSetIconSizes_PROC) dlsym(libx11, "XSetIconSizes");
    XSetNormalHints_PROC = (PFN_XSetNormalHints_PROC) dlsym(libx11, "XSetNormalHints");
    XSetRGBColormaps_PROC = (PFN_XSetRGBColormaps_PROC) dlsym(libx11, "XSetRGBColormaps");
    XSetRegion_PROC = (PFN_XSetRegion_PROC) dlsym(libx11, "XSetRegion");
    XSetSizeHints_PROC = (PFN_XSetSizeHints_PROC) dlsym(libx11, "XSetSizeHints");
    XSetStandardColormap_PROC = (PFN_XSetStandardColormap_PROC) dlsym(libx11, "XSetStandardColormap");
    XSetStandardProperties_PROC = (PFN_XSetStandardProperties_PROC) dlsym(libx11, "XSetStandardProperties");
    XSetTextProperty_PROC = (PFN_XSetTextProperty_PROC) dlsym(libx11, "XSetTextProperty");
    XSetWMClientMachine_PROC = (PFN_XSetWMClientMachine_PROC) dlsym(libx11, "XSetWMClientMachine");
    XSetWMHints_PROC = (PFN_XSetWMHints_PROC) dlsym(libx11, "XSetWMHints");
    XSetWMIconName_PROC = (PFN_XSetWMIconName_PROC) dlsym(libx11, "XSetWMIconName");
    XSetWMName_PROC = (PFN_XSetWMName_PROC) dlsym(libx11, "XSetWMName");
    XSetWMNormalHints_PROC = (PFN_XSetWMNormalHints_PROC) dlsym(libx11, "XSetWMNormalHints");
    XSetWMProperties_PROC = (PFN_XSetWMProperties_PROC) dlsym(libx11, "XSetWMProperties");
    XSetWMSizeHints_PROC = (PFN_XSetWMSizeHints_PROC) dlsym(libx11, "XSetWMSizeHints");
    XSetZoomHints_PROC = (PFN_XSetZoomHints_PROC) dlsym(libx11, "XSetZoomHints");
    XShrinkRegion_PROC = (PFN_XShrinkRegion_PROC) dlsym(libx11, "XShrinkRegion");
    XStringListToTextProperty_PROC = (PFN_XStringListToTextProperty_PROC) dlsym(libx11, "XStringListToTextProperty");
    XSubtractRegion_PROC = (PFN_XSubtractRegion_PROC) dlsym(libx11, "XSubtractRegion");
    XTextPropertyToStringList_PROC = (PFN_XTextPropertyToStringList_PROC) dlsym(libx11, "XTextPropertyToStringList");
    XUnionRectWithRegion_PROC = (PFN_XUnionRectWithRegion_PROC) dlsym(libx11, "XUnionRectWithRegion");
    XUnionRegion_PROC = (PFN_XUnionRegion_PROC) dlsym(libx11, "XUnionRegion");
    XWMGeometry_PROC = (PFN_XWMGeometry_PROC) dlsym(libx11, "XWMGeometry");
    XXorRegion_PROC = (PFN_XXorRegion_PROC) dlsym(libx11, "XXorRegion");
    XmbSetWMProperties_PROC = (PFN_XmbSetWMProperties_PROC) dlsym(libx11, "XmbSetWMProperties");
    XmbTextListToTextProperty_PROC = (PFN_XmbTextListToTextProperty_PROC) dlsym(libx11, "XmbTextListToTextProperty");
    XmbTextPropertyToTextList_PROC = (PFN_XmbTextPropertyToTextList_PROC) dlsym(libx11, "XmbTextPropertyToTextList");
    Xutf8SetWMProperties_PROC = (PFN_Xutf8SetWMProperties_PROC) dlsym(libx11, "Xutf8SetWMProperties");
    Xutf8TextListToTextProperty_PROC = (PFN_Xutf8TextListToTextProperty_PROC) dlsym(libx11, "Xutf8TextListToTextProperty");
    Xutf8TextPropertyToTextList_PROC = (PFN_Xutf8TextPropertyToTextList_PROC) dlsym(libx11, "Xutf8TextPropertyToTextList");
    XwcFreeStringList_PROC = (PFN_XwcFreeStringList_PROC) dlsym(libx11, "XwcFreeStringList");
    XwcTextListToTextProperty_PROC = (PFN_XwcTextListToTextProperty_PROC) dlsym(libx11, "XwcTextListToTextProperty");
    XwcTextPropertyToTextList_PROC = (PFN_XwcTextPropertyToTextList_PROC) dlsym(libx11, "XwcTextPropertyToTextList");

    /* libX11: XKBlib.h */
    XkbAddDeviceLedInfo_PROC = (PFN_XkbAddDeviceLedInfo_PROC) dlsym(libx11, "XkbAddDeviceLedInfo");
    XkbAddKeyType_PROC = (PFN_XkbAddKeyType_PROC) dlsym(libx11, "XkbAddKeyType");
    XkbAllocClientMap_PROC = (PFN_XkbAllocClientMap_PROC) dlsym(libx11, "XkbAllocClientMap");
    XkbAllocCompatMap_PROC = (PFN_XkbAllocCompatMap_PROC) dlsym(libx11, "XkbAllocCompatMap");
    XkbAllocControls_PROC = (PFN_XkbAllocControls_PROC) dlsym(libx11, "XkbAllocControls");
    XkbAllocDeviceInfo_PROC = (PFN_XkbAllocDeviceInfo_PROC) dlsym(libx11, "XkbAllocDeviceInfo");
    XkbAllocIndicatorMaps_PROC = (PFN_XkbAllocIndicatorMaps_PROC) dlsym(libx11, "XkbAllocIndicatorMaps");
    XkbAllocKeyboard_PROC = (PFN_XkbAllocKeyboard_PROC) dlsym(libx11, "XkbAllocKeyboard");
    XkbAllocNames_PROC = (PFN_XkbAllocNames_PROC) dlsym(libx11, "XkbAllocNames");
    XkbAllocServerMap_PROC = (PFN_XkbAllocServerMap_PROC) dlsym(libx11, "XkbAllocServerMap");
    XkbApplyCompatMapToKey_PROC = (PFN_XkbApplyCompatMapToKey_PROC) dlsym(libx11, "XkbApplyCompatMapToKey");
    XkbApplyVirtualModChanges_PROC = (PFN_XkbApplyVirtualModChanges_PROC) dlsym(libx11, "XkbApplyVirtualModChanges");
    XkbBell_PROC = (PFN_XkbBell_PROC) dlsym(libx11, "XkbBell");
    XkbBellEvent_PROC = (PFN_XkbBellEvent_PROC) dlsym(libx11, "XkbBellEvent");
    XkbChangeDeviceInfo_PROC = (PFN_XkbChangeDeviceInfo_PROC) dlsym(libx11, "XkbChangeDeviceInfo");
    XkbChangeEnabledControls_PROC = (PFN_XkbChangeEnabledControls_PROC) dlsym(libx11, "XkbChangeEnabledControls");
    XkbChangeKeycodeRange_PROC = (PFN_XkbChangeKeycodeRange_PROC) dlsym(libx11, "XkbChangeKeycodeRange");
    XkbChangeMap_PROC = (PFN_XkbChangeMap_PROC) dlsym(libx11, "XkbChangeMap");
    XkbChangeNames_PROC = (PFN_XkbChangeNames_PROC) dlsym(libx11, "XkbChangeNames");
    XkbChangeTypesOfKey_PROC = (PFN_XkbChangeTypesOfKey_PROC) dlsym(libx11, "XkbChangeTypesOfKey");
    XkbComputeEffectiveMap_PROC = (PFN_XkbComputeEffectiveMap_PROC) dlsym(libx11, "XkbComputeEffectiveMap");
    XkbCopyKeyType_PROC = (PFN_XkbCopyKeyType_PROC) dlsym(libx11, "XkbCopyKeyType");
    XkbCopyKeyTypes_PROC = (PFN_XkbCopyKeyTypes_PROC) dlsym(libx11, "XkbCopyKeyTypes");
    XkbDeviceBell_PROC = (PFN_XkbDeviceBell_PROC) dlsym(libx11, "XkbDeviceBell");
    XkbDeviceBellEvent_PROC = (PFN_XkbDeviceBellEvent_PROC) dlsym(libx11, "XkbDeviceBellEvent");
    XkbForceBell_PROC = (PFN_XkbForceBell_PROC) dlsym(libx11, "XkbForceBell");
    XkbForceDeviceBell_PROC = (PFN_XkbForceDeviceBell_PROC) dlsym(libx11, "XkbForceDeviceBell");
    XkbFreeClientMap_PROC = (PFN_XkbFreeClientMap_PROC) dlsym(libx11, "XkbFreeClientMap");
    XkbFreeCompatMap_PROC = (PFN_XkbFreeCompatMap_PROC) dlsym(libx11, "XkbFreeCompatMap");
    XkbFreeComponentList_PROC = (PFN_XkbFreeComponentList_PROC) dlsym(libx11, "XkbFreeComponentList");
    XkbFreeControls_PROC = (PFN_XkbFreeControls_PROC) dlsym(libx11, "XkbFreeControls");
    XkbFreeDeviceInfo_PROC = (PFN_XkbFreeDeviceInfo_PROC) dlsym(libx11, "XkbFreeDeviceInfo");
    XkbFreeIndicatorMaps_PROC = (PFN_XkbFreeIndicatorMaps_PROC) dlsym(libx11, "XkbFreeIndicatorMaps");
    XkbFreeKeyboard_PROC = (PFN_XkbFreeKeyboard_PROC) dlsym(libx11, "XkbFreeKeyboard");
    XkbFreeNames_PROC = (PFN_XkbFreeNames_PROC) dlsym(libx11, "XkbFreeNames");
    XkbFreeServerMap_PROC = (PFN_XkbFreeServerMap_PROC) dlsym(libx11, "XkbFreeServerMap");
    XkbGetAutoRepeatRate_PROC = (PFN_XkbGetAutoRepeatRate_PROC) dlsym(libx11, "XkbGetAutoRepeatRate");
    XkbGetAutoResetControls_PROC = (PFN_XkbGetAutoResetControls_PROC) dlsym(libx11, "XkbGetAutoResetControls");
    XkbGetCompatMap_PROC = (PFN_XkbGetCompatMap_PROC) dlsym(libx11, "XkbGetCompatMap");
    XkbGetControls_PROC = (PFN_XkbGetControls_PROC) dlsym(libx11, "XkbGetControls");
    XkbGetDetectableAutoRepeat_PROC = (PFN_XkbGetDetectableAutoRepeat_PROC) dlsym(libx11, "XkbGetDetectableAutoRepeat");
    XkbGetDeviceButtonActions_PROC = (PFN_XkbGetDeviceButtonActions_PROC) dlsym(libx11, "XkbGetDeviceButtonActions");
    XkbGetDeviceInfo_PROC = (PFN_XkbGetDeviceInfo_PROC) dlsym(libx11, "XkbGetDeviceInfo");
    XkbGetDeviceInfoChanges_PROC = (PFN_XkbGetDeviceInfoChanges_PROC) dlsym(libx11, "XkbGetDeviceInfoChanges");
    XkbGetDeviceLedInfo_PROC = (PFN_XkbGetDeviceLedInfo_PROC) dlsym(libx11, "XkbGetDeviceLedInfo");
    XkbGetIndicatorMap_PROC = (PFN_XkbGetIndicatorMap_PROC) dlsym(libx11, "XkbGetIndicatorMap");
    XkbGetIndicatorState_PROC = (PFN_XkbGetIndicatorState_PROC) dlsym(libx11, "XkbGetIndicatorState");
    XkbGetKeyActions_PROC = (PFN_XkbGetKeyActions_PROC) dlsym(libx11, "XkbGetKeyActions");
    XkbGetKeyBehaviors_PROC = (PFN_XkbGetKeyBehaviors_PROC) dlsym(libx11, "XkbGetKeyBehaviors");
    XkbGetKeyExplicitComponents_PROC = (PFN_XkbGetKeyExplicitComponents_PROC) dlsym(libx11, "XkbGetKeyExplicitComponents");
    XkbGetKeyModifierMap_PROC = (PFN_XkbGetKeyModifierMap_PROC) dlsym(libx11, "XkbGetKeyModifierMap");
    XkbGetKeySyms_PROC = (PFN_XkbGetKeySyms_PROC) dlsym(libx11, "XkbGetKeySyms");
    XkbGetKeyTypes_PROC = (PFN_XkbGetKeyTypes_PROC) dlsym(libx11, "XkbGetKeyTypes");
    XkbGetKeyVirtualModMap_PROC = (PFN_XkbGetKeyVirtualModMap_PROC) dlsym(libx11, "XkbGetKeyVirtualModMap");
    XkbGetKeyboard_PROC = (PFN_XkbGetKeyboard_PROC) dlsym(libx11, "XkbGetKeyboard");
    XkbGetKeyboardByName_PROC = (PFN_XkbGetKeyboardByName_PROC) dlsym(libx11, "XkbGetKeyboardByName");
    XkbGetMap_PROC = (PFN_XkbGetMap_PROC) dlsym(libx11, "XkbGetMap");
    XkbGetMapChanges_PROC = (PFN_XkbGetMapChanges_PROC) dlsym(libx11, "XkbGetMapChanges");
    XkbGetNamedDeviceIndicator_PROC = (PFN_XkbGetNamedDeviceIndicator_PROC) dlsym(libx11, "XkbGetNamedDeviceIndicator");
    XkbGetNamedIndicator_PROC = (PFN_XkbGetNamedIndicator_PROC) dlsym(libx11, "XkbGetNamedIndicator");
    XkbGetNames_PROC = (PFN_XkbGetNames_PROC) dlsym(libx11, "XkbGetNames");
    XkbGetPerClientControls_PROC = (PFN_XkbGetPerClientControls_PROC) dlsym(libx11, "XkbGetPerClientControls");
    XkbGetState_PROC = (PFN_XkbGetState_PROC) dlsym(libx11, "XkbGetState");
    XkbGetUpdatedMap_PROC = (PFN_XkbGetUpdatedMap_PROC) dlsym(libx11, "XkbGetUpdatedMap");
    XkbGetVirtualMods_PROC = (PFN_XkbGetVirtualMods_PROC) dlsym(libx11, "XkbGetVirtualMods");
    XkbGetXlibControls_PROC = (PFN_XkbGetXlibControls_PROC) dlsym(libx11, "XkbGetXlibControls");
    XkbIgnoreExtension_PROC = (PFN_XkbIgnoreExtension_PROC) dlsym(libx11, "XkbIgnoreExtension");
    XkbInitCanonicalKeyTypes_PROC = (PFN_XkbInitCanonicalKeyTypes_PROC) dlsym(libx11, "XkbInitCanonicalKeyTypes");
    XkbKeyTypesForCoreSymbols_PROC = (PFN_XkbKeyTypesForCoreSymbols_PROC) dlsym(libx11, "XkbKeyTypesForCoreSymbols");
    XkbKeycodeToKeysym_PROC = (PFN_XkbKeycodeToKeysym_PROC) dlsym(libx11, "XkbKeycodeToKeysym");
    XkbKeysymToModifiers_PROC = (PFN_XkbKeysymToModifiers_PROC) dlsym(libx11, "XkbKeysymToModifiers");
    XkbLatchGroup_PROC = (PFN_XkbLatchGroup_PROC) dlsym(libx11, "XkbLatchGroup");
    XkbLatchModifiers_PROC = (PFN_XkbLatchModifiers_PROC) dlsym(libx11, "XkbLatchModifiers");
    XkbLibraryVersion_PROC = (PFN_XkbLibraryVersion_PROC) dlsym(libx11, "XkbLibraryVersion");
    XkbListComponents_PROC = (PFN_XkbListComponents_PROC) dlsym(libx11, "XkbListComponents");
    XkbLockGroup_PROC = (PFN_XkbLockGroup_PROC) dlsym(libx11, "XkbLockGroup");
    XkbLockModifiers_PROC = (PFN_XkbLockModifiers_PROC) dlsym(libx11, "XkbLockModifiers");
    XkbLookupKeyBinding_PROC = (PFN_XkbLookupKeyBinding_PROC) dlsym(libx11, "XkbLookupKeyBinding");
    XkbLookupKeySym_PROC = (PFN_XkbLookupKeySym_PROC) dlsym(libx11, "XkbLookupKeySym");
    XkbNoteControlsChanges_PROC = (PFN_XkbNoteControlsChanges_PROC) dlsym(libx11, "XkbNoteControlsChanges");
    XkbNoteDeviceChanges_PROC = (PFN_XkbNoteDeviceChanges_PROC) dlsym(libx11, "XkbNoteDeviceChanges");
    XkbNoteMapChanges_PROC = (PFN_XkbNoteMapChanges_PROC) dlsym(libx11, "XkbNoteMapChanges");
    XkbNoteNameChanges_PROC = (PFN_XkbNoteNameChanges_PROC) dlsym(libx11, "XkbNoteNameChanges");
    XkbOpenDisplay_PROC = (PFN_XkbOpenDisplay_PROC) dlsym(libx11, "XkbOpenDisplay");
    XkbQueryExtension_PROC = (PFN_XkbQueryExtension_PROC) dlsym(libx11, "XkbQueryExtension");
    XkbRefreshKeyboardMapping_PROC = (PFN_XkbRefreshKeyboardMapping_PROC) dlsym(libx11, "XkbRefreshKeyboardMapping");
    XkbResizeDeviceButtonActions_PROC = (PFN_XkbResizeDeviceButtonActions_PROC) dlsym(libx11, "XkbResizeDeviceButtonActions");
    XkbResizeKeyActions_PROC = (PFN_XkbResizeKeyActions_PROC) dlsym(libx11, "XkbResizeKeyActions");
    XkbResizeKeySyms_PROC = (PFN_XkbResizeKeySyms_PROC) dlsym(libx11, "XkbResizeKeySyms");
    XkbResizeKeyType_PROC = (PFN_XkbResizeKeyType_PROC) dlsym(libx11, "XkbResizeKeyType");
    XkbSelectEventDetails_PROC = (PFN_XkbSelectEventDetails_PROC) dlsym(libx11, "XkbSelectEventDetails");
    XkbSelectEvents_PROC = (PFN_XkbSelectEvents_PROC) dlsym(libx11, "XkbSelectEvents");
    XkbSetAtomFuncs_PROC = (PFN_XkbSetAtomFuncs_PROC) dlsym(libx11, "XkbSetAtomFuncs");
    XkbSetAutoRepeatRate_PROC = (PFN_XkbSetAutoRepeatRate_PROC) dlsym(libx11, "XkbSetAutoRepeatRate");
    XkbSetAutoResetControls_PROC = (PFN_XkbSetAutoResetControls_PROC) dlsym(libx11, "XkbSetAutoResetControls");
    XkbSetCompatMap_PROC = (PFN_XkbSetCompatMap_PROC) dlsym(libx11, "XkbSetCompatMap");
    XkbSetControls_PROC = (PFN_XkbSetControls_PROC) dlsym(libx11, "XkbSetControls");
    XkbSetDebuggingFlags_PROC = (PFN_XkbSetDebuggingFlags_PROC) dlsym(libx11, "XkbSetDebuggingFlags");
    XkbSetDetectableAutoRepeat_PROC = (PFN_XkbSetDetectableAutoRepeat_PROC) dlsym(libx11, "XkbSetDetectableAutoRepeat");
    XkbSetDeviceButtonActions_PROC = (PFN_XkbSetDeviceButtonActions_PROC) dlsym(libx11, "XkbSetDeviceButtonActions");
    XkbSetDeviceInfo_PROC = (PFN_XkbSetDeviceInfo_PROC) dlsym(libx11, "XkbSetDeviceInfo");
    XkbSetDeviceLedInfo_PROC = (PFN_XkbSetDeviceLedInfo_PROC) dlsym(libx11, "XkbSetDeviceLedInfo");
    XkbSetIgnoreLockMods_PROC = (PFN_XkbSetIgnoreLockMods_PROC) dlsym(libx11, "XkbSetIgnoreLockMods");
    XkbSetIndicatorMap_PROC = (PFN_XkbSetIndicatorMap_PROC) dlsym(libx11, "XkbSetIndicatorMap");
    XkbSetMap_PROC = (PFN_XkbSetMap_PROC) dlsym(libx11, "XkbSetMap");
    XkbSetNamedDeviceIndicator_PROC = (PFN_XkbSetNamedDeviceIndicator_PROC) dlsym(libx11, "XkbSetNamedDeviceIndicator");
    XkbSetNamedIndicator_PROC = (PFN_XkbSetNamedIndicator_PROC) dlsym(libx11, "XkbSetNamedIndicator");
    XkbSetNames_PROC = (PFN_XkbSetNames_PROC) dlsym(libx11, "XkbSetNames");
    XkbSetPerClientControls_PROC = (PFN_XkbSetPerClientControls_PROC) dlsym(libx11, "XkbSetPerClientControls");
    XkbSetServerInternalMods_PROC = (PFN_XkbSetServerInternalMods_PROC) dlsym(libx11, "XkbSetServerInternalMods");
    XkbSetXlibControls_PROC = (PFN_XkbSetXlibControls_PROC) dlsym(libx11, "XkbSetXlibControls");
    XkbToControl_PROC = (PFN_XkbToControl_PROC) dlsym(libx11, "XkbToControl");
    XkbTranslateKeyCode_PROC = (PFN_XkbTranslateKeyCode_PROC) dlsym(libx11, "XkbTranslateKeyCode");
    XkbTranslateKeySym_PROC = (PFN_XkbTranslateKeySym_PROC) dlsym(libx11, "XkbTranslateKeySym");
    XkbUpdateActionVirtualMods_PROC = (PFN_XkbUpdateActionVirtualMods_PROC) dlsym(libx11, "XkbUpdateActionVirtualMods");
    XkbUpdateKeyTypeVirtualMods_PROC = (PFN_XkbUpdateKeyTypeVirtualMods_PROC) dlsym(libx11, "XkbUpdateKeyTypeVirtualMods");
    XkbUpdateMapFromCore_PROC = (PFN_XkbUpdateMapFromCore_PROC) dlsym(libx11, "XkbUpdateMapFromCore");
    XkbUseExtension_PROC = (PFN_XkbUseExtension_PROC) dlsym(libx11, "XkbUseExtension");
    XkbVirtualModsToReal_PROC = (PFN_XkbVirtualModsToReal_PROC) dlsym(libx11, "XkbVirtualModsToReal");
    XkbXlibControlsImplemented_PROC = (PFN_XkbXlibControlsImplemented_PROC) dlsym(libx11, "XkbXlibControlsImplemented");

    /* }}} */

    x11->handle = libx11;

    /* return the result */
    lib->x11 = x11;
    
    /* success */
    return (1);
}


WININT int __win_x11_quit(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* references */
    struct _window_h_x11 *x11 = lib->x11; 
    if (!x11) { return (0); }

    /* close IPC window */
    XDestroyWindow(x11->dpy,
                   x11->ipc);

    /* success */
    return (1);
}


WININT int __win_x11_unload(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    struct _window_h_x11 *x11 = lib->x11;
    if (!x11) { return (0); }

    XCloseDisplay(x11->dpy);

    /* release X11 module */
    if (x11->handle) { dlclose(x11->handle), x11->handle = 0; }

    /* release 'x11' */
    free(x11);

    /* success */
    return (1);
}


WININT int __win_x11_window_create(struct _window_h *lib, struct _window_h_window *win, const size_t width, const size_t height, const char *title) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }
    
    /* xlib references */
    Display *dpy = lib->x11->dpy;
    Window  root = lib->x11->root;
    
    int screen = DefaultScreen(dpy);

    /* alloc new 'x11' window object */
    struct _window_h_window_x11 *x11 = calloc(1, sizeof(struct _window_h_window_x11));
    if (!x11) { return (0); }

    /* get 'depth' and 'visual' */
    Visual *visual = 0;
    int depth = 0;
    if (win->attrib.api == WINDOW_API_OPENGL ||
        win->attrib.api == WINDOW_API_OPENGLES
    ) {
        /* get 'visualid' */
        int visualid = 0;
        if (!lib->platform.gl_choose_config(lib) ||
            !lib->platform.gl_get_visual(lib, &visualid)
        ) {
            free(x11); return (0);
        }

        /* create desired XVisualInfo */
        XVisualInfo desired = {
            .visualid = visualid,
            .screen = screen
        };

        /* get XVisualInfo based on 'desired' */
        int count = 0;
        XVisualInfo *vi = XGetVisualInfo(lib->x11->dpy, VisualScreenMask | VisualIDMask, &desired, &count);
        if (!vi) { return (0); }

        /* get 'visual' from 'vi' */
        visual = vi->visual;

        /* get 'depth' value from 'vi' */
        depth = vi->depth;

        /* release 'vi' */
        XFree(vi), vi = 0;
    }

    /* fallback to default 'visual' and 'depth' values */
    if (!visual) {
        visual = DefaultVisual(dpy, screen);
        depth  = DefaultDepth(dpy, screen);
    }

    /* create XSetWindowAttributes */
    XSetWindowAttributes attr = { 0 };
    attr.bit_gravity = StaticGravity;
    attr.colormap = XCreateColormap(dpy, root, visual, AllocNone);
    attr.event_mask = StructureNotifyMask | SubstructureNotifyMask |
                      KeyPressMask | KeyReleaseMask |
                      PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                      ExposureMask | FocusChangeMask | VisibilityChangeMask |
                      EnterWindowMask | LeaveWindowMask | PropertyChangeMask;

    /* create client window */
    Window handle = XCreateWindow(dpy, root,
                                  0, 0,
                                  width, height,
                                  0,
                                  depth,
                                  InputOutput,
                                  visual,
                                  CWBorderPixel | CWColormap | CWEventMask | CWBackPixel,
                                  &attr);
    if (!handle) { return (0); }

    /* set the title */
    XStoreName(dpy, handle, title);

    /* set WM protocols atoms */
    Atom WM_PROTOCOLS = lib->x11->WM_PROTOCOLS;
    XSetWMProtocols(dpy, handle, &WM_PROTOCOLS, 1);
    
    Atom WM_DELETE_WINDOW = lib->x11->WM_DELETE_WINDOW;
    XSetWMProtocols(dpy, handle, &WM_DELETE_WINDOW, 1);

    /* set 'x11' members */
    x11->handle = handle;
    x11->visual = visual;

    /* return the result */
    win->x11 = x11;

    /* set the 'win' members */
    win->handle = (uint64_t) handle;

    /* success */
    return (1);
}


WININT int __win_x11_window_destroy(struct _window_h *lib, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* destroy client */
    XDestroyWindow(lib->x11->dpy,
                   win->handle);

    /* deallocate window object */
    free(win->x11);

    /* success */
    return (1);
}


WININT int __win_x11_window_map(struct _window_h *lib, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* map window */
    XMapWindow(lib->x11->dpy,
               win->handle);

    /* success */
    return (1);
}


WININT int __win_x11_window_unmap(struct _window_h *lib, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* unmap window */
    XUnwindow_map(lib->x11->dpy,
                 win->handle);

    /* success */
    return (1);
}


WININT int __win_x11_window_get_size(struct _window_h *lib, struct _window_h_window *win, size_t *w_ptr, size_t *h_ptr) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* get window hints */
    XWindowAttributes attr = { 0 };
    if (!XGetWindowAttributes(lib->x11->dpy,
                              win->handle,
                              &attr)
    ) { return (0); }

    /* return values */
    if (w_ptr) { *w_ptr = attr.width; }
    if (h_ptr) { *h_ptr = attr.height; }

    /* success */
    return (1);
}


WININT int __win_x11_window_set_size(struct _window_h *lib, struct _window_h_window *win, const size_t w, const size_t h) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* resize window */
    if (!XResizeWindow(lib->x11->dpy,
                       win->handle,
                       w, h)
    ) { return (0); }

    /* success */
    return (1);
}


WININT int __win_x11_window_set_size_min(struct _window_h *lib, struct _window_h_window *win, const size_t w, const size_t h) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(lib->x11->dpy,
                      win->handle,
                      &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags |= PMinSize;
    hints.min_width  = w;
    hints.min_height = h;
    XSetWMNormalHints(lib->x11->dpy,
                      win->handle,
                      &hints);

    /* success */
    return (1);
}


WININT int __win_x11_window_set_size_max(struct _window_h *lib, struct _window_h_window *win, const size_t w, const size_t h) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* get WM normal hints */
    XSizeHints hints;
    int64_t supp;
    XGetWMNormalHints(lib->x11->dpy,
                      win->handle,
                      &hints, &supp);

    /* set new WM normal hints with position changed */
    hints.flags |= PMaxSize;
    hints.max_width  = w;
    hints.max_height = h;
    XSetWMNormalHints(lib->x11->dpy,
                      win->handle,
                      &hints);

    /* success */
    return (1);
}


WININT int __win_x11_window_get_position(struct _window_h *lib, struct _window_h_window *win, size_t *x_ptr, size_t *y_ptr) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* get window hints */
    XWindowAttributes attr = { 0 };
    if (!XGetWindowAttributes(lib->x11->dpy,
                              win->handle,
                              &attr)
    ) { return (0); }

    /* return values */
    if (x_ptr) { *x_ptr = attr.x; }
    if (y_ptr) { *y_ptr = attr.y; }

    /* success */
    return (1);
}


WININT int __win_x11_window_set_position(struct _window_h *lib, struct _window_h_window *win, const size_t x, const size_t y) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* resize window */
    if (!XMoveWindow(lib->x11->dpy,
                     win->handle,
                     x, y)
    ) { return (0); }

    /* success */
    return (1);
}


WININT int __win_x11_window_get_title(struct _window_h *lib, struct _window_h_window *win, char **t_ptr) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* fetch window title */
    if (!XFetchName(lib->x11->dpy,
                    win->handle, t_ptr)
    ) { return (0); }

    /* success */
    return (1);
}


WININT int __win_x11_window_set_title(struct _window_h *lib, struct _window_h_window *win, const char *t) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* fetch window title */
    if (!XStoreName(lib->x11->dpy,
                    win->handle, t)
    ) { return (0); }

    /* success */
    return (1);
}


WININT int __win_x11_context_create(struct _window_h *lib, struct _window_h_context *ctx, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }
            
    /* alloc new 'x11' object */
    struct _window_h_context_x11 *x11 = calloc(1, sizeof(struct _window_h_context_x11));
    if (!x11) { return (0); }

    /* create new 'GC' */
    x11->handle = XCreateGC(lib->x11->dpy,
                            win->handle,
                            0, 0);
    if (!x11->handle) {
        free(x11);
        return (0);
    }

    /* return 'x11' object */
    ctx->x11 = x11;

    /* success */
    return (1);
}


WININT int __win_x11_context_destroy(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
            
    /* release GC 'handle' */
    XFreeGC(lib->x11->dpy, ctx->x11->handle);

    /* release 'x11' */
    free(ctx->x11);
            
    /* success */
    return (1);
}


WININT int __win_x11_cursor_create(struct _window_h *lib, struct _window_h_cursor *cur, const uint8_t *data, const size_t width, const size_t height, const int xhot, const int yhot) {
    /* null-check */
    if (!lib) { return (0); }
    if (!cur) { return (0); }

    /* alloc new 'x11' object */
    struct _window_h_cursor_x11 *x11 = calloc(1, sizeof(struct _window_h_cursor_x11));
    if (!x11) { return (0); }

    /* create 'source' pixmap */
    Pixmap source = XCreateBitmapFromData(lib->x11->dpy,
                                          lib->x11->root,
                                          (char *) data,
                                          width, height);
    if (!source) { free(x11); return (0); }

    /* create 'foreground_color' and 'background_color' XColor components */
    XColor foreground_color = { .red   = 0xffff,
                                .green = 0xffff,
                                .blue  = 0xffff },
           background_color = { .red   = 0x0000,
                                .green = 0x0000,
                                .blue  = 0x0000 };

    Cursor handle = XCreatePixmapCursor(lib->x11->dpy,
                                        source, None,
                                        &foreground_color,
                                        &background_color,
                                        xhot, yhot);

    /* failure */
    if (!handle) { return (0); }

    /* release 'source' pixmap */
    XFreePixmap(lib->x11->dpy, source);

    /* return the result */
    x11->handle = handle; 
    cur->x11 = x11;

    /* set the 'cur' members */
    cur->handle = (uint64_t) handle;

    /* success */
    return (1);
}


WININT int __win_x11_cursor_destroy(struct _window_h *lib, struct _window_h_cursor *cur) {
    /* null-check */
    if (!lib) { return (0); }
    if (!cur) { return (0); }

    /* release 'cursor' */
    XFreeCursor(lib->x11->dpy,
                cur->handle);

    /* release 'x11' */
    free(cur->x11);

    /* success */
    return (1);
}


WININT int __win_x11_cursor_get_position(struct _window_h *lib, struct _window_h_window *win, size_t *x_ptr, size_t *y_ptr) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* get cursor position */
    Window root_return  = None,
           child_return = None;
    int root_x  = 0, root_y  = 0;
    int child_x = 0, child_y = 0;
    unsigned int mask_return = 0;
    if (!XQueryPointer(lib->x11->dpy,
                       win->x11->handle,
                       &root_return,
                       &child_return,
                       &root_x, &root_y,
                       &child_x, &child_y,
                       &mask_return)) { return (0); }

    /* return values */
    if (x_ptr) { *x_ptr = child_x; }
    if (y_ptr) { *y_ptr = child_y; }

    /* success */
    return (1);
}


WININT int __win_x11_cursor_set_position(struct _window_h *lib, struct _window_h_window *win, const size_t x, const size_t y) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    if (!XWarpPointer(lib->x11->dpy, None,
                      win->x11->handle,
                      0, 0, 0, 0,
                      x, y)) { return (0); }
    XFlush(lib->x11->dpy);

    /* success */
    return (1);
}


WININT int __win_x11_cursor_get_mode(struct _window_h *lib, struct _window_h_window *win, uint32_t *m_ptr) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* return result */
    if (m_ptr) {
        *m_ptr = win->cursor.attrib.mode;
    }
    
    /* success */
    return (1);
}


WININT int __win_x11_cursor_set_mode(struct _window_h *lib, struct _window_h_window *win, const uint32_t mode) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* only execute if window is focused */
    if (win->attrib.focused) {
        /* grab / ungrab the cursor */
        switch (mode) {
            case (WINDOW_CURSOR_MODE_NORMAL):
            case (WINDOW_CURSOR_MODE_HIDDEN): {
                XUngrabPointer(lib->x11->dpy, CurrentTime);
            } break;

            case (WINDOW_CURSOR_MODE_CENTERED):
            case (WINDOW_CURSOR_MODE_CAPTURED):
            case (WINDOW_CURSOR_MODE_DISABLED): {
                XGrabPointer(lib->x11->dpy, win->x11->handle, True,
                             ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                             GrabModeAsync, GrabModeAsync,
                             win->x11->handle, None, CurrentTime);
            } break;
        }
    }

    /* set cursor visibility */
    switch (mode) {
        case (WINDOW_CURSOR_MODE_NORMAL):
        case (WINDOW_CURSOR_MODE_CAPTURED):
        case (WINDOW_CURSOR_MODE_CENTERED): {
            /* define 'win' cursor as it's 'cursor.handle' */
            if (win->cursor.handle) {
                XDefineCursor(lib->x11->dpy,
                              win->x11->handle,
                              win->cursor.handle->x11->handle);
            }
            /* otherwise, undefine the cursor */
            else {
                XUndefineCursor(lib->x11->dpy,
                                win->x11->handle);
            }

        } break;

        case (WINDOW_CURSOR_MODE_HIDDEN):
        case (WINDOW_CURSOR_MODE_DISABLED): {
            XDefineCursor(lib->x11->dpy,
                          win->x11->handle,
                          lib->cursor.blank->x11->handle);
        } break;
    }
    
    /* success */
    return (1);
}


WININT int __win_x11_event_poll(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    XEvent xevent = { 0 };
    /* iterate until X11's queue is not empty */
    XPending(lib->x11->dpy);
    while (QLength(lib->x11->dpy)) {
        /* get the next event from queue */
        XNextEvent(lib->x11->dpy, &xevent);

        /* process upcoming events */
        __win_x11_event_process(lib, &xevent);
    }


    /* success */
    return (1);
}


WININT int __win_x11_event_wait(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* success */
    return (1);
}


WININT int __win_x11_copy(struct _window_h *lib, const uint32_t selection, const void *data, const size_t size) {
    /* null-check */
    if (!lib) { return (0); }
    
    /* references */
    struct _window_h_x11 *x11 = lib->x11; 
    if (!x11) { return (0); }

    /* get selection atom */
    Atom atom = 0;
    switch (selection) {
        case (WINDOW_SELECTION_PRIMARY):   { atom = XA_PRIMARY;     } break;
        case (WINDOW_SELECTION_SECONDARY): { atom = XA_SECONDARY;   } break;
        case (WINDOW_SELECTION_CLIPBOARD): { atom = x11->CLIPBOARD; } break;

        /* ... */
        default: { return (0); }
    }

    return (__win_x11_selection_set(lib, atom, data, size));
}


WININT int __win_x11_paste(struct _window_h *lib, const uint32_t selection, void **d_ptr, size_t *s_ptr) {
    /* null-check */
    if (!lib) { return (0); }
    
    /* references */
    struct _window_h_x11 *x11 = lib->x11; 
    if (!x11) { return (0); }

    /* get selection atom */
    Atom atom = 0;
    switch (selection) {
        case (WINDOW_SELECTION_PRIMARY):   { atom = XA_PRIMARY;     } break;
        case (WINDOW_SELECTION_SECONDARY): { atom = XA_SECONDARY;   } break;
        case (WINDOW_SELECTION_CLIPBOARD): { atom = x11->CLIPBOARD; } break;

        /* ... */
        default: { return (0); }
    }

    return (__win_x11_selection_get(lib, atom, d_ptr, s_ptr));
}

/* }}} */
# endif /* WINDOW_BACKEND_X11 */
#
# /* WINDOW_BACKEND_WAYLAND - Wayland implementation layer */
# if defined (WINDOW_BACKEND_WAYLAND)
/* {{{ */

/* internal functions (declarations) */

WININT int __winLoadWayland(struct _window_h_wl *);

WININT int __winUnloadWayland(struct _window_h_wl *);

/* internal functions (definitions) */

WININT int __winLoadWayland(struct _window_h_wl *wl) {
    /* null-check */
    if (!wl) { return (0); }

    /* try to load handle */
    void *handle  = 0;
    {
        /* ... */
    }

    /* ... */

    /* set 'wl->libwayland_client' member */ 
    wl->libwayland_client = handle;

    /* success */
    return (1);
}

/* }}} */
# endif /* WINDOW_BACKEND_WAYLAND */
#
# /* WINDOW_BACKEND_WIN32 - Win32 implementation layer */
# if defined (WINDOW_BACKEND_WIN32)
/* {{{ */

/* internal functions (declarations) */

LRESULT CALLBACK __win_win32_event_process(HWND, UINT, WPARAM, LPARAM);

/* window.h API (declarations) */

WININT int __win_win32_init(struct _window_h *);

WININT int __win_win32_load(struct _window_h *);

WININT int __win_win32_quit(struct _window_h *);

WININT int __win_win32_unload(struct _window_h *);

WININT int __win_win32_window_create(struct _window_h *, struct _window_h_window *, const size_t, const size_t, const char *);

WININT int __win_win32_window_destroy(struct _window_h *, struct _window_h_window *);

WININT int __win_win32_window_map(struct _window_h *, struct _window_h_window *);

WININT int __win_win32_window_unmap(struct _window_h *, struct _window_h_window *);

WININT int __win_win32_context_create(struct _window_h *, struct _window_h_context *, struct _window_h_window *);

WININT int __win_win32_context_destroy(struct _window_h *, struct _window_h_context *);

WININT int __win_win32_cursor_create(struct _window_h *, struct _window_h_cursor *, const uint8_t *, const size_t, const size_t, const int, const int);

WININT int __win_win32_cursor_destroy(struct _window_h *, struct _window_h_cursor *);

WININT int __win_win32_event_poll(struct _window_h *);

/* internal functions (definitions) */

LRESULT CALLBACK __win_win32_event_process(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    /* handle 'WM_NCCREATE' event */
    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT *pCreateStruct = (CREATESTRUCT *) lParam;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) pCreateStruct->lpCreateParams);
        return (DefWindowProc(hWnd, uMsg, wParam, lParam));
    }
    
    /* get the 'lib' object */    
    struct _window_h *lib = (struct _window_h *) GetWindowLongPtr(hWnd, GWLP_USERDATA);

    /* get the window object */
    struct _window_h_window *win = lib->window.list;
    while (win) {
        if (win->handle == (uintptr_t) hWnd) { break; }
        win = win->next;
    }

    /* process events */
    int result = 0;
    switch (uMsg) {
        case (WM_CLOSE): {
            PostQuitMessage(0);
            win_event_send(lib, win, WINDOW_EVENT_QUIT);
        } break; 

        case (WM_CREATE): {
            win_event_send(lib, win, WINDOW_EVENT_WINDOW_CREATE, 0, 0);
        } break;

        case (WM_DESTROY): {
            win_event_send(lib, win, WINDOW_EVENT_WINDOW_DESTROY, 0, 0);
        } break;

        case (WM_SHOWWINDOW): {
            /* only handle for 'ShowWindow' function call */
            if (lParam) {
                /* update attribute */
                win->attrib.mapped = wParam; /* wParam == 0: window is hidden
                                              * wParam == 1: window is shown 
                                              * */

                win_event_send(lib, win, wParam ? WINDOW_EVENT_WINDOW_MAP :
                                                  WINDOW_EVENT_WINDOW_UNMAP, 0, 0); 
            }
        } break;

        case (WM_SIZE): {
            win->attrib.size.x = LOWORD(lParam);
            win->attrib.size.y = HIWORD(lParam);
            win_event_send(lib, win, WINDOW_EVENT_WINDOW_RESIZE, win->attrib.size.x,
                                                                 win->attrib.size.y);
        } break;

        case (WM_MOVE): {
            win->attrib.position.x = LOWORD(lParam);
            win->attrib.position.y = HIWORD(lParam);
            win_event_send(lib, win, WINDOW_EVENT_WINDOW_MOTION, win->attrib.position.x,
                                                                 win->attrib.position.y);
        } break;

        default: { result = DefWindowProc(hWnd, uMsg, wParam, lParam); } break;
    }

    /* return 'result' */
    return (result);
}

/* window.h API (declarations) */

WININT int __win_win32_init(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* references */
    struct _window_h_win32 *win32 = lib->win32; 
    if (!win32) { return (0); }

    /* register new window class */
    win32->wndclass.hInstance = 0; 
    win32->wndclass.lpfnWndProc = __win_win32_event_process;
    win32->wndclass.lpszClassName = "Sample Window Class";
    RegisterClass(&win32->wndclass);

    /* success */
    return (1);
}


WININT int __win_win32_load(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }
    if (lib->win32) { return (1); }

    /* init-check */
    struct _window_h_win32 *win32 = calloc(1, sizeof(struct _window_h_win32));
    if (!win32) { return (0); }

    /* return the result */
    lib->win32 = win32;
    
    /* success */
    return (1);
}


WININT int __win_win32_quit(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* references */
    struct _window_h_win32 *win32 = lib->win32; 
    if (!win32) { return (0); }

    /* success */
    return (1);
}


WININT int __win_win32_unload(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    struct _window_h_win32 *win32 = lib->win32;
    if (!win32) { return (0); }

    /* release 'win32' */
    free(win32);

    /* success */
    return (1);
}


WININT int __win_win32_window_create(struct _window_h *lib, struct _window_h_window *win, const size_t width, const size_t height, const char *title) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* references */
    const char *classname = lib->win32->wndclass.lpszClassName;

    /* alloc new 'win32' window object */
    struct _window_h_window_win32 *win32 = calloc(1, sizeof(struct _window_h_window_win32));
    if (!win32) { return (0); }

    /* create client window */
    HWND handle = CreateWindowEx(0,
                                 classname,
                                 title,
                                 WS_OVERLAPPEDWINDOW,
                                 CW_USEDEFAULT,
                                 CW_USEDEFAULT,
                                 width,
                                 height,
                                 0,
                                 0,
                                 0,
                                 lib);
    if (!handle) {
        free(win32);
        return (0);
    }
    
    /* set 'win32' members */
    win32->handle = handle;

    /* return the result */
    win->win32 = win32;

    /* set the 'win' members */
    win->handle = (uintptr_t) handle;

    /* success */
    return (1);
}


WININT int __win_win32_window_destroy(struct _window_h *lib, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* destroy client */
    DestroyWindow(win->win32->handle);

    /* deallocate window object */
    free(win->win32);

    /* success */
    return (1);
}


WININT int __win_win32_window_map(struct _window_h *lib, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* show window */
    ShowWindow(win->win32->handle, SW_SHOWNORMAL);

    /* success */
    return (1);
}


WININT int __win_win32_window_unmap(struct _window_h *lib, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!win) { return (0); }

    /* hide window */
    ShowWindow(win->win32->handle, SW_HIDE);

    /* success */
    return (1);
}


WININT int __win_win32_context_create(struct _window_h *lib, struct _window_h_context *ctx, struct _window_h_window *win) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }
    if (!win) { return (0); }
            
    /* alloc new 'win32' object */
    struct _window_h_context_win32 *win32 = calloc(1, sizeof(struct _window_h_context_win32));
    if (!win32) { return (0); }

    /* return 'win32' object */
    ctx->win32 = win32;

    /* success */
    return (1);
}


WININT int __win_win32_context_destroy(struct _window_h *lib, struct _window_h_context *ctx) {
    /* null-check */
    if (!lib) { return (0); }
    if (!ctx) { return (0); }

    /* release 'win32' */
    free(ctx->win32);
            
    /* success */
    return (1);
}


WININT int __win_win32_cursor_create(struct _window_h *lib, struct _window_h_cursor *cur, const uint8_t *data, const size_t width, const size_t height, const int xhot, const int yhot) {
    /* null-check */
    if (!lib) { return (0); }
    if (!cur) { return (0); }

    (void) data;
    (void) width;
    (void) height;
    (void) xhot;
    (void) yhot;

    /* alloc new 'win32' object */
    struct _window_h_cursor_win32 *win32 = calloc(1, sizeof(struct _window_h_cursor_win32));
    if (!win32) { return (0); }

    /* return the result */
    cur->win32 = win32;

    /* success */
    return (1);
}


WININT int __win_win32_cursor_destroy(struct _window_h *lib, struct _window_h_cursor *cur) {
    /* null-check */
    if (!lib) { return (0); }
    if (!cur) { return (0); }

    /* release 'win32' */
    free(cur->win32);

    /* success */
    return (1);
}


WININT int __win_win32_event_poll(struct _window_h *lib) {
    /* null-check */
    if (!lib) { return (0); }

    /* init-check */
    struct _window_h_win32 *win32 = lib->win32;
    if (!win32) { return (0); }

    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    /* success */
    return (1);
}

/* }}} */
# endif /* WINDOW_BACKEND_WIN32 */

/* window.h implementation layer */
/* {{{ */
/* platform internal functions */

WININT int __winLoadPlatform(struct _window_h *, struct _window_h_platform *);

/* platform functions */

WINDEF int win_init(library_t *result) {
    /* initialize window.h */
    struct _window_h *lib = calloc(1, sizeof(struct _window_h));
    if (!lib) { return (0); }

    /* set default hints */
    lib->hints.api = WINDOW_API_NATIVE;
    
    /* set default 'window' hints */
    lib->hints.window.resize = 0;
    lib->hints.window.decor  = 1;

    /* set default 'gl' hints */
    lib->hints.gl.red     = 8;
    lib->hints.gl.green   = 8;
    lib->hints.gl.blue    = 8;
    lib->hints.gl.alpha   = 8;
    lib->hints.gl.depth   = 24;
    lib->hints.gl.stencil = 8;
    lib->hints.gl.dblbuf  = 1;
    lib->hints.gl.major   = 1;
    lib->hints.gl.minor   = 0;
    lib->hints.gl.profile = WINDOW_GL_CONTEXT_PROFILE_COMPATIBILITY;

    /* load window.h platform */
    if (!__winLoadPlatform(lib, &lib->platform)) {
        free(lib);
        return (0);
    }
    
    /* call platform - specific load function */
    if (!lib->platform.load(lib)) {
        free(lib);
        return (0);
    }

    /* call platform - specific init function */
    if (!lib->platform.init(lib)) {
        free(lib);
        return (0);
    }

    /* create blank cursor handle */
    const uint8_t data[16 * 16 * 4] = { 0 };
    if (!win_cursor_create(lib, (cursor_t *) &lib->cursor.blank, data, 16, 16, 0, 0)) {
        free(lib);
        return (0);
    }

    /* return the 'result' */
    *result = lib;
    return (1);
}


WINDEF int win_quit(library_t library) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }

    /* destroy all the existing cursors */
    struct _window_h_cursor *cursor = lib->cursor.list;
    while (cursor) {
        void *next = cursor->next;
        win_cursor_destroy(library, cursor);
        cursor = next;
    }
    
    /* destroy all the existing contexts */
    struct _window_h_context *context = lib->context.list;
    while (context) {
        void *next = context->next;
        win_context_destroy(library, context);
        context = next;
    }

    /* close all the open windows */
    struct _window_h_window *window = lib->window.list;
    while (window) {
        void *next = window->next;
        win_window_destroy(library, window);
        window = next;
    }

    /* release selections */
    struct _window_h_selection *selection = &lib->selection;
    
    /* release 'primary' */
    free(selection->primary.data);
    selection->primary.data = 0;
    selection->primary.size = 0;
    
    /* release 'secondary' */
    free(selection->secondary.data);
    selection->secondary.data = 0;
    selection->secondary.size = 0;
    
    /* release 'clipboard' */
    free(selection->clipboard.data);
    selection->clipboard.data = 0;
    selection->clipboard.size = 0;

    /* flush event queue */
    event_t event = { 0 };
    do {
        win_event_pop(library, &event);
    } while (event.type);
    
    /* call platform - specific quit function */
    lib->platform.quit(library);

    /* call platform - specific unload function */
    lib->platform.unload(library);

    /* call platform - specific unload OpenGL function */
    lib->platform.gl_unload(library);

    /* release 'library' */
    free(library);

    /* success */
    return (1);
}


WINDEF int win_set_hints(library_t library, const uint32_t hint, const int32_t value) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    switch (hint) {
        case (WINDOW_CLIENT_API): { lib->hints.api = value; } break;

        case (WINDOW_GL_RED): {
            lib->hints.gl.red = value;
        } break;

        case (WINDOW_GL_GREEN): {
            lib->hints.gl.green = value;
        } break;

        case (WINDOW_GL_BLUE): {
            lib->hints.gl.blue = value;
        } break;

        case (WINDOW_GL_ALPHA): {
            lib->hints.gl.alpha = value;
        } break;

        case (WINDOW_GL_DEPTH): {
            lib->hints.gl.depth = value;
        } break;

        case (WINDOW_GL_STENCIL): {
            lib->hints.gl.stencil = value;
        } break;

        case (WINDOW_GL_DOUBLEBUFFER): {
            lib->hints.gl.dblbuf = value;
        } break;

        case (WINDOW_GL_CONTEXT_VERSION_MAJOR): {
            lib->hints.gl.major = value;
        } break;

        case (WINDOW_GL_CONTEXT_VERSION_MINOR): {
            lib->hints.gl.minor = value;
        } break;

        case (WINDOW_GL_CONTEXT_PROFILE): {
            lib->hints.gl.profile = value;
        } break;

        /* failure */
        default: { return (0); }
    }

    /* success */
    return (1);
}

/* windowing functions */

WINDEF int win_window_create(library_t library, window_t *result, const size_t width, const size_t height, const char *title) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* alloc new window object */
    struct _window_h_window *win = calloc(1, sizeof(struct _window_h_window));
    if (!win) { return (0); }
    
    /* API-specific implementation */
    win->attrib.api = lib->hints.api;
    switch (win->attrib.api) {
        case (WINDOW_API_OPENGL):
        case (WINDOW_API_OPENGLES): {
            if (!lib->platform.gl_load(lib) ||
                !lib->platform.gl_init(lib, lib->handle)
            ) {
                free(win);
                return (0);
            }
        } break;
    }

    /* create window object */
    if (!lib->platform.window_create(lib, win, width, height, title)) {
        free(win);
        return (0);
    }

    /* add the result to the 'lib->window.list' linked list */
    win->next = lib->window.list;
    lib->window.list = win;

    /* and return the result */
    *result = win;

    /* success */
    return (1);
}

WINDEF int win_window_destroy(library_t library, window_t window) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* call platform - specific destroy function */
    if (!lib->platform.window_destroy(library, window)) { return (0); }

    /* references */
    struct _window_h_window *win = (struct _window_h_window *) window;

    /* unlink 'win' from 'lib->window.list' */
    struct _window_h_window **curr = &lib->window.list;
    /* case when 'win' is the first node of 'lib->window.list' */
    if (win == (*curr)) {
        lib->window.list = (*curr)->next;
    }
    /* case when 'win' is not the first node of 'lib->window.list' */
    else {
        /* search for prepending window for 'win' */
        while ((*curr) && (*curr)->next != win) {
            (*curr) = (*curr)->next;
        }

        if (!(*curr)) { return (0); }
        (*curr) = (*curr)->next;
    }

    /* deallocate window object */
    free(win);

    /* success */
    return (1);
}

WINDEF int win_window_map(library_t library, window_t window) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_map(library, window));
}

WINDEF int win_window_unmap(library_t library, window_t window) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_unmap(library, window)); 
}

WINDEF int win_window_get_size(library_t library, window_t window, size_t *w_ptr, size_t *h_ptr) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_get_size(library, window, w_ptr, h_ptr)); 
}

WINDEF int win_window_set_size(library_t library, window_t window, const size_t w, const size_t h) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_set_size(library, window, w, h)); 
}

WINDEF int win_window_set_size_min(library_t library, window_t window, const size_t w, const size_t h) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_set_size_min(library, window, w, h)); 
}

WINDEF int win_window_set_size_max(library_t library, window_t window, const size_t w, const size_t h) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_set_size_max(library, window, w, h)); 
}

WINDEF int win_window_get_position(library_t library, window_t window, size_t *x_ptr, size_t *y_ptr) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_get_position(library, window, x_ptr, y_ptr)); 
}

WINDEF int win_window_set_position(library_t library, window_t window, const size_t x, const size_t y) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_set_position(library, window, x, y)); 
}

WINDEF int win_window_get_title(library_t library, window_t window, char **t_ptr) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_get_title(library, window, t_ptr)); 
}

WINDEF int win_window_set_title(library_t library, window_t window, const char *t) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.window_set_title(library, window, t)); 
}

WINDEF int win_window_get_context(library_t library, window_t window, context_t *c_ptr) {
    /* null-check */
    if (!library) { return (0); }

    /* references */
    struct _window_h_window *win = (struct _window_h_window *) window;
    if (!win) { return (0); }

    /* get the context from the 'win' */
    if (c_ptr) { *c_ptr = win->context.handle; }

    /* success */
    return (1);
}

WINDEF int win_window_set_context(library_t library, window_t window, context_t context) {
    /* null-check */
    if (!library) { return (0); }
    
    /* references */
    struct _window_h_window  *win = (struct _window_h_window *) window;
    struct _window_h_context *ctx = (struct _window_h_context *) context;

    /* update the internal references in 'win' and 'ctx' */
    win->context.handle = context;
    ctx->window.current  = window;

    /* success */
    return (1);
}

/* context functions */

WINDEF int win_context_create(library_t library, context_t *result, window_t window) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* references */
    struct _window_h_window *win = (struct _window_h_window *) window;
    if (!win) { return (0); }
    
    /* alloc new cursor object */
    struct _window_h_context *ctx= calloc(1, sizeof(struct _window_h_context));
    if (!ctx) { return (0); }
    
    /* Context MUST inherit the context from the 'window'!
     * Like, imagine: you create 'Native' window and 'OpenGL' context?
     * Window and Context must have the same API and in-between their creation
     * 'WINDOW_CLIENT_API' hint can change.
     * */
    ctx->attrib.api = win->attrib.api;
    
    /* API-specific implementation */
    switch (ctx->attrib.api) {
        case (WINDOW_API_NATIVE): {
            if (!lib->platform.context_create(library, ctx, win)) {
                free(ctx);
                return (0);
            }
        } break;

        case (WINDOW_API_OPENGL):
        case (WINDOW_API_OPENGLES): {
            if (!lib->platform.gl_context_create(library, ctx, win)) {
                free(ctx);
                return (0);
            }
        } break;

        default: { free(ctx); return (0); }
    } 

    /* set the context ownership */
    win_context_set_window(lib, ctx, win);

    /* add the result to the 'lib->context.list' linked list */
    ctx->next = lib->context.list;
    lib->context.list = ctx;
    
    /* and return the result */
    *result = ctx;

    /* success */
    return (1);
}

WINDEF int win_context_destroy(library_t library, context_t context) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    struct _window_h_context *ctx = (struct _window_h_context *) context;
    if (!ctx) { return (0); }
    
    /* API-specific implementation */
    switch (ctx->attrib.api) {
        case (WINDOW_API_NATIVE): {
            /* call platform - specific destroy function */
            if (!lib->platform.context_destroy(library, context)) { return (0); }
        } break;

        case (WINDOW_API_OPENGL):
        case (WINDOW_API_OPENGLES): {
            /* call platform - specific destroy function */
            if (!lib->platform.gl_context_destroy(library, context)) { return (0); }
        } break;

        default: { return (0); }
    } 

    /* unlink 'ctx' from 'lib->context.list' */
    struct _window_h_context **curr = &lib->context.list;
    /* case when 'ctx' is the first node of 'lib->context.list' */
    if (ctx == (*curr)) {
        lib->context.list = (*curr)->next;
    }
    /* case when 'ctx' is not the first node of 'lib->context.list' */
    else {
        /* search for prepending window for 'ctx' */
        while ((*curr) && (*curr)->next != ctx) {
            (*curr) = (*curr)->next;
        }

        if (!(*curr)) { return (0); }
        (*curr) = (*curr)->next;
    }

    /* deallocate context object */
    free(ctx);

    /* success */
    return (1);
}

WINDEF int win_context_get_window(library_t library, context_t context, window_t *w_ptr) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    struct _window_h_context *ctx = (struct _window_h_context *) context;
    if (!ctx) { return (0); }

    /* get the context from the 'win' */
    if (w_ptr) { *w_ptr = ctx->window.current; }

    /* success */
    return (1);
}

WINDEF int win_context_set_window(library_t library, context_t context, window_t window) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* references */
    struct _window_h_context *ctx = (struct _window_h_context *) context;
    struct _window_h_window  *win = (struct _window_h_window *) window;

    /* update the internal references in 'win' and 'ctx' */
    ctx->window.current = window;
    win->context.handle = context;

    /* success */
    return (1);
}

/* opengl context functions */

WINDEF int win_gl_make_current(library_t library, context_t context) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.gl_make_current(library, context));
}

WINDEF int win_gl_swap_buffers(library_t library, context_t context) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.gl_swap_buffers(library, context));
}

WINDEF int win_gl_swap_interval(library_t library, context_t context, const int interval) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.gl_swap_interval(library, context, interval));
}

WINDEF void *win_gl_get_proc_address(const char *proc) {

# if defined (WINDOW_BACKEND_GLX)
    /* attempt to load 'proc' using 'glXGetProcAddress' */
    if (glXGetProcAddress_PROC) { return (glXGetProcAddress((const uint8_t *) proc)); }
    
    /* attempt to load 'proc' using 'glXGetProcAddressARB' */
    if (glXGetProcAddressARB_PROC) { return (glXGetProcAddressARB((const uint8_t *) proc)); }

# elif defined (WINDOW_BACKEND_EGL)
    /* attempt to load 'proc' using 'eglGetProcAddress' */
    if (eglGetProcAddress_PROC) { return (eglGetProcAddress(proc)); }

# elif defined (WINDOW_BACKEND_WGL)
    /* attempt to load 'proc' using 'wglGetProcAddress' */
    (void) proc;
    // if (wglGetProcAddress_PROC) { return (wglGetProcAddress(proc)); }

# endif

    /* failure */
    return (0);
}

/* cursor functions */

WINDEF int win_cursor_create(library_t library, cursor_t *result, const uint8_t *data, const size_t width, const size_t height, const int xhot, const int yhot) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* alloc new cursor object */
    struct _window_h_cursor *cur = calloc(1, sizeof(struct _window_h_cursor));
    if (!cur) { return (0); }
    
    /* call platform - specific create function */
    if (!lib->platform.cursor_create(library, cur, data, width, height, xhot, yhot)) {
        free(cur);
        return (0);
    }
    
    /* add the result to the 'lib->cursor.list' linked list */
    cur->next = lib->cursor.list;
    lib->cursor.list = cur;
    
    /* and return the result */
    *result = cur;

    /* success */
    return (1);
}

WINDEF int win_cursor_destroy(library_t library, cursor_t cursor) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* call platform - specific destroy function */
    if (!lib->platform.cursor_destroy(library, cursor)) { return (0); }
    
    /* references */
    struct _window_h_cursor *cur = (struct _window_h_cursor *) cursor;

    /* unlink 'cur' from 'lib->cursor.list' */
    struct _window_h_cursor **curr = &lib->cursor.list;
    /* case when 'cur' is the first node of 'lib->cursor.list' */
    if (cur == (*curr)) {
        lib->cursor.list = (*curr)->next;
    }
    /* case when 'cur' is not the first node of 'lib->cursor.list' */
    else {
        /* search for prepending window for 'cur' */
        while ((*curr) && (*curr)->next != cur) {
            (*curr) = (*curr)->next;
        }

        if (!(*curr)) { return (0); }
        (*curr) = (*curr)->next;
    }

    /* deallocate cursor object */
    free(cur);

    /* success */
    return (1);
}

WINDEF int win_cursor_get_position(library_t library, window_t window, size_t *x_ptr, size_t *y_ptr) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.cursor_get_position(library, window, x_ptr, y_ptr));
}

WINDEF int win_cursor_set_position(library_t library, window_t window, const size_t x, const size_t y) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.cursor_set_position(library, window, x, y));
}

WINDEF int win_cursor_set_position_center(library_t library, window_t window) {
    /* 'result' exit-code */
    int result = 1;
   
    /* get the window size */
    size_t w, h;
    result = win_window_get_size(library, window, &w, &h);

    /* set the cursor to the middle of the window */
    result = win_cursor_set_position(library, window, w / 2, h / 2);
    return (result);
}

WINDEF int win_cursor_get_mode(library_t library, window_t window, uint32_t *m_ptr) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    struct _window_h_window *win = (struct _window_h_window *) window;
    if (!win) { return (0); }
    
    /* return the result */
    if (m_ptr) { *m_ptr = win->cursor.attrib.mode; }

    /* success */
    return (1);
}

WINDEF int win_cursor_set_mode(library_t library, window_t window, const uint32_t mode) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    struct _window_h_window *win = (struct _window_h_window *) window;
    if (!win) { return (0); }

    /* update 'win->cursor' members */
    win->cursor.attrib.mode = mode;
    
    return (lib->platform.cursor_set_mode(library, window, mode));
}

/* event functions */

WINDEF int win_event_poll(library_t library, event_t *event) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* flush the event queue */
    if (win_event_pop(library, event)) { return (1); }

    /* call platform-specific poll events function */
    lib->platform.event_poll(library);

    /* get the centered/disabled cursor window */
    struct _window_h_window *win = lib->window.list;
    while (win) {
        /* centered/disabled window found */
        if (win->cursor.attrib.mode == WINDOW_CURSOR_MODE_CENTERED ||
            win->cursor.attrib.mode == WINDOW_CURSOR_MODE_DISABLED
        ) {
            if (win->cursor.attrib.accum.x != 0 ||
                win->cursor.attrib.accum.y != 0
            ) {
                win_event_send(lib, win, WINDOW_EVENT_MOUSE_MOTION, win->cursor.attrib.accum.x,
                                                                    win->cursor.attrib.accum.y);

                win->cursor.attrib.accum.x = win->cursor.attrib.accum.y = 0;
            }

            win_cursor_set_position_center(lib, win);
            win->cursor.attrib.warp = 1;

            /* break from the loop */
            break;
        }

        /* otherwise, get to the next window */
        win = win->next;
    }

    /* we don't have any event left here to process */
    *event = (event_t) { 0 };
    return (0);
}

WINDEF int win_event_wait(library_t library, event_t *event) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    /* flush the event queue */
    if (win_event_pop(library, event)) { return (1); }

    /* call platform-specific poll events function */
    lib->platform.event_wait(library);

    /* this means we don't have any event... */
    *event = (event_t) { 0 };
    return (0);
}

WINDEF int win_event_push(library_t library, event_t *event) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    struct _window_h_event *eq = lib->event.queue;
    /* no events in queue */
    if (!eq) {
        eq = calloc(1, sizeof(struct _window_h_event));
        if (!eq) { return (0); }

        eq->next  = 0;
        eq->event = *event;

        /* assign back new queue */
        lib->event.queue = eq;
    } else {
        /* go to the end of the queue */
        while (eq->next) { eq = eq->next; }

        /* alloc new event queue member */
        struct _window_h_event *node = calloc(1, sizeof(struct _window_h_event));
        if (!node) { return (0); }

        node->next  = 0;
        node->event = *event;

        /* push the 'node' to the end of 'eq' */
        eq->next = node;
    }

    /* success */
    return (1);
}

WINDEF int win_event_pop(library_t library, event_t *event) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    struct _window_h_event *eq = lib->event.queue;
    /* empty event queue */
    if (!eq) {
        *event = (event_t) { 0 };
        return (0);
    }

    /* get the event from the top */
    *event = eq->event;

    /* re-assign the global event queue */
    lib->event.queue = eq->next;

    /* release top event */
    free(eq);

    /* success */
    return (1);
}

WINDEF int win_event_send(library_t library, window_t window, uint32_t type, ...) {
    /* null-check */
    if (!library) { return (0); }

    /* default 'event' object */
    event_t event = { 0 };
    
    /* set event 'type' */
    event.type = type;

    /* set event 'common' members */
    event.common.time = win_time_get();
    event.common.window = window;

    /* get the variadic argument list */
    va_list list;
    va_start(list, type);
    switch (type) {

        case (WINDOW_EVENT_QUIT): { } break;

        /* Mouse events */

        case (WINDOW_EVENT_MOUSE_MOTION): {
            event.mouse.motion.x = va_arg(list, int32_t);
            event.mouse.motion.y = va_arg(list, int32_t);
        } break;

        case (WINDOW_EVENT_MOUSE_BUTTON): {
            event.mouse.input.btn   = va_arg(list, int);
            event.mouse.input.state = va_arg(list, int);
        } break;

        case (WINDOW_EVENT_MOUSE_SCROLL): {
            event.mouse.scroll.x = va_arg(list, int32_t);
            event.mouse.scroll.y = va_arg(list, int32_t);
        } break;

        /* Keyboard events */

        case (WINDOW_EVENT_KEYBOARD_KEY): {
            event.keyboard.keysym  = va_arg(list, uint64_t);
            event.keyboard.keycode = va_arg(list, uint32_t);
            event.keyboard.keymod  = va_arg(list, uint32_t);
            event.keyboard.keyraw  = va_arg(list, uint32_t);
            event.keyboard.state   = va_arg(list, uint32_t);
            event.keyboard.repeat  = va_arg(list, uint32_t);
        } break;

        /* Window events */

        case (WINDOW_EVENT_WINDOW_CREATE):
        case (WINDOW_EVENT_WINDOW_DESTROY):
        case (WINDOW_EVENT_WINDOW_MAP):
        case (WINDOW_EVENT_WINDOW_UNMAP):
        case (WINDOW_EVENT_WINDOW_RESIZE):
        case (WINDOW_EVENT_WINDOW_MOTION):
        case (WINDOW_EVENT_WINDOW_ENTER):
        case (WINDOW_EVENT_WINDOW_LEAVE):
        case (WINDOW_EVENT_WINDOW_MAXIMIZE):
        case (WINDOW_EVENT_WINDOW_MINIMIZE):
        case (WINDOW_EVENT_WINDOW_FULLSCREEN): {
            event.window.data1  = va_arg(list, uint32_t);
            event.window.data2  = va_arg(list, uint32_t);
        } break;

        case (WINDOW_EVENT_SELECTION_COPY):
        case (WINDOW_EVENT_SELECTION_PASTE): {
            event.clipboard.data = va_arg(list, void *);
            event.clipboard.size = va_arg(list, size_t);
        } break;

        /* ... */

        default: { } break;
    }


    /* finish variadic argument list */
    va_end(list);
    
    /* return */
    return (win_event_push(library, &event));
}

WINDEF int win_event_head(library_t library, event_t *event) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    *event = (event_t) { 0 };
    
    struct _window_h_event *eq = lib->event.queue;
    if (eq) { *event = eq->event; }

    /* success */
    return (1);
}

/* clipboard functions */

WINDEF int win_copy(library_t library, const uint32_t selection, const void *data, const size_t size) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.copy(library, selection, data, size));
}

WINDEF int win_paste(library_t library, const uint32_t selection, void **d_ptr, size_t *s_ptr) {
    /* references */
    struct _window_h *lib = (struct _window_h *) library;
    if (!lib) { return (0); }
    
    return (lib->platform.paste(library, selection, d_ptr, s_ptr));
}

/* timing functions */

WINDEF uint64_t win_time_get(void) {

# if defined (WINDOW_PLATFORM_LINUX) || \
      defined (WINDOW_PLATFORM_APPLE) || \
      defined (WINDOW_PLATFORM_BSD)
    struct timeval t;
    if (gettimeofday(&t, 0) == -1) {
        return (0);
    }

    return (t.tv_sec * 1000 + t.tv_usec / 1000);
# elif defined (WINDOW_PLATFORM_WIN32)
    SYSTEMTIME  systemtime;
    GetSystemTime(&systemtime);
    return (systemtime.wMilliseconds);
# endif

}

WINDEF int win_time_wait(uint64_t ms) {
    uint64_t t = win_time_get();
    if (t == 0) { return (0); }

    while ((win_time_get() - t) < ms);
    return (1);
}

/* platform internal functions */

WININT int __winLoadPlatform(struct _window_h *library, struct _window_h_platform *platform) {
    /* null-check */
    if (!library)  { return (0); }
    if (!platform) { return (0); }

# if defined (WINDOW_BACKEND_X11)

    /* select API function callbacks */
    
    platform->id = WINDOW_BACKEND_X11;
    
    /* library functions */

    platform->init = __win_x11_init;
    platform->load = __win_x11_load;
    platform->quit = __win_x11_quit;
    platform->unload = __win_x11_unload;
    
    /* window functions */
   
    platform->window_create = __win_x11_window_create;
    platform->window_destroy = __win_x11_window_destroy;
    platform->window_map = __win_x11_window_map;
    platform->window_unmap = __win_x11_window_unmap;
    platform->window_get_size = __win_x11_window_get_size;
    platform->window_set_size = __win_x11_window_set_size;
    platform->window_set_size_min = __win_x11_window_set_size_min;
    platform->window_set_size_max = __win_x11_window_set_size_max;
    platform->window_get_position = __win_x11_window_get_position;
    platform->window_set_position = __win_x11_window_set_position;
    platform->window_get_title = __win_x11_window_get_title;
    platform->window_set_title = __win_x11_window_set_title;

    /* context functions */

    platform->context_create = __win_x11_context_create;
    platform->context_destroy = __win_x11_context_destroy;

    /* cursor functions */

    platform->cursor_create = __win_x11_cursor_create;
    platform->cursor_destroy = __win_x11_cursor_destroy;
    platform->cursor_get_position = __win_x11_cursor_get_position;
    platform->cursor_set_position = __win_x11_cursor_set_position;
    platform->cursor_set_mode = __win_x11_cursor_set_mode;

    /* event functions */

    platform->event_poll = __win_x11_event_poll;
    platform->event_wait = __win_x11_event_wait;

    /* clipboard functions */
    
    platform->copy = __win_x11_copy;
    platform->paste = __win_x11_paste;

# elif defined (WINDOW_BACKEND_WIN32)

    /* select API function callbacks */
    
    platform->id = WINDOW_BACKEND_WIN32;
    
    /* library functions */

    platform->init = __win_win32_init;
    platform->load = __win_win32_load;
    platform->quit = __win_win32_quit;
    platform->unload = __win_win32_unload;
    
    /* window functions */
   
    platform->window_create = __win_win32_window_create;
    platform->window_destroy = __win_win32_window_destroy;
    platform->window_map = __win_win32_window_map;
    platform->window_unmap = __win_win32_window_unmap;
    
    /* context functions */

    platform->context_create = __win_win32_context_create;
    platform->context_destroy = __win_win32_context_destroy;

    /* cursor functions */

    platform->cursor_create = __win_win32_cursor_create;
    platform->cursor_destroy = __win_win32_cursor_destroy;

    /* event functions */

    platform->event_poll = __win_win32_event_poll;

# else
# endif

# if defined (WINDOW_BACKEND_GLX)
    
    /* opengl context functions */

    platform->gl_init = __win_glx_init;
    platform->gl_load = __win_glx_load;
    platform->gl_unload = __win_glx_unload;
    platform->gl_context_create = __win_glx_create_context;
    platform->gl_context_destroy = __win_glx_context_destroy;
    platform->gl_make_current = __win_glx_make_current;
    platform->gl_swap_buffers = __win_glx_swap_buffers;
    platform->gl_swap_interval = __win_glx_swap_interval;
    platform->gl_choose_config = __win_glx_choose_config;
    platform->gl_get_visual = __win_glx_get_visual;

# elif defined (WINDOW_BACKEND_EGL)

    /* opengl context functions */

    platform->gl_init = __win_egl_init;
    platform->gl_load = __win_egl_load;
    platform->gl_unload = __win_egl_unload;
    platform->gl_context_create = __win_egl_create_context;
    platform->gl_context_destroy = __win_egl_context_destroy;
    platform->gl_make_current = __win_egl_make_current;
    platform->gl_swap_buffers = __win_egl_swap_buffers;
    platform->gl_swap_interval = __win_egl_swap_interval;
    platform->gl_choose_config = __win_egl_choose_config;
    platform->gl_get_visual = __win_egl_get_visual;

# elif defined (WINDOW_BACKEND_WGL)
    
    /* opengl context functions */
    platform->gl_init = __win_wgl_init;
    platform->gl_load = __win_wgl_load;
    platform->gl_unload = __win_wgl_unload;
/*
    platform->gl_context_create = __win_wgl_context_create;
    platform->gl_context_destroy = __win_wgl_context_destroy;
    platform->gl_make_current = __win_wgl_make_current;
    platform->gl_swap_buffers = __win_wgl_swap_buffers;
    platform->gl_swap_interval = __win_wgl_swap_interval;
*/
# endif
    
    /* success */
    return (1);
}

/* }}} */

#endif /* WINDOW_IMPLEMENTATION */
