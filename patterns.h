#pragma once
#include <map>

struct Pattern {
	const char * name;
	const char * description;
	const char * pattern;
};

struct PatternFactory {
	PatternFactory();
	bool has_pattern(const std::string & name) const;
	const char * get_pattern(const std::string & name) const;
	static void print_list();
private:
	std::map<std::string, const Pattern *> patterns;
};
