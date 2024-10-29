#include "InputMemoryBitStream.h"

void InputMemoryBitStream::Read(void* outData, uint32_t inBitCount) {

}

uint32_t InputMemoryBitStream::GetRemainingBitCount() const {
	return mBitCapacity - mBitHead;

}