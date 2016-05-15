#include <RoboCatClientPCH.h>

std::unique_ptr<SFTextureManager> SFTextureManager::sInstance;

void SFTextureManager::StaticInit()
{
	sInstance.reset(new SFTextureManager());
}

SFTextureManager::SFTextureManager()
{
	CacheTexture("cat", "../Assets/cat.png");
	CacheTexture("heart", "../Assets/heart.png");
	CacheTexture("yarn", "../Assets/yarn.png");
	CacheTexture("tile", "../Assets/tile.png");
	CacheTexture("wood", "../Assets/wood.png");
	CacheTexture("stone", "../Assets/stone.png");
	CacheTexture("grass", "../Assets/grass.png");
	CacheTexture("start_screen", "../Assets/start_screen.png");

	// Player textures.
	CacheTexture("hitman", "../Assets/hitman.png");
	CacheTexture("hatman", "../Assets/hatman.png");
	CacheTexture("man_blue", "../Assets/man_blue.png");
	CacheTexture("man_brown", "../Assets/man_brown.png");
	CacheTexture("man_old", "../Assets/man_old.png");
	CacheTexture("robot", "../Assets/robot.png");
	CacheTexture("soldier", "../Assets/soldier.png");
	CacheTexture("woman", "../Assets/woman.png");
	CacheTexture("zombie", "../Assets/zombie.png");

}

SFTexturePtr SFTextureManager::GetTexture(const string & inTextureName)
{
	return mNameToTextureMap[inTextureName];
}

bool SFTextureManager::CacheTexture(string inName, const char * inFileName)
{
	SFTexturePtr newTex(new sf::Texture());
	if (!newTex->loadFromFile(inFileName))
		return false;

	mNameToTextureMap[inName] = newTex;
	return true;
}
