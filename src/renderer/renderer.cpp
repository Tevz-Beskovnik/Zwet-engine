#include <renderer.h>

namespace ZWET
{
    double old = 0;
    void blockFramerate(float fpsCap) {
    	if (old == 0) {
    		old = glfwGetTime();
    	}
    	while (glfwGetTime() - old < 1.0 / fpsCap) {
    	}
    	old = glfwGetTime();
    }

    Renderer::Renderer(Scene& outsideScene, unsigned int fpsCap)
        : scene(outsideScene), entities(scene.getEntities()), camera(scene.getCamera()), fpsCap(fpsCap)
    {
        ;
    }

    Renderer::~Renderer()
    {
        ;
    }

    void Renderer::init()
    {
        create(); 

        #ifdef ZWET_DEBUG
            glEnable(GL_DEBUG_OUTPUT);
		    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
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

    UniquePtr<Renderer> Renderer::create(Scene& scene, unsigned int fpsCap)
    {
        return CreateUnique<Renderer>(scene, fpsCap);
    }
    
    void Renderer::frame()
    {
        blockFramerate(fpsCap);
		// Poll for and process events
		glfwPollEvents();

		glClearColor(0.36862f, 0.20392f, 0.9215686f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.sceneStepFunc();

        for(auto it = entities.begin(); it != entities.end(); it++)
        {
            it.value().vertexBuffer->bind();

            AttributeLayout::setLayout({
                it.value().shader->getProgram(),
                it.value().vertexBuffer->getBuffer(),
                "position",
		        3,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        0
            });

            AttributeLayout::setLayout({
                it.value().shader->getProgram(),
                it.value().vertexBuffer->getBuffer(),
                "iColor",
		        3,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        3 * sizeof(float)
            });

            AttributeLayout::setLayout({
                it.value().shader->getProgram(),
                it.value().vertexBuffer->getBuffer(),
                "iNormal",
		        3,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        6 * sizeof(float)
            });

            AttributeLayout::setLayout({
                it.value().shader->getProgram(),
                it.value().vertexBuffer->getBuffer(),
                "iUV",
		        2,
		        GL_FLOAT,
		        GL_FALSE,
		        11 * sizeof(float),
		        9 * sizeof(float)
            });

            it.value().shader->bind();

            it.value().texture->bind();

            it.value().stepStart(entities, camera);

            it.value().step(entities, camera);

            vec3 camPosition = camera->getPosition();

            mat4 yawRotation = rotY(camera->getYaw());
            mat4 rollRotation = rotZ(camera->getRoll());
            mat4 pitchRotation = rotX(camera->getPitch());

            mat4 world = scene.world;
            mat4 inverseWorld = scene.inverseWorld;
            mat4 view = camera->getView();

            float yaw = camera->getYaw();
            float roll = camera->getRoll();
            float pitch = camera->getPitch();

            unsigned int& program = it.value().shader->getProgram();

            //get uniform locations to bind the predefined uniforms
	        int uTexture = glGetUniformLocation(program, "uTexture");
	        int uWorld = glGetUniformLocation(program, "uWorld");
	        int uWorldInvTran = glGetUniformLocation(program, "uWorldInvTran");
	        int uViewMat = glGetUniformLocation(program, "uViewMat");
	        int uCameraPos = glGetUniformLocation(program, "uCameraPos");
	        int uObjPos = glGetUniformLocation(program, "uObjPos");
	        int uYaw = glGetUniformLocation(program, "uYaw");
	        int uYawMat = glGetUniformLocation(program, "uYawMat");
	        int uPitch = glGetUniformLocation(program, "uPitch");
	        int uPitchMat = glGetUniformLocation(program, "uPitchMat");
	        int uRoll = glGetUniformLocation(program, "uRoll");
	        int uRollMat = glGetUniformLocation(program, "uRollMat");

	        glUniform1i(uTexture, 0);
	        glUniformMatrix4fv(uWorld, 1, GL_FALSE, &world.r[0][0]);
	        glUniformMatrix4fv(uWorldInvTran, 1, GL_FALSE, &inverseWorld.r[0][0]);
	        glUniformMatrix4fv(uViewMat, 1, GL_FALSE, &view.r[0][0]);
	        glUniform3f(uCameraPos, camPosition.x, camPosition.y, camPosition.z);
	        glUniform3f(uObjPos, it.value().position.x, it.value().position.y, it.value().position.z);
	        glUniform1f(uYaw, yaw);
	        glUniform1f(uPitch, pitch);
	        glUniform1f(uRoll, roll);
	        glUniformMatrix4fv(uYawMat, 1, GL_FALSE, &yawRotation.r[0][0]);
	        glUniformMatrix4fv(uPitchMat, 1, GL_FALSE, &pitchRotation.r[0][0]);
	        glUniformMatrix4fv(uRollMat, 1, GL_FALSE, &rollRotation.r[0][0]);

            it.value().stepEnd(entities, camera);

            it.value().drawer->draw();

            it.value().texture->unbind();

            it.value().shader->unbind();

            it.value().vertexBuffer->unbind();
        }

        // Swap front and back buffers
		glfwSwapBuffers(window);
    }

    void Renderer::create()
    {
        scene.sceneCreateFunc();

        for(auto it = entities.begin(); it != entities.end(); it++)
        {
            it.value().createFun(scene.getEntities(), scene.getCamera());
        }
    }

    void Renderer::setWindow(GLFWwindow* newWindow)
    {
        window = newWindow;
    }

    void Renderer::setFpsCap(unsigned int newCap)
    {
        fpsCap = newCap;
    }
}