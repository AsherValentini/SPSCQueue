#pragma once
#include <string>

struct Tick {
	std::string symbol_;
	int price_;
	Tick(std::string symbol, int price) : symbol_(symbol), price_(price) {}
};