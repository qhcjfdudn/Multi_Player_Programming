#include "pch.h"
#include "AckRange.h"

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

AckRange::AckRange(PacketSequenceNumber packetSequenceNumber) :
	mStart{ packetSequenceNumber }, mCount{ 1 }
{
}

bool AckRange::ExtendIfShould(PacketSequenceNumber inSequenceNumber) {
	if (inSequenceNumber == mStart + mCount) {
		++mCount;
		return true;
	}
	
	return false;
}

PacketSequenceNumber AckRange::GetStart() const
{
	return mStart;
}

uint32_t AckRange::GetCount() const
{
	return mCount;
}

void AckRange::Write(OutputMemoryBitStream& inPacket) const
{
	inPacket.Write(mStart);
	bool hasCount = mCount > 1;
	inPacket.Write(hasCount);
	if (hasCount) {
		// 절대 255 이상이 될 수 없다고 가정
		uint32_t countMinusOne = mCount - 1;
		uint8_t countToAck = countMinusOne > 255 ?
			255 : static_cast<uint8_t>(countMinusOne);
		inPacket.Write(countToAck);
	}
}

void AckRange::Read(InputMemoryBitStream& inPacket)
{
	inPacket.Read(mStart);
	bool hasCount = false;
	inPacket.Read(hasCount);
	if (hasCount) {
		uint8_t countMinusOne = 0;
		inPacket.Read(countMinusOne);
		mCount = countMinusOne + 1;
	}
	else
		mCount = 1;
}