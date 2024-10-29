#pragma once

#include <iostream>

class InputMemoryBitStream
{
public:
	//InputMemoryBitStream();
	~InputMemoryBitStream() { free(mBuffer); }

	void Read(void* outData, uint32_t inBitCount);

private:
	char* mBuffer;

	uint32_t mHead;
	uint32_t mCapacity;
};

