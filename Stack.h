#ifndef STACK_H
#define STACK_H

#include <List.h>
#include <Vector.h>
// TODO: 实现栈的list和vector版本

template <typename T>
class Stack_list{
    private:
        /* data */
    public:
        Stack_list(/* args */);
        ~Stack_list();

        void pop();
        Object top();
};


template <typename Object>
class Stack_vector{
    private:

    public:

};


#endif