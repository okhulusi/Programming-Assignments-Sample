#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include "puzzle_solver.h"
#include "pmminlist.h"
#include "mylist.h"

using namespace std;

PuzzleSolver::PuzzleSolver(const Board &b){
	b_ = new Board(b);
}

PuzzleSolver::~PuzzleSolver(){ delete b_; }

int PuzzleSolver::getNumExpansions()
{
  return expansions_;
}

int PuzzleSolver::run(PuzzleHeuristic *ph){
	PMMinList open_list;
	BoardSet closed_list;
	vector<PuzzleMove*> garbage_list;
	expansions_ = 0;
	int moveCounter = 0;
	
	PuzzleMove *move = new PuzzleMove(*b_);	
	open_list.push(move);
	closed_list.insert(b_);
	garbage_list.push_back(move);
	
	while((!open_list.empty()) && (!b_->solved())){
		move = open_list.top();
		open_list.pop();
		
		if(move->b_->solved()){
			while(move->prev_ != NULL){
				moveCounter++;
				solution_list.push_back(move->tileMove_);
				move = move->prev_;
			}
			
			for(unsigned int i = 0; i < garbage_list.size(); i++){
				delete garbage_list[i];
			}
			return moveCounter;
		}
		
		map<int, Board*> potentialNextMoves = move->b_->potentialMoves();
		for(map<int, Board*>::iterator it = potentialNextMoves.begin(); it != potentialNextMoves.end(); ++it){
			PuzzleMove *s = new PuzzleMove(it->first, it->second, move);
			bool checked = false;
			for(BoardSet::iterator it2 = closed_list.begin(); it2 != closed_list.end(); ++it2){ //for each s
				if(*(s->b_) == **it2){
					checked = true;
					break;
				}
			}
			if(!checked){
				s->h_ = ph->compute(s->b_->getTiles(), s->b_->getSize());
				closed_list.insert(s->b_);
				open_list.push(s);
				expansions_++;
				
				garbage_list.push_back(s);
			} else delete s;
			delete it->second;
		}
		
	}
	
	delete move;
	 return -1;
}

MyList<int>& PuzzleSolver:: getSolutionList(){
	return solution_list;
}
