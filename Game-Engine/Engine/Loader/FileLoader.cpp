#include "FileLoader.h"
#include "..\System\Utility\String\StringUtility.h"
#include <SDL.h>
#include "..\Engine.h"
#include "..\Resources\ResourceManager.h"
#include "..\System\Subsystem\Rendering\Asset\Mesh\Vertex.h"
#include "ObjLoader\ObjLoader.h"
#include "..\Rendering\RenderingHelper.h"
#include "..\Utils\ParseUtil.h"

const std::string FileLoader::DATA_CFG_PATH("data/data.cfg");

using namespace Utility::String;

std::string FileLoader::GetFileName(const std::string& filePath)
{
	std::string pathFileWithoutExtension = Split(filePath, '.')[0];
	std::vector<std::string> splitted = Split(pathFileWithoutExtension, '/');
	std::string fileName = splitted[splitted.size() - 1];
	return fileName;
}

char* FileLoader::LoadFile(const std::string& filePath, Sint64* size)
{
	SDL_RWops *rw = SDL_RWFromFile(filePath.c_str(), "rb");
	if (rw == NULL) return NULL;

	Sint64 resSize = SDL_RWsize(rw);
	char* res = new char[resSize + 1];

	Sint64 nbReadTotal = 0, nbRead = 1;
	char* buf = res;
	while (nbReadTotal < resSize && nbRead != 0)
	{
		nbRead = SDL_RWread(rw, buf, 1, (resSize - nbReadTotal));
		nbReadTotal += nbRead;
		buf += nbRead;
	}
	SDL_RWclose(rw);

	if (nbReadTotal != resSize)
	{
		delete[] res;
		SDL_Log("Readtotal != resSize");
		return NULL;
	}

	res[nbReadTotal] = '\0';
	if (size != nullptr)
	{
		*size = nbReadTotal;
	}
	SDL_Log("%s file loading success", filePath.c_str());
	return res;
}

void FileLoader::WriteFile(const std::string& filePath, const std::string& data, size_t size)
{
	SDL_RWops *rw = SDL_RWFromFile(filePath.c_str(), "w");
	if (rw != NULL) {
		size_t len = SDL_strlen(data.c_str());
		if (SDL_RWwrite(rw, data.c_str(), 1, size) != size) {
			SDL_Log("Couldn't fully write string\n");
		}
		else {
			SDL_Log("Wrote %d 1-byte blocks\n", len);
		}
		SDL_RWclose(rw);
	}
}

void FileLoader::ParseFileByLine(const std::string& filePath, std::function<bool(const std::string& line)> f) {
	std::string cfgStr = FileLoader::LoadFile(filePath);

	std::istringstream cfgFile(cfgStr);
	std::string line;
	while (!cfgFile.eof()) {
		std::getline(cfgFile, line);
		line = RemoveSubstring(line, "\r");
		if (!f(line))
			break;
	}
}

std::vector<std::string> FileLoader::LoadCfgFile(const std::string& filePath)
{
	std::vector<std::string> files;

	ParseFileByLine(filePath, [&files] (std::string line) -> bool {
		if (IfContainStr(line, "//") || line == "\n")
			return true;

		files.push_back(line);
		return true;
	});

	return files;
}

SDL_Surface* FileLoader::LoadImageFile(const std::string& filePath)
{
	return IMG_Load(filePath.c_str());
}

void FileLoader::SaveResourcesToStr(std::string* cfgFileStr)
{
	*cfgFileStr = "Resources:\n";

	vector<pair<string, string>> resourcesCfgData = ParseUtil::GetOrderedResourcesNames();
	for (auto r : resourcesCfgData) {
		*cfgFileStr += "\t" + r.first + "=" + r.second + "\n";
	}

	*cfgFileStr += "\n";
}

void FileLoader::SaveComponentsToStr(std::string* cfgFileStr)
{
	*cfgFileStr += "Components:\n";

	for (auto cs : *Engine::GetManager<ResourceManager>()->GetComponents()) {
		std::string verseName = RemoveSubstring(cs.first.name(), "class ");
		*cfgFileStr += "\t" + verseName + "s:\n";
		for (auto c : *cs.second->GetActiveObjects()) {
			*cfgFileStr += "\t\tC" + verseName + "=";
			for (auto str : c->GetParsedData()) {
				*cfgFileStr += str.first + ":" + str.second + ",";
			}
			*cfgFileStr += "\n";
		}
	}

	*cfgFileStr += "\n";
}

void FileLoader::SaveGameObjectsToStr(std::string* cfgFileStr)
{
	*cfgFileStr += "GameObjects:\n";
	float x = 0;
	float z = 0;

	for (auto g : *Engine::GetManager<ResourceManager>()->GetGameObjects()) {
		std::string gData("");
		gData += "\tGGameObject=";
		gData += "id:" + std::to_string(g->GetID()) + ',';
		gData += "name:" + g->GetName() + ',';

		x+=10;
		if (x > 200) {
			x = 0;
			z+=10;
		}

		if (g->GetName() == "MainCamera")
			gData += "pos:" + ParseUtil::FromVec3ToString(g->GetPos()) + ",";
		else
			gData += "pos:" + ParseUtil::FromVec3ToString(glm::vec3(x, g->GetPos().y, z)) + ",";

		gData += "rot:" + ParseUtil::FromVec3ToString(g->GetRot()) + ",";
		gData += "scale:" + ParseUtil::FromVec3ToString(g->GetScale()) + ",";

		Model* m = g->GetComponentOfType<Model>();
		gData += "model:" + (m ? std::to_string(m->GetID()) : "-1") + ',';
		Camera* c = g->GetComponentOfType<Camera>();
		gData += "camera:" + (c ? std::to_string(c->GetID()) : "-1") + ',';
		Light* l = g->GetComponentOfType<Light>();
		gData += "light:" + (l ? std::to_string(l->GetID()) : "-1");

		*cfgFileStr += gData + '\n';
	}
}

void FileLoader::SaveAllToDataCfg()
{
	string cfgFileStr("");

	SaveResourcesToStr(&cfgFileStr);
	SaveComponentsToStr(&cfgFileStr);
	SaveGameObjectsToStr(&cfgFileStr);
	WriteFile(DATA_CFG_PATH, cfgFileStr, cfgFileStr.size());
}

void FileLoader::LoadObjFile(ObjModel* owner, const std::string& filePath)
{
	using namespace TinyObj;

	attrib_t attrib;
	std::vector<shape_t> shapes;
	string aa;
	std::stringstream stream(LoadFile(filePath));

	if (!TinyObj::LoadObj(&attrib, &shapes, aa, &stream))
		throw;

	ParsedData data;
	data["name"] = Split(filePath, '.')[0];
	data["isFromFile"] = "1";
	Model* model = Engine::GetManager<ResourceManager>()->InitComponent<Model>(data);
	model->SetObjModel(owner);
	for (shape_t shape : shapes) {
		Mesh* mesh = new Mesh();

		vector<GLfloat> vertices;
		vector<GLuint> indices;

		bool hasNormalMap = ObjLoader::SetMaterial(owner, &shape, model->GetMaterials());

		ObjLoader::SetVertices(shape, attrib, vertices, indices, hasNormalMap);
		mesh->dataSize = vertices.size();
		mesh->indicesSize = indices.size();
		mesh->attribs.hasTangents = hasNormalMap;
		RenderingHelper::AddToGPU(&vertices, &indices, mesh, hasNormalMap);

		owner->GetMeshes()->push_back(mesh);
	}
}