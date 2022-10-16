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

static std::string vertexShaderSourceTriangle = R"(#version 300 es
                                 layout (location = 0) in vec2 aPos;
                                 layout (location = 1) in vec4 aColor;
                                 out vec4 vColor;
                                 void main()
                                 {
                                    vColor = aColor;
                                    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
                                 })";
static std::string fragmentShaderSourceTriangle = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   in vec4 vColor;
                                   void main()
                                   {
                                        FragColor = vColor;
                                   })";

static std::string vertexShaderSourceSquare = R"(#version 300 es
                                 layout (location = 0) in vec2 aPos;
                                 void main()
                                 {
                                    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
                                 })";

static std::string fragmentShaderSourceSquare = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   void main()
                                   {
                                        FragColor = vec4(0.0f, 0.0f, 1.0f, 0.0f);
                                   })";


static std::unique_ptr<Shader> shaderTriangle;
static std::unique_ptr<Shader> shaderSquare;

static std::unique_ptr<VertexArray> vertexArrayTriangle;
static std::unique_ptr<VertexArray> vertexArraySquare;

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
