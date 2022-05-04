#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"

// TODO: queue的list和vector实现
template <typename Object>
class Queue{
    public:
        Queue();
        virtual ~Queue() { }
        virtual void EnQueue(const Object & element) = 0;
        virtual Object DeQueue() = 0;
    public:
        int currentSize;
};


// 队列，双链表实现
template <typename Object>
class Queue_list: public Queue<Object>, public List<Object>{
    public:
        Queue_list() : Queue<Object>(), List<Object>() {
            currentSize = 0;
        }
        ~Queue_list() {}

        void EnQueue(const Object & element) {
            List<Object>::push_back(element);
            currentSize++;
        }

        void EnQueue(Object && element) {
            List<Object>::push_back(std::move(element));
            currentSize++;
        }

        Object DeQueue() {
            // 判断是否空
            Object ret = List<Object>::front();
            List<Object>::pop_front();
            currentSize--;
            return ret;
        }
    
};


// 队列，循环数组实现
template <typename Object>
class Queue_vector: public Queue<Object>, public Vector<Object> {
    private:
        int front;
        int back;

    public:
        Queue_vector() : Queue<Object>(), Vector<Object>() {
            currentSize = 0;
            front = 0;
            back = 0;

        }
        ~Queue_vector() { }

        void EnQueue(const Object & element) {
            int Capacity = Vector::capacity();
            // 回转操作
            if (back == Capacity - 1) {
                if (currentSize < Capacity) {
                    back = 0;
                    
                }
                else {
                    Vector::resize(2 * Capacity + 1); 
                    back++;
                    
                }
            }
            // 第一次enqueue操作，queue为空
            if (currentSize == 0) && (back == front){
                *this[back] = element;
                return;
            }
            if (currentSize != 0) {
                back++;
            }
            
            *this[back] = element;
            currentSize++;

        }

        void EnQueue(Object && element) {
            
            currentSize++;
        }

        Object DeQueue() {
            int Capacity = Vector::capacity();
            // queue空
            if (currentSize == 0) {
                
            }
            // front在末尾
            if (front == Capacity - 1) {
                front = 0;
            }
            else {
                front++;
            }
            currentSize--;
            return *this[front];
        }

};


#endif