#include "KingPiece.hh"
#include "ChessBoard.hh"

using namespace Student;
//using Student::ChessBoard;

//ChessBoard::ChessBoard() {};
//ChessBoard::~ChessBoard() {};

// Constructor for KingPiece
KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column): 
    ChessPiece(board, color, row, column) {}

// Get Type of Piece (King)
Type KingPiece:: getType() {
    return ::King; 
}
// King Movement to a location function
bool KingPiece:: canMoveToLocation(int toRow, int toColumn) {
    /* King can move horizontally, vertically, and diagonally by one step */

    // Get direction that King Piece is moving towards (diagonally, horizontal, vertical)
    int diff_row = abs(toRow - getRow());
    int diff_col = abs(toColumn - getColumn());

    // Make sure that King is moved by one step only
    if (diff_row <= 1 && diff_col <= 1) {
        return true;
    }

    return false;
}
const char* KingPiece:: toString() {
    return(getColor() == ::White) ? u8"\u2654" : u8"\u265A";

}
