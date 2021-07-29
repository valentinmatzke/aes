
#	Compiler: usually gcc or g++

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall

RM = rm -rf

SOURCE = src
TARGET = aes
OUTPUT = build


all: $(TARGET)

$(TARGET):
	mkdir build;
	$(MAKE) -C src


test:
	$(MAKE) -C test

.PHONY: clean

clean:
	$(RM) build

