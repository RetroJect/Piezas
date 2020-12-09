#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/

/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  this->turn = X;

  // Start with a fresh board just in case
  this->board.clear();
  // Set the board columns
  this->board.resize(BOARD_COLS);
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  // Delete the board
  this->board.clear();

  // Set the board columns
  this->board.resize(BOARD_COLS);
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
  // The piece to place
  Piece droppedPiece = this->turn;

  // Change players turn
  this->turn = (this->turn == X) ? O : X;

  // Check if out of bounds
  if (column < 0 || column > BOARD_COLS) {
    return Invalid;
  }

  // Check the column isn't full
  if (this->board[column].size() != BOARD_ROWS) {
    // Place the piece on the "top"
    this->board[column].push_back(droppedPiece);
    return droppedPiece;
  }

  // Column is full or something unpredicted happened
  return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  // Check out of bounds column
  if (column < 0 || column > BOARD_COLS) {
    return Invalid;
  }

  // Check out of bounds row
  if (row < 0 || row > BOARD_ROWS) {
    return Invalid;
  }

  // Make sure there are enough pieces in the column
  if (row < this->board[column].size()) {
    // Return the piece at the location
    return this->board[column][row];
  }

  // Not invalid, and location hasn't been modified yet
  return Blank;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  // Check if board is filled
  bool anyBlank = false;
  for (int i=0; i < BOARD_COLS; i++) {
    // If the length of the column isn't the amount of rows
    // there is a blank piece
    anyBlank = this->board[i].size() != BOARD_ROWS;
  }

  // If any blank, game is not over
  if (anyBlank) return Invalid;

  short int Xcount = 0;
  short int Ocount = 0;

  /* Count the columns */

  // Count max x's in columns
  for (int col=0; col < BOARD_COLS; col++) {
    int localMax = 0;
    int localCount = 0;
    Piece lastPiece = X;

    // Check every piece in the column
    for (int row=0; row < BOARD_ROWS; row++) {
      // If we see another of the same piece
      // and the current piece is X
      if (this->board[col][row] == X && this->board[col][row] == lastPiece) {
        // Increase # of successive pieces
        localCount++;
        // If our current string of Pieces is larger, set the max
        if (localCount > localMax) localMax = localCount;
      } else {
        // The streak has ended
        localCount = 0;
      }
      // Set our last seen piece
      lastPiece = this->board[col][row];
    }

    // Set the max X
    if (localMax > Xcount) Xcount = localMax;
  }

  // Count max O's in columns
  for (int col=0; col < BOARD_COLS; col++) {
    int localMax = 0;
    int localCount = 0;
    Piece lastPiece = O;

    // Check every piece in the column
    for (int row=0; row < BOARD_ROWS; row++) {
      // If we see another of the same piece
      // and the current piece is O
      if (this->board[col][row] == O && this->board[col][row] == lastPiece) {
        // Increase # of successive pieces
        localCount++;
        // If our current string of Pieces is larger, set the max
        if (localCount > localMax) localMax = localCount;
      } else {
        // The streak has ended
        localCount = 0;
      }
      // Set our last seen piece
      lastPiece = this->board[col][row];
    }

    // Set the max O
    if (localMax > Ocount) Ocount = localMax;
  }

  /* Count the rows */

  // Count max x's in rows
  for (int row=0; row < BOARD_ROWS; row++) {
    int localMax = 0;
    int localCount = 0;
    Piece lastPiece = X;

    // Check every piece in the column
    for (int col=0; col < BOARD_COLS; col++) {
      // If we see another of the same piece
      // and the current piece is X
      if (this->board[col][row] == X && this->board[col][row] == lastPiece) {
        // Increase # of successive pieces
        localCount++;
        // If our current string of Pieces is larger, set the max
        if (localCount > localMax) localMax = localCount;
      } else {
        // The streak has ended
        localCount = 0;
      }
      // Set our last seen piece
      lastPiece = this->board[col][row];
    }

    // Set the max X
    if (localMax > Xcount) Xcount = localMax;
  }

  // Count max o's in rows
  for (int row=0; row < BOARD_ROWS; row++) {
    int localMax = 0;
    int localCount = 0;
    Piece lastPiece = O;

    // Check every piece in the column
    for (int col=0; col < BOARD_COLS; col++) {
      // If we see another of the same piece
      // and the current piece is O
      if (this->board[col][row] == O && this->board[col][row] == lastPiece) {
        // Increase # of successive pieces
        localCount++;
        // If our current string of Pieces is larger, set the max
        if (localCount > localMax) localMax = localCount;
      } else {
        // The streak has ended
        localCount = 0;
      }
      // Set our last seen piece
      lastPiece = this->board[col][row];
    }

    // Set the max O
    if (localMax > Ocount) Ocount = localMax;
  }

  // Check if X won
  if (Xcount > Ocount) {
    return X;
  }

  // Check if O won
  if (Ocount > Xcount) {
    return O;
  }

  // It's a tie
  return Blank;
}