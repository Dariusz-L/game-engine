#pragma once
#include "..\Object.h"
#include <string>
#include "..\..\..\Utils\ParseUtil.h"

class GameObject;

class Component : public Object
{
protected:
	bool _isFromFile;

public:
	Component();
	virtual ~Component();

	virtual void Update() {}
	virtual void Parse(ParsedData& data) {};
	virtual ParsedData GetParsedData();

	bool IsFromFile();
};