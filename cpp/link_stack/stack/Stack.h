#ifndef _STACK_H_
#define _STACK_H_
#include <exception>
#include <deque>
using namespace std;
template <class T,class se = deque<T> >
class Stack{
private:
	se s;
public:
	Stack():s(){}
	~Stack(){}
	void push(const T &elem){ s.push_back(elem);}
	void pop(){ s.pop_back();}
	T& top(){ return s.back();}
	const T& top()const {return s.back();}
	bool empty()const{ return s.empty();}
};

#endif