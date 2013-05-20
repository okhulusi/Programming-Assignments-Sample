#include <iostream>
#include "mylist.h"
#include "bcuser.h"
#include "bcalg.h"
#include "llist.h"
#include "stack.h"
#include "queue.h"

MyList<double>* BCAlg:: computeBC(MyList<BCUser*> &userList){
										//BC Algorithm Execution
 	for(int i = 0; i < userList.size(); i++){				
		userList[i]->bc = 0;
	}

	for(int s = 0; s < userList.size(); s++){							
		for(int t = 0; t < userList.size(); t++){				
			delete userList[t]->preds;
			userList[t]->preds = new MyList<int>;

			userList[t]->numsp = 0;
			userList[t]->dist = -1;
			userList[t]->delta = 0.0;
		}

		userList[s]->numsp = 1;					
		userList[s]->dist = 0;

		Stack<BCUser*> myStack;				
		Queue<BCUser*> myQueue;				
		myQueue.push_back(userList[s]);

		while(!myQueue.empty()){				//BFS searching
			BCUser *v = myQueue.front();
			myQueue.pop_front();

			myStack.push(v);

			for(int w = 0; w < v->getFriendList().size(); w++){
				BCUser *doubleU = userList[v->getFriendList()[w]];			
				if(doubleU->dist == -1){
					myQueue.push_back(doubleU);
					doubleU->dist = v->dist + 1;
				}
				if(doubleU->dist == v->dist + 1){
					doubleU->numsp = doubleU->numsp + v->numsp;
					doubleU->preds->push_back(v->getID());		
				}
			}
		}
		while(!myStack.empty()){
			BCUser *w = myStack.top();
			myStack.pop();

			for(int v = 0; v < w->preds->size(); v++){	
				userList[w->preds->at(v)]->delta = userList[w->preds->at(v)]->delta + (userList[w->preds->at(v)]->numsp*1.0)/(w->numsp)*(1+w->delta);
			}
			w->bc = w->bc + w->delta;
		}

	}
	
	MyList<double> *normals = new MyList<double>();					//Normalize scores below
	double minScore = userList[0]->bc;
	double maxScore = userList[0]->bc;
	
	for(int i = 0; i < userList.size(); i++){					//Initializes normal values
		normals->push_back(-1);
	}
	for(int i = 1; i < userList.size(); i++){					//Finds min score
		if(userList[i]->bc < minScore) { minScore = userList[i]->bc; }
	}
	for(int i = 1; i < userList.size(); i++){
		if(userList[i]->bc > maxScore) { maxScore = userList[i]->bc; }		//Finds max score
	}
	
	for(int i = 0; i < userList.size(); i++){
		(*normals)[userList[i]->getID()] = userList[i]->bc;
	}
	for(int i = 0; i < normals->size(); i++){
		normals->at(i) = (normals->at(i) - minScore)/(maxScore-minScore);	//Finishes calculation
	}

	return normals;
}




