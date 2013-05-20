#ifndef PUZZLE_HEUR_H
#define PUZZLE_HEUR_H

using namespace std; 

/** PuzzleHeuristic is an abstract class that has two child classes 
*   used to calculate the f distance of a particular board state.
*   @author Omar Khulusi
*/
class PuzzleHeuristic
{
 public:
 /** This is a pure virtual function that is overloaded in OutOfPlaceHeuristic and ManhattanHeuristic
 *   @param tiles The array of tiles
 *   @param size Size of the board
 *
 *   @return 0
 */
  virtual int compute(int *tiles, int size) = 0;
};

/** This is a class used to calculate the f distance that is simple to implement but inefficient.  It inherits
*   from PuzzleHeuristic.
*   @author Omar Khulusi
*/
class OutOfPlaceHeuristic : public PuzzleHeuristic
{

 /** Compute the f distance of the board state, where the distance is incrementedy by one for every tile that is out of place. 
 *
 *   @param tiles The array of tiles
 *   @param size Size of the board
 *
 *   @return F distance
 */
 int compute(int *tiles, int size);
};

/** This is a class used to calculate the f distance that is more difficult to implement but very efficient.  It inherits
*   from PuzzleHeuristic
*
*   @author Omar Khulusi
*/
class ManhattanHeuristic : public PuzzleHeuristic
{
 /** Compute the F distance of the board state, where the distance that each tile is from its correct location is added for
 *   every out of place tile.
 *
 *   @param tiles The array of tiles
 *   @param size Size of the board
 *
 *   @return F distance
 */
 int compute(int *tiles, int size);
};

#endif
