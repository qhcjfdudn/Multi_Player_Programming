#pragma once

class OutputMemoryBitStream;
class InputMemoryBitStream;

class InputState
{
public:
	InputState();

	float GetDesiredHorizontalDelta() const;
	float GetDesiredVerticalDelta() const;

	bool IsShooting() const;
	
	bool Write(OutputMemoryBitStream& inOutputStream) const;
	bool Read(InputMemoryBitStream& inInputStream);

private:
	float mDesiredRightAmount, mDesiredLeftAmount;
	float mDesiredForwardAmount, mDesiredBackwardAmount;
	bool mIsShooting;
};
