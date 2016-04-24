#include <RoboCatClientPCH.h>

MouseClient::MouseClient()
{
	mSpriteComponent.reset( new SpriteComponent( this ) );
	mSpriteComponent->SetTexture( TextureManager::sInstance->GetTexture( "mouse" ) );

	m_sprite.setTexture(*SFTextureManager::sInstance->GetTexture("mouse"));
}