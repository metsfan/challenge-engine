#include <Challenge/Challenge.h>
#include <Challenge/Util/Util.h>

namespace challenge
{
	int Util::ReadContentsOfBinaryFile(std::string file, unsigned char **buffer)
	{
		int size;
		std::ifstream stream(file, std::ios::in|std::ios::binary|std::ios::ate);
		size = stream.tellg();
		stream.seekg(0, std::ios::beg);
		unsigned char *outBuffer = new unsigned char[size];
		stream.read ((char *)outBuffer, size);
		stream.close();

		*buffer = outBuffer;
		return size;
	}

	glm::vec3 Util::CalculateFaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
	{
		glm::vec3 u1 = v2 - v1;
		glm::vec3 u2 = v3 - v1;

		glm::vec3 normal = glm::cross(u1, u2);
		return glm::normalize(normal);
	}

	glm::mat3 Util::normal_matrix_frommodelview(glm::mat4 modelview)
	{
		glm::mat3 normalMatrix = glm::mat3(
			modelview[0].x, modelview[0].y, modelview[0].z,
			modelview[1].x, modelview[1].y, modelview[1].z,
			modelview[2].x, modelview[2].y, modelview[2].z
		);
	
		normalMatrix = glm::inverse(normalMatrix);
		normalMatrix = glm::transpose(normalMatrix);
	
		return normalMatrix;
	}

	glm::vec3 Util::cubic_poly_roots(float a, float b, float c)
	{
		glm::vec3 ret;

		float p1 = (-(a*a) / 9.0f) + (b / 3.0f);
		float q1 = ((a*a*a) / 27.0f) - ((a * b) / 6.0f) + (0.5 * c);

		float theta = acos(-q1 / sqrt(pow(-p1,3))) / 3.0f;
		float two_sqrt_p = 2.0f * sqrt(-p1);
		float two_pi_over_three = (2.0f * kPi) / 3; 
		float a_over_3 = a / 3.0f;

		ret[0] = (two_sqrt_p * cos(theta)) - a_over_3;
		ret[1] = (two_sqrt_p * cos(theta + two_pi_over_three)) - a_over_3;
		ret[2] = (two_sqrt_p * cos(theta - two_pi_over_three)) - a_over_3;

		for(int i = 0; i < 3; i++) {
			float max = -99999999;
			float max_ind;
			for(int j = i; j < 2; j++) {
				if(ret[j] < ret[j+1]) {
					float tmp = ret[j+1];
					ret[j+1] = ret[j];
					ret[j] = tmp;
				}
			}
		}

		return ret;
	}

	glm::vec3 Util::reduce_linear_system(glm::mat3 matrix, glm::vec3 result, bool normalize)
	{
		glm::vec3 ret;

		glm::mat3x4 augmented = glm::mat3x4(
			glm::vec4(matrix[0], result.x),
			glm::vec4(matrix[1], result.y),
			glm::vec4(matrix[2], result.z)
		);
		int i = 0;
		for(int j = 0; j < 3; j++) {
			float max = 0.0001;
			int max_row = -1;
			for(int k = i; k < 3; k++) {
				float nval = abs(augmented[k][j]);
				if(nval > max) {
					max = nval;
					max_row = k;
				}
			}
			if(max_row >= 0 && max > 0) {
				if(max_row != i) {
					glm::vec4 k_row = augmented[max_row];
					augmented[max_row] = augmented[i];
					augmented[i] = k_row;
				}
				glm::vec4 i_row = augmented[i];
				i_row *= 1 / augmented[i][j];
				augmented[i] = i_row;

				for(int r = 0; r < 3; r++) {
					if(r != i) {
						float factor = -augmented[r][j];
						glm::vec4 i_row = factor * augmented[i];
						augmented[r] += i_row;
					}
				}
				i++;
			}
		}
	
		glm::vec3 return_vec;
		if(result.x == 0 && result.y == 0 && result.z == 0) {
			for(int i = 0; i < 3; i++) {
				glm::vec4 i_row = augmented[i];
				float max = 0.0001;
				if(abs(i_row.x) < max && abs(i_row.y) < max && abs(i_row.z) < max) {
					if(matrix[i].z > 0) {
						return_vec[i] = -1;
					} else {
						return_vec[i] = -1;
					}
				} else {
					return_vec[i] = i_row.z;
				}
			}
		} else {
			return_vec = glm::vec3(augmented[0][3], augmented[1][3], augmented[2][3]);
		}
		if(normalize) {
			return_vec = glm::normalize(return_vec);
		}
		return return_vec;
	}

	std::string Util::uuid_create()
	{
	#ifdef WIN32
		UUID uuid;
		UuidCreate(&uuid);
		unsigned char * str;
		UuidToStringA(&uuid, &str);
		std::string s((char*)str);
		RpcStringFreeA(&str);
	#else 
		uuid_t uuid;
		uuid_generate_random ( uuid );
		char s[37];
		uuid_unparse ( uuid, s );
	#endif
		return s;
	}

	std::string Util::GetFilenameExtension(std::string filename)
	{
		int lastIndex = filename.find_last_of('.');
		if(lastIndex > 0) {
			return filename.substr(lastIndex+1);
		}
		return "";
	}

	std::vector<std::string> Util::StringSplit(std::string str, char token)
	{
		std::string::iterator it = str.begin();

		std::vector<std::string> out;
		std::stringstream ss;
		while(it != str.end()) {
			char c = (*it);
			if(c == token) {
				out.push_back(ss.str());
				ss.str("");
			} else {
				ss << c;
			}

			++it;
		}

		return out;
	}

	int Util::ParseInt(std::string str)
	{
		int outInt;
		std::stringstream ss(str);
		ss >> outInt;
		return outInt;
	}

	std::vector<int> Util::SplitIP(std::string ip)
	{
		std::vector<int> out;
		std::string curStr;

		std::string::iterator it = ip.begin();
		while(it != ip.end()) {
			char c = (*it);
			if(c == '.') {
				int part = Util::ParseInt(curStr);
				curStr = "";
				out.push_back(part);
			} else {
				curStr += c;
			}

			++it;
		}
		out.push_back(Util::ParseInt(curStr));

		return out;
	}

	std::string Util::JoinIP(int *parts)
	{
		std::stringstream ss;
		ss << parts[0] << "." << parts[1] << "." << parts[2] << "." << parts[3];
		return ss.str();
	}

	int Util::NearestPow2(int v)
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        
        return v;
    }
};
