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

std::string vertexShaderSource = R"(#version 300 es
                                 layout (location = 0) in vec3 aPos;
                                 void main()
                                 {
                                    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                                 })";
std::string fragmentShaderSource = R"(#version 300 es
                                   precision mediump float;
                                   out vec4 FragColor;
                                   void main()
                                   {
                                      FragColor = vec4(0.0f, 0.8f, 0.8f, 1.0f);
                                   })";

GLFWwindow* window;
std::unique_ptr<Shader> shader;
unsigned int vaoId, vboId;

void mainLoop()
{
    /* Render here */
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->Bind();
    glBindVertexArray(vaoId);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

}

int main() {
    // Initialize glfw and end program if problem ocurred
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

    shader.reset(new Shader(vertexShaderSource, fragmentShaderSource));


    // Create vertex buffer
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.0f, 0.5f, 0.0f  // top
    };

    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &vboId);

    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
