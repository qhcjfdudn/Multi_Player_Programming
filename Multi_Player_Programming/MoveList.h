#pragma once

#include <deque>

#include "Move.h"

class InputState;

class MoveList
{
public:
	MoveList();

	const Move& AddMove(const InputState& inInputState,
		float inTimestamp);

	bool HasMoves() const;
	int GetMoveCount() const;
	void Clear();

private:
	std::deque<Move> mMoves;
	float mLastMoveTimestamp;
};
