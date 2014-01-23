LIBS     = -lncurses -lSDL
TARGET   = life
OBJECTS  = main.o life.o
CXXFLAGS = -Wall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) $(LIBS) -o $@ 

run: $(TARGET)
	screen ./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS)

main.o:
life.o:
