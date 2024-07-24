#pragma once
#include <SFML/Graphics.hpp>

class Bullet {

	public:

		sf::Texture texture;
		sf::Sprite sprite;
	
		float speed = 2; 
		sf::Vector2f velocity;
};