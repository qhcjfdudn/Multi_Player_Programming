#pragma once

#include <iostream>
#include <string>

class InputMemoryBitStream
{
public:
	//InputMemoryBitStream();
	~InputMemoryBitStream() { free(mBuffer); }

	void Read(void* outData, uint32_t inBitCount);
	void Read(uint32_t& outData);
	void Read(uint32_t& outData, uint32_t inBitCount);
	void Read(std::string& outData);
	void Read(int& outData);
	void Read(float& outData);

	uint32_t GetRemainingBitCount() const;

private:
	char* mBuffer;

	uint32_t mBitHead;
	uint32_t mBitCapacity;
};

