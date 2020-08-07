#pragma once

// Singleton object
class Config {
private:
	Config();

public:
	static Config & getInstance();
	Config(Config const &) = delete;
	void operator=(Config const &) = delete;
};
