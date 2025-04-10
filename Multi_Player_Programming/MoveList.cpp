#include "MoveList.h"

MoveList::MoveList() : mLastMoveTimestamp(-1.f)
{
}

const Move& MoveList::AddMove(const InputState& inInputState, float inTimestamp)
{
	float deltaTime = mLastMoveTimestamp >= 0.0f ?
		inTimestamp - mLastMoveTimestamp : 0.0f;

	mMoves.emplace_back(inInputState, inTimestamp, deltaTime);
	mLastMoveTimestamp = inTimestamp;

	return mMoves.back();
}

bool MoveList::HasMoves() const
{
	return mMoves.empty() == false;
}

int MoveList::GetMoveCount() const
{
	return static_cast<int>(mMoves.size());
}

void MoveList::Clear()
{
	mMoves.clear();
}
