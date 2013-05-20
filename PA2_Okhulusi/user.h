#ifndef USER_H
#define USER_H
#include "mylist.h"

class User{

	public:
		User();
		User(string name, int age, int zip);
		~User();
		string getName();
		int getAge();
		int getZip();
		int getID();
		MyList<int>& getFriendList();
		
		void setName(string s);
		void setAge(int a);
		void setZip(int z);
		void setID(int i);
		void addFriend(int newFriend);
		void removeFriend(int friendID);
	private:
		string name_;
		int age_;
		int zip_;
		int id_;
		MyList<int> friendList_;

};
#endif
