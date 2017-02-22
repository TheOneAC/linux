#include "link_stack.h"

template<class T>
Stack < T >::Stack():s(0),head(NULL){
	cout << "stack init" << endl;
};
template<class T>
Stack < T >:: ~Stack(){
	node<T>* tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		delete(tmp);
	}
}
/*template<class T>
void stack<T>:: operator=(const T & other){
	data = other.data;
};*/
template<class T>
T& Stack < T >::top()const {	return head->data;}
template<class T>
size_t Stack < T >::size(){ return size;}
template<class T>
bool Stack < T >::empty(){ return size == 0;}
template<class T>
void Stack < T >::push(const T &d){
	node<T>* tmp = new node(d);
	//std::cout << d << "hello";
	assert(tmp != NULL);
	tmp -> next = head;
	head = tmp;
	++size;
}
template<class T>
void Stack < T >::pop(){ 
	if(s <= 0)return;
	node<T>* tmp = head;
	head = head->next;
	free(tmp);
	--size;
	return ;
}
template<class T>
void Stack < T >::swap(T& other){
	if(data == other)return;
	T tmp = data;
	data = other;
	other = data;
	return;
}
ostream& operator<<(ostream &os,const T& d){
	os << d;
	return os;
}
