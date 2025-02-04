#ifndef JSONMANAGER_H
#define JSONMANAGER_H

class JsonManager
{
private:
	const static std::string directoryName;
	std::string _path;
	std::map<std::string, std::string> _content;

	void initIfEmpty();
	void parseJson();

public:
	JsonManager(std::string fileName);
	~JsonManager() {};

	void writeString(std::string key, std::string value);

	bool ifKeyExist(std::string key);
	std::string getStringValue(std::string key);
	int getIntegerValue(std::string key);
	bool getBooleanValue(std::string key);
};

#endif JSONMANAGER_H