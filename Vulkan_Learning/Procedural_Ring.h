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
		std::function<float(int, int)> f_radius_External;
		std::function<float(int, int)> f_radius_Internal;
		std::function<float(float)> f_disp_l = Procedural_Ring::identitiy;
		std::function<float(float)> f_disp_r = Procedural_Ring::identitiy;
		std::function<void()> f_active_external = []() {};
		std::function<void()> f_active_iternal = []() {};

		
		void build( const std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad );
		
		//void init_example_0();

		static float const identitiy(const float v) { return v; }
		
	private:

		static void m_draw(
			const int r_index,
			const int l_index,
			const float x0,
			const float y0,
			const float x1,
			const float y1,
			const float d0,
			const float d1,
			std::function<void(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)> f_addQuad,
			std::function<float(int, int)> f_radius
		);
		
		//static float m_example_0_external(int r, int l);
		
		//static float m_example_0_internal(int r, int l);
		
	};
}
