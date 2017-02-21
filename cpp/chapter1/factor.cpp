#include <iostream>
using namespace std;
template <class T>
struct plus{
	T operator()(const T&x, const T& y)const {return x+y;};
};
struct minus{
	T operator()(const T&x, const T& y)const {return x-y;};
};
int main(){
	plus<int> plusobj;
	minus<int>minusobj;
	// using in commom function style
	cout << plusobj(3,5) << endl;
	cout << minusobj(3,5) << endl;
	// create temporary object and using factor funtion style 
	cout << plusobj()(3,5) << endl;
	cout << plusobj()(3,5) << endl;
}
