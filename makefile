all: chess

chess: Chessmain.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -g -o chess Chessmain.cpp
