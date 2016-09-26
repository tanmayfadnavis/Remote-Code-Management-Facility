#ifndef WINDOWSHELPERS_H
#define WINDOWSHELPERS_H

/////////////////////////////////////////////////////////////////////////
// WindowsHelpers.h - I/O and Conversion helpers                       //
// ver 2.0                                                             //
//---------------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                      //
// All rights granted provided this copyright notice is retained       //
//---------------------------------------------------------------------//
// Application: OOD Projects #3, #4                                    //
// Platform:    Visual Studio 2013, Dell 2720, Win 8.1 pro             //
/////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

namespace WindowsHelpers
{
  std::string wstringToString(const std::wstring& wstr);
  std::wstring stringToWideString(const std::string& str);
  std::string GetLastMsg(bool wantSocketMessage);
}
 
#endif
