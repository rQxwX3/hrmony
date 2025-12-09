CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -framework ApplicationServices
SRC = $(wildcard src/*.cpp) main.cpp
OUT = main
DEBUGOUT = maing

all: $(OUT)

debug: $(DEBUGOUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

$(DEBUGOUT): $(SRC)
	$(CXX) -g $(CXXFLAGS) $(SRC) -o $(DEBUGOUT)
