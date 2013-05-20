#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "gmlreader.h"
#include "gmlwriter.h"
#include "user.h"
#include "mylist.h"
// Added appropriate headers here

using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 4){
    cerr << "Please provide the input GML file, command file, and output file" << endl;
    return 1;
  }
  
  GMLReader gmlReader;						//Initiate the GML reader for Input
  GMLWriter gmlWriter;						//Initiate the GML writer for output
  
  char *a1, *a2, *a3;
  a1 = argv[1];
  a2 = argv[2];							//Takes in and stores the command line arguments
  a3 = argv[3];

  vector<string> nodes;						//Instantiate the nodes and edges vectors to store input data
  vector<string> edges;
  if(gmlReader.read(a1,nodes,edges) != true){			//Read in the input data (w/ error checking)
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
  
  MyList<User*> list;
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
  		else { cout << "Line/Command not recognized" << endl;}
  	}
  	
  	if(failFlag == false){
  		User *user = new User();
  		
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

  ifstream ifile(a2);
  if(ifile.good()){
  	while(ifile.good()){							//Milestone E, adding/removing friends
									//as prompted by the .txt file
  		string action, u1, u2, u1first, u1last, u2first, u2last;
  		int u1ID, u2ID, u1Index, u2Index;
  		string val1;
  	
  		ifile >> action;
  		
  		bool user1Exists = false;					//used for Error checking later
  		bool user2Exists = false;
  		if(action.compare("a") == 0 || action.compare("r") == 0){			//Error Checking
  			ifile >> u1first >> u1last;				//Parses the names (not using a stringstream) 
  			u1 = u1first + " " + u1last;
  			if(u1 == " "){break;}
  			ifile >> u2first >> u2last;
  			u2 = u2first + " " + u2last;
  			u1.erase(u1.begin());
  			u1 = u1.substr(0, u1.size()-1);
  			u2.erase(u2.begin());
  			u2 = u2.substr(0,u2.size()-1);
  			cout << u1 << endl;
  			cout << u2 << endl;
  		
  			for(int i = 0; i < list.size(); i++){		
 //				cout << "List Name: " << list[i]->getName() << endl;		//Line used for testing
 //				cout << "U1: " << u1 << endl;					//Line used for testing
  				if((list[i]->getName()).compare(u1) == 0){
  					u1ID = list[i]->getID();			//See next comment
  					user1Exists = true;
  					u1Index = i;
  					break;
  				}	
  			}
  			for(int i = 0; i < list.size(); i++){				//Both for loops search list for pointer to user with	
  				if((list[i]->getName()).compare(u2) == 0){		//matching name as text file specifies
  					u2ID = list[i]->getID();
  					user2Exists = true;
  					u2Index = i;
  					break;
  				}
  			}
  			if(user1Exists == false || user2Exists == false){		//Error checking for nonexistant username
  				cout << "User does not exist" << endl;
  			}
  		}
  			
  		if(action.compare("a") == 0 && user1Exists == true && user2Exists == true){
  			cout << "U1ID " << u1ID << " U2ID " << u2ID << endl;		//Add Friend
  			cout << "U1Index: " << u1Index << " U2Index: " << u2Index << endl;
  			list[u1Index]->addFriend(u2ID);	
  			list[u2Index]->addFriend(u1ID);
  			cout << "Added Friend" << endl;
  		}
  		else if(action.compare("r") == 0 && user1Exists == true && user2Exists == true){
  									//Remove Friend
  			list[u1Index]->removeFriend(u2ID);
  			list[u2Index]->removeFriend(u1ID);
  			cout << "Removed Friend" << endl;
  		}
  	
  	}
 	 ifile.close();
  }
  else {cout << "Cannot open the command file" << endl;}				//Error Checking
					
//  for(int i = 0; i < list.size(); i++){							//Block used for testing
//  	cout << (*list[i]).getName() << endl;
//  }
  gmlWriter.write(a3, list);							//Writes to the output file specified in
  										//the third command line argument
  return 0;
}
