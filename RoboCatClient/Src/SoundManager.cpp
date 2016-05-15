#include "RoboCatClientPCH.h"

std::unique_ptr< SoundManager >	SoundManager::sInstance;

void SoundManager::StaticInit()
{
	sInstance.reset(new SoundManager());
}

SoundManager::SoundManager()
{
	LoadSoundFromFile(pickup, pickupB, "../Assets/audio/Pickup.wav");
	LoadMusicFromFile(bgMusic, "../Assets/audio/background.wav");
}

void SoundManager::LoadSoundFromFile(sf::Sound &p_sound, sf::SoundBuffer &p_buffer, string p_file)
{
	if (p_buffer.loadFromFile(p_file))
	{
		p_sound.setBuffer(p_buffer);
		p_sound.setVolume(50);
	}
}

void SoundManager::LoadMusicFromFile(sf::Music &p_music, string p_file)
{
	p_music.openFromFile(p_file);
	p_music.setLoop(true);
	p_music.setVolume(25);
}

void SoundManager::PlayMusic()
{
	bgMusic.play();
}