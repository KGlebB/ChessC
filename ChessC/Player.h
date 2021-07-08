#pragma once
#include "GamePlay.h"
#include "ChessBoard.h"
#include "ChessPiece.h"

struct Location;
class GamePlay;
class ChessBoard;

enum class Color {
	White,
	Black
};

std::string ColorName(const Color& color);

class Player
{
public:
	Player();
	Player(const Color& color);

	void Move(const Location& from, const Location& to, GamePlay& game) const;
	Color getColor() const;
	void setColor(const Color& color);
private:
	Color mColor;
};

