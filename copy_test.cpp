#include <iostream>
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

int main()
{
    cout << "Hello, world!" << endl;
    return 0;
}