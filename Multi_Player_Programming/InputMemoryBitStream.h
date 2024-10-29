#pragma once

#include <iostream>

class InputMemoryBitStream
{
public:
	//InputMemoryBitStream();
	~InputMemoryBitStream() { free(mBuffer); }

	void Read(void* outData, uint32_t inBitCount);

	uint32_t GetRemainingBitCount() const;

private:
	char* mBuffer;

	uint32_t mBitHead;
	uint32_t mBitCapacity;
};

