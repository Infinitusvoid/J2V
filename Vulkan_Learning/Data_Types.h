#pragma once

#include <glm/glm.hpp>

namespace Cosmos::Data_Types
{
	struct Vert
	{
		glm::vec3 position{};
		glm::vec3 color{};
		glm::vec3 normal{};
		glm::vec2 uv{};
	};

	struct Object3d_Data
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		std::vector<Cosmos::Data_Types::Vert> vertices{};
		std::vector<uint32_t> indices{};
	};

	typedef std::vector<Cosmos::Data_Types::Object3d_Data*> VectorOfPointers_PointingTo_Procedural_ObjectData;
}