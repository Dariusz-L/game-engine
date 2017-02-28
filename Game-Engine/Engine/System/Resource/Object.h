#pragma once

class Object
{
protected:
	int _id;

public:
	Object() {
		_id = -1;
	}

	virtual ~Object() {}

	int GetID() {
		return _id;
	}

	void SetID(int id) {
		_id = id;
	}
};