
#include "RenderingHelper.h"
#include "..\System\Subsystem\Rendering\Asset\Mesh\Mesh.h"

void RenderingHelper::AddToGPU(std::vector<GLfloat>* vertices, std::vector<GLuint>* indices, Mesh* mesh, bool hasTangents)
{
	int bufDataOffset = hasTangents ? 11 : 8;

#ifdef _MSC_VER
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

#endif

	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices->size(), indices->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, bufDataOffset * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, bufDataOffset * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, bufDataOffset * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	if (hasTangents) {
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, bufDataOffset * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

#ifdef _MSC_VER
	glBindVertexArray(0);
#else
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif

}