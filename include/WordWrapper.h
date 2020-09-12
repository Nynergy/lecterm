#pragma once

#include <sstream>
#include <string>
#include <vector>

class WordWrapper {
private:
	static std::vector<std::string> getWordsFromLine(std::string line);
	static std::vector<std::string> constructWrappedLines(std::vector<std::string> words, int width);
	static bool wordFitsIntoLine(std::string word, int spaceLeft);

public:
	WordWrapper();
	~WordWrapper();
	// Overloading for vectors and single strings
	static std::vector<std::string> getWrappedLinesFromWidth(std::vector<std::string> lines, int width);
	static std::vector<std::string> getWrappedLinesFromWidth(std::string line, int width);
};
