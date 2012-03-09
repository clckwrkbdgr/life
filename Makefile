LIBS     = -lncurses
TARGET   = life
LANG     = cpp
CXXFLAGS = -Wall

all: $(TARGET)

$(TARGET): $(TARGET).$(LANG)
	$(CXX) $^ $(CXXFLAGS) $(LIBS) -o $@ 

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)

