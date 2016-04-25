#include <RoboCatClientPCH.h>

SFSpriteComponent::SFSpriteComponent(GameObject* inGameObject) :
	mGameObject(inGameObject)
{
	// Add to the render manager.
	SFRenderManager::sInstance->AddComponent(this);
}

SFSpriteComponent::~SFSpriteComponent()
{
	// If there is a new render manager, need to remove it from here when we die.
	SFRenderManager::sInstance->RemoveComponent(this);
}

void SFSpriteComponent::SetTexture(SFTexturePtr inTexture)
{
	m_sprite.setTexture(*inTexture);
}

sf::Sprite & SFSpriteComponent::GetSprite()
{
	// Update the sprite based on the game object stuff.
	auto pos = mGameObject->GetLocation();
	auto rot = RoboMath::ToDegrees(mGameObject->GetRotation());
	auto size = SFWindowManager::sInstance->getSize();
	m_sprite.setPosition(pos.mX * size.x, pos.mY * size.y);
	m_sprite.setRotation(rot);

	
	return m_sprite;
}
