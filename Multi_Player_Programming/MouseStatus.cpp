#include "MouseStatus.h"
#include "GetRequiredBits.h"

void MouseStatus::Write(OutputMemoryBitStream& inStream, uint32_t inProperties)
{
	inStream.WriteBits(inProperties,
		GetRequiredBits<static_cast<int>(MouseStatusProperties::MSP_MAX)>::value);

	if (inProperties & static_cast<int>(MouseStatusProperties::MSP_Name)) {
		inStream.Write(mName);
	}
	if (inProperties & static_cast<int>(MouseStatusProperties::MSP_LegCount)) {
		inStream.Write(mLegCount);
	}
	if (inProperties & static_cast<int>(MouseStatusProperties::MSP_HeadCount)) {
		inStream.Write(mHeadCount);
	}
	if (inProperties & static_cast<int>(MouseStatusProperties::MSP_Health)) {
		inStream.Write(static_cast<uint32_t>(mHealth));
	}
}