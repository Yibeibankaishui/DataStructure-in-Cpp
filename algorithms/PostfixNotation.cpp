#include "../Stack.h"
#include <iostream>
#include <fstream>


using namespace std;

double count_postfix_notation(ifstream & input_file){

    Stack_list<double> stack_count;
    if()

}

int main(int argc, char **argv){

    string filename("input.txt");

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }



    return 0;
}