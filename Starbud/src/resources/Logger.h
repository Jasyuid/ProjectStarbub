#pragma once

#include <iostream>
#include <Windows.h>

//Message Loggers
#define LOG(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); std::cout << x << std::endl;
#define LOGC(x, y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), y); std::cout << x << std::endl;
#define LOGN(x, y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); std::cout << x << ": " << y << std::endl;
#define LOGE(x, y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); std::cout << "ERROR~" << x << ": " << y << std::endl;