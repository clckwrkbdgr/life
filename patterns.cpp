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

,{"r-pentomino", "R-pentomino Methuselah",
	" @@\n"
	"@@\n"
	" @\n"
}

,{"diehard", "Diehard Methuselah",
	"      @\n"
	"@@\n"
	" @   @@@\n"
}

,{"acorn", "Acorn Methuselah",
	" @\n"
	"   @\n"
	"@@  @@@\n"
}

,{"infinite1", "Infinite pattern",
"      @\n"
"    @ @@\n"
"    @ @\n"
"    @\n"
"  @\n"
"@ @\n"
}

,{"infinite2", "Infinite pattern",
"@@@ @\n"
"@    \n"
"   @@\n"
" @@ @\n"
"@ @ @\n"
}

,{"infinite3", "Infinite pattern",
	"@@@@@@@@ @@@@@   @@@      @@@@@@@ @@@@@"
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
