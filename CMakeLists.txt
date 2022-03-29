cmake_minimum_required(VERSION 3.1)

project (Bomberman)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra)

if (UNIX)
    set ( CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
endif(UNIX)
if (WIN32)
    set( SFML_STATIC_LIBRARIES TRUE )
    set ( SFML_DIR "C:/Users/Kisiel/Documents/SFML/SFML-2.5.1/lib/cmake/SFML/")
endif(WIN32)


find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )



add_executable( Bomberman main.cpp engine/GameManager.cpp states/intro/IntroController.cpp states/options/OptionsController.cpp states/game/GameController.cpp states/game/GameController.h states/game/Background.cpp states/game/Background.h states/game/Player.cpp states/game/Player.h states/game/Walls.cpp states/game/Walls.h states/game/Bomb.cpp states/game/Bomb.h)



target_link_libraries(Bomberman sfml-system sfml-window sfml-graphics sfml-audio)







