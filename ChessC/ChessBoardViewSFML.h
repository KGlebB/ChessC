#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "ChessBoardView.h"

const int cTileSize = 128;

class ChessBoardViewSFML : public ChessBoardView
{
public:
	ChessBoardViewSFML(std::shared_ptr<sf::RenderWindow> window, const std::string& textureLink);
	void ClickProcess(const sf::Vector2i clickPosition, GamePlay& game);
	void DrawFrame(GamePlay& game) override;
	void DrawPiece(std::shared_ptr<ChessPiece> pPiece) override;
	void DrawAvailableMoves(std::shared_ptr<ChessPiece> pPiece, const GamePlay& game) override;
	void PlayerTurn(const Color& color, GamePlay& game) override;
private:
	sf::Sprite getSpriteOfChessPiece(const Color& color, const ChessPiece::Type& type);
	std::shared_ptr<sf::RenderWindow> mWindow;
	sf::Texture mTextureOfChessPieces;

	sf::RectangleShape
		mRectangleChoicedPieceOutline,
		mRectangleAvailableMoveFill,
		mRectangleWhiteTileOfBoard,
		mRectangleBlackTileOfBoard;

	std::shared_ptr<ChessPiece> mpChoicedPiece;
};

