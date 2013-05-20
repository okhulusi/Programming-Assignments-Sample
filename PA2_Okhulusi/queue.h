#ifndef QUEUE_H
#define QUEUE_H

#include "llist.h"
//Templated Queue Class
template <typename T>
class Queue : private LList<T>
{
	public:
		Queue();
		~Queue();
		int size() const;
		void push_back(const T& value);
		void pop_front();
		T& front();
		T& back();
		bool empty() const;
};

template <typename T>
Queue<T>::Queue():LList<T>(){}		

template <typename T>
Queue<T>:: ~Queue(){
	this->clear();
}

template <typename T>
int Queue<T>:: size() const{
	return this->size_;
}

template <typename T>
void Queue<T>:: push_back(const T& value){
	LList<T>::push_back(value);
}

template <typename T>
void Queue<T>:: pop_front(){
	if(this->size() <= 0){return;}
	LList<T>::pop_front();
}

template <typename T>
T& Queue<T>:: front(){
	if(this->size() == 0){ throw invalid_argument("Fail");}			
	return this->head_->val;
}

template <typename T>
T& Queue<T>:: back(){			
	return this->tail_->val;
}

template <typename T>
bool Queue<T>:: empty() const{
	return this->head_ == NULL;
}
#endif
