CXX	= g++
FLAGS	= -O3 -Wall -Wextra -pedantic -std=c++14
SOURCE	= main.cpp
TARGET	= graph

all:
	$(CXX) $(FLAGS) -o $(TARGET) $(SOURCE)
