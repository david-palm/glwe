#pragma once
#include <string>

class Shader{
public:
    Shader();
    Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    ~Shader();

    void Bind() const;
    void Unbind() const;
private:
    uint32_t m_ProgramId;
};
