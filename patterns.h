#pragma once
#include <map>

struct PatternFactory {
	PatternFactory();
	bool has_pattern(const std::string & name) const;
	const char * get_pattern(const std::string & name) const;
private:
	std::map<std::string, const char *> patterns;
};
