#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "gmlreader.h"
#include "gmlwriter.h"
#include "user.h"
#include "mylist.h"
#include "bcuser.h"
#include "stack.h"
#include "queue.h"
#include "llist.h"
#include "bcalg.h"
// Added appropriate headers here

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 3){
    cerr << "Please provide the input GML file, command file, and output file" << endl;
    return 1;
  }
  
  GMLReader gmlReader;						//Initiate the GML reader for Input
//  GMLWriter gmlWriter;						//Initiate the GML writer for output
  
  char *a1, *a2;
  a1 = argv[1];							//Takes in and stores the command line arguments
  a2 = argv[2];

  vector<string> nodes;						//Instantiate the nodes and edges vectors to store input data
  vector<string> edges;
  if(gmlReader.read(a1,nodes,edges) != true){			//Read in input data (w/ error checking)
  	cout << "Cannot open GML input file." << endl;
  	return 0;
  }
  
/*  for(unsigned int i = 0; i < nodes.size(); i++){				//Block used for testing
  	cout << nodes[i] << endl;
  }
  for(unsigned int i = 0; i < edges.size(); i++){
  	cout << edges[i] << endl;
  }
*/
  
  MyList<BCUser*> list;
  for(unsigned int i = 0; i < nodes.size(); i++){			//Milestone D, creating users and
  	int tempID = -1;
  	int tempAge = -1; 
  	int tempZip = -1;
  	string tempName = "Name Name";					//storing their information as needed
 	string sNew = nodes[i];
  	stringstream ss(sNew);		
  	string word;
  	bool failFlag = false;
  	
  	while(ss.good()){						//Each loop takes one line of input and reacts
  									//accordingly
  		getline(ss, word, ' ');					
  		 
  		if(word.compare("id") == 0){				//Sets ID of User
  			int idWord;
  			ss >> idWord;
  			if(ss.fail()){
  				cout << "Invalid ID" << endl;
  				failFlag = true;
  			}
 			else{
  				tempID = idWord;
  			}
  		}
  		else if(word.compare("name") == 0){			//Sets Name of User
  			string sWord;
  			getline(ss, sWord, '\"');
  			getline(ss, sWord, '\"');
  			if(ss.fail()){
  				failFlag = true;
  				cout << "Invalid name" << endl;
  			}
 			else{
  				tempName = sWord;
  			}
  		}
  		else if(word.compare("age") == 0){			//Sets Age of User
  			int ageWord;
  			ss >> ageWord;
  			if(ss.fail()){
  				failFlag = true;
  				cout << "Invalid age" << endl;
  				break;
  			}
  			else{
  				tempAge = ageWord;
  			}
  		}
  		else if(word.compare("zip") == 0){			//Sets Zip of User
  			int zipWord;
  			ss >> zipWord;
  			if(ss.fail()){
  				failFlag = true;
  				cout << "Invalid zip" << endl;
  			}
 			else{
  				tempZip = zipWord;
  			}
  		}
  	//	else { cout << "Line/Command not recognized" << endl;}
  	}
  	
  	if(failFlag == false){
  		BCUser *user = new BCUser();
  		
  		user->setID(tempID);
  		user->setName(tempName);
  		user->setAge(tempAge);
  		user->setZip(tempZip);
 
  		list.push_back(user);
  	}	
  }
  
  for(unsigned int i = 0; i < edges.size(); i++){				//Adding Friends
    	string sNew2 = edges[i];
  	stringstream ss2(sNew2);
  	string word2;
  	
  	while(ss2.good()){
  		getline(ss2, word2, ' ');
  		
  		if(word2.compare("source") == 0 || word2.compare("target") == 0){
  			int sourceID, targetID, sourceIndex, targetIndex;
  			bool u1Exists = false;
  			bool u2Exists = false;
  			if(word2.compare("source") == 0){				//Parses the Add friend edges (source/target)					//and adds them accordingly
  				ss2 >> sourceID;
  				getline(ss2, word2, ' ');
  				getline(ss2, word2, ' ');
  				ss2 >> targetID;
  				for(int i = 0; i < list.size(); i++){
  					if(list[i]->getID() == sourceID){
  						sourceIndex = i;
  						u1Exists = true;
  					}
  					if(list[i]->getID() == targetID){
  						targetIndex = i;
  						u2Exists = true;
  					}
  				}
  				if(u1Exists == true && u2Exists == true){
  					list[sourceIndex]->addFriend(targetID);
  	//				list[targetIndex]->addFriend(sourceID);
  				}
  				else { cout << "Invalid friend connection" << endl;}
  			}
  			else if(word2.compare("target") == 0){
  				ss2>>targetID;
  				getline(ss2, word2, ' ');
  				getline(ss2, word2, ' ');
  				ss2 >> sourceID;
    				for(int i = 0; i < list.size(); i++){
  					if(list[i]->getID() == sourceID){
  						sourceIndex = i;
  						u1Exists = true;
  					}
  					if(list[i]->getID() == targetID){
  						targetIndex = i;
  						u2Exists = true;
  					}
  				}
  				if(u1Exists == true && u2Exists == true){
  	//				list[sourceIndex]->addFriend(targetID);
  					list[targetIndex]->addFriend(sourceID);
  				}
  				else { cout << "Invalid friend connection" << endl;}
  			}
  			else{ cout << "Invalid input in GML edges" << endl;}
  				     
//  			cout << "source " << sourceID << endl;
//  			cout << "target " << targetID << endl;	
  		}
  	}
  }
	
	MyList<double> *score = BCAlg::computeBC(list);					//Calls the method that finds score
	
	for(int i = 0; i < list.size(); i++){
	//	cout << "BC unNormalized Score: " << list[i]->bc << endl;			//Used for testing
	}
	
	for(int i = 0; i < score->size();i++){
	//	cout << "BC Normalized Score: " << (*score)[i] << endl;
	}				
//  for(int i = 0; i < list.size(); i++){							//Block used for testing
//  	cout << (*list[i]).getName() << endl;
//  }
	
	ofstream ofile;
	ofile.open(argv[2]);
	
	if(ofile.fail()){
		cout << "Failed to open file" << endl;
	}
	else{
		for(int i = 0; i < score->size(); i++){					//File output 
			if(score->at(i) != -1){
				ofile << i << " ";
				ofile << score->at(i) << endl;
			}
		}
	}
	
	for(int i = 0; i < list.size(); i++){
		delete list[i];
	}
//  gmlWriter.write(a2, list);							//Writes to the output file specified in
  										//the third command line argument
  return 0;
}
