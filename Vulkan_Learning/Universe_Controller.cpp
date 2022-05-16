#include "Universe_Controller.h"

#include <iostream>
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

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
			std::cout << ellapsed_time << "\n";

			frameInfo.gameObjects.empty();
		}


	}
}

