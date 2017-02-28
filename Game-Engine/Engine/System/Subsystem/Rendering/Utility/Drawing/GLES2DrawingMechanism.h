#pragma once

#include "..\DrawingMechanism.h"

class GLES2DrawingMechanism : public DrawingMechanism
{

public:

	void Draw(Mesh* mesh) override;

};

