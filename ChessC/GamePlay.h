#pragma once
#include <memory>
#include "Player.h"
#include "ChessBoard.h"

enum class Color;
class ChessBoard;
class Player;

class GamePlay
{
public:
	GamePlay();

	void ResetBoard();
	void SwitchTurn();
	
	std::shared_ptr<ChessBoard> getPBoard() const;
	Color getTurn() const;
	std::shared_ptr<Player> getPCurrentPlayer() const;
private:
	std::shared_ptr<ChessBoard> mpBoard;
	Color mTurn;
	std::shared_ptr<Player> mpPlayerWhite = std::make_shared<Player>();
	std::shared_ptr<Player> mpPlayerBlack = std::make_shared<Player>();
};

