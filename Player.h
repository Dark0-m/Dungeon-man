#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <iostream>

class Player{

    public:

        int amountOfKills = 0;
        int maxKills = 0; 

        float swingKeyTime = 10;
        float swingTimeLimit = 10;

        sf::Texture axeTexture;
        sf::Sprite axe;

        sf::Texture skeletonTexture;
        sf::Sprite skeleton;

        sf::Text killsText;

        sf::Texture texture;
        sf::Sprite sprite;

        sf::Vector2f position;
        sf::Vector2f scale;

        sf::Vector2f velocity;
        float speed = 300.0f;

        void movement(sf::Vector2f &velocity, int speed, float dt) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                velocity.y -= speed * dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                velocity.y += speed * dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                velocity.x -= speed * dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                velocity.x += speed * dt;
        }

        void Collision(sf::Sprite& player, sf::Sprite& wall, sf::Vector2f& velocity) {
            auto playerBounds = player.getGlobalBounds();
            auto wallBounds = wall.getGlobalBounds();

            sf::FloatRect nextPos = playerBounds;
            nextPos.left += velocity.x;
            nextPos.top += velocity.y;

            if (nextPos.intersects(wallBounds)) {

                float deltaX = playerBounds.left + playerBounds.width / 2 - (wallBounds.left + wallBounds.width / 2);
                float deltaY = playerBounds.top + playerBounds.height / 2 - (wallBounds.top + wallBounds.height / 2);

                // Calculate the intersection depth
                float intersectX = (playerBounds.width / 2 + wallBounds.width / 2) - abs(deltaX);
                float intersectY = (playerBounds.height / 2 + wallBounds.height / 2) - abs(deltaY);

                // Resolve the collision
                if (intersectX < intersectY) {
                    if (deltaX > 0)
                        velocity.x = intersectX;
                    else
                        velocity.x = -intersectX;
                }
                else {
                    if (deltaY > 0)
                        velocity.y = intersectY;
                    else
                        velocity.y = -intersectY;
                }
            }
        }

};