#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>


int file_to_token(std::ifstream & input_file, std::vector<std::string> & dst_vector);

#endif