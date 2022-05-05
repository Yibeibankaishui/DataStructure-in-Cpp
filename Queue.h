#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"
#include <exception>

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
    
    private:
        class QueueEmptyException : public std::exception {
            virtual const char *what() const throw() { 
                return "Queue is Empty ";
                }
        };

    public:
        Queue_vector() : Queue<Object>(), Vector<Object>() {
            currentSize = 0;
            front = 0;
            back = 0;

        }
        ~Queue_vector() { }

        void EnQueue(const Object & element) {
            int Capacity = Vector::capacity();
            // queue 满
            if (currentSize == Capacity) {
                if (back <= front) {
                    Vector::reserve(2 * currentSize);
                    for (int k = front; k < currentSize; k++) {
                        *this[k + currentSize] = std::move(*this[k]);
                    }
                }
                else {
                    Vector::reserve(2 * currentSize);
                }
                Capacity = 2 * currentSize;
            }

            // 第一次enqueue操作，queue为空
            if (currentSize == 0) && (back == front){
                *this[back] = element;
                return;
            }
            // 回转操作
            if (back == Capacity - 1) {
                back = 0;
            }
            else if (currentSize != 0) {
                back++;
            }
            
            *this[back] = element;
            currentSize++;

        }

        void EnQueue(Object && element) {
            // queue 满
            if (currentSize == Capacity) {
                if (back <= front) {
                    Vector::reserve(2 * currentSize);
                    for (int k = front; k < currentSize; k++) {
                        *this[k + currentSize] = std::move(*this[k]);
                    }
                }
                else {
                    Vector::reserve(2 * currentSize);
                }
                Capacity = 2 * currentSize;
            }

            // 第一次enqueue操作，queue为空
            if (currentSize == 0) && (back == front){
                *this[back] = std::move(element);
                return;
            }
            // 回转操作
            if (back == Capacity - 1) {
                back = 0;
            }
            else if (currentSize != 0) {
                back++;
            }
            
            *this[back] = std::move(element);
            currentSize++;
        }

        Object DeQueue() {
            int Capacity = Vector::capacity();
            // queue空
            if (currentSize == 0) {
                throw QueueEmptyException { };
            }
            Object ret = *this[front];
            // front在末尾
            if (front == Capacity - 1) {
                front = 0;
            }
            else {
                front++;
            }
            currentSize--;
            return ret;
        }

};


#endif