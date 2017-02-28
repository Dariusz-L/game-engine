#pragma once

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"
#include "..\..\..\..\Config\Include\IncludeGLM.h"

namespace Rendering { namespace Utility { namespace Uniform {

	void LoadUniform(const GLint location, const glm::mat4& value, bool transpose = false);
	void LoadUniform(const GLint location, const glm::mat3& value, bool transpose = false);
	void LoadUniform(const GLint location, const glm::vec3& value);
	void LoadUniform(const GLint location, const float value);
	void LoadUniform(const GLint location, const int texture, const int texInd, GLuint tex);


}}}