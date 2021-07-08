#include "Player.h"

Player::Player()
{
}

Player::Player(const Color& color)
{
	mColor = color;
}

void Player::Move(const Location& from, const Location& to, GamePlay& game) const
{
	if (from == to)
		return;

	auto pBoard = game.getPBoard();
	auto pPieceFrom = pBoard->getPieceAt(from);
	if (pPieceFrom != nullptr && pPieceFrom->isColor(mColor))
	{
		auto pPieceTo = pBoard->getPieceAt(to);
		if (pPieceFrom->isMoveAvailable(to))
		{
			pPieceFrom->Move(to, pBoard);
			game.SwitchTurn();
		}
	}
}

Color Player::getColor() const
{
	return mColor;
}

void Player::setColor(const Color& color)
{
	mColor = color;
}


std::string ColorName(const Color& color)
{
	if (color == Color::White)
		return "White";
	else
		return "Black";
}