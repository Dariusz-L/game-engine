#include "AttributeLoader.h"

#include "..\..\Asset\Mesh\Mesh.h";

void AttributeLoader::Load(Mesh* mesh, std::vector<GLfloat>* data, std::vector<GLuint>* indices) {

	int bufDataOffset = mesh->attribs.hasTangents ? 11 : 8;

#if defined(_PLATFORM_WINDOWS_) || defined(_PLATFORM_EDITOR_)
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);
#endif

	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data->size(), data->data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices->size(), indices->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, bufDataOffset * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, bufDataOffset * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, bufDataOffset * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	if (mesh->attribs.hasTangents) {
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