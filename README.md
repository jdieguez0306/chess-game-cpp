# C++ Chess Game

An object-oriented chess engine written in C++ that models chess pieces, board state, movement rules, captures, and threat detection using inheritance and polymorphism.

This project was developed to practice object-oriented programming principles and C++ memory management while implementing the core logic of a chess system.

## Features

* Object-oriented chess piece hierarchy
* Abstract `ChessPiece` base class
* Derived classes for:

  * Pawn
  * Rook
  * Bishop
  * King
* Piece-specific movement validation
* Board boundary validation
* Path obstruction detection
* Piece capture logic
* Turn tracking
* Threat detection
* Unicode representation of chess pieces
* Deep copying of board state
* Dynamic memory management
* Copy constructor and copy-assignment support

## Object-Oriented Design

The project uses an abstract `ChessPiece` class as the base of the chess-piece hierarchy.

Each chess piece implements its own movement behavior by overriding virtual functions such as:

```cpp
virtual Type getType() = 0;
virtual bool canMoveToLocation(int toRow, int toColumn) = 0;
virtual const char* toString() = 0;
```

This design allows the chess board to interact with different piece types through `ChessPiece` pointers while allowing each derived class to provide its own behavior.

### Piece Hierarchy

```text
ChessPiece
├── PawnPiece
├── RookPiece
├── BishopPiece
└── KingPiece
```

## C++ Concepts Demonstrated

This project demonstrates several important C++ and software-engineering concepts:

* Object-oriented programming
* Classes and encapsulation
* Inheritance
* Runtime polymorphism
* Abstract classes
* Pure virtual functions
* Pointers and dynamic allocation
* Destructors
* Deep copying
* Copy constructors
* Copy assignment
* 2D vectors
* Enumerations
* Modular `.cc` and `.hh` file organization

## Project Structure

```text
chess-game-cpp/
│
├── Chess.h
│
├── ChessBoard.cc
├── ChessBoard.hh
│
├── ChessPiece.cc
├── ChessPiece.hh
│
├── PawnPiece.cc
├── PawnPiece.hh
│
├── RookPiece.cc
├── RookPiece.hh
│
├── BishopPiece.cc
├── BishopPiece.hh
│
├── KingPiece.cc
└── KingPiece.hh
```

## Chess Board

`ChessBoard` manages the current state of the game and stores chess pieces in a two-dimensional board representation.

The board is responsible for operations such as:

* Adding pieces
* Moving pieces
* Validating destinations
* Checking whether movement paths are clear
* Capturing opposing pieces
* Tracking turns
* Determining whether a board location is under threat

## Memory Management

Chess pieces are dynamically allocated and stored using pointers.

The board implements proper cleanup as well as deep-copy behavior so that copied chess boards maintain independent copies of their pieces rather than sharing the same memory.

This includes implementation of:

* Destructor
* Copy constructor
* Copy-assignment operator

## Building the Project

The source files can be compiled using a C++17-compatible compiler.

For example:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -c *.cc
```

A runnable demonstration program can also be added using a `main.cpp` file.


## Skills

`C++` `Object-Oriented Programming` `Inheritance` `Polymorphism` `Algorithms` `Data Structures` `Memory Management`

