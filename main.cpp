#include <iostream>

#include "ChessBoard.hh"
#include "Chess.h"

using namespace Student;

void printMoveResult(const std::string& description, bool success)
{
    std::cout << description << ": "
              << (success ? "SUCCESS" : "INVALID")
              << "\n";
}

int main()
{
    std::cout << "=====================================\n";
    std::cout << "       C++ OOP Chess Demo\n";
    std::cout << "=====================================\n\n";

    // Create an 8x8 chess board.
    ChessBoard board(8, 8);

    // White pieces
    board.createChessPiece(White, King,   7, 4);
    board.createChessPiece(White, Rook,   7, 0);
    board.createChessPiece(White, Bishop, 7, 2);
    board.createChessPiece(White, Pawn,   6, 3);
    board.createChessPiece(White, Pawn,   6, 4);

    // Black pieces
    board.createChessPiece(Black, King,   0, 4);
    board.createChessPiece(Black, Rook,   0, 7);
    board.createChessPiece(Black, Bishop, 0, 5);
    board.createChessPiece(Black, Pawn,   1, 3);
    board.createChessPiece(Black, Pawn,   1, 4);

    std::cout << "Initial board:\n\n";
    std::cout << board.displayBoard().str();

    // ---------------------------------------------------------
    // Demonstrate valid movement and alternating turns.
    // ---------------------------------------------------------

    std::cout << "Move demonstration\n";
    std::cout << "------------------\n";

    bool result = board.movePiece(6, 4, 5, 4);
    printMoveResult(
        "White pawn moves from (6,4) to (5,4)",
        result
    );

    std::cout << board.displayBoard().str();

    result = board.movePiece(1, 4, 2, 4);
    printMoveResult(
        "Black pawn moves from (1,4) to (2,4)",
        result
    );

    std::cout << board.displayBoard().str();

    // ---------------------------------------------------------
    // Demonstrate invalid movement.
    // ---------------------------------------------------------

    result = board.movePiece(7, 0, 6, 1);
    printMoveResult(
        "White rook attempts diagonal movement from (7,0) to (6,1)",
        result
    );

    // Since the invalid move does not change turns,
    // White should still be able to make a valid move.
    result = board.movePiece(6, 3, 5, 3);
    printMoveResult(
        "White pawn moves from (6,3) to (5,3)",
        result
    );

    std::cout << board.displayBoard().str();

    // Give Black a valid turn.
    result = board.movePiece(1, 3, 2, 3);
    printMoveResult(
        "Black pawn moves from (1,3) to (2,3)",
        result
    );

    std::cout << board.displayBoard().str();

    // ---------------------------------------------------------
    // Demonstrate threat detection.
    // ---------------------------------------------------------

    std::cout << "Threat detection\n";
    std::cout << "----------------\n";

    bool whiteKingThreatened = board.isPieceUnderThreat(7, 4);
    bool blackKingThreatened = board.isPieceUnderThreat(0, 4);

    std::cout << "White king under threat: "
              << (whiteKingThreatened ? "Yes" : "No")
              << "\n";

    std::cout << "Black king under threat: "
              << (blackKingThreatened ? "Yes" : "No")
              << "\n\n";

    // ---------------------------------------------------------
    // Demonstrate deep copying.
    // ---------------------------------------------------------

    std::cout << "Deep copy demonstration\n";
    std::cout << "-----------------------\n";

    ChessBoard copiedBoard(board);

    std::cout << "A second ChessBoard was created using "
                 "the copy constructor.\n\n";

    std::cout << "Copied board:\n\n";
    std::cout << copiedBoard.displayBoard().str();

    std::cout << "Demo complete.\n";

    return 0;
}
