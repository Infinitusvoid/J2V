#pragma once

#include "Procedural_Generation.h";
#include <vector>
#include <math.h>
#include <functional>

#include "glm/glm.hpp"

#include "Procedural_Ring.h"

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
	

	float Radius_External(int r, int l)
	{
		float r_angle = (r / (float)500) * glm::two_pi<float>();
		float l_fak = (l / (float)500);

		float this_offst = 1.5f +
			0.25f * glm::sin(r_angle * 10) +
			0.1f * glm::sin(l_fak * glm::two_pi<float>() * 20.0f);
			//0.025f * glm::sin(l_fak * glm::two_pi<float>() * 105.0f);

		float lerp_fak = 1 - (abs(l_fak - 0.5f) * 2);

		lerp_fak = pow(lerp_fak, 0.8f);
		//return std::lerp(Radius_Internal(r, l), this_offst, lerp_fak);
		// 
		return std::lerp(0.5f, this_offst, lerp_fak);
		//return this_offst;
		//return std::lerp(0.5f, this_offst, l_fak);
		return  1.0 + l_fak;//l_fak * 2.5f;
	}

	float Radius_Internal(int r, int l)
	{
		float r_angle = (r / (float)500) * glm::two_pi<float>();
		float l_fak = (l / (float)500);

		float this_offst = 0.7f +
			0.025 * glm::sin(r_angle * 25) +
			0.025 * glm::sin(l_fak * glm::two_pi<float>() * 8);
		

		float lerp_fak = 1 - (abs(l_fak - 0.5f) * 2);

		lerp_fak = pow(lerp_fak, 0.4f);

		float val = std::lerp(0.5f, this_offst, lerp_fak);
		
		val = std::min(Radius_External(r, l), val);
		
		//return this_offst;
		//return std::lerp(0.5f, this_offst, l_fak);
		return val;
	}

	

	/*
	struct RingShape
	{
		int num_radial_slices = 500;
		int num_length_slices = 500;
		
		float length_multiplier = 5.0f;

		float f_radial_displacement(float r)
		{
			return r;
		}

		float f_length_displacement(float l)
		{
			return l;
		}

		float radius_f(int r, int l)
		{
			float r_angle = (r / (float)num_radial_slices) * glm::two_pi<float>();
			float l_fak = (l / (float)num_length_slices);

			float this_offst = 1.5f + 0.25 * glm::sin(r_angle * 10);
			this_offst += 0.1 * glm::sin(l_fak * glm::two_pi<float>() * 20.0f);


			//return std::lerp(Radius_Internal(r, l), this_offst, 1 - (abs(l_fak - 0.5f) * 2));
			//return this_offst;
			//return std::lerp(0.5f, this_offst, l_fak);
			return  1.0;// + l_fak;//l_fak * 2.5f;
		}

		void calculate(std::function<void(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> f)
		{
			//pre loop
			float length_slice = 1.0f / (float)num_length_slices;
			float length_slice_radial =  1.0f / (float)num_radial_slices;
			

			for (int l_index = 0; l_index < num_length_slices; l_index++)
			{
				for (int r_index = 0; r_index < num_radial_slices; r_index++)
				{
					length_slice_radial = f_radial_displacement(length_slice_radial);
					length_slice_radial *= glm::two_pi<float>();
					
					float d0 = l_index * length_slice;
					float d0_m = d0 * length_multiplier;
					float d1 = (l_index + 1) * length_slice;
					float d1_m = d1 * length_multiplier;

					float t0 = length_slice_radial * r_index;
					float t1 = length_slice_radial * (r_index + 1);

					float x0 = glm::sin(t0);
					float y0 = glm::cos(t0);

					float x1 = glm::sin(t1);
					float y1 = glm::cos(t1);


					//ring
					const float offset_0_0 = radius_f(r_index, l_index);
					const float offset_0_1 = radius_f(r_index, l_index + 1);
					const float offset_1_0 = radius_f(r_index + 1, l_index);
					const float offset_1_1 = radius_f(r_index + 1, l_index + 1);

					float x0_d0 = x0 * offset_0_0;//Radius_External(r_index, l_index);
					float x0_d1 = x0 * offset_0_1;//Radius_External(r_index, l_index + 1);

					float y0_d0 = y0 * offset_0_0;//Radius_External(r_index, l_index);
					float y0_d1 = y0 * offset_0_1;//Radius_External(r_index, l_index + 1);

					float x1_d0 = x1 * offset_1_0;//Radius_External(r_index + 1, l_index);
					float x1_d1 = x1 * offset_1_1;//Radius_External(r_index + 1, l_index + 1);

					float y1_d0 = y1 * offset_1_0;//Radius_External(r_index + 1, l_index);
					float y1_d1 = y1 * offset_1_1;// Radius_External(r_index + 1, l_index + 1);



					glm::vec3 v0(x0_d0, y0_d0, d0_m);
					glm::vec3 v1(x0_d1, y0_d1, d1_m);
					glm::vec3 v2(x1_d1, y1_d1, d1_m);
					glm::vec3 v3(x1_d0, y1_d0, d0_m);

					
					glm::vec3 color{ 0.5, 0.8, 0.6 };
					//add_quad(data, v0, v1, v2, v3, color);
					f(v0, v1, v2, v3, color);
				}
			}
		}
	};
	*/
	
	void DrawRing_Quadr()
	{

	}

	
	void AddRing(Data data)
	{
		auto lambda = [&data](glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& v3) {
			glm::vec3 color{ 0.5, 0.8, 0.6 };
			add_quad(data,v0, v1, v2, v3, color);
		};

		Cosmos::Procedural_Ring r;
		r.init_example_0();
		r.build(lambda);

		return;

		float thicknes_internal_mult = 0.8f;

		const float length_multiplier = 5.0f;

		int num_radial_slices = 500;
		int num_length_slices = 500;

		float length_slice = 1.0f / (float)num_length_slices;
		float length_slice_radial = glm::two_pi<float>() / (float)num_radial_slices;

		for (int l_index = 0; l_index < num_length_slices; l_index++)
		{
			for (int r_index = 0; r_index < num_radial_slices; r_index++)
			{
				//TODO d1 should become d0 in next iteration of loop to avoid unecessery calulations

				float d0 = l_index * length_slice;
				//place to f(d0)
				float d0_m = d0 * length_multiplier;
				float d1 = (l_index + 1) * length_slice;
				//place to f(d1)
				float d1_m = d1 * length_multiplier;

				float t0 = length_slice_radial * r_index;
				//place for f(t0) [t0 should be from 0 to 1 in this step not 0 to 2PI]
				float t1 = length_slice_radial * (r_index + 1);
				//place for f(t1) [t0 should be from 0 to 1 in this step not 0 to 2PI]

				float x0 = glm::sin(t0);
				float y0 = glm::cos(t0);

				float x1 = glm::sin(t1);
				float y1 = glm::cos(t1);

				//External
				{
					const float offset_0_0 = Radius_External(r_index, l_index);
					const float offset_0_1 = Radius_External(r_index, l_index + 1);
					const float offset_1_0 = Radius_External(r_index + 1, l_index);
					const float offset_1_1 = Radius_External(r_index + 1, l_index + 1);

					float x0_d0 = x0 * offset_0_0;
					float x0_d1 = x0 * offset_0_1;

					float y0_d0 = y0 * offset_0_0;
					float y0_d1 = y0 * offset_0_1;

					float x1_d0 = x1 * offset_1_0;
					float x1_d1 = x1 * offset_1_1;

					float y1_d0 = y1 * offset_1_0;
					float y1_d1 = y1 * offset_1_1;


					glm::vec3 v0(x0_d0, y0_d0, d0_m);
					glm::vec3 v1(x0_d1, y0_d1, d1_m);
					glm::vec3 v2(x1_d1, y1_d1, d1_m);
					glm::vec3 v3(x1_d0, y1_d0, d0_m);

					glm::vec3 color{ 0.5, 0.8, 0.6 };
					add_quad(data, v0, v1, v2, v3, color);
				}

				//Internal 
				{
					

					const float offset_0_0 = Radius_Internal(r_index, l_index);
					const float offset_0_1 = Radius_Internal(r_index, l_index + 1);
					const float offset_1_0 = Radius_Internal(r_index + 1, l_index);
					const float offset_1_1 = Radius_Internal(r_index + 1, l_index + 1);

					float x0_d0 = x0 * offset_0_0;
					float x0_d1 = x0 * offset_0_1;

					float y0_d0 = y0 * offset_0_0;
					float y0_d1 = y0 * offset_0_1;

					float x1_d0 = x1 * offset_1_0;
					float x1_d1 = x1 * offset_1_1;

					float y1_d0 = y1 * offset_1_0;
					float y1_d1 = y1 * offset_1_1;


					glm::vec3 v0(x0_d0, y0_d0, d0_m);
					glm::vec3 v1(x0_d1, y0_d1, d1_m);
					glm::vec3 v2(x1_d1, y1_d1, d1_m);
					glm::vec3 v3(x1_d0, y1_d0, d0_m);

					glm::vec3 color{ 0.5, 0.8, 0.6 };
					add_quad(data, v0, v1, v2, v3, color);
				}
				

				
			}
		}
		
		

		
	}

}



