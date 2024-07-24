#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Math.h"
#include "Bullet.h"
#include <iostream>
#include <random>

#define MAPWIDTH 30
#define MAPHEIGHT 15

class Game {
	public:

        Math math;

        sf::View mainView;
        bool inMenu = true;

        sf::Music Dungeonmusic;

        int gridSize;
		
        Player player;

        sf::Text finsh;
        bool finshGame = false;;
		
        sf::Texture wallTexture;
		sf::Sprite wall;

        std::vector<sf::Sprite> walls;

        sf::Texture torchTexture;
        sf::Sprite torch;

        sf::Texture chainTexture;
        sf::Sprite chain;

        std::vector<sf::Sprite> chains;

        sf::Texture skeletonTexture;
        sf::Sprite skeleton;

        std::vector<sf::Sprite> skeletons;

        sf::Texture arrowTexture;
        sf::Sprite arrow;

        sf::Texture infectedBoneTexture;
        sf::Sprite infectedBone;

        sf::Texture groundTexture;
        sf::Sprite ground;

        std::vector<sf::Sprite> grounds;

        std::vector<sf::Sprite> infectedBones;

        sf::Texture spellBallTexture;
        Bullet spellBall;
        
        std::vector<Bullet> spellBalls;

        sf::Texture gateTexture;
        sf::Sprite gate;
		
		sf::Font font;

		sf::Clock clock;
		float dt;

        sf::Text start;
        sf::Text exit;
        sf::Text title;

        int menuButtonIndex = 0;
        float menuRandPos = 27;
        float menuRandPosLimit = 27;

        char map[MAPHEIGHT][MAPWIDTH]{
            {"####################G########"},
            {"#C....C.#...S...#......#..S.#"},
            {"#..S....###...###...........#"},
            {"#.........#...#.............#"},
            {"#....######...######.###...##"},
            {"##..##C.......C...C###.....C#"},
            {"#C..P.......................#"},
            {"#........................S..#"},
            {"##..##.............###......#"},
            {"#....######...######.###..###"},
            {"#.........#...#........#...C#"},
            {"#.......###...###....###....#"},
            {"#.S.....#C..S..C#....#C..S..#"},
            {"#.......#.......#....#......#"},
            {"#############################"},
        };


	protected:
        
