#pragma once

#include "Data_Types.h"

namespace Cosmos::Operations_3d
{
	typedef Cosmos::Data_Types::ptr_to_Object3d_Data Mesh;

	void vertices_randomize_positions(Mesh data, const float rnd_ammout);

	void add_quad_every_vertex_color(
		Mesh data,
		const glm::vec3& p0,
		const glm::vec3& p1,
		const glm::vec3& p2,
		const glm::vec3& p3,
		const glm::vec3& color_0,
		const glm::vec3& color_1,
		const glm::vec3& color_2,
		const glm::vec3& color_3);

	void AddRing(Mesh data);
}

