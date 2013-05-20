#include "puzzle_move.h"
#include "pmminlist.h"

/**
 * Default Constructor
 */
PMMinList::PMMinList() : slist_()
{

}

/**
 * Default Destructor
 */
PMMinList::~PMMinList()
{

}

void PMMinList::push(PuzzleMove* pm)
{
  std::list<PuzzleMove*>::iterator it = slist_.begin();
 
 	if(slist_.size() ==0){
 		slist_.push_front(pm);
 		return;
 	}
 	
 	for(it = slist_.begin(); it != slist_.end(); ++it){
 		if(*pm < **it){
 			slist_.insert(it, pm);
 			return;
 		}
 	}
 	
 	slist_.push_back(pm);
}

void PMMinList::pop()
{
  slist_.pop_front();
}

PuzzleMove* PMMinList::top()
{
  return slist_.front();
}

