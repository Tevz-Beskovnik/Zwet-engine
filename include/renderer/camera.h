#pragma once

#include <core.h>
#include <structs.h>
#include <utils.h>
#include <vecCalc.h>
#include <keyInput.h>

namespace ZWET
{
    class Camera
    {
        public:
            Camera(float x, float y, float z);

            ~Camera();

            void create3d(int width, int height, float fFar, float fNear, float fov);

            void create2d();

            void create();

            void step();

            mat4& getCamera();

            mat4& getView();

            vec3& getPosition();

            float& getYaw();

            float& getRoll();

            float& getPitch();

            float& getForward();

            float& getSideways();

            float& getVertical();

            static SharedPtr<Camera> create(float x, float y, float z);

        protected:

            vec3 position;
            vec3 lookDir = { 0.0f, 0.0f, 1.0f };
	        vec3 lookDirSqued = { 1.0f, 0.0f, 0.0f };
	        vec3 lookDirSquedUp = { 0.0f, 1.0f, 0.0f };
	        vec3 up = { 0.0f, 1.0f, 0.0f };

            float yaw = 0.0f;
            float roll = 0.0f;
            float pitch = 0.0f;
	        float forward = 0.0f;   
	        float sideways = 0.0f;
	        float vertical = 0.0f;

            mat4 camera;
            mat4 view;

            void viewMat();
    };
}