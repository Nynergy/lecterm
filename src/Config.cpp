#include "Config.h"

// FIXME This method of config pathing seems awkward
static const char * CONFIG_PATH = "config";

Config::Config() {}

Config & Config::getInstance() {
	static Config instance;
	return instance;
}

void Config::addKeyValuePair(std::string key, std::string value) {
	config.insert({key, value});
}

void Config::readFromConfigFile() {
	ConfigParser * parser = new ConfigParser();
	parser->parseKeyValuePairs();
	delete parser;
}

std::string Config::getValueFromKey(std::string key) {
	return config[key];
}

ConfigParser::ConfigParser() {
	config.open (CONFIG_PATH, std::ifstream::in);
}

ConfigParser::~ConfigParser() {
	config.close();
}

// FIXME Heavily nested code should be broken up into multiple methods
void ConfigParser::parseKeyValuePairs() {
	Config & instance = Config::getInstance();
	std::string line;
	while(std::getline(config, line)) {
		std::istringstream lineStream(line);
		std::string key;
		if(std::getline(lineStream, key, '=')) {
			std::string value;
			if(std::getline(lineStream, value)) {
				instance.addKeyValuePair(trimWhitespace(key), trimWhitespace(value));
			}
		}
	}
}

std::string ConfigParser::trimWhitespace(std::string str) {
	size_t first = str.find_first_not_of(' ');
	if(std::string::npos == first) {
		return str;
	}

	size_t last = str.find_last_not_of(' ');

	return str.substr(first, (last - first + 1));
}
