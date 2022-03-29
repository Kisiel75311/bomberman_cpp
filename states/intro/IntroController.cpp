
#include "IntroController.h"
#include <iostream>
#include <sstream>
#include <cstring>

IntroController::IntroController() : GameStateController("INTRO")
{
    if ( ! introBackgroundTexture.loadFromFile("resrc/textures/background.jpg") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if ( ! titleTexture.loadFromFile("resrc/textures/title.png") )
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
    if ( ! gameMusic.openFromFile("resrc/audio/intro_music.ogg") )
    {
        //PROBLEM!!!
        std::cerr << strerror(errno) << std::endl;
        abort();
    }

    setIntro();
	nextState = this->getStateID();
}

void IntroController::onEnter(const std::string & data) {
    std::cout << data << std::endl;
    setVolume(10);
    if(!data.empty())
    {
        float f1 = std::stof(data);
        setVolume(f1);
        Data = data;
    }
    playMusic();

	nextState = this->getStateID();
}

std::string IntroController::onExit() {
    pauseMusic();
	return Data;
}

IntroController::~IntroController() {
	// TODO Auto-generated destructor stub
}

void IntroController::handleEvent(const sf::Event &event)
{

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
            Up();
        }
        if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S){
            Down();
        }
        if(event.key.code == sf::Keyboard::Enter){
            if(getSelectedOption() == 0){
                nextState = "GAME";
            }
            if(getSelectedOption() == 1) {
                nextState = "OPTIONS";
            }
            if(getSelectedOption() == 2) {
                exit(0);
            }
        }
    }
}

void IntroController::updateModel()
{
}

void IntroController::draw(sf::RenderWindow &win)
{
    win.draw(introBackgroundSprite);
    win.draw(titleSprite);
    for(const auto & i : intro)
    {
        win.draw(i);
    }
}

std::string IntroController::getNextState() const
{
	return nextState;
}

void IntroController::setIntro() {
    introBackgroundSprite.setTexture(introBackgroundTexture);
    introBackgroundSprite.setPosition(sf::Vector2f(0, 0));
    titleSprite.setTexture(titleTexture);
    titleSprite.setPosition(130,-59);

    sf::Text tmp;
    tmp.setFont(font);
    tmp.setCharacterSize(60);
    intro.push_back(tmp);
    intro.back().setFillColor(sf::Color::Red);
    intro.back().setString("PLAY");
    intro.back().setPosition(420, 300  );

    intro.push_back(tmp);
    intro.back().setFillColor(sf::Color::White);
    intro.back().setString("OPTIONS");
    intro.back().setPosition(420, 380 );

    intro.push_back(tmp);
    intro.back().setFillColor(sf::Color::White);
    intro.back().setString("EXIT");
    intro.back().setPosition(420, 460 );

    selectedOption = 0;
}

void IntroController::Up() {
    if( selectedOption - 1 >= 0)
    {
        intro[selectedOption].setFillColor(sf::Color::White);
        selectedOption--;
        intro[selectedOption].setFillColor(sf::Color::Red);
    }
}

void IntroController::Down() {
    if( selectedOption + 1 < intro.size())
    {
        intro[selectedOption].setFillColor(sf::Color::White);
        selectedOption++;
        intro[selectedOption].setFillColor(sf::Color::Red);
    }
}

int IntroController::getSelectedOption() const {
    return selectedOption;
}

void IntroController::setVolume(float v) {
    IntroController::volume = v;
    gameMusic.setVolume(v);
    gameMusic.setLoop(true);
}

