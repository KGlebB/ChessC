#include "ChessBoardView.h"

void ChessBoardView::DrawFrame(GamePlay& game)
{
}

void ChessBoardView::DrawPiece(std::shared_ptr<ChessPiece> piece)
{
}

void ChessBoardView::DrawAvailableMoves(std::shared_ptr<ChessPiece> piece, const GamePlay& game)
{
}

void ChessBoardView::PlayerTurn(const Color& color, GamePlay& game)
{
}

void ChessBoardViewConsole::DrawFrame(GamePlay& game)
{
	SetBasicConsoleColor();
	auto pBoard = game.getPBoard();
	std::cout << "  0 1 2 3 4 5 6 7\n";
	for (int row{ 0 }; row < cBoardSize; row++)
	{
		std::cout << row << " ";
		for (int column{ 0 }; column < cBoardSize; column++)
		{
			auto pPiece = pBoard->getPieceAt(Location{ row, column });

			if (pPiece == nullptr)
				std::cout << " ";
			else
				DrawPiece(pPiece);

			std::cout << " ";
			SetBasicConsoleColor();
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
	PlayerTurn(game.getTurn(), game);
}

void ChessBoardViewConsole::DrawPiece(std::shared_ptr<ChessPiece> pPiece)
{

	SetConsoleColorOfPiece(pPiece);

	switch (pPiece->getType())
	{
	case ChessPiece::Type::Pawn:
		std::cout << "P";
		break;
	case ChessPiece::Type::Rook:
		std::cout << "R";
		break;
	case ChessPiece::Type::Bishop:
		std::cout << "B";
		break;
	case ChessPiece::Type::Knight:
		std::cout << "H";
		break;
	case ChessPiece::Type::Queen:
		std::cout << "Q";
		break;
	case ChessPiece::Type::King:
		std::cout << "K";
		break;
	default:
		break;
	}

}

void ChessBoardViewConsole::DrawAvailableMoves(std::shared_ptr<ChessPiece> pPiece, const GamePlay& game)
{
	auto pBoard = game.getPBoard();
	pPiece->checkAvailableMoves(*pBoard);
	pPiece->checkMovesOnSafety(*pBoard);
	auto moves = pPiece->getAvailableMoves();
	std::cout << "  0 1 2 3 4 5 6 7\n";
	for (int row{ 0 }; row < cBoardSize; row++)
	{
		std::cout << row << " ";
		for (int column{ 0 }; column < cBoardSize; column++)
		{

			if (pPiece->isMoveAvailable(Location{ row, column }))
			{
				std::cout << "*";
			}
			else if (pPiece->getLocation() == Location{ row, column})
			{
				DrawPiece(pPiece);
			}
			else
			{
				std::cout << " ";
			}
			
			std::cout << " ";
			SetBasicConsoleColor();
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void ChessBoardViewConsole::PlayerTurn(const Color& color, GamePlay& game)
{
	std::cout << ColorName(color) << " player turn.\n";
	std::cout << "Choose piece to move: ";
	Location from, to;
	std::cin >> from;
	DrawAvailableMoves(game.getPBoard()->getPieceAt(from), game);
	std::cout << "Choose position to move: ";
	std::cin >> to;
	game.getPCurrentPlayer()->Move(from, to, game);
}

void ChessBoardViewConsole::SetBasicConsoleColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void ChessBoardViewConsole::SetConsoleColorOfPiece(std::shared_ptr<const ChessPiece> pPiece)
{
	if (pPiece->getColor() == Color::Black)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

