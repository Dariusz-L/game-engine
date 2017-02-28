#pragma once

#include "..\ISubsystem.h"

#include <memory>

class DrawingMechanism;
class TextureLoader;
class ShaderLoader;
class MeshLoader;
class MaterialLoader;

namespace Rendering {

	class RenderingSystem : public ISubsystem {

	private:
		void InitGL();
		void CreateWindow();

		void SetAllMeshesInPoolRenderable();

		DrawingMechanism*	_drawingMechanism;

	public:
		TextureLoader*		_textureLoader;
		ShaderLoader*		_shaderLoader;
		MeshLoader*			_meshLoader;
		MaterialLoader*		_materialLoader;

		RenderingSystem();

		void OnStart()	override;
		void Update()	override;
		void OnEnd()	override;
	};

}