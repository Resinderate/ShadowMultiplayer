#include <RoboCatClientPCH.h>

std::unique_ptr< SFRenderManager >	SFRenderManager::sInstance;

SFRenderManager::SFRenderManager()
{
	// Might need some view stuff in here or something.
}

void SFRenderManager::RenderUI()
{
	sf::Font bebas = *FontManager::sInstance->GetFont("bebas");

	sf::Text RTT, InOut, Scoreboard, Health;

	RTT.setPosition(20, 20);
	InOut.setPosition(20, 50);

	RTT.setFont(bebas);
	InOut.setFont(bebas);
	//Scoreboard.setFont(bebas);
	//Health.setFont(bebas);

	RTT.setCharacterSize(24);
	InOut.setCharacterSize(24);
	//Scoreboard.setCharacterSize(24);
	//Health.setCharacterSize(24);
	
	RTT.setColor(sf::Color::White);
	InOut.setColor(sf::Color::White);
	//Scoreboard.setColor(sf::Color::White);
	//Health.setColor(sf::Color::Black);

	// RTT
	float rttMS = NetworkManagerClient::sInstance->GetAvgRoundTripTime().GetValue() * 1000.f;
	string roundTripTime = StringUtils::Sprintf("RTT %d ms", (int)rttMS);
	RTT.setString(roundTripTime);

	// Bandwidth
	string bandwidth = StringUtils::Sprintf("In %d  Bps, Out %d Bps",
		static_cast< int >(NetworkManagerClient::sInstance->GetBytesReceivedPerSecond().GetValue()),
		static_cast< int >(NetworkManagerClient::sInstance->GetBytesSentPerSecond().GetValue()));
	InOut.setString(bandwidth);

	// Scoreboard stuff
	//const vector< ScoreBoardManager::Entry >& entries = ScoreBoardManager::sInstance->GetEntries();
	//Scoreboard.setString("");

	// HUD actually had some health in it. Not tracked really.
	//Health.setString("");

	// Draw the text to screen.
	SFWindowManager::sInstance->draw(RTT);
	SFWindowManager::sInstance->draw(InOut);

}


void SFRenderManager::StaticInit()
{
	sInstance.reset(new SFRenderManager());
}


void SFRenderManager::AddComponent(SFSpriteComponent* inComponent)
{
	mComponents.push_back(inComponent);
}

void SFRenderManager::RemoveComponent(SFSpriteComponent* inComponent)
{
	int index = GetComponentIndex(inComponent);

	if (index != -1)
	{
		int lastIndex = mComponents.size() - 1;
		if (index != lastIndex)
		{
			mComponents[index] = mComponents[lastIndex];
		}
		mComponents.pop_back();
	}
}

int SFRenderManager::GetComponentIndex(SFSpriteComponent* inComponent) const
{
	for (int i = 0, c = mComponents.size(); i < c; ++i)
	{
		if (mComponents[i] == inComponent)
		{
			return i;
		}
	}

	return -1;
}


//this part that renders the world is really a camera-
//in a more detailed engine, we'd have a list of cameras, and then render manager would
//render the cameras in order
void SFRenderManager::RenderComponents()
{
	//Get the logical viewport so we can pass this to the SpriteComponents when it's draw time

	for (auto c : mComponents)
	{
		SFWindowManager::sInstance->draw(c->GetSprite());
	}
}

void SFRenderManager::Render()
{
	//
	// Clear the back buffer
	//
	SFWindowManager::sInstance->clear(sf::Color::Blue);

	SFRenderManager::sInstance->RenderComponents();

	//HUD::sInstance->Render();
	// Might draw the UI elements in a different way. Could make a function in Render Manager to take care of it.
	SFRenderManager::sInstance->RenderUI();

	//
	// Present our back buffer to our front buffer
	//
	SFWindowManager::sInstance->display();
}