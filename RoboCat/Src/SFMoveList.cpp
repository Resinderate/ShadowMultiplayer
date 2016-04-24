#include <RoboCatPCH.h>

const SFMove& SFMoveList::AddMove(const SFInputState& inInputState, float inTimestamp)
{
	//first move has 0 time. it's okay, it only happens once
	float deltaTime = mLastMoveTimestamp >= 0.f ? inTimestamp - mLastMoveTimestamp : 0.f;

	mMoves.emplace_back(inInputState, inTimestamp, deltaTime);

	mLastMoveTimestamp = inTimestamp;

	return mMoves.back();
}

bool SFMoveList::AddMoveIfNew(const SFMove& inMove)
{
	//we might have already received this move in another packet ( since we're sending the same move in multiple packets )
	//so make sure it's new...

	//adjust the deltatime and then place!
	float timeStamp = inMove.GetTimestamp();

	if (timeStamp > mLastMoveTimestamp)
	{
		float deltaTime = mLastMoveTimestamp >= 0.f ? timeStamp - mLastMoveTimestamp : 0.f;

		mLastMoveTimestamp = timeStamp;

		mMoves.emplace_back(inMove.GetInputState(), timeStamp, deltaTime);
		return true;
	}

	return false;
}

void SFMoveList::RemovedProcessedMoves(float inLastMoveProcessedOnServerTimestamp)
{
	while (!mMoves.empty() && mMoves.front().GetTimestamp() <= inLastMoveProcessedOnServerTimestamp)
	{
		mMoves.pop_front();
	}
}
