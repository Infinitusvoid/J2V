#include "first_app.h"

#include "keybord_movement_controller.h"
#include "lve_buffer.h"
#include "lve_camera.h"
#include "simple_render_system.h"
#include "point_light_system.h"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <chrono>
#include <stdexcept>

// cosmos
#include "Procedural_Generation.h"


#include "Data_Types.h"

#include <iostream>

#include <thread>

namespace lve {

    

    FirstApp::FirstApp() {
        globalPool =
            LveDescriptorPool::Builder(lveDevice)
            .setMaxSets(LveSwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, LveSwapChain::MAX_FRAMES_IN_FLIGHT)
            .build();
        loadGameObjects();
    }

    FirstApp::~FirstApp() {}

    


    void FirstApp::run() {
        std::vector<std::unique_ptr<LveBuffer>> uboBuffers(LveSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++) {
            uboBuffers[i] = std::make_unique<LveBuffer>(
                lveDevice,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

        auto globalSetLayout =
            LveDescriptorSetLayout::Builder(lveDevice)
            .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
            .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(LveSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); i++) {
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            LveDescriptorWriter(*globalSetLayout, *globalPool)
                .writeBuffer(0, &bufferInfo)
                .build(globalDescriptorSets[i]);
        }

        SimpleRenderSystem simpleRenderSystem{
            lveDevice,
            lveRenderer.getSwapChainRenderPass(),
            globalSetLayout->getDescriptorSetLayout() };
        PointLightSystem pointLightSystem{
            lveDevice,
            lveRenderer.getSwapChainRenderPass(),
            globalSetLayout->getDescriptorSetLayout() };
        LveCamera camera{};

        auto viewerObject = LveGameObject::createGameObject();
        viewerObject.transform.translation.z = -2.5f;
        KeyboardMovementController cameraController{};

        //cosmos
        Cosmos::Controller::Initialization();
        Cosmos::Tonix tonix;
        //std::thread worker([&tonix]() {tonix.run_foo(); });
        std::thread worker([&tonix]() { tonix.run(); });
        //end cosmos

        auto currentTime = std::chrono::high_resolution_clock::now();
        while (!lveWindow.shouldClose()) {
            glfwPollEvents();

            // Cosmos
            if (Cosmos::Controller::get_generate_value())//universe_con.call_generate)
            {
                Cosmos::Controller::set_generate(false);
                My_ProcedurallyGenerateNewObject_Cosmos();
                std::cout << "Generated!" << std::endl;
            }

            if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_SPACE) == GLFW_PRESS) { //GLFW_KEY_K) == GLFW_PRESS) { // I Need to remove this
                My_ProcedurallyGenerateNewObject_2();
            }

            if (glfwGetKey(lveWindow.getGLFWwindow(), GLFW_KEY_R) == GLFW_PRESS)
            {
                //std::cout << "press the key R" << std::endl;
                if (tonix.state == Cosmos::Tonix::state_idle)
                {
                    tonix.state = Cosmos::Tonix::state_compute;
                }
                

            }

            if (tonix.state == Cosmos::Tonix::state_done)
            {
                //read data, after all data is read set it to idle
                My_ProceduralReadFromTonix(tonix);
                std::cout << "Computation in tonix done read data!" << std::endl;
                tonix.state = Cosmos::Tonix::state_idle;
                
            }
            // Cosmos

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime =
                std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(lveWindow.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = lveRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

            if (auto commandBuffer = lveRenderer.beginFrame()) {
                int frameIndex = lveRenderer.getFrameIndex();
                FrameInfo frameInfo{
                    frameIndex,
                    frameTime,
                    commandBuffer,
                    camera,
                    globalDescriptorSets[frameIndex],
                    gameObjects };

                //cosmos update
                Cosmos::Controller::loop(lveWindow.getGLFWwindow(), frameInfo);

                // update
                GlobalUbo ubo{};
                ubo.projection = camera.getProjection();
                ubo.view = camera.getView();
                ubo.inverseView = camera.getInverseView();
                pointLightSystem.update(frameInfo, ubo);
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // render
                lveRenderer.beginSwapChainRenderPass(commandBuffer);
                
                // order here matters
                simpleRenderSystem.renderGameObjects(frameInfo);
                pointLightSystem.render(frameInfo);
                
                
                lveRenderer.endSwapChainRenderPass(commandBuffer);
                lveRenderer.endFrame();
            }
        }

        //Cosmos
        std::cout << "YEY COSMOS" << std::endl;
        tonix.continue_executing = false;
        //Cosmos::Tonix::cosmos_compute = false;
       
        worker.join();
        //Cosmos end


        vkDeviceWaitIdle(lveDevice.device());
    }

