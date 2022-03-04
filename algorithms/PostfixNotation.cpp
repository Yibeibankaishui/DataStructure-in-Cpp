#include "Stack.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "utilities.h"


using namespace std;

double count_postfix_notation(vector<string> & token_vector){
    Stack_list<double> cal_stack{};

    for(auto token: token_vector){
        double numl, numr, token_num = 0;
        if(token == "+"){
            cal_stack.pop(numl);

            cal_stack.pop(numr);
 
            cal_stack.push(numl + numr);
        }
        else if(token == "-"){
            cal_stack.pop(numl);
            cal_stack.pop(numr);
            cal_stack.push(numl - numr);
        }
        else if(token == "*"){
            cal_stack.pop(numl);
            cal_stack.pop(numr);
            cal_stack.push(numl * numr);
        }
        else if(token == "/"){
            cal_stack.pop(numl);
            cal_stack.pop(numr);
            cal_stack.push(numl / numr);
        }
        else{
            // string -> double
            token_num = stod(token);
            cal_stack.push(token_num);
        }
        for(auto i : cal_stack){
            cout << i << "  ,  ";
        }
        cout << endl;
    }
    return cal_stack.top();         
}

int main(int argc, char **argv){

    string filename("../data/input_2.txt");
    ifstream input_file(filename);
    vector<string> token_vec{};
    if(file_to_token(input_file, token_vec)){
        double result = count_postfix_notation(token_vec);
        cout << result << endl;
    }


    return 0;
}