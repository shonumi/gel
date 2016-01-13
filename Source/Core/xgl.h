/****** XGL ******/
/****** Parse XGL Data From File ******/

#ifndef XGL
#define XGL

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool parse_xgl_string(std::string filename, std::vector <std::string>& contents);
bool parse_xgl_int(std::string filename, std::vector <int>& contents);
double numparse(std::string input);

#endif // XGL