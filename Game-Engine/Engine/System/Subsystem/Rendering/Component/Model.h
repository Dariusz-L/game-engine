#pragma once
#include "..\..\..\Resource\Component\Component.h"
#include <vector>

class Mesh;
class Material;
class ObjModel;

class Model : public Component
{
private:
	ObjModel* _objModel;
	std::vector<Material*> _materials;

public:
	Model();
	~Model();

	ObjModel* GetObjModel(); 
	void SetObjModel(ObjModel* objModel);

	void Parse(ParsedData& data) override;
	ParsedData GetParsedData() override;

	std::vector<Material*>* GetMaterials();
};