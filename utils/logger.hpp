#pragma once

#include <iostream>
#include <stdlib.h>

#include <boost/format.hpp>

#define WINDOWS
#define COLORED
#ifdef COLORED
   #define XTERM_RED_COLOR "\033[1;31m"
   #define XTERM_GREEN_COLOR "\033[2;32m"
   #define XTERM_END_COLOR "\033[0m"
#ifdef WINDOWS
   #include "windows.h"
   std::string win_term_color(int color);

   #define RED_COLOR win_term_color(FOREGROUND_RED)
   #define GREEN_COLOR win_term_color(FOREGROUND_GREEN)
   #define END_COLOR win_term_color(1)
#else
   #define RED_COLOR XTERM_RED_COLOR
   #define GREEN_COLOR XTERM_GREEN_COLOR
   #define END_COLOR XTERM_END_COLOR
#endif
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