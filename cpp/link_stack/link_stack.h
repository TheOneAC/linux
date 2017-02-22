#include <iostream>
#include <cstring> // include size_t 
using namespace std;
template<class T>
class node{
public:
	T data;
	node<T>* next;
	node(T d):data(d),next(NULL){};
};
template<class T>
class Stack{
private:
	size_t s;
	node<T>* head;
public:
	Stack(){}
	~Stack(){}
	void  operator=(const T& other){};
	T& top()const {};
	bool empty(){};
	size_t size(){};
	void push(const T&d){};
	void pop(){};
	//friend ostream & operator<<(ostream &os,const T& d){};
};
