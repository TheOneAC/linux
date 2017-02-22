#include "link_stack.h"

using namespace std;
int main(int argc, char const *argv[])
{
	Stack< int > mystack;
	for(int i = 0; i < 10; i++)mystack.push(i  );
	for(int i = 0;i < 10; i++)
  	{  
   	  	cout << mystack.top() << " ";
    	mystack.pop();
  	}
  	cout << endl;
	return 0;
}