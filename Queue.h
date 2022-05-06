#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"
#include "Vector.h"
#include <exception>

// TODO: queue的list和vector实现
template <typename Object>
class Queue{
    public:
        virtual ~Queue() { }
        virtual void EnQueue(const Object & element) = 0;
        virtual Object DeQueue() = 0;

};


// 队列，双链表实现
template <typename Object>
class Queue_list: public Queue<Object>, public List<Object>{
    public:
        int currentSize;

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
        int currentSize;
    
    private:
        class QueueEmptyException : public std::exception {
            virtual const char *what() const throw() { 
                return "Queue is Empty ";
                }
        };

        // TODO : iterator
    public:
        class const_iterator{
            public:
                const_iterator(): curIdx(0), theQueue(nullptr) { }
                const_iterator(int id, const Queue_vector<Object> & queue): curIdx(id), theQueue(&queue) { }

                const Object & operator*() const {
                    return theQueue->operator[](curIdx);
                }

                // prefix ++
                const_iterator & operator++() {
                    curIdx++;
                    int capacity = theQueue->capacity();
                    if (curIdx >= capacity) {
                        curIdx = 0;
                    }
                    return *this;
                }

                // postfix ++
                const_iterator operator++(int) {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }

                bool operator==(const const_iterator & rhs) const {
                    return curIdx == rhs.curIdx;
                }

                bool operator!=(const const_iterator & rhs) const {
                    return !(*this == rhs);
                }

            protected:
                int curIdx;

                const Queue_vector<Object> * theQueue;

        };

        class iterator : public const_iterator {
            public:
                iterator() { }
                iterator(int idx, const Queue_vector<Object> & queue) : const_iterator(idx, queue) { }

                Object & operator*() {
                    return const_iterator::theQueue->operator[](const_iterator::curIdx);
                }

                const Object & operator*() const {
                    return const_iterator::operator*();
                }

                iterator & operator++() {
                    const_iterator::curIdx++;
                    int capacity = const_iterator::theQueue->capacity();
                    if (const_iterator::curIdx >= capacity) {
                        const_iterator::curIdx = 0;
                    }
                    return *this;
                }

                iterator & operator++(int) {
                    iterator old = *this;
                    ++(*this);
                    return old;
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
            int Capacity = Vector<Object>::capacity();
            // queue 满
            if (currentSize == Capacity) {
                if (back <= front) {
                    Vector<Object>::reserve(2 * currentSize);
                    for (int k = front; k < currentSize; k++) {
                        this->operator[](k + currentSize) = std::move(this->operator[](k));
                    }
                }
                else {
                    Vector<Object>::reserve(2 * currentSize);
                }
                Capacity = 2 * currentSize;
            }

            // 第一次enqueue操作，queue为空
            if ((currentSize == 0) && (back == front)){
                this->operator[](back) = element;
                currentSize++;
                return;
            }
            // 回转操作
            if (back == Capacity - 1) {
                back = 0;
            }
            else if (currentSize != 0) {
                back++;
            }
            
            this->operator[](back) = element;
            currentSize++;

        }

        void EnQueue(Object && element) {
            int Capacity = Vector<Object>::capacity();
            // queue 满
            if (currentSize == Capacity) {
                if (back <= front) {
                    Vector<Object>::reserve(2 * currentSize);
                    for (int k = front; k < currentSize; k++) {
                        this->operator[](k + currentSize) = std::move(this->operator[](k));
                    }
                }
                else {
                    Vector<Object>::reserve(2 * currentSize);
                }
                Capacity = 2 * currentSize;
            }

            // 第一次enqueue操作，queue为空
            if ((currentSize == 0) && (back == front)){
                this->operator[](back) = std::move(element);
                currentSize++;
                return;
            }
            // 回转操作
            if (back == Capacity - 1) {
                back = 0;
            }
            else if (currentSize != 0) {
                back++;
            }
            
            this->operator[](back) = std::move(element);
            currentSize++;
        }

        Object DeQueue() {
            int Capacity = Vector<Object>::capacity();
            // queue空
            if (currentSize == 0) {
                throw QueueEmptyException { };
            }
            Object ret = this->operator[](front);
            // front在末尾
            if (front == Capacity - 1) {
                front = 0;
            }
            else {
                front++;
            }
            currentSize--;
            std::cout << ret << std::endl;
            return ret;
        }

        bool empty() const{
            return currentSize == 0;
        }


        // 获取首指针
        iterator begin(){
            return {front, *this};
        }

        const_iterator begin() const{
            return {front, *this};
        }

        // 获取末指针
        iterator end(){
            iterator itr{back, *this};
            return ++itr;
        }

        const_iterator end() const{
            const_iterator itr{back, *this};
            return ++itr;
        }

};


#endif