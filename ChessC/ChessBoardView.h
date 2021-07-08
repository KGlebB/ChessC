#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>
#include "GamePlay.h"
class GamePlay;
class ChessPiece;
enum class Color;

class ChessBoardView
{
public:
	virtual void DrawFrame(GamePlay& game);
	virtual void DrawPiece(std::shared_ptr<ChessPiece> piece);
	virtual void DrawAvailableMoves(std::shared_ptr<ChessPiece> piece, const GamePlay& game);
	virtual void PlayerTurn(const Color& color, GamePlay& game);
};

class ChessBoardViewConsole : public ChessBoardView
{
public:
	void DrawFrame(GamePlay& game) override;
	void DrawPiece(std::shared_ptr<ChessPiece> pPiece) override;
	void DrawAvailableMoves(std::shared_ptr<ChessPiece> pPiece, const GamePlay& game) override;
	void PlayerTurn(const Color& color, GamePlay& game) override;
private:
	void SetBasicConsoleColor();
	void SetConsoleColorOfPiece(std::shared_ptr<const ChessPiece> pPiece);
};