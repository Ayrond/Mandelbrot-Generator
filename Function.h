#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <string>
#include <map>
#include <thread>
#include <sstream>
#include <iostream>
#include <ctime>

#define TRACE_INPUT() std::cout << "Call: " << __PRETTY_FUNCTION__ << std::endl;
#define TRACE_OUTPUT() std::cout << "Exit: " << __PRETTY_FUNCTION__ << std::endl;
#define TP() std::cout << "File: " << __FILE__ << ":" << __LINE__ << std::endl;


std::string get_data_pWidth_Height();
std::string get_data_pWidth_Width();
std::string get_data_pItera_Itera();
std::string get_data_pItera_Mod();
std::string get_data_pWhere_x();
std::string get_data_pWhere_y();
std::string get_data_pWhere_Largeur();
std::string get_data_pFile_name();


void thread_function();

int stoint(std::string st);
double stodou(std::string st);
bool stobool(std::string st);

std::time_t chrono(std::time_t tref);
#endif // FUNCTION_H_INCLUDED
