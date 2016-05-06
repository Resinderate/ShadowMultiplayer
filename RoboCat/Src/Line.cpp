#include <RoboCatPCH.h>

Line::Line()
{
	start = sf::Vector2f();
	end = sf::Vector2f();
}

Line::Line(sf::Vector2f pStart, sf::Vector2f pEnd)
{
	start = pStart;
	end = pEnd;
}
