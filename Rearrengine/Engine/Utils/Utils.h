#pragma once

#include "json/json.h"
#include "Math/float3.h"

#include <fstream>
#include <json/writer.h>

void Float3ToJson(Json::Value& _arrayValue, float3 _value) {
	for (unsigned int i = 0; i < 3; i++) {
		_arrayValue.append(_value[i]);
	}
}

void PrintToFile(std::string _name, Json::Value& _root) {
	Json::StyledStreamWriter writer;
	_name.append(".json");
	std::ofstream config_doc(_name);
	writer.write(config_doc, _root);
}