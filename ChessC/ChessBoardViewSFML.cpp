#include "ChessBoardViewSFML.h"

ChessBoardViewSFML::ChessBoardViewSFML(std::shared_ptr<sf::RenderWindow> window, const std::string& textureLink)
{
	mWindow = window;
	mTextureOfChessPieces.loadFromFile(textureLink);

    mRectangleChoicedPieceOutline.setSize(sf::Vector2f(cTileSize, cTileSize));
    mRectangleChoicedPieceOutline.setOutlineColor(sf::Color::Red);
    mRectangleChoicedPieceOutline.setOutlineThickness(5);
    mRectangleChoicedPieceOutline.setFillColor(sf::Color(0, 0, 0, 0));
    mRectangleChoicedPieceOutline.setPosition(-250, -250);

    mRectangleAvailableMoveFill.setSize(sf::Vector2f(cTileSize, cTileSize));
    mRectangleAvailableMoveFill.setFillColor(sf::Color(255, 255, 0, 128));
    mRectangleAvailableMoveFill.setPosition(-250, -250);

    mRectangleWhiteTileOfBoard.setSize(sf::Vector2f(cTileSize, cTileSize));
    mRectangleWhiteTileOfBoard.setFillColor(sf::Color(255, 128, 128, 255));
    mRectangleWhiteTileOfBoard.setPosition(-250, -250);

    mRectangleBlackTileOfBoard.setSize(sf::Vector2f(cTileSize, cTileSize));
    mRectangleBlackTileOfBoard.setFillColor(sf::Color(64, 32, 32, 255));
    mRectangleBlackTileOfBoard.setPosition(-250, -250);

    mpChoicedPiece = nullptr;
}

void ChessBoardViewSFML::ClickProcess(const sf::Vector2i clickPosition, GamePlay& game)
{
    int clickedRow = clickPosition.y / cTileSize,
        clickedColumn = clickPosition.x / cTileSize;
    if (mpChoicedPiece && mpChoicedPiece->isMoveAvailable(Location{ clickedRow, clickedColumn }))
    {
        game.getPCurrentPlayer()->Move(mpChoicedPiece->getLocation(), Location{ clickedRow, clickedColumn }, game);
    }

    auto pBoard = game.getPBoard();

    if (pBoard->getPieceAt(Location{ clickedRow, clickedColumn }))
    {
        mpChoicedPiece = pBoard->getPieceAt(Location{ clickedRow, clickedColumn });
        mRectangleChoicedPieceOutline.setPosition(clickedColumn * cTileSize, clickedRow * cTileSize);
        mpChoicedPiece->checkAvailableMoves(*pBoard);
        mpChoicedPiece->checkMovesOnSafety(*pBoard);
    }
}

void ChessBoardViewSFML::DrawFrame(GamePlay& game)
{
    for (int row{ 0 }; row < cBoardSize; row++)
    {
        for (int column{ 0 }; column < cBoardSize; column++)
        {
            if ((row + column) % 2 == 0)
            {
                mRectangleWhiteTileOfBoard.setPosition(cTileSize * column, cTileSize * row);
                mWindow->draw(mRectangleWhiteTileOfBoard);
            }
            else
            {
                mRectangleBlackTileOfBoard.setPosition(cTileSize * column, cTileSize * row);
                mWindow->draw(mRectangleBlackTileOfBoard);
            }
            auto pBoard = game.getPBoard();
            auto pPiece = pBoard->getPieceAt(Location{ row, column });
            if (pPiece != nullptr)
            {
                sf::Sprite drawingSprite{ getSpriteOfChessPiece(pPiece->getColor(),pPiece->getType()) };
                drawingSprite.setPosition(cTileSize * column, cTileSize * row);
                mWindow->draw(drawingSprite);
            }
            if (mpChoicedPiece && mpChoicedPiece->isMoveAvailable(Location{ row, column }))
            {
                mRectangleAvailableMoveFill.setPosition(cTileSize * column, cTileSize * row);
                mWindow->draw(mRectangleAvailableMoveFill);
            }
        }
    }

    mWindow->draw(mRectangleChoicedPieceOutline);
}

void ChessBoardViewSFML::DrawPiece(std::shared_ptr<ChessPiece> pPiece)
{
}

void ChessBoardViewSFML::DrawAvailableMoves(std::shared_ptr<ChessPiece> pPiece, const GamePlay& game)
{
}

void ChessBoardViewSFML::PlayerTurn(const Color& color, GamePlay& game)
{
}

sf::Sprite ChessBoardViewSFML::getSpriteOfChessPiece(const Color& color, const ChessPiece::Type& type)
{
    sf::Sprite sprite;
    sprite.setTexture(mTextureOfChessPieces);
    int offsetLeft{ 0 }, offsetTop{ 0 };

    if (color == Color::White)
        offsetTop = 0;
    else
        offsetTop = 1;

    switch (type)
    {
    case ChessPiece::Type::Pawn:
        offsetLeft = 0;
        break;
    case ChessPiece::Type::Rook:
        offsetLeft = 1;
        break;
    case ChessPiece::Type::Bishop:
        offsetLeft = 2;
        break;
    case ChessPiece::Type::Knight:
        offsetLeft = 3;
        break;
    case ChessPiece::Type::Queen:
        offsetLeft = 4;
        break;
    case ChessPiece::Type::King:
        offsetLeft = 5;
        break;
    default:
        break;
    }

    sprite.setTextureRect(sf::Rect(offsetLeft * cTileSize, offsetTop * cTileSize, cTileSize, cTileSize));
    return sprite;
}

