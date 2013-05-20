#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "gmlwriter.h"
#include "mylist.h"

using namespace std;

GMLWriter:: GMLWriter(){}

GMLWriter:: ~GMLWriter(){}

void GMLWriter:: write(char *oFilename, MyList<BCUser*> &list)
{
	ofstream oFile;							//Instantiate output filestream
	oFile.open(oFilename);
	
	for(int i = 0; i < list.size(); i++){				//Each loop Outputs one user's information
		oFile << "node [" << endl;
		oFile << " id " << (*list[i]).getID() << endl;
		oFile << " name " << '\"' << (*list[i]).getName() << '\"' << endl;
		oFile << " age " << (*list[i]).getAge() << endl;
		oFile << " zip " << (*list[i]).getZip() << endl;
		oFile << "]" << endl;	
	}
	
	for(int i = 0; i < list.size(); i++){				//Each loop outputs one "edge", or friend connection		
		for(int j = 0; j < list.at(i)->getFriendList().size(); j++){		//Two edges = one FC (to go both ways)
				oFile << "edge [" << endl;
				oFile << " source " << i << endl;
				oFile << " target " << list.at(i)->getFriendList().at(j) << endl;
				oFile << "]" << endl; 
		}
	}

	oFile.close();
}

void GMLWriter:: write(char *oFilename, MyList<User*> &list)
{
	ofstream oFile;							//Instantiate output filestream
	oFile.open(oFilename);
	
	for(int i = 0; i < list.size(); i++){				//Each loop Outputs one user's information
		oFile << "node [" << endl;
		oFile << " id " << (*list[i]).getID() << endl;
		oFile << " name " << '\"' << (*list[i]).getName() << '\"' << endl;
		oFile << " age " << (*list[i]).getAge() << endl;
		oFile << " zip " << (*list[i]).getZip() << endl;
		oFile << "]" << endl;
	}
	
	for(int i = 0; i < list.size(); i++){				//Each loop outputs one "edge", or friend connection		
		for(int j = 0; j < list.at(i)->getFriendList().size(); j++){		//Two edges = one FC (to go both ways)
				oFile << "edge [" << endl;
				oFile << " source " << list[i]->getID() << endl;
				oFile << " target " << list.at(i)->getFriendList().at(j) << endl;
				oFile << "]" << endl; 
		}
	}

	oFile.close();
}
