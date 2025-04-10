#include "InputMemoryBitStream.h"

void InputMemoryBitStream::Read(void* outData, uint32_t inBitCount)
{

}

void InputMemoryBitStream::Read(uint32_t& outData)
{

}
void InputMemoryBitStream::Read(uint32_t& outData, uint32_t inBitCount)
{

}
void InputMemoryBitStream::Read(std::string& outData)
{

}
void InputMemoryBitStream::Read(int& outData)
{

}
void InputMemoryBitStream::Read(float& outData)
{

}

void InputMemoryBitStream::Read(Vector3& outData)
{

}

void InputMemoryBitStream::Read(bool& outData)
{
}

uint32_t InputMemoryBitStream::GetRemainingBitCount() const
{
	return mBitCapacity - mBitHead;

}