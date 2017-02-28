#include "GL3DrawingMechanism.h"

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"

#include "..\..\Asset\Mesh\Mesh.h";

void GL3DrawingMechanism::Draw(Mesh* mesh) {

#if defined(_PLATFORM_WINDOWS_) || defined (_PLATFORM_EDITOR_)
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
#endif
}