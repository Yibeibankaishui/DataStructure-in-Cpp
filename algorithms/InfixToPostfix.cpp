#include "Stack.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "utilities.h"


using namespace std;

double count_postfix_notation(vector<string> & token_vector){
        
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