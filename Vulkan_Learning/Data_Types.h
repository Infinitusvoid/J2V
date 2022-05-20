#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <functional>

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

	typedef Object3d_Data* ptr_to_Object3d_Data;
	
	typedef std::vector<Cosmos::Data_Types::Object3d_Data*> VectorOfPointers_PointingTo_Procedural_ObjectData;

	template<typename T>
	struct Frequency_Amplitude_Offset
	{
		T frequency;
		T amplitude;
		T offset;
	};



	namespace Info
	{
		struct Ring_Info
		{
			int num_x;
			int num_y;
			float radius_a;
			float radius_b;
			float radius_merge;
			float interpolation_exponent_a;
			float interpolation_exponent_b;

			std::vector<Cosmos::Data_Types::Frequency_Amplitude_Offset<float>> sinus_signals_angleAttribute_a_radius;
			std::vector<Cosmos::Data_Types::Frequency_Amplitude_Offset<float>> sinus_signals_angleAttribute_b_radius;

			std::vector<Cosmos::Data_Types::Frequency_Amplitude_Offset<float>> sinus_signals_lengthAttribute_a_radius;
			std::vector<Cosmos::Data_Types::Frequency_Amplitude_Offset<float>> sinus_signals_lengthAttribute_b_radius;

			//radius, amp1, amp2, angle, length
			std::function<glm::vec3(float, float, float, float, float)> f_color_a;
			std::function<glm::vec3(float, float, float, float, float)> f_color_b;
		};
	}

	

}