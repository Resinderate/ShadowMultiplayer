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