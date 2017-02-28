#include "RenderingSystem.h"

#include "..\..\..\Engine.h"
#include "..\..\..\Resources\ResourceManager.h"
#include "RenderingConfig.h"
#include "Utility\Uniform\UniformLoading.h"
#include "Utility\Uniform\UniformInfo.h"
#include "Component\Camera.h"
#include "..\..\Resource\GameObject.h"

#include "Utility\Drawing\GL3DrawingMechanism.h"
#include "Utility\Drawing\GLES2DrawingMechanism.h"

#include "Loader\TextureLoader.h"
#include "Loader\ShaderLoader.h"
#include "Loader\MeshLoader.h"
#include "Loader\MaterialLoader.h"

#include "..\..\Resource\Asset\Parser\Image\ImageAssetParsed.h"
#include "..\..\Resource\Asset\Parser\Image\ImageAssetParser.h"
#include "..\..\Resource\Asset\Parser\Shader\ShaderAssetParsed.h"
#include "..\..\Resource\Asset\Parser\Shader\ShaderAssetParser.h"
#include "..\..\Resource\Asset\Parser\OBJ\MeshAssetParsed.h"
#include "..\..\Resource\Asset\Parser\OBJ\MeshAssetParser.h"
#include "..\..\Resource\Asset\Parser\MTL\MtlAssetParsed.h"
#include "..\..\Resource\Asset\Parser\MTL\MtlAssetParser.h"

using namespace Rendering;
using namespace Rendering::Utility::Uniform;

RenderingSystem::RenderingSystem() {
	 
#if defined(_PLATFORM_WINDOWS_) || defined(_PLATFORM_EDITOR_)
	_drawingMechanism = new GL3DrawingMechanism();
#else
	_drawingMechanism = new GLES2DrawingMechanism();
#endif

	_textureLoader = new TextureLoader();
	_shaderLoader = new ShaderLoader();
	_meshLoader = new MeshLoader();
	_materialLoader = new MaterialLoader();
}

void RenderingSystem::OnStart() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "SDL Init video error\n";

	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
	CreateWindow();
	InitGL();

	AssetsParsed* assetsParsed = Engine::system.resourceLoader.GetAssetParsingManager()->GetAssetsParsed();
	Assets* assets = &Engine::data.resources.assets;

	assets->emplace(typeid(Texture), 
		_textureLoader->LoadAssets((*assetsParsed)[typeid(ImageAssetParser)]));

	assets->emplace(typeid(Shader), 
		_shaderLoader->LoadAssets((*assetsParsed)[typeid(ShaderAssetParser)]));
	
	assets->emplace(typeid(MtlMaterial),
		_materialLoader->LoadAssets((*assetsParsed)[typeid(MtlAssetParser)]));

	assets->emplace(typeid(ObjModel),
		_meshLoader->LoadAssets((*assetsParsed)[typeid(MeshAssetParser)]));
}