    void FirstApp::loadGameObjects() {
        std::shared_ptr<Lve_model> lveModel =
            Lve_model::createModelFromFile(lveDevice, "models/flat_vase.obj");
        auto flatVase = LveGameObject::createGameObject();
        flatVase.model = lveModel;
        flatVase.transform.translation = { -.5f, .5f, 0.f };
        flatVase.transform.scale = { 3.f, 1.5f, 3.f };
        gameObjects.emplace(flatVase.getId(), std::move(flatVase));

        lveModel = Lve_model::createModelFromFile(lveDevice, "models/smooth_vase.obj");
        auto smoothVase = LveGameObject::createGameObject();
        smoothVase.model = lveModel;
        smoothVase.transform.translation = { .5f, .5f, 0.f };
        smoothVase.transform.scale = { 3.f, 1.5f, 3.f };
        gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

        lveModel = Lve_model::createModelFromFile(lveDevice, "models/quad.obj");
        auto floor = LveGameObject::createGameObject();
        floor.model = lveModel;
        floor.transform.translation = { 0.f, .5f, 0.f };
        floor.transform.scale = { 3.f, 1.f, 3.f };
        gameObjects.emplace(floor.getId(), std::move(floor));

        My_ProcedurallyGenerateNewObject_2();

        std::vector<glm::vec3> lightColors{
        {1.f, .1f, .1f},
        {.1f, .1f, 1.f},
        {.1f, 1.f, .1f},
        {1.f, 1.f, .1f},
        {.1f, 1.f, 1.f},
        {1.f, 1.f, 1.f}  //
        };

        for (int i = 0; i < lightColors.size(); i++) {
            auto pointLight = LveGameObject::makePointLight(0.2f);
            pointLight.color = lightColors[i];
            auto rotateLight = glm::rotate(
                glm::mat4(1.f),
                (i * glm::two_pi<float>()) / lightColors.size(),
                { 0.f, -1.f, 0.f });
            pointLight.transform.translation = glm::vec3(rotateLight * glm::vec4(-1.f, -1.f, -1.f, 1.f));
            gameObjects.emplace(pointLight.getId(), std::move(pointLight));
        }
        
    }


    void FirstApp::My_ProcedurallyGenerateNewObject_Cosmos()
    {
        

    }

    
    void FirstApp::My_ProceduralReadFromTonix(const Cosmos::Tonix& tonix)
    {
        
        if (tonix.model_builders.size() > 0)
        {
            for (int i = 0; i < tonix.model_builders.size(); i++)
            {
                std::shared_ptr<Lve_model> lveModel = std::make_unique<Lve_model>(lveDevice, *tonix.model_builders[i]);
                auto proc_gm = LveGameObject::createGameObject();
                proc_gm.model = lveModel;
                proc_gm.transform.translation = tonix.data[i]->position;
                proc_gm.transform.scale = tonix.data[i]->scale;
                proc_gm.transform.rotation = tonix.data[i]->rotation;
                gameObjects.emplace(proc_gm.getId(), std::move(proc_gm));
            }
        }
        

        //if (tonix.data.size() > 0)
        //{
        //    for (Cosmos::Data_Types::Object3d_Data* data_obj : tonix.data)//for (Proc::Procedural_ObjectData* data_obj : pc.data)
        //    {
        //        Lve_model::Builder modelBuilder{};
        //        //modelBuilder.vertices = std::vector<Lve_model::Vertex>(data_obj->vertices.size());
        //        
        //        
        //        //int size = data_obj->vertices.size();//data_obj->vertices.size();

        //       

        //        modelBuilder.vertices = std::vector<Lve_model::Vertex>();//size);
        //        for (const Cosmos::Data_Types::Vert& vert : data_obj->vertices)//for (const Proc::Vert& vert : data_obj->vertices)
        //        {
        //            modelBuilder.vertices.push_back(
        //                {  { vert.position.x, vert.position.y, vert.position.z },
        //                                                { vert.color.r, vert.color.g, vert.color.b },
        //                                                { vert.normal.x, vert.normal.y, vert.normal.z}
        //                                             } 
        //            );
        //        }

        //        modelBuilder.indices = std::vector<uint32_t>(data_obj->indices);

        //        std::shared_ptr<Lve_model> lveModel = std::make_unique<Lve_model>(lveDevice, modelBuilder);
        //        auto proc_gm = LveGameObject::createGameObject();
        //        proc_gm.model = lveModel;
        //        proc_gm.transform.translation = data_obj->position;
        //        proc_gm.transform.scale = data_obj->scale;
        //        proc_gm.transform.rotation = data_obj->rotation;
        //        //gameObjects.push_back(std::move(proc_gm));
        //        gameObjects.emplace(proc_gm.getId(), std::move(proc_gm));
        //    }
        //}
    }


  
    void FirstApp::My_ProcedurallyGenerateNewObject_2()
    {
        //PrintMemoryUsage();
        {

            Proc::Procedural_Generation pc;
            if (pc.data.size() > 0)
            {

                for(Cosmos::Data_Types::Object3d_Data* data_obj : pc.data)//for (Proc::Procedural_ObjectData* data_obj : pc.data)
                {
                    Lve_model::Builder modelBuilder{};
                    modelBuilder.vertices = std::vector<Lve_model::Vertex>(data_obj->vertices.size());

                    modelBuilder.vertices = std::vector<Lve_model::Vertex>();
                    for (const Cosmos::Data_Types::Vert& vert : data_obj->vertices)//for (const Proc::Vert& vert : data_obj->vertices)
                    {
                        modelBuilder.vertices.push_back({ { vert.position.x, vert.position.y, vert.position.z }, { vert.color.r, vert.color.g, vert.color.b }, {vert.normal.x, vert.normal.y, vert.normal.z} });
                    }

                    modelBuilder.indices = std::vector<uint32_t>(data_obj->indices);

                    std::shared_ptr<Lve_model> lveModel = std::make_unique<Lve_model>(lveDevice, modelBuilder);
                    auto proc_gm = LveGameObject::createGameObject();
                    proc_gm.model = lveModel;
                    proc_gm.transform.translation = data_obj->position;
                    proc_gm.transform.scale = data_obj->scale;
                    proc_gm.transform.rotation = data_obj->rotation;
                    //gameObjects.push_back(std::move(proc_gm));
                    gameObjects.emplace(proc_gm.getId(), std::move(proc_gm));
                }
            }
        }

    }

}  // namespace lve