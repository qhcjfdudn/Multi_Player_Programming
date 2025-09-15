#include "pch.h"
#include "Move.h"

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

Move::Move(const InputState& inInputState, float inTimestamp, float inDeltaTime) :
	mInputState(inInputState),
	mTimestamp(inTimestamp),
	mDeltaTime(inDeltaTime)
{
}

const InputState& Move::GetInputState() const
{
	return mInputState;
}

float Move::GetTimestamp() const
{
	return mTimestamp;
}

float Move::GetDeltaTime() const
{
	return mDeltaTime;
}

bool Move::Write(OutputMemoryBitStream& inOutputStream) const
{
	inOutputStream.Write(mInputState);
	inOutputStream.Write(mTimestamp);
	inOutputStream.Write(mDeltaTime);
	return true;
}

bool Move::Read(InputMemoryBitStream& inInputStream)
{
	inInputStream.Read(mInputState);
	inInputStream.Read(mTimestamp);
	inInputStream.Read(mDeltaTime);
	return true;
}
