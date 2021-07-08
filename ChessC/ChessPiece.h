#pragma once
#include <iostream>
#include <forward_list>
#include <algorithm>
#include "Player.h"
struct Location;
enum class Color;
class ChessBoard;

struct Location
{
	int row, column;

	Location operator+(const Location& other) const;
	Location operator*(const int multiplier) const;
};

const int cMinCoordinate{ 0 };
const int cMaxCoordinate{ 7 };

std::istream& operator>>(std::istream& is, Location& location);
bool operator==(const Location& left, const Location& right);
Location operator*(const int multiplier, const Location& coordinates);

class ChessPiece
{
public:
	enum class Type
	{
		Pawn,
		Rook,
		Knight,
		Bishop,
		Queen,
		King
	};

	ChessPiece(const Color& color, const Location& location);

	void Move(const Location& newLocation, std::shared_ptr<ChessBoard> pBoard);
	
	void checkMovesOnSafety(const ChessBoard& board);
	virtual void checkAvailableMoves(const ChessBoard& board);
	bool isMoveAvailable(const Location& location);
	bool canPromote();

	inline Color getColor() const;
	bool isColor(const Color& color) const;
	inline Type getType() const;
	inline Location getLocation();
	void setLocation(const Location& location);

	inline std::forward_list<Location> getAvailableMoves();

protected:
	void setColor(Color color);

	enum class ProcessMoveResult
	{
		OutOfBoard,
		FreeSpace,
		FriendlyPiece,
		HostilePiece
	};

	ProcessMoveResult ProcessOneMove(const ChessBoard& board, const Location& offset); // relative Location
	void resetAvailableMoves();
	void addToAvailableMoves(const Location& movedLocation); // abosulte Location

	void checkOneMove(const ChessBoard& board, const Location& way); // relative Location
	void checkOneWayMoves(const ChessBoard& board, const Location& way); // relative Location
	inline void allowMoveIfHostile(const ChessBoard& board, const Location& way); // relative Location

	bool isCheckSafely(const ChessBoard& board, const Location& newLocation);

	Location mLocationOnBoard;
	Color mColor;
	Type mType;

	std::forward_list<Location> mlAvailableMoves;
};

class ChessPiecePawn : public ChessPiece
{
public:
	ChessPiecePawn(const Color& color, const Location& location);

	void checkAvailableMoves(const ChessBoard& board) override;

private:
	inline void processPawnStepForward(const ChessBoard& board, const Location& direction, const int& rowToDash);
};

class ChessPieceBishop : public ChessPiece
{
public:
	ChessPieceBishop(const Color& color, const Location& location);

	void checkAvailableMoves(const ChessBoard& board) override;
};

class ChessPieceKnight : public ChessPiece
{
public:
	ChessPieceKnight(const Color& color, const Location& location);

	void checkAvailableMoves(const ChessBoard& board) override;

};

class ChessPieceRook : public ChessPiece
{
public:
	ChessPieceRook(const Color& color, const Location& location);

	void checkAvailableMoves(const ChessBoard& board) override;
};

class ChessPieceQueen : public ChessPiece
{
public:
	ChessPieceQueen(const Color& color, const Location& location);

	void checkAvailableMoves(const ChessBoard& board) override;
};

class ChessPieceKing : public ChessPiece
{
public:
	ChessPieceKing(const Color& color, const Location& location);

	void checkAvailableMoves(const ChessBoard& board) override;

private:
	void checkCastlingMoves(const ChessBoard& board);
};

