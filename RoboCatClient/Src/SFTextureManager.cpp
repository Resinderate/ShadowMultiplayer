#include <RoboCatClientPCH.h>

std::unique_ptr<SFTextureManager> SFTextureManager::sInstance;

void SFTextureManager::StaticInit()
{
	sInstance.reset(new SFTextureManager());
}

SFTextureManager::SFTextureManager()
{
	CacheTexture("cat", "../Assets/cat.png");
	CacheTexture("mouse", "../Assets/mouse.png");
	CacheTexture("yarn", "../Assets/yarn.png");
	CacheTexture("hitman", "../Assets/hitman.png");
	CacheTexture("floor1", "../Assets/floor1.png");
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
