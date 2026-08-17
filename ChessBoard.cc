#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
//#include <iostream> // DELETE After debug

using Student::ChessBoard;

// Constructor for ChessBoard
ChessBoard::ChessBoard(int numRow, int numCol) : numRows(numRow), numCols(numCol) {
    
    board.resize(numRows, std::vector<ChessPiece*>(numCols, nullptr));
}

// Copy Constructor
ChessBoard:: ChessBoard(const ChessBoard &other) : numRows(other.numRows), numCols(other.numCols), turn(other.turn) {
    
    board.resize(numRows, std::vector<ChessPiece*>(numCols, nullptr));

    // Copy each individual part/piece of the Chessboard
    for (int row = 0; row< numRows; row++) {
        for( int col = 0; col < numCols; col++) {
            ChessPiece* piece = other.board[row][col];
            if (piece != nullptr) {
                 switch (piece->getType()) {
                    case Type::Pawn:
                        board[row][col] = new PawnPiece(*this, piece->getColor(), row, col);
                        break;
                    case Type::Rook:
                        board[row][col] = new RookPiece(*this, piece->getColor(), row, col);
                        break;
                    case Type::Bishop:
                        board[row][col] = new BishopPiece(*this, piece->getColor(), row, col);
                        break;
                    case Type::King:
                        board[row][col] = new KingPiece(*this, piece->getColor(), row, col);
                        break;
                    default:
                        board[row][col] = nullptr;

                }
            }
        }
    }
}

// Assignment Operator to perform a Deep Copy
ChessBoard& ChessBoard:: operator=(const ChessBoard& other) {
    // Handle self test
    if (this == &other){
        return *this;
    }

    // Set temp object using copy constructor
    ChessBoard temp(other);
    
    // Copy and Swap Method
    std::swap(numRows, temp.numRows);
    std::swap(numCols, temp.numCols);
    std::swap(turn, temp.turn);
    std::swap(board, temp.board);
   
    return *this;
}

// Destructor
ChessBoard:: ~ChessBoard() {
    // Clear the ChessBoard to free the memory
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (board[row][col] != nullptr) {
                delete board[row][col];
                board[row][col] = nullptr;
            }
        }
    }
}
// Create  Chess Piece
void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {

    // returns nothing if piece is placed out of bounds 
    if (!inBounds(startRow, startColumn)) {
        return;
    }

    // Remove any existing piece first before adding new pieces
    if (board.at(startRow).at(startColumn) != nullptr) {
        delete board.at(startRow).at(startColumn);
        board.at(startRow).at(startColumn) = nullptr;
    }

    ChessPiece* newChessPiece = nullptr;

    switch(ty) {
        case Type::Pawn:
            newChessPiece = new PawnPiece(*this, col, startRow, startColumn);
            break;
        case Type::Bishop:
            newChessPiece = new BishopPiece(*this, col, startRow, startColumn);
            break;
        case Type::Rook:
            newChessPiece = new RookPiece(*this, col, startRow, startColumn);
            break;
        case Type::King:
            newChessPiece = new KingPiece(*this, col, startRow, startColumn);
            break;
        default:
            return;
    }

    // Add new piece into the memory and assign it to a pointer on board
    board[startRow][startColumn] = newChessPiece;
}

// TODO: Part 2, Implement Part 2
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
     
    // Check if a piece exists at the start position
    ChessPiece* piece = getPiece(fromRow, fromColumn);
    if (piece == nullptr) {
        return false;  // no piece to move
    }
    // Check if the turn color is correct
    //std::cout << "color turn: " << piece->getColor() << std::endl;
    if (piece->getColor() != turn) {
        //std::cout << "Not correct turn" << std::endl;
        return false; 
    }
    // Check if the move itself is valid
    if (!isValidMove(fromRow, fromColumn, toRow, toColumn)) {
        return false;
    }

    // Handle the capture if move is valid (free memory on occupied space)
    if (board[toRow][toColumn] != nullptr) {
        delete board[toRow][toColumn];
        board[toRow][toColumn] = nullptr; 
    }

    // Move the Piece
    board[toRow][toColumn] = piece;
    board[fromRow][fromColumn] = nullptr;
    piece->setPosition(toRow, toColumn);

    // Change turns from White <-> Black
    turn = (turn == White)? Black: White;
    //std::cout << "turn: " << turn << std::endl; //debug (DELETE LATER)
    return true;
}

// Determines if the chess piece moves within the bounds
bool ChessBoard::inBounds(int row, int column) {

    if(row >= 0 && row < numRows && column >= 0 && column < numCols) {
        return true;
    }
    return false;
}

// Is the pathway from start to finish occupied by another piece
bool ChessBoard::isOccupied(int row, int column) {
    if (!inBounds(row, column)) {
        return false;
    }
    if (board[row][column] != nullptr) {
        return true;
    }
    return false;
}

