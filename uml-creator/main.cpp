#include <iostream>
#include <memory>

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

std::string vertexShaderSourceTriangle = R"(#version 300 es
                                 layout (location = 0) in vec2 aPos;
                                 layout (location = 1) in vec4 aColor;
                                 out vec4 vColor;
                                 void main()
                                 {
                                    vColor = aColor;
                                    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
                                 })";
std::string fragmentShaderSourceTriangle = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   in vec4 vColor;
                                   void main()
                                   {
                                        FragColor = vColor;
                                   })";

std::string vertexShaderSourceSquare = R"(#version 300 es
                                 layout (location = 0) in vec2 aPos;
                                 void main()
                                 {
                                    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
                                 })";

std::string fragmentShaderSourceSquare = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   void main()
                                   {
                                        FragColor = vec4(0.0f, 0.0f, 1.0f, 0.0f);
                                   })";

GLFWwindow* window;
std::unique_ptr<Shader> shaderTriangle;
std::unique_ptr<Shader> shaderSquare;

std::unique_ptr<VertexArray> vertexArrayTriangle;
std::unique_ptr<VertexArray> vertexArraySquare;

// Render loop. Needs to be a separate function because of Emscripten
void mainLoop()
{
    /* Render here */
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderSquare->bind();
    vertexArraySquare->bind();
    glDrawElements(GL_TRIANGLES, vertexArraySquare->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    shaderTriangle->bind();
    vertexArrayTriangle->bind();
    glDrawElements(GL_TRIANGLES, vertexArrayTriangle->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

}

int main() {
    // Initialize glfw and end program if problem occurred
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating a window and ending program if creation failed
    window = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Setting current window as context
    glfwMakeContextCurrent(window);
#ifndef __EMSCRIPTEN__
    // Loading OpenGL ES2 pointers with glad and ending program if failing to do so
    if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
#endif
    // Create triangle
    float verticesTriangle[18] = {
            -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,// left
            0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,// right
            0.0f, 0.5f,   0.0f, 0.0f, 1.0f, 1.0f// top
    };

    uint32_t indicesTriangle[3] = { 0, 1, 2 };

    std::shared_ptr<VertexBuffer> vertexBufferTriangle;
    std::shared_ptr<IndexBuffer> indexBufferTriangle;

    shaderTriangle.reset(new Shader(vertexShaderSourceTriangle, fragmentShaderSourceTriangle));
    vertexBufferTriangle.reset(VertexBuffer::create(verticesTriangle, sizeof(verticesTriangle)));
    indexBufferTriangle.reset(IndexBuffer::create(indicesTriangle, sizeof(indicesTriangle) / sizeof(uint32_t)));
    vertexArrayTriangle.reset(VertexArray::create());

    vertexArrayTriangle->bind();


    BufferLayout bufferLayoutTriangle =
            {
                    { ShaderDataType::Vec2, "aPosition" },
                    { ShaderDataType::Vec4, "aColor"}
            };
    vertexBufferTriangle->setLayout(bufferLayoutTriangle);
    vertexArrayTriangle->addVertexBuffer(vertexBufferTriangle);
    vertexArrayTriangle->setIndexBuffer(indexBufferTriangle);

    vertexBufferTriangle->unbind();

    float verticesSquare[24] = {
            -0.7f, -0.7f, // left
            -0.7f, 0.7f,  // right
            0.7f, -0.7f,  // top
            0.7f, 0.7f    // top
    };

    uint32_t indicesSquare[6] = { 0, 1, 2, 1, 2, 3 };

    std::shared_ptr<VertexBuffer> vertexBufferSquare;
    std::shared_ptr<IndexBuffer> indexBufferSquare;

    shaderSquare.reset(new Shader(vertexShaderSourceSquare, fragmentShaderSourceSquare));
    vertexBufferSquare.reset(VertexBuffer::create(verticesSquare, sizeof(verticesSquare)));
    indexBufferSquare.reset(IndexBuffer::create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));
    vertexArraySquare.reset(VertexArray::create());

    vertexArraySquare->bind();

    BufferLayout bufferLayoutSquare =
            {
                    { ShaderDataType::Vec2, "aPosition" },
            };
    vertexBufferSquare->setLayout(bufferLayoutSquare);
    vertexArraySquare->addVertexBuffer(vertexBufferSquare);
    vertexArraySquare->setIndexBuffer(indexBufferSquare);

    vertexBufferSquare->unbind();



#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, true);
#else
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        mainLoop();
    }
    glfwTerminate();
#endif
}
