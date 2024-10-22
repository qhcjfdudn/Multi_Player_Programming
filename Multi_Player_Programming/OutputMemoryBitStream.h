#pragma once
#include <iostream>

class OutputMemoryBitStream
{
public:
	OutputMemoryBitStream() :
		mBuffer(nullptr), mBitHead(0), mBitCapacity(0)
	{
		ReallocBuffer(256);		// 32bytes
	}
	~OutputMemoryBitStream()
	{
		free(mBuffer);
	}

	void WriteBits(uint8_t inData, size_t inBitCount);
	void WriteBits(const void* inData, size_t inBitCount);

	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetBitLength() const { return mBitHead; }
	uint32_t GetByteLength() const { return (mBitHead + 7) >> 3; }

	void WriteBytes(const void* inData, size_t inByteCount) {
		WriteBits(inData, inByteCount << 3);
	}

	void Write(uint32_t inData);

private:
	void ReallocBuffer(uint32_t newBitCapacity);

	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;
};
