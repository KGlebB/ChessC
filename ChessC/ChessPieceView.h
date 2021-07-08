#pragma once
#include "ChessPiece.h"

class ChessPieceView
{
public:
	virtual void Draw(std::shared_ptr<ChessPiece> piece);

};

class ChessPieceViewConsole : public ChessPieceView
{
public:
	void Draw(std::shared_ptr<ChessPiece> piece) override;

};