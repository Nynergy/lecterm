#pragma once

#include <sstream>
#include <string>
#include <vector>

class WordWrapper {
private:
	static bool wordFitsIntoLine(std::string word, int spaceLeft);

public:
	WordWrapper();
	~WordWrapper();
	static std::vector<std::string> getWrappedLinesFromWidth(std::string line, int width);
};
