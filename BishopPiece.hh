#ifndef __BISHOPPIECE_H__
#define __BISHOPPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Bishop chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class BishopPiece : public ChessPiece
    {
    // Functions that are derived from ChessPiece
    public:
         /**
        * @brief
        * Constructor for BishopPiece.
        * @param board
        * The board to which the piece belongs.
        * @param color
        * The colour of the piece.
        * @param row
        * Starting row of the piece.
        * @param column
        * Starting column of the piece.
        */
        BishopPiece(ChessBoard &board, Color color, int row, int column);
        /**
        * @return
        * Type of piece.
        *
        * Note: An alternate perhaps more ideal way of implementation
        * would have been to define this function as pure virtual and
        * let each derived class override this function.
        */
       Type getType() override; // is the override necessary?
        /**
        * @brief
        * A pure virtual method to be implemented in the derived classes.
        * Determines if movement from current position to new position is valid.
        * @param toRow
        * The row of the destination position.
        * @param toColumn
        * The column of the destination position.
        * @return
        * A boolean indicating if a move from current to destination is valid.
        */
        bool canMoveToLocation(int toRow, int toColumn) override;

        /**
        * @brief
        * A pure virtual method to be implemented in the derived classes.
        * Returns a unicode string representation of the piece.
        * Refer to this link https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode
        * for more information on unicode representation of chess piece.
        * @return
        * A unicode representation of the piece.
        */
        const char *toString() override;

    };
}

#endif
