#ifndef GAME_H
#define GAME_H

#pragma once
//https://riptutorial.com/cplusplus/example/16851/sharppragma-once
#include "settings.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <deque>
#include <unordered_map>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

namespace settings
{
    class Game
    {
    public:
        Game(int w, int h);
        void onEvent(sf::Event event);
        void render(sf::RenderTarget& target);
        void update();
        void create(); // creates a new block
        void reset();

    private:
        int blockSize;
        char board[GAME_WIDTH][GAME_HEIGHT] = {0};
        char board2[GAME_WIDTH][GAME_HEIGHT] = {0};
        sf::Clock clock;
        bool animate;
        sf::Font font;
        std::vector<std::pair<std::pair<sf::Vector2i, sf::Vector2i>, char>> moves;
        //https://www.cplusplus.com/reference/utility/pair/pair/
        //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php

        sf::Color getBlockColor(char block);
        sf::Color getTextColor(char block);
        std::string getText(char block);
        int getTextSize(char block);
        void move(char direction1, char direction2);
        void makeMove(sf::Vector2i from, sf::Vector2i to, int d1, int d2);
    };
}

#endif
