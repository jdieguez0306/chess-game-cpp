#include "RookPiece.hh"
#include "ChessBoard.hh"

using namespace Student;
using Student::ChessBoard;

// Constructor for BishopPiece
RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column): 
    ChessPiece(board, color, row, column) {}

// Get Type of Piece (Bishop)
Type RookPiece:: getType() {
    return ::Type::Rook; // what does the double colon before type do?
}

bool RookPiece::canMoveToLocation(int toRow, int toColumn) {
    // Rook can move horizontally or vertically with no limit to distance
    int diff_row = abs(toRow - getRow());
    int diff_col = abs(toColumn - getColumn());
    
    return (diff_row == 0 && diff_col > 0) || (diff_col == 0 && diff_row > 0);
}

const char* RookPiece:: toString() {
    return(getColor() == ::Color::White) ? u8"\u2656" : u8"\u265C";

}
