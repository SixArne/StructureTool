#include "StructureLoader.h"

// STL includes
#include <fstream>
#include <iostream>

// External libs
#include "rapidjson.h"
#include <document.h>
#include <istreamwrapper.h>

void StructureLoader::LoadStructureFromJSON(const std::string& jsonFile, Structure& structure)
{
	auto is = std::ifstream{ jsonFile };

	if (is)
	{
		rapidjson::IStreamWrapper isw{ is };
		rapidjson::Document jsonDoc{};
		jsonDoc.ParseStream(isw);

		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); itr++)
		{
			const auto& blocks = *itr;

			Block outBlock{};
			LoadBlock(blocks, outBlock);
			structure.blocks.emplace_back(outBlock);
		}

		is.close();
	}
}

void StructureLoader::LoadBlock(const Value& blockData, Block& outBlock)
{
	// ADD LOGGING FUNCTIONALITY IN CASE MISSING
	outBlock.layer = blockData["layer"].GetString();
	outBlock.isOpaque = blockData["opaque"].GetBool();

	// Get positions json key
	const auto positions = blockData["positions"].GetArray();

	// Store positions in outBlock.
	GetPositionsFromBlock(positions, outBlock.positions);
}

void StructureLoader::GetPositionsFromBlock(const GenericArray& positionData, Positions& outPositions)
{
	for (Value::ConstValueIterator itr = positionData.Begin(); itr != positionData.End(); itr++)
	{
		const auto& coordinates = *itr;

		auto locationData = coordinates.GetArray();
		std::array<int, 3> elements{locationData[0].GetInt(), locationData[1].GetInt(), locationData[2].GetInt()};

		outPositions.emplace_back(elements);
	}
}
