#include "Universe_Controller.h"

#include "MemoryLoger.h"

#include <iostream>
#include <memory>

#include "Procedural_Generation.h"
//#include "Lve_model.h"

#include "first_app.h"



namespace Cosmos
{
	
	Universe_Controller::Universe_Controller()
	{

	}

	Universe_Controller::~Universe_Controller()
	{

	}

	void Universe_Controller::loop(GLFWwindow* window, lve::FrameInfo& frameInfo)
	{


		//std::cout << "Frame : " << frameInfo.frameIndex << "\n"; //It's just oscilating betwen 0 and 1
		//std::cout << "Time for one frame" << frameInfo.frameTime << "\n";
		ellapsed_time += frameInfo.frameTime;


		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			this->call_generate = true;
		}

		// - Deleting objects
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			//std::cout << ellapsed_time << "\n";

			//frameInfo.gameObjects.empty();

			for (auto& kv : frameInfo.gameObjects) {
				auto& obj = kv.second;
				if (obj.model != nullptr) {//if (obj.model == nullptr) {
					if (obj.cosmos_object_state == nullptr)
					{
						obj.cosmos_object_state = std::make_unique<lve::CosmosObjectState>();
						obj.cosmos_object_state->mark_as_invisible = true;
						break;
					}
				}
			}
		}

		// - Number of game objects
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			std::cout << "gameObjects size : " << frameInfo.gameObjects.size() << "\n";
		}

		//MY - delete unmapped object market for deleting
		
		unsigned int id_to_delete;
		bool delete_the_id = false;
		for (auto& kv : frameInfo.gameObjects) {
			auto& obj = kv.second;
			if (obj.cosmos_object_state != nullptr)
			{
				if (obj.cosmos_object_state->ready_for_deletion)
				{
					id_to_delete = obj.getId();
					delete_the_id = true;
					break;
				}
			}
		}

		if (delete_the_id)
		{
			
			frameInfo.gameObjects.erase(id_to_delete);
			
			std::cout << "After erase gameObjects size : " << frameInfo.gameObjects.size() << "\n";
			std::cout << "Memory current usage : " << s_allocationsMetrics.CurrentUsage() << "\n";
		}
		
		

		/*
		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (gameObjects[i].my_to_be_deleted_as_unmaped)
			{
				gameObjects.erase(gameObjects.begin() + i);
				break;
			}
		}
		*/
		

	}
}

