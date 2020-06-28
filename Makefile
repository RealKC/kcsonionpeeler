CXX=clang++
CXXFLAGS=-std=c++2a -O3 -fexceptions -Wall -Wextra

layer0:
	$(CXX) $(CXXFLAGS) -o bin/layer0 src/layer0.cpp

layer1:
	$(CXX) $(CXXFLAGS) -o bin/layer1 src/layer1.cpp

.PHONY: all
all: layer0 layer1