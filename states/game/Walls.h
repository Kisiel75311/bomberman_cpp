
#ifndef BOMBERMAN_WALLS_H
#define BOMBERMAN_WALLS_H

#include <fstream>

#include "engine/GameStateController.h"

struct Wall
{
    int id;
    sf::Sprite wallSprite;
};

class Walls {
    std::ifstream solidWallPositions;
    std::vector<sf::Vector2f> solidWallPos;
    std::vector<sf::Vector2f> wallPos;
    sf::Texture solidWallTexture;
    sf::Texture wallTexture;
    std::vector<sf::Sprite> solidWallSpriteArray;
    std::vector<Wall> wallSpriteArray;
public:
    Walls();

    void setSolidWalls();
    void setExplodableWalls();
    void destroy(int n);

    const std::vector<sf::Sprite> &getSolidWallSpriteArray() const;

    const std::vector<Wall> &getWallSpriteArray() const;

    void draw(sf::RenderWindow & win);

    void clearWalls();

};


#endif //BOMBERMAN_WALLS_H
