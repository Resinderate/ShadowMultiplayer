#pragma once

class SFMove
{
public:

	SFMove() {}

	SFMove(const SFInputState& inInputState, float inTimestamp, float inDeltaTime) :
		mInputState(inInputState),
		mTimestamp(inTimestamp),
		mDeltaTime(inDeltaTime)
	{}


	const SFInputState&	GetInputState()	const { return mInputState; }
	float				GetTimestamp()	const { return mTimestamp; }
	float				GetDeltaTime()	const { return mDeltaTime; }

	//bool Write(OutputMemoryBitStream& inOutputStream) const;
	//bool Read(InputMemoryBitStream& inInputStream);

private:
	SFInputState	mInputState;
	float		mTimestamp;
	float		mDeltaTime;

};
