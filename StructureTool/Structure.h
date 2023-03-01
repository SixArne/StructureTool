#pragma once
#include <string>
#include <vector>
#include <array>

struct Block
{
	std::string layer{};
	bool isOpaque{};
	std::vector<std::array<int, 3>> positions{};
};

struct Structure
{
	std::vector<Block> blocks{};
};