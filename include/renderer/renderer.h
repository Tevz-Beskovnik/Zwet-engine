#pragma once

#include <core.h>
#include <utils.h>
#include <log.h>
#include <scene.h>
#include <attributeLayout.h>
#include <drawer.h>

namespace ZWET
{
    using EntityMap = tsl::hopscotch_map<int, Entity>;

    class Renderer
    {
        public:
            Renderer(Scene& scene, unsigned int fpsCap);

            ~Renderer();

            void init();

            void viewport(size_t x, size_t y, size_t width, size_t height);

            void setWindow(GLFWwindow* window);

            void setFpsCap(unsigned int fpsCap);

            static UniquePtr<Renderer> create(Scene& scene, unsigned int fpsCap);

            void frame();

        private:
            unsigned int fpsCap;
            GLFWwindow* window;
            Scene& scene;
            EntityMap& entities;
            SharedPtr<Camera>& camera;

            void create();
    };
}