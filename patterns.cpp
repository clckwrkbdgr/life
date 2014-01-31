#include "patterns.h"

static const char glider[] =
"@ @\n"
" @@\n"
" @ \n"
;

static const char gun[] =
"                           @\n"
"                          @ @\n"
"         @@               @@ @\n"
"         @ @              @@ @@   @@\n"
"    @@      @             @@ @    @@\n"
"@@ @  @  @  @             @ @\n"
"@@  @@      @              @\n"
"         @ @              \n"
"         @@               \n"
;


PatternFactory::PatternFactory()
{
	patterns["glider"] = glider;
	patterns["gun"] = gun;
}

bool PatternFactory::has_pattern(const std::string & name) const
{
	return patterns.count(name) > 0;
}

const char * PatternFactory::get_pattern(const std::string & name) const
{
	return patterns.at(name);
}

