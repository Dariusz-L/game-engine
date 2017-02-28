#include "Component.h"
#include "..\..\Utility\String\StringUtility.h"

Component::Component()
{
	_isFromFile = false;
}

Component::~Component()
{
}

ParsedData Component::GetParsedData()
{
	ParsedData p;

	p["id"] = std::to_string(_id);
	p["isFromFile"] = _isFromFile ? "1" : "0";

	return p;
}

bool Component::IsFromFile()
{
	return _isFromFile;
}