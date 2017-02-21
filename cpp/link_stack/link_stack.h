#include <iostream>
#include <cstring> // include size_t 
template<class T>
class Stack{
private:
	struct node{
		T data;
		node* next;
		node(T d):data(d),next(NULL){};
	};
private:
	size_t s;
	node* head;
public:
	Stack(){};
	~Stack(){};
	T operator=(const T& other){};
	T& top(){};
	bool empty(){};
	size_t size(){};
	void push(const T d){};
	void pop(){};
	void swap(T& other){};
};
