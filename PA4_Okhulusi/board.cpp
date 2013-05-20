#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;

Board::Board(int size, int numInitMoves, int seed )
{
  size_ = size;
  tiles_ = new int[size_];
  int dim = static_cast<int>(sqrt(size_));
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  for(int i=0; i < numInitMoves; i++){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
    }
  }
}

Board::Board()
{
  size_ = 4;
  tiles_ = new int[size_];
  for(int i = 0; i < 4; i++){
  	tiles_[i] = i;
  }
}

Board::~Board()
{
  delete [] tiles_;
}

bool Board::operator<(const Board& rhs) const
{
  if(size_ < rhs.size_){
    return true;
  }
  bool val = false;
  for(int i=0; i < size_; i++){
    if(tiles_[i] < rhs.tiles_[i]){
       //val = true;
       //break;
       return true;
     }
     else if(tiles_[i] > rhs.tiles_[i]){
       //break;
       return false;
     }
  }
  return val;
}

bool Board::move(int tile){
	int blankLocation = 0;
	int tileLocation = 0;
	
	for(int i = 0; i < size_; i++){
		if(tiles_[i] == 0){
			blankLocation = i;
		}
		if(tiles_[i] == tile){
			tileLocation = i;
		}
	}
	
	if(tileLocation == (int)(blankLocation + sqrt(size_))){		//down move
		tiles_[blankLocation] = tile;
		tiles_[tileLocation] = 0;
	} else if(tileLocation == (int)(blankLocation - sqrt(size_))){	//up move
		tiles_[blankLocation] = tile;
		tiles_[tileLocation] = 0;
	} else if(tileLocation == (blankLocation - 1) && blankLocation%((int)sqrt(size_)) != 0){ //left move
		tiles_[blankLocation] = tile;
		tiles_[tileLocation] = 0;
	} else if(tileLocation == (blankLocation + 1) && (blankLocation + 1)%((int)sqrt(size_)) != 0){ //right move
		tiles_[blankLocation] = tile;
		tiles_[tileLocation] = 0;
	} else{
		return false;
	}
	
	return true;
}

std::map<int, Board*> Board::potentialMoves(){
	int blankLocation = 0;
	
	std::map<int, Board*> moveList;
	
	for(int i = 0; i < size_; i++){
		if(tiles_[i] == 0){
			blankLocation = i;
		}
	}
	
	if(blankLocation - (int)sqrt(size_) >= 0){
		 Board *board = new Board(*this);
		 board->move(tiles_[blankLocation - (int)sqrt(size_)]);
		 moveList[tiles_[blankLocation - (int)sqrt(size_)]] = board;
	}
	if(blankLocation + (int)sqrt(size_) < size_){
		Board *board = new Board(*this);
		board->move(tiles_[blankLocation + (int)sqrt(size_)]);
		moveList[tiles_[blankLocation + (int)sqrt(size_)]] = board;
	}
	if(blankLocation%((int)sqrt(size_)) != 0){
		Board *board = new Board(*this);
		board->move(tiles_[blankLocation-1]);
		moveList[tiles_[blankLocation-1]] = board;
	}
	if((blankLocation + 1)%((int)sqrt(size_)) != 0){
		Board *board = new Board(*this);
		board->move(tiles_[blankLocation+1]);
		moveList[tiles_[blankLocation+1]] = board;
	}
	
	return moveList;
}

bool Board::solved(){
	for(int i = 0; i < size_; i++){
		if(tiles_[i] != i){
			return false;
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream &os, const Board &b){	//overload << operator
	int numMaxDigits = 0;
	int widthVal = b.getSize() - 1;
	
	while(widthVal != 0){
		widthVal/=10;
		numMaxDigits++;
	}
	
	for(int j = 0; j < (int)sqrt(b.getSize()); j++){
		for(int i = 0; i < (int)sqrt(b.getSize()); i++){
			if(b.getTiles()[i+j*(int)sqrt(b.getSize())] != 0){
				os << setw((numMaxDigits+1));
				os << b.getTiles()[i+j*(int)sqrt(b.getSize())];
			}
			else {
				os << setw((numMaxDigits+1));
				os << " ";
			}
		}
		os << '\n';
	}
	return os;
}

bool Board::operator==(const Board& rhs) const{
	if(size_ != rhs.getSize()){
		return false;
	}
	for(int i = 0; i < size_; i++){
		if(tiles_[i] != rhs.getTiles()[i]){
			return false;
		}
	} 
	
	return true;
}

Board::Board(const Board &b){ 						
	size_ = b.size_;
	tiles_ = new int[size_];
	
	for(int i = 0; i < size_; i++){
		tiles_[i] = b.tiles_[i];
	}	
}

bool Board::operator!=(const Board& rhs) const{				//overload != operator
	if(size_ != rhs.getSize()){
		return true;
	}
	for(int i = 0; i < size_; i++){
		if(tiles_[i] != rhs.getTiles()[i]){
			return true;
		}
	} 
	
	return false;
}

int* Board::getTiles() const{
	return tiles_;
}

int Board::getSize() const{
	return size_;
}


