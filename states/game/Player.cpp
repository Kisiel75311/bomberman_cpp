
#include <cstring>
#include <iostream>
#include "Player.h"

Player::Player(Walls &w, Bomb &b, sf::Vector2f p, sf::Color c): walls(w),bomb(b), position(p), playerColor(c) {
    if ( ! playerTexture.loadFromFile("resrc/textures/Bman_F_f00.png") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if ( ! deathBuffer.loadFromFile("resrc/audio/death_sound.wav") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if ( ! font.loadFromFile("resrc/fonts/BigSpace-rPKx.ttf") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    text.setFont(font);
    deathSound.setBuffer(deathBuffer);
    deathSound.setVolume(10);
    setPlayers();

}

void Player::setPlayers() {
    playerSprite.setPosition(position);
    playerSprite.setColor(playerColor);
    playerSprite.setTexture(playerTexture);
    alive=true;
    text.setString(" ");
}



void Player::updatePlayer() {
    if(flameCollision()){
        alive = false;
    }
}

void Player::player1Inputer(const sf::Event &event) {
    if(!alive)
        return;
    if (event.type == sf::Event::KeyReleased) {

        if (event.key.code == sf::Keyboard::W) {
            moveUp();
            if (collision()) {
                moveDown();
            }
        }
        if (event.key.code == sf::Keyboard::S) {
            moveDown();
            if (collision()) {
                moveUp();
            }
        }
        if (event.key.code == sf::Keyboard::A) {
            moveLeft();
            if (collision()) {
                moveRight();
            }
        }
        if (event.key.code == sf::Keyboard::D) {
            moveRight();
            if (collision()) {
                moveLeft();
            }
        }

        if (event.key.code == sf::Keyboard::Space) {
            bomb.dropBomb(playerSprite.getPosition(), bomb.bomb1);
        }
    }

}

void Player::player2Inputer(const sf::Event &event) {
    if(!alive)
        return;
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up) {
            moveUp();
            if (collision()) {
                moveDown();
            }
        }
        if (event.key.code == sf::Keyboard::Down) {
            moveDown();
            if (collision()) {
                moveUp();
            }
        }
        if (event.key.code == sf::Keyboard::Left) {
            moveLeft();
            if (collision()) {
                moveRight();
            }
        }
        if (event.key.code == sf::Keyboard::Right) {
            moveRight();
            if (collision()) {
                moveLeft();
            }
        }

        if (event.key.code == sf::Keyboard::Numpad0) {
            bomb.dropBomb(playerSprite.getPosition(), bomb.bomb2);
        }
    }
}

bool Player::collision() {
    for(const auto & i : walls.getSolidWallSpriteArray()){
        if(playerSprite.getGlobalBounds().intersects(i.getGlobalBounds())){
            std::cout << "Collision" << std::endl;
            return true;
        }
    }
    for(const auto & i : walls.getWallSpriteArray()){
        if(playerSprite.getGlobalBounds().intersects(i.wallSprite.getGlobalBounds())){
            std::cout << "Collision" << std::endl;
            return true;
        }
    }
    return false;
}

void Player::draw(sf::RenderWindow &win) {
    win.draw(playerSprite);
    win.draw(text);
}

bool Player::flameCollision() {
    for(const auto & i : bomb.flame1){
        if(playerSprite.getGlobalBounds().intersects(i.getGlobalBounds())){
            deathSound.play();
            return true;
        }
    }
    for(const auto & i : bomb.flame2){
        if(playerSprite.getGlobalBounds().intersects(i.getGlobalBounds())){
            deathSound.play();
            return true;
        }
    }
    return false;
}

bool Player::isAlive() const {
    return alive;
}

void Player::winner(const std::string &winner, sf::Color color) {
    text.setCharacterSize(80);
    text.setFillColor(color);
    text.setPosition(280.f, 300.f);
    text.setString(winner);
}




