#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class Background : public sf::Drawable
{
public:
	Background();
	~Background();
	bool loadBackground(const std::string & fileName);

private:
	sf::Texture mTexture;
	sf::Sprite mSprite;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw the background
		target.draw(mSprite);
	}
};

