#include <iostream>
#include <vector>
#include <string>
#include "bcuser.h"

using namespace std;

BCUser:: BCUser(): User(){
	dist = -1;
	numsp = 0;
	delta = 0;
	bc = 0;
	
	preds = new MyList<int>;
}

BCUser:: ~BCUser(){
	delete preds;
}


