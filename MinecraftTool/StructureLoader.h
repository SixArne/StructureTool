#ifndef STRUCTURE_LOADER_H
#define STRUCTURE_LOADER_H

#include <string>

#include <rapidjson/document.h>

#include "Structure.h"

using rapidjson::Value;
using rapidjson::GenericArray;
using rapidjson::GenericValue;
using rapidjson::UTF8;

class StructureLoader final
{
	typedef std::vector<std::array<int, 3>> Positions;
	typedef GenericArray<true, GenericValue<UTF8<>>> GenericArray;

public:
	static void LoadStructureFromJSON(const std::string& jsonFile, Structure& structure);

private:
	static void LoadBlock(const Value& blockData, Block& outBlock);
	static void GetPositionsFromBlock(const GenericArray& positionData, Positions& outPositions);
};

#endif
