#include "InputState.h"

#include "OutputMemoryBitStream.h"
#include "InputMemoryBitStream.h"

InputState::InputState() :
	mDesiredRightAmount(0.0f),
	mDesiredLeftAmount(0.0f),
	mDesiredForwardAmount(0.0f),
	mDesiredBackwardAmount(0.0f),
	mIsShooting(false)
{
}

float InputState::GetDesiredHorizontalDelta() const
{
	return mDesiredRightAmount - mDesiredLeftAmount;
}

float InputState::GetDesiredVerticalDelta() const
{
	return mDesiredForwardAmount - mDesiredBackwardAmount;
}

bool InputState::IsShooting() const
{
	return mIsShooting;
}

bool InputState::Write(OutputMemoryBitStream& inOutputStream) const
{
	inOutputStream.Write(mDesiredRightAmount);
	inOutputStream.Write(mDesiredLeftAmount);
	inOutputStream.Write(mDesiredForwardAmount);
	inOutputStream.Write(mDesiredBackwardAmount);
	inOutputStream.Write(mIsShooting);

	return true;
}

bool InputState::Read(InputMemoryBitStream& inInputStream)
{
	inInputStream.Read(mDesiredRightAmount);
	inInputStream.Read(mDesiredLeftAmount);
	inInputStream.Read(mDesiredForwardAmount);
	inInputStream.Read(mDesiredBackwardAmount);
	inInputStream.Read(mIsShooting);

	return true;
}
