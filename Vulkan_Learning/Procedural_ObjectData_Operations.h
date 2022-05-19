#pragma once

#include "Procedural_Generation.h";
#include "Procedural_Ring.h"
#include "Ring_Example_000.h"

// libs
#include <vector>
#include <math.h>
#include <functional>
#include "glm/glm.hpp"
#include "Ring_Example_000.h"

namespace Proc::Opr
{
	
	typedef Procedural_ObjectData* const  Data;

	void vertices_randomize_positions(Data data, const float rnd_ammout)
	{
		for (auto& v : data->vertices)
		{
			float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			v.position += glm::vec3{ x * rnd_ammout, y * rnd_ammout, z * rnd_ammout };
		}
	}
	

	void add_quad_every_vertex_color(
		Data data,
		const glm::vec3& p0,
		const glm::vec3& p1,
		const glm::vec3& p2,
		const glm::vec3& p3,
		const glm::vec3& color_0,
		const glm::vec3& color_1,
		const glm::vec3& color_2,
		const glm::vec3& color_3)
	{
		uint32_t start_pos_indices = data->indices.size();
		uint32_t start_pos_vertex = data->vertices.size();

		glm::vec3 A = p1 - p0;
		glm::vec3 B = p2 - p0;

		const glm::vec3 normal = -glm::vec3(
			A.y * B.z - A.z * B.y,
			A.z * B.x - A.x * B.z,
			A.x * B.y - A.y * B.x
		);




		{
			Vert v;
			v.position = p0;
			v.color = color_0;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Vert v;
			v.position = p1;
			v.color = color_1;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Vert v;
			v.position = p2;
			v.color = color_2;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Vert v;
			v.position = p3;
			v.color = color_3;
			v.normal = normal;
			data->vertices.push_back(v);
		}



		data->indices.push_back(start_pos_vertex);
		data->indices.push_back(start_pos_vertex + 1);
		data->indices.push_back(start_pos_vertex + 2);

		data->indices.push_back(start_pos_vertex + 2);
		data->indices.push_back(start_pos_vertex + 3);
		data->indices.push_back(start_pos_vertex + 0);
		//data->indices.pop_back(10);

	}


	void add_quad(
		Data data,
		const glm::vec3& p0,
		const glm::vec3& p1,
		const glm::vec3& p2,
		const glm::vec3& p3,
		const glm::vec3& color)
	{
		uint32_t start_pos_indices = data->indices.size();
		uint32_t start_pos_vertex = data->vertices.size();

		glm::vec3 A = p1 - p0;
		glm::vec3 B = p2 - p0;

		const glm::vec3 normal = -glm::vec3(
			A.y * B.z - A.z * B.y,
			A.z * B.x - A.x * B.z,
			A.x * B.y - A.y * B.x
		);




		{
			Vert v;
			v.position = p0;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Vert v;
			v.position = p1;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Vert v;
			v.position = p2;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}

		{
			Vert v;
			v.position = p3;
			v.color = color;
			v.normal = normal;
			data->vertices.push_back(v);
		}



		data->indices.push_back(start_pos_vertex);
		data->indices.push_back(start_pos_vertex + 1);
		data->indices.push_back(start_pos_vertex + 2);

		data->indices.push_back(start_pos_vertex + 2);
		data->indices.push_back(start_pos_vertex + 3);
		data->indices.push_back(start_pos_vertex + 0);
		//data->indices.pop_back(10);

	}
	

	
	void add_circular(Data data,
		const int sections,
		const float radius_max,
		const float radius_min,
		const float hight,
		const glm::vec3& color_1,
		const glm::vec3& color_2,
		const glm::vec3& color_3,
		const glm::vec3& color_4)
	{
		const float angle_per_section = glm::two_pi<float>() / (float)sections;

		for (int i = 0; i < sections; i++)
		{
			float t1 = angle_per_section * i;
			float t2 = angle_per_section * (i + 1);

			float x0 = radius_min * glm::sin(t1);
			float y0 = radius_min * glm::cos(t1);

			float x1 = radius_max * glm::sin(t1);
			float y1 = radius_max * glm::cos(t1);

			float x2 = radius_max * glm::sin(t2);
			float y2 = radius_max * glm::cos(t2);

			float x3 = radius_min * glm::sin(t2);
			float y3 = radius_min * glm::cos(t2);


			glm::vec3 v0 = glm::vec3(x0, y0, 0.0f);
			glm::vec3 v1 = glm::vec3(x1, y1, 0.0f);
			glm::vec3 v2 = glm::vec3(x2, y2, 0.0f);
			glm::vec3 v3 = glm::vec3(x3, y3, 0.0f);
			add_quad(data, v0, v1, v2, v3, color_1);

			glm::vec3 v0_top = glm::vec3(x0, y0, hight);
			glm::vec3 v1_top = glm::vec3(x1, y1, hight);
			glm::vec3 v2_top = glm::vec3(x2, y2, hight);
			glm::vec3 v3_top = glm::vec3(x3, y3, hight);
			add_quad(data, v0_top, v1_top, v2_top, v3_top, color_2);

			glm::vec3 v0_side_external = glm::vec3(x2, y2, hight);
			glm::vec3 v1_side_external = glm::vec3(x1, y1, hight);

			glm::vec3 v2_side_external = glm::vec3(x1, y1, 0);
			glm::vec3 v3_side_external = glm::vec3(x2, y2, 0);
			add_quad(data, v0_side_external, v1_side_external, v2_side_external, v3_side_external, color_3);


			glm::vec3 v0_side_internal = glm::vec3(x0, y0, hight);
			glm::vec3 v1_side_internal = glm::vec3(x3, y3, hight);

			glm::vec3 v2_side_internal = glm::vec3(x3, y3, 0);
			glm::vec3 v3_side_internal = glm::vec3(x0, y0, 0);
			add_quad(data, v0_side_internal, v1_side_internal, v2_side_internal, v3_side_internal, color_4);

		}
		
	}
	
