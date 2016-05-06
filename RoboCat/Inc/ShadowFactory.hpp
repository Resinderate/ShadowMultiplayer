// Written by: Ronan

#ifndef SHADOWFACTORY_HPP
#define SHADOWFACTORY_HPP

class ShadowFactory
{
public:
	std::vector<sf::VertexArray> getShadows(sf::Vector2f playerPosition, sf::Color color);
	bool load();
	bool doesCollideWithWorld(sf::FloatRect p_bounds);

private:
	std::vector<sf::FloatRect> shadowCasters;

	std::vector<Line> getShadowLines();
	void optimizeShadowCasters();
};
#endif