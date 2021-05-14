/**
 * @file 2048.cpp
 * @author Elijah Otter, Luke Hicks, Duane Crawford
 * @brief 
 * @version 0.1
 * @date 2021-05-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "game.h"

namespace settings
{
    /**
     * @brief Construct a new Game:: Game object
     * 
     * @param w 
     * @param h 
     */
    Game::Game(int w, int h)
    {
        blockSize = (w - GAME_MARGIN * 2 - BLOCK_MARGIN * (GAME_MARGIN - 1)) / GAME_WIDTH;
    }

    void Game::onEvent(sf::Event event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (animate)
            {
                return;
            }

        sf::Keyboard::Key key = event.key.code;
        //sets up movements to work with both arrows and keyboard
        if (key == sf::Keyboard::Left || key == sf::Keyboard::A)
        {
            move (-1, 0);
        }
        else if (key == sf::Keyboard::Right || key == sf::Keyboard::D)
        {
            move (1, 0);
        }
        else if (key == sf::Keyboard::Up || key == sf::Keyboard::W)
        {
            move (0, -1);
        }
        else if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
        {
            move (0, 1);
        }

        }
    }
    /**
     * @brief 
     * 
     */
    void Game::update()
    {
        if (animate)
        {
            if (clock.getElapsedTime().asSeconds() >= ANIMATION_TIME)
            {
                animate = false;

                for (int i = 0; i < moves.size(); i++)
                {
                    sf::Vector2i j = moves[i].first.first;
                    sf::Vector2i k = moves[i].first.second;

                    char val = moves[i].second;
                    char val2 = board[k.x][k.y];
                    board[j.x][j.y] = 0;

                    if (val == val2 && j != k)
                    {
                        board[k.x][k.y] = val + 1;
                    }
                    else 
                    {
                        board[k.x][k.y] = val + 1;
                    }
                }

                moves.clear();

                create();
                return;
            }
        }
    }

    /**
     * @brief 
     * 
     * @param target 
     */
    void Game::render(sf::RenderTarget& target)
    {
        sf::Text text;
        text.setFont(font);
        text.setStyle(sf::Text::Style::Bold);

        sf::RectangleShape block;
        block.setSize(sf::Vector2f(blockSize, blockSize));
        for (int i = 0; i < GAME_WIDTH; i++)
        {
            for (int j = 0; j < GAME_HEIGHT; j++)
            {
                block.setPosition(GAME_MARGIN + i * (blockSize + BLOCK_MARGIN),
                GAME_MARGIN + j * (blockSize + BLOCK_MARGIN));
                block.setFillColor(getBlockColor(board[i][j]));

                target.draw(block);

                if (board[i][j] != 0)
                {
                    text.setCharacterSize(getTextSize(board[i][j]));
                    text.setString(getText(board[i][j]));

                    sf::FloatRect rect = text.getLocalBounds();

                    text.setPosition(GAME_WIDTH + i * (blockSize + GAME_MARGIN)
                    + (blockSize - rect.width) / 2 - rect.left, 
                    GAME_MARGIN + j * (blockSize + GAME_MARGIN) + (blockSize - rect.height) / 2 - rect.top);
                    
                    block.setFillColor(getTextColor(board[i][j]));

                    target.draw(text);
                }
            }
        }

        sf::Vector2i gMargin (GAME_MARGIN, GAME_MARGIN);
        for (int i = 0; i < moves.size(); i++)
        {
            sf::Vector2i start = moves[i].first.first;
            sf::Vector2i m1 = gMargin + start * (blockSize + GAME_MARGIN);
            sf::Vector2i m2 = gMargin + moves[i].first.second * (blockSize + GAME_MARGIN);

            float move = (clock.getElapsedTime().asSeconds() / ANIMATION_TIME);
            sf::Vector2f position = sf::Vector2f(m1) + sf::Vector2f(m1 - m2) * move;

            text.setCharacterSize(getTextSize(moves[i].second));
            text.setString(getText(moves[i].second));

            sf::FloatRect rect = text.getLocalBounds();
            text.setPosition(position.x + (blockSize - rect.width) /  2 - rect.left,
            position.y + (blockSize - rect.height) / 2 - rect.top);
            text.setFillColor(getTextColor(moves[i].second));

            block.setPosition(position);
            block.setFillColor(getBlockColor(moves[i].second));

            target.draw(block);
            target.draw(text);
        }

    }

    /**
     * @brief 
     * 
     */
    void Game::create()
    {
        int count = 0;
        sf::Vector2i posMoves[GAME_WIDTH * GAME_HEIGHT];
        for (int i = 0; i < GAME_WIDTH; i++)
        {
            for (int j = 0; j < GAME_HEIGHT; j++)
            {
                if (board[i][j] == 0)
                {
                    posMoves[count] = sf::Vector2i(i, j);
                    count++;
                }
            }
        }

        if (count == 0)
        {
            reset();
            return;
        }
        
        sf::Vector2i position = posMoves[rand() % count];
        
        char newBlock = (rand() % 10) < 9 ? 1 : 2;
        //https://www.cplusplus.com/doc/tutorial/operators/
        //https://www.cplusplus.com/reference/cstdlib/rand/
        board[position.x][position.y] = newBlock;

    }

    /**
     * @brief 
     * 
     */
    void Game::reset()
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            for (int y = 0; y < GAME_HEIGHT; y++)
            {
                board[x][y] = 0;
            }
        }
        create();
    }

    sf::Color Game::getBlockColor(char block)
    {
        static const sf::Color colors[] = 
        {
            //cycles through the color combinations of the numbers
            sf::Color(238, 228, 218, 97), 
            sf::Color(238, 228, 218), // 2
			sf::Color(237, 224, 200), // 4
			sf::Color(242, 177, 121), // 8
			sf::Color(245, 149, 99), // 16
			sf::Color(246, 124, 95), // 32
			sf::Color(246, 94, 59),	 // 64
			sf::Color(237, 207, 114), // 128
			sf::Color(237, 204, 97), // 256
			sf::Color(237, 200, 80), // 512
			sf::Color(237, 197, 63), // 1024
			sf::Color(237, 194, 46), // 2048
        };
        return colors[block];
    }

    /**
     * @brief 
     * 
     * @param block 
     * @return sf::Color 
     */
    //color changes on different number 
    sf::Color Game::getTextColor(char block)
    {
        if (block >= 3) //value of block is >= 8
        {
            return sf::Color(249, 246, 242);
        }

        return sf::Color(119, 110, 101);
    }

    std::string Game::getText(char block)
    {
        static const std::string text[] = { "", "2", "4", "8", "16",
        "32", "64", "128", "256", "512", "1024", "2048"};

        return text[block];
    }

    /**
     * @brief 
     * 
     * @param block 
     * @return int 
     */
    int Game::getTextSize(char block)
    {
        if (block >= 10)
        {
            return 35;
        }
        else if (block >= 7)
        {
            return 45;
        }
        else 
        {
            return 55;
        }
    }
    //copies the board
    void Game::move(char direction1, char direction2)
    {
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            for (int y = 0; y < GAME_HEIGHT; y++)
            {
                board2[x][y] = board[x][y];
            }
        }
        //goes throug hypothetical move scenarios
        if (direction1 == -1)
        {
            for (int x = 1; x < GAME_WIDTH; x++)
            {
                for (int y = 0; y < GAME_HEIGHT; y++)
                {
                    if (board2[x][y] == 0)
                    {
                        continue;
                    }
                    sf::Vector2i position = sf::Vector2i(x, y);

                    for (int i = (x - 1); i >= 0; i--)
                    {
                        position = sf::Vector2i(i, y);

                        if (board2[i][y] != 0)
                        {
                            break;
                        }

                        makeMove(sf::Vector2i(x, y), position, direction1, direction2);

                    }
                }
            }
        }
        else if (direction1 == 1)
        {
            for (int x = (GAME_WIDTH - 2); x >= 0; x--)
            {
                for (int y = 0; y < GAME_HEIGHT; y++)
                {
                    if (board2[x][y] == 0)
                    {
                        continue;
                    }

                    sf::Vector2i position = sf::Vector2i(x, y);

                    for (int i = (x + 1); i < GAME_HEIGHT; i++)
                    {
                        position = sf::Vector2i(i, y);
                        if (board2[i][y] != 0)
                        {
                            break;
                        }
                    }

                    makeMove(sf::Vector2i(x, y), position, direction1, direction2);
                }
            }
        }
        else if (direction2 == -1)
        {
            for (int y = 1; y < GAME_HEIGHT; y++)
            {
                for (int x = 0; x < GAME_WIDTH; x++)
                {
                    if (board2[x][y] == 0)
                    {
                        continue;
                    }

                    sf::Vector2i position = sf::Vector2i(x, y);

                    for (int i = (y - 1); i >= 0; i--)
                    {
                        position = sf::Vector2i(x, i);

                        if (board2[x][i] != 0)
                        {
                            break;
                        }
                    }

                    makeMove(sf::Vector2i(x, y), position, direction1, direction2);
                }
            }
        }
        else if (direction2 == 1)
        {
            for (int y = (GAME_HEIGHT - 2); y >= 0; y--)
            {
                for (int x = 0; x < GAME_WIDTH; x++)
                {
                    if (board2[x][y] == 0)
                    {
                        continue;
                    }

                    sf::Vector2i position = sf::Vector2i(x, y);

                    for (int i = (y + 1); i < GAME_HEIGHT; i++)
                    {
                        position = sf::Vector2i(x, i);

                        if (board2[x][i] != 0)
                        {
                            break;
                        }
                    }

                    makeMove(sf::Vector2i(x, y), position, direction1, direction2);
                }
            }
        }

        bool boardFilled = true;
        bool gameOver = true;
        for (int x = 0; x < GAME_WIDTH; x++)
        {
            for (int y = 0; y < GAME_HEIGHT; y++)
            {
                if (board2[x][y] == 0)
                {
                    boardFilled = false;
                    gameOver = false;
                    break;
                }

                char val = board2[x][y];

                if (x != 0 && board2[x - 1][y] == val)
                {
                    gameOver = false;
                }
                else if (y != 0 && board2[x][y - 1] == val)
                {
                    gameOver = false;
                }
                else if (x != GAME_WIDTH - 1 && board2[x + 1][y] ==val)
                {
                    gameOver = false;
                }
                else if (y != GAME_WIDTH - 1 && board2[x][y + 1] == val)
                {
                    gameOver = false;
                }
            }

            if (!boardFilled || !gameOver)
            {
                break;
            }
        }

        if (gameOver)
        {
            reset();
        }
        
    }

    /**
     * @brief 
     * 
     * @param f 
     * @param t 
     * @param d1 
     * @param d2 
     */
    void Game::makeMove(sf::Vector2i f, sf::Vector2i t, int d1, int d2)
    {
        char val = board2[f.x][f.y];
        char val2 = board2[t.x][t.y];
        board2[f.x][f.y] = 0;

        if (val2 == val)
        {
            board2[t.x][t.y] = val + 1;
            if (val + 1 == 12)
            {
                reset();
            }
        }
        else 
        {
            board2[t.x - (d1 * (val2 != 0))][t.y - (d2 * (val2 != 0))] = val;
        }

        sf::Vector2i from = f, to;

        if (val2 == val)
        {
            to = t;
        }
        else 
        {
            to = sf::Vector2i(t.x - (d1 * (val2 != 0)), t.y - (d2 * (d2 != 0)));
        }

        if (from != to)
        {
            board[f.x][f.y] = 0;

            moves.push_back(std::make_pair(std::make_pair(from, to), val));

            animate = true;
            clock.restart();
        }
    }
}
