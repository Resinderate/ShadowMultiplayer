#pragma once
class SFSpriteComponent
{
public:

	SFSpriteComponent(GameObject* inGameObject);
	~SFSpriteComponent();

	void SetTexture(SFTexturePtr inTexture);
	sf::Sprite& GetSprite();

private:

	sf::Sprite m_sprite;

	//don't want circular reference...
	GameObject* mGameObject;
};

typedef shared_ptr< SFSpriteComponent >	SFSpriteComponentPtr;