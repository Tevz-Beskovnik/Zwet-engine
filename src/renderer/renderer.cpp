#include <renderer.h>

namespace ZWET
{
    Renderer::Renderer(SharedPtr<Scene> scene)
        : scene(scene)
    {

    }

    Renderer::~Renderer()
    {

    }

    void Renderer::init()
    {
        #ifdef ZWET_DEBUG
            lEnable(GL_DEBUG_OUTPUT);
		    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		    glDebugMessageCallback(OpenGLMessageCallback, nullptr);
        #endif

        glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
	    glFrontFace(GL_CCW);
	    glCullFace(GL_FRONT);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::viewport(size_t x, size_t y, size_t width, size_t height)
    {
        glViewport(x, y, width, height);
    }

    UniquePtr<Renderer> Renderer::create(SharedPtr<Scene> scene)
    {

    }
    
    void Renderer::frame()
    {

    }
}