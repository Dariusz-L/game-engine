#pragma once

#include "..\..\..\Resource\Asset\AssetLoader.h"
#include "..\..\..\Resource\Asset\Parser\OBJ\TinyObj\TinyObjParserStructs.h"
#include "..\..\..\Config\Include\IncludeOpenGL.h"

class Mesh;
class ObjModel;
class Material;

class MeshLoader : public AssetLoader<ObjModel> {
private:
	bool SetMaterial(ObjModel* owner, TinyObj::shape_t* shape, std::vector<Material*>* materials);
	void SetVertices(TinyObj::shape_t& shape, TinyObj::attrib_t& attrib, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, bool hasNormalMap);

public:
	void Load(ObjModel* asset, AssetParsed* assetParsed) override;
	void Destroy(ObjModel* asset) override;
};

