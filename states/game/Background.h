

#ifndef BOMBERMAN_BACKGROUND_H
#define BOMBERMAN_BACKGROUND_H

#include "engine/GameStateController.h"


class Background {
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Music gameMusic;
float volume;
public:
    Background();

    void setBackground();

    virtual void draw(sf::RenderWindow & win);

    void setVolume(float v);

    void pauseMusic(){gameMusic.pause();}
    void playMusic(){gameMusic.play();}
};


#endif //BOMBERMAN_BACKGROUND_H
