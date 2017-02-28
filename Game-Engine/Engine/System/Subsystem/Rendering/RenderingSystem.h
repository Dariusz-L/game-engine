#pragma once

#include "..\ISubsystem.h"

#include <memory>

class DrawingMechanism;
class TextureLoader;
class ShaderLoader;

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
		RenderingSystem();

		void OnStart()	override;
		void Update()	override;
		void OnEnd()	override;
	};

}