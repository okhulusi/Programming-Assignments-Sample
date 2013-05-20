#include "puzzle_move.h"

PuzzleMove::PuzzleMove(int tile, Board *b, PuzzleMove *parent){
	tileMove_ = tile;
	b_ = new Board(*b);
	prev_ = parent;
	g_ = (parent->g_) + 1;
	
	h_ = 0;
}

PuzzleMove::PuzzleMove(Board &b){
	tileMove_ = 0;
	b_ = new Board(b);
	prev_ = NULL; 
	g_ = 0;
	h_ = 0;
}

PuzzleMove::~PuzzleMove(){
	delete b_;
}

// Compare to PuzzleMoves based on f distance (needed for priority queue
bool PuzzleMove::operator<(const PuzzleMove& p) const
{
  if((g_ + h_) < (p.g_ + p.h_)){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ > p.g_)){
    return true;
  }
  else {
    return false;
  }
}
bool PuzzleMove::operator>(const PuzzleMove& p) const
{
  if( (g_ + h_) > (p.g_ + p.h_) ){
    return true;
  }
  else if((g_ + h_ == p.g_ + p.h_) && (g_ < p.g_) ){
    return true;
  }
  else {
     return false;
  }
  
}

bool PuzzleMove::operator==(const PuzzleMove& p) const {
	if( (g_ + h_) == (p.g_ + p.h_) ){
		return true;
	}
	
	return false;
}

