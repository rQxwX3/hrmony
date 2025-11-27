CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -framework ApplicationServices
SRC = $(wildcard src/*.cpp) main.cpp
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)
