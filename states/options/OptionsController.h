

#ifndef STATES_OPTIONS_OPTIONSCONTROLLER_H_
#define STATES_OPTIONS_OPTIONSCONTROLLER_H_

#include <string>
#include <SFML/Graphics.hpp>
#include "engine/GameStateController.h"

class OptionsController : public GameStateController
{
	std::string nextState;
    sf::Texture optionsBackgroundTexture;
    sf::Sprite optionsBackgroundSprite;

    std::vector<int> options;
    int currentOption;
    std::vector<sf::Color> colors;

    sf::Font font;
    std::vector<sf::Text> menu;

public:
	OptionsController();
	virtual ~OptionsController();
    virtual void onEnter(const std::string & data) ;
    virtual std::string onExit() ;

	virtual std::string getNextState() const;
    virtual void handleEvent ( const sf::Event & event ) ;
    virtual void updateModel() ;
    virtual void draw(sf::RenderWindow & win) ;

    void setOptions();

};

#endif /* STATES_OPTIONS_OPTIONSCONTROLLER_H_ */
