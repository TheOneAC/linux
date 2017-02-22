#include "Stack.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main(void)
{
    /*Stack<int> s;*/
    Stack<string > s;
    s.push("hello");
    s.push("zero");
    s.push("world");

    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    return 0;
}