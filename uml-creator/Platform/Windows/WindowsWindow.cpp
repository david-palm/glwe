#include "WindowsWindow.h"

#include "../../Events/WindowEvents.h"
#include "../../Events/KeyEvent.h"


static bool s_GLFWInitialized = false;

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


    // Setting callbacks
#ifdef __EMSCRIPTEN__
    //EMSCRIPTEN callbacks
    EMSCRIPTEN_RESULT ret = emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &m_WindowData, 1, [](int eventType, const EmscriptenKeyboardEvent *e, void *userData)
    {
        const char *keyA = "KeyA";
        if(std::strcmp(e->code, keyA) == 0)
        {
            WindowData& windowData = *(WindowData*)userData;

            KeyDownEvent event(65, 0);
            windowData.eventCallback(event);
        }
        return 0;
    });
    ret = emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, &m_WindowData, 1, [](int eventType, const EmscriptenKeyboardEvent *e, void *userData)
    {
        const char *keyA = "KeyA";
        if(std::strcmp(e->code, keyA) == 0)
        {
            WindowData& windowData = *(WindowData*)userData;

            KeyUpEvent event(65);
            windowData.eventCallback(event);
        }
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
        }
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

