#include <RoboCatClientPCH.h>

MouseClient::MouseClient()
{
	mSpriteComponent.reset( new SpriteComponent( this ) );
	mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "mouse" ) );

	m_sprite.reset(new SFSpriteComponent(this));
	m_sprite->SetTexture(SFTextureManager::sInstance->GetTexture("mouse"));
}