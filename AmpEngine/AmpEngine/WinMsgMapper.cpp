#include "WinMsgMapper.h"

// special messages definitions
#define WM_UAHDESTROYWINDOW 0x0090
#define WM_UAHDRAWMENU      0x0091
#define WM_UAHDRAWMENUITEM  0x0092
#define WM_UAHINITMENU      0x0093
#define WM_UAHMEASUREMENUITEM 0x0094
#define WM_UAHNCPAINTMENUPOPUP 0x0095

// define register message macro to turn message into a string literal using # operator
#define REGISTER_MESSAGE( msg ) { msg, #msg }

// register messages in constructor using initializer list
WinMsgMapper::WinMsgMapper( ) :
    m_map( {
    REGISTER_MESSAGE( WM_ACTIVATE ),
    REGISTER_MESSAGE( WM_ACTIVATEAPP ),
    REGISTER_MESSAGE( WM_CANCELJOURNAL ),
    REGISTER_MESSAGE( WM_CANCELMODE ),
    REGISTER_MESSAGE( WM_CHARTOITEM ),
    REGISTER_MESSAGE( WM_CHILDACTIVATE ),
    REGISTER_MESSAGE( WM_CLOSE ),
    REGISTER_MESSAGE( WM_COMMNOTIFY ),
    REGISTER_MESSAGE( WM_COMPACTING ),
    REGISTER_MESSAGE( WM_COMPAREITEM ),
    REGISTER_MESSAGE( WM_COPYDATA ),
    REGISTER_MESSAGE( WM_CREATE ),
    REGISTER_MESSAGE( WM_DELETEITEM ),
    REGISTER_MESSAGE( WM_DESTROY ),
    REGISTER_MESSAGE( WM_DEVMODECHANGE ),
    REGISTER_MESSAGE( WM_DRAWITEM ),
    REGISTER_MESSAGE( WM_ENABLE ),
    REGISTER_MESSAGE( WM_ENDSESSION ),
    REGISTER_MESSAGE( WM_ERASEBKGND ),
    REGISTER_MESSAGE( WM_FONTCHANGE ),
    REGISTER_MESSAGE( WM_GETFONT ),
    REGISTER_MESSAGE( WM_GETHOTKEY ),
    REGISTER_MESSAGE( WM_GETMINMAXINFO ),
    REGISTER_MESSAGE( WM_GETOBJECT ),
    REGISTER_MESSAGE( WM_GETTEXT ),
    REGISTER_MESSAGE( WM_GETTEXTLENGTH ),
    REGISTER_MESSAGE( WM_ICONERASEBKGND ),
    REGISTER_MESSAGE( WM_KILLFOCUS ),
    REGISTER_MESSAGE( WM_MEASUREITEM ),
    REGISTER_MESSAGE( WM_MOUSEACTIVATE ),
    REGISTER_MESSAGE( WM_MOVE ),
    REGISTER_MESSAGE( WM_NEXTDLGCTL ),
    REGISTER_MESSAGE( WM_NULL ),
    REGISTER_MESSAGE( WM_PAINT ),
    REGISTER_MESSAGE( WM_PAINTICON ),
    REGISTER_MESSAGE( WM_POWER ),
    REGISTER_MESSAGE( WM_QUERYDRAGICON ),
    REGISTER_MESSAGE( WM_QUERYENDSESSION ),
    REGISTER_MESSAGE( WM_QUERYOPEN ),
    REGISTER_MESSAGE( WM_QUEUESYNC ),
    REGISTER_MESSAGE( WM_QUIT ),
    REGISTER_MESSAGE( WM_SETCURSOR ),
    REGISTER_MESSAGE( WM_SETFOCUS ),
    REGISTER_MESSAGE( WM_SETFONT ),
    REGISTER_MESSAGE( WM_SETHOTKEY ),
    REGISTER_MESSAGE( WM_SETREDRAW ),
    REGISTER_MESSAGE( WM_SETTEXT ),
    REGISTER_MESSAGE( WM_SHOWWINDOW ),
    REGISTER_MESSAGE( WM_SIZE ),
    REGISTER_MESSAGE( WM_SPOOLERSTATUS ),
    REGISTER_MESSAGE( WM_SYSCOLORCHANGE ),
    REGISTER_MESSAGE( WM_TIMECHANGE ),
    REGISTER_MESSAGE( WM_VKEYTOITEM ),
    REGISTER_MESSAGE( WM_WINDOWPOSCHANGED ),
    REGISTER_MESSAGE( WM_WINDOWPOSCHANGING ),
    REGISTER_MESSAGE( WM_WININICHANGE ),
        } ) {
}

WinMsgMapper::~WinMsgMapper( ) {
}

std::string WinMsgMapper::operator()( DWORD msg, LPARAM pMapLparam, WPARAM pMapWparam ) const {
    // format message string into readable format
    constexpr int FIRST_COL_WIDTH = 25;
    const auto msgKey = m_map.find( msg );

    // setup ostream to format message string
    std::ostringstream oss;
    // check if message is in map and format message string
    if ( msgKey != m_map.end( ) ) {
        oss << std::left << std::setw( FIRST_COL_WIDTH ) << msgKey->second << std::right;
    }
    else {
        std::ostringstream ossHex;
        ossHex << "Unknown message: 0x" << std::hex << std::uppercase << msg;
        oss << std::left << std::setw( FIRST_COL_WIDTH ) << ossHex.str( ) << std::right;
    }

    // format known messages into readable format
    oss << "  PMAPLPARAM: 0x" << std::hex << std::setfill( '0' ) << std::uppercase << std::setw( 8 ) << pMapLparam;
    oss << "  PMAPWPARAM: 0x" << std::hex << std::setfill( '0' ) << std::uppercase << std::setw( 8 ) << pMapWparam << std::endl;

    // return formatted message string
    return oss.str( );
}
