#include "Move.h"

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
