#include "Mesh.h"

void Mesh::ClearVBO()
{
	if (vbo != -1)
		glDeleteBuffers(1, &vbo);

	if (vbo != -1)
		glDeleteBuffers(1, &ebo);

#ifdef _MSC_VER	
	if (vao != -1)
		glDeleteVertexArrays(1, &vao);
#endif

	vbo = -1;
	ebo = -1;
	vao = -1;
}

Mesh::~Mesh() {
	ClearVBO();
}