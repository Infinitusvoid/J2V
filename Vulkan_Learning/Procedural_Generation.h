#pragma once

#include "lve_game_object.h"

#include <glm/glm.hpp>
#include <vector>

#include <math.h>       /* sin */

namespace Proc
{
	struct Vert
	{
		glm::vec3 position{};
		glm::vec3 color{};
		glm::vec3 normal{};
		glm::vec2 uv{};
	};

	struct Procedural_ObjectData
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		std::vector<Vert> vertices{};
		std::vector<uint32_t> indices{};


	};

	class Procedural_Generation
	{
	public:
		Procedural_Generation();
		~Procedural_Generation();

		std::vector<Procedural_ObjectData*> data;
	};


}
