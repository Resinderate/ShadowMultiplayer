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
	inline void UpdateDesireVariableFromKey(SFEInputAction inInputAction, bool& ioVariable)
	{
		if (inInputAction == SFEInputAction::EIA_Pressed)
		{
			ioVariable = true;
		}
		else if (inInputAction == SFEInputAction::EIA_Released)
		{
			ioVariable = false;
		}
	}

	inline void UpdateDesireFloatFromKey(SFEInputAction inInputAction, float& ioVariable)
	{
		if (inInputAction == SFEInputAction::EIA_Pressed)
		{
			ioVariable = 1.f;
		}
		else if (inInputAction == SFEInputAction::EIA_Released)
		{
			ioVariable = 0.f;
		}
	}
}

//Kevin 
//inKeyCode will be a const uint8_t from Attributes.h associated with sf:keyboard keys 
void SFInputManager::HandleInput(SFEInputAction inInputAction, uint8_t inKeyCode)
{
	switch (inKeyCode)
	{
	case 0:
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredLeftAmount);
		break;
	case 1:
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredRightAmount);
		break;
	case 2:
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredForwardAmount);
		break;
	case 3:
		UpdateDesireFloatFromKey(inInputAction, mCurrentState.mDesiredBackAmount);
		break;
	case 4:
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