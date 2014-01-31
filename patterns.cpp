#include "patterns.h"
#include <iostream>

static const Pattern predefined_patterns[] = {
{"glider", "Common glider",
"@ @\n"
" @@\n"
" @ \n"
}

,{"gun", "Glider gun",
"                           @\n"
"                          @ @\n"
"         @@               @@ @\n"
"         @ @              @@ @@   @@\n"
"    @@      @             @@ @    @@\n"
"@@ @  @  @  @             @ @\n"
"@@  @@      @              @\n"
"         @ @              \n"
"         @@               \n"
}

};


PatternFactory::PatternFactory()
{
	for(const Pattern & pattern : predefined_patterns) {
		patterns[pattern.name] = &pattern;
	}
}

bool PatternFactory::has_pattern(const std::string & name) const
{
	return patterns.count(name) > 0;
}

const char * PatternFactory::get_pattern(const std::string & name) const
{
	return patterns.at(name)->pattern;
}

void PatternFactory::print_list()
{
	for(const Pattern & pattern : predefined_patterns) {
		std::cout << pattern.name << " - " << pattern.description << '\n';
	}
}
