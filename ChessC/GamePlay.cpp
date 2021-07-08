#include "GamePlay.h"

GamePlay::GamePlay()
{
	mpBoard = std::make_shared<ChessBoard>();
	mTurn = Color::White;
	mpPlayerWhite->setColor(Color::White);
	mpPlayerBlack->setColor(Color::Black);
}

void GamePlay::ResetBoard() {
	mpBoard->Reset();
	mTurn = Color::White;
}

void GamePlay::SwitchTurn()
{
	if (mTurn == Color::White)
		mTurn = Color::Black;
	else
		mTurn = Color::White;
}

std::shared_ptr<ChessBoard> GamePlay::getPBoard() const
{
	return mpBoard;
}

Color GamePlay::getTurn() const
{
	return mTurn;
}

std::shared_ptr<Player> GamePlay::getPCurrentPlayer() const
{
	if (mTurn == Color::White)
		return mpPlayerWhite;
	else
		return mpPlayerBlack;
}
