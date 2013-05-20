#ifndef STACK_H
#define STACK_H

#include "llist.h"

template<typename T>
class Stack : private LList<T>
{
	public:
		Stack();
		~Stack();
		int size() const;
		void push(const T& value);
		void pop();
		T& top();
		bool empty() const;
};

template <typename T>
Stack<T>::Stack():LList<T>(){}	

template <typename T>
Stack<T>::~Stack(){ 
	this->clear();
}

template <typename T>
int Stack<T>:: size() const{
	return this->size_;
}

template <typename T>
void Stack<T>:: push(const T& value){
	this->push_back(value);
}

template <typename T>
void Stack<T>:: pop(){
	if(this->size() <= 0){return;}
	Item<T> *temp = this->head_;
	
	if(this->size() == 1){
		delete this->head_;
		this->head_ = NULL;
		this->tail_ = NULL;
	}
	
	else{
		for(int i = 0; i < this->size() - 2; i++){
			temp = temp->next;
		}
		delete this->tail_;
		this->tail_ = temp;
	}
	this->size_--;	
}

template <typename T>
T& Stack<T>:: top(){
	if(this->size() == 0){ throw invalid_argument("There is nothing in the stack.");}					
	return this->tail_->val;
}

template <typename T>
bool Stack<T>:: empty() const{
	return this->head_ == NULL;
}
#endif
