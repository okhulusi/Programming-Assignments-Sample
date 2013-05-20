#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int DEFAULT_LIST_SIZE = 10;

template <typename T>
class MyList{						//Function prototypes and data names
	public:
		T& operator[](int input);  
		MyList();
		MyList(int capacity);
		~MyList();
		void push_back(T val);
		int size() const;
		T& at(int loc) const;
		
		bool remove(T val);
		T pop(int loc);
	private:
		int size_;
		int capacity_;
		T *data_;	
};

template <typename T>
T& MyList<T>::operator[](int input){				//overloads the [] operator
	return (*this).at(input); 
}

template <typename T>
MyList<T>::MyList()						//Default MyList constructor
{
	size_ = 0;
	capacity_ = DEFAULT_LIST_SIZE;
	data_ = new T[capacity_];
}
template <typename T>
MyList<T>::MyList(int capacity)					//MyList constructor w/ specified capacity
{
	size_ = 0;
	capacity_ = capacity;
	data_ = new T[capacity_];
}
template <typename T>
MyList<T>::~MyList()						//Destructor
{
	delete [] data_;
}
template <typename T>
void MyList<T>::push_back(T val)				//Pushes a value to the end of the list				
{
	if(size_ < capacity_){
		data_[size_++] = val;
	}
	else{
		T *tempList = new T[capacity_*2];		//Creates a new list twice the size if capacity is exceeded
		for(int i = 0; i < size_; i++){			//and populates it with all of the data in the old one
			tempList[i] = data_[i];
		}
		tempList[size_++] = val; 
		
		delete [] data_;
		data_ = tempList;
	}
}
template <typename T>
int MyList<T>::size() const					//Returns list size					
{
		return size_;
}
template <typename T>	
T& MyList<T>::at(int loc) const					//returns value at specified index location (loc)			
{
	if(loc < 0 || loc >= size_){throw 1;}
	return data_[loc];
}

template <typename T>
bool MyList<T>::remove(T val)					//Removes first value from list with specified val if it exists		
{
	for(int i = 0; i < size(); i++){
		if(data_[i] == val){
			for(int j = i; j < size_; j++){
				data_[j] = data_[j+1];
			}
			size_--;
			return true;
		}
	}
	cout << "Nothing to be removed." << endl;
	return false;
}

template <typename T>
T MyList<T>::pop(int loc)					//Removes and returns value at specified index location (loc)			
{
	T val = at(loc);
	remove(val);
	return val;
}

#endif
