#pragma once

#include "../../Renderer/Buffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();
    virtual void bind() const;
    virtual void unbind() const;
private:
    uint32_t m_VboId;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
    virtual ~OpenGLIndexBuffer();
    virtual void bind() const;
    virtual void unbind() const;
    virtual uint32_t getCount() const { return m_Count; }
private:
    uint32_t m_EboId;
    uint32_t m_Count;
};