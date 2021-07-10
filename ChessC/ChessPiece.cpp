#include "ChessPiece.h"

Location Location::operator+(const Location& other) const
{
	return Location{ this->row + other.row, this->column + other.column };
}

Location Location::operator*(const int multiplier) const
{
	return Location{ this->row * multiplier, this->column * multiplier };
}

std::istream& operator>>(std::istream& is, Location& location)
{
	is >> location.row >> location.column;
	return is;
}

bool operator==(const Location& left, const Location& right)
{
	if (left.row == right.row && left.column == right.column)
		return true;
	else
		return false;
}

Location operator*(const int multiplier, const Location& coordinates)
{
	return coordinates * multiplier;
}

ChessPiece::ChessPiece(const Color& color, const Location& location)
{
	setLocation(location);
	setColor(color);
}

Location ChessPiece::getLocation()
{
	return mLocationOnBoard;
}

void ChessPiece::setLocation(const Location& location)
{
	mLocationOnBoard = location;
}

void ChessPiece::Move(const Location& newLocation, std::shared_ptr<ChessBoard> pBoard)
{
	pBoard->MovePiece(getLocation(), newLocation);
}

void ChessPiece::checkMovesOnSafety(const ChessBoard& board)
{
	for (auto move : getAvailableMoves())
		if (!(isCheckSafely(board, move)))
			mlAvailableMoves.remove(move);
}

void ChessPiece::checkAvailableMoves(const ChessBoard& board)
{
}

bool ChessPiece::isMoveAvailable(const Location& location)
{
	for (auto move : getAvailableMoves())
		if (move == location)
			return true;
	return false;
}

inline Color ChessPiece::getColor() const
{
	return mColor;
}

bool ChessPiece::isColor(const Color& color) const
{
	if (getColor() == color)
		return true;
	else
		return false;
}

inline void ChessPiece::setColor(Color color)
{
	mColor = color;
}

ChessPiece::ProcessMoveResult ChessPiece::ProcessOneMove(const ChessBoard& board, const Location& offset)
{
	Location moveLocation{ getLocation() + offset };

	if (moveLocation.column < 0 || moveLocation.column > cMaxCoordinate || moveLocation.row < 0 || moveLocation.row > cMaxCoordinate)
		return ProcessMoveResult::OutOfBoard;

	auto pPiece{ board.getPieceAt(moveLocation) };

	if (pPiece == nullptr)
		return ProcessMoveResult::FreeSpace;

	if (isColor(pPiece->getColor()))
		return ProcessMoveResult::FriendlyPiece;
	else
		return ProcessMoveResult::HostilePiece;
}

void ChessPiece::resetAvailableMoves()
{
	mlAvailableMoves.clear();
}

void ChessPiece::addToAvailableMoves(const Location& movedLocation)
{
	mlAvailableMoves.push_front(movedLocation);
}

void ChessPiece::checkOneMove(const ChessBoard& board, const Location& way)
{
	ProcessMoveResult result;
	result = ProcessOneMove(board, way);
	if (result == ProcessMoveResult::FreeSpace || result == ProcessMoveResult::HostilePiece)
		addToAvailableMoves(getLocation() + way);
}

void ChessPiece::checkOneWayMoves(const ChessBoard& board, const Location& way)
{
	Location offset{ way };
	while (true)
	{
		ProcessMoveResult result = ProcessOneMove(board, offset);
		if (result == ProcessMoveResult::FreeSpace)
		{
			addToAvailableMoves(getLocation() + offset);
		}
		else
		{
			if (result == ProcessMoveResult::HostilePiece)
				addToAvailableMoves(getLocation() + offset);
			return;
		}
		offset = offset + way;
	}
}

inline void ChessPiece::allowMoveIfHostile(const ChessBoard& board, const Location& way)
{
	if (ProcessOneMove(board, way) == ProcessMoveResult::HostilePiece)
		addToAvailableMoves(getLocation() + way);
}

bool ChessPiece::isCheckSafely(const ChessBoard& board, const Location& newLocation)
{
	std::shared_ptr<ChessBoard> pNewBoard = std::make_shared<ChessBoard>(board);
	pNewBoard->getPieceAt(getLocation())->Move(newLocation, pNewBoard);
	CheckMoves(*pNewBoard);

	if (pNewBoard->isKingInCheck(getColor()))
		return false;
	else
		return true;
}

inline ChessPiece::Type ChessPiece::getType() const
{
	return mType;
}

std::forward_list<Location> ChessPiece::getAvailableMoves()
{
	return mlAvailableMoves;
}

ChessPiecePawn::ChessPiecePawn(const Color& color, const Location& location) : ChessPiece(color, location)
{
	mType = Type::Pawn;
}

void ChessPiecePawn::checkAvailableMoves(const ChessBoard& board)
{
	resetAvailableMoves();
	
	if (mColor == Color::White)
	{
		processPawnStepForward(board, Location{ 1, 0 }, cMinCoordinate + 1);

		allowMoveIfHostile(board, Location{  1,  1 });
		allowMoveIfHostile(board, Location{  1, -1 });
	}
	else
	{
		processPawnStepForward(board, Location{ -1, 0 }, cMaxCoordinate - 1);

		allowMoveIfHostile(board, Location{ -1,  1 });
		allowMoveIfHostile(board, Location{ -1, -1 });
	}
}

