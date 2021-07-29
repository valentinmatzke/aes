
#	Compiler: usually gcc or g++

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall

RM = rm -rf

TARGET = src/aes
OUTPUT = build/aes



all: $(TARGET)

$(TARGET):	$(TARGET).cpp $(TARGET).h
	mkdir build;
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(TARGET).cpp


test:

.PHONY: clean

clean:
	$(RM) build

