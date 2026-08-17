#include "BishopPiece.hh"
#include "ChessBoard.hh"

using namespace Student;
//using Student::ChessBoard;

//ChessBoard::ChessBoard() {};
//ChessBoard::~ChessBoard() {};

// Constructor for BishopPiece
BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column): 
    ChessPiece(board, color, row, column) {}

// Get Type of Piece (Bishop)
Type BishopPiece:: getType() {
    return ::Bishop; 
}

bool BishopPiece::canMoveToLocation(int toRow, int toColumn) {
    
    // Bishop can move diagonally with no limit distance
    int differ_row = std::abs(toRow - getRow());
    int differ_col = std::abs(toColumn - getColumn());
    if (differ_row != differ_col) {
        return false;
    }
    return true;
}

const char* BishopPiece:: toString() {
    return(getColor() == ::White) ? u8"\u2657" : u8"\u265D";

}