// Checks of piece's pathway is obstructed
bool ChessBoard:: isPathObstructed(int fromRow, int fromCol, int toRow, int toCol) {
    // Gets direction the piece will be moving (1 or -1) or staying in same row/column 
    int rowDir = (toRow - fromRow) == 0 ? 0 : (toRow - fromRow) / abs(toRow - fromRow);
    int colDir = (toCol - fromCol) == 0 ? 0 : (toCol - fromCol) / abs(toCol - fromCol);

    // update row and column if piece will be moving
    int currRow = fromRow + rowDir;
    int currCol = fromCol + colDir;

    // Makes sure the Piece is moving, not staying in the same place
    if (rowDir == 0 && colDir == 0) {
        return false;
    }

    // Helps to prevent infinite loops
    int steps = 0;
    int maxSteps = numRows * numCols;

    while ((currRow != toRow || currCol != toCol) && steps < maxSteps) {
        if (!inBounds(currRow, currCol)){
            break;
        }
        // Checks if path is occuppied by another piece
        if (isOccupied(currRow, currCol)) {
            return true;
        }

        currRow += rowDir;
        currCol += colDir;
        steps++;
    }
    
    return false;
}

// Is the move valid function
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
    
    ChessPiece* curr_piece = getPiece(fromRow, fromColumn);
    ChessPiece* dest_piece = getPiece(toRow, toColumn);

    // Moving piece must exist on board
    if (curr_piece == nullptr) {
        return false;
    }

    // Piece does not move to the same spot
    if (fromRow == toRow && fromColumn == toColumn) {
        return false;
    }

    // Piece should not move out of bounds
    if (!inBounds(fromRow, fromColumn) || !inBounds(toRow, toColumn)) {
        return false;
    }

    // Piece should not be obstructed by another piece between start to finish
    if(isPathObstructed(fromRow, fromColumn, toRow, toColumn)) {
        return false;
    }

    // Final position should not contain another piece of the same color
    if((dest_piece != nullptr) && (curr_piece->getColor() == dest_piece->getColor())) {
        return false;
    }
    // Check if the move valid based on the type of chess piece
    if (!curr_piece->canMoveToLocation(toRow, toColumn)){
        return false;
    }

    // TODO Part 3: Check when piece is moved, will King be under threat of being checked
    // Temporary move to see the potential threat to king piece (move piece logic)
    board.at(toRow).at(toColumn) = curr_piece;
    curr_piece->setPosition(toRow, toColumn);
    board.at(fromRow).at(fromColumn) = nullptr;

    // Initializing king piece variables
    bool king_check = false;
    ChessPiece* king_piece = nullptr;

    // Go through each row and column combo until a king piece is found
    for (int row_it = 0; row_it < numRows; row_it++) {
        for (int col_it = 0; col_it < numCols; col_it++) {
            // Piece at current row and column position
            ChessPiece* piece = getPiece(row_it, col_it);
            // Check if piece is a king of the same color of the moving piece
            if (piece != nullptr && piece->getColor() == curr_piece->getColor() && piece->getType() == King) {
                king_piece = piece;
                break; // break inner loop
            }
        }
        if (king_piece != nullptr) {
            break; // break outer loop
        }
    }

    // Check if found king piece is under threat due to the temp move
     if (king_piece != nullptr) {
        if (isPieceUnderThreat(king_piece->getRow(), king_piece->getColumn()) && king_piece->getColor() == turn) {
            king_check = true;
        }
     }

    // Undo the temporary move
    board.at(fromRow).at(fromColumn) = curr_piece;
    curr_piece->setPosition(fromRow, fromColumn);
    board.at(toRow).at(toColumn) = dest_piece;

    if (king_check) {
        return false;
    }
    
    return true;
}

// TODO: Part 2
bool ChessBoard::isPieceUnderThreat(int row, int column){
    ChessPiece* threat_piece = board[row][column];
    
    if (threat_piece == nullptr) {
        return false;
    }

    // get color of piece being checked
    Color turn_color = threat_piece->getColor();

    // go through all surrounding pieces of the opposing color
    for (int row_pos = 0; row_pos < numRows; row_pos++) {
        for (int col_pos = 0; col_pos < numCols; col_pos++) {
            ChessPiece* opponent_piece = getPiece(row_pos, col_pos);
            if (opponent_piece == nullptr) {
                continue;
            }
            if (opponent_piece->getColor() != turn_color){
                if (opponent_piece->canMoveToLocation(row, column) && !isPathObstructed(row_pos, col_pos, row, column)) {
                    return  true;
                }
            }
        }
    }
    return false;
}

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << i << " ";
    }
    outputString << std::endl << "  ";
    // top border
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++){
        outputString << row << "|";
        for (int column = 0; column < numCols; column++){
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString()) << " ";
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl << std::endl;

    return outputString;
}