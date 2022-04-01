#ifndef QUEUE_H
#define QUEUE_H


// TODO: queue的list和vector实现
template <typename Object>
class Queue{
    public:
    Queue();
    virtual ~Queue();
    virtual EnQueue() = 0;
    virtual QuQueue() = 0;
};


template <typename Object>
class Queue_list: public Queue<Object>{

};


template <typename Object>
class Queue_vector: public Queue<Object>{

};


#endif