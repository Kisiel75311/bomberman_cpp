
#ifndef STATES_INTRO_INTROCONTROLLER_H_
#define STATES_INTRO_INTROCONTROLLER_H_

#include "engine/GameStateController.h"

class IntroController : public GameStateController
{
	std::string nextState;
    sf::Texture introBackgroundTexture;
    sf::Sprite introBackgroundSprite;
    sf::Texture titleTexture;
    sf::Sprite titleSprite;
    int selectedOption;
    sf::Font font;
    std::vector<sf::Text> intro;
    sf::Music gameMusic;
    float volume;
    std::string Data;

public:
	IntroController();
	virtual ~IntroController();
    virtual void onEnter(const std::string & data) ;
    virtual std::string onExit() ;

	virtual std::string getNextState() const;
    virtual void handleEvent ( const sf::Event & event ) ;
    virtual void updateModel() ;
    virtual void draw(sf::RenderWindow & win) ;

    void setIntro();
    void Up();
    void Down();
    int getSelectedOption() const;

    void setVolume(float v);

    void pauseMusic(){gameMusic.pause();}
    void playMusic(){gameMusic.play();}
};

#endif
