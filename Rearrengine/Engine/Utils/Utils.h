#pragma once

#include "Math/float3.h"

#include <fstream>
#include <json/json.h>
#include <json/writer.h>

static void Float3ToJson(Json::Value& _arrayValue, float3 _value) {
	for (unsigned int i = 0; i < 3; i++) {
		_arrayValue.append(_value[i]);
	}
}

static void PrintToFile(std::string _name, std::string _directory, Json::Value& _root) {
	Json::StyledStreamWriter writer;
	std::string path = JSON_ROOT_PATH;
	std::string extension = JSON_FILE_EXTENSION;
	path.append(_directory + _name + extension);
	std::ofstream output_file(path);
	writer.write(output_file, _root);
	output_file.close();
}

static Json::Value LoadFromFile(std::string _path, Json::Value& _root) {
	Json::CharReaderBuilder reader;
	std::ifstream input_file(_path);
	std::string error;

	if (!Json::parseFromStream(reader, input_file, &_root, &error)) {
		LOG("%s", error);
		return NULL;
	}
	input_file.close();

	return _root;
}