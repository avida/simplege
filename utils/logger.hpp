#pragma once

#include <iostream>
#include <stdlib.h>

namespace gl
{
using namespace std;

template <class T> 
void Log(const T& msg)
{
    cout << msg << endl;
}

template <class T>
void LogFatal(const T& msg)
{
    cout << msg << endl;
    exit(0);
}

}