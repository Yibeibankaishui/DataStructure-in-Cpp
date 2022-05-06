// 中缀表达式转换为后缀表达式

#include "Stack.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "utilities.h"


using namespace std;

vector<string> Infix2Postfix(vector<string> & token_vector){
    Stack_list<string> cal_stack{};
    vector<string> ret_vector;
    string pop_element;

    for (auto token: token_vector) {
        if (token == "+") {
            while ((cal_stack.top() == "*") || (cal_stack.top() == "+")) {
                cal_stack.pop(pop_element);
                ret_vector.push_back(pop_element);
            }
            cal_stack.push(token);
        }
        else if (token == "*") {
            cal_stack.push(token);
        }
        else if (token == "(") {
            cal_stack.push(token);
        }
        else if (token == ")") {
            while (cal_stack.top() != "("){
                cal_stack.pop(pop_element);
                ret_vector.push_back(pop_element);
            }
            cal_stack.pop(pop_element);
        }
        else {
            ret_vector.push_back(token);
        }
    }  

    while (!cal_stack.empty()) {
        cal_stack.pop(pop_element);
        ret_vector.push_back(pop_element);
    }

    return ret_vector;          
}

int main(int argc, char **argv){

    string filename("../data/input_2.txt");
    ifstream input_file(filename);
    vector<string> token_vec{};
    if(file_to_token(input_file, token_vec)){
        vector<string> result = Infix2Postfix(token_vec);
        for (auto itr = result.begin(); itr != result.end(); itr++) {
            cout << *itr << endl;
        }
        
    }


    return 0;
}