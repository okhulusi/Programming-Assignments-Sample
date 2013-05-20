#include "puzzle_heur.h"
#include <cmath>

int ManhattanHeuristic::compute(int *tiles, int size){
	int h_ = 0;

	for(int i = 0; i < size; i++){
		if(tiles[i] != 0 && tiles[i] != i){
			int xValOriginalLoc = i%((int)sqrt(size));
			int yValOriginalLoc = i/((int)sqrt(size));
			int xValCorrectLoc = tiles[i]%((int)sqrt(size));
			int yValCorrectLoc = tiles[i]/((int)sqrt(size));

			h_+=abs(xValCorrectLoc-xValOriginalLoc) + abs(yValCorrectLoc-yValOriginalLoc);
		}
	}

	return h_;
}

int OutOfPlaceHeuristic::compute(int *tiles, int size){
	int distance = 0;
	
	for(int i = 0; i < size; i++){
		if(tiles[i] != i && tiles[i] != 0){
			distance++;
		}
	}
	
	return distance;
}
