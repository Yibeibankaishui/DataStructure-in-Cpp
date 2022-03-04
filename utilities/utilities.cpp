#include "utilities.h"

using namespace std;

int file_to_token(ifstream & input_file, vector<string> & dst_vector){
    string token;
    if (!input_file.is_open()) {
        cerr << "Could not open the file" << endl;
        return 0;
    }
    while(input_file >> token) {
        dst_vector.push_back(token);
    }
    if(dst_vector.empty())
        return 0;
    return 1;
}

// int main(int argc, char **argv){

//     string filename("../algorithms/input_2.txt");
//     ifstream input_file(filename);
//     vector<string> token_vec{};
//     if(file_to_token(input_file, token_vec)){
//         cout << token_vec.size() << endl;
//     }
//     for (auto token: token_vec){
//         cout << token << endl;
//     }
//     return 0;
// }