#include <RoboCatClientPCH.h>

unique_ptr< SFInputManager >	SFInputManager::sInstance;

namespace
{
	float kTimeBetweenInputSamples = 0.03f;
}

void SFInputManager::StaticInit()
{
	sInstance.reset(new SFInputManager());
}


namespace
{
	inline void UpdateDesireVariableFromKey(EInputAction inInputAction, bool& ioVariable)
	{
		if (inInputAction == EIA_Pressed)
		{
			ioVariable = true;
		}
		else if (inInputAction == EIA_Released)
		{
			ioVariable = false;
		}
	}

	inline void UpdateDesireFloatFromKey(EInputAction inInputAction, float& ioVariable)
	{
		if (inInputAction == EIA_Pressed)
		{
			ioVariable = 1.f;
		}
		else if (inInputAction == EIA_Released)
		{
			ioVariable = 0.f;
		}
	}
}

void SFInputManager::HandleInput(EInputAction inInputAction, int inKeyCode)
{
	switch (inKeyCode)
	{
	case 'a':
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredLeftAmount);
		break;
	case 'd':
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredRightAmount);
		break;
	case 'w':
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredForwardAmount);
		break;
	case 's':
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredBackAmount);
		break;
	case 'k':
		UpdateDesireVariableFromKey(inInputAction, mCurrentState.mIsShooting);
		break;
	}

}


SFInputManager::SFInputManager() :
	mNextTimeToSampleInput(0.f),
	mPendingMove(nullptr)
{

}

const SFMove& SFInputManager::SampleInputAsMove()
{
	return mMoveList.AddMove(GetState(), SFTiming::sInstance.GetFrameStartTime());
}

bool SFInputManager::IsTimeToSampleInput()
{
	float time = SFTiming::sInstance.GetFrameStartTime();
	if (time > mNextTimeToSampleInput)
	{
		mNextTimeToSampleInput = mNextTimeToSampleInput + kTimeBetweenInputSamples;
		return true;
	}

	return false;
}

void SFInputManager::Update()
{
	if (IsTimeToSampleInput())
	{
		mPendingMove = &SampleInputAsMove();
	}
}