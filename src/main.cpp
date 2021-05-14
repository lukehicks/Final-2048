/**
 * @file main.cpp
 * @author Elijah Otter, Luke Hicks, Duane Crawford
 * @brief 
 * @version 0.1
 * @date 2021-05-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(600, 600), "2048", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;

    window.setKeyRepeatEnabled(false);

    settings::Game game(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            game.onEvent(event);
        }

        game.update();
        
        window.clear(sf::Color(187, 173, 160));
        game.render(window);
        window.display();
    }

    return 0;

}