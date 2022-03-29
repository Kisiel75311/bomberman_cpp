//
// Created by Kisiel on 18.06.2020.
//

#include <iostream>
#include <cstring>
#include "Bomb.h"

Bomb::Bomb(Walls & w) : walls(w) {
    if ( ! bombTexture.loadFromFile("resrc/textures/Bomb_f01.png") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if ( ! flameTexture.loadFromFile("resrc/textures/Flame_f00.png") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if ( ! dropBombBuffer.loadFromFile("resrc/audio/drop_bomb_sound.wav") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    dropBombSound.setBuffer(dropBombBuffer);
    dropBombSound.setVolume(10);
}

void Bomb::dropBomb(sf::Vector2f pos, std::vector<BombStruct> &b) {
    if( b.size() < maximumBombAmount) {
        setBomb(b);
        b.back().bombSprite.setPosition(pos.x + 8, pos.y + 8);
        dropBombSound.play();
    }
}

void Bomb::drawBomb(sf::RenderWindow & win) {
    for(const auto & i : bomb1)
        win.draw(i.bombSprite);
    for(const auto & i : bomb2)
        win.draw(i.bombSprite);
    for(const auto & i : flame1)
        win.draw(i);
    for(const auto & i : flame2)
        win.draw(i);

}

void Bomb::explode(std::vector<BombStruct> &b, std::vector<sf::Sprite> &f) {
    if(!b.empty()) {
        setFlame(b,f);
        destroyWall(f);
    }
}

bool Bomb::isExplode(int n) {
    return bomb1.at(n).isExplode;
}

void Bomb::setBomb(std::vector<BombStruct> &b) {
    sf::Sprite tmpSprite;
    tmpSprite.setTexture(bombTexture);
    BombStruct tmp = {tmpSprite, false};
    b.push_back(tmp);
}

void Bomb::update() {
    for(const auto& i : bomb1){
        if(i.clk.getElapsedTime().asSeconds() > delay.asSeconds() )
        {
            explode(bomb1,flame1);
            if(i.clk.getElapsedTime().asSeconds() > delay.asSeconds() + 0.8)
            {
                deleteFlame(flame1);
                bomb1.erase(bomb1.begin());
            }
        }
    }
    for(const auto& i : bomb2) {
        if (i.clk.getElapsedTime().asSeconds() > delay.asSeconds())
        {
            explode(bomb2,flame2);
            if (i.clk.getElapsedTime().asSeconds() > delay.asSeconds() + 0.8)
            {
                deleteFlame(flame2);
                bomb2.erase(bomb2.begin());
            }
        }

    }
}

void Bomb::setFlame(std::vector<BombStruct> &b, std::vector<sf::Sprite> &f) {
    sf::Sprite tmpSprite;
    tmpSprite.setTexture(flameTexture);
    f.push_back(tmpSprite);
    f.back().setPosition(b.front().bombSprite.getPosition());
            for( int j = 1; j < b.back().flameRange; j++)
            {
                f.push_back(tmpSprite);
                f.back().setPosition(b.front().bombSprite.getPosition().x,b.front().bombSprite.getPosition().y+j*64);
                for(const auto & i : walls.getSolidWallSpriteArray()) {
                    if (f.back().getGlobalBounds().intersects(i.getGlobalBounds())) {
                        f.erase(f.end());
                    }
                }
                f.push_back(tmpSprite);
                f.back().setPosition(b.front().bombSprite.getPosition().x+j*64,b.front().bombSprite.getPosition().y);
                for(const auto & i : walls.getSolidWallSpriteArray()) {
                    if (f.back().getGlobalBounds().intersects(i.getGlobalBounds())) {
                        f.erase(f.end());
                    }
                }
                f.push_back(tmpSprite);
                f.back().setPosition(b.front().bombSprite.getPosition().x-j*64,b.front().bombSprite.getPosition().y);
                for(const auto & i : walls.getSolidWallSpriteArray()) {
                    if (f.back().getGlobalBounds().intersects(i.getGlobalBounds())) {
                        f.erase(f.end());
                    }
                }
                f.push_back(tmpSprite);
                f.back().setPosition(b.front().bombSprite.getPosition().x,b.front().bombSprite.getPosition().y-j*64);
                for(const auto & i : walls.getSolidWallSpriteArray()) {
                    if (f.back().getGlobalBounds().intersects(i.getGlobalBounds())) {
                        f.erase(f.end());
                    }
                }
            }
}

void Bomb::destroyWall(std::vector<sf::Sprite> &f) {
    for(auto & j : f)
    {
        for( size_t i = 0; i < walls.getWallSpriteArray().size(); i++ )
        {
            if(j.getGlobalBounds().intersects(walls.getWallSpriteArray().at(i).wallSprite.getGlobalBounds()))
            {
                walls.destroy(i);
            }
        }
    }

}

void Bomb::deleteFlame(std::vector<sf::Sprite> &f) {
    f.clear();
}

void Bomb::clearFlame() {
    flame1.clear();
    flame2.clear();
}




