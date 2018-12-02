#pragma once
 
#include <SFML/Graphics.hpp>

class Points : public sf::Drawable, public sf::Transformable
{
public:
	
	Points(unsigned int width, unsigned int height);
	~Points(){}

private:
	unsigned int mWidth;
	unsigned int mHeight;
	sf::VertexArray mPoints;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw the vertex array
		target.draw(mPoints);
	}
};