		void Start(sf::RenderWindow &window) {

            mainView.setSize(sf::Vector2f(window.getSize()));

            Dungeonmusic.openFromFile("Music\\dark-ambient-atmosphere-2-141314.mp3");

			//Fonts
			font.loadFromFile("Fonts\\Minecraft.ttf");

            player.killsText.setPosition(window.getSize().x / 2 - 50, 20);
            player.killsText.setFont(font);
            player.killsText.setCharacterSize(24);
            player.killsText.setFillColor(sf::Color::White);

            //player
            player.texture.loadFromFile("Textures\\muthafer.jpg");
            player.sprite.setTexture(player.texture);
            player.sprite.setPosition(300, 500);
            player.sprite.setScale(0.125, 0.125);

            player.axeTexture.loadFromFile("Textures\\axe.png");
            player.axe.setTexture(player.axeTexture);
            player.axe.setScale(4, 4);

            player.skeletonTexture.loadFromFile("Textures\\skeleton.png");
            player.skeleton.setTexture(player.skeletonTexture);
            player.skeleton.setPosition(player.killsText.getPosition().x - 40, player.killsText.getPosition().y);
            player.skeleton.setScale(2, 2);

            //Bullet
            spellBallTexture.loadFromFile("Textures\\spellBall.png");
            spellBall.sprite.setTexture(spellBallTexture);
            spellBall.sprite.setScale(2, 2);

            //gate
            gateTexture.loadFromFile("Textures\\gate.png");
            gate.setTexture(gateTexture);
            gate.setScale(6, 6);


			//wall
            wallTexture.loadFromFile("Textures\\wall.png");
            wall.setTexture(wallTexture);
            wall.setPosition(sf::Vector2f(400, 400));
            wall.setScale(6, 6);

            groundTexture.loadFromFile("Textures\\ground.png");
            ground.setTexture(groundTexture);
            ground.setScale(6, 6);
            ground.setColor(sf::Color(50, 50, 50));

            //Chains
            chainTexture.loadFromFile("Textures\\chain.png");
            chain.setTexture(chainTexture);
            chain.setScale(4, 6);

            //Torch
            torchTexture.loadFromFile("Textures\\torch.png");
            torch.setTexture(torchTexture);
            torch.setScale(4, 4);

            //Skeleton
            skeletonTexture.loadFromFile("Textures\\skeleton.png");
            skeleton.setTexture(skeletonTexture);
            skeleton.setScale(6, 6);

            //Arrow
            arrowTexture.loadFromFile("Textures\\arrow.png");
            arrow.setTexture(arrowTexture);
            arrow.setScale(3, 3);

            infectedBoneTexture.loadFromFile("Textures\\infectedBone.png");
            infectedBone.setTexture(infectedBoneTexture);
            infectedBone.setScale(3, 3);

            infectedBones.push_back(infectedBone);

            gridSize = wall.getTexture()->getSize().x * wall.getScale().x;

            finsh.setFont(font);
            finsh.setString("You Finshed The Game :)");
            finsh.setFillColor(sf::Color::Green);
            finsh.setCharacterSize(32);
            finsh.setPosition(window.getSize().x / 2, window.getSize().y / 2);


            for (int y = 0; y < MAPHEIGHT; y++) {
                for (int x = 0; x < MAPWIDTH; x++) {
                    switch (map[y][x]) {
                    case '#':
                        wall.setPosition(sf::Vector2f(x * gridSize, y * gridSize));
                        walls.push_back(sf::Sprite(wall));
                        break;
                    case 'G':
                        gate.setPosition(sf::Vector2f(x * gridSize, y * gridSize));
                        walls.push_back(gate);

                    case 'P':
                        player.sprite.setPosition(x * gridSize, y * gridSize);
                        break;

                    case 'C':
                        chain.setPosition(x * gridSize, y * gridSize);
                        chains.push_back(sf::Sprite(chain));
                        break;

                    case 'S':
                        skeleton.setPosition(x * gridSize, y * gridSize);
                        skeletons.push_back(sf::Sprite(skeleton));
                        break;

                    default:
                        break;
                    }

                    ground.setPosition(x * gridSize, y * gridSize);
                    grounds.push_back(sf::Sprite(ground));
                }

            }

            skeleton.setPosition(window.getSize().x / 2, window.getSize().y - 100);

            player.maxKills = skeletons.size();

            title.setFont(font);
            start.setFont(font);
            exit.setFont(font);

            title.setCharacterSize(60);
            start.setCharacterSize(36);
            exit.setCharacterSize(36);

            title.setFillColor(sf::Color::White);
            start.setFillColor(sf::Color::White);
            exit.setFillColor(sf::Color::White);

            title.setPosition(window.getSize().x / 2 - 200, 200);
            start.setPosition(window.getSize().x / 2 - 50, title.getPosition().y + 100);
            exit.setPosition(start.getPosition().x, start.getPosition().y + 50);

            title.setString("DUNGEON MAN");
            start.setString("START");
            exit.setString("EXIT");

            exit.setFillColor(sf::Color(100, 100, 100, 255));
            start.setFillColor(sf::Color::White);
            arrow.setPosition(start.getPosition().x - 50, start.getPosition().y);
            menuButtonIndex = 1;

            Dungeonmusic.play();
            Dungeonmusic.setPlayingOffset(sf::seconds(9.f));
            Dungeonmusic.setLoop(true);
        }

        int Update(sf::RenderWindow& window) {

            srand(time(NULL));


            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        window.close();
                }

                dt = clock.restart().asSeconds();

