#include "UniformLoading.h"

namespace Rendering { namespace Utility { namespace Uniform {
	
	void LoadUniform(const GLint location, const glm::mat4& mat4, bool transpose) {
		glUniformMatrix4fv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat4));
	}

	void LoadUniform(const GLint location, const glm::mat3& value, bool transpose) {
		glUniformMatrix3fv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
	}

	void LoadUniform(const GLint location, const glm::vec3& value) {
		glUniform3f(location, value.x, value.y, value.z);
	}

	void LoadUniform(const GLint location, const float value) {
		glUniform1f(location, value);
	}

	void LoadUniform(const GLint location, const int texture, const int texInd, GLuint tex) {
		glActiveTexture(texture);
		glBindTexture(GL_TEXTURE_2D, tex);
		glUniform1i(location, texInd);
	}

}}}