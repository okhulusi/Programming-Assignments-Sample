#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "pmminlist.h"
#include "puzzle_move.h"

using namespace std;

int main(int argc, char *argv[])
{

  /** @mainpage Omar Khulusi's Programming Assignment 3
      @section purpose Purpose/Overview
        The purpose of this assignment is to create a puzzle game.  This puzzle game can be won by moving any tile
        adjacent to the blank tile (O) until all values are sorted. In other words, in order to win the puzzle game 
        one must place all values in order from 1 to the maximum number from left to right, top to bottom.  To win, one
        can call a cheat that implements an efficient algorithm called the A* algorithm, giving the correct move order.    
        Furthermore, various lists are created in the process, and the idea of a "game state" is introduced.  
     
      @section requirements Requirements
        1) puzzlesolver.cpp/h or equivalent (runs A* algorithm), 
        2) puzzle_heur.cpp/h or equivalent (gives heuristic values), 
        3) pmminlist.cpp/h + mylist.h or equivalent (container to keep track of "best case scenario", sorting by heuristic), 
        4) board.cpp/h or equivalent (board object that holds all data to be manipulated, the base of the game), 
        5) puzzlemove.cpp/h or equivalent (stores and manipulates potential board states), 
        6) main() method.
        
        @author Omar Khulusi
  */
  if(argc < 4){
    cerr << "Usage: ./puzzle size initMoves seed" << endl;
    return 1;
  }

  int size, initMoves, seed;

  size = atoi(argv[1]);
  initMoves = atoi(argv[2]);
  seed = atoi(argv[3]);

  Board b(size,initMoves,seed);
  
  while(!b.solved()){
  	int input;
  	cout << endl;
  	cout << b << endl;
  	
  	cout << "Enter tile number to move or -1 for a cheat: ";
  	cin >> input;
  	cout << endl;
  	
  	if(input == -1){
  	
  		ManhattanHeuristic *puzzleHeuristic = new ManhattanHeuristic();
  //		OutOfPlaceHeuristic *puzzleHeuristic = new OutOfPlaceHeuristic();
  		
  		PuzzleSolver *solver = new PuzzleSolver(b);
  		solver->run(puzzleHeuristic);
  		
  		cout << "Try this sequence: ";
  		for(int i = (solver->getSolutionList()).size()-1; i >= 0; i--){	//Prints out backwards because solution pushed back
  			cout << (solver->getSolutionList())[i] << " ";
  		}
  		cout << endl;
  		cout << "(Expansions = " << solver->getNumExpansions() << ") " << endl;
  		cout << endl;
  		
  		delete solver;
  		delete puzzleHeuristic;
  	}
  	
  	if(cin.fail()){
  		cin.clear();
  		cin.ignore(1024, '\n');
  		cout << "Invalid input.  Enter a valid number." << endl;
  		continue;
  	} else if(input >=size || input == 0 || input <= -1){
  		cout << "Number out of range. Enter a valid number." << endl;
  	}
  	
  	if(input != -1){
  		b.move(input);
  	}
  	
  }
  
  cout << "You Win!" << endl;

  return 0;
}
