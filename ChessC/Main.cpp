#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include <utility>
#include "GamePlay.h"
#include "ChessBoard.h"
#include "ChessBoardView.h"
#include "ChessBoardViewSFML.h"
#include "ChessPiece.h"
#include "ChessPieceView.h"
#include "Player.h"


int main()
{
    std::shared_ptr<sf::RenderWindow> pWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 1024), "Chess Game");
    ChessBoardViewSFML graphics(pWindow, "images/figures.png");

    GamePlay game;

    while (pWindow->isOpen())
    {
        sf::Event event;
        while (pWindow->pollEvent(event))
        {
            if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased)
            {
                graphics.ClickProcess(sf::Vector2i{ event.mouseButton.x, event.mouseButton.y }, game);
            }

            if (event.type == sf::Event::Closed)
                pWindow->close();
        }

        pWindow->clear();

        graphics.DrawFrame(game);

        pWindow->display();
    }
}