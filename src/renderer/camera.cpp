#include <camera.h>

namespace ZWET 
{
    Camera::Camera(float x, float y, float z)
        :position({x, y, z})
    {
        ;
    }

    Camera::~Camera()
    {
        ;
    }

    void Camera::create3d(int width, int height, float fFar, float fNear, float fov)
    {
        const float fovRad = 1 / tanf(fov * 0.5f / 180.0f * (float)PI);

        const float aspectRatio = (float)height / (float)width;

        camera = {
	    	aspectRatio * fovRad, 0.0f, 0.0f, 0.0f,
	    	0.0f, fovRad, 0.0f, 0.0f,
	    	0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
	    	0.0f, 0.0f, (-fFar * fNear) / (fFar - fNear), 0.0f
	    };
    }

    void Camera::create2d()
    {

    }

    SharedPtr<Camera> Camera::create(float x, float y, float z)
    {
        return CreateUnique<Camera>(x, y, z);
    }

    void Camera::create()
    {
        viewMat();
    }

    void Camera::step()
    {
        //std::cout << position.x << " " << position.y << " " << position.z << std::endl;

        viewMat();
    }

    void Camera::viewMat()
    {
        position = position + (lookDir * forward) + (lookDirSqued * sideways) + (lookDirSquedUp * vertical);
        
        vec3 vTargetF = { 1.0f, 0.0f, 0.0f };
        
        mat4 mCameraRot = rotY(yaw);
        
        lookDir = customVecMultiply(mCameraRot, vTargetF);
        lookDirSqued = customVecMultiply(mCameraRot, { 0.0f, 1.0f, 0.0f });
        lookDirSquedUp = customVecMultiply(mCameraRot, { 0.0f, 0.0f, 1.0f});
        
        vTargetF = position + lookDir;
        
        view = createViewMatrix(camera, position, vTargetF, up, pitch, 0.0f, 0.0f);
    }
}