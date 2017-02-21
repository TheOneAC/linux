#include "link_stack.h"
template<class T>
Stack::Stack():s(0),head(NULL){};
template<class T>
Stack::~Stack(){
	node* tmp;
	while(head != NULL){
		tmp = head;
		head = head->next;
		delete(tmp);
	}
}
template<class T>
T& operator=(const T & other){
	data = other.data;
	return data;
};
template<class T>
T& Stack::top(){	return head->data;}
template<class T>
size_t Stack::size(){ return size;}
template<class T>
bool Stack::empty(){ return size == 0;}
template<class T>
void Stack::push(const T d){
	node* tmp = new node(d);
	assert(tmp != NULL);
	tmp -> next = head;
	head = tmp;
	++size;
}
template<class T>
void Stack::pop(){ 
	if(s <= 0)return;
	node* tmp = head;
	head = head->next;
	free(tmp);
	--size;
	return ;
}
template<class T>
void Stack::swap(T& other){
	if(data == other)return;
	T tmp = data;
	data = other;
	other = data;
	return;
}
