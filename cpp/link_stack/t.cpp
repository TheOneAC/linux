#include <iostream>
using namespace std;
template<class T>
class Stack
{
private:
    struct Link
    {
        T data_;
        Link *next_;
        Link(T data, Link *next) : data_(data), next_(next)
        {

        }
    };

public:
    Stack() : head_(0), size_(0)
    {

    }

    ~Stack()
    {
        Link *tmp;
        while (head_)
        {
            tmp = head_;
            head_ = head_->next_;
            delete tmp;
        }
    }

    void Push(const T data)
    {
        Link *node = new Link(data, head_);
        head_ = node;
        ++size_;
    }

    bool Empty()
    {
        return (size_ == 0);
    }

    bool Pop(int &data)
    {
        if (Empty())
        {
            return false;
        }

        Link *tmp = head_;
        data = head_->data_;
        head_ = head_->next_;
        delete tmp;
        --size_;

        return true;
    }

private:
    Link *head_;
    int size_;
};

// 避免名称冲突
// 类型的扩充
// 数据封装、能够保护内部的数据结构不遭受外界破坏


int main(void)
{
    Stack<int> stack;        // 抽象数据类型  类类型
    int i;
    for (i = 0; i < 5; i++)
    {
        stack.Push(i);      // this = &stack
    }

    while (!stack.Empty())
    {
        stack.Pop(i);
        cout << i << " ";
    }

    cout << endl;

    return 0;
}