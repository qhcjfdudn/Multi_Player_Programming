#pragma once

#include "InputState.h"

class OutputMemoryBitStream;
class InputMemoryBitStream;

class Move
{
public:
	Move(const InputState& inInputState, float inTimestamp, float inDeltaTime);

	const InputState& GetInputState() const;
	float GetTimestamp() const;
	float GetDeltaTime() const;

	bool Write(OutputMemoryBitStream& inOutputStream) const;
	bool Read(InputMemoryBitStream& inInputStream);

private:
	InputState mInputState;
	float mTimestamp;
	float mDeltaTime;
};
