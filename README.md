Zwet-engine
=======

![Newest realease](https://img.shields.io/github/v/release/tevzi2/Zwet-engine?include_prereleases)

Zwet-engine is a multy platform game engine that currently works on **Linux** and **MacOS**


## CURRENT FEATURES

* scene scripting in json,
* game object scripting in C++,
* shader binding to objects,
* texture binding to objects,
* model assignment.


## FEATURES IN THE WORKS

* font rendering,
* audio implementations,
* 3D animations.


## DEPENDENCIES

Zwet-engine uses the following dependencies:

* GLFW 3.3.4
* GLEW 2.2.0
* OpenAL 1.21.0
* Assimp 5.0.1
* tsl-hopscotch-map 2.3.0
* simdjson 0.9.7


## SETTING UP ZWET-ENGINE

### INSTALLING DEPENDENCIES

After you download it on a valid operating system you want to make sure you have the cmake, make and conan tool chains installed.

Now that you have those installed you want to move to your folder conataining the project and open it in terminal and install the dependencies by running the following command:

 ```
 conan install conanfile.txt
 ```
Now that you have all the dependencies installed we have to build it, so in your project create a build folder and move to it in the terminal. To build it run:

```
cmake ..
make
```
This should build the test.

### SETTING UP THE ENGINE

First you want to include the engine in your project:

```cpp
#include<zwet.h>
```

Then you want to setup the render, scene and window:

```cpp
std::string path = "path/to/your/scene/";

Application testApp; // create a instance of the Application class
    
testApp.setFpsCap(60); // set the fps cap
    
testApp.setWindowDims(2560, 1600); // set the window dims
    
Scene scene(path + "scenes/sceneExample.json"); // set the game scene
    
SharedPtr<Camera> camera = Camera::create(0, 0, 0); // create a 3D camera
    
camera->create3d(2560, 1600, 1000.0f, 0.1f, 90); // setup the camera

scene.setCamera(camera); // set the camera to the scene
```

Then you want to create some entities, to create entities you want to create a derived class from the `Entity` class:

```cpp
using namespace ZWET; // let cpp know we are using the ZWET namespace here

using EntityMap = tsl::hopscotch_map<int, SharedPtr<Entity>>; // this is just to make some things easier

class CubeEntityCam : public Entity
{
    public:
        std::string classFamily = "cube"; // the name of the entity

        float entityYaw = 0.0f;
        float entityPitch = 0.0f;

        std::string getFamilyName()
        {
            return classFamily; // function that returns the name of the entity
        }

        void createFun(EntityMap& entityMap, SharedPtr<Camera>& cam)
        {
            std::cout << "Yes hello this is the create function" << std::endl;
        }

        void step(EntityMap& entityMap, SharedPtr<Camera>& cam, double delta)
        {
            float& yaw = cam->getYaw();
            float& pitch = cam->getPitch();
            float& forward = cam->getForward();
            float& sideways = cam->getSideways();
            vec3& pos = cam->getPosition();

            std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;

            /*movement mods for by how muh it should increase the movement speed*/
            const float movementMod = 0.08f;
            const float yawMod = 0.03f;

            //camera controls for yaw and pitch
            pitch += (-yawMod * keyBoard->isKeyHeld(GLFW_KEY_DOWN) + yawMod * keyBoard->isKeyHeld(GLFW_KEY_UP));
            yaw += (-yawMod * keyBoard->isKeyHeld(GLFW_KEY_RIGHT) + yawMod * keyBoard->isKeyHeld(GLFW_KEY_LEFT));

            //camera controls for movement
            pos.y += (movementMod * keyBoard->isKeyHeld(GLFW_KEY_SPACE)) + (-movementMod * keyBoard->isKeyHeld(GLFW_KEY_LEFT_SHIFT));
            forward = ((movementMod * keyBoard->isKeyHeld(GLFW_KEY_W)) + (-movementMod * keyBoard->isKeyHeld(GLFW_KEY_S)));
            sideways = ((-movementMod * keyBoard->isKeyHeld(GLFW_KEY_A)) + (movementMod * keyBoard->isKeyHeld(GLFW_KEY_D)));

            int yawLoc = glGetUniformLocation(shader->getProgram(), "objYaw");
            int pitchLoc = glGetUniformLocation(shader->getProgram(), "objPitch");

            mat4 objYaw = rotY(entityYaw);
            mat4 objPicth = rotX(entityPitch);

            glUniformMatrix4fv(yawLoc, 1, GL_FALSE, &objYaw.r[0][0]);
            glUniformMatrix4fv(pitchLoc, 1, GL_FALSE, &objPicth.r[0][0]);
        }
};
```
This entity sets up the controls for the camera. The entity class has 4 types of functions you can define:
* **createFun**: This function only runs once and is called before the render cycle.
* **stepStart**: This function runs every render call before the start of uniform and texture binding.
* **step**: Function that runs mid texture, function, buffer etc. binds (used for binding uniforms for shaders).
* **stepEnd**: Function called after the end of the render call.

Now that you have a entity you want to add it to the scene and start the your game:
```cpp
SharedPtr<Entity> ent = CreateShared<CubeEntityCam>(); // create a pointer to the class

scene.registerEntity(ent); // register the entity to the scene
    
testApp.setScene(scene); // finnaly set the scene

testApp.run(); // run the application
```


### EDITING THE SCENE

You can edit, move, rotate, apply textures, meshes and colors to game objects without writting much code, becouse the scene is setup when the game opens by just simply edeting the scene as it is seen in the **test** folder. Here is a example scene:

```json
{
  "scene": [
    {
      "entity": {
        "name": "cube",
        "position": {
          "x": 7,
          "y": 3,
          "z": 0
        },
        "static_rotation": {
          "x": 0,
          "y": 0,
          "z": 0
        },
        "dynamic_rotation": {
          "x": 0,
          "y": 0,
          "z": 0
        },
        "rgb": {
          "r": 1,
          "g": 1,
          "b": 1
        },
        "velocity": {
          "x": 0,
          "y": 0,
          "z": 0
        },
        "weight": 0,
        "physics": false,
        "texture_path": "/Users/usr/documents/programing/Zwet-Engine/test/resources/textures/lol.jpg",
        "model_location": "/Users/usr/documents/programing/Zwet-Engine/test/resources/models/cube2.obj",
        "vertex_shader": "/Users/usr/documents/programing/Zwet-Engine/test/resources/shaders/vertCube.glsl",
        "fragment_shader": "/Users/usr/documents/programing/Zwet-Engine/test/resources/shaders/frag.glsl"
      }
    }
  ]
}
```
