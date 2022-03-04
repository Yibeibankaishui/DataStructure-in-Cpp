#include <iostream>

#include "List.h"
#include "Vector.h"
#include "Stack.h"

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
    int pop1;
    int pop2;
    // Stack_vector<double> stack_2;
    print(stack_1);
    stack_1.push(1);
    print(stack_1);
    stack_1.push(2);
    print(stack_1);
    stack_1.push(3);
    print(stack_1);
    stack_1.push(8);
    print(stack_1);
    stack_1.pop(pop1);
    print(stack_1);
    stack_1.push(21);
    print(stack_1);
    stack_1.push(30);
    print(stack_1);
    // cout << stack_1.top() << endl;
    // print(stack_1);
    stack_1.pop(pop2);
    print(stack_1);
    cout << pop1 << "    " << pop2 << endl;

    return 0;
}