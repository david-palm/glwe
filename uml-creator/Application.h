#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GLFW_INCLUDE_ES3
#include "GLFW/glfw3.h"
#else
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#endif

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

void mainLoop();

class Application{
public:
    Application();
    ~Application();
    static Application& get() { return *s_Instance; }
    void runLoop();
private:
    void run();
private:
    static Application* s_Instance;
    bool m_Running = false;
    GLFWwindow* window;
};
