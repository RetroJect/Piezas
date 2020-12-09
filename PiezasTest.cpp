/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
protected:
  PiezasTest() {}            //constructor runs before each test
  virtual ~PiezasTest() {}   //destructor cleans up after tests
  virtual void SetUp() {}    //sets up before each test (after constructor)
  virtual void TearDown() {} //clean up after each test, (before destructor)
};

TEST(PiezasTest, dropPieceInvalidNegative)
{
  Piezas game;
  ASSERT_TRUE(game.dropPiece(-1) == Invalid);
}

TEST(PiezasTest, dropPieceInvalidLarge)
{
  Piezas game;
  ASSERT_TRUE(game.dropPiece(5) == Invalid);
}

TEST(PiezasTest, dropPieceValid)
{
  Piezas game;
  for (int i=0; i < BOARD_COLS; i++) {
    Piece dropped = game.dropPiece(i);
    ASSERT_TRUE(dropped != Invalid && dropped != Blank);
  }
}

TEST(PiezasTest, dropPieceFull)
{
  Piezas game;
  for (int i=0; i < BOARD_ROWS; i++) {
    game.dropPiece(0);
  }
  ASSERT_TRUE(game.dropPiece(0) == Blank);
}

TEST(PiezasTest, pieceAtInvalidNegativeRow)
{
  Piezas game;
  ASSERT_TRUE(game.pieceAt(-1, 0) == Invalid);
}

TEST(PiezasTest, pieceAtInvalidNegativeCol)
{
  Piezas game;
  ASSERT_TRUE(game.pieceAt(0, -1) == Invalid);
}

TEST(PiezasTest, pieceAtInvalidLargeRow)
{
  Piezas game;
  ASSERT_TRUE(game.pieceAt(5, 0) == Invalid);
}

TEST(PiezasTest, pieceAtInvalidLargeCol)
{
  Piezas game;
  ASSERT_TRUE(game.pieceAt(0, 5) == Invalid);
}

TEST(PiezasTest, pieceAtValidEmpty)
{
  Piezas game;
  for (int col=0; col < BOARD_COLS; col++) {
    for (int row=0; row < BOARD_ROWS; row++) {
      ASSERT_TRUE(game.pieceAt(row, col) == Blank);
    }
  }
}

TEST(PiezasTest, pieceAtValidFullBoard)
{
  Piezas game;
  // Put a piece in every spot
  for (int col=0; col < BOARD_COLS; col++) {
    for (int row=0; row < BOARD_ROWS; row++) {
      game.dropPiece(col);
    }
  }

  for (int col=0; col < BOARD_COLS; col++) {
    for (int row=0; row < BOARD_ROWS; row++) {
      Piece dropped = game.pieceAt(row, col);
      ASSERT_TRUE(dropped != Invalid && dropped != Blank);
    }
  }
}

TEST(PiezasTest, pieceAtValidPartFull)
{
  Piezas game;
  // Drop an x
  game.dropPiece(0);
  // Drop an o
  game.dropPiece(0);

  ASSERT_TRUE(game.pieceAt(0, 0) == X);
  ASSERT_TRUE(game.pieceAt(1, 0) == O);
  ASSERT_TRUE(game.pieceAt(2, 0) == Blank);
}

TEST(PiezasTest, gameStateEmpty)
{
  Piezas game;
  ASSERT_TRUE(game.gameState() == Invalid);
}

TEST(PiezasTest, gameStatePartFull)
{
  Piezas game;
  // Put some pieces
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(2);
  game.dropPiece(3);
  game.dropPiece(3);
  ASSERT_TRUE(game.gameState() == Invalid);
}

TEST(PiezasTest, gameStateTieCheckerboard)
{
  Piezas game;
  /*
    xoxo
    oxox
    xoxo
  */
  for (int col=0; col < BOARD_COLS; col++) {
    for (int row=0; row < BOARD_ROWS; row++) {
      game.dropPiece(col);
    }
  }
  ASSERT_TRUE(game.gameState() == Blank);
}

TEST(PiezasTest, gameStateTieRow)
{
  Piezas game;
  /*
    xoxo
    oooo
    xxxx
  */

  // First two rows
  for (int col=0; col < BOARD_COLS; col++) {
    // drop x
    game.dropPiece(col);
    // drop o
    game.dropPiece(col);
  }
  // Top row
  for (int col=0; col < BOARD_COLS; col++) {
    game.dropPiece(col);
  }
  ASSERT_TRUE(game.gameState() == Blank);
}

TEST(PiezasTest, gameStateTieCol)
{
  Piezas game;
  /*
    xoxo
    xoxo
    xoxo
  */
  for (int row=0; row < BOARD_ROWS; row++) {
    for (int col=0; col < BOARD_COLS; col++) {
      game.dropPiece(col);
    }
  }
  ASSERT_TRUE(game.gameState() == Blank);
}

TEST(PiezasTest, gameStateXWinCol)
{
  Piezas game;
  /*
    xxox
    xoxo
    xxox
  */
  for (int col=1; col < BOARD_COLS; col++) {
    for (int row=0; row < BOARD_ROWS; row++) {
      game.dropPiece(col);
    }
  }
  for (int row=0; row < BOARD_ROWS; row++) {
    // Pass O turn with bad placement
    game.dropPiece(-1);
    // Drop x
    game.dropPiece(0);
  }
  ASSERT_TRUE(game.gameState() == X);
}

TEST(PiezasTest, gameStateOWinCol)
{
  Piezas game;
  /*
    oxox
    ooxo
    oxox
  */
  for (int col=1; col < BOARD_COLS; col++) {
    for (int row=0; row < BOARD_ROWS; row++) {
      game.dropPiece(col);
    }
  }
  for (int row=0; row < BOARD_ROWS; row++) {
    // Drop O
    game.dropPiece(0);
    // Pass X turn with bad placement
    game.dropPiece(-1);
  }
  ASSERT_TRUE(game.gameState() == O);
}

TEST(PiezasTest, gameStateXWinRow)
{
  Piezas game;
  /*
    xoxo
    oxox
    xxxx
  */

  // First row
  for (int col=0; col < BOARD_COLS; col++) {
    // drop x
    game.dropPiece(col);
    // drop o
    game.dropPiece(-1);
  }
  // Col 0 and 2
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(2);
  game.dropPiece(2);

  // Drop a piece
  game.dropPiece(-1);

  // Col 1 and 3
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(3);
  game.dropPiece(3);

  ASSERT_TRUE(game.gameState() == X);
}

TEST(PiezasTest, gameStateOWinRow)
{
  Piezas game;
  /*
    oxox
    xoxo
    oooo
  */

  // Switch to O
  game.dropPiece(-1);

  // First row
  for (int col=0; col < BOARD_COLS; col++) {
    // drop o
    game.dropPiece(col);
    // drop x
    game.dropPiece(-1);
  }
  // Col 0 and 2
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(2);
  game.dropPiece(2);

  // Drop a piece
  game.dropPiece(-1);

  // Col 1 and 3
  game.dropPiece(1);
  game.dropPiece(1);
  game.dropPiece(3);
  game.dropPiece(3);

  ASSERT_TRUE(game.gameState() == O);
}