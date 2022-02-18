#include <iostream>

#include "List.h"
#include "Vector.h"

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
        out << "(empty)";
    else{
        auto itr = begin(c);

        out << "[ " << *itr++;

        while(itr  != end(c))
            out << ", " << *itr++;
        out << " ]" << endl;
    }    
}

int main(int argc, char **argv){

    List<int> list1;
    int x = 1;
    list1.push_back(x);
    list1.push_back(2);
    list1.push_back(10);
    print(list1);

    cout << list1.back() << endl;



    return 0;
}