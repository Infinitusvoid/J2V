#pragma once

#include "lve_descriptors.h"
#include "lve_device.h"
#include "lve_game_object.h"
#include "lve_renderer.h"
#include "lve_window.h"

// std
#include <memory>
#include <vector>

// Cosmos
#include "Universe_Controller.h"
#include "Tonix.h"

namespace lve {
	class FirstApp {
	public:
		static constexpr int WIDTH = 1980;//800;
		static constexpr int HEIGHT = 1080;//600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();

	private:
		void loadGameObjects();

		LveWindow lveWindow{ WIDTH, HEIGHT, "Vulkan Tutorial" };
		LveDevice lveDevice{ lveWindow };
		LveRenderer lveRenderer{ lveWindow, lveDevice };

		
		// - Cosmos
		Cosmos::Universe_Controller universe_con;
		void My_ProcedurallyGenerateNewObject_2();
		void My_ProcedurallyGenerateNewObject_Cosmos();
		void My_ProceduralReadFromTonix(const Cosmos::Tonix& tonix);
		//static void My_Calc();
		//std::make_unique<Cosmos::Tonix> tonix;
		// -

		// note: order of declarations matters
		std::unique_ptr<LveDescriptorPool> globalPool{};
		LveGameObject::Map gameObjects;
	};
}  // namespace lve