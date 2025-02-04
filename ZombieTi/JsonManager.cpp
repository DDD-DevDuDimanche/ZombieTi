#include "pch.h"
#include "JsonManager.h"

const std::string JsonManager::directoryName = "Data";

// Verify if the json file is empty to init it with new brackets
void JsonManager::initIfEmpty()
{
	std::ifstream file(_path);
	bool isEmpty = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n') == 0;
	file.close();

	if (isEmpty)
	{
		std::ofstream file(_path);
		file << "{\n}";
		file.close();
	}
}

void JsonManager::parseJson()
{
	std::ifstream file(_path);
	std::string line;
	std::vector<std::string> data;

	while (std::getline(file, line))
	{
		if (line.compare("{") != 0 && line.compare("}") != 0)
		{
			line.erase(std::remove(line.begin(), line.end(), ':'));
			line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());

			std::stringstream ss(line);
			std::string tempString;

			while (std::getline(ss, tempString, '"'))
			{
				if (tempString.compare("") != 0) {
					data.push_back(tempString);
				}
			}
		}
	}

	file.close();

	for (int index = 0; index < data.size(); index++) {
		if (index == 0 || index % 2 == 0)
		{
			_content[data[index]] = data[index + 1];
		}
	}
}

JsonManager::JsonManager(std::string fileName)
{
	// Create a Data folder if doesn't exist
	if (!std::filesystem::is_directory(JsonManager::directoryName)) {
		std::filesystem::create_directory(JsonManager::directoryName);
	}

	_path = JsonManager::directoryName + "/" + fileName + ".json";
	initIfEmpty();
	parseJson();
}

void JsonManager::writeString(std::string key, std::string value)
{
	for (auto& element : _content)
	{
		std::cout << element.first << " -> " << element.second << std::endl;
	}
}

bool JsonManager::ifKeyExist(std::string key)
{
	return _content.count(key) != 0;
}

std::string JsonManager::getStringValue(std::string key)
{
	if (!ifKeyExist(key)) {
		throw "JsonManager::getStringValue::" + key + " wasn't found";
	}

	return _content[key];
}

// Return -1 if error
int JsonManager::getIntegerValue(std::string key)
{
	if (!ifKeyExist(key)) {
		throw "JsonManager::getIntegerValue::" + key + " wasn't found";
	}

	return std::stoi(_content[key]);
}

bool JsonManager::getBooleanValue(std::string key)
{
	if (!ifKeyExist(key)) {
		throw "JsonManager::getBooleanValue::" + key + " wasn't found";
	}

	// Value is not a boolean
	if (_content[key].compare("true") != 0 && _content[key].compare("false") != 0) {
		throw "JsonManager::getBooleanValue::" + key + " isn't a boolean value";
	}

	return _content[key].compare("true") == 0;
}
