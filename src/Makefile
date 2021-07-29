
#	Compiler: usually gcc or g++

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall

RM = rm -rf

MAIN = main
TARGET = aes
OUTPUT = ../build


all: $(TARGET)

$(TARGET):	$(MAIN).cpp $(TARGET).cpp $(TARGET).h
	$(CXX) $(CXXFLAGS) -o $(OUTPUT)/$(TARGET) $(MAIN).cpp $(TARGET).cpp




