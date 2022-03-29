
#ifndef ENGINE_GAMEMANAGER_H_
#define ENGINE_GAMEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStateController.h"
#include <memory>
#include <exception>

class GameStateException : public std::exception
{
	std::string missing;
public:
	explicit GameStateException(const std::string & id) : missing(id) {}
	const char* what() const noexcept { return missing.c_str(); }
};

class GameManager {
	sf::RenderWindow & window;

	std::map <std::string, std::shared_ptr<GameStateController> > stateMap;
	std::shared_ptr<GameStateController> currentStatePtr;


public:
	explicit GameManager(sf::RenderWindow & win );

	void changeState(const std::string & newState);



	void registerState(std::shared_ptr<GameStateController> state);
	void run();
};

#endif /* ENGINE_GAMEMANAGER_H_ */
