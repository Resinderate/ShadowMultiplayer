class SoundManager
{
public:

	static void StaticInit();
	static std::unique_ptr< SoundManager >	sInstance;

	void PlaySound();
	void PlayMusic();
protected:
	SoundManager();
	sf::Sound pickup;
	sf::SoundBuffer pickupB;
	sf::Music bgMusic;
	void LoadSoundFromFile(sf::Sound &p_sound, sf::SoundBuffer &p_buffer, string p_file);
	void LoadMusicFromFile(sf::Music &p_music, string p_file);
};