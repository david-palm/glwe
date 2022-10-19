#include "Application.h"


#ifdef __EMSCRIPTEN__

static inline const char *emscripten_event_type_to_string(int eventType) {
    const char *events[] = { "(invalid)", "(none)", "keypress", "keydown", "keyup", "click", "mousedown", "mouseup", "dblclick", "mousemove", "wheel", "resize",
                             "scroll", "blur", "focus", "focusin", "focusout", "deviceorientation", "devicemotion", "orientationchange", "fullscreenchange", "pointerlockchange",
                             "visibilitychange", "touchstart", "touchend", "touchmove", "touchcancel", "gamepadconnected", "gamepaddisconnected", "beforeunload",
                             "batterychargingchange", "batterylevelchange", "webglcontextlost", "webglcontextrestored", "mouseenter", "mouseleave", "mouseover", "mouseout", "(invalid)" };
    ++eventType;
    if (eventType < 0) eventType = 0;
    if (eventType >= sizeof(events)/sizeof(events[0])) eventType = sizeof(events)/sizeof(events[0])-1;
    return events[eventType];
}

const char *emscripten_result_to_string(EMSCRIPTEN_RESULT result) {
  if (result == EMSCRIPTEN_RESULT_SUCCESS) return "EMSCRIPTEN_RESULT_SUCCESS";
  if (result == EMSCRIPTEN_RESULT_DEFERRED) return "EMSCRIPTEN_RESULT_DEFERRED";
  if (result == EMSCRIPTEN_RESULT_NOT_SUPPORTED) return "EMSCRIPTEN_RESULT_NOT_SUPPORTED";
  if (result == EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED) return "EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED";
  if (result == EMSCRIPTEN_RESULT_INVALID_TARGET) return "EMSCRIPTEN_RESULT_INVALID_TARGET";
  if (result == EMSCRIPTEN_RESULT_UNKNOWN_TARGET) return "EMSCRIPTEN_RESULT_UNKNOWN_TARGET";
  if (result == EMSCRIPTEN_RESULT_INVALID_PARAM) return "EMSCRIPTEN_RESULT_INVALID_PARAM";
  if (result == EMSCRIPTEN_RESULT_FAILED) return "EMSCRIPTEN_RESULT_FAILED";
  if (result == EMSCRIPTEN_RESULT_NO_DATA) return "EMSCRIPTEN_RESULT_NO_DATA";
  return "Unknown EMSCRIPTEN_RESULT!";
}

#define TEST_RESULT(x) if (ret != EMSCRIPTEN_RESULT_SUCCESS) printf("%s returned %s.\n", #x, emscripten_result_to_string(ret));

EM_BOOL key_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
    printf("%s, key: \"%s\", code: \"%s\", location: %lu,%s%s%s%s repeat: %d, locale: \"%s\", char: \"%s\", charCode: %lu, keyCode: %lu, which: %lu, timestamp: %lf\n",
           emscripten_event_type_to_string(eventType), e->key, e->code, e->location,
           e->ctrlKey ? " CTRL" : " NCTRL", e->shiftKey ? " SHIFT" : " NSHIFT", e->altKey ? " ALT" : " NALT", e->metaKey ? " META" : " NMETA",
           e->repeat, e->locale, e->charValue, e->charCode, e->keyCode, e->which,
           e->timestamp);
    return 0;
}

#endif

Application::Application()
{
#ifdef __EMSCRIPTEN__
    // Key callback test
    EMSCRIPTEN_RESULT ret = emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, key_callback);
#endif
    // Initialize glfw and end program if problem occurred
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = std::unique_ptr<Window>(Window::create());

#ifndef __EMSCRIPTEN__
    // Loading OpenGL ES2 pointers with glad and ending program if failing to do so
    if (!gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
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

    m_Running = true;

    run();

}
Application::~Application()
{

}

void Application::run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, true);
#else
    /* Loop until the user closes the window */
    while (m_Running)
    {
        runLoop();
    }
    glfwTerminate();
#endif
}

// EMSCRIPTEN requirement: main loop needs to be separate function
void Application::runLoop()
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

    m_Window->onUpdate();
}