inline void ChessPiecePawn::processPawnStepForward(const ChessBoard& board, const Location& direction, const int& rowToDash)
{

	if (ProcessOneMove(board, direction) == ProcessMoveResult::FreeSpace)
	{
		addToAvailableMoves(getLocation() + direction);
		if (getLocation().row == rowToDash && ProcessOneMove(board, 2 * direction) == ProcessMoveResult::FreeSpace)
			addToAvailableMoves(getLocation() + 2 * direction);
	}
}

bool ChessPiece::canPromote()
{
	if (getType() == Type::Pawn && isColor(Color::White) && getLocation().row == 7)
		return true;
	if (getType() == Type::Pawn && isColor(Color::Black) && getLocation().row == 0)
		return true;
	return false;
}

ChessPieceBishop::ChessPieceBishop(const Color& color, const Location& location) : ChessPiece(color, location)
{
	mType = Type::Bishop;
}

void ChessPieceBishop::checkAvailableMoves(const ChessBoard& board)
{
	resetAvailableMoves();

	checkOneWayMoves(board, Location{  1,  1 });
	checkOneWayMoves(board, Location{  1, -1 });
	checkOneWayMoves(board, Location{ -1,  1 });
	checkOneWayMoves(board, Location{ -1, -1 });
}

ChessPieceKnight::ChessPieceKnight(const Color& color, const Location& location) : ChessPiece(color, location)
{
	mType = Type::Knight;
}

void ChessPieceKnight::checkAvailableMoves(const ChessBoard& board)
{
	resetAvailableMoves();
	
	checkOneMove(board, Location{  2, -1 });
	checkOneMove(board, Location{  2,  1 });
	checkOneMove(board, Location{  1, -2 });
	checkOneMove(board, Location{  1,  2 });

	checkOneMove(board, Location{ -2, -1 });
	checkOneMove(board, Location{ -2,  1 });
	checkOneMove(board, Location{ -1, -2 });
	checkOneMove(board, Location{ -1,  2 });
}

ChessPieceRook::ChessPieceRook(const Color& color, const Location& location) : ChessPiece(color, location)
{
	mType = Type::Rook;
}

void ChessPieceRook::checkAvailableMoves(const ChessBoard& board)
{
	resetAvailableMoves();

	checkOneWayMoves(board, Location{  0,  1 });
	checkOneWayMoves(board, Location{  0, -1 });
	checkOneWayMoves(board, Location{  1,  0 });
	checkOneWayMoves(board, Location{ -1,  0 });
}

ChessPieceQueen::ChessPieceQueen(const Color& color, const Location& location) : ChessPiece(color, location)
{
	mType = Type::Queen;
}

void ChessPieceQueen::checkAvailableMoves(const ChessBoard& board)
{
	resetAvailableMoves();

	checkOneWayMoves(board, Location{  1,  1 });
	checkOneWayMoves(board, Location{  1, -1 });
	checkOneWayMoves(board, Location{ -1,  1 });
	checkOneWayMoves(board, Location{ -1, -1 });

	checkOneWayMoves(board, Location{  0,  1 });
	checkOneWayMoves(board, Location{  0, -1 });
	checkOneWayMoves(board, Location{  1,  0 });
	checkOneWayMoves(board, Location{ -1,  0 });
}

ChessPieceKing::ChessPieceKing(const Color& color, const Location& location) : ChessPiece(color, location)
{
	mType = Type::King;
}

void ChessPieceKing::checkAvailableMoves(const ChessBoard& board)
{
	resetAvailableMoves();

	checkOneMove(board, Location{  1,  1 });
	checkOneMove(board, Location{  1,  0 });
	checkOneMove(board, Location{  1, -1 });

	checkOneMove(board, Location{  0,  1 });
	checkOneMove(board, Location{  0, -1 });

	checkOneMove(board, Location{ -1,  1 });
	checkOneMove(board, Location{ -1,  0 });
	checkOneMove(board, Location{ -1, -1 });

	checkCastlingMoves(board);
}

void ChessPieceKing::checkCastlingMoves(const ChessBoard& board)
{
	if (isColor(Color::White) && getLocation() == Location{ 0, 4 } ||
		isColor(Color::Black) && getLocation() == Location{ 7, 4 })
	{
		if (ProcessOneMove(board, Location{ 0,  1 }) == ProcessMoveResult::FreeSpace &&
			ProcessOneMove(board, Location{ 0,  2 }) == ProcessMoveResult::FreeSpace &&
			ProcessOneMove(board, Location{ 0,  3 }) == ProcessMoveResult::FriendlyPiece &&
			board.getPieceAt(Location{ getLocation().row, 7 })->getType() == Type::Rook)
		{
			addToAvailableMoves(Location{ getLocation().row, 7 });
		}
		if (ProcessOneMove(board, Location{ 0, -1 }) == ProcessMoveResult::FreeSpace &&
			ProcessOneMove(board, Location{ 0, -2 }) == ProcessMoveResult::FreeSpace &&
			ProcessOneMove(board, Location{ 0, -3 }) == ProcessMoveResult::FreeSpace &&
			ProcessOneMove(board, Location{ 0, -4 }) == ProcessMoveResult::FriendlyPiece &&
			board.getPieceAt(Location{ getLocation().row, 0 })->getType() == Type::Rook)
		{
			addToAvailableMoves(Location{ getLocation().row, 0 });
		}
	}
}

