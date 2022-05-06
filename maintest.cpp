#include <iostream>

#include "List.h"
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

template <typename Container>
auto begin(Container& c) -> decltype(c.begin()){
    return c.begin();
}


template <typename Container>
auto end(Container& c) -> decltype(c.end()){
    return c.end();
}

template <typename Container>
void print(const Container& c, ostream& out = cout){
    if (c.empty())
        out << "(empty)" << endl;
    else{
        auto itr = begin(c);

        out << "[ " << *(itr++);

        while(itr != end(c))
            out << ", " << *(itr++);
        out << " ]" << endl;
    }    
}

int main(int argc, char **argv){

    ListSingle<int> list1;

    Stack_list<int> stack_1;

    Queue_vector<int> queue_1;
    Queue_list<int> queue_2;
    queue_1.EnQueue(1);
    print(queue_1);
    queue_1.EnQueue(7);
    queue_1.EnQueue(8);
    queue_1.EnQueue(11);
    print(queue_1);
    queue_1.DeQueue();
    print(queue_1);
    queue_1.DeQueue();
    queue_1.DeQueue();
    queue_1.DeQueue();
    
    // cout << pop1 << "    " << pop2 << endl;

    return 0;
}