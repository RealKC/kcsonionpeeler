CXX=clang++
CXXFLAGS=-std=c++17 -O3 -fexceptions -Wall -Wextra

layer0:
	$(CXX) $(CXXFLAGS) -o bin/layer0 src/layer0.cpp
