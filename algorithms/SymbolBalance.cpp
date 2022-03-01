#include "../Stack.h"
#include <iostream>
#include <fstream>

using namespace std;


bool symbol_balance(ifstream & input_file){
    Stack_list<char> stack_1;
    char byte;
    while(input_file.get(byte)){
        // cout << byte << endl;
        if(byte == '(' || byte == '[' || byte == '{'){
            stack_1.push(byte);
        }
        else{
            if ((stack_1.empty() == true) || (byte == ')' && stack_1.top() != '(') || (byte == ']' && stack_1.top() != '[') || (byte == '}' && stack_1.top() != '{'))
                return false;
            else if(byte != ' ') 
                stack_1.pop();
        }
    }
    return stack_1.empty();
}

int main(int argc, char ** argv){
    // read files
    string filename("input.txt");

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    cout << symbol_balance(input_file);

    return 0;
}