void RenderingSystem::Update() {
	static bool a = false;
	if (!a) {
		a = true;
		SetAllMeshesInPoolRenderable();
		Engine::data.rendering.mainCamera->GetComponentOfType<Camera>()->SetProjectionMode(ProjectionMode::PERSPECTIVE);
	}
	
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	RenderingSystem*	system	= &Engine::system.subsystems.rendering;
	RenderingData*		data	= &Engine::data.rendering;
	for (auto& p1 : data->renderable.shaderBranch) {
		Shader* shader = p1.shader;
		shader->Use();
		const std::vector<std::pair<UniformType, GLint>>* uniforms = &shader->uniformInfos;
		for (auto& p2 : p1.materialBranch) {
			Material* mat = p2.material;
			for (auto& p3 : p2.mg) {
				Mesh* mesh = p3.mesh;
				GameObject* go = p3.gameObject;

				for (auto up : *uniforms) {
					GLint loc = up.second;
					switch (up.first) {

					case UniformType::PROJECTION:
						LoadUniform(loc, data->mainCamera->GetComponentOfType<Camera>()->GetProjectionMatrix());
						break;

					case UniformType::VIEW:
						LoadUniform(loc, data->mainCamera->GetComponentOfType<Camera>()->GetViewMatrix());
						break;

					case UniformType::MODEL:
						LoadUniform(loc, go->GetModel());
						break;

					case UniformType::INVERSE_TRANSPOSE_MODEL:
						LoadUniform(loc, go->GetInversedModel(), true);
						break;

					case UniformType::AMBIENT_STRENGTH:
						LoadUniform(loc, 0.3f);
						break;

					case UniformType::AMBIENT_COLOR:
						LoadUniform(loc, mat->GetColorAmbient());
						break;

					case UniformType::COLOR_DIFFUSE:
						LoadUniform(loc, mat->GetColorDiffuse());
						break;

					case UniformType::COLOR_SPECULAR:
						LoadUniform(loc, mat->GetColorSpecular());
						break;

					case UniformType::SPECULAR_STRENGTH:
						LoadUniform(loc, 0.5f);
						break;

					case UniformType::LIGHT_POS:
						LoadUniform(loc, data->lights[0]->GetPos());
						break;

					case UniformType::LIGHT_COLOR:
						LoadUniform(loc, data->lights[0]->GetComponentOfType<Light>()->color);
						break;

					case UniformType::VIEW_POS:
						LoadUniform(loc, data->mainCamera->GetPos());
						break;

					case UniformType::TEX_DIFFUSE:
						if (mat->GetTexDiffuse()) {
							LoadUniform(loc, GL_TEXTURE0, 0, mat->GetTexDiffuse()->GetTexture());
						}
						break;

					case UniformType::TEX_SPECULAR:
						if (mat->GetTexSpecular())
							LoadUniform(loc, GL_TEXTURE1, 1, mat->GetTexSpecular()->GetTexture());
						break;

					case UniformType::TEX_NORMAL:
						if (mat->GetTexNormal())
							LoadUniform(loc, GL_TEXTURE2, 2, mat->GetTexNormal()->GetTexture());
						break;
					}
				}
					
				go->changedTransform = false;
				_drawingMechanism->Draw(mesh);
			}
		}
	}

	SDL_GL_SwapWindow(Engine::data.rendering.window.GetWindow());
}

void RenderingSystem::OnEnd() {

}

void RenderingSystem::InitGL() {

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#if defined(_PLATFORM_WINDOWS_) || defined(_PLATFORM_EDITOR_)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW not initialized\n";

#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);

#endif
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

}

void RenderingSystem::CreateWindow() {

	Window* window = &Engine::data.rendering.window;
	window->Create();

	glm::ivec2 size = window->GetSize();
	glViewport(0, 0, size.x, size.y);
	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

}

void RenderingSystem::SetAllMeshesInPoolRenderable() {

	ResourceManager*	rm				= Engine::GetManager<ResourceManager>();
	RenderingData*		renderingData	= &Engine::data.rendering;
	RenderableObjects*	renderable		= &renderingData->renderable;

	for (auto* go : *rm->GetGameObjects()) {
		Model* model = go->GetComponentOfType<Model>();
		if (model != nullptr) {
			auto materials = model->GetMaterials();
			auto meshes = model->GetObjModel()->GetMeshes();

			for (int mi = 0; mi < meshes->size(); mi++) {
				Material* m = materials->operator[](mi);
				Shader* shader = m->GetShader();

				// Check if there is shaderBranch with this shader
				ShaderBranch* shaderBranch = nullptr;
				for (auto& sb : renderable->shaderBranch) {
					if (sb.shader == shader) {
						shaderBranch = &sb;
						break;
					}
				}

				// If there is no such branch create one and ensure local var is inited
				if (!shaderBranch) {
					ShaderBranch newShaderBranch;
					newShaderBranch.shader = shader;
					renderable->shaderBranch.push_back(newShaderBranch);

					shaderBranch = &renderable->shaderBranch[renderable->shaderBranch.size() - 1];
				}

				// Check if there is materialBranch in shaderBranch
				MaterialBranch* materialBranch = nullptr;
				for (auto& mb : shaderBranch->materialBranch) {
					if (mb.material == m) {
						materialBranch = &mb;
						break;
					}
				}

				// If there is no such branch create one and ensure local var is inited
				if (!materialBranch) {
					auto* mBranches = &shaderBranch->materialBranch;

					MaterialBranch newMaterialBranch;
					newMaterialBranch.material = m;
					mBranches->push_back(newMaterialBranch);
					materialBranch = &mBranches->operator[](mBranches->size() - 1);
				}

				// Finally push mesh to render
				MG mg;
				mg.mesh = meshes->operator[](mi);
				mg.gameObject = go;
				materialBranch->mg.push_back(mg);
			}
		}
	}

}