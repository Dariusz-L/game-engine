#pragma once

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"
#include "..\..\..\..\Config\Include\IncludeGLM.h"

#include <vector>
#include <string>

struct Vertex {
	std::string hash;

	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 n;
	glm::vec3 tangent;

	void PushToVec(std::vector<GLfloat>* vec, bool pushTangent = false) {
		vec->push_back(pos.x);
		vec->push_back(pos.y);
		vec->push_back(pos.z);
		vec->push_back(uv.x);
		vec->push_back(uv.y);
		vec->push_back(n.x);
		vec->push_back(n.y);
		vec->push_back(n.z);

		if (pushTangent) {

			tangent = glm::normalize(tangent);
			vec->push_back(tangent.x);
			vec->push_back(tangent.y);
			vec->push_back(tangent.z);
		}
	}

	inline bool operator==(const Vertex& other) {
		if (pos == other.pos && uv == other.uv & n == other.n)
			return true;

		return false;
	}

	void Hash() {
		using namespace std;

		hash =
			to_string(pos.x + pos.y + pos.z + uv.x + uv.y + n.x + n.y + n.z);
	}
};