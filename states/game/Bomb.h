//
// Created by Kisiel on 18.06.2020.
//

#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H

#include "engine/GameStateController.h"
#include "Player.h"
#include "Walls.h"

struct BombStruct {
    sf::Sprite bombSprite;
    bool isExplode;
    std::vector<sf::Sprite> flame;
    sf::Clock clk;
    int flameRange = 2;

};

struct FlameStruct{

};

class Bomb{
    Walls & walls;

    sf::Texture bombTexture;
    sf::Texture flameTexture;
    unsigned int maximumBombAmount = 2;
    sf::Time delay=sf::seconds(2.f);
    sf::SoundBuffer dropBombBuffer;
    sf::Sound dropBombSound;

public:
    std::vector<BombStruct> bomb1;
    std::vector<BombStruct> bomb2;
    std::vector<sf::Sprite> flame1;
    std::vector<sf::Sprite> flame2;

    explicit Bomb(Walls & walls);

    void dropBomb(sf::Vector2f pos, std::vector<BombStruct> &b);
    void drawBomb(sf::RenderWindow & win);
    void explode(std::vector<BombStruct> &b, std::vector<sf::Sprite> &f);
    void setBomb(std::vector<BombStruct> &b);
    void setFlame(std::vector<BombStruct> &b, std::vector<sf::Sprite> &f);
    static void deleteFlame(std::vector<sf::Sprite> &f);
    void update();
    void clearFlame();

    void destroyWall(std::vector<sf::Sprite> &f);
    bool isExplode(int n);
};


#endif //BOMBERMAN_BOMB_H
