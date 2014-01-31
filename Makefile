LIBS     = -lncursesw
TARGET   = life
CXXFLAGS = -MD -MP -std=c++0x -Werror -Wall -Wextra
SOURCES = $(wildcard *.cpp)
OBJECTS = $(addprefix tmp/,$(SOURCES:.cpp=.o))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) $(LIBS) -o $@ 

run: $(TARGET)
	screen ./$(TARGET) gun

tmp/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean Makefile

clean:
	$(RM) -rf $(TARGET) tmp/*

$(shell mkdir -p tmp)
-include $(OBJECTS:%.o=%.d)
