#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student:: ChessBoard;
using Student::ChessPiece;

// Constructor for ChessPiece
ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column): 
    board(board), color(color), row(row), column(column) {}

ChessBoard& ChessPiece:: getBoard(){
    return board;
}

// Get Colour of Piece
Color ChessPiece:: getColor(){
    return color;
}

// Get Row number of chess piece
int ChessPiece:: getRow(){
    return row;

}

// Get Column number of chess piece
int ChessPiece:: getColumn(){
    return column; 
}

void ChessPiece:: setPosition(int new_row, int new_column) {
    row = new_row;
    column = new_column;
}
