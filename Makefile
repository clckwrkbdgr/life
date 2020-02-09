LIBS     = -lncursesw
TARGET   = life
CXXFLAGS = -MD -MP -std=c++0x -Werror -Wall -Wextra
SOURCES = $(wildcard *.cpp)
OBJECTS = $(addprefix tmp/,$(SOURCES:.cpp=.o))
VERSION=$(shell git tag | sed 's/.*\([0-9]\+\.[0-9]\+\.[0-9]\+\)/\1/' | sort -nt . | tail -1)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) $(LIBS) -o $@ 

run: $(TARGET)
	screen ./$(TARGET)

deb: $(TARGET)
	@debpackage.py \
		life-on-console \
		-v $(VERSION) \
		--bin $(TARGET) \
		--maintainer 'umi0451 <umi0451@gmail.com>' \
		--build-dir tmp/ \
		--dest-dir . \
		--description "Implementation of Conway's Game of Life for terminal emulators."

tmp/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean Makefile

clean:
	$(RM) -rf $(TARGET) tmp/*

$(shell mkdir -p tmp)
-include $(OBJECTS:%.o=%.d)
