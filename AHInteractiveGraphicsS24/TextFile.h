#pragma once
#include <sstream>
#include <fstream>
#include "BaseObject.h"

class TextFile : public BaseObject {
protected:
	std::string data;
	std::string filePath;

public:
	TextFile(std::string filename);
	TextFile(std::vector<char> filename);
	TextFile(const char* filename);

	inline const std::string& GetData() const { return data; }

	bool ReadIn();
	void Trim(std::string& str);
};