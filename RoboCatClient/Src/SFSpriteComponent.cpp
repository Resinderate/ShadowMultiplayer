#include <RoboCatClientPCH.h>

SFSpriteComponent::SFSpriteComponent(GameObject* inGameObject) :
	mGameObject(inGameObject)
{
	// Setting up some origin in the other one, but will have to see how that works.

	// Add to the render manager.
	// RenderManager::sInstance->AddComponent(this);
}

SFSpriteComponent::~SFSpriteComponent()
{
	// If there is a new render manager, need to remove it from here when we die.
	// RenderManager::sInstance->RemoveComponent(this);
}

void SFSpriteComponent::SetTexture(SFTexturePtr inTexture)
{
	m_sprite.setTexture(*inTexture);
}