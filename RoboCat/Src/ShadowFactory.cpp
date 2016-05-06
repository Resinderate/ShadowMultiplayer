#include "RoboCatPCH.h"

std::unique_ptr<ShadowFactory> ShadowFactory::sInstance;

void ShadowFactory::StaticInit()
{
	ShadowFactory* sf = new ShadowFactory();
	sf->load();
	sInstance.reset(sf);
}

std::vector<sf::VertexArray> ShadowFactory::getShadows(sf::Vector2f playerPosition, sf::Color color)
{
	auto lines = getShadowLines();
	std::vector<sf::VertexArray> shadows(lines.size());

	for (auto l : lines)
	{
		if (playerPosition == l.start || playerPosition == l.end)
			continue;

		sf::VertexArray shadow(sf::TrianglesStrip, 4);
		float shadowLength = 30;

		// Set the color
		for (int i = 0; i < shadow.getVertexCount(); i++)
		{
			shadow[i].color = color;
		}

		shadow[0].position = l.start;
		shadow[1].position = l.end;

		sf::Vector2f startDir = l.start - playerPosition;
		sf::Vector2f endDir = l.end - playerPosition;

		thor::unitVector(startDir);
		thor::unitVector(endDir);

		shadow[2].position = l.start + startDir * shadowLength;
		shadow[3].position = l.end + endDir * shadowLength;

		shadows.push_back(shadow);
	}

	return shadows;
}

bool ShadowFactory::load()
{
	// Might be able to perform some optimizations here.
	float rectSize = 64;

	sf::Image map;
	if (!map.loadFromFile("../Assets/maps/map.png"))
		return false;


	auto size = map.getSize();

	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			if (map.getPixel(i, j) == sf::Color::Black)
			{
				shadowCasters.push_back(sf::FloatRect(i * rectSize, j * rectSize, rectSize, rectSize));
			}
		}
	}
	// Turn these shadow casters into better shadowCasters.
	optimizeShadowCasters();

	return true;
}

bool ShadowFactory::doesCollideWithWorld(sf::FloatRect p_bounds)
{
	for (auto s : shadowCasters)
	{
		if (s.intersects(p_bounds))
		{
			return true;
		}
	}
	return false;
}

std::vector<Line> ShadowFactory::getShadowLines()
{
	// 4 lines in each rect.
	std::vector<Line> lines(shadowCasters.size() * 4);

	for (auto r : shadowCasters)
	{
		lines.push_back(Line(sf::Vector2f(r.left, r.top), sf::Vector2f(r.left + r.width, r.top)));
		lines.push_back(Line(sf::Vector2f(r.left + r.width, r.top), sf::Vector2f(r.left + r.width, r.top + r.height)));
		lines.push_back(Line(sf::Vector2f(r.left + r.width, r.top + r.height), sf::Vector2f(r.left, r.top + r.height)));
		lines.push_back(Line(sf::Vector2f(r.left, r.top + r.height), sf::Vector2f(r.left, r.top)));
	}

	return lines;
}

void ShadowFactory::optimizeShadowCasters()
{
	// Go through and reduce the shadowCasters down into a smaller possible number of rects.
	bool hit = true;
	while (hit)
	{
		hit = false;
		for (auto itr = shadowCasters.begin(); itr != shadowCasters.end(); itr++)
		{
			for (auto jtr = shadowCasters.begin(); jtr != shadowCasters.end(); jtr++)
			{
				if (itr != jtr)
				{
					// If it lines up right.
					if ((itr->top == jtr->top) && (itr->height == jtr->height) && (itr->left + itr->width == jtr->left))
					{
						// Add the width to the first one.
						itr->width += jtr->width;

						// Remove the second one.
						if (itr > jtr)
							itr = shadowCasters.begin();
						jtr = shadowCasters.erase(jtr);
						hit = true;
					}
					else if ((itr->left == jtr->left) && (itr->width == jtr->width) && (itr->top + itr->height == jtr->top))
					{
						// Add the height to the first one
						itr->height += jtr->height;

						// Remove the second one.
						if (itr > jtr)
							itr = shadowCasters.begin();
						jtr = shadowCasters.erase(jtr);
						hit = true;
					}

					if (jtr == shadowCasters.end())
						break;
				}
			}
		}
	}

}
