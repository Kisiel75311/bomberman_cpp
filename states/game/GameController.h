
#ifndef BOMBERMAN_GAMECONTROLLER_H
#define BOMBERMAN_GAMECONTROLLER_H

#include <SFML/Audio.hpp>

#include "engine/GameStateController.h"
#include "Background.h"
#include "Player.h"
#include "Walls.h"
#include "Bomb.h"

class GameController : public GameStateController{
    std::string nextState;
    Background & background;
    Player & player1;
    Player & player2;
    Walls & walls;
    Bomb & bomb;
    sf::Clock clk;
    std::string Data;

public:
    GameController(Background & background, Player & player1, Player & player2, Walls & walls, Bomb & bomb);
    virtual ~GameController();
    virtual void onEnter(const std::string & data) ;
    virtual std::string onExit() ;

    virtual std::string getNextState() const;
    virtual void handleEvent ( const sf::Event & event ) ;
    virtual void updateModel() ;
    virtual void draw(sf::RenderWindow & win) ;


};


#endif //BOMBERMAN_GAMECONTROLLER_H
