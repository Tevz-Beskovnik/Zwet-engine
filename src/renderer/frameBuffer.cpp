#include<frameBuffer.h>

namespace ZWET
{
    FrameBuffer::FrameBuffer(FrameBufferSettings* settings)
        :settings(settings)
    {
        genFrameBuffer(1, frameBuffer);
        genFrameBufferTex(frameBufferTexture);
        genFrameBufferObject(frameBufferObject);
        attachToRenderBuffer(frameBuffer, frameBufferObject, frameBufferTexture);
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &frameBuffer);
        glDeleteRenderbuffers(1, &frameBufferObject);
        glDeleteTextures(1, &frameBufferTexture);
    }

    void FrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    }

    void FrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::attachTexture()
    {
        //do stuff here to attach the texture from the framebuffer
    }

    SharedPtr<FrameBuffer> FrameBuffer::create(FrameBufferSettings* settings)
    {
        return CreateShared<FrameBuffer>(settings);
    }

    void FrameBuffer::genFrameBuffer(size_t amount, unsigned int buffer)
    {
        glGenFramebuffers(amount, &frameBuffer);
    }

    void FrameBuffer::genFrameBufferTex(unsigned int buffer)
    {
        glGenTextures(1, &frameBufferTexture);
        glBindTexture(settings->target, frameBuffer);
        glTexImage2D(
            settings->target, 
            0, 
            settings->internalFormatTexture,
            settings->width,
            settings->height,
            0,
            settings->internalFormatTexture, 
            settings->textureType,
            settings->pixels
        );
        glTexParameteri(
            settings->target,
            GL_TEXTURE_MIN_FILTER,
            settings->minInterpolation
        );
        glTexParameteri(
            settings->target,
            GL_TEXTURE_MAG_FILTER,
            settings->maxInterpolation
        );
    }

    void FrameBuffer::genFrameBufferObject(unsigned int buffer)
    {
        glGenRenderbuffers(1, &frameBufferObject);
        glBindRenderbuffer(GL_RENDERBUFFER, frameBufferObject);
        glRenderbufferStorage(GL_RENDERBUFFER, settings->internalFormatRenderBuffer, settings->width, settings->height);
    }

    void FrameBuffer::attachToRenderBuffer(unsigned int frameBuffer, unsigned int renderBuffer, unsigned int textureBuffer)
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, settings->target, textureBuffer, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
}