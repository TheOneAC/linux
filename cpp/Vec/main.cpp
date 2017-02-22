#include <iostream>
#include "vec.h"
using namespace std;
class test{
public:
	test(){
		cout << "default constructor...." << endl;
	}
	test(const test& rhs){
		cout  << "copy constructor..." << endl;
	}
	~test(){
		cout  << "destructor..." << endl;
	}
};
int main(int argc, char const *argv[])
{
	vec<int>v;
	for(int i = 0; i < 3; i++){
		//test t;
		v.push_back(i);
	}
	return 0;
}