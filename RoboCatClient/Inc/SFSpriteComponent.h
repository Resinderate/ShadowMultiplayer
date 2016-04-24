#pragma once
class SFSpriteComponent
{
public:

	SFSpriteComponent(GameObject* inGameObject);
	~SFSpriteComponent();

	void SetTexture(SFTexturePtr inTexture);
	sf::Sprite& GetSprite() { return m_sprite; }

private:

	sf::Sprite m_sprite;

	//don't want circular reference...
	GameObject* mGameObject;
};

typedef shared_ptr< SFSpriteComponent >	SFSpriteComponentPtr;