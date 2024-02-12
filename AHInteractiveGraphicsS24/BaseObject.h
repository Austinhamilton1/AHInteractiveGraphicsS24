#pragma once
#include <sstream>
#include <vector>

//the base class for everything
class BaseObject {
protected:
	//all objects will have access to the logger
	static std::stringstream _log;

public:
	inline const std::string GetLog() const {
		return _log.str();
	}

	void log(const std::string& message) {
		_log << message << std::endl;
	}

	void log(const char* message) {
		_log << message << std::endl;
	}

	void log(const std::vector<char>& infoLog) {
		std::copy(
			infoLog.begin(), infoLog.end(),
			std::ostream_iterator<char>(_log, "")
		);
	}
};