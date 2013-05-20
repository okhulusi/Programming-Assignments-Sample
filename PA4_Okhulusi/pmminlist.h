#ifndef PMMINLIST_H
#define PMMINLIST_H
#include <list>

/**
 * PMMinList implements a sorted list of PuzzleMoves
 * based on their f-score (from smallest to largest)
 */
class PMMinList 
{
 public:
  
  PMMinList();
  ~PMMinList();
  
  /** Accessor Method for size of items in the list
  *   @return The size of items in the list 
  */
  int size() const { return slist_.size(); }
  
  /** Method to see if the list is empty
  *  @return True if the list is empty, false otherwise 
  */
  bool empty() const { return slist_.empty(); }
  
  /** Adds a puzzle move to the sorted list.  In other words, 
  *    adds the value val to the internal list in sorted
  *    order from smallest to largest 
  *    @param pm Pointer to PuzzleMove that will be added to the list in its sorted position. 
  *    @return nothing
  */
  void push(PuzzleMove* pm);
  
  /** Removes the minimum scored (front) puzzle move
  *   @return nothing
  */
  void pop();
  
  /** Get the PuzzleMove with the lowest score (at the top of the list) 
  *
  *  @return A pointer to the PuzzleMove with the lowest score  
  */
  PuzzleMove* top();
 private:
  /** the sorted list */
  std::list<PuzzleMove*> slist_;
};

#endif
