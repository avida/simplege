#include "logger.hpp"
#ifdef COLORED
#ifdef WINDOWS

std::string win_term_color(int color)
{
   static bool isXterm = std::getenv("TERM") && std::string(std::getenv("TERM")) == "xterm";
   if (isXterm)
   {
      switch (color)
      {
         case FOREGROUND_RED:
            return XTERM_RED_COLOR;
         case FOREGROUND_GREEN:
            return XTERM_GREEN_COLOR;
         case 0:
            return XTERM_END_COLOR;
         default:
            return "";
      }
   }
   else
   {
      static HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hConsole, color);
   }
   return "";
}
#endif
#endif