LIBS     = -lncurses
TARGET   = life
OBJECTS  = main.o
VERSION  = 0.2.0.0
CXXFLAGS = -Wall
TARBALL  = ../$(TARGET)-$(VERSION).tar.bz2

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(CXXFLAGS) $(LIBS) -o $@ 

run: $(TARGET)
	./$(TARGET)

.PHONY: clean bak
clean:
	$(RM) *.o $(TARGET)

bak:
	tar cjf $(TARBALL) ..

###################################################

main.o: 