	void add_quad_rnd_color(Data data, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
	{
		//srand(time(NULL));
		glm::vec3 color = glm::vec3(rand() / static_cast<float>(RAND_MAX),
			rand() / static_cast<float>(RAND_MAX),
			rand() / static_cast<float>(RAND_MAX));

		add_quad(data, v0, v1, v2, v3, color);
	}
	
	//TODO make the same interface, but it's more efficienet than this one
	//than write a test that will give you confidence that the functions produce same results
	//you look at Data data.
	void AddGrid(
		Data data,
		const int size_x,
		const int size_y,
		const std::function<void(const glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&)>& f)
	{
		// ring one (internal / exterial )
		glm::vec3 a_v0;
		glm::vec3 a_v1;
		glm::vec3 a_v2;
		glm::vec3 a_v3;

		glm::vec3 a_v0_color;
		glm::vec3 a_v1_color;
		glm::vec3 a_v2_color;
		glm::vec3 a_v3_color;

		// ring two ( internal / exterial)
		glm::vec3 b_v0;
		glm::vec3 b_v1;
		glm::vec3 b_v2;
		glm::vec3 b_v3;

		glm::vec3 b_v0_color;
		glm::vec3 b_v1_color;
		glm::vec3 b_v2_color;
		glm::vec3 b_v3_color;

		for (int y = 0; y < size_y; y++)
		{
			for (int x = 0; x < size_x; x++)
			{
				if (x == 0)
				{
					f(glm::vec3(0.0f, 0.0f, 0.0f + y), a_v0, a_v0_color, b_v0, b_v0_color);
					f(glm::vec3(0.0f, 0.0f, 1.0f + y), a_v1, a_v1_color, b_v1, b_v1_color);
					f(glm::vec3(1.0f, 0.0f, 1.0f + y), a_v2, a_v2_color, b_v2, b_v2_color);
					f(glm::vec3(1.0f, 0.0f, 0.0f + y), a_v3, a_v3_color, b_v3, b_v3_color);
				}
				else
				{
					a_v0 = a_v3;
					a_v1 = a_v2;
					a_v0_color = a_v3_color;
					a_v1_color = a_v2_color;

					b_v0 = b_v3;
					b_v1 = b_v2;
					b_v0_color = b_v3_color;
					b_v1_color = b_v2_color;


					f(glm::vec3(1.0f + x, 0.0f, 1.0f + y), a_v2, a_v2_color, b_v2, b_v2_color);
					f(glm::vec3(1.0f + x, 0.0f, 0.0f + y), a_v3, a_v3_color, b_v3, b_v3_color);
				}


				add_quad_every_vertex_color(data,
					a_v0, a_v1, a_v2, a_v3,
					a_v0_color, a_v1_color, a_v2_color, a_v3_color
					);
				add_quad_every_vertex_color(data,
					b_v0, b_v1, b_v2, b_v3,
					b_v0_color, b_v1_color, b_v2_color, b_v3_color
				);

			}
		}
		
		//v0 = glm::vec3(0.0f, -0.18f, 0.0f);
		//v1 = glm::vec3(0.0f, -0.18f, 1.0f);
		//v2 = glm::vec3(1.0f, -0.18f, 1.0f);
		//v3 = glm::vec3(1.0f, -0.18f, 0.0f);
		//add_quad_rnd_color(data, v0, v1, v2, v3);
	}

	void AddRing(Data data)
	{
		constexpr int num_x = 800;
		constexpr int num_y = 800;

		constexpr float x_proc = 1.0f / (float)num_x;
		constexpr float y_proc = 1.0f /(float) num_y;

		auto lambda = [](glm::vec3 v, glm::vec3& v1_out, glm::vec3& v1_out_color, glm::vec3& v2_v_out, glm::vec3& v2_out_color) {
			
			
			
			v.x *= x_proc;// * 5.0;
			v.z *= y_proc;// * 5.0;

			const float angle = v.x * glm::two_pi<float>();
			const float length = v.z;

			// v1
			float amp_modul = 1.0f +
				0.015 * sin(length * glm::two_pi<float>() * 10) +
				0.1 * sin(angle * 15)  + 
				0.025 * sin(angle * 22);


			float lerp_fak = 1 - (abs(length - 0.5f) * 2);
			lerp_fak = pow(lerp_fak, 0.4f);

			float val = std::lerp(0.5f, amp_modul, lerp_fak);

			amp_modul = val;

			v.x = amp_modul * glm::sin(angle);
			v.y = amp_modul * glm::cos(angle);
			v.z = length * 10.0f;

			
			
			v.y += -0.15f;
			
			v1_out = v;
			v1_out_color = glm::vec3(0.2, 0.8 + 0.3 * glm::sin(length * 100 + 0.1f * sin(angle * 100)), 0.1f);


			v1_out_color += ( glm::vec3(rand() / static_cast<float>(RAND_MAX),
									  rand() / static_cast<float>(RAND_MAX),
									  rand() / static_cast<float>(RAND_MAX)) * 
							  glm::vec3(0.2f, 0.2f, 0.2f));

			// v1 end


			// v2

			float amp_modul_2 = 2.0f +
				0.015 * sin(length * glm::two_pi<float>() * 16) +
				0.015 * sin(length * glm::two_pi<float>() * 6) +
				0.1 * sin(angle * 7) +
				0.025 * sin(angle * 4);


			float lerp_fak_2 = 1 - (abs(length - 0.5f) * 2);
			lerp_fak_2 = pow(lerp_fak_2, 0.33f);

			float val2 = std::lerp(0.5f, amp_modul_2, lerp_fak_2);

			amp_modul_2 = val2;

			v2_v_out.x = amp_modul_2 * glm::sin(angle);
			v2_v_out.y = amp_modul_2 * glm::cos(angle);
			v2_v_out.z = length * 10.0f;

			v2_v_out.y += -0.15f;

			v2_v_out = v2_v_out;
			
			v2_out_color = glm::vec3(1.0, 0.5, 0.1f);
			v2_out_color  += (glm::vec3(rand() / static_cast<float>(RAND_MAX),
				rand() / static_cast<float>(RAND_MAX),
				rand() / static_cast<float>(RAND_MAX)) *
				glm::vec3(0.2f, 0.2f, 0.2f));
			

			v2_out_color *= glm::vec3(
				0.0,
				1.0f * glm::sin(angle * 25) * glm::sin(length * 25) + 0.2f * glm::sin(angle * 25  + glm::sin(length * 215)) + 0.05f * glm::sin(angle * 125 + glm::sin(length * 615)),
				pow(glm::sin(sin(angle * 15) * sin(length * 10) * 25), 4)
			);
			// v2 end
		};

		AddGrid(data, num_x, num_y, lambda);
		/*
		auto lambda = [&data](glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& v3, glm::vec3 color) {
			//glm::vec3 color{ 0.5, 0.8, 0.6 };
			add_quad(data,v0, v1, v2, v3, color);
		};

		Cosmos::Ring_Example_000 ring_000;
		ring_000.build(lambda);
		*/
		
		//Cosmos::Procedural_Ring r;
		//r.init_example_0();
		//r.build(lambda);
		


	}

}



