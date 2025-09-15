#include "pch.h"
#include "OutputMemoryBitStream.h"

void OutputMemoryBitStream::ReallocBuffer(uint32_t newBitCapacity) {

}


void OutputMemoryBitStream::WriteBits(uint8_t inData, size_t inBitCount)
{
	// inBitCount와 비교해 buffer의 사이즈를 늘려줄지 판단
	uint32_t nextBitHead = mBitHead + static_cast<uint32_t>(inBitCount);
	if (nextBitHead > mBitCapacity) {
		ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));
	}

	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 7;

	// 현재 처리 중 바이트에 inData 중 쓸 수 있는 만큼 우선 쓰기
	uint8_t currentMask = ~(0xff << bitOffset);
	mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

	// inData의 쓰지 못한 상위 부분 쓰기
	uint32_t bitsFreeThisByte = 8 - bitOffset;
	if (inBitCount > bitsFreeThisByte) {
		mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
	}

	mBitHead += nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void* inData, size_t inBitCount)
{
	const char* srcByte = static_cast<const char*>(inData);

	while (inBitCount > 8) {
		WriteBits(*srcByte, 8);
		srcByte++;
		inBitCount -= 8;
	}

	if (inBitCount > 0) {
		WriteBits(*srcByte, inBitCount);
	}
}

void OutputMemoryBitStream::Write(uint32_t inData)
{
	WriteBits(&inData, sizeof(uint32_t) << 3);
}

void OutputMemoryBitStream::Write(std::string inData)
{

}

void OutputMemoryBitStream::Write(Vector3 inData)
{}

void OutputMemoryBitStream::Write(InputState inData)
{
}
