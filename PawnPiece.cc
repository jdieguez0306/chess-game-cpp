#include "PawnPiece.hh"
#include "ChessBoard.hh"

using namespace Student;
using Student::ChessBoard;

// Constructor for BishopPiece
PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column): 
    ChessPiece(board, color, row, column) {}

// Get Type of Piece (Bishop)
Type PawnPiece:: getType() {
    return ::Pawn; // what does the double colon before type do?
}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn) {
    /*Black piece 
    - can move in increasing row number (downwards)
    - if on row 1, can move 1 or 2 steps along the same column
    - pawn can consume another piece by moving diagonally adjacent square with a higher
        row number for black piece*/

     /*White piece 
    - can move in decreasing row number (upwards)
    - A white piece on row n-2 can move 1 or 2 steps along the same column.
    -A pawn can consume another piece by moving to a diagonally adjacent square with
     a lower row number for a white piece
    */

    int fromRow = getRow();
    int fromCol = getColumn();
    ChessBoard& board = getBoard();

    int dir = (getColor() == ::Color::White) ? -1 : 1;                          // direction of movement
    int startRow = (getColor() == ::Color::White) ? board.getNumRows() - 2: 1;  //White start row n-1, Black start row 1

    //Consuming another piece diagonially of a different color
    if (std::abs(toColumn - fromCol) == 1 && (toRow - fromRow) == dir) {
        ChessPiece* dest = board.getPiece(toRow, toColumn);
        // Check if the next step is empty or can be captured based on different color
        if (dest != nullptr && dest->getColor() != getColor()) {
            return true;
        }

        return false; 
    }

    // can’t move forward into occupied square (Can move along the same column)
    if (toColumn == fromCol && (toRow - fromRow) == dir) {
        if (board.isOccupied(toRow, toColumn))
            return false; // can’t move forward into occupied square
        return true;
    }

    if (toColumn == fromCol && (toRow - fromRow) == 2 * dir && fromRow == startRow) {
        int midRow = fromRow + dir;
        // Checks if path along the column is clear for an additonal step (can move 1 or 2 steps)
        if (board.isOccupied(midRow, fromCol) || board.isOccupied(toRow, toColumn))
            return false;
            
        return true;
    }

    return false;

}

const char* PawnPiece:: toString() {
    return(getColor() == ::White) ? u8"\u2659" : u8"\u265F";

}