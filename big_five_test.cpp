#include <iostream>
#include <utility>
using namespace std;

class IntCell{
    public:
        explicit IntCell(int initialValue = 0){
            storedValue = new int{initialValue};
        }
        
        // ~IntCell(){
        //     delete storedValue;
        // }

        int read() const{
            return *storedValue;
        }

        void write(int x){
            *storedValue = x;
        }

    private:
        int *storedValue;
};


class IntCell2{
    public:
        explicit IntCell2(int initialValue = 0){
            storedValue = new int{initialValue};
        }

        ~IntCell2(){
            delete storedValue;
        }

        IntCell2(const IntCell2 & rhs){
            storedValue = new int{*rhs.storedValue};
        }

        IntCell2(IntCell2 && rhs): storedValue{rhs.storedValue}{
            rhs.storedValue = nullptr;
        }

        IntCell2 & operator= (const IntCell2 & rhs){
            if(this != &rhs)
                *storedValue = *rhs.storedValue;
            return *this;
        }

        IntCell2 & operator= (IntCell2 && rhs){
            std::swap(storedValue, rhs.storedValue);
            return *this;
        }

        int read() const { return *storedValue;}

        void write(int x){*storedValue = x;}

    private:
         int *storedValue;
};


int f(){
    IntCell2 a{2};
    IntCell2 b = a;
    IntCell2 c;

    c = b;
    a.write(4);
    cout << a.read() << endl << b.read() << endl << c.read() << endl;
    return 0;
}

int main()
{
    cout << "Hello, world!" << endl;
    f();
    return 0;
}