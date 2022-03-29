
#include <iostream>
#include <cstring>
#include "Walls.h"

Walls::Walls() {
    if ( ! solidWallTexture.loadFromFile("resrc/textures/SolidBlock.png") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if ( ! wallTexture.loadFromFile("resrc/textures/ExplodableBlock.png") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    solidWallSpriteArray.resize(82);
    solidWallPos.resize(82);
    //wallSpriteArray.resize(56);

    solidWallPositions.open("config/solidWallPositions.txt");
    if(solidWallPositions.is_open())
    {
        float x,y;
        for (size_t i = 0; i < solidWallSpriteArray.size(); i++ )
        {
            solidWallPositions >> x;
            solidWallPositions >> y;

            solidWallPos.at(i) = {x*64, y*64};
        }
        solidWallPositions.close();
    }
    setSolidWalls();
    setExplodableWalls();
}

void Walls::setSolidWalls() {
    for(size_t i = 0; i < solidWallSpriteArray.size(); i++){
        solidWallSpriteArray.at(i).setTexture(solidWallTexture);
        solidWallSpriteArray.at(i).setPosition(solidWallPos.at(i));
    }

}

const std::vector<sf::Sprite> &Walls::getSolidWallSpriteArray() const {
    return solidWallSpriteArray;
}

void Walls::draw(sf::RenderWindow &win) {
    for(const auto & i : solidWallSpriteArray)
        win.draw(i);
    for(const auto & i : wallSpriteArray)
        win.draw(i.wallSprite);
}

void Walls::setExplodableWalls() {
    float x,y;
    sf::Vector2f tmpVec;
    int tmp = 1;
    sf::Sprite tmpSprite;
    tmpSprite.setTexture(wallTexture);


    while (wallPos.size() < 70)
    {
        x=static_cast<float>(rand() % 13+1)*64;
        y=static_cast<float>(rand() % 11+1)*64;
        tmpVec.x = x;
        tmpVec.y = y;
        auto resault1 = std::find(std::begin(solidWallPos), std::end(solidWallPos), tmpVec);
        auto resault2 = std::find(std::begin(wallPos), std::end(wallPos), tmpVec);
        if( resault1 != std::end(solidWallPos))
        {
            continue;
        }
        if( resault2 != std::end(wallPos))
        {
            continue;
        }
        if( (tmpVec.x == 64.f && tmpVec.y == 64.f) || (tmpVec.x == 64.f && tmpVec.y == 128.f) ||
            (tmpVec.x == 128.f && tmpVec.y == 64.f) || (tmpVec.x == 832.f && tmpVec.y == 704.f) ||
            (tmpVec.x == 768.f && tmpVec.y == 704.f) || (tmpVec.x == 832.f && tmpVec.y == 640.f)  )
        {
            continue;
        }
        wallPos.emplace_back(tmpVec);
        wallSpriteArray.push_back({tmp, tmpSprite});
        wallSpriteArray.back().wallSprite.setPosition(wallPos.back());
        tmp++;
    }
}



void Walls::destroy(int n) {
    if(!wallSpriteArray.empty())
    {
        wallSpriteArray.erase(wallSpriteArray.begin()+n);
    }
}

const std::vector<Wall> &Walls::getWallSpriteArray() const {
    return wallSpriteArray;
}

void Walls::clearWalls() {
    wallPos.clear();
    wallSpriteArray.clear();
}
