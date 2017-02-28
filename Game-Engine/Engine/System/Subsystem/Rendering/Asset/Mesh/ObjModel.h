#pragma once

#include "..\..\..\..\Resource\Asset\Asset.h"
#include "..\..\..\..\..\Loader\FileLoader.h"

#include <vector>
#include <string>

class Mesh;
class MeshPart;
class Material;

class ObjModel : public Asset
{
private:
	std::vector<Mesh*> _meshes;

public:
	ObjModel();
	~ObjModel();

	void Load(std::vector<std::string>& filePaths) override;
	std::vector<Mesh*>* GetMeshes();
};