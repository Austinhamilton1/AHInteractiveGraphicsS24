#include "TextFile.h"

TextFile::TextFile(std::string filename) {
	filePath = filename;
}

TextFile::TextFile(std::vector<char> filename) {
	filePath = std::string(filename.begin(), filename.end());
}

TextFile::TextFile(const char* filename) {
	filePath = std::string(filename);
}

bool TextFile::ReadIn() {
	std::stringstream ss;
	std::ifstream fin{};
	fin.open(filePath.c_str());
	if (fin.fail()) {
		log("Could not open: " + filePath);
		return false;
	}

	std::string line;
	while(!fin.eof()) {
		getline(fin, line);
		Trim(line);
		if (line != "") {
			data += line + "\n";
		}
	}
	fin.close();
}

void TextFile::Trim(std::string& str) {
	const std::string delimiters = " \f\n\r\t\v";
	str.erase(str.find_last_not_of(delimiters) + 1);
	str.erase(0, str.find_first_not_of(delimiters));
}
