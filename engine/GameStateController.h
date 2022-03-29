
#ifndef ENGINE_GAMESTATECONTROLLER_H_
#define ENGINE_GAMESTATECONTROLLER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameStateController
{
	const std::string myStateID;
public:
	explicit GameStateController(const std::string & stateId) : myStateID(stateId) {}

	std::string getStateID() const { return myStateID; }


    virtual std::string getNextState() const = 0;
    virtual void handleEvent ( const sf::Event & event ) = 0;
    virtual void updateModel() = 0;
    virtual void draw(sf::RenderWindow & win) = 0;

    virtual void onEnter(const std::string & data) = 0;
    virtual std::string onExit() = 0;
};



#endif /* ENGINE_GAMESTATECONTROLLER_H_ */
