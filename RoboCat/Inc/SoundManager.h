class SoundManager
{
public:

	static void StaticInit();
	static std::unique_ptr< SoundManager >	sInstance;
protected:
	SoundManager();
	sf::Sound sound1;
	sf::SoundBuffer sound1B;
	sf::Music bgMusic;
	void LoadSoundFromFile(sf::Sound &p_sound, sf::SoundBuffer &p_buffer, string p_file);
	void LoadMusicFromFile(sf::Music &p_music, string p_file);
};