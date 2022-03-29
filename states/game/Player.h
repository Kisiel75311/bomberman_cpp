
#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include "engine/GameStateController.h"

#include "Walls.h"
#include "Bomb.h"


class Walls;
class Bomb;

class Player {
    Walls &walls;
    Bomb &bomb;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    float speed = 64.f;
    sf::Vector2f position;
    sf::Color playerColor;
    sf::SoundBuffer deathBuffer;
    sf::Sound deathSound;
    bool alive = true;
    sf::Font font;
    sf::Text text;
public:
    Player(Walls & walls, Bomb & bomb, sf::Vector2f position, sf::Color playerColor);

    void setPlayers();
    void updatePlayer();

    bool isAlive() const;

    void player1Inputer ( const sf::Event & event );
    void player2Inputer ( const sf::Event & event ) ;

    bool collision();
    bool flameCollision();

    void moveUp(){playerSprite.move(0.f,-speed);}
    void moveDown(){playerSprite.move(0.f,speed);}
    void moveRight(){playerSprite.move(speed,0.f);}
    void moveLeft(){playerSprite.move(-speed,0.f);}
    void draw(sf::RenderWindow & win);

    void winner(const std::string& winner, sf::Color color);



};


#endif //BOMBERMAN_PLAYER_H
