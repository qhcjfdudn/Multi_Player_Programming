#include "OutputMemoryStream.h"

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	//handle realloc failure
	//...
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData,
	size_t inByteCount)
{
	//make sure we have space...
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
	{
		ReallocBuffer(std::max(mCapacity * 2, resultHead));
	}

	//copy into buffer at head
	std::memcpy(mBuffer + mHead, inData, inByteCount);

	//increment head for next write
	mHead = resultHead;
}