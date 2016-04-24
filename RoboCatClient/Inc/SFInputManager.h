#pragma once

class SFInputManager
{
public:


	static void StaticInit();
	static unique_ptr< SFInputManager >	sInstance;

	void HandleInput(SFEInputAction inInputAction, uint8_t inKeyCode);

	const SFInputState& GetState()	const { return mCurrentState; }

	SFMoveList&			GetMoveList() { return mMoveList; }

	const SFMove*		GetAndClearPendingMove() { auto toRet = mPendingMove; mPendingMove = nullptr; return toRet; }

	void				Update();

private:

	SFInputState		mCurrentState;

	SFInputManager();
	bool				IsTimeToSampleInput();
	const SFMove&		SampleInputAsMove();
	SFMoveList			mMoveList;
	float				mNextTimeToSampleInput;
	const SFMove*		mPendingMove;
};
