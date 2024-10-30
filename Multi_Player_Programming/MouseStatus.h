#pragma once

#include <string>

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

enum class MouseStatusProperties
{
	MSP_Name = 1 << 0,
	MSP_LegCount = 1 << 1,
	MSP_HeadCount = 1 << 2,
	MSP_Health = 1 << 3,
	MSP_MAX
};

class MouseStatus
{
public:
	void Write(OutputMemoryBitStream& inStream, uint32_t inProperties);
	void Read(InputMemoryBitStream& inStream);

private:
	std::string mName;
	int mLegCount, mHeadCount;
	float mHealth;
};

