
#include <iostream>
#include <cstring>
#include "GameController.h"

GameController::GameController(Background &bg, Player &p1, Player &p2, Walls & w, Bomb & b) :  GameStateController("GAME"), background(bg), player1(p1), player2(p2), walls(w), bomb(b)
{
    nextState = this->getStateID();

}

void GameController::onEnter(const std::string &data) {
    std::cout << data << std::endl;
    background.setVolume(10);
    if(!data.empty())
    {
        float f1 = std::stof(data);
        background.setVolume(f1);
    }
    background.playMusic();
    nextState = this->getStateID();
    player1.setPlayers();
    player2.setPlayers();
    walls.setExplodableWalls();
    walls.setSolidWalls();
}

std::string GameController::onExit() {
    walls.clearWalls();
    bomb.clearFlame();
    background.pauseMusic();
    return Data;
}

std::string GameController::getNextState() const {
    return nextState;
}

void GameController::handleEvent(const sf::Event &event) {

        player1.player1Inputer(event);
        player2.player2Inputer(event);

}

void GameController::updateModel() {

    float elapsed=clk.getElapsedTime().asSeconds();
    int tmp = static_cast<int>(elapsed);
    player1.updatePlayer();
    player2.updatePlayer();
    bomb.update();
    if(!player1.isAlive())
    {

        player2.winner("Player 2 WON!",{179, 0, 0});
        if(tmp % 4 == 1)
            nextState = "INTRO";
    }
    if(!player2.isAlive())
    {
        player1.winner("Player 1 WON!", {0, 0, 179});
        if(tmp % 4 == 1)
            nextState = "INTRO";
    }


}

void GameController::draw(sf::RenderWindow &win) {
    background.draw(win);
    walls.draw(win);
    player1.draw(win);
    player2.draw(win);
    bomb.drawBomb(win);


}



GameController::~GameController() {

}




