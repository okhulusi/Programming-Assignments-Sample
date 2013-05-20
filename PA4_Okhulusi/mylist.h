#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

const int DEFAULT_LIST_SIZE = 10;

/** The MyList class is used particularly in this assignment to store the solution_list in puzzlesolver.cpp.  It
*   is a templated container for any type T
*/
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

/** Overloads the operator [] to be able to access values at a certain index
*   @param input An index of the requested value T in the list
*   @return Reference to a value T in the list
*/
template <typename T>
T& MyList<T>::operator[](int input){				//overloads the [] operator
	return (*this).at(input); 
}

/** Default MyList constructor, dynamically allocating the array, setting size to 0, and using a default capacity
*/
template <typename T>
MyList<T>::MyList()						//Default MyList constructor
{
	size_ = 0;
	capacity_ = DEFAULT_LIST_SIZE;
	data_ = new T[capacity_];
}

/** MyList constructor, dynamically allocating the array, setting size to 0, and using a given capacity.
*   @param capacity Capacity of the array
*/
template <typename T>
MyList<T>::MyList(int capacity)					//MyList constructor w/ specified capacity
{
	size_ = 0;
	capacity_ = capacity;
	data_ = new T[capacity_];
}

/** Destructor for the MyList.  Deletes the dynamically allocated array data_
*/
template <typename T>
MyList<T>::~MyList()						//Destructor
{
	delete [] data_;
}

/** Pushes a value to the end of the list
*   @param val Any val of type T designated when instantiating the MyList
*   @return nothing
*/
template <typename T>
void MyList<T>::push_back(T val)							
{
	if(size_ < capacity_){
		data_[size_++] = val;
	}
	else{
		capacity_ *= 2;
		T *tempList = new T[capacity_];			//Creates a new list twice the size if capacity is exceeded
		for(int i = 0; i < size_; i++){			//and populates it with all of the data in the old one
			tempList[i] = data_[i];
		}
		tempList[size_++] = val; 
		
		delete [] data_;
		data_ = tempList;
	}
}

/** Accessor method for the size of the MyList
*   @return size_ Size of the list
*/
template <typename T>
int MyList<T>::size() const					//Returns list size					
{
		return size_;
}

/** Gets the value at the specified index location.  Called in the [] operator overload
*   @param loc Location of the item in the list
*   @return A reference to the item in the list of type T
*/
template <typename T>	
T& MyList<T>::at(int loc) const						
{
	if(loc < 0 || loc >= size_){throw invalid_argument("Invalid Argument");}
	return data_[loc];
}

/** Removes first value from the list with specified value val if it exists
*   @param val Value to be removed
*   @return true if value exists in list, false otherwise
*/
template <typename T>
bool MyList<T>::remove(T val)					
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

/** Removes and returns value at specified index location (loc)
*   @param loc Location of value to be popped from list
*   @return value at index loc
*/
template <typename T>
T MyList<T>::pop(int loc)						
{
	T val = at(loc);
	remove(val);
	return val;
}

#endif
