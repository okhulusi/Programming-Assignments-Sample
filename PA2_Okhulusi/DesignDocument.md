# Omar Khulusi's Design Document for PA1: Clear and Concise

## Purpose/Overview

### *The purpose of this software is centered around User Information.  Here we track and connect Users with specified User information.  This is done using a simple GML format.  Overall, this software represents a simple social network.*

## Software Requirements/Function

 + Easily Track User Information
 
 	*-User information, that is all taken in through a GML file, is the most important part of this software.  We have here a list of users with information such as their name, age, zip code, and friends.  It would be relatively simple to add even more User information functionality.*
 	
 + Connect Users
 
 	*-Just as any social network does best, this software connects people.  The connections are all tracked in a vector and can easily be accessed and altered.*
 	
 + Take network information in using GML file format
 
 	*-Use a GML reader class to read in nodes and edges.  These nodes and edges represent all of the user information and the friend connections, respectively.  This information is then to be parsed into values that we can use to store user information.*
 	
 + Send network information out using GML file format
 
 	*-Use a GML writer class to write out nodes and edges.  This file that is output is formatted such that it can even be taken right back into the software as an input file.  This is useful so that we can easily send the information in a simple document to be processed elsewhere.*

## Classes

1. Main File (sn.cpp)
	+ The main file executed the program, essentially connecting all of the classes together
	+No methods other than the main method
	+No data members are used other than temporary variables, the most important three being:
		
	```C++
		vector<string> nodes;		//Stores all User information
		vector<string> edges;		//Stores all Friend connection information
		MyList<User*> list;		//Stores pointers to all of the users
	```
2. User File + User Header File (user.cpp, user.h)
	+ The User class and its header file serve to keep track of everything about a single user
	
	```C++
 		string name_;					//User Name
 		int age_;					//User Age
 		int zip_;					//User Zip Code
 		MyList<int> friendList_; 			//User Friend List
 		
 		string getName();
 		int getAge();
 		int getZip();
 		
	```
3. GML Reader + GML Reader Header File (gmlreader.cpp, gmlreader.h)
	+ Read in a GML file containing nodes and edges, representing user information and friend connections
	+ Only method is the read method:
	```C++
		bool read(const char *fn, vector<std::string>& nodes, vector<std::string>& edges);
	```
4. GML Writer + GML Writer Header File (gmlwriter.cpp, gmlwriter.h)
	+ Write out a GML file containing nodes and edges, representing user information and friend connections
	+ Only method is the write method:
	```C+
		void write(char *oFilename, MyList<User*> &list);	//Writes out all User information in a GML file
	```
5. Templated List class (mylist.h)
	+ Serves as a container for the User List and each User's friendList
	```C++
		//Major Methods
		void push_back(T val);		//Add a value T to the end of the list
		int size() const;		//Get the size of the list
		T& at(int loc) const;		//Get a value T at a location in the list
		bool remove(T val);		//Remove a value T from the list
		T pop(int loc);			//Remove and return a value T from the list
		
		//Major data (all private)
		int size_;			//size of the list
		int capacity_;			//capacity of the container
		T *data_;			//data array that the list holds
	```

## Global Data/Functions

*No global data or functions exist in this software.*

## High-level Architecture

1. GML reader will populate two vectors:
	+ Vector of Pointers to Users
		* A Vector of Pointers to Users will access all user information
	+ Vector of Integers
		* A Vector of Integers will store all friend connections
		
2. The vectors will then be parsed into the needed values
	+ Users will be created, with all of their information stored
	+ User connections will be stored in the user Friend Lists
	
3. GML Writer will output GML file with all User information, including friend connections

## User Interface

*All user information is entered into a GML file prior to using the software.  Therefore, the user does not technically interact with the software, with the exception of typing in the command line prompt.* 
No GUI is used for this software.
No controls buttons or other controls are necessary.
Thus, the user does not have to interact with the software.
Users do enter their name, age, and zip code.  However, this is done to the GML file.

##Test Cases

*Testing will occur constantly throughout development in addition to a series of tests when the code is completed.*
	+ The tests done after code completion will involving printing out all user information and friend connections
		* This ensures that they are established correctly  
		
##### Potential Problem Cases

If any of the user information is invalid, we need to catch the error.  This includes:
	1. A non-string Username
	2. A nonreal or nonexistent zip code
	3. A nonreal age
