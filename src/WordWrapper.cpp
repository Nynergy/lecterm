#include "WordWrapper.h"

static const int SPACE_WIDTH = 1;

WordWrapper::WordWrapper() {}

WordWrapper::~WordWrapper() {}

std::vector<std::string> WordWrapper::getWrappedLinesFromWidth(std::string line, int width) {
	std::stringstream ss(line);
	std::string token;
	std::vector<std::string> words;
	while(std::getline(ss, token, ' ')) {
		words.push_back(token);
	}

	std::vector<std::string> lines;
	int spaceLeft = width;
	std::string newLine = "";
	for(std::string word : words) {
		if(wordFitsIntoLine(word, spaceLeft)) {
			spaceLeft = spaceLeft - (word.length() + SPACE_WIDTH);
			newLine = newLine + word + " ";
		} else {
			// FIXME Whitespace trimming should be moved into a utility class
			lines.push_back(newLine.substr(0, newLine.length() - 1)); // Remove trailing whitespace
			newLine = word + " ";
			spaceLeft = width - (word.length() + SPACE_WIDTH);
		}
	}

	lines.push_back(newLine.substr(0, newLine.length() - 1)); // Remove trailing whitespace
	return lines;
}

bool WordWrapper::wordFitsIntoLine(std::string word, int spaceLeft) {
	return ((int)word.length() + SPACE_WIDTH) <= spaceLeft;
}
