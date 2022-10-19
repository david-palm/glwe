#include "WindowsWindow.h"

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
}

void WindowsWindow::shutdown()
{
    glfwDestroyWindow(m_Window);
}

void WindowsWindow::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
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

