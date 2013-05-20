#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <functional>

/** The Board class is the center of the entire puzzle game.  It is an array that has data containing 
*   the values at each tile on it, has the ability to move tiles, and overloads operators to be able to 
*   compare its state to other boards.  Furthermore, it has the ability to generate all potential moves
*   a user can make on it.
*/
class Board
{
 public:
  /** Default constructor.
  *  Initializes a 2x2 board that is dynamically allocated.  Each space is set to its index value, 
  *  which is technically a solved board.  No parameters are taken in.
  */
  Board(); 

  /** Init a board of given size and scramble it with numInitMoves 
  * by moving the space tile with a randomly chosen direction N, W, S, E
  * some of which may be invalid, in which case we skip that move 
  * 
  *  @param size Number of tiles for the game.  \
  *      Should be a perfect square (4, 16, 25)
  *  @param numInitMoves Number of tile moves to attempt to scramble the board
  *  @param seed Use to seed the random number generator (srand) 
  */
  Board(int size, int numInitMoves, int seed);

  /** Copy constructor that makes a deep copy of the given board.  This allows for the avoidance of 
  *  segmentation faults when trying to access the tiles array.
  *
  *  @param b Board that is to be copied
  *
  *  @return A deep copy of the given board
  */
  Board(const Board &b);

  /** Another kind of "copy" constructor */
  Board(int *tiles, int size); 

  /** Default destructor.
  *  Deletes the dynamically allocated array of tiles, otherwise known as the board pieces.
  */
  ~Board();

  /** Move method, takes in a value of a tile on the board and switches it with the blank space.  This method
  *  will not make the swap if the move is invalid, where the tile value's index is not vertically or
  *  horizontally adjacent to the blank tile space, which has its location found at the beginning of the method.
  *
  *  @param tile The value of a tile on the board.  This is not to be confused with the index value int.
  *  @return true if the move is valid, false otherwise
  */
  bool move(int tile);

  /** This method plays out a single move of the current board, giving back 
  *   new boards with all possible moves that can be made.  In other words, it gives all move scenarios.
  *   Key=tile, Value=Ptr to corresponding Board
  * 
  *   @return a map containing key values that are the tile value that was moved and the Board that would result
  *   from the move
  */
  std::map<int, Board*> potentialMoves(); 

  /** Solved method.  This method is used to determine whether or not the game is complete, where all values
  *  are in their proper positions.
  *
  *  @return a bool that is true if the board is in its solved state and false if it still needs more moves
  *  to complete.
  */
  bool solved();

  /** Overload the operator <<.  Allows us to print out a board that is nicely formatted.  The width is
  *  set to the number of digits that the largest value in the puzzle is.
  *
  *  @param os An empty Ostream to be returned with the contents of the board
  *  @param b Board and its data to be printed out
  *  @return an ostream containing the contents of the board
  */
  friend std::ostream& operator<<(std::ostream &os, const Board &b);
  
  /** Overload the operator ==.  This is used to compare two boards to see if all of the tiles are the same
  *  values at respective indices.  
  *
  * @param rhs Board being compared to this board
  *
  * @return a bool that is true if the boards are the same and false if they're not.
  */
  bool operator==(const Board& rhs) const;
  
  /** Overload operator <.  This was given as skeleton code.
  * 
  *  @param rhs Board to be compared with
  *  @return a bool that is true if the first board size is smaller or if the values are smaller, checking
  *  from top right to bottom left by row.
  */
  bool operator<(const Board& rhs) const;
  
  /** Overload the operator !=.  This is the opposite of the overload of operator ==, where it compares
  *  two boards to see if they're not equal.
  *
  *  @param rhs Board to be compared with current board.
  *
  *  @return a bool that is true if the boards are not equal and false otherwise.
  */
  bool operator!=(const Board& rhs) const;
  
  /** Accessor method for pointer to the array of tiles, otherwise known as a board.
  *
  *  @return the pointer to the array of tiles of the board.
  */
  int* getTiles() const;
  
  /** Accessor method for the size of the board.  This is the value resulting from multiply the dimensions of the
  *  puzzle.
  *
  *  @return the size of the board
  */
  int getSize() const;


 private:
  int *tiles_;
  int size_;

};

// Leave this alone and don't touch it!

/** Skeleton code
*/
struct BoardLessThan : 
  public std::binary_function<const Board*, const Board*,bool>
{
  /** Skeleton code method not modified
  *   @param b1 Pointer to first Board
  *   @param b2 Pointer to second Board
  *   @return true if b1 is less than b2 as defined by < operator
  */
  bool operator()(const Board *b1, const Board *b2) const
  {
    return *b1 < *b2;
  }
};



#endif
