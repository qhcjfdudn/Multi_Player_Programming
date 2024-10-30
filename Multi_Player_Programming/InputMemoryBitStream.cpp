#include "InputMemoryBitStream.h"

void InputMemoryBitStream::Read(void* outData, uint32_t inBitCount)
{

}

void InputMemoryBitStream::Read(uint32_t& outData)
{

}

uint32_t InputMemoryBitStream::GetRemainingBitCount() const
{
	return mBitCapacity - mBitHead;

}