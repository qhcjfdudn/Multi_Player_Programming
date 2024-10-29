#pragma once
#include <iostream>

enum {
	STREAM_ENDIANNESS, PLATFORM_ENDIANNESS
};

class OutputMemoryStream {
public:
	OutputMemoryStream() :
		mBuffer(nullptr), mHead(0), mCapacity(0)
	{
		ReallocBuffer(32);
	}
	~OutputMemoryStream()
	{
		free(mBuffer);
	}

	const char* GetBufferPtr() { return mBuffer; }
	uint32_t GetLength() const { return mHead; }


	void Write(const void* inData, size_t inByteCount);

	template<typename T>
	void Write(const T& inData) {
		static_assert(
			std::is_arithmetic_v<T> ||
			std::is_enum_v<T>,
			"Generic write only supports primitive data types.");

		if (STREAM_ENDIANNESS == PLATFORM_ENDIANNESS)
		{
			Write(&inData, sizeof(inData));
		}
		else
		{
			T swappedData = ByteSwap(inData);
			Write(&swappedData, sizeof(inData));
		}
	}

private:
	void ReallocBuffer(uint32_t inNewLength);

	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};