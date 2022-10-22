#ifdef __EMSCRIPTEN__
#include <Emscripten.h>
#endif
#include "Application.h"

Application* application;


int main()
{
    application = new Application();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, true);
#endif
    delete application;
}

void mainLoop()
{
    application->runLoop();
}