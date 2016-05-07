#include <RoboCatClientPCH.h>

unique_ptr< InputManager >	InputManager::sInstance;

namespace
{
	float kTimeBetweenInputSamples = 0.03f;
}

void InputManager::StaticInit()
{
	sInstance.reset( new InputManager() );
}


namespace
{
	inline void UpdateDesireVariableFromKey( EInputAction inInputAction, bool& ioVariable )
	{
		if( inInputAction == EIA_Pressed )
		{
			ioVariable = true;
		}
		else if( inInputAction == EIA_Released )
		{
			ioVariable = false;
		}
	}

	inline void UpdateDesireFloatFromKey(EInputAction inInputAction, float& ioVariable )
	{
		if( inInputAction == EIA_Pressed )
		{
			ioVariable = 1.f;
		}
		else if( inInputAction == EIA_Released )
		{
			ioVariable = 0.f;
		}
	}
}

void InputManager::HandleInput( EInputAction inInputAction, int inKeyCode )
{
	// Could just set the numbers here for input from controller.
	switch( inKeyCode )
	{
	case sf::Keyboard::A:
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredLeftAmount );
		break;
	case sf::Keyboard::D:
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredRightAmount );
		break;
	case sf::Keyboard::W:
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredForwardAmount );
		break;
	case sf::Keyboard::S:
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredBackAmount );
		break;
	case sf::Keyboard::K:
		UpdateDesireVariableFromKey( inInputAction, mCurrentState.mIsShooting );
		break;
	}

}

void InputManager::HandleControllerInput(sf::Vector2f p_axis)
{
	mCurrentState.mDesiredForwardAmount = std::max(p_axis.y, 0.f);
	mCurrentState.mDesiredBackAmount = std::min(p_axis.y, 0.f);
	
	mCurrentState.mDesiredLeftAmount = std::min(p_axis.x, 0.f);
	mCurrentState.mDesiredRightAmount = std::max(p_axis.x, 0.f);
}


InputManager::InputManager() :
	mNextTimeToSampleInput( 0.f ),
	mPendingMove( nullptr )
{

}

const Move& InputManager::SampleInputAsMove()
{
	return mMoveList.AddMove( GetState(), Timing::sInstance.GetFrameStartTime() );
}

bool InputManager::IsTimeToSampleInput()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if( time > mNextTimeToSampleInput )
	{
		mNextTimeToSampleInput = mNextTimeToSampleInput + kTimeBetweenInputSamples;
		return true;
	}

	return false;
}

void InputManager::Update()
{
	if( IsTimeToSampleInput() )
	{
		mPendingMove = &SampleInputAsMove();
	}
}