#include "GLES2DrawingMechanism.h"

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"

#include "..\..\Asset\Mesh\Mesh.h";

void GLES2DrawingMechanism::Draw(Mesh* mesh) {

	int bufDataOffset = mesh->attribs.hasTangents ? 11 : 8;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glDrawElements(GL_TRIANGLES, mesh->indicesSize, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}