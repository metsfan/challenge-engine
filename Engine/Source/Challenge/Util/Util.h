#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class Util 
	{
	public:
		static int ReadContentsOfBinaryFile(std::string file, unsigned char **buffer);
		static glm::vec3 CalculateFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
		static glm::mat3 normal_matrix_frommodelview(glm::mat4 modelview);
		static glm::vec3 cubic_poly_roots(float a, float b, float c);
		static glm::vec3 reduce_linear_system(glm::mat3 matrix, glm::vec3 result, bool normalize);
		static std::string GetFilenameExtension(std::string filename);
		static std::vector<std::string> StringSplit(std::string str, char token);
		static int ParseInt(std::string str);
		static std::vector<int> SplitIP(std::string ip);
		static std::string JoinIP(int *parts);
		static int Util::NearestPow2(int v);

		template <typename T>
		static bool IsKindOfClass(void *object)
		{
			return dynamic_cast<T *>(object) != NULL;
		}

		template <typename T>
		static size_t Hash(const T &value)
		{
			std::hash<T> hashFunc;
			return hashFunc(value);
		}

		static double GetSystemTime();
		static double GetClockTime();

		template <typename T>
		static T Wrap(T val, T min, T max)
		{
			if (val < min)
			{
				return max + (val - min);
			}

			if (val > max)
			{
				return min + (val - max);
			}

			return val;
		}
	};
};