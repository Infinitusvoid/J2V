#pragma once

#include "Procedural_Generation.h";
#include <vector>

#include "glm/glm.hpp"

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
	

	void AddRing(Data data)
	{
		float thicknes_external_mult = 1.5f;
		float thicknes_internal_mult = 0.8f;

		const float length_multiplier = 5.0f;

		int num_radial_slices = 100;
		int num_length_slices = 100;

		float length_slice = 1.0f / (float)num_length_slices;
		float length_slice_radial = glm::two_pi<float>() / (float)num_radial_slices;

		for (int l_index = 0; l_index < num_length_slices; l_index++)
		{
			for (int r_index = 0; r_index < num_radial_slices; r_index++)
			{
				float d0 = l_index * length_slice;
				float d0_m = d0 * length_multiplier;
				float d1 = (l_index + 1) * length_slice;
				float d1_m = d1 * length_multiplier;

				float t0 = length_slice_radial * r_index;
				float t1 = length_slice_radial * (r_index + 1);

				{
					float x0 = thicknes_external_mult * glm::sin(t0);
					float y0 = thicknes_external_mult * glm::cos(t0);

					float x1 = thicknes_external_mult * glm::sin(t1);
					float y1 = thicknes_external_mult * glm::cos(t1);

					glm::vec3 v0(x0, y0, d0_m);
					glm::vec3 v1(x0, y0, d1_m);
					glm::vec3 v2(x1, y1, d1_m);
					glm::vec3 v3(x1, y1, d0_m);

					glm::vec3 color{ 0.5, 0.8, 0.6 };
					add_quad(data, v0, v1, v2, v3, color);
				}

				{
					float x0 = thicknes_internal_mult * glm::sin(t0);
					float y0 = thicknes_internal_mult * glm::cos(t0);

					float x1 = thicknes_internal_mult * glm::sin(t1);
					float y1 = thicknes_internal_mult * glm::cos(t1);

					glm::vec3 v0(x0, y0, d0_m);
					glm::vec3 v1(x0, y0, d1_m);
					glm::vec3 v2(x1, y1, d1_m);
					glm::vec3 v3(x1, y1, d0_m);

					glm::vec3 color{ 0.5, 0.8, 0.6 };
					add_quad(data, v0, v1, v2, v3, color);
				}
				

				
			}
		}
		
		

		
	}

}



