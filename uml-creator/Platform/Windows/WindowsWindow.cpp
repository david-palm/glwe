#include "WindowsWindow.h"

#include "../../Events/WindowEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"


static bool s_GLFWInitialized = false;

#ifdef __EMSCRIPTEN__
static std::map<std::string, int> keyCodesHtml;
#else
static std::map<int, int> keyCodesGlfw;
#endif

Window* Window::create(const WindowProperties& properties)
{
    return new WindowsWindow(properties);
}

WindowsWindow::WindowsWindow(const WindowProperties& properties)
{
    init(properties);
}

WindowsWindow::~WindowsWindow()
{

}

void WindowsWindow::init(const WindowProperties& properties)
{
    m_WindowData.title = properties.title;
    m_WindowData.width = properties.width;
    m_WindowData.height = properties.height;

    if(!s_GLFWInitialized)
    {
        int success = glfwInit();
        if(!success) {
            std::cerr << "Failed to initialize GLFW window" << std::endl;
            glfwTerminate();
        }
        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_WindowData);
    setVSync(true);

    // Setting up key code conversion maps
#ifdef __EMSCRIPTEN__
    // Key codes modelled after mozilla html5/windows (US) codes

    keyCodesHtml.insert(std::make_pair("Tab", 9));
    keyCodesHtml.insert(std::make_pair("Enter", 13));
    keyCodesHtml.insert(std::make_pair("ShiftLeft", 16));
    keyCodesHtml.insert(std::make_pair("ShiftRight", 16));
    keyCodesHtml.insert(std::make_pair("ControlLeft", 17));
    keyCodesHtml.insert(std::make_pair("ControlRight", 17));
    keyCodesHtml.insert(std::make_pair("AltLeft", 18));
    keyCodesHtml.insert(std::make_pair("AltRight", 18));
    keyCodesHtml.insert(std::make_pair("Escape", 27));
    keyCodesHtml.insert(std::make_pair("Space", 32));

    keyCodesHtml.insert(std::make_pair("ArrowLeft", 37));
    keyCodesHtml.insert(std::make_pair("ArrowUp", 38));
    keyCodesHtml.insert(std::make_pair("ArrowRight", 39));
    keyCodesHtml.insert(std::make_pair("ArrowDown", 40));

    keyCodesHtml.insert(std::make_pair("Digit0", 48));
    keyCodesHtml.insert(std::make_pair("Digit1", 49));
    keyCodesHtml.insert(std::make_pair("Digit2", 50));
    keyCodesHtml.insert(std::make_pair("Digit3", 51));
    keyCodesHtml.insert(std::make_pair("Digit4", 52));
    keyCodesHtml.insert(std::make_pair("Digit5", 53));
    keyCodesHtml.insert(std::make_pair("Digit6", 54));
    keyCodesHtml.insert(std::make_pair("Digit7", 55));
    keyCodesHtml.insert(std::make_pair("Digit8", 56));
    keyCodesHtml.insert(std::make_pair("Digit9", 57));

    keyCodesHtml.insert(std::make_pair("KeyA", 65));
    keyCodesHtml.insert(std::make_pair("KeyB", 66));
    keyCodesHtml.insert(std::make_pair("KeyC", 67));
    keyCodesHtml.insert(std::make_pair("KeyD", 68));
    keyCodesHtml.insert(std::make_pair("KeyE", 69));
    keyCodesHtml.insert(std::make_pair("KeyF", 70));
    keyCodesHtml.insert(std::make_pair("KeyG", 71));
    keyCodesHtml.insert(std::make_pair("KeyH", 72));
    keyCodesHtml.insert(std::make_pair("KeyI", 73));
    keyCodesHtml.insert(std::make_pair("KeyJ", 74));
    keyCodesHtml.insert(std::make_pair("KeyK", 75));
    keyCodesHtml.insert(std::make_pair("KeyL", 76));
    keyCodesHtml.insert(std::make_pair("KeyM", 77));
    keyCodesHtml.insert(std::make_pair("KeyN", 78));
    keyCodesHtml.insert(std::make_pair("KeyO", 79));
    keyCodesHtml.insert(std::make_pair("KeyP", 80));
    keyCodesHtml.insert(std::make_pair("KeyQ", 81));
    keyCodesHtml.insert(std::make_pair("KeyR", 82));
    keyCodesHtml.insert(std::make_pair("KeyS", 83));
    keyCodesHtml.insert(std::make_pair("KeyT", 84));
    keyCodesHtml.insert(std::make_pair("KeyU", 85));
    keyCodesHtml.insert(std::make_pair("KeyV", 86));
    keyCodesHtml.insert(std::make_pair("KeyW", 87));
    keyCodesHtml.insert(std::make_pair("KeyX", 88));
    keyCodesHtml.insert(std::make_pair("KeyY", 89));
    keyCodesHtml.insert(std::make_pair("KeyZ", 90));

    keyCodesHtml.insert(std::make_pair("Numpad0", 96));
    keyCodesHtml.insert(std::make_pair("Numpad1", 97));
    keyCodesHtml.insert(std::make_pair("Numpad2", 98));
    keyCodesHtml.insert(std::make_pair("Numpad3", 99));
    keyCodesHtml.insert(std::make_pair("Numpad4", 100));
    keyCodesHtml.insert(std::make_pair("Numpad5", 101));
    keyCodesHtml.insert(std::make_pair("Numpad6", 102));
    keyCodesHtml.insert(std::make_pair("Numpad7", 103));
    keyCodesHtml.insert(std::make_pair("Numpad8", 104));
    keyCodesHtml.insert(std::make_pair("Numpad9", 105));
    keyCodesHtml.insert(std::make_pair("NumpadAdd", 107));
    keyCodesHtml.insert(std::make_pair("NumpadSubtract", 109));
    keyCodesHtml.insert(std::make_pair("NumpadDecimal", 110));

    keyCodesHtml.insert(std::make_pair("Comma", 188));
    keyCodesHtml.insert(std::make_pair("Minus", 189));
    keyCodesHtml.insert(std::make_pair("Period", 190));
#else
    keyCodesGlfw.insert(std::make_pair(258, 9)); // Tab
    keyCodesGlfw.insert(std::make_pair(257, 13)); // Enter
    keyCodesGlfw.insert(std::make_pair(340, 16)); // Shift left
    keyCodesGlfw.insert(std::make_pair(344, 16)); // Shift right
    keyCodesGlfw.insert(std::make_pair(341, 17)); // Ctrl left
    keyCodesGlfw.insert(std::make_pair(345, 17)); // Ctrl right
    keyCodesGlfw.insert(std::make_pair(342, 18)); // Alt left
    keyCodesGlfw.insert(std::make_pair(346, 18)); // Alt right
    keyCodesGlfw.insert(std::make_pair(256, 27)); // Escape
    keyCodesGlfw.insert(std::make_pair(32, 32)); // Space

    keyCodesGlfw.insert(std::make_pair(263, 37)); // Arrow left
    keyCodesGlfw.insert(std::make_pair(265, 38)); // Arrow up
    keyCodesGlfw.insert(std::make_pair(262, 39)); // Arrow right
    keyCodesGlfw.insert(std::make_pair(264, 40)); // Arrow down

    keyCodesGlfw.insert(std::make_pair(320, 96)); // Numpad 0
    keyCodesGlfw.insert(std::make_pair(321, 97)); // Numpad 1
    keyCodesGlfw.insert(std::make_pair(322, 98)); // Numpad 2
    keyCodesGlfw.insert(std::make_pair(323, 99)); // Numpad 3
    keyCodesGlfw.insert(std::make_pair(324, 100)); // Numpad 4
    keyCodesGlfw.insert(std::make_pair(325, 101)); // Numpad 5
    keyCodesGlfw.insert(std::make_pair(326, 102)); // Numpad 6
    keyCodesGlfw.insert(std::make_pair(327, 103)); // Numpad 7
    keyCodesGlfw.insert(std::make_pair(328, 104)); // Numpad 8
    keyCodesGlfw.insert(std::make_pair(329, 105)); // Numpad 9
    keyCodesGlfw.insert(std::make_pair(334, 107)); // Numpad add
    keyCodesGlfw.insert(std::make_pair(333, 109)); // Numpad subtract
    keyCodesGlfw.insert(std::make_pair(330, 110)); // Numpad decimal
#endif

    // Setting callbacks
#ifdef __EMSCRIPTEN__
    //EMSCRIPTEN callbacks
    EMSCRIPTEN_RESULT ret = emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &m_WindowData, 1, [](int eventType, const EmscriptenKeyboardEvent *e, void *userData)
    {
        std::string keyCodeHtml(e->code);
        int keyCode = convertHtmlKeyCode(keyCodeHtml);

        WindowData& windowData = *(WindowData*)userData;

        KeyDownEvent event(keyCode, e->repeat);
        windowData.eventCallback(event);

        return 0;
    });
    ret = emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &m_WindowData, 1, [](int eventType, const EmscriptenKeyboardEvent *e, void *userData)
    {
        std::string keyCodeHtml(e->code);
        int keyCode = convertHtmlKeyCode(keyCodeHtml);

        WindowData& windowData = *(WindowData*)userData;

        KeyUpEvent event(keyCode);
        windowData.eventCallback(event);
        return 0;
    });
