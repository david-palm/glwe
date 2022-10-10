#include "Application.h"
Application::Application(){

}
Application::~Application(){

}
void Application::run(){
    while(true);
}

int main(){
    Application* application = new Application();
    application->run();
    delete application;
}