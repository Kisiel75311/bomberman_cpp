
#include "OptionsController.h"
#include <sstream>
#include <cstring>
#include <iostream>

OptionsController::OptionsController() : GameStateController("OPTIONS")
{

    if ( ! optionsBackgroundTexture.loadFromFile("resrc/textures/background.jpg") )
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
	nextState = this->getStateID();

    setOptions();

}

void OptionsController::onEnter(const std::string & data) {
	nextState = this->getStateID();

}

std::string OptionsController::onExit() {
	std::stringstream ss;
	//ss << "OPTIONS ";
    for (int option : options)
    {
    	ss << option << " ";
    }
	return ss.str();
}

OptionsController::~OptionsController() {
	// TODO Auto-generated destructor stub
}

void OptionsController::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			nextState = "GAME";
		}
        if (event.key.code == sf::Keyboard::Enter)
        {
            nextState = "INTRO";
        }

	    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
		{
			currentOption -= 1;
			if (currentOption < 0)
				currentOption = options.size() - 1;
		}
		if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
		{
			currentOption += 1;
			if (currentOption >= options.size())
				currentOption = 0;
		}

		if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
		{
			options[currentOption] -= 1;
			if(options[currentOption] <= 0)
			    options[currentOption] = 0;
		}
		if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
		{
			options[currentOption] += 1;
            if(options[currentOption] >= 10)
                options[currentOption] = 10;
		}
	}
}

void OptionsController::updateModel() {
}

void OptionsController::draw(sf::RenderWindow &win)
{
    win.draw(optionsBackgroundSprite);
    for(const auto& i : menu)
        win.draw(i);
    sf::RectangleShape r(sf::Vector2f(5, 20));

    for (size_t i=0; i<options.size(); ++i)
    {
        for (int pos = 0; pos < options[i]; ++pos)
        {
            r.setFillColor(colors[i]);
            r.setPosition(200 + 10*pos,200 + 30*i);
            win.draw(r);
        }
    }

    sf::CircleShape c(10, 3);
    c.rotate(90);
    c.setPosition(90, 200+30*currentOption);
    win.draw(c);
}

std::string OptionsController::getNextState() const
{
	return nextState;
}

void OptionsController::setOptions() {
    optionsBackgroundSprite.setTexture(optionsBackgroundTexture);
    optionsBackgroundSprite.setPosition(sf::Vector2f(0, 0));

    options.resize(1,10);
    currentOption = 0;

    colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta};

    sf::Text tmp;
    tmp.setFont(font);
    tmp.setCharacterSize(40);

    menu.push_back(tmp);
    menu.back().setFillColor(sf::Color::Red);
    menu.back().setString("Press 'ENTER' to back");
    menu.back().setPosition(120, 300  );

    menu.push_back(tmp);
    menu.back().setCharacterSize(25);
    menu.back().setFillColor(colors[0]);
    menu.back().setString("Volume");
    menu.back().setPosition(110, 195);

}


