#pragma once
//I take care of rendering things!

class SFRenderManager
{
public:

	static void StaticInit();
	static std::unique_ptr<SFRenderManager>	sInstance;

	void Render();
	void RenderComponents();

	//vert inefficient method of tracking scene graph...
	void AddComponent(SFSpriteComponent* inComponent);
	void RemoveComponent(SFSpriteComponent* inComponent);
	int	 GetComponentIndex(SFSpriteComponent* inComponent) const;

private:

	SFRenderManager();

	void RenderUI();

	//this can't be only place that holds on to component- it has to live inside a GameObject in the world
	vector< SFSpriteComponent* > mComponents;
};