#else
    //GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
        windowData.width = width;
        windowData.height = height;

        WindowResizeEvent event(width, height);
        windowData.eventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window,[](GLFWwindow* window)
    {
        WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        windowData.eventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
    {
        WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
        keyCode = convertGlfwKeyCode(keyCode);
        switch(action)
        {
            case GLFW_PRESS:
            {
                KeyDownEvent event(keyCode, 0);
                windowData.eventCallback(event);
                break;
            }

            case GLFW_RELEASE:
            {
                KeyUpEvent event(keyCode);
                windowData.eventCallback(event);
                break;
            }

            case GLFW_REPEAT:
                KeyDownEvent event(keyCode, 1);
                windowData.eventCallback(event);
                break;
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
        switch(action)
        {
            case GLFW_PRESS:
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseDownEvent event(button);
                windowData.eventCallback(event);
                break;
            }

            case GLFW_RELEASE:
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseUpEvent event(button);
                windowData.eventCallback(event);
                break;
            }
        }
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
        WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMoveEvent event(x, y);
        windowData.eventCallback(event);
    });
#endif
}

void WindowsWindow::shutdown()
{
    glfwDestroyWindow(m_Window);
}

void WindowsWindow::onUpdate()
{
#ifndef __EMSCRIPTEN__
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
#endif
}

void WindowsWindow::setVSync(bool enabled)
{
    if(enabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
    m_WindowData.vSync = enabled;
}

bool WindowsWindow::isVSync() const
{
    return m_WindowData.vSync;
}

// Key code conversion functions
#ifdef __EMSCRIPTEN__
static int convertHtmlKeyCode(std::string keyCode)
{
    for(auto const& [htmlKeyCode, windowsKeyCode] : keyCodesHtml)
    {
        if(htmlKeyCode == keyCode)
        {
            return windowsKeyCode;
        }
    }
    return -1;
}
#else
static int convertGlfwKeyCode(int keyCode)
{
    // Key codes for digits are the same
    if(keyCode > 47 && keyCode < 58)
    {
        return keyCode;
    }
    // Key codes for letters too
    if(keyCode > 64 && keyCode < 91)
    {
        return keyCode;
    }
    // As is the code for the space key
    if(keyCode == 32)
    {
        return keyCode;
    }
    for(auto const& [glfwKeyCode, windowsKeyCode] : keyCodesGlfw)
    {
        if(glfwKeyCode == keyCode)
        {
            return windowsKeyCode;
        }
    }
    return -1;
}
#endif

