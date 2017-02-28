#pragma once

class Mesh;

class DrawingMechanism {

public:

	virtual ~DrawingMechanism() {}

	virtual void Draw(Mesh* mesh) = 0;

};