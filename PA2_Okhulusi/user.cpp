#include <iostream>
#include <string>
#include "user.h"
#include "mylist.h"

User:: User()						//Default user Constructor
{
	name_ = " ";
	age_ = 0;
	zip_ = 00000;
	MyList<int> friendList_;
	id_ = -1;
}

User:: User(string name, int age, int zip)		//User constructor setting name/age/zip
{
	name_ = name;
	age_ = age;
	zip_ = zip;
	MyList<int> friendList_;
}

User:: ~User(){}					//User destructor

string User:: getName()					//Five getter functions: name, age, zip, id, friendlist (respectively)			
{
	return name_;
}

int User:: getAge()
{
	return age_;
}

int User:: getZip()
{
	return zip_;
}

int User:: getID(){
	return id_;
}

MyList<int>& User:: getFriendList(){
	return friendList_;
}

void User:: setName(string s)				//Four setter functions: name/age/zip/id (respectively)
{
	name_ = s;
}

void User:: setAge(int a)
{
	age_ = a;
}

void User:: setZip(int z)
{
	zip_ = z;
}

void User:: setID(int i){
	id_ = i;
}

void User:: addFriend(int newFriend){			//Adds friend ID to back of friendList
	friendList_.push_back(newFriend);
}

void User:: removeFriend(int friendID){			//Removes friend ID from friendList if it exists there
	friendList_.remove(friendID);
}
