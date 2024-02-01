#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <Windows.h>

class WinMsgMapper {
public:
    // constructor and destructor
    WinMsgMapper( );
    ~WinMsgMapper( );

public:
    // public methods
    std::string operator( )( DWORD msg, LPARAM pMapLparam, WPARAM pMapWparam ) const;

private:
    // private attributes
    std::unordered_map<DWORD, std::string> m_map;
};
