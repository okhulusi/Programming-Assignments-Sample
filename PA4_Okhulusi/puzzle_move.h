#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include <functional>
#include "board.h"
#include "puzzle_heur.h"

/** The purpose of this class is to keep track of a board state until the game has 
*   been solved.
*/
class PuzzleMove
{
 public:
  /** Constructor for starting Board of an A* search
  *
  *   @param b Starting Board that will be initialized and dynamically allocated
  */
  PuzzleMove(Board &b);

  /** Constructor for subsequent search boards that keep track of board states until game is completed.
  *    (i.e. those returned by Board::potentialMoves() )
  *
  *    @param tile Tile to be moved
  *    @param b Board state to be modified
  *    @param parent Board state that keeps track of the previous move
  */
  PuzzleMove(int tile, Board *b, PuzzleMove *parent);

  /** PuzzleMove Destructor
  *   Deletes the dynamically allocated board.
  */
  ~PuzzleMove();

  /** Compare to PuzzleMoves based on f distance
  *
  *   @param p PuzzleMove to be compared with
  *
  *   @return true if the first puzzlemove has a lower f distance, false otherwise
  */
  bool operator<(const PuzzleMove& p) const;
  
  /** Compare to PuzzleMoves based on f distance
  *
  *   @param p Reference to a PuzzleMove to be compared with
  *   
  *   @return true if the first puzzlemove has a higher f distance, false otherwise 
  */
  bool operator>(const PuzzleMove& p) const;
  
  /** Compare to PuzzleMoves based of f distance
  *
  *   @param p PuzzleMove to be compared with
  *
  *   @return true if the first puzzle has the same f distance as the second, false otherwise
  */
  bool operator==(const PuzzleMove& p) const;

  // Data members can be public
 public:
 
 /** Tile moved to reach the Board b */
  int tileMove_; 
  
  /** Pointer to a board representing the updated state */
  Board *b_; 
  
  /** Distance from the start board */     
  int g_;
  
  /** Heuristic distance to the goal */
  int h_;
  
  /** Pointer to parent PuzzleMove */
  PuzzleMove *prev_; 
};


// Leave this alone and don't touch it!
/** Skeleton code given
*/
struct PuzzleMoveGreater : 
  public std::binary_function<const PuzzleMove*, const PuzzleMove*,bool>
{
  /** Skeleton code not modified
  *   @param m1 Pointer to a PuzzleMove
  *   @param m2 Pointer to another PuzzleMove
  *   @return true if m1's f distance is larger than m2's f distance as defined in the > operator overload, false otherwise
  */
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    return *m1 > *m2;
  }
};

#endif
