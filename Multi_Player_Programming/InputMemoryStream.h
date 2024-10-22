#pragma once
#include <iostream>

class InputMemoryStream {
public:
	void Read(void* outData,
		uint32_t inByteCount);

private:
	char* mBuffer;

	uint32_t mHead;
	uint32_t mCapacity;
};
