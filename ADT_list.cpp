#include <iostream>
#include <chrono>
#include <iterator>
#include <vector>
#include <list>

using namespace std;
using namespace chrono;


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


template <typename Container>
void removeEveryOtherItem(Container& lst){
    auto itr = lst.begin();

    while(itr != lst.end()){
        itr = lst.erase(itr);
        if(itr != lst.end())
            ++itr;
    }
}


template <typename Container, typename Object>
void change(Container& c, const Object& newValue){
    typename Container::iterator itr = c.begin();
    while(itr != c.end()){
        *itr++ = newValue;
    }

}


int main(int argc, char **argv)
{
    list<int> list_test = list<int>{1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11};
    vector<int> vector_test = vector<int>{1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11,1,2,3,4,5,6,7,8,9,10,11};

    auto start = system_clock::now();

    // code here (counting time)
    removeEveryOtherItem(list_test);
    print(list_test);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "time :  " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "  s" << endl;

    return 0;
}