#include "MeshLoader.h"

#include "..\..\..\Resource\Asset\Parser\OBJ\MeshAssetParsed.h"
#include "..\Asset\Mesh\Mesh.h"
#include "..\..\Rendering\Utility\Attribute\AttributeLoader.h"
#include "..\..\..\..\Resources\ResourceManager.h"
#include "..\..\..\Resource\Asset\Parser\OBJ\TinyObj\TinyObjParser.h"
#include "..\..\..\Utility\String\StringUtility.h"
#include "..\Asset\Mesh\ObjModel.h"
#include "..\Asset\Mesh\Vertex.h"

using namespace TinyObj;

void MeshLoader::Load(ObjModel* mesh, AssetParsed* assetParsed) {

	auto meshAssetParsed = static_cast<MeshAssetParsed*>(assetParsed);

	ParsedData data;
	data["name"] = meshAssetParsed->name;
	data["isFromFile"] = "1";
	Model* model = Engine::GetManager<ResourceManager>()->InitComponent<Model>(data);
	model->SetObjModel(mesh);

	for (shape_t shape : meshAssetParsed->shapes) {
		Mesh* subMesh = new Mesh();

		vector<GLfloat> vertices;
		vector<GLuint> indices;

		bool hasNormalMap = SetMaterial(mesh, &shape, model->GetMaterials());

		SetVertices(shape, meshAssetParsed->attribs, vertices, indices, hasNormalMap);
		subMesh->dataSize = vertices.size();
		subMesh->indicesSize = indices.size();
		subMesh->attribs.hasTangents = hasNormalMap;
		AttributeLoader::Load(subMesh, &vertices, &indices);

		mesh->GetMeshes()->push_back(subMesh);
	}
}

void MeshLoader::Destroy(ObjModel* asset) {

}

bool MeshLoader::SetMaterial(ObjModel* owner, TinyObj::shape_t* shape, std::vector<Material*>* materials) {
	ResourceManager* rm = Engine::GetManager<ResourceManager>();

	std::string matID = shape->mesh.materialName;
	MtlMaterial* mtlMat = rm->GetResourceByName<MtlMaterial>(owner->GetName());

	bool useDefaultMaterial = false;

	//if (mtlMat)
	//	for (auto m : *mtlMat->GetMaterials()) {
	//		if (!m.second->GetTexDiffuse()) {
	//			useDefaultMaterial = true;
	//			break;
	//		}
	//	}

	if (matID == "" || useDefaultMaterial || !mtlMat) {
		std::vector<Component*>& allMetarials = *rm->GetComponents()->at(typeid(Material))->GetActiveObjects();
		for (auto m : allMetarials) {
			Material* mat = static_cast<Material*>(m);
			if (mat->GetName() == "default") {
				materials->push_back(mat);
			}
		}
	}
	else {
		materials->push_back(mtlMat->GetMaterial(matID));
	}

	return (*materials)[materials->size() - 1]->GetTexNormal();
}

void MeshLoader::SetVertices(TinyObj::shape_t& shape, TinyObj::attrib_t& attrib, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, bool hasNormalMap) {
	vector<Vertex> helpingVertices;

	// Basic vertices
	int i = 0;
	for (TinyObj::index_t index : shape.mesh.indices) {
		Vertex v;
		v.pos.x = attrib.vertices[index.vertex_index * 3];
		v.pos.y = attrib.vertices[index.vertex_index * 3 + 1];
		v.pos.z = attrib.vertices[index.vertex_index * 3 + 2];
		if (attrib.texcoords.size() > 0 && index.texcoord_index != -1) {
			v.uv.x = attrib.texcoords[index.texcoord_index * 2];
			v.uv.y = attrib.texcoords[index.texcoord_index * 2 + 1];
		}
		v.n.x = attrib.normals[index.normal_index * 3];
		v.n.y = attrib.normals[index.normal_index * 3 + 1];
		v.n.z = attrib.normals[index.normal_index * 3 + 2];

		//vector<Vertex>::iterator indV = std::find(helpingVertices.begin(), helpingVertices.end(), v);
		//if (indV == helpingVertices.end()) {
		helpingVertices.push_back(v);
		//	indices.push_back(helpingVertices.size() - 1);
		//}
		//else {
		indices.push_back(i++);

		//indices.push_back(std::distance(helpingVertices.begin(), indV));
		//}
	}

	// Calculating tangent
	if (hasNormalMap) {
		for (unsigned int i = 0; i < indices.size(); i += 3) {
			Vertex& v0 = helpingVertices[indices[i]];
			Vertex& v1 = helpingVertices[indices[i + 1]];
			Vertex& v2 = helpingVertices[indices[i + 2]];

			glm::vec3 edge1 = v1.pos - v0.pos;
			glm::vec3 edge2 = v2.pos - v0.pos;

			float deltaU1 = v1.uv.x - v0.uv.x;
			float deltaV1 = v1.uv.y - v0.uv.y;
			float deltaU2 = v2.uv.x - v0.uv.x;
			float deltaV2 = v2.uv.y - v0.uv.y;

			float f = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

			glm::vec3 tangent;

			tangent.x = f * (deltaV2 * edge1.x - deltaV1 * edge2.x);
			tangent.y = f * (deltaV2 * edge1.y - deltaV1 * edge2.y);
			tangent.z = f * (deltaV2 * edge1.z - deltaV1 * edge2.z);

			v0.tangent += tangent;
			v1.tangent += tangent;
			v2.tangent += tangent;
		}
	}

	// Push finally
	for (auto v : helpingVertices) {
		v.PushToVec(&vertices, hasNormalMap);
	}
}