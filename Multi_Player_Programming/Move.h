#pragma once

#include "InputState.h"

class Move
{
public:
	Move(const InputState& inInputState, float inTimestamp, float inDeltaTime);

	const InputState& GetInputState() const;
	float GetTimestamp() const;
	float GetDeltaTime() const;

private:
	InputState mInputState;
	float mTimestamp;
	float mDeltaTime;
};

