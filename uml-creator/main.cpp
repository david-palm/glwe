#include "Application.h"
Application* application;

int main()
{
    application = new Application();
    delete application;
}

void mainLoop()
{
    application->runLoop();
}