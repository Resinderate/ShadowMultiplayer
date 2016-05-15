#include <RoboCatServerPCH.h>


MouseServer::MouseServer()
{
}

void MouseServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}


bool MouseServer::HandleCollisionWithCat( RoboCat* inCat )
{
	if (!picked)
	{
		inCat->GetHealth()++;
		picked = true;
		
		// Hacked in here.
		int ECRS_Health = 1 << 3;
		NetworkManagerServer::sInstance->SetStateDirty(inCat->GetNetworkId(), ECRS_Health);
	}
	//kill yourself!
	SetDoesWantToDie( true );

	ScoreBoardManager::sInstance->IncScore( inCat->GetPlayerId(), 1 );

	return false;
}


