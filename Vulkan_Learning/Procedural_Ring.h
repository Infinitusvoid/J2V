#pragma once

#include <functional>
#include <iostream>
//#include <glm/glm.hpp>
#include <glm/glm.hpp>

//here is PI and you should have this in .cpp file.
#include <glm/gtc/constants.hpp>

namespace Cosmos
{
	struct Procedural_Ring
	{
		int num_radial_slices;
		int num_length_slices;
		std::function<void()> f_init;
		std::function<void(int, int)> f_update;
		std::fun ction<float(int, int)> f_radius_External;
		std::function<float(int, int)> f_radius_Internal;
		std::function<float(float)> f_disp_l = Procedural_Ring::identitiy;
		std::function<float(float)> f_disp_r = Procedural_Ring::identitiy;
		std::function<void()> f_active_external = []() {};
		std::function<void()> f_active_iternal = []() {};
		std::function<glm::vec3(int, int)> f_color = [](int r, int l) {
			return glm::vec3(
				(1.0f / 500.0f)*(float)r,
				(1.0f / 500.0f) * (float)l, 1.0f); };
		

		void build(const std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad);
		
		static float const identitiy(const float v) { return v; }

	private:

		void m_draw(
			const int r_index,
			const int l_index,
			const float x0,
			const float y0,
			const float x1,
			const float y1,
			const float d0,
			const float d1,
			std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad,
			std::function<float(int, int)> f_radius);
	};
	
}
