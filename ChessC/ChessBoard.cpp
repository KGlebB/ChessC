#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	Reset();
}

ChessBoard::ChessBoard(const ChessBoard& other)
{
	for (int row{ 0 }; row < cBoardSize; row++)
		for (int column{ 0 }; column < cBoardSize; column++)
		{
			if (other.mapBoard[row][column])
			{
				auto color = other.mapBoard[row][column]->getColor();
				auto location = other.mapBoard[row][column]->getLocation();
				switch (other.mapBoard[row][column]->getType())
				{
				case ChessPiece::Type::Pawn:
					this->mapBoard[row][column] = std::make_shared<ChessPiecePawn>(color, location);
					break;
				case ChessPiece::Type::Rook:
					this->mapBoard[row][column] = std::make_shared<ChessPieceRook>(color, location);
					break;
				case ChessPiece::Type::Knight:
					this->mapBoard[row][column] = std::make_shared<ChessPieceKnight>(color, location);
					break;
				case ChessPiece::Type::Bishop:
					this->mapBoard[row][column] = std::make_shared<ChessPieceBishop>(color, location);
					break;
				case ChessPiece::Type::Queen:
					this->mapBoard[row][column] = std::make_shared<ChessPieceQueen>(color, location);
					break;
				case ChessPiece::Type::King:
					this->mapBoard[row][column] = std::make_shared<ChessPieceKing>(color, location);
					break;
				default:
					break;
				}
			}
			else
			{
				this->mapBoard[row][column] = nullptr;
			}
		}
}

void ChessBoard::Reset()
{
	SettleChessPieces(Color::White);
	SettleChessPieces(Color::Black);
}

void ChessBoard::SettleChessPieces(const Color& color)
{
	int row;
	if (color == Color::Black)
		row = cBoardSize - 1;
	else
		row = 0;

	mapBoard[row][0] = std::make_shared<ChessPieceRook>(color, Location{ row, 0 });
	mapBoard[row][7] = std::make_shared<ChessPieceRook>(color, Location{ row, 7 });
	mapBoard[row][1] = std::make_shared<ChessPieceKnight>(color, Location{ row, 1 });
	mapBoard[row][6] = std::make_shared<ChessPieceKnight>(color, Location{ row, 6 });
	mapBoard[row][2] = std::make_shared<ChessPieceBishop>(color, Location{ row, 2 });
	mapBoard[row][5] = std::make_shared<ChessPieceBishop>(color, Location{ row, 5 });
	mapBoard[row][3] = std::make_shared<ChessPieceQueen>(color, Location{ row, 3 });
	mapBoard[row][4] = std::make_shared<ChessPieceKing>(color, Location{ row, 4 });

	if (color == Color::Black)
		row = cBoardSize - 2;
	else
		row = 1;

	for (int column{ 0 }; column < cBoardSize; column++)
		mapBoard[row][column] = std::make_shared<ChessPiecePawn>(color, Location{ row, column });
}

void ChessBoard::MovePiece(const Location& from, const Location& to)
{
	if (mapBoard[from.row][from.column]->getType() == ChessPiece::Type::King &&
		mapBoard[to.row][to.column] &&
		mapBoard[to.row][to.column]->getType() == ChessPiece::Type::Rook)
	{
		auto pRookPiece = std::make_shared<ChessPieceRook>(getPieceAt(to)->getColor(), to);
		mapBoard[to.row][to.column] = mapBoard[from.row][from.column];
		mapBoard[to.row][to.column]->setLocation(to);
		mapBoard[from.row][from.column] = nullptr;
		if (pRookPiece->getLocation() == Location{ 0, 0 })
		{
			mapBoard[0][3] = pRookPiece;
			mapBoard[0][3]->setLocation(Location{ 0, 3 });
		}
		else if (pRookPiece->getLocation() == Location{ 0, 7 })
		{
			mapBoard[0][5] = pRookPiece;
			mapBoard[0][5]->setLocation(Location{ 0, 5 });
		}
		else if (pRookPiece->getLocation() == Location{ 7, 0 })
		{
			mapBoard[7][3] = pRookPiece;
			mapBoard[7][3]->setLocation(Location{ 7, 3 });
		}
		else if (pRookPiece->getLocation() == Location{ 7, 7 })
		{
			mapBoard[7][5] = pRookPiece;
			mapBoard[7][5]->setLocation(Location{ 7, 5 });
		}
	}
	else
	{
		mapBoard[to.row][to.column] = mapBoard[from.row][from.column];
		mapBoard[from.row][from.column] = nullptr;
		mapBoard[to.row][to.column]->setLocation(to);
		if (mapBoard[to.row][to.column]->canPromote())
			PromotePawn(to);
	}
}

void ChessBoard::PromotePawn(const Location& pawnLocation)
{
	Color color{ mapBoard[pawnLocation.row][pawnLocation.column]->getColor() };
	mapBoard[pawnLocation.row][pawnLocation.column] = std::make_shared<ChessPieceBishop>(color, pawnLocation);
}

std::shared_ptr<ChessPiece> ChessBoard::getPieceAt(const Location& location) const
{
	return mapBoard[location.row][location.column];
}

bool ChessBoard::isTileFree(const Location& location)
{
	if (getPieceAt(location) == nullptr)
		return true;
	else
		return false;
}

void ChessBoard::setPieceAt(const std::shared_ptr<ChessPiece>& piece, const Location& location)
{
	mapBoard[location.row][location.column] = piece;
}

Location ChessBoard::FindKing(const Color& kingColor)
{
	for (auto y : mapBoard)
		for (auto x : y)
			if (x && x->getType() == ChessPiece::Type::King && x->isColor(kingColor))
				return x->getLocation();
	return Location{ -1, -1 };
}

bool ChessBoard::isKingInCheck(const Color& kingColor)
{
	Location kingLocation{ FindKing(kingColor) };

	for (auto y : mapBoard)
		for (auto x : y)
			if (x && !(x->isColor(kingColor)) && x->isMoveAvailable(kingLocation))
				return true;
	return false;
}

void CheckMoves(const ChessBoard& board)
{
	for (auto y : board.mapBoard)
		for (auto x : y)
			if (x)
				x->checkAvailableMoves(board);
}

