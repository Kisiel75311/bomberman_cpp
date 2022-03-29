

#include <cstring>
#include <iostream>
#include "Background.h"

Background::Background() {
    if ( ! backgroundTexture.loadFromFile("resrc/textures/BackgroundTile.png") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if ( ! gameMusic.openFromFile("resrc/audio/game_music.ogg") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }


    setBackground();
}

void Background::setBackground() {
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.f, 0.f);

}


void Background::draw(sf::RenderWindow &win) {
    win.draw(backgroundSprite);
}

void Background::setVolume(float v) {
    Background::volume = v;
    gameMusic.setVolume(v);
    gameMusic.setLoop(true);
}


