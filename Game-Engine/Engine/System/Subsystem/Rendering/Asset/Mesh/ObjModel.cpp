#include "ObjModel.h"

#include "..\..\..\..\Utility\String\StringUtility.h"
#include "Vertex.h"
#include "Mesh.h"

#include "..\..\..\..\..\Resources\ResourceManager.h"

ObjModel::ObjModel() :
	_meshes() {}

ObjModel::~ObjModel() {

	for (Mesh* m : _meshes) {
		delete m;
	}

}

void ObjModel::Load(std::vector<std::string>& filePaths) {
	
	Asset::Load(filePaths);

	FileLoader::LoadObjFile(this, filePaths[0]);

}

std::vector<Mesh*>* ObjModel::GetMeshes() {
	return &_meshes;
}