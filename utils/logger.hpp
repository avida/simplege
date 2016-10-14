#pragma once

#include <iostream>
#include <stdlib.h>

#include <boost/format.hpp>

#define COLORED

#ifdef COLORED

#define RED_COLOR "\033[1;31m"
#define GREEN_COLOR "\033[2;32m"
#define END_COLOR "\033[0m"

#else 

#define RED_COLOR ""
#define GREEN_COLOR ""
#define END_COLOR ""

#endif

namespace gl
{
using namespace std;

template <class T> 
void Log(const T& msg)
{
    cout << GREEN_COLOR <<  msg << END_COLOR << endl;
}

template <class T>
void LogFatal(const T& msg)
{
    cout << RED_COLOR << msg << END_COLOR << endl;
    exit(0);
}

}