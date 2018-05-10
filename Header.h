#pragma once
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <queue>
#include <clocale>
#include <windows.h>





void readFile(std::string &filepath);
void revizor();
void writeToFile(std::string& filepath);
