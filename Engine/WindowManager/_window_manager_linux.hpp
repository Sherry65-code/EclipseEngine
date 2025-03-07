#include "WindowManager.hpp"
#if __linux__
#include "../Standard/IO.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <cstring> // for memset

// X11-specific data
struct X11Data {
    Display* display;
    Window window;
    GLXContext glContext;
    bool quit;
    bool gl;
    WindowManager::MouseMoveCallbackFunction mouse_move_callback;
    bool* mouse_buttons;
};

static X11Data x11Data; // Static instance to hold X11-specific data

bool WindowManager::createNewWindow(WindowCreateInfo& window_create_info) {
    // Open connection to the X server
    x11Data.display = XOpenDisplay(nullptr);
    if (!x11Data.display) {
        io::logMessage(io::LogLevel::EERROR, "Failed to open X11 display.");
        return false;
    }

    // Get the default screen
    int screen = DefaultScreen(x11Data.display);

    // Set up OpenGL visual attributes
    static int visualAttributes[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
    };

    XVisualInfo* visualInfo = glXChooseVisual(x11Data.display, screen, visualAttributes);
    if (!visualInfo) {
        io::logMessage(io::LogLevel::EERROR, "Failed to choose visual for OpenGL.");
        return false;
    }

    // Create a colormap
    Colormap colormap = XCreateColormap(x11Data.display, RootWindow(x11Data.display, screen), visualInfo->visual, AllocNone);

    // Set up window attributes
    XSetWindowAttributes windowAttributes;
    windowAttributes.colormap = colormap;
    windowAttributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask;

    // Create the window
    x11Data.window = XCreateWindow(
        x11Data.display, RootWindow(x11Data.display, screen),
        0,0,
        window_create_info.width, window_create_info.height, // width, height
        0, visualInfo->depth, InputOutput, visualInfo->visual,
        CWColormap | CWEventMask, &windowAttributes
    );

    if (!x11Data.window) {
        io::logMessage(io::LogLevel::EERROR, "Failed to create X11 window.");
        return false;
    }

    // Set the window title
    XStoreName(x11Data.display, x11Data.window, window_create_info.title.c_str());

    // Map the window to the display
    XMapWindow(x11Data.display, x11Data.window);

    // Flush the display to ensure the window is shown
    XFlush(x11Data.display);

    // Initialize mouse buttons
    x11Data.mouse_buttons = (bool*)malloc(sizeof(bool) * 3);
    memset(x11Data.mouse_buttons, 0, sizeof(bool) * 3); // Initialize mouse buttons to false

    io::logMessage(io::LogLevel::EINFO, "X11 window created successfully.");
    return true;
}

void WindowManager::update() {
    // Handle X11 events
    XEvent event;
    while (XPending(x11Data.display)) {
        XNextEvent(x11Data.display, &event);

        switch (event.type) {
            case MotionNotify:
                if (x11Data.mouse_move_callback) {
                    int x = event.xmotion.x;
                    int y = event.xmotion.y;
                    x11Data.mouse_move_callback(x11Data.mouse_buttons, x, y);
                }
                break;
            case ButtonPress:
                if (event.xbutton.button == Button1) x11Data.mouse_buttons[0] = true;
                if (event.xbutton.button == Button2) x11Data.mouse_buttons[2] = true;
                if (event.xbutton.button == Button3) x11Data.mouse_buttons[1] = true;
                if (x11Data.mouse_move_callback) {
                    int x = event.xbutton.x;
                    int y = event.xbutton.y;
                    x11Data.mouse_move_callback(x11Data.mouse_buttons, x, y);
                }
                break;
            case ButtonRelease:
                if (event.xbutton.button == Button1) x11Data.mouse_buttons[0] = false;
                if (event.xbutton.button == Button2) x11Data.mouse_buttons[2] = false;
                if (event.xbutton.button == Button3) x11Data.mouse_buttons[1] = false;
                if (x11Data.mouse_move_callback) {
                    int x = event.xbutton.x;
                    int y = event.xbutton.y;
                    x11Data.mouse_move_callback(x11Data.mouse_buttons, x, y);
                }
                break;
            case ClientMessage:
                x11Data.quit = true;
                break;
        }
    }
}

bool WindowManager::shouldClose() {
    return x11Data.quit;
}

bool WindowManager::createGLContext() {
    // Get the default screen
    int screen = DefaultScreen(x11Data.display);

    // Set up OpenGL visual attributes
    static int visualAttributes[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
    };

    XVisualInfo* visualInfo = glXChooseVisual(x11Data.display, screen, visualAttributes);
    if (!visualInfo) {
        io::logMessage(io::LogLevel::EERROR, "Failed to choose visual for OpenGL.");
        return false;
    }

    // Create the OpenGL context
    x11Data.glContext = glXCreateContext(x11Data.display, visualInfo, nullptr, GL_TRUE);
    if (!x11Data.glContext) {
        io::logMessage(io::LogLevel::EERROR, "Failed to create OpenGL context.");
        return false;
    }

    // Make the context current
    if (!glXMakeCurrent(x11Data.display, x11Data.window, x11Data.glContext)) {
        io::logMessage(io::LogLevel::EERROR, "Failed to make OpenGL context current.");
        return false;
    }

    io::logMessage(io::LogLevel::EINFO, "OpenGL context created successfully.");
    return true;
}

void* WindowManager::win32_getWindowHandle() {
    return reinterpret_cast<void*>(x11Data.window);
}

void WindowManager::setMouseMoveCallbackFunction(MouseMoveCallbackFunction mmcf) {
    x11Data.mouse_move_callback = mmcf;
}

WindowManager::~WindowManager() {
    // Cleanup resources in the destructor
    if (x11Data.glContext) {
        glXDestroyContext(x11Data.display, x11Data.glContext);
    }
    if (x11Data.window) {
        XDestroyWindow(x11Data.display, x11Data.window);
    }
    if (x11Data.display) {
        XCloseDisplay(x11Data.display);
    }
    if (x11Data.mouse_buttons) {
        free(x11Data.mouse_buttons);
    }
}
#endif
