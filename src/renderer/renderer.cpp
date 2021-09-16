#include <renderer.h>

namespace ZWET
{
    Renderer::Renderer(SharedPtr<Scene>& outsideScene)
        : scene(outsideScene), entities(scene->getEntities()), camera(scene->getCamera())
    {
        ;
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::init()
    {
        #ifdef ZWET_DEBUG
            glEnable(GL_DEBUG_OUTPUT);
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

    UniquePtr<Renderer> Renderer::create(SharedPtr<Scene>& scene)
    {
        return CreateUnique<Renderer>(scene);
    }
    
    void Renderer::frame()
    {
        scene->sceneStepFunc();

        for(auto it = entities.begin(); it != entities.end(); it++)
        {
            it.value()->shader->bind();

            it.value()->stepStart(entities, camera);

            it.value()->step(entities, camera);

            it.value()->stepEnd(entities, camera);
        }
    }

    void Renderer::create()
    {
        scene->sceneCreateFunc();

        for(auto it = entities.begin(); it != entities.end(); it++)
        {
            it.value()->createFun(scene->getEntities(), scene->getCamera());

            AttributeLayout::setLayout({
                it.value()->shader->getProgram(),
                it.value()->vertexBuffer->getBuffer(),
                "position",
		        3,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        0
            });

            AttributeLayout::setLayout({
                it.value()->shader->getProgram(),
                it.value()->vertexBuffer->getBuffer(),
                "iColor",
		        3,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        3 * sizeof(float)
            });

            AttributeLayout::setLayout({
                it.value()->shader->getProgram(),
                it.value()->vertexBuffer->getBuffer(),
                "iNormal",
		        3,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        6 * sizeof(float)
            });

            AttributeLayout::setLayout({
                it.value()->shader->getProgram(),
                it.value()->vertexBuffer->getBuffer(),
                "iUV",
		        2,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        9 * sizeof(float)
            });
        }
    }
}