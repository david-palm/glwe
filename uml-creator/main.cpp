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

std::string vertexShaderSource = R"(#version 300 es
                                 layout (location = 0) in vec2 aPos;
                                 layout (location = 1) in vec4 aColor;
                                 out vec4 vColor;
                                 void main()
                                 {
                                    vColor = aColor;
                                    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
                                 })";
std::string fragmentShaderSource = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   in vec4 vColor;
                                   void main()
                                   {
                                      //FragColor = vec4(0.0f, 0.8f, 0.8f, 1.0f);
                                        FragColor = vColor;
                                   })";

GLFWwindow* window;
std::unique_ptr<Shader> shader;
std::unique_ptr<VertexBuffer> vertexBuffer;
std::unique_ptr<IndexBuffer> indexBuffer;
unsigned int vaoId, vboId;

// Render loop. Needs to be a separate function because of Emscripten
void mainLoop()
{
    /* Render here */
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->bind();
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);

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
    // Create vertex buffer
    float vertices[18] = {
            -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,// left
            0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,// right
            0.0f, 0.5f,   0.0f, 0.0f, 1.0f, 1.0f// top
    };

    uint32_t indices[3] = { 0, 1, 2 };

    shader.reset(new Shader(vertexShaderSource, fragmentShaderSource));
    vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
    indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));

    glGenVertexArrays(1, &vaoId);

    glBindVertexArray(vaoId);

    vertexBuffer->bind();
    indexBuffer->bind();

    BufferLayout bufferLayout =
            {
                    { ShaderDataType::Vec2, "aPosition" },
                    { ShaderDataType::Vec4, "aColor"}
            };

    uint32_t index = 0;
    for(const auto& element: bufferLayout)
    {
        glVertexAttribPointer(index,
                              element.getComponentCount(),
                              convertShaderDataTypeToGLBaseType(element.getDataType()),
                              element.isNormalized() ? GL_TRUE : GL_FALSE,
                              bufferLayout.getStride(),
                              (void *) element.getOffset());
        glEnableVertexAttribArray(index);
        index++;
    }

    vertexBuffer->unbind();

    glBindVertexArray(0);

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
