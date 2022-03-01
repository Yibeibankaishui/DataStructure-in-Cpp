#ifndef STACK_H
#define STACK_H

#include "List.h"
#include "Vector.h"

template <typename Object>
class Stack{
    public:
        virtual ~Stack(){};
        virtual void push(const Object & element) = 0;
        virtual void pop() = 0;
        virtual Object & top() = 0;
};


// TODO: 实现栈的list和vector版本
// Stack_list 同时继承Stack 和 List
template <typename Object>
class Stack_list: public Stack<Object>, public ListSingle<Object>{      
    public:
        Stack_list(): Stack<Object>(), ListSingle<Object>(){}
        ~Stack_list(){}
        void push(const Object & element){
            ListSingle<Object>::push_front(element);
        }
        void push(Object && element){
            ListSingle<Object>::push_front(std::move(element));
        }
        void pop(){
            ListSingle<Object>::pop_front();
        }
        Object & top(){
            return ListSingle<Object>::front();
        }
};


template <typename Object>
class Stack_vector: public Stack<Object>, public Vector<Object>{
    public:
        Stack_vector(){}
        ~Stack_vector(){}
        void push(const Object & element){
            Vector<Object>::push_back(element);
        }
        void push(Object && element){
            Vector<Object>::push_back(element);
        }
        void pop(){
            Vector<Object>::pop_back();
        }
        Object & top(){
            return Vector<Object>::back();
        }

};


#endif