                if (inMenu) {

                    if (menuRandPos < menuRandPosLimit)
                        menuRandPos += 30 * dt;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        exit.setFillColor(sf::Color(100, 100, 100, 255));

                        start.setFillColor(sf::Color::White);

                        arrow.setPosition(start.getPosition().x - 50, start.getPosition().y);
                        menuButtonIndex = 1;

                        if (menuRandPos >= menuRandPosLimit) {
                            skeleton.setPosition(rand() % window.getSize().x, rand() % window.getSize().y);
                            menuRandPos = 0.0f;
                        }
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        start.setFillColor(sf::Color(100, 100, 100, 255));

                        exit.setFillColor(sf::Color::White);

                        arrow.setPosition(exit.getPosition().x - 50, exit.getPosition().y);
                        menuButtonIndex = 2;

                        if (menuRandPos >= menuRandPosLimit) {
                            skeleton.setPosition(rand() % window.getSize().x, rand() % window.getSize().y);
                            menuRandPos = 0.0f;
                        }
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuButtonIndex == 1)
                        inMenu = false;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuButtonIndex == 2)
                        return -1;

                    window.setView(window.getDefaultView());
                    window.clear();
                    window.draw(skeleton);
                    window.draw(arrow);
                    window.draw(title);
                    window.draw(start);
                    window.draw(exit);
                    window.display();
                }



                if (!inMenu) {

                    if (player.swingKeyTime < player.swingTimeLimit)
                        player.swingKeyTime += 10 * dt;

                    mainView.setCenter(player.sprite.getPosition());

                    torch.setPosition(player.sprite.getPosition().x - 30, player.sprite.getPosition().y + player.sprite.getTexture()->getSize().y / 2 * player.sprite.getScale().y);

                    for (auto wall : walls)
                        player.Collision(player.sprite, wall, player.velocity);

                    for (int i = 0; i < walls.size(); i++) {
                        double distance = math.getDistance(player.sprite.getPosition(), walls[i].getPosition());
                        if (distance >= 300)
                            walls[i].setColor(sf::Color(100, 100, 100));
                        else
                            walls[i].setColor(sf::Color(255, 255, 255));
                    }

                    player.axe.setPosition(player.sprite.getPosition().x + player.sprite.getTexture()->getSize().x / 2 * player.sprite.getScale().x, player.sprite.getPosition().y + player.sprite.getTexture()->getSize().y / 2 * player.sprite.getScale().y - 40);

                    player.movement(player.velocity, 300, dt);

                    player.sprite.move(player.velocity);

                    player.velocity = sf::Vector2f(0, 0);

                    for (int i = 0; i < skeletons.size(); i++) {
                        if (player.axe.getGlobalBounds().intersects(skeletons[i].getGlobalBounds())) {
                            skeletons.erase(skeletons.begin() + i);
                            player.amountOfKills++;
                            break;
                        }
                    }

                    player.killsText.setString(std::to_string(player.amountOfKills));

                    if (player.amountOfKills == player.maxKills && player.sprite.getGlobalBounds().intersects(gate.getGlobalBounds())) {
                        finshGame = true;
                    }

                    window.setView(mainView);

                    window.clear();
                    
                    for (auto ground : grounds)
                        window.draw(ground);

                    for (auto wall : walls)
                        window.draw(wall);     

                    for (auto chain : chains)
                        window.draw(chain);

                    for (auto skeleton : skeletons)
                        window.draw(skeleton);

                    for (auto infectedBone : infectedBones)
                        window.draw(infectedBone);

                    for (auto spellBall : spellBalls)
                        window.draw(spellBall.sprite);

                    window.draw(player.sprite);
                    window.draw(player.axe);
                    window.draw(gate);

                    window.draw(torch);

                    window.setView(window.getDefaultView());

                    window.draw(player.killsText);
                    window.draw(player.skeleton);

                    window.display();
                }

                if (finshGame) {
                    window.draw(finsh);
                    sf::sleep(sf::milliseconds(2));
                    finshGame = false;
                    inMenu = true;
                    Start(window);
                    Update(window);
                }

            }

            return -1;
		}

        public: void Begin(sf::RenderWindow &window) {
            Start(window);
            Update(window);
        }
       
};