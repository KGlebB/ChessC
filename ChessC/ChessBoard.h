#pragma once
#include <array>
#include <memory>
#include "ChessPiece.h"
enum class Color;
struct Location;
class ChessPiece;

const int cBoardSize{ 8 };

class ChessBoard
{
public:
	ChessBoard();
	ChessBoard(const ChessBoard& other);

	void Reset();
	void SettleChessPieces(const Color& color);
	void MovePiece(const Location& from, const Location& to);
	void MovePieceCastle(const Location& from, const Location& to);
	void PromotePawn(const Location& pawnLocation);

	std::shared_ptr<ChessPiece> getPieceAt(const Location& location) const;
	bool isTileFree(const Location& location);
	void setPieceAt(const std::shared_ptr<ChessPiece>& piece, const Location& location);

	Location FindKing(const Color& kingColor);
	bool isKingInCheck(const Color& kingColor);

	friend void CheckMoves(const ChessBoard& board);

private:
	std::array<std::array<std::shared_ptr<ChessPiece>, cBoardSize>, cBoardSize> mapBoard;
};

