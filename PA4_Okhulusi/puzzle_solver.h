#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <queue>
#include <vector>
#include <deque>
#include <set>
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"
#include "mylist.h"

/**  PuzzleSolver is the class used to implement a cheat to the puzzle, where a user can enter -1 to receive
*    an efficient order of moves to make in order to solve the puzzle and thus complete the game.
*/
class PuzzleSolver
{
 public:
  /** Typedef for the closed-list set.  closed_list variable is defined as
  *   BoardSet closedlist; when you written for the run() function
  */
  typedef std::set<Board *, BoardLessThan> BoardSet;

  /** Constructor makes a copy of the Board and stores it in _b
  *
  *   @param b Board that is to be copied and dynamically allocated
  */
  PuzzleSolver(const Board &b);

  /** PuzzleSolver Destructor deletes the dynamically allocated board b_
  */
  ~PuzzleSolver();

  /** Run the A* search returning -1 if no solution exists or
  *  the number of moves in the solution.  The A* search is a complex algorithm
  *  that essentially dictates that the fastest way to complete the game or solve the problem
  *  is to follow the path with the lowest heuristic score f. 
  *
  *   @param ph A PuzzleHeuristic pointer to the chosen puzzle heuristic that calculates f distances
  *   @return -1 if no solution exists or the number of moves in the solution (moveCounter)
  */
  int run(PuzzleHeuristic *ph);

  /** Accessor method for the solution List
  *   @return Mylist<int> solution_list, the solution list that will be printed out in the main() in puzzle.cpp
  */
  MyList<int>& getSolutionList();

  /** Accessor method for how many expansions were performed in the search
  *   @return int expansions_, the number of expansions performed in the search
  */
  int getNumExpansions();

 private:
  Board* b_;
  int expansions_;
  MyList<int> solution_list;
  //**** Declare a List to store your solutions sequence of tiles to move
};

#endif
