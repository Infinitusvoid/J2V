#include "Universe_Controller.h"

#include "MemoryLoger.h"

#include <iostream>
#include <memory>

#include "Procedural_Generation.h"
//#include "Lve_model.h"

#include "first_app.h"

#include <functional>

namespace Cosmos
{
	namespace UI_GLFW_GLOBAL
	{
		Universe_Controller* uc;

		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
		{
			if (uc != nullptr)
			{
				uc->scroll_callback_2(yoffset);
			}
		}
	}


	Universe_Controller::Universe_Controller()
	{
		first_loop_cycle = true;
		Cosmos::UI_GLFW_GLOBAL::uc = this;
	}

	Universe_Controller::~Universe_Controller()
	{
		Cosmos::UI_GLFW_GLOBAL::uc = nullptr;
	}


	void Universe_Controller::scroll_callback_2(float y)
	{
		std::cout << "Callback y : " << y << std::endl;
	}
	
	void Universe_Controller::init(GLFWwindow* window, lve::FrameInfo& frameInfo)
	{
		std::cout << "-- Init --" << std::endl;
		glfwSetScrollCallback(window, Cosmos::UI_GLFW_GLOBAL::scroll_callback);

	}

	void Universe_Controller::loop(GLFWwindow* window, lve::FrameInfo& frameInfo)
	{
		if (first_loop_cycle)
		{
			first_loop_cycle = false; //TODO : it would be cool if I could somehow have varible that I can only set to false never to true
			init(window, frameInfo);
		}

		//std::cout << "offset Y " << UI_GLFW_GLOBAL::y_offset << std::endl;

		//TODO make is using callback insted of this
		// learning keybord input
		{
			int state = glfwGetKey(window, GLFW_KEY_T);
			if (state == GLFW_PRESS)
			{
			//	std::cout << "key T pressed!" << std::endl;
			}
			else if (state == GLFW_RELEASE)
			{
			//	std::cout << "key T released!" << std::endl;
			}
		}

		//mouse position
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			//std::cout << "xpos : " << xpos << " ypos : " << ypos << std::endl;
		}

		{
			int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
			if (state == GLFW_PRESS)
			{
				std::cout << "Mouse left click!" << std::endl;
			}
		}

		{
			int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
			if (state == GLFW_PRESS)
			{
				std::cout << "Mouse right click!" << std::endl;
			}
		}

		{
			int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
			if (state == GLFW_PRESS)
			{
				std::cout << "Mouse middle click!" << std::endl;
			}
		}
		
		// end learning keybord input

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

