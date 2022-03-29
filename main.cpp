#include <SFML/Graphics.hpp>
#include "engine/GameManager.h"

#include "states/intro/IntroController.h"
#include "states/options/OptionsController.h"
#include "states/game/GameController.h"
#include "states/game/Player.h"
#include "states/game/Bomb.h"


#include <memory>
#include <ctime>



int main()
{
    srand( time( NULL ) );
	sf::RenderWindow win (sf::VideoMode(960, 832), "Bomberman");
    win.setFramerateLimit(120);
    Background bg;

    Walls w;
    Bomb b(w);
    Player p1(w,b,{64.f,64.f}, sf::Color(180, 180, 255));
    Player p2(w,b, {832.f, 704.f}, sf::Color(255, 180, 180));

	GameManager mgr(win);

	mgr.registerState ( std::make_shared<IntroController>() );
	mgr.registerState ( std::make_shared<OptionsController>() );
    mgr.registerState ( std::make_shared<GameController>(bg, p1, p2, w, b) );

	mgr.changeState("INTRO");
	mgr.run();
}
