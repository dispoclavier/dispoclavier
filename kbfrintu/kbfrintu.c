/*************************** C Module Header **************************************\
* CharSet=ANSI
* TabSetting=8
* ModuleName=kbfrintu.c
* Version=0.6.4.0
* LastEdited=
2018-07-16T1905+0200
*
* FileName="kbfrintu"
* FileDescription="FR-azerty with additions Keyboard Layout"
* Locale="fr-FR"
* ProductName="Prototypes for French standardization"
* ProductDescription="Prototypes for French standardization"
* Comments="Additional modifiers and toggles"
* ReleaseInformation="drivers compiled using MSKLC 1.4 and the included KbdUTool 3.40"
*
* Copyright1="© 1985..2001 Microsoft Corporation pro parte"
* Copyright2="© 2017..2018 marcel@dispoclavier.eu pro parte"
*
* FileHistory1="KBDTOOL v3.40 - Created  Sat Feb 17 08:59:15 2018"
* FileHistory2={
Mon Jul 16, 2018  updated quotation marks in compose (v0.6.4)
Sun Jul 15, 2018  catched up with kbfredis v0.6.3 (v0.6.3)
Thu Apr 14, 2018  permutated comma and period on Numbers
Thu Apr 12, 2018  moved group selector from spacebar to C05
Thu Apr 11, 2018  moved checkbox from Numbers to C01
Thu Apr 07, 2018  changed mappings rows B, C, D, and Numbers righthand
Thu Apr 05, 2018  changed mappings E06, E08 and more (version 0.5.0.0)
Mon Apr 02, 2018  changed mappings E06, E08 and more
Sat Mar 24, 2018  adjusted mapping B09, B10 (version 0.4.4)
Sat Mar 24, 2018  adjusted mapping C10 (version 0.4.3)
Thu Mar 22, 2018  improved mapping B09 (version 0.4.2)
Wed Mar 21, 2018  corrected errors (version 0.4.1)
Tue Mar 20, 2018  corrected mapping B10, C11..12, E01..10 (version 0.4.0)
Thu Mar 15, 2018  remapped punctuation and symbols (version 0.3.0)
Mon Mar 12, 2018  updated as "kbfrintu" for French prototyping
Fri Feb 23, 2018  updated tables and deadlist for CLDR #10851 (PRI #367)
Thu Feb 22, 2018  updated tables and deadlist for CLDR #10851 (PRI #367)
Wed Feb 21, 2018  updated tables and deadlist for CLDR #10851 (PRI #367)
Sat Feb 17, 2018  updated for CLDR #10851 (PRI #367) prototyping as "kbenintu"
}
\***************************************************************************/
#include <windows.h>
#include <kbd.h>
#include "kbfrintu.h"
#include "kbcommon.h"

#if defined(_M_IA64)
#pragma section(".data")
#define ALLOC_SECTION_LDATA __declspec(allocate(".data"))
#else
#pragma data_seg(".data")
#define ALLOC_SECTION_LDATA
#endif

/***************************************************************************\
* ausVK[] - Virtual Scan Code to Virtual Key conversion table
\***************************************************************************/

static ALLOC_SECTION_LDATA USHORT ausVK[] = {
    T00, T01, T02, T03, T04, T05, T06, T07,
    T08, T09, T0A, T0B, T0C, T0D, T0E, T0F,
    T10, T11, T12, T13, T14, T15, T16, T17,
    T18, T19, T1A, T1B, T1C, T1D, T1E, T1F,
    T20, T21, T22, T23, T24, T25, T26, T27,
    T28, T29, T2A, T2B, T2C, T2D, T2E, T2F,
    T30, T31, T32, T33, T34, T35,

    /*
     * Right-hand Shift key must have KBDEXT bit set.
     */
    T36 | KBDEXT,

    T37 | KBDMULTIVK,               // numpad_* + Shift/Alt -> SnapShot

    T38, T39, T3A, T3B, T3C, T3D, T3E,
    T3F, T40, T41, T42, T43, T44,

    /*
     * NumLock Key:
     *     KBDEXT     - VK_NUMLOCK is an Extended key
     *     KBDMULTIVK - VK_NUMLOCK or VK_PAUSE (without or with CTRL)
     */
    T45 | KBDEXT | KBDMULTIVK,

    T46 | KBDMULTIVK,

    /*
     * Number Pad keys:
     *     KBDNUMPAD  - digits 0-9 and decimal point.
     *     KBDSPECIAL - require special processing by Windows
     *                  but are DISABLED ON THIS LAYOUT.
     *                  ***The below is legacy.***
     */
    T47 | KBDNUMPAD | KBDSPECIAL,   // Numpad 7 (Home)
    T48 | KBDNUMPAD | KBDSPECIAL,   // Numpad 8 (Up),
    T49 | KBDNUMPAD | KBDSPECIAL,   // Numpad 9 (PgUp),
    T4A,
    T4B | KBDNUMPAD | KBDSPECIAL,   // Numpad 4 (Left),
    T4C | KBDNUMPAD | KBDSPECIAL,   // Numpad 5 (Clear),
    T4D | KBDNUMPAD | KBDSPECIAL,   // Numpad 6 (Right),
    T4E,
    T4F | KBDNUMPAD | KBDSPECIAL,   // Numpad 1 (End),
    T50 | KBDNUMPAD | KBDSPECIAL,   // Numpad 2 (Down),
    T51 | KBDNUMPAD | KBDSPECIAL,   // Numpad 3 (PgDn),
    T52 | KBDNUMPAD | KBDSPECIAL,   // Numpad 0 (Ins),
    T53 | KBDNUMPAD | KBDSPECIAL,   // Numpad . (Del),

    T54, T55, T56, T57, T58, T59, T5A, T5B,
    T5C, T5D, T5E, T5F, T60, T61, T62, T63,
    T64, T65, T66, T67, T68, T69, T6A, T6B,
    T6C, T6D, T6E, T6F, T70, T71, T72, T73,
    T74, T75, T76, T77, T78, T79, T7A, T7B,
    T7C, T7D, T7E

};

static ALLOC_SECTION_LDATA VSC_VK aE0VscToVk[] = {
        { 0x10, X10 | KBDEXT              },  // Speedracer: Previous Track
        { 0x19, X19 | KBDEXT              },  // Speedracer: Next Track
        { 0x1D, X1D | KBDEXT              },  // RControl
        { 0x20, X20 | KBDEXT              },  // Speedracer: Volume Mute
        { 0x21, X21 | KBDEXT              },  // Speedracer: Launch App 2
        { 0x22, X22 | KBDEXT              },  // Speedracer: Media Play/Pause
        { 0x24, X24 | KBDEXT              },  // Speedracer: Media Stop
        { 0x2E, X2E | KBDEXT              },  // Speedracer: Volume Down
        { 0x30, X30 | KBDEXT              },  // Speedracer: Volume Up
        { 0x32, X32 | KBDEXT              },  // Speedracer: Browser Home
        { 0x35, X35 | KBDEXT              },  // Numpad Divide
        { 0x37, X37 | KBDEXT              },  // Snapshot
        { 0x38, X38 | KBDEXT              },  // RMenu
        { 0x47, X47 | KBDEXT              },  // Home
        { 0x48, X48 | KBDEXT              },  // Up
        { 0x49, X49 | KBDEXT              },  // Prior
        { 0x4B, X4B | KBDEXT              },  // Left
        { 0x4D, X4D | KBDEXT              },  // Right
        { 0x4F, X4F | KBDEXT              },  // End
        { 0x50, X50 | KBDEXT              },  // Down
        { 0x51, X51 | KBDEXT              },  // Next
        { 0x52, X52 | KBDEXT              },  // Insert
        { 0x53, X53 | KBDEXT              },  // Delete
        { 0x5B, X5B | KBDEXT              },  // Left Win
        { 0x5C, X5C | KBDEXT              },  // Right Win
        { 0x5D, X5D | KBDEXT              },  // Application
        { 0x5F, X5F | KBDEXT              },  // Speedracer: Sleep
        { 0x65, X65 | KBDEXT              },  // Speedracer: Browser Search
        { 0x66, X66 | KBDEXT              },  // Speedracer: Browser Favorites
        { 0x67, X67 | KBDEXT              },  // Speedracer: Browser Refresh
        { 0x68, X68 | KBDEXT              },  // Speedracer: Browser Stop
        { 0x69, X69 | KBDEXT              },  // Speedracer: Browser Forward
        { 0x6A, X6A | KBDEXT              },  // Speedracer: Browser Back
        { 0x6B, X6B | KBDEXT              },  // Speedracer: Launch App 1
        { 0x6C, X6C | KBDEXT              },  // Speedracer: Launch Mail
        { 0x6D, X6D | KBDEXT              },  // Speedracer: Launch Media Selector
        { 0x1C, X1C | KBDEXT              },  // Numpad Enter
        { 0x46, X46 | KBDEXT              },  // Break (Ctrl + Pause)
        { 0,      0                       }
};

static ALLOC_SECTION_LDATA VSC_VK aE1VscToVk[] = {
        { 0x1D, Y1D                       },  // Pause
        { 0   ,   0                       }
};

/***************************************************************************\
* aVkToBits[]  - map Virtual Keys to Modifier Bits
*
* See kbd.h for a full description.
*
* This keyboard layout uses all eight modifier bits available on Windows.
* See kbd.h(52) and kbd.h(364). For names, see also kbcommon.h(382).
*
* 0x01  SHIFT      User control on LSHIFT, RSHIFT and CAPITAL (the toggle).
*                  KBDSHIFT   XOR   CAPLOK
*
* 0x02  CONTROL    User control on LCONTROL and RCONTROL
*                  Some control characters are allocated in the keyboard layout.
*
* 0x04  ALT        User control on LMENU and RMENU, unless RMENU is AltGr.
*                  For input of characters by code in conjunction with numpad.
*                  Emulates AltGr if pressed in combination with CONTROL.
*
* 0x08  KANA       User control on KANA modifier, and/or on KANA toggle.
*                  KBDKANA   OR   KANALOK
*                  Used as Programmer toggle, on E00 by default. (No modifier.)
*
* 0x10  ROYAYUBI   User control now on AltGr key (disambiguation with CTRL+ALT).
*                  Shifts to levels 1B and 2B.
*
* 0x20  LOYAYUBI   User control now on Numbers modifier, on B00 by default.
*                  Remapped to Left Alt using the built-in Scancode Mapper.
*                  (Alt to LWindows, Windows either on RWin, Apps, RCtrl, E00)
*
* 0x40  <no name>  User control now holding down the CapsLock key.
*                  Shifts to four levels allocated to scripts 2 and 3.
*
* 0x80  GRPSELTAP  User control now holding down the KanaLock key.
*                  Shifts to four levels allocated to scripts 4 and 5.
*
* This keyboard has no RMENU key, thus properly no AltGr key.
* But scan code T5E can be mapped to any key, like Applications, to get
* an AltGr again. Otherwise the few peripherical allocations are accessed
* using Control + Alt. See kbcommon.h(289).
*
* Modifiers are renamed in kbfrintu.h(52).
*
\***************************************************************************/
static ALLOC_SECTION_LDATA VK_TO_BIT aVkToBits[] = {
  { VK_SHIFT      , MODSHIFT   },  // 0x01 == 0000 0001
  { VK_CONTROL    , MODCTRL    },  // 0x02 == 0000 0010
  { VK_MENU       , MODALT     },  // 0x04 == 0000 0100
//{ /*none*/      , MODKANA    },  // 0x08 == 0000 1000 = KanaLock (Programmer)
  { VK_OEM_AX     , MODALTGR   },  // 0x10 == 0001 0000 = new on AltGr key
  { VK_OEM_WSCTRL , MODNUM     },  // 0x20 == 0010 0000 = Numbers modifier
  { VK_CAPITAL    , MODGREEK   },  // 0x40 == 0100 0000 = added on CapsLock
  { VK_KANA       , MODARAB    },  // 0x80 == 1000 0000 = added on KanaLock
  { 0             , 0          }
};

/***************************************************************************\
* aModification[]  - map character modifier bits to modification number
*
* See kbd.h for a full description.
*
* All shift states from Base through the highest used one must be enumerated
* in ascending order in this comma-separated list, where each shift state is
* represented either by the modification number that it is used in, or by
* the string "SHFT_INVALID".
*
* A huge majority of the theoretically available shift states cannot be used in
* practice, either because they are not implemented in the APIs, or because they
* are disabled. Some shift states result in a random mix of enabled and disabled
* keys, but most of them are entirely disabled.
* The following list shows some examples of shift states that cannot be used:
*     Kana + Right Oyayubi
*     Kana + Left Oyayubi
*     Right Oyayubi + Left Oyayubi
*     Shift + Group Selector
*     Kana + Group Selector
* However we double many shift states in these disabled shift states, hoping
* that this will make the mappings independent of the Kana toggle state.
* This turned out to be a working method, showing up by the way that some of
* these shift states are disabled when the modifier is used to access them,
* but not when the toggle is used.
* Additionally we doubled the Group Selector shift state on Shift + Grpselt,
* as well as on Kana + Grpselt and Shift + Kana + Grpselt, so that the end user
* may be in a position to make sure by himself what the disabling of higher
* Group Selector shift states on Windows is about.
*
* The Alternate Graphic modifier, used mostly as a third level chooser on
* ISO/IEC 9995 conformant keyboard layouts, or alternatively as a group selector
* as specified in the same standard, has been implemented on Windows by using the
* Control + Alt key combination.
*
* Some shift states must not be used for keyboard layouts to avoid interference
* with keyboard shortcuts and accelerator sequences. They include the Alt and
* Shift + Alt shift states. Some allocations in the Control and Shift + Control
* shift states are traditionally used to insert a few control characters or layout
* controls.
*
* Today the same concern about interference with application shortcuts applies to
* the Control + Alt combo, so that characters cannot be mapped safely on AltGr
* levels, especially on alphabetical keys. However AltGr and Shift + AltGr are
* the only additional shift states that can be submitted to the Caps Lock toggle.
* Therefore it is recommended not to map casing characters in other shift states
* than Base and Shift, and to use Kana and Shift + Kana as the next shift states,
* accessed using the Right Alt key, which ideally has its Kana modifier counterpart
* to the left of the space bar (performed by the Windows Scan Code Mapper).
*
*
* The list below must contain the modification number of each shift state in
* the line corresponding to the modifier combination(s).
* The modification number is found in the comment header of the allocation
* table.
* If a modifier should be optional (indifferent) in a given combination, the
* number of the corresponding shift state must be repeated once so that it
* stands both at the combination without and at the combination with that
* modifier.
*
\********************************************************************************************************************/
static ALLOC_SECTION_LDATA MODIFIERS CharModifiers = {
&aVkToBits[0],
255, // This # == decimal # of the last shift state that is not commented out.
     // The listing must be continuous until the last active one.
       {
// Column # in | Shift State| Modifier| Modifier Keys Pressed (or toggle active):      | Use:
// Alloc Table |  dec | hex |  Bits   | Shft  Ctrl  Alt   (Pro) AltGr Num   Greek Arab |
// ============| ====================================================================================================
0,            //    0  0x00  0000 0000
1,            //    1  0x01  0000 0001  x01
32,           //    2  0x02  0000 0010        x02
33,           //    3  0x03  0000 0011  x01 + x02
SHFT_INVALID, //    4  0x04  0000 0100              x04
SHFT_INVALID, //    5  0x05  0000 0101  x01 +       x04
SHFT_INVALID, //    6  0x06  0000 0110        x02 + x04
SHFT_INVALID, //    7  0x07  0000 0111  x01 + x02 + x04
4,            //    8  0x08  0000 1000                    x08
5,            //    9  0x09  0000 1001  x01 +             x08
32,           //   10  0x0a  0000 1010        x02 +       x08
33,           //   11  0x0b  0000 1011  x01 + x02 +       x08
SHFT_INVALID, //   12  0x0c  0000 1100              x04 + x08
SHFT_INVALID, //   13  0x0d  0000 1101  x01 +       x04 + x08
SHFT_INVALID, //   14  0x0e  0000 1110        x02 + x04 + x08
SHFT_INVALID, //   15  0x0f  0000 1111  x01 + x02 + x04 + x08
2,            //   16  0x10  0001 0000                          x10
3,            //   17  0x11  0001 0001  x01 +                   x10
SHFT_INVALID, //   18  0x12  0001 0010        x02 +             x10
SHFT_INVALID, //   19  0x13  0001 0011  x01 + x02 +             x10
SHFT_INVALID, //   20  0x14  0001 0100              x04 +       x10
SHFT_INVALID, //   21  0x15  0001 0101  x01 +       x04 +       x10
SHFT_INVALID, //   22  0x16  0001 0110        x02 + x04 +       x10
SHFT_INVALID, //   23  0x17  0001 0111  x01 + x02 + x04 +       x10
6,            //   24  0x18  0001 1000                    x08 + x10
7,            //   25  0x19  0001 1001  x01 +             x08 + x10
SHFT_INVALID, //   26  0x1a  0001 1010        x02 +       x08 + x10
SHFT_INVALID, //   27  0x1b  0001 1011  x01 + x02 +       x08 + x10
SHFT_INVALID, //   28  0x1c  0001 1100              x04 + x08 + x10
SHFT_INVALID, //   29  0x1d  0001 1101  x01 +       x04 + x08 + x10
SHFT_INVALID, //   30  0x1e  0001 1110        x02 + x04 + x08 + x10
SHFT_INVALID, //   31  0x1f  0001 1111  x01 + x02 + x04 + x08 + x10
8,            //   32  0x20  0010 0000                                x20
9,            //   33  0x21  0010 0001  x01 +                         x20
SHFT_INVALID, //   34  0x22  0010 0010        x02 +                   x20
SHFT_INVALID, //   35  0x23  0010 0011  x01 + x02 +                   x20
SHFT_INVALID, //   36  0x24  0010 0100              x04 +             x20
SHFT_INVALID, //   37  0x25  0010 0101  x01 +       x04 +             x20
SHFT_INVALID, //   38  0x26  0010 0110        x02 + x04 +             x20
SHFT_INVALID, //   39  0x27  0010 0111  x01 + x02 + x04 +             x20
12,           //   40  0x28  0010 1000                    x08 +       x20
13,           //   41  0x29  0010 1001  x01 +             x08 +       x20
SHFT_INVALID, //   42  0x2a  0010 1010        x02 +       x08 +       x20
SHFT_INVALID, //   43  0x2b  0010 1011  x01 + x02 +       x08 +       x20
SHFT_INVALID, //   44  0x2c  0010 1100              x04 + x08 +       x20
SHFT_INVALID, //   45  0x2d  0010 1101  x01 +       x04 + x08 +       x20
SHFT_INVALID, //   46  0x2e  0010 1110        x02 + x04 + x08 +       x20
SHFT_INVALID, //   47  0x2f  0010 1111  x01 + x02 + x04 + x08 +       x20
10,           //   48  0x30  0011 0000                          x10 + x20
11,           //   49  0x31  0011 0001  x01 +                   x10 + x20
SHFT_INVALID, //   50  0x32  0011 0010        x02 +             x10 + x20
SHFT_INVALID, //   51  0x33  0011 0011  x01 + x02 +             x10 + x20
SHFT_INVALID, //   52  0x34  0011 0100              x04 +       x10 + x20
SHFT_INVALID, //   53  0x35  0011 0101  x01 +       x04 +       x10 + x20
SHFT_INVALID, //   54  0x36  0011 0110        x02 + x04 +       x10 + x20
SHFT_INVALID, //   55  0x37  0011 0111  x01 + x02 + x04 +       x10 + x20
14,           //   56  0x38  0011 1000                    x08 + x10 + x20
15,           //   57  0x39  0011 1001  x01 +             x08 + x10 + x20
SHFT_INVALID, //   58  0x3a  0011 1010        x02 +       x08 + x10 + x20
SHFT_INVALID, //   59  0x3b  0011 1011  x01 + x02 +       x08 + x10 + x20
SHFT_INVALID, //   60  0x3c  0011 1100              x04 + x08 + x10 + x20
SHFT_INVALID, //   61  0x3d  0011 1101  x01 +       x04 + x08 + x10 + x20
SHFT_INVALID, //   62  0x3e  0011 1110        x02 + x04 + x08 + x10 + x20
SHFT_INVALID, //   63  0x3f  0011 1111  x01 + x02 + x04 + x08 + x10 + x20
20,           //   64  0x40  0100 0000                                      x40
21,           //   65  0x41  0100 0001  x01 +                               x40
SHFT_INVALID, //   66  0x42  0100 0010        x02 +                         x40
SHFT_INVALID, //   67  0x43  0100 0011  x01 + x02 +                         x40
SHFT_INVALID, //   68  0x44  0100 0100              x04 +                   x40
SHFT_INVALID, //   69  0x45  0100 0101  x01 +       x04 +                   x40
SHFT_INVALID, //   70  0x46  0100 0110        x02 + x04 +                   x40
SHFT_INVALID, //   71  0x47  0100 0111  x01 + x02 + x04 +                   x40
20,           //   72  0x48  0100 1000                    x08 +             x40
21,           //   73  0x49  0100 1001  x01 +             x08 +             x40
SHFT_INVALID, //   74  0x4a  0100 1010        x02 +       x08 +             x40
SHFT_INVALID, //   75  0x4b  0100 1011  x01 + x02 +       x08 +             x40
SHFT_INVALID, //   76  0x4c  0100 1100              x04 + x08 +             x40
SHFT_INVALID, //   77  0x4d  0100 1101  x01 +       x04 + x08 +             x40
SHFT_INVALID, //   78  0x4e  0100 1110        x02 + x04 + x08 +             x40
SHFT_INVALID, //   79  0x4f  0100 1111  x01 + x02 + x04 + x08 +             x40
22,           //   80  0x50  0101 0000                          x10 +       x40
23,           //   81  0x51  0101 0001  x01 +                   x10 +       x40
SHFT_INVALID, //   82  0x52  0101 0010        x02 +             x10 +       x40
SHFT_INVALID, //   83  0x53  0101 0011  x01 + x02 +             x10 +       x40
SHFT_INVALID, //   84  0x54  0101 0100              x04 +       x10 +       x40
SHFT_INVALID, //   85  0x55  0101 0101  x01 +       x04 +       x10 +       x40
SHFT_INVALID, //   86  0x56  0101 0110        x02 + x04 +       x10 +       x40
SHFT_INVALID, //   87  0x57  0101 0111  x01 + x02 + x04 +       x10 +       x40
22,           //   88  0x58  0101 1000                    x08 + x10 +       x40
23,           //   89  0x59  0101 1001  x01 +             x08 + x10 +       x40
SHFT_INVALID, //   90  0x5a  0101 1010        x02 +       x08 + x10 +       x40
SHFT_INVALID, //   91  0x5b  0101 1011  x01 + x02 +       x08 + x10 +       x40
SHFT_INVALID, //   92  0x5c  0101 1100              x04 + x08 + x10 +       x40
SHFT_INVALID, //   93  0x5d  0101 1101  x01 +       x04 + x08 + x10 +       x40
SHFT_INVALID, //   94  0x5e  0101 1110        x02 + x04 + x08 + x10 +       x40
SHFT_INVALID, //   95  0x5f  0101 1111  x01 + x02 + x04 + x08 + x10 +       x40
24,           //   96  0x60  0110 0000                                x20 + x40
25,           //   97  0x61  0110 0001  x01 +                         x20 + x40
SHFT_INVALID, //   98  0x62  0110 0010        x02 +                   x20 + x40
SHFT_INVALID, //   99  0x63  0110 0011  x01 + x02 +                   x20 + x40
SHFT_INVALID, //  100  0x64  0110 0100              x04 +             x20 + x40
SHFT_INVALID, //  101  0x65  0110 0101  x01 +       x04 +             x20 + x40
SHFT_INVALID, //  102  0x66  0110 0110        x02 + x04 +             x20 + x40
SHFT_INVALID, //  103  0x67  0110 0111  x01 + x02 + x04 +             x20 + x40
24,           //  104  0x68  0110 1000                    x08 +       x20 + x40
25,           //  105  0x69  0110 1001  x01 +             x08 +       x20 + x40
SHFT_INVALID, //  106  0x6a  0110 1010        x02 +       x08 +       x20 + x40
SHFT_INVALID, //  107  0x6b  0110 1011  x01 + x02 +       x08 +       x20 + x40
SHFT_INVALID, //  108  0x6c  0110 1100              x04 + x08 +       x20 + x40
SHFT_INVALID, //  109  0x6d  0110 1101  x01 +       x04 + x08 +       x20 + x40
SHFT_INVALID, //  110  0x6e  0110 1110        x02 + x04 + x08 +       x20 + x40
SHFT_INVALID, //  111  0x6f  0110 1111  x01 + x02 + x04 + x08 +       x20 + x40
SHFT_INVALID, //  112  0x70  0111 0000                          x10 + x20 + x40
SHFT_INVALID, //  113  0x71  0111 0001  x01 +                   x10 + x20 + x40
SHFT_INVALID, //  114  0x72  0111 0010        x02 +             x10 + x20 + x40
SHFT_INVALID, //  115  0x73  0111 0011  x01 + x02 +             x10 + x20 + x40
SHFT_INVALID, //  116  0x74  0111 0100              x04 +       x10 + x20 + x40
SHFT_INVALID, //  117  0x75  0111 0101  x01 +       x04 +       x10 + x20 + x40
SHFT_INVALID, //  118  0x76  0111 0110        x02 + x04 +       x10 + x20 + x40
SHFT_INVALID, //  119  0x77  0111 0111  x01 + x02 + x04 +       x10 + x20 + x40
SHFT_INVALID, //  120  0x78  0111 1000                    x08 + x10 + x20 + x40
SHFT_INVALID, //  121  0x79  0111 1001  x01 +             x08 + x10 + x20 + x40
SHFT_INVALID, //  122  0x7a  0111 1010        x02 +       x08 + x10 + x20 + x40
SHFT_INVALID, //  123  0x7b  0111 1011  x01 + x02 +       x08 + x10 + x20 + x40
SHFT_INVALID, //  124  0x7c  0111 1100              x04 + x08 + x10 + x20 + x40
SHFT_INVALID, //  125  0x7d  0111 1101  x01 +       x04 + x08 + x10 + x20 + x40
SHFT_INVALID, //  126  0x7e  0111 1110        x02 + x04 + x08 + x10 + x20 + x40
SHFT_INVALID, //  127  0x7f  0111 1111  x01 + x02 + x04 + x08 + x10 + x20 + x40
16,           //  128  0x80  1000 0000                                            x80
17,           //  129  0x81  1000 0001  x01 +                                     x80
SHFT_INVALID, //  130  0x82  1000 0010        x02 +                               x80
SHFT_INVALID, //  131  0x83  1000 0011  x01 + x02 +                               x80
SHFT_INVALID, //  132  0x84  1000 0100              x04 +                         x80
SHFT_INVALID, //  133  0x85  1000 0101  x01 +       x04 +                         x80
SHFT_INVALID, //  134  0x86  1000 0110        x02 + x04 +                         x80
SHFT_INVALID, //  135  0x87  1000 0111  x01 + x02 + x04 +                         x80
16,           //  136  0x88  1000 1000                    x08 +                   x80
17,           //  137  0x89  1000 1001  x01 +             x08 +                   x80
SHFT_INVALID, //  138  0x8a  1000 1010        x02 +       x08 +                   x80
SHFT_INVALID, //  139  0x8b  1000 1011  x01 + x02 +       x08 +                   x80
SHFT_INVALID, //  140  0x8c  1000 1100              x04 + x08 +                   x80
SHFT_INVALID, //  141  0x8d  1000 1101  x01 +       x04 + x08 +                   x80
SHFT_INVALID, //  142  0x8e  1000 1110        x02 + x04 + x08 +                   x80
SHFT_INVALID, //  143  0x8f  1000 1111  x01 + x02 + x04 + x08 +                   x80
18,           //  144  0x90  1001 0000                          x10 +             x80
19,           //  145  0x91  1001 0001  x01 +                   x10 +             x80
SHFT_INVALID, //  146  0x92  1001 0010        x02 +             x10 +             x80
SHFT_INVALID, //  147  0x93  1001 0011  x01 + x02 +             x10 +             x80
SHFT_INVALID, //  148  0x94  1001 0100              x04 +       x10 +             x80
SHFT_INVALID, //  149  0x95  1001 0101  x01 +       x04 +       x10 +             x80
SHFT_INVALID, //  150  0x96  1001 0110        x02 + x04 +       x10 +             x80
SHFT_INVALID, //  151  0x97  1001 0111  x01 + x02 + x04 +       x10 +             x80
18,           //  152  0x98  1001 1000                    x08 + x10 +             x80
19,           //  153  0x99  1001 1001  x01 +             x08 + x10 +             x80
SHFT_INVALID, //  154  0x9a  1001 1010        x02 +       x08 + x10 +             x80
SHFT_INVALID, //  155  0x9b  1001 1011  x01 + x02 +       x08 + x10 +             x80
SHFT_INVALID, //  156  0x9c  1001 1100              x04 + x08 + x10 +             x80
SHFT_INVALID, //  157  0x9d  1001 1101  x01 +       x04 + x08 + x10 +             x80
SHFT_INVALID, //  158  0x9e  1001 1110        x02 + x04 + x08 + x10 +             x80
SHFT_INVALID, //  159  0x9f  1001 1111  x01 + x02 + x04 + x08 + x10 +             x80
26,           //  160  0xa0  1010 0000                                x20 +       x80
27,           //  161  0xa1  1010 0001  x01 +                         x20 +       x80
SHFT_INVALID, //  162  0xa2  1010 0010        x02 +                   x20 +       x80
SHFT_INVALID, //  163  0xa3  1010 0011  x01 + x02 +                   x20 +       x80
SHFT_INVALID, //  164  0xa4  1010 0100              x04 +             x20 +       x80
SHFT_INVALID, //  165  0xa5  1010 0101  x01 +       x04 +             x20 +       x80
SHFT_INVALID, //  166  0xa6  1010 0110        x02 + x04 +             x20 +       x80
SHFT_INVALID, //  167  0xa7  1010 0111  x01 + x02 + x04 +             x20 +       x80
26,           //  168  0xa8  1010 1000                    x08 +       x20 +       x80
27,           //  169  0xa9  1010 1001  x01 +             x08 +       x20 +       x80
SHFT_INVALID, //  170  0xaa  1010 1010        x02 +       x08 +       x20 +       x80
SHFT_INVALID, //  171  0xab  1010 1011  x01 + x02 +       x08 +       x20 +       x80
SHFT_INVALID, //  172  0xac  1010 1100              x04 + x08 +       x20 +       x80
SHFT_INVALID, //  173  0xad  1010 1101  x01 +       x04 + x08 +       x20 +       x80
SHFT_INVALID, //  174  0xae  1010 1110        x02 + x04 + x08 +       x20 +       x80
SHFT_INVALID, //  175  0xaf  1010 1111  x01 + x02 + x04 + x08 +       x20 +       x80
SHFT_INVALID, //  176  0xb0  1011 0000                          x10 + x20 +       x80
SHFT_INVALID, //  177  0xb1  1011 0001  x01 +                   x10 + x20 +       x80
SHFT_INVALID, //  178  0xb2  1011 0010        x02 +             x10 + x20 +       x80
SHFT_INVALID, //  179  0xb3  1011 0011  x01 + x02 +             x10 + x20 +       x80
SHFT_INVALID, //  180  0xb4  1011 0100              x04 +       x10 + x20 +       x80
SHFT_INVALID, //  181  0xb5  1011 0101  x01 +       x04 +       x10 + x20 +       x80
SHFT_INVALID, //  182  0xb6  1011 0110        x02 + x04 +       x10 + x20 +       x80
SHFT_INVALID, //  183  0xb7  1011 0111  x01 + x02 + x04 +       x10 + x20 +       x80
SHFT_INVALID, //  184  0xb8  1011 1000                    x08 + x10 + x20 +       x80
SHFT_INVALID, //  185  0xb9  1011 1001  x01 +             x08 + x10 + x20 +       x80
SHFT_INVALID, //  186  0xba  1011 1010        x02 +       x08 + x10 + x20 +       x80
SHFT_INVALID, //  187  0xbb  1011 1011  x01 + x02 +       x08 + x10 + x20 +       x80
SHFT_INVALID, //  188  0xbc  1011 1100              x04 + x08 + x10 + x20 +       x80
SHFT_INVALID, //  189  0xbd  1011 1101  x01 +       x04 + x08 + x10 + x20 +       x80
SHFT_INVALID, //  190  0xbe  1011 1110        x02 + x04 + x08 + x10 + x20 +       x80
SHFT_INVALID, //  191  0xbf  1011 1111  x01 + x02 + x04 + x08 + x10 + x20 +       x80
30,           //  192  0xc0  1100 0000                                      x40 + x80
31,           //  193  0xc1  1100 0001  x01 +                               x40 + x80
SHFT_INVALID, //  194  0xc2  1100 0010        x02 +                         x40 + x80
SHFT_INVALID, //  195  0xc3  1100 0011  x01 + x02 +                         x40 + x80
SHFT_INVALID, //  196  0xc4  1100 0100              x04 +                   x40 + x80
SHFT_INVALID, //  197  0xc5  1100 0101  x01 +       x04 +                   x40 + x80
SHFT_INVALID, //  198  0xc6  1100 0110        x02 + x04 +                   x40 + x80
SHFT_INVALID, //  199  0xc7  1100 0111  x01 + x02 + x04 +                   x40 + x80
30,           //  200  0xc8  1100 1000                    x08 +             x40 + x80
31,           //  201  0xc9  1100 1001  x01 +             x08 +             x40 + x80
SHFT_INVALID, //  202  0xca  1100 1010        x02 +       x08 +             x40 + x80
SHFT_INVALID, //  203  0xcb  1100 1011  x01 + x02 +       x08 +             x40 + x80
SHFT_INVALID, //  204  0xcc  1100 1100              x04 + x08 +             x40 + x80
SHFT_INVALID, //  205  0xcd  1100 1101  x01 +       x04 + x08 +             x40 + x80
SHFT_INVALID, //  206  0xce  1100 1110        x02 + x04 + x08 +             x40 + x80
SHFT_INVALID, //  207  0xcf  1100 1111  x01 + x02 + x04 + x08 +             x40 + x80
SHFT_INVALID, //  208  0xd0  1101 0000                          x10 +       x40 + x80
SHFT_INVALID, //  209  0xd1  1101 0001  x01 +                   x10 +       x40 + x80
SHFT_INVALID, //  210  0xd2  1101 0010        x02 +             x10 +       x40 + x80
SHFT_INVALID, //  211  0xd3  1101 0011  x01 + x02 +             x10 +       x40 + x80
SHFT_INVALID, //  212  0xd4  1101 0100              x04 +       x10 +       x40 + x80
SHFT_INVALID, //  213  0xd5  1101 0101  x01 +       x04 +       x10 +       x40 + x80
SHFT_INVALID, //  214  0xd6  1101 0110        x02 + x04 +       x10 +       x40 + x80
SHFT_INVALID, //  215  0xd7  1101 0111  x01 + x02 + x04 +       x10 +       x40 + x80
SHFT_INVALID, //  216  0xd8  1101 1000                    x08 + x10 +       x40 + x80
SHFT_INVALID, //  217  0xd9  1101 1001  x01 +             x08 + x10 +       x40 + x80
SHFT_INVALID, //  218  0xda  1101 1010        x02 +       x08 + x10 +       x40 + x80
SHFT_INVALID, //  219  0xdb  1101 1011  x01 + x02 +       x08 + x10 +       x40 + x80
SHFT_INVALID, //  220  0xdc  1101 1100              x04 + x08 + x10 +       x40 + x80
SHFT_INVALID, //  221  0xdd  1101 1101  x01 +       x04 + x08 + x10 +       x40 + x80
SHFT_INVALID, //  222  0xde  1101 1110        x02 + x04 + x08 + x10 +       x40 + x80
SHFT_INVALID, //  223  0xdf  1101 1111  x01 + x02 + x04 + x08 + x10 +       x40 + x80
28,           //  224  0xe0  1110 0000                                x20 + x40 + x80
29,           //  225  0xe1  1110 0001  x01 +                         x20 + x40 + x80
SHFT_INVALID, //  226  0xe2  1110 0010        x02 +                   x20 + x40 + x80
SHFT_INVALID, //  227  0xe3  1110 0011  x01 + x02 +                   x20 + x40 + x80
SHFT_INVALID, //  228  0xe4  1110 0100              x04 +             x20 + x40 + x80
SHFT_INVALID, //  229  0xe5  1110 0101  x01 +       x04 +             x20 + x40 + x80
SHFT_INVALID, //  230  0xe6  1110 0110        x02 + x04 +             x20 + x40 + x80
SHFT_INVALID, //  231  0xe7  1110 0111  x01 + x02 + x04 +             x20 + x40 + x80
28,           //  232  0xe8  1110 1000                    x08 +       x20 + x40 + x80
29,           //  233  0xe9  1110 1001  x01 +             x08 +       x20 + x40 + x80
SHFT_INVALID, //  234  0xea  1110 1010        x02 +       x08 +       x20 + x40 + x80
SHFT_INVALID, //  235  0xeb  1110 1011  x01 + x02 +       x08 +       x20 + x40 + x80
SHFT_INVALID, //  236  0xec  1110 1100              x04 + x08 +       x20 + x40 + x80
SHFT_INVALID, //  237  0xed  1110 1101  x01 +       x04 + x08 +       x20 + x40 + x80
SHFT_INVALID, //  238  0xee  1110 1110        x02 + x04 + x08 +       x20 + x40 + x80
SHFT_INVALID, //  239  0xef  1110 1111  x01 + x02 + x04 + x08 +       x20 + x40 + x80
SHFT_INVALID, //  240  0xf0  1111 0000                          x10 + x20 + x40 + x80
SHFT_INVALID, //  241  0xf1  1111 0001  x01 +                   x10 + x20 + x40 + x80
SHFT_INVALID, //  242  0xf2  1111 0010        x02 +             x10 + x20 + x40 + x80
SHFT_INVALID, //  243  0xf3  1111 0011  x01 + x02 +             x10 + x20 + x40 + x80
SHFT_INVALID, //  244  0xf4  1111 0100              x04 +       x10 + x20 + x40 + x80
SHFT_INVALID, //  245  0xf5  1111 0101  x01 +       x04 +       x10 + x20 + x40 + x80
SHFT_INVALID, //  246  0xf6  1111 0110        x02 + x04 +       x10 + x20 + x40 + x80
SHFT_INVALID, //  247  0xf7  1111 0111  x01 + x02 + x04 +       x10 + x20 + x40 + x80
SHFT_INVALID, //  248  0xf8  1111 1000                    x08 + x10 + x20 + x40 + x80
SHFT_INVALID, //  249  0xf9  1111 1001  x01 +             x08 + x10 + x20 + x40 + x80
SHFT_INVALID, //  250  0xfa  1111 1010        x02 +       x08 + x10 + x20 + x40 + x80
SHFT_INVALID, //  251  0xfb  1111 1011  x01 + x02 +       x08 + x10 + x20 + x40 + x80
SHFT_INVALID, //  252  0xfc  1111 1100              x04 + x08 + x10 + x20 + x40 + x80
SHFT_INVALID, //  253  0xfd  1111 1101  x01 +       x04 + x08 + x10 + x20 + x40 + x80
SHFT_INVALID, //  254  0xfe  1111 1110        x02 + x04 + x08 + x10 + x20 + x40 + x80
SHFT_INVALID, //  255  0xff  1111 1111  x01 + x02 + x04 + x08 + x10 + x20 + x40 + x80
       }
};

/************************************************************************************************************************************************************************************************************************************************************\
* aVkToWch<n>[]  -  map Virtual Keys to Unicode Characters
*
* "Table attributes: Unordered Scan, null-terminated"
*
* "Search this table for an entry with a matching Virtual Key to find
* the corresponding unshifted and shifted WCHAR characters."
(END ORIGINAL COMMENT.)
*
* <n> is the number of shift states in a given allocation table.
*
* 'WCHAR', 'WCH' are short forms for 'Unicode code unit',
* as opposed to the 'UCHAR' which is a Unicode character.
* Windows being a UTF-16 operating system, UCHARs are represented using WCHARs.
* For the UCHARs of the Basic Multilingual Plane:
*      1 UCHAR = 1 WCHAR.
* Outside, that is in the Supplemental Multilingual Planes:
*      1 UCHAR = 2 WCHARs.
*
* WCHAR Values *************************************************************
*
* > Controls:
*   Tab, Backspace and Carriage Return are letters
*   preceded by a backslash, as '\t', '\b', '\r'.
*
* > ASCII Characters:
*   Values can be given in clear text, surrounded by single quotes.
*   The ', " and \ punctuations must be escaped with a backslash.
*
* > Non-ASCII Characters:
*   Values are in hexadecimal UTF-16, prefixed with 0x.
*   Not case-sensitive.
*   Characters of the SMP must be input as a sequence of two WCHARs,
*   and therefore are represented by a ligature (LGTR).
*
* Special Values ***********************************************************
*
*   | Text:     | Hex: |   (These two forms are equivalent.)
*
* > Special values for VirtualKey (column 1):
*     -1          0xff - This entry contains dead wchars and/or
*                         SGCaps for the previous entry.
*      0               - Terminates a VK_TO_WCHARS[] table.
*
*   NOTES:
*   Instead of -1 or Oxff, the Virtual Key name may be repeated.
*   For SGCaps WCHARS, data may be in aVkToWch2[] form.
*
*   CAUTION:
*   SGCaps WCHARS for modification# 2 through last are discarded.
*
* > Special values for Attributes (column 2):
*     CAPLOK      0x01 - The CAPS-LOCK toggle affects this key like SHIFT
*                         on Base and Shift shift states.
*     SGCAPS      0x02 - While CAPS-LOCK toggle is on, special mapping
*                         of Base and Shift shift states is applied.
*                         (Originally Swiss-German)
*     CAPLOKALTGR 0x04 - The CAPS-LOCK toggle affects this key like SHIFT
*                         on AltGr and Shift+AltGr shift states.
*     KANALOK     0x08 - The KANA-LOCK toggle affects this key like KANA.
*
*   NOTES:
*   > The CAPS-LOCK toggle has no effect on Kana shift states.
*   > The attribute hex values are adding:
*                 0x05 - CAPS-LOCK affects the four shift states above.
*                 0x09 - As 0x01, with KANA affecting this key.
*                 0x0a - As 0x02, with KANA affecting this key.
*                 0x0d - As 0x05, with KANA affecting this key.
*
* > Special values for WCHAR (column 3 through last):
*     NONE      0xF000 - No character.
*     DEAD      0xF001 - Dead character; Wchar value is on next line.
*     LGTR      0xF002 - Multiple characters. The sequence is found
*                         in the Ligature Table.
*
*   NOTE:
*   These WCHAR special text values have been abbreviated
*   to fit into tabulation columns of Windows NotePad.
*   This is intended for editing with spreadsheet software.
*   Original values are: WCH_NONE; WCH_DEAD; WCH_LGTR.
*   See kbd.h and kbdfrfre.H for defines.
*
* Row and key refs in conformance to ISO/IEC 9995-1.
*
****************************************************************************
* INFORMATION:
* Original kbdxxxxx.C sources contain a peculiar treatment of
* numpad digit keys:
*
*   // Put this last so that VkKeyScan interprets number characters
*   // as coming from the main section of the kbd (aVkToWch2 and
*   // aVkToWch5) before considering the numpad (aVkToWch1).
*
*   static ALLOC_SECTION_LDATA VK_TO_WCHARS1 aVkToWch1[] = {
*      { VK_NUMPAD0   , 0      ,  '0'   },
*      { VK_NUMPAD1   , 0      ,  '1'   },
*      { VK_NUMPAD2   , 0      ,  '2'   },
*      { VK_NUMPAD3   , 0      ,  '3'   },
*      { VK_NUMPAD4   , 0      ,  '4'   },
*      { VK_NUMPAD5   , 0      ,  '5'   },
*      { VK_NUMPAD6   , 0      ,  '6'   },
*      { VK_NUMPAD7   , 0      ,  '7'   },
*      { VK_NUMPAD8   , 0      ,  '8'   },
*      { VK_NUMPAD9   , 0      ,  '9'   },
*      { 0            , 0      ,  '\0'  }
*   };
*
* No evidence was found for excluding the numpad digits from
* the general allocation table, where they are now included
* but still “last”, in the bottom rows.
*
*
* The following initialisation must contain the total number of valid
* shift states as a decimal integer replacing both instances of <n> in
* this template:
*     static ALLOC_SECTION_LDATA VK_TO_WCHARS<n> aVkToWch<n>[] = {
*
\*************************************************************************************************************************************************************************************************************************************************************************************************************/
// See the explanations in the comment above.
static ALLOC_SECTION_LDATA VK_TO_WCHARS34 aVkToWch34[] = {
/*** ALLOCATION TABLE: START OF PASTE-AND-REPLACE HERE BELOW **§*/

//	|		Description	>>>	|PileA	|Level2	|PileB	|Level2	|Prog				|Number				|Pr+Num				|Arab		|Cyrl		|Grek		|Hebr		|MScrip		|MDblst		|MBold		|MItal		|Ctrls		
//	|		Modification	#  >>>	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|10	|11	|12	|13	|14	|15	|16	|17	|18	|19	|20	|21	|22	|23	|24	|25	|26	|27	|28	|29	|30	|31	|32	|33	
//ISO_#	|	|ScanC	|Virtual_Key 	|Attr.	|0x00	|0x01	|0x10	|0x11	|0x08	|0x09	|0x18	|0x19	|0x20	|0x21	|0x30	|0x31	|0x06	|0x07	|0x16	|0x17	|0x40	|0x41	|0x50	|0x51	|0x80	|0x81	|0x90	|0x91	|0x60	|0x61	|0xa0	|0xa1	|0xe0	|0xe1	|0xc0	|0xc1	|0x02	|0x03	
/*K00	|	T01*/	{VK_ESCAPE     	,0x08	,0x001b	,0x001b	,LGTR	,0x001b	,0x001b	,0x001b	,LGTR	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	,0x001b	}, // 
/*K15	|	X46*/	{VK_CANCEL     	,0	,0x0003	,0x0003	,0x0003	,0x0003	,NONE	,NONE	,NONE	,NONE	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	,0x0003	}, // 
//|====	|	|======	|==============	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|  
/*E00	0	T29*/	//{VK_OEM_7  	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E00	0	T29*/	//{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E01	|	T02*/	{'1'           	,0x09	,0x00e6	,0x00c6	,'1'	,NONE	,'1'	,'&'	,'1'	,NONE	,LGTR	,0x00b9	,NONE	,NONE	,LGTR	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x044c	,0x0482	,DEAD	,'*'	,DEAD	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E01	|	T02*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x2135	,NONE	,NONE	,NONE	,0x1f7d	,NONE	,0x2135	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E02	|	T03*/	{'2'           	,0x09	,0x00e9	,0x00c9	,'2'	,NONE	,'2'	,'~'	,'2'	,NONE	,0x00b2	,0x00b2	,NONE	,NONE	,LGTR	,NONE	,NONE	,NONE	,0xd835	,NONE	,0x044e	,0x042e	,DEAD	,'*'	,0x05bb	,'*'	,0xd835	,0xd835	,0xd835	,0xd835	,0xd835	,0xd835	,0xd835	,0xd835	,NONE	,NONE	}, // 
/*E02	|	T03*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x1fc6	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E03	|	T04*/	{'3'           	,0x08	,'\"'	,0x2015	,'3'	,NONE	,'3'	,'#'	,'3'	,NONE	,0x00b3	,0x00b3	,0x2033	,NONE	,LGTR	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x0435	,0x0415	,DEAD	,'*'	,0x05b0	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E03	|	T04*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x212c	,NONE	,NONE	,NONE	,0x03ca	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E04	|	T05*/	{'4'           	,0x08	,'\''	,0x2014	,'4'	,NONE	,'4'	,'['	,'4'	,NONE	,LGTR	,0x2074	,0x2032	,NONE	,LGTR	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x0444	,0x0424	,DEAD	,'*'	,0x05b4	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E04	|	T05*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x210e	,NONE	,NONE	,NONE	,0x03cc	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E05	|	T06*/	{'5'           	,0x0a	,0x00f9	,0x2013	,'5'	,NONE	,'5'	,']'	,'5'	,NONE	,'E'	,0x2075	,0x00b0	,NONE	,'E'	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x0442	,0x0422	,DEAD	,'*'	,0x05b5	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E05	|	T06*/	{0xff       	,0	,0x00d9	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x212f	,NONE	,NONE	,NONE	,0x1f51	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E06	|	T07*/	{'6'           	,0x08	,'-'	,0x2011	,'6'	,NONE	,'6'	,'|'	,'6'	,NONE	,'F'	,0x2076	,0x00ad	,NONE	,'F'	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x0445	,0x0425	,DEAD	,'*'	,0x05b6	,0x05b1	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E06	|	T07*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x212d	,NONE	,NONE	,NONE	,0x1f10	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E07	|	T08*/	{'7'           	,0x09	,0x00e8	,0x00c8	,'7'	,NONE	,'7'	,'`'	,'7'	,NONE	,'7'	,0x2077	,NONE	,NONE	,'7'	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x043c	,0x041c	,DEAD	,'*'	,0x05b8	,0x05b3	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E07	|	T08*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x210b	,NONE	,NONE	,NONE	,0x1f70	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E08	|	T09*/	{'8'           	,0x09	,0x0153	,0x0152	,'8'	,NONE	,'8'	,'\\'	,'8'	,NONE	,'8'	,0x2078	,NONE	,NONE	,'8'	,NONE	,NONE	,NONE	,DEAD	,NONE	,'#'	,'*'	,DEAD	,'*'	,0x05b7	,0x05b2	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E08	|	T09*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x2115	,NONE	,NONE	,NONE	,0x1fb1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E09	|	T0A*/	{'9'           	,0x09	,0x00e7	,0x00c7	,'9'	,NONE	,'9'	,'^'	,'9'	,NONE	,'9'	,0x2079	,NONE	,NONE	,'9'	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x043b	,0x041b	,DEAD	,'*'	,0x05c2	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E09	|	T0A*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x2102	,NONE	,NONE	,NONE	,0x1fe0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E10	|	T0B*/	{'0'           	,0x09	,0x00e0	,0x00c0	,'0'	,NONE	,'0'	,'@'	,'0'	,NONE	,'/'	,0x2070	,0x2205	,NONE	,'0'	,NONE	,NONE	,NONE	,DEAD	,NONE	,0x043f	,0x041f	,DEAD	,'*'	,0x05c1	,0x05bf	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*E10	|	T0B*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x210a	,NONE	,NONE	,NONE	,0x1f51	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E11	|	T0C*/	{VK_OEM_MINUS  	,0x08	,DEAD	,0x00b0	,0x1d49	,NONE	,'-'	,0x00b0	,0x2212	,NONE	,0x00f7	,0x207b	,0x00b0	,NONE	,'1'	,NONE	,NONE	,NONE	,NONE	,NONE	,0x044f	,0x042f	,DEAD	,DEAD	,0x05be	,0x05bf	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,NONE	,NONE	}, // 
/*E11	|	T0C*/	{0xff       	,0	,0x00e1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x1f10	,0x1f26	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*E12	|	T0D*/	{VK_OEM_PLUS   	,0x08	,DEAD	,'+'	,'='	,NONE	,'='	,'+'	,0x00b1	,NONE	,'='	,0x207a	,0x2248	,0x2243	,'='	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0449	,0x0429	,DEAD	,'*'	,0x05bc	,0x05bd	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,NONE	,NONE	}, // 
/*E12	|	T0D*/	{0xff       	,0	,0x00f2	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x03ca	,NONE	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*E13	0	T2B*/	//{VK_OEM_5  	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E13	0	T2B*/	//{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*E14	|	T0E*/	{VK_BACK       	,0x08	,'\b'	,'\b'	,LGTR	,'\b'	,'\b'	,'\b'	,LGTR	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,'\b'	,0x007f	,NONE	}, // 
//|====	|	|======	|==============	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|  
/*D00	|	T0F*/	{VK_TAB        	,0	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,'\t'	,NONE	,NONE	}, // 
/*D01	|	T10*/	{'A'           	,0x01	,'a'	,'A'	,'@'	,DEAD	,NONE	,NONE	,NONE	,NONE	,0x00a5	,0x1d43	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0636	,0x064e	,0x0430	,0x0410	,0x03b1	,0x0391	,0x05d0	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D01	|	T10*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x0151	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D02	|	T11*/	{'Z'           	,0x01	,'z'	,'Z'	,'%'	,DEAD	,NONE	,NONE	,NONE	,NONE	,0x00a3	,0x1dbb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0635	,0x064b	,0x0437	,0x0417	,0x03b6	,0x0396	,0x05d6	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D02	|	T11*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x00f8	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D03	|	T12*/	{'E'           	,0x01	,'e'	,'E'	,0x20ac	,DEAD	,NONE	,NONE	,NONE	,NONE	,0x20ac	,0x1d49	,0x025b	,0x0190	,NONE	,NONE	,NONE	,NONE	,0x062b	,0x064f	,0x0435	,0x0415	,0x03b5	,0x0395	,0x05c3	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D03	|	T12*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x005e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D04	|	T13*/	{'R'           	,0x01	,'r'	,'R'	,'&'	,DEAD	,NONE	,NONE	,NONE	,NONE	,0x00b0	,0x02b3	,0x0254	,0x0186	,NONE	,NONE	,NONE	,NONE	,0x0642	,0x064c	,0x0440	,0x0420	,0x03c1	,0x03a1	,0x05e8	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D04	|	T13*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x00e5	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D05	|	T14*/	{'T'           	,0x01	,'t'	,'T'	,'~'	,0x2020	,NONE	,NONE	,NONE	,NONE	,'C'	,0x1d57	,0x1e97	,LGTR	,NONE	,NONE	,NONE	,NONE	,0x0641	,LGTR	,0x0442	,0x0422	,0x03c4	,0x03a4	,0x05ea	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D05	0	T14*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D06	|	T15*/	{'Y'           	,0x01	,'y'	,'Y'	,0x00a5	,0x2021	,NONE	,NONE	,NONE	,NONE	,'D'	,0x02b8	,0x200c	,NONE	,NONE	,NONE	,NONE	,NONE	,0x063a	,0x0625	,0x044a	,0x042a	,0x03c5	,0x03a5	,0x05e6	,0x05e5	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D06	0	T15*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D07	|	T16*/	{'U'           	,0x01	,'u'	,'U'	,'-'	,0x222a	,NONE	,NONE	,NONE	,NONE	,'4'	,0x1d58	,LGTR	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0639	,0x2018	,0x0443	,0x0423	,0x03b8	,0x0398	,0x05d8	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D07	0	T16*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D08	|	T17*/	{'I'           	,0x01	,'i'	,'I'	,'|'	,DEAD	,NONE	,NONE	,NONE	,NONE	,'5'	,0x2071	,LGTR	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0647	,0x007f	,0x0438	,0x0418	,0x03b9	,0x0399	,0x05b4	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D08	|	T17*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x005f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D09	|	T18*/	{'O'           	,0x01	,'o'	,'O'	,DEAD	,DEAD	,NONE	,NONE	,NONE	,NONE	,'6'	,0x1d52	,0x2126	,NONE	,NONE	,NONE	,NONE	,NONE	,0x062e	,0x005f	,0x043e	,0x041e	,0x03bf	,0x039f	,0x05b9	,0x05ba	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D09	|	T18*/	{0xff       	,0	,NONE	,NONE	,0x00a6	,0x01eb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D10	|	T19*/	{'P'           	,0x01	,'p'	,'P'	,'*'	,DEAD	,NONE	,NONE	,NONE	,NONE	,'*'	,0x1d56	,0x00b7	,NONE	,NONE	,NONE	,NONE	,NONE	,0x062d	,0x061b	,0x043f	,0x041f	,0x03c0	,0x03a0	,0x05e4	,0x05e3	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*D10	|	T19*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x1e57	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D11	|	T1A*/	{VK_OEM_6      	,0x08	,DEAD	,LGTR	,DEAD	,0x2039	,'/'	,'^'	,'/'	,NONE	,'^'	,LGTR	,0x2023	,NONE	,'^'	,NONE	,NONE	,NONE	,0x062c	,'}'	,0x044f	,0x042f	,DEAD	,DEAD	,0x05d9	,'*'	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,0x001b	,NONE	}, // 
/*D11	|	T1A*/	{0xff       	,0	,0x00ea	,NONE	,0x00f5	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x1fc6	,0x03ca	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*D12	|	T1B*/	{VK_OEM_1      	,0x08	,DEAD	,LGTR	,DEAD	,0x203a	,'\\'	,'$'	,'$'	,NONE	,0x00d7	,LGTR	,0x2022	,NONE	,'$'	,NONE	,NONE	,NONE	,0x062f	,'{'	,0x0439	,0x0419	,DEAD	,DEAD	,0x20aa	,'*'	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,0x001d	,NONE	}, // 
/*D12	|	T1B*/	{0xff       	,0	,0x00eb	,NONE	,0x0101	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x1f7d	,0x1f14	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*D13	0	T2B*/	//{VK_OEM_5  	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D13	0	T2B*/	//{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
//|====	|	|======	|==============	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|  
/*C01	|	T1E*/	{'Q'           	,0x01	,'q'	,'Q'	,'#'	,0x2610	,NONE	,NONE	,NONE	,NONE	,LGTR	,LGTR	,0x1da3	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0634	,'\\'	,0x0447	,0x0427	,0x03c2	,0x2211	,0x05e7	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C01	0	T1E*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C02	|	T1F*/	{'S'           	,0x01	,'s'	,'S'	,'$'	,DEAD	,NONE	,NONE	,NONE	,NONE	,'$'	,0x02e2	,DEAD	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0633	,NONE	,0x0441	,0x0421	,0x03c3	,0x03a3	,0x05e1	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C02	|	T1F*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x1e05	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x2075	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C03	|	T20*/	{'D'           	,0x01	,'d'	,'D'	,'('	,0x2300	,NONE	,NONE	,NONE	,NONE	,'('	,0x1d48	,0x2013	,NONE	,NONE	,NONE	,NONE	,NONE	,0x064a	,']'	,0x0434	,0x0414	,0x03b4	,0x0394	,0x05d3	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C03	0	T20*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C04	|	T21*/	{'F'           	,0x01	,'f'	,'F'	,')'	,DEAD	,NONE	,NONE	,NONE	,NONE	,')'	,0x1da0	,0xfeff	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0628	,'['	,0x0444	,0x0424	,0x03c6	,0x03a6	,0x05c3	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C04	|	T21*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x024d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C05	|	T22*/	{'G'           	,0x01	,'g'	,'G'	,'`'	,DEAD	,NONE	,NONE	,NONE	,NONE	,'A'	,0x1d4d	,0x2060	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0644	,LGTR	,0x0433	,0x0413	,0x03b3	,0x0393	,0x05d2	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C05	|	T22*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x03b5	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C06	|	T23*/	{'H'           	,0x01	,'h'	,'H'	,'^'	,DEAD	,NONE	,NONE	,NONE	,NONE	,'B'	,0x02b0	,0x1e96	,LGTR	,NONE	,NONE	,NONE	,NONE	,0x0627	,0x0623	,0x0445	,0x0425	,0x03b7	,0x0397	,0x05d4	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C06	|	T23*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x021f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C07	|	T24*/	{'J'           	,0x01	,'j'	,'J'	,'['	,DEAD	,NONE	,NONE	,NONE	,NONE	,'1'	,0x02b2	,LGTR	,NONE	,NONE	,NONE	,NONE	,NONE	,0x062a	,0x0640	,0x0439	,0x0419	,0x03be	,0x039e	,0x05d9	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C07	|	T24*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x0192	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C08	|	T25*/	{'K'           	,0x01	,'k'	,'K'	,']'	,DEAD	,NONE	,NONE	,NONE	,NONE	,'2'	,0x1d4f	,LGTR	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0646	,0x060c	,0x043a	,0x041a	,0x03ba	,0x039a	,0x05db	,0x05da	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C08	|	T25*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x1ebb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C09	|	T26*/	{'L'           	,0x01	,'l'	,'L'	,0x2026	,0x00a3	,NONE	,NONE	,NONE	,NONE	,'3'	,0x02e1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0645	,'/'	,0x043b	,0x041b	,0x03bb	,0x039b	,0x05dc	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C09	0	T26*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C10	|	T27*/	{'M'           	,0x01	,'m'	,'M'	,0x00b7	,DEAD	,NONE	,NONE	,NONE	,NONE	,'-'	,0x1d50	,0x2013	,0x2012	,NONE	,NONE	,NONE	,NONE	,0x0643	,':'	,0x043c	,0x041c	,0x03bc	,0x039c	,0x05de	,0x05dd	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*C10	|	T27*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x00a4	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*C11	|	T28*/	{VK_OEM_3      	,0x08	,0x2019	,LGTR	,0x02bc	,0x00ab	,'\''	,'%'	,'`'	,NONE	,'%'	,LGTR	,0x2030	,NONE	,'%'	,0x2030	,0x2030	,NONE	,0x0637	,'\"'	,0x045d	,0x040d	,DEAD	,DEAD	,0x05de	,0x05dd	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,0x200c	,NONE	}, // 
/*C11	|	T28*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x03cc	,0x0390	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*C12	|	T2B*/	{VK_OEM_5      	,0x08	,'_'	,LGTR	,DEAD	,0x00bb	,'\"'	,0x00b5	,'_'	,NONE	,0x2212	,LGTR	,0x00b5	,NONE	,'/'	,0x00b5	,0x00b5	,NONE	,0x0630	,0x0651	,0x045d	,0x040d	,DEAD	,DEAD	,0x05bc	,'*'	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,0x001c	,NONE	}, // 
/*C12	|	T2B*/	{0xff       	,0	,NONE	,NONE	,0x00b2	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x1f70	,0x1f12	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*C13	|	T1C*/	{VK_RETURN     	,0	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	,'\r'	}, // 
/*C13	0	T1C*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
//|====	|	|======	|==============	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|  
/*B00	0	T56*/	//{VK_OEM_102	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B00	0	T56*/	//{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B01	|	T2C*/	{'W'           	,0x01	,'w'	,'W'	,'<'	,0x2713	,NONE	,NONE	,NONE	,NONE	,LGTR	,0x02b7	,LGTR	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0626	,'~'	,0x0448	,0x0428	,DEAD	,0x03da	,0x05d5	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*B01	|	T2C*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0448	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B02	|	T2D*/	{'X'           	,0x01	,'x'	,'X'	,'>'	,0x2717	,NONE	,NONE	,NONE	,NONE	,LGTR	,0x02e3	,LGTR	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0621	,0x0652	,0x0436	,0x0416	,0x03c7	,0x03a7	,0x05d7	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*B02	0	T2D*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B03	|	T2E*/	{'C'           	,0x01	,'c'	,'C'	,'{'	,DEAD	,NONE	,NONE	,NONE	,NONE	,':'	,0x1d9c	,LGTR	,LGTR	,NONE	,NONE	,NONE	,NONE	,0x0624	,0x0650	,0x0446	,0x0426	,0x03c8	,0x03a8	,0x05e9	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*B03	|	T2E*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x0229	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B04	|	T2F*/	{'V'           	,0x01	,'v'	,'V'	,'}'	,DEAD	,NONE	,NONE	,NONE	,NONE	,';'	,0x1d5b	,LGTR	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0631	,0x064d	,0x0432	,0x0412	,0x03c9	,0x03a9	,0x05e2	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*B04	|	T2F*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x0219	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B05	|	T30*/	{'B'           	,0x01	,'b'	,'B'	,'/'	,DEAD	,NONE	,NONE	,NONE	,NONE	,LGTR	,0x1d47	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,LGTR	,LGTR	,0x0431	,0x0411	,0x03b2	,0x0392	,0x05d1	,'*'	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*B05	|	T30*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x0115	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B06	|	T31*/	{'N'           	,0x01	,'n'	,'N'	,'\\'	,DEAD	,NONE	,NONE	,NONE	,NONE	,LGTR	,0x207f	,LGTR	,LGTR	,NONE	,NONE	,NONE	,NONE	,0x0649	,0x0622	,0x043d	,0x041d	,0x03bd	,0x039d	,0x05e0	,0x05df	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*B06	|	T31*/	{0xff       	,0	,NONE	,NONE	,NONE	,0x01a1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B07	|	T32*/	{VK_OEM_COMMA  	,0x08	,','	,LGTR	,'?'	,'?'	,','	,'?'	,'?'	,NONE	,'0'	,LGTR	,NONE	,NONE	,'0'	,NONE	,NONE	,NONE	,0x0643	,':'	,0x043c	,0x041c	,0x03bc	,0x039c	,0x05de	,0x05dd	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,LGTR	,NONE	,NONE	}, // 
/*B07	0	T32*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B08	|	T33*/	{VK_OEM_PERIOD 	,0x08	,'.'	,LGTR	,';'	,';'	,'.'	,'='	,';'	,NONE	,'.'	,LGTR	,0x2027	,NONE	,'.'	,NONE	,NONE	,NONE	,0x0629	,0x2019	,0x0432	,0x0412	,','	,';'	,0x05c1	,0x05c2	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,NONE	,NONE	}, // 
/*B08	|	T33*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*B09	|	T34*/	{VK_OEM_2      	,0x08	,'@'	,LGTR	,':'	,':'	,':'	,'/'	,'@'	,NONE	,','	,LGTR	,0x2044	,NONE	,','	,NONE	,NONE	,NONE	,0x0648	,','	,'#'	,'*'	,'.'	,0x00b7	,0x05c3	,'*'	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,NONE	,NONE	}, // 
/*B09	|	T34*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*B10	|	T35*/	{VK_OEM_8      	,0x08	,'#'	,LGTR	,0x00a7	,'!'	,';'	,'!'	,0x00a7	,NONE	,'+'	,LGTR	,0x00b1	,NONE	,'+'	,0x00b1	,0x00b1	,NONE	,0x0632	,'.'	,'#'	,'*'	,0x00b7	,':'	,0x05c3	,'*'	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,DEAD	,NONE	,NONE	}, // 
/*B10	|	T35*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x212f	,0x212f	,0x2115	,0x2115	,0x212c	,0x212c	,0x210e	,0x210e	,NONE	,NONE	}, // 
/*B11	0	T73*/	//{VK_ABNT_C1	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*B11	0	T73*/	//{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
//|====	|	|======	|==============	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|  
/*A03	|	T39*/	{VK_SPACE      	,0x08	,0x0020	,0x0020	,0x00a0	,LGTR	,0x0020	,0x0020	,0x0020	,0x0020	,0x202f	,LGTR	,0x202f	,0x202f	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	,0x0020	}, // 
/*A03	0	T39*/	{0xff       	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
//|====	|	|======	|==============	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|======	|  
/*C54	0	T7E*/	//{VK_ABNT_C2	,0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
/*D54	|	T4E*/	{VK_ADD        	,0x08	,'+'	,'+'	,NONE	,NONE	,'+'	,'='	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0600	,'*'	,'#'	,'*'	,'#'	,'*'	,'#'	,'*'	,'+'	,0x00b1	,'+'	,0x00b1	,'+'	,0x00b1	,'+'	,0x00b1	,NONE	,NONE	}, // 
/*E54	|	T4A*/	{VK_SUBTRACT   	,0x08	,'-'	,0x2212	,NONE	,NONE	,'-'	,'^'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0609	,0x060a	,'#'	,'*'	,'#'	,'*'	,'#'	,'*'	,'-'	,0x2212	,'-'	,0x2212	,'-'	,0x2212	,'-'	,0x2212	,NONE	,NONE	}, // 
/*E53	|	T37*/	{VK_MULTIPLY   	,0x08	,'*'	,0x00d7	,NONE	,NONE	,'*'	,')'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x0605	,'*'	,'#'	,'*'	,'#'	,'*'	,'#'	,'*'	,'*'	,0x00d7	,'*'	,0x00d7	,'*'	,0x00d7	,'*'	,0x00d7	,NONE	,NONE	}, // 
/*E52	|	X35*/	{VK_DIVIDE     	,0x08	,'/'	,0x00f7	,NONE	,NONE	,'/'	,'('	,NONE	,NONE	,0x2044	,0x2044	,NONE	,NONE	,0x2044	,0x2044	,NONE	,NONE	,0x066a	,'*'	,'#'	,'*'	,0x2044	,0x2044	,'#'	,'*'	,'/'	,0x00f7	,'/'	,0x00f7	,'/'	,0x00f7	,'/'	,0x00f7	,NONE	,NONE	}, // 
/*A53	|	TXX*/	{VK_DECIMAL    	,0x01	,'.'	,','	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,0x2032	,0x2033	,NONE	,NONE	,0x066b	,0x066c	,'#'	,'*'	,'#'	,'*'	,'#'	,'*'	,'.'	,','	,'.'	,','	,'.'	,','	,'.'	,','	,NONE	,NONE	}, // 
/*A51	|	TXX*/	{VK_NUMPAD0    	,0x08	,'0'	,LGTR	,0x2195	,NONE	,'0'	,LGTR	,0x2195	,NONE	,0x2195	,0x21d5	,0x2195	,0x21d5	,0x2070	,0x2080	,0x2070	,0x2080	,0x0660	,'*'	,'#'	,'*'	,0x2070	,0x2080	,'#'	,'*'	,'0'	,LGTR	,'0'	,LGTR	,'0'	,LGTR	,'0'	,LGTR	,NONE	,NONE	}, // 
/*B51	|	TXX*/	{VK_NUMPAD1    	,0x08	,'1'	,LGTR	,0x2199	,NONE	,'1'	,LGTR	,0x2199	,NONE	,0x2199	,0x21d9	,0x2199	,0x21d9	,0x00b9	,0x2081	,0x00b9	,0x2081	,0x0661	,'*'	,'#'	,'*'	,0x00b9	,0x2081	,'#'	,'*'	,'1'	,LGTR	,'1'	,LGTR	,'1'	,LGTR	,'1'	,LGTR	,NONE	,NONE	}, // 
/*B52	|	TXX*/	{VK_NUMPAD2    	,0x08	,'2'	,'A'	,0x2193	,NONE	,'2'	,'a'	,0x2193	,NONE	,0x2193	,0x21d3	,0x2193	,0x21d3	,0x00b2	,0x2082	,0x00b2	,0x2082	,0x0662	,'*'	,'#'	,'*'	,0x00b2	,0x2082	,'#'	,'*'	,'2'	,'A'	,'2'	,'A'	,'2'	,'A'	,'2'	,'A'	,NONE	,NONE	}, // 
/*B53	|	TXX*/	{VK_NUMPAD3    	,0x08	,'3'	,'B'	,0x2198	,NONE	,'3'	,'b'	,0x2198	,NONE	,0x2198	,0x21d8	,0x2198	,0x21d8	,0x00b3	,0x2083	,0x00b3	,0x2083	,0x0663	,'*'	,'#'	,'*'	,0x00b3	,0x2083	,'#'	,'*'	,'3'	,'B'	,'3'	,'B'	,'3'	,'B'	,'3'	,'B'	,NONE	,NONE	}, // 
/*C51	|	TXX*/	{VK_NUMPAD4    	,0x08	,'4'	,LGTR	,0x2190	,NONE	,'4'	,LGTR	,0x2190	,NONE	,0x2190	,0x21d0	,0x2190	,0x21d0	,0x2074	,0x2084	,0x2074	,0x2084	,0x0664	,'*'	,'#'	,'*'	,0x2074	,0x2084	,'#'	,'*'	,'4'	,LGTR	,'4'	,LGTR	,'4'	,LGTR	,'4'	,LGTR	,NONE	,NONE	}, // 
/*C52	|	TXX*/	{VK_NUMPAD5    	,0x08	,'5'	,'C'	,0x2194	,NONE	,'5'	,'c'	,0x2194	,NONE	,0x2194	,0x21d4	,0x2194	,0x21d4	,0x2075	,0x2085	,0x2075	,0x2085	,0x0665	,'*'	,'#'	,'*'	,0x2075	,0x2085	,'#'	,'*'	,'5'	,'C'	,'5'	,'C'	,'5'	,'C'	,'5'	,'C'	,NONE	,NONE	}, // 
/*C53	|	TXX*/	{VK_NUMPAD6    	,0x08	,'6'	,'D'	,0x2192	,NONE	,'6'	,'d'	,0x2192	,NONE	,0x2192	,0x21d2	,0x2192	,0x21d2	,0x2076	,0x2086	,0x2076	,0x2086	,0x0666	,'*'	,'#'	,'*'	,0x2076	,0x2086	,'#'	,'*'	,'6'	,'D'	,'6'	,'D'	,'6'	,'D'	,'6'	,'D'	,NONE	,NONE	}, // 
/*D51	|	TXX*/	{VK_NUMPAD7    	,0x08	,'7'	,0x202f	,0x2196	,NONE	,'7'	,LGTR	,0x2196	,NONE	,0x2196	,0x21d6	,0x2196	,0x21d6	,0x2077	,0x2087	,0x2077	,0x2087	,0x0667	,'*'	,'#'	,'*'	,0x2077	,0x2087	,'#'	,'*'	,'7'	,0x202f	,'7'	,0x202f	,'7'	,0x202f	,'7'	,0x202f	,NONE	,NONE	}, // 
/*D52	|	TXX*/	{VK_NUMPAD8    	,0x08	,'8'	,'E'	,0x2191	,NONE	,'8'	,'e'	,0x2191	,NONE	,0x2191	,0x21d1	,0x2191	,0x21d1	,0x2078	,0x2088	,0x2078	,0x2088	,0x0668	,'*'	,'#'	,'*'	,0x2078	,0x2088	,'#'	,'*'	,'8'	,'E'	,'8'	,'E'	,'8'	,'E'	,'8'	,'E'	,NONE	,NONE	}, // 
/*D53	|	TXX*/	{VK_NUMPAD9    	,0x08	,'9'	,'F'	,0x2197	,NONE	,'9'	,'f'	,0x2197	,NONE	,0x2197	,0x21d7	,0x2197	,0x21d7	,0x2079	,0x2089	,0x2079	,0x2089	,0x0669	,'*'	,'#'	,'*'	,0x2079	,0x2089	,'#'	,'*'	,'9'	,'F'	,'9'	,'F'	,'9'	,'F'	,'9'	,'F'	,NONE	,NONE	}, // 
/*NULL-	|	TERMN*/	{0             	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	,0	}        

/*** ALLOCATION TABLE: END OF PASTE-AND-REPLACE ***/
};
// The following list must contain one entry per allocation table (1 for instance).
// In each entry, the total number of valid shift states shows up three times,
// as a decimal integer replacing all instances of <n> in this generic template:
//      {  (PVK_TO_WCHARS1)aVkToWch<n>,  <n>,  sizeof(aVkToWch<n>[0])  },
static ALLOC_SECTION_LDATA VK_TO_WCHAR_TABLE aVkToWcharTable[] = {
    {  (PVK_TO_WCHARS1)aVkToWch34,  34,  sizeof(aVkToWch34[0])  },
    {                        NULL,   0,  0                      },
};

/****************************************************************************************\
* aLigature[]  -  map Wchar instances to Ligatures
*
* Ligature is an internal name for Wchar sequences that are
* generated when a specified key is pressed.
*
* The ligatures are all in *one* table.
* The number of code units of the longest ligature
* determines the number replacing the <n> in
*     static ALLOC_SECTION_LDATA LIGATURE<n>
* and in
*     <n>,
*     sizeof(aLigature[0]),
*     (PLIGATURE1)aLigature
* below in the static ALLOC_SECTION_LDATA KBDTABLES.
*
* The maximum length of a ligature is 16 code units.
* Code units from 17th on are discarded even when the table is defined for more.
*
* CAUTION:
* ON THE SHIFT+ALTGR SHIFT STATE, LIGATURES ARE LIMITED TO 4 CODE UNITS.
* MORE CODE UNITS ON THIS SHIFT STATE CAUSE THE KEYBOARD DRIVER TO FAIL.
* IF THE FAILING DRIVER IS THE ONE OF THE DEFAULT KEYBOARD LAYOUT,
* THE SYSTEM MAY NOT WORK AS EXPECTED.
* The probable explanation is that when ligatures were implemented,
* they were imposed a design limit of four code units, given that the
* main purpose was to generate SMP characters, which need 2 code units,
* and some digraphs and letters with combining diacritics.
*
* The ligatures table must be defined for <n> characters,
* whether in kbd.h, or kbdfrfre.h, or here before,
* using the following define:
*     TYPEDEF_LIGATURE(<n>)
* For clarification, a trailing comment is added:
*                            // LIGATURE<n>, *PLIGATURE<n>
* Tables for up to 5 characters length are already defined in
* kbd.h.
*
* The lasting Wchar fields of each ligature that is shorter than
* the maximum length defined, may be filled up with 0xF000, or with
* WCH_NONE as defined in kbd.h, or NONE defined in the custom header.
* These entries may be shortened to less long ligature allocations,
* especially when the ligatures are not edited in a spreadsheet table.
*
* The table is sorted to facilitate human reading. Sorting is not required.
\****************************************************************************************/
static ALLOC_SECTION_LDATA LIGATURE16 aLigature[] = {
// |Virtual_Key	|SC	|ISO_#	|Modif#	|Char0	|Char1	|Char2	|Char3	|Char4	|Char5	|Char6	|Char7	|Char8	|Char9	|Char10	|Char11	|Char12	|Char13	|Char14	|Char15|
/*** TABLE OF SEQUENCES: START OF PASTE-AND-REPLACE HERE BELOW **§*/

{VK_ESCAPE	/*K00*/	,2	,'f'	,'r'	,'-'	,'F'	,'R'	,'_'	,'a'	,'z'	,'e'	,'r'	,'t'	,'y'	,'u'	,'i'	,'o'	,'p'	}, // 
{VK_ESCAPE	/*K00*/	,6	,'k'	,'b'	,'f'	,'r'	,'i'	,'n'	,'t'	,'u'	,'_'	,'0'	,'.'	,'6'	,'.'	,'3'	,'.'	,'0'	}, // 
{'1'        	/*E01*/	,8	,'&'	,'n'	,'b'	,'s'	,'p'	,';'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'1'        	/*E01*/	,12	,'&'	,'n'	,'b'	,'s'	,'p'	,';'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'2'        	/*E02*/	,12	,'\\'	,'x'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'3'        	/*E03*/	,12	,'0'	,'x'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'4'        	/*E04*/	,8	,'U'	,'+'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'4'        	/*E04*/	,12	,'\\'	,'u'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_BACK	/*E14*/	,2	,'P'	,'r'	,'g'	,'_'	,'0'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_BACK	/*E14*/	,6	,'P'	,'r'	,'o'	,'g'	,'r'	,'a'	,'m'	,'m'	,'e'	,'u'	,'r'	,'_'	,'V'	,'e'	,'r'	,'r'	}, // 
{'T'        	/*D05*/	,11	,'T'	,0x0308	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'U'        	/*D07*/	,10	,0x2013	,0x0020	,0xfeff	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'I'        	/*D08*/	,10	,0x0020	,0xfeff	,0x2013	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_6	/*D11*/	,1	,0x2039	,0x202f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_6	/*D11*/	,9	,0x2039	,0x00a0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_1	/*D12*/	,1	,0x202f	,0x203a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_1	/*D12*/	,9	,0x00a0	,0x203a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'Q'        	/*C01*/	,8	,'n'	,0x1d52	,0x202f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'Q'        	/*C01*/	,9	,'N'	,0x1d52	,0x202f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'H'        	/*C06*/	,11	,'H'	,0x0331	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'J'        	/*C07*/	,10	,0x2013	,0x0020	,0x2060	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'K'        	/*C08*/	,10	,0x0020	,0x2060	,0x2013	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_3	/*C11*/	,1	,0x00ab	,0x202f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_3	/*C11*/	,9	,0x00ab	,0x00a0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_5	/*C12*/	,1	,0x202f	,0x00bb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_5	/*C12*/	,9	,0x00a0	,0x00bb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'W'        	/*B01*/	,8	,'&'	,'#'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'W'        	/*B01*/	,12	,'&'	,'#'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'X'        	/*B02*/	,8	,'&'	,'#'	,'x'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'X'        	/*B02*/	,12	,'&'	,'#'	,'x'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'C'        	/*B03*/	,10	,'c'	,0x02bc	,'h'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'C'        	/*B03*/	,11	,'C'	,0x02bc	,'H'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'V'        	/*B04*/	,10	,'C'	,0x02bc	,'h'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'B'        	/*B05*/	,8	,'0'	,'0'	,'0'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'N'        	/*B06*/	,8	,'0'	,'0'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'N'        	/*B06*/	,10	,'n'	,0x1d52	,0x202f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{'N'        	/*B06*/	,11	,'N'	,0x1d52	,0x202f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_COMMA	/*B07*/	,1	,0x202f	,'?'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_COMMA	/*B07*/	,9	,0x00a0	,'?'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_PERIOD	/*B08*/	,1	,0x202f	,';'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_PERIOD	/*B08*/	,9	,0x00a0	,';'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_2	/*B09*/	,1	,0x202f	,':'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_2	/*B09*/	,9	,0x00a0	,':'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_8	/*B10*/	,1	,0x202f	,'!'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_OEM_8	/*B10*/	,9	,0x00a0	,'!'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_SPACE	/*A03*/	,3	,0x0020	,0x2060	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_SPACE	/*A03*/	,9	,0x0020	,0xfeff	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_NUMPAD0	/*A51*/	,1	,'0'	,'0'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_NUMPAD0	/*A51*/	,5	,'0'	,'0'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_NUMPAD1	/*B51*/	,1	,'0'	,'0'	,'0'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_NUMPAD1	/*B51*/	,5	,'0'	,'x'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_NUMPAD4	/*C51*/	,1	,'U'	,'+'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_NUMPAD4	/*C51*/	,5	,'\\'	,'u'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
{VK_NUMPAD7	/*D51*/	,5	,'\\'	,'x'	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, // 
// Mathematical alphanumeric symbols  =================================================================================================================================																			}, //
// Script symbols lowercase																			}, //
{'A'           		,24	,0xd835	,0xdcb6	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,24	,0xd835	,0xdcb7	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,24	,0xd835	,0xdcb8	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,24	,0xd835	,0xdcb9	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,24	,0x212f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,24	,0xd835	,0xdcbb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,24	,0x210a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,24	,0xd835	,0xdcbd	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,24	,0xd835	,0xdcbe	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,24	,0xd835	,0xdcbf	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,24	,0xd835	,0xdcc0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,24	,0xd835	,0xdcc1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,24	,0xd835	,0xdcc2	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,24	,0xd835	,0xdcc3	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,24	,0x2134	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,24	,0xd835	,0xdcc5	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,24	,0xd835	,0xdcc6	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,24	,0xd835	,0xdcc7	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,24	,0xd835	,0xdcc8	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,24	,0xd835	,0xdcc9	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,24	,0xd835	,0xdcca	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,24	,0xd835	,0xdccb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,24	,0xd835	,0xdccc	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,24	,0xd835	,0xdccd	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,24	,0xd835	,0xdcce	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,24	,0xd835	,0xdccf	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Script symbols uppercase																			}, //
{'A'           		,25	,0xd835	,0xdc9c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,25	,0x212c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,25	,0xd835	,0xdc9e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,25	,0xd835	,0xdc9f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,25	,0x2130	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,25	,0x2131	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,25	,0xd835	,0xdca2	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,25	,0x210b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,25	,0x2110	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,25	,0xd835	,0xdca5	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,25	,0xd835	,0xdca6	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,25	,0x2112	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,25	,0x2133	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,25	,0xd835	,0xdca9	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,25	,0xd835	,0xdcaa	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,25	,0xd835	,0xdcab	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,25	,0xd835	,0xdcac	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,25	,0x211b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,25	,0xd835	,0xdcae	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,25	,0xd835	,0xdcaf	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,25	,0xd835	,0xdcb0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,25	,0xd835	,0xdcb1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,25	,0xd835	,0xdcb2	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,25	,0xd835	,0xdcb3	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,25	,0xd835	,0xdcb4	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,25	,0xd835	,0xdcb5	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Double-struck symbols digits																			}, //
{'0'           		,26	,0xd835	,0xdfd8	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'1'           		,26	,0xd835	,0xdfd9	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'2'           		,26	,0xd835	,0xdfda	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'3'           		,26	,0xd835	,0xdfdb	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'4'           		,26	,0xd835	,0xdfdc	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'5'           		,26	,0xd835	,0xdfdd	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'6'           		,26	,0xd835	,0xdfde	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'7'           		,26	,0xd835	,0xdfdf	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'8'           		,26	,0xd835	,0xdfe0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'9'           		,26	,0xd835	,0xdfe1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Double-struck symbols lowercase																			}, //
{'A'           		,26	,0xd835	,0xdd52	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,26	,0xd835	,0xdd53	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,26	,0xd835	,0xdd54	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,26	,0xd835	,0xdd55	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,26	,0xd835	,0xdd56	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,26	,0xd835	,0xdd57	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,26	,0xd835	,0xdd58	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,26	,0xd835	,0xdd59	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,26	,0xd835	,0xdd5a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,26	,0xd835	,0xdd5b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,26	,0xd835	,0xdd5c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,26	,0xd835	,0xdd5d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,26	,0xd835	,0xdd5e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,26	,0xd835	,0xdd5f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,26	,0xd835	,0xdd60	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,26	,0xd835	,0xdd61	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,26	,0xd835	,0xdd62	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,26	,0xd835	,0xdd63	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,26	,0xd835	,0xdd64	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,26	,0xd835	,0xdd65	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,26	,0xd835	,0xdd66	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,26	,0xd835	,0xdd67	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,26	,0xd835	,0xdd68	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,26	,0xd835	,0xdd69	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,26	,0xd835	,0xdd6a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,26	,0xd835	,0xdd6b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Double-struck symbols uppercase																			}, //
{'A'           		,27	,0xd835	,0xdd38	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,27	,0xd835	,0xdd39	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,27	,0xd835	,0x2102	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,27	,0xd835	,0xdd3b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,27	,0xd835	,0xdd3c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,27	,0xd835	,0xdd3d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,27	,0xd835	,0xdd3e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,27	,0xd835	,0x210d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,27	,0xd835	,0xdd40	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,27	,0xd835	,0xdd41	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,27	,0xd835	,0xdd42	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,27	,0xd835	,0xdd43	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,27	,0xd835	,0xdd44	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,27	,0xd835	,0x2115	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,27	,0xd835	,0xdd46	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,27	,0xd835	,0x2119	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,27	,0xd835	,0x211a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,27	,0xd835	,0x211d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,27	,0xd835	,0xdd4a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,27	,0xd835	,0xdd4b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,27	,0xd835	,0xdd4c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,27	,0xd835	,0xdd4d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,27	,0xd835	,0xdd4e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,27	,0xd835	,0xdd4f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,27	,0xd835	,0xdd50	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,27	,0xd835	,0x2124	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Bold symbols digits																			}, //
{'0'           		,28	,0xd835	,0xdfce	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'1'           		,28	,0xd835	,0xdfcf	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'2'           		,28	,0xd835	,0xdfd0	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'3'           		,28	,0xd835	,0xdfd1	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'4'           		,28	,0xd835	,0xdfd2	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'5'           		,28	,0xd835	,0xdfd3	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'6'           		,28	,0xd835	,0xdfd4	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'7'           		,28	,0xd835	,0xdfd5	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'8'           		,28	,0xd835	,0xdfd6	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'9'           		,28	,0xd835	,0xdfd7	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Bold symbols lowercase																			}, //
{'A'           		,28	,0xd835	,0xdc1a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,28	,0xd835	,0xdc1b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,28	,0xd835	,0xdc1c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,28	,0xd835	,0xdc1d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,28	,0xd835	,0xdc1e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,28	,0xd835	,0xdc1f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,28	,0xd835	,0xdc20	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,28	,0xd835	,0xdc21	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,28	,0xd835	,0xdc22	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,28	,0xd835	,0xdc23	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,28	,0xd835	,0xdc24	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,28	,0xd835	,0xdc25	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,28	,0xd835	,0xdc26	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,28	,0xd835	,0xdc27	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,28	,0xd835	,0xdc28	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,28	,0xd835	,0xdc29	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,28	,0xd835	,0xdc2a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,28	,0xd835	,0xdc2b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,28	,0xd835	,0xdc2c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,28	,0xd835	,0xdc2d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,28	,0xd835	,0xdc2e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,28	,0xd835	,0xdc2f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,28	,0xd835	,0xdc30	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,28	,0xd835	,0xdc31	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,28	,0xd835	,0xdc32	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,28	,0xd835	,0xdc33	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Bold symbols uppercase																			}, //
{'A'           		,29	,0xd835	,0xdc00	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,29	,0xd835	,0xdc01	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,29	,0xd835	,0xdc02	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,29	,0xd835	,0xdc03	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,29	,0xd835	,0xdc04	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,29	,0xd835	,0xdc05	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,29	,0xd835	,0xdc06	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,29	,0xd835	,0xdc07	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,29	,0xd835	,0xdc08	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,29	,0xd835	,0xdc09	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,29	,0xd835	,0xdc0a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,29	,0xd835	,0xdc0b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,29	,0xd835	,0xdc0c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,29	,0xd835	,0xdc0d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,29	,0xd835	,0xdc0e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,29	,0xd835	,0xdc0f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,29	,0xd835	,0xdc10	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,29	,0xd835	,0xdc11	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,29	,0xd835	,0xdc12	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,29	,0xd835	,0xdc13	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,29	,0xd835	,0xdc14	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,29	,0xd835	,0xdc15	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,29	,0xd835	,0xdc16	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,29	,0xd835	,0xdc17	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,29	,0xd835	,0xdc18	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,29	,0xd835	,0xdc19	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Italic symbols lowercase																			}, //
{'A'           		,30	,0xd835	,0xdc4e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,30	,0xd835	,0xdc4f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,30	,0xd835	,0xdc50	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,30	,0xd835	,0xdc51	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,30	,0xd835	,0xdc52	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,30	,0xd835	,0xdc53	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,30	,0xd835	,0xdc54	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,30	,0x210e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,30	,0xd835	,0xdc56	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,30	,0xd835	,0xdc57	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,30	,0xd835	,0xdc58	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,30	,0xd835	,0xdc59	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,30	,0xd835	,0xdc5a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,30	,0xd835	,0xdc5b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,30	,0xd835	,0xdc5c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,30	,0xd835	,0xdc5d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,30	,0xd835	,0xdc5e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,30	,0xd835	,0xdc5f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,30	,0xd835	,0xdc60	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,30	,0xd835	,0xdc61	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,30	,0xd835	,0xdc62	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,30	,0xd835	,0xdc63	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,30	,0xd835	,0xdc64	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,30	,0xd835	,0xdc65	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,30	,0xd835	,0xdc66	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,30	,0xd835	,0xdc67	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
// Italic symbols uppercase																			}, //
{'A'           		,31	,0xd835	,0xdc34	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'B'           		,31	,0xd835	,0xdc35	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'C'           		,31	,0xd835	,0xdc36	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'D'           		,31	,0xd835	,0xdc37	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'E'           		,31	,0xd835	,0xdc38	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'F'           		,31	,0xd835	,0xdc39	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'G'           		,31	,0xd835	,0xdc3a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'H'           		,31	,0xd835	,0xdc3b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'I'           		,31	,0xd835	,0xdc3c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'J'           		,31	,0xd835	,0xdc3d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'K'           		,31	,0xd835	,0xdc3e	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'L'           		,31	,0xd835	,0xdc3f	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'M'           		,31	,0xd835	,0xdc40	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'N'           		,31	,0xd835	,0xdc41	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'O'           		,31	,0xd835	,0xdc42	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'P'           		,31	,0xd835	,0xdc43	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Q'           		,31	,0xd835	,0xdc44	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'R'           		,31	,0xd835	,0xdc45	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'S'           		,31	,0xd835	,0xdc46	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'T'           		,31	,0xd835	,0xdc47	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'U'           		,31	,0xd835	,0xdc48	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'V'           		,31	,0xd835	,0xdc49	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'W'           		,31	,0xd835	,0xdc4a	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'X'           		,31	,0xd835	,0xdc4b	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Y'           		,31	,0xd835	,0xdc4c	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{'Z'           		,31	,0xd835	,0xdc4d	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	,NONE	}, //
{0             		,0	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	,',0'	}, //

/*** TABLE OF SEQUENCES: END OF PASTE-AND-REPLACE **§*/
};

/**********************************************************************\
* aKeyNamesDead[]  -  Character to Dead Key Name table
*
* This list contains only the main names. Strictly only the names
* of the dead keys in the Base shift state are required.
* The only use is to make available some information to
* the GetKeyNameText function.
*
* Extensively speaking about, every dead key, even intermediate
* links in dead key chains, should be named. But this is not required
* because there is no use of supplemental dead key names, neither for
* DeadKeyNameText, nor to ensure the functionality of dead keys.
\**********************************************************************/
static ALLOC_SECTION_LDATA DEADKEY_LPWSTR aKeyNamesDead[] = {
	// 3 dead keys in the Base shift state:
    L"\x00ea"	L"ACCENT CIRCONFLEXE",
    L"\x00eb"	L"TRÉMA",
    L"\x00f3"	L"ACCENT AIGU",
	// 2 dead keys with non-obvious names:
    L"\x00a6"	L"COMPOSE",
    L"\x00b2"	L"SÉLECTEUR DE GROUPE",
    NULL
};

/**************************************************************************\
* aDeadKey[]  -  map Base Characters to Combined Characters
*                 depending on Dead Key
*
* What is called Dead Key Repertories are subsets of this
* Deadtrans Function List, also called Deadlist.
*
* When speaking of a dead key, we mean the intersection of a key and a level.
*
* This layout contains 35 real dead keys:
*   6 easy dead keys on 3 keys (duplicates);
*  19 diacritic dead keys on 19 keys;
*   4 symbol dead keys (superscript, subscript, currency, scientific [Numbers level]);
*   4 script dead keys (Greek, Cyrillic, Arabic, Hebrew);
*   1 group selector dead key (11 supplemental layout groups);
*   1 composition dead key (neutral dead key; dead char is '¦').
*
* The layout-specific compose functionality is implemented in this deadlist.
* It uses the dead key chaining feature available on Windows.
* All intermediate dead states occurring in any dead sequence (starting with
* a real dead key followed by two or more dead or live keys) are called
* virtual dead keys. These are very numerous.
*
* The DEADTRANS function has four arguments:
* 1  Base character: The code unit after the dead key entry.
* 2  Dead key character: The code unit of the dead key.
* 3  Combined character: The code unit that is potentially output.
* 4  Dead key flag: Allows to define chained dead keys.
*
* Values of WCHARs:
* In this allocation section, ASCII characters are preceded by 'L'.
*
* CAUTION:
* Windows is architecturally limited to output no more than one single
* WCHAR at the issue of a dead key sequence.
* The leading surrogate of SMP characters must be input previously.
* So far as the characters on this keyboard are concerned, only five
* leading surrogate code units are used. These five high surrogates
* are input using five dedicated key positions on Shift+Kana.
*
* Values of Dead Key Flag:
* |Text: |Hex:  | (By define, these two forms are equivalent.)
*  DKF_0  0x0000  The combined character is inserted.
*  CHAIN  0x0001  The combined character is processed as a dead key,
*                 and a next base character is waited for.
* NOTES:
* > CHAIN is originally DKF_DEAD. Shortening facilitates tabulation
*   source layout for spreadsheet-aided modification.
* > DKF_0 has been added for transparency and shortening.
* > DKF_1 has been added to complete, though it is not used below.
*
* Chained dead keys:
*
* > Purposes:
*   1) Multiply diacriticized precomposed characters.
*   2) Composed mathematical and other symbols and pictographs.
*   3) Compose key implementation using chained dead keys.
*
* > How to:
*   To chain a dead key, put the dead key flag to 1 (CHAIN).
*   Add at least one entry which has this character as a dead
*   character argument.
*   These entries may be chained again.
*
* CAUTION:
* WHEN THE LAST KEYPRESS IS ON ALTGR OR SHIFT+ALTGR SHIFT STATE,
* DEADKEYS ARE DISABLED ON MICROSOFT WORD.
* There are two known workarounds:
* 1  Provide alternate input sequences for these characters.
* 2  Set the dead key flag to 1. The character will be inserted
*    along with the following.
\**************************************************************************/
static ALLOC_SECTION_LDATA DEADKEY aDeadKey[] = {
// 	|Label	|Function	|Base	|Diacri	|Combin	|Flag	|Description
/*** DEADTRANS LIST: START OF PASTE-AND-REPLACE HERE BELOW **§*/

/*ACUTE&DOT_ABOVE    */	DEADTRANS(	L'S'	,0x1e65	,0x1e64	,DKF_0	), // LATIN CAPITAL LETTER S WITH ACUTE AND DOT ABOVE
/*ACUTE&DOT_ABOVE    */	DEADTRANS(	L's'	,0x1e65	,0x1e65	,DKF_0	), // LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE
/*ACUTE_ACCENT       */	DEADTRANS(	0x0020	,0x00e1	,0x0301	,DKF_0	), // COMBINING ACUTE ACCENT
/*ACUTE_ACCENT       */	DEADTRANS(	0x00a0	,0x00e1	,0x00b4	,DKF_0	), // ACUTE ACCENT
/*ACUTE_ACCENT       */	DEADTRANS(	0x202f	,0x00e1	,0x02ca	,DKF_0	), // MODIFIER LETTER ACUTE ACCENT
/*ACUTE_ACCENT       */	DEADTRANS(	L'A'	,0x00e1	,0x00c1	,DKF_0	), // LATIN CAPITAL LETTER A WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'a'	,0x00e1	,0x00e1	,DKF_0	), // LATIN SMALL LETTER A WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'B'	,0x00e1	,0x00d1	,DKF_0	), // LATIN CAPITAL LETTER N WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	L'b'	,0x00e1	,0x00f1	,DKF_0	), // LATIN SMALL LETTER N WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	L'C'	,0x00e1	,0x0106	,DKF_0	), // LATIN CAPITAL LETTER C WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'c'	,0x00e1	,0x0107	,DKF_0	), // LATIN SMALL LETTER C WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'D'	,0x00e1	,0x0189	,DKF_0	), // LATIN CAPITAL LETTER AFRICAN D
/*ACUTE_ACCENT       */	DEADTRANS(	L'd'	,0x00e1	,0x0256	,DKF_0	), // LATIN SMALL LETTER D WITH TAIL
/*ACUTE_ACCENT       */	DEADTRANS(	L'E'	,0x00e1	,0x00c9	,DKF_0	), // LATIN CAPITAL LETTER E WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'e'	,0x00e1	,0x00e9	,DKF_0	), // LATIN SMALL LETTER E WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'F'	,0x00e1	,0x018e	,DKF_0	), // LATIN CAPITAL LETTER REVERSED E
/*ACUTE_ACCENT       */	DEADTRANS(	L'f'	,0x00e1	,0x01dd	,DKF_0	), // LATIN SMALL LETTER TURNED E
/*ACUTE_ACCENT       */	DEADTRANS(	L'G'	,0x00e1	,0x01f4	,DKF_0	), // LATIN CAPITAL LETTER G WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'g'	,0x00e1	,0x01f5	,DKF_0	), // LATIN SMALL LETTER G WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'H'	,0x00e1	,0x1e24	,DKF_0	), // LATIN CAPITAL LETTER H WITH DOT BELOW
/*ACUTE_ACCENT       */	DEADTRANS(	L'h'	,0x00e1	,0x1e25	,DKF_0	), // LATIN SMALL LETTER H WITH DOT BELOW
/*ACUTE_ACCENT       */	DEADTRANS(	L'I'	,0x00e1	,0x00cd	,DKF_0	), // LATIN CAPITAL LETTER I WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'i'	,0x00e1	,0x00ed	,DKF_0	), // LATIN SMALL LETTER I WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'J'	,0x00e1	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*ACUTE_ACCENT       */	DEADTRANS(	L'j'	,0x00e1	,0x0272	,DKF_0	), // LATIN SMALL LETTER N WITH LEFT HOOK
/*ACUTE_ACCENT       */	DEADTRANS(	L'K'	,0x00e1	,0x1e30	,DKF_0	), // LATIN CAPITAL LETTER K WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'k'	,0x00e1	,0x1e31	,DKF_0	), // LATIN SMALL LETTER K WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'L'	,0x00e1	,0x0139	,DKF_0	), // LATIN CAPITAL LETTER L WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'l'	,0x00e1	,0x013a	,DKF_0	), // LATIN SMALL LETTER L WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'M'	,0x00e1	,0x1e3e	,DKF_0	), // LATIN CAPITAL LETTER M WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'm'	,0x00e1	,0x1e3f	,DKF_0	), // LATIN SMALL LETTER M WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'N'	,0x00e1	,0x0143	,DKF_0	), // LATIN CAPITAL LETTER N WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'n'	,0x00e1	,0x0144	,DKF_0	), // LATIN SMALL LETTER N WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'O'	,0x00e1	,0x00d3	,DKF_0	), // LATIN CAPITAL LETTER O WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'o'	,0x00e1	,0x00f3	,DKF_0	), // LATIN SMALL LETTER O WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'P'	,0x00e1	,0x1e54	,DKF_0	), // LATIN CAPITAL LETTER P WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'p'	,0x00e1	,0x1e55	,DKF_0	), // LATIN SMALL LETTER P WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'Q'	,0x00e1	,0x00a6	,CHAIN	), // BROKEN BAR
/*ACUTE_ACCENT       */	DEADTRANS(	L'q'	,0x00e1	,0x00a6	,CHAIN	), // BROKEN BAR
/*ACUTE_ACCENT       */	DEADTRANS(	L'R'	,0x00e1	,0x0154	,DKF_0	), // LATIN CAPITAL LETTER R WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'r'	,0x00e1	,0x0155	,DKF_0	), // LATIN SMALL LETTER R WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'S'	,0x00e1	,0x015a	,DKF_0	), // LATIN CAPITAL LETTER S WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L's'	,0x00e1	,0x015b	,DKF_0	), // LATIN SMALL LETTER S WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'T'	,0x00e1	,0x01ae	,DKF_0	), // LATIN CAPITAL LETTER T WITH RETROFLEX HOOK
/*ACUTE_ACCENT       */	DEADTRANS(	L't'	,0x00e1	,0x0288	,DKF_0	), // LATIN SMALL LETTER T WITH RETROFLEX HOOK
/*ACUTE_ACCENT       */	DEADTRANS(	L'U'	,0x00e1	,0x00da	,DKF_0	), // LATIN CAPITAL LETTER U WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'u'	,0x00e1	,0x00fa	,DKF_0	), // LATIN SMALL LETTER U WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'V'	,0x00e1	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*ACUTE_ACCENT       */	DEADTRANS(	L'v'	,0x00e1	,0x028c	,DKF_0	), // LATIN SMALL LETTER TURNED V
/*ACUTE_ACCENT       */	DEADTRANS(	L'W'	,0x00e1	,0x1e82	,DKF_0	), // LATIN CAPITAL LETTER W WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'w'	,0x00e1	,0x1e83	,DKF_0	), // LATIN SMALL LETTER W WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'X'	,0x00e1	,0x014a	,DKF_0	), // LATIN CAPITAL LETTER ENG
/*ACUTE_ACCENT       */	DEADTRANS(	L'x'	,0x00e1	,0x014b	,DKF_0	), // LATIN SMALL LETTER ENG
/*ACUTE_ACCENT       */	DEADTRANS(	L'Y'	,0x00e1	,0x00dd	,DKF_0	), // LATIN CAPITAL LETTER Y WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'y'	,0x00e1	,0x00fd	,DKF_0	), // LATIN SMALL LETTER Y WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'Z'	,0x00e1	,0x0179	,DKF_0	), // LATIN CAPITAL LETTER Z WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'z'	,0x00e1	,0x017a	,DKF_0	), // LATIN SMALL LETTER Z WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	L'1'	,0x00e1	,0x2032	,DKF_0	), // PRIME
/*ACUTE_ACCENT       */	DEADTRANS(	L'2'	,0x00e1	,0x2033	,DKF_0	), // DOUBLE PRIME
/*ACUTE_ACCENT       */	DEADTRANS(	L'3'	,0x00e1	,0x2034	,DKF_0	), // TRIPLE PRIME
/*ACUTE_ACCENT       */	DEADTRANS(	L'4'	,0x00e1	,0x2057	,DKF_0	), // QUADRUPLE PRIME
/*ACUTE_ACCENT       */	DEADTRANS(	L'7'	,0x00e1	,0x0294	,DKF_0	), // LATIN LETTER GLOTTAL STOP
/*ACUTE_ACCENT       */	DEADTRANS(	0x0021	,0x00e1	,0x2020	,DKF_0	), // DAGGER
/*ACUTE_ACCENT       */	DEADTRANS(	0x0022	,0x00e1	,0x201d	,DKF_0	), // RIGHT DOUBLE QUOTATION MARK
/*ACUTE_ACCENT       */	DEADTRANS(	0x0023	,0x00e1	,0x201d	,DKF_0	), // RIGHT DOUBLE QUOTATION MARK
/*ACUTE_ACCENT       */	DEADTRANS(	0x0025	,0x00e1	,0x2030	,DKF_0	), // PER MILLE SIGN
/*ACUTE_ACCENT       */	DEADTRANS(	0x0027	,0x00e1	,0x2019	,DKF_0	), // RIGHT SINGLE QUOTATION MARK
/*ACUTE_ACCENT       */	DEADTRANS(	0x0028	,0x00e1	,0xab45	,DKF_0	), // LATIN SMALL LETTER STIRRUP R
/*ACUTE_ACCENT       */	DEADTRANS(	0x0029	,0x00e1	,0x1eaf	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x002a	,0x00e1	,0x2022	,DKF_0	), // BULLET
/*ACUTE_ACCENT       */	DEADTRANS(	0x002b	,0x00e1	,0x00b1	,DKF_0	), // PLUS-MINUS SIGN
/*ACUTE_ACCENT       */	DEADTRANS(	0x002c	,0x00e1	,0x1edb	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x002d	,0x00e1	,0x2013	,DKF_0	), // EN DASH
/*ACUTE_ACCENT       */	DEADTRANS(	0x002e	,0x00e1	,0x1e65	,CHAIN	), // LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE
/*ACUTE_ACCENT       */	DEADTRANS(	0x002f	,0x00e1	,0x01ff	,CHAIN	), // LATIN SMALL LETTER O WITH STROKE AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x003a	,0x00e1	,0x01d8	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x003c	,0x00e1	,0x1ebf	,CHAIN	), // LATIN SMALL LETTER E WITH CIRCUMFLEX AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x003d	,0x00e1	,0x2260	,DKF_0	), // NOT EQUAL TO
/*ACUTE_ACCENT       */	DEADTRANS(	0x00b0	,0x00e1	,0x2023	,DKF_0	), // TRIANGULAR BULLET
/*ACUTE_ACCENT       */	DEADTRANS(	0x003f	,0x00e1	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*ACUTE_ACCENT       */	DEADTRANS(	0x0040	,0x00e1	,0x25cc	,DKF_0	), // DOTTED CIRCLE
/*ACUTE_ACCENT       */	DEADTRANS(	0x007c	,0x00e1	,0x1e53	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x0060	,0x00e1	,0x0295	,DKF_0	), // LATIN LETTER PHARYNGEAL VOICED FRICATIVE
/*ACUTE_ACCENT       */	DEADTRANS(	0x007e	,0x00e1	,0x1e4d	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x0152	,0x00e1	,0x00d5	,DKF_0	), // LATIN CAPITAL LETTER O WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x0153	,0x00e1	,0x00f5	,DKF_0	), // LATIN SMALL LETTER O WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00ab	,0x00e1	,0x201c	,DKF_0	), // LEFT DOUBLE QUOTATION MARK
/*ACUTE_ACCENT       */	DEADTRANS(	0x00bb	,0x00e1	,0x201d	,DKF_0	), // RIGHT DOUBLE QUOTATION MARK
/*ACUTE_ACCENT       */	DEADTRANS(	0x00c0	,0x00e1	,0x00c3	,DKF_0	), // LATIN CAPITAL LETTER A WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00c6	,0x00e1	,0x01fc	,DKF_0	), // LATIN CAPITAL LETTER AE WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00c7	,0x00e1	,0x1e08	,DKF_0	), // LATIN CAPITAL LETTER C WITH CEDILLA AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00c8	,0x00e1	,0x0241	,DKF_0	), // LATIN CAPITAL LETTER GLOTTAL STOP
/*ACUTE_ACCENT       */	DEADTRANS(	0x00c9	,0x00e1	,0x00d5	,DKF_0	), // LATIN CAPITAL LETTER O WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00d9	,0x00e1	,0x00d1	,DKF_0	), // LATIN CAPITAL LETTER N WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00e0	,0x00e1	,0x00e3	,DKF_0	), // LATIN SMALL LETTER A WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00e1	,0x00e1	,0x0151	,CHAIN	), // LATIN SMALL LETTER O WITH DOUBLE ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00e6	,0x00e1	,0x01fd	,DKF_0	), // LATIN SMALL LETTER AE WITH ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00e7	,0x00e1	,0x1e09	,DKF_0	), // LATIN SMALL LETTER C WITH CEDILLA AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00e8	,0x00e1	,0x0242	,DKF_0	), // LATIN SMALL LETTER GLOTTAL STOP
/*ACUTE_ACCENT       */	DEADTRANS(	0x00e9	,0x00e1	,0x00f5	,DKF_0	), // LATIN SMALL LETTER O WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00ea	,0x00e1	,0x1ed1	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00eb	,0x00e1	,0x01d8	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00f2	,0x00e1	,0x021f	,CHAIN	), // LATIN SMALL LETTER H WITH CARON
/*ACUTE_ACCENT       */	DEADTRANS(	0x00f8	,0x00e1	,0x01ff	,CHAIN	), // LATIN SMALL LETTER O WITH STROKE AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x00f9	,0x00e1	,0x00f1	,DKF_0	), // LATIN SMALL LETTER N WITH TILDE
/*ACUTE_ACCENT       */	DEADTRANS(	0x2019	,0x00e1	,0x2019	,DKF_0	), // RIGHT SINGLE QUOTATION MARK
/*ACUTE_ACCENT       */	DEADTRANS(	0x2212	,0x00e1	,0x2012	,DKF_0	), // FIGURE DASH
/*ACUTE_ACCENT       */	DEADTRANS(	0x2610	,0x00e1	,0x2752	,DKF_0	), // UPPER RIGHT SHADOWED WHITE SQUARE
/*ACUTE_ACCENT       */	DEADTRANS(	0x222a	,0x00e1	,0x2282	,DKF_0	), // SUBSET OF
/*ACUTE_ACCENT       */	DEADTRANS(	0x0101	,0x00e1	,0x1e53	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x0115	,0x00e1	,0x1eaf	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x0229	,0x00e1	,0x1edb	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x01a1	,0x00e1	,0x1edb	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND ACUTE
/*ACUTE_ACCENT       */	DEADTRANS(	0x1e57	,0x00e1	,0x1e65	,CHAIN	), // LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE
/*ACUTE_BELOW        */	DEADTRANS(	0x0020	,0x02cf	,0x0317	,DKF_0	), // COMBINING ACUTE ACCENT BELOW
/*ACUTE_BELOW        */	DEADTRANS(	0x00a0	,0x02cf	,0x02cf	,DKF_0	), // MODIFIER LETTER LOW ACUTE ACCENT
/*ACUTE_BELOW        */	DEADTRANS(	0x202f	,0x02cf	,0x02cf	,DKF_0	), // MODIFIER LETTER LOW ACUTE ACCENT
/*BAR&STROKE         */	DEADTRANS(	L'K'	,0xa745	,0xa744	,DKF_0	), // LATIN CAPITAL LETTER K WITH STROKE AND DIAGONAL STROKE
/*BAR&STROKE         */	DEADTRANS(	L'k'	,0xa745	,0xa745	,DKF_0	), // LATIN SMALL LETTER K WITH STROKE AND DIAGONAL STROKE
/*BAR&STROKE         */	DEADTRANS(	0x222a	,0xa745	,0x2209	,DKF_0	), // NOT AN ELEMENT OF
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x0020	,0x024d	,0x0335	,DKF_0	), // COMBINING SHORT STROKE OVERLAY
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'A'	,0x024d	,0xa73a	,DKF_0	), // LATIN CAPITAL LETTER AV WITH HORIZONTAL BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'a'	,0x024d	,0xa73b	,DKF_0	), // LATIN SMALL LETTER AV WITH HORIZONTAL BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'B'	,0x024d	,0x0243	,DKF_0	), // LATIN CAPITAL LETTER B WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'b'	,0x024d	,0x0180	,DKF_0	), // LATIN SMALL LETTER B WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'C'	,0x024d	,0xa792	,DKF_0	), // LATIN CAPITAL LETTER C WITH BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'c'	,0x024d	,0xa793	,DKF_0	), // LATIN SMALL LETTER C WITH BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'D'	,0x024d	,0x0110	,DKF_0	), // LATIN CAPITAL LETTER D WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'd'	,0x024d	,0x0111	,DKF_0	), // LATIN SMALL LETTER D WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'e'	,0x024d	,0xab33	,DKF_0	), // LATIN SMALL LETTER BARRED E
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'F'	,0x024d	,0xa798	,DKF_0	), // LATIN CAPITAL LETTER F WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'f'	,0x024d	,0xa799	,DKF_0	), // LATIN SMALL LETTER F WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'G'	,0x024d	,0x01e4	,DKF_0	), // LATIN CAPITAL LETTER G WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'g'	,0x024d	,0x01e5	,DKF_0	), // LATIN SMALL LETTER G WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'H'	,0x024d	,0x0126	,DKF_0	), // LATIN CAPITAL LETTER H WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'h'	,0x024d	,0x0127	,DKF_0	), // LATIN SMALL LETTER H WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'I'	,0x024d	,0x0197	,DKF_0	), // LATIN CAPITAL LETTER I WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'i'	,0x024d	,0x0268	,DKF_0	), // LATIN SMALL LETTER I WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'J'	,0x024d	,0x0248	,DKF_0	), // LATIN CAPITAL LETTER J WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'j'	,0x024d	,0x0249	,DKF_0	), // LATIN SMALL LETTER J WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'K'	,0x024d	,0xa740	,DKF_0	), // LATIN CAPITAL LETTER K WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'k'	,0x024d	,0xa741	,DKF_0	), // LATIN SMALL LETTER K WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'L'	,0x024d	,0x023d	,DKF_0	), // LATIN CAPITAL LETTER L WITH BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'l'	,0x024d	,0x019a	,DKF_0	), // LATIN SMALL LETTER L WITH BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'O'	,0x024d	,0x019f	,DKF_0	), // LATIN CAPITAL LETTER O WITH MIDDLE TILDE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'o'	,0x024d	,0x0275	,DKF_0	), // LATIN SMALL LETTER BARRED O
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'P'	,0x024d	,0x2c63	,DKF_0	), // LATIN CAPITAL LETTER P WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'p'	,0x024d	,0x1d7d	,DKF_0	), // LATIN SMALL LETTER P WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'R'	,0x024d	,0x024c	,DKF_0	), // LATIN CAPITAL LETTER R WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'r'	,0x024d	,0x024d	,DKF_0	), // LATIN SMALL LETTER R WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'T'	,0x024d	,0x0166	,DKF_0	), // LATIN CAPITAL LETTER T WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L't'	,0x024d	,0x0167	,DKF_0	), // LATIN SMALL LETTER T WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'U'	,0x024d	,0x0244	,DKF_0	), // LATIN CAPITAL LETTER U BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'u'	,0x024d	,0x0289	,DKF_0	), // LATIN SMALL LETTER U BAR
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'Y'	,0x024d	,0x024e	,DKF_0	), // LATIN CAPITAL LETTER Y WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'y'	,0x024d	,0x024f	,DKF_0	), // LATIN SMALL LETTER Y WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'Z'	,0x024d	,0x01b5	,DKF_0	), // LATIN CAPITAL LETTER Z WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'z'	,0x024d	,0x01b6	,DKF_0	), // LATIN SMALL LETTER Z WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'2'	,0x024d	,0x01bb	,DKF_0	), // LATIN LETTER TWO WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'7'	,0x024d	,0x02a1	,DKF_0	), // LATIN LETTER GLOTTAL STOP WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x0025	,0x024d	,0x01be	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x0027	,0x024d	,0x02a1	,DKF_0	), // LATIN LETTER GLOTTAL STOP WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x0029	,0x024d	,0x279c	,DKF_0	), // HEAVY ROUND-TIPPED RIGHTWARDS ARROW
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x002b	,0x024d	,0x2213	,DKF_0	), // MINUS-OR-PLUS SIGN
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x002c	,0x024d	,0x00ac	,DKF_0	), // NOT SIGN
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x002d	,0x024d	,0x2013	,CHAIN	), // EN DASH
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x002f	,0x024d	,0xa745	,CHAIN	), // LATIN SMALL LETTER K WITH STROKE AND DIAGONAL STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x003a	,0x024d	,0x00f7	,DKF_0	), // DIVISION SIGN
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x003c	,0x024d	,0x2190	,DKF_0	), // LEFTWARDS ARROW
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x003e	,0x024d	,0x2192	,DKF_0	), // RIGHTWARDS ARROW
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x003f	,0x024d	,0x02a1	,DKF_0	), // LATIN LETTER GLOTTAL STOP WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x005b	,0x024d	,0x2045	,DKF_0	), // LEFT SQUARE BRACKET WITH QUILL
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x005c	,0x024d	,0x02a2	,DKF_0	), // LATIN LETTER REVERSED GLOTTAL STOP WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x005d	,0x024d	,0x2046	,DKF_0	), // RIGHT SQUARE BRACKET WITH QUILL
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x005f	,0x024d	,0xa751	,CHAIN	), // LATIN SMALL LETTER P WITH STROKE THROUGH DESCENDER
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x007c	,0x024d	,0x2020	,DKF_0	), // DAGGER
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x007d	,0x024d	,0x2794	,DKF_0	), // HEAVY WIDE-HEADED RIGHTWARDS ARROW
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x2020	,0x024d	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x00fe	,0x024d	,0xa765	,CHAIN	), // LATIN SMALL LETTER THORN WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'a'	,0xa765	,0xab30	,DKF_0	), // LATIN SMALL LETTER BARRED ALPHA
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'c'	,0xa765	,0x0284	,DKF_0	), // LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'i'	,0xa765	,0x1d7c	,DKF_0	), // LATIN SMALL LETTER IOTA WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'l'	,0xa765	,0x019b	,DKF_0	), // LATIN SMALL LETTER LAMBDA WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L's'	,0xa765	,0x1e9d	,DKF_0	), // LATIN SMALL LETTER LONG S WITH HIGH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'T'	,0xa765	,0xa764	,DKF_0	), // LATIN CAPITAL LETTER THORN WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L't'	,0xa765	,0xa765	,DKF_0	), // LATIN SMALL LETTER THORN WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	L'u'	,0xa765	,0x1d7f	,DKF_0	), // LATIN SMALL LETTER UPSILON WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x2019	,0x024d	,0x02a1	,DKF_0	), // LATIN LETTER GLOTTAL STOP WITH STROKE
/*BAR_(HORIZONTAL)   */	DEADTRANS(	0x222a	,0x024d	,0x2208	,DKF_0	), // ELEMENT OF
/*BARRED_DESCENDER   */	DEADTRANS(	L'P'	,0xa751	,0xa750	,DKF_0	), // LATIN CAPITAL LETTER P WITH STROKE THROUGH DESCENDER
/*BARRED_DESCENDER   */	DEADTRANS(	L'p'	,0xa751	,0xa751	,DKF_0	), // LATIN SMALL LETTER P WITH STROKE THROUGH DESCENDER
/*BARRED_DESCENDER   */	DEADTRANS(	L'Q'	,0xa751	,0xa756	,DKF_0	), // LATIN CAPITAL LETTER Q WITH STROKE THROUGH DESCENDER
/*BARRED_DESCENDER   */	DEADTRANS(	L'q'	,0xa751	,0xa757	,DKF_0	), // LATIN SMALL LETTER Q WITH STROKE THROUGH DESCENDER
/*BARRED_DESCENDER   */	DEADTRANS(	L'T'	,0xa751	,0xa766	,DKF_0	), // LATIN CAPITAL LETTER THORN WITH STROKE THROUGH DESCENDER
/*BARRED_DESCENDER   */	DEADTRANS(	L't'	,0xa751	,0xa767	,DKF_0	), // LATIN SMALL LETTER THORN WITH STROKE THROUGH DESCENDER
/*BLACKLETTER        */	DEADTRANS(	L'e'	,0xab32	,0xab32	,DKF_0	), // LATIN SMALL LETTER BLACKLETTER E
/*BLACKLETTER        */	DEADTRANS(	L'o'	,0xab32	,0xab3d	,DKF_0	), // LATIN SMALL LETTER BLACKLETTER O
/*BREVE              */	DEADTRANS(	0x0020	,0x0115	,0x0306	,DKF_0	), // COMBINING BREVE
/*BREVE              */	DEADTRANS(	0x202f	,0x0115	,0x02d8	,DKF_0	), // BREVE
/*BREVE              */	DEADTRANS(	0x00a0	,0x0115	,0x222a	,DKF_0	), // UNION
/*BREVE              */	DEADTRANS(	L'A'	,0x0115	,0x0102	,DKF_0	), // LATIN CAPITAL LETTER A WITH BREVE
/*BREVE              */	DEADTRANS(	L'a'	,0x0115	,0x0103	,DKF_0	), // LATIN SMALL LETTER A WITH BREVE
/*BREVE              */	DEADTRANS(	L'E'	,0x0115	,0x0114	,DKF_0	), // LATIN CAPITAL LETTER E WITH BREVE
/*BREVE              */	DEADTRANS(	L'e'	,0x0115	,0x0115	,DKF_0	), // LATIN SMALL LETTER E WITH BREVE
/*BREVE              */	DEADTRANS(	L'G'	,0x0115	,0x011e	,DKF_0	), // LATIN CAPITAL LETTER G WITH BREVE
/*BREVE              */	DEADTRANS(	L'g'	,0x0115	,0x011f	,DKF_0	), // LATIN SMALL LETTER G WITH BREVE
/*BREVE              */	DEADTRANS(	L'H'	,0x0115	,0x1e2a	,DKF_0	), // LATIN CAPITAL LETTER H WITH BREVE BELOW
/*BREVE              */	DEADTRANS(	L'h'	,0x0115	,0x1e2b	,DKF_0	), // LATIN SMALL LETTER H WITH BREVE BELOW
/*BREVE              */	DEADTRANS(	L'I'	,0x0115	,0x012c	,DKF_0	), // LATIN CAPITAL LETTER I WITH BREVE
/*BREVE              */	DEADTRANS(	L'i'	,0x0115	,0x012d	,DKF_0	), // LATIN SMALL LETTER I WITH BREVE
/*BREVE              */	DEADTRANS(	L'n'	,0x0115	,0x0149	,DKF_0	), // LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
/*BREVE              */	DEADTRANS(	L'O'	,0x0115	,0x014e	,DKF_0	), // LATIN CAPITAL LETTER O WITH BREVE
/*BREVE              */	DEADTRANS(	L'o'	,0x0115	,0x014f	,DKF_0	), // LATIN SMALL LETTER O WITH BREVE
/*BREVE              */	DEADTRANS(	L'r'	,0x0115	,0xab47	,DKF_0	), // LATIN SMALL LETTER R WITHOUT HANDLE
/*BREVE              */	DEADTRANS(	L'U'	,0x0115	,0x016c	,DKF_0	), // LATIN CAPITAL LETTER U WITH BREVE
/*BREVE              */	DEADTRANS(	L'u'	,0x0115	,0x016d	,DKF_0	), // LATIN SMALL LETTER U WITH BREVE
/*BREVE              */	DEADTRANS(	L'y'	,0x0115	,0xab5a	,DKF_0	), // LATIN SMALL LETTER Y WITH SHORT RIGHT LEG
/*BREVE              */	DEADTRANS(	0x0021	,0x0115	,0x1eb7	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
/*BREVE              */	DEADTRANS(	0x0023	,0x0115	,0xab4e	,CHAIN	), // LATIN SMALL LETTER U WITH SHORT RIGHT LEG
/*BREVE              */	DEADTRANS(	0x0027	,0x0115	,0x1eaf	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND ACUTE
/*BREVE              */	DEADTRANS(	0x0028	,0x0115	,0xab5b	,DKF_0	), // MODIFIER BREVE WITH INVERTED BREVE
/*BREVE              */	DEADTRANS(	0x0029	,0x0115	,0x0213	,CHAIN	), // LATIN SMALL LETTER R WITH INVERTED BREVE
/*BREVE              */	DEADTRANS(	0x002c	,0x0115	,0x1e1d	,CHAIN	), // LATIN SMALL LETTER E WITH CEDILLA AND BREVE
/*BREVE              */	DEADTRANS(	0x002e	,0x0115	,0x0310	,DKF_0	), // COMBINING CANDRABINDU
/*BREVE              */	DEADTRANS(	0x005d	,0x0115	,0x1eb3	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
/*BREVE              */	DEADTRANS(	0x005f	,0x0115	,0x1dcb	,DKF_0	), // COMBINING BREVE-MACRON
/*BREVE              */	DEADTRANS(	0x0060	,0x0115	,0x1eb1	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND GRAVE
/*BREVE              */	DEADTRANS(	0x007e	,0x0115	,0x1eb5	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND TILDE
/*BREVE              */	DEADTRANS(	0x00e1	,0x0115	,0x1eaf	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND ACUTE
/*BREVE              */	DEADTRANS(	0x00f2	,0x0115	,0x1eb1	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND GRAVE
/*BREVE              */	DEADTRANS(	0x00f5	,0x0115	,0x1eb5	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND TILDE
/*BREVE              */	DEADTRANS(	0x2610	,0x0115	,0x25ef	,DKF_0	), // LARGE CIRCLE
/*BREVE              */	DEADTRANS(	0x0229	,0x0115	,0x1e1d	,CHAIN	), // LATIN SMALL LETTER E WITH CEDILLA AND BREVE
/*BREVE              */	DEADTRANS(	0x1ebb	,0x0115	,0x1eb3	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
/*BREVE              */	DEADTRANS(	0x0115	,0x0115	,0x0213	,CHAIN	), // LATIN SMALL LETTER R WITH INVERTED BREVE
/*BREVE              */	DEADTRANS(	0x014d	,0x0115	,0x1dcb	,DKF_0	), // COMBINING BREVE-MACRON
/*BREVE              */	DEADTRANS(	0x1ee5	,0x0115	,0x1eb7	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
/*BREVE&ACUTE_ACCENT */	DEADTRANS(	L'A'	,0x1eaf	,0x1eae	,DKF_0	), // LATIN CAPITAL LETTER A WITH BREVE AND ACUTE
/*BREVE&ACUTE_ACCENT */	DEADTRANS(	L'a'	,0x1eaf	,0x1eaf	,DKF_0	), // LATIN SMALL LETTER A WITH BREVE AND ACUTE
/*BREVE&DOT_BELOW    */	DEADTRANS(	L'A'	,0x1eb7	,0x1eb6	,DKF_0	), // LATIN CAPITAL LETTER A WITH BREVE AND DOT BELOW
/*BREVE&DOT_BELOW    */	DEADTRANS(	L'a'	,0x1eb7	,0x1eb7	,DKF_0	), // LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
/*BREVE&GRAVE        */	DEADTRANS(	L'A'	,0x1eb1	,0x1eb0	,DKF_0	), // LATIN CAPITAL LETTER A WITH BREVE AND GRAVE
/*BREVE&GRAVE        */	DEADTRANS(	L'a'	,0x1eb1	,0x1eb1	,DKF_0	), // LATIN SMALL LETTER A WITH BREVE AND GRAVE
/*BREVE&HOOK_ABOVE   */	DEADTRANS(	L'A'	,0x1eb3	,0x1eb2	,DKF_0	), // LATIN CAPITAL LETTER A WITH BREVE AND HOOK ABOVE
/*BREVE&HOOK_ABOVE   */	DEADTRANS(	L'a'	,0x1eb3	,0x1eb3	,DKF_0	), // LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
/*BREVE&TILDE        */	DEADTRANS(	L'A'	,0x1eb5	,0x1eb4	,DKF_0	), // LATIN CAPITAL LETTER A WITH BREVE AND TILDE
/*BREVE&TILDE        */	DEADTRANS(	L'a'	,0x1eb5	,0x1eb5	,DKF_0	), // LATIN SMALL LETTER A WITH BREVE AND TILDE
/*BREVE_BELOW        */	DEADTRANS(	0x0020	,0x1e2b	,0x032e	,DKF_0	), // COMBINING BREVE BELOW
/*BREVE_BELOW        */	DEADTRANS(	L'H'	,0x1e2b	,0x1e2a	,DKF_0	), // LATIN CAPITAL LETTER H WITH BREVE BELOW
/*BREVE_BELOW        */	DEADTRANS(	L'h'	,0x1e2b	,0x1e2b	,DKF_0	), // LATIN SMALL LETTER H WITH BREVE BELOW
/*CEDILLA            */	DEADTRANS(	0x0020	,0x0229	,0x0327	,DKF_0	), // COMBINING CEDILLA
/*CEDILLA            */	DEADTRANS(	0x00a0	,0x0229	,0x00b8	,DKF_0	), // CEDILLA
/*CEDILLA            */	DEADTRANS(	0x202f	,0x0229	,0x00b8	,DKF_0	), // CEDILLA
/*CEDILLA            */	DEADTRANS(	L'C'	,0x0229	,0x00c7	,DKF_0	), // LATIN CAPITAL LETTER C WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'c'	,0x0229	,0x00e7	,DKF_0	), // LATIN SMALL LETTER C WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'D'	,0x0229	,0x1e10	,DKF_0	), // LATIN CAPITAL LETTER D WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'd'	,0x0229	,0x1e11	,DKF_0	), // LATIN SMALL LETTER D WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'E'	,0x0229	,0x0228	,DKF_0	), // LATIN CAPITAL LETTER E WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'e'	,0x0229	,0x0229	,DKF_0	), // LATIN SMALL LETTER E WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'G'	,0x0229	,0x0122	,DKF_0	), // LATIN CAPITAL LETTER G WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'g'	,0x0229	,0x0123	,DKF_0	), // LATIN SMALL LETTER G WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'H'	,0x0229	,0x1e28	,DKF_0	), // LATIN CAPITAL LETTER H WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'h'	,0x0229	,0x1e29	,DKF_0	), // LATIN SMALL LETTER H WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'K'	,0x0229	,0x0136	,DKF_0	), // LATIN CAPITAL LETTER K WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'k'	,0x0229	,0x0137	,DKF_0	), // LATIN SMALL LETTER K WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'L'	,0x0229	,0x013b	,DKF_0	), // LATIN CAPITAL LETTER L WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'l'	,0x0229	,0x013c	,DKF_0	), // LATIN SMALL LETTER L WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'N'	,0x0229	,0x0145	,DKF_0	), // LATIN CAPITAL LETTER N WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'n'	,0x0229	,0x0146	,DKF_0	), // LATIN SMALL LETTER N WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'R'	,0x0229	,0x0156	,DKF_0	), // LATIN CAPITAL LETTER R WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'r'	,0x0229	,0x0157	,DKF_0	), // LATIN SMALL LETTER R WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'S'	,0x0229	,0x015e	,DKF_0	), // LATIN CAPITAL LETTER S WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L's'	,0x0229	,0x015f	,DKF_0	), // LATIN SMALL LETTER S WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'T'	,0x0229	,0x0162	,DKF_0	), // LATIN CAPITAL LETTER T WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L't'	,0x0229	,0x0163	,DKF_0	), // LATIN SMALL LETTER T WITH CEDILLA
/*CEDILLA            */	DEADTRANS(	L'x'	,0x0229	,0xab55	,DKF_0	), // LATIN SMALL LETTER CHI WITH LOW LEFT SERIF
/*CEDILLA            */	DEADTRANS(	0x0027	,0x0229	,0x1e09	,CHAIN	), // LATIN SMALL LETTER C WITH CEDILLA AND ACUTE
/*CEDILLA            */	DEADTRANS(	0x0029	,0x0229	,0x1e1d	,CHAIN	), // LATIN SMALL LETTER E WITH CEDILLA AND BREVE
/*CEDILLA            */	DEADTRANS(	0x002c	,0x0229	,0x01b0	,CHAIN	), // LATIN SMALL LETTER U WITH HORN
/*CEDILLA            */	DEADTRANS(	0x002f	,0x0229	,0xab59	,DKF_0	), // LATIN SMALL LETTER X WITH LONG LEFT LEG WITH SERIF
/*CEDILLA            */	DEADTRANS(	0x003b	,0x0229	,0x2c6a	,CHAIN	), // LATIN SMALL LETTER K WITH DESCENDER
/*CEDILLA            */	DEADTRANS(	0x00e1	,0x0229	,0x1e09	,CHAIN	), // LATIN SMALL LETTER C WITH CEDILLA AND ACUTE
/*CEDILLA            */	DEADTRANS(	0x0115	,0x0229	,0x1e1d	,CHAIN	), // LATIN SMALL LETTER E WITH CEDILLA AND BREVE
/*CEDILLA            */	DEADTRANS(	0x0229	,0x0229	,0x1ebb	,CHAIN	), // LATIN SMALL LETTER E WITH HOOK ABOVE
/*CEDILLA&BREVE      */	DEADTRANS(	L'E'	,0x1e1d	,0x1e1c	,DKF_0	), // LATIN CAPITAL LETTER E WITH CEDILLA AND BREVE
/*CEDILLA&BREVE      */	DEADTRANS(	L'e'	,0x1e1d	,0x1e1d	,DKF_0	), // LATIN SMALL LETTER E WITH CEDILLA AND BREVE
/*CIRCLED            */	DEADTRANS(	0x0020	,0x25ef	,0x20dd	,DKF_0	), // COMBINING ENCLOSING CIRCLE
/*CIRCLED            */	DEADTRANS(	0x0029	,0x25ef	,0x20dd	,DKF_0	), // COMBINING ENCLOSING CIRCLE
/*CIRCLED            */	DEADTRANS(	0x003e	,0x25ef	,0x20df	,DKF_0	), // COMBINING ENCLOSING DIAMOND
/*CIRCLED            */	DEADTRANS(	0x005c	,0x25ef	,0x20e0	,DKF_0	), // COMBINING ENCLOSING CIRCLE BACKSLASH
/*CIRCLED            */	DEADTRANS(	0x005d	,0x25ef	,0x20de	,DKF_0	), // COMBINING ENCLOSING SQUARE
/*CIRCLED            */	DEADTRANS(	0x00a0	,0x25ef	,0x25ef	,DKF_0	), // LARGE CIRCLE
/*CIRCLED            */	DEADTRANS(	0x202f	,0x25ef	,0x25ef	,DKF_0	), // LARGE CIRCLE
/*CIRCLED            */	DEADTRANS(	L'A'	,0x25ef	,0x24b6	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER A
/*CIRCLED            */	DEADTRANS(	L'a'	,0x25ef	,0x24d0	,DKF_0	), // CIRCLED LATIN SMALL LETTER A
/*CIRCLED            */	DEADTRANS(	L'B'	,0x25ef	,0x24b7	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER B
/*CIRCLED            */	DEADTRANS(	L'b'	,0x25ef	,0x24d1	,DKF_0	), // CIRCLED LATIN SMALL LETTER B
/*CIRCLED            */	DEADTRANS(	L'C'	,0x25ef	,0x24b8	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER C
/*CIRCLED            */	DEADTRANS(	L'c'	,0x25ef	,0x24d2	,DKF_0	), // CIRCLED LATIN SMALL LETTER C
/*CIRCLED            */	DEADTRANS(	L'D'	,0x25ef	,0x24b9	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER D
/*CIRCLED            */	DEADTRANS(	L'd'	,0x25ef	,0x24d3	,DKF_0	), // CIRCLED LATIN SMALL LETTER D
/*CIRCLED            */	DEADTRANS(	L'E'	,0x25ef	,0x24ba	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER E
/*CIRCLED            */	DEADTRANS(	L'e'	,0x25ef	,0x24d4	,DKF_0	), // CIRCLED LATIN SMALL LETTER E
/*CIRCLED            */	DEADTRANS(	L'F'	,0x25ef	,0x24bb	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER F
/*CIRCLED            */	DEADTRANS(	L'f'	,0x25ef	,0x24d5	,DKF_0	), // CIRCLED LATIN SMALL LETTER F
/*CIRCLED            */	DEADTRANS(	L'G'	,0x25ef	,0x24bc	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER G
/*CIRCLED            */	DEADTRANS(	L'g'	,0x25ef	,0x24d6	,DKF_0	), // CIRCLED LATIN SMALL LETTER G
/*CIRCLED            */	DEADTRANS(	L'H'	,0x25ef	,0x24bd	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER H
/*CIRCLED            */	DEADTRANS(	L'h'	,0x25ef	,0x24d7	,DKF_0	), // CIRCLED LATIN SMALL LETTER H
/*CIRCLED            */	DEADTRANS(	L'I'	,0x25ef	,0x24be	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER I
/*CIRCLED            */	DEADTRANS(	L'i'	,0x25ef	,0x24d8	,DKF_0	), // CIRCLED LATIN SMALL LETTER I
/*CIRCLED            */	DEADTRANS(	L'J'	,0x25ef	,0x24bf	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER J
/*CIRCLED            */	DEADTRANS(	L'j'	,0x25ef	,0x24d9	,DKF_0	), // CIRCLED LATIN SMALL LETTER J
/*CIRCLED            */	DEADTRANS(	L'K'	,0x25ef	,0x24c0	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER K
/*CIRCLED            */	DEADTRANS(	L'k'	,0x25ef	,0x24da	,DKF_0	), // CIRCLED LATIN SMALL LETTER K
/*CIRCLED            */	DEADTRANS(	L'L'	,0x25ef	,0x24c1	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER L
/*CIRCLED            */	DEADTRANS(	L'l'	,0x25ef	,0x24db	,DKF_0	), // CIRCLED LATIN SMALL LETTER L
/*CIRCLED            */	DEADTRANS(	L'M'	,0x25ef	,0x24c2	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER M
/*CIRCLED            */	DEADTRANS(	L'm'	,0x25ef	,0x24dc	,DKF_0	), // CIRCLED LATIN SMALL LETTER M
/*CIRCLED            */	DEADTRANS(	L'N'	,0x25ef	,0x24c3	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER N
/*CIRCLED            */	DEADTRANS(	L'n'	,0x25ef	,0x24dd	,DKF_0	), // CIRCLED LATIN SMALL LETTER N
/*CIRCLED            */	DEADTRANS(	L'O'	,0x25ef	,0x24c4	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER O
/*CIRCLED            */	DEADTRANS(	L'o'	,0x25ef	,0x24de	,DKF_0	), // CIRCLED LATIN SMALL LETTER O
/*CIRCLED            */	DEADTRANS(	L'P'	,0x25ef	,0x24c5	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER P
/*CIRCLED            */	DEADTRANS(	L'p'	,0x25ef	,0x24df	,DKF_0	), // CIRCLED LATIN SMALL LETTER P
/*CIRCLED            */	DEADTRANS(	L'Q'	,0x25ef	,0x24c6	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER Q
/*CIRCLED            */	DEADTRANS(	L'q'	,0x25ef	,0x24e0	,DKF_0	), // CIRCLED LATIN SMALL LETTER Q
/*CIRCLED            */	DEADTRANS(	L'R'	,0x25ef	,0x24c7	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER R
/*CIRCLED            */	DEADTRANS(	L'r'	,0x25ef	,0x24e1	,DKF_0	), // CIRCLED LATIN SMALL LETTER R
/*CIRCLED            */	DEADTRANS(	L'S'	,0x25ef	,0x24c8	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER S
/*CIRCLED            */	DEADTRANS(	L's'	,0x25ef	,0x24e2	,DKF_0	), // CIRCLED LATIN SMALL LETTER S
/*CIRCLED            */	DEADTRANS(	L'T'	,0x25ef	,0x24c9	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER T
/*CIRCLED            */	DEADTRANS(	L't'	,0x25ef	,0x24e3	,DKF_0	), // CIRCLED LATIN SMALL LETTER T
/*CIRCLED            */	DEADTRANS(	L'U'	,0x25ef	,0x24ca	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER U
/*CIRCLED            */	DEADTRANS(	L'u'	,0x25ef	,0x24e4	,DKF_0	), // CIRCLED LATIN SMALL LETTER U
/*CIRCLED            */	DEADTRANS(	L'V'	,0x25ef	,0x24cb	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER V
/*CIRCLED            */	DEADTRANS(	L'v'	,0x25ef	,0x24e5	,DKF_0	), // CIRCLED LATIN SMALL LETTER V
/*CIRCLED            */	DEADTRANS(	L'W'	,0x25ef	,0x24cc	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER W
/*CIRCLED            */	DEADTRANS(	L'w'	,0x25ef	,0x24e6	,DKF_0	), // CIRCLED LATIN SMALL LETTER W
/*CIRCLED            */	DEADTRANS(	L'X'	,0x25ef	,0x24cd	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER X
/*CIRCLED            */	DEADTRANS(	L'x'	,0x25ef	,0x24e7	,DKF_0	), // CIRCLED LATIN SMALL LETTER X
/*CIRCLED            */	DEADTRANS(	L'Y'	,0x25ef	,0x24ce	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER Y
/*CIRCLED            */	DEADTRANS(	L'y'	,0x25ef	,0x24e8	,DKF_0	), // CIRCLED LATIN SMALL LETTER Y
/*CIRCLED            */	DEADTRANS(	L'Z'	,0x25ef	,0x24cf	,DKF_0	), // CIRCLED LATIN CAPITAL LETTER Z
/*CIRCLED            */	DEADTRANS(	L'z'	,0x25ef	,0x24e9	,DKF_0	), // CIRCLED LATIN SMALL LETTER Z
/*CIRCLED            */	DEADTRANS(	L'0'	,0x25ef	,0x2469	,DKF_0	), // CIRCLED NUMBER TEN
/*CIRCLED            */	DEADTRANS(	L'1'	,0x25ef	,0x2460	,DKF_0	), // CIRCLED DIGIT ONE
/*CIRCLED            */	DEADTRANS(	L'2'	,0x25ef	,0x2461	,DKF_0	), // CIRCLED DIGIT TWO
/*CIRCLED            */	DEADTRANS(	L'3'	,0x25ef	,0x2462	,DKF_0	), // CIRCLED DIGIT THREE
/*CIRCLED            */	DEADTRANS(	L'4'	,0x25ef	,0x2463	,DKF_0	), // CIRCLED DIGIT FOUR
/*CIRCLED            */	DEADTRANS(	L'5'	,0x25ef	,0x2464	,DKF_0	), // CIRCLED DIGIT FIVE
/*CIRCLED            */	DEADTRANS(	L'6'	,0x25ef	,0x2465	,DKF_0	), // CIRCLED DIGIT SIX
/*CIRCLED            */	DEADTRANS(	L'7'	,0x25ef	,0x2466	,DKF_0	), // CIRCLED DIGIT SEVEN
/*CIRCLED            */	DEADTRANS(	L'8'	,0x25ef	,0x2467	,DKF_0	), // CIRCLED DIGIT EIGHT
/*CIRCLED            */	DEADTRANS(	L'9'	,0x25ef	,0x2468	,DKF_0	), // CIRCLED DIGIT NINE
/*CIRCLED            */	DEADTRANS(	0x0023	,0x25ef	,0x24c3	,CHAIN	), // CIRCLED LATIN CAPITAL LETTER N
/*CIRCLED            */	DEADTRANS(	0x0024	,0x25ef	,0x2780	,CHAIN	), // DINGBAT CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED            */	DEADTRANS(	0x0025	,0x25ef	,0x24ff	,CHAIN	), // NEGATIVE CIRCLED DIGIT ZERO
/*CIRCLED            */	DEADTRANS(	0x0028	,0x25ef	,0x24aa	,CHAIN	), // PARENTHESIZED LATIN SMALL LETTER O
/*CIRCLED            */	DEADTRANS(	0x002a	,0x25ef	,0x229b	,DKF_0	), // CIRCLED ASTERISK OPERATOR
/*CIRCLED            */	DEADTRANS(	0x002b	,0x25ef	,0x2295	,DKF_0	), // CIRCLED PLUS
/*CIRCLED            */	DEADTRANS(	0x002d	,0x25ef	,0x2296	,DKF_0	), // CIRCLED MINUS
/*CIRCLED            */	DEADTRANS(	0x002e	,0x25ef	,0x2299	,DKF_0	), // CIRCLED DOT OPERATOR
/*CIRCLED            */	DEADTRANS(	0x002f	,0x25ef	,0x2298	,DKF_0	), // CIRCLED DIVISION SLASH
/*CIRCLED            */	DEADTRANS(	0x003b	,0x25ef	,0x2297	,DKF_0	), // CIRCLED TIMES
/*CIRCLED            */	DEADTRANS(	0x003d	,0x25ef	,0x229c	,DKF_0	), // CIRCLED EQUALS
/*CIRCLED            */	DEADTRANS(	0x0040	,0x25ef	,0x25ce	,CHAIN	), // BULLSEYE
/*CIRCLED            */	DEADTRANS(	0x005e	,0x25ef	,0x24c3	,CHAIN	), // CIRCLED LATIN CAPITAL LETTER N
/*CIRCLED            */	DEADTRANS(	0x005f	,0x25ef	,0x229d	,DKF_0	), // CIRCLED DASH
/*CIRCLED            */	DEADTRANS(	0x007c	,0x25ef	,0x2780	,CHAIN	), // DINGBAT CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED            */	DEADTRANS(	0x00b0	,0x25ef	,0x229a	,DKF_0	), // CIRCLED RING OPERATOR
/*CIRCLED            */	DEADTRANS(	0x00d7	,0x25ef	,0x2297	,DKF_0	), // CIRCLED TIMES
/*CIRCLED            */	DEADTRANS(	0x00d9	,0x25ef	,0x24ff	,CHAIN	), // NEGATIVE CIRCLED DIGIT ZERO
/*CIRCLED            */	DEADTRANS(	0x00ea	,0x25ef	,0x24c3	,CHAIN	), // CIRCLED LATIN CAPITAL LETTER N
/*CIRCLED            */	DEADTRANS(	0x00f2	,0x25ef	,0x2780	,CHAIN	), // DINGBAT CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED            */	DEADTRANS(	0x00f5	,0x25ef	,0x2780	,CHAIN	), // DINGBAT CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED            */	DEADTRANS(	0x00f9	,0x25ef	,0x24ff	,CHAIN	), // NEGATIVE CIRCLED DIGIT ZERO
/*CIRCLED            */	DEADTRANS(	0x2212	,0x25ef	,0x2296	,DKF_0	), // CIRCLED MINUS
/*CIRCLED_##         */	DEADTRANS(	L'0'	,0x24c3	,0x24ea	,CHAIN	), // CIRCLED DIGIT ZERO
/*CIRCLED_##         */	DEADTRANS(	L'1'	,0x24c3	,0x2469	,CHAIN	), // CIRCLED NUMBER TEN
/*CIRCLED_##         */	DEADTRANS(	L'2'	,0x24c3	,0x2473	,CHAIN	), // CIRCLED NUMBER TWENTY
/*CIRCLED_##         */	DEADTRANS(	L'3'	,0x24c3	,0x325a	,CHAIN	), // CIRCLED NUMBER THIRTY
/*CIRCLED_##         */	DEADTRANS(	L'4'	,0x24c3	,0x32b5	,CHAIN	), // CIRCLED NUMBER FORTY
/*CIRCLED_##         */	DEADTRANS(	L'5'	,0x24c3	,0x32bf	,DKF_0	), // CIRCLED NUMBER FIFTY
/*CIRCLED_0#         */	DEADTRANS(	L'0'	,0x24ea	,0x24ea	,DKF_0	), // CIRCLED DIGIT ZERO
/*CIRCLED_0#         */	DEADTRANS(	L'1'	,0x24ea	,0x2460	,DKF_0	), // CIRCLED DIGIT ONE
/*CIRCLED_0#         */	DEADTRANS(	L'2'	,0x24ea	,0x2461	,DKF_0	), // CIRCLED DIGIT TWO
/*CIRCLED_0#         */	DEADTRANS(	L'3'	,0x24ea	,0x2462	,DKF_0	), // CIRCLED DIGIT THREE
/*CIRCLED_0#         */	DEADTRANS(	L'4'	,0x24ea	,0x2463	,DKF_0	), // CIRCLED DIGIT FOUR
/*CIRCLED_0#         */	DEADTRANS(	L'5'	,0x24ea	,0x2464	,DKF_0	), // CIRCLED DIGIT FIVE
/*CIRCLED_0#         */	DEADTRANS(	L'6'	,0x24ea	,0x2465	,DKF_0	), // CIRCLED DIGIT SIX
/*CIRCLED_0#         */	DEADTRANS(	L'7'	,0x24ea	,0x2466	,DKF_0	), // CIRCLED DIGIT SEVEN
/*CIRCLED_0#         */	DEADTRANS(	L'8'	,0x24ea	,0x2467	,DKF_0	), // CIRCLED DIGIT EIGHT
/*CIRCLED_0#         */	DEADTRANS(	L'9'	,0x24ea	,0x2468	,DKF_0	), // CIRCLED DIGIT NINE
/*CIRCLED_1#         */	DEADTRANS(	L'0'	,0x2469	,0x2469	,DKF_0	), // CIRCLED NUMBER TEN
/*CIRCLED_1#         */	DEADTRANS(	L'1'	,0x2469	,0x246a	,DKF_0	), // CIRCLED NUMBER ELEVEN
/*CIRCLED_1#         */	DEADTRANS(	L'2'	,0x2469	,0x246b	,DKF_0	), // CIRCLED NUMBER TWELVE
/*CIRCLED_1#         */	DEADTRANS(	L'3'	,0x2469	,0x246c	,DKF_0	), // CIRCLED NUMBER THIRTEEN
/*CIRCLED_1#         */	DEADTRANS(	L'4'	,0x2469	,0x246d	,DKF_0	), // CIRCLED NUMBER FOURTEEN
/*CIRCLED_1#         */	DEADTRANS(	L'5'	,0x2469	,0x246e	,DKF_0	), // CIRCLED NUMBER FIFTEEN
/*CIRCLED_1#         */	DEADTRANS(	L'6'	,0x2469	,0x246f	,DKF_0	), // CIRCLED NUMBER SIXTEEN
/*CIRCLED_1#         */	DEADTRANS(	L'7'	,0x2469	,0x2470	,DKF_0	), // CIRCLED NUMBER SEVENTEEN
/*CIRCLED_1#         */	DEADTRANS(	L'8'	,0x2469	,0x2471	,DKF_0	), // CIRCLED NUMBER EIGHTEEN
/*CIRCLED_1#         */	DEADTRANS(	L'9'	,0x2469	,0x2472	,DKF_0	), // CIRCLED NUMBER NINETEEN
/*CIRCLED_2#         */	DEADTRANS(	L'0'	,0x2473	,0x2473	,DKF_0	), // CIRCLED NUMBER TWENTY
/*CIRCLED_2#         */	DEADTRANS(	L'1'	,0x2473	,0x3251	,DKF_0	), // CIRCLED NUMBER TWENTY ONE
/*CIRCLED_2#         */	DEADTRANS(	L'2'	,0x2473	,0x3252	,DKF_0	), // CIRCLED NUMBER TWENTY TWO
/*CIRCLED_2#         */	DEADTRANS(	L'3'	,0x2473	,0x3253	,DKF_0	), // CIRCLED NUMBER TWENTY THREE
/*CIRCLED_2#         */	DEADTRANS(	L'4'	,0x2473	,0x3254	,DKF_0	), // CIRCLED NUMBER TWENTY FOUR
/*CIRCLED_2#         */	DEADTRANS(	L'5'	,0x2473	,0x3255	,DKF_0	), // CIRCLED NUMBER TWENTY FIVE
/*CIRCLED_2#         */	DEADTRANS(	L'6'	,0x2473	,0x3256	,DKF_0	), // CIRCLED NUMBER TWENTY SIX
/*CIRCLED_2#         */	DEADTRANS(	L'7'	,0x2473	,0x3257	,DKF_0	), // CIRCLED NUMBER TWENTY SEVEN
/*CIRCLED_2#         */	DEADTRANS(	L'8'	,0x2473	,0x3258	,DKF_0	), // CIRCLED NUMBER TWENTY EIGHT
/*CIRCLED_2#         */	DEADTRANS(	L'9'	,0x2473	,0x3259	,DKF_0	), // CIRCLED NUMBER TWENTY NINE
/*CIRCLED_3#         */	DEADTRANS(	L'0'	,0x325a	,0x325a	,DKF_0	), // CIRCLED NUMBER THIRTY
/*CIRCLED_3#         */	DEADTRANS(	L'1'	,0x325a	,0x325b	,DKF_0	), // CIRCLED NUMBER THIRTY ONE
/*CIRCLED_3#         */	DEADTRANS(	L'2'	,0x325a	,0x325c	,DKF_0	), // CIRCLED NUMBER THIRTY TWO
/*CIRCLED_3#         */	DEADTRANS(	L'3'	,0x325a	,0x325d	,DKF_0	), // CIRCLED NUMBER THIRTY THREE
/*CIRCLED_3#         */	DEADTRANS(	L'4'	,0x325a	,0x325e	,DKF_0	), // CIRCLED NUMBER THIRTY FOUR
/*CIRCLED_3#         */	DEADTRANS(	L'5'	,0x325a	,0x325f	,DKF_0	), // CIRCLED NUMBER THIRTY FIVE
/*CIRCLED_3#         */	DEADTRANS(	L'6'	,0x325a	,0x32b1	,DKF_0	), // CIRCLED NUMBER THIRTY SIX
/*CIRCLED_3#         */	DEADTRANS(	L'7'	,0x325a	,0x32b2	,DKF_0	), // CIRCLED NUMBER THIRTY SEVEN
/*CIRCLED_3#         */	DEADTRANS(	L'8'	,0x325a	,0x32b3	,DKF_0	), // CIRCLED NUMBER THIRTY EIGHT
/*CIRCLED_3#         */	DEADTRANS(	L'9'	,0x325a	,0x32b4	,DKF_0	), // CIRCLED NUMBER THIRTY NINE
/*CIRCLED_4#         */	DEADTRANS(	L'0'	,0x32b5	,0x32b5	,DKF_0	), // CIRCLED NUMBER FORTY
/*CIRCLED_4#         */	DEADTRANS(	L'1'	,0x32b5	,0x32b6	,DKF_0	), // CIRCLED NUMBER FORTY ONE
/*CIRCLED_4#         */	DEADTRANS(	L'2'	,0x32b5	,0x32b7	,DKF_0	), // CIRCLED NUMBER FORTY TWO
/*CIRCLED_4#         */	DEADTRANS(	L'3'	,0x32b5	,0x32b8	,DKF_0	), // CIRCLED NUMBER FORTY THREE
/*CIRCLED_4#         */	DEADTRANS(	L'4'	,0x32b5	,0x32b9	,DKF_0	), // CIRCLED NUMBER FORTY FOUR
/*CIRCLED_4#         */	DEADTRANS(	L'5'	,0x32b5	,0x32ba	,DKF_0	), // CIRCLED NUMBER FORTY FIVE
/*CIRCLED_4#         */	DEADTRANS(	L'6'	,0x32b5	,0x32bb	,DKF_0	), // CIRCLED NUMBER FORTY SIX
/*CIRCLED_4#         */	DEADTRANS(	L'7'	,0x32b5	,0x32bc	,DKF_0	), // CIRCLED NUMBER FORTY SEVEN
/*CIRCLED_4#         */	DEADTRANS(	L'8'	,0x32b5	,0x32bd	,DKF_0	), // CIRCLED NUMBER FORTY EIGHT
/*CIRCLED_4#         */	DEADTRANS(	L'9'	,0x32b5	,0x32be	,DKF_0	), // CIRCLED NUMBER FORTY NINE
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'0'	,0x25ce	,0x24fe	,DKF_0	), // DOUBLE CIRCLED NUMBER TEN
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'1'	,0x25ce	,0x24f5	,DKF_0	), // DOUBLE CIRCLED DIGIT ONE
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'2'	,0x25ce	,0x24f6	,DKF_0	), // DOUBLE CIRCLED DIGIT TWO
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'3'	,0x25ce	,0x24f7	,DKF_0	), // DOUBLE CIRCLED DIGIT THREE
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'4'	,0x25ce	,0x24f8	,DKF_0	), // DOUBLE CIRCLED DIGIT FOUR
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'5'	,0x25ce	,0x24f9	,DKF_0	), // DOUBLE CIRCLED DIGIT FIVE
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'6'	,0x25ce	,0x24fa	,DKF_0	), // DOUBLE CIRCLED DIGIT SIX
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'7'	,0x25ce	,0x24fb	,DKF_0	), // DOUBLE CIRCLED DIGIT SEVEN
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'8'	,0x25ce	,0x24fc	,DKF_0	), // DOUBLE CIRCLED DIGIT EIGHT
/*CIRCLED_DOUBLE     */	DEADTRANS(	L'9'	,0x25ce	,0x24fd	,DKF_0	), // DOUBLE CIRCLED DIGIT NINE
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'0'	,0x278a	,0x2793	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF NUMBER TEN
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'1'	,0x278a	,0x278a	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'2'	,0x278a	,0x278b	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT TWO
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'3'	,0x278a	,0x278c	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT THREE
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'4'	,0x278a	,0x278d	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT FOUR
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'5'	,0x278a	,0x278e	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT FIVE
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'6'	,0x278a	,0x278f	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT SIX
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'7'	,0x278a	,0x2790	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT SEVEN
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'8'	,0x278a	,0x2791	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT EIGHT
/*CIRCLED_NEG_SANS   */	DEADTRANS(	L'9'	,0x278a	,0x2792	,DKF_0	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT NINE
/*CIRCLED_NEG_SANS   */	DEADTRANS(	0x0023	,0x278a	,0xdd0c	,DKF_0	), // U+1F10C; input D83C high surrogate first; DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ZERO
/*CIRCLED_NEG_SANS   */	DEADTRANS(	0x005e	,0x278a	,0xdd0c	,DKF_0	), // U+1F10C; input D83C high surrogate first; DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ZERO
/*CIRCLED_NEG_SANS   */	DEADTRANS(	0x00ea	,0x278a	,0xdd0c	,DKF_0	), // U+1F10C; input D83C high surrogate first; DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ZERO
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'0'	,0x24ff	,0x277f	,DKF_0	), // DINGBAT NEGATIVE CIRCLED NUMBER TEN
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'1'	,0x24ff	,0x2776	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT ONE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'2'	,0x24ff	,0x2777	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT TWO
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'3'	,0x24ff	,0x2778	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT THREE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'4'	,0x24ff	,0x2779	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT FOUR
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'5'	,0x24ff	,0x277a	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT FIVE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'6'	,0x24ff	,0x277b	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT SIX
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'7'	,0x24ff	,0x277c	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT SEVEN
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'8'	,0x24ff	,0x277d	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT EIGHT
/*CIRCLED_NEGATIVE   */	DEADTRANS(	L'9'	,0x24ff	,0x277e	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT NINE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x0023	,0x24ff	,0x277f	,CHAIN	), // DINGBAT NEGATIVE CIRCLED NUMBER TEN
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x0024	,0x24ff	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x005e	,0x24ff	,0x277f	,CHAIN	), // DINGBAT NEGATIVE CIRCLED NUMBER TEN
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x007c	,0x24ff	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x007d	,0x24ff	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x00ea	,0x24ff	,0x277f	,CHAIN	), // DINGBAT NEGATIVE CIRCLED NUMBER TEN
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x00f2	,0x24ff	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_NEGATIVE   */	DEADTRANS(	0x00f5	,0x24ff	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_NEGATIVE_##*/	DEADTRANS(	L'0'	,0x277f	,0x24f4	,CHAIN	), // NEGATIVE CIRCLED NUMBER TWENTY
/*CIRCLED_NEGATIVE_##*/	DEADTRANS(	L'1'	,0x277f	,0x24eb	,CHAIN	), // NEGATIVE CIRCLED NUMBER ELEVEN
/*CIRCLED_NEGATIVE_##*/	DEADTRANS(	L'2'	,0x277f	,0x24f4	,DKF_0	), // NEGATIVE CIRCLED NUMBER TWENTY
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'1'	,0x24f4	,0x2776	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT ONE
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'2'	,0x24f4	,0x2777	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT TWO
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'3'	,0x24f4	,0x2778	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT THREE
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'4'	,0x24f4	,0x2779	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT FOUR
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'5'	,0x24f4	,0x277a	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT FIVE
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'6'	,0x24f4	,0x277b	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT SIX
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'7'	,0x24f4	,0x277c	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT SEVEN
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'8'	,0x24f4	,0x277d	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT EIGHT
/*CIRCLED_NEGATIVE_0#*/	DEADTRANS(	L'9'	,0x24f4	,0x277e	,DKF_0	), // DINGBAT NEGATIVE CIRCLED DIGIT NINE
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'0'	,0x24eb	,0x277f	,DKF_0	), // DINGBAT NEGATIVE CIRCLED NUMBER TEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'1'	,0x24eb	,0x24eb	,DKF_0	), // NEGATIVE CIRCLED NUMBER ELEVEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'2'	,0x24eb	,0x24ec	,DKF_0	), // NEGATIVE CIRCLED NUMBER TWELVE
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'3'	,0x24eb	,0x24ed	,DKF_0	), // NEGATIVE CIRCLED NUMBER THIRTEEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'4'	,0x24eb	,0x24ee	,DKF_0	), // NEGATIVE CIRCLED NUMBER FOURTEEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'5'	,0x24eb	,0x24ef	,DKF_0	), // NEGATIVE CIRCLED NUMBER FIFTEEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'6'	,0x24eb	,0x24f0	,DKF_0	), // NEGATIVE CIRCLED NUMBER SIXTEEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'7'	,0x24eb	,0x24f1	,DKF_0	), // NEGATIVE CIRCLED NUMBER SEVENTEEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'8'	,0x24eb	,0x24f2	,DKF_0	), // NEGATIVE CIRCLED NUMBER EIGHTEEN
/*CIRCLED_NEGATIVE_1#*/	DEADTRANS(	L'9'	,0x24eb	,0x24f3	,DKF_0	), // NEGATIVE CIRCLED NUMBER NINETEEN
/*CIRCLED_SANS       */	DEADTRANS(	L'0'	,0x2780	,0x2789	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF NUMBER TEN
/*CIRCLED_SANS       */	DEADTRANS(	L'1'	,0x2780	,0x2780	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_SANS       */	DEADTRANS(	L'2'	,0x2780	,0x2781	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT TWO
/*CIRCLED_SANS       */	DEADTRANS(	L'3'	,0x2780	,0x2782	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT THREE
/*CIRCLED_SANS       */	DEADTRANS(	L'4'	,0x2780	,0x2783	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT FOUR
/*CIRCLED_SANS       */	DEADTRANS(	L'5'	,0x2780	,0x2784	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT FIVE
/*CIRCLED_SANS       */	DEADTRANS(	L'6'	,0x2780	,0x2785	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT SIX
/*CIRCLED_SANS       */	DEADTRANS(	L'7'	,0x2780	,0x2786	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT SEVEN
/*CIRCLED_SANS       */	DEADTRANS(	L'8'	,0x2780	,0x2787	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT EIGHT
/*CIRCLED_SANS       */	DEADTRANS(	L'9'	,0x2780	,0x2788	,DKF_0	), // DINGBAT CIRCLED SANS-SERIF DIGIT NINE
/*CIRCLED_SANS       */	DEADTRANS(	0x0023	,0x2780	,0xdd0b	,DKF_0	), // U+1F10B; input D83C high surrogate first; DINGBAT CIRCLED SANS-SERIF DIGIT ZERO
/*CIRCLED_SANS       */	DEADTRANS(	0x0025	,0x2780	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_SANS       */	DEADTRANS(	0x005e	,0x2780	,0xdd0b	,DKF_0	), // U+1F10B; input D83C high surrogate first; DINGBAT CIRCLED SANS-SERIF DIGIT ZERO
/*CIRCLED_SANS       */	DEADTRANS(	0x00d9	,0x2780	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCLED_SANS       */	DEADTRANS(	0x00ea	,0x2780	,0xdd0b	,DKF_0	), // U+1F10B; input D83C high surrogate first; DINGBAT CIRCLED SANS-SERIF DIGIT ZERO
/*CIRCLED_SANS       */	DEADTRANS(	0x00f9	,0x2780	,0x278a	,CHAIN	), // DINGBAT NEGATIVE CIRCLED SANS-SERIF DIGIT ONE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	L'A'	,0x1ebf	,0x1ea4	,DKF_0	), // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	L'a'	,0x1ebf	,0x1ea5	,DKF_0	), // LATIN SMALL LETTER A WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	L'E'	,0x1ebf	,0x1ebe	,DKF_0	), // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	L'e'	,0x1ebf	,0x1ebf	,DKF_0	), // LATIN SMALL LETTER E WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	L'O'	,0x1ebf	,0x1ed0	,DKF_0	), // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	L'o'	,0x1ebf	,0x1ed1	,DKF_0	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	0x00c7	,0x1ebf	,0x01fe	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE AND ACUTE
/*CIRCUMFLEX&ACUTE   */	DEADTRANS(	0x00e7	,0x1ebf	,0x01ff	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE AND ACUTE
/*CIRCUMFLEX&DOT_BELO*/	DEADTRANS(	L'A'	,0x1ed9	,0x1eac	,DKF_0	), // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX&DOT_BELO*/	DEADTRANS(	L'a'	,0x1ed9	,0x1ead	,DKF_0	), // LATIN SMALL LETTER A WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX&DOT_BELO*/	DEADTRANS(	L'E'	,0x1ed9	,0x1ec6	,DKF_0	), // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX&DOT_BELO*/	DEADTRANS(	L'e'	,0x1ed9	,0x1ec7	,DKF_0	), // LATIN SMALL LETTER E WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX&DOT_BELO*/	DEADTRANS(	L'O'	,0x1ed9	,0x1ed8	,DKF_0	), // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX&DOT_BELO*/	DEADTRANS(	L'o'	,0x1ed9	,0x1ed9	,DKF_0	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX&GRAVE   */	DEADTRANS(	L'A'	,0x1ed3	,0x1ea6	,DKF_0	), // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX&GRAVE   */	DEADTRANS(	L'a'	,0x1ed3	,0x1ea7	,DKF_0	), // LATIN SMALL LETTER A WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX&GRAVE   */	DEADTRANS(	L'E'	,0x1ed3	,0x1ec0	,DKF_0	), // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX&GRAVE   */	DEADTRANS(	L'e'	,0x1ed3	,0x1ec1	,DKF_0	), // LATIN SMALL LETTER E WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX&GRAVE   */	DEADTRANS(	L'O'	,0x1ed3	,0x1ed2	,DKF_0	), // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX&GRAVE   */	DEADTRANS(	L'o'	,0x1ed3	,0x1ed3	,DKF_0	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'A'	,0x1ed5	,0x1ea8	,DKF_0	), // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'a'	,0x1ed5	,0x1ea9	,DKF_0	), // LATIN SMALL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'D'	,0x1ed5	,0x276c	,CHAIN	), // MEDIUM LEFT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'd'	,0x1ed5	,0x276c	,CHAIN	), // MEDIUM LEFT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'D'	,0x276c	,0x2770	,CHAIN	), // HEAVY LEFT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'd'	,0x276c	,0x2770	,CHAIN	), // HEAVY LEFT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0028	,0x2770	,0x2770	,DKF_0	), // HEAVY LEFT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0029	,0x2770	,0x2771	,DKF_0	), // HEAVY RIGHT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0028	,0x276c	,0x276c	,DKF_0	), // MEDIUM LEFT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0029	,0x276c	,0x276d	,DKF_0	), // MEDIUM RIGHT-POINTING ANGLE BRACKET ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'E'	,0x1ed5	,0x1ec2	,DKF_0	), // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'e'	,0x1ed5	,0x1ec3	,DKF_0	), // LATIN SMALL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'O'	,0x1ed5	,0x1ed4	,DKF_0	), // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	L'o'	,0x1ed5	,0x1ed5	,DKF_0	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0028	,0x1ed5	,0x27e8	,DKF_0	), // MATHEMATICAL LEFT ANGLE BRACKET
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0029	,0x1ed5	,0x27e9	,DKF_0	), // MATHEMATICAL RIGHT ANGLE BRACKET
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x003c	,0x1ed5	,0x276e	,DKF_0	), // HEAVY LEFT-POINTING ANGLE QUOTATION MARK ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x003e	,0x1ed5	,0x276f	,DKF_0	), // HEAVY RIGHT-POINTING ANGLE QUOTATION MARK ORNAMENT
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x005d	,0x1ed5	,0x27ea	,CHAIN	), // MATHEMATICAL LEFT DOUBLE ANGLE BRACKET
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0028	,0x27ea	,0x27ea	,DKF_0	), // MATHEMATICAL LEFT DOUBLE ANGLE BRACKET
/*CIRCUMFLEX&HOOK_ABV*/	DEADTRANS(	0x0029	,0x27ea	,0x27eb	,DKF_0	), // MATHEMATICAL RIGHT DOUBLE ANGLE BRACKET
/*CIRCUMFLEX&TILDE   */	DEADTRANS(	L'A'	,0x1ed7	,0x1eaa	,DKF_0	), // LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX&TILDE   */	DEADTRANS(	L'a'	,0x1ed7	,0x1eab	,DKF_0	), // LATIN SMALL LETTER A WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX&TILDE   */	DEADTRANS(	L'E'	,0x1ed7	,0x1ec4	,DKF_0	), // LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX&TILDE   */	DEADTRANS(	L'e'	,0x1ed7	,0x1ec5	,DKF_0	), // LATIN SMALL LETTER E WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX&TILDE   */	DEADTRANS(	L'O'	,0x1ed7	,0x1ed6	,DKF_0	), // LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX&TILDE   */	DEADTRANS(	L'o'	,0x1ed7	,0x1ed7	,DKF_0	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0020	,0x00ea	,0x0302	,DKF_0	), // COMBINING CIRCUMFLEX ACCENT
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00a0	,0x00ea	,0x005e	,DKF_0	), // CIRCUMFLEX ACCENT
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x202f	,0x00ea	,0x02c6	,DKF_0	), // MODIFIER LETTER CIRCUMFLEX ACCENT
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'A'	,0x00ea	,0x00c2	,DKF_0	), // LATIN CAPITAL LETTER A WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'a'	,0x00ea	,0x00e2	,DKF_0	), // LATIN SMALL LETTER A WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'B'	,0x00ea	,0x00a6	,DKF_0	), // BROKEN BAR
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'b'	,0x00ea	,0x00a6	,DKF_0	), // BROKEN BAR
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'C'	,0x00ea	,0x0108	,DKF_0	), // LATIN CAPITAL LETTER C WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'c'	,0x00ea	,0x0109	,DKF_0	), // LATIN SMALL LETTER C WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'E'	,0x00ea	,0x00ca	,DKF_0	), // LATIN CAPITAL LETTER E WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'e'	,0x00ea	,0x00ea	,DKF_0	), // LATIN SMALL LETTER E WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'G'	,0x00ea	,0x011c	,DKF_0	), // LATIN CAPITAL LETTER G WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'g'	,0x00ea	,0x011d	,DKF_0	), // LATIN SMALL LETTER G WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'H'	,0x00ea	,0x0124	,DKF_0	), // LATIN CAPITAL LETTER H WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'h'	,0x00ea	,0x0125	,DKF_0	), // LATIN SMALL LETTER H WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'I'	,0x00ea	,0x00ce	,DKF_0	), // LATIN CAPITAL LETTER I WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'i'	,0x00ea	,0x00ee	,DKF_0	), // LATIN SMALL LETTER I WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'J'	,0x00ea	,0x0134	,DKF_0	), // LATIN CAPITAL LETTER J WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'j'	,0x00ea	,0x0135	,DKF_0	), // LATIN SMALL LETTER J WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'K'	,0x00ea	,0x00a9	,CHAIN	), // COPYRIGHT SIGN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'k'	,0x00ea	,0x00a9	,CHAIN	), // COPYRIGHT SIGN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'O'	,0x00ea	,0x00d4	,DKF_0	), // LATIN CAPITAL LETTER O WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'o'	,0x00ea	,0x00f4	,DKF_0	), // LATIN SMALL LETTER O WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'Q'	,0x00ea	,0x0043	,DKF_0	), // LATIN CAPITAL LETTER C
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'q'	,0x00ea	,0x0063	,DKF_0	), // LATIN SMALL LETTER C
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'S'	,0x00ea	,0x015c	,DKF_0	), // LATIN CAPITAL LETTER S WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L's'	,0x00ea	,0x015d	,DKF_0	), // LATIN SMALL LETTER S WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'U'	,0x00ea	,0x00db	,DKF_0	), // LATIN CAPITAL LETTER U WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'u'	,0x00ea	,0x00fb	,DKF_0	), // LATIN SMALL LETTER U WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'W'	,0x00ea	,0x0174	,DKF_0	), // LATIN CAPITAL LETTER W WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'w'	,0x00ea	,0x0175	,DKF_0	), // LATIN SMALL LETTER W WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'X'	,0x00ea	,0x2715	,DKF_0	), // MULTIPLICATION X
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'x'	,0x00ea	,0x017f	,DKF_0	), // LATIN SMALL LETTER LONG S
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'Y'	,0x00ea	,0x0176	,DKF_0	), // LATIN CAPITAL LETTER Y WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'y'	,0x00ea	,0x0177	,DKF_0	), // LATIN SMALL LETTER Y WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'Z'	,0x00ea	,0x1e90	,DKF_0	), // LATIN CAPITAL LETTER Z WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'z'	,0x00ea	,0x1e91	,DKF_0	), // LATIN SMALL LETTER Z WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'0'	,0x00ea	,0x2070	,DKF_0	), // SUPERSCRIPT ZERO
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'1'	,0x00ea	,0x00b9	,DKF_0	), // SUPERSCRIPT ONE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'2'	,0x00ea	,0x00b2	,DKF_0	), // SUPERSCRIPT TWO
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'3'	,0x00ea	,0x00b3	,DKF_0	), // SUPERSCRIPT THREE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'4'	,0x00ea	,0x2074	,DKF_0	), // SUPERSCRIPT FOUR
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'5'	,0x00ea	,0x2075	,DKF_0	), // SUPERSCRIPT FIVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'6'	,0x00ea	,0x2076	,DKF_0	), // SUPERSCRIPT SIX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'7'	,0x00ea	,0x2077	,DKF_0	), // SUPERSCRIPT SEVEN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'8'	,0x00ea	,0x2078	,DKF_0	), // SUPERSCRIPT EIGHT
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	L'9'	,0x00ea	,0x2079	,DKF_0	), // SUPERSCRIPT NINE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0021	,0x00ea	,0x1ed9	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0022	,0x00ea	,0x201c	,DKF_0	), // LEFT DOUBLE QUOTATION MARK
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0023	,0x00ea	,0x00b3	,DKF_0	), // SUPERSCRIPT THREE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0024	,0x00ea	,0x017f	,DKF_0	), // LATIN SMALL LETTER LONG S
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0025	,0x00ea	,0x2030	,DKF_0	), // PER MILLE SIGN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0027	,0x00ea	,0x2018	,DKF_0	), // LEFT SINGLE QUOTATION MARK
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0028	,0x00ea	,0x02bf	,DKF_0	), // MODIFIER LETTER LEFT HALF RING
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0029	,0x00ea	,0x02be	,DKF_0	), // MODIFIER LETTER RIGHT HALF RING
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x002a	,0x00ea	,0x2042	,DKF_0	), // ASTERISM
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x002b	,0x00ea	,0x207a	,DKF_0	), // SUPERSCRIPT PLUS SIGN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x002c	,0x00ea	,0x02bc	,DKF_0	), // MODIFIER LETTER APOSTROPHE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x002d	,0x00ea	,0x2014	,DKF_0	), // EM DASH
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x002e	,0x00ea	,0x00b7	,DKF_0	), // MIDDLE DOT
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x002f	,0x00ea	,0x2044	,DKF_0	), // FRACTION SLASH
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003a	,0x00ea	,0x2026	,DKF_0	), // HORIZONTAL ELLIPSIS
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003b	,0x00ea	,0x2027	,DKF_0	), // HYPHENATION POINT
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003c	,0x00ea	,0x2a7d	,DKF_0	), // LESS-THAN OR SLANTED EQUAL TO
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003d	,0x00ea	,0x2266	,DKF_0	), // LESS-THAN OVER EQUAL TO
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003e	,0x00ea	,0x2276	,DKF_0	), // LESS-THAN OR GREATER-THAN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003f	,0x00ea	,0x203d	,DKF_0	), // INTERROBANG
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0040	,0x00ea	,0x25b3	,DKF_0	), // WHITE UP-POINTING TRIANGLE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x005b	,0x00ea	,0x0188	,CHAIN	), // LATIN SMALL LETTER C WITH HOOK
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0028	,0x0188	,0x2329	,DKF_0	), // LEFT-POINTING ANGLE BRACKET
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0029	,0x0188	,0x232a	,DKF_0	), // RIGHT-POINTING ANGLE BRACKET
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003c	,0x0188	,0x3008	,DKF_0	), // LEFT ANGLE BRACKET
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003e	,0x0188	,0x3009	,DKF_0	), // RIGHT ANGLE BRACKET
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x005b	,0x0188	,0x300a	,CHAIN	), // LEFT DOUBLE ANGLE BRACKET
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003c	,0x300a	,0x300a	,DKF_0	), // LEFT DOUBLE ANGLE BRACKET
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x003e	,0x300a	,0x300b	,DKF_0	), // RIGHT DOUBLE ANGLE BRACKET
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x2026	,0x0188	,0xf900	,CHAIN	), // CJK COMPATIBILITY IDEOGRAPH-F900
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x005d	,0xf900	,0x0125	,DKF_0	), // LATIN SMALL LETTER H WITH CIRCUMFLEX
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x005d	,0x00ea	,0x1ed5	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x005f	,0x00ea	,0x2264	,DKF_0	), // LESS-THAN OR EQUAL TO
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0060	,0x00ea	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x007c	,0x00ea	,0x2020	,DKF_0	), // DAGGER
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x007e	,0x00ea	,0x1ed7	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x20ac	,0x00ea	,0x20a6	,DKF_0	), // NAIRA SIGN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x2021	,0x00ea	,0x2e4b	,DKF_0	), // TRIPLE DAGGER
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0152	,0x00ea	,0x0026	,DKF_0	), // AMPERSAND
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0153	,0x00ea	,0x0026	,DKF_0	), // AMPERSAND
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0027	,0x00b2	,0x1ed1	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0060	,0x00b2	,0x1ed3	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00a7	,0x00ea	,0x00b6	,DKF_0	), // PILCROW SIGN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00ab	,0x00ea	,0x2039	,DKF_0	), // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00b5	,0x00ea	,0x2208	,DKF_0	), // ELEMENT OF
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00bb	,0x00ea	,0x203a	,DKF_0	), // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00c0	,0x00ea	,0x00c5	,DKF_0	), // LATIN CAPITAL LETTER A WITH RING ABOVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00c6	,0x00ea	,0x00ad	,DKF_0	), // SOFT HYPHEN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00c7	,0x00ea	,0x00d8	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00c8	,0x00ea	,0x0130	,DKF_0	), // LATIN CAPITAL LETTER I WITH DOT ABOVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00c9	,0x00ea	,0x00b2	,DKF_0	), // SUPERSCRIPT TWO
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00d9	,0x00ea	,0x0026	,DKF_0	), // AMPERSAND
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00e0	,0x00ea	,0x00e5	,DKF_0	), // LATIN SMALL LETTER A WITH RING ABOVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00e1	,0x00ea	,0x1ed1	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00e6	,0x00ea	,0x00ad	,DKF_0	), // SOFT HYPHEN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00e7	,0x00ea	,0x00f8	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00e8	,0x00ea	,0x0131	,DKF_0	), // LATIN SMALL LETTER DOTLESS I
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00e9	,0x00ea	,0x00b2	,DKF_0	), // SUPERSCRIPT TWO
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00ea	,0x00ea	,0x1e19	,CHAIN	), // LATIN SMALL LETTER E WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00eb	,0x00ea	,0x022f	,CHAIN	), // LATIN SMALL LETTER O WITH DOT ABOVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00f2	,0x00ea	,0x1ed3	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00f5	,0x00ea	,0x1ed7	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x00f9	,0x00ea	,0x0026	,DKF_0	), // AMPERSAND
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x02bc	,0x00ea	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x2019	,0x00ea	,0x02bc	,DKF_0	), // MODIFIER LETTER APOSTROPHE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x2212	,0x00ea	,0x207b	,DKF_0	), // SUPERSCRIPT MINUS
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x2610	,0x00ea	,0x2612	,DKF_0	), // BALLOT BOX WITH X
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x222a	,0x00ea	,0x2229	,DKF_0	), // INTERSECTION
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x1ebb	,0x00ea	,0x1ed5	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0132	,0x00ea	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x0133	,0x00ea	,0x00a5	,DKF_0	), // YEN SIGN
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x1ee5	,0x00ea	,0x1ed9	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x03b8	,0x00ea	,0x2229	,DKF_0	), // INTERSECTION
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x03f4	,0x00ea	,0x222a	,DKF_0	), // UNION
/*CIRCUMFLEX_ACCENT  */	DEADTRANS(	0x03c0	,0x00ea	,0x220b	,DKF_0	), // CONTAINS AS MEMBER
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	0x0020	,0x1e19	,0x032d	,DKF_0	), // COMBINING CIRCUMFLEX ACCENT BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	0x00a0	,0x1e19	,0xa788	,DKF_0	), // MODIFIER LETTER LOW CIRCUMFLEX ACCENT
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	0x202f	,0x1e19	,0xa788	,DKF_0	), // MODIFIER LETTER LOW CIRCUMFLEX ACCENT
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'D'	,0x1e19	,0x1e12	,DKF_0	), // LATIN CAPITAL LETTER D WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'd'	,0x1e19	,0x1e13	,DKF_0	), // LATIN SMALL LETTER D WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'E'	,0x1e19	,0x1e18	,DKF_0	), // LATIN CAPITAL LETTER E WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'e'	,0x1e19	,0x1e19	,DKF_0	), // LATIN SMALL LETTER E WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'L'	,0x1e19	,0x1e3c	,DKF_0	), // LATIN CAPITAL LETTER L WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'l'	,0x1e19	,0x1e3d	,DKF_0	), // LATIN SMALL LETTER L WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'N'	,0x1e19	,0x1e4a	,DKF_0	), // LATIN CAPITAL LETTER N WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'n'	,0x1e19	,0x1e4b	,DKF_0	), // LATIN SMALL LETTER N WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'T'	,0x1e19	,0x1e70	,DKF_0	), // LATIN CAPITAL LETTER T WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L't'	,0x1e19	,0x1e71	,DKF_0	), // LATIN SMALL LETTER T WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'U'	,0x1e19	,0x1e76	,DKF_0	), // LATIN CAPITAL LETTER U WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'u'	,0x1e19	,0x1e77	,DKF_0	), // LATIN SMALL LETTER U WITH CIRCUMFLEX BELOW
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	L'X'	,0x1e19	,0x2716	,DKF_0	), // HEAVY MULTIPLICATION X
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	0x0025	,0x1e19	,0x2031	,DKF_0	), // PER TEN THOUSAND SIGN
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	0x00ea	,0x1e19	,0x021f	,CHAIN	), // LATIN SMALL LETTER H WITH CARON
/*CIRCUMFLEX_BELOW   */	DEADTRANS(	0x2610	,0x1e19	,0x2611	,DKF_0	), // BALLOT BOX WITH CHECK
/*COMBINING_ABOVE    */	DEADTRANS(	L'A'	,0x002a	,0x031a	,DKF_0	), // COMBINING LEFT ANGLE ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	L'a'	,0x002a	,0x0363	,DKF_0	), // COMBINING LATIN SMALL LETTER A
/*COMBINING_ABOVE    */	DEADTRANS(	L'b'	,0x002a	,0x1de8	,DKF_0	), // COMBINING LATIN SMALL LETTER B
/*COMBINING_ABOVE    */	DEADTRANS(	L'c'	,0x002a	,0x0368	,DKF_0	), // COMBINING LATIN SMALL LETTER C
/*COMBINING_ABOVE    */	DEADTRANS(	L'd'	,0x002a	,0x0369	,DKF_0	), // COMBINING LATIN SMALL LETTER D
/*COMBINING_ABOVE    */	DEADTRANS(	L'e'	,0x002a	,0x0364	,DKF_0	), // COMBINING LATIN SMALL LETTER E
/*COMBINING_ABOVE    */	DEADTRANS(	L'f'	,0x002a	,0x1deb	,DKF_0	), // COMBINING LATIN SMALL LETTER F
/*COMBINING_ABOVE    */	DEADTRANS(	L'G'	,0x002a	,0x1ddb	,DKF_0	), // COMBINING LATIN LETTER SMALL CAPITAL G
/*COMBINING_ABOVE    */	DEADTRANS(	L'g'	,0x002a	,0x1dda	,DKF_0	), // COMBINING LATIN SMALL LETTER G
/*COMBINING_ABOVE    */	DEADTRANS(	L'h'	,0x002a	,0x036a	,DKF_0	), // COMBINING LATIN SMALL LETTER H
/*COMBINING_ABOVE    */	DEADTRANS(	L'i'	,0x002a	,0x0365	,DKF_0	), // COMBINING LATIN SMALL LETTER I
/*COMBINING_ABOVE    */	DEADTRANS(	L'k'	,0x002a	,0x1ddc	,DKF_0	), // COMBINING LATIN SMALL LETTER K
/*COMBINING_ABOVE    */	DEADTRANS(	L'L'	,0x002a	,0x1dde	,DKF_0	), // COMBINING LATIN LETTER SMALL CAPITAL L
/*COMBINING_ABOVE    */	DEADTRANS(	L'l'	,0x002a	,0x1ddd	,DKF_0	), // COMBINING LATIN SMALL LETTER L
/*COMBINING_ABOVE    */	DEADTRANS(	L'M'	,0x002a	,0x1ddf	,DKF_0	), // COMBINING LATIN LETTER SMALL CAPITAL M
/*COMBINING_ABOVE    */	DEADTRANS(	L'm'	,0x002a	,0x036b	,DKF_0	), // COMBINING LATIN SMALL LETTER M
/*COMBINING_ABOVE    */	DEADTRANS(	L'N'	,0x002a	,0x1de1	,DKF_0	), // COMBINING LATIN LETTER SMALL CAPITAL N
/*COMBINING_ABOVE    */	DEADTRANS(	L'n'	,0x002a	,0x1de0	,DKF_0	), // COMBINING LATIN SMALL LETTER N
/*COMBINING_ABOVE    */	DEADTRANS(	L'o'	,0x002a	,0x0366	,DKF_0	), // COMBINING LATIN SMALL LETTER O
/*COMBINING_ABOVE    */	DEADTRANS(	L'p'	,0x002a	,0x1dee	,DKF_0	), // COMBINING LATIN SMALL LETTER P
/*COMBINING_ABOVE    */	DEADTRANS(	L'R'	,0x002a	,0x1de2	,DKF_0	), // COMBINING LATIN LETTER SMALL CAPITAL R
/*COMBINING_ABOVE    */	DEADTRANS(	L'r'	,0x002a	,0x036c	,DKF_0	), // COMBINING LATIN SMALL LETTER R
/*COMBINING_ABOVE    */	DEADTRANS(	L'S'	,0x002a	,0x1dd1	,DKF_0	), // COMBINING UR ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	L's'	,0x002a	,0x1de4	,DKF_0	), // COMBINING LATIN SMALL LETTER S
/*COMBINING_ABOVE    */	DEADTRANS(	L'T'	,0x002a	,0x1df5	,DKF_0	), // COMBINING UP TACK ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	L't'	,0x002a	,0x036d	,DKF_0	), // COMBINING LATIN SMALL LETTER T
/*COMBINING_ABOVE    */	DEADTRANS(	L'u'	,0x002a	,0x0367	,DKF_0	), // COMBINING LATIN SMALL LETTER U
/*COMBINING_ABOVE    */	DEADTRANS(	L'V'	,0x002a	,0x1dc3	,DKF_0	), // COMBINING SUSPENSION MARK
/*COMBINING_ABOVE    */	DEADTRANS(	L'v'	,0x002a	,0x036e	,DKF_0	), // COMBINING LATIN SMALL LETTER V
/*COMBINING_ABOVE    */	DEADTRANS(	L'w'	,0x002a	,0x1df1	,DKF_0	), // COMBINING LATIN SMALL LETTER W
/*COMBINING_ABOVE    */	DEADTRANS(	L'X'	,0x002a	,0x033d	,DKF_0	), // COMBINING X ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	L'x'	,0x002a	,0x036f	,DKF_0	), // COMBINING LATIN SMALL LETTER X
/*COMBINING_ABOVE    */	DEADTRANS(	L'Z'	,0x002a	,0x035b	,DKF_0	), // COMBINING ZIGZAG ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	L'z'	,0x002a	,0x1de6	,DKF_0	), // COMBINING LATIN SMALL LETTER Z
/*COMBINING_ABOVE    */	DEADTRANS(	L'8'	,0x002a	,0x1ab2	,DKF_0	), // COMBINING INFINITY
/*COMBINING_ABOVE    */	DEADTRANS(	L'9'	,0x002a	,0x1dd2	,DKF_0	), // COMBINING US ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x0022	,0x002a	,0x030e	,DKF_0	), // COMBINING DOUBLE VERTICAL LINE ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x0023	,0x002a	,0x030e	,DKF_0	), // COMBINING DOUBLE VERTICAL LINE ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x0026	,0x002a	,0x0363	,DKF_0	), // COMBINING LATIN SMALL LETTER A
/*COMBINING_ABOVE    */	DEADTRANS(	0x0027	,0x002a	,0x030d	,DKF_0	), // COMBINING VERTICAL LINE ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x0028	,0x002a	,0x0351	,DKF_0	), // COMBINING LEFT HALF RING ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x0029	,0x002a	,0x0357	,DKF_0	), // COMBINING RIGHT HALF RING ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x002c	,0x002a	,0x0313	,DKF_0	), // COMBINING COMMA ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x002d	,0x002a	,0x1ab3	,DKF_0	), // COMBINING DOWNWARDS ARROW
/*COMBINING_ABOVE    */	DEADTRANS(	L'2'	,0x002a	,0x1ab3	,DKF_0	), // COMBINING DOWNWARDS ARROW
/*COMBINING_ABOVE    */	DEADTRANS(	0x005f	,0x002a	,0xfe26	,DKF_0	), // COMBINING CONJOINING MACRON
/*COMBINING_ABOVE    */	DEADTRANS(	0x002e	,0x002a	,0x0358	,DKF_0	), // COMBINING DOT ABOVE RIGHT
/*COMBINING_ABOVE    */	DEADTRANS(	0x00e1	,0x002a	,0x1dc1	,DKF_0	), // COMBINING DOTTED ACUTE ACCENT
/*COMBINING_ABOVE    */	DEADTRANS(	0x00f2	,0x002a	,0x1dc0	,DKF_0	), // COMBINING DOTTED GRAVE ACCENT
/*COMBINING_ABOVE    */	DEADTRANS(	0x002f	,0x002a	,0x1ded	,DKF_0	), // COMBINING LATIN SMALL LETTER O WITH LIGHT CENTRALIZATION STROKE
/*COMBINING_ABOVE    */	DEADTRANS(	0x003b	,0x002a	,0x1dce	,DKF_0	), // COMBINING OGONEK ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x003c	,0x002a	,0x1dfe	,DKF_0	), // COMBINING LEFT ARROWHEAD ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x003d	,0x002a	,0x033f	,DKF_0	), // COMBINING DOUBLE OVERLINE
/*COMBINING_ABOVE    */	DEADTRANS(	0x003e	,0x002a	,0x0350	,DKF_0	), // COMBINING RIGHT ARROWHEAD ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x005b	,0x002a	,0x0346	,DKF_0	), // COMBINING BRIDGE ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x007e	,0x002a	,0xfe22	,DKF_0	), // COMBINING DOUBLE TILDE LEFT HALF
/*COMBINING_ABOVE    */	DEADTRANS(	0x005d	,0x002a	,0xfe25	,DKF_0	), // COMBINING MACRON RIGHT HALF
/*COMBINING_ABOVE    */	DEADTRANS(	0x00a3	,0x002a	,0x1dd8	,DKF_0	), // COMBINING LATIN SMALL LETTER INSULAR D
/*COMBINING_ABOVE    */	DEADTRANS(	0x00a9	,0x002a	,0x1de5	,CHAIN	), // COMBINING LATIN SMALL LETTER LONG S
/*COMBINING_ABOVE    */	DEADTRANS(	0x00b0	,0x002a	,0x1de3	,DKF_0	), // COMBINING LATIN SMALL LETTER R ROTUNDA
/*COMBINING_ABOVE    */	DEADTRANS(	0x00b5	,0x002a	,0x1de7	,DKF_0	), // COMBINING LATIN SMALL LETTER ALPHA
/*COMBINING_ABOVE    */	DEADTRANS(	0x00d7	,0x002a	,0x033d	,DKF_0	), // COMBINING X ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x00e7	,0x002a	,0x1dd7	,DKF_0	), // COMBINING LATIN SMALL LETTER C CEDILLA
/*COMBINING_ABOVE    */	DEADTRANS(	0x005e	,0x002a	,0x1dcd	,DKF_0	), // COMBINING DOUBLE CIRCUMFLEX ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x00ea	,0x002a	,0x1dcd	,DKF_0	), // COMBINING DOUBLE CIRCUMFLEX ABOVE
/*COMBINING_ABOVE    */	DEADTRANS(	0x00f5	,0x002a	,0x0360	,DKF_0	), // COMBINING DOUBLE TILDE
/*COMBINING_ABOVE    */	DEADTRANS(	0x0020	,0x002a	,0x1ab0	,DKF_0	), // COMBINING DOUBLED CIRCUMFLEX ACCENT
/*COMBINING_ABOVE    */	DEADTRANS(	0x00f9	,0x002a	,0x0315	,DKF_0	), // COMBINING COMMA ABOVE RIGHT
/*COMBINING_ABOVE    */	DEADTRANS(	0x2019	,0x002a	,0x0315	,DKF_0	), // COMBINING COMMA ABOVE RIGHT
/*COMBINING_ABOVE    */	DEADTRANS(	0x00eb	,0x002a	,0x1df2	,DKF_0	), // COMBINING LATIN SMALL LETTER A WITH DIAERESIS
/*COMBINING_ABOVE    */	DEADTRANS(	0x00e0	,0x002a	,0x1df3	,DKF_0	), // COMBINING LATIN SMALL LETTER O WITH DIAERESIS
/*COMBINING_ABOVE    */	DEADTRANS(	0x00e8	,0x002a	,0x1df4	,DKF_0	), // COMBINING LATIN SMALL LETTER U WITH DIAERESIS
/*COMBINING_ABOVE    */	DEADTRANS(	0x00e9	,0x002a	,0x1df2	,DKF_0	), // COMBINING LATIN SMALL LETTER A WITH DIAERESIS
/*COMBINING_BELOW    */	DEADTRANS(	L'A'	,0x2038	,0x0349	,DKF_0	), // COMBINING LEFT ANGLE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'i'	,0x2038	,0x1dd0	,DKF_0	), // COMBINING IS BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'j'	,0x2038	,0x1ab7	,DKF_0	), // COMBINING OPEN MARK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'r'	,0x2038	,0x1dca	,DKF_0	), // COMBINING LATIN SMALL LETTER R BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L's'	,0x2038	,0x1dc2	,DKF_0	), // COMBINING SNAKE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L't'	,0x2038	,0x031d	,CHAIN	), // COMBINING UP TACK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'b'	,0x031d	,0x031e	,DKF_0	), // COMBINING DOWN TACK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'd'	,0x031d	,0x0319	,DKF_0	), // COMBINING RIGHT TACK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'g'	,0x031d	,0x0318	,DKF_0	), // COMBINING LEFT TACK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'h'	,0x031d	,0x031d	,DKF_0	), // COMBINING UP TACK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'V'	,0x2038	,0x1dff	,DKF_0	), // COMBINING RIGHT ARROWHEAD AND DOWN ARROWHEAD BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'v'	,0x2038	,0x033c	,DKF_0	), // COMBINING SEAGULL BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'w'	,0x2038	,0x1ab6	,DKF_0	), // COMBINING WIGGLY LINE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'x'	,0x2038	,0x0353	,DKF_0	), // COMBINING X BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'z'	,0x2038	,0x1dcf	,DKF_0	), // COMBINING ZIGZAG BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'8'	,0x2038	,0x035a	,DKF_0	), // COMBINING DOUBLE RING BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0022	,0x2038	,0x0348	,DKF_0	), // COMBINING DOUBLE VERTICAL LINE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0024	,0x2038	,0x00c7	,CHAIN	), // LATIN CAPITAL LETTER C WITH CEDILLA
/*COMBINING_BELOW    */	DEADTRANS(	0x0029	,0x00c7	,0x035c	,DKF_0	), // COMBINING DOUBLE BREVE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x002d	,0x00c7	,0x0362	,DKF_0	), // COMBINING DOUBLE RIGHTWARDS ARROW BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005f	,0x00c7	,0x035f	,DKF_0	), // COMBINING DOUBLE MACRON BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0027	,0x2038	,0x0329	,DKF_0	), // COMBINING VERTICAL LINE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0028	,0x2038	,0x031c	,DKF_0	), // COMBINING LEFT HALF RING BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0020	,0x1abd	,0x032f	,DKF_0	), // COMBINING INVERTED BREVE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0029	,0x1abd	,0x1abd	,DKF_0	), // COMBINING PARENTHESES BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0029	,0x2038	,0x0339	,DKF_0	), // COMBINING RIGHT HALF RING BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x002a	,0x2038	,0x0359	,DKF_0	), // COMBINING ASTERISK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x002b	,0x2038	,0x031f	,DKF_0	), // COMBINING PLUS SIGN BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x002d	,0x2038	,0x1e07	,CHAIN	), // LATIN SMALL LETTER B WITH LINE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'5'	,0x1e07	,0x034d	,DKF_0	), // COMBINING LEFT RIGHT ARROW BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'8'	,0x1e07	,0x034e	,DKF_0	), // COMBINING UPWARDS ARROW BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x002d	,0x1e07	,0x0320	,DKF_0	), // COMBINING MINUS SIGN BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005f	,0x1e07	,0xfe2d	,DKF_0	), // COMBINING CONJOINING MACRON BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x002e	,0x2038	,0x1aba	,DKF_0	), // COMBINING STRONG CENTRALIZATION STROKE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x002f	,0x2038	,0x1ab9	,DKF_0	), // COMBINING LIGHT CENTRALIZATION STROKE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x003c	,0x2038	,0x0354	,DKF_0	), // COMBINING LEFT ARROWHEAD BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x003d	,0x2038	,0x2017	,CHAIN	), // DOUBLE LOW LINE
/*COMBINING_BELOW    */	DEADTRANS(	L'j'	,0x2017	,0x1ab8	,DKF_0	), // COMBINING DOUBLE OPEN MARK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	L'x'	,0x2017	,0x1ab5	,DKF_0	), // COMBINING X-X BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0020	,0x2017	,0x0333	,DKF_0	), // COMBINING DOUBLE LOW LINE
/*COMBINING_BELOW    */	DEADTRANS(	0x0029	,0x2017	,0x032b	,DKF_0	), // COMBINING INVERTED DOUBLE ARCH BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x003d	,0x2017	,0x0347	,DKF_0	), // COMBINING EQUALS SIGN BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x00a0	,0x2017	,0x2017	,DKF_0	), // DOUBLE LOW LINE
/*COMBINING_BELOW    */	DEADTRANS(	0x00b0	,0x2017	,0x035a	,DKF_0	), // COMBINING DOUBLE RING BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x00d7	,0x2017	,0x1ab5	,DKF_0	), // COMBINING X-X BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x202f	,0x2017	,0x2017	,DKF_0	), // DOUBLE LOW LINE
/*COMBINING_BELOW    */	DEADTRANS(	0x003e	,0x2038	,0x0355	,DKF_0	), // COMBINING RIGHT ARROWHEAD BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005b	,0x2038	,0x032a	,CHAIN	), // COMBINING BRIDGE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0028	,0x032a	,0xfe27	,DKF_0	), // COMBINING LIGATURE LEFT HALF BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005b	,0x032a	,0x032a	,DKF_0	), // COMBINING BRIDGE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005f	,0x032a	,0xfe2b	,DKF_0	), // COMBINING MACRON LEFT HALF BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x007e	,0x032a	,0xfe29	,DKF_0	), // COMBINING TILDE LEFT HALF BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005d	,0x2038	,0x033a	,CHAIN	), // COMBINING INVERTED BRIDGE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0020	,0x033a	,0x0321	,DKF_0	), // COMBINING PALATALIZED HOOK BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x0028	,0x033a	,0xfe28	,DKF_0	), // COMBINING LIGATURE RIGHT HALF BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005d	,0x033a	,0x033a	,DKF_0	), // COMBINING INVERTED BRIDGE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005f	,0x033a	,0xfe2c	,DKF_0	), // COMBINING MACRON RIGHT HALF BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x007e	,0x033a	,0xfe2a	,DKF_0	), // COMBINING TILDE RIGHT HALF BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x005e	,0x2038	,0x0356	,DKF_0	), // COMBINING RIGHT ARROWHEAD AND UP ARROWHEAD BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x00d7	,0x2038	,0x0353	,DKF_0	), // COMBINING X BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x00e1	,0x2038	,0x02cf	,DKF_0	), // MODIFIER LETTER LOW ACUTE ACCENT
/*COMBINING_BELOW    */	DEADTRANS(	0x00ea	,0x2038	,0x2041	,CHAIN	), // CARET INSERTION POINT
/*COMBINING_BELOW    */	DEADTRANS(	0x0020	,0x2041	,0x032d	,DKF_0	), // COMBINING CIRCUMFLEX ACCENT BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x00ea	,0x2041	,0xa788	,DKF_0	), // MODIFIER LETTER LOW CIRCUMFLEX ACCENT
/*COMBINING_BELOW    */	DEADTRANS(	0x202f	,0x2041	,0x2041	,DKF_0	), // CARET INSERTION POINT
/*COMBINING_BELOW    */	DEADTRANS(	0x00eb	,0x2038	,0x0324	,DKF_0	), // COMBINING DIAERESIS BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x00f2	,0x2038	,0x02ce	,CHAIN	), // MODIFIER LETTER LOW GRAVE ACCENT
/*COMBINING_BELOW    */	DEADTRANS(	0x0020	,0x02ce	,0x0316	,DKF_0	), // COMBINING GRAVE ACCENT BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x202f	,0x02ce	,0x02ce	,DKF_0	), // MODIFIER LETTER LOW GRAVE ACCENT
/*COMBINING_BELOW    */	DEADTRANS(	0x00f5	,0x2038	,0x02f7	,CHAIN	), // MODIFIER LETTER LOW TILDE
/*COMBINING_BELOW    */	DEADTRANS(	0x0020	,0x02f7	,0x0330	,DKF_0	), // COMBINING TILDE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x003d	,0x02f7	,0x1dfd	,DKF_0	), // COMBINING ALMOST EQUAL TO BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x00f5	,0x02f7	,0x1dfd	,DKF_0	), // COMBINING ALMOST EQUAL TO BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x202f	,0x02f7	,0x02f7	,DKF_0	), // MODIFIER LETTER LOW TILDE
/*COMBINING_BELOW    */	DEADTRANS(	0x00f9	,0x2038	,0x0329	,DKF_0	), // COMBINING VERTICAL LINE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x2019	,0x2038	,0x0329	,DKF_0	), // COMBINING VERTICAL LINE BELOW
/*COMBINING_BELOW    */	DEADTRANS(	0x2610	,0x2038	,0x033b	,DKF_0	), // COMBINING SQUARE BELOW
/*COMBINING_OVERLAY  */	DEADTRANS(	L'P'	,0x002b	,0x204d	,DKF_0	), // BLACK RIGHTWARDS BULLET
/*COMBINING_OVERLAY  */	DEADTRANS(	L'p'	,0x002b	,0x204d	,DKF_0	), // BLACK RIGHTWARDS BULLET
/*COMBINING_OVERLAY  */	DEADTRANS(	L'Q'	,0x002b	,0x204c	,DKF_0	), // BLACK LEFTWARDS BULLET
/*COMBINING_OVERLAY  */	DEADTRANS(	L'q'	,0x002b	,0x204c	,DKF_0	), // BLACK LEFTWARDS BULLET
/*COMBINING_OVERLAY  */	DEADTRANS(	0x0025	,0x002b	,0x0337	,DKF_0	), // COMBINING SHORT SOLIDUS OVERLAY
/*COMBINING_OVERLAY  */	DEADTRANS(	0x002a	,0x002b	,0x2055	,DKF_0	), // FLOWER PUNCTUATION MARK
/*COMBINING_OVERLAY  */	DEADTRANS(	0x002b	,0x002b	,0x00b1	,DKF_0	), // PLUS-MINUS SIGN
/*COMBINING_OVERLAY  */	DEADTRANS(	0x002d	,0x002b	,0x0335	,DKF_0	), // COMBINING SHORT STROKE OVERLAY
/*COMBINING_OVERLAY  */	DEADTRANS(	0x002e	,0x002b	,0x2022	,DKF_0	), // BULLET
/*COMBINING_OVERLAY  */	DEADTRANS(	0x002f	,0x002b	,0x0338	,DKF_0	), // COMBINING LONG SOLIDUS OVERLAY
/*COMBINING_OVERLAY  */	DEADTRANS(	0x003a	,0x002b	,0x205c	,DKF_0	), // DOTTED CROSS
/*COMBINING_OVERLAY  */	DEADTRANS(	0x003d	,0x002b	,0x2043	,DKF_0	), // HYPHEN BULLET
/*COMBINING_OVERLAY  */	DEADTRANS(	0x003e	,0x002b	,0x2023	,DKF_0	), // TRIANGULAR BULLET
/*COMBINING_OVERLAY  */	DEADTRANS(	0x005f	,0x002b	,0x0336	,DKF_0	), // COMBINING LONG STROKE OVERLAY
/*COMBINING_OVERLAY  */	DEADTRANS(	0x007e	,0x002b	,0x026b	,CHAIN	), // LATIN SMALL LETTER L WITH MIDDLE TILDE
/*COMBINING_OVERLAY  */	DEADTRANS(	0x00f5	,0x002b	,0x026b	,CHAIN	), // LATIN SMALL LETTER L WITH MIDDLE TILDE
/*COMBINING_OVERLAY  */	DEADTRANS(	0x2212	,0x002b	,0x00b1	,DKF_0	), // PLUS-MINUS SIGN
/*COMMA_BELOW        */	DEADTRANS(	0x0020	,0x0219	,0x0326	,DKF_0	), // COMBINING COMMA BELOW
/*COMMA_BELOW        */	DEADTRANS(	L'J'	,0x0219	,0xa72e	,DKF_0	), // LATIN CAPITAL LETTER CUATRILLO WITH COMMA
/*COMMA_BELOW        */	DEADTRANS(	L'j'	,0x0219	,0xa72f	,DKF_0	), // LATIN SMALL LETTER CUATRILLO WITH COMMA
/*COMMA_BELOW        */	DEADTRANS(	L'S'	,0x0219	,0x0218	,DKF_0	), // LATIN CAPITAL LETTER S WITH COMMA BELOW
/*COMMA_BELOW        */	DEADTRANS(	L's'	,0x0219	,0x0219	,DKF_0	), // LATIN SMALL LETTER S WITH COMMA BELOW
/*COMMA_BELOW        */	DEADTRANS(	L'T'	,0x0219	,0x021a	,DKF_0	), // LATIN CAPITAL LETTER T WITH COMMA BELOW
/*COMMA_BELOW        */	DEADTRANS(	L't'	,0x0219	,0x021b	,DKF_0	), // LATIN SMALL LETTER T WITH COMMA BELOW
/*COMMA_BELOW        */	DEADTRANS(	L'X'	,0x0219	,0xab55	,DKF_0	), // LATIN SMALL LETTER CHI WITH LOW LEFT SERIF
/*COMMA_BELOW        */	DEADTRANS(	L'x'	,0x0219	,0xab58	,DKF_0	), // LATIN SMALL LETTER X WITH LONG LEFT LEG AND LOW RIGHT RING
/*COMPOSE            */	DEADTRANS(	0x202f	,0x00a6	,0x2384	,DKF_0	), // COMPOSITION SYMBOL
/*COMPOSE            */	DEADTRANS(	L'A'	,0x00a6	,0x0041	,CHAIN	), // LATIN CAPITAL LETTER A
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0041	,0xa732	,DKF_0	), // LATIN CAPITAL LETTER AA
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0041	,0xa732	,DKF_0	), // LATIN CAPITAL LETTER AA
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0041	,0x00c6	,DKF_0	), // LATIN CAPITAL LETTER AE
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0041	,0x00c6	,DKF_0	), // LATIN CAPITAL LETTER AE
/*COMPOSE            */	DEADTRANS(	L'I'	,0x0041	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0041	,0x2c6d	,DKF_0	), // LATIN CAPITAL LETTER ALPHA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0041	,0x2c6d	,DKF_0	), // LATIN CAPITAL LETTER ALPHA
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0041	,0xa734	,DKF_0	), // LATIN CAPITAL LETTER AO
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0041	,0xa734	,DKF_0	), // LATIN CAPITAL LETTER AO
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0041	,0x214d	,DKF_0	), // AKTIESELSKAB
/*COMPOSE            */	DEADTRANS(	L'U'	,0x0041	,0xa736	,DKF_0	), // LATIN CAPITAL LETTER AU
/*COMPOSE            */	DEADTRANS(	L'u'	,0x0041	,0xa736	,DKF_0	), // LATIN CAPITAL LETTER AU
/*COMPOSE            */	DEADTRANS(	L'V'	,0x0041	,0xa738	,DKF_0	), // LATIN CAPITAL LETTER AV
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0041	,0xa738	,DKF_0	), // LATIN CAPITAL LETTER AV
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x0041	,0xa73c	,DKF_0	), // LATIN CAPITAL LETTER AY
/*COMPOSE            */	DEADTRANS(	L'y'	,0x0041	,0xa73c	,DKF_0	), // LATIN CAPITAL LETTER AY
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0041	,0xa79a	,DKF_0	), // LATIN CAPITAL LETTER VOLAPUK AE
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0041	,0x01c2	,DKF_0	), // LATIN LETTER ALVEOLAR CLICK
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0041	,0x2100	,CHAIN	), // ACCOUNT OF
/*COMPOSE            */	DEADTRANS(	L'O'	,0x2100	,0x2100	,DKF_0	), // ACCOUNT OF
/*COMPOSE            */	DEADTRANS(	L'S'	,0x2100	,0x214d	,DKF_0	), // AKTIESELSKAB
/*COMPOSE            */	DEADTRANS(	0x005f	,0x0041	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'a'	,0x00a6	,0x0061	,CHAIN	), // LATIN SMALL LETTER A
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0061	,0xa732	,DKF_0	), // LATIN CAPITAL LETTER AA
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0061	,0xa733	,DKF_0	), // LATIN SMALL LETTER AA
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0061	,0x00c6	,DKF_0	), // LATIN CAPITAL LETTER AE
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0061	,0x00e6	,DKF_0	), // LATIN SMALL LETTER AE
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0061	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0061	,0x0251	,DKF_0	), // LATIN SMALL LETTER ALPHA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0061	,0x0251	,DKF_0	), // LATIN SMALL LETTER ALPHA
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0061	,0xa734	,DKF_0	), // LATIN CAPITAL LETTER AO
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0061	,0xa735	,DKF_0	), // LATIN SMALL LETTER AO
/*COMPOSE            */	DEADTRANS(	L's'	,0x0061	,0x2101	,DKF_0	), // ADDRESSED TO THE SUBJECT
/*COMPOSE            */	DEADTRANS(	L'u'	,0x0061	,0xa737	,DKF_0	), // LATIN SMALL LETTER AU
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0061	,0xa739	,DKF_0	), // LATIN SMALL LETTER AV
/*COMPOSE            */	DEADTRANS(	L'y'	,0x0061	,0xa73d	,DKF_0	), // LATIN SMALL LETTER AY
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0061	,0xa79b	,DKF_0	), // LATIN SMALL LETTER VOLAPUK AE
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0061	,0x01c2	,DKF_0	), // LATIN LETTER ALVEOLAR CLICK
/*COMPOSE            */	DEADTRANS(	0x0029	,0x0061	,0x1e9a	,DKF_0	), // LATIN SMALL LETTER A WITH RIGHT HALF RING
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0061	,0x2100	,CHAIN	), // ACCOUNT OF
/*COMPOSE            */	DEADTRANS(	L'o'	,0x2100	,0x2100	,DKF_0	), // ACCOUNT OF
/*COMPOSE            */	DEADTRANS(	L's'	,0x2100	,0x2101	,DKF_0	), // ADDRESSED TO THE SUBJECT
/*COMPOSE            */	DEADTRANS(	0x005c	,0x0061	,0xab31	,DKF_0	), // LATIN SMALL LETTER A REVERSED-SCHWA
/*COMPOSE            */	DEADTRANS(	0x005f	,0x0061	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'B'	,0x00a6	,0x0062	,CHAIN	), // LATIN SMALL LETTER B
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0042	,0x264e	,DKF_0	), // LIBRA
/*COMPOSE            */	DEADTRANS(	L'B'	,0x0042	,0x266d	,DKF_0	), // MUSIC FLAT SIGN
/*COMPOSE            */	DEADTRANS(	L'C'	,0x0042	,0x2658	,DKF_0	), // WHITE CHESS KNIGHT
/*COMPOSE            */	DEADTRANS(	L'D'	,0x0042	,0x2655	,DKF_0	), // WHITE CHESS QUEEN
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0042	,0x2648	,DKF_0	), // ARIES
/*COMPOSE            */	DEADTRANS(	L'F'	,0x0042	,0x2657	,DKF_0	), // WHITE CHESS BISHOP
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0042	,0xa7b4	,DKF_0	), // LATIN CAPITAL LETTER BETA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0042	,0xa7b4	,DKF_0	), // LATIN CAPITAL LETTER BETA
/*COMPOSE            */	DEADTRANS(	L'M'	,0x0042	,0x266d	,DKF_0	), // MUSIC FLAT SIGN
/*COMPOSE            */	DEADTRANS(	L'P'	,0x0042	,0x2659	,DKF_0	), // WHITE CHESS PAWN
/*COMPOSE            */	DEADTRANS(	L'Q'	,0x0042	,0x266e	,DKF_0	), // MUSIC NATURAL SIGN
/*COMPOSE            */	DEADTRANS(	L'R'	,0x0042	,0x2654	,DKF_0	), // WHITE CHESS KING
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0042	,0x2656	,DKF_0	), // WHITE CHESS ROOK
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0042	,0x0298	,DKF_0	), // LATIN LETTER BILABIAL CLICK
/*COMPOSE            */	DEADTRANS(	0x003c	,0x0042	,0x02fb	,DKF_0	), // MODIFIER LETTER BEGIN LOW TONE
/*COMPOSE            */	DEADTRANS(	0x003e	,0x0042	,0x02fc	,DKF_0	), // MODIFIER LETTER END LOW TONE
/*COMPOSE            */	DEADTRANS(	0x00c9	,0x0042	,0x2648	,DKF_0	), // ARIES
/*COMPOSE            */	DEADTRANS(	L'b'	,0x00a6	,0x0062	,CHAIN	), // LATIN SMALL LETTER B
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0062	,0x264e	,DKF_0	), // LIBRA
/*COMPOSE            */	DEADTRANS(	L'b'	,0x0062	,0x266d	,DKF_0	), // MUSIC FLAT SIGN
/*COMPOSE            */	DEADTRANS(	L'c'	,0x0062	,0x2658	,DKF_0	), // WHITE CHESS KNIGHT
/*COMPOSE            */	DEADTRANS(	L'd'	,0x0062	,0x2655	,DKF_0	), // WHITE CHESS QUEEN
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0062	,0x2648	,DKF_0	), // ARIES
/*COMPOSE            */	DEADTRANS(	L'f'	,0x0062	,0x2657	,DKF_0	), // WHITE CHESS BISHOP
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0062	,0xa7b5	,DKF_0	), // LATIN SMALL LETTER BETA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0062	,0xa7b5	,DKF_0	), // LATIN SMALL LETTER BETA
/*COMPOSE            */	DEADTRANS(	L'm'	,0x0062	,0x266d	,DKF_0	), // MUSIC FLAT SIGN
/*COMPOSE            */	DEADTRANS(	L'p'	,0x0062	,0x2659	,DKF_0	), // WHITE CHESS PAWN
/*COMPOSE            */	DEADTRANS(	L'q'	,0x0062	,0x266e	,DKF_0	), // MUSIC NATURAL SIGN
/*COMPOSE            */	DEADTRANS(	L'r'	,0x0062	,0x2654	,DKF_0	), // WHITE CHESS KING
/*COMPOSE            */	DEADTRANS(	L't'	,0x0062	,0x2656	,DKF_0	), // WHITE CHESS ROOK
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0062	,0x0298	,DKF_0	), // LATIN LETTER BILABIAL CLICK
/*COMPOSE            */	DEADTRANS(	0x003c	,0x0062	,0x02fb	,DKF_0	), // MODIFIER LETTER BEGIN LOW TONE
/*COMPOSE            */	DEADTRANS(	0x003e	,0x0062	,0x02fc	,DKF_0	), // MODIFIER LETTER END LOW TONE
/*COMPOSE            */	DEADTRANS(	0x00e9	,0x0062	,0x2648	,DKF_0	), // ARIES
/*COMPOSE            */	DEADTRANS(	L'C'	,0x00a6	,0x0043	,CHAIN	), // LATIN CAPITAL LETTER C
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0043	,0x264b	,CHAIN	), // CANCER
/*COMPOSE            */	DEADTRANS(	L'N'	,0x264b	,0x264b	,DKF_0	), // CANCER
/*COMPOSE            */	DEADTRANS(	L'P'	,0x264b	,0x2651	,DKF_0	), // CAPRICORN
/*COMPOSE            */	DEADTRANS(	L'C'	,0x0043	,0x2102	,DKF_0	), // DOUBLE-STRUCK CAPITAL C
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0043	,0xdd2f	,DKF_0	), // U+1F12F; input D83C high surrogate first; COPYLEFT SYMBOL
/*COMPOSE            */	DEADTRANS(	L'N'	,0x0043	,0x264b	,DKF_0	), // CANCER
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0043	,0xa76e	,DKF_0	), // LATIN CAPITAL LETTER CON
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0043	,0xa76e	,DKF_0	), // LATIN CAPITAL LETTER CON
/*COMPOSE            */	DEADTRANS(	L'P'	,0x0043	,0x2651	,DKF_0	), // CAPRICORN
/*COMPOSE            */	DEADTRANS(	L'R'	,0x0043	,0x00a9	,DKF_0	), // COPYRIGHT SIGN
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0043	,0x0297	,DKF_0	), // LATIN LETTER STRETCHED C
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x0043	,0x0436	,CHAIN	), // CYRILLIC SMALL LETTER ZHE
/*COMPOSE            */	DEADTRANS(	L'0'	,0x0043	,0x2648	,CHAIN	), // ARIES
/*COMPOSE            */	DEADTRANS(	L'1'	,0x0043	,0x2651	,CHAIN	), // CAPRICORN
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0043	,0xa72c	,DKF_0	), // LATIN CAPITAL LETTER CUATRILLO
/*COMPOSE            */	DEADTRANS(	0x002d	,0x0043	,0x266b	,DKF_0	), // BEAMED EIGHTH NOTES
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0043	,0x2105	,CHAIN	), // CARE OF
/*COMPOSE            */	DEADTRANS(	L'O'	,0x2105	,0x2105	,DKF_0	), // CARE OF
/*COMPOSE            */	DEADTRANS(	L'U'	,0x2105	,0x2106	,DKF_0	), // CADA UNA
/*COMPOSE            */	DEADTRANS(	0x003d	,0x0043	,0x266c	,DKF_0	), // BEAMED SIXTEENTH NOTES
/*COMPOSE            */	DEADTRANS(	0x00c9	,0x0043	,0x0297	,DKF_0	), // LATIN LETTER STRETCHED C
/*COMPOSE            */	DEADTRANS(	0x00ea	,0x0043	,0xa702	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN SHANG
/*COMPOSE            */	DEADTRANS(	0x00eb	,0x0043	,0xa700	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN PING
/*COMPOSE            */	DEADTRANS(	L'c'	,0x00a6	,0x0063	,CHAIN	), // LATIN SMALL LETTER C
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0063	,0x264b	,CHAIN	), // CANCER
/*COMPOSE            */	DEADTRANS(	L'n'	,0x264b	,0x264b	,DKF_0	), // CANCER
/*COMPOSE            */	DEADTRANS(	L'p'	,0x264b	,0x2651	,DKF_0	), // CAPRICORN
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0063	,0xab62	,DKF_0	), // LATIN SMALL LETTER OPEN OE
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0063	,0xdd2f	,DKF_0	), // U+1F12F; input D83C high surrogate first; COPYLEFT SYMBOL
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0063	,0x264b	,DKF_0	), // CANCER
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0063	,0xa76e	,DKF_0	), // LATIN CAPITAL LETTER CON
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0063	,0xa76f	,DKF_0	), // LATIN SMALL LETTER CON
/*COMPOSE            */	DEADTRANS(	L'p'	,0x0063	,0x2651	,DKF_0	), // CAPRICORN
/*COMPOSE            */	DEADTRANS(	L'r'	,0x0063	,0x00a9	,DKF_0	), // COPYRIGHT SIGN
/*COMPOSE            */	DEADTRANS(	L's'	,0x0063	,0x0297	,DKF_0	), // LATIN LETTER STRETCHED C
/*COMPOSE            */	DEADTRANS(	L'y'	,0x0063	,0x0448	,CHAIN	), // CYRILLIC SMALL LETTER SHA
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0063	,0xa72d	,DKF_0	), // LATIN SMALL LETTER CUATRILLO
/*COMPOSE            */	DEADTRANS(	0x002d	,0x0063	,0x266b	,DKF_0	), // BEAMED EIGHTH NOTES
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0063	,0x2105	,CHAIN	), // CARE OF
/*COMPOSE            */	DEADTRANS(	L'o'	,0x2105	,0x2105	,DKF_0	), // CARE OF
/*COMPOSE            */	DEADTRANS(	L'u'	,0x2105	,0x2106	,DKF_0	), // CADA UNA
/*COMPOSE            */	DEADTRANS(	0x003d	,0x0063	,0x266c	,DKF_0	), // BEAMED SIXTEENTH NOTES
/*COMPOSE            */	DEADTRANS(	0x00e9	,0x0063	,0x0297	,DKF_0	), // LATIN LETTER STRETCHED C
/*COMPOSE            */	DEADTRANS(	0x00ea	,0x0063	,0xa702	,CHAIN	), // MODIFIER LETTER CHINESE TONE YIN SHANG
/*COMPOSE            */	DEADTRANS(	0x0028	,0xa702	,0xa702	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN SHANG
/*COMPOSE            */	DEADTRANS(	0x0029	,0xa702	,0xa704	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN QU
/*COMPOSE            */	DEADTRANS(	0x005f	,0xa702	,0xa703	,CHAIN	), // MODIFIER LETTER CHINESE TONE YANG SHANG
/*COMPOSE            */	DEADTRANS(	0x0028	,0xa703	,0xa703	,DKF_0	), // MODIFIER LETTER CHINESE TONE YANG SHANG
/*COMPOSE            */	DEADTRANS(	0x0029	,0xa703	,0xa705	,DKF_0	), // MODIFIER LETTER CHINESE TONE YANG QU
/*COMPOSE            */	DEADTRANS(	0x00eb	,0x0063	,0xa700	,CHAIN	), // MODIFIER LETTER CHINESE TONE YIN PING
/*COMPOSE            */	DEADTRANS(	0x0028	,0xa700	,0xa700	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN PING
/*COMPOSE            */	DEADTRANS(	0x0029	,0xa700	,0xa706	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN RU
/*COMPOSE            */	DEADTRANS(	0x005f	,0xa700	,0xa701	,CHAIN	), // MODIFIER LETTER CHINESE TONE YANG PING
/*COMPOSE            */	DEADTRANS(	0x0028	,0xa701	,0xa701	,DKF_0	), // MODIFIER LETTER CHINESE TONE YANG PING
/*COMPOSE            */	DEADTRANS(	0x0029	,0xa701	,0xa707	,DKF_0	), // MODIFIER LETTER CHINESE TONE YANG RU
/*COMPOSE            */	DEADTRANS(	L'D'	,0x00a6	,0x0044	,CHAIN	), // LATIN CAPITAL LETTER D
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0044	,0x00d0	,DKF_0	), // LATIN CAPITAL LETTER ETH
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0044	,0x00d0	,DKF_0	), // LATIN CAPITAL LETTER ETH
/*COMPOSE            */	DEADTRANS(	L'I'	,0x0044	,0x2300	,DKF_0	), // DIAMETER SIGN
/*COMPOSE            */	DEADTRANS(	L'N'	,0x0044	,0x2669	,DKF_0	), // QUARTER NOTE
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0044	,0x266f	,DKF_0	), // MUSIC SHARP SIGN
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0044	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L't'	,0x0044	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x0044	,0x01f1	,DKF_0	), // LATIN CAPITAL LETTER DZ
/*COMPOSE            */	DEADTRANS(	L'z'	,0x0044	,0x01f2	,DKF_0	), // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0044	,0x01c0	,DKF_0	), // LATIN LETTER DENTAL CLICK
/*COMPOSE            */	DEADTRANS(	0x0023	,0x0044	,0x266f	,DKF_0	), // MUSIC SHARP SIGN
/*COMPOSE            */	DEADTRANS(	0x0029	,0x0044	,0x266a	,DKF_0	), // EIGHTH NOTE
/*COMPOSE            */	DEADTRANS(	0x005b	,0x0044	,0x266a	,DKF_0	), // EIGHTH NOTE
/*COMPOSE            */	DEADTRANS(	0x005d	,0x0044	,0x266a	,DKF_0	), // EIGHTH NOTE
/*COMPOSE            */	DEADTRANS(	0x00c8	,0x0044	,0x266f	,DKF_0	), // MUSIC SHARP SIGN
/*COMPOSE            */	DEADTRANS(	L'd'	,0x00a6	,0x0064	,CHAIN	), // LATIN SMALL LETTER D
/*COMPOSE            */	DEADTRANS(	L'b'	,0x0064	,0x0238	,DKF_0	), // LATIN SMALL LETTER DB DIGRAPH
/*COMPOSE            */	DEADTRANS(	L'f'	,0x0064	,0xfb00	,DKF_0	), // LATIN SMALL LIGATURE FF
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0064	,0x00d0	,DKF_0	), // LATIN CAPITAL LETTER ETH
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0064	,0x00f0	,DKF_0	), // LATIN SMALL LETTER ETH
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0064	,0x2300	,DKF_0	), // DIAMETER SIGN
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0064	,0x1e9f	,DKF_0	), // LATIN SMALL LETTER DELTA
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0064	,0x2669	,DKF_0	), // QUARTER NOTE
/*COMPOSE            */	DEADTRANS(	L's'	,0x0064	,0x266f	,DKF_0	), // MUSIC SHARP SIGN
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0064	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L't'	,0x0064	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*COMPOSE            */	DEADTRANS(	L'u'	,0x0064	,0xa771	,DKF_0	), // LATIN SMALL LETTER DUM
/*COMPOSE            */	DEADTRANS(	L'z'	,0x0064	,0x01f3	,DKF_0	), // LATIN SMALL LETTER DZ
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0064	,0x01c0	,DKF_0	), // LATIN LETTER DENTAL CLICK
/*COMPOSE            */	DEADTRANS(	0x0023	,0x0064	,0x266f	,DKF_0	), // MUSIC SHARP SIGN
/*COMPOSE            */	DEADTRANS(	0x0026	,0x0064	,0x02a3	,DKF_0	), // LATIN SMALL LETTER DZ DIGRAPH
/*COMPOSE            */	DEADTRANS(	0x0029	,0x0064	,0x266a	,DKF_0	), // EIGHTH NOTE
/*COMPOSE            */	DEADTRANS(	0x005b	,0x0064	,0x266a	,DKF_0	), // EIGHTH NOTE
/*COMPOSE            */	DEADTRANS(	0x005d	,0x0064	,0x266a	,DKF_0	), // EIGHTH NOTE
/*COMPOSE            */	DEADTRANS(	0x00a9	,0x0064	,0x02a4	,DKF_0	), // LATIN SMALL LETTER DEZH DIGRAPH
/*COMPOSE            */	DEADTRANS(	0x00e8	,0x0064	,0x266f	,DKF_0	), // MUSIC SHARP SIGN
/*COMPOSE            */	DEADTRANS(	L'E'	,0x00a6	,0x0045	,CHAIN	), // LATIN CAPITAL LETTER E
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0045	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0045	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0045	,0x018f	,DKF_0	), // LATIN CAPITAL LETTER SCHWA
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0045	,0x018f	,DKF_0	), // LATIN CAPITAL LETTER SCHWA
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0045	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0045	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0045	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0045	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0045	,0x212e	,DKF_0	), // ESTIMATED SYMBOL
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0045	,0xa76a	,DKF_0	), // LATIN CAPITAL LETTER ET
/*COMPOSE            */	DEADTRANS(	L't'	,0x0045	,0xa76a	,DKF_0	), // LATIN CAPITAL LETTER ET
/*COMPOSE            */	DEADTRANS(	L'V'	,0x0045	,0x2205	,DKF_0	), // EMPTY SET
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0045	,0xa72a	,DKF_0	), // LATIN CAPITAL LETTER TRESILLO
/*COMPOSE            */	DEADTRANS(	L'7'	,0x0045	,0x204a	,DKF_0	), // TIRONIAN SIGN ET
/*COMPOSE            */	DEADTRANS(	L'e'	,0x00a6	,0x0065	,CHAIN	), // LATIN SMALL LETTER E
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0065	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0065	,0x025b	,DKF_0	), // LATIN SMALL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0065	,0x018f	,DKF_0	), // LATIN CAPITAL LETTER SCHWA
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0065	,0x0259	,DKF_0	), // LATIN SMALL LETTER SCHWA
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0065	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0065	,0x025b	,DKF_0	), // LATIN SMALL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0065	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0065	,0x025b	,DKF_0	), // LATIN SMALL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L's'	,0x0065	,0x212e	,DKF_0	), // ESTIMATED SYMBOL
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0065	,0xa76a	,DKF_0	), // LATIN CAPITAL LETTER ET
/*COMPOSE            */	DEADTRANS(	L't'	,0x0065	,0xa76b	,DKF_0	), // LATIN SMALL LETTER ET
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0065	,0x2205	,DKF_0	), // EMPTY SET
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0065	,0xa72b	,DKF_0	), // LATIN SMALL LETTER TRESILLO
/*COMPOSE            */	DEADTRANS(	L'7'	,0x0065	,0x204a	,DKF_0	), // TIRONIAN SIGN ET
/*COMPOSE            */	DEADTRANS(	L'F'	,0x00a6	,0x0046	,CHAIN	), // LATIN CAPITAL LETTER F
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0046	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'f'	,0x00a6	,0x0066	,CHAIN	), // LATIN SMALL LETTER F
/*COMPOSE            */	DEADTRANS(	L'd'	,0x0066	,0xab35	,DKF_0	), // LATIN SMALL LETTER LENIS F
/*COMPOSE            */	DEADTRANS(	L'f'	,0x0066	,0xfb00	,CHAIN	), // LATIN SMALL LIGATURE FF
/*COMPOSE            */	DEADTRANS(	L'f'	,0xfb00	,0xfb00	,DKF_0	), // LATIN SMALL LIGATURE FF
/*COMPOSE            */	DEADTRANS(	L'i'	,0xfb00	,0xfb03	,DKF_0	), // LATIN SMALL LIGATURE FFI
/*COMPOSE            */	DEADTRANS(	L'l'	,0xfb00	,0xfb04	,DKF_0	), // LATIN SMALL LIGATURE FFL
/*COMPOSE            */	DEADTRANS(	0x0020	,0xfb00	,0xfb00	,DKF_0	), // LATIN SMALL LIGATURE FF
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0066	,0xfb01	,DKF_0	), // LATIN SMALL LIGATURE FI
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0066	,0xfb02	,DKF_0	), // LATIN SMALL LIGATURE FL
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0066	,0x02a9	,DKF_0	), // LATIN SMALL LETTER FENG DIGRAPH
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0066	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'G'	,0x00a6	,0x0047	,CHAIN	), // LATIN CAPITAL LETTER G
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0047	,0x264a	,DKF_0	), // GEMINI
/*COMPOSE            */	DEADTRANS(	L'G'	,0x0047	,0x021c	,DKF_0	), // LATIN CAPITAL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'g'	,0x0047	,0x021c	,DKF_0	), // LATIN CAPITAL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0047	,0x01a2	,DKF_0	), // LATIN CAPITAL LETTER OI
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0047	,0x01a2	,DKF_0	), // LATIN CAPITAL LETTER OI
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0047	,0x0194	,DKF_0	), // LATIN CAPITAL LETTER GAMMA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0047	,0x0194	,DKF_0	), // LATIN CAPITAL LETTER GAMMA
/*COMPOSE            */	DEADTRANS(	L'M'	,0x0047	,0xfeff	,DKF_0	), // ZERO WIDTH NO-BREAK SPACE
/*COMPOSE            */	DEADTRANS(	L'N'	,0x0047	,0x014a	,DKF_0	), // LATIN CAPITAL LETTER ENG
/*COMPOSE            */	DEADTRANS(	L'R'	,0x0047	,0x03a9	,DKF_0	), // GREEK CAPITAL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	0x00c9	,0x0047	,0x264a	,DKF_0	), // GEMINI
/*COMPOSE            */	DEADTRANS(	L'g'	,0x00a6	,0x0067	,CHAIN	), // LATIN SMALL LETTER G
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0067	,0x264a	,DKF_0	), // GEMINI
/*COMPOSE            */	DEADTRANS(	L'G'	,0x0067	,0x021c	,DKF_0	), // LATIN CAPITAL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'g'	,0x0067	,0x021d	,DKF_0	), // LATIN SMALL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0067	,0x01a2	,DKF_0	), // LATIN CAPITAL LETTER OI
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0067	,0x01a3	,DKF_0	), // LATIN SMALL LETTER OI
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0067	,0x0263	,DKF_0	), // LATIN SMALL LETTER GAMMA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0067	,0x0263	,DKF_0	), // LATIN SMALL LETTER GAMMA
/*COMPOSE            */	DEADTRANS(	L'm'	,0x0067	,0x2060	,DKF_0	), // WORD JOINER
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0067	,0x014b	,DKF_0	), // LATIN SMALL LETTER ENG
/*COMPOSE            */	DEADTRANS(	L'r'	,0x0067	,0x03a9	,DKF_0	), // GREEK CAPITAL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	0x00e9	,0x0067	,0x264a	,DKF_0	), // GEMINI
/*COMPOSE            */	DEADTRANS(	L'H'	,0x00a6	,0x0048	,CHAIN	), // LATIN CAPITAL LETTER H
/*COMPOSE            */	DEADTRANS(	L'D'	,0x0048	,0x00d0	,DKF_0	), // LATIN CAPITAL LETTER ETH
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0048	,0x2135	,DKF_0	), // ALEF SYMBOL
/*COMPOSE            */	DEADTRANS(	L'G'	,0x0048	,0x01a2	,DKF_0	), // LATIN CAPITAL LETTER OI
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0048	,0x210d	,DKF_0	), // DOUBLE-STRUCK CAPITAL H
/*COMPOSE            */	DEADTRANS(	L'N'	,0x0048	,0xa726	,DKF_0	), // LATIN CAPITAL LETTER HENG
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0048	,0xa726	,DKF_0	), // LATIN CAPITAL LETTER HENG
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0048	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0048	,0x01a9	,DKF_0	), // LATIN CAPITAL LETTER ESH
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0048	,0x00de	,DKF_0	), // LATIN CAPITAL LETTER THORN
/*COMPOSE            */	DEADTRANS(	L'W'	,0x0048	,0x01f6	,DKF_0	), // LATIN CAPITAL LETTER HWAIR
/*COMPOSE            */	DEADTRANS(	L'w'	,0x0048	,0x01f6	,DKF_0	), // LATIN CAPITAL LETTER HWAIR
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x0048	,0x01b7	,DKF_0	), // LATIN CAPITAL LETTER EZH
/*COMPOSE            */	DEADTRANS(	0x0028	,0x0048	,0x2c75	,DKF_0	), // LATIN CAPITAL LETTER HALF H
/*COMPOSE            */	DEADTRANS(	0x003c	,0x0048	,0x02f9	,DKF_0	), // MODIFIER LETTER BEGIN HIGH TONE
/*COMPOSE            */	DEADTRANS(	0x003e	,0x0048	,0x02fa	,DKF_0	), // MODIFIER LETTER END HIGH TONE
/*COMPOSE            */	DEADTRANS(	L'h'	,0x00a6	,0x0068	,CHAIN	), // LATIN SMALL LETTER H
/*COMPOSE            */	DEADTRANS(	L'd'	,0x0068	,0x00f0	,DKF_0	), // LATIN SMALL LETTER ETH
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0068	,0x2135	,DKF_0	), // ALEF SYMBOL
/*COMPOSE            */	DEADTRANS(	L'g'	,0x0068	,0x01a3	,DKF_0	), // LATIN SMALL LETTER OI
/*COMPOSE            */	DEADTRANS(	L'N'	,0x0068	,0xa726	,DKF_0	), // LATIN CAPITAL LETTER HENG
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0068	,0xa727	,DKF_0	), // LATIN SMALL LETTER HENG
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0068	,0x0254	,DKF_0	), // LATIN SMALL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L's'	,0x0068	,0x0283	,DKF_0	), // LATIN SMALL LETTER ESH
/*COMPOSE            */	DEADTRANS(	L't'	,0x0068	,0x00fe	,DKF_0	), // LATIN SMALL LETTER THORN
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0068	,0x0195	,DKF_0	), // LATIN SMALL LETTER HV
/*COMPOSE            */	DEADTRANS(	L'z'	,0x0068	,0x0292	,DKF_0	), // LATIN SMALL LETTER EZH
/*COMPOSE            */	DEADTRANS(	0x0028	,0x0068	,0x2c76	,DKF_0	), // LATIN SMALL LETTER HALF H
/*COMPOSE            */	DEADTRANS(	0x003c	,0x0068	,0x02f9	,DKF_0	), // MODIFIER LETTER BEGIN HIGH TONE
/*COMPOSE            */	DEADTRANS(	0x003e	,0x0068	,0x02fa	,DKF_0	), // MODIFIER LETTER END HIGH TONE
/*COMPOSE            */	DEADTRANS(	L'I'	,0x00a6	,0x0049	,CHAIN	), // LATIN CAPITAL LETTER I
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0049	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'D'	,0x0049	,0x2300	,DKF_0	), // DIAMETER SIGN
/*COMPOSE            */	DEADTRANS(	L'F'	,0x0049	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'I'	,0x0049	,0xa7ae	,DKF_0	), // LATIN CAPITAL LETTER SMALL CAPITAL I
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0049	,0xa7ae	,DKF_0	), // LATIN CAPITAL LETTER SMALL CAPITAL I
/*COMPOSE            */	DEADTRANS(	L'J'	,0x0049	,0x0132	,DKF_0	), // LATIN CAPITAL LIGATURE IJ
/*COMPOSE            */	DEADTRANS(	L'j'	,0x0049	,0x0132	,DKF_0	), // LATIN CAPITAL LIGATURE IJ
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0049	,0x0196	,DKF_0	), // LATIN CAPITAL LETTER IOTA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0049	,0x0196	,DKF_0	), // LATIN CAPITAL LETTER IOTA
/*COMPOSE            */	DEADTRANS(	L'M'	,0x0049	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0049	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'P'	,0x0049	,0x00b6	,DKF_0	), // PILCROW SIGN
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0049	,0xa76c	,DKF_0	), // LATIN CAPITAL LETTER IS
/*COMPOSE            */	DEADTRANS(	L's'	,0x0049	,0xa76c	,DKF_0	), // LATIN CAPITAL LETTER IS
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0049	,0xa72c	,DKF_0	), // LATIN CAPITAL LETTER CUATRILLO
/*COMPOSE            */	DEADTRANS(	0x0027	,0x0049	,0xa78b	,DKF_0	), // LATIN CAPITAL LETTER SALTILLO
/*COMPOSE            */	DEADTRANS(	0x00f9	,0x0049	,0xa78b	,DKF_0	), // LATIN CAPITAL LETTER SALTILLO
/*COMPOSE            */	DEADTRANS(	0x2019	,0x0049	,0xa78b	,DKF_0	), // LATIN CAPITAL LETTER SALTILLO
/*COMPOSE            */	DEADTRANS(	L'i'	,0x00a6	,0x0069	,CHAIN	), // LATIN SMALL LETTER I
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0069	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'd'	,0x0069	,0x2300	,DKF_0	), // DIAMETER SIGN
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0069	,0xab61	,DKF_0	), // LATIN SMALL LETTER IOTIFIED E
/*COMPOSE            */	DEADTRANS(	L'f'	,0x0069	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'I'	,0x0069	,0xa7ae	,DKF_0	), // LATIN CAPITAL LETTER SMALL CAPITAL I
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0069	,0x026a	,DKF_0	), // LATIN LETTER SMALL CAPITAL I
/*COMPOSE            */	DEADTRANS(	L'J'	,0x0069	,0x0132	,DKF_0	), // LATIN CAPITAL LIGATURE IJ
/*COMPOSE            */	DEADTRANS(	L'j'	,0x0069	,0x0133	,DKF_0	), // LATIN SMALL LIGATURE IJ
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0069	,0x0269	,DKF_0	), // LATIN SMALL LETTER IOTA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0069	,0x0269	,DKF_0	), // LATIN SMALL LETTER IOTA
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0069	,0x2282	,DKF_0	), // SUBSET OF
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0069	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'P'	,0x0069	,0x00b6	,DKF_0	), // PILCROW SIGN
/*COMPOSE            */	DEADTRANS(	L'p'	,0x0069	,0x00b6	,DKF_0	), // PILCROW SIGN
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0069	,0xa76c	,DKF_0	), // LATIN CAPITAL LETTER IS
/*COMPOSE            */	DEADTRANS(	L's'	,0x0069	,0xa76d	,DKF_0	), // LATIN SMALL LETTER IS
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0069	,0xa72d	,DKF_0	), // LATIN SMALL LETTER CUATRILLO
/*COMPOSE            */	DEADTRANS(	0x0027	,0x0069	,0xa78c	,DKF_0	), // LATIN SMALL LETTER SALTILLO
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0069	,0x2284	,DKF_0	), // NOT A SUBSET OF
/*COMPOSE            */	DEADTRANS(	0x00f9	,0x0069	,0xa78c	,DKF_0	), // LATIN SMALL LETTER SALTILLO
/*COMPOSE            */	DEADTRANS(	0x2019	,0x0069	,0xa78c	,DKF_0	), // LATIN SMALL LETTER SALTILLO
/*COMPOSE            */	DEADTRANS(	L'J'	,0x00a6	,0x004a	,CHAIN	), // LATIN CAPITAL LETTER J
/*COMPOSE            */	DEADTRANS(	L'j'	,0x00a6	,0x006a	,CHAIN	), // LATIN SMALL LETTER J
/*COMPOSE            */	DEADTRANS(	L'K'	,0x00a6	,0x004b	,CHAIN	), // LATIN CAPITAL LETTER K
/*COMPOSE            */	DEADTRANS(	L'B'	,0x004b	,0x2328	,DKF_0	), // KEYBOARD
/*COMPOSE            */	DEADTRANS(	L'k'	,0x00a6	,0x006b	,CHAIN	), // LATIN SMALL LETTER K
/*COMPOSE            */	DEADTRANS(	L'b'	,0x006b	,0x2328	,DKF_0	), // KEYBOARD
/*COMPOSE            */	DEADTRANS(	L'r'	,0x006b	,0x0138	,DKF_0	), // LATIN SMALL LETTER KRA
/*COMPOSE            */	DEADTRANS(	L'L'	,0x00a6	,0x004c	,CHAIN	), // LATIN CAPITAL LETTER L
/*COMPOSE            */	DEADTRANS(	L'A'	,0x004c	,0x2c6d	,DKF_0	), // LATIN CAPITAL LETTER ALPHA
/*COMPOSE            */	DEADTRANS(	L'B'	,0x004c	,0xa7b4	,DKF_0	), // LATIN CAPITAL LETTER BETA
/*COMPOSE            */	DEADTRANS(	L'E'	,0x004c	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'G'	,0x004c	,0x0194	,DKF_0	), // LATIN CAPITAL LETTER GAMMA
/*COMPOSE            */	DEADTRANS(	L'I'	,0x004c	,0x264c	,DKF_0	), // LEO
/*COMPOSE            */	DEADTRANS(	L'J'	,0x004c	,0x01c7	,DKF_0	), // LATIN CAPITAL LETTER LJ
/*COMPOSE            */	DEADTRANS(	L'j'	,0x004c	,0x01c8	,DKF_0	), // LATIN CAPITAL LETTER L WITH SMALL LETTER J
/*COMPOSE            */	DEADTRANS(	L'L'	,0x004c	,0x1efa	,DKF_0	), // LATIN CAPITAL LETTER MIDDLE-WELSH LL
/*COMPOSE            */	DEADTRANS(	L'L'	,0x006c	,0x1efa	,DKF_0	), // LATIN CAPITAL LETTER MIDDLE-WELSH LL
/*COMPOSE            */	DEADTRANS(	L'O'	,0x004c	,0xa7b6	,DKF_0	), // LATIN CAPITAL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	L'T'	,0x004c	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L'X'	,0x004c	,0xa7b3	,DKF_0	), // LATIN CAPITAL LETTER CHI
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x004c	,0x01b1	,DKF_0	), // LATIN CAPITAL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	0x0021	,0x004c	,0x01c1	,DKF_0	), // LATIN LETTER LATERAL CLICK
/*COMPOSE            */	DEADTRANS(	L'l'	,0x00a6	,0x006c	,CHAIN	), // LATIN SMALL LETTER L
/*COMPOSE            */	DEADTRANS(	L'a'	,0x006c	,0x0251	,DKF_0	), // LATIN SMALL LETTER ALPHA
/*COMPOSE            */	DEADTRANS(	L'b'	,0x006c	,0xa7b5	,DKF_0	), // LATIN SMALL LETTER BETA
/*COMPOSE            */	DEADTRANS(	L'c'	,0x006c	,0x2113	,DKF_0	), // SCRIPT SMALL L
/*COMPOSE            */	DEADTRANS(	L'd'	,0x006c	,0x1e9f	,DKF_0	), // LATIN SMALL LETTER DELTA
/*COMPOSE            */	DEADTRANS(	L'e'	,0x006c	,0x025b	,DKF_0	), // LATIN SMALL LETTER OPEN E
/*COMPOSE            */	DEADTRANS(	L'f'	,0x006c	,0xfb00	,DKF_0	), // LATIN SMALL LIGATURE FF
/*COMPOSE            */	DEADTRANS(	L'g'	,0x006c	,0x0263	,DKF_0	), // LATIN SMALL LETTER GAMMA
/*COMPOSE            */	DEADTRANS(	L'i'	,0x006c	,0x264c	,DKF_0	), // LEO
/*COMPOSE            */	DEADTRANS(	L'j'	,0x006c	,0x01c9	,DKF_0	), // LATIN SMALL LETTER LJ
/*COMPOSE            */	DEADTRANS(	L'l'	,0x004c	,0x1efa	,DKF_0	), // LATIN CAPITAL LETTER MIDDLE-WELSH LL
/*COMPOSE            */	DEADTRANS(	L'l'	,0x006c	,0x1efb	,DKF_0	), // LATIN SMALL LETTER MIDDLE-WELSH LL
/*COMPOSE            */	DEADTRANS(	L'o'	,0x006c	,0xa7b7	,DKF_0	), // LATIN SMALL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	L's'	,0x006c	,0x02aa	,DKF_0	), // LATIN SMALL LETTER LS DIGRAPH
/*COMPOSE            */	DEADTRANS(	L't'	,0x006c	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*COMPOSE            */	DEADTRANS(	L'u'	,0x006c	,0xa772	,DKF_0	), // LATIN SMALL LETTER LUM
/*COMPOSE            */	DEADTRANS(	L'x'	,0x006c	,0xab53	,DKF_0	), // LATIN SMALL LETTER CHI
/*COMPOSE            */	DEADTRANS(	L'y'	,0x006c	,0x028a	,DKF_0	), // LATIN SMALL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'z'	,0x006c	,0x02ab	,CHAIN	), // LATIN SMALL LETTER LZ DIGRAPH
/*COMPOSE            */	DEADTRANS(	L'h'	,0x02ab	,0x026e	,DKF_0	), // LATIN SMALL LETTER LEZH
/*COMPOSE            */	DEADTRANS(	0x0020	,0x02ab	,0x02ab	,DKF_0	), // LATIN SMALL LETTER LZ DIGRAPH
/*COMPOSE            */	DEADTRANS(	0x002e	,0x02ab	,0x02ab	,DKF_0	), // LATIN SMALL LETTER LZ DIGRAPH
/*COMPOSE            */	DEADTRANS(	0x0021	,0x006c	,0x01c1	,DKF_0	), // LATIN LETTER LATERAL CLICK
/*COMPOSE            */	DEADTRANS(	0x0025	,0x006c	,0xab37	,DKF_0	), // LATIN SMALL LETTER L WITH INVERTED LAZY S
/*COMPOSE            */	DEADTRANS(	0x00b0	,0x006c	,0xab58	,DKF_0	), // LATIN SMALL LETTER X WITH LONG LEFT LEG AND LOW RIGHT RING
/*COMPOSE            */	DEADTRANS(	L'M'	,0x00a6	,0x004d	,CHAIN	), // LATIN CAPITAL LETTER M
/*COMPOSE            */	DEADTRANS(	L'A'	,0x004d	,0xa7ff	,DKF_0	), // LATIN EPIGRAPHIC LETTER ARCHAIC M
/*COMPOSE            */	DEADTRANS(	L'a'	,0x004d	,0xa7ff	,DKF_0	), // LATIN EPIGRAPHIC LETTER ARCHAIC M
/*COMPOSE            */	DEADTRANS(	L'C'	,0x004d	,0xdd6a	,DKF_0	), // U+1F16A; input D83C high surrogate first; RAISED MC SIGN
/*COMPOSE            */	DEADTRANS(	L'D'	,0x004d	,0xdd6b	,DKF_0	), // U+1F16B; input D83C high surrogate first; RAISED MD SIGN
/*COMPOSE            */	DEADTRANS(	L'M'	,0x004d	,0x2133	,CHAIN	), // SCRIPT CAPITAL M
/*COMPOSE            */	DEADTRANS(	L'O'	,0x004d	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'T'	,0x004d	,0x2122	,DKF_0	), // TRADE MARK SIGN
/*COMPOSE            */	DEADTRANS(	L'W'	,0x004d	,0xa7ff	,DKF_0	), // LATIN EPIGRAPHIC LETTER ARCHAIC M
/*COMPOSE            */	DEADTRANS(	L'm'	,0x00a6	,0x006d	,CHAIN	), // LATIN SMALL LETTER M
/*COMPOSE            */	DEADTRANS(	L'A'	,0x006d	,0xa7ff	,DKF_0	), // LATIN EPIGRAPHIC LETTER ARCHAIC M
/*COMPOSE            */	DEADTRANS(	L'c'	,0x006d	,0xdd6a	,DKF_0	), // U+1F16A; input D83C high surrogate first; RAISED MC SIGN
/*COMPOSE            */	DEADTRANS(	L'd'	,0x006d	,0xdd6b	,DKF_0	), // U+1F16B; input D83C high surrogate first; RAISED MD SIGN
/*COMPOSE            */	DEADTRANS(	L'i'	,0x006d	,0x00b5	,DKF_0	), // MICRO SIGN
/*COMPOSE            */	DEADTRANS(	L'm'	,0x006d	,0x2133	,CHAIN	), // SCRIPT CAPITAL M
/*COMPOSE            */	DEADTRANS(	L'o'	,0x006d	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L't'	,0x006d	,0x2122	,DKF_0	), // TRADE MARK SIGN
/*COMPOSE            */	DEADTRANS(	L'u'	,0x006d	,0xa773	,DKF_0	), // LATIN SMALL LETTER MUM
/*COMPOSE            */	DEADTRANS(	L'N'	,0x00a6	,0x004e	,CHAIN	), // LATIN CAPITAL LETTER N
/*COMPOSE            */	DEADTRANS(	L'C'	,0x004e	,0x265e	,DKF_0	), // BLACK CHESS KNIGHT
/*COMPOSE            */	DEADTRANS(	L'D'	,0x004e	,0x265b	,DKF_0	), // BLACK CHESS QUEEN
/*COMPOSE            */	DEADTRANS(	L'F'	,0x004e	,0x265d	,DKF_0	), // BLACK CHESS BISHOP
/*COMPOSE            */	DEADTRANS(	L'G'	,0x004e	,0x014a	,DKF_0	), // LATIN CAPITAL LETTER ENG
/*COMPOSE            */	DEADTRANS(	L'g'	,0x004e	,0x014a	,DKF_0	), // LATIN CAPITAL LETTER ENG
/*COMPOSE            */	DEADTRANS(	L'J'	,0x004e	,0x01ca	,DKF_0	), // LATIN CAPITAL LETTER NJ
/*COMPOSE            */	DEADTRANS(	L'j'	,0x004e	,0x01cb	,DKF_0	), // LATIN CAPITAL LETTER N WITH SMALL LETTER J
/*COMPOSE            */	DEADTRANS(	L'L'	,0x004e	,0x0220	,DKF_0	), // LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
/*COMPOSE            */	DEADTRANS(	L'l'	,0x004e	,0x0220	,DKF_0	), // LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
/*COMPOSE            */	DEADTRANS(	L'N'	,0x004e	,0x2115	,DKF_0	), // DOUBLE-STRUCK CAPITAL N
/*COMPOSE            */	DEADTRANS(	L'O'	,0x004e	,0x2116	,DKF_0	), // NUMERO SIGN
/*COMPOSE            */	DEADTRANS(	L'o'	,0x004e	,0x2116	,DKF_0	), // NUMERO SIGN
/*COMPOSE            */	DEADTRANS(	L'P'	,0x004e	,0x265f	,DKF_0	), // BLACK CHESS PAWN
/*COMPOSE            */	DEADTRANS(	L'R'	,0x004e	,0x265a	,DKF_0	), // BLACK CHESS KING
/*COMPOSE            */	DEADTRANS(	L'T'	,0x004e	,0x265c	,DKF_0	), // BLACK CHESS ROOK
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x004e	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*COMPOSE            */	DEADTRANS(	L'y'	,0x004e	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*COMPOSE            */	DEADTRANS(	L'n'	,0x00a6	,0x006e	,CHAIN	), // LATIN SMALL LETTER N
/*COMPOSE            */	DEADTRANS(	L'c'	,0x006e	,0x265e	,DKF_0	), // BLACK CHESS KNIGHT
/*COMPOSE            */	DEADTRANS(	L'd'	,0x006e	,0x265b	,DKF_0	), // BLACK CHESS QUEEN
/*COMPOSE            */	DEADTRANS(	L'f'	,0x006e	,0x265d	,DKF_0	), // BLACK CHESS BISHOP
/*COMPOSE            */	DEADTRANS(	L'G'	,0x006e	,0x014a	,DKF_0	), // LATIN CAPITAL LETTER ENG
/*COMPOSE            */	DEADTRANS(	L'g'	,0x006e	,0x014b	,DKF_0	), // LATIN SMALL LETTER ENG
/*COMPOSE            */	DEADTRANS(	L'i'	,0x006e	,0x2283	,DKF_0	), // SUPERSET OF
/*COMPOSE            */	DEADTRANS(	L'j'	,0x006e	,0x01cc	,DKF_0	), // LATIN SMALL LETTER NJ
/*COMPOSE            */	DEADTRANS(	L'l'	,0x006e	,0x019e	,DKF_0	), // LATIN SMALL LETTER N WITH LONG RIGHT LEG
/*COMPOSE            */	DEADTRANS(	L'n'	,0x006e	,0x2669	,DKF_0	), // QUARTER NOTE
/*COMPOSE            */	DEADTRANS(	L'O'	,0x006e	,0x2116	,DKF_0	), // NUMERO SIGN
/*COMPOSE            */	DEADTRANS(	L'o'	,0x006e	,0x2116	,DKF_0	), // NUMERO SIGN
/*COMPOSE            */	DEADTRANS(	L'p'	,0x006e	,0x265f	,DKF_0	), // BLACK CHESS PAWN
/*COMPOSE            */	DEADTRANS(	L'r'	,0x006e	,0x265a	,DKF_0	), // BLACK CHESS KING
/*COMPOSE            */	DEADTRANS(	L't'	,0x006e	,0x265c	,DKF_0	), // BLACK CHESS ROOK
/*COMPOSE            */	DEADTRANS(	L'u'	,0x006e	,0xa774	,DKF_0	), // LATIN SMALL LETTER NUM
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x006e	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*COMPOSE            */	DEADTRANS(	L'y'	,0x006e	,0x0272	,DKF_0	), // LATIN SMALL LETTER N WITH LEFT HOOK
/*COMPOSE            */	DEADTRANS(	0x002f	,0x006e	,0x2285	,DKF_0	), // NOT A SUPERSET OF
/*COMPOSE            */	DEADTRANS(	L'O'	,0x00a6	,0x004f	,CHAIN	), // LATIN CAPITAL LETTER O
/*COMPOSE            */	DEADTRANS(	L'A'	,0x004f	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'a'	,0x004f	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'C'	,0x004f	,0x00a9	,DKF_0	), // COPYRIGHT SIGN
/*COMPOSE            */	DEADTRANS(	L'D'	,0x004f	,0xdd2f	,DKF_0	), // U+1F12F; input D83C high surrogate first; COPYLEFT SYMBOL
/*COMPOSE            */	DEADTRANS(	L'E'	,0x004f	,0x0152	,DKF_0	), // LATIN CAPITAL LIGATURE OE
/*COMPOSE            */	DEADTRANS(	L'e'	,0x004f	,0x0152	,DKF_0	), // LATIN CAPITAL LIGATURE OE
/*COMPOSE            */	DEADTRANS(	L'F'	,0x004f	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'H'	,0x004f	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'h'	,0x004f	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'I'	,0x004f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'L'	,0x004f	,0xa7b6	,DKF_0	), // LATIN CAPITAL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x004f	,0xa7b6	,DKF_0	), // LATIN CAPITAL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	L'M'	,0x004f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'O'	,0x004f	,0xa74e	,DKF_0	), // LATIN CAPITAL LETTER OO
/*COMPOSE            */	DEADTRANS(	L'o'	,0x004f	,0xa74e	,DKF_0	), // LATIN CAPITAL LETTER OO
/*COMPOSE            */	DEADTRANS(	L'P'	,0x004f	,0x2117	,DKF_0	), // SOUND RECORDING COPYRIGHT
/*COMPOSE            */	DEADTRANS(	L'R'	,0x004f	,0x00ae	,DKF_0	), // REGISTERED SIGN
/*COMPOSE            */	DEADTRANS(	L'U'	,0x004f	,0x0222	,DKF_0	), // LATIN CAPITAL LETTER OU
/*COMPOSE            */	DEADTRANS(	L'u'	,0x004f	,0x0222	,DKF_0	), // LATIN CAPITAL LETTER OU
/*COMPOSE            */	DEADTRANS(	L'3'	,0x004f	,0xa79c	,DKF_0	), // LATIN CAPITAL LETTER VOLAPUK OE
/*COMPOSE            */	DEADTRANS(	0x005f	,0x004f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	0x0186	,0x004f	,0xdd2f	,DKF_0	), // U+1F12F; input D83C high surrogate first; COPYLEFT SYMBOL
/*COMPOSE            */	DEADTRANS(	L'o'	,0x00a6	,0x006f	,CHAIN	), // LATIN SMALL LETTER O
/*COMPOSE            */	DEADTRANS(	L'A'	,0x006f	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'a'	,0x006f	,0x0254	,DKF_0	), // LATIN SMALL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'c'	,0x006f	,0x00a9	,DKF_0	), // COPYRIGHT SIGN
/*COMPOSE            */	DEADTRANS(	L'd'	,0x006f	,0xdd2f	,DKF_0	), // U+1F12F; input D83C high surrogate first; COPYLEFT SYMBOL
/*COMPOSE            */	DEADTRANS(	L'E'	,0x006f	,0x0152	,DKF_0	), // LATIN CAPITAL LIGATURE OE
/*COMPOSE            */	DEADTRANS(	L'e'	,0x006f	,0x0153	,DKF_0	), // LATIN SMALL LIGATURE OE
/*COMPOSE            */	DEADTRANS(	L'f'	,0x006f	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'H'	,0x006f	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'h'	,0x006f	,0x0254	,DKF_0	), // LATIN SMALL LETTER OPEN O
/*COMPOSE            */	DEADTRANS(	L'i'	,0x006f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'L'	,0x006f	,0xa7b7	,DKF_0	), // LATIN SMALL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	L'l'	,0x006f	,0xa7b7	,DKF_0	), // LATIN SMALL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	L'm'	,0x006f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	L'O'	,0x006f	,0xa74e	,DKF_0	), // LATIN CAPITAL LETTER OO
/*COMPOSE            */	DEADTRANS(	L'o'	,0x006f	,0xa74f	,DKF_0	), // LATIN SMALL LETTER OO
/*COMPOSE            */	DEADTRANS(	L'p'	,0x006f	,0x2117	,DKF_0	), // SOUND RECORDING COPYRIGHT
/*COMPOSE            */	DEADTRANS(	L'r'	,0x006f	,0x00ae	,DKF_0	), // REGISTERED SIGN
/*COMPOSE            */	DEADTRANS(	L'U'	,0x006f	,0x0222	,DKF_0	), // LATIN CAPITAL LETTER OU
/*COMPOSE            */	DEADTRANS(	L'u'	,0x006f	,0x0223	,DKF_0	), // LATIN SMALL LETTER OU
/*COMPOSE            */	DEADTRANS(	L'3'	,0x006f	,0xa79d	,DKF_0	), // LATIN SMALL LETTER VOLAPUK OE
/*COMPOSE            */	DEADTRANS(	0x0028	,0x006f	,0x1d16	,DKF_0	), // LATIN SMALL LETTER TOP HALF O
/*COMPOSE            */	DEADTRANS(	0x0029	,0x006f	,0x1d17	,DKF_0	), // LATIN SMALL LETTER BOTTOM HALF O
/*COMPOSE            */	DEADTRANS(	0x005f	,0x006f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*COMPOSE            */	DEADTRANS(	0x0254	,0x006f	,0xdd2f	,DKF_0	), // U+1F12F; input D83C high surrogate first; COPYLEFT SYMBOL
/*COMPOSE            */	DEADTRANS(	L'P'	,0x00a6	,0x0050	,DKF_0	), // LATIN CAPITAL LETTER P
/*COMPOSE            */	DEADTRANS(	L'M'	,0x0050	,0x00b6	,DKF_0	), // PILCROW SIGN
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0050	,0x2653	,DKF_0	), // PISCES
/*COMPOSE            */	DEADTRANS(	L'P'	,0x0050	,0x2119	,DKF_0	), // DOUBLE-STRUCK CAPITAL P
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0050	,0x0297	,DKF_0	), // LATIN LETTER STRETCHED C
/*COMPOSE            */	DEADTRANS(	L'p'	,0x00a6	,0x0070	,CHAIN	), // LATIN SMALL LETTER P
/*COMPOSE            */	DEADTRANS(	L'g'	,0x0070	,0x0264	,DKF_0	), // LATIN SMALL LETTER RAMS HORN
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0070	,0x0278	,DKF_0	), // LATIN SMALL LETTER PHI
/*COMPOSE            */	DEADTRANS(	L'm'	,0x0070	,0x00b6	,DKF_0	), // PILCROW SIGN
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0070	,0x2653	,DKF_0	), // PISCES
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0070	,0x0297	,DKF_0	), // LATIN LETTER STRETCHED C
/*COMPOSE            */	DEADTRANS(	L'Q'	,0x00a6	,0x0051	,CHAIN	), // LATIN CAPITAL LETTER Q
/*COMPOSE            */	DEADTRANS(	L'Q'	,0x0051	,0x211a	,DKF_0	), // DOUBLE-STRUCK CAPITAL Q
/*COMPOSE            */	DEADTRANS(	L'q'	,0x00a6	,0x0071	,CHAIN	), // LATIN SMALL LETTER Q
/*COMPOSE            */	DEADTRANS(	L'p'	,0x0071	,0x0239	,DKF_0	), // LATIN SMALL LETTER QP DIGRAPH
/*COMPOSE            */	DEADTRANS(	L'R'	,0x00a6	,0x0052	,CHAIN	), // LATIN CAPITAL LETTER R
/*COMPOSE            */	DEADTRANS(	L'R'	,0x0052	,0x211d	,DKF_0	), // DOUBLE-STRUCK CAPITAL R
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0052	,0x01c3	,DKF_0	), // LATIN LETTER RETROFLEX CLICK
/*COMPOSE            */	DEADTRANS(	L'r'	,0x00a6	,0x0072	,CHAIN	), // LATIN SMALL LETTER R
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0072	,0x027c	,DKF_0	), // LATIN SMALL LETTER R WITH LONG LEG
/*COMPOSE            */	DEADTRANS(	L'r'	,0x0072	,0xab48	,DKF_0	), // LATIN SMALL LETTER DOUBLE R
/*COMPOSE            */	DEADTRANS(	L'u'	,0x0072	,0xa775	,DKF_0	), // LATIN SMALL LETTER RUM
/*COMPOSE            */	DEADTRANS(	0x0021	,0x0072	,0x01c3	,DKF_0	), // LATIN LETTER RETROFLEX CLICK
/*COMPOSE            */	DEADTRANS(	0x00e9	,0x0072	,0xab45	,DKF_0	), // LATIN SMALL LETTER STIRRUP R
/*COMPOSE            */	DEADTRANS(	L'S'	,0x00a6	,0x0053	,CHAIN	), // LATIN CAPITAL LETTER S
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0053	,0x2650	,DKF_0	), // SAGITTARIUS
/*COMPOSE            */	DEADTRANS(	L'C'	,0x0053	,0x264f	,DKF_0	), // SCORPIUS
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0053	,0x212e	,DKF_0	), // ESTIMATED SYMBOL
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0053	,0x01a9	,DKF_0	), // LATIN CAPITAL LETTER ESH
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0053	,0x01a9	,DKF_0	), // LATIN CAPITAL LETTER ESH
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0053	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L's'	,0x0053	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x0053	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L'z'	,0x0053	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L's'	,0x00a6	,0x0073	,CHAIN	), // LATIN SMALL LETTER S
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0073	,0x2650	,DKF_0	), // SAGITTARIUS
/*COMPOSE            */	DEADTRANS(	L'c'	,0x0073	,0x264f	,DKF_0	), // SCORPIUS
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0073	,0x212e	,DKF_0	), // ESTIMATED SYMBOL
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0073	,0x01a9	,DKF_0	), // LATIN CAPITAL LETTER ESH
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0073	,0x0283	,DKF_0	), // LATIN SMALL LETTER ESH
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0073	,0x017f	,DKF_0	), // LATIN SMALL LETTER LONG S
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0073	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L's'	,0x0073	,0x00df	,DKF_0	), // LATIN SMALL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L't'	,0x0073	,0xfb06	,DKF_0	), // LATIN SMALL LIGATURE ST
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x0073	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L'z'	,0x0073	,0x00df	,DKF_0	), // LATIN SMALL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L'0'	,0x0073	,0x2648	,CHAIN	), // ARIES
/*COMPOSE            */	DEADTRANS(	L'1'	,0x2648	,0x2648	,DKF_0	), // ARIES
/*COMPOSE            */	DEADTRANS(	L'2'	,0x2648	,0x2649	,DKF_0	), // TAURUS
/*COMPOSE            */	DEADTRANS(	L'3'	,0x2648	,0x264a	,DKF_0	), // GEMINI
/*COMPOSE            */	DEADTRANS(	L'4'	,0x2648	,0x264b	,DKF_0	), // CANCER
/*COMPOSE            */	DEADTRANS(	L'5'	,0x2648	,0x264c	,DKF_0	), // LEO
/*COMPOSE            */	DEADTRANS(	L'6'	,0x2648	,0x264d	,DKF_0	), // VIRGO
/*COMPOSE            */	DEADTRANS(	L'7'	,0x2648	,0x264e	,DKF_0	), // LIBRA
/*COMPOSE            */	DEADTRANS(	L'8'	,0x2648	,0x264f	,DKF_0	), // SCORPIUS
/*COMPOSE            */	DEADTRANS(	L'9'	,0x2648	,0x2650	,DKF_0	), // SAGITTARIUS
/*COMPOSE            */	DEADTRANS(	L'1'	,0x0073	,0x2651	,CHAIN	), // CAPRICORN
/*COMPOSE            */	DEADTRANS(	L'0'	,0x2651	,0x2651	,DKF_0	), // CAPRICORN
/*COMPOSE            */	DEADTRANS(	L'1'	,0x2651	,0x2652	,DKF_0	), // AQUARIUS
/*COMPOSE            */	DEADTRANS(	L'2'	,0x2651	,0x2653	,DKF_0	), // PISCES
/*COMPOSE            */	DEADTRANS(	0x002e	,0x0073	,0xa78f	,DKF_0	), // LATIN LETTER SINOLOGICAL DOT
/*COMPOSE            */	DEADTRANS(	0x007c	,0x0073	,0xfb05	,DKF_0	), // LATIN SMALL LIGATURE LONG S T
/*COMPOSE            */	DEADTRANS(	L'T'	,0x00a6	,0x0054	,CHAIN	), // LATIN CAPITAL LETTER T
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0054	,0x2649	,DKF_0	), // TAURUS
/*COMPOSE            */	DEADTRANS(	L'D'	,0x0054	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0054	,0x204a	,DKF_0	), // TIRONIAN SIGN ET
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0054	,0x00de	,DKF_0	), // LATIN CAPITAL LETTER THORN
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0054	,0x00de	,DKF_0	), // LATIN CAPITAL LETTER THORN
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0054	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0054	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L'M'	,0x0054	,0x2122	,DKF_0	), // TRADE MARK SIGN
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0054	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L't'	,0x0054	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x0054	,0xa728	,DKF_0	), // LATIN CAPITAL LETTER TZ
/*COMPOSE            */	DEADTRANS(	L'z'	,0x0054	,0xa728	,DKF_0	), // LATIN CAPITAL LETTER TZ
/*COMPOSE            */	DEADTRANS(	L'2'	,0x0054	,0x01a7	,DKF_0	), // LATIN CAPITAL LETTER TONE TWO
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0054	,0x0417	,DKF_0	), // CYRILLIC CAPITAL LETTER ZE
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0054	,0x0427	,DKF_0	), // CYRILLIC CAPITAL LETTER CHE
/*COMPOSE            */	DEADTRANS(	L'5'	,0x0054	,0x01bc	,DKF_0	), // LATIN CAPITAL LETTER TONE FIVE
/*COMPOSE            */	DEADTRANS(	L'6'	,0x0054	,0x0184	,DKF_0	), // LATIN CAPITAL LETTER TONE SIX
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0054	,0x02d4	,DKF_0	), // MODIFIER LETTER UP TACK
/*COMPOSE            */	DEADTRANS(	0x005c	,0x0054	,0x02d5	,DKF_0	), // MODIFIER LETTER DOWN TACK
/*COMPOSE            */	DEADTRANS(	L't'	,0x00a6	,0x0074	,CHAIN	), // LATIN SMALL LETTER T
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0074	,0x2649	,DKF_0	), // TAURUS
/*COMPOSE            */	DEADTRANS(	L'c'	,0x0074	,0x02a7	,DKF_0	), // LATIN SMALL LETTER TESH DIGRAPH
/*COMPOSE            */	DEADTRANS(	L'd'	,0x0074	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0074	,0x204a	,DKF_0	), // TIRONIAN SIGN ET
/*COMPOSE            */	DEADTRANS(	L'H'	,0x0074	,0x00de	,DKF_0	), // LATIN CAPITAL LETTER THORN
/*COMPOSE            */	DEADTRANS(	L'h'	,0x0074	,0x00fe	,DKF_0	), // LATIN SMALL LETTER THORN
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0074	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0074	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*COMPOSE            */	DEADTRANS(	L'm'	,0x0074	,0x2122	,DKF_0	), // TRADE MARK SIGN
/*COMPOSE            */	DEADTRANS(	L's'	,0x0074	,0x02a6	,DKF_0	), // LATIN SMALL LETTER TS DIGRAPH
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0074	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*COMPOSE            */	DEADTRANS(	L't'	,0x0074	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*COMPOSE            */	DEADTRANS(	L'u'	,0x0074	,0xa777	,DKF_0	), // LATIN SMALL LETTER TUM
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x0074	,0xa728	,DKF_0	), // LATIN CAPITAL LETTER TZ
/*COMPOSE            */	DEADTRANS(	L'z'	,0x0074	,0xa729	,DKF_0	), // LATIN SMALL LETTER TZ
/*COMPOSE            */	DEADTRANS(	L'2'	,0x0074	,0x01a8	,DKF_0	), // LATIN SMALL LETTER TONE TWO
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0074	,0x0437	,DKF_0	), // CYRILLIC SMALL LETTER ZE
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0074	,0x0447	,DKF_0	), // CYRILLIC SMALL LETTER CHE
/*COMPOSE            */	DEADTRANS(	L'5'	,0x0074	,0x01bd	,DKF_0	), // LATIN SMALL LETTER TONE FIVE
/*COMPOSE            */	DEADTRANS(	L'6'	,0x0074	,0x0185	,DKF_0	), // LATIN SMALL LETTER TONE SIX
/*COMPOSE            */	DEADTRANS(	0x002d	,0x0074	,0x01be	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP WITH STROKE
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0074	,0x02d4	,DKF_0	), // MODIFIER LETTER UP TACK
/*COMPOSE            */	DEADTRANS(	0x005c	,0x0074	,0x02d5	,DKF_0	), // MODIFIER LETTER DOWN TACK
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0055	,0x01b1	,DKF_0	), // LATIN CAPITAL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0055	,0x01b1	,DKF_0	), // LATIN CAPITAL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0055	,0xa79e	,DKF_0	), // LATIN CAPITAL LETTER VOLAPUK UE
/*COMPOSE            */	DEADTRANS(	L'u'	,0x00a6	,0x0075	,CHAIN	), // LATIN SMALL LETTER U
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0075	,0x1d6b	,DKF_0	), // LATIN SMALL LETTER UE
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0075	,0xab50	,DKF_0	), // LATIN SMALL LETTER UI
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0075	,0x028a	,DKF_0	), // LATIN SMALL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0075	,0x028a	,DKF_0	), // LATIN SMALL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'm'	,0x0075	,0xa778	,DKF_0	), // LATIN SMALL LETTER UM
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0075	,0xab63	,DKF_0	), // LATIN SMALL LETTER UO
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0075	,0xa79f	,DKF_0	), // LATIN SMALL LETTER VOLAPUK UE
/*COMPOSE            */	DEADTRANS(	L'V'	,0x00a6	,0x0056	,CHAIN	), // LATIN CAPITAL LETTER V
/*COMPOSE            */	DEADTRANS(	L'E'	,0x0056	,0x2652	,DKF_0	), // AQUARIUS
/*COMPOSE            */	DEADTRANS(	L'I'	,0x0056	,0x264d	,DKF_0	), // VIRGO
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0056	,0xa768	,DKF_0	), // LATIN CAPITAL LETTER VEND
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0056	,0xa768	,DKF_0	), // LATIN CAPITAL LETTER VEND
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0056	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L't'	,0x0056	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L'V'	,0x0056	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0056	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x0056	,0xa760	,DKF_0	), // LATIN CAPITAL LETTER VY
/*COMPOSE            */	DEADTRANS(	L'y'	,0x0056	,0xa760	,DKF_0	), // LATIN CAPITAL LETTER VY
/*COMPOSE            */	DEADTRANS(	0x002e	,0x0056	,0x02d1	,DKF_0	), // MODIFIER LETTER HALF TRIANGULAR COLON
/*COMPOSE            */	DEADTRANS(	0x003a	,0x0056	,0x02d0	,DKF_0	), // MODIFIER LETTER TRIANGULAR COLON
/*COMPOSE            */	DEADTRANS(	0x005b	,0x0056	,0xddf9	,DKF_0	), // U+1F5F9; input D83D high surrogate first; BALLOT BOX WITH BOLD CHECK
/*COMPOSE            */	DEADTRANS(	0x2610	,0x0056	,0xddf9	,DKF_0	), // U+1F5F9; input D83D high surrogate first; BALLOT BOX WITH BOLD CHECK
/*COMPOSE            */	DEADTRANS(	L'v'	,0x00a6	,0x0076	,CHAIN	), // LATIN SMALL LETTER V
/*COMPOSE            */	DEADTRANS(	L'e'	,0x0076	,0x2652	,DKF_0	), // AQUARIUS
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0076	,0x264d	,DKF_0	), // VIRGO
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0076	,0xa768	,DKF_0	), // LATIN CAPITAL LETTER VEND
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0076	,0xa769	,DKF_0	), // LATIN SMALL LETTER VEND
/*COMPOSE            */	DEADTRANS(	L'T'	,0x0076	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L't'	,0x0076	,0x028c	,DKF_0	), // LATIN SMALL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L'V'	,0x0076	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0076	,0x028c	,DKF_0	), // LATIN SMALL LETTER TURNED V
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x0076	,0xa760	,DKF_0	), // LATIN CAPITAL LETTER VY
/*COMPOSE            */	DEADTRANS(	L'y'	,0x0076	,0xa761	,DKF_0	), // LATIN SMALL LETTER VY
/*COMPOSE            */	DEADTRANS(	0x002e	,0x0076	,0x02d1	,DKF_0	), // MODIFIER LETTER HALF TRIANGULAR COLON
/*COMPOSE            */	DEADTRANS(	0x003a	,0x0076	,0x02d0	,DKF_0	), // MODIFIER LETTER TRIANGULAR COLON
/*COMPOSE            */	DEADTRANS(	0x005b	,0x0076	,0x2611	,DKF_0	), // BALLOT BOX WITH CHECK
/*COMPOSE            */	DEADTRANS(	0x2610	,0x0076	,0x2611	,DKF_0	), // BALLOT BOX WITH CHECK
/*COMPOSE            */	DEADTRANS(	L'W'	,0x00a6	,0x0057	,CHAIN	), // LATIN CAPITAL LETTER W
/*COMPOSE            */	DEADTRANS(	L'W'	,0x0057	,0x02ac	,DKF_0	), // LATIN LETTER BILABIAL PERCUSSIVE
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x0057	,0x01f7	,DKF_0	), // LATIN CAPITAL LETTER WYNN
/*COMPOSE            */	DEADTRANS(	L'y'	,0x0057	,0x01f7	,DKF_0	), // LATIN CAPITAL LETTER WYNN
/*COMPOSE            */	DEADTRANS(	L'w'	,0x00a6	,0x0077	,CHAIN	), // LATIN SMALL LETTER W
/*COMPOSE            */	DEADTRANS(	L'w'	,0x0077	,0x02ac	,DKF_0	), // LATIN LETTER BILABIAL PERCUSSIVE
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x0077	,0x01f7	,DKF_0	), // LATIN CAPITAL LETTER WYNN
/*COMPOSE            */	DEADTRANS(	L'y'	,0x0077	,0x01bf	,DKF_0	), // LATIN LETTER WYNN
/*COMPOSE            */	DEADTRANS(	0x007c	,0x0077	,0x2307	,DKF_0	), // WAVY LINE
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0058	,0xa7b3	,DKF_0	), // LATIN CAPITAL LETTER CHI
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0058	,0xa7b3	,DKF_0	), // LATIN CAPITAL LETTER CHI
/*COMPOSE            */	DEADTRANS(	L'X'	,0x0058	,0x00d7	,DKF_0	), // MULTIPLICATION SIGN
/*COMPOSE            */	DEADTRANS(	0x003a	,0x0058	,0x203b	,DKF_0	), // REFERENCE MARK
/*COMPOSE            */	DEADTRANS(	0x005b	,0x0058	,0xddf7	,DKF_0	), // U+1F5F7; input D83D high surrogate first; BALLOT BOX WITH BOLD SCRIPT X
/*COMPOSE            */	DEADTRANS(	0x2610	,0x0058	,0xddf7	,DKF_0	), // U+1F5F7; input D83D high surrogate first; BALLOT BOX WITH BOLD SCRIPT X
/*COMPOSE            */	DEADTRANS(	L'x'	,0x00a6	,0x0078	,CHAIN	), // LATIN SMALL LETTER X
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0078	,0xab53	,DKF_0	), // LATIN SMALL LETTER CHI
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0078	,0xab53	,DKF_0	), // LATIN SMALL LETTER CHI
/*COMPOSE            */	DEADTRANS(	L'x'	,0x0078	,0x00d7	,DKF_0	), // MULTIPLICATION SIGN
/*COMPOSE            */	DEADTRANS(	0x003a	,0x0078	,0x203b	,DKF_0	), // REFERENCE MARK
/*COMPOSE            */	DEADTRANS(	0x005b	,0x0078	,0x2612	,DKF_0	), // BALLOT BOX WITH X
/*COMPOSE            */	DEADTRANS(	0x2610	,0x0078	,0x2612	,DKF_0	), // BALLOT BOX WITH X
/*COMPOSE            */	DEADTRANS(	L'Y'	,0x00a6	,0x0059	,CHAIN	), // LATIN CAPITAL LETTER Y
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0059	,0x02eb	,DKF_0	), // MODIFIER LETTER YANG DEPARTING TONE MARK
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0059	,0x02eb	,DKF_0	), // MODIFIER LETTER YANG DEPARTING TONE MARK
/*COMPOSE            */	DEADTRANS(	L'I'	,0x0059	,0x02ea	,DKF_0	), // MODIFIER LETTER YIN DEPARTING TONE MARK
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0059	,0x01b1	,DKF_0	), // LATIN CAPITAL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0059	,0x01b1	,DKF_0	), // LATIN CAPITAL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'N'	,0x0059	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0059	,0x021c	,DKF_0	), // LATIN CAPITAL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0059	,0x021c	,DKF_0	), // LATIN CAPITAL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'P'	,0x0059	,0xa700	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN PING
/*COMPOSE            */	DEADTRANS(	L'p'	,0x0059	,0xa700	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN PING
/*COMPOSE            */	DEADTRANS(	L'R'	,0x0059	,0x01a6	,DKF_0	), // LATIN LETTER YR
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0059	,0xa702	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN SHANG
/*COMPOSE            */	DEADTRANS(	L's'	,0x0059	,0xa702	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN SHANG
/*COMPOSE            */	DEADTRANS(	L'y'	,0x00a6	,0x0079	,CHAIN	), // LATIN SMALL LETTER Y
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0079	,0x02eb	,DKF_0	), // MODIFIER LETTER YANG DEPARTING TONE MARK
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0079	,0x02eb	,CHAIN	), // MODIFIER LETTER YANG DEPARTING TONE MARK
/*COMPOSE            */	DEADTRANS(	L'n'	,0x02eb	,0x02eb	,DKF_0	), // MODIFIER LETTER YANG DEPARTING TONE MARK
/*COMPOSE            */	DEADTRANS(	L't'	,0x02eb	,0xab60	,DKF_0	), // LATIN SMALL LETTER SAKHA YAT
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0079	,0x02ea	,DKF_0	), // MODIFIER LETTER YIN DEPARTING TONE MARK
/*COMPOSE            */	DEADTRANS(	L'L'	,0x0079	,0x028a	,DKF_0	), // LATIN SMALL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'l'	,0x0079	,0x028a	,DKF_0	), // LATIN SMALL LETTER UPSILON
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0079	,0x0272	,DKF_0	), // LATIN SMALL LETTER N WITH LEFT HOOK
/*COMPOSE            */	DEADTRANS(	L'O'	,0x0079	,0x021c	,DKF_0	), // LATIN CAPITAL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'o'	,0x0079	,0x021d	,DKF_0	), // LATIN SMALL LETTER YOGH
/*COMPOSE            */	DEADTRANS(	L'P'	,0x0079	,0xa700	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN PING
/*COMPOSE            */	DEADTRANS(	L'p'	,0x0079	,0xa700	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN PING
/*COMPOSE            */	DEADTRANS(	L'r'	,0x0079	,0x01a6	,DKF_0	), // LATIN LETTER YR
/*COMPOSE            */	DEADTRANS(	L'S'	,0x0079	,0xa702	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN SHANG
/*COMPOSE            */	DEADTRANS(	L's'	,0x0079	,0xa702	,DKF_0	), // MODIFIER LETTER CHINESE TONE YIN SHANG
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x00a6	,0x005a	,CHAIN	), // LATIN CAPITAL LETTER Z
/*COMPOSE            */	DEADTRANS(	L'H'	,0x005a	,0x01b7	,DKF_0	), // LATIN CAPITAL LETTER EZH
/*COMPOSE            */	DEADTRANS(	L'h'	,0x005a	,0x01b7	,DKF_0	), // LATIN CAPITAL LETTER EZH
/*COMPOSE            */	DEADTRANS(	L'S'	,0x005a	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L'Z'	,0x005a	,0x2124	,DKF_0	), // DOUBLE-STRUCK CAPITAL Z
/*COMPOSE            */	DEADTRANS(	L'z'	,0x00a6	,0x007a	,CHAIN	), // LATIN SMALL LETTER Z
/*COMPOSE            */	DEADTRANS(	L'H'	,0x007a	,0x01b7	,DKF_0	), // LATIN CAPITAL LETTER EZH
/*COMPOSE            */	DEADTRANS(	L'h'	,0x007a	,0x0292	,DKF_0	), // LATIN SMALL LETTER EZH
/*COMPOSE            */	DEADTRANS(	L's'	,0x007a	,0x00df	,DKF_0	), // LATIN SMALL LETTER SHARP S
/*COMPOSE            */	DEADTRANS(	L'0'	,0x00a6	,0x2189	,DKF_0	), // VULGAR FRACTION ZERO THIRDS
/*COMPOSE            */	DEADTRANS(	L'1'	,0x00a6	,0x0031	,CHAIN	), // DIGIT ONE
/*COMPOSE            */	DEADTRANS(	L'1'	,0x0031	,0x2152	,DKF_0	), // VULGAR FRACTION ONE TENTH
/*COMPOSE            */	DEADTRANS(	L'2'	,0x0031	,0x00bd	,DKF_0	), // VULGAR FRACTION ONE HALF
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0031	,0x2153	,DKF_0	), // VULGAR FRACTION ONE THIRD
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0031	,0x00bc	,DKF_0	), // VULGAR FRACTION ONE QUARTER
/*COMPOSE            */	DEADTRANS(	L'5'	,0x0031	,0x2155	,DKF_0	), // VULGAR FRACTION ONE FIFTH
/*COMPOSE            */	DEADTRANS(	L'6'	,0x0031	,0x2159	,DKF_0	), // VULGAR FRACTION ONE SIXTH
/*COMPOSE            */	DEADTRANS(	L'7'	,0x0031	,0x2150	,DKF_0	), // VULGAR FRACTION ONE SEVENTH
/*COMPOSE            */	DEADTRANS(	L'8'	,0x0031	,0x215b	,DKF_0	), // VULGAR FRACTION ONE EIGHTH
/*COMPOSE            */	DEADTRANS(	L'9'	,0x0031	,0x2151	,DKF_0	), // VULGAR FRACTION ONE NINTH
/*COMPOSE            */	DEADTRANS(	0x002f	,0x0031	,0x215f	,DKF_0	), // FRACTION NUMERATOR ONE
/*COMPOSE            */	DEADTRANS(	L'2'	,0x00a6	,0x0032	,CHAIN	), // DIGIT TWO
/*COMPOSE            */	DEADTRANS(	L'V'	,0x0032	,0x221a	,DKF_0	), // SQUARE ROOT
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0032	,0x221a	,DKF_0	), // SQUARE ROOT
/*COMPOSE            */	DEADTRANS(	L'3'	,0x0032	,0x2154	,DKF_0	), // VULGAR FRACTION TWO THIRDS
/*COMPOSE            */	DEADTRANS(	L'5'	,0x0032	,0x2156	,DKF_0	), // VULGAR FRACTION TWO FIFTHS
/*COMPOSE            */	DEADTRANS(	0x003c	,0x0032	,0x226a	,DKF_0	), // MUCH LESS-THAN
/*COMPOSE            */	DEADTRANS(	0x003e	,0x0032	,0x226b	,DKF_0	), // MUCH GREATER-THAN
/*COMPOSE            */	DEADTRANS(	L'3'	,0x00a6	,0x0033	,CHAIN	), // DIGIT THREE
/*COMPOSE            */	DEADTRANS(	L'A'	,0x0033	,0xa722	,DKF_0	), // LATIN CAPITAL LETTER EGYPTOLOGICAL ALEF
/*COMPOSE            */	DEADTRANS(	L'a'	,0x0033	,0xa723	,DKF_0	), // LATIN SMALL LETTER EGYPTOLOGICAL ALEF
/*COMPOSE            */	DEADTRANS(	L'V'	,0x0033	,0x221b	,DKF_0	), // CUBE ROOT
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0033	,0x221b	,DKF_0	), // CUBE ROOT
/*COMPOSE            */	DEADTRANS(	L'4'	,0x0033	,0x00be	,DKF_0	), // VULGAR FRACTION THREE QUARTERS
/*COMPOSE            */	DEADTRANS(	L'5'	,0x0033	,0x2157	,DKF_0	), // VULGAR FRACTION THREE FIFTHS
/*COMPOSE            */	DEADTRANS(	L'8'	,0x0033	,0x215c	,DKF_0	), // VULGAR FRACTION THREE EIGHTHS
/*COMPOSE            */	DEADTRANS(	0x003c	,0x0033	,0x22d8	,DKF_0	), // VERY MUCH LESS-THAN
/*COMPOSE            */	DEADTRANS(	0x003e	,0x0033	,0x22d9	,DKF_0	), // VERY MUCH GREATER-THAN
/*COMPOSE            */	DEADTRANS(	L'4'	,0x00a6	,0x0034	,CHAIN	), // DIGIT FOUR
/*COMPOSE            */	DEADTRANS(	L'V'	,0x0034	,0x221c	,DKF_0	), // FOURTH ROOT
/*COMPOSE            */	DEADTRANS(	L'v'	,0x0034	,0x221c	,DKF_0	), // FOURTH ROOT
/*COMPOSE            */	DEADTRANS(	L'5'	,0x0034	,0x2158	,DKF_0	), // VULGAR FRACTION FOUR FIFTHS
/*COMPOSE            */	DEADTRANS(	L'5'	,0x00a6	,0x0035	,CHAIN	), // DIGIT FIVE
/*COMPOSE            */	DEADTRANS(	L'6'	,0x0035	,0x215a	,DKF_0	), // VULGAR FRACTION FIVE SIXTHS
/*COMPOSE            */	DEADTRANS(	L'8'	,0x0035	,0x215d	,DKF_0	), // VULGAR FRACTION FIVE EIGHTHS
/*COMPOSE            */	DEADTRANS(	L'6'	,0x00a6	,0x007c	,CHAIN	), // VERTICAL LINE
/*COMPOSE            */	DEADTRANS(	L'7'	,0x00a6	,0x0037	,CHAIN	), // DIGIT SEVEN
/*COMPOSE            */	DEADTRANS(	L'I'	,0x0037	,0x0296	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP
/*COMPOSE            */	DEADTRANS(	L'i'	,0x0037	,0x0296	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP
/*COMPOSE            */	DEADTRANS(	L'M'	,0x0037	,0x0241	,DKF_0	), // LATIN CAPITAL LETTER GLOTTAL STOP
/*COMPOSE            */	DEADTRANS(	L'm'	,0x0037	,0x0242	,DKF_0	), // LATIN SMALL LETTER GLOTTAL STOP
/*COMPOSE            */	DEADTRANS(	L'R'	,0x0037	,0x0295	,DKF_0	), // LATIN LETTER PHARYNGEAL VOICED FRICATIVE
/*COMPOSE            */	DEADTRANS(	L'r'	,0x0037	,0x0295	,DKF_0	), // LATIN LETTER PHARYNGEAL VOICED FRICATIVE
/*COMPOSE            */	DEADTRANS(	L'U'	,0x0037	,0x0294	,DKF_0	), // LATIN LETTER GLOTTAL STOP
/*COMPOSE            */	DEADTRANS(	L'u'	,0x0037	,0x0294	,DKF_0	), // LATIN LETTER GLOTTAL STOP
/*COMPOSE            */	DEADTRANS(	L'8'	,0x0037	,0x215e	,DKF_0	), // VULGAR FRACTION SEVEN EIGHTHS
/*COMPOSE            */	DEADTRANS(	L'8'	,0x00a6	,0x0038	,CHAIN	), // DIGIT EIGHT
/*COMPOSE            */	DEADTRANS(	0x003c	,0x0038	,0x2702	,CHAIN	), // BLACK SCISSORS
/*COMPOSE            */	DEADTRANS(	L'A'	,0x2702	,0x2700	,DKF_0	), // BLACK SAFETY SCISSORS
/*COMPOSE            */	DEADTRANS(	L'a'	,0x2702	,0x2700	,DKF_0	), // BLACK SAFETY SCISSORS
/*COMPOSE            */	DEADTRANS(	L'B'	,0x2702	,0x2704	,DKF_0	), // WHITE SCISSORS
/*COMPOSE            */	DEADTRANS(	L'b'	,0x2702	,0x2704	,DKF_0	), // WHITE SCISSORS
/*COMPOSE            */	DEADTRANS(	L'I'	,0x2702	,0x2703	,DKF_0	), // LOWER BLADE SCISSORS
/*COMPOSE            */	DEADTRANS(	L'i'	,0x2702	,0x2703	,DKF_0	), // LOWER BLADE SCISSORS
/*COMPOSE            */	DEADTRANS(	L'N'	,0x2702	,0x2702	,DKF_0	), // BLACK SCISSORS
/*COMPOSE            */	DEADTRANS(	L'n'	,0x2702	,0x2702	,DKF_0	), // BLACK SCISSORS
/*COMPOSE            */	DEADTRANS(	L'S'	,0x2702	,0x2701	,DKF_0	), // UPPER BLADE SCISSORS
/*COMPOSE            */	DEADTRANS(	L's'	,0x2702	,0x2701	,DKF_0	), // UPPER BLADE SCISSORS
/*COMPOSE            */	DEADTRANS(	0x002f	,0x2702	,0x2701	,DKF_0	), // UPPER BLADE SCISSORS
/*COMPOSE            */	DEADTRANS(	0x005c	,0x2702	,0x2703	,DKF_0	), // LOWER BLADE SCISSORS
/*COMPOSE            */	DEADTRANS(	0x0020	,0x00a6	,0x005f	,CHAIN	), // LOW LINE
/*COMPOSE            */	DEADTRANS(	0x0021	,0x00a6	,0x1e05	,CHAIN	), // LATIN SMALL LETTER B WITH DOT BELOW
/*COMPOSE            */	DEADTRANS(	0x0022	,0x00a6	,0x0151	,CHAIN	), // LATIN SMALL LETTER O WITH DOUBLE ACUTE
/*COMPOSE            */	DEADTRANS(	0x0023	,0x00a6	,0x1d14	,CHAIN	), // LATIN SMALL LETTER TURNED OE
/*COMPOSE            */	DEADTRANS(	0x0025	,0x00a6	,0x0281	,CHAIN	), // LATIN LETTER SMALL CAPITAL INVERTED R
/*COMPOSE            */	DEADTRANS(	0x0026	,0x00a6	,0x0221	,CHAIN	), // LATIN SMALL LETTER D WITH CURL
/*COMPOSE            */	DEADTRANS(	0x0027	,0x00a6	,0x00e1	,CHAIN	), // LATIN SMALL LETTER A WITH ACUTE
/*COMPOSE            */	DEADTRANS(	0x0028	,0x00a6	,0x0213	,CHAIN	), // LATIN SMALL LETTER R WITH INVERTED BREVE
/*COMPOSE            */	DEADTRANS(	0x0029	,0x00a6	,0x014f	,CHAIN	), // LATIN SMALL LETTER O WITH BREVE
/*COMPOSE            */	DEADTRANS(	0x002a	,0x00a6	,0x002a	,CHAIN	), // ASTERISK
/*COMPOSE            */	DEADTRANS(	0x002b	,0x00a6	,0x002b	,CHAIN	), // PLUS SIGN
/*COMPOSE            */	DEADTRANS(	0x002c	,0x00a6	,0x0229	,CHAIN	), // LATIN SMALL LETTER E WITH CEDILLA
/*COMPOSE            */	DEADTRANS(	0x002d	,0x00a6	,0x024d	,CHAIN	), // LATIN SMALL LETTER R WITH STROKE
/*COMPOSE            */	DEADTRANS(	0x002e	,0x00a6	,0x1e57	,CHAIN	), // LATIN SMALL LETTER P WITH DOT ABOVE
/*COMPOSE            */	DEADTRANS(	0x002f	,0x00a6	,0x00f8	,CHAIN	), // LATIN SMALL LETTER O WITH STROKE
/*COMPOSE            */	DEADTRANS(	0x003a	,0x00a6	,0x00eb	,CHAIN	), // LATIN SMALL LETTER E WITH DIAERESIS
/*COMPOSE            */	DEADTRANS(	0x003b	,0x00a6	,0x0219	,CHAIN	), // LATIN SMALL LETTER S WITH COMMA BELOW
/*COMPOSE            */	DEADTRANS(	0x003c	,0x00a6	,0x00ea	,CHAIN	), // LATIN SMALL LETTER E WITH CIRCUMFLEX
/*COMPOSE            */	DEADTRANS(	0x003d	,0x00a6	,0x003d	,CHAIN	), // EQUALS SIGN
/*COMPOSE            */	DEADTRANS(	0x003e	,0x00a6	,0x021f	,CHAIN	), // LATIN SMALL LETTER H WITH CARON
/*COMPOSE            */	DEADTRANS(	0x003f	,0x00a6	,0x003f	,CHAIN	), // QUESTION MARK
/*COMPOSE            */	DEADTRANS(	0x0021	,0x003f	,0x2048	,DKF_0	), // QUESTION EXCLAMATION MARK
/*COMPOSE            */	DEADTRANS(	0x0025	,0x003f	,0x1d24	,DKF_0	), // LATIN LETTER VOICED LARYNGEAL SPIRANT
/*COMPOSE            */	DEADTRANS(	0x002b	,0x003f	,0x203d	,DKF_0	), // INTERROBANG
/*COMPOSE            */	DEADTRANS(	0x002e	,0x003f	,0x203d	,DKF_0	), // INTERROBANG
/*COMPOSE            */	DEADTRANS(	0x003f	,0x003f	,0x2047	,DKF_0	), // DOUBLE QUESTION MARK
/*COMPOSE            */	DEADTRANS(	0x0040	,0x00a6	,0x25ef	,CHAIN	), // LARGE CIRCLE
/*COMPOSE            */	DEADTRANS(	0x005b	,0x00a6	,0x01eb	,CHAIN	), // LATIN SMALL LETTER O WITH OGONEK
/*COMPOSE            */	DEADTRANS(	0x005c	,0x00a6	,0x1d19	,CHAIN	), // LATIN LETTER SMALL CAPITAL REVERSED R
/*COMPOSE            */	DEADTRANS(	0x005d	,0x00a6	,0x1ebb	,CHAIN	), // LATIN SMALL LETTER E WITH HOOK ABOVE
/*COMPOSE            */	DEADTRANS(	0x005e	,0x00a6	,0x005e	,CHAIN	), // CIRCUMFLEX ACCENT
/*COMPOSE            */	DEADTRANS(	0x0060	,0x00a6	,0x00f2	,CHAIN	), // LATIN SMALL LETTER O WITH GRAVE
/*COMPOSE            */	DEADTRANS(	0x007b	,0x00a6	,0x0273	,CHAIN	), // LATIN SMALL LETTER N WITH RETROFLEX HOOK
/*COMPOSE            */	DEADTRANS(	0x007c	,0x00a6	,0x0101	,CHAIN	), // LATIN SMALL LETTER A WITH MACRON
/*COMPOSE            */	DEADTRANS(	0x007d	,0x00a6	,0x0192	,CHAIN	), // LATIN SMALL LETTER F WITH HOOK
/*COMPOSE            */	DEADTRANS(	0x007e	,0x00a6	,0x00f5	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE
/*COMPOSE            */	DEADTRANS(	0x20ac	,0x00a6	,0x00a4	,CHAIN	), // CURRENCY SIGN
/*COMPOSE            */	DEADTRANS(	0x00a4	,0x00a6	,0x1d79	,CHAIN	), // LATIN SMALL LETTER INSULAR G
/*COMPOSE            */	DEADTRANS(	0x00a9	,0x00a6	,0x00ae	,CHAIN	), // REGISTERED SIGN
/*COMPOSE            */	DEADTRANS(	0x00b0	,0x00a6	,0x00e5	,CHAIN	), // LATIN SMALL LETTER A WITH RING ABOVE
/*COMPOSE            */	DEADTRANS(	0x00b5	,0x00a6	,0x03a9	,CHAIN	), // GREEK CAPITAL LETTER OMEGA
/*COMPOSE            */	DEADTRANS(	0x0027	,0x03b5	,0x0313	,DKF_0	), // COMBINING COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x00f9	,0x03b5	,0x0313	,DKF_0	), // COMBINING COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x2019	,0x03b5	,0x0313	,DKF_0	), // COMBINING COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x00e8	,0x020f	,0x1abe	,DKF_0	), // COMBINING PARENTHESES OVERLAY
/*COMPOSE            */	DEADTRANS(	0x00e9	,0x020f	,0x1abb	,DKF_0	), // COMBINING PARENTHESES ABOVE
/*COMPOSE            */	DEADTRANS(	0x00ea	,0x00a6	,0x2191	,CHAIN	), // UPWARDS ARROW
/*COMPOSE            */	DEADTRANS(	0x00eb	,0x00a6	,0x2193	,CHAIN	), // DOWNWARDS ARROW
/*COMPOSE            */	DEADTRANS(	0x002e	,0x2193	,0x1ab4	,DKF_0	), // COMBINING TRIPLE DOT
/*COMPOSE            */	DEADTRANS(	0x003a	,0x2193	,0x205a	,DKF_0	), // TWO DOT PUNCTUATION
/*COMPOSE            */	DEADTRANS(	0x00eb	,0x2193	,0x205b	,DKF_0	), // FOUR DOT MARK
/*COMPOSE            */	DEADTRANS(	0x00f2	,0x00a6	,0x00d2	,CHAIN	), // LATIN CAPITAL LETTER O WITH GRAVE
/*COMPOSE            */	DEADTRANS(	0x0027	,0x00d2	,0x0312	,DKF_0	), // COMBINING TURNED COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x2019	,0x00d2	,0x0312	,DKF_0	), // COMBINING TURNED COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x00f5	,0x00a6	,0x00d5	,CHAIN	), // LATIN CAPITAL LETTER O WITH TILDE
/*COMPOSE            */	DEADTRANS(	0x0027	,0x00d5	,0x0314	,DKF_0	), // COMBINING REVERSED COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x00a3	,0x00d5	,0x1e1b	,CHAIN	), // LATIN SMALL LETTER E WITH TILDE BELOW
/*COMPOSE            */	DEADTRANS(	0x00f9	,0x00d5	,0x0314	,DKF_0	), // COMBINING REVERSED COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x2019	,0x00d5	,0x0314	,DKF_0	), // COMBINING REVERSED COMMA ABOVE
/*COMPOSE            */	DEADTRANS(	0x00f9	,0x020f	,0x1abb	,DKF_0	), // COMBINING PARENTHESES ABOVE
/*COMPOSE            */	DEADTRANS(	0x02bc	,0x00a6	,0x0149	,DKF_0	), // LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
/*COMPOSE            */	DEADTRANS(	0x2019	,0x00a6	,0x0149	,CHAIN	), // LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
/*COMPOSE            */	DEADTRANS(	L'n'	,0x0149	,0x0149	,DKF_0	), // LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
/*COMPOSE            */	DEADTRANS(	0x2610	,0x00a6	,0x2610	,CHAIN	), // BALLOT BOX
/*COMPOSE            */	DEADTRANS(	L'O'	,0x2610	,0x2384	,DKF_0	), // COMPOSITION SYMBOL
/*COMPOSE            */	DEADTRANS(	L'o'	,0x2610	,0x2384	,DKF_0	), // COMPOSITION SYMBOL
/*COMPOSE            */	DEADTRANS(	0x0040	,0x2610	,0x2384	,DKF_0	), // COMPOSITION SYMBOL
/*CROSSED_TAIL       */	DEADTRANS(	L'g'	,0xab3a	,0xab36	,DKF_0	), // LATIN SMALL LETTER SCRIPT G WITH CROSSED-TAIL
/*CROSSED_TAIL       */	DEADTRANS(	L'J'	,0xab3a	,0xa7b2	,DKF_0	), // LATIN CAPITAL LETTER J WITH CROSSED-TAIL
/*CROSSED_TAIL       */	DEADTRANS(	L'j'	,0xab3a	,0x029d	,DKF_0	), // LATIN SMALL LETTER J WITH CROSSED-TAIL
/*CROSSED_TAIL       */	DEADTRANS(	L'm'	,0xab3a	,0xab3a	,DKF_0	), // LATIN SMALL LETTER M WITH CROSSED-TAIL
/*CROSSED_TAIL       */	DEADTRANS(	L'n'	,0xab3a	,0xab3b	,DKF_0	), // LATIN SMALL LETTER N WITH CROSSED-TAIL
/*CROSSED_TAIL       */	DEADTRANS(	L'r'	,0xab3a	,0xab49	,DKF_0	), // LATIN SMALL LETTER R WITH CROSSED-TAIL
/*CROSSED_TAIL       */	DEADTRANS(	0x003d	,0xab3a	,0xab4a	,DKF_0	), // LATIN SMALL LETTER DOUBLE R WITH CROSSED-TAIL
/*CROSSED_TAIL       */	DEADTRANS(	0x00a9	,0xab3a	,0xab3c	,DKF_0	), // LATIN SMALL LETTER ENG WITH CROSSED-TAIL
/*CURL               */	DEADTRANS(	L'a'	,0x0221	,0x1d25	,DKF_0	), // LATIN LETTER AIN
/*CURL               */	DEADTRANS(	L'c'	,0x0221	,0x0255	,DKF_0	), // LATIN SMALL LETTER C WITH CURL
/*CURL               */	DEADTRANS(	L'd'	,0x0221	,0x0221	,DKF_0	), // LATIN SMALL LETTER D WITH CURL
/*CURL               */	DEADTRANS(	L'g'	,0x0221	,0xab36	,DKF_0	), // LATIN SMALL LETTER SCRIPT G WITH CROSSED-TAIL
/*CURL               */	DEADTRANS(	L'J'	,0x0221	,0xa7b2	,DKF_0	), // LATIN CAPITAL LETTER J WITH CROSSED-TAIL
/*CURL               */	DEADTRANS(	L'j'	,0x0221	,0x029d	,DKF_0	), // LATIN SMALL LETTER J WITH CROSSED-TAIL
/*CURL               */	DEADTRANS(	L'l'	,0x0221	,0x0234	,DKF_0	), // LATIN SMALL LETTER L WITH CURL
/*CURL               */	DEADTRANS(	L'n'	,0x0221	,0x0235	,DKF_0	), // LATIN SMALL LETTER N WITH CURL
/*CURL               */	DEADTRANS(	L'O'	,0x0221	,0xa74c	,DKF_0	), // LATIN CAPITAL LETTER O WITH LOOP
/*CURL               */	DEADTRANS(	L'o'	,0x0221	,0xa74d	,DKF_0	), // LATIN SMALL LETTER O WITH LOOP
/*CURL               */	DEADTRANS(	L's'	,0x0221	,0x0286	,DKF_0	), // LATIN SMALL LETTER ESH WITH CURL
/*CURL               */	DEADTRANS(	L't'	,0x0221	,0x0236	,DKF_0	), // LATIN SMALL LETTER T WITH CURL
/*CURL               */	DEADTRANS(	L'v'	,0x0221	,0x2c74	,DKF_0	), // LATIN SMALL LETTER V WITH CURL
/*CURL               */	DEADTRANS(	L'X'	,0x0221	,0xab3a	,CHAIN	), // LATIN SMALL LETTER M WITH CROSSED-TAIL
/*CURL               */	DEADTRANS(	L'x'	,0x0221	,0xab3a	,CHAIN	), // LATIN SMALL LETTER M WITH CROSSED-TAIL
/*CURL               */	DEADTRANS(	L'Y'	,0x0221	,0x1efe	,DKF_0	), // LATIN CAPITAL LETTER Y WITH LOOP
/*CURL               */	DEADTRANS(	L'y'	,0x0221	,0x1eff	,DKF_0	), // LATIN SMALL LETTER Y WITH LOOP
/*CURL               */	DEADTRANS(	L'z'	,0x0221	,0x0291	,DKF_0	), // LATIN SMALL LETTER Z WITH CURL
/*CURL               */	DEADTRANS(	0x0026	,0x0221	,0x2113	,CHAIN	), // SCRIPT SMALL L
/*CURL               */	DEADTRANS(	0x002e	,0x0221	,0x2055	,DKF_0	), // FLOWER PUNCTUATION MARK
/*CURL               */	DEADTRANS(	0x007c	,0x0221	,0x2055	,CHAIN	), // FLOWER PUNCTUATION MARK
/*CURL               */	DEADTRANS(	L'A'	,0x2055	,0xa724	,DKF_0	), // LATIN CAPITAL LETTER EGYPTOLOGICAL AIN
/*CURL               */	DEADTRANS(	L'a'	,0x2055	,0xa725	,DKF_0	), // LATIN SMALL LETTER EGYPTOLOGICAL AIN
/*CURL               */	DEADTRANS(	0x00a9	,0x0221	,0x0255	,CHAIN	), // LATIN SMALL LETTER C WITH CURL
/*CURL               */	DEADTRANS(	L'd'	,0x0255	,0x02a5	,DKF_0	), // LATIN SMALL LETTER DZ DIGRAPH WITH CURL
/*CURL               */	DEADTRANS(	L's'	,0x0255	,0x0286	,DKF_0	), // LATIN SMALL LETTER ESH WITH CURL
/*CURL               */	DEADTRANS(	L't'	,0x0255	,0x02a8	,DKF_0	), // LATIN SMALL LETTER TC DIGRAPH WITH CURL
/*CURL               */	DEADTRANS(	L'z'	,0x0255	,0x0293	,DKF_0	), // LATIN SMALL LETTER EZH WITH CURL
/*CURRENCY           */	DEADTRANS(	0x0020	,0x00a4	,0x00a4	,DKF_0	), // CURRENCY SIGN
/*CURRENCY           */	DEADTRANS(	0x202f	,0x00a4	,0x00a4	,DKF_0	), // CURRENCY SIGN
/*CURRENCY           */	DEADTRANS(	L'A'	,0x00a4	,0x20b3	,DKF_0	), // AUSTRAL SIGN
/*CURRENCY           */	DEADTRANS(	L'a'	,0x00a4	,0x060b	,DKF_0	), // AFGHANI SIGN
/*CURRENCY           */	DEADTRANS(	L'B'	,0x00a4	,0x0e3f	,DKF_0	), // THAI CURRENCY SYMBOL BAHT
/*CURRENCY           */	DEADTRANS(	L'b'	,0x00a4	,0x20bf	,DKF_0	), // BITCOIN SIGN
/*CURRENCY           */	DEADTRANS(	L'C'	,0x00a4	,0x20b5	,DKF_0	), // CEDI SIGN
/*CURRENCY           */	DEADTRANS(	L'c'	,0x00a4	,0x00a2	,CHAIN	), // CENT SIGN
/*CURRENCY           */	DEADTRANS(	L'e'	,0x00a2	,0x20b5	,DKF_0	), // CEDI SIGN
/*CURRENCY           */	DEADTRANS(	L'o'	,0x00a2	,0x20a1	,DKF_0	), // COLON SIGN
/*CURRENCY           */	DEADTRANS(	L'r'	,0x00a2	,0x20a2	,DKF_0	), // CRUZEIRO SIGN
/*CURRENCY           */	DEADTRANS(	0x002f	,0x00a2	,0x00a2	,DKF_0	), // CENT SIGN
/*CURRENCY           */	DEADTRANS(	L'D'	,0x00a4	,0x20af	,DKF_0	), // DRACHMA SIGN
/*CURRENCY           */	DEADTRANS(	L'd'	,0x00a4	,0x20ab	,DKF_0	), // DONG SIGN
/*CURRENCY           */	DEADTRANS(	L'E'	,0x00a4	,0x20ac	,DKF_0	), // EURO SIGN
/*CURRENCY           */	DEADTRANS(	L'e'	,0x00a4	,0x20ac	,DKF_0	), // EURO SIGN
/*CURRENCY           */	DEADTRANS(	L'F'	,0x00a4	,0x20a3	,DKF_0	), // FRENCH FRANC SIGN
/*CURRENCY           */	DEADTRANS(	L'f'	,0x00a4	,0x0192	,DKF_0	), // LATIN SMALL LETTER F WITH HOOK
/*CURRENCY           */	DEADTRANS(	L'G'	,0x00a4	,0x20b2	,DKF_0	), // GUARANI SIGN
/*CURRENCY           */	DEADTRANS(	L'H'	,0x00a4	,0x20bd	,DKF_0	), // RUBLE SIGN
/*CURRENCY           */	DEADTRANS(	L'h'	,0x00a4	,0x20b4	,DKF_0	), // HRYVNIA SIGN
/*CURRENCY           */	DEADTRANS(	L'I'	,0x00a4	,0x20a4	,DKF_0	), // LIRA SIGN
/*CURRENCY           */	DEADTRANS(	L'K'	,0x00a4	,0x20ad	,DKF_0	), // KIP SIGN
/*CURRENCY           */	DEADTRANS(	L'k'	,0x00a4	,0x17db	,DKF_0	), // KHMER CURRENCY SYMBOL RIEL
/*CURRENCY           */	DEADTRANS(	L'L'	,0x00a4	,0x20be	,DKF_0	), // LARI SIGN
/*CURRENCY           */	DEADTRANS(	L'l'	,0x00a4	,0x20ba	,DKF_0	), // TURKISH LIRA SIGN
/*CURRENCY           */	DEADTRANS(	L'M'	,0x00a4	,0x20bc	,DKF_0	), // MANAT SIGN
/*CURRENCY           */	DEADTRANS(	L'm'	,0x00a4	,0x20a5	,DKF_0	), // MILL SIGN
/*CURRENCY           */	DEADTRANS(	L'N'	,0x00a4	,0x20a6	,DKF_0	), // NAIRA SIGN
/*CURRENCY           */	DEADTRANS(	L'n'	,0x00a4	,0x20aa	,DKF_0	), // NEW SHEQEL SIGN
/*CURRENCY           */	DEADTRANS(	L'O'	,0x00a4	,0x20a1	,DKF_0	), // COLON SIGN
/*CURRENCY           */	DEADTRANS(	L'o'	,0x00a4	,0x20a1	,DKF_0	), // COLON SIGN
/*CURRENCY           */	DEADTRANS(	L'P'	,0x00a4	,0x20b1	,DKF_0	), // PESO SIGN
/*CURRENCY           */	DEADTRANS(	L'p'	,0x00a4	,0x20a7	,CHAIN	), // PESETA SIGN
/*CURRENCY           */	DEADTRANS(	L'f'	,0x20a7	,0x20b0	,DKF_0	), // GERMAN PENNY SIGN
/*CURRENCY           */	DEADTRANS(	L't'	,0x20a7	,0x20a7	,DKF_0	), // PESETA SIGN
/*CURRENCY           */	DEADTRANS(	L'Q'	,0x00a4	,0x00a4	,DKF_0	), // CURRENCY SIGN
/*CURRENCY           */	DEADTRANS(	L'q'	,0x00a4	,0x00a4	,DKF_0	), // CURRENCY SIGN
/*CURRENCY           */	DEADTRANS(	L'R'	,0x00a4	,0x20b9	,CHAIN	), // INDIAN RUPEE SIGN
/*CURRENCY           */	DEADTRANS(	L'b'	,0x20b9	,0x09f2	,DKF_0	), // BENGALI RUPEE MARK
/*CURRENCY           */	DEADTRANS(	L'g'	,0x20b9	,0x0af1	,DKF_0	), // GUJARATI RUPEE SIGN
/*CURRENCY           */	DEADTRANS(	L'r'	,0x20b9	,0x20b9	,DKF_0	), // INDIAN RUPEE SIGN
/*CURRENCY           */	DEADTRANS(	L's'	,0x20b9	,0x20a8	,DKF_0	), // RUPEE SIGN
/*CURRENCY           */	DEADTRANS(	L't'	,0x20b9	,0x0bf9	,DKF_0	), // TAMIL RUPEE SIGN
/*CURRENCY           */	DEADTRANS(	L'r'	,0x00a4	,0xfdfc	,DKF_0	), // RIAL SIGN
/*CURRENCY           */	DEADTRANS(	L'S'	,0x00a4	,0x20b7	,DKF_0	), // SPESMILO SIGN
/*CURRENCY           */	DEADTRANS(	0x007c	,0x00a4	,0x0024	,DKF_0	), // DOLLAR SIGN
/*CURRENCY           */	DEADTRANS(	L'T'	,0x00a4	,0x20b8	,DKF_0	), // TENGE SIGN
/*CURRENCY           */	DEADTRANS(	L't'	,0x00a4	,0x20ae	,DKF_0	), // TUGRIK SIGN
/*CURRENCY           */	DEADTRANS(	L'W'	,0x00a4	,0x20a9	,DKF_0	), // WON SIGN
/*CURRENCY           */	DEADTRANS(	L'w'	,0x00a4	,0x20a9	,DKF_0	), // WON SIGN
/*CURRENCY           */	DEADTRANS(	L'X'	,0x00a4	,0x2133	,DKF_0	), // SCRIPT CAPITAL M
/*CURRENCY           */	DEADTRANS(	L'Y'	,0x00a4	,0x00a5	,DKF_0	), // YEN SIGN
/*CURRENCY           */	DEADTRANS(	L'y'	,0x00a4	,0x00a5	,DKF_0	), // YEN SIGN
/*CURRENCY           */	DEADTRANS(	L'Z'	,0x00a4	,0x20a2	,DKF_0	), // CRUZEIRO SIGN
/*CURRENCY           */	DEADTRANS(	L'z'	,0x00a4	,0x20a2	,DKF_0	), // CRUZEIRO SIGN
/*CURRENCY           */	DEADTRANS(	0x20ac	,0x00a4	,0x20a0	,DKF_0	), // EURO-CURRENCY SIGN
/*CURRENCY           */	DEADTRANS(	0x00a3	,0x00a4	,0x00a3	,DKF_0	), // POUND SIGN
/*CURRENCY           */	DEADTRANS(	0x00b5	,0x00a4	,0x20bb	,DKF_0	), // NORDIC MARK SIGN
/*CURRENCY           */	DEADTRANS(	0x2610	,0x00a4	,0x20b6	,DKF_0	), // LIVRE TOURNOIS SIGN
/*CYRILLIC           */	DEADTRANS(	L'A'	,0x0436	,0x0410	,DKF_0	), // CYRILLIC CAPITAL LETTER A
/*CYRILLIC           */	DEADTRANS(	L'a'	,0x0436	,0x0430	,DKF_0	), // CYRILLIC SMALL LETTER A
/*CYRILLIC           */	DEADTRANS(	L'B'	,0x0436	,0x0411	,DKF_0	), // CYRILLIC CAPITAL LETTER BE
/*CYRILLIC           */	DEADTRANS(	L'b'	,0x0436	,0x0431	,DKF_0	), // CYRILLIC SMALL LETTER BE
/*CYRILLIC           */	DEADTRANS(	L'C'	,0x0436	,0x0426	,DKF_0	), // CYRILLIC CAPITAL LETTER TSE
/*CYRILLIC           */	DEADTRANS(	L'c'	,0x0436	,0x0446	,DKF_0	), // CYRILLIC SMALL LETTER TSE
/*CYRILLIC           */	DEADTRANS(	L'D'	,0x0436	,0x0414	,DKF_0	), // CYRILLIC CAPITAL LETTER DE
/*CYRILLIC           */	DEADTRANS(	L'd'	,0x0436	,0x0434	,DKF_0	), // CYRILLIC SMALL LETTER DE
/*CYRILLIC           */	DEADTRANS(	L'E'	,0x0436	,0x0415	,DKF_0	), // CYRILLIC CAPITAL LETTER IE
/*CYRILLIC           */	DEADTRANS(	L'e'	,0x0436	,0x0435	,DKF_0	), // CYRILLIC SMALL LETTER IE
/*CYRILLIC           */	DEADTRANS(	L'F'	,0x0436	,0x0424	,DKF_0	), // CYRILLIC CAPITAL LETTER EF
/*CYRILLIC           */	DEADTRANS(	L'f'	,0x0436	,0x0444	,DKF_0	), // CYRILLIC SMALL LETTER EF
/*CYRILLIC           */	DEADTRANS(	L'G'	,0x0436	,0x0413	,DKF_0	), // CYRILLIC CAPITAL LETTER GHE
/*CYRILLIC           */	DEADTRANS(	L'g'	,0x0436	,0x0433	,DKF_0	), // CYRILLIC SMALL LETTER GHE
/*CYRILLIC           */	DEADTRANS(	L'H'	,0x0436	,0x0425	,DKF_0	), // CYRILLIC CAPITAL LETTER HA
/*CYRILLIC           */	DEADTRANS(	L'h'	,0x0436	,0x0445	,DKF_0	), // CYRILLIC SMALL LETTER HA
/*CYRILLIC           */	DEADTRANS(	L'I'	,0x0436	,0x0418	,DKF_0	), // CYRILLIC CAPITAL LETTER I
/*CYRILLIC           */	DEADTRANS(	L'i'	,0x0436	,0x0438	,DKF_0	), // CYRILLIC SMALL LETTER I
/*CYRILLIC           */	DEADTRANS(	L'J'	,0x0436	,0x0419	,DKF_0	), // CYRILLIC CAPITAL LETTER SHORT I
/*CYRILLIC           */	DEADTRANS(	L'j'	,0x0436	,0x0439	,DKF_0	), // CYRILLIC SMALL LETTER SHORT I
/*CYRILLIC           */	DEADTRANS(	L'K'	,0x0436	,0x041a	,DKF_0	), // CYRILLIC CAPITAL LETTER KA
/*CYRILLIC           */	DEADTRANS(	L'k'	,0x0436	,0x043a	,DKF_0	), // CYRILLIC SMALL LETTER KA
/*CYRILLIC           */	DEADTRANS(	L'L'	,0x0436	,0x041b	,DKF_0	), // CYRILLIC CAPITAL LETTER EL
/*CYRILLIC           */	DEADTRANS(	L'l'	,0x0436	,0x043b	,DKF_0	), // CYRILLIC SMALL LETTER EL
/*CYRILLIC           */	DEADTRANS(	L'M'	,0x0436	,0x041c	,DKF_0	), // CYRILLIC CAPITAL LETTER EM
/*CYRILLIC           */	DEADTRANS(	L'm'	,0x0436	,0x043c	,DKF_0	), // CYRILLIC SMALL LETTER EM
/*CYRILLIC           */	DEADTRANS(	L'N'	,0x0436	,0x041d	,DKF_0	), // CYRILLIC CAPITAL LETTER EN
/*CYRILLIC           */	DEADTRANS(	L'n'	,0x0436	,0x043d	,DKF_0	), // CYRILLIC SMALL LETTER EN
/*CYRILLIC           */	DEADTRANS(	L'O'	,0x0436	,0x041e	,DKF_0	), // CYRILLIC CAPITAL LETTER O
/*CYRILLIC           */	DEADTRANS(	L'o'	,0x0436	,0x043e	,DKF_0	), // CYRILLIC SMALL LETTER O
/*CYRILLIC           */	DEADTRANS(	L'P'	,0x0436	,0x041f	,DKF_0	), // CYRILLIC CAPITAL LETTER PE
/*CYRILLIC           */	DEADTRANS(	L'p'	,0x0436	,0x043f	,DKF_0	), // CYRILLIC SMALL LETTER PE
/*CYRILLIC           */	DEADTRANS(	L'Q'	,0x0436	,0x0427	,DKF_0	), // CYRILLIC CAPITAL LETTER CHE
/*CYRILLIC           */	DEADTRANS(	L'q'	,0x0436	,0x0447	,DKF_0	), // CYRILLIC SMALL LETTER CHE
/*CYRILLIC           */	DEADTRANS(	L'R'	,0x0436	,0x0420	,DKF_0	), // CYRILLIC CAPITAL LETTER ER
/*CYRILLIC           */	DEADTRANS(	L'r'	,0x0436	,0x0440	,DKF_0	), // CYRILLIC SMALL LETTER ER
/*CYRILLIC           */	DEADTRANS(	L'S'	,0x0436	,0x0421	,DKF_0	), // CYRILLIC CAPITAL LETTER ES
/*CYRILLIC           */	DEADTRANS(	L's'	,0x0436	,0x0441	,DKF_0	), // CYRILLIC SMALL LETTER ES
/*CYRILLIC           */	DEADTRANS(	L'T'	,0x0436	,0x0422	,DKF_0	), // CYRILLIC CAPITAL LETTER TE
/*CYRILLIC           */	DEADTRANS(	L't'	,0x0436	,0x0442	,DKF_0	), // CYRILLIC SMALL LETTER TE
/*CYRILLIC           */	DEADTRANS(	L'U'	,0x0436	,0x0423	,DKF_0	), // CYRILLIC CAPITAL LETTER U
/*CYRILLIC           */	DEADTRANS(	L'u'	,0x0436	,0x0443	,DKF_0	), // CYRILLIC SMALL LETTER U
/*CYRILLIC           */	DEADTRANS(	L'V'	,0x0436	,0x0412	,DKF_0	), // CYRILLIC CAPITAL LETTER VE
/*CYRILLIC           */	DEADTRANS(	L'v'	,0x0436	,0x0432	,DKF_0	), // CYRILLIC SMALL LETTER VE
/*CYRILLIC           */	DEADTRANS(	L'W'	,0x0436	,0x0428	,DKF_0	), // CYRILLIC CAPITAL LETTER SHA
/*CYRILLIC           */	DEADTRANS(	L'w'	,0x0436	,0x0448	,DKF_0	), // CYRILLIC SMALL LETTER SHA
/*CYRILLIC           */	DEADTRANS(	L'X'	,0x0436	,0x0416	,DKF_0	), // CYRILLIC CAPITAL LETTER ZHE
/*CYRILLIC           */	DEADTRANS(	L'x'	,0x0436	,0x0436	,DKF_0	), // CYRILLIC SMALL LETTER ZHE
/*CYRILLIC           */	DEADTRANS(	L'Y'	,0x0436	,0x042a	,DKF_0	), // CYRILLIC CAPITAL LETTER HARD SIGN
/*CYRILLIC           */	DEADTRANS(	L'y'	,0x0436	,0x044a	,DKF_0	), // CYRILLIC SMALL LETTER HARD SIGN
/*CYRILLIC           */	DEADTRANS(	L'Z'	,0x0436	,0x0417	,DKF_0	), // CYRILLIC CAPITAL LETTER ZE
/*CYRILLIC           */	DEADTRANS(	L'z'	,0x0436	,0x0437	,DKF_0	), // CYRILLIC SMALL LETTER ZE
/*CYRILLIC           */	DEADTRANS(	0x002a	,0x0436	,0x0482	,DKF_0	), // CYRILLIC THOUSANDS SIGN
/*CYRILLIC           */	DEADTRANS(	0x0436	,0x0436	,0x0416	,CHAIN	), // CYRILLIC CAPITAL LETTER ZHE
/*CYRILLIC           */	DEADTRANS(	0x1f12	,0x0436	,0x0482	,DKF_0	), // CYRILLIC THOUSANDS SIGN
/*CYRILLIC           */	DEADTRANS(	0x00e1	,0x0436	,0x0449	,DKF_0	), // CYRILLIC SMALL LETTER SHCHA
/*CYRILLIC           */	DEADTRANS(	0x1f7d	,0x0436	,0x0449	,DKF_0	), // CYRILLIC SMALL LETTER SHCHA
/*CYRILLIC           */	DEADTRANS(	0x00ea	,0x0436	,0x044f	,DKF_0	), // CYRILLIC SMALL LETTER YA
/*CYRILLIC           */	DEADTRANS(	0x1fc6	,0x0436	,0x044f	,DKF_0	), // CYRILLIC SMALL LETTER YA
/*CYRILLIC           */	DEADTRANS(	0x00eb	,0x0436	,0x042f	,DKF_0	), // CYRILLIC CAPITAL LETTER YA
/*CYRILLIC           */	DEADTRANS(	0x03ca	,0x0436	,0x042f	,DKF_0	), // CYRILLIC CAPITAL LETTER YA
/*CYRILLIC           */	DEADTRANS(	0x00f2	,0x0436	,0x044c	,DKF_0	), // CYRILLIC SMALL LETTER SOFT SIGN
/*CYRILLIC           */	DEADTRANS(	0x1f70	,0x0436	,0x044c	,DKF_0	), // CYRILLIC SMALL LETTER SOFT SIGN
/*CYRILLIC           */	DEADTRANS(	0x00f5	,0x0436	,0x0429	,DKF_0	), // CYRILLIC CAPITAL LETTER SHCHA
/*CYRILLIC           */	DEADTRANS(	0x1f14	,0x0436	,0x0429	,DKF_0	), // CYRILLIC CAPITAL LETTER SHCHA
/*CYRILLIC           */	DEADTRANS(	0x03cc	,0x0436	,0x045d	,DKF_0	), // CYRILLIC SMALL LETTER I WITH GRAVE
/*CYRILLIC           */	DEADTRANS(	0x2019	,0x0436	,0x045d	,DKF_0	), // CYRILLIC SMALL LETTER I WITH GRAVE
/*CYRILLIC           */	DEADTRANS(	0x02bc	,0x0436	,0x040d	,DKF_0	), // CYRILLIC CAPITAL LETTER I WITH GRAVE
/*CYRILLIC           */	DEADTRANS(	0x0390	,0x0436	,0x040d	,DKF_0	), // CYRILLIC CAPITAL LETTER I WITH GRAVE
/*CYRILLIC           */	DEADTRANS(	0x0391	,0x0436	,0x0410	,DKF_0	), // CYRILLIC CAPITAL LETTER A
/*CYRILLIC           */	DEADTRANS(	0x03b1	,0x0436	,0x0430	,DKF_0	), // CYRILLIC SMALL LETTER A
/*CYRILLIC           */	DEADTRANS(	0x0392	,0x0436	,0x0411	,DKF_0	), // CYRILLIC CAPITAL LETTER BE
/*CYRILLIC           */	DEADTRANS(	0x03b2	,0x0436	,0x0431	,DKF_0	), // CYRILLIC SMALL LETTER BE
/*CYRILLIC           */	DEADTRANS(	0x0393	,0x0436	,0x0413	,DKF_0	), // CYRILLIC CAPITAL LETTER GHE
/*CYRILLIC           */	DEADTRANS(	0x03b3	,0x0436	,0x0433	,DKF_0	), // CYRILLIC SMALL LETTER GHE
/*CYRILLIC           */	DEADTRANS(	0x0394	,0x0436	,0x0414	,DKF_0	), // CYRILLIC CAPITAL LETTER DE
/*CYRILLIC           */	DEADTRANS(	0x03b4	,0x0436	,0x0434	,DKF_0	), // CYRILLIC SMALL LETTER DE
/*CYRILLIC           */	DEADTRANS(	0x0395	,0x0436	,0x0415	,DKF_0	), // CYRILLIC CAPITAL LETTER IE
/*CYRILLIC           */	DEADTRANS(	0x03b5	,0x0436	,0x0435	,DKF_0	), // CYRILLIC SMALL LETTER IE
/*CYRILLIC           */	DEADTRANS(	0x0396	,0x0436	,0x0417	,DKF_0	), // CYRILLIC CAPITAL LETTER ZE
/*CYRILLIC           */	DEADTRANS(	0x03b6	,0x0436	,0x0437	,DKF_0	), // CYRILLIC SMALL LETTER ZE
/*CYRILLIC           */	DEADTRANS(	0x0397	,0x0436	,0x0425	,DKF_0	), // CYRILLIC CAPITAL LETTER HA
/*CYRILLIC           */	DEADTRANS(	0x03b7	,0x0436	,0x0445	,DKF_0	), // CYRILLIC SMALL LETTER HA
/*CYRILLIC           */	DEADTRANS(	0x0398	,0x0436	,0x0423	,DKF_0	), // CYRILLIC CAPITAL LETTER U
/*CYRILLIC           */	DEADTRANS(	0x03b8	,0x0436	,0x0443	,DKF_0	), // CYRILLIC SMALL LETTER U
/*CYRILLIC           */	DEADTRANS(	0x0399	,0x0436	,0x0418	,DKF_0	), // CYRILLIC CAPITAL LETTER I
/*CYRILLIC           */	DEADTRANS(	0x03b9	,0x0436	,0x0438	,DKF_0	), // CYRILLIC SMALL LETTER I
/*CYRILLIC           */	DEADTRANS(	0x039a	,0x0436	,0x041a	,DKF_0	), // CYRILLIC CAPITAL LETTER KA
/*CYRILLIC           */	DEADTRANS(	0x03ba	,0x0436	,0x043a	,DKF_0	), // CYRILLIC SMALL LETTER KA
/*CYRILLIC           */	DEADTRANS(	0x039b	,0x0436	,0x041b	,DKF_0	), // CYRILLIC CAPITAL LETTER EL
/*CYRILLIC           */	DEADTRANS(	0x03bb	,0x0436	,0x043b	,DKF_0	), // CYRILLIC SMALL LETTER EL
/*CYRILLIC           */	DEADTRANS(	0x039c	,0x0436	,0x041c	,DKF_0	), // CYRILLIC CAPITAL LETTER EM
/*CYRILLIC           */	DEADTRANS(	0x03bc	,0x0436	,0x043c	,DKF_0	), // CYRILLIC SMALL LETTER EM
/*CYRILLIC           */	DEADTRANS(	0x039d	,0x0436	,0x041d	,DKF_0	), // CYRILLIC CAPITAL LETTER EN
/*CYRILLIC           */	DEADTRANS(	0x03bd	,0x0436	,0x043d	,DKF_0	), // CYRILLIC SMALL LETTER EN
/*CYRILLIC           */	DEADTRANS(	0x039e	,0x0436	,0x0419	,DKF_0	), // CYRILLIC CAPITAL LETTER SHORT I
/*CYRILLIC           */	DEADTRANS(	0x03be	,0x0436	,0x0439	,DKF_0	), // CYRILLIC SMALL LETTER SHORT I
/*CYRILLIC           */	DEADTRANS(	0x039f	,0x0436	,0x041e	,DKF_0	), // CYRILLIC CAPITAL LETTER O
/*CYRILLIC           */	DEADTRANS(	0x03bf	,0x0436	,0x043e	,DKF_0	), // CYRILLIC SMALL LETTER O
/*CYRILLIC           */	DEADTRANS(	0x03a0	,0x0436	,0x041f	,DKF_0	), // CYRILLIC CAPITAL LETTER PE
/*CYRILLIC           */	DEADTRANS(	0x03c0	,0x0436	,0x043f	,DKF_0	), // CYRILLIC SMALL LETTER PE
/*CYRILLIC           */	DEADTRANS(	0x03a1	,0x0436	,0x0420	,DKF_0	), // CYRILLIC CAPITAL LETTER ER
/*CYRILLIC           */	DEADTRANS(	0x03c1	,0x0436	,0x0440	,DKF_0	), // CYRILLIC SMALL LETTER ER
/*CYRILLIC           */	DEADTRANS(	0x03a3	,0x0436	,0x0421	,DKF_0	), // CYRILLIC CAPITAL LETTER ES
/*CYRILLIC           */	DEADTRANS(	0x03c2	,0x0436	,0x0447	,DKF_0	), // CYRILLIC SMALL LETTER CHE
/*CYRILLIC           */	DEADTRANS(	0x03c3	,0x0436	,0x0441	,DKF_0	), // CYRILLIC SMALL LETTER ES
/*CYRILLIC           */	DEADTRANS(	0x03a4	,0x0436	,0x0422	,DKF_0	), // CYRILLIC CAPITAL LETTER TE
/*CYRILLIC           */	DEADTRANS(	0x03c4	,0x0436	,0x0442	,DKF_0	), // CYRILLIC SMALL LETTER TE
/*CYRILLIC           */	DEADTRANS(	0x03a5	,0x0436	,0x042a	,DKF_0	), // CYRILLIC CAPITAL LETTER HARD SIGN
/*CYRILLIC           */	DEADTRANS(	0x03c5	,0x0436	,0x044a	,DKF_0	), // CYRILLIC SMALL LETTER HARD SIGN
/*CYRILLIC           */	DEADTRANS(	0x03a6	,0x0436	,0x0424	,DKF_0	), // CYRILLIC CAPITAL LETTER EF
/*CYRILLIC           */	DEADTRANS(	0x03c6	,0x0436	,0x0444	,DKF_0	), // CYRILLIC SMALL LETTER EF
/*CYRILLIC           */	DEADTRANS(	0x03a7	,0x0436	,0x0416	,DKF_0	), // CYRILLIC CAPITAL LETTER ZHE
/*CYRILLIC           */	DEADTRANS(	0x03c7	,0x0436	,0x0436	,DKF_0	), // CYRILLIC SMALL LETTER ZHE
/*CYRILLIC           */	DEADTRANS(	0x03a8	,0x0436	,0x0426	,DKF_0	), // CYRILLIC CAPITAL LETTER TSE
/*CYRILLIC           */	DEADTRANS(	0x03c8	,0x0436	,0x0446	,DKF_0	), // CYRILLIC SMALL LETTER TSE
/*CYRILLIC           */	DEADTRANS(	0x03a9	,0x0436	,0x0412	,DKF_0	), // CYRILLIC CAPITAL LETTER VE
/*CYRILLIC           */	DEADTRANS(	0x03c9	,0x0436	,0x0432	,DKF_0	), // CYRILLIC SMALL LETTER VE
/*CYRILLIC           */	DEADTRANS(	0x03da	,0x0436	,0x0428	,DKF_0	), // CYRILLIC CAPITAL LETTER SHA
/*CYRILLIC           */	DEADTRANS(	0x0448	,0x0436	,0x0448	,DKF_0	), // CYRILLIC SMALL LETTER SHA
/*CYRILLIC           */	DEADTRANS(	0x2211	,0x0436	,0x0427	,DKF_0	), // CYRILLIC CAPITAL LETTER CHE
/*DESCENDER          */	DEADTRANS(	L'e'	,0x2c6a	,0x2c78	,DKF_0	), // LATIN SMALL LETTER E WITH NOTCH
/*DESCENDER          */	DEADTRANS(	L'H'	,0x2c6a	,0x2c67	,DKF_0	), // LATIN CAPITAL LETTER H WITH DESCENDER
/*DESCENDER          */	DEADTRANS(	L'h'	,0x2c6a	,0x2c68	,DKF_0	), // LATIN SMALL LETTER H WITH DESCENDER
/*DESCENDER          */	DEADTRANS(	L'K'	,0x2c6a	,0x2c69	,DKF_0	), // LATIN CAPITAL LETTER K WITH DESCENDER
/*DESCENDER          */	DEADTRANS(	L'k'	,0x2c6a	,0x2c6a	,DKF_0	), // LATIN SMALL LETTER K WITH DESCENDER
/*DESCENDER          */	DEADTRANS(	L'N'	,0x2c6a	,0xa790	,DKF_0	), // LATIN CAPITAL LETTER N WITH DESCENDER
/*DESCENDER          */	DEADTRANS(	L'n'	,0x2c6a	,0xa791	,DKF_0	), // LATIN SMALL LETTER N WITH DESCENDER
/*DESCENDER          */	DEADTRANS(	L'Z'	,0x2c6a	,0x2c6b	,DKF_0	), // LATIN CAPITAL LETTER Z WITH DESCENDER
/*DESCENDER          */	DEADTRANS(	L'z'	,0x2c6a	,0x2c6c	,DKF_0	), // LATIN SMALL LETTER Z WITH DESCENDER
/*DIAERESIS          */	DEADTRANS(	0x0020	,0x00eb	,0x0308	,DKF_0	), // COMBINING DIAERESIS
/*DIAERESIS          */	DEADTRANS(	0x00b0	,0x00eb	,0x1ab1	,DKF_0	), // COMBINING DIAERESIS-RING
/*DIAERESIS          */	DEADTRANS(	0x00a0	,0x00eb	,0x00a8	,DKF_0	), // DIAERESIS
/*DIAERESIS          */	DEADTRANS(	0x202f	,0x00eb	,0x00a8	,DKF_0	), // DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'A'	,0x00eb	,0x00c4	,DKF_0	), // LATIN CAPITAL LETTER A WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'a'	,0x00eb	,0x00e4	,DKF_0	), // LATIN SMALL LETTER A WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'B'	,0x00eb	,0x014a	,DKF_0	), // LATIN CAPITAL LETTER ENG
/*DIAERESIS          */	DEADTRANS(	L'b'	,0x00eb	,0x014b	,DKF_0	), // LATIN SMALL LETTER ENG
/*DIAERESIS          */	DEADTRANS(	L'C'	,0x00eb	,0x00b0	,DKF_0	), // DEGREE SIGN
/*DIAERESIS          */	DEADTRANS(	L'c'	,0x00eb	,0x00b0	,DKF_0	), // DEGREE SIGN
/*DIAERESIS          */	DEADTRANS(	L'D'	,0x00eb	,0x00d0	,DKF_0	), // LATIN CAPITAL LETTER ETH
/*DIAERESIS          */	DEADTRANS(	L'd'	,0x00eb	,0x00f0	,DKF_0	), // LATIN SMALL LETTER ETH
/*DIAERESIS          */	DEADTRANS(	L'E'	,0x00eb	,0x00cb	,DKF_0	), // LATIN CAPITAL LETTER E WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'e'	,0x00eb	,0x00eb	,DKF_0	), // LATIN SMALL LETTER E WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'F'	,0x00eb	,0x00a6	,DKF_0	), // BROKEN BAR
/*DIAERESIS          */	DEADTRANS(	L'f'	,0x00eb	,0x00a6	,DKF_0	), // BROKEN BAR
/*DIAERESIS          */	DEADTRANS(	L'G'	,0x00eb	,0x0194	,DKF_0	), // LATIN CAPITAL LETTER GAMMA
/*DIAERESIS          */	DEADTRANS(	L'g'	,0x00eb	,0x0263	,DKF_0	), // LATIN SMALL LETTER GAMMA
/*DIAERESIS          */	DEADTRANS(	L'H'	,0x00eb	,0x1e26	,DKF_0	), // LATIN CAPITAL LETTER H WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'h'	,0x00eb	,0x1e27	,DKF_0	), // LATIN SMALL LETTER H WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'I'	,0x00eb	,0x00cf	,DKF_0	), // LATIN CAPITAL LETTER I WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'i'	,0x00eb	,0x00ef	,DKF_0	), // LATIN SMALL LETTER I WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'J'	,0x00eb	,0x0196	,DKF_0	), // LATIN CAPITAL LETTER IOTA
/*DIAERESIS          */	DEADTRANS(	L'j'	,0x00eb	,0x0269	,DKF_0	), // LATIN SMALL LETTER IOTA
/*DIAERESIS          */	DEADTRANS(	L'l'	,0x00eb	,0x019b	,DKF_0	), // LATIN SMALL LETTER LAMBDA WITH STROKE
/*DIAERESIS          */	DEADTRANS(	L'O'	,0x00eb	,0x00d6	,DKF_0	), // LATIN CAPITAL LETTER O WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'o'	,0x00eb	,0x00f6	,DKF_0	), // LATIN SMALL LETTER O WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'Q'	,0x00eb	,0x2c6d	,DKF_0	), // LATIN CAPITAL LETTER ALPHA
/*DIAERESIS          */	DEADTRANS(	L'q'	,0x00eb	,0x0251	,DKF_0	), // LATIN SMALL LETTER ALPHA
/*DIAERESIS          */	DEADTRANS(	L'r'	,0x00eb	,0x027e	,DKF_0	), // LATIN SMALL LETTER R WITH FISHHOOK
/*DIAERESIS          */	DEADTRANS(	L'S'	,0x00eb	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*DIAERESIS          */	DEADTRANS(	L's'	,0x00eb	,0x00df	,DKF_0	), // LATIN SMALL LETTER SHARP S
/*DIAERESIS          */	DEADTRANS(	L'T'	,0x00eb	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*DIAERESIS          */	DEADTRANS(	0x2011	,0x00eb	,0x2010	,DKF_0	), // HYPHEN
/*DIAERESIS          */	DEADTRANS(	L't'	,0x00eb	,0x1e97	,DKF_0	), // LATIN SMALL LETTER T WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'U'	,0x00eb	,0x00dc	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'u'	,0x00eb	,0x00fc	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'W'	,0x00eb	,0x1e84	,DKF_0	), // LATIN CAPITAL LETTER W WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'w'	,0x00eb	,0x1e85	,DKF_0	), // LATIN SMALL LETTER W WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'X'	,0x00eb	,0x1e8c	,DKF_0	), // LATIN CAPITAL LETTER X WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'x'	,0x00eb	,0x1e8d	,DKF_0	), // LATIN SMALL LETTER X WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'Y'	,0x00eb	,0x0178	,DKF_0	), // LATIN CAPITAL LETTER Y WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'y'	,0x00eb	,0x00ff	,DKF_0	), // LATIN SMALL LETTER Y WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	L'Z'	,0x00eb	,0x2260	,DKF_0	), // NOT EQUAL TO
/*DIAERESIS          */	DEADTRANS(	L'z'	,0x00eb	,0x2260	,DKF_0	), // NOT EQUAL TO
/*DIAERESIS          */	DEADTRANS(	L'0'	,0x00eb	,0x2080	,DKF_0	), // SUBSCRIPT ZERO
/*DIAERESIS          */	DEADTRANS(	L'1'	,0x00eb	,0x2081	,DKF_0	), // SUBSCRIPT ONE
/*DIAERESIS          */	DEADTRANS(	L'2'	,0x00eb	,0x2082	,DKF_0	), // SUBSCRIPT TWO
/*DIAERESIS          */	DEADTRANS(	L'3'	,0x00eb	,0x2083	,DKF_0	), // SUBSCRIPT THREE
/*DIAERESIS          */	DEADTRANS(	L'4'	,0x00eb	,0x2084	,DKF_0	), // SUBSCRIPT FOUR
/*DIAERESIS          */	DEADTRANS(	L'5'	,0x00eb	,0x2085	,DKF_0	), // SUBSCRIPT FIVE
/*DIAERESIS          */	DEADTRANS(	L'6'	,0x00eb	,0x2086	,DKF_0	), // SUBSCRIPT SIX
/*DIAERESIS          */	DEADTRANS(	L'7'	,0x00eb	,0x2087	,DKF_0	), // SUBSCRIPT SEVEN
/*DIAERESIS          */	DEADTRANS(	L'8'	,0x00eb	,0x2088	,DKF_0	), // SUBSCRIPT EIGHT
/*DIAERESIS          */	DEADTRANS(	L'9'	,0x00eb	,0x2089	,DKF_0	), // SUBSCRIPT NINE
/*DIAERESIS          */	DEADTRANS(	0x0021	,0x00eb	,0x00a1	,DKF_0	), // INVERTED EXCLAMATION MARK
/*DIAERESIS          */	DEADTRANS(	0x0022	,0x00eb	,0x201e	,DKF_0	), // DOUBLE LOW-9 QUOTATION MARK
/*DIAERESIS          */	DEADTRANS(	0x0023	,0x00eb	,0x201e	,DKF_0	), // DOUBLE LOW-9 QUOTATION MARK
/*DIAERESIS          */	DEADTRANS(	0x0027	,0x00eb	,0x201a	,DKF_0	), // SINGLE LOW-9 QUOTATION MARK
/*DIAERESIS          */	DEADTRANS(	0x0028	,0x00eb	,0x208d	,DKF_0	), // SUBSCRIPT LEFT PARENTHESIS
/*DIAERESIS          */	DEADTRANS(	0x0029	,0x00eb	,0x208e	,DKF_0	), // SUBSCRIPT RIGHT PARENTHESIS
/*DIAERESIS          */	DEADTRANS(	0x002a	,0x00eb	,0x2051	,DKF_0	), // TWO ASTERISKS ALIGNED VERTICALLY
/*DIAERESIS          */	DEADTRANS(	0x002b	,0x00eb	,0x208a	,DKF_0	), // SUBSCRIPT PLUS SIGN
/*DIAERESIS          */	DEADTRANS(	0x002d	,0x00eb	,0x2e3a	,DKF_0	), // TWO-EM DASH
/*DIAERESIS          */	DEADTRANS(	0x002e	,0x00eb	,0x2026	,DKF_0	), // HORIZONTAL ELLIPSIS
/*DIAERESIS          */	DEADTRANS(	0x002f	,0x00eb	,0x2052	,DKF_0	), // COMMERCIAL MINUS SIGN
/*DIAERESIS          */	DEADTRANS(	0x003a	,0x00eb	,0x2026	,DKF_0	), // HORIZONTAL ELLIPSIS
/*DIAERESIS          */	DEADTRANS(	0x003e	,0x00eb	,0x01da	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND CARON
/*DIAERESIS          */	DEADTRANS(	0x003d	,0x00eb	,0x208c	,DKF_0	), // SUBSCRIPT EQUALS SIGN
/*DIAERESIS          */	DEADTRANS(	0x003f	,0x00eb	,0x00bf	,DKF_0	), // INVERTED QUESTION MARK
/*DIAERESIS          */	DEADTRANS(	0x0060	,0x00eb	,0x01dc	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE
/*DIAERESIS          */	DEADTRANS(	0x005f	,0x00eb	,0x022b	,CHAIN	), // LATIN SMALL LETTER O WITH DIAERESIS AND MACRON
/*DIAERESIS          */	DEADTRANS(	0x007c	,0x00eb	,0x00a6	,DKF_0	), // BROKEN BAR
/*DIAERESIS          */	DEADTRANS(	0x007e	,0x00eb	,0x1e4f	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND DIAERESIS
/*DIAERESIS          */	DEADTRANS(	0x0152	,0x00eb	,0x00d8	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE
/*DIAERESIS          */	DEADTRANS(	0x0153	,0x00eb	,0x00f8	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE
/*DIAERESIS          */	DEADTRANS(	0x00a9	,0x00eb	,0x00f6	,CHAIN	), // LATIN SMALL LETTER O WITH DIAERESIS
/*DIAERESIS          */	DEADTRANS(	0x0027	,0x00f6	,0x01d8	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
/*DIAERESIS          */	DEADTRANS(	0x00a7	,0x00eb	,0x204b	,DKF_0	), // REVERSED PILCROW SIGN
/*DIAERESIS          */	DEADTRANS(	0x00ab	,0x00eb	,0x2039	,DKF_0	), // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
/*DIAERESIS          */	DEADTRANS(	0x00b5	,0x00eb	,0x2282	,DKF_0	), // SUBSET OF
/*DIAERESIS          */	DEADTRANS(	0x00bb	,0x00eb	,0x203a	,DKF_0	), // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
/*DIAERESIS          */	DEADTRANS(	0x00c9	,0x00c0	,0x00c5	,DKF_0	), // LATIN CAPITAL LETTER A WITH RING ABOVE
/*DIAERESIS          */	DEADTRANS(	0x00c9	,0x00eb	,0x00c5	,DKF_0	), // LATIN CAPITAL LETTER A WITH RING ABOVE
/*DIAERESIS          */	DEADTRANS(	0x00e9	,0x00e0	,0x00e5	,DKF_0	), // LATIN SMALL LETTER A WITH RING ABOVE
/*DIAERESIS          */	DEADTRANS(	0x00e1	,0x00eb	,0x01d8	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
/*DIAERESIS          */	DEADTRANS(	0x00e9	,0x00eb	,0x00e5	,DKF_0	), // LATIN SMALL LETTER A WITH RING ABOVE
/*DIAERESIS          */	DEADTRANS(	0x00ea	,0x00eb	,0x1ecd	,CHAIN	), // LATIN SMALL LETTER O WITH DOT BELOW
/*DIAERESIS          */	DEADTRANS(	0x00eb	,0x00eb	,0x1e73	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS BELOW
/*DIAERESIS          */	DEADTRANS(	0x00f2	,0x00eb	,0x01dc	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE
/*DIAERESIS          */	DEADTRANS(	0x00f5	,0x00eb	,0x1e4f	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND DIAERESIS
/*DIAERESIS          */	DEADTRANS(	0x02bc	,0x00eb	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*DIAERESIS          */	DEADTRANS(	0x2019	,0x00eb	,0x201a	,DKF_0	), // SINGLE LOW-9 QUOTATION MARK
/*DIAERESIS          */	DEADTRANS(	0x2212	,0x00eb	,0x208b	,DKF_0	), // SUBSCRIPT MINUS
/*DIAERESIS          */	DEADTRANS(	0x2610	,0x00eb	,0x2611	,DKF_0	), // BALLOT BOX WITH CHECK
/*DIAERESIS          */	DEADTRANS(	0x021f	,0x00eb	,0x01da	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND CARON
/*DIAERESIS          */	DEADTRANS(	0x014d	,0x00eb	,0x022b	,CHAIN	), // LATIN SMALL LETTER O WITH DIAERESIS AND MACRON
/*DIAERESIS          */	DEADTRANS(	0x03c0	,0x00eb	,0x2283	,DKF_0	), // SUPERSET OF
/*DIAERESIS&ACUTE    */	DEADTRANS(	L'I'	,0x01d8	,0x1e2e	,DKF_0	), // LATIN CAPITAL LETTER I WITH DIAERESIS AND ACUTE
/*DIAERESIS&ACUTE    */	DEADTRANS(	L'i'	,0x01d8	,0x1e2f	,DKF_0	), // LATIN SMALL LETTER I WITH DIAERESIS AND ACUTE
/*DIAERESIS&ACUTE    */	DEADTRANS(	L'U'	,0x01d8	,0x01d7	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS AND ACUTE
/*DIAERESIS&ACUTE    */	DEADTRANS(	L'u'	,0x01d8	,0x01d8	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
/*DIAERESIS&GRAVE    */	DEADTRANS(	L'U'	,0x01dc	,0x01db	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS AND GRAVE
/*DIAERESIS&GRAVE    */	DEADTRANS(	L'u'	,0x01dc	,0x01dc	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE
/*DIAERESIS&HACEK    */	DEADTRANS(	L'U'	,0x01da	,0x01d9	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS AND CARON
/*DIAERESIS&HACEK    */	DEADTRANS(	L'u'	,0x01da	,0x01da	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS AND CARON
/*DIAERESIS&MACRON   */	DEADTRANS(	L'A'	,0x022b	,0x01de	,DKF_0	), // LATIN CAPITAL LETTER A WITH DIAERESIS AND MACRON
/*DIAERESIS&MACRON   */	DEADTRANS(	L'a'	,0x022b	,0x01df	,DKF_0	), // LATIN SMALL LETTER A WITH DIAERESIS AND MACRON
/*DIAERESIS&MACRON   */	DEADTRANS(	L'O'	,0x022b	,0x022a	,DKF_0	), // LATIN CAPITAL LETTER O WITH DIAERESIS AND MACRON
/*DIAERESIS&MACRON   */	DEADTRANS(	L'o'	,0x022b	,0x022b	,DKF_0	), // LATIN SMALL LETTER O WITH DIAERESIS AND MACRON
/*DIAERESIS&MACRON   */	DEADTRANS(	L'U'	,0x022b	,0x01d5	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS AND MACRON
/*DIAERESIS&MACRON   */	DEADTRANS(	L'u'	,0x022b	,0x01d6	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS AND MACRON
/*DIAERESIS_BELOW    */	DEADTRANS(	0x0020	,0x1e73	,0x0324	,DKF_0	), // COMBINING DIAERESIS BELOW
/*DIAERESIS_BELOW    */	DEADTRANS(	L'U'	,0x1e73	,0x1e72	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS BELOW
/*DIAERESIS_BELOW    */	DEADTRANS(	L'u'	,0x1e73	,0x1e73	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS BELOW
/*DOT_ABOVE          */	DEADTRANS(	0x0020	,0x1e57	,0x0307	,DKF_0	), // COMBINING DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x0028	,0x1e57	,0x0352	,DKF_0	), // COMBINING FERMATA
/*DOT_ABOVE          */	DEADTRANS(	0x0029	,0x1e57	,0x0310	,DKF_0	), // COMBINING CANDRABINDU
/*DOT_ABOVE          */	DEADTRANS(	0x00eb	,0x1e57	,0x1ab4	,DKF_0	), // COMBINING TRIPLE DOT
/*DOT_ABOVE          */	DEADTRANS(	0x00a0	,0x1e57	,0x02d9	,DKF_0	), // DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x202f	,0x1e57	,0x02d9	,DKF_0	), // DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'A'	,0x1e57	,0x0226	,DKF_0	), // LATIN CAPITAL LETTER A WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'a'	,0x1e57	,0x0227	,DKF_0	), // LATIN SMALL LETTER A WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'B'	,0x1e57	,0x1e02	,DKF_0	), // LATIN CAPITAL LETTER B WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'b'	,0x1e57	,0x1e03	,DKF_0	), // LATIN SMALL LETTER B WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'C'	,0x1e57	,0x010a	,DKF_0	), // LATIN CAPITAL LETTER C WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'c'	,0x1e57	,0x010b	,DKF_0	), // LATIN SMALL LETTER C WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'D'	,0x1e57	,0x1e0a	,DKF_0	), // LATIN CAPITAL LETTER D WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'd'	,0x1e57	,0x1e0b	,DKF_0	), // LATIN SMALL LETTER D WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'E'	,0x1e57	,0x0116	,DKF_0	), // LATIN CAPITAL LETTER E WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'e'	,0x1e57	,0x0117	,DKF_0	), // LATIN SMALL LETTER E WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'F'	,0x1e57	,0x1e1e	,DKF_0	), // LATIN CAPITAL LETTER F WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'f'	,0x1e57	,0x1e1f	,DKF_0	), // LATIN SMALL LETTER F WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'G'	,0x1e57	,0x0120	,DKF_0	), // LATIN CAPITAL LETTER G WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'g'	,0x1e57	,0x0121	,DKF_0	), // LATIN SMALL LETTER G WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'H'	,0x1e57	,0x1e22	,DKF_0	), // LATIN CAPITAL LETTER H WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'h'	,0x1e57	,0x1e23	,DKF_0	), // LATIN SMALL LETTER H WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'I'	,0x1e57	,0x0130	,DKF_0	), // LATIN CAPITAL LETTER I WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'i'	,0x1e57	,0x0131	,DKF_0	), // LATIN SMALL LETTER DOTLESS I
/*DOT_ABOVE          */	DEADTRANS(	L'j'	,0x1e57	,0x0237	,DKF_0	), // LATIN SMALL LETTER DOTLESS J
/*DOT_ABOVE          */	DEADTRANS(	L'L'	,0x1e57	,0x013f	,DKF_0	), // LATIN CAPITAL LETTER L WITH MIDDLE DOT
/*DOT_ABOVE          */	DEADTRANS(	L'l'	,0x1e57	,0x0140	,DKF_0	), // LATIN SMALL LETTER L WITH MIDDLE DOT
/*DOT_ABOVE          */	DEADTRANS(	L'M'	,0x1e57	,0x1e40	,DKF_0	), // LATIN CAPITAL LETTER M WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'm'	,0x1e57	,0x1e41	,DKF_0	), // LATIN SMALL LETTER M WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'N'	,0x1e57	,0x1e44	,DKF_0	), // LATIN CAPITAL LETTER N WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'n'	,0x1e57	,0x1e45	,DKF_0	), // LATIN SMALL LETTER N WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'O'	,0x1e57	,0x022e	,DKF_0	), // LATIN CAPITAL LETTER O WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'o'	,0x1e57	,0x022f	,DKF_0	), // LATIN SMALL LETTER O WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'P'	,0x1e57	,0x1e56	,DKF_0	), // LATIN CAPITAL LETTER P WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'p'	,0x1e57	,0x1e57	,DKF_0	), // LATIN SMALL LETTER P WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'R'	,0x1e57	,0x1e58	,DKF_0	), // LATIN CAPITAL LETTER R WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'r'	,0x1e57	,0x1e59	,DKF_0	), // LATIN SMALL LETTER R WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'S'	,0x1e57	,0x1e60	,DKF_0	), // LATIN CAPITAL LETTER S WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L's'	,0x1e57	,0x1e61	,DKF_0	), // LATIN SMALL LETTER S WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'T'	,0x1e57	,0x1e6a	,DKF_0	), // LATIN CAPITAL LETTER T WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L't'	,0x1e57	,0x1e6b	,DKF_0	), // LATIN SMALL LETTER T WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'W'	,0x1e57	,0x1e86	,DKF_0	), // LATIN CAPITAL LETTER W WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'w'	,0x1e57	,0x1e87	,DKF_0	), // LATIN SMALL LETTER W WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'X'	,0x1e57	,0x1e8a	,DKF_0	), // LATIN CAPITAL LETTER X WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'x'	,0x1e57	,0x1e8b	,DKF_0	), // LATIN SMALL LETTER X WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'Y'	,0x1e57	,0x1e8e	,DKF_0	), // LATIN CAPITAL LETTER Y WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'y'	,0x1e57	,0x1e8f	,DKF_0	), // LATIN SMALL LETTER Y WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'Z'	,0x1e57	,0x017b	,DKF_0	), // LATIN CAPITAL LETTER Z WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'z'	,0x1e57	,0x017c	,DKF_0	), // LATIN SMALL LETTER Z WITH DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	L'1'	,0x1e57	,0x2024	,DKF_0	), // ONE DOT LEADER
/*DOT_ABOVE          */	DEADTRANS(	L'2'	,0x1e57	,0x2025	,DKF_0	), // TWO DOT LEADER
/*DOT_ABOVE          */	DEADTRANS(	L'3'	,0x1e57	,0x2026	,DKF_0	), // HORIZONTAL ELLIPSIS
/*DOT_ABOVE          */	DEADTRANS(	0x0021	,0x1e57	,0x1e69	,CHAIN	), // LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x0025	,0x1e57	,0x2052	,DKF_0	), // COMMERCIAL MINUS SIGN
/*DOT_ABOVE          */	DEADTRANS(	0x0027	,0x1e57	,0x1e65	,CHAIN	), // LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x002e	,0x1e57	,0x2026	,DKF_0	), // HORIZONTAL ELLIPSIS
/*DOT_ABOVE          */	DEADTRANS(	0x002f	,0x1e57	,0x2052	,DKF_0	), // COMMERCIAL MINUS SIGN
/*DOT_ABOVE          */	DEADTRANS(	0x003a	,0x1e57	,0x2056	,DKF_0	), // THREE DOT PUNCTUATION
/*DOT_ABOVE          */	DEADTRANS(	0x003e	,0x1e57	,0x1e67	,CHAIN	), // LATIN SMALL LETTER S WITH CARON AND DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x005f	,0x1e57	,0x0231	,CHAIN	), // LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
/*DOT_ABOVE          */	DEADTRANS(	L'0'	,0x1e9b	,0xa70c	,DKF_0	), // MODIFIER LETTER EXTRA-LOW DOTTED TONE BAR
/*DOT_ABOVE          */	DEADTRANS(	L'1'	,0x1e9b	,0xa70b	,DKF_0	), // MODIFIER LETTER LOW DOTTED TONE BAR
/*DOT_ABOVE          */	DEADTRANS(	L'2'	,0x1e9b	,0xa70a	,DKF_0	), // MODIFIER LETTER MID DOTTED TONE BAR
/*DOT_ABOVE          */	DEADTRANS(	L'3'	,0x1e9b	,0xa709	,DKF_0	), // MODIFIER LETTER HIGH DOTTED TONE BAR
/*DOT_ABOVE          */	DEADTRANS(	L'4'	,0x1e9b	,0xa708	,DKF_0	), // MODIFIER LETTER EXTRA-HIGH DOTTED TONE BAR
/*DOT_ABOVE          */	DEADTRANS(	0x00e1	,0x1e57	,0x1e65	,CHAIN	), // LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x021f	,0x1e57	,0x1e67	,CHAIN	), // LATIN SMALL LETTER S WITH CARON AND DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x014d	,0x1e57	,0x0231	,CHAIN	), // LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
/*DOT_ABOVE          */	DEADTRANS(	0x1ee5	,0x1e57	,0x1e69	,CHAIN	), // LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE
/*DOT_ABOVE          */	DEADTRANS(	0x017f	,0x1e57	,0x1e9b	,CHAIN	), // LATIN SMALL LETTER LONG S WITH DOT ABOVE
/*DOT_ABOVE&DOT_BELOW*/	DEADTRANS(	L'S'	,0x1e69	,0x1e68	,DKF_0	), // LATIN CAPITAL LETTER S WITH DOT BELOW AND DOT ABOVE
/*DOT_ABOVE&DOT_BELOW*/	DEADTRANS(	L's'	,0x1e69	,0x1e69	,DKF_0	), // LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE
/*DOT_ABOVE&MACRON   */	DEADTRANS(	L'A'	,0x0231	,0x01e0	,DKF_0	), // LATIN CAPITAL LETTER A WITH DOT ABOVE AND MACRON
/*DOT_ABOVE&MACRON   */	DEADTRANS(	L'a'	,0x0231	,0x01e1	,DKF_0	), // LATIN SMALL LETTER A WITH DOT ABOVE AND MACRON
/*DOT_ABOVE&MACRON   */	DEADTRANS(	L'O'	,0x0231	,0x0230	,DKF_0	), // LATIN CAPITAL LETTER O WITH DOT ABOVE AND MACRON
/*DOT_ABOVE&MACRON   */	DEADTRANS(	L'o'	,0x0231	,0x0231	,DKF_0	), // LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
/*DOT_BELOW          */	DEADTRANS(	0x0020	,0x1e05	,0x0323	,DKF_0	), // COMBINING DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'A'	,0x1e05	,0x1ea0	,DKF_0	), // LATIN CAPITAL LETTER A WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'a'	,0x1e05	,0x1ea1	,DKF_0	), // LATIN SMALL LETTER A WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'B'	,0x1e05	,0x1e04	,DKF_0	), // LATIN CAPITAL LETTER B WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'b'	,0x1e05	,0x1e05	,DKF_0	), // LATIN SMALL LETTER B WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'D'	,0x1e05	,0x1e0c	,DKF_0	), // LATIN CAPITAL LETTER D WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'd'	,0x1e05	,0x1e0d	,DKF_0	), // LATIN SMALL LETTER D WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'E'	,0x1e05	,0x1eb8	,DKF_0	), // LATIN CAPITAL LETTER E WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'e'	,0x1e05	,0x1eb9	,DKF_0	), // LATIN SMALL LETTER E WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'H'	,0x1e05	,0x1e24	,DKF_0	), // LATIN CAPITAL LETTER H WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'h'	,0x1e05	,0x1e25	,DKF_0	), // LATIN SMALL LETTER H WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'I'	,0x1e05	,0x1eca	,DKF_0	), // LATIN CAPITAL LETTER I WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'i'	,0x1e05	,0x1ecb	,DKF_0	), // LATIN SMALL LETTER I WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'K'	,0x1e05	,0x1e32	,DKF_0	), // LATIN CAPITAL LETTER K WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'k'	,0x1e05	,0x1e33	,DKF_0	), // LATIN SMALL LETTER K WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'L'	,0x1e05	,0x1e36	,DKF_0	), // LATIN CAPITAL LETTER L WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'l'	,0x1e05	,0x1e37	,DKF_0	), // LATIN SMALL LETTER L WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'M'	,0x1e05	,0x1e42	,DKF_0	), // LATIN CAPITAL LETTER M WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'm'	,0x1e05	,0x1e43	,DKF_0	), // LATIN SMALL LETTER M WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'N'	,0x1e05	,0x1e46	,DKF_0	), // LATIN CAPITAL LETTER N WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'n'	,0x1e05	,0x1e47	,DKF_0	), // LATIN SMALL LETTER N WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'O'	,0x1e05	,0x1ecc	,DKF_0	), // LATIN CAPITAL LETTER O WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'o'	,0x1e05	,0x1ecd	,DKF_0	), // LATIN SMALL LETTER O WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'R'	,0x1e05	,0x1e5a	,DKF_0	), // LATIN CAPITAL LETTER R WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'r'	,0x1e05	,0x1e5b	,DKF_0	), // LATIN SMALL LETTER R WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'S'	,0x1e05	,0x1e62	,DKF_0	), // LATIN CAPITAL LETTER S WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L's'	,0x1e05	,0x1e63	,DKF_0	), // LATIN SMALL LETTER S WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'T'	,0x1e05	,0x1e6c	,DKF_0	), // LATIN CAPITAL LETTER T WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L't'	,0x1e05	,0x1e6d	,DKF_0	), // LATIN SMALL LETTER T WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'U'	,0x1e05	,0x1ee4	,DKF_0	), // LATIN CAPITAL LETTER U WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'u'	,0x1e05	,0x1ee5	,DKF_0	), // LATIN SMALL LETTER U WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'V'	,0x1e05	,0x1e7e	,DKF_0	), // LATIN CAPITAL LETTER V WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'v'	,0x1e05	,0x1e7f	,DKF_0	), // LATIN SMALL LETTER V WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'W'	,0x1e05	,0x1e88	,DKF_0	), // LATIN CAPITAL LETTER W WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'w'	,0x1e05	,0x1e89	,DKF_0	), // LATIN SMALL LETTER W WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'Y'	,0x1e05	,0x1ef4	,DKF_0	), // LATIN CAPITAL LETTER Y WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'y'	,0x1e05	,0x1ef5	,DKF_0	), // LATIN SMALL LETTER Y WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'Z'	,0x1e05	,0x1e92	,DKF_0	), // LATIN CAPITAL LETTER Z WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	L'z'	,0x1e05	,0x1e93	,DKF_0	), // LATIN SMALL LETTER Z WITH DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x0021	,0x1e05	,0x203c	,DKF_0	), // DOUBLE EXCLAMATION MARK
/*DOT_BELOW          */	DEADTRANS(	0x0029	,0x1e05	,0x1eb7	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x002b	,0x1e05	,0x203d	,DKF_0	), // INTERROBANG
/*DOT_BELOW          */	DEADTRANS(	0x002c	,0x1e05	,0x1ee3	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x002e	,0x1e05	,0x1e69	,CHAIN	), // LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE
/*DOT_BELOW          */	DEADTRANS(	0x003f	,0x1e69	,0x203d	,DKF_0	), // INTERROBANG
/*DOT_BELOW          */	DEADTRANS(	0x003a	,0x1e05	,0x205d	,DKF_0	), // TRICOLON
/*DOT_BELOW          */	DEADTRANS(	0x003f	,0x1e05	,0x2049	,DKF_0	), // EXCLAMATION QUESTION MARK
/*DOT_BELOW          */	DEADTRANS(	0x005e	,0x1e05	,0x1ed9	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x005f	,0x1e05	,0x1e5d	,CHAIN	), // LATIN SMALL LETTER R WITH DOT BELOW AND MACRON
/*DOT_BELOW          */	DEADTRANS(	0x00ea	,0x1e05	,0x1ed9	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x0229	,0x1e05	,0x1ee3	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x022f	,0x1e05	,0x1e69	,CHAIN	), // LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE
/*DOT_BELOW          */	DEADTRANS(	0x014f	,0x1e05	,0x1eb7	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x014d	,0x1e05	,0x1e5d	,CHAIN	), // LATIN SMALL LETTER R WITH DOT BELOW AND MACRON
/*DOT_BELOW          */	DEADTRANS(	0x01a1	,0x1e05	,0x1ee3	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND DOT BELOW
/*DOT_BELOW          */	DEADTRANS(	0x002d	,0x1e05	,0xa719	,DKF_0	), // MODIFIER LETTER DOT HORIZONTAL BAR
/*DOT_BELOW          */	DEADTRANS(	0x002f	,0x1e05	,0xa718	,DKF_0	), // MODIFIER LETTER DOT SLASH
/*DOT_BELOW          */	DEADTRANS(	0x007c	,0x1e05	,0xa717	,DKF_0	), // MODIFIER LETTER DOT VERTICAL BAR
/*DOT_BELOW&MACRON   */	DEADTRANS(	L'L'	,0x1e5d	,0x1e38	,DKF_0	), // LATIN CAPITAL LETTER L WITH DOT BELOW AND MACRON
/*DOT_BELOW&MACRON   */	DEADTRANS(	L'l'	,0x1e5d	,0x1e39	,DKF_0	), // LATIN SMALL LETTER L WITH DOT BELOW AND MACRON
/*DOT_BELOW&MACRON   */	DEADTRANS(	L'R'	,0x1e5d	,0x1e5c	,DKF_0	), // LATIN CAPITAL LETTER R WITH DOT BELOW AND MACRON
/*DOT_BELOW&MACRON   */	DEADTRANS(	L'r'	,0x1e5d	,0x1e5d	,DKF_0	), // LATIN SMALL LETTER R WITH DOT BELOW AND MACRON
/*DOUBLE             */	DEADTRANS(	0x0020	,0x003d	,0x030b	,DKF_0	), // COMBINING DOUBLE ACUTE ACCENT
/*DOUBLE             */	DEADTRANS(	0x202f	,0x003d	,0xa78a	,DKF_0	), // MODIFIER LETTER SHORT EQUALS SIGN
/*DOUBLE             */	DEADTRANS(	L'L'	,0x003d	,0x2c60	,DKF_0	), // LATIN CAPITAL LETTER L WITH DOUBLE BAR
/*DOUBLE             */	DEADTRANS(	L'l'	,0x003d	,0x2c61	,DKF_0	), // LATIN SMALL LETTER L WITH DOUBLE BAR
/*DOUBLE             */	DEADTRANS(	L'O'	,0x003d	,0x0150	,DKF_0	), // LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
/*DOUBLE             */	DEADTRANS(	L'o'	,0x003d	,0x0151	,DKF_0	), // LATIN SMALL LETTER O WITH DOUBLE ACUTE
/*DOUBLE             */	DEADTRANS(	L'U'	,0x003d	,0x0170	,DKF_0	), // LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
/*DOUBLE             */	DEADTRANS(	L'u'	,0x003d	,0x0171	,DKF_0	), // LATIN SMALL LETTER U WITH DOUBLE ACUTE
/*DOUBLE             */	DEADTRANS(	L'0'	,0x003d	,0x21d5	,DKF_0	), // UP DOWN DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'1'	,0x003d	,0x21d9	,DKF_0	), // SOUTH WEST DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'2'	,0x003d	,0x21d3	,DKF_0	), // DOWNWARDS DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'3'	,0x003d	,0x21d8	,DKF_0	), // SOUTH EAST DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'4'	,0x003d	,0x21d0	,DKF_0	), // LEFTWARDS DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'5'	,0x003d	,0x21d4	,DKF_0	), // LEFT RIGHT DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'6'	,0x003d	,0x21d2	,DKF_0	), // RIGHTWARDS DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'7'	,0x003d	,0x21d6	,DKF_0	), // NORTH WEST DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'8'	,0x003d	,0x21d1	,DKF_0	), // UPWARDS DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	L'9'	,0x003d	,0x21d7	,DKF_0	), // NORTH EAST DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	0x0021	,0x003d	,0x203c	,CHAIN	), // DOUBLE EXCLAMATION MARK
/*DOUBLE             */	DEADTRANS(	0x0025	,0x003d	,0x2031	,DKF_0	), // PER TEN THOUSAND SIGN
/*DOUBLE             */	DEADTRANS(	0x0027	,0x003d	,0x0151	,CHAIN	), // LATIN SMALL LETTER O WITH DOUBLE ACUTE
/*DOUBLE             */	DEADTRANS(	0x002d	,0x003d	,0x2261	,DKF_0	), // IDENTICAL TO
/*DOUBLE             */	DEADTRANS(	0x002f	,0x003d	,0x2288	,CHAIN	), // NEITHER A SUBSET OF NOR EQUAL TO
/*DOUBLE             */	DEADTRANS(	L'i'	,0x2288	,0x2288	,DKF_0	), // NEITHER A SUBSET OF NOR EQUAL TO
/*DOUBLE             */	DEADTRANS(	L'n'	,0x2288	,0x2289	,DKF_0	), // NEITHER A SUPERSET OF NOR EQUAL TO
/*DOUBLE             */	DEADTRANS(	0x002d	,0x2288	,0x2262	,DKF_0	), // NOT IDENTICAL TO
/*DOUBLE             */	DEADTRANS(	0x003c	,0x003d	,0x21d0	,DKF_0	), // LEFTWARDS DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	0x003d	,0x003d	,0x2263	,DKF_0	), // STRICTLY EQUIVALENT TO
/*DOUBLE             */	DEADTRANS(	0x003e	,0x003d	,0x21d2	,DKF_0	), // RIGHTWARDS DOUBLE ARROW
/*DOUBLE             */	DEADTRANS(	0x003f	,0x003d	,0x2047	,DKF_0	), // DOUBLE QUESTION MARK
/*DOUBLE             */	DEADTRANS(	0x005f	,0x003d	,0x2017	,DKF_0	), // DOUBLE LOW LINE
/*DOUBLE             */	DEADTRANS(	0x0060	,0x003d	,0x020d	,CHAIN	), // LATIN SMALL LETTER O WITH DOUBLE GRAVE
/*DOUBLE             */	DEADTRANS(	0x007c	,0x0151	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x0020	,0x0151	,0x030b	,DKF_0	), // COMBINING DOUBLE ACUTE ACCENT
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x00a0	,0x0151	,0x02dd	,DKF_0	), // DOUBLE ACUTE ACCENT
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x202f	,0x0151	,0x02dd	,DKF_0	), // DOUBLE ACUTE ACCENT
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'A'	,0x0151	,0x00c3	,DKF_0	), // LATIN CAPITAL LETTER A WITH TILDE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'a'	,0x0151	,0x00e3	,DKF_0	), // LATIN SMALL LETTER A WITH TILDE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'E'	,0x0151	,0x018e	,DKF_0	), // LATIN CAPITAL LETTER REVERSED E
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'e'	,0x0151	,0x01dd	,DKF_0	), // LATIN SMALL LETTER TURNED E
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'i'	,0x0151	,0x2286	,DKF_0	), // SUBSET OF OR EQUAL TO
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'N'	,0x0151	,0x00d1	,DKF_0	), // LATIN CAPITAL LETTER N WITH TILDE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'n'	,0x0151	,0x00f1	,DKF_0	), // LATIN SMALL LETTER N WITH TILDE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'O'	,0x0151	,0x0150	,DKF_0	), // LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'o'	,0x0151	,0x0151	,DKF_0	), // LATIN SMALL LETTER O WITH DOUBLE ACUTE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L't'	,0x0151	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'U'	,0x0151	,0x0170	,DKF_0	), // LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'u'	,0x0151	,0x0171	,DKF_0	), // LATIN SMALL LETTER U WITH DOUBLE ACUTE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'0'	,0x0151	,0x2195	,DKF_0	), // UP DOWN ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'1'	,0x0151	,0x2199	,DKF_0	), // SOUTH WEST ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'2'	,0x0151	,0x2193	,DKF_0	), // DOWNWARDS ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'3'	,0x0151	,0x2198	,DKF_0	), // SOUTH EAST ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'4'	,0x0151	,0x2190	,DKF_0	), // LEFTWARDS ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'5'	,0x0151	,0x2194	,DKF_0	), // LEFT RIGHT ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'6'	,0x0151	,0x2192	,DKF_0	), // RIGHTWARDS ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'7'	,0x0151	,0x2196	,DKF_0	), // NORTH WEST ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'8'	,0x0151	,0x2191	,DKF_0	), // UPWARDS ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	L'9'	,0x0151	,0x2197	,DKF_0	), // NORTH EAST ARROW
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x0022	,0x0151	,0x02ee	,DKF_0	), // MODIFIER LETTER DOUBLE APOSTROPHE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x0023	,0x0151	,0x02ee	,DKF_0	), // MODIFIER LETTER DOUBLE APOSTROPHE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x0027	,0x0151	,0x02bc	,DKF_0	), // MODIFIER LETTER APOSTROPHE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x002b	,0x0151	,0x02f6	,DKF_0	), // MODIFIER LETTER MIDDLE DOUBLE ACUTE ACCENT
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x003d	,0x0151	,0x02ba	,DKF_0	), // MODIFIER LETTER DOUBLE PRIME
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x0152	,0x0151	,0x01fe	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE AND ACUTE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x0153	,0x0151	,0x01ff	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE AND ACUTE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x00ea	,0x0151	,0x1ab0	,DKF_0	), // COMBINING DOUBLED CIRCUMFLEX ACCENT
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x2019	,0x0151	,0x02bc	,DKF_0	), // MODIFIER LETTER APOSTROPHE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x2610	,0x0151	,0x2750	,DKF_0	), // UPPER RIGHT DROP-SHADOWED WHITE SQUARE
/*DOUBLE_ACUTE_ACCENT*/	DEADTRANS(	0x222a	,0x0151	,0x2284	,DKF_0	), // NOT A SUBSET OF
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x0020	,0x020d	,0x030f	,DKF_0	), // COMBINING DOUBLE GRAVE ACCENT
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x00a0	,0x020d	,0x02f5	,DKF_0	), // MODIFIER LETTER MIDDLE DOUBLE GRAVE ACCENT
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x00c0	,0x020d	,0x02f5	,DKF_0	), // MODIFIER LETTER MIDDLE DOUBLE GRAVE ACCENT
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x00e0	,0x020d	,0x02f5	,DKF_0	), // MODIFIER LETTER MIDDLE DOUBLE GRAVE ACCENT
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x202f	,0x020d	,0x02f5	,DKF_0	), // MODIFIER LETTER MIDDLE DOUBLE GRAVE ACCENT
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'A'	,0x020d	,0x0200	,DKF_0	), // LATIN CAPITAL LETTER A WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'a'	,0x020d	,0x0201	,DKF_0	), // LATIN SMALL LETTER A WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'E'	,0x020d	,0x0204	,DKF_0	), // LATIN CAPITAL LETTER E WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'e'	,0x020d	,0x0205	,DKF_0	), // LATIN SMALL LETTER E WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'I'	,0x020d	,0x0208	,DKF_0	), // LATIN CAPITAL LETTER I WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'i'	,0x020d	,0x0209	,DKF_0	), // LATIN SMALL LETTER I WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'N'	,0x020d	,0x1daf	,DKF_0	), // MODIFIER LETTER SMALL N WITH RETROFLEX HOOK
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'n'	,0x020d	,0x0273	,DKF_0	), // LATIN SMALL LETTER N WITH RETROFLEX HOOK
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'O'	,0x020d	,0x020c	,DKF_0	), // LATIN CAPITAL LETTER O WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'o'	,0x020d	,0x020d	,DKF_0	), // LATIN SMALL LETTER O WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'R'	,0x020d	,0x0210	,DKF_0	), // LATIN CAPITAL LETTER R WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'r'	,0x020d	,0x0211	,DKF_0	), // LATIN SMALL LETTER R WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'U'	,0x020d	,0x0214	,DKF_0	), // LATIN CAPITAL LETTER U WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'u'	,0x020d	,0x0215	,DKF_0	), // LATIN SMALL LETTER U WITH DOUBLE GRAVE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'W'	,0x020d	,0x2c72	,DKF_0	), // LATIN CAPITAL LETTER W WITH HOOK
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'w'	,0x020d	,0x2c73	,DKF_0	), // LATIN SMALL LETTER W WITH HOOK
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'Y'	,0x020d	,0x01b3	,DKF_0	), // LATIN CAPITAL LETTER Y WITH HOOK
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'y'	,0x020d	,0x01b4	,DKF_0	), // LATIN SMALL LETTER Y WITH HOOK
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'0'	,0x020d	,0x21d5	,DKF_0	), // UP DOWN DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'1'	,0x020d	,0x21d9	,DKF_0	), // SOUTH WEST DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'2'	,0x020d	,0x21d3	,DKF_0	), // DOWNWARDS DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'3'	,0x020d	,0x21d8	,DKF_0	), // SOUTH EAST DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'4'	,0x020d	,0x21d0	,DKF_0	), // LEFTWARDS DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'5'	,0x020d	,0x21d4	,DKF_0	), // LEFT RIGHT DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'6'	,0x020d	,0x21d2	,DKF_0	), // RIGHTWARDS DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'7'	,0x020d	,0x21d6	,DKF_0	), // NORTH WEST DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'8'	,0x020d	,0x21d1	,DKF_0	), // UPWARDS DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	L'9'	,0x020d	,0x21d7	,DKF_0	), // NORTH EAST DOUBLE ARROW
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x0027	,0x020d	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x0152	,0x020d	,0x00d8	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x0153	,0x020d	,0x00f8	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x00f9	,0x020d	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x2019	,0x020d	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x2610	,0x020d	,0x274f	,DKF_0	), // LOWER RIGHT DROP-SHADOWED WHITE SQUARE
/*DOUBLE_GRAVE_ACCENT*/	DEADTRANS(	0x222a	,0x020d	,0x2285	,DKF_0	), // NOT A SUPERSET OF
/*DOUBLE_MIDDLE_TILDE*/	DEADTRANS(	L'l'	,0xab38	,0xab38	,DKF_0	), // LATIN SMALL LETTER L WITH DOUBLE MIDDLE TILDE
/*DOUBLE_TILDE       */	DEADTRANS(	L'l'	,0x00d5	,0xab38	,DKF_0	), // LATIN SMALL LETTER L WITH DOUBLE MIDDLE TILDE
/*DOUBLE_TILDE       */	DEADTRANS(	0x003d	,0x00d5	,0x2243	,DKF_0	), // ASYMPTOTICALLY EQUAL TO
/*G_DASIA            */	DEADTRANS(	0x00a0	,0x1f51	,0x1ffe	,DKF_0	), // GREEK DASIA
/*G_DASIA            */	DEADTRANS(	0x202f	,0x1f51	,0x1ffe	,DKF_0	), // GREEK DASIA
/*G_DASIA            */	DEADTRANS(	L'A'	,0x1f51	,0x1f09	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'a'	,0x1f51	,0x1f01	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'E'	,0x1f51	,0x1f19	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'e'	,0x1f51	,0x1f11	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'H'	,0x1f51	,0x1f29	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'h'	,0x1f51	,0x1f21	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'I'	,0x1f51	,0x1f39	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'i'	,0x1f51	,0x1f31	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'O'	,0x1f51	,0x1f49	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'o'	,0x1f51	,0x1f41	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'R'	,0x1f51	,0x1fec	,DKF_0	), // GREEK CAPITAL LETTER RHO WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'r'	,0x1f51	,0x1fe5	,DKF_0	), // GREEK SMALL LETTER RHO WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'V'	,0x1f51	,0x1f69	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'v'	,0x1f51	,0x1f61	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'W'	,0x1f51	,0x1f69	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'w'	,0x1f51	,0x1f61	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'Y'	,0x1f51	,0x1f59	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	L'y'	,0x1f51	,0x1f51	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x1f70	,0x1f51	,0x1f53	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND VARIA
/*G_DASIA            */	DEADTRANS(	0x1f7d	,0x1f51	,0x1f55	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND OXIA
/*G_DASIA            */	DEADTRANS(	0x1fc3	,0x1f51	,0x1fa1	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA            */	DEADTRANS(	0x1fc6	,0x1f51	,0x1f57	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_DASIA            */	DEADTRANS(	0x002c	,0x1f51	,0x1f55	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND OXIA
/*G_DASIA            */	DEADTRANS(	0x003b	,0x1f51	,0x1fa1	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA            */	DEADTRANS(	0x0060	,0x1f51	,0x1f53	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND VARIA
/*G_DASIA            */	DEADTRANS(	0x007e	,0x1f51	,0x1f57	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_DASIA            */	DEADTRANS(	0x0391	,0x1f51	,0x1f09	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03b1	,0x1f51	,0x1f01	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x0395	,0x1f51	,0x1f19	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03b5	,0x1f51	,0x1f11	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x0397	,0x1f51	,0x1f29	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03b7	,0x1f51	,0x1f21	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x0399	,0x1f51	,0x1f39	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03b9	,0x1f51	,0x1f31	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x039f	,0x1f51	,0x1f49	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03bf	,0x1f51	,0x1f41	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03a1	,0x1f51	,0x1fec	,DKF_0	), // GREEK CAPITAL LETTER RHO WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03c1	,0x1f51	,0x1fe5	,DKF_0	), // GREEK SMALL LETTER RHO WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03a5	,0x1f51	,0x1f59	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03c5	,0x1f51	,0x1f51	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03a9	,0x1f51	,0x1f69	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA
/*G_DASIA            */	DEADTRANS(	0x03c9	,0x1f51	,0x1f61	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA
/*G_DASIA&I          */	DEADTRANS(	L'A'	,0x1fa1	,0x1f89	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PROSGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	L'a'	,0x1fa1	,0x1f81	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	L'H'	,0x1fa1	,0x1f99	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND PROSGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	L'h'	,0x1fa1	,0x1f91	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	L'V'	,0x1fa1	,0x1fa9	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PROSGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	L'v'	,0x1fa1	,0x1fa1	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	L'W'	,0x1fa1	,0x1fa9	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PROSGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	L'w'	,0x1fa1	,0x1fa1	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x1f70	,0x1fa1	,0x1f93	,CHAIN	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x1f7d	,0x1fa1	,0x1fa5	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x002c	,0x1fa1	,0x1fa5	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x0060	,0x1fa1	,0x1f93	,CHAIN	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x0391	,0x1fa1	,0x1f89	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PROSGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x03b1	,0x1fa1	,0x1f81	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x0397	,0x1fa1	,0x1f99	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND PROSGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x03b7	,0x1fa1	,0x1f91	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x03a9	,0x1fa1	,0x1fa9	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PROSGEGRAMMENI
/*G_DASIA&I          */	DEADTRANS(	0x03c9	,0x1fa1	,0x1fa1	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA       */	DEADTRANS(	0x00a0	,0x1f55	,0x1fde	,DKF_0	), // GREEK DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'A'	,0x1f55	,0x1f0d	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'a'	,0x1f55	,0x1f05	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'E'	,0x1f55	,0x1f1d	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'e'	,0x1f55	,0x1f15	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'H'	,0x1f55	,0x1f2d	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'h'	,0x1f55	,0x1f25	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'I'	,0x1f55	,0x1f3d	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'i'	,0x1f55	,0x1f35	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'O'	,0x1f55	,0x1f4d	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'o'	,0x1f55	,0x1f45	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'V'	,0x1f55	,0x1f6d	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'v'	,0x1f55	,0x1f65	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'W'	,0x1f55	,0x1f6d	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'w'	,0x1f55	,0x1f65	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'Y'	,0x1f55	,0x1f5d	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	L'y'	,0x1f55	,0x1f55	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x1fc3	,0x1f55	,0x1fa5	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA       */	DEADTRANS(	0x003b	,0x1f55	,0x1fa5	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA       */	DEADTRANS(	0x0391	,0x1f55	,0x1f0d	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03b1	,0x1f55	,0x1f05	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x0395	,0x1f55	,0x1f1d	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03b5	,0x1f55	,0x1f15	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x0397	,0x1f55	,0x1f2d	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03b7	,0x1f55	,0x1f25	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x0399	,0x1f55	,0x1f3d	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03b9	,0x1f55	,0x1f35	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x039f	,0x1f55	,0x1f4d	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03bf	,0x1f55	,0x1f45	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03a5	,0x1f55	,0x1f5d	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03c5	,0x1f55	,0x1f55	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03a9	,0x1f55	,0x1f6d	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA
/*G_DASIA&OXIA       */	DEADTRANS(	0x03c9	,0x1f55	,0x1f65	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA
/*G_DASIA&OXIA&I     */	DEADTRANS(	0x0391	,0x1fa5	,0x1f8d	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND OXIA AND PROSGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	0x0397	,0x1fa5	,0x1f9d	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND OXIA AND PROSGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	0x03a9	,0x1fa5	,0x1fad	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA AND PROSGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	0x03b1	,0x1fa5	,0x1f85	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	0x03b7	,0x1fa5	,0x1f95	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	0x03c9	,0x1fa5	,0x1fa5	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'A'	,0x1fa5	,0x1f8d	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND OXIA AND PROSGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'H'	,0x1fa5	,0x1f9d	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND OXIA AND PROSGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'V'	,0x1fa5	,0x1fad	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA AND PROSGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'W'	,0x1fa5	,0x1fad	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND OXIA AND PROSGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'a'	,0x1fa5	,0x1f85	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'h'	,0x1fa5	,0x1f95	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'v'	,0x1fa5	,0x1fa5	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&OXIA&I     */	DEADTRANS(	L'w'	,0x1fa5	,0x1fa5	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x00a0	,0x1f57	,0x1fdf	,DKF_0	), // GREEK DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x202f	,0x1f57	,0x1fdf	,DKF_0	), // GREEK DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'A'	,0x1f57	,0x1f0f	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'a'	,0x1f57	,0x1f07	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'H'	,0x1f57	,0x1f2f	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'h'	,0x1f57	,0x1f27	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'I'	,0x1f57	,0x1f3f	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'i'	,0x1f57	,0x1f37	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'V'	,0x1f57	,0x1f6f	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'v'	,0x1f57	,0x1f67	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'W'	,0x1f57	,0x1f6f	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'w'	,0x1f57	,0x1f67	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'Y'	,0x1f57	,0x1f5f	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	L'y'	,0x1f57	,0x1f57	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x1fc3	,0x1f57	,0x1f87	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x003b	,0x1f57	,0x1f87	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x0391	,0x1f57	,0x1f0f	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x03b1	,0x1f57	,0x1f07	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x0397	,0x1f57	,0x1f2f	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x03b7	,0x1f57	,0x1f27	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x0399	,0x1f57	,0x1f3f	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x03b9	,0x1f57	,0x1f37	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x03a5	,0x1f57	,0x1f5f	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x03c5	,0x1f57	,0x1f57	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x03a9	,0x1f57	,0x1f6f	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI       */	DEADTRANS(	0x03c9	,0x1f57	,0x1f67	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'A'	,0x1f87	,0x1f8f	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'H'	,0x1f87	,0x1f9f	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'V'	,0x1f87	,0x1faf	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'W'	,0x1f87	,0x1faf	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'a'	,0x1f87	,0x1f87	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'h'	,0x1f87	,0x1f97	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'v'	,0x1f87	,0x1fa7	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	L'w'	,0x1f87	,0x1fa7	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	0x0391	,0x1f87	,0x1f8f	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	0x03b1	,0x1f87	,0x1f87	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	0x0397	,0x1f87	,0x1f9f	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	0x03b7	,0x1f87	,0x1f97	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	0x03a9	,0x1f87	,0x1faf	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND PERISPOMENI AND PROSGEGRAMMENI
/*G_DASIA&PERI&I     */	DEADTRANS(	0x03c9	,0x1f87	,0x1fa7	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND PERISPOMENI AND YPOGEGRAMMENI
/*G_DASIA&VARIA      */	DEADTRANS(	0x00a0	,0x1f53	,0x1fdd	,DKF_0	), // GREEK DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'A'	,0x1f53	,0x1f0b	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'a'	,0x1f53	,0x1f03	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'E'	,0x1f53	,0x1f1b	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'e'	,0x1f53	,0x1f13	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'H'	,0x1f53	,0x1f2b	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'h'	,0x1f53	,0x1f23	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'I'	,0x1f53	,0x1f3b	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'i'	,0x1f53	,0x1f33	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'O'	,0x1f53	,0x1f4b	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'o'	,0x1f53	,0x1f43	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'V'	,0x1f53	,0x1f6b	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'v'	,0x1f53	,0x1f63	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'W'	,0x1f53	,0x1f6b	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'w'	,0x1f53	,0x1f63	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'Y'	,0x1f53	,0x1f5b	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	L'y'	,0x1f53	,0x1f53	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x1fc3	,0x1f53	,0x1f93	,CHAIN	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA      */	DEADTRANS(	0x003b	,0x1f53	,0x1f93	,CHAIN	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA      */	DEADTRANS(	0x0391	,0x1f53	,0x1f0b	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03b1	,0x1f53	,0x1f03	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x0395	,0x1f53	,0x1f1b	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03b5	,0x1f53	,0x1f13	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x0397	,0x1f53	,0x1f2b	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03b7	,0x1f53	,0x1f23	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x0399	,0x1f53	,0x1f3b	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03b9	,0x1f53	,0x1f33	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x039f	,0x1f53	,0x1f4b	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03bf	,0x1f53	,0x1f43	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03a5	,0x1f53	,0x1f5b	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03c5	,0x1f53	,0x1f53	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03a9	,0x1f53	,0x1f6b	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA
/*G_DASIA&VARIA      */	DEADTRANS(	0x03c9	,0x1f53	,0x1f63	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'A'	,0x1f93	,0x1f8b	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND VARIA AND PROSGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'H'	,0x1f93	,0x1f9b	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND VARIA AND PROSGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'V'	,0x1f93	,0x1fab	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA AND PROSGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'W'	,0x1f93	,0x1fab	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA AND PROSGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'a'	,0x1f93	,0x1f83	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'h'	,0x1f93	,0x1f93	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'v'	,0x1f93	,0x1fa3	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	L'w'	,0x1f93	,0x1fa3	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	0x0391	,0x1f93	,0x1f8b	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH DASIA AND VARIA AND PROSGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	0x03b1	,0x1f93	,0x1f83	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	0x0397	,0x1f93	,0x1f9b	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH DASIA AND VARIA AND PROSGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	0x03b7	,0x1f93	,0x1f93	,DKF_0	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	0x03a9	,0x1f93	,0x1fab	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH DASIA AND VARIA AND PROSGEGRAMMENI
/*G_DASIA&VARIA&I    */	DEADTRANS(	0x03c9	,0x1f93	,0x1fa3	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_DIALYTIKA        */	DEADTRANS(	0x0020	,0x03ca	,0x0308	,DKF_0	), // COMBINING DIAERESIS
/*G_DIALYTIKA        */	DEADTRANS(	0x00a0	,0x03ca	,0x00a8	,DKF_0	), // DIAERESIS
/*G_DIALYTIKA        */	DEADTRANS(	0x202f	,0x03ca	,0x00a8	,DKF_0	), // DIAERESIS
/*G_DIALYTIKA        */	DEADTRANS(	L'I'	,0x03ca	,0x03aa	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DIALYTIKA
/*G_DIALYTIKA        */	DEADTRANS(	L'i'	,0x03ca	,0x03ca	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA
/*G_DIALYTIKA        */	DEADTRANS(	L'Y'	,0x03ca	,0x03ab	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA
/*G_DIALYTIKA        */	DEADTRANS(	L'y'	,0x03ca	,0x03cb	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA
/*G_DIALYTIKA        */	DEADTRANS(	0x03cc	,0x03ca	,0x0390	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
/*G_DIALYTIKA        */	DEADTRANS(	0x1f70	,0x03ca	,0x1fe2	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND VARIA
/*G_DIALYTIKA        */	DEADTRANS(	0x1f7d	,0x03ca	,0x1fe3	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND OXIA
/*G_DIALYTIKA        */	DEADTRANS(	0x1fc6	,0x03ca	,0x1fe7	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND PERISPOMENI
/*G_DIALYTIKA        */	DEADTRANS(	0x002c	,0x03ca	,0x1fe3	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND OXIA
/*G_DIALYTIKA        */	DEADTRANS(	0x0027	,0x03ca	,0x0390	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
/*G_DIALYTIKA        */	DEADTRANS(	0x0060	,0x03ca	,0x1fe2	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND VARIA
/*G_DIALYTIKA        */	DEADTRANS(	0x007e	,0x03ca	,0x1fe7	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND PERISPOMENI
/*G_DIALYTIKA        */	DEADTRANS(	0x0399	,0x03ca	,0x03aa	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH DIALYTIKA
/*G_DIALYTIKA        */	DEADTRANS(	0x03b9	,0x03ca	,0x03ca	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA
/*G_DIALYTIKA        */	DEADTRANS(	0x03a5	,0x03ca	,0x03ab	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA
/*G_DIALYTIKA        */	DEADTRANS(	0x03c5	,0x03ca	,0x03cb	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA
/*G_DIALYTIKA&OXIA   */	DEADTRANS(	0x00a0	,0x1fe3	,0x1fee	,DKF_0	), // GREEK DIALYTIKA AND OXIA
/*G_DIALYTIKA&OXIA   */	DEADTRANS(	L'i'	,0x1fe3	,0x1fd3	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND OXIA
/*G_DIALYTIKA&OXIA   */	DEADTRANS(	L'y'	,0x1fe3	,0x1fe3	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND OXIA
/*G_DIALYTIKA&OXIA   */	DEADTRANS(	0x03b9	,0x1fe3	,0x1fd3	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND OXIA
/*G_DIALYTIKA&OXIA   */	DEADTRANS(	0x03c5	,0x1fe3	,0x1fe3	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND OXIA
/*G_DIALYTIKA&PERI   */	DEADTRANS(	0x00a0	,0x1fe7	,0x1fc1	,DKF_0	), // GREEK DIALYTIKA AND PERISPOMENI
/*G_DIALYTIKA&PERI   */	DEADTRANS(	L'i'	,0x1fe7	,0x1fd7	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND PERISPOMENI
/*G_DIALYTIKA&PERI   */	DEADTRANS(	L'y'	,0x1fe7	,0x1fe7	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND PERISPOMENI
/*G_DIALYTIKA&PERI   */	DEADTRANS(	0x03b9	,0x1fe7	,0x1fd7	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND PERISPOMENI
/*G_DIALYTIKA&PERI   */	DEADTRANS(	0x03c5	,0x1fe7	,0x1fe7	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND PERISPOMENI
/*G_DIALYTIKA&TONOS  */	DEADTRANS(	0x0020	,0x0390	,0x0344	,DKF_0	), // COMBINING GREEK DIALYTIKA TONOS
/*G_DIALYTIKA&TONOS  */	DEADTRANS(	0x00a0	,0x0390	,0x0385	,DKF_0	), // GREEK DIALYTIKA TONOS
/*G_DIALYTIKA&TONOS  */	DEADTRANS(	0x202f	,0x0390	,0x0385	,DKF_0	), // GREEK DIALYTIKA TONOS
/*G_DIALYTIKA&TONOS  */	DEADTRANS(	L'i'	,0x0390	,0x0390	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
/*G_DIALYTIKA&TONOS  */	DEADTRANS(	L'y'	,0x0390	,0x03b0	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS
/*G_DIALYTIKA&TONOS  */	DEADTRANS(	0x03b9	,0x0390	,0x0390	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
/*G_DIALYTIKA&TONOS  */	DEADTRANS(	0x03c5	,0x0390	,0x03b0	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS
/*G_DIALYTIKA&VARIA  */	DEADTRANS(	0x00a0	,0x1fe2	,0x1fed	,DKF_0	), // GREEK DIALYTIKA AND VARIA
/*G_DIALYTIKA&VARIA  */	DEADTRANS(	L'i'	,0x1fe2	,0x1fd2	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND VARIA
/*G_DIALYTIKA&VARIA  */	DEADTRANS(	L'y'	,0x1fe2	,0x1fe2	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND VARIA
/*G_DIALYTIKA&VARIA  */	DEADTRANS(	0x03b9	,0x1fe2	,0x1fd2	,DKF_0	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND VARIA
/*G_DIALYTIKA&VARIA  */	DEADTRANS(	0x03c5	,0x1fe2	,0x1fe2	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND VARIA
/*G_KORONIS          */	DEADTRANS(	0x0020	,0x1fbd	,0x0343	,DKF_0	), // COMBINING GREEK KORONIS
/*G_KORONIS          */	DEADTRANS(	0x00a0	,0x1fbd	,0x1fbd	,DKF_0	), // GREEK KORONIS
/*G_MACRON           */	DEADTRANS(	0x0020	,0x1fb1	,0x0304	,DKF_0	), // COMBINING MACRON
/*G_MACRON           */	DEADTRANS(	0x00a0	,0x1fb1	,0x00af	,DKF_0	), // MACRON
/*G_MACRON           */	DEADTRANS(	0x202f	,0x1fb1	,0x02c9	,DKF_0	), // MODIFIER LETTER MACRON
/*G_MACRON           */	DEADTRANS(	L'A'	,0x1fb1	,0x1fb9	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH MACRON
/*G_MACRON           */	DEADTRANS(	L'a'	,0x1fb1	,0x1fb1	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH MACRON
/*G_MACRON           */	DEADTRANS(	L'I'	,0x1fb1	,0x1fd9	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH MACRON
/*G_MACRON           */	DEADTRANS(	L'i'	,0x1fb1	,0x1fd1	,DKF_0	), // GREEK SMALL LETTER IOTA WITH MACRON
/*G_MACRON           */	DEADTRANS(	L'Y'	,0x1fb1	,0x1fe9	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH MACRON
/*G_MACRON           */	DEADTRANS(	L'y'	,0x1fb1	,0x1fe1	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH MACRON
/*G_MACRON           */	DEADTRANS(	0x0391	,0x1fb1	,0x1fb9	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH MACRON
/*G_MACRON           */	DEADTRANS(	0x03b1	,0x1fb1	,0x1fb1	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH MACRON
/*G_MACRON           */	DEADTRANS(	0x0399	,0x1fb1	,0x1fd9	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH MACRON
/*G_MACRON           */	DEADTRANS(	0x03b9	,0x1fb1	,0x1fd1	,DKF_0	), // GREEK SMALL LETTER IOTA WITH MACRON
/*G_MACRON           */	DEADTRANS(	0x03a5	,0x1fb1	,0x1fe9	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH MACRON
/*G_MACRON           */	DEADTRANS(	0x03c5	,0x1fb1	,0x1fe1	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH MACRON
/*G_OXIA             */	DEADTRANS(	0x0020	,0x1f7d	,0x0301	,DKF_0	), // COMBINING ACUTE ACCENT
/*G_OXIA             */	DEADTRANS(	0x00a0	,0x1f7d	,0x1ffd	,DKF_0	), // GREEK OXIA
/*G_OXIA             */	DEADTRANS(	0x202f	,0x1f7d	,0x1ffd	,DKF_0	), // GREEK OXIA
/*G_OXIA             */	DEADTRANS(	L'A'	,0x1f7d	,0x1fbb	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'a'	,0x1f7d	,0x1f71	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'E'	,0x1f7d	,0x1fc9	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'e'	,0x1f7d	,0x1f73	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'H'	,0x1f7d	,0x1fcb	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'h'	,0x1f7d	,0x1f75	,DKF_0	), // GREEK SMALL LETTER ETA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'I'	,0x1f7d	,0x1fdb	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'i'	,0x1f7d	,0x1f77	,DKF_0	), // GREEK SMALL LETTER IOTA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'O'	,0x1f7d	,0x1ff9	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'o'	,0x1f7d	,0x1f79	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'V'	,0x1f7d	,0x1ffb	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'v'	,0x1f7d	,0x1f7d	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'W'	,0x1f7d	,0x1ffb	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'w'	,0x1f7d	,0x1f7d	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'Y'	,0x1f7d	,0x1feb	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	L'y'	,0x1f7d	,0x1f7b	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x1f10	,0x1f7d	,0x1f14	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND OXIA
/*G_OXIA             */	DEADTRANS(	0x1f51	,0x1f7d	,0x1f55	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND OXIA
/*G_OXIA             */	DEADTRANS(	0x003c	,0x1f7d	,0x1f55	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND OXIA
/*G_OXIA             */	DEADTRANS(	0x003e	,0x1f7d	,0x1f14	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND OXIA
/*G_OXIA             */	DEADTRANS(	0x0391	,0x1f7d	,0x1fbb	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03b1	,0x1f7d	,0x1f71	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x0395	,0x1f7d	,0x1fc9	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03b5	,0x1f7d	,0x1f73	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x0397	,0x1f7d	,0x1fcb	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03b7	,0x1f7d	,0x1f75	,DKF_0	), // GREEK SMALL LETTER ETA WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x0399	,0x1f7d	,0x1fdb	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03b9	,0x1f7d	,0x1f77	,DKF_0	), // GREEK SMALL LETTER IOTA WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x039f	,0x1f7d	,0x1ff9	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03bf	,0x1f7d	,0x1f79	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03a5	,0x1f7d	,0x1feb	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03c5	,0x1f7d	,0x1f7b	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03a9	,0x1f7d	,0x1ffb	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH OXIA
/*G_OXIA             */	DEADTRANS(	0x03c9	,0x1f7d	,0x1f7d	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH OXIA
/*G_OXIA&I           */	DEADTRANS(	L'a'	,0x1ff4	,0x1fb4	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	L'h'	,0x1ff4	,0x1fc4	,DKF_0	), // GREEK SMALL LETTER ETA WITH OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	L'v'	,0x1ff4	,0x1ff4	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	L'w'	,0x1ff4	,0x1ff4	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	0x1f10	,0x1ff4	,0x1f84	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	0x1f51	,0x1ff4	,0x1fa5	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	0x003c	,0x1ff4	,0x1fa5	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	0x003e	,0x1ff4	,0x1f84	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	0x03b1	,0x1ff4	,0x1fb4	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	0x03b7	,0x1ff4	,0x1fc4	,DKF_0	), // GREEK SMALL LETTER ETA WITH OXIA AND YPOGEGRAMMENI
/*G_OXIA&I           */	DEADTRANS(	0x03c9	,0x1ff4	,0x1ff4	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x0020	,0x1fc6	,0x0342	,DKF_0	), // COMBINING GREEK PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x00a0	,0x1fc6	,0x1fc0	,DKF_0	), // GREEK PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x202f	,0x1fc6	,0x1fc0	,DKF_0	), // GREEK PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	L'a'	,0x1fc6	,0x1fb6	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	L'h'	,0x1fc6	,0x1fc6	,DKF_0	), // GREEK SMALL LETTER ETA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	L'i'	,0x1fc6	,0x1fd6	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	L'v'	,0x1fc6	,0x1ff6	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	L'w'	,0x1fc6	,0x1ff6	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	L'y'	,0x1fc6	,0x1fe6	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x1f10	,0x1fc6	,0x1f26	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x1f51	,0x1fc6	,0x1f57	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x003c	,0x1fc6	,0x1f57	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x003e	,0x1fc6	,0x1f26	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x03b1	,0x1fc6	,0x1fb6	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x03b7	,0x1fc6	,0x1fc6	,DKF_0	), // GREEK SMALL LETTER ETA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x03b9	,0x1fc6	,0x1fd6	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x03c5	,0x1fc6	,0x1fe6	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PERISPOMENI
/*G_PERISPOMENI      */	DEADTRANS(	0x03c9	,0x1fc6	,0x1ff6	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PERISPOMENI
/*G_PERISPOMENI&I    */	DEADTRANS(	L'a'	,0x1fc7	,0x1fb7	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_PERISPOMENI&I    */	DEADTRANS(	L'h'	,0x1fc7	,0x1fc7	,DKF_0	), // GREEK SMALL LETTER ETA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_PERISPOMENI&I    */	DEADTRANS(	L'v'	,0x1fc7	,0x1ff7	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_PERISPOMENI&I    */	DEADTRANS(	L'w'	,0x1fc7	,0x1ff7	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_PERISPOMENI&I    */	DEADTRANS(	0x03b1	,0x1fc7	,0x1fb7	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_PERISPOMENI&I    */	DEADTRANS(	0x03b7	,0x1fc7	,0x1fc7	,DKF_0	), // GREEK SMALL LETTER ETA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_PERISPOMENI&I    */	DEADTRANS(	0x03c9	,0x1fc7	,0x1ff7	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI            */	DEADTRANS(	0x00a0	,0x1f10	,0x1fbf	,DKF_0	), // GREEK PSILI
/*G_PSILI            */	DEADTRANS(	0x202f	,0x1f10	,0x1fbf	,DKF_0	), // GREEK PSILI
/*G_PSILI            */	DEADTRANS(	L'A'	,0x1f10	,0x1f08	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'a'	,0x1f10	,0x1f00	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'E'	,0x1f10	,0x1f18	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'e'	,0x1f10	,0x1f10	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'H'	,0x1f10	,0x1f28	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'h'	,0x1f10	,0x1f20	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'I'	,0x1f10	,0x1f38	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'i'	,0x1f10	,0x1f30	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'O'	,0x1f10	,0x1f48	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'o'	,0x1f10	,0x1f40	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'r'	,0x1f10	,0x1fe4	,DKF_0	), // GREEK SMALL LETTER RHO WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'V'	,0x1f10	,0x1f68	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'v'	,0x1f10	,0x1f60	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'W'	,0x1f10	,0x1f68	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'w'	,0x1f10	,0x1f60	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI
/*G_PSILI            */	DEADTRANS(	L'y'	,0x1f10	,0x1f50	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x1f70	,0x1f10	,0x1f12	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND VARIA
/*G_PSILI            */	DEADTRANS(	0x1f7d	,0x1f10	,0x1f14	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND OXIA
/*G_PSILI            */	DEADTRANS(	0x1fc3	,0x1f10	,0x1f90	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI            */	DEADTRANS(	0x1fc6	,0x1f10	,0x1f26	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PSILI            */	DEADTRANS(	0x002c	,0x1f10	,0x1f14	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND OXIA
/*G_PSILI            */	DEADTRANS(	0x003b	,0x1f10	,0x1f90	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI            */	DEADTRANS(	0x0060	,0x1f10	,0x1f12	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND VARIA
/*G_PSILI            */	DEADTRANS(	0x007e	,0x1f10	,0x1f26	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PSILI            */	DEADTRANS(	0x0391	,0x1f10	,0x1f08	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03b1	,0x1f10	,0x1f00	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x0395	,0x1f10	,0x1f18	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03b5	,0x1f10	,0x1f10	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x0397	,0x1f10	,0x1f28	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03b7	,0x1f10	,0x1f20	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x0399	,0x1f10	,0x1f38	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03b9	,0x1f10	,0x1f30	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x039f	,0x1f10	,0x1f48	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03bf	,0x1f10	,0x1f40	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03c1	,0x1f10	,0x1fe4	,DKF_0	), // GREEK SMALL LETTER RHO WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03c5	,0x1f10	,0x1f50	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03a9	,0x1f10	,0x1f68	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI
/*G_PSILI            */	DEADTRANS(	0x03c9	,0x1f10	,0x1f60	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI
/*G_PSILI&I          */	DEADTRANS(	L'A'	,0x1f90	,0x1f88	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PROSGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	L'a'	,0x1f90	,0x1f80	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	L'H'	,0x1f90	,0x1f98	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND PROSGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	L'h'	,0x1f90	,0x1f90	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	L'V'	,0x1f90	,0x1fa8	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	L'v'	,0x1f90	,0x1fa0	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	L'W'	,0x1f90	,0x1fa8	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	L'w'	,0x1f90	,0x1fa0	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x1f70	,0x1f90	,0x1f82	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x1f7d	,0x1f90	,0x1f84	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x002c	,0x1f90	,0x1f84	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x0060	,0x1f90	,0x1f82	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x0391	,0x1f90	,0x1f88	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PROSGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x03b1	,0x1f90	,0x1f80	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x0397	,0x1f90	,0x1f98	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND PROSGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x03b7	,0x1f90	,0x1f90	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x03a9	,0x1f90	,0x1fa8	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PROSGEGRAMMENI
/*G_PSILI&I          */	DEADTRANS(	0x03c9	,0x1f90	,0x1fa0	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND YPOGEGRAMMENI
/*G_PSILI&OXIA       */	DEADTRANS(	0x00a0	,0x1f14	,0x1fce	,DKF_0	), // GREEK PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'A'	,0x1f14	,0x1f0c	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'a'	,0x1f14	,0x1f04	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'E'	,0x1f14	,0x1f1c	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'e'	,0x1f14	,0x1f14	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'H'	,0x1f14	,0x1f2c	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'h'	,0x1f14	,0x1f24	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'I'	,0x1f14	,0x1f3c	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'i'	,0x1f14	,0x1f34	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'O'	,0x1f14	,0x1f4c	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'o'	,0x1f14	,0x1f44	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'V'	,0x1f14	,0x1f6c	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'v'	,0x1f14	,0x1f64	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'W'	,0x1f14	,0x1f6c	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'w'	,0x1f14	,0x1f64	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	L'y'	,0x1f14	,0x1f54	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x1fc3	,0x1f14	,0x1f84	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA       */	DEADTRANS(	0x003b	,0x1f14	,0x1f84	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA       */	DEADTRANS(	0x0391	,0x1f14	,0x1f0c	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03b1	,0x1f14	,0x1f04	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x0395	,0x1f14	,0x1f1c	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03b5	,0x1f14	,0x1f14	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x0397	,0x1f14	,0x1f2c	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03b7	,0x1f14	,0x1f24	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x0399	,0x1f14	,0x1f3c	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03b9	,0x1f14	,0x1f34	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x039f	,0x1f14	,0x1f4c	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03bf	,0x1f14	,0x1f44	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03c5	,0x1f14	,0x1f54	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03a9	,0x1f14	,0x1f6c	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA
/*G_PSILI&OXIA       */	DEADTRANS(	0x03c9	,0x1f14	,0x1f64	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'A'	,0x1f84	,0x1f8c	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND OXIA AND PROSGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'a'	,0x1f84	,0x1f84	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'H'	,0x1f84	,0x1f9c	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND OXIA AND PROSGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'h'	,0x1f84	,0x1f94	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'V'	,0x1f84	,0x1fac	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA AND PROSGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'v'	,0x1f84	,0x1fa4	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'W'	,0x1f84	,0x1fac	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA AND PROSGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	L'w'	,0x1f84	,0x1fa4	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	0x0391	,0x1f84	,0x1f8c	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND OXIA AND PROSGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	0x03b1	,0x1f84	,0x1f84	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	0x0397	,0x1f84	,0x1f9c	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND OXIA AND PROSGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	0x03b7	,0x1f84	,0x1f94	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	0x03a9	,0x1f84	,0x1fac	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND OXIA AND PROSGEGRAMMENI
/*G_PSILI&OXIA&I     */	DEADTRANS(	0x03c9	,0x1f84	,0x1fa4	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND OXIA AND YPOGEGRAMMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x00a0	,0x1f26	,0x1fcf	,DKF_0	), // GREEK PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x202f	,0x1f26	,0x1fcf	,DKF_0	), // GREEK PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'A'	,0x1f26	,0x1f0e	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'a'	,0x1f26	,0x1f06	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'H'	,0x1f26	,0x1f2e	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'h'	,0x1f26	,0x1f26	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'I'	,0x1f26	,0x1f3e	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'i'	,0x1f26	,0x1f36	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'V'	,0x1f26	,0x1f6e	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'v'	,0x1f26	,0x1f66	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'W'	,0x1f26	,0x1f6e	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'w'	,0x1f26	,0x1f66	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	L'y'	,0x1f26	,0x1f56	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x1fc3	,0x1f26	,0x1fa6	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x003b	,0x1f26	,0x1fa6	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x0391	,0x1f26	,0x1f0e	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x03b1	,0x1f26	,0x1f06	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x0397	,0x1f26	,0x1f2e	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x03b7	,0x1f26	,0x1f26	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x0399	,0x1f26	,0x1f3e	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x03b9	,0x1f26	,0x1f36	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x03c5	,0x1f26	,0x1f56	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x03a9	,0x1f26	,0x1f6e	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI       */	DEADTRANS(	0x03c9	,0x1f26	,0x1f66	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'A'	,0x1fa6	,0x1f8e	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'a'	,0x1fa6	,0x1f86	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'H'	,0x1fa6	,0x1f9e	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'h'	,0x1fa6	,0x1f96	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'V'	,0x1fa6	,0x1fae	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'v'	,0x1fa6	,0x1fa6	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'W'	,0x1fa6	,0x1fae	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	L'w'	,0x1fa6	,0x1fa6	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	0x0391	,0x1fa6	,0x1f8e	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	0x03b1	,0x1fa6	,0x1f86	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	0x0397	,0x1fa6	,0x1f9e	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	0x03b7	,0x1fa6	,0x1f96	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	0x03a9	,0x1fa6	,0x1fae	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND PERISPOMENI AND PROSGEGRAMMENI
/*G_PSILI&PERI&I     */	DEADTRANS(	0x03c9	,0x1fa6	,0x1fa6	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND PERISPOMENI AND YPOGEGRAMMENI
/*G_PSILI&VARIA      */	DEADTRANS(	0x00a0	,0x1f12	,0x1fcd	,DKF_0	), // GREEK PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'A'	,0x1f12	,0x1f0a	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'a'	,0x1f12	,0x1f02	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'E'	,0x1f12	,0x1f1a	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'e'	,0x1f12	,0x1f12	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'H'	,0x1f12	,0x1f2a	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'h'	,0x1f12	,0x1f22	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'I'	,0x1f12	,0x1f3a	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'i'	,0x1f12	,0x1f32	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'O'	,0x1f12	,0x1f4a	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'o'	,0x1f12	,0x1f42	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'V'	,0x1f12	,0x1f6a	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'v'	,0x1f12	,0x1f62	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'W'	,0x1f12	,0x1f6a	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'w'	,0x1f12	,0x1f62	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	L'y'	,0x1f12	,0x1f52	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x1fc3	,0x1f12	,0x1f82	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA      */	DEADTRANS(	0x003b	,0x1f12	,0x1f82	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA      */	DEADTRANS(	0x0391	,0x1f12	,0x1f0a	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03b1	,0x1f12	,0x1f02	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x0395	,0x1f12	,0x1f1a	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03b5	,0x1f12	,0x1f12	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x0397	,0x1f12	,0x1f2a	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03b7	,0x1f12	,0x1f22	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x0399	,0x1f12	,0x1f3a	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03b9	,0x1f12	,0x1f32	,DKF_0	), // GREEK SMALL LETTER IOTA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x039f	,0x1f12	,0x1f4a	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03bf	,0x1f12	,0x1f42	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03c5	,0x1f12	,0x1f52	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03a9	,0x1f12	,0x1f6a	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA
/*G_PSILI&VARIA      */	DEADTRANS(	0x03c9	,0x1f12	,0x1f62	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'A'	,0x1f82	,0x1f8a	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND VARIA AND PROSGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'a'	,0x1f82	,0x1f82	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'H'	,0x1f82	,0x1f9a	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND VARIA AND PROSGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'h'	,0x1f82	,0x1f92	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'V'	,0x1f82	,0x1faa	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA AND PROSGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'v'	,0x1f82	,0x1fa2	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'W'	,0x1f82	,0x1faa	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA AND PROSGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	L'w'	,0x1f82	,0x1fa2	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	0x0391	,0x1f82	,0x1f8a	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PSILI AND VARIA AND PROSGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	0x03b1	,0x1f82	,0x1f82	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	0x0397	,0x1f82	,0x1f9a	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PSILI AND VARIA AND PROSGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	0x03b7	,0x1f82	,0x1f92	,DKF_0	), // GREEK SMALL LETTER ETA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	0x03a9	,0x1f82	,0x1faa	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PSILI AND VARIA AND PROSGEGRAMMENI
/*G_PSILI&VARIA&I    */	DEADTRANS(	0x03c9	,0x1f82	,0x1fa2	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_TONOS            */	DEADTRANS(	0x0020	,0x03cc	,0x0301	,DKF_0	), // COMBINING ACUTE ACCENT
/*G_TONOS            */	DEADTRANS(	0x202f	,0x03cc	,0x0384	,DKF_0	), // GREEK TONOS
/*G_TONOS            */	DEADTRANS(	0x00a0	,0x03cc	,0x0384	,DKF_0	), // GREEK TONOS
/*G_TONOS            */	DEADTRANS(	L'A'	,0x03cc	,0x0386	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'a'	,0x03cc	,0x03ac	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'E'	,0x03cc	,0x0388	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'e'	,0x03cc	,0x03ad	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'H'	,0x03cc	,0x0389	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'h'	,0x03cc	,0x03ae	,DKF_0	), // GREEK SMALL LETTER ETA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'I'	,0x03cc	,0x038a	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'i'	,0x03cc	,0x03af	,DKF_0	), // GREEK SMALL LETTER IOTA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'O'	,0x03cc	,0x038c	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'o'	,0x03cc	,0x03cc	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'V'	,0x03cc	,0x038f	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'v'	,0x03cc	,0x03ce	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'W'	,0x03cc	,0x038f	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'w'	,0x03cc	,0x03ce	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'Y'	,0x03cc	,0x038e	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	L'y'	,0x03cc	,0x03cd	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03ca	,0x03cc	,0x0390	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
/*G_TONOS            */	DEADTRANS(	0x003a	,0x03cc	,0x0390	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
/*G_TONOS            */	DEADTRANS(	0x0391	,0x03cc	,0x0386	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03b1	,0x03cc	,0x03ac	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x0395	,0x03cc	,0x0388	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03b5	,0x03cc	,0x03ad	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x0397	,0x03cc	,0x0389	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03b7	,0x03cc	,0x03ae	,DKF_0	), // GREEK SMALL LETTER ETA WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x0399	,0x03cc	,0x038a	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03b9	,0x03cc	,0x03af	,DKF_0	), // GREEK SMALL LETTER IOTA WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x039f	,0x03cc	,0x038c	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03bf	,0x03cc	,0x03cc	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03a5	,0x03cc	,0x038e	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03c5	,0x03cc	,0x03cd	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03a9	,0x03cc	,0x038f	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH TONOS
/*G_TONOS            */	DEADTRANS(	0x03c9	,0x03cc	,0x03ce	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH TONOS
/*G_VARIA            */	DEADTRANS(	0x0020	,0x1f70	,0x0300	,DKF_0	), // COMBINING GRAVE ACCENT
/*G_VARIA            */	DEADTRANS(	0x00a0	,0x1f70	,0x1fef	,DKF_0	), // GREEK VARIA
/*G_VARIA            */	DEADTRANS(	0x202f	,0x1f70	,0x1fef	,DKF_0	), // GREEK VARIA
/*G_VARIA            */	DEADTRANS(	L'A'	,0x1f70	,0x1fba	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'a'	,0x1f70	,0x1f70	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'E'	,0x1f70	,0x1fc8	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'e'	,0x1f70	,0x1f72	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'H'	,0x1f70	,0x1fca	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'h'	,0x1f70	,0x1f74	,DKF_0	), // GREEK SMALL LETTER ETA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'I'	,0x1f70	,0x1fda	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'i'	,0x1f70	,0x1f76	,DKF_0	), // GREEK SMALL LETTER IOTA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'O'	,0x1f70	,0x1ff8	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'o'	,0x1f70	,0x1f78	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'V'	,0x1f70	,0x1ffa	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'v'	,0x1f70	,0x1f7c	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'W'	,0x1f70	,0x1ffa	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'w'	,0x1f70	,0x1f7c	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'Y'	,0x1f70	,0x1fea	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	L'y'	,0x1f70	,0x1f7a	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x1f10	,0x1f70	,0x1f12	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND VARIA
/*G_VARIA            */	DEADTRANS(	0x1f51	,0x1f70	,0x1f53	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND VARIA
/*G_VARIA            */	DEADTRANS(	0x003c	,0x1f70	,0x1f53	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA AND VARIA
/*G_VARIA            */	DEADTRANS(	0x003e	,0x1f70	,0x1f12	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI AND VARIA
/*G_VARIA            */	DEADTRANS(	0x0391	,0x1f70	,0x1fba	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03b1	,0x1f70	,0x1f70	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x0395	,0x1f70	,0x1fc8	,DKF_0	), // GREEK CAPITAL LETTER EPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03b5	,0x1f70	,0x1f72	,DKF_0	), // GREEK SMALL LETTER EPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x0397	,0x1f70	,0x1fca	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03b7	,0x1f70	,0x1f74	,DKF_0	), // GREEK SMALL LETTER ETA WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x0399	,0x1f70	,0x1fda	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03b9	,0x1f70	,0x1f76	,DKF_0	), // GREEK SMALL LETTER IOTA WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x039f	,0x1f70	,0x1ff8	,DKF_0	), // GREEK CAPITAL LETTER OMICRON WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03bf	,0x1f70	,0x1f78	,DKF_0	), // GREEK SMALL LETTER OMICRON WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03a5	,0x1f70	,0x1fea	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03c5	,0x1f70	,0x1f7a	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03a9	,0x1f70	,0x1ffa	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH VARIA
/*G_VARIA            */	DEADTRANS(	0x03c9	,0x1f70	,0x1f7c	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH VARIA
/*G_VARIA&I          */	DEADTRANS(	L'a'	,0x1fb2	,0x1fb2	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	L'h'	,0x1fb2	,0x1fc2	,DKF_0	), // GREEK SMALL LETTER ETA WITH VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	L'v'	,0x1fb2	,0x1ff2	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	L'w'	,0x1fb2	,0x1ff2	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	0x1f10	,0x1fb2	,0x1f82	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	0x1f51	,0x1fb2	,0x1f93	,CHAIN	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	0x003c	,0x1fb2	,0x1f93	,CHAIN	), // GREEK SMALL LETTER ETA WITH DASIA AND VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	0x003e	,0x1fb2	,0x1f82	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH PSILI AND VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	0x03b1	,0x1fb2	,0x1fb2	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	0x03b7	,0x1fb2	,0x1fc2	,DKF_0	), // GREEK SMALL LETTER ETA WITH VARIA AND YPOGEGRAMMENI
/*G_VARIA&I          */	DEADTRANS(	0x03c9	,0x1fb2	,0x1ff2	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH VARIA AND YPOGEGRAMMENI
/*G_VRACHY           */	DEADTRANS(	0x0020	,0x1fe0	,0x0306	,DKF_0	), // COMBINING BREVE
/*G_VRACHY           */	DEADTRANS(	L'A'	,0x1fe0	,0x1fb8	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	L'a'	,0x1fe0	,0x1fb0	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	L'I'	,0x1fe0	,0x1fd8	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	L'i'	,0x1fe0	,0x1fd0	,DKF_0	), // GREEK SMALL LETTER IOTA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	L'Y'	,0x1fe0	,0x1fe8	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	L'y'	,0x1fe0	,0x1fe0	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	0x0391	,0x1fe0	,0x1fb8	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	0x03b1	,0x1fe0	,0x1fb0	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	0x0399	,0x1fe0	,0x1fd8	,DKF_0	), // GREEK CAPITAL LETTER IOTA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	0x03b9	,0x1fe0	,0x1fd0	,DKF_0	), // GREEK SMALL LETTER IOTA WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	0x03a5	,0x1fe0	,0x1fe8	,DKF_0	), // GREEK CAPITAL LETTER UPSILON WITH VRACHY
/*G_VRACHY           */	DEADTRANS(	0x03c5	,0x1fe0	,0x1fe0	,DKF_0	), // GREEK SMALL LETTER UPSILON WITH VRACHY
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x00a0	,0x1fc3	,0x037a	,DKF_0	), // GREEK YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x202f	,0x1fc3	,0x1fbe	,DKF_0	), // GREEK PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'A'	,0x1fc3	,0x1fbc	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'a'	,0x1fc3	,0x1fb3	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'H'	,0x1fc3	,0x1fcc	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'h'	,0x1fc3	,0x1fc3	,DKF_0	), // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'V'	,0x1fc3	,0x1ffc	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'v'	,0x1fc3	,0x1ff3	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'W'	,0x1fc3	,0x1ffc	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	L'w'	,0x1fc3	,0x1ff3	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x1f10	,0x1fc3	,0x1f90	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x1f51	,0x1fc3	,0x1fa1	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x1f70	,0x1fc3	,0x1fb2	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH VARIA AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x1f7d	,0x1fc3	,0x1ff4	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x1fc6	,0x1fc3	,0x1fc7	,CHAIN	), // GREEK SMALL LETTER ETA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x0020	,0x1fc3	,0x0345	,DKF_0	), // COMBINING GREEK YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x002c	,0x1fc3	,0x1ff4	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH OXIA AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x003c	,0x1fc3	,0x1fa1	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH DASIA AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x003e	,0x1fc3	,0x1f90	,CHAIN	), // GREEK SMALL LETTER ETA WITH PSILI AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x0060	,0x1fc3	,0x1fb2	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH VARIA AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x007e	,0x1fc3	,0x1fc7	,CHAIN	), // GREEK SMALL LETTER ETA WITH PERISPOMENI AND YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x0391	,0x1fc3	,0x1fbc	,DKF_0	), // GREEK CAPITAL LETTER ALPHA WITH PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x03b1	,0x1fc3	,0x1fb3	,DKF_0	), // GREEK SMALL LETTER ALPHA WITH YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x0397	,0x1fc3	,0x1fcc	,DKF_0	), // GREEK CAPITAL LETTER ETA WITH PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x03b7	,0x1fc3	,0x1fc3	,DKF_0	), // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x03a9	,0x1fc3	,0x1ffc	,DKF_0	), // GREEK CAPITAL LETTER OMEGA WITH PROSGEGRAMMENI
/*G_YPOGEGRAMMENI    */	DEADTRANS(	0x03c9	,0x1fc3	,0x1ff3	,DKF_0	), // GREEK SMALL LETTER OMEGA WITH YPOGEGRAMMENI
/*GRAVE_ACCENT       */	DEADTRANS(	0x0020	,0x00f2	,0x0300	,DKF_0	), // COMBINING GRAVE ACCENT
/*GRAVE_ACCENT       */	DEADTRANS(	0x00f2	,0x021f	,0x1dc8	,DKF_0	), // COMBINING GRAVE-ACUTE-GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00a0	,0x00f2	,0x0060	,DKF_0	), // GRAVE ACCENT
/*GRAVE_ACCENT       */	DEADTRANS(	0x00a3	,0x00f2	,0x02ce	,DKF_0	), // MODIFIER LETTER LOW GRAVE ACCENT
/*GRAVE_ACCENT       */	DEADTRANS(	0x202f	,0x00f2	,0x02cb	,DKF_0	), // MODIFIER LETTER GRAVE ACCENT
/*GRAVE_ACCENT       */	DEADTRANS(	L'A'	,0x00f2	,0x00c0	,DKF_0	), // LATIN CAPITAL LETTER A WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'a'	,0x00f2	,0x00e0	,DKF_0	), // LATIN SMALL LETTER A WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'B'	,0x00f2	,0x0181	,DKF_0	), // LATIN CAPITAL LETTER B WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'b'	,0x00f2	,0x0253	,DKF_0	), // LATIN SMALL LETTER B WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'C'	,0x00f2	,0x0187	,DKF_0	), // LATIN CAPITAL LETTER C WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'c'	,0x00f2	,0x0188	,DKF_0	), // LATIN SMALL LETTER C WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'D'	,0x00f2	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*GRAVE_ACCENT       */	DEADTRANS(	L'd'	,0x00f2	,0x0254	,DKF_0	), // LATIN SMALL LETTER OPEN O
/*GRAVE_ACCENT       */	DEADTRANS(	L'E'	,0x00f2	,0x00c8	,DKF_0	), // LATIN CAPITAL LETTER E WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'e'	,0x00f2	,0x00e8	,DKF_0	), // LATIN SMALL LETTER E WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'F'	,0x00f2	,0x0191	,DKF_0	), // LATIN CAPITAL LETTER F WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'f'	,0x00f2	,0x0192	,DKF_0	), // LATIN SMALL LETTER F WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'G'	,0x00f2	,0x0193	,DKF_0	), // LATIN CAPITAL LETTER G WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'g'	,0x00f2	,0x0260	,DKF_0	), // LATIN SMALL LETTER G WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'H'	,0x00f2	,0xa7aa	,DKF_0	), // LATIN CAPITAL LETTER H WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'h'	,0x00f2	,0x0266	,DKF_0	), // LATIN SMALL LETTER H WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'I'	,0x00f2	,0x00cc	,DKF_0	), // LATIN CAPITAL LETTER I WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'i'	,0x00f2	,0x00ec	,DKF_0	), // LATIN SMALL LETTER I WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'J'	,0x00f2	,0x0132	,DKF_0	), // LATIN CAPITAL LIGATURE IJ
/*GRAVE_ACCENT       */	DEADTRANS(	L'j'	,0x00f2	,0x0133	,DKF_0	), // LATIN SMALL LIGATURE IJ
/*GRAVE_ACCENT       */	DEADTRANS(	L'K'	,0x00f2	,0x0198	,DKF_0	), // LATIN CAPITAL LETTER K WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'k'	,0x00f2	,0x0199	,DKF_0	), // LATIN SMALL LETTER K WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'L'	,0x00f2	,0x01b3	,DKF_0	), // LATIN CAPITAL LETTER Y WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'l'	,0x00f2	,0x01b4	,DKF_0	), // LATIN SMALL LETTER Y WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'M'	,0x00f2	,0x2c6e	,DKF_0	), // LATIN CAPITAL LETTER M WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'm'	,0x00f2	,0x0271	,DKF_0	), // LATIN SMALL LETTER M WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'N'	,0x00f2	,0x01f8	,DKF_0	), // LATIN CAPITAL LETTER N WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'n'	,0x00f2	,0x01f9	,DKF_0	), // LATIN SMALL LETTER N WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'O'	,0x00f2	,0x00d2	,DKF_0	), // LATIN CAPITAL LETTER O WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'o'	,0x00f2	,0x00f2	,DKF_0	), // LATIN SMALL LETTER O WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'P'	,0x00f2	,0x01a4	,DKF_0	), // LATIN CAPITAL LETTER P WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'p'	,0x00f2	,0x01a5	,DKF_0	), // LATIN SMALL LETTER P WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'Q'	,0x00f2	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*GRAVE_ACCENT       */	DEADTRANS(	L'q'	,0x00f2	,0x025b	,DKF_0	), // LATIN SMALL LETTER OPEN E
/*GRAVE_ACCENT       */	DEADTRANS(	L'R'	,0x00f2	,0x2c64	,DKF_0	), // LATIN CAPITAL LETTER R WITH TAIL
/*GRAVE_ACCENT       */	DEADTRANS(	L'r'	,0x00f2	,0x027d	,DKF_0	), // LATIN SMALL LETTER R WITH TAIL
/*GRAVE_ACCENT       */	DEADTRANS(	L'S'	,0x00f2	,0x017f	,DKF_0	), // LATIN SMALL LETTER LONG S
/*GRAVE_ACCENT       */	DEADTRANS(	L's'	,0x00f2	,0x017f	,DKF_0	), // LATIN SMALL LETTER LONG S
/*GRAVE_ACCENT       */	DEADTRANS(	L'T'	,0x00f2	,0x01ac	,DKF_0	), // LATIN CAPITAL LETTER T WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L't'	,0x00f2	,0x01ad	,DKF_0	), // LATIN SMALL LETTER T WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'U'	,0x00f2	,0x00d9	,DKF_0	), // LATIN CAPITAL LETTER U WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'u'	,0x00f2	,0x00f9	,DKF_0	), // LATIN SMALL LETTER U WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'V'	,0x00f2	,0x01b2	,DKF_0	), // LATIN CAPITAL LETTER V WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'v'	,0x00f2	,0x028b	,DKF_0	), // LATIN SMALL LETTER V WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'W'	,0x00f2	,0x1e80	,DKF_0	), // LATIN CAPITAL LETTER W WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'w'	,0x00f2	,0x1e81	,DKF_0	), // LATIN SMALL LETTER W WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'X'	,0x00f2	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'x'	,0x00f2	,0x0272	,DKF_0	), // LATIN SMALL LETTER N WITH LEFT HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'Y'	,0x00f2	,0x1ef2	,DKF_0	), // LATIN CAPITAL LETTER Y WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'y'	,0x00f2	,0x1ef3	,DKF_0	), // LATIN SMALL LETTER Y WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	L'Z'	,0x00f2	,0x0224	,DKF_0	), // LATIN CAPITAL LETTER Z WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'z'	,0x00f2	,0x0225	,DKF_0	), // LATIN SMALL LETTER Z WITH HOOK
/*GRAVE_ACCENT       */	DEADTRANS(	L'0'	,0x00f2	,0x0298	,DKF_0	), // LATIN LETTER BILABIAL CLICK
/*GRAVE_ACCENT       */	DEADTRANS(	L'1'	,0x00f2	,0x2035	,DKF_0	), // REVERSED PRIME
/*GRAVE_ACCENT       */	DEADTRANS(	L'2'	,0x00f2	,0x2036	,DKF_0	), // REVERSED DOUBLE PRIME
/*GRAVE_ACCENT       */	DEADTRANS(	L'3'	,0x00f2	,0x2037	,DKF_0	), // REVERSED TRIPLE PRIME
/*GRAVE_ACCENT       */	DEADTRANS(	L'6'	,0x00f2	,0x01c0	,DKF_0	), // LATIN LETTER DENTAL CLICK
/*GRAVE_ACCENT       */	DEADTRANS(	L'7'	,0x00f2	,0x0296	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP
/*GRAVE_ACCENT       */	DEADTRANS(	0x0021	,0x00f2	,0x01c3	,DKF_0	), // LATIN LETTER RETROFLEX CLICK
/*GRAVE_ACCENT       */	DEADTRANS(	0x0022	,0x00f2	,0x201f	,DKF_0	), // DOUBLE HIGH-REVERSED-9 QUOTATION MARK
/*GRAVE_ACCENT       */	DEADTRANS(	0x0023	,0x00f2	,0x201c	,DKF_0	), // LEFT DOUBLE QUOTATION MARK
/*GRAVE_ACCENT       */	DEADTRANS(	0x0025	,0x00f2	,0x2031	,DKF_0	), // PER TEN THOUSAND SIGN
/*GRAVE_ACCENT       */	DEADTRANS(	0x0027	,0x00f2	,0x201b	,DKF_0	), // SINGLE HIGH-REVERSED-9 QUOTATION MARK
/*GRAVE_ACCENT       */	DEADTRANS(	0x0029	,0x00f2	,0x1eb1	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x002a	,0x00f2	,0x00d7	,DKF_0	), // MULTIPLICATION SIGN
/*GRAVE_ACCENT       */	DEADTRANS(	0x002b	,0x00f2	,0x02f4	,DKF_0	), // MODIFIER LETTER MIDDLE GRAVE ACCENT
/*GRAVE_ACCENT       */	DEADTRANS(	0x002c	,0x00f2	,0x1edd	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x002d	,0x00f2	,0x2015	,DKF_0	), // HORIZONTAL BAR
/*GRAVE_ACCENT       */	DEADTRANS(	0x002e	,0x00f2	,0x00d7	,DKF_0	), // MULTIPLICATION SIGN
/*GRAVE_ACCENT       */	DEADTRANS(	0x002f	,0x00f2	,0x00f7	,DKF_0	), // DIVISION SIGN
/*GRAVE_ACCENT       */	DEADTRANS(	0x003a	,0x00f2	,0x01dc	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x003b	,0x00f2	,0x00d7	,DKF_0	), // MULTIPLICATION SIGN
/*GRAVE_ACCENT       */	DEADTRANS(	0x003c	,0x00f2	,0x2264	,DKF_0	), // LESS-THAN OR EQUAL TO
/*GRAVE_ACCENT       */	DEADTRANS(	0x003d	,0x00f2	,0x00ad	,DKF_0	), // SOFT HYPHEN
/*GRAVE_ACCENT       */	DEADTRANS(	0x003e	,0x00f2	,0x2265	,DKF_0	), // GREATER-THAN OR EQUAL TO
/*GRAVE_ACCENT       */	DEADTRANS(	0x003f	,0x00f2	,0x0294	,DKF_0	), // LATIN LETTER GLOTTAL STOP
/*GRAVE_ACCENT       */	DEADTRANS(	0x0040	,0x00f2	,0x20dd	,DKF_0	), // COMBINING ENCLOSING CIRCLE
/*GRAVE_ACCENT       */	DEADTRANS(	0x005e	,0x00f2	,0x1ed3	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x005f	,0x00f2	,0x1e51	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x0060	,0x00f2	,0x020d	,CHAIN	), // LATIN SMALL LETTER O WITH DOUBLE GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x007c	,0x00f2	,0x01c1	,DKF_0	), // LATIN LETTER LATERAL CLICK
/*GRAVE_ACCENT       */	DEADTRANS(	0x0152	,0x00f2	,0x00c6	,DKF_0	), // LATIN CAPITAL LETTER AE
/*GRAVE_ACCENT       */	DEADTRANS(	0x0153	,0x00f2	,0x00e6	,DKF_0	), // LATIN SMALL LETTER AE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00a9	,0x00f2	,0x01f9	,CHAIN	), // LATIN SMALL LETTER N WITH GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00a7	,0x00f2	,0x203b	,DKF_0	), // REFERENCE MARK
/*GRAVE_ACCENT       */	DEADTRANS(	0x00ab	,0x00f2	,0x2039	,DKF_0	), // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
/*GRAVE_ACCENT       */	DEADTRANS(	0x00b5	,0x00f2	,0x03c0	,DKF_0	), // GREEK SMALL LETTER PI
/*GRAVE_ACCENT       */	DEADTRANS(	0x00bb	,0x00f2	,0x203a	,DKF_0	), // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
/*GRAVE_ACCENT       */	DEADTRANS(	0x00c0	,0x00f2	,0x00c4	,DKF_0	), // LATIN CAPITAL LETTER A WITH DIAERESIS
/*GRAVE_ACCENT       */	DEADTRANS(	0x00c6	,0x00f2	,0x00c4	,DKF_0	), // LATIN CAPITAL LETTER A WITH DIAERESIS
/*GRAVE_ACCENT       */	DEADTRANS(	0x00c7	,0x00f2	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*GRAVE_ACCENT       */	DEADTRANS(	0x00c8	,0x00f2	,0x00d8	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00c9	,0x00f2	,0x00c5	,DKF_0	), // LATIN CAPITAL LETTER A WITH RING ABOVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00d9	,0x00f2	,0x00dc	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS
/*GRAVE_ACCENT       */	DEADTRANS(	0x00e0	,0x00f2	,0x00e4	,DKF_0	), // LATIN SMALL LETTER A WITH DIAERESIS
/*GRAVE_ACCENT       */	DEADTRANS(	0x00e1	,0x00f2	,0x021f	,CHAIN	), // LATIN SMALL LETTER H WITH CARON
/*GRAVE_ACCENT       */	DEADTRANS(	0x00e6	,0x00f2	,0x00e4	,DKF_0	), // LATIN SMALL LETTER A WITH DIAERESIS
/*GRAVE_ACCENT       */	DEADTRANS(	0x00e7	,0x00f2	,0x00df	,DKF_0	), // LATIN SMALL LETTER SHARP S
/*GRAVE_ACCENT       */	DEADTRANS(	0x00e8	,0x00f2	,0x00f8	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00e9	,0x00f2	,0x00e5	,DKF_0	), // LATIN SMALL LETTER A WITH RING ABOVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00ea	,0x00f2	,0x1ed3	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00eb	,0x00f2	,0x1ecd	,CHAIN	), // LATIN SMALL LETTER O WITH DOT BELOW
/*GRAVE_ACCENT       */	DEADTRANS(	0x00f2	,0x00f2	,0x020d	,CHAIN	), // LATIN SMALL LETTER O WITH DOUBLE GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x00f9	,0x00f2	,0x00fc	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS
/*GRAVE_ACCENT       */	DEADTRANS(	0x2019	,0x00f2	,0x2018	,DKF_0	), // LEFT SINGLE QUOTATION MARK
/*GRAVE_ACCENT       */	DEADTRANS(	0x2212	,0x00f2	,0x2011	,DKF_0	), // NON-BREAKING HYPHEN
/*GRAVE_ACCENT       */	DEADTRANS(	0x2610	,0x00f2	,0x2751	,DKF_0	), // LOWER RIGHT SHADOWED WHITE SQUARE
/*GRAVE_ACCENT       */	DEADTRANS(	0x222a	,0x00f2	,0x2228	,DKF_0	), // LOGICAL OR
/*GRAVE_ACCENT       */	DEADTRANS(	0x0186	,0x00f2	,0x019f	,DKF_0	), // LATIN CAPITAL LETTER O WITH MIDDLE TILDE
/*GRAVE_ACCENT       */	DEADTRANS(	0x0254	,0x00f2	,0x0275	,DKF_0	), // LATIN SMALL LETTER BARRED O
/*GRAVE_ACCENT       */	DEADTRANS(	0x0229	,0x00f2	,0x1edd	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x014f	,0x00f2	,0x1eb1	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x014d	,0x00f2	,0x1e51	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND GRAVE
/*GRAVE_ACCENT       */	DEADTRANS(	0x01a1	,0x00f2	,0x1edd	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND GRAVE
/*GRAVE_BELOW        */	DEADTRANS(	0x00a0	,0x02ce	,0x02ce	,DKF_0	), // MODIFIER LETTER LOW GRAVE ACCENT
/*GREEK              */	DEADTRANS(	L'A'	,0x03b5	,0x0391	,DKF_0	), // GREEK CAPITAL LETTER ALPHA
/*GREEK              */	DEADTRANS(	L'a'	,0x03b5	,0x03b1	,DKF_0	), // GREEK SMALL LETTER ALPHA
/*GREEK              */	DEADTRANS(	L'B'	,0x03b5	,0x0392	,DKF_0	), // GREEK CAPITAL LETTER BETA
/*GREEK              */	DEADTRANS(	L'b'	,0x03b5	,0x03b2	,DKF_0	), // GREEK SMALL LETTER BETA
/*GREEK              */	DEADTRANS(	L'C'	,0x03b5	,0x03a8	,DKF_0	), // GREEK CAPITAL LETTER PSI
/*GREEK              */	DEADTRANS(	L'c'	,0x03b5	,0x03c8	,DKF_0	), // GREEK SMALL LETTER PSI
/*GREEK              */	DEADTRANS(	L'D'	,0x03b5	,0x0394	,DKF_0	), // GREEK CAPITAL LETTER DELTA
/*GREEK              */	DEADTRANS(	L'd'	,0x03b5	,0x03b4	,DKF_0	), // GREEK SMALL LETTER DELTA
/*GREEK              */	DEADTRANS(	L'E'	,0x03b5	,0x0395	,DKF_0	), // GREEK CAPITAL LETTER EPSILON
/*GREEK              */	DEADTRANS(	L'e'	,0x03b5	,0x03b5	,DKF_0	), // GREEK SMALL LETTER EPSILON
/*GREEK              */	DEADTRANS(	L'F'	,0x03b5	,0x03a6	,DKF_0	), // GREEK CAPITAL LETTER PHI
/*GREEK              */	DEADTRANS(	L'f'	,0x03b5	,0x03c6	,DKF_0	), // GREEK SMALL LETTER PHI
/*GREEK              */	DEADTRANS(	L'G'	,0x03b5	,0x0393	,DKF_0	), // GREEK CAPITAL LETTER GAMMA
/*GREEK              */	DEADTRANS(	L'g'	,0x03b5	,0x03b3	,DKF_0	), // GREEK SMALL LETTER GAMMA
/*GREEK              */	DEADTRANS(	L'H'	,0x03b5	,0x0397	,DKF_0	), // GREEK CAPITAL LETTER ETA
/*GREEK              */	DEADTRANS(	L'h'	,0x03b5	,0x03b7	,DKF_0	), // GREEK SMALL LETTER ETA
/*GREEK              */	DEADTRANS(	L'I'	,0x03b5	,0x0399	,DKF_0	), // GREEK CAPITAL LETTER IOTA
/*GREEK              */	DEADTRANS(	L'i'	,0x03b5	,0x03b9	,DKF_0	), // GREEK SMALL LETTER IOTA
/*GREEK              */	DEADTRANS(	L'J'	,0x03b5	,0x039e	,DKF_0	), // GREEK CAPITAL LETTER XI
/*GREEK              */	DEADTRANS(	L'j'	,0x03b5	,0x03be	,DKF_0	), // GREEK SMALL LETTER XI
/*GREEK              */	DEADTRANS(	L'K'	,0x03b5	,0x039a	,DKF_0	), // GREEK CAPITAL LETTER KAPPA
/*GREEK              */	DEADTRANS(	L'k'	,0x03b5	,0x03ba	,DKF_0	), // GREEK SMALL LETTER KAPPA
/*GREEK              */	DEADTRANS(	L'L'	,0x03b5	,0x039b	,DKF_0	), // GREEK CAPITAL LETTER LAMDA
/*GREEK              */	DEADTRANS(	L'l'	,0x03b5	,0x03bb	,DKF_0	), // GREEK SMALL LETTER LAMDA
/*GREEK              */	DEADTRANS(	L'M'	,0x03b5	,0x039c	,DKF_0	), // GREEK CAPITAL LETTER MU
/*GREEK              */	DEADTRANS(	L'm'	,0x03b5	,0x03bc	,DKF_0	), // GREEK SMALL LETTER MU
/*GREEK              */	DEADTRANS(	L'N'	,0x03b5	,0x039d	,DKF_0	), // GREEK CAPITAL LETTER NU
/*GREEK              */	DEADTRANS(	L'n'	,0x03b5	,0x03bd	,DKF_0	), // GREEK SMALL LETTER NU
/*GREEK              */	DEADTRANS(	L'O'	,0x03b5	,0x039f	,DKF_0	), // GREEK CAPITAL LETTER OMICRON
/*GREEK              */	DEADTRANS(	L'o'	,0x03b5	,0x03bf	,DKF_0	), // GREEK SMALL LETTER OMICRON
/*GREEK              */	DEADTRANS(	L'P'	,0x03b5	,0x03a0	,DKF_0	), // GREEK CAPITAL LETTER PI
/*GREEK              */	DEADTRANS(	L'p'	,0x03b5	,0x03c0	,DKF_0	), // GREEK SMALL LETTER PI
/*GREEK              */	DEADTRANS(	L'Q'	,0x03b5	,0x2211	,DKF_0	), // N-ARY SUMMATION
/*GREEK              */	DEADTRANS(	L'q'	,0x03b5	,0x03c2	,DKF_0	), // GREEK SMALL LETTER FINAL SIGMA
/*GREEK              */	DEADTRANS(	L'R'	,0x03b5	,0x03a1	,DKF_0	), // GREEK CAPITAL LETTER RHO
/*GREEK              */	DEADTRANS(	L'r'	,0x03b5	,0x03c1	,DKF_0	), // GREEK SMALL LETTER RHO
/*GREEK              */	DEADTRANS(	L'S'	,0x03b5	,0x03a3	,DKF_0	), // GREEK CAPITAL LETTER SIGMA
/*GREEK              */	DEADTRANS(	L's'	,0x03b5	,0x03c3	,DKF_0	), // GREEK SMALL LETTER SIGMA
/*GREEK              */	DEADTRANS(	L'T'	,0x03b5	,0x03a4	,DKF_0	), // GREEK CAPITAL LETTER TAU
/*GREEK              */	DEADTRANS(	L't'	,0x03b5	,0x03c4	,DKF_0	), // GREEK SMALL LETTER TAU
/*GREEK              */	DEADTRANS(	L'U'	,0x03b5	,0x0398	,DKF_0	), // GREEK CAPITAL LETTER THETA
/*GREEK              */	DEADTRANS(	L'u'	,0x03b5	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*GREEK              */	DEADTRANS(	L'V'	,0x03b5	,0x03a9	,DKF_0	), // GREEK CAPITAL LETTER OMEGA
/*GREEK              */	DEADTRANS(	L'v'	,0x03b5	,0x03c9	,DKF_0	), // GREEK SMALL LETTER OMEGA
/*GREEK              */	DEADTRANS(	L'W'	,0x03b5	,0x03a9	,DKF_0	), // GREEK CAPITAL LETTER OMEGA
/*GREEK              */	DEADTRANS(	L'w'	,0x03b5	,0x03c9	,DKF_0	), // GREEK SMALL LETTER OMEGA
/*GREEK              */	DEADTRANS(	L'X'	,0x03b5	,0x03a7	,DKF_0	), // GREEK CAPITAL LETTER CHI
/*GREEK              */	DEADTRANS(	L'x'	,0x03b5	,0x03c7	,DKF_0	), // GREEK SMALL LETTER CHI
/*GREEK              */	DEADTRANS(	L'Y'	,0x03b5	,0x03a5	,DKF_0	), // GREEK CAPITAL LETTER UPSILON
/*GREEK              */	DEADTRANS(	L'y'	,0x03b5	,0x03c5	,DKF_0	), // GREEK SMALL LETTER UPSILON
/*GREEK              */	DEADTRANS(	L'Z'	,0x03b5	,0x0396	,DKF_0	), // GREEK CAPITAL LETTER ZETA
/*GREEK              */	DEADTRANS(	L'z'	,0x03b5	,0x03b6	,DKF_0	), // GREEK SMALL LETTER ZETA
/*GREEK              */	DEADTRANS(	0x0029	,0x03b5	,0x1fe0	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH VRACHY
/*GREEK              */	DEADTRANS(	0x03b5	,0x03b5	,0x0395	,CHAIN	), // GREEK CAPITAL LETTER EPSILON
/*GREEK              */	DEADTRANS(	0x002c	,0x03b5	,0x1f7d	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH OXIA
/*GREEK              */	DEADTRANS(	0x003a	,0x03b5	,0x03ca	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA
/*GREEK              */	DEADTRANS(	0x003b	,0x03b5	,0x1fc3	,CHAIN	), // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI
/*GREEK              */	DEADTRANS(	0x003c	,0x03b5	,0x1f51	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA
/*GREEK              */	DEADTRANS(	0x003e	,0x03b5	,0x1f10	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI
/*GREEK              */	DEADTRANS(	0x005f	,0x03b5	,0x1fb1	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH MACRON
/*GREEK              */	DEADTRANS(	0x0060	,0x03b5	,0x1f70	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH VARIA
/*GREEK              */	DEADTRANS(	0x007e	,0x03b5	,0x1fc6	,CHAIN	), // GREEK SMALL LETTER ETA WITH PERISPOMENI
/*GREEK              */	DEADTRANS(	0x00b5	,0x03b5	,0x0448	,CHAIN	), // CYRILLIC SMALL LETTER SHA
/*GREEK              */	DEADTRANS(	0x1f70	,0x03b5	,0x1f70	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH VARIA
/*GREEK              */	DEADTRANS(	0x1fb1	,0x03b5	,0x1fb1	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH MACRON
/*GREEK              */	DEADTRANS(	0x1f10	,0x03b5	,0x1f10	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI
/*GREEK              */	DEADTRANS(	0x1fc6	,0x03b5	,0x1fc6	,CHAIN	), // GREEK SMALL LETTER ETA WITH PERISPOMENI
/*GREEK              */	DEADTRANS(	0x1fc3	,0x03b5	,0x1fc3	,CHAIN	), // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI
/*GREEK              */	DEADTRANS(	0x03ca	,0x03b5	,0x03ca	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA
/*GREEK              */	DEADTRANS(	0x03cc	,0x03b5	,0x03cc	,CHAIN	), // GREEK SMALL LETTER OMICRON WITH TONOS
/*GREEK              */	DEADTRANS(	0x1fe0	,0x03b5	,0x1fe0	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH VRACHY
/*GREEK              */	DEADTRANS(	0x1f51	,0x03b5	,0x1f51	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA
/*GREEK              */	DEADTRANS(	0x1f7d	,0x03b5	,0x1f7d	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH OXIA
/*GREEK_LOCK         */	DEADTRANS(	L'A'	,0x0395	,0x0391	,CHAIN	), // GREEK CAPITAL LETTER ALPHA
/*GREEK_LOCK         */	DEADTRANS(	L'a'	,0x0395	,0x03b1	,CHAIN	), // GREEK SMALL LETTER ALPHA
/*GREEK_LOCK         */	DEADTRANS(	L'B'	,0x0395	,0x0392	,CHAIN	), // GREEK CAPITAL LETTER BETA
/*GREEK_LOCK         */	DEADTRANS(	L'b'	,0x0395	,0x03b2	,CHAIN	), // GREEK SMALL LETTER BETA
/*GREEK_LOCK         */	DEADTRANS(	L'C'	,0x0395	,0x03a8	,CHAIN	), // GREEK CAPITAL LETTER PSI
/*GREEK_LOCK         */	DEADTRANS(	L'c'	,0x0395	,0x03c8	,CHAIN	), // GREEK SMALL LETTER PSI
/*GREEK_LOCK         */	DEADTRANS(	L'D'	,0x0395	,0x0394	,CHAIN	), // GREEK CAPITAL LETTER DELTA
/*GREEK_LOCK         */	DEADTRANS(	L'd'	,0x0395	,0x03b4	,CHAIN	), // GREEK SMALL LETTER DELTA
/*GREEK_LOCK         */	DEADTRANS(	L'E'	,0x0395	,0x0395	,CHAIN	), // GREEK CAPITAL LETTER EPSILON
/*GREEK_LOCK         */	DEADTRANS(	L'e'	,0x0395	,0x03b5	,CHAIN	), // GREEK SMALL LETTER EPSILON
/*GREEK_LOCK         */	DEADTRANS(	L'F'	,0x0395	,0x03a6	,CHAIN	), // GREEK CAPITAL LETTER PHI
/*GREEK_LOCK         */	DEADTRANS(	L'f'	,0x0395	,0x03c6	,CHAIN	), // GREEK SMALL LETTER PHI
/*GREEK_LOCK         */	DEADTRANS(	L'G'	,0x0395	,0x0393	,CHAIN	), // GREEK CAPITAL LETTER GAMMA
/*GREEK_LOCK         */	DEADTRANS(	L'g'	,0x0395	,0x03b3	,CHAIN	), // GREEK SMALL LETTER GAMMA
/*GREEK_LOCK         */	DEADTRANS(	L'H'	,0x0395	,0x0397	,CHAIN	), // GREEK CAPITAL LETTER ETA
/*GREEK_LOCK         */	DEADTRANS(	L'h'	,0x0395	,0x03b7	,CHAIN	), // GREEK SMALL LETTER ETA
/*GREEK_LOCK         */	DEADTRANS(	L'I'	,0x0395	,0x0399	,CHAIN	), // GREEK CAPITAL LETTER IOTA
/*GREEK_LOCK         */	DEADTRANS(	L'i'	,0x0395	,0x03b9	,CHAIN	), // GREEK SMALL LETTER IOTA
/*GREEK_LOCK         */	DEADTRANS(	L'J'	,0x0395	,0x039e	,CHAIN	), // GREEK CAPITAL LETTER XI
/*GREEK_LOCK         */	DEADTRANS(	L'j'	,0x0395	,0x03be	,CHAIN	), // GREEK SMALL LETTER XI
/*GREEK_LOCK         */	DEADTRANS(	L'K'	,0x0395	,0x039a	,CHAIN	), // GREEK CAPITAL LETTER KAPPA
/*GREEK_LOCK         */	DEADTRANS(	L'k'	,0x0395	,0x03ba	,CHAIN	), // GREEK SMALL LETTER KAPPA
/*GREEK_LOCK         */	DEADTRANS(	L'L'	,0x0395	,0x039b	,CHAIN	), // GREEK CAPITAL LETTER LAMDA
/*GREEK_LOCK         */	DEADTRANS(	L'l'	,0x0395	,0x03bb	,CHAIN	), // GREEK SMALL LETTER LAMDA
/*GREEK_LOCK         */	DEADTRANS(	L'M'	,0x0395	,0x039c	,CHAIN	), // GREEK CAPITAL LETTER MU
/*GREEK_LOCK         */	DEADTRANS(	L'm'	,0x0395	,0x03bc	,CHAIN	), // GREEK SMALL LETTER MU
/*GREEK_LOCK         */	DEADTRANS(	L'N'	,0x0395	,0x039d	,CHAIN	), // GREEK CAPITAL LETTER NU
/*GREEK_LOCK         */	DEADTRANS(	L'n'	,0x0395	,0x03bd	,CHAIN	), // GREEK SMALL LETTER NU
/*GREEK_LOCK         */	DEADTRANS(	L'O'	,0x0395	,0x039f	,CHAIN	), // GREEK CAPITAL LETTER OMICRON
/*GREEK_LOCK         */	DEADTRANS(	L'o'	,0x0395	,0x03bf	,CHAIN	), // GREEK SMALL LETTER OMICRON
/*GREEK_LOCK         */	DEADTRANS(	L'P'	,0x0395	,0x03a0	,CHAIN	), // GREEK CAPITAL LETTER PI
/*GREEK_LOCK         */	DEADTRANS(	L'p'	,0x0395	,0x03c0	,CHAIN	), // GREEK SMALL LETTER PI
/*GREEK_LOCK         */	DEADTRANS(	L'Q'	,0x0395	,0x2211	,CHAIN	), // N-ARY SUMMATION
/*GREEK_LOCK         */	DEADTRANS(	L'q'	,0x0395	,0x03c2	,CHAIN	), // GREEK SMALL LETTER FINAL SIGMA
/*GREEK_LOCK         */	DEADTRANS(	L'R'	,0x0395	,0x03a1	,CHAIN	), // GREEK CAPITAL LETTER RHO
/*GREEK_LOCK         */	DEADTRANS(	L'r'	,0x0395	,0x03c1	,CHAIN	), // GREEK SMALL LETTER RHO
/*GREEK_LOCK         */	DEADTRANS(	L'S'	,0x0395	,0x03a3	,CHAIN	), // GREEK CAPITAL LETTER SIGMA
/*GREEK_LOCK         */	DEADTRANS(	L's'	,0x0395	,0x03c3	,CHAIN	), // GREEK SMALL LETTER SIGMA
/*GREEK_LOCK         */	DEADTRANS(	L'T'	,0x0395	,0x03a4	,CHAIN	), // GREEK CAPITAL LETTER TAU
/*GREEK_LOCK         */	DEADTRANS(	L't'	,0x0395	,0x03c4	,CHAIN	), // GREEK SMALL LETTER TAU
/*GREEK_LOCK         */	DEADTRANS(	L'U'	,0x0395	,0x0398	,CHAIN	), // GREEK CAPITAL LETTER THETA
/*GREEK_LOCK         */	DEADTRANS(	L'u'	,0x0395	,0x03b8	,CHAIN	), // GREEK SMALL LETTER THETA
/*GREEK_LOCK         */	DEADTRANS(	L'V'	,0x0395	,0x03a9	,CHAIN	), // GREEK CAPITAL LETTER OMEGA
/*GREEK_LOCK         */	DEADTRANS(	L'v'	,0x0395	,0x03c9	,CHAIN	), // GREEK SMALL LETTER OMEGA
/*GREEK_LOCK         */	DEADTRANS(	L'W'	,0x0395	,0x03a9	,CHAIN	), // GREEK CAPITAL LETTER OMEGA
/*GREEK_LOCK         */	DEADTRANS(	L'w'	,0x0395	,0x03c9	,CHAIN	), // GREEK SMALL LETTER OMEGA
/*GREEK_LOCK         */	DEADTRANS(	L'X'	,0x0395	,0x03a7	,CHAIN	), // GREEK CAPITAL LETTER CHI
/*GREEK_LOCK         */	DEADTRANS(	L'x'	,0x0395	,0x03c7	,CHAIN	), // GREEK SMALL LETTER CHI
/*GREEK_LOCK         */	DEADTRANS(	L'Y'	,0x0395	,0x03a5	,CHAIN	), // GREEK CAPITAL LETTER UPSILON
/*GREEK_LOCK         */	DEADTRANS(	L'y'	,0x0395	,0x03c5	,CHAIN	), // GREEK SMALL LETTER UPSILON
/*GREEK_LOCK         */	DEADTRANS(	L'Z'	,0x0395	,0x0396	,CHAIN	), // GREEK CAPITAL LETTER ZETA
/*GREEK_LOCK         */	DEADTRANS(	L'z'	,0x0395	,0x03b6	,CHAIN	), // GREEK SMALL LETTER ZETA
/*GREEK_LOCK         */	DEADTRANS(	0x0029	,0x0395	,0x1fe0	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH VRACHY
/*GREEK_LOCK         */	DEADTRANS(	0x002c	,0x0395	,0x1f7d	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH OXIA
/*GREEK_LOCK         */	DEADTRANS(	0x003a	,0x0395	,0x03ca	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA
/*GREEK_LOCK         */	DEADTRANS(	0x003b	,0x0395	,0x1fc3	,CHAIN	), // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI
/*GREEK_LOCK         */	DEADTRANS(	0x003c	,0x0395	,0x1f51	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA
/*GREEK_LOCK         */	DEADTRANS(	0x003e	,0x0395	,0x1f10	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI
/*GREEK_LOCK         */	DEADTRANS(	0x005f	,0x0395	,0x1fb1	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH MACRON
/*GREEK_LOCK         */	DEADTRANS(	0x0060	,0x0395	,0x1f70	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH VARIA
/*GREEK_LOCK         */	DEADTRANS(	0x007e	,0x0395	,0x1fc6	,CHAIN	), // GREEK SMALL LETTER ETA WITH PERISPOMENI
/*GREEK_LOCK         */	DEADTRANS(	0x00b5	,0x0395	,0x0448	,CHAIN	), // CYRILLIC SMALL LETTER SHA
/*GREEK_LOCK         */	DEADTRANS(	0x1f70	,0x0395	,0x1f70	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH VARIA
/*GREEK_LOCK         */	DEADTRANS(	0x1fb1	,0x0395	,0x1fb1	,CHAIN	), // GREEK SMALL LETTER ALPHA WITH MACRON
/*GREEK_LOCK         */	DEADTRANS(	0x1f10	,0x0395	,0x1f10	,CHAIN	), // GREEK SMALL LETTER EPSILON WITH PSILI
/*GREEK_LOCK         */	DEADTRANS(	0x1fc6	,0x0395	,0x1fc6	,CHAIN	), // GREEK SMALL LETTER ETA WITH PERISPOMENI
/*GREEK_LOCK         */	DEADTRANS(	0x1fc3	,0x0395	,0x1fc3	,CHAIN	), // GREEK SMALL LETTER ETA WITH YPOGEGRAMMENI
/*GREEK_LOCK         */	DEADTRANS(	0x03ca	,0x0395	,0x03ca	,CHAIN	), // GREEK SMALL LETTER IOTA WITH DIALYTIKA
/*GREEK_LOCK         */	DEADTRANS(	0x03cc	,0x0395	,0x03cc	,CHAIN	), // GREEK SMALL LETTER OMICRON WITH TONOS
/*GREEK_LOCK         */	DEADTRANS(	0x1fe0	,0x0395	,0x1fe0	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH VRACHY
/*GREEK_LOCK         */	DEADTRANS(	0x1f51	,0x0395	,0x1f51	,CHAIN	), // GREEK SMALL LETTER UPSILON WITH DASIA
/*GREEK_LOCK         */	DEADTRANS(	0x1f7d	,0x0395	,0x1f7d	,CHAIN	), // GREEK SMALL LETTER OMEGA WITH OXIA
/*GROUP_02           */	DEADTRANS(	L'A'	,0x00b2	,0x00c6	,DKF_0	), // LATIN CAPITAL LETTER AE
/*GROUP_02           */	DEADTRANS(	L'a'	,0x00b2	,0x00e6	,DKF_0	), // LATIN SMALL LETTER AE
/*GROUP_02           */	DEADTRANS(	L'B'	,0x00b2	,0x021c	,DKF_0	), // LATIN CAPITAL LETTER YOGH
/*GROUP_02           */	DEADTRANS(	L'b'	,0x00b2	,0x021d	,DKF_0	), // LATIN SMALL LETTER YOGH
/*GROUP_02           */	DEADTRANS(	L'C'	,0x00b2	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*GROUP_02           */	DEADTRANS(	L'c'	,0x00b2	,0x0254	,DKF_0	), // LATIN SMALL LETTER OPEN O
/*GROUP_02           */	DEADTRANS(	L'D'	,0x00b2	,0x00d0	,DKF_0	), // LATIN CAPITAL LETTER ETH
/*GROUP_02           */	DEADTRANS(	L'd'	,0x00b2	,0x00f0	,DKF_0	), // LATIN SMALL LETTER ETH
/*GROUP_02           */	DEADTRANS(	L'E'	,0x00b2	,0x018e	,DKF_0	), // LATIN CAPITAL LETTER REVERSED E
/*GROUP_02           */	DEADTRANS(	L'e'	,0x00b2	,0x01dd	,DKF_0	), // LATIN SMALL LETTER TURNED E
/*GROUP_02           */	DEADTRANS(	L'F'	,0x00b2	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*GROUP_02           */	DEADTRANS(	L'f'	,0x00b2	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*GROUP_02           */	DEADTRANS(	L'G'	,0x00b2	,0x014a	,DKF_0	), // LATIN CAPITAL LETTER ENG
/*GROUP_02           */	DEADTRANS(	L'g'	,0x00b2	,0x014b	,DKF_0	), // LATIN SMALL LETTER ENG
/*GROUP_02           */	DEADTRANS(	L'H'	,0x00b2	,0x0398	,DKF_0	), // GREEK CAPITAL LETTER THETA
/*GROUP_02           */	DEADTRANS(	L'h'	,0x00b2	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*GROUP_02           */	DEADTRANS(	L'I'	,0x00b2	,0x0196	,DKF_0	), // LATIN CAPITAL LETTER IOTA
/*GROUP_02           */	DEADTRANS(	L'i'	,0x00b2	,0x0269	,DKF_0	), // LATIN SMALL LETTER IOTA
/*GROUP_02           */	DEADTRANS(	L'J'	,0x00b2	,0x0132	,DKF_0	), // LATIN CAPITAL LIGATURE IJ
/*GROUP_02           */	DEADTRANS(	L'j'	,0x00b2	,0x0133	,DKF_0	), // LATIN SMALL LIGATURE IJ
/*GROUP_02           */	DEADTRANS(	L'K'	,0x00b2	,0x004b	,DKF_0	), // LATIN CAPITAL LETTER K
/*GROUP_02           */	DEADTRANS(	L'k'	,0x00b2	,0x0138	,DKF_0	), // LATIN SMALL LETTER KRA
/*GROUP_02           */	DEADTRANS(	L'L'	,0x00b2	,0x013f	,DKF_0	), // LATIN CAPITAL LETTER L WITH MIDDLE DOT
/*GROUP_02           */	DEADTRANS(	L'l'	,0x00b2	,0x0140	,DKF_0	), // LATIN SMALL LETTER L WITH MIDDLE DOT
/*GROUP_02           */	DEADTRANS(	L'M'	,0x00b2	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*GROUP_02           */	DEADTRANS(	L'm'	,0x00b2	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*GROUP_02           */	DEADTRANS(	L'N'	,0x00b2	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*GROUP_02           */	DEADTRANS(	L'n'	,0x00b2	,0x0272	,DKF_0	), // LATIN SMALL LETTER N WITH LEFT HOOK
/*GROUP_02           */	DEADTRANS(	L'O'	,0x00b2	,0x0152	,DKF_0	), // LATIN CAPITAL LIGATURE OE
/*GROUP_02           */	DEADTRANS(	L'o'	,0x00b2	,0x0153	,DKF_0	), // LATIN SMALL LIGATURE OE
/*GROUP_02           */	DEADTRANS(	L'P'	,0x00b2	,0xa7ae	,DKF_0	), // LATIN CAPITAL LETTER SMALL CAPITAL I
/*GROUP_02           */	DEADTRANS(	L'p'	,0x00b2	,0x026a	,DKF_0	), // LATIN LETTER SMALL CAPITAL I
/*GROUP_02           */	DEADTRANS(	L'Q'	,0x00b2	,0x0241	,DKF_0	), // LATIN CAPITAL LETTER GLOTTAL STOP
/*GROUP_02           */	DEADTRANS(	L'q'	,0x00b2	,0x0242	,DKF_0	), // LATIN SMALL LETTER GLOTTAL STOP
/*GROUP_02           */	DEADTRANS(	L'R'	,0x00b2	,0xa78b	,DKF_0	), // LATIN CAPITAL LETTER SALTILLO
/*GROUP_02           */	DEADTRANS(	L'r'	,0x00b2	,0xa78c	,DKF_0	), // LATIN SMALL LETTER SALTILLO
/*GROUP_02           */	DEADTRANS(	L'S'	,0x00b2	,0x1e9e	,DKF_0	), // LATIN CAPITAL LETTER SHARP S
/*GROUP_02           */	DEADTRANS(	L's'	,0x00b2	,0x00df	,DKF_0	), // LATIN SMALL LETTER SHARP S
/*GROUP_02           */	DEADTRANS(	L'T'	,0x00b2	,0x00de	,DKF_0	), // LATIN CAPITAL LETTER THORN
/*GROUP_02           */	DEADTRANS(	L't'	,0x00b2	,0x00fe	,DKF_0	), // LATIN SMALL LETTER THORN
/*GROUP_02           */	DEADTRANS(	L'U'	,0x00b2	,0x00dc	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS
/*GROUP_02           */	DEADTRANS(	L'u'	,0x00b2	,0x00fc	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS
/*GROUP_02           */	DEADTRANS(	L'V'	,0x00b2	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*GROUP_02           */	DEADTRANS(	L'v'	,0x00b2	,0x028c	,DKF_0	), // LATIN SMALL LETTER TURNED V
/*GROUP_02           */	DEADTRANS(	L'W'	,0x00b2	,0x018f	,DKF_0	), // LATIN CAPITAL LETTER SCHWA
/*GROUP_02           */	DEADTRANS(	L'w'	,0x00b2	,0x0259	,DKF_0	), // LATIN SMALL LETTER SCHWA
/*GROUP_02           */	DEADTRANS(	L'X'	,0x00b2	,0x0190	,DKF_0	), // LATIN CAPITAL LETTER OPEN E
/*GROUP_02           */	DEADTRANS(	L'x'	,0x00b2	,0x025b	,DKF_0	), // LATIN SMALL LETTER OPEN E
/*GROUP_02           */	DEADTRANS(	L'Y'	,0x00b2	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*GROUP_02           */	DEADTRANS(	L'y'	,0x00b2	,0x0272	,DKF_0	), // LATIN SMALL LETTER N WITH LEFT HOOK
/*GROUP_02           */	DEADTRANS(	L'Z'	,0x00b2	,0x01b7	,DKF_0	), // LATIN CAPITAL LETTER EZH
/*GROUP_02           */	DEADTRANS(	L'z'	,0x00b2	,0x0292	,DKF_0	), // LATIN SMALL LETTER EZH
/*GROUP_02           */	DEADTRANS(	L'0'	,0x00b2	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_02           */	DEADTRANS(	L'1'	,0x00b2	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_02           */	DEADTRANS(	L'2'	,0x00b2	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_02           */	DEADTRANS(	L'3'	,0x00b2	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_02           */	DEADTRANS(	L'4'	,0x00b2	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_02           */	DEADTRANS(	L'5'	,0x00b2	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_02           */	DEADTRANS(	L'6'	,0x00b2	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_02           */	DEADTRANS(	L'7'	,0x00b2	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_02           */	DEADTRANS(	L'8'	,0x00b2	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_02           */	DEADTRANS(	L'9'	,0x00b2	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_02           */	DEADTRANS(	0x0020	,0x00b2	,0x0032	,DKF_0	), // DIGIT TWO
/*GROUP_02           */	DEADTRANS(	0x0023	,0x00b2	,0x024d	,CHAIN	), // LATIN SMALL LETTER R WITH STROKE
/*GROUP_02           */	DEADTRANS(	0x0024	,0x00b2	,0x00e5	,CHAIN	), // LATIN SMALL LETTER A WITH RING ABOVE
/*GROUP_02           */	DEADTRANS(	0x0025	,0x00b2	,0x00f8	,CHAIN	), // LATIN SMALL LETTER O WITH STROKE
/*GROUP_02           */	DEADTRANS(	0x0026	,0x00b2	,0x022f	,CHAIN	), // LATIN SMALL LETTER O WITH DOT ABOVE
/*GROUP_02           */	DEADTRANS(	0x0028	,0x00b2	,0x00ab	,DKF_0	), // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
/*GROUP_02           */	DEADTRANS(	0x0029	,0x00b2	,0x00bb	,DKF_0	), // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
/*GROUP_02           */	DEADTRANS(	0x002b	,0x00b2	,0x2248	,DKF_0	), // ALMOST EQUAL TO
/*GROUP_02           */	DEADTRANS(	0x002f	,0x00b2	,0x0229	,CHAIN	), // LATIN SMALL LETTER E WITH CEDILLA
/*GROUP_02           */	DEADTRANS(	0x003c	,0x00b2	,0x2039	,DKF_0	), // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
/*GROUP_02           */	DEADTRANS(	0x003d	,0x00b2	,0x2243	,DKF_0	), // ASYMPTOTICALLY EQUAL TO
/*GROUP_02           */	DEADTRANS(	0x003e	,0x00b2	,0x203a	,DKF_0	), // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
/*GROUP_02           */	DEADTRANS(	0x0040	,0x00b2	,0x00e1	,CHAIN	), // LATIN SMALL LETTER A WITH ACUTE
/*GROUP_02           */	DEADTRANS(	0x005b	,0x00b2	,0x01b0	,CHAIN	), // LATIN SMALL LETTER U WITH HORN
/*GROUP_02           */	DEADTRANS(	0x005c	,0x00b2	,0x0219	,CHAIN	), // LATIN SMALL LETTER S WITH COMMA BELOW
/*GROUP_02           */	DEADTRANS(	0x005d	,0x00b2	,0x01eb	,CHAIN	), // LATIN SMALL LETTER O WITH OGONEK
/*GROUP_02           */	DEADTRANS(	0x005e	,0x00b2	,0x00ea	,CHAIN	), // LATIN SMALL LETTER E WITH CIRCUMFLEX
/*GROUP_02           */	DEADTRANS(	0x007b	,0x00b2	,0x03a9	,CHAIN	), // GREEK CAPITAL LETTER OMEGA
/*GROUP_02           */	DEADTRANS(	0x007c	,0x00b2	,0x014f	,CHAIN	), // LATIN SMALL LETTER O WITH BREVE
/*GROUP_02           */	DEADTRANS(	0x007d	,0x00b2	,0x021f	,CHAIN	), // LATIN SMALL LETTER H WITH CARON
/*GROUP_02           */	DEADTRANS(	0x007e	,0x00b2	,0x00f5	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE
/*GROUP_02           */	DEADTRANS(	0x20ac	,0x00b2	,0x005e	,CHAIN	), // CIRCUMFLEX ACCENT
/*GROUP_02           */	DEADTRANS(	0x00a3	,0x00b2	,0x005f	,CHAIN	), // LOW LINE
/*GROUP_02           */	DEADTRANS(	0x00a4	,0x00b2	,0x0032	,DKF_0	), // DIGIT TWO
/*GROUP_02           */	DEADTRANS(	0x00a5	,0x00b2	,0x00eb	,CHAIN	), // LATIN SMALL LETTER E WITH DIAERESIS
/*GROUP_02           */	DEADTRANS(	0x00a9	,0x00b2	,0x0032	,DKF_0	), // DIGIT TWO
/*GROUP_02           */	DEADTRANS(	0x00b2	,0x00b2	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_02           */	DEADTRANS(	0x00b5	,0x00b2	,0x0032	,DKF_0	), // DIGIT TWO
/*GROUP_02           */	DEADTRANS(	0x02bc	,0x00b2	,0x014d	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON
/*GROUP_02           */	DEADTRANS(	0x222a	,0x00b2	,0x1ee5	,CHAIN	), // LATIN SMALL LETTER U WITH DOT BELOW
/*GROUP_03           */	DEADTRANS(	L'A'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'a'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'B'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'b'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'C'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'c'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'D'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'd'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'E'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'e'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'F'	,0x00b3	,0x01a9	,DKF_0	), // LATIN CAPITAL LETTER ESH
/*GROUP_03           */	DEADTRANS(	L'f'	,0x00b3	,0x0283	,DKF_0	), // LATIN SMALL LETTER ESH
/*GROUP_03           */	DEADTRANS(	L'G'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'g'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'H'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'h'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'I'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'i'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'J'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'j'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'K'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'k'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'L'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'l'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'M'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'm'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'N'	,0x00b3	,0x0220	,DKF_0	), // LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
/*GROUP_03           */	DEADTRANS(	L'n'	,0x00b3	,0x019e	,DKF_0	), // LATIN SMALL LETTER N WITH LONG RIGHT LEG
/*GROUP_03           */	DEADTRANS(	L'O'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'o'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'P'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'p'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'Q'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'q'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'R'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'r'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'S'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L's'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'T'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L't'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'U'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'u'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'V'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'v'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'W'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'w'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'X'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'x'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'Y'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'y'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'Z'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'z'	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	L'0'	,0x00b3	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_03           */	DEADTRANS(	L'1'	,0x00b3	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_03           */	DEADTRANS(	L'2'	,0x00b3	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_03           */	DEADTRANS(	L'3'	,0x00b3	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_03           */	DEADTRANS(	L'4'	,0x00b3	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_03           */	DEADTRANS(	L'5'	,0x00b3	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_03           */	DEADTRANS(	L'6'	,0x00b3	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_03           */	DEADTRANS(	L'7'	,0x00b3	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_03           */	DEADTRANS(	L'8'	,0x00b3	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_03           */	DEADTRANS(	L'9'	,0x00b3	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_03           */	DEADTRANS(	0x0020	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0023	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0024	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0025	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0026	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0028	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0029	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x002b	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x002f	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x003c	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x003d	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x003e	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0040	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x005b	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x005c	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x005d	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x005e	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x0060	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x007b	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x007c	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x007d	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x007e	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x20ac	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x00a3	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x00a4	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x00a5	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x00a9	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x00b2	,0x00b3	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_03           */	DEADTRANS(	0x00b5	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x02bc	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_03           */	DEADTRANS(	0x222a	,0x00b3	,0x0033	,DKF_0	), // DIGIT THREE
/*GROUP_04           */	DEADTRANS(	0x0020	,0x2074	,0x00a0	,DKF_0	), // NO-BREAK SPACE
/*GROUP_04           */	DEADTRANS(	0x00a9	,0x2074	,0x00a0	,DKF_0	), // NO-BREAK SPACE
/*GROUP_04           */	DEADTRANS(	L'A'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'a'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'B'	,0x2074	,0x0181	,DKF_0	), // LATIN CAPITAL LETTER B WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'b'	,0x2074	,0x0253	,DKF_0	), // LATIN SMALL LETTER B WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'C'	,0x2074	,0x0187	,DKF_0	), // LATIN CAPITAL LETTER C WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'c'	,0x2074	,0x0188	,DKF_0	), // LATIN SMALL LETTER C WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'D'	,0x2074	,0x0189	,DKF_0	), // LATIN CAPITAL LETTER AFRICAN D
/*GROUP_04           */	DEADTRANS(	L'd'	,0x2074	,0x0256	,DKF_0	), // LATIN SMALL LETTER D WITH TAIL
/*GROUP_04           */	DEADTRANS(	L'E'	,0x2074	,0x018e	,DKF_0	), // LATIN CAPITAL LETTER REVERSED E
/*GROUP_04           */	DEADTRANS(	L'e'	,0x2074	,0x01dd	,DKF_0	), // LATIN SMALL LETTER TURNED E
/*GROUP_04           */	DEADTRANS(	L'F'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'f'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'G'	,0x2074	,0x0194	,DKF_0	), // LATIN CAPITAL LETTER GAMMA
/*GROUP_04           */	DEADTRANS(	L'g'	,0x2074	,0x0263	,DKF_0	), // LATIN SMALL LETTER GAMMA
/*GROUP_04           */	DEADTRANS(	L'H'	,0x2074	,0xa78d	,DKF_0	), // LATIN CAPITAL LETTER TURNED H
/*GROUP_04           */	DEADTRANS(	L'h'	,0x2074	,0x0265	,DKF_0	), // LATIN SMALL LETTER TURNED H
/*GROUP_04           */	DEADTRANS(	L'I'	,0x2074	,0x0130	,DKF_0	), // LATIN CAPITAL LETTER I WITH DOT ABOVE
/*GROUP_04           */	DEADTRANS(	L'i'	,0x2074	,0x0131	,DKF_0	), // LATIN SMALL LETTER DOTLESS I
/*GROUP_04           */	DEADTRANS(	L'J'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'j'	,0x2074	,0x0237	,DKF_0	), // LATIN SMALL LETTER DOTLESS J
/*GROUP_04           */	DEADTRANS(	L'K'	,0x2074	,0x0198	,DKF_0	), // LATIN CAPITAL LETTER K WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'k'	,0x2074	,0x0199	,DKF_0	), // LATIN SMALL LETTER K WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'L'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'l'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'M'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'm'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'N'	,0x2074	,0x0220	,DKF_0	), // LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
/*GROUP_04           */	DEADTRANS(	L'n'	,0x2074	,0x019e	,DKF_0	), // LATIN SMALL LETTER N WITH LONG RIGHT LEG
/*GROUP_04           */	DEADTRANS(	L'O'	,0x2074	,0x0222	,DKF_0	), // LATIN CAPITAL LETTER OU
/*GROUP_04           */	DEADTRANS(	L'o'	,0x2074	,0x0223	,DKF_0	), // LATIN SMALL LETTER OU
/*GROUP_04           */	DEADTRANS(	L'P'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'p'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'Q'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'q'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'R'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'r'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'S'	,0x2074	,0xa78b	,DKF_0	), // LATIN CAPITAL LETTER SALTILLO
/*GROUP_04           */	DEADTRANS(	L's'	,0x2074	,0xa78c	,DKF_0	), // LATIN SMALL LETTER SALTILLO
/*GROUP_04           */	DEADTRANS(	L'T'	,0x2074	,0x03f4	,DKF_0	), // GREEK CAPITAL THETA SYMBOL
/*GROUP_04           */	DEADTRANS(	L't'	,0x2074	,0x03b8	,DKF_0	), // GREEK SMALL LETTER THETA
/*GROUP_04           */	DEADTRANS(	L'U'	,0x2074	,0x0244	,DKF_0	), // LATIN CAPITAL LETTER U BAR
/*GROUP_04           */	DEADTRANS(	L'u'	,0x2074	,0x0289	,DKF_0	), // LATIN SMALL LETTER U BAR
/*GROUP_04           */	DEADTRANS(	L'V'	,0x2074	,0x01b2	,DKF_0	), // LATIN CAPITAL LETTER V WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'v'	,0x2074	,0x028b	,DKF_0	), // LATIN SMALL LETTER V WITH HOOK
/*GROUP_04           */	DEADTRANS(	L'W'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'w'	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	L'X'	,0x2074	,0x2714	,DKF_0	), // HEAVY CHECK MARK
/*GROUP_04           */	DEADTRANS(	L'x'	,0x2074	,0x2713	,DKF_0	), // CHECK MARK
/*GROUP_04           */	DEADTRANS(	L'Y'	,0x2074	,0x01b1	,DKF_0	), // LATIN CAPITAL LETTER UPSILON
/*GROUP_04           */	DEADTRANS(	L'y'	,0x2074	,0x028a	,DKF_0	), // LATIN SMALL LETTER UPSILON
/*GROUP_04           */	DEADTRANS(	L'Z'	,0x2074	,0x01ee	,DKF_0	), // LATIN CAPITAL LETTER EZH WITH CARON
/*GROUP_04           */	DEADTRANS(	L'z'	,0x2074	,0x01ef	,DKF_0	), // LATIN SMALL LETTER EZH WITH CARON
/*GROUP_04           */	DEADTRANS(	L'0'	,0x2074	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_04           */	DEADTRANS(	L'1'	,0x2074	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_04           */	DEADTRANS(	L'2'	,0x2074	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_04           */	DEADTRANS(	L'3'	,0x2074	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_04           */	DEADTRANS(	L'4'	,0x2074	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_04           */	DEADTRANS(	L'5'	,0x2074	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_04           */	DEADTRANS(	L'6'	,0x2074	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_04           */	DEADTRANS(	L'7'	,0x2074	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_04           */	DEADTRANS(	L'8'	,0x2074	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_04           */	DEADTRANS(	L'9'	,0x2074	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_04           */	DEADTRANS(	0x0023	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x0024	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x0025	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x0026	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x0028	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x0029	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x002b	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x002f	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x003c	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x003d	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x003e	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x0040	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x005b	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x005c	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x005d	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x005e	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x0060	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x007b	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x007c	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x007d	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x007e	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x20ac	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x00a3	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x00a4	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x00a5	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x00b2	,0x2074	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_04           */	DEADTRANS(	0x00b5	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x02bc	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_04           */	DEADTRANS(	0x222a	,0x2074	,0x0034	,DKF_0	), // DIGIT FOUR
/*GROUP_05           */	DEADTRANS(	L'A'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'a'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'B'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'b'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'C'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'c'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'D'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'd'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'E'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'e'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'F'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'f'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'G'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'g'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'H'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'h'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'I'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'i'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'J'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'j'	,0x2075	,0x025f	,DKF_0	), // LATIN SMALL LETTER DOTLESS J WITH STROKE
/*GROUP_05           */	DEADTRANS(	L'K'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'k'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'L'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'l'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'M'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'm'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'N'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'n'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'O'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'o'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'P'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'p'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'Q'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'q'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'R'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'r'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'S'	,0x2075	,0x222c	,DKF_0	), // DOUBLE INTEGRAL
/*GROUP_05           */	DEADTRANS(	L's'	,0x2075	,0x222b	,DKF_0	), // INTEGRAL
/*GROUP_05           */	DEADTRANS(	L'T'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L't'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'U'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'u'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'V'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'v'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'W'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'w'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'X'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'x'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'Y'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'y'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'Z'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'z'	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	L'0'	,0x2075	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_05           */	DEADTRANS(	L'1'	,0x2075	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_05           */	DEADTRANS(	L'2'	,0x2075	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_05           */	DEADTRANS(	L'3'	,0x2075	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_05           */	DEADTRANS(	L'4'	,0x2075	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_05           */	DEADTRANS(	L'5'	,0x2075	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_05           */	DEADTRANS(	L'6'	,0x2075	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_05           */	DEADTRANS(	L'7'	,0x2075	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_05           */	DEADTRANS(	L'8'	,0x2075	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_05           */	DEADTRANS(	L'9'	,0x2075	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_05           */	DEADTRANS(	0x0020	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0023	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0024	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0025	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0026	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0028	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0029	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x002b	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x002f	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x003c	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x003d	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x003e	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0040	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x005b	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x005c	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x005d	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x005e	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x0060	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x007b	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x007c	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x007d	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x007e	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x20ac	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x00a3	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x00a4	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x00a5	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x00a9	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x00b2	,0x2075	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_05           */	DEADTRANS(	0x00b5	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x02bc	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_05           */	DEADTRANS(	0x222a	,0x2075	,0x0035	,DKF_0	), // DIGIT FIVE
/*GROUP_06           */	DEADTRANS(	L'A'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'a'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'B'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'b'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'C'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'c'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'D'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'd'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'E'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'e'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'F'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'f'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'G'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'g'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'H'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'h'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'I'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'i'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'J'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'j'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'K'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'k'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'L'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'l'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'M'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'm'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'N'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'n'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'O'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'o'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'P'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'p'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'Q'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'q'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'R'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'r'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'S'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L's'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'T'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L't'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'U'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'u'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'V'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'v'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'W'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'w'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'X'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'x'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'Y'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'y'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'Z'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'z'	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	L'0'	,0x2076	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_06           */	DEADTRANS(	L'1'	,0x2076	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_06           */	DEADTRANS(	L'2'	,0x2076	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_06           */	DEADTRANS(	L'3'	,0x2076	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_06           */	DEADTRANS(	L'4'	,0x2076	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_06           */	DEADTRANS(	L'5'	,0x2076	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_06           */	DEADTRANS(	L'6'	,0x2076	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_06           */	DEADTRANS(	L'7'	,0x2076	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_06           */	DEADTRANS(	L'8'	,0x2076	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_06           */	DEADTRANS(	L'9'	,0x2076	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_06           */	DEADTRANS(	0x0020	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0023	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0024	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0025	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0026	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0028	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0029	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x002b	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x002f	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x003c	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x003d	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x003e	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0040	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x005b	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x005c	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x005d	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x005e	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x0060	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x007b	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x007c	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x007d	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x007e	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x20ac	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x00a3	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x00a4	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x00a5	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x00a9	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x00b2	,0x2076	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_06           */	DEADTRANS(	0x00b5	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x02bc	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_06           */	DEADTRANS(	0x222a	,0x2076	,0x0036	,DKF_0	), // DIGIT SIX
/*GROUP_07           */	DEADTRANS(	L'A'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'a'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'B'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'b'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'C'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'c'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'D'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'd'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'E'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'e'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'F'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'f'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'G'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'g'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'H'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'h'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'I'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'i'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'J'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'j'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'K'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'k'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'L'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'l'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'M'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'm'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'N'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'n'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'O'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'o'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'P'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'p'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'Q'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'q'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'R'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'r'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'S'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L's'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'T'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L't'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'U'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'u'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'V'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'v'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'W'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'w'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'X'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'x'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'Y'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'y'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'Z'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'z'	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	L'0'	,0x2077	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_07           */	DEADTRANS(	L'1'	,0x2077	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_07           */	DEADTRANS(	L'2'	,0x2077	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_07           */	DEADTRANS(	L'3'	,0x2077	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_07           */	DEADTRANS(	L'4'	,0x2077	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_07           */	DEADTRANS(	L'5'	,0x2077	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_07           */	DEADTRANS(	L'6'	,0x2077	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_07           */	DEADTRANS(	L'7'	,0x2077	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_07           */	DEADTRANS(	L'8'	,0x2077	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_07           */	DEADTRANS(	L'9'	,0x2077	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_07           */	DEADTRANS(	0x0020	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0023	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0024	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0025	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0026	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0028	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0029	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x002b	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x002f	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x003c	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x003d	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x003e	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0040	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x005b	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x005c	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x005d	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x005e	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x0060	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x007b	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x007c	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x007d	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x007e	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x20ac	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x00a3	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x00a4	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x00a5	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x00a9	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x00b2	,0x2077	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_07           */	DEADTRANS(	0x00b5	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x02bc	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_07           */	DEADTRANS(	0x222a	,0x2077	,0x0037	,DKF_0	), // DIGIT SEVEN
/*GROUP_08           */	DEADTRANS(	L'A'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'a'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'B'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'b'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'C'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'c'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'D'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'd'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'E'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'e'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'F'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'f'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'G'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'g'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'H'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'h'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'I'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'i'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'J'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'j'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'K'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'k'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'L'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'l'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'M'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'm'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'N'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'n'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'O'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'o'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'P'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'p'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'Q'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'q'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'R'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'r'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'S'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L's'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'T'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L't'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'U'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'u'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'V'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'v'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'W'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'w'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'X'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'x'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'Y'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'y'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'Z'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'z'	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	L'0'	,0x2078	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_08           */	DEADTRANS(	L'1'	,0x2078	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_08           */	DEADTRANS(	L'2'	,0x2078	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_08           */	DEADTRANS(	L'3'	,0x2078	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_08           */	DEADTRANS(	L'4'	,0x2078	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_08           */	DEADTRANS(	L'5'	,0x2078	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_08           */	DEADTRANS(	L'6'	,0x2078	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_08           */	DEADTRANS(	L'7'	,0x2078	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_08           */	DEADTRANS(	L'8'	,0x2078	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_08           */	DEADTRANS(	L'9'	,0x2078	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_08           */	DEADTRANS(	0x0020	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0023	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0024	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0025	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0026	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0028	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0029	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x002b	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x002f	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x003c	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x003d	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x003e	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0040	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x005b	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x005c	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x005d	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x005e	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x0060	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x007b	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x007c	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x007d	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x007e	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x20ac	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x00a3	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x00a4	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x00a5	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x00a9	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x00b2	,0x2078	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_08           */	DEADTRANS(	0x00b5	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x02bc	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_08           */	DEADTRANS(	0x222a	,0x2078	,0x0038	,DKF_0	), // DIGIT EIGHT
/*GROUP_09           */	DEADTRANS(	L'A'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'a'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'B'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'b'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'C'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'c'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'D'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'd'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'E'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'e'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'F'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'f'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'G'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'g'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'H'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'h'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'I'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'i'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'J'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'j'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'K'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'k'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'L'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'l'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'M'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'm'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'N'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'n'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'O'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'o'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'P'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'p'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'Q'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'q'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'R'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'r'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'S'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L's'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'T'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L't'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'U'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'u'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'V'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'v'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'W'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'w'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'X'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'x'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'Y'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'y'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'Z'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'z'	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	L'0'	,0x2079	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_09           */	DEADTRANS(	L'1'	,0x2079	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_09           */	DEADTRANS(	L'2'	,0x2079	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_09           */	DEADTRANS(	L'3'	,0x2079	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_09           */	DEADTRANS(	L'4'	,0x2079	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_09           */	DEADTRANS(	L'5'	,0x2079	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_09           */	DEADTRANS(	L'6'	,0x2079	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_09           */	DEADTRANS(	L'7'	,0x2079	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_09           */	DEADTRANS(	L'8'	,0x2079	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_09           */	DEADTRANS(	L'9'	,0x2079	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_09           */	DEADTRANS(	0x0020	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0023	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0024	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0025	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0026	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0028	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0029	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x002b	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x002f	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x003c	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x003d	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x003e	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0040	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x005b	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x005c	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x005d	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x005e	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x0060	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x007b	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x007c	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x007d	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x007e	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x20ac	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x00a3	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x00a4	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x00a5	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x00a9	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x00b2	,0x2079	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_09           */	DEADTRANS(	0x00b5	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x02bc	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_09           */	DEADTRANS(	0x222a	,0x2079	,0x0039	,DKF_0	), // DIGIT NINE
/*GROUP_10           */	DEADTRANS(	L'A'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'a'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'B'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'b'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'C'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'c'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'D'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'd'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'E'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'e'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'F'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'f'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'G'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'g'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'H'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'h'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'I'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'i'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'J'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'j'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'K'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'k'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'L'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'l'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'M'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'm'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'N'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'n'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'O'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'o'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'P'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'p'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'Q'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'q'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'R'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'r'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'S'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L's'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'T'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L't'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'U'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'u'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'V'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'v'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'W'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'w'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'X'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'x'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'Y'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'y'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'Z'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'z'	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	L'0'	,0x2070	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_10           */	DEADTRANS(	L'1'	,0x2070	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_10           */	DEADTRANS(	L'2'	,0x2070	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_10           */	DEADTRANS(	L'3'	,0x2070	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_10           */	DEADTRANS(	L'4'	,0x2070	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_10           */	DEADTRANS(	L'5'	,0x2070	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_10           */	DEADTRANS(	L'6'	,0x2070	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_10           */	DEADTRANS(	L'7'	,0x2070	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_10           */	DEADTRANS(	L'8'	,0x2070	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_10           */	DEADTRANS(	L'9'	,0x2070	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_10           */	DEADTRANS(	0x0020	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0023	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0024	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0025	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0026	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0028	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0029	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x002b	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x002f	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x003c	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x003d	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x003e	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0040	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x005b	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x005c	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x005d	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x005e	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x0060	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x007b	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x007c	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x007d	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x007e	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x20ac	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x00a3	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x00a4	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x00a5	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x00a9	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x00b2	,0x2070	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_10           */	DEADTRANS(	0x00b5	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x02bc	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_10           */	DEADTRANS(	0x222a	,0x2070	,0x0030	,DKF_0	), // DIGIT ZERO
/*GROUP_11           */	DEADTRANS(	L'A'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'a'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'B'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'b'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'C'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'c'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'D'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'd'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'E'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'e'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'F'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'f'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'G'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'g'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'H'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'h'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'I'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'i'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'J'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'j'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'K'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'k'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'L'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'l'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'M'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'm'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'N'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'n'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'O'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'o'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'P'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'p'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'Q'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'q'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'R'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'r'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'S'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L's'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'T'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L't'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'U'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'u'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'V'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'v'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'W'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'w'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'X'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'x'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'Y'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'y'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'Z'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'z'	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	L'0'	,0x00b9	,0x2070	,CHAIN	), // SUPERSCRIPT ZERO
/*GROUP_11           */	DEADTRANS(	L'1'	,0x00b9	,0x00b9	,CHAIN	), // SUPERSCRIPT ONE
/*GROUP_11           */	DEADTRANS(	L'2'	,0x00b9	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_11           */	DEADTRANS(	L'3'	,0x00b9	,0x00b3	,CHAIN	), // SUPERSCRIPT THREE
/*GROUP_11           */	DEADTRANS(	L'4'	,0x00b9	,0x2074	,CHAIN	), // SUPERSCRIPT FOUR
/*GROUP_11           */	DEADTRANS(	L'5'	,0x00b9	,0x2075	,CHAIN	), // SUPERSCRIPT FIVE
/*GROUP_11           */	DEADTRANS(	L'6'	,0x00b9	,0x2076	,CHAIN	), // SUPERSCRIPT SIX
/*GROUP_11           */	DEADTRANS(	L'7'	,0x00b9	,0x2077	,CHAIN	), // SUPERSCRIPT SEVEN
/*GROUP_11           */	DEADTRANS(	L'8'	,0x00b9	,0x2078	,CHAIN	), // SUPERSCRIPT EIGHT
/*GROUP_11           */	DEADTRANS(	L'9'	,0x00b9	,0x2079	,CHAIN	), // SUPERSCRIPT NINE
/*GROUP_11           */	DEADTRANS(	0x0020	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0023	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0024	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0025	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0026	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0028	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0029	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x002b	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x002f	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x003c	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x003d	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x003e	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0040	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x005b	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x005c	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x005d	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x005e	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x0060	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x007b	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x007c	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x007d	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x007e	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x20ac	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x00a3	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x00a4	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x00a5	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x00a9	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x00b2	,0x00b9	,0x00b2	,CHAIN	), // SUPERSCRIPT TWO
/*GROUP_11           */	DEADTRANS(	0x00b5	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x02bc	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*GROUP_11           */	DEADTRANS(	0x222a	,0x00b9	,0x0031	,DKF_0	), // DIGIT ONE
/*HACEK              */	DEADTRANS(	0x0020	,0x021f	,0x030c	,DKF_0	), // COMBINING CARON
/*HACEK              */	DEADTRANS(	0x00a3	,0x021f	,0x032c	,DKF_0	), // COMBINING CARON BELOW
/*HACEK              */	DEADTRANS(	0x00a0	,0x021f	,0x02c7	,DKF_0	), // CARON
/*HACEK              */	DEADTRANS(	0x202f	,0x021f	,0x02c7	,DKF_0	), // CARON
/*HACEK              */	DEADTRANS(	0x00e1	,0x021f	,0x1dc9	,DKF_0	), // COMBINING ACUTE-GRAVE-ACUTE
/*HACEK              */	DEADTRANS(	L'A'	,0x021f	,0x01cd	,DKF_0	), // LATIN CAPITAL LETTER A WITH CARON
/*HACEK              */	DEADTRANS(	L'a'	,0x021f	,0x01ce	,DKF_0	), // LATIN SMALL LETTER A WITH CARON
/*HACEK              */	DEADTRANS(	L'C'	,0x021f	,0x010c	,DKF_0	), // LATIN CAPITAL LETTER C WITH CARON
/*HACEK              */	DEADTRANS(	L'c'	,0x021f	,0x010d	,DKF_0	), // LATIN SMALL LETTER C WITH CARON
/*HACEK              */	DEADTRANS(	L'D'	,0x021f	,0x010e	,DKF_0	), // LATIN CAPITAL LETTER D WITH CARON
/*HACEK              */	DEADTRANS(	L'd'	,0x021f	,0x010f	,DKF_0	), // LATIN SMALL LETTER D WITH CARON
/*HACEK              */	DEADTRANS(	L'E'	,0x021f	,0x011a	,DKF_0	), // LATIN CAPITAL LETTER E WITH CARON
/*HACEK              */	DEADTRANS(	L'e'	,0x021f	,0x011b	,DKF_0	), // LATIN SMALL LETTER E WITH CARON
/*HACEK              */	DEADTRANS(	L'F'	,0x021f	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*HACEK              */	DEADTRANS(	L'f'	,0x021f	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*HACEK              */	DEADTRANS(	L'G'	,0x021f	,0x01e6	,DKF_0	), // LATIN CAPITAL LETTER G WITH CARON
/*HACEK              */	DEADTRANS(	L'g'	,0x021f	,0x01e7	,DKF_0	), // LATIN SMALL LETTER G WITH CARON
/*HACEK              */	DEADTRANS(	L'H'	,0x021f	,0x021e	,DKF_0	), // LATIN CAPITAL LETTER H WITH CARON
/*HACEK              */	DEADTRANS(	L'h'	,0x021f	,0x021f	,DKF_0	), // LATIN SMALL LETTER H WITH CARON
/*HACEK              */	DEADTRANS(	L'I'	,0x021f	,0x01cf	,DKF_0	), // LATIN CAPITAL LETTER I WITH CARON
/*HACEK              */	DEADTRANS(	L'i'	,0x021f	,0x01d0	,DKF_0	), // LATIN SMALL LETTER I WITH CARON
/*HACEK              */	DEADTRANS(	L'j'	,0x021f	,0x01f0	,DKF_0	), // LATIN SMALL LETTER J WITH CARON
/*HACEK              */	DEADTRANS(	L'K'	,0x021f	,0x01e8	,DKF_0	), // LATIN CAPITAL LETTER K WITH CARON
/*HACEK              */	DEADTRANS(	L'k'	,0x021f	,0x01e9	,DKF_0	), // LATIN SMALL LETTER K WITH CARON
/*HACEK              */	DEADTRANS(	L'L'	,0x021f	,0x013d	,DKF_0	), // LATIN CAPITAL LETTER L WITH CARON
/*HACEK              */	DEADTRANS(	L'l'	,0x021f	,0x013e	,DKF_0	), // LATIN SMALL LETTER L WITH CARON
/*HACEK              */	DEADTRANS(	L'M'	,0x021f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*HACEK              */	DEADTRANS(	L'm'	,0x021f	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*HACEK              */	DEADTRANS(	L'N'	,0x021f	,0x0147	,DKF_0	), // LATIN CAPITAL LETTER N WITH CARON
/*HACEK              */	DEADTRANS(	L'n'	,0x021f	,0x0148	,DKF_0	), // LATIN SMALL LETTER N WITH CARON
/*HACEK              */	DEADTRANS(	L'O'	,0x021f	,0x01d1	,DKF_0	), // LATIN CAPITAL LETTER O WITH CARON
/*HACEK              */	DEADTRANS(	L'o'	,0x021f	,0x01d2	,DKF_0	), // LATIN SMALL LETTER O WITH CARON
/*HACEK              */	DEADTRANS(	L'R'	,0x021f	,0x0158	,DKF_0	), // LATIN CAPITAL LETTER R WITH CARON
/*HACEK              */	DEADTRANS(	L'r'	,0x021f	,0x0159	,DKF_0	), // LATIN SMALL LETTER R WITH CARON
/*HACEK              */	DEADTRANS(	L'S'	,0x021f	,0x0160	,DKF_0	), // LATIN CAPITAL LETTER S WITH CARON
/*HACEK              */	DEADTRANS(	L's'	,0x021f	,0x0161	,DKF_0	), // LATIN SMALL LETTER S WITH CARON
/*HACEK              */	DEADTRANS(	L'T'	,0x021f	,0x0164	,DKF_0	), // LATIN CAPITAL LETTER T WITH CARON
/*HACEK              */	DEADTRANS(	L't'	,0x021f	,0x0165	,DKF_0	), // LATIN SMALL LETTER T WITH CARON
/*HACEK              */	DEADTRANS(	L'U'	,0x021f	,0x01d3	,DKF_0	), // LATIN CAPITAL LETTER U WITH CARON
/*HACEK              */	DEADTRANS(	L'u'	,0x021f	,0x01d4	,DKF_0	), // LATIN SMALL LETTER U WITH CARON
/*HACEK              */	DEADTRANS(	L'Z'	,0x021f	,0x017d	,DKF_0	), // LATIN CAPITAL LETTER Z WITH CARON
/*HACEK              */	DEADTRANS(	L'z'	,0x021f	,0x017e	,DKF_0	), // LATIN SMALL LETTER Z WITH CARON
/*HACEK              */	DEADTRANS(	L'0'	,0x021f	,0x2080	,DKF_0	), // SUBSCRIPT ZERO
/*HACEK              */	DEADTRANS(	L'1'	,0x021f	,0x2081	,DKF_0	), // SUBSCRIPT ONE
/*HACEK              */	DEADTRANS(	L'2'	,0x021f	,0x2082	,DKF_0	), // SUBSCRIPT TWO
/*HACEK              */	DEADTRANS(	L'3'	,0x021f	,0x2083	,DKF_0	), // SUBSCRIPT THREE
/*HACEK              */	DEADTRANS(	L'4'	,0x021f	,0x2084	,DKF_0	), // SUBSCRIPT FOUR
/*HACEK              */	DEADTRANS(	L'5'	,0x021f	,0x2085	,DKF_0	), // SUBSCRIPT FIVE
/*HACEK              */	DEADTRANS(	L'6'	,0x021f	,0x2086	,DKF_0	), // SUBSCRIPT SIX
/*HACEK              */	DEADTRANS(	L'7'	,0x021f	,0x2087	,DKF_0	), // SUBSCRIPT SEVEN
/*HACEK              */	DEADTRANS(	L'8'	,0x021f	,0x2088	,DKF_0	), // SUBSCRIPT EIGHT
/*HACEK              */	DEADTRANS(	L'9'	,0x021f	,0x2089	,DKF_0	), // SUBSCRIPT NINE
/*HACEK              */	DEADTRANS(	0x0023	,0x021f	,0x2083	,DKF_0	), // SUBSCRIPT THREE
/*HACEK              */	DEADTRANS(	0x0025	,0x021f	,0x2031	,CHAIN	), // PER TEN THOUSAND SIGN
/*HACEK              */	DEADTRANS(	0x0027	,0x021f	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*HACEK              */	DEADTRANS(	0x002e	,0x021f	,0x1e67	,CHAIN	), // LATIN SMALL LETTER S WITH CARON AND DOT ABOVE
/*HACEK              */	DEADTRANS(	0x003c	,0x021f	,0x2277	,DKF_0	), // GREATER-THAN OR LESS-THAN
/*HACEK              */	DEADTRANS(	0x003d	,0x021f	,0x2267	,DKF_0	), // GREATER-THAN OVER EQUAL TO
/*HACEK              */	DEADTRANS(	0x003e	,0x021f	,0x2a7e	,DKF_0	), // GREATER-THAN OR SLANTED EQUAL TO
/*HACEK              */	DEADTRANS(	0x0040	,0x021f	,0x25b2	,DKF_0	), // BLACK UP-POINTING TRIANGLE
/*HACEK              */	DEADTRANS(	0x005f	,0x021f	,0x2265	,DKF_0	), // GREATER-THAN OR EQUAL TO
/*HACEK              */	DEADTRANS(	0x007c	,0x021f	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*HACEK              */	DEADTRANS(	0x0152	,0x021f	,0x2082	,DKF_0	), // SUBSCRIPT TWO
/*HACEK              */	DEADTRANS(	0x0153	,0x021f	,0x2082	,DKF_0	), // SUBSCRIPT TWO
/*HACEK              */	DEADTRANS(	0x00a9	,0x021f	,0x010d	,CHAIN	), // LATIN SMALL LETTER C WITH CARON
/*HACEK              */	DEADTRANS(	L'D'	,0x010d	,0x01c5	,CHAIN	), // LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
/*HACEK              */	DEADTRANS(	L'Z'	,0x01c5	,0x01c4	,DKF_0	), // LATIN CAPITAL LETTER DZ WITH CARON
/*HACEK              */	DEADTRANS(	L'z'	,0x01c5	,0x01c5	,DKF_0	), // LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
/*HACEK              */	DEADTRANS(	L'd'	,0x010d	,0x01c6	,DKF_0	), // LATIN SMALL LETTER DZ WITH CARON
/*HACEK              */	DEADTRANS(	L'Z'	,0x010d	,0x01ee	,DKF_0	), // LATIN CAPITAL LETTER EZH WITH CARON
/*HACEK              */	DEADTRANS(	L'z'	,0x010d	,0x01ef	,DKF_0	), // LATIN SMALL LETTER EZH WITH CARON
/*HACEK              */	DEADTRANS(	0x00c9	,0x021f	,0x2082	,DKF_0	), // SUBSCRIPT TWO
/*HACEK              */	DEADTRANS(	0x00e9	,0x021f	,0x2082	,DKF_0	), // SUBSCRIPT TWO
/*HACEK              */	DEADTRANS(	0x00ea	,0x021f	,0x1e19	,CHAIN	), // LATIN SMALL LETTER E WITH CIRCUMFLEX BELOW
/*HACEK              */	DEADTRANS(	0x00eb	,0x021f	,0x01da	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS AND CARON
/*HACEK              */	DEADTRANS(	0x00c8	,0x01da	,0x01d9	,DKF_0	), // LATIN CAPITAL LETTER U WITH DIAERESIS AND CARON
/*HACEK              */	DEADTRANS(	0x00e8	,0x01da	,0x01da	,DKF_0	), // LATIN SMALL LETTER U WITH DIAERESIS AND CARON
/*HACEK              */	DEADTRANS(	0x00f9	,0x021f	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*HACEK              */	DEADTRANS(	0x2019	,0x021f	,0x02bb	,DKF_0	), // MODIFIER LETTER TURNED COMMA
/*HACEK              */	DEADTRANS(	0x2610	,0x021f	,0x2611	,DKF_0	), // BALLOT BOX WITH CHECK
/*HACEK              */	DEADTRANS(	0x022f	,0x021f	,0x1e67	,CHAIN	), // LATIN SMALL LETTER S WITH CARON AND DOT ABOVE
/*HACEK&DOT_ABOVE    */	DEADTRANS(	L'S'	,0x1e67	,0x1e66	,DKF_0	), // LATIN CAPITAL LETTER S WITH CARON AND DOT ABOVE
/*HACEK&DOT_ABOVE    */	DEADTRANS(	L's'	,0x1e67	,0x1e67	,DKF_0	), // LATIN SMALL LETTER S WITH CARON AND DOT ABOVE
/*HEBREW             */	DEADTRANS(	L'a'	,0x05d0	,0x05d0	,DKF_0	), // HEBREW LETTER ALEF
/*HEBREW             */	DEADTRANS(	0x05d0	,0x05d0	,0x05d1	,CHAIN	), // HEBREW LETTER BET
/*HEBREW             */	DEADTRANS(	L'b'	,0x05d0	,0x05d1	,DKF_0	), // HEBREW LETTER BET
/*HEBREW             */	DEADTRANS(	L'd'	,0x05d0	,0x05d3	,DKF_0	), // HEBREW LETTER DALET
/*HEBREW             */	DEADTRANS(	L'g'	,0x05d0	,0x05d2	,DKF_0	), // HEBREW LETTER GIMEL
/*HEBREW             */	DEADTRANS(	L'h'	,0x05d0	,0x05d4	,DKF_0	), // HEBREW LETTER HE
/*HEBREW             */	DEADTRANS(	L'i'	,0x05d0	,0x05d5	,DKF_0	), // HEBREW LETTER VAV
/*HEBREW             */	DEADTRANS(	L'j'	,0x05d0	,0x05d9	,DKF_0	), // HEBREW LETTER YOD
/*HEBREW             */	DEADTRANS(	L'K'	,0x05d0	,0x05da	,DKF_0	), // HEBREW LETTER FINAL KAF
/*HEBREW             */	DEADTRANS(	L'k'	,0x05d0	,0x05db	,DKF_0	), // HEBREW LETTER KAF
/*HEBREW             */	DEADTRANS(	L'l'	,0x05d0	,0x05dc	,DKF_0	), // HEBREW LETTER LAMED
/*HEBREW             */	DEADTRANS(	L'M'	,0x05d0	,0x05dd	,DKF_0	), // HEBREW LETTER FINAL MEM
/*HEBREW             */	DEADTRANS(	L'm'	,0x05d0	,0x05de	,DKF_0	), // HEBREW LETTER MEM
/*HEBREW             */	DEADTRANS(	L'N'	,0x05d0	,0x05df	,DKF_0	), // HEBREW LETTER FINAL NUN
/*HEBREW             */	DEADTRANS(	L'n'	,0x05d0	,0x05e0	,DKF_0	), // HEBREW LETTER NUN
/*HEBREW             */	DEADTRANS(	L'P'	,0x05d0	,0x05e3	,DKF_0	), // HEBREW LETTER FINAL PE
/*HEBREW             */	DEADTRANS(	L'p'	,0x05d0	,0x05e4	,DKF_0	), // HEBREW LETTER PE
/*HEBREW             */	DEADTRANS(	L'q'	,0x05d0	,0x05e7	,DKF_0	), // HEBREW LETTER QOF
/*HEBREW             */	DEADTRANS(	L'r'	,0x05d0	,0x05e8	,DKF_0	), // HEBREW LETTER RESH
/*HEBREW             */	DEADTRANS(	L's'	,0x05d0	,0x05e1	,DKF_0	), // HEBREW LETTER SAMEKH
/*HEBREW             */	DEADTRANS(	L't'	,0x05d0	,0x05ea	,DKF_0	), // HEBREW LETTER TAV
/*HEBREW             */	DEADTRANS(	L'u'	,0x05d0	,0x05d8	,DKF_0	), // HEBREW LETTER TET
/*HEBREW             */	DEADTRANS(	L'v'	,0x05d0	,0x05e2	,DKF_0	), // HEBREW LETTER AYIN
/*HEBREW             */	DEADTRANS(	L'w'	,0x05d0	,0x05e9	,DKF_0	), // HEBREW LETTER SHIN
/*HEBREW             */	DEADTRANS(	L'x'	,0x05d0	,0x05d7	,DKF_0	), // HEBREW LETTER HET
/*HEBREW             */	DEADTRANS(	L'Y'	,0x05d0	,0x05e5	,DKF_0	), // HEBREW LETTER FINAL TSADI
/*HEBREW             */	DEADTRANS(	L'y'	,0x05d0	,0x05e6	,DKF_0	), // HEBREW LETTER TSADI
/*HEBREW             */	DEADTRANS(	L'z'	,0x05d0	,0x05d6	,DKF_0	), // HEBREW LETTER ZAYIN
/*HEBREW_LOCK        */	DEADTRANS(	L'a'	,0x05d1	,0x05d0	,CHAIN	), // HEBREW LETTER ALEF
/*HEBREW_LOCK        */	DEADTRANS(	L'b'	,0x05d1	,0x05d1	,CHAIN	), // HEBREW LETTER BET
/*HEBREW_LOCK        */	DEADTRANS(	L'd'	,0x05d1	,0x05d3	,CHAIN	), // HEBREW LETTER DALET
/*HEBREW_LOCK        */	DEADTRANS(	L'g'	,0x05d1	,0x05d2	,CHAIN	), // HEBREW LETTER GIMEL
/*HEBREW_LOCK        */	DEADTRANS(	L'h'	,0x05d1	,0x05d4	,CHAIN	), // HEBREW LETTER HE
/*HEBREW_LOCK        */	DEADTRANS(	L'i'	,0x05d1	,0x05d5	,CHAIN	), // HEBREW LETTER VAV
/*HEBREW_LOCK        */	DEADTRANS(	L'j'	,0x05d1	,0x05d9	,CHAIN	), // HEBREW LETTER YOD
/*HEBREW_LOCK        */	DEADTRANS(	L'K'	,0x05d1	,0x05da	,CHAIN	), // HEBREW LETTER FINAL KAF
/*HEBREW_LOCK        */	DEADTRANS(	L'k'	,0x05d1	,0x05db	,CHAIN	), // HEBREW LETTER KAF
/*HEBREW_LOCK        */	DEADTRANS(	L'l'	,0x05d1	,0x05dc	,CHAIN	), // HEBREW LETTER LAMED
/*HEBREW_LOCK        */	DEADTRANS(	L'M'	,0x05d1	,0x05dd	,CHAIN	), // HEBREW LETTER FINAL MEM
/*HEBREW_LOCK        */	DEADTRANS(	L'm'	,0x05d1	,0x05de	,CHAIN	), // HEBREW LETTER MEM
/*HEBREW_LOCK        */	DEADTRANS(	L'N'	,0x05d1	,0x05df	,CHAIN	), // HEBREW LETTER FINAL NUN
/*HEBREW_LOCK        */	DEADTRANS(	L'n'	,0x05d1	,0x05e0	,CHAIN	), // HEBREW LETTER NUN
/*HEBREW_LOCK        */	DEADTRANS(	L'P'	,0x05d1	,0x05e3	,CHAIN	), // HEBREW LETTER FINAL PE
/*HEBREW_LOCK        */	DEADTRANS(	L'p'	,0x05d1	,0x05e4	,CHAIN	), // HEBREW LETTER PE
/*HEBREW_LOCK        */	DEADTRANS(	L'q'	,0x05d1	,0x05e7	,CHAIN	), // HEBREW LETTER QOF
/*HEBREW_LOCK        */	DEADTRANS(	L'r'	,0x05d1	,0x05e8	,CHAIN	), // HEBREW LETTER RESH
/*HEBREW_LOCK        */	DEADTRANS(	L's'	,0x05d1	,0x05e1	,CHAIN	), // HEBREW LETTER SAMEKH
/*HEBREW_LOCK        */	DEADTRANS(	L't'	,0x05d1	,0x05ea	,CHAIN	), // HEBREW LETTER TAV
/*HEBREW_LOCK        */	DEADTRANS(	L'u'	,0x05d1	,0x05d8	,CHAIN	), // HEBREW LETTER TET
/*HEBREW_LOCK        */	DEADTRANS(	L'v'	,0x05d1	,0x05e2	,CHAIN	), // HEBREW LETTER AYIN
/*HEBREW_LOCK        */	DEADTRANS(	L'w'	,0x05d1	,0x05e9	,CHAIN	), // HEBREW LETTER SHIN
/*HEBREW_LOCK        */	DEADTRANS(	L'x'	,0x05d1	,0x05d7	,CHAIN	), // HEBREW LETTER HET
/*HEBREW_LOCK        */	DEADTRANS(	L'Y'	,0x05d1	,0x05e5	,CHAIN	), // HEBREW LETTER FINAL TSADI
/*HEBREW_LOCK        */	DEADTRANS(	L'y'	,0x05d1	,0x05e6	,CHAIN	), // HEBREW LETTER TSADI
/*HEBREW_LOCK        */	DEADTRANS(	L'z'	,0x05d1	,0x05d6	,CHAIN	), // HEBREW LETTER ZAYIN
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'B'	,0x0183	,0x0182	,DKF_0	), // LATIN CAPITAL LETTER B WITH TOPBAR
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'b'	,0x0183	,0x0183	,DKF_0	), // LATIN SMALL LETTER B WITH TOPBAR
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'D'	,0x0183	,0x018b	,DKF_0	), // LATIN CAPITAL LETTER D WITH TOPBAR
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'd'	,0x0183	,0x018c	,DKF_0	), // LATIN SMALL LETTER D WITH TOPBAR
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'H'	,0x0183	,0xa7f8	,DKF_0	), // MODIFIER LETTER CAPITAL H WITH STROKE
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'i'	,0x0183	,0x1da4	,DKF_0	), // MODIFIER LETTER SMALL I WITH STROKE
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'L'	,0x0183	,0xa748	,DKF_0	), // LATIN CAPITAL LETTER L WITH HIGH STROKE
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'l'	,0x0183	,0xa749	,DKF_0	), // LATIN SMALL LETTER L WITH HIGH STROKE
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'o'	,0x0183	,0x1db1	,DKF_0	), // MODIFIER LETTER SMALL BARRED O
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'u'	,0x0183	,0x1db6	,DKF_0	), // MODIFIER LETTER SMALL U BAR
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'v'	,0x0183	,0x02c5	,DKF_0	), // MODIFIER LETTER DOWN ARROWHEAD
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'2'	,0x0183	,0xa71c	,DKF_0	), // MODIFIER LETTER RAISED DOWN ARROW
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	L'8'	,0x0183	,0xa71b	,DKF_0	), // MODIFIER LETTER RAISED UP ARROW
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	0x002d	,0x0183	,0x207b	,DKF_0	), // SUPERSCRIPT MINUS
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	0x003c	,0x0183	,0x02c2	,DKF_0	), // MODIFIER LETTER LEFT ARROWHEAD
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	0x003e	,0x0183	,0x02c3	,DKF_0	), // MODIFIER LETTER RIGHT ARROWHEAD
/*HIGH_BAR_(HORIZONT)*/	DEADTRANS(	0x005e	,0x0183	,0x02c4	,DKF_0	), // MODIFIER LETTER UP ARROWHEAD
/*HOOK_ABOVE         */	DEADTRANS(	0x0020	,0x1ebb	,0x0309	,DKF_0	), // COMBINING HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'A'	,0x1ebb	,0x1ea2	,DKF_0	), // LATIN CAPITAL LETTER A WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'a'	,0x1ebb	,0x1ea3	,DKF_0	), // LATIN SMALL LETTER A WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'b'	,0x1ebb	,0x1d80	,DKF_0	), // LATIN SMALL LETTER B WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'c'	,0x1ebb	,0xa794	,DKF_0	), // LATIN SMALL LETTER C WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'd'	,0x1ebb	,0x1d81	,DKF_0	), // LATIN SMALL LETTER D WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'E'	,0x1ebb	,0x1eba	,DKF_0	), // LATIN CAPITAL LETTER E WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'e'	,0x1ebb	,0x1ebb	,DKF_0	), // LATIN SMALL LETTER E WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'f'	,0x1ebb	,0x1d82	,DKF_0	), // LATIN SMALL LETTER F WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'g'	,0x1ebb	,0x1d83	,DKF_0	), // LATIN SMALL LETTER G WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'h'	,0x1ebb	,0xa795	,DKF_0	), // LATIN SMALL LETTER H WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'I'	,0x1ebb	,0x1ec8	,DKF_0	), // LATIN CAPITAL LETTER I WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'i'	,0x1ebb	,0x1ec9	,DKF_0	), // LATIN SMALL LETTER I WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'k'	,0x1ebb	,0x1d84	,DKF_0	), // LATIN SMALL LETTER K WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'l'	,0x1ebb	,0x1d85	,DKF_0	), // LATIN SMALL LETTER L WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'm'	,0x1ebb	,0x1d86	,DKF_0	), // LATIN SMALL LETTER M WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'n'	,0x1ebb	,0x1d87	,DKF_0	), // LATIN SMALL LETTER N WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'O'	,0x1ebb	,0x1ece	,DKF_0	), // LATIN CAPITAL LETTER O WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'o'	,0x1ebb	,0x1ecf	,DKF_0	), // LATIN SMALL LETTER O WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'p'	,0x1ebb	,0x1d88	,DKF_0	), // LATIN SMALL LETTER P WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'r'	,0x1ebb	,0x1d89	,DKF_0	), // LATIN SMALL LETTER R WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L's'	,0x1ebb	,0x1d8a	,DKF_0	), // LATIN SMALL LETTER S WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L't'	,0x1ebb	,0x01ab	,DKF_0	), // LATIN SMALL LETTER T WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'U'	,0x1ebb	,0x1ee6	,DKF_0	), // LATIN CAPITAL LETTER U WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'u'	,0x1ebb	,0x1ee7	,DKF_0	), // LATIN SMALL LETTER U WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'v'	,0x1ebb	,0x1d8c	,DKF_0	), // LATIN SMALL LETTER V WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'x'	,0x1ebb	,0x1d8d	,DKF_0	), // LATIN SMALL LETTER X WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'Y'	,0x1ebb	,0x1ef6	,DKF_0	), // LATIN CAPITAL LETTER Y WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'y'	,0x1ebb	,0x1ef7	,DKF_0	), // LATIN SMALL LETTER Y WITH HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	L'z'	,0x1ebb	,0x1d8e	,DKF_0	), // LATIN SMALL LETTER Z WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	0x0029	,0x1ebb	,0x1eb3	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	0x002c	,0x1ebb	,0x1edf	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	0x002d	,0x1ecf	,0x266b	,DKF_0	), // BEAMED EIGHTH NOTES
/*HOOK_ABOVE         */	DEADTRANS(	0x003c	,0x1ebb	,0x1ed5	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	0x003d	,0x1ecf	,0x266c	,DKF_0	), // BEAMED SIXTEENTH NOTES
/*HOOK_ABOVE         */	DEADTRANS(	0x005d	,0x1ebb	,0xab32	,CHAIN	), // LATIN SMALL LETTER BLACKLETTER E
/*HOOK_ABOVE         */	DEADTRANS(	0x00a9	,0x1ebb	,0x1d8b	,CHAIN	), // LATIN SMALL LETTER ESH WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L'c'	,0x1d8b	,0x1d8b	,DKF_0	), // LATIN SMALL LETTER ESH WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	L's'	,0x1d8b	,0x1d8b	,DKF_0	), // LATIN SMALL LETTER ESH WITH PALATAL HOOK
/*HOOK_ABOVE         */	DEADTRANS(	0x00ea	,0x1ebb	,0x1ed5	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	0x0229	,0x1ebb	,0x1edf	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	0x014f	,0x1ebb	,0x1eb3	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
/*HOOK_ABOVE         */	DEADTRANS(	0x01a1	,0x1ebb	,0x1edf	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
/*HORN               */	DEADTRANS(	0x0020	,0x01a1	,0x031b	,DKF_0	), // COMBINING HORN
/*HORN               */	DEADTRANS(	L'O'	,0x01a1	,0x01a0	,DKF_0	), // LATIN CAPITAL LETTER O WITH HORN
/*HORN               */	DEADTRANS(	L'o'	,0x01a1	,0x01a1	,DKF_0	), // LATIN SMALL LETTER O WITH HORN
/*HORN               */	DEADTRANS(	L'U'	,0x01a1	,0x01af	,DKF_0	), // LATIN CAPITAL LETTER U WITH HORN
/*HORN               */	DEADTRANS(	L'u'	,0x01a1	,0x01b0	,DKF_0	), // LATIN SMALL LETTER U WITH HORN
/*HORN               */	DEADTRANS(	0x0021	,0x01a1	,0x1ee3	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND DOT BELOW
/*HORN               */	DEADTRANS(	0x0027	,0x01a1	,0x1edb	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND ACUTE
/*HORN               */	DEADTRANS(	0x005d	,0x01a1	,0x1edf	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
/*HORN               */	DEADTRANS(	0x0060	,0x01a1	,0x1edd	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND GRAVE
/*HORN               */	DEADTRANS(	0x007e	,0x01a1	,0x1ee1	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND TILDE
/*HORN               */	DEADTRANS(	0x00e1	,0x01a1	,0x1edb	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND ACUTE
/*HORN               */	DEADTRANS(	0x00f2	,0x01a1	,0x1edd	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND GRAVE
/*HORN               */	DEADTRANS(	0x00f5	,0x01a1	,0x1ee1	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND TILDE
/*HORN               */	DEADTRANS(	0x1ebb	,0x01a1	,0x1edf	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
/*HORN               */	DEADTRANS(	0x1ee5	,0x01a1	,0x1ee3	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND DOT BELOW
/*HORN&ACUTE_ACCENT  */	DEADTRANS(	L'C'	,0x1e09	,0x1e08	,DKF_0	), // LATIN CAPITAL LETTER C WITH CEDILLA AND ACUTE
/*HORN&ACUTE_ACCENT  */	DEADTRANS(	L'c'	,0x1e09	,0x1e09	,DKF_0	), // LATIN SMALL LETTER C WITH CEDILLA AND ACUTE
/*HORN&ACUTE_ACCENT  */	DEADTRANS(	L'O'	,0x1e09	,0x1eda	,DKF_0	), // LATIN CAPITAL LETTER O WITH HORN AND ACUTE
/*HORN&ACUTE_ACCENT  */	DEADTRANS(	L'o'	,0x1e09	,0x1edb	,DKF_0	), // LATIN SMALL LETTER O WITH HORN AND ACUTE
/*HORN&ACUTE_ACCENT  */	DEADTRANS(	L'U'	,0x1e09	,0x1ee8	,DKF_0	), // LATIN CAPITAL LETTER U WITH HORN AND ACUTE
/*HORN&ACUTE_ACCENT  */	DEADTRANS(	L'u'	,0x1e09	,0x1ee9	,DKF_0	), // LATIN SMALL LETTER U WITH HORN AND ACUTE
/*HORN&DOT_BELOW     */	DEADTRANS(	L'O'	,0x1ee3	,0x1ee2	,DKF_0	), // LATIN CAPITAL LETTER O WITH HORN AND DOT BELOW
/*HORN&DOT_BELOW     */	DEADTRANS(	L'o'	,0x1ee3	,0x1ee3	,DKF_0	), // LATIN SMALL LETTER O WITH HORN AND DOT BELOW
/*HORN&DOT_BELOW     */	DEADTRANS(	L'U'	,0x1ee3	,0x1ef0	,DKF_0	), // LATIN CAPITAL LETTER U WITH HORN AND DOT BELOW
/*HORN&DOT_BELOW     */	DEADTRANS(	L'u'	,0x1ee3	,0x1ef1	,DKF_0	), // LATIN SMALL LETTER U WITH HORN AND DOT BELOW
/*HORN&GRAVE         */	DEADTRANS(	L'O'	,0x1edd	,0x1edc	,DKF_0	), // LATIN CAPITAL LETTER O WITH HORN AND GRAVE
/*HORN&GRAVE         */	DEADTRANS(	L'o'	,0x1edd	,0x1edd	,DKF_0	), // LATIN SMALL LETTER O WITH HORN AND GRAVE
/*HORN&GRAVE         */	DEADTRANS(	L'U'	,0x1edd	,0x1eea	,DKF_0	), // LATIN CAPITAL LETTER U WITH HORN AND GRAVE
/*HORN&GRAVE         */	DEADTRANS(	L'u'	,0x1edd	,0x1eeb	,DKF_0	), // LATIN SMALL LETTER U WITH HORN AND GRAVE
/*HORN&HOOK_ABOVE    */	DEADTRANS(	L'O'	,0x1edf	,0x1ede	,DKF_0	), // LATIN CAPITAL LETTER O WITH HORN AND HOOK ABOVE
/*HORN&HOOK_ABOVE    */	DEADTRANS(	L'o'	,0x1edf	,0x1edf	,DKF_0	), // LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
/*HORN&HOOK_ABOVE    */	DEADTRANS(	L'U'	,0x1edf	,0x1eec	,DKF_0	), // LATIN CAPITAL LETTER U WITH HORN AND HOOK ABOVE
/*HORN&HOOK_ABOVE    */	DEADTRANS(	L'u'	,0x1edf	,0x1eed	,DKF_0	), // LATIN SMALL LETTER U WITH HORN AND HOOK ABOVE
/*HORN&TILDE         */	DEADTRANS(	L'O'	,0x1ee1	,0x1ee0	,DKF_0	), // LATIN CAPITAL LETTER O WITH HORN AND TILDE
/*HORN&TILDE         */	DEADTRANS(	L'o'	,0x1ee1	,0x1ee1	,DKF_0	), // LATIN SMALL LETTER O WITH HORN AND TILDE
/*HORN&TILDE         */	DEADTRANS(	L'U'	,0x1ee1	,0x1eee	,DKF_0	), // LATIN CAPITAL LETTER U WITH HORN AND TILDE
/*HORN&TILDE         */	DEADTRANS(	L'u'	,0x1ee1	,0x1eef	,DKF_0	), // LATIN SMALL LETTER U WITH HORN AND TILDE
/*INSULAR            */	DEADTRANS(	L'D'	,0x1d79	,0xa779	,DKF_0	), // LATIN CAPITAL LETTER INSULAR D
/*INSULAR            */	DEADTRANS(	L'd'	,0x1d79	,0xa77a	,DKF_0	), // LATIN SMALL LETTER INSULAR D
/*INSULAR            */	DEADTRANS(	L'F'	,0x1d79	,0xa77b	,DKF_0	), // LATIN CAPITAL LETTER INSULAR F
/*INSULAR            */	DEADTRANS(	L'f'	,0x1d79	,0xa77c	,DKF_0	), // LATIN SMALL LETTER INSULAR F
/*INSULAR            */	DEADTRANS(	L'G'	,0x1d79	,0xa77d	,DKF_0	), // LATIN CAPITAL LETTER INSULAR G
/*INSULAR            */	DEADTRANS(	L'g'	,0x1d79	,0x1d79	,DKF_0	), // LATIN SMALL LETTER INSULAR G
/*INSULAR            */	DEADTRANS(	L'R'	,0x1d79	,0xa782	,DKF_0	), // LATIN CAPITAL LETTER INSULAR R
/*INSULAR            */	DEADTRANS(	L'r'	,0x1d79	,0xa783	,DKF_0	), // LATIN SMALL LETTER INSULAR R
/*INSULAR            */	DEADTRANS(	L'S'	,0x1d79	,0xa784	,DKF_0	), // LATIN CAPITAL LETTER INSULAR S
/*INSULAR            */	DEADTRANS(	L's'	,0x1d79	,0xa785	,DKF_0	), // LATIN SMALL LETTER INSULAR S
/*INSULAR            */	DEADTRANS(	L'T'	,0x1d79	,0xa786	,DKF_0	), // LATIN CAPITAL LETTER INSULAR T
/*INSULAR            */	DEADTRANS(	L't'	,0x1d79	,0xa787	,DKF_0	), // LATIN SMALL LETTER INSULAR T
/*INVERTED           */	DEADTRANS(	L'A'	,0x0281	,0x2c6f	,DKF_0	), // LATIN CAPITAL LETTER TURNED A
/*INVERTED           */	DEADTRANS(	L'a'	,0x0281	,0xab64	,DKF_0	), // LATIN SMALL LETTER INVERTED ALPHA
/*INVERTED           */	DEADTRANS(	L'M'	,0x0281	,0xa7fd	,DKF_0	), // LATIN EPIGRAPHIC LETTER INVERTED M
/*INVERTED           */	DEADTRANS(	L'o'	,0x0281	,0xab40	,DKF_0	), // LATIN SMALL LETTER INVERTED OE
/*INVERTED           */	DEADTRANS(	L'T'	,0x0281	,0xa7b1	,DKF_0	), // LATIN CAPITAL LETTER TURNED T
/*INVERTED           */	DEADTRANS(	L'V'	,0x0281	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*INVERTED           */	DEADTRANS(	L'v'	,0x0281	,0x028c	,DKF_0	), // LATIN SMALL LETTER TURNED V
/*INVERTED           */	DEADTRANS(	0x0021	,0x0281	,0x00a1	,DKF_0	), // INVERTED EXCLAMATION MARK
/*INVERTED           */	DEADTRANS(	0x0025	,0x0281	,0x2030	,DKF_0	), // PER MILLE SIGN
/*INVERTED           */	DEADTRANS(	0x0027	,0x0281	,0x0296	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP
/*INVERTED           */	DEADTRANS(	0x003f	,0x0281	,0x00bf	,DKF_0	), // INVERTED QUESTION MARK
/*INVERTED           */	DEADTRANS(	0x00f9	,0x0281	,0x0296	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP
/*INVERTED           */	DEADTRANS(	0x2019	,0x0281	,0x0296	,DKF_0	), // LATIN LETTER INVERTED GLOTTAL STOP
/*INVERTED_BREVE     */	DEADTRANS(	0x0020	,0x0213	,0x0311	,DKF_0	), // COMBINING INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	0x202f	,0x0213	,0x2229	,DKF_0	), // INTERSECTION
/*INVERTED_BREVE     */	DEADTRANS(	0x00a0	,0x0213	,0x2229	,DKF_0	), // INTERSECTION
/*INVERTED_BREVE     */	DEADTRANS(	0x0029	,0x0213	,0x2050	,DKF_0	), // CLOSE UP
/*INVERTED_BREVE     */	DEADTRANS(	0x002e	,0x0213	,0x0352	,DKF_0	), // COMBINING FERMATA
/*INVERTED_BREVE     */	DEADTRANS(	L'A'	,0x0213	,0x0202	,DKF_0	), // LATIN CAPITAL LETTER A WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'a'	,0x0213	,0x0203	,DKF_0	), // LATIN SMALL LETTER A WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'E'	,0x0213	,0x0206	,DKF_0	), // LATIN CAPITAL LETTER E WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'e'	,0x0213	,0x0207	,DKF_0	), // LATIN SMALL LETTER E WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'H'	,0x0213	,0x1e2a	,DKF_0	), // LATIN CAPITAL LETTER H WITH BREVE BELOW
/*INVERTED_BREVE     */	DEADTRANS(	L'h'	,0x0213	,0x1e2b	,DKF_0	), // LATIN SMALL LETTER H WITH BREVE BELOW
/*INVERTED_BREVE     */	DEADTRANS(	L'I'	,0x0213	,0x020a	,DKF_0	), // LATIN CAPITAL LETTER I WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'i'	,0x0213	,0x020b	,DKF_0	), // LATIN SMALL LETTER I WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'O'	,0x0213	,0x020e	,DKF_0	), // LATIN CAPITAL LETTER O WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'o'	,0x0213	,0x020f	,DKF_0	), // LATIN SMALL LETTER O WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'R'	,0x0213	,0x0212	,DKF_0	), // LATIN CAPITAL LETTER R WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'r'	,0x0213	,0x0213	,DKF_0	), // LATIN SMALL LETTER R WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'U'	,0x0213	,0x0216	,DKF_0	), // LATIN CAPITAL LETTER U WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	L'u'	,0x0213	,0x0217	,DKF_0	), // LATIN SMALL LETTER U WITH INVERTED BREVE
/*INVERTED_BREVE     */	DEADTRANS(	0x0115	,0x0213	,0x1e2b	,DKF_0	), // LATIN SMALL LETTER H WITH BREVE BELOW
/*LONG               */	DEADTRANS(	L'c'	,0x007c	,0x0297	,DKF_0	), // LATIN LETTER STRETCHED C
/*LONG               */	DEADTRANS(	L'I'	,0x007c	,0xa7fe	,DKF_0	), // LATIN EPIGRAPHIC LETTER I LONGA
/*LONG               */	DEADTRANS(	L'i'	,0x007c	,0xa7fe	,DKF_0	), // LATIN EPIGRAPHIC LETTER I LONGA
/*LONG               */	DEADTRANS(	L'N'	,0x007c	,0x0220	,DKF_0	), // LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
/*LONG               */	DEADTRANS(	L'n'	,0x007c	,0x019e	,DKF_0	), // LATIN SMALL LETTER N WITH LONG RIGHT LEG
/*LONG               */	DEADTRANS(	L'o'	,0x007c	,0x2c77	,DKF_0	), // LATIN SMALL LETTER TAILLESS PHI
/*LONG               */	DEADTRANS(	L'P'	,0x007c	,0x00b6	,DKF_0	), // PILCROW SIGN
/*LONG               */	DEADTRANS(	L'p'	,0x007c	,0x00b6	,DKF_0	), // PILCROW SIGN
/*LONG               */	DEADTRANS(	L'R'	,0x007c	,0xab46	,DKF_0	), // LATIN LETTER SMALL CAPITAL R WITH RIGHT LEG
/*LONG               */	DEADTRANS(	L'r'	,0x007c	,0x027c	,DKF_0	), // LATIN SMALL LETTER R WITH LONG LEG
/*LONG               */	DEADTRANS(	L'V'	,0x007c	,0xa768	,DKF_0	), // LATIN CAPITAL LETTER VEND
/*LONG               */	DEADTRANS(	L'v'	,0x007c	,0xa769	,DKF_0	), // LATIN SMALL LETTER VEND
/*LONG               */	DEADTRANS(	L'x'	,0x007c	,0xab57	,DKF_0	), // LATIN SMALL LETTER X WITH LONG LEFT LEG
/*LONG               */	DEADTRANS(	L'0'	,0x007c	,0x02e9	,DKF_0	), // MODIFIER LETTER EXTRA-LOW TONE BAR
/*LONG               */	DEADTRANS(	L'1'	,0x007c	,0x02e8	,DKF_0	), // MODIFIER LETTER LOW TONE BAR
/*LONG               */	DEADTRANS(	L'2'	,0x007c	,0x02e7	,DKF_0	), // MODIFIER LETTER MID TONE BAR
/*LONG               */	DEADTRANS(	L'3'	,0x007c	,0x02e6	,DKF_0	), // MODIFIER LETTER HIGH TONE BAR
/*LONG               */	DEADTRANS(	L'4'	,0x007c	,0x02e5	,DKF_0	), // MODIFIER LETTER EXTRA-HIGH TONE BAR
/*LONG               */	DEADTRANS(	0x0023	,0x007c	,0x2e38	,DKF_0	), // TURNED DAGGER
/*LONG               */	DEADTRANS(	0x0025	,0x007c	,0x2e4b	,DKF_0	), // TRIPLE DAGGER
/*LONG               */	DEADTRANS(	0x002b	,0x007c	,0x2020	,DKF_0	), // DAGGER
/*LONG               */	DEADTRANS(	0x002d	,0x007c	,0xa714	,CHAIN	), // MODIFIER LETTER MID LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'0'	,0xa714	,0xa716	,DKF_0	), // MODIFIER LETTER EXTRA-LOW LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'1'	,0xa714	,0xa715	,DKF_0	), // MODIFIER LETTER LOW LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'2'	,0xa714	,0xa714	,DKF_0	), // MODIFIER LETTER MID LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'3'	,0xa714	,0xa713	,DKF_0	), // MODIFIER LETTER HIGH LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'4'	,0xa714	,0xa712	,DKF_0	), // MODIFIER LETTER EXTRA-HIGH LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	0x002e	,0x007c	,0xa70f	,CHAIN	), // MODIFIER LETTER MID DOTTED LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'0'	,0xa70f	,0xa711	,DKF_0	), // MODIFIER LETTER EXTRA-LOW DOTTED LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'1'	,0xa70f	,0xa710	,DKF_0	), // MODIFIER LETTER LOW DOTTED LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'2'	,0xa70f	,0xa70f	,DKF_0	), // MODIFIER LETTER MID DOTTED LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'3'	,0xa70f	,0xa70e	,DKF_0	), // MODIFIER LETTER HIGH DOTTED LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	L'4'	,0xa70f	,0xa70d	,DKF_0	), // MODIFIER LETTER EXTRA-HIGH DOTTED LEFT-STEM TONE BAR
/*LONG               */	DEADTRANS(	0x003a	,0xa70f	,0x205b	,DKF_0	), // FOUR DOT MARK
/*LONG               */	DEADTRANS(	0x003a	,0x007c	,0x205a	,DKF_0	), // TWO DOT PUNCTUATION
/*LONG               */	DEADTRANS(	0x003c	,0x007c	,0x2e36	,DKF_0	), // DAGGER WITH LEFT GUARD
/*LONG               */	DEADTRANS(	0x003d	,0x007c	,0x2021	,DKF_0	), // DOUBLE DAGGER
/*LONG               */	DEADTRANS(	0x003e	,0x007c	,0x2e37	,DKF_0	), // DAGGER WITH RIGHT GUARD
/*LONG               */	DEADTRANS(	0x007c	,0x007c	,0x2016	,DKF_0	), // DOUBLE VERTICAL LINE
/*LONG               */	DEADTRANS(	0x00b0	,0x007c	,0x2020	,DKF_0	), // DAGGER
/*LONG_BAR           */	DEADTRANS(	0x0020	,0x2013	,0x0336	,DKF_0	), // COMBINING LONG STROKE OVERLAY
/*LONG_BAR           */	DEADTRANS(	0x0021	,0x2013	,0x2013	,DKF_0	), // EN DASH
/*LONG_BAR           */	DEADTRANS(	0x002d	,0x2013	,0x2014	,DKF_0	), // EM DASH
/*LONG_BAR           */	DEADTRANS(	L'O'	,0x2013	,0xa74a	,DKF_0	), // LATIN CAPITAL LETTER O WITH LONG STROKE OVERLAY
/*LONG_BAR           */	DEADTRANS(	L'o'	,0x2013	,0xa74b	,DKF_0	), // LATIN SMALL LETTER O WITH LONG STROKE OVERLAY
/*LONG_BAR           */	DEADTRANS(	L'0'	,0x2013	,0x2195	,DKF_0	), // UP DOWN ARROW
/*LONG_BAR           */	DEADTRANS(	L'1'	,0x2013	,0x2199	,DKF_0	), // SOUTH WEST ARROW
/*LONG_BAR           */	DEADTRANS(	L'2'	,0x2013	,0x2193	,DKF_0	), // DOWNWARDS ARROW
/*LONG_BAR           */	DEADTRANS(	L'3'	,0x2013	,0x2198	,DKF_0	), // SOUTH EAST ARROW
/*LONG_BAR           */	DEADTRANS(	L'4'	,0x2013	,0x2190	,DKF_0	), // LEFTWARDS ARROW
/*LONG_BAR           */	DEADTRANS(	L'5'	,0x2013	,0x2194	,DKF_0	), // LEFT RIGHT ARROW
/*LONG_BAR           */	DEADTRANS(	L'6'	,0x2013	,0x2192	,DKF_0	), // RIGHTWARDS ARROW
/*LONG_BAR           */	DEADTRANS(	L'7'	,0x2013	,0x2196	,DKF_0	), // NORTH WEST ARROW
/*LONG_BAR           */	DEADTRANS(	L'8'	,0x2013	,0x2191	,DKF_0	), // UPWARDS ARROW
/*LONG_BAR           */	DEADTRANS(	L'9'	,0x2013	,0x2197	,DKF_0	), // NORTH EAST ARROW
/*M_BOLD             */	DEADTRANS(	L'A'	,0x212c	,0xdc00	,DKF_0	), // U+1D400; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL A
/*M_BOLD             */	DEADTRANS(	L'a'	,0x212c	,0xdc1a	,DKF_0	), // U+1D41A; input D835 high surrogate first; MATHEMATICAL BOLD SMALL A
/*M_BOLD             */	DEADTRANS(	L'B'	,0x212c	,0xdc01	,DKF_0	), // U+1D401; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL B
/*M_BOLD             */	DEADTRANS(	L'b'	,0x212c	,0xdc1b	,DKF_0	), // U+1D41B; input D835 high surrogate first; MATHEMATICAL BOLD SMALL B
/*M_BOLD             */	DEADTRANS(	L'C'	,0x212c	,0xdc02	,DKF_0	), // U+1D402; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL C
/*M_BOLD             */	DEADTRANS(	L'c'	,0x212c	,0xdc1c	,DKF_0	), // U+1D41C; input D835 high surrogate first; MATHEMATICAL BOLD SMALL C
/*M_BOLD             */	DEADTRANS(	L'D'	,0x212c	,0xdc03	,DKF_0	), // U+1D403; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL D
/*M_BOLD             */	DEADTRANS(	L'd'	,0x212c	,0xdc1d	,DKF_0	), // U+1D41D; input D835 high surrogate first; MATHEMATICAL BOLD SMALL D
/*M_BOLD             */	DEADTRANS(	L'E'	,0x212c	,0xdc04	,DKF_0	), // U+1D404; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL E
/*M_BOLD             */	DEADTRANS(	L'e'	,0x212c	,0xdc1e	,DKF_0	), // U+1D41E; input D835 high surrogate first; MATHEMATICAL BOLD SMALL E
/*M_BOLD             */	DEADTRANS(	L'F'	,0x212c	,0xdc05	,DKF_0	), // U+1D405; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL F
/*M_BOLD             */	DEADTRANS(	L'f'	,0x212c	,0xdc1f	,DKF_0	), // U+1D41F; input D835 high surrogate first; MATHEMATICAL BOLD SMALL F
/*M_BOLD             */	DEADTRANS(	L'G'	,0x212c	,0xdc06	,DKF_0	), // U+1D406; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL G
/*M_BOLD             */	DEADTRANS(	L'g'	,0x212c	,0xdc20	,DKF_0	), // U+1D420; input D835 high surrogate first; MATHEMATICAL BOLD SMALL G
/*M_BOLD             */	DEADTRANS(	L'H'	,0x212c	,0xdc07	,DKF_0	), // U+1D407; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL H
/*M_BOLD             */	DEADTRANS(	L'h'	,0x212c	,0xdc21	,DKF_0	), // U+1D421; input D835 high surrogate first; MATHEMATICAL BOLD SMALL H
/*M_BOLD             */	DEADTRANS(	L'I'	,0x212c	,0xdc08	,DKF_0	), // U+1D408; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL I
/*M_BOLD             */	DEADTRANS(	L'i'	,0x212c	,0xdc22	,DKF_0	), // U+1D422; input D835 high surrogate first; MATHEMATICAL BOLD SMALL I
/*M_BOLD             */	DEADTRANS(	L'J'	,0x212c	,0xdc09	,DKF_0	), // U+1D409; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL J
/*M_BOLD             */	DEADTRANS(	L'j'	,0x212c	,0xdc23	,DKF_0	), // U+1D423; input D835 high surrogate first; MATHEMATICAL BOLD SMALL J
/*M_BOLD             */	DEADTRANS(	L'K'	,0x212c	,0xdc0a	,DKF_0	), // U+1D40A; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL K
/*M_BOLD             */	DEADTRANS(	L'k'	,0x212c	,0xdc24	,DKF_0	), // U+1D424; input D835 high surrogate first; MATHEMATICAL BOLD SMALL K
/*M_BOLD             */	DEADTRANS(	L'L'	,0x212c	,0xdc0b	,DKF_0	), // U+1D40B; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL L
/*M_BOLD             */	DEADTRANS(	L'l'	,0x212c	,0xdc25	,DKF_0	), // U+1D425; input D835 high surrogate first; MATHEMATICAL BOLD SMALL L
/*M_BOLD             */	DEADTRANS(	L'M'	,0x212c	,0xdc0c	,DKF_0	), // U+1D40C; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL M
/*M_BOLD             */	DEADTRANS(	L'm'	,0x212c	,0xdc26	,DKF_0	), // U+1D426; input D835 high surrogate first; MATHEMATICAL BOLD SMALL M
/*M_BOLD             */	DEADTRANS(	L'N'	,0x212c	,0xdc0d	,DKF_0	), // U+1D40D; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL N
/*M_BOLD             */	DEADTRANS(	L'n'	,0x212c	,0xdc27	,DKF_0	), // U+1D427; input D835 high surrogate first; MATHEMATICAL BOLD SMALL N
/*M_BOLD             */	DEADTRANS(	L'O'	,0x212c	,0xdc0e	,DKF_0	), // U+1D40E; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL O
/*M_BOLD             */	DEADTRANS(	L'o'	,0x212c	,0xdc28	,DKF_0	), // U+1D428; input D835 high surrogate first; MATHEMATICAL BOLD SMALL O
/*M_BOLD             */	DEADTRANS(	L'P'	,0x212c	,0xdc0f	,DKF_0	), // U+1D40F; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL P
/*M_BOLD             */	DEADTRANS(	L'p'	,0x212c	,0xdc29	,DKF_0	), // U+1D429; input D835 high surrogate first; MATHEMATICAL BOLD SMALL P
/*M_BOLD             */	DEADTRANS(	L'Q'	,0x212c	,0xdc10	,DKF_0	), // U+1D410; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL Q
/*M_BOLD             */	DEADTRANS(	L'q'	,0x212c	,0xdc2a	,DKF_0	), // U+1D42A; input D835 high surrogate first; MATHEMATICAL BOLD SMALL Q
/*M_BOLD             */	DEADTRANS(	L'R'	,0x212c	,0xdc11	,DKF_0	), // U+1D411; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL R
/*M_BOLD             */	DEADTRANS(	L'r'	,0x212c	,0xdc2b	,DKF_0	), // U+1D42B; input D835 high surrogate first; MATHEMATICAL BOLD SMALL R
/*M_BOLD             */	DEADTRANS(	L'S'	,0x212c	,0xdc12	,DKF_0	), // U+1D412; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL S
/*M_BOLD             */	DEADTRANS(	L's'	,0x212c	,0xdc2c	,DKF_0	), // U+1D42C; input D835 high surrogate first; MATHEMATICAL BOLD SMALL S
/*M_BOLD             */	DEADTRANS(	L'T'	,0x212c	,0xdc13	,DKF_0	), // U+1D413; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL T
/*M_BOLD             */	DEADTRANS(	L't'	,0x212c	,0xdc2d	,DKF_0	), // U+1D42D; input D835 high surrogate first; MATHEMATICAL BOLD SMALL T
/*M_BOLD             */	DEADTRANS(	L'U'	,0x212c	,0xdc14	,DKF_0	), // U+1D414; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL U
/*M_BOLD             */	DEADTRANS(	L'u'	,0x212c	,0xdc2e	,DKF_0	), // U+1D42E; input D835 high surrogate first; MATHEMATICAL BOLD SMALL U
/*M_BOLD             */	DEADTRANS(	L'V'	,0x212c	,0xdc15	,DKF_0	), // U+1D415; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL V
/*M_BOLD             */	DEADTRANS(	L'v'	,0x212c	,0xdc2f	,DKF_0	), // U+1D42F; input D835 high surrogate first; MATHEMATICAL BOLD SMALL V
/*M_BOLD             */	DEADTRANS(	L'W'	,0x212c	,0xdc16	,DKF_0	), // U+1D416; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL W
/*M_BOLD             */	DEADTRANS(	L'w'	,0x212c	,0xdc30	,DKF_0	), // U+1D430; input D835 high surrogate first; MATHEMATICAL BOLD SMALL W
/*M_BOLD             */	DEADTRANS(	L'X'	,0x212c	,0xdc17	,DKF_0	), // U+1D417; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL X
/*M_BOLD             */	DEADTRANS(	L'x'	,0x212c	,0xdc31	,DKF_0	), // U+1D431; input D835 high surrogate first; MATHEMATICAL BOLD SMALL X
/*M_BOLD             */	DEADTRANS(	L'Y'	,0x212c	,0xdc18	,DKF_0	), // U+1D418; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL Y
/*M_BOLD             */	DEADTRANS(	L'y'	,0x212c	,0xdc32	,DKF_0	), // U+1D432; input D835 high surrogate first; MATHEMATICAL BOLD SMALL Y
/*M_BOLD             */	DEADTRANS(	L'Z'	,0x212c	,0xdc19	,DKF_0	), // U+1D419; input D835 high surrogate first; MATHEMATICAL BOLD CAPITAL Z
/*M_BOLD             */	DEADTRANS(	L'z'	,0x212c	,0xdc33	,DKF_0	), // U+1D433; input D835 high surrogate first; MATHEMATICAL BOLD SMALL Z
/*M_BOLD             */	DEADTRANS(	0x0024	,0x212c	,0x211b	,CHAIN	), // SCRIPT CAPITAL R
/*M_BOLD             */	DEADTRANS(	0x0025	,0x212c	,0x211c	,CHAIN	), // BLACK-LETTER CAPITAL R
/*M_BOLD             */	DEADTRANS(	0x0026	,0x212c	,0x2131	,CHAIN	), // SCRIPT CAPITAL F
/*M_BOLD             */	DEADTRANS(	0x002f	,0x212c	,0x2110	,CHAIN	), // SCRIPT CAPITAL I
/*M_BOLD_ITALIC      */	DEADTRANS(	L'A'	,0x2110	,0xdc68	,DKF_0	), // U+1D468; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL A
/*M_BOLD_ITALIC      */	DEADTRANS(	L'a'	,0x2110	,0xdc82	,DKF_0	), // U+1D482; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL A
/*M_BOLD_ITALIC      */	DEADTRANS(	L'B'	,0x2110	,0xdc69	,DKF_0	), // U+1D469; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL B
/*M_BOLD_ITALIC      */	DEADTRANS(	L'b'	,0x2110	,0xdc83	,DKF_0	), // U+1D483; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL B
/*M_BOLD_ITALIC      */	DEADTRANS(	L'C'	,0x2110	,0xdc6a	,DKF_0	), // U+1D46A; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL C
/*M_BOLD_ITALIC      */	DEADTRANS(	L'c'	,0x2110	,0xdc84	,DKF_0	), // U+1D484; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL C
/*M_BOLD_ITALIC      */	DEADTRANS(	L'D'	,0x2110	,0xdc6b	,DKF_0	), // U+1D46B; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL D
/*M_BOLD_ITALIC      */	DEADTRANS(	L'd'	,0x2110	,0xdc85	,DKF_0	), // U+1D485; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL D
/*M_BOLD_ITALIC      */	DEADTRANS(	L'E'	,0x2110	,0xdc6c	,DKF_0	), // U+1D46C; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL E
/*M_BOLD_ITALIC      */	DEADTRANS(	L'e'	,0x2110	,0xdc86	,DKF_0	), // U+1D486; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL E
/*M_BOLD_ITALIC      */	DEADTRANS(	L'F'	,0x2110	,0xdc6d	,DKF_0	), // U+1D46D; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL F
/*M_BOLD_ITALIC      */	DEADTRANS(	L'f'	,0x2110	,0xdc87	,DKF_0	), // U+1D487; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL F
/*M_BOLD_ITALIC      */	DEADTRANS(	L'G'	,0x2110	,0xdc6e	,DKF_0	), // U+1D46E; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL G
/*M_BOLD_ITALIC      */	DEADTRANS(	L'g'	,0x2110	,0xdc88	,DKF_0	), // U+1D488; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL G
/*M_BOLD_ITALIC      */	DEADTRANS(	L'H'	,0x2110	,0xdc6f	,DKF_0	), // U+1D46F; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL H
/*M_BOLD_ITALIC      */	DEADTRANS(	L'h'	,0x2110	,0xdc89	,DKF_0	), // U+1D489; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL H
/*M_BOLD_ITALIC      */	DEADTRANS(	L'I'	,0x2110	,0xdc70	,DKF_0	), // U+1D470; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL I
/*M_BOLD_ITALIC      */	DEADTRANS(	L'i'	,0x2110	,0xdc8a	,DKF_0	), // U+1D48A; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL I
/*M_BOLD_ITALIC      */	DEADTRANS(	L'J'	,0x2110	,0xdc71	,DKF_0	), // U+1D471; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL J
/*M_BOLD_ITALIC      */	DEADTRANS(	L'j'	,0x2110	,0xdc8b	,DKF_0	), // U+1D48B; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL J
/*M_BOLD_ITALIC      */	DEADTRANS(	L'K'	,0x2110	,0xdc72	,DKF_0	), // U+1D472; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL K
/*M_BOLD_ITALIC      */	DEADTRANS(	L'k'	,0x2110	,0xdc8c	,DKF_0	), // U+1D48C; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL K
/*M_BOLD_ITALIC      */	DEADTRANS(	L'L'	,0x2110	,0xdc73	,DKF_0	), // U+1D473; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL L
/*M_BOLD_ITALIC      */	DEADTRANS(	L'l'	,0x2110	,0xdc8d	,DKF_0	), // U+1D48D; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL L
/*M_BOLD_ITALIC      */	DEADTRANS(	L'M'	,0x2110	,0xdc74	,DKF_0	), // U+1D474; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL M
/*M_BOLD_ITALIC      */	DEADTRANS(	L'm'	,0x2110	,0xdc8e	,DKF_0	), // U+1D48E; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL M
/*M_BOLD_ITALIC      */	DEADTRANS(	L'N'	,0x2110	,0xdc75	,DKF_0	), // U+1D475; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL N
/*M_BOLD_ITALIC      */	DEADTRANS(	L'n'	,0x2110	,0xdc8f	,DKF_0	), // U+1D48F; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL N
/*M_BOLD_ITALIC      */	DEADTRANS(	L'O'	,0x2110	,0xdc76	,DKF_0	), // U+1D476; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL O
/*M_BOLD_ITALIC      */	DEADTRANS(	L'o'	,0x2110	,0xdc90	,DKF_0	), // U+1D490; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL O
/*M_BOLD_ITALIC      */	DEADTRANS(	L'P'	,0x2110	,0xdc77	,DKF_0	), // U+1D477; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL P
/*M_BOLD_ITALIC      */	DEADTRANS(	L'p'	,0x2110	,0xdc91	,DKF_0	), // U+1D491; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL P
/*M_BOLD_ITALIC      */	DEADTRANS(	L'Q'	,0x2110	,0xdc78	,DKF_0	), // U+1D478; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL Q
/*M_BOLD_ITALIC      */	DEADTRANS(	L'q'	,0x2110	,0xdc92	,DKF_0	), // U+1D492; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL Q
/*M_BOLD_ITALIC      */	DEADTRANS(	L'R'	,0x2110	,0xdc79	,DKF_0	), // U+1D479; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL R
/*M_BOLD_ITALIC      */	DEADTRANS(	L'r'	,0x2110	,0xdc93	,DKF_0	), // U+1D493; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL R
/*M_BOLD_ITALIC      */	DEADTRANS(	L'S'	,0x2110	,0xdc7a	,DKF_0	), // U+1D47A; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL S
/*M_BOLD_ITALIC      */	DEADTRANS(	L's'	,0x2110	,0xdc94	,DKF_0	), // U+1D494; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL S
/*M_BOLD_ITALIC      */	DEADTRANS(	L'T'	,0x2110	,0xdc7b	,DKF_0	), // U+1D47B; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL T
/*M_BOLD_ITALIC      */	DEADTRANS(	L't'	,0x2110	,0xdc95	,DKF_0	), // U+1D495; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL T
/*M_BOLD_ITALIC      */	DEADTRANS(	L'U'	,0x2110	,0xdc7c	,DKF_0	), // U+1D47C; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL U
/*M_BOLD_ITALIC      */	DEADTRANS(	L'u'	,0x2110	,0xdc96	,DKF_0	), // U+1D496; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL U
/*M_BOLD_ITALIC      */	DEADTRANS(	L'V'	,0x2110	,0xdc7d	,DKF_0	), // U+1D47D; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL V
/*M_BOLD_ITALIC      */	DEADTRANS(	L'v'	,0x2110	,0xdc97	,DKF_0	), // U+1D497; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL V
/*M_BOLD_ITALIC      */	DEADTRANS(	L'W'	,0x2110	,0xdc7e	,DKF_0	), // U+1D47E; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL W
/*M_BOLD_ITALIC      */	DEADTRANS(	L'w'	,0x2110	,0xdc98	,DKF_0	), // U+1D498; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL W
/*M_BOLD_ITALIC      */	DEADTRANS(	L'X'	,0x2110	,0xdc7f	,DKF_0	), // U+1D47F; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL X
/*M_BOLD_ITALIC      */	DEADTRANS(	L'x'	,0x2110	,0xdc99	,DKF_0	), // U+1D499; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL X
/*M_BOLD_ITALIC      */	DEADTRANS(	L'Y'	,0x2110	,0xdc80	,DKF_0	), // U+1D480; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL Y
/*M_BOLD_ITALIC      */	DEADTRANS(	L'y'	,0x2110	,0xdc9a	,DKF_0	), // U+1D49A; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL Y
/*M_BOLD_ITALIC      */	DEADTRANS(	L'Z'	,0x2110	,0xdc81	,DKF_0	), // U+1D481; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC CAPITAL Z
/*M_BOLD_ITALIC      */	DEADTRANS(	L'z'	,0x2110	,0xdc9b	,DKF_0	), // U+1D49B; input D835 high surrogate first; MATHEMATICAL BOLD ITALIC SMALL Z
/*M_BOLD_ITALIC      */	DEADTRANS(	0x0024	,0x2110	,0x2130	,CHAIN	), // SCRIPT CAPITAL E
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'A'	,0x211c	,0xdd6c	,DKF_0	), // U+1D56C; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL A
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'a'	,0x211c	,0xdd86	,DKF_0	), // U+1D586; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL A
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'B'	,0x211c	,0xdd6d	,DKF_0	), // U+1D56D; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL B
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'b'	,0x211c	,0xdd87	,DKF_0	), // U+1D587; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL B
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'C'	,0x211c	,0xdd6e	,DKF_0	), // U+1D56E; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL C
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'c'	,0x211c	,0xdd88	,DKF_0	), // U+1D588; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL C
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'D'	,0x211c	,0xdd6f	,DKF_0	), // U+1D56F; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL D
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'd'	,0x211c	,0xdd89	,DKF_0	), // U+1D589; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL D
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'E'	,0x211c	,0xdd70	,DKF_0	), // U+1D570; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL E
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'e'	,0x211c	,0xdd8a	,DKF_0	), // U+1D58A; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL E
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'F'	,0x211c	,0xdd71	,DKF_0	), // U+1D571; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL F
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'f'	,0x211c	,0xdd8b	,DKF_0	), // U+1D58B; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL F
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'G'	,0x211c	,0xdd72	,DKF_0	), // U+1D572; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL G
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'g'	,0x211c	,0xdd8c	,DKF_0	), // U+1D58C; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL G
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'H'	,0x211c	,0xdd73	,DKF_0	), // U+1D573; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL H
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'h'	,0x211c	,0xdd8d	,DKF_0	), // U+1D58D; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL H
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'I'	,0x211c	,0xdd74	,DKF_0	), // U+1D574; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL I
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'i'	,0x211c	,0xdd8e	,DKF_0	), // U+1D58E; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL I
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'J'	,0x211c	,0xdd75	,DKF_0	), // U+1D575; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL J
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'j'	,0x211c	,0xdd8f	,DKF_0	), // U+1D58F; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL J
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'K'	,0x211c	,0xdd76	,DKF_0	), // U+1D576; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL K
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'k'	,0x211c	,0xdd90	,DKF_0	), // U+1D590; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL K
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'L'	,0x211c	,0xdd77	,DKF_0	), // U+1D577; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL L
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'l'	,0x211c	,0xdd91	,DKF_0	), // U+1D591; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL L
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'M'	,0x211c	,0xdd78	,DKF_0	), // U+1D578; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL M
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'm'	,0x211c	,0xdd92	,DKF_0	), // U+1D592; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL M
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'N'	,0x211c	,0xdd79	,DKF_0	), // U+1D579; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL N
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'n'	,0x211c	,0xdd93	,DKF_0	), // U+1D593; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL N
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'O'	,0x211c	,0xdd7a	,DKF_0	), // U+1D57A; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL O
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'o'	,0x211c	,0xdd94	,DKF_0	), // U+1D594; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL O
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'P'	,0x211c	,0xdd7b	,DKF_0	), // U+1D57B; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL P
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'p'	,0x211c	,0xdd95	,DKF_0	), // U+1D595; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL P
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'Q'	,0x211c	,0xdd7c	,DKF_0	), // U+1D57C; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL Q
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'q'	,0x211c	,0xdd96	,DKF_0	), // U+1D596; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL Q
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'R'	,0x211c	,0xdd7d	,DKF_0	), // U+1D57D; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL R
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'r'	,0x211c	,0xdd97	,DKF_0	), // U+1D597; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL R
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'S'	,0x211c	,0xdd7e	,DKF_0	), // U+1D57E; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL S
/*M_BOLD_SCRIPT      */	DEADTRANS(	L's'	,0x211c	,0xdd98	,DKF_0	), // U+1D598; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL S
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'T'	,0x211c	,0xdd7f	,DKF_0	), // U+1D57F; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL T
/*M_BOLD_SCRIPT      */	DEADTRANS(	L't'	,0x211c	,0xdd99	,DKF_0	), // U+1D599; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL T
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'U'	,0x211c	,0xdd80	,DKF_0	), // U+1D580; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL U
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'u'	,0x211c	,0xdd9a	,DKF_0	), // U+1D59A; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL U
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'V'	,0x211c	,0xdd81	,DKF_0	), // U+1D581; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL V
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'v'	,0x211c	,0xdd9b	,DKF_0	), // U+1D59B; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL V
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'W'	,0x211c	,0xdd82	,DKF_0	), // U+1D582; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL W
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'w'	,0x211c	,0xdd9c	,DKF_0	), // U+1D59C; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL W
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'X'	,0x211c	,0xdd83	,DKF_0	), // U+1D583; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL X
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'x'	,0x211c	,0xdd9d	,DKF_0	), // U+1D59D; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL X
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'Y'	,0x211c	,0xdd84	,DKF_0	), // U+1D584; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL Y
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'y'	,0x211c	,0xdd9e	,DKF_0	), // U+1D59E; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL Y
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'Z'	,0x211c	,0xdd85	,DKF_0	), // U+1D585; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR CAPITAL Z
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'z'	,0x211c	,0xdd9f	,DKF_0	), // U+1D59F; input D835 high surrogate first; MATHEMATICAL BOLD FRAKTUR SMALL Z
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'A'	,0x2131	,0xdcd0	,DKF_0	), // U+1D4D0; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL A
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'a'	,0x2131	,0xdcea	,DKF_0	), // U+1D4EA; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL A
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'B'	,0x2131	,0xdcd1	,DKF_0	), // U+1D4D1; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL B
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'b'	,0x2131	,0xdceb	,DKF_0	), // U+1D4EB; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL B
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'C'	,0x2131	,0xdcd2	,DKF_0	), // U+1D4D2; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL C
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'c'	,0x2131	,0xdcec	,DKF_0	), // U+1D4EC; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL C
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'D'	,0x2131	,0xdcd3	,DKF_0	), // U+1D4D3; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL D
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'd'	,0x2131	,0xdced	,DKF_0	), // U+1D4ED; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL D
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'E'	,0x2131	,0xdcd4	,DKF_0	), // U+1D4D4; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL E
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'e'	,0x2131	,0xdcee	,DKF_0	), // U+1D4EE; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL E
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'F'	,0x2131	,0xdcd5	,DKF_0	), // U+1D4D5; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL F
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'f'	,0x2131	,0xdcef	,DKF_0	), // U+1D4EF; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL F
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'G'	,0x2131	,0xdcd6	,DKF_0	), // U+1D4D6; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL G
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'g'	,0x2131	,0xdcf0	,DKF_0	), // U+1D4F0; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL G
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'H'	,0x2131	,0xdcd7	,DKF_0	), // U+1D4D7; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL H
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'h'	,0x2131	,0xdcf1	,DKF_0	), // U+1D4F1; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL H
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'I'	,0x2131	,0xdcd8	,DKF_0	), // U+1D4D8; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL I
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'i'	,0x2131	,0xdcf2	,DKF_0	), // U+1D4F2; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL I
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'J'	,0x2131	,0xdcd9	,DKF_0	), // U+1D4D9; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL J
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'j'	,0x2131	,0xdcf3	,DKF_0	), // U+1D4F3; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL J
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'K'	,0x2131	,0xdcda	,DKF_0	), // U+1D4DA; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL K
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'k'	,0x2131	,0xdcf4	,DKF_0	), // U+1D4F4; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL K
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'L'	,0x2131	,0xdcdb	,DKF_0	), // U+1D4DB; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL L
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'l'	,0x2131	,0xdcf5	,DKF_0	), // U+1D4F5; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL L
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'M'	,0x2131	,0xdcdc	,DKF_0	), // U+1D4DC; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL M
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'm'	,0x2131	,0xdcf6	,DKF_0	), // U+1D4F6; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL M
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'N'	,0x2131	,0xdcdd	,DKF_0	), // U+1D4DD; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL N
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'n'	,0x2131	,0xdcf7	,DKF_0	), // U+1D4F7; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL N
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'O'	,0x2131	,0xdcde	,DKF_0	), // U+1D4DE; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL O
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'o'	,0x2131	,0xdcf8	,DKF_0	), // U+1D4F8; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL O
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'P'	,0x2131	,0xdcdf	,DKF_0	), // U+1D4DF; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL P
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'p'	,0x2131	,0xdcf9	,DKF_0	), // U+1D4F9; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL P
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'Q'	,0x2131	,0xdce0	,DKF_0	), // U+1D4E0; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL Q
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'q'	,0x2131	,0xdcfa	,DKF_0	), // U+1D4FA; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL Q
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'R'	,0x2131	,0xdce1	,DKF_0	), // U+1D4E1; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL R
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'r'	,0x2131	,0xdcfb	,DKF_0	), // U+1D4FB; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL R
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'S'	,0x2131	,0xdce2	,DKF_0	), // U+1D4E2; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL S
/*M_BOLD_SCRIPT      */	DEADTRANS(	L's'	,0x2131	,0xdcfc	,DKF_0	), // U+1D4FC; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL S
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'T'	,0x2131	,0xdce3	,DKF_0	), // U+1D4E3; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL T
/*M_BOLD_SCRIPT      */	DEADTRANS(	L't'	,0x2131	,0xdcfd	,DKF_0	), // U+1D4FD; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL T
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'U'	,0x2131	,0xdce4	,DKF_0	), // U+1D4E4; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL U
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'u'	,0x2131	,0xdcfe	,DKF_0	), // U+1D4FE; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL U
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'V'	,0x2131	,0xdce5	,DKF_0	), // U+1D4E5; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL V
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'v'	,0x2131	,0xdcff	,DKF_0	), // U+1D4FF; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL V
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'W'	,0x2131	,0xdce6	,DKF_0	), // U+1D4E6; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL W
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'w'	,0x2131	,0xdd00	,DKF_0	), // U+1D500; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL W
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'X'	,0x2131	,0xdce7	,DKF_0	), // U+1D4E7; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL X
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'x'	,0x2131	,0xdd01	,DKF_0	), // U+1D501; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL X
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'Y'	,0x2131	,0xdce8	,DKF_0	), // U+1D4E8; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL Y
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'y'	,0x2131	,0xdd02	,DKF_0	), // U+1D502; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL Y
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'Z'	,0x2131	,0xdce9	,DKF_0	), // U+1D4E9; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT CAPITAL Z
/*M_BOLD_SCRIPT      */	DEADTRANS(	L'z'	,0x2131	,0xdd03	,DKF_0	), // U+1D503; input D835 high surrogate first; MATHEMATICAL BOLD SCRIPT SMALL Z
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'A'	,0x2115	,0xdd38	,DKF_0	), // U+1D538; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL A
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'a'	,0x2115	,0xdd52	,DKF_0	), // U+1D552; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL A
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'B'	,0x2115	,0xdd39	,DKF_0	), // U+1D539; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL B
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'b'	,0x2115	,0xdd53	,DKF_0	), // U+1D553; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL B
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'C'	,0x2115	,0x2102	,DKF_0	), // DOUBLE-STRUCK CAPITAL C
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'c'	,0x2115	,0xdd54	,DKF_0	), // U+1D554; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL C
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'D'	,0x2115	,0xdd3b	,DKF_0	), // U+1D53B; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL D
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'd'	,0x2115	,0xdd55	,DKF_0	), // U+1D555; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL D
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'E'	,0x2115	,0xdd3c	,DKF_0	), // U+1D53C; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL E
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'e'	,0x2115	,0xdd56	,DKF_0	), // U+1D556; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL E
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'F'	,0x2115	,0xdd3d	,DKF_0	), // U+1D53D; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL F
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'f'	,0x2115	,0xdd57	,DKF_0	), // U+1D557; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL F
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'G'	,0x2115	,0xdd3e	,DKF_0	), // U+1D53E; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL G
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'g'	,0x2115	,0xdd58	,DKF_0	), // U+1D558; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL G
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'H'	,0x2115	,0x210d	,DKF_0	), // DOUBLE-STRUCK CAPITAL H
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'h'	,0x2115	,0xdd59	,DKF_0	), // U+1D559; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL H
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'I'	,0x2115	,0xdd40	,DKF_0	), // U+1D540; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL I
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'i'	,0x2115	,0xdd5a	,DKF_0	), // U+1D55A; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL I
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'J'	,0x2115	,0xdd41	,DKF_0	), // U+1D541; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL J
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'j'	,0x2115	,0xdd5b	,DKF_0	), // U+1D55B; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL J
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'K'	,0x2115	,0xdd42	,DKF_0	), // U+1D542; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL K
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'k'	,0x2115	,0xdd5c	,DKF_0	), // U+1D55C; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL K
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'L'	,0x2115	,0xdd43	,DKF_0	), // U+1D543; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL L
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'l'	,0x2115	,0xdd5d	,DKF_0	), // U+1D55D; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL L
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'M'	,0x2115	,0xdd44	,DKF_0	), // U+1D544; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL M
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'm'	,0x2115	,0xdd5e	,DKF_0	), // U+1D55E; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL M
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'N'	,0x2115	,0x2115	,DKF_0	), // DOUBLE-STRUCK CAPITAL N
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'n'	,0x2115	,0xdd5f	,DKF_0	), // U+1D55F; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL N
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'O'	,0x2115	,0xdd46	,DKF_0	), // U+1D546; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL O
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'o'	,0x2115	,0xdd60	,DKF_0	), // U+1D560; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL O
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'P'	,0x2115	,0x2119	,DKF_0	), // DOUBLE-STRUCK CAPITAL P
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'p'	,0x2115	,0xdd61	,DKF_0	), // U+1D561; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL P
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'Q'	,0x2115	,0x211a	,DKF_0	), // DOUBLE-STRUCK CAPITAL Q
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'q'	,0x2115	,0xdd62	,DKF_0	), // U+1D562; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL Q
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'R'	,0x2115	,0x211d	,DKF_0	), // DOUBLE-STRUCK CAPITAL R
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'r'	,0x2115	,0xdd63	,DKF_0	), // U+1D563; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL R
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'S'	,0x2115	,0xdd4a	,DKF_0	), // U+1D54A; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL S
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L's'	,0x2115	,0xdd64	,DKF_0	), // U+1D564; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL S
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'T'	,0x2115	,0xdd4b	,DKF_0	), // U+1D54B; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL T
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L't'	,0x2115	,0xdd65	,DKF_0	), // U+1D565; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL T
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'U'	,0x2115	,0xdd4c	,DKF_0	), // U+1D54C; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL U
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'u'	,0x2115	,0xdd66	,DKF_0	), // U+1D566; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL U
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'V'	,0x2115	,0xdd4d	,DKF_0	), // U+1D54D; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL V
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'v'	,0x2115	,0xdd67	,DKF_0	), // U+1D567; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL V
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'W'	,0x2115	,0xdd4e	,DKF_0	), // U+1D54E; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL W
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'w'	,0x2115	,0xdd68	,DKF_0	), // U+1D568; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL W
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'X'	,0x2115	,0xdd4f	,DKF_0	), // U+1D54F; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL X
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'x'	,0x2115	,0xdd69	,DKF_0	), // U+1D569; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL X
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'Y'	,0x2115	,0xdd50	,DKF_0	), // U+1D550; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK CAPITAL Y
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'y'	,0x2115	,0xdd6a	,DKF_0	), // U+1D56A; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL Y
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'Z'	,0x2115	,0x2124	,DKF_0	), // DOUBLE-STRUCK CAPITAL Z
/*M_DOUBLE-STRUCK    */	DEADTRANS(	L'z'	,0x2115	,0xdd6b	,DKF_0	), // U+1D56B; input D835 high surrogate first; MATHEMATICAL DOUBLE-STRUCK SMALL Z
/*M_FRAKTUR          */	DEADTRANS(	L'A'	,0x212d	,0xdd04	,DKF_0	), // U+1D504; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL A
/*M_FRAKTUR          */	DEADTRANS(	L'a'	,0x212d	,0xdd1e	,DKF_0	), // U+1D51E; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL A
/*M_FRAKTUR          */	DEADTRANS(	L'B'	,0x212d	,0xdd05	,DKF_0	), // U+1D505; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL B
/*M_FRAKTUR          */	DEADTRANS(	L'b'	,0x212d	,0xdd1f	,DKF_0	), // U+1D51F; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL B
/*M_FRAKTUR          */	DEADTRANS(	L'C'	,0x212d	,0x212d	,DKF_0	), // BLACK-LETTER CAPITAL C
/*M_FRAKTUR          */	DEADTRANS(	L'c'	,0x212d	,0xdd20	,DKF_0	), // U+1D520; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL C
/*M_FRAKTUR          */	DEADTRANS(	L'D'	,0x212d	,0xdd07	,DKF_0	), // U+1D507; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL D
/*M_FRAKTUR          */	DEADTRANS(	L'd'	,0x212d	,0xdd21	,DKF_0	), // U+1D521; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL D
/*M_FRAKTUR          */	DEADTRANS(	L'E'	,0x212d	,0xdd08	,DKF_0	), // U+1D508; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL E
/*M_FRAKTUR          */	DEADTRANS(	L'e'	,0x212d	,0xdd22	,DKF_0	), // U+1D522; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL E
/*M_FRAKTUR          */	DEADTRANS(	L'F'	,0x212d	,0xdd09	,DKF_0	), // U+1D509; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL F
/*M_FRAKTUR          */	DEADTRANS(	L'f'	,0x212d	,0xdd23	,DKF_0	), // U+1D523; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL F
/*M_FRAKTUR          */	DEADTRANS(	L'G'	,0x212d	,0xdd0a	,DKF_0	), // U+1D50A; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL G
/*M_FRAKTUR          */	DEADTRANS(	L'g'	,0x212d	,0xdd24	,DKF_0	), // U+1D524; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL G
/*M_FRAKTUR          */	DEADTRANS(	L'H'	,0x212d	,0x210c	,DKF_0	), // BLACK-LETTER CAPITAL H
/*M_FRAKTUR          */	DEADTRANS(	L'h'	,0x212d	,0xdd25	,DKF_0	), // U+1D525; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL H
/*M_FRAKTUR          */	DEADTRANS(	L'I'	,0x212d	,0x2111	,DKF_0	), // BLACK-LETTER CAPITAL I
/*M_FRAKTUR          */	DEADTRANS(	L'i'	,0x212d	,0xdd26	,DKF_0	), // U+1D526; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL I
/*M_FRAKTUR          */	DEADTRANS(	L'J'	,0x212d	,0xdd0d	,DKF_0	), // U+1D50D; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL J
/*M_FRAKTUR          */	DEADTRANS(	L'j'	,0x212d	,0xdd27	,DKF_0	), // U+1D527; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL J
/*M_FRAKTUR          */	DEADTRANS(	L'K'	,0x212d	,0xdd0e	,DKF_0	), // U+1D50E; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL K
/*M_FRAKTUR          */	DEADTRANS(	L'k'	,0x212d	,0xdd28	,DKF_0	), // U+1D528; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL K
/*M_FRAKTUR          */	DEADTRANS(	L'L'	,0x212d	,0xdd0f	,DKF_0	), // U+1D50F; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL L
/*M_FRAKTUR          */	DEADTRANS(	L'l'	,0x212d	,0xdd29	,DKF_0	), // U+1D529; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL L
/*M_FRAKTUR          */	DEADTRANS(	L'M'	,0x212d	,0xdd10	,DKF_0	), // U+1D510; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL M
/*M_FRAKTUR          */	DEADTRANS(	L'm'	,0x212d	,0xdd2a	,DKF_0	), // U+1D52A; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL M
/*M_FRAKTUR          */	DEADTRANS(	L'N'	,0x212d	,0xdd11	,DKF_0	), // U+1D511; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL N
/*M_FRAKTUR          */	DEADTRANS(	L'n'	,0x212d	,0xdd2b	,DKF_0	), // U+1D52B; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL N
/*M_FRAKTUR          */	DEADTRANS(	L'O'	,0x212d	,0xdd12	,DKF_0	), // U+1D512; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL O
/*M_FRAKTUR          */	DEADTRANS(	L'o'	,0x212d	,0xdd2c	,DKF_0	), // U+1D52C; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL O
/*M_FRAKTUR          */	DEADTRANS(	L'P'	,0x212d	,0xdd13	,DKF_0	), // U+1D513; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL P
/*M_FRAKTUR          */	DEADTRANS(	L'p'	,0x212d	,0xdd2d	,DKF_0	), // U+1D52D; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL P
/*M_FRAKTUR          */	DEADTRANS(	L'Q'	,0x212d	,0xdd14	,DKF_0	), // U+1D514; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL Q
/*M_FRAKTUR          */	DEADTRANS(	L'q'	,0x212d	,0xdd2e	,DKF_0	), // U+1D52E; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL Q
/*M_FRAKTUR          */	DEADTRANS(	L'R'	,0x212d	,0x211c	,DKF_0	), // BLACK-LETTER CAPITAL R
/*M_FRAKTUR          */	DEADTRANS(	L'r'	,0x212d	,0xdd2f	,DKF_0	), // U+1D52F; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL R
/*M_FRAKTUR          */	DEADTRANS(	L'S'	,0x212d	,0xdd16	,DKF_0	), // U+1D516; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL S
/*M_FRAKTUR          */	DEADTRANS(	L's'	,0x212d	,0xdd30	,DKF_0	), // U+1D530; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL S
/*M_FRAKTUR          */	DEADTRANS(	L'T'	,0x212d	,0xdd17	,DKF_0	), // U+1D517; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL T
/*M_FRAKTUR          */	DEADTRANS(	L't'	,0x212d	,0xdd31	,DKF_0	), // U+1D531; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL T
/*M_FRAKTUR          */	DEADTRANS(	L'U'	,0x212d	,0xdd18	,DKF_0	), // U+1D518; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL U
/*M_FRAKTUR          */	DEADTRANS(	L'u'	,0x212d	,0xdd32	,DKF_0	), // U+1D532; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL U
/*M_FRAKTUR          */	DEADTRANS(	L'V'	,0x212d	,0xdd19	,DKF_0	), // U+1D519; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL V
/*M_FRAKTUR          */	DEADTRANS(	L'v'	,0x212d	,0xdd33	,DKF_0	), // U+1D533; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL V
/*M_FRAKTUR          */	DEADTRANS(	L'W'	,0x212d	,0xdd1a	,DKF_0	), // U+1D51A; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL W
/*M_FRAKTUR          */	DEADTRANS(	L'w'	,0x212d	,0xdd34	,DKF_0	), // U+1D534; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL W
/*M_FRAKTUR          */	DEADTRANS(	L'X'	,0x212d	,0xdd1b	,DKF_0	), // U+1D51B; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL X
/*M_FRAKTUR          */	DEADTRANS(	L'x'	,0x212d	,0xdd35	,DKF_0	), // U+1D535; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL X
/*M_FRAKTUR          */	DEADTRANS(	L'Y'	,0x212d	,0xdd1c	,DKF_0	), // U+1D51C; input D835 high surrogate first; MATHEMATICAL FRAKTUR CAPITAL Y
/*M_FRAKTUR          */	DEADTRANS(	L'y'	,0x212d	,0xdd36	,DKF_0	), // U+1D536; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL Y
/*M_FRAKTUR          */	DEADTRANS(	L'Z'	,0x212d	,0x2128	,DKF_0	), // BLACK-LETTER CAPITAL Z
/*M_FRAKTUR          */	DEADTRANS(	L'z'	,0x212d	,0xdd37	,DKF_0	), // U+1D537; input D835 high surrogate first; MATHEMATICAL FRAKTUR SMALL Z
/*M_FRAKTUR          */	DEADTRANS(	0x002a	,0x212d	,0x211c	,CHAIN	), // BLACK-LETTER CAPITAL R
/*M_ITALIC           */	DEADTRANS(	L'A'	,0x210e	,0xdc34	,DKF_0	), // U+1D434; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL A
/*M_ITALIC           */	DEADTRANS(	L'a'	,0x210e	,0xdc4e	,DKF_0	), // U+1D44E; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL A
/*M_ITALIC           */	DEADTRANS(	L'B'	,0x210e	,0xdc35	,DKF_0	), // U+1D435; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL B
/*M_ITALIC           */	DEADTRANS(	L'b'	,0x210e	,0xdc4f	,DKF_0	), // U+1D44F; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL B
/*M_ITALIC           */	DEADTRANS(	L'C'	,0x210e	,0xdc36	,DKF_0	), // U+1D436; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL C
/*M_ITALIC           */	DEADTRANS(	L'c'	,0x210e	,0xdc50	,DKF_0	), // U+1D450; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL C
/*M_ITALIC           */	DEADTRANS(	L'D'	,0x210e	,0xdc37	,DKF_0	), // U+1D437; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL D
/*M_ITALIC           */	DEADTRANS(	L'd'	,0x210e	,0xdc51	,DKF_0	), // U+1D451; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL D
/*M_ITALIC           */	DEADTRANS(	L'E'	,0x210e	,0xdc38	,DKF_0	), // U+1D438; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL E
/*M_ITALIC           */	DEADTRANS(	L'e'	,0x210e	,0xdc52	,DKF_0	), // U+1D452; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL E
/*M_ITALIC           */	DEADTRANS(	L'F'	,0x210e	,0xdc39	,DKF_0	), // U+1D439; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL F
/*M_ITALIC           */	DEADTRANS(	L'f'	,0x210e	,0xdc53	,DKF_0	), // U+1D453; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL F
/*M_ITALIC           */	DEADTRANS(	L'G'	,0x210e	,0xdc3a	,DKF_0	), // U+1D43A; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL G
/*M_ITALIC           */	DEADTRANS(	L'g'	,0x210e	,0xdc54	,DKF_0	), // U+1D454; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL G
/*M_ITALIC           */	DEADTRANS(	L'H'	,0x210e	,0xdc3b	,DKF_0	), // U+1D43B; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL H
/*M_ITALIC           */	DEADTRANS(	L'h'	,0x210e	,0x210e	,DKF_0	), // PLANCK CONSTANT
/*M_ITALIC           */	DEADTRANS(	L'I'	,0x210e	,0xdc3c	,DKF_0	), // U+1D43C; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL I
/*M_ITALIC           */	DEADTRANS(	L'i'	,0x210e	,0xdc56	,DKF_0	), // U+1D456; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL I
/*M_ITALIC           */	DEADTRANS(	L'J'	,0x210e	,0xdc3d	,DKF_0	), // U+1D43D; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL J
/*M_ITALIC           */	DEADTRANS(	L'j'	,0x210e	,0xdc57	,DKF_0	), // U+1D457; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL J
/*M_ITALIC           */	DEADTRANS(	L'K'	,0x210e	,0xdc3e	,DKF_0	), // U+1D43E; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL K
/*M_ITALIC           */	DEADTRANS(	L'k'	,0x210e	,0xdc58	,DKF_0	), // U+1D458; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL K
/*M_ITALIC           */	DEADTRANS(	L'L'	,0x210e	,0xdc3f	,DKF_0	), // U+1D43F; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL L
/*M_ITALIC           */	DEADTRANS(	L'l'	,0x210e	,0xdc59	,DKF_0	), // U+1D459; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL L
/*M_ITALIC           */	DEADTRANS(	L'M'	,0x210e	,0xdc40	,DKF_0	), // U+1D440; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL M
/*M_ITALIC           */	DEADTRANS(	L'm'	,0x210e	,0xdc5a	,DKF_0	), // U+1D45A; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL M
/*M_ITALIC           */	DEADTRANS(	L'N'	,0x210e	,0xdc41	,DKF_0	), // U+1D441; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL N
/*M_ITALIC           */	DEADTRANS(	L'n'	,0x210e	,0xdc5b	,DKF_0	), // U+1D45B; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL N
/*M_ITALIC           */	DEADTRANS(	L'O'	,0x210e	,0xdc42	,DKF_0	), // U+1D442; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL O
/*M_ITALIC           */	DEADTRANS(	L'o'	,0x210e	,0xdc5c	,DKF_0	), // U+1D45C; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL O
/*M_ITALIC           */	DEADTRANS(	L'P'	,0x210e	,0xdc43	,DKF_0	), // U+1D443; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL P
/*M_ITALIC           */	DEADTRANS(	L'p'	,0x210e	,0xdc5d	,DKF_0	), // U+1D45D; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL P
/*M_ITALIC           */	DEADTRANS(	L'Q'	,0x210e	,0xdc44	,DKF_0	), // U+1D444; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL Q
/*M_ITALIC           */	DEADTRANS(	L'q'	,0x210e	,0xdc5e	,DKF_0	), // U+1D45E; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL Q
/*M_ITALIC           */	DEADTRANS(	L'R'	,0x210e	,0xdc45	,DKF_0	), // U+1D445; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL R
/*M_ITALIC           */	DEADTRANS(	L'r'	,0x210e	,0xdc5f	,DKF_0	), // U+1D45F; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL R
/*M_ITALIC           */	DEADTRANS(	L'S'	,0x210e	,0xdc46	,DKF_0	), // U+1D446; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL S
/*M_ITALIC           */	DEADTRANS(	L's'	,0x210e	,0xdc60	,DKF_0	), // U+1D460; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL S
/*M_ITALIC           */	DEADTRANS(	L'T'	,0x210e	,0xdc47	,DKF_0	), // U+1D447; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL T
/*M_ITALIC           */	DEADTRANS(	L't'	,0x210e	,0xdc61	,DKF_0	), // U+1D461; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL T
/*M_ITALIC           */	DEADTRANS(	L'U'	,0x210e	,0xdc48	,DKF_0	), // U+1D448; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL U
/*M_ITALIC           */	DEADTRANS(	L'u'	,0x210e	,0xdc62	,DKF_0	), // U+1D462; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL U
/*M_ITALIC           */	DEADTRANS(	L'V'	,0x210e	,0xdc49	,DKF_0	), // U+1D449; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL V
/*M_ITALIC           */	DEADTRANS(	L'v'	,0x210e	,0xdc63	,DKF_0	), // U+1D463; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL V
/*M_ITALIC           */	DEADTRANS(	L'W'	,0x210e	,0xdc4a	,DKF_0	), // U+1D44A; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL W
/*M_ITALIC           */	DEADTRANS(	L'w'	,0x210e	,0xdc64	,DKF_0	), // U+1D464; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL W
/*M_ITALIC           */	DEADTRANS(	L'X'	,0x210e	,0xdc4b	,DKF_0	), // U+1D44B; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL X
/*M_ITALIC           */	DEADTRANS(	L'x'	,0x210e	,0xdc65	,DKF_0	), // U+1D465; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL X
/*M_ITALIC           */	DEADTRANS(	L'Y'	,0x210e	,0xdc4c	,DKF_0	), // U+1D44C; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL Y
/*M_ITALIC           */	DEADTRANS(	L'y'	,0x210e	,0xdc66	,DKF_0	), // U+1D466; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL Y
/*M_ITALIC           */	DEADTRANS(	L'Z'	,0x210e	,0xdc4d	,DKF_0	), // U+1D44D; input D835 high surrogate first; MATHEMATICAL ITALIC CAPITAL Z
/*M_ITALIC           */	DEADTRANS(	L'z'	,0x210e	,0xdc67	,DKF_0	), // U+1D467; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL Z
/*M_ITALIC           */	DEADTRANS(	0x0024	,0x210e	,0x2112	,CHAIN	), // SCRIPT CAPITAL L
/*M_ITALIC           */	DEADTRANS(	0x002a	,0x210e	,0x2110	,CHAIN	), // SCRIPT CAPITAL I
/*M_ITALIC           */	DEADTRANS(	0x002c	,0x210e	,0xdea5	,DKF_0	), // U+1D6A5; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL DOTLESS J
/*M_ITALIC           */	DEADTRANS(	0x002e	,0x210e	,0xdea4	,DKF_0	), // U+1D6A4; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL DOTLESS I
/*M_ITALIC           */	DEADTRANS(	0x003b	,0x210e	,0xdea4	,DKF_0	), // U+1D6A4; input D835 high surrogate first; MATHEMATICAL ITALIC SMALL DOTLESS I
/*M_MONOSPACE        */	DEADTRANS(	L'A'	,0x2102	,0xde70	,DKF_0	), // U+1D670; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL A
/*M_MONOSPACE        */	DEADTRANS(	L'a'	,0x2102	,0xde8a	,DKF_0	), // U+1D68A; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL A
/*M_MONOSPACE        */	DEADTRANS(	L'B'	,0x2102	,0xde71	,DKF_0	), // U+1D671; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL B
/*M_MONOSPACE        */	DEADTRANS(	L'b'	,0x2102	,0xde8b	,DKF_0	), // U+1D68B; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL B
/*M_MONOSPACE        */	DEADTRANS(	L'C'	,0x2102	,0xde72	,DKF_0	), // U+1D672; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL C
/*M_MONOSPACE        */	DEADTRANS(	L'c'	,0x2102	,0xde8c	,DKF_0	), // U+1D68C; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL C
/*M_MONOSPACE        */	DEADTRANS(	L'D'	,0x2102	,0xde73	,DKF_0	), // U+1D673; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL D
/*M_MONOSPACE        */	DEADTRANS(	L'd'	,0x2102	,0xde8d	,DKF_0	), // U+1D68D; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL D
/*M_MONOSPACE        */	DEADTRANS(	L'E'	,0x2102	,0xde74	,DKF_0	), // U+1D674; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL E
/*M_MONOSPACE        */	DEADTRANS(	L'e'	,0x2102	,0xde8e	,DKF_0	), // U+1D68E; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL E
/*M_MONOSPACE        */	DEADTRANS(	L'F'	,0x2102	,0xde75	,DKF_0	), // U+1D675; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL F
/*M_MONOSPACE        */	DEADTRANS(	L'f'	,0x2102	,0xde8f	,DKF_0	), // U+1D68F; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL F
/*M_MONOSPACE        */	DEADTRANS(	L'G'	,0x2102	,0xde76	,DKF_0	), // U+1D676; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL G
/*M_MONOSPACE        */	DEADTRANS(	L'g'	,0x2102	,0xde90	,DKF_0	), // U+1D690; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL G
/*M_MONOSPACE        */	DEADTRANS(	L'H'	,0x2102	,0xde77	,DKF_0	), // U+1D677; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL H
/*M_MONOSPACE        */	DEADTRANS(	L'h'	,0x2102	,0xde91	,DKF_0	), // U+1D691; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL H
/*M_MONOSPACE        */	DEADTRANS(	L'I'	,0x2102	,0xde78	,DKF_0	), // U+1D678; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL I
/*M_MONOSPACE        */	DEADTRANS(	L'i'	,0x2102	,0xde92	,DKF_0	), // U+1D692; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL I
/*M_MONOSPACE        */	DEADTRANS(	L'J'	,0x2102	,0xde79	,DKF_0	), // U+1D679; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL J
/*M_MONOSPACE        */	DEADTRANS(	L'j'	,0x2102	,0xde93	,DKF_0	), // U+1D693; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL J
/*M_MONOSPACE        */	DEADTRANS(	L'K'	,0x2102	,0xde7a	,DKF_0	), // U+1D67A; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL K
/*M_MONOSPACE        */	DEADTRANS(	L'k'	,0x2102	,0xde94	,DKF_0	), // U+1D694; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL K
/*M_MONOSPACE        */	DEADTRANS(	L'L'	,0x2102	,0xde7b	,DKF_0	), // U+1D67B; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL L
/*M_MONOSPACE        */	DEADTRANS(	L'l'	,0x2102	,0xde95	,DKF_0	), // U+1D695; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL L
/*M_MONOSPACE        */	DEADTRANS(	L'M'	,0x2102	,0xde7c	,DKF_0	), // U+1D67C; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL M
/*M_MONOSPACE        */	DEADTRANS(	L'm'	,0x2102	,0xde96	,DKF_0	), // U+1D696; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL M
/*M_MONOSPACE        */	DEADTRANS(	L'N'	,0x2102	,0xde7d	,DKF_0	), // U+1D67D; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL N
/*M_MONOSPACE        */	DEADTRANS(	L'n'	,0x2102	,0xde97	,DKF_0	), // U+1D697; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL N
/*M_MONOSPACE        */	DEADTRANS(	L'O'	,0x2102	,0xde7e	,DKF_0	), // U+1D67E; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL O
/*M_MONOSPACE        */	DEADTRANS(	L'o'	,0x2102	,0xde98	,DKF_0	), // U+1D698; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL O
/*M_MONOSPACE        */	DEADTRANS(	L'P'	,0x2102	,0xde7f	,DKF_0	), // U+1D67F; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL P
/*M_MONOSPACE        */	DEADTRANS(	L'p'	,0x2102	,0xde99	,DKF_0	), // U+1D699; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL P
/*M_MONOSPACE        */	DEADTRANS(	L'Q'	,0x2102	,0xde80	,DKF_0	), // U+1D680; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL Q
/*M_MONOSPACE        */	DEADTRANS(	L'q'	,0x2102	,0xde9a	,DKF_0	), // U+1D69A; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL Q
/*M_MONOSPACE        */	DEADTRANS(	L'R'	,0x2102	,0xde81	,DKF_0	), // U+1D681; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL R
/*M_MONOSPACE        */	DEADTRANS(	L'r'	,0x2102	,0xde9b	,DKF_0	), // U+1D69B; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL R
/*M_MONOSPACE        */	DEADTRANS(	L'S'	,0x2102	,0xde82	,DKF_0	), // U+1D682; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL S
/*M_MONOSPACE        */	DEADTRANS(	L's'	,0x2102	,0xde9c	,DKF_0	), // U+1D69C; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL S
/*M_MONOSPACE        */	DEADTRANS(	L'T'	,0x2102	,0xde83	,DKF_0	), // U+1D683; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL T
/*M_MONOSPACE        */	DEADTRANS(	L't'	,0x2102	,0xde9d	,DKF_0	), // U+1D69D; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL T
/*M_MONOSPACE        */	DEADTRANS(	L'U'	,0x2102	,0xde84	,DKF_0	), // U+1D684; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL U
/*M_MONOSPACE        */	DEADTRANS(	L'u'	,0x2102	,0xde9e	,DKF_0	), // U+1D69E; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL U
/*M_MONOSPACE        */	DEADTRANS(	L'V'	,0x2102	,0xde85	,DKF_0	), // U+1D685; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL V
/*M_MONOSPACE        */	DEADTRANS(	L'v'	,0x2102	,0xde9f	,DKF_0	), // U+1D69F; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL V
/*M_MONOSPACE        */	DEADTRANS(	L'W'	,0x2102	,0xde86	,DKF_0	), // U+1D686; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL W
/*M_MONOSPACE        */	DEADTRANS(	L'w'	,0x2102	,0xdea0	,DKF_0	), // U+1D6A0; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL W
/*M_MONOSPACE        */	DEADTRANS(	L'X'	,0x2102	,0xde87	,DKF_0	), // U+1D687; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL X
/*M_MONOSPACE        */	DEADTRANS(	L'x'	,0x2102	,0xdea1	,DKF_0	), // U+1D6A1; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL X
/*M_MONOSPACE        */	DEADTRANS(	L'Y'	,0x2102	,0xde88	,DKF_0	), // U+1D688; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL Y
/*M_MONOSPACE        */	DEADTRANS(	L'y'	,0x2102	,0xdea2	,DKF_0	), // U+1D6A2; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL Y
/*M_MONOSPACE        */	DEADTRANS(	L'Z'	,0x2102	,0xde89	,DKF_0	), // U+1D689; input D835 high surrogate first; MATHEMATICAL MONOSPACE CAPITAL Z
/*M_MONOSPACE        */	DEADTRANS(	L'z'	,0x2102	,0xdea3	,DKF_0	), // U+1D6A3; input D835 high surrogate first; MATHEMATICAL MONOSPACE SMALL Z
/*M_SANS             */	DEADTRANS(	L'A'	,0x210b	,0xdda0	,DKF_0	), // U+1D5A0; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL A
/*M_SANS             */	DEADTRANS(	L'a'	,0x210b	,0xddba	,DKF_0	), // U+1D5BA; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL A
/*M_SANS             */	DEADTRANS(	L'B'	,0x210b	,0xdda1	,DKF_0	), // U+1D5A1; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL B
/*M_SANS             */	DEADTRANS(	L'b'	,0x210b	,0xddbb	,DKF_0	), // U+1D5BB; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL B
/*M_SANS             */	DEADTRANS(	L'C'	,0x210b	,0xdda2	,DKF_0	), // U+1D5A2; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL C
/*M_SANS             */	DEADTRANS(	L'c'	,0x210b	,0xddbc	,DKF_0	), // U+1D5BC; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL C
/*M_SANS             */	DEADTRANS(	L'D'	,0x210b	,0xdda3	,DKF_0	), // U+1D5A3; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL D
/*M_SANS             */	DEADTRANS(	L'd'	,0x210b	,0xddbd	,DKF_0	), // U+1D5BD; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL D
/*M_SANS             */	DEADTRANS(	L'E'	,0x210b	,0xdda4	,DKF_0	), // U+1D5A4; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL E
/*M_SANS             */	DEADTRANS(	L'e'	,0x210b	,0xddbe	,DKF_0	), // U+1D5BE; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL E
/*M_SANS             */	DEADTRANS(	L'F'	,0x210b	,0xdda5	,DKF_0	), // U+1D5A5; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL F
/*M_SANS             */	DEADTRANS(	L'f'	,0x210b	,0xddbf	,DKF_0	), // U+1D5BF; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL F
/*M_SANS             */	DEADTRANS(	L'G'	,0x210b	,0xdda6	,DKF_0	), // U+1D5A6; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL G
/*M_SANS             */	DEADTRANS(	L'g'	,0x210b	,0xddc0	,DKF_0	), // U+1D5C0; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL G
/*M_SANS             */	DEADTRANS(	L'H'	,0x210b	,0xdda7	,DKF_0	), // U+1D5A7; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL H
/*M_SANS             */	DEADTRANS(	L'h'	,0x210b	,0xddc1	,DKF_0	), // U+1D5C1; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL H
/*M_SANS             */	DEADTRANS(	L'I'	,0x210b	,0xdda8	,DKF_0	), // U+1D5A8; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL I
/*M_SANS             */	DEADTRANS(	L'i'	,0x210b	,0xddc2	,DKF_0	), // U+1D5C2; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL I
/*M_SANS             */	DEADTRANS(	L'J'	,0x210b	,0xdda9	,DKF_0	), // U+1D5A9; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL J
/*M_SANS             */	DEADTRANS(	L'j'	,0x210b	,0xddc3	,DKF_0	), // U+1D5C3; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL J
/*M_SANS             */	DEADTRANS(	L'K'	,0x210b	,0xddaa	,DKF_0	), // U+1D5AA; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL K
/*M_SANS             */	DEADTRANS(	L'k'	,0x210b	,0xddc4	,DKF_0	), // U+1D5C4; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL K
/*M_SANS             */	DEADTRANS(	L'L'	,0x210b	,0xddab	,DKF_0	), // U+1D5AB; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL L
/*M_SANS             */	DEADTRANS(	L'l'	,0x210b	,0xddc5	,DKF_0	), // U+1D5C5; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL L
/*M_SANS             */	DEADTRANS(	L'M'	,0x210b	,0xddac	,DKF_0	), // U+1D5AC; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL M
/*M_SANS             */	DEADTRANS(	L'm'	,0x210b	,0xddc6	,DKF_0	), // U+1D5C6; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL M
/*M_SANS             */	DEADTRANS(	L'N'	,0x210b	,0xddad	,DKF_0	), // U+1D5AD; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL N
/*M_SANS             */	DEADTRANS(	L'n'	,0x210b	,0xddc7	,DKF_0	), // U+1D5C7; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL N
/*M_SANS             */	DEADTRANS(	L'O'	,0x210b	,0xddae	,DKF_0	), // U+1D5AE; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL O
/*M_SANS             */	DEADTRANS(	L'o'	,0x210b	,0xddc8	,DKF_0	), // U+1D5C8; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL O
/*M_SANS             */	DEADTRANS(	L'P'	,0x210b	,0xddaf	,DKF_0	), // U+1D5AF; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL P
/*M_SANS             */	DEADTRANS(	L'p'	,0x210b	,0xddc9	,DKF_0	), // U+1D5C9; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL P
/*M_SANS             */	DEADTRANS(	L'Q'	,0x210b	,0xddb0	,DKF_0	), // U+1D5B0; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL Q
/*M_SANS             */	DEADTRANS(	L'q'	,0x210b	,0xddca	,DKF_0	), // U+1D5CA; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL Q
/*M_SANS             */	DEADTRANS(	L'R'	,0x210b	,0xddb1	,DKF_0	), // U+1D5B1; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL R
/*M_SANS             */	DEADTRANS(	L'r'	,0x210b	,0xddcb	,DKF_0	), // U+1D5CB; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL R
/*M_SANS             */	DEADTRANS(	L'S'	,0x210b	,0xddb2	,DKF_0	), // U+1D5B2; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL S
/*M_SANS             */	DEADTRANS(	L's'	,0x210b	,0xddcc	,DKF_0	), // U+1D5CC; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL S
/*M_SANS             */	DEADTRANS(	L'T'	,0x210b	,0xddb3	,DKF_0	), // U+1D5B3; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL T
/*M_SANS             */	DEADTRANS(	L't'	,0x210b	,0xddcd	,DKF_0	), // U+1D5CD; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL T
/*M_SANS             */	DEADTRANS(	L'U'	,0x210b	,0xddb4	,DKF_0	), // U+1D5B4; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL U
/*M_SANS             */	DEADTRANS(	L'u'	,0x210b	,0xddce	,DKF_0	), // U+1D5CE; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL U
/*M_SANS             */	DEADTRANS(	L'V'	,0x210b	,0xddb5	,DKF_0	), // U+1D5B5; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL V
/*M_SANS             */	DEADTRANS(	L'v'	,0x210b	,0xddcf	,DKF_0	), // U+1D5CF; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL V
/*M_SANS             */	DEADTRANS(	L'W'	,0x210b	,0xddb6	,DKF_0	), // U+1D5B6; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL W
/*M_SANS             */	DEADTRANS(	L'w'	,0x210b	,0xddd0	,DKF_0	), // U+1D5D0; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL W
/*M_SANS             */	DEADTRANS(	L'X'	,0x210b	,0xddb7	,DKF_0	), // U+1D5B7; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL X
/*M_SANS             */	DEADTRANS(	L'x'	,0x210b	,0xddd1	,DKF_0	), // U+1D5D1; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL X
/*M_SANS             */	DEADTRANS(	L'Y'	,0x210b	,0xddb8	,DKF_0	), // U+1D5B8; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL Y
/*M_SANS             */	DEADTRANS(	L'y'	,0x210b	,0xddd2	,DKF_0	), // U+1D5D2; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL Y
/*M_SANS             */	DEADTRANS(	L'Z'	,0x210b	,0xddb9	,DKF_0	), // U+1D5B9; input D835 high surrogate first; MATHEMATICAL SANS-SERIF CAPITAL Z
/*M_SANS             */	DEADTRANS(	L'z'	,0x210b	,0xddd3	,DKF_0	), // U+1D5D3; input D835 high surrogate first; MATHEMATICAL SANS-SERIF SMALL Z
/*M_SANS             */	DEADTRANS(	0x002a	,0x210b	,0x211b	,CHAIN	), // SCRIPT CAPITAL R
/*M_SANS             */	DEADTRANS(	0x002f	,0x210b	,0x2112	,CHAIN	), // SCRIPT CAPITAL L
/*M_SANS_BOLD        */	DEADTRANS(	L'A'	,0x211b	,0xddd4	,DKF_0	), // U+1D5D4; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL A
/*M_SANS_BOLD        */	DEADTRANS(	L'a'	,0x211b	,0xddee	,DKF_0	), // U+1D5EE; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL A
/*M_SANS_BOLD        */	DEADTRANS(	L'B'	,0x211b	,0xddd5	,DKF_0	), // U+1D5D5; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL B
/*M_SANS_BOLD        */	DEADTRANS(	L'b'	,0x211b	,0xddef	,DKF_0	), // U+1D5EF; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL B
/*M_SANS_BOLD        */	DEADTRANS(	L'C'	,0x211b	,0xddd6	,DKF_0	), // U+1D5D6; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL C
/*M_SANS_BOLD        */	DEADTRANS(	L'c'	,0x211b	,0xddf0	,DKF_0	), // U+1D5F0; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL C
/*M_SANS_BOLD        */	DEADTRANS(	L'D'	,0x211b	,0xddd7	,DKF_0	), // U+1D5D7; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL D
/*M_SANS_BOLD        */	DEADTRANS(	L'd'	,0x211b	,0xddf1	,DKF_0	), // U+1D5F1; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL D
/*M_SANS_BOLD        */	DEADTRANS(	L'E'	,0x211b	,0xddd8	,DKF_0	), // U+1D5D8; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL E
/*M_SANS_BOLD        */	DEADTRANS(	L'e'	,0x211b	,0xddf2	,DKF_0	), // U+1D5F2; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL E
/*M_SANS_BOLD        */	DEADTRANS(	L'F'	,0x211b	,0xddd9	,DKF_0	), // U+1D5D9; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL F
/*M_SANS_BOLD        */	DEADTRANS(	L'f'	,0x211b	,0xddf3	,DKF_0	), // U+1D5F3; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL F
/*M_SANS_BOLD        */	DEADTRANS(	L'G'	,0x211b	,0xddda	,DKF_0	), // U+1D5DA; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL G
/*M_SANS_BOLD        */	DEADTRANS(	L'g'	,0x211b	,0xddf4	,DKF_0	), // U+1D5F4; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL G
/*M_SANS_BOLD        */	DEADTRANS(	L'H'	,0x211b	,0xdddb	,DKF_0	), // U+1D5DB; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL H
/*M_SANS_BOLD        */	DEADTRANS(	L'h'	,0x211b	,0xddf5	,DKF_0	), // U+1D5F5; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL H
/*M_SANS_BOLD        */	DEADTRANS(	L'I'	,0x211b	,0xdddc	,DKF_0	), // U+1D5DC; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL I
/*M_SANS_BOLD        */	DEADTRANS(	L'i'	,0x211b	,0xddf6	,DKF_0	), // U+1D5F6; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL I
/*M_SANS_BOLD        */	DEADTRANS(	L'J'	,0x211b	,0xdddd	,DKF_0	), // U+1D5DD; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL J
/*M_SANS_BOLD        */	DEADTRANS(	L'j'	,0x211b	,0xddf7	,DKF_0	), // U+1D5F7; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL J
/*M_SANS_BOLD        */	DEADTRANS(	L'K'	,0x211b	,0xddde	,DKF_0	), // U+1D5DE; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL K
/*M_SANS_BOLD        */	DEADTRANS(	L'k'	,0x211b	,0xddf8	,DKF_0	), // U+1D5F8; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL K
/*M_SANS_BOLD        */	DEADTRANS(	L'L'	,0x211b	,0xdddf	,DKF_0	), // U+1D5DF; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL L
/*M_SANS_BOLD        */	DEADTRANS(	L'l'	,0x211b	,0xddf9	,DKF_0	), // U+1D5F9; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL L
/*M_SANS_BOLD        */	DEADTRANS(	L'M'	,0x211b	,0xdde0	,DKF_0	), // U+1D5E0; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL M
/*M_SANS_BOLD        */	DEADTRANS(	L'm'	,0x211b	,0xddfa	,DKF_0	), // U+1D5FA; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL M
/*M_SANS_BOLD        */	DEADTRANS(	L'N'	,0x211b	,0xdde1	,DKF_0	), // U+1D5E1; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL N
/*M_SANS_BOLD        */	DEADTRANS(	L'n'	,0x211b	,0xddfb	,DKF_0	), // U+1D5FB; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL N
/*M_SANS_BOLD        */	DEADTRANS(	L'O'	,0x211b	,0xdde2	,DKF_0	), // U+1D5E2; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL O
/*M_SANS_BOLD        */	DEADTRANS(	L'o'	,0x211b	,0xddfc	,DKF_0	), // U+1D5FC; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL O
/*M_SANS_BOLD        */	DEADTRANS(	L'P'	,0x211b	,0xdde3	,DKF_0	), // U+1D5E3; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL P
/*M_SANS_BOLD        */	DEADTRANS(	L'p'	,0x211b	,0xddfd	,DKF_0	), // U+1D5FD; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL P
/*M_SANS_BOLD        */	DEADTRANS(	L'Q'	,0x211b	,0xdde4	,DKF_0	), // U+1D5E4; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL Q
/*M_SANS_BOLD        */	DEADTRANS(	L'q'	,0x211b	,0xddfe	,DKF_0	), // U+1D5FE; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL Q
/*M_SANS_BOLD        */	DEADTRANS(	L'R'	,0x211b	,0xdde5	,DKF_0	), // U+1D5E5; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL R
/*M_SANS_BOLD        */	DEADTRANS(	L'r'	,0x211b	,0xddff	,DKF_0	), // U+1D5FF; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL R
/*M_SANS_BOLD        */	DEADTRANS(	L'S'	,0x211b	,0xdde6	,DKF_0	), // U+1D5E6; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL S
/*M_SANS_BOLD        */	DEADTRANS(	L's'	,0x211b	,0xde00	,DKF_0	), // U+1D600; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL S
/*M_SANS_BOLD        */	DEADTRANS(	L'T'	,0x211b	,0xdde7	,DKF_0	), // U+1D5E7; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL T
/*M_SANS_BOLD        */	DEADTRANS(	L't'	,0x211b	,0xde01	,DKF_0	), // U+1D601; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL T
/*M_SANS_BOLD        */	DEADTRANS(	L'U'	,0x211b	,0xdde8	,DKF_0	), // U+1D5E8; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL U
/*M_SANS_BOLD        */	DEADTRANS(	L'u'	,0x211b	,0xde02	,DKF_0	), // U+1D602; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL U
/*M_SANS_BOLD        */	DEADTRANS(	L'V'	,0x211b	,0xdde9	,DKF_0	), // U+1D5E9; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL V
/*M_SANS_BOLD        */	DEADTRANS(	L'v'	,0x211b	,0xde03	,DKF_0	), // U+1D603; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL V
/*M_SANS_BOLD        */	DEADTRANS(	L'W'	,0x211b	,0xddea	,DKF_0	), // U+1D5EA; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL W
/*M_SANS_BOLD        */	DEADTRANS(	L'w'	,0x211b	,0xde04	,DKF_0	), // U+1D604; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL W
/*M_SANS_BOLD        */	DEADTRANS(	L'X'	,0x211b	,0xddeb	,DKF_0	), // U+1D5EB; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL X
/*M_SANS_BOLD        */	DEADTRANS(	L'x'	,0x211b	,0xde05	,DKF_0	), // U+1D605; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL X
/*M_SANS_BOLD        */	DEADTRANS(	L'Y'	,0x211b	,0xddec	,DKF_0	), // U+1D5EC; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL Y
/*M_SANS_BOLD        */	DEADTRANS(	L'y'	,0x211b	,0xde06	,DKF_0	), // U+1D606; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL Y
/*M_SANS_BOLD        */	DEADTRANS(	L'Z'	,0x211b	,0xdded	,DKF_0	), // U+1D5ED; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD CAPITAL Z
/*M_SANS_BOLD        */	DEADTRANS(	L'z'	,0x211b	,0xde07	,DKF_0	), // U+1D607; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD SMALL Z
/*M_SANS_BOLD        */	DEADTRANS(	0x002f	,0x211b	,0x2130	,CHAIN	), // SCRIPT CAPITAL E
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'A'	,0x2130	,0xde3c	,DKF_0	), // U+1D63C; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL A
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'B'	,0x2130	,0xde3d	,DKF_0	), // U+1D63D; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL B
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'C'	,0x2130	,0xde3e	,DKF_0	), // U+1D63E; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL C
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'D'	,0x2130	,0xde3f	,DKF_0	), // U+1D63F; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL D
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'E'	,0x2130	,0xde40	,DKF_0	), // U+1D640; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL E
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'F'	,0x2130	,0xde41	,DKF_0	), // U+1D641; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL F
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'G'	,0x2130	,0xde42	,DKF_0	), // U+1D642; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL G
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'H'	,0x2130	,0xde43	,DKF_0	), // U+1D643; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL H
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'I'	,0x2130	,0xde44	,DKF_0	), // U+1D644; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL I
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'J'	,0x2130	,0xde45	,DKF_0	), // U+1D645; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL J
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'K'	,0x2130	,0xde46	,DKF_0	), // U+1D646; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL K
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'L'	,0x2130	,0xde47	,DKF_0	), // U+1D647; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL L
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'M'	,0x2130	,0xde48	,DKF_0	), // U+1D648; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL M
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'N'	,0x2130	,0xde49	,DKF_0	), // U+1D649; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL N
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'O'	,0x2130	,0xde4a	,DKF_0	), // U+1D64A; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL O
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'P'	,0x2130	,0xde4b	,DKF_0	), // U+1D64B; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL P
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'Q'	,0x2130	,0xde4c	,DKF_0	), // U+1D64C; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL Q
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'R'	,0x2130	,0xde4d	,DKF_0	), // U+1D64D; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL R
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'S'	,0x2130	,0xde4e	,DKF_0	), // U+1D64E; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL S
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'T'	,0x2130	,0xde4f	,DKF_0	), // U+1D64F; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL T
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'U'	,0x2130	,0xde50	,DKF_0	), // U+1D650; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL U
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'V'	,0x2130	,0xde51	,DKF_0	), // U+1D651; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL V
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'W'	,0x2130	,0xde52	,DKF_0	), // U+1D652; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL W
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'X'	,0x2130	,0xde53	,DKF_0	), // U+1D653; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL X
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'Y'	,0x2130	,0xde54	,DKF_0	), // U+1D654; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL Y
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'Z'	,0x2130	,0xde55	,DKF_0	), // U+1D655; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL Z
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'a'	,0x2130	,0xde56	,DKF_0	), // U+1D656; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL A
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'b'	,0x2130	,0xde57	,DKF_0	), // U+1D657; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL B
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'c'	,0x2130	,0xde58	,DKF_0	), // U+1D658; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL C
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'd'	,0x2130	,0xde59	,DKF_0	), // U+1D659; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL D
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'e'	,0x2130	,0xde5a	,DKF_0	), // U+1D65A; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL E
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'f'	,0x2130	,0xde5b	,DKF_0	), // U+1D65B; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL F
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'g'	,0x2130	,0xde5c	,DKF_0	), // U+1D65C; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL G
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'h'	,0x2130	,0xde5d	,DKF_0	), // U+1D65D; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL H
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'i'	,0x2130	,0xde5e	,DKF_0	), // U+1D65E; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL I
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'j'	,0x2130	,0xde5f	,DKF_0	), // U+1D65F; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL J
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'k'	,0x2130	,0xde60	,DKF_0	), // U+1D660; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL K
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'l'	,0x2130	,0xde61	,DKF_0	), // U+1D661; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL L
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'm'	,0x2130	,0xde62	,DKF_0	), // U+1D662; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL M
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'n'	,0x2130	,0xde63	,DKF_0	), // U+1D663; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL N
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'o'	,0x2130	,0xde64	,DKF_0	), // U+1D664; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL O
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'p'	,0x2130	,0xde65	,DKF_0	), // U+1D665; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL P
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'q'	,0x2130	,0xde66	,DKF_0	), // U+1D666; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL Q
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'r'	,0x2130	,0xde67	,DKF_0	), // U+1D667; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL R
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L's'	,0x2130	,0xde68	,DKF_0	), // U+1D668; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL S
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L't'	,0x2130	,0xde69	,DKF_0	), // U+1D669; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL T
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'u'	,0x2130	,0xde6a	,DKF_0	), // U+1D66A; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL U
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'v'	,0x2130	,0xde6b	,DKF_0	), // U+1D66B; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL V
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'w'	,0x2130	,0xde6c	,DKF_0	), // U+1D66C; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL W
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'x'	,0x2130	,0xde6d	,DKF_0	), // U+1D66D; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL X
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'y'	,0x2130	,0xde6e	,DKF_0	), // U+1D66E; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL Y
/*M_SANS_BOLD_ITALIC */	DEADTRANS(	L'z'	,0x2130	,0xde6f	,DKF_0	), // U+1D66F; input D835 high surrogate first; MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL Z
/*M_SANS_ITALIC      */	DEADTRANS(	L'A'	,0x2112	,0xde08	,DKF_0	), // U+1D608; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL A
/*M_SANS_ITALIC      */	DEADTRANS(	L'a'	,0x2112	,0xde22	,DKF_0	), // U+1D622; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL A
/*M_SANS_ITALIC      */	DEADTRANS(	L'B'	,0x2112	,0xde09	,DKF_0	), // U+1D609; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL B
/*M_SANS_ITALIC      */	DEADTRANS(	L'b'	,0x2112	,0xde23	,DKF_0	), // U+1D623; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL B
/*M_SANS_ITALIC      */	DEADTRANS(	L'C'	,0x2112	,0xde0a	,DKF_0	), // U+1D60A; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL C
/*M_SANS_ITALIC      */	DEADTRANS(	L'c'	,0x2112	,0xde24	,DKF_0	), // U+1D624; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL C
/*M_SANS_ITALIC      */	DEADTRANS(	L'D'	,0x2112	,0xde0b	,DKF_0	), // U+1D60B; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL D
/*M_SANS_ITALIC      */	DEADTRANS(	L'd'	,0x2112	,0xde25	,DKF_0	), // U+1D625; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL D
/*M_SANS_ITALIC      */	DEADTRANS(	L'E'	,0x2112	,0xde0c	,DKF_0	), // U+1D60C; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL E
/*M_SANS_ITALIC      */	DEADTRANS(	L'e'	,0x2112	,0xde26	,DKF_0	), // U+1D626; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL E
/*M_SANS_ITALIC      */	DEADTRANS(	L'F'	,0x2112	,0xde0d	,DKF_0	), // U+1D60D; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL F
/*M_SANS_ITALIC      */	DEADTRANS(	L'f'	,0x2112	,0xde27	,DKF_0	), // U+1D627; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL F
/*M_SANS_ITALIC      */	DEADTRANS(	L'G'	,0x2112	,0xde0e	,DKF_0	), // U+1D60E; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL G
/*M_SANS_ITALIC      */	DEADTRANS(	L'g'	,0x2112	,0xde28	,DKF_0	), // U+1D628; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL G
/*M_SANS_ITALIC      */	DEADTRANS(	L'H'	,0x2112	,0xde0f	,DKF_0	), // U+1D60F; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL H
/*M_SANS_ITALIC      */	DEADTRANS(	L'h'	,0x2112	,0xde29	,DKF_0	), // U+1D629; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL H
/*M_SANS_ITALIC      */	DEADTRANS(	L'I'	,0x2112	,0xde10	,DKF_0	), // U+1D610; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL I
/*M_SANS_ITALIC      */	DEADTRANS(	L'i'	,0x2112	,0xde2a	,DKF_0	), // U+1D62A; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL I
/*M_SANS_ITALIC      */	DEADTRANS(	L'J'	,0x2112	,0xde11	,DKF_0	), // U+1D611; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL J
/*M_SANS_ITALIC      */	DEADTRANS(	L'j'	,0x2112	,0xde2b	,DKF_0	), // U+1D62B; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL J
/*M_SANS_ITALIC      */	DEADTRANS(	L'K'	,0x2112	,0xde12	,DKF_0	), // U+1D612; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL K
/*M_SANS_ITALIC      */	DEADTRANS(	L'k'	,0x2112	,0xde2c	,DKF_0	), // U+1D62C; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL K
/*M_SANS_ITALIC      */	DEADTRANS(	L'L'	,0x2112	,0xde13	,DKF_0	), // U+1D613; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL L
/*M_SANS_ITALIC      */	DEADTRANS(	L'l'	,0x2112	,0xde2d	,DKF_0	), // U+1D62D; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL L
/*M_SANS_ITALIC      */	DEADTRANS(	L'M'	,0x2112	,0xde14	,DKF_0	), // U+1D614; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL M
/*M_SANS_ITALIC      */	DEADTRANS(	L'm'	,0x2112	,0xde2e	,DKF_0	), // U+1D62E; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL M
/*M_SANS_ITALIC      */	DEADTRANS(	L'N'	,0x2112	,0xde15	,DKF_0	), // U+1D615; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL N
/*M_SANS_ITALIC      */	DEADTRANS(	L'n'	,0x2112	,0xde2f	,DKF_0	), // U+1D62F; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL N
/*M_SANS_ITALIC      */	DEADTRANS(	L'O'	,0x2112	,0xde16	,DKF_0	), // U+1D616; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL O
/*M_SANS_ITALIC      */	DEADTRANS(	L'o'	,0x2112	,0xde30	,DKF_0	), // U+1D630; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL O
/*M_SANS_ITALIC      */	DEADTRANS(	L'P'	,0x2112	,0xde17	,DKF_0	), // U+1D617; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL P
/*M_SANS_ITALIC      */	DEADTRANS(	L'p'	,0x2112	,0xde31	,DKF_0	), // U+1D631; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL P
/*M_SANS_ITALIC      */	DEADTRANS(	L'Q'	,0x2112	,0xde18	,DKF_0	), // U+1D618; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL Q
/*M_SANS_ITALIC      */	DEADTRANS(	L'q'	,0x2112	,0xde32	,DKF_0	), // U+1D632; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL Q
/*M_SANS_ITALIC      */	DEADTRANS(	L'R'	,0x2112	,0xde19	,DKF_0	), // U+1D619; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL R
/*M_SANS_ITALIC      */	DEADTRANS(	L'r'	,0x2112	,0xde33	,DKF_0	), // U+1D633; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL R
/*M_SANS_ITALIC      */	DEADTRANS(	L'S'	,0x2112	,0xde1a	,DKF_0	), // U+1D61A; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL S
/*M_SANS_ITALIC      */	DEADTRANS(	L's'	,0x2112	,0xde34	,DKF_0	), // U+1D634; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL S
/*M_SANS_ITALIC      */	DEADTRANS(	L'T'	,0x2112	,0xde1b	,DKF_0	), // U+1D61B; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL T
/*M_SANS_ITALIC      */	DEADTRANS(	L't'	,0x2112	,0xde35	,DKF_0	), // U+1D635; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL T
/*M_SANS_ITALIC      */	DEADTRANS(	L'U'	,0x2112	,0xde1c	,DKF_0	), // U+1D61C; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL U
/*M_SANS_ITALIC      */	DEADTRANS(	L'u'	,0x2112	,0xde36	,DKF_0	), // U+1D636; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL U
/*M_SANS_ITALIC      */	DEADTRANS(	L'V'	,0x2112	,0xde1d	,DKF_0	), // U+1D61D; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL V
/*M_SANS_ITALIC      */	DEADTRANS(	L'v'	,0x2112	,0xde37	,DKF_0	), // U+1D637; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL V
/*M_SANS_ITALIC      */	DEADTRANS(	L'W'	,0x2112	,0xde1e	,DKF_0	), // U+1D61E; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL W
/*M_SANS_ITALIC      */	DEADTRANS(	L'w'	,0x2112	,0xde38	,DKF_0	), // U+1D638; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL W
/*M_SANS_ITALIC      */	DEADTRANS(	L'X'	,0x2112	,0xde1f	,DKF_0	), // U+1D61F; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL X
/*M_SANS_ITALIC      */	DEADTRANS(	L'x'	,0x2112	,0xde39	,DKF_0	), // U+1D639; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL X
/*M_SANS_ITALIC      */	DEADTRANS(	L'Y'	,0x2112	,0xde20	,DKF_0	), // U+1D620; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL Y
/*M_SANS_ITALIC      */	DEADTRANS(	L'y'	,0x2112	,0xde3a	,DKF_0	), // U+1D63A; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL Y
/*M_SANS_ITALIC      */	DEADTRANS(	L'Z'	,0x2112	,0xde21	,DKF_0	), // U+1D621; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC CAPITAL Z
/*M_SANS_ITALIC      */	DEADTRANS(	L'z'	,0x2112	,0xde3b	,DKF_0	), // U+1D63B; input D835 high surrogate first; MATHEMATICAL SANS-SERIF ITALIC SMALL Z
/*M_SANS_ITALIC      */	DEADTRANS(	0x002a	,0x2112	,0x2130	,CHAIN	), // SCRIPT CAPITAL E
/*M_SCRIPT           */	DEADTRANS(	L'A'	,0x212f	,0xdc9c	,DKF_0	), // U+1D49C; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL A
/*M_SCRIPT           */	DEADTRANS(	L'a'	,0x212f	,0xdcb6	,DKF_0	), // U+1D4B6; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL A
/*M_SCRIPT           */	DEADTRANS(	L'B'	,0x212f	,0x212c	,DKF_0	), // SCRIPT CAPITAL B
/*M_SCRIPT           */	DEADTRANS(	L'b'	,0x212f	,0xdcb7	,DKF_0	), // U+1D4B7; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL B
/*M_SCRIPT           */	DEADTRANS(	L'C'	,0x212f	,0xdc9e	,DKF_0	), // U+1D49E; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL C
/*M_SCRIPT           */	DEADTRANS(	L'c'	,0x212f	,0xdcb8	,DKF_0	), // U+1D4B8; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL C
/*M_SCRIPT           */	DEADTRANS(	L'D'	,0x212f	,0xdc9f	,DKF_0	), // U+1D49F; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL D
/*M_SCRIPT           */	DEADTRANS(	L'd'	,0x212f	,0xdcb9	,DKF_0	), // U+1D4B9; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL D
/*M_SCRIPT           */	DEADTRANS(	L'E'	,0x212f	,0x2130	,DKF_0	), // SCRIPT CAPITAL E
/*M_SCRIPT           */	DEADTRANS(	L'e'	,0x212f	,0x212f	,DKF_0	), // SCRIPT SMALL E
/*M_SCRIPT           */	DEADTRANS(	L'F'	,0x212f	,0x2131	,DKF_0	), // SCRIPT CAPITAL F
/*M_SCRIPT           */	DEADTRANS(	L'f'	,0x212f	,0xdcbb	,DKF_0	), // U+1D4BB; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL F
/*M_SCRIPT           */	DEADTRANS(	L'G'	,0x212f	,0xdca2	,DKF_0	), // U+1D4A2; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL G
/*M_SCRIPT           */	DEADTRANS(	L'g'	,0x212f	,0x210a	,DKF_0	), // SCRIPT SMALL G
/*M_SCRIPT           */	DEADTRANS(	L'H'	,0x212f	,0x210b	,DKF_0	), // SCRIPT CAPITAL H
/*M_SCRIPT           */	DEADTRANS(	L'h'	,0x212f	,0xdcbd	,DKF_0	), // U+1D4BD; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL H
/*M_SCRIPT           */	DEADTRANS(	L'I'	,0x212f	,0x2110	,DKF_0	), // SCRIPT CAPITAL I
/*M_SCRIPT           */	DEADTRANS(	L'i'	,0x212f	,0xdcbe	,DKF_0	), // U+1D4BE; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL I
/*M_SCRIPT           */	DEADTRANS(	L'J'	,0x212f	,0xdca5	,DKF_0	), // U+1D4A5; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL J
/*M_SCRIPT           */	DEADTRANS(	L'j'	,0x212f	,0xdcbf	,DKF_0	), // U+1D4BF; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL J
/*M_SCRIPT           */	DEADTRANS(	L'K'	,0x212f	,0xdca6	,DKF_0	), // U+1D4A6; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL K
/*M_SCRIPT           */	DEADTRANS(	L'k'	,0x212f	,0xdcc0	,DKF_0	), // U+1D4C0; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL K
/*M_SCRIPT           */	DEADTRANS(	L'L'	,0x212f	,0x2112	,DKF_0	), // SCRIPT CAPITAL L
/*M_SCRIPT           */	DEADTRANS(	L'l'	,0x212f	,0xdcc1	,DKF_0	), // U+1D4C1; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL L
/*M_SCRIPT           */	DEADTRANS(	L'M'	,0x212f	,0x2133	,DKF_0	), // SCRIPT CAPITAL M
/*M_SCRIPT           */	DEADTRANS(	L'm'	,0x212f	,0xdcc2	,DKF_0	), // U+1D4C2; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL M
/*M_SCRIPT           */	DEADTRANS(	L'N'	,0x212f	,0xdca9	,DKF_0	), // U+1D4A9; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL N
/*M_SCRIPT           */	DEADTRANS(	L'n'	,0x212f	,0xdcc3	,DKF_0	), // U+1D4C3; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL N
/*M_SCRIPT           */	DEADTRANS(	L'O'	,0x212f	,0xdcaa	,DKF_0	), // U+1D4AA; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL O
/*M_SCRIPT           */	DEADTRANS(	L'o'	,0x212f	,0x2134	,DKF_0	), // SCRIPT SMALL O
/*M_SCRIPT           */	DEADTRANS(	L'P'	,0x212f	,0xdcab	,DKF_0	), // U+1D4AB; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL P
/*M_SCRIPT           */	DEADTRANS(	L'p'	,0x212f	,0xdcc5	,DKF_0	), // U+1D4C5; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL P
/*M_SCRIPT           */	DEADTRANS(	L'Q'	,0x212f	,0xdcac	,DKF_0	), // U+1D4AC; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL Q
/*M_SCRIPT           */	DEADTRANS(	L'q'	,0x212f	,0xdcc6	,DKF_0	), // U+1D4C6; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL Q
/*M_SCRIPT           */	DEADTRANS(	L'R'	,0x212f	,0x211b	,DKF_0	), // SCRIPT CAPITAL R
/*M_SCRIPT           */	DEADTRANS(	L'r'	,0x212f	,0xdcc7	,DKF_0	), // U+1D4C7; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL R
/*M_SCRIPT           */	DEADTRANS(	L'S'	,0x212f	,0xdcae	,DKF_0	), // U+1D4AE; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL S
/*M_SCRIPT           */	DEADTRANS(	L's'	,0x212f	,0xdcc8	,DKF_0	), // U+1D4C8; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL S
/*M_SCRIPT           */	DEADTRANS(	L'T'	,0x212f	,0xdcaf	,DKF_0	), // U+1D4AF; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL T
/*M_SCRIPT           */	DEADTRANS(	L't'	,0x212f	,0xdcc9	,DKF_0	), // U+1D4C9; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL T
/*M_SCRIPT           */	DEADTRANS(	L'U'	,0x212f	,0xdcb0	,DKF_0	), // U+1D4B0; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL U
/*M_SCRIPT           */	DEADTRANS(	L'u'	,0x212f	,0xdcca	,DKF_0	), // U+1D4CA; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL U
/*M_SCRIPT           */	DEADTRANS(	L'V'	,0x212f	,0xdcb1	,DKF_0	), // U+1D4B1; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL V
/*M_SCRIPT           */	DEADTRANS(	L'v'	,0x212f	,0xdccb	,DKF_0	), // U+1D4CB; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL V
/*M_SCRIPT           */	DEADTRANS(	L'W'	,0x212f	,0xdcb2	,DKF_0	), // U+1D4B2; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL W
/*M_SCRIPT           */	DEADTRANS(	L'w'	,0x212f	,0xdccc	,DKF_0	), // U+1D4CC; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL W
/*M_SCRIPT           */	DEADTRANS(	L'X'	,0x212f	,0xdcb3	,DKF_0	), // U+1D4B3; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL X
/*M_SCRIPT           */	DEADTRANS(	L'x'	,0x212f	,0xdccd	,DKF_0	), // U+1D4CD; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL X
/*M_SCRIPT           */	DEADTRANS(	L'Y'	,0x212f	,0xdcb4	,DKF_0	), // U+1D4B4; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL Y
/*M_SCRIPT           */	DEADTRANS(	L'y'	,0x212f	,0xdcce	,DKF_0	), // U+1D4CE; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL Y
/*M_SCRIPT           */	DEADTRANS(	L'Z'	,0x212f	,0xdcb5	,DKF_0	), // U+1D4B5; input D835 high surrogate first; MATHEMATICAL SCRIPT CAPITAL Z
/*M_SCRIPT           */	DEADTRANS(	L'z'	,0x212f	,0xdccf	,DKF_0	), // U+1D4CF; input D835 high surrogate first; MATHEMATICAL SCRIPT SMALL Z
/*M_SCRIPT           */	DEADTRANS(	0x002a	,0x212f	,0x2131	,CHAIN	), // SCRIPT CAPITAL F
/*MACRON             */	DEADTRANS(	0x0020	,0x0101	,0x0304	,DKF_0	), // COMBINING MACRON
/*MACRON             */	DEADTRANS(	0x0028	,0x0101	,0x1dcc	,DKF_0	), // COMBINING MACRON-BREVE
/*MACRON             */	DEADTRANS(	0x005f	,0x0101	,0x0332	,DKF_0	), // COMBINING LOW LINE
/*MACRON             */	DEADTRANS(	0x0020	,0x1e53	,0x1dc4	,DKF_0	), // COMBINING MACRON-ACUTE
/*MACRON             */	DEADTRANS(	0x0020	,0x02cd	,0x0331	,DKF_0	), // COMBINING MACRON BELOW
/*MACRON             */	DEADTRANS(	0x0020	,0x1e51	,0x1dc6	,DKF_0	), // COMBINING MACRON-GRAVE
/*MACRON             */	DEADTRANS(	0x002a	,0x0101	,0x02c9	,DKF_0	), // MODIFIER LETTER MACRON
/*MACRON             */	DEADTRANS(	0x202f	,0x02cd	,0x02cd	,DKF_0	), // MODIFIER LETTER LOW MACRON
/*MACRON             */	DEADTRANS(	0x00a0	,0x0101	,0x00af	,DKF_0	), // MACRON
/*MACRON             */	DEADTRANS(	L'A'	,0x0101	,0x0100	,DKF_0	), // LATIN CAPITAL LETTER A WITH MACRON
/*MACRON             */	DEADTRANS(	L'a'	,0x0101	,0x0101	,DKF_0	), // LATIN SMALL LETTER A WITH MACRON
/*MACRON             */	DEADTRANS(	L'B'	,0x0101	,0x1e06	,DKF_0	), // LATIN CAPITAL LETTER B WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'b'	,0x0101	,0x1e07	,DKF_0	), // LATIN SMALL LETTER B WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'D'	,0x0101	,0x1e0e	,DKF_0	), // LATIN CAPITAL LETTER D WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'd'	,0x0101	,0x1e0f	,DKF_0	), // LATIN SMALL LETTER D WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'E'	,0x0101	,0x0112	,DKF_0	), // LATIN CAPITAL LETTER E WITH MACRON
/*MACRON             */	DEADTRANS(	L'e'	,0x0101	,0x0113	,DKF_0	), // LATIN SMALL LETTER E WITH MACRON
/*MACRON             */	DEADTRANS(	L'G'	,0x0101	,0x1e20	,DKF_0	), // LATIN CAPITAL LETTER G WITH MACRON
/*MACRON             */	DEADTRANS(	L'g'	,0x0101	,0x1e21	,DKF_0	), // LATIN SMALL LETTER G WITH MACRON
/*MACRON             */	DEADTRANS(	L'h'	,0x0101	,0x1e96	,DKF_0	), // LATIN SMALL LETTER H WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'I'	,0x0101	,0x012a	,DKF_0	), // LATIN CAPITAL LETTER I WITH MACRON
/*MACRON             */	DEADTRANS(	L'i'	,0x0101	,0x012b	,DKF_0	), // LATIN SMALL LETTER I WITH MACRON
/*MACRON             */	DEADTRANS(	L'K'	,0x0101	,0x1e34	,DKF_0	), // LATIN CAPITAL LETTER K WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'k'	,0x0101	,0x1e35	,DKF_0	), // LATIN SMALL LETTER K WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'L'	,0x0101	,0x1e3a	,DKF_0	), // LATIN CAPITAL LETTER L WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'l'	,0x0101	,0x1e3b	,DKF_0	), // LATIN SMALL LETTER L WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'N'	,0x0101	,0x1e48	,DKF_0	), // LATIN CAPITAL LETTER N WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'n'	,0x0101	,0x1e49	,DKF_0	), // LATIN SMALL LETTER N WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'O'	,0x0101	,0x014c	,DKF_0	), // LATIN CAPITAL LETTER O WITH MACRON
/*MACRON             */	DEADTRANS(	L'o'	,0x0101	,0x014d	,DKF_0	), // LATIN SMALL LETTER O WITH MACRON
/*MACRON             */	DEADTRANS(	L'R'	,0x0101	,0x1e5e	,DKF_0	), // LATIN CAPITAL LETTER R WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'r'	,0x0101	,0x1e5f	,DKF_0	), // LATIN SMALL LETTER R WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L's'	,0x0101	,0x017f	,DKF_0	), // LATIN SMALL LETTER LONG S
/*MACRON             */	DEADTRANS(	L'T'	,0x0101	,0x1e6e	,DKF_0	), // LATIN CAPITAL LETTER T WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L't'	,0x0101	,0x1e6f	,DKF_0	), // LATIN SMALL LETTER T WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'U'	,0x0101	,0x016a	,DKF_0	), // LATIN CAPITAL LETTER U WITH MACRON
/*MACRON             */	DEADTRANS(	L'u'	,0x0101	,0x016b	,DKF_0	), // LATIN SMALL LETTER U WITH MACRON
/*MACRON             */	DEADTRANS(	L'V'	,0x0101	,0x0332	,DKF_0	), // COMBINING LOW LINE
/*MACRON             */	DEADTRANS(	L'v'	,0x0101	,0x0332	,DKF_0	), // COMBINING LOW LINE
/*MACRON             */	DEADTRANS(	L'W'	,0x0101	,0x0333	,DKF_0	), // COMBINING DOUBLE LOW LINE
/*MACRON             */	DEADTRANS(	L'w'	,0x0101	,0x0333	,DKF_0	), // COMBINING DOUBLE LOW LINE
/*MACRON             */	DEADTRANS(	L'Y'	,0x0101	,0x0232	,DKF_0	), // LATIN CAPITAL LETTER Y WITH MACRON
/*MACRON             */	DEADTRANS(	L'y'	,0x0101	,0x0233	,DKF_0	), // LATIN SMALL LETTER Y WITH MACRON
/*MACRON             */	DEADTRANS(	L'Z'	,0x0101	,0x1e94	,DKF_0	), // LATIN CAPITAL LETTER Z WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'z'	,0x0101	,0x1e95	,DKF_0	), // LATIN SMALL LETTER Z WITH LINE BELOW
/*MACRON             */	DEADTRANS(	L'0'	,0x0101	,0x2469	,DKF_0	), // CIRCLED NUMBER TEN
/*MACRON             */	DEADTRANS(	L'1'	,0x0101	,0x2460	,DKF_0	), // CIRCLED DIGIT ONE
/*MACRON             */	DEADTRANS(	L'2'	,0x0101	,0x2461	,DKF_0	), // CIRCLED DIGIT TWO
/*MACRON             */	DEADTRANS(	L'3'	,0x0101	,0x2462	,DKF_0	), // CIRCLED DIGIT THREE
/*MACRON             */	DEADTRANS(	L'4'	,0x0101	,0x2463	,DKF_0	), // CIRCLED DIGIT FOUR
/*MACRON             */	DEADTRANS(	L'5'	,0x0101	,0x2464	,DKF_0	), // CIRCLED DIGIT FIVE
/*MACRON             */	DEADTRANS(	L'6'	,0x0101	,0x2465	,DKF_0	), // CIRCLED DIGIT SIX
/*MACRON             */	DEADTRANS(	L'7'	,0x0101	,0x2466	,DKF_0	), // CIRCLED DIGIT SEVEN
/*MACRON             */	DEADTRANS(	L'8'	,0x0101	,0x2467	,DKF_0	), // CIRCLED DIGIT EIGHT
/*MACRON             */	DEADTRANS(	L'9'	,0x0101	,0x2468	,DKF_0	), // CIRCLED DIGIT NINE
/*MACRON             */	DEADTRANS(	0x0021	,0x0101	,0x1e5d	,CHAIN	), // LATIN SMALL LETTER R WITH DOT BELOW AND MACRON
/*MACRON             */	DEADTRANS(	0x0025	,0x0101	,0x246b	,DKF_0	), // CIRCLED NUMBER TWELVE
/*MACRON             */	DEADTRANS(	0x0027	,0x0101	,0x1e53	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND ACUTE
/*MACRON             */	DEADTRANS(	0x002e	,0x0101	,0x0231	,CHAIN	), // LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
/*MACRON             */	DEADTRANS(	0x003a	,0x0101	,0x1e7b	,CHAIN	), // LATIN SMALL LETTER U WITH MACRON AND DIAERESIS
/*MACRON             */	DEADTRANS(	0x003d	,0x0101	,0x2261	,DKF_0	), // IDENTICAL TO
/*MACRON             */	DEADTRANS(	0x005b	,0x0101	,0x01ed	,CHAIN	), // LATIN SMALL LETTER O WITH OGONEK AND MACRON
/*MACRON             */	DEADTRANS(	0x0060	,0x0101	,0x1e51	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND GRAVE
/*MACRON             */	DEADTRANS(	0x007e	,0x0101	,0x022d	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND MACRON
/*MACRON             */	DEADTRANS(	0x0152	,0x0101	,0x01e2	,DKF_0	), // LATIN CAPITAL LETTER AE WITH MACRON
/*MACRON             */	DEADTRANS(	0x0153	,0x0101	,0x01e3	,DKF_0	), // LATIN SMALL LETTER AE WITH MACRON
/*MACRON             */	DEADTRANS(	0x00a9	,0x0101	,0x01e3	,CHAIN	), // LATIN SMALL LETTER AE WITH MACRON
/*MACRON             */	DEADTRANS(	L'A'	,0x01e3	,0x01e2	,DKF_0	), // LATIN CAPITAL LETTER AE WITH MACRON
/*MACRON             */	DEADTRANS(	L'a'	,0x01e3	,0x01e3	,DKF_0	), // LATIN SMALL LETTER AE WITH MACRON
/*MACRON             */	DEADTRANS(	0x00b0	,0x0101	,0x246a	,DKF_0	), // CIRCLED NUMBER ELEVEN
/*MACRON             */	DEADTRANS(	0x00c6	,0x0101	,0x01e2	,DKF_0	), // LATIN CAPITAL LETTER AE WITH MACRON
/*MACRON             */	DEADTRANS(	0x00e1	,0x0101	,0x1e53	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND ACUTE
/*MACRON             */	DEADTRANS(	0x00e6	,0x0101	,0x01e3	,DKF_0	), // LATIN SMALL LETTER AE WITH MACRON
/*MACRON             */	DEADTRANS(	0x00a3	,0x0101	,0x02cd	,CHAIN	), // MODIFIER LETTER LOW MACRON
/*MACRON             */	DEADTRANS(	0x00eb	,0x0101	,0x1e7b	,CHAIN	), // LATIN SMALL LETTER U WITH MACRON AND DIAERESIS
/*MACRON             */	DEADTRANS(	0x00f2	,0x0101	,0x1e51	,CHAIN	), // LATIN SMALL LETTER O WITH MACRON AND GRAVE
/*MACRON             */	DEADTRANS(	0x00f5	,0x0101	,0x022d	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND MACRON
/*MACRON             */	DEADTRANS(	0x022f	,0x0101	,0x0231	,CHAIN	), // LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
/*MACRON             */	DEADTRANS(	0x0101	,0x0101	,0x1e07	,CHAIN	), // LATIN SMALL LETTER B WITH LINE BELOW
/*MACRON             */	DEADTRANS(	0x01eb	,0x0101	,0x01ed	,CHAIN	), // LATIN SMALL LETTER O WITH OGONEK AND MACRON
/*MACRON             */	DEADTRANS(	0x1ee5	,0x0101	,0x1e5d	,CHAIN	), // LATIN SMALL LETTER R WITH DOT BELOW AND MACRON
/*MACRON&ACUTE_ACCENT*/	DEADTRANS(	L'E'	,0x1e53	,0x1e16	,DKF_0	), // LATIN CAPITAL LETTER E WITH MACRON AND ACUTE
/*MACRON&ACUTE_ACCENT*/	DEADTRANS(	L'e'	,0x1e53	,0x1e17	,DKF_0	), // LATIN SMALL LETTER E WITH MACRON AND ACUTE
/*MACRON&ACUTE_ACCENT*/	DEADTRANS(	L'O'	,0x1e53	,0x1e52	,DKF_0	), // LATIN CAPITAL LETTER O WITH MACRON AND ACUTE
/*MACRON&ACUTE_ACCENT*/	DEADTRANS(	L'o'	,0x1e53	,0x1e53	,DKF_0	), // LATIN SMALL LETTER O WITH MACRON AND ACUTE
/*MACRON&DIAERESIS   */	DEADTRANS(	L'U'	,0x1e7b	,0x1e7a	,DKF_0	), // LATIN CAPITAL LETTER U WITH MACRON AND DIAERESIS
/*MACRON&DIAERESIS   */	DEADTRANS(	L'u'	,0x1e7b	,0x1e7b	,DKF_0	), // LATIN SMALL LETTER U WITH MACRON AND DIAERESIS
/*MACRON&GRAVE_ACCENT*/	DEADTRANS(	L'E'	,0x1e51	,0x1e14	,DKF_0	), // LATIN CAPITAL LETTER E WITH MACRON AND GRAVE
/*MACRON&GRAVE_ACCENT*/	DEADTRANS(	L'e'	,0x1e51	,0x1e15	,DKF_0	), // LATIN SMALL LETTER E WITH MACRON AND GRAVE
/*MACRON&GRAVE_ACCENT*/	DEADTRANS(	L'O'	,0x1e51	,0x1e50	,DKF_0	), // LATIN CAPITAL LETTER O WITH MACRON AND GRAVE
/*MACRON&GRAVE_ACCENT*/	DEADTRANS(	L'o'	,0x1e51	,0x1e51	,DKF_0	), // LATIN SMALL LETTER O WITH MACRON AND GRAVE
/*MACRON_BELOW       */	DEADTRANS(	0x0020	,0x1e07	,0x0331	,DKF_0	), // COMBINING MACRON BELOW
/*MACRON_BELOW       */	DEADTRANS(	0x00a0	,0x1e07	,0x005f	,DKF_0	), // LOW LINE
/*MACRON_BELOW       */	DEADTRANS(	0x202f	,0x1e07	,0x02cd	,DKF_0	), // MODIFIER LETTER LOW MACRON
/*MACRON_BELOW       */	DEADTRANS(	L'B'	,0x1e07	,0x1e06	,DKF_0	), // LATIN CAPITAL LETTER B WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'b'	,0x1e07	,0x1e07	,DKF_0	), // LATIN SMALL LETTER B WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'D'	,0x1e07	,0x1e0e	,DKF_0	), // LATIN CAPITAL LETTER D WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'd'	,0x1e07	,0x1e0f	,DKF_0	), // LATIN SMALL LETTER D WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'h'	,0x1e07	,0x1e96	,DKF_0	), // LATIN SMALL LETTER H WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'K'	,0x1e07	,0x1e34	,DKF_0	), // LATIN CAPITAL LETTER K WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'k'	,0x1e07	,0x1e35	,DKF_0	), // LATIN SMALL LETTER K WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'L'	,0x1e07	,0x1e3a	,DKF_0	), // LATIN CAPITAL LETTER L WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'l'	,0x1e07	,0x1e3b	,DKF_0	), // LATIN SMALL LETTER L WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'N'	,0x1e07	,0x1e48	,DKF_0	), // LATIN CAPITAL LETTER N WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'n'	,0x1e07	,0x1e49	,DKF_0	), // LATIN SMALL LETTER N WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'R'	,0x1e07	,0x1e5e	,DKF_0	), // LATIN CAPITAL LETTER R WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'r'	,0x1e07	,0x1e5f	,DKF_0	), // LATIN SMALL LETTER R WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'T'	,0x1e07	,0x1e6e	,DKF_0	), // LATIN CAPITAL LETTER T WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L't'	,0x1e07	,0x1e6f	,DKF_0	), // LATIN SMALL LETTER T WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'Z'	,0x1e07	,0x1e94	,DKF_0	), // LATIN CAPITAL LETTER Z WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	L'z'	,0x1e07	,0x1e95	,DKF_0	), // LATIN SMALL LETTER Z WITH LINE BELOW
/*MACRON_BELOW       */	DEADTRANS(	0x007c	,0x1e07	,0x007c	,CHAIN	), // VERTICAL LINE
/*MATHEMATICAL       */	DEADTRANS(	L'A'	,0x2133	,0x2115	,CHAIN	), // DOUBLE-STRUCK CAPITAL N
/*MATHEMATICAL       */	DEADTRANS(	L'a'	,0x2133	,0x2115	,CHAIN	), // DOUBLE-STRUCK CAPITAL N
/*MATHEMATICAL       */	DEADTRANS(	L'B'	,0x2133	,0x212c	,CHAIN	), // SCRIPT CAPITAL B
/*MATHEMATICAL       */	DEADTRANS(	L'b'	,0x2133	,0x212c	,CHAIN	), // SCRIPT CAPITAL B
/*MATHEMATICAL       */	DEADTRANS(	L'C'	,0x2133	,0x212f	,CHAIN	), // SCRIPT SMALL E
/*MATHEMATICAL       */	DEADTRANS(	L'c'	,0x2133	,0x212f	,CHAIN	), // SCRIPT SMALL E
/*MATHEMATICAL       */	DEADTRANS(	L'D'	,0x2133	,0x2131	,CHAIN	), // SCRIPT CAPITAL F
/*MATHEMATICAL       */	DEADTRANS(	L'd'	,0x2133	,0x2131	,CHAIN	), // SCRIPT CAPITAL F
/*MATHEMATICAL       */	DEADTRANS(	L'F'	,0x2133	,0x212d	,CHAIN	), // BLACK-LETTER CAPITAL C
/*MATHEMATICAL       */	DEADTRANS(	L'f'	,0x2133	,0x212d	,CHAIN	), // BLACK-LETTER CAPITAL C
/*MATHEMATICAL       */	DEADTRANS(	L'G'	,0x2133	,0x210a	,CHAIN	), // SCRIPT SMALL G
/*MATHEMATICAL       */	DEADTRANS(	L'g'	,0x2133	,0x210a	,CHAIN	), // SCRIPT SMALL G
/*MATHEMATICAL       */	DEADTRANS(	L'H'	,0x2133	,0x211c	,CHAIN	), // BLACK-LETTER CAPITAL R
/*MATHEMATICAL       */	DEADTRANS(	L'h'	,0x2133	,0x211c	,CHAIN	), // BLACK-LETTER CAPITAL R
/*MATHEMATICAL       */	DEADTRANS(	L'I'	,0x2133	,0x210e	,CHAIN	), // PLANCK CONSTANT
/*MATHEMATICAL       */	DEADTRANS(	L'i'	,0x2133	,0x210e	,CHAIN	), // PLANCK CONSTANT
/*MATHEMATICAL       */	DEADTRANS(	L'J'	,0x2133	,0x2110	,CHAIN	), // SCRIPT CAPITAL I
/*MATHEMATICAL       */	DEADTRANS(	L'j'	,0x2133	,0x2110	,CHAIN	), // SCRIPT CAPITAL I
/*MATHEMATICAL       */	DEADTRANS(	L'M'	,0x2133	,0x2102	,CHAIN	), // DOUBLE-STRUCK CAPITAL C
/*MATHEMATICAL       */	DEADTRANS(	L'm'	,0x2133	,0x2102	,CHAIN	), // DOUBLE-STRUCK CAPITAL C
/*MATHEMATICAL       */	DEADTRANS(	L'S'	,0x2133	,0x210b	,CHAIN	), // SCRIPT CAPITAL H
/*MATHEMATICAL       */	DEADTRANS(	L's'	,0x2133	,0x210b	,CHAIN	), // SCRIPT CAPITAL H
/*MATHEMATICAL       */	DEADTRANS(	L'T'	,0x2133	,0x2112	,CHAIN	), // SCRIPT CAPITAL L
/*MATHEMATICAL       */	DEADTRANS(	L't'	,0x2133	,0x2112	,CHAIN	), // SCRIPT CAPITAL L
/*MATHEMATICAL       */	DEADTRANS(	L'U'	,0x2133	,0x211b	,CHAIN	), // SCRIPT CAPITAL R
/*MATHEMATICAL       */	DEADTRANS(	L'u'	,0x2133	,0x211b	,CHAIN	), // SCRIPT CAPITAL R
/*MATHEMATICAL       */	DEADTRANS(	L'V'	,0x2133	,0x2130	,CHAIN	), // SCRIPT CAPITAL E
/*MATHEMATICAL       */	DEADTRANS(	L'v'	,0x2133	,0x2130	,CHAIN	), // SCRIPT CAPITAL E
/*MATHEMATICAL       */	DEADTRANS(	0x0023	,0x2133	,0x2115	,CHAIN	), // DOUBLE-STRUCK CAPITAL N
/*MATHEMATICAL       */	DEADTRANS(	0x0024	,0x2133	,0x210b	,CHAIN	), // SCRIPT CAPITAL H
/*MATHEMATICAL       */	DEADTRANS(	0x0025	,0x2133	,0x212d	,CHAIN	), // BLACK-LETTER CAPITAL C
/*MATHEMATICAL       */	DEADTRANS(	0x0026	,0x2133	,0x212f	,CHAIN	), // SCRIPT SMALL E
/*MATHEMATICAL       */	DEADTRANS(	0x002a	,0x2133	,0x212c	,CHAIN	), // SCRIPT CAPITAL B
/*MATHEMATICAL       */	DEADTRANS(	0x002f	,0x2133	,0x210e	,CHAIN	), // PLANCK CONSTANT
/*MATHEMATICAL       */	DEADTRANS(	0x003d	,0x2133	,0x2102	,CHAIN	), // DOUBLE-STRUCK CAPITAL C
/*OGONEK&MACRON      */	DEADTRANS(	L'O'	,0x01ed	,0x01ec	,DKF_0	), // LATIN CAPITAL LETTER O WITH OGONEK AND MACRON
/*OGONEK&MACRON      */	DEADTRANS(	L'o'	,0x01ed	,0x01ed	,DKF_0	), // LATIN SMALL LETTER O WITH OGONEK AND MACRON
/*OGONEK/CROOK       */	DEADTRANS(	0x0020	,0x01eb	,0x0328	,DKF_0	), // COMBINING OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	0x00a0	,0x01eb	,0x02db	,DKF_0	), // OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	0x202f	,0x01eb	,0x02db	,DKF_0	), // OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'A'	,0x01eb	,0x0104	,DKF_0	), // LATIN CAPITAL LETTER A WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'a'	,0x01eb	,0x0105	,DKF_0	), // LATIN SMALL LETTER A WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'B'	,0x01eb	,0x0181	,DKF_0	), // LATIN CAPITAL LETTER B WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'b'	,0x01eb	,0x0253	,DKF_0	), // LATIN SMALL LETTER B WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'C'	,0x01eb	,0x0187	,DKF_0	), // LATIN CAPITAL LETTER C WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'c'	,0x01eb	,0x0188	,DKF_0	), // LATIN SMALL LETTER C WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'D'	,0x01eb	,0x018a	,DKF_0	), // LATIN CAPITAL LETTER D WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'd'	,0x01eb	,0x0257	,DKF_0	), // LATIN SMALL LETTER D WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'E'	,0x01eb	,0x0118	,DKF_0	), // LATIN CAPITAL LETTER E WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'e'	,0x01eb	,0x0119	,DKF_0	), // LATIN SMALL LETTER E WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'F'	,0x01eb	,0x0191	,DKF_0	), // LATIN CAPITAL LETTER F WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'f'	,0x01eb	,0x0192	,DKF_0	), // LATIN SMALL LETTER F WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'G'	,0x01eb	,0x0193	,DKF_0	), // LATIN CAPITAL LETTER G WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'g'	,0x01eb	,0x0260	,DKF_0	), // LATIN SMALL LETTER G WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'H'	,0x01eb	,0xa7aa	,DKF_0	), // LATIN CAPITAL LETTER H WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'h'	,0x01eb	,0x0266	,DKF_0	), // LATIN SMALL LETTER H WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'I'	,0x01eb	,0x012e	,DKF_0	), // LATIN CAPITAL LETTER I WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'i'	,0x01eb	,0x012f	,DKF_0	), // LATIN SMALL LETTER I WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'K'	,0x01eb	,0x0198	,DKF_0	), // LATIN CAPITAL LETTER K WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'k'	,0x01eb	,0x0199	,DKF_0	), // LATIN SMALL LETTER K WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'O'	,0x01eb	,0x01ea	,DKF_0	), // LATIN CAPITAL LETTER O WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'o'	,0x01eb	,0x01eb	,DKF_0	), // LATIN SMALL LETTER O WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'P'	,0x01eb	,0x01a4	,DKF_0	), // LATIN CAPITAL LETTER P WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'p'	,0x01eb	,0x01a5	,DKF_0	), // LATIN SMALL LETTER P WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'q'	,0x01eb	,0x02a0	,DKF_0	), // LATIN SMALL LETTER Q WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'r'	,0x01eb	,0x027e	,DKF_0	), // LATIN SMALL LETTER R WITH FISHHOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'T'	,0x01eb	,0x01ac	,DKF_0	), // LATIN CAPITAL LETTER T WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L't'	,0x01eb	,0x01ad	,DKF_0	), // LATIN SMALL LETTER T WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'U'	,0x01eb	,0x0172	,DKF_0	), // LATIN CAPITAL LETTER U WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'u'	,0x01eb	,0x0173	,DKF_0	), // LATIN SMALL LETTER U WITH OGONEK
/*OGONEK/CROOK       */	DEADTRANS(	L'V'	,0x01eb	,0x01b2	,DKF_0	), // LATIN CAPITAL LETTER V WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'v'	,0x01eb	,0x028b	,DKF_0	), // LATIN SMALL LETTER V WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'W'	,0x01eb	,0x2c72	,DKF_0	), // LATIN CAPITAL LETTER W WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'w'	,0x01eb	,0x2c73	,DKF_0	), // LATIN SMALL LETTER W WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'Y'	,0x01eb	,0x01b3	,DKF_0	), // LATIN CAPITAL LETTER Y WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'y'	,0x01eb	,0x01b4	,DKF_0	), // LATIN SMALL LETTER Y WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'Z'	,0x01eb	,0x0224	,DKF_0	), // LATIN CAPITAL LETTER Z WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'z'	,0x01eb	,0x0225	,DKF_0	), // LATIN SMALL LETTER Z WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	0x005b	,0x01eb	,0x02ad	,DKF_0	), // LATIN LETTER BIDENTAL PERCUSSIVE
/*OGONEK/CROOK       */	DEADTRANS(	L'e'	,0x02ad	,0x029a	,DKF_0	), // LATIN SMALL LETTER CLOSED OPEN E
/*OGONEK/CROOK       */	DEADTRANS(	L'o'	,0x02ad	,0x0277	,DKF_0	), // LATIN SMALL LETTER CLOSED OMEGA
/*OGONEK/CROOK       */	DEADTRANS(	0x005c	,0x02ad	,0x025e	,DKF_0	), // LATIN SMALL LETTER CLOSED REVERSED OPEN E
/*OGONEK/CROOK       */	DEADTRANS(	0x005f	,0x01eb	,0x01ed	,CHAIN	), // LATIN SMALL LETTER O WITH OGONEK AND MACRON
/*OGONEK/CROOK       */	DEADTRANS(	0x007b	,0x01eb	,0x1d91	,DKF_0	), // LATIN SMALL LETTER D WITH HOOK AND TAIL
/*OGONEK/CROOK       */	DEADTRANS(	0x007e	,0x01eb	,0x1d73	,DKF_0	), // LATIN SMALL LETTER R WITH FISHHOOK AND MIDDLE TILDE
/*OGONEK/CROOK       */	DEADTRANS(	0x00a9	,0x01eb	,0x025a	,CHAIN	), // LATIN SMALL LETTER SCHWA WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	L'e'	,0x025a	,0x025a	,DKF_0	), // LATIN SMALL LETTER SCHWA WITH HOOK
/*OGONEK/CROOK       */	DEADTRANS(	0x00f5	,0x01eb	,0x1d73	,DKF_0	), // LATIN SMALL LETTER R WITH FISHHOOK AND MIDDLE TILDE
/*OGONEK/CROOK       */	DEADTRANS(	0x014d	,0x01eb	,0x01ed	,CHAIN	), // LATIN SMALL LETTER O WITH OGONEK AND MACRON
/*PALATAL_HOOK       */	DEADTRANS(	L'B'	,0x0192	,0xa796	,DKF_0	), // LATIN CAPITAL LETTER B WITH FLOURISH
/*PALATAL_HOOK       */	DEADTRANS(	L'b'	,0x0192	,0xa797	,DKF_0	), // LATIN SMALL LETTER B WITH FLOURISH
/*PALATAL_HOOK       */	DEADTRANS(	L'e'	,0x0192	,0xab34	,DKF_0	), // LATIN SMALL LETTER E WITH FLOURISH
/*PALATAL_HOOK       */	DEADTRANS(	L'F'	,0x0192	,0x0191	,DKF_0	), // LATIN CAPITAL LETTER F WITH HOOK
/*PALATAL_HOOK       */	DEADTRANS(	L'f'	,0x0192	,0x0192	,DKF_0	), // LATIN SMALL LETTER F WITH HOOK
/*PALATAL_HOOK       */	DEADTRANS(	L'M'	,0x0192	,0x2c6e	,DKF_0	), // LATIN CAPITAL LETTER M WITH HOOK
/*PALATAL_HOOK       */	DEADTRANS(	L'm'	,0x0192	,0x0271	,DKF_0	), // LATIN SMALL LETTER M WITH HOOK
/*PALATAL_HOOK       */	DEADTRANS(	L'N'	,0x0192	,0x019d	,DKF_0	), // LATIN CAPITAL LETTER N WITH LEFT HOOK
/*PALATAL_HOOK       */	DEADTRANS(	L'n'	,0x0192	,0x0272	,DKF_0	), // LATIN SMALL LETTER N WITH LEFT HOOK
/*PALATAL_HOOK       */	DEADTRANS(	L'P'	,0x0192	,0xa752	,DKF_0	), // LATIN CAPITAL LETTER P WITH FLOURISH
/*PALATAL_HOOK       */	DEADTRANS(	L'p'	,0x0192	,0xa753	,DKF_0	), // LATIN SMALL LETTER P WITH FLOURISH
/*PALATAL_HOOK       */	DEADTRANS(	L'Q'	,0x0192	,0x024a	,DKF_0	), // LATIN CAPITAL LETTER SMALL Q WITH HOOK TAIL
/*PALATAL_HOOK       */	DEADTRANS(	L'q'	,0x0192	,0x024b	,DKF_0	), // LATIN SMALL LETTER Q WITH HOOK TAIL
/*PALATAL_HOOK       */	DEADTRANS(	L'S'	,0x0192	,0x2c7e	,DKF_0	), // LATIN CAPITAL LETTER S WITH SWASH TAIL
/*PALATAL_HOOK       */	DEADTRANS(	L's'	,0x0192	,0x023f	,DKF_0	), // LATIN SMALL LETTER S WITH SWASH TAIL
/*PALATAL_HOOK       */	DEADTRANS(	L'u'	,0x0192	,0xab52	,DKF_0	), // LATIN SMALL LETTER U WITH LEFT HOOK
/*PALATAL_HOOK       */	DEADTRANS(	L'Z'	,0x0192	,0x2c7f	,DKF_0	), // LATIN CAPITAL LETTER Z WITH SWASH TAIL
/*PALATAL_HOOK       */	DEADTRANS(	L'z'	,0x0192	,0x0240	,DKF_0	), // LATIN SMALL LETTER Z WITH SWASH TAIL
/*PALATAL_HOOK       */	DEADTRANS(	0x007d	,0x0192	,0xa755	,CHAIN	), // LATIN SMALL LETTER P WITH SQUIRREL TAIL
/*PALATAL_HOOK       */	DEADTRANS(	L'P'	,0xa755	,0xa754	,DKF_0	), // LATIN CAPITAL LETTER P WITH SQUIRREL TAIL
/*PALATAL_HOOK       */	DEADTRANS(	L'p'	,0xa755	,0xa755	,DKF_0	), // LATIN SMALL LETTER P WITH SQUIRREL TAIL
/*PALATAL_HOOK       */	DEADTRANS(	0x00a9	,0x0192	,0x01ba	,DKF_0	), // LATIN SMALL LETTER EZH WITH TAIL
/*PARENTHESIZED      */	DEADTRANS(	L'a'	,0x24aa	,0x249c	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER A
/*PARENTHESIZED      */	DEADTRANS(	L'b'	,0x24aa	,0x249d	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER B
/*PARENTHESIZED      */	DEADTRANS(	L'c'	,0x24aa	,0x249e	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER C
/*PARENTHESIZED      */	DEADTRANS(	L'd'	,0x24aa	,0x249f	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER D
/*PARENTHESIZED      */	DEADTRANS(	L'e'	,0x24aa	,0x24a0	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER E
/*PARENTHESIZED      */	DEADTRANS(	L'f'	,0x24aa	,0x24a1	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER F
/*PARENTHESIZED      */	DEADTRANS(	L'g'	,0x24aa	,0x24a2	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER G
/*PARENTHESIZED      */	DEADTRANS(	L'h'	,0x24aa	,0x24a3	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER H
/*PARENTHESIZED      */	DEADTRANS(	L'i'	,0x24aa	,0x24a4	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER I
/*PARENTHESIZED      */	DEADTRANS(	L'j'	,0x24aa	,0x24a5	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER J
/*PARENTHESIZED      */	DEADTRANS(	L'k'	,0x24aa	,0x24a6	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER K
/*PARENTHESIZED      */	DEADTRANS(	L'l'	,0x24aa	,0x24a7	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER L
/*PARENTHESIZED      */	DEADTRANS(	L'm'	,0x24aa	,0x24a8	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER M
/*PARENTHESIZED      */	DEADTRANS(	L'n'	,0x24aa	,0x24a9	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER N
/*PARENTHESIZED      */	DEADTRANS(	L'o'	,0x24aa	,0x24aa	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER O
/*PARENTHESIZED      */	DEADTRANS(	L'p'	,0x24aa	,0x24ab	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER P
/*PARENTHESIZED      */	DEADTRANS(	L'q'	,0x24aa	,0x24ac	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER Q
/*PARENTHESIZED      */	DEADTRANS(	L'r'	,0x24aa	,0x24ad	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER R
/*PARENTHESIZED      */	DEADTRANS(	L's'	,0x24aa	,0x24ae	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER S
/*PARENTHESIZED      */	DEADTRANS(	L't'	,0x24aa	,0x24af	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER T
/*PARENTHESIZED      */	DEADTRANS(	L'u'	,0x24aa	,0x24b0	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER U
/*PARENTHESIZED      */	DEADTRANS(	L'v'	,0x24aa	,0x24b1	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER V
/*PARENTHESIZED      */	DEADTRANS(	L'w'	,0x24aa	,0x24b2	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER W
/*PARENTHESIZED      */	DEADTRANS(	L'x'	,0x24aa	,0x24b3	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER X
/*PARENTHESIZED      */	DEADTRANS(	L'y'	,0x24aa	,0x24b4	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER Y
/*PARENTHESIZED      */	DEADTRANS(	L'z'	,0x24aa	,0x24b5	,DKF_0	), // PARENTHESIZED LATIN SMALL LETTER Z
/*PARENTHESIZED      */	DEADTRANS(	L'1'	,0x24aa	,0x2474	,CHAIN	), // PARENTHESIZED DIGIT ONE
/*PARENTHESIZED      */	DEADTRANS(	L'2'	,0x24aa	,0x2475	,CHAIN	), // PARENTHESIZED DIGIT TWO
/*PARENTHESIZED      */	DEADTRANS(	L'3'	,0x24aa	,0x2476	,DKF_0	), // PARENTHESIZED DIGIT THREE
/*PARENTHESIZED      */	DEADTRANS(	L'4'	,0x24aa	,0x2477	,DKF_0	), // PARENTHESIZED DIGIT FOUR
/*PARENTHESIZED      */	DEADTRANS(	L'5'	,0x24aa	,0x2478	,DKF_0	), // PARENTHESIZED DIGIT FIVE
/*PARENTHESIZED      */	DEADTRANS(	L'6'	,0x24aa	,0x2479	,DKF_0	), // PARENTHESIZED DIGIT SIX
/*PARENTHESIZED      */	DEADTRANS(	L'7'	,0x24aa	,0x247a	,DKF_0	), // PARENTHESIZED DIGIT SEVEN
/*PARENTHESIZED      */	DEADTRANS(	L'8'	,0x24aa	,0x247b	,DKF_0	), // PARENTHESIZED DIGIT EIGHT
/*PARENTHESIZED      */	DEADTRANS(	L'9'	,0x24aa	,0x247c	,DKF_0	), // PARENTHESIZED DIGIT NINE
/*PARENTHESIZED_1#   */	DEADTRANS(	L'0'	,0x2474	,0x247d	,DKF_0	), // PARENTHESIZED NUMBER TEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'1'	,0x2474	,0x247e	,DKF_0	), // PARENTHESIZED NUMBER ELEVEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'2'	,0x2474	,0x247f	,DKF_0	), // PARENTHESIZED NUMBER TWELVE
/*PARENTHESIZED_1#   */	DEADTRANS(	L'3'	,0x2474	,0x2480	,DKF_0	), // PARENTHESIZED NUMBER THIRTEEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'4'	,0x2474	,0x2481	,DKF_0	), // PARENTHESIZED NUMBER FOURTEEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'5'	,0x2474	,0x2482	,DKF_0	), // PARENTHESIZED NUMBER FIFTEEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'6'	,0x2474	,0x2483	,DKF_0	), // PARENTHESIZED NUMBER SIXTEEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'7'	,0x2474	,0x2484	,DKF_0	), // PARENTHESIZED NUMBER SEVENTEEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'8'	,0x2474	,0x2485	,DKF_0	), // PARENTHESIZED NUMBER EIGHTEEN
/*PARENTHESIZED_1#   */	DEADTRANS(	L'9'	,0x2474	,0x2486	,DKF_0	), // PARENTHESIZED NUMBER NINETEEN
/*PARENTHESIZED_1#   */	DEADTRANS(	0x0029	,0x2474	,0x2474	,DKF_0	), // PARENTHESIZED DIGIT ONE
/*PARENTHESIZED_2#   */	DEADTRANS(	L'0'	,0x2475	,0x2487	,DKF_0	), // PARENTHESIZED NUMBER TWENTY
/*PARENTHESIZED_2#   */	DEADTRANS(	0x0029	,0x2475	,0x2475	,DKF_0	), // PARENTHESIZED DIGIT TWO
/*RECOMPOSE          */	DEADTRANS(	0x00e9	,0x00ae	,0x1def	,CHAIN	), // COMBINING LATIN SMALL LETTER ESH
/*RECOMPOSE          */	DEADTRANS(	L'c'	,0x1def	,0x1def	,DKF_0	), // COMBINING LATIN SMALL LETTER ESH
/*RECOMPOSE          */	DEADTRANS(	L'd'	,0x1def	,0x1dd9	,DKF_0	), // COMBINING LATIN SMALL LETTER ETH
/*RECOMPOSE          */	DEADTRANS(	L'e'	,0x1def	,0x1dea	,DKF_0	), // COMBINING LATIN SMALL LETTER SCHWA
/*RECOMPOSE          */	DEADTRANS(	L's'	,0x1def	,0x1de5	,DKF_0	), // COMBINING LATIN SMALL LETTER LONG S
/*RECOMPOSE          */	DEADTRANS(	L'w'	,0x1def	,0x035b	,DKF_0	), // COMBINING ZIGZAG ABOVE
/*RECOMPOSE          */	DEADTRANS(	L'x'	,0x1def	,0x033d	,DKF_0	), // COMBINING X ABOVE
/*RECOMPOSE          */	DEADTRANS(	L'z'	,0x1def	,0x035b	,DKF_0	), // COMBINING ZIGZAG ABOVE
/*RECOMPOSE          */	DEADTRANS(	L'd'	,0x00ae	,0x02a4	,DKF_0	), // LATIN SMALL LETTER DEZH DIGRAPH
/*RECOMPOSE          */	DEADTRANS(	L's'	,0x00ae	,0xab4d	,DKF_0	), // LATIN SMALL LETTER BASELINE ESH
/*RECOMPOSE          */	DEADTRANS(	0x00a7	,0x00ae	,0xab51	,DKF_0	), // LATIN SMALL LETTER TURNED UI
/*RECOMPOSE          */	DEADTRANS(	0x0024	,0x00ae	,0x00a4	,CHAIN	), // CURRENCY SIGN
/*RECOMPOSE          */	DEADTRANS(	0x0026	,0x00ae	,0x2113	,CHAIN	), // SCRIPT SMALL L
/*RECOMPOSE          */	DEADTRANS(	0x002d	,0x00ae	,0x0284	,CHAIN	), // LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK
/*RECOMPOSE          */	DEADTRANS(	L'c'	,0x0284	,0x0284	,DKF_0	), // LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK
/*RECOMPOSE          */	DEADTRANS(	L's'	,0x0284	,0x1e9d	,DKF_0	), // LATIN SMALL LETTER LONG S WITH HIGH STROKE
/*RECOMPOSE          */	DEADTRANS(	L'T'	,0x0284	,0xa764	,DKF_0	), // LATIN CAPITAL LETTER THORN WITH STROKE
/*RECOMPOSE          */	DEADTRANS(	L't'	,0x0284	,0xa765	,DKF_0	), // LATIN SMALL LETTER THORN WITH STROKE
/*RECOMPOSE          */	DEADTRANS(	0x002f	,0x00ae	,0x1e9c	,CHAIN	), // LATIN SMALL LETTER LONG S WITH DIAGONAL STROKE
/*RECOMPOSE          */	DEADTRANS(	0x00a6	,0x00ae	,0x00a6	,CHAIN	), // BROKEN BAR
/*RECOMPOSE          */	DEADTRANS(	0x003c	,0x00ae	,0x01ef	,CHAIN	), // LATIN SMALL LETTER EZH WITH CARON
/*RECOMPOSE          */	DEADTRANS(	L'D'	,0x01ef	,0x01c4	,CHAIN	), // LATIN CAPITAL LETTER DZ WITH CARON
/*RECOMPOSE          */	DEADTRANS(	L'Z'	,0x01c4	,0x01c4	,DKF_0	), // LATIN CAPITAL LETTER DZ WITH CARON
/*RECOMPOSE          */	DEADTRANS(	L'z'	,0x01c4	,0x01c5	,DKF_0	), // LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
/*RECOMPOSE          */	DEADTRANS(	L'd'	,0x01ef	,0x01c6	,DKF_0	), // LATIN SMALL LETTER DZ WITH CARON
/*RECOMPOSE          */	DEADTRANS(	L'Z'	,0x01ef	,0x01ee	,DKF_0	), // LATIN CAPITAL LETTER EZH WITH CARON
/*RECOMPOSE          */	DEADTRANS(	L'z'	,0x01ef	,0x01ef	,DKF_0	), // LATIN SMALL LETTER EZH WITH CARON
/*RECOMPOSE          */	DEADTRANS(	0x005b	,0x00ae	,0x0267	,CHAIN	), // LATIN SMALL LETTER HENG WITH HOOK
/*RECOMPOSE          */	DEADTRANS(	L'e'	,0x0267	,0x025a	,DKF_0	), // LATIN SMALL LETTER SCHWA WITH HOOK
/*RECOMPOSE          */	DEADTRANS(	L'h'	,0x0267	,0x0267	,DKF_0	), // LATIN SMALL LETTER HENG WITH HOOK
/*RECOMPOSE          */	DEADTRANS(	L'Z'	,0x0267	,0xa762	,DKF_0	), // LATIN CAPITAL LETTER VISIGOTHIC Z
/*RECOMPOSE          */	DEADTRANS(	L'z'	,0x0267	,0xa763	,DKF_0	), // LATIN SMALL LETTER VISIGOTHIC Z
/*RECOMPOSE          */	DEADTRANS(	0x005d	,0x00ae	,0x1d8b	,DKF_0	), // LATIN SMALL LETTER ESH WITH PALATAL HOOK
/*RECOMPOSE          */	DEADTRANS(	0x005e	,0x00ae	,0x1d9e	,CHAIN	), // MODIFIER LETTER SMALL ETH
/*RECOMPOSE          */	DEADTRANS(	0x005f	,0x00ae	,0x01e2	,CHAIN	), // LATIN CAPITAL LETTER AE WITH MACRON
/*RECOMPOSE          */	DEADTRANS(	L'A'	,0x01e2	,0x01e2	,DKF_0	), // LATIN CAPITAL LETTER AE WITH MACRON
/*RECOMPOSE          */	DEADTRANS(	L'a'	,0x01e2	,0x01e3	,DKF_0	), // LATIN SMALL LETTER AE WITH MACRON
/*RECOMPOSE          */	DEADTRANS(	0x0060	,0x00ae	,0x00a4	,CHAIN	), // CURRENCY SIGN
/*RECOMPOSE          */	DEADTRANS(	0x007b	,0x00ae	,0x1d98	,CHAIN	), // LATIN SMALL LETTER ESH WITH RETROFLEX HOOK
/*RECOMPOSE          */	DEADTRANS(	L'c'	,0x1d98	,0x1d98	,DKF_0	), // LATIN SMALL LETTER ESH WITH RETROFLEX HOOK
/*RECOMPOSE          */	DEADTRANS(	L'e'	,0x1d98	,0x1d95	,DKF_0	), // LATIN SMALL LETTER SCHWA WITH RETROFLEX HOOK
/*RECOMPOSE          */	DEADTRANS(	L's'	,0x1d98	,0x1d98	,DKF_0	), // LATIN SMALL LETTER ESH WITH RETROFLEX HOOK
/*RECOMPOSE          */	DEADTRANS(	L'z'	,0x1d98	,0x1d9a	,DKF_0	), // LATIN SMALL LETTER EZH WITH RETROFLEX HOOK
/*RECOMPOSE          */	DEADTRANS(	0x00b0	,0x00ae	,0xa75c	,DKF_0	), // LATIN CAPITAL LETTER RUM ROTUNDA
/*RECOMPOSE          */	DEADTRANS(	L'R'	,0xa75c	,0xa75c	,DKF_0	), // LATIN CAPITAL LETTER RUM ROTUNDA
/*RECOMPOSE          */	DEADTRANS(	L'r'	,0xa75c	,0xa75d	,DKF_0	), // LATIN SMALL LETTER RUM ROTUNDA
/*RECOMPOSE          */	DEADTRANS(	0x00ea	,0x00ae	,0x1d9e	,CHAIN	), // MODIFIER LETTER SMALL ETH
/*RECOMPOSE          */	DEADTRANS(	L'c'	,0x1d9e	,0x1d9d	,DKF_0	), // MODIFIER LETTER SMALL C WITH CURL
/*RECOMPOSE          */	DEADTRANS(	L'd'	,0x1d9e	,0x1d9e	,DKF_0	), // MODIFIER LETTER SMALL ETH
/*RECOMPOSE          */	DEADTRANS(	0x0259	,0x1d9e	,0x1d4a	,DKF_0	), // MODIFIER LETTER SMALL SCHWA
/*RECOMPOSE          */	DEADTRANS(	L'h'	,0x1d9e	,0xab5c	,DKF_0	), // MODIFIER LETTER SMALL HENG
/*RECOMPOSE          */	DEADTRANS(	L'j'	,0x1d9e	,0x1da8	,DKF_0	), // MODIFIER LETTER SMALL J WITH CROSSED-TAIL
/*RECOMPOSE          */	DEADTRANS(	0x014b	,0x1d9e	,0x1d51	,DKF_0	), // MODIFIER LETTER SMALL ENG
/*RECOMPOSE          */	DEADTRANS(	L'O'	,0x1d9e	,0x1d3d	,DKF_0	), // MODIFIER LETTER CAPITAL OU
/*RECOMPOSE          */	DEADTRANS(	L'o'	,0x1d9e	,0x1d54	,CHAIN	), // MODIFIER LETTER SMALL TOP HALF O
/*RECOMPOSE          */	DEADTRANS(	0x0028	,0x1d54	,0x1d54	,DKF_0	), // MODIFIER LETTER SMALL TOP HALF O
/*RECOMPOSE          */	DEADTRANS(	0x0029	,0x1d54	,0x1d55	,DKF_0	), // MODIFIER LETTER SMALL BOTTOM HALF O
/*RECOMPOSE          */	DEADTRANS(	0x0283	,0x1d9e	,0x1db4	,DKF_0	), // MODIFIER LETTER SMALL ESH
/*RECOMPOSE          */	DEADTRANS(	0x0292	,0x1d9e	,0x1dbe	,DKF_0	), // MODIFIER LETTER SMALL EZH
/*RECOMPOSE          */	DEADTRANS(	0x0026	,0x1d9e	,0x1dbd	,DKF_0	), // MODIFIER LETTER SMALL Z WITH CURL
/*RECOMPOSE          */	DEADTRANS(	0x002d	,0x1d9e	,0x1d2f	,DKF_0	), // MODIFIER LETTER CAPITAL BARRED B
/*RECOMPOSE          */	DEADTRANS(	0x0153	,0x1d9e	,0x1da8	,CHAIN	), // MODIFIER LETTER SMALL J WITH CROSSED-TAIL
/*RECOMPOSE          */	DEADTRANS(	L'c'	,0x1da8	,0x1d9d	,DKF_0	), // MODIFIER LETTER SMALL C WITH CURL
/*RECOMPOSE          */	DEADTRANS(	L'j'	,0x1da8	,0x1da8	,DKF_0	), // MODIFIER LETTER SMALL J WITH CROSSED-TAIL
/*RECOMPOSE          */	DEADTRANS(	L'z'	,0x1da8	,0x1dbd	,DKF_0	), // MODIFIER LETTER SMALL Z WITH CURL
/*RECOMPOSE          */	DEADTRANS(	0x0153	,0x1da8	,0x1da8	,DKF_0	), // MODIFIER LETTER SMALL J WITH CROSSED-TAIL
/*RECOMPOSE          */	DEADTRANS(	0x00a9	,0x2193	,0x2094	,CHAIN	), // LATIN SUBSCRIPT SMALL LETTER SCHWA
/*RECOMPOSE          */	DEADTRANS(	L'A'	,0x2094	,0x1d01	,DKF_0	), // LATIN LETTER SMALL CAPITAL AE
/*RECOMPOSE          */	DEADTRANS(	L'e'	,0x2094	,0x2094	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER SCHWA
/*RECOMPOSE          */	DEADTRANS(	L'O'	,0x2094	,0x1d15	,CHAIN	), // LATIN LETTER SMALL CAPITAL OU
/*RECOMPOSE          */	DEADTRANS(	L'E'	,0x1d15	,0x0276	,DKF_0	), // LATIN LETTER SMALL CAPITAL OE
/*RECOMPOSE          */	DEADTRANS(	L'U'	,0x1d15	,0x1d15	,DKF_0	), // LATIN LETTER SMALL CAPITAL OU
/*RECOMPOSE          */	DEADTRANS(	L'R'	,0x2094	,0xa776	,DKF_0	), // LATIN LETTER SMALL CAPITAL RUM
/*RECOMPOSE          */	DEADTRANS(	L'Z'	,0x2094	,0x1d23	,DKF_0	), // LATIN LETTER SMALL CAPITAL EZH
/*RECOMPOSE          */	DEADTRANS(	L'z'	,0x2094	,0x1d23	,DKF_0	), // LATIN LETTER SMALL CAPITAL EZH
/*RECOMPOSE          */	DEADTRANS(	0x002d	,0x2094	,0x1d03	,CHAIN	), // LATIN LETTER SMALL CAPITAL BARRED B
/*RECOMPOSE          */	DEADTRANS(	L'B'	,0x1d03	,0x1d03	,DKF_0	), // LATIN LETTER SMALL CAPITAL BARRED B
/*RECOMPOSE          */	DEADTRANS(	L'I'	,0x1d03	,0x1d7b	,DKF_0	), // LATIN SMALL CAPITAL LETTER I WITH STROKE
/*RECOMPOSE          */	DEADTRANS(	L'L'	,0x1d03	,0x1d0c	,DKF_0	), // LATIN LETTER SMALL CAPITAL L WITH STROKE
/*RECOMPOSE          */	DEADTRANS(	L'U'	,0x1d03	,0x1d7e	,DKF_0	), // LATIN SMALL CAPITAL LETTER U WITH STROKE
/*RECOMPOSE          */	DEADTRANS(	0x2191	,0x00ae	,0x1d9e	,CHAIN	), // MODIFIER LETTER SMALL ETH
/*RETROFLEX_HOOK     */	DEADTRANS(	0x0020	,0x0273	,0x0322	,DKF_0	), // COMBINING RETROFLEX HOOK BELOW
/*RETROFLEX_HOOK     */	DEADTRANS(	L'a'	,0x0273	,0x1d8f	,DKF_0	), // LATIN SMALL LETTER A WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'D'	,0x0273	,0x0189	,DKF_0	), // LATIN CAPITAL LETTER AFRICAN D
/*RETROFLEX_HOOK     */	DEADTRANS(	L'd'	,0x0273	,0x0256	,DKF_0	), // LATIN SMALL LETTER D WITH TAIL
/*RETROFLEX_HOOK     */	DEADTRANS(	L'e'	,0x0273	,0x1d92	,DKF_0	), // LATIN SMALL LETTER E WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'i'	,0x0273	,0x1d96	,DKF_0	), // LATIN SMALL LETTER I WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'l'	,0x0273	,0x026d	,DKF_0	), // LATIN SMALL LETTER L WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'n'	,0x0273	,0x0273	,DKF_0	), // LATIN SMALL LETTER N WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'Q'	,0x0273	,0x024a	,DKF_0	), // LATIN CAPITAL LETTER SMALL Q WITH HOOK TAIL
/*RETROFLEX_HOOK     */	DEADTRANS(	L'q'	,0x0273	,0x024b	,DKF_0	), // LATIN SMALL LETTER Q WITH HOOK TAIL
/*RETROFLEX_HOOK     */	DEADTRANS(	L'R'	,0x0273	,0x2c64	,DKF_0	), // LATIN CAPITAL LETTER R WITH TAIL
/*RETROFLEX_HOOK     */	DEADTRANS(	L'r'	,0x0273	,0x027d	,DKF_0	), // LATIN SMALL LETTER R WITH TAIL
/*RETROFLEX_HOOK     */	DEADTRANS(	L's'	,0x0273	,0x0282	,DKF_0	), // LATIN SMALL LETTER S WITH HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'T'	,0x0273	,0x01ae	,DKF_0	), // LATIN CAPITAL LETTER T WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L't'	,0x0273	,0x0288	,DKF_0	), // LATIN SMALL LETTER T WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'u'	,0x0273	,0x1d99	,DKF_0	), // LATIN SMALL LETTER U WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'v'	,0x0273	,0x2c71	,DKF_0	), // LATIN SMALL LETTER V WITH RIGHT HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'z'	,0x0273	,0x0290	,DKF_0	), // LATIN SMALL LETTER Z WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	0x0024	,0x0273	,0xa78e	,DKF_0	), // LATIN SMALL LETTER L WITH RETROFLEX HOOK AND BELT
/*RETROFLEX_HOOK     */	DEADTRANS(	0x005c	,0x0273	,0x0285	,DKF_0	), // LATIN SMALL LETTER SQUAT REVERSED ESH
/*RETROFLEX_HOOK     */	DEADTRANS(	0x00a9	,0x1d97	,0x1d95	,CHAIN	), // LATIN SMALL LETTER SCHWA WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'c'	,0x1d95	,0x1d98	,DKF_0	), // LATIN SMALL LETTER ESH WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'e'	,0x1d95	,0x1d95	,DKF_0	), // LATIN SMALL LETTER SCHWA WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L's'	,0x1d95	,0x1d98	,DKF_0	), // LATIN SMALL LETTER ESH WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'z'	,0x1d95	,0x1d9a	,DKF_0	), // LATIN SMALL LETTER EZH WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	0x00a7	,0x0273	,0x1d97	,CHAIN	), // LATIN SMALL LETTER OPEN O WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'c'	,0x1d97	,0x1d97	,DKF_0	), // LATIN SMALL LETTER OPEN O WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	0x00f9	,0x0273	,0x0282	,CHAIN	), // LATIN SMALL LETTER S WITH HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'a'	,0x0282	,0x1d90	,DKF_0	), // LATIN SMALL LETTER ALPHA WITH RETROFLEX HOOK
/*RETROFLEX_HOOK     */	DEADTRANS(	L'e'	,0x0282	,0x1d93	,DKF_0	), // LATIN SMALL LETTER OPEN E WITH RETROFLEX HOOK
/*REVERSED           */	DEADTRANS(	L'C'	,0x1d19	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*REVERSED           */	DEADTRANS(	L'c'	,0x1d19	,0x0254	,DKF_0	), // LATIN SMALL LETTER OPEN O
/*REVERSED           */	DEADTRANS(	L'E'	,0x1d19	,0x018e	,DKF_0	), // LATIN CAPITAL LETTER REVERSED E
/*REVERSED           */	DEADTRANS(	L'e'	,0x1d19	,0x0258	,DKF_0	), // LATIN SMALL LETTER REVERSED E
/*REVERSED           */	DEADTRANS(	L'F'	,0x1d19	,0xa7fb	,DKF_0	), // LATIN EPIGRAPHIC LETTER REVERSED F
/*REVERSED           */	DEADTRANS(	L'o'	,0x1d19	,0xab43	,DKF_0	), // LATIN SMALL LETTER TURNED O OPEN-O
/*REVERSED           */	DEADTRANS(	L'P'	,0x1d19	,0xa7fc	,DKF_0	), // LATIN EPIGRAPHIC LETTER REVERSED P
/*REVERSED           */	DEADTRANS(	L'S'	,0x1d19	,0x01aa	,DKF_0	), // LATIN LETTER REVERSED ESH LOOP
/*REVERSED           */	DEADTRANS(	L's'	,0x1d19	,0x01aa	,DKF_0	), // LATIN LETTER REVERSED ESH LOOP
/*REVERSED           */	DEADTRANS(	L'Z'	,0x1d19	,0x01b8	,DKF_0	), // LATIN CAPITAL LETTER EZH REVERSED
/*REVERSED           */	DEADTRANS(	L'z'	,0x1d19	,0x01b9	,DKF_0	), // LATIN SMALL LETTER EZH REVERSED
/*REVERSED           */	DEADTRANS(	0x0027	,0x1d19	,0x0295	,DKF_0	), // LATIN LETTER PHARYNGEAL VOICED FRICATIVE
/*REVERSED           */	DEADTRANS(	0x002d	,0x1d19	,0x02a2	,DKF_0	), // LATIN LETTER REVERSED GLOTTAL STOP WITH STROKE
/*REVERSED           */	DEADTRANS(	0x002e	,0x1d19	,0xa73f	,CHAIN	), // LATIN SMALL LETTER REVERSED C WITH DOT
/*REVERSED           */	DEADTRANS(	L'C'	,0xa73f	,0xa73e	,DKF_0	), // LATIN CAPITAL LETTER REVERSED C WITH DOT
/*REVERSED           */	DEADTRANS(	L'c'	,0xa73f	,0xa73f	,DKF_0	), // LATIN SMALL LETTER REVERSED C WITH DOT
/*REVERSED           */	DEADTRANS(	0x003b	,0x1d19	,0x204f	,DKF_0	), // REVERSED SEMICOLON
/*REVERSED           */	DEADTRANS(	0x005b	,0x1d19	,0x027f	,DKF_0	), // LATIN SMALL LETTER REVERSED R WITH FISHHOOK
/*REVERSED           */	DEADTRANS(	0x005d	,0x1d19	,0x025d	,DKF_0	), // LATIN SMALL LETTER REVERSED OPEN E WITH HOOK
/*REVERSED           */	DEADTRANS(	0x007b	,0x1d19	,0x1d94	,DKF_0	), // LATIN SMALL LETTER REVERSED OPEN E WITH RETROFLEX HOOK
/*REVERSED           */	DEADTRANS(	0x007c	,0x1d19	,0x204b	,DKF_0	), // REVERSED PILCROW SIGN
/*REVERSED           */	DEADTRANS(	0x00b5	,0x1d19	,0x025c	,CHAIN	), // LATIN SMALL LETTER REVERSED OPEN E
/*REVERSED           */	DEADTRANS(	L'E'	,0x025c	,0xa7ab	,DKF_0	), // LATIN CAPITAL LETTER REVERSED OPEN E
/*REVERSED           */	DEADTRANS(	L'e'	,0x025c	,0x025c	,DKF_0	), // LATIN SMALL LETTER REVERSED OPEN E
/*REVERSED           */	DEADTRANS(	0x00f9	,0x1d19	,0x0295	,DKF_0	), // LATIN LETTER PHARYNGEAL VOICED FRICATIVE
/*REVERSED           */	DEADTRANS(	0x2019	,0x1d19	,0x0295	,DKF_0	), // LATIN LETTER PHARYNGEAL VOICED FRICATIVE
/*RING_ABOVE         */	DEADTRANS(	0x0020	,0x00e5	,0x030a	,DKF_0	), // COMBINING RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	0x00eb	,0x00e5	,0x1ab1	,DKF_0	), // COMBINING DIAERESIS-RING
/*RING_ABOVE         */	DEADTRANS(	0x00a0	,0x00e5	,0x02da	,DKF_0	), // RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	0x202f	,0x00e5	,0x02da	,DKF_0	), // RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	L'A'	,0x00e5	,0x00c5	,DKF_0	), // LATIN CAPITAL LETTER A WITH RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	L'a'	,0x00e5	,0x00e5	,DKF_0	), // LATIN SMALL LETTER A WITH RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	L'C'	,0x00e5	,0x2103	,DKF_0	), // DEGREE CELSIUS
/*RING_ABOVE         */	DEADTRANS(	L'c'	,0x00e5	,0x2103	,DKF_0	), // DEGREE CELSIUS
/*RING_ABOVE         */	DEADTRANS(	L'F'	,0x00e5	,0x2109	,DKF_0	), // DEGREE FAHRENHEIT
/*RING_ABOVE         */	DEADTRANS(	L'f'	,0x00e5	,0x2109	,DKF_0	), // DEGREE FAHRENHEIT
/*RING_ABOVE         */	DEADTRANS(	L'l'	,0x00e5	,0xab39	,DKF_0	), // LATIN SMALL LETTER L WITH MIDDLE RING
/*RING_ABOVE         */	DEADTRANS(	L'o'	,0x00e5	,0x2c7a	,DKF_0	), // LATIN SMALL LETTER O WITH LOW RING INSIDE
/*RING_ABOVE         */	DEADTRANS(	L'R'	,0x00e5	,0xa75a	,DKF_0	), // LATIN CAPITAL LETTER R ROTUNDA
/*RING_ABOVE         */	DEADTRANS(	L'r'	,0x00e5	,0xa75b	,DKF_0	), // LATIN SMALL LETTER R ROTUNDA
/*RING_ABOVE         */	DEADTRANS(	L'U'	,0x00e5	,0x016e	,DKF_0	), // LATIN CAPITAL LETTER U WITH RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	L'u'	,0x00e5	,0x016f	,DKF_0	), // LATIN SMALL LETTER U WITH RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	L'V'	,0x00e5	,0x1efc	,DKF_0	), // LATIN CAPITAL LETTER MIDDLE-WELSH V
/*RING_ABOVE         */	DEADTRANS(	L'v'	,0x00e5	,0x1efd	,DKF_0	), // LATIN SMALL LETTER MIDDLE-WELSH V
/*RING_ABOVE         */	DEADTRANS(	L'w'	,0x00e5	,0x1e98	,DKF_0	), // LATIN SMALL LETTER W WITH RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	L'x'	,0x00e5	,0xab56	,DKF_0	), // LATIN SMALL LETTER X WITH LOW RIGHT RING
/*RING_ABOVE         */	DEADTRANS(	L'y'	,0x00e5	,0x1e99	,DKF_0	), // LATIN SMALL LETTER Y WITH RING ABOVE
/*RING_ABOVE         */	DEADTRANS(	0x0026	,0x00e5	,0xab4c	,DKF_0	), // LATIN SMALL LETTER SCRIPT R WITH RING
/*RING_ABOVE         */	DEADTRANS(	0x0027	,0x00e5	,0x01fb	,CHAIN	), // LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE
/*RING_ABOVE         */	DEADTRANS(	0x00a9	,0x00e5	,0xa75d	,DKF_0	), // LATIN SMALL LETTER RUM ROTUNDA
/*RING_ABOVE         */	DEADTRANS(	L'R'	,0xa75d	,0xa75c	,DKF_0	), // LATIN CAPITAL LETTER RUM ROTUNDA
/*RING_ABOVE         */	DEADTRANS(	L'r'	,0xa75d	,0xa75d	,DKF_0	), // LATIN SMALL LETTER RUM ROTUNDA
/*RING_ABOVE         */	DEADTRANS(	0x00b0	,0x00e5	,0x1e01	,CHAIN	), // LATIN SMALL LETTER A WITH RING BELOW
/*RING_ABOVE         */	DEADTRANS(	0x00e5	,0x00e5	,0x1e01	,CHAIN	), // LATIN SMALL LETTER A WITH RING BELOW
/*RING_ABOVE         */	DEADTRANS(	0x00b5	,0x00e5	,0xab54	,DKF_0	), // LATIN SMALL LETTER CHI WITH LOW RIGHT RING
/*RING_ABOVE         */	DEADTRANS(	0x00e1	,0x00e5	,0x01fb	,CHAIN	), // LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE
/*RING_ABOVE         */	DEADTRANS(	0x00f9	,0x00e5	,0xab54	,DKF_0	), // LATIN SMALL LETTER CHI WITH LOW RIGHT RING
/*RING_ABOVE         */	DEADTRANS(	0x2610	,0x00e5	,0x274d	,DKF_0	), // SHADOWED WHITE CIRCLE
/*RING_ABOVE&ACUTE   */	DEADTRANS(	L'A'	,0x01fb	,0x01fa	,DKF_0	), // LATIN CAPITAL LETTER A WITH RING ABOVE AND ACUTE
/*RING_ABOVE&ACUTE   */	DEADTRANS(	L'a'	,0x01fb	,0x01fb	,DKF_0	), // LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE
/*RING_BELOW         */	DEADTRANS(	0x0020	,0x1e01	,0x0325	,DKF_0	), // COMBINING RING BELOW
/*RING_BELOW         */	DEADTRANS(	0x00a0	,0x1e01	,0x02f3	,DKF_0	), // MODIFIER LETTER LOW RING
/*RING_BELOW         */	DEADTRANS(	0x202f	,0x1e01	,0x02f3	,DKF_0	), // MODIFIER LETTER LOW RING
/*RING_BELOW         */	DEADTRANS(	L'A'	,0x1e01	,0x1e00	,DKF_0	), // LATIN CAPITAL LETTER A WITH RING BELOW
/*RING_BELOW         */	DEADTRANS(	L'a'	,0x1e01	,0x1e01	,DKF_0	), // LATIN SMALL LETTER A WITH RING BELOW
/*RING_BELOW         */	DEADTRANS(	L'L'	,0x1e01	,0xa7ad	,DKF_0	), // LATIN CAPITAL LETTER L WITH BELT
/*RING_BELOW         */	DEADTRANS(	L'l'	,0x1e01	,0x026c	,DKF_0	), // LATIN SMALL LETTER L WITH BELT
/*RING_BELOW         */	DEADTRANS(	L'X'	,0x1e01	,0xab54	,DKF_0	), // LATIN SMALL LETTER CHI WITH LOW RIGHT RING
/*RING_BELOW         */	DEADTRANS(	L'x'	,0x1e01	,0xab56	,DKF_0	), // LATIN SMALL LETTER X WITH LOW RIGHT RING
/*SCRIPT             */	DEADTRANS(	L'G'	,0x2113	,0xa7ac	,DKF_0	), // LATIN CAPITAL LETTER SCRIPT G
/*SCRIPT             */	DEADTRANS(	L'g'	,0x2113	,0x0261	,DKF_0	), // LATIN SMALL LETTER SCRIPT G
/*SCRIPT             */	DEADTRANS(	L'L'	,0x2113	,0x2112	,DKF_0	), // SCRIPT CAPITAL L
/*SCRIPT             */	DEADTRANS(	L'l'	,0x2113	,0x2113	,DKF_0	), // SCRIPT SMALL L
/*SCRIPT             */	DEADTRANS(	L'r'	,0x2113	,0xab4b	,DKF_0	), // LATIN SMALL LETTER SCRIPT R
/*SCRIPT             */	DEADTRANS(	L't'	,0x2113	,0x204a	,DKF_0	), // TIRONIAN SIGN ET
/*SHORTENED          */	DEADTRANS(	L'r'	,0xab4e	,0xab47	,DKF_0	), // LATIN SMALL LETTER R WITHOUT HANDLE
/*SHORTENED          */	DEADTRANS(	L'u'	,0xab4e	,0xab4e	,DKF_0	), // LATIN SMALL LETTER U WITH SHORT RIGHT LEG
/*SHORTENED          */	DEADTRANS(	L'y'	,0xab4e	,0xab5a	,DKF_0	), // LATIN SMALL LETTER Y WITH SHORT RIGHT LEG
/*SHORTENED          */	DEADTRANS(	0x0020	,0xab4e	,0x1dd3	,DKF_0	), // COMBINING LATIN SMALL LETTER FLATTENED OPEN A ABOVE
/*SHORTENED          */	DEADTRANS(	0x002d	,0xab4e	,0xab4f	,DKF_0	), // LATIN SMALL LETTER U BAR WITH SHORT RIGHT LEG
/*SPACE/FORMAT       */	DEADTRANS(	0x0020	,0x005f	,0x2423	,DKF_0	), // OPEN BOX
/*SPACE/FORMAT       */	DEADTRANS(	0x00a0	,0x005f	,0x237d	,DKF_0	), // SHOULDERED OPEN BOX
/*SPACE/FORMAT       */	DEADTRANS(	0x202f	,0x005f	,0x2422	,DKF_0	), // BLANK SYMBOL
/*SPACE/FORMAT       */	DEADTRANS(	L'a'	,0x005f	,0x200c	,DKF_0	), // ZERO WIDTH NON-JOINER
/*SPACE/FORMAT       */	DEADTRANS(	L'b'	,0x005f	,0x034f	,DKF_0	), // COMBINING GRAPHEME JOINER
/*SPACE/FORMAT       */	DEADTRANS(	L'C'	,0x005f	,0x2001	,DKF_0	), // EM QUAD
/*SPACE/FORMAT       */	DEADTRANS(	L'c'	,0x005f	,0x2003	,DKF_0	), // EM SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'D'	,0x005f	,0x2000	,DKF_0	), // EN QUAD
/*SPACE/FORMAT       */	DEADTRANS(	L'd'	,0x005f	,0x2002	,DKF_0	), // EN SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'E'	,0x005f	,0x202a	,CHAIN	), // LEFT-TO-RIGHT EMBEDDING
/*SPACE/FORMAT       */	DEADTRANS(	0x003c	,0x202a	,0x202b	,DKF_0	), // RIGHT-TO-LEFT EMBEDDING
/*SPACE/FORMAT       */	DEADTRANS(	0x003e	,0x202a	,0x202a	,DKF_0	), // LEFT-TO-RIGHT EMBEDDING
/*SPACE/FORMAT       */	DEADTRANS(	L'F'	,0x005f	,0x202d	,CHAIN	), // LEFT-TO-RIGHT OVERRIDE
/*SPACE/FORMAT       */	DEADTRANS(	0x003c	,0x202d	,0x202e	,DKF_0	), // RIGHT-TO-LEFT OVERRIDE
/*SPACE/FORMAT       */	DEADTRANS(	0x003e	,0x202d	,0x202d	,DKF_0	), // LEFT-TO-RIGHT OVERRIDE
/*SPACE/FORMAT       */	DEADTRANS(	L'f'	,0x005f	,0x2009	,DKF_0	), // THIN SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'G'	,0x005f	,0xfeff	,DKF_0	), // ZERO WIDTH NO-BREAK SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'g'	,0x005f	,0x2060	,DKF_0	), // WORD JOINER
/*SPACE/FORMAT       */	DEADTRANS(	L'I'	,0x005f	,0x2066	,CHAIN	), // LEFT-TO-RIGHT ISOLATE
/*SPACE/FORMAT       */	DEADTRANS(	L'a'	,0x2066	,0x2068	,DKF_0	), // FIRST STRONG ISOLATE
/*SPACE/FORMAT       */	DEADTRANS(	0x003c	,0x2066	,0x2067	,DKF_0	), // RIGHT-TO-LEFT ISOLATE
/*SPACE/FORMAT       */	DEADTRANS(	0x003d	,0x2066	,0x2069	,DKF_0	), // POP DIRECTIONAL ISOLATE
/*SPACE/FORMAT       */	DEADTRANS(	0x003e	,0x2066	,0x2066	,DKF_0	), // LEFT-TO-RIGHT ISOLATE
/*SPACE/FORMAT       */	DEADTRANS(	L'i'	,0x005f	,0x00a0	,DKF_0	), // NO-BREAK SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'j'	,0x005f	,0x202f	,DKF_0	), // NARROW NO-BREAK SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'k'	,0x005f	,0x202f	,DKF_0	), // NARROW NO-BREAK SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'l'	,0x005f	,0x200d	,DKF_0	), // ZERO WIDTH JOINER
/*SPACE/FORMAT       */	DEADTRANS(	L'm'	,0x005f	,0x205f	,DKF_0	), // MEDIUM MATHEMATICAL SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'p'	,0x005f	,0x2008	,DKF_0	), // PUNCTUATION SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'q'	,0x005f	,0x2005	,DKF_0	), // FOUR-PER-EM SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'S'	,0x005f	,0x3000	,DKF_0	), // IDEOGRAPHIC SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L's'	,0x005f	,0x2006	,DKF_0	), // SIX-PER-EM SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L't'	,0x005f	,0x2007	,DKF_0	), // FIGURE SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'u'	,0x005f	,0x200a	,DKF_0	), // HAIR SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'0'	,0x005f	,0x200b	,DKF_0	), // ZERO WIDTH SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'1'	,0x005f	,0x2003	,DKF_0	), // EM SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'2'	,0x005f	,0x2002	,DKF_0	), // EN SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'3'	,0x005f	,0x2004	,DKF_0	), // THREE-PER-EM SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'4'	,0x005f	,0x2005	,DKF_0	), // FOUR-PER-EM SPACE
/*SPACE/FORMAT       */	DEADTRANS(	L'6'	,0x005f	,0x2006	,DKF_0	), // SIX-PER-EM SPACE
/*SPACE/FORMAT       */	DEADTRANS(	0x002f	,0x005f	,0x2028	,DKF_0	), // LINE SEPARATOR
/*SPACE/FORMAT       */	DEADTRANS(	0x003c	,0x005f	,0x200f	,DKF_0	), // RIGHT-TO-LEFT MARK
/*SPACE/FORMAT       */	DEADTRANS(	0x003d	,0x005f	,0x202c	,DKF_0	), // POP DIRECTIONAL FORMATTING
/*SPACE/FORMAT       */	DEADTRANS(	0x003e	,0x005f	,0x200e	,DKF_0	), // LEFT-TO-RIGHT MARK
/*SPACE/FORMAT       */	DEADTRANS(	0x007c	,0x005f	,0x2029	,DKF_0	), // PARAGRAPH SEPARATOR
/*SPACE/FORMAT       */	DEADTRANS(	0x00c9	,0x005f	,0x202f	,DKF_0	), // NARROW NO-BREAK SPACE
/*SPACE/FORMAT       */	DEADTRANS(	0x00e9	,0x005f	,0x202f	,DKF_0	), // NARROW NO-BREAK SPACE
/*STROKE&ACUTE       */	DEADTRANS(	L'O'	,0x01ff	,0x01fe	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE AND ACUTE
/*STROKE&ACUTE       */	DEADTRANS(	L'o'	,0x01ff	,0x01ff	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE AND ACUTE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x0020	,0x00f8	,0x0338	,DKF_0	), // COMBINING LONG SOLIDUS OVERLAY
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'A'	,0x00f8	,0x023a	,DKF_0	), // LATIN CAPITAL LETTER A WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'a'	,0x00f8	,0x2c65	,DKF_0	), // LATIN SMALL LETTER A WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'C'	,0x00f8	,0x023b	,DKF_0	), // LATIN CAPITAL LETTER C WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'c'	,0x00f8	,0x023c	,DKF_0	), // LATIN SMALL LETTER C WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'd'	,0x00f8	,0xab3f	,DKF_0	), // LATIN SMALL LETTER OPEN O WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'E'	,0x00f8	,0x0246	,DKF_0	), // LATIN CAPITAL LETTER E WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'e'	,0x00f8	,0x0247	,DKF_0	), // LATIN SMALL LETTER E WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'F'	,0x00f8	,0xa798	,DKF_0	), // LATIN CAPITAL LETTER F WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'f'	,0x00f8	,0xa799	,DKF_0	), // LATIN SMALL LETTER F WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'G'	,0x00f8	,0xa7a0	,DKF_0	), // LATIN CAPITAL LETTER G WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'g'	,0x00f8	,0xa7a1	,DKF_0	), // LATIN SMALL LETTER G WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'K'	,0x00f8	,0xa742	,DKF_0	), // LATIN CAPITAL LETTER K WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'k'	,0x00f8	,0xa743	,DKF_0	), // LATIN SMALL LETTER K WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'L'	,0x00f8	,0x0141	,DKF_0	), // LATIN CAPITAL LETTER L WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'l'	,0x00f8	,0x0142	,DKF_0	), // LATIN SMALL LETTER L WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'm'	,0x00f8	,0x20a5	,DKF_0	), // MILL SIGN
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'N'	,0x00f8	,0xa7a4	,DKF_0	), // LATIN CAPITAL LETTER N WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'n'	,0x00f8	,0xa7a5	,DKF_0	), // LATIN SMALL LETTER N WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'O'	,0x00f8	,0x00d8	,DKF_0	), // LATIN CAPITAL LETTER O WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'o'	,0x00f8	,0x00f8	,DKF_0	), // LATIN SMALL LETTER O WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'Q'	,0x00f8	,0xa758	,DKF_0	), // LATIN CAPITAL LETTER Q WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'q'	,0x00f8	,0xa759	,DKF_0	), // LATIN SMALL LETTER Q WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'R'	,0x00f8	,0xa7a6	,DKF_0	), // LATIN CAPITAL LETTER R WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'r'	,0x00f8	,0xa7a7	,DKF_0	), // LATIN SMALL LETTER R WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'S'	,0x00f8	,0xa7a8	,DKF_0	), // LATIN CAPITAL LETTER S WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L's'	,0x00f8	,0xa7a9	,DKF_0	), // LATIN SMALL LETTER S WITH OBLIQUE STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'T'	,0x00f8	,0x023e	,DKF_0	), // LATIN CAPITAL LETTER T WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L't'	,0x00f8	,0x2c66	,DKF_0	), // LATIN SMALL LETTER T WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'U'	,0x00f8	,0xa7b8	,DKF_0	), // LATIN CAPITAL LETTER U WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'u'	,0x00f8	,0xa7b9	,DKF_0	), // LATIN SMALL LETTER U WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'V'	,0x00f8	,0xa75e	,DKF_0	), // LATIN CAPITAL LETTER V WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'v'	,0x00f8	,0xa75f	,DKF_0	), // LATIN SMALL LETTER V WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'0'	,0x00f8	,0x2205	,DKF_0	), // EMPTY SET
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x0027	,0x00f8	,0x01ff	,CHAIN	), // LATIN SMALL LETTER O WITH STROKE AND ACUTE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x002f	,0x00f8	,0xa743	,CHAIN	), // LATIN SMALL LETTER K WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x003a	,0x00f8	,0x2e4a	,DKF_0	), // DOTTED SOLIDUS
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x003d	,0x00f8	,0x2260	,DKF_0	), // NOT EQUAL TO
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x005d	,0x00f8	,0xab3e	,DKF_0	), // LATIN SMALL LETTER BLACKLETTER O WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x007c	,0x00f8	,0x1e9c	,CHAIN	), // LATIN SMALL LETTER LONG S WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L's'	,0x1e9c	,0x1e9c	,DKF_0	), // LATIN SMALL LETTER LONG S WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L't'	,0x1e9c	,0x1d7a	,DKF_0	), // LATIN SMALL LETTER TH WITH STRIKETHROUGH
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x00a9	,0x00f8	,0x023c	,CHAIN	), // LATIN SMALL LETTER C WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L'o'	,0x023c	,0xab3f	,DKF_0	), // LATIN SMALL LETTER OPEN O WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L's'	,0x023c	,0x1e9c	,DKF_0	), // LATIN SMALL LETTER LONG S WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	L't'	,0x023c	,0x1d7a	,DKF_0	), // LATIN SMALL LETTER TH WITH STRIKETHROUGH
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x00a7	,0x00f8	,0xab3f	,DKF_0	), // LATIN SMALL LETTER OPEN O WITH STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x00e1	,0x00f8	,0x01ff	,CHAIN	), // LATIN SMALL LETTER O WITH STROKE AND ACUTE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x00f5	,0x00f8	,0x034a	,DKF_0	), // COMBINING NOT TILDE ABOVE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x00f8	,0x00f8	,0xa743	,CHAIN	), // LATIN SMALL LETTER K WITH DIAGONAL STROKE
/*STROKE_(DIAGONAL)  */	DEADTRANS(	0x0254	,0x00f8	,0xab3f	,DKF_0	), // LATIN SMALL LETTER OPEN O WITH STROKE
/*STROKE_SHORT       */	DEADTRANS(	0x0020	,0xa743	,0x0337	,DKF_0	), // COMBINING SHORT SOLIDUS OVERLAY
/*STROKE_SHORT       */	DEADTRANS(	L'K'	,0xa743	,0xa7a2	,DKF_0	), // LATIN CAPITAL LETTER K WITH OBLIQUE STROKE
/*STROKE_SHORT       */	DEADTRANS(	L'k'	,0xa743	,0xa7a3	,DKF_0	), // LATIN SMALL LETTER K WITH OBLIQUE STROKE
/*SUBSCRIPT          */	DEADTRANS(	L'A'	,0x005f	,0x1d00	,DKF_0	), // LATIN LETTER SMALL CAPITAL A
/*SUBSCRIPT          */	DEADTRANS(	L'B'	,0x005f	,0x0299	,DKF_0	), // LATIN LETTER SMALL CAPITAL B
/*SUBSCRIPT          */	DEADTRANS(	L'e'	,0x005f	,0x2091	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER E
/*SUBSCRIPT          */	DEADTRANS(	L'H'	,0x005f	,0x029c	,DKF_0	), // LATIN LETTER SMALL CAPITAL H
/*SUBSCRIPT          */	DEADTRANS(	L'h'	,0x005f	,0x2095	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER H
/*SUBSCRIPT          */	DEADTRANS(	L'J'	,0x005f	,0x1d0a	,DKF_0	), // LATIN LETTER SMALL CAPITAL J
/*SUBSCRIPT          */	DEADTRANS(	L'K'	,0x005f	,0x1d0b	,DKF_0	), // LATIN LETTER SMALL CAPITAL K
/*SUBSCRIPT          */	DEADTRANS(	L'L'	,0x005f	,0x029f	,DKF_0	), // LATIN LETTER SMALL CAPITAL L
/*SUBSCRIPT          */	DEADTRANS(	L'M'	,0x005f	,0x1d0d	,DKF_0	), // LATIN LETTER SMALL CAPITAL M
/*SUBSCRIPT          */	DEADTRANS(	L'N'	,0x005f	,0x0274	,DKF_0	), // LATIN LETTER SMALL CAPITAL N
/*SUBSCRIPT          */	DEADTRANS(	L'n'	,0x005f	,0x2099	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER N
/*SUBSCRIPT          */	DEADTRANS(	L'O'	,0x005f	,0x1d0f	,DKF_0	), // LATIN LETTER SMALL CAPITAL O
/*SUBSCRIPT          */	DEADTRANS(	L'o'	,0x005f	,0x2092	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER O
/*SUBSCRIPT          */	DEADTRANS(	L'P'	,0x005f	,0x1d18	,DKF_0	), // LATIN LETTER SMALL CAPITAL P
/*SUBSCRIPT          */	DEADTRANS(	L'Q'	,0x005f	,0xa7af	,DKF_0	), // LATIN LETTER SMALL CAPITAL Q
/*SUBSCRIPT          */	DEADTRANS(	L'R'	,0x005f	,0x0280	,DKF_0	), // LATIN LETTER SMALL CAPITAL R
/*SUBSCRIPT          */	DEADTRANS(	L'r'	,0x005f	,0x1d63	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER R
/*SUBSCRIPT          */	DEADTRANS(	L'T'	,0x005f	,0x1d1b	,DKF_0	), // LATIN LETTER SMALL CAPITAL T
/*SUBSCRIPT          */	DEADTRANS(	L'U'	,0x005f	,0x1d1c	,DKF_0	), // LATIN LETTER SMALL CAPITAL U
/*SUBSCRIPT          */	DEADTRANS(	L'V'	,0x005f	,0x1d20	,DKF_0	), // LATIN LETTER SMALL CAPITAL V
/*SUBSCRIPT          */	DEADTRANS(	L'v'	,0x005f	,0x1d65	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER V
/*SUBSCRIPT          */	DEADTRANS(	L'W'	,0x005f	,0x1d21	,DKF_0	), // LATIN LETTER SMALL CAPITAL W
/*SUBSCRIPT          */	DEADTRANS(	L'x'	,0x005f	,0x2093	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER X
/*SUBSCRIPT          */	DEADTRANS(	L'Y'	,0x005f	,0x028f	,DKF_0	), // LATIN LETTER SMALL CAPITAL Y
/*SUBSCRIPT          */	DEADTRANS(	L'Z'	,0x005f	,0x1d22	,DKF_0	), // LATIN LETTER SMALL CAPITAL Z
/*SUBSCRIPT          */	DEADTRANS(	L'5'	,0x005f	,0x2085	,DKF_0	), // SUBSCRIPT FIVE
/*SUBSCRIPT          */	DEADTRANS(	L'7'	,0x005f	,0x2087	,DKF_0	), // SUBSCRIPT SEVEN
/*SUBSCRIPT          */	DEADTRANS(	L'8'	,0x005f	,0x2088	,DKF_0	), // SUBSCRIPT EIGHT
/*SUBSCRIPT          */	DEADTRANS(	L'9'	,0x005f	,0x2089	,DKF_0	), // SUBSCRIPT NINE
/*SUBSCRIPT          */	DEADTRANS(	0x0023	,0x005f	,0x203f	,CHAIN	), // UNDERTIE
/*SUBSCRIPT          */	DEADTRANS(	0x0021	,0x203f	,0xa71f	,DKF_0	), // MODIFIER LETTER LOW INVERTED EXCLAMATION MARK
/*SUBSCRIPT          */	DEADTRANS(	0x0028	,0x203f	,0x2054	,DKF_0	), // INVERTED UNDERTIE
/*SUBSCRIPT          */	DEADTRANS(	0x0029	,0x203f	,0x203f	,DKF_0	), // UNDERTIE
/*SUBSCRIPT          */	DEADTRANS(	0x0025	,0x005f	,0xa71f	,DKF_0	), // MODIFIER LETTER LOW INVERTED EXCLAMATION MARK
/*SUBSCRIPT          */	DEADTRANS(	0x0027	,0x005f	,0x02cf	,CHAIN	), // MODIFIER LETTER LOW ACUTE ACCENT
/*SUBSCRIPT          */	DEADTRANS(	0x0028	,0x1e2b	,0x1d10	,DKF_0	), // LATIN LETTER SMALL CAPITAL OPEN O
/*SUBSCRIPT          */	DEADTRANS(	0x002a	,0x005f	,0x204e	,DKF_0	), // LOW ASTERISK
/*SUBSCRIPT          */	DEADTRANS(	0x002b	,0x005f	,0x208a	,DKF_0	), // SUBSCRIPT PLUS SIGN
/*SUBSCRIPT          */	DEADTRANS(	0x002c	,0x005f	,0x0219	,CHAIN	), // LATIN SMALL LETTER S WITH COMMA BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x002d	,0x005f	,0xa751	,CHAIN	), // LATIN SMALL LETTER P WITH STROKE THROUGH DESCENDER
/*SUBSCRIPT          */	DEADTRANS(	0x2190	,0x005f	,0x02ff	,DKF_0	), // MODIFIER LETTER LOW LEFT ARROW
/*SUBSCRIPT          */	DEADTRANS(	0x002e	,0x005f	,0x1ecd	,CHAIN	), // LATIN SMALL LETTER O WITH DOT BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x003a	,0x005f	,0x1e73	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x005b	,0x005f	,0x029b	,DKF_0	), // LATIN LETTER SMALL CAPITAL G WITH HOOK
/*SUBSCRIPT          */	DEADTRANS(	0x005c	,0x005f	,0x1d0e	,DKF_0	), // LATIN LETTER SMALL CAPITAL REVERSED N
/*SUBSCRIPT          */	DEADTRANS(	0x005d	,0x005f	,0x02fd	,DKF_0	), // MODIFIER LETTER SHELF
/*SUBSCRIPT          */	DEADTRANS(	0x005e	,0x005f	,0x2038	,DKF_0	), // CARET
/*SUBSCRIPT          */	DEADTRANS(	0x005f	,0x005f	,0x2038	,CHAIN	), // CARET
/*SUBSCRIPT          */	DEADTRANS(	0x0060	,0x005f	,0x02ce	,CHAIN	), // MODIFIER LETTER LOW GRAVE ACCENT
/*SUBSCRIPT          */	DEADTRANS(	L'v'	,0x02cc	,0x02ef	,DKF_0	), // MODIFIER LETTER LOW DOWN ARROWHEAD
/*SUBSCRIPT          */	DEADTRANS(	0x003c	,0x02cc	,0x02f1	,DKF_0	), // MODIFIER LETTER LOW LEFT ARROWHEAD
/*SUBSCRIPT          */	DEADTRANS(	0x003e	,0x02cc	,0x02f2	,DKF_0	), // MODIFIER LETTER LOW RIGHT ARROWHEAD
/*SUBSCRIPT          */	DEADTRANS(	0x005e	,0x02cc	,0x02f0	,DKF_0	), // MODIFIER LETTER LOW UP ARROWHEAD
/*SUBSCRIPT          */	DEADTRANS(	0x202f	,0x02cc	,0x02cc	,DKF_0	), // MODIFIER LETTER LOW VERTICAL LINE
/*SUBSCRIPT          */	DEADTRANS(	0x007e	,0x005f	,0x1e75	,CHAIN	), // LATIN SMALL LETTER U WITH TILDE BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x0152	,0x005f	,0x0276	,DKF_0	), // LATIN LETTER SMALL CAPITAL OE
/*SUBSCRIPT          */	DEADTRANS(	0x0153	,0x005f	,0x0276	,DKF_0	), // LATIN LETTER SMALL CAPITAL OE
/*SUBSCRIPT          */	DEADTRANS(	0x00a9	,0x005f	,0x1d01	,CHAIN	), // LATIN LETTER SMALL CAPITAL AE
/*SUBSCRIPT          */	DEADTRANS(	L'A'	,0x1d01	,0x1d01	,DKF_0	), // LATIN LETTER SMALL CAPITAL AE
/*SUBSCRIPT          */	DEADTRANS(	L'e'	,0x1d01	,0x2094	,DKF_0	), // LATIN SUBSCRIPT SMALL LETTER SCHWA
/*SUBSCRIPT          */	DEADTRANS(	L'O'	,0x1d01	,0x0276	,CHAIN	), // LATIN LETTER SMALL CAPITAL OE
/*SUBSCRIPT          */	DEADTRANS(	L'E'	,0x0276	,0x0276	,DKF_0	), // LATIN LETTER SMALL CAPITAL OE
/*SUBSCRIPT          */	DEADTRANS(	L'U'	,0x0276	,0x1d15	,DKF_0	), // LATIN LETTER SMALL CAPITAL OU
/*SUBSCRIPT          */	DEADTRANS(	L'R'	,0x1d01	,0xa776	,DKF_0	), // LATIN LETTER SMALL CAPITAL RUM
/*SUBSCRIPT          */	DEADTRANS(	L'Z'	,0x1d01	,0x1d23	,DKF_0	), // LATIN LETTER SMALL CAPITAL EZH
/*SUBSCRIPT          */	DEADTRANS(	L'z'	,0x1d01	,0x1d23	,DKF_0	), // LATIN LETTER SMALL CAPITAL EZH
/*SUBSCRIPT          */	DEADTRANS(	0x002d	,0x1d01	,0x1d7b	,CHAIN	), // LATIN SMALL CAPITAL LETTER I WITH STROKE
/*SUBSCRIPT          */	DEADTRANS(	L'B'	,0x1d7b	,0x1d03	,DKF_0	), // LATIN LETTER SMALL CAPITAL BARRED B
/*SUBSCRIPT          */	DEADTRANS(	L'I'	,0x1d7b	,0x1d7b	,DKF_0	), // LATIN SMALL CAPITAL LETTER I WITH STROKE
/*SUBSCRIPT          */	DEADTRANS(	L'L'	,0x1d7b	,0x1d0c	,DKF_0	), // LATIN LETTER SMALL CAPITAL L WITH STROKE
/*SUBSCRIPT          */	DEADTRANS(	L'U'	,0x1d7b	,0x1d7e	,DKF_0	), // LATIN SMALL CAPITAL LETTER U WITH STROKE
/*SUBSCRIPT          */	DEADTRANS(	0x00b0	,0x005f	,0x1e01	,CHAIN	), // LATIN SMALL LETTER A WITH RING BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x00d0	,0x005f	,0x1d06	,DKF_0	), // LATIN LETTER SMALL CAPITAL ETH
/*SUBSCRIPT          */	DEADTRANS(	0x00e1	,0x005f	,0x02cf	,CHAIN	), // MODIFIER LETTER LOW ACUTE ACCENT
/*SUBSCRIPT          */	DEADTRANS(	0x00eb	,0x005f	,0x1e73	,CHAIN	), // LATIN SMALL LETTER U WITH DIAERESIS BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x00f2	,0x005f	,0x02ce	,CHAIN	), // MODIFIER LETTER LOW GRAVE ACCENT
/*SUBSCRIPT          */	DEADTRANS(	0x00f5	,0x005f	,0x1e75	,CHAIN	), // LATIN SMALL LETTER U WITH TILDE BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x2212	,0x005f	,0x208b	,DKF_0	), // SUBSCRIPT MINUS
/*SUBSCRIPT          */	DEADTRANS(	0x022f	,0x005f	,0x1ecd	,CHAIN	), // LATIN SMALL LETTER O WITH DOT BELOW
/*SUBSCRIPT          */	DEADTRANS(	0x014d	,0x005f	,0x1e07	,CHAIN	), // LATIN SMALL LETTER B WITH LINE BELOW
/*SUPERSCRIPT        */	DEADTRANS(	0x202f	,0x005e	,0x2191	,DKF_0	), // UPWARDS ARROW
/*SUPERSCRIPT        */	DEADTRANS(	L'A'	,0x005e	,0x1d2c	,DKF_0	), // MODIFIER LETTER CAPITAL A
/*SUPERSCRIPT        */	DEADTRANS(	L'a'	,0x005e	,0x1d43	,DKF_0	), // MODIFIER LETTER SMALL A
/*SUPERSCRIPT        */	DEADTRANS(	L'B'	,0x005e	,0x1d2e	,DKF_0	), // MODIFIER LETTER CAPITAL B
/*SUPERSCRIPT        */	DEADTRANS(	L'b'	,0x005e	,0x1d47	,DKF_0	), // MODIFIER LETTER SMALL B
/*SUPERSCRIPT        */	DEADTRANS(	L'c'	,0x005e	,0x1d9c	,DKF_0	), // MODIFIER LETTER SMALL C
/*SUPERSCRIPT        */	DEADTRANS(	L'D'	,0x005e	,0x1d30	,DKF_0	), // MODIFIER LETTER CAPITAL D
/*SUPERSCRIPT        */	DEADTRANS(	L'd'	,0x005e	,0x1d48	,DKF_0	), // MODIFIER LETTER SMALL D
/*SUPERSCRIPT        */	DEADTRANS(	L'E'	,0x005e	,0x1d31	,DKF_0	), // MODIFIER LETTER CAPITAL E
/*SUPERSCRIPT        */	DEADTRANS(	L'e'	,0x005e	,0x1d49	,DKF_0	), // MODIFIER LETTER SMALL E
/*SUPERSCRIPT        */	DEADTRANS(	L'f'	,0x005e	,0x1da0	,DKF_0	), // MODIFIER LETTER SMALL F
/*SUPERSCRIPT        */	DEADTRANS(	L'G'	,0x005e	,0x1d33	,DKF_0	), // MODIFIER LETTER CAPITAL G
/*SUPERSCRIPT        */	DEADTRANS(	L'g'	,0x005e	,0x1d4d	,DKF_0	), // MODIFIER LETTER SMALL G
/*SUPERSCRIPT        */	DEADTRANS(	L'H'	,0x005e	,0x1d34	,DKF_0	), // MODIFIER LETTER CAPITAL H
/*SUPERSCRIPT        */	DEADTRANS(	L'h'	,0x005e	,0x02b0	,DKF_0	), // MODIFIER LETTER SMALL H
/*SUPERSCRIPT        */	DEADTRANS(	L'I'	,0x005e	,0x1d35	,DKF_0	), // MODIFIER LETTER CAPITAL I
/*SUPERSCRIPT        */	DEADTRANS(	L'i'	,0x005e	,0x2071	,DKF_0	), // SUPERSCRIPT LATIN SMALL LETTER I
/*SUPERSCRIPT        */	DEADTRANS(	L'J'	,0x005e	,0x1d36	,DKF_0	), // MODIFIER LETTER CAPITAL J
/*SUPERSCRIPT        */	DEADTRANS(	L'j'	,0x005e	,0x02b2	,DKF_0	), // MODIFIER LETTER SMALL J
/*SUPERSCRIPT        */	DEADTRANS(	L'K'	,0x005e	,0x1d37	,DKF_0	), // MODIFIER LETTER CAPITAL K
/*SUPERSCRIPT        */	DEADTRANS(	L'k'	,0x005e	,0x1d4f	,DKF_0	), // MODIFIER LETTER SMALL K
/*SUPERSCRIPT        */	DEADTRANS(	L'L'	,0x005e	,0x1d38	,DKF_0	), // MODIFIER LETTER CAPITAL L
/*SUPERSCRIPT        */	DEADTRANS(	L'l'	,0x005e	,0x02e1	,DKF_0	), // MODIFIER LETTER SMALL L
/*SUPERSCRIPT        */	DEADTRANS(	L'M'	,0x005e	,0x1d39	,DKF_0	), // MODIFIER LETTER CAPITAL M
/*SUPERSCRIPT        */	DEADTRANS(	L'm'	,0x005e	,0x1d50	,DKF_0	), // MODIFIER LETTER SMALL M
/*SUPERSCRIPT        */	DEADTRANS(	L'N'	,0x005e	,0x1d3a	,DKF_0	), // MODIFIER LETTER CAPITAL N
/*SUPERSCRIPT        */	DEADTRANS(	L'n'	,0x005e	,0x207f	,DKF_0	), // SUPERSCRIPT LATIN SMALL LETTER N
/*SUPERSCRIPT        */	DEADTRANS(	L'O'	,0x005e	,0x1d3c	,DKF_0	), // MODIFIER LETTER CAPITAL O
/*SUPERSCRIPT        */	DEADTRANS(	L'o'	,0x005e	,0x1d52	,DKF_0	), // MODIFIER LETTER SMALL O
/*SUPERSCRIPT        */	DEADTRANS(	L'P'	,0x005e	,0x1d3e	,DKF_0	), // MODIFIER LETTER CAPITAL P
/*SUPERSCRIPT        */	DEADTRANS(	L'p'	,0x005e	,0x1d56	,DKF_0	), // MODIFIER LETTER SMALL P
/*SUPERSCRIPT        */	DEADTRANS(	L'R'	,0x005e	,0x1d3f	,DKF_0	), // MODIFIER LETTER CAPITAL R
/*SUPERSCRIPT        */	DEADTRANS(	L'r'	,0x005e	,0x02b3	,DKF_0	), // MODIFIER LETTER SMALL R
/*SUPERSCRIPT        */	DEADTRANS(	L's'	,0x005e	,0x02e2	,DKF_0	), // MODIFIER LETTER SMALL S
/*SUPERSCRIPT        */	DEADTRANS(	L'T'	,0x005e	,0x1d40	,DKF_0	), // MODIFIER LETTER CAPITAL T
/*SUPERSCRIPT        */	DEADTRANS(	L't'	,0x005e	,0x1d57	,DKF_0	), // MODIFIER LETTER SMALL T
/*SUPERSCRIPT        */	DEADTRANS(	L'U'	,0x005e	,0x1d41	,DKF_0	), // MODIFIER LETTER CAPITAL U
/*SUPERSCRIPT        */	DEADTRANS(	L'u'	,0x005e	,0x1d58	,DKF_0	), // MODIFIER LETTER SMALL U
/*SUPERSCRIPT        */	DEADTRANS(	L'V'	,0x005e	,0x2c7d	,DKF_0	), // MODIFIER LETTER CAPITAL V
/*SUPERSCRIPT        */	DEADTRANS(	L'v'	,0x005e	,0x1d5b	,DKF_0	), // MODIFIER LETTER SMALL V
/*SUPERSCRIPT        */	DEADTRANS(	L'W'	,0x005e	,0x1d42	,DKF_0	), // MODIFIER LETTER CAPITAL W
/*SUPERSCRIPT        */	DEADTRANS(	L'w'	,0x005e	,0x02b7	,DKF_0	), // MODIFIER LETTER SMALL W
/*SUPERSCRIPT        */	DEADTRANS(	L'x'	,0x005e	,0x02e3	,DKF_0	), // MODIFIER LETTER SMALL X
/*SUPERSCRIPT        */	DEADTRANS(	L'y'	,0x005e	,0x02b8	,DKF_0	), // MODIFIER LETTER SMALL Y
/*SUPERSCRIPT        */	DEADTRANS(	L'z'	,0x005e	,0x1dbb	,DKF_0	), // MODIFIER LETTER SMALL Z
/*SUPERSCRIPT        */	DEADTRANS(	L'0'	,0x005e	,0x2070	,DKF_0	), // SUPERSCRIPT ZERO
/*SUPERSCRIPT        */	DEADTRANS(	L'1'	,0x005e	,0x00b9	,DKF_0	), // SUPERSCRIPT ONE
/*SUPERSCRIPT        */	DEADTRANS(	L'2'	,0x005e	,0x00b2	,DKF_0	), // SUPERSCRIPT TWO
/*SUPERSCRIPT        */	DEADTRANS(	L'3'	,0x005e	,0x00b3	,DKF_0	), // SUPERSCRIPT THREE
/*SUPERSCRIPT        */	DEADTRANS(	L'4'	,0x005e	,0x2074	,DKF_0	), // SUPERSCRIPT FOUR
/*SUPERSCRIPT        */	DEADTRANS(	L'5'	,0x005e	,0x2075	,DKF_0	), // SUPERSCRIPT FIVE
/*SUPERSCRIPT        */	DEADTRANS(	L'6'	,0x005e	,0x2076	,DKF_0	), // SUPERSCRIPT SIX
/*SUPERSCRIPT        */	DEADTRANS(	L'7'	,0x005e	,0x2077	,DKF_0	), // SUPERSCRIPT SEVEN
/*SUPERSCRIPT        */	DEADTRANS(	L'8'	,0x005e	,0x2078	,DKF_0	), // SUPERSCRIPT EIGHT
/*SUPERSCRIPT        */	DEADTRANS(	L'9'	,0x005e	,0x2079	,DKF_0	), // SUPERSCRIPT NINE
/*SUPERSCRIPT        */	DEADTRANS(	0x0021	,0x005e	,0xa71d	,DKF_0	), // MODIFIER LETTER RAISED EXCLAMATION MARK
/*SUPERSCRIPT        */	DEADTRANS(	0x0023	,0x005e	,0x02b4	,CHAIN	), // MODIFIER LETTER SMALL TURNED R
/*SUPERSCRIPT        */	DEADTRANS(	L'a'	,0x02b4	,0x1d44	,DKF_0	), // MODIFIER LETTER SMALL TURNED A
/*SUPERSCRIPT        */	DEADTRANS(	L'c'	,0x02b4	,0x1d53	,DKF_0	), // MODIFIER LETTER SMALL OPEN O
/*SUPERSCRIPT        */	DEADTRANS(	L'f'	,0x02b4	,0x1da1	,DKF_0	), // MODIFIER LETTER SMALL DOTLESS J WITH STROKE
/*SUPERSCRIPT        */	DEADTRANS(	L'h'	,0x02b4	,0x1da3	,DKF_0	), // MODIFIER LETTER SMALL TURNED H
/*SUPERSCRIPT        */	DEADTRANS(	L'i'	,0x02b4	,0x1d4e	,DKF_0	), // MODIFIER LETTER SMALL TURNED I
/*SUPERSCRIPT        */	DEADTRANS(	L'l'	,0x02b4	,0x1dad	,DKF_0	), // MODIFIER LETTER SMALL TURNED M WITH LONG LEG
/*SUPERSCRIPT        */	DEADTRANS(	L'm'	,0x02b4	,0x1d5a	,DKF_0	), // MODIFIER LETTER SMALL TURNED M
/*SUPERSCRIPT        */	DEADTRANS(	L'r'	,0x02b4	,0x02b4	,DKF_0	), // MODIFIER LETTER SMALL TURNED R
/*SUPERSCRIPT        */	DEADTRANS(	L's'	,0x02b4	,0xab5d	,DKF_0	), // MODIFIER LETTER SMALL L WITH INVERTED LAZY S
/*SUPERSCRIPT        */	DEADTRANS(	L'v'	,0x02b4	,0x1dba	,DKF_0	), // MODIFIER LETTER SMALL TURNED V
/*SUPERSCRIPT        */	DEADTRANS(	0x0021	,0x02b4	,0xa71e	,DKF_0	), // MODIFIER LETTER RAISED INVERTED EXCLAMATION MARK
/*SUPERSCRIPT        */	DEADTRANS(	0x0023	,0x02b4	,0x1d59	,CHAIN	), // MODIFIER LETTER SMALL SIDEWAYS U
/*SUPERSCRIPT        */	DEADTRANS(	L'F'	,0x1d59	,0xa720	,DKF_0	), // MODIFIER LETTER STRESS AND HIGH TONE
/*SUPERSCRIPT        */	DEADTRANS(	L'L'	,0x1d59	,0xa71a	,DKF_0	), // MODIFIER LETTER LOWER RIGHT CORNER ANGLE
/*SUPERSCRIPT        */	DEADTRANS(	L'u'	,0x1d59	,0x1d59	,DKF_0	), // MODIFIER LETTER SMALL SIDEWAYS U
/*SUPERSCRIPT        */	DEADTRANS(	0x005b	,0x02b4	,0x02b5	,DKF_0	), // MODIFIER LETTER SMALL TURNED R WITH HOOK
/*SUPERSCRIPT        */	DEADTRANS(	0x0153	,0x02b4	,0x1d46	,DKF_0	), // MODIFIER LETTER SMALL TURNED AE
/*SUPERSCRIPT        */	DEADTRANS(	0x00a9	,0x02b4	,0x1d46	,DKF_0	), // MODIFIER LETTER SMALL TURNED AE
/*SUPERSCRIPT        */	DEADTRANS(	0x00b5	,0x02b4	,0x1d4c	,CHAIN	), // MODIFIER LETTER SMALL TURNED OPEN E
/*SUPERSCRIPT        */	DEADTRANS(	0x00f2	,0x02b4	,0x1d46	,DKF_0	), // MODIFIER LETTER SMALL TURNED AE
/*SUPERSCRIPT        */	DEADTRANS(	0x00f9	,0x02b4	,0x1d4c	,CHAIN	), // MODIFIER LETTER SMALL TURNED OPEN E
/*SUPERSCRIPT        */	DEADTRANS(	L'a'	,0x1d4c	,0x1d9b	,DKF_0	), // MODIFIER LETTER SMALL TURNED ALPHA
/*SUPERSCRIPT        */	DEADTRANS(	L'e'	,0x1d4c	,0x1d4c	,DKF_0	), // MODIFIER LETTER SMALL TURNED OPEN E
/*SUPERSCRIPT        */	DEADTRANS(	0x0024	,0x005e	,0x017f	,DKF_0	), // LATIN SMALL LETTER LONG S
/*SUPERSCRIPT        */	DEADTRANS(	0x0025	,0x005e	,0xa71e	,DKF_0	), // MODIFIER LETTER RAISED INVERTED EXCLAMATION MARK
/*SUPERSCRIPT        */	DEADTRANS(	0x0026	,0x005e	,0x1da2	,DKF_0	), // MODIFIER LETTER SMALL SCRIPT G
/*SUPERSCRIPT        */	DEADTRANS(	0x0027	,0x005e	,0x02cf	,CHAIN	), // MODIFIER LETTER LOW ACUTE ACCENT
/*SUPERSCRIPT        */	DEADTRANS(	0x0028	,0x005e	,0x207d	,DKF_0	), // SUPERSCRIPT LEFT PARENTHESIS
/*SUPERSCRIPT        */	DEADTRANS(	0x0029	,0x005e	,0x207e	,DKF_0	), // SUPERSCRIPT RIGHT PARENTHESIS
/*SUPERSCRIPT        */	DEADTRANS(	0x002a	,0x005e	,0x1d5c	,DKF_0	), // MODIFIER LETTER SMALL AIN
/*SUPERSCRIPT        */	DEADTRANS(	0x002b	,0x005e	,0x207a	,DKF_0	), // SUPERSCRIPT PLUS SIGN
/*SUPERSCRIPT        */	DEADTRANS(	0x002c	,0x005e	,0x0219	,CHAIN	), // LATIN SMALL LETTER S WITH COMMA BELOW
/*SUPERSCRIPT        */	DEADTRANS(	0x002d	,0x005e	,0x0183	,CHAIN	), // LATIN SMALL LETTER B WITH TOPBAR
/*SUPERSCRIPT        */	DEADTRANS(	0x002e	,0x005e	,0x02d9	,CHAIN	), // DOT ABOVE
/*SUPERSCRIPT        */	DEADTRANS(	0x002f	,0x005e	,0x2044	,DKF_0	), // FRACTION SLASH
/*SUPERSCRIPT        */	DEADTRANS(	0x003a	,0x005e	,0x02f8	,DKF_0	), // MODIFIER LETTER RAISED COLON
/*SUPERSCRIPT        */	DEADTRANS(	0x003d	,0x005e	,0x207c	,DKF_0	), // SUPERSCRIPT EQUALS SIGN
/*SUPERSCRIPT        */	DEADTRANS(	0x005b	,0x005e	,0x02b1	,CHAIN	), // MODIFIER LETTER SMALL H WITH HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'h'	,0x02b1	,0x02b1	,DKF_0	), // MODIFIER LETTER SMALL H WITH HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'v'	,0x02b1	,0x1db9	,DKF_0	), // MODIFIER LETTER SMALL V WITH HOOK
/*SUPERSCRIPT        */	DEADTRANS(	0x005c	,0x005e	,0x1d32	,CHAIN	), // MODIFIER LETTER CAPITAL REVERSED E
/*SUPERSCRIPT        */	DEADTRANS(	L'E'	,0x1d32	,0x1d32	,DKF_0	), // MODIFIER LETTER CAPITAL REVERSED E
/*SUPERSCRIPT        */	DEADTRANS(	L'N'	,0x1d32	,0x1d3b	,DKF_0	), // MODIFIER LETTER CAPITAL REVERSED N
/*SUPERSCRIPT        */	DEADTRANS(	0x0027	,0x1d32	,0x02c1	,DKF_0	), // MODIFIER LETTER REVERSED GLOTTAL STOP
/*SUPERSCRIPT        */	DEADTRANS(	0x00b5	,0x1d32	,0x1d9f	,DKF_0	), // MODIFIER LETTER SMALL REVERSED OPEN E
/*SUPERSCRIPT        */	DEADTRANS(	0x00f2	,0x1d32	,0x02e4	,DKF_0	), // MODIFIER LETTER SMALL REVERSED GLOTTAL STOP
/*SUPERSCRIPT        */	DEADTRANS(	0x00f9	,0x1d32	,0x02c1	,DKF_0	), // MODIFIER LETTER REVERSED GLOTTAL STOP
/*SUPERSCRIPT        */	DEADTRANS(	0x2019	,0x1d32	,0x02c1	,DKF_0	), // MODIFIER LETTER REVERSED GLOTTAL STOP
/*SUPERSCRIPT        */	DEADTRANS(	0x005d	,0x005e	,0x1db5	,CHAIN	), // MODIFIER LETTER SMALL T WITH PALATAL HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'l'	,0x1db5	,0x1daa	,DKF_0	), // MODIFIER LETTER SMALL L WITH PALATAL HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L't'	,0x1db5	,0x1db5	,DKF_0	), // MODIFIER LETTER SMALL T WITH PALATAL HOOK
/*SUPERSCRIPT        */	DEADTRANS(	0x005e	,0x005e	,0x2193	,CHAIN	), // DOWNWARDS ARROW
/*SUPERSCRIPT        */	DEADTRANS(	0x005f	,0x005e	,0x203e	,DKF_0	), // OVERLINE
/*SUPERSCRIPT        */	DEADTRANS(	0x0060	,0x005e	,0x02ce	,CHAIN	), // MODIFIER LETTER LOW GRAVE ACCENT
/*SUPERSCRIPT        */	DEADTRANS(	0x007b	,0x005e	,0x1dbc	,CHAIN	), // MODIFIER LETTER SMALL Z WITH RETROFLEX HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'l'	,0x1dbc	,0x1da9	,DKF_0	), // MODIFIER LETTER SMALL L WITH RETROFLEX HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'n'	,0x1dbc	,0x1daf	,DKF_0	), // MODIFIER LETTER SMALL N WITH RETROFLEX HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L's'	,0x1dbc	,0x1db3	,DKF_0	), // MODIFIER LETTER SMALL S WITH HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'z'	,0x1dbc	,0x1dbc	,DKF_0	), // MODIFIER LETTER SMALL Z WITH RETROFLEX HOOK
/*SUPERSCRIPT        */	DEADTRANS(	0x007d	,0x005e	,0xab5f	,CHAIN	), // MODIFIER LETTER SMALL U WITH LEFT HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'm'	,0xab5f	,0x1dac	,DKF_0	), // MODIFIER LETTER SMALL M WITH HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'n'	,0xab5f	,0x1dae	,DKF_0	), // MODIFIER LETTER SMALL N WITH LEFT HOOK
/*SUPERSCRIPT        */	DEADTRANS(	L'u'	,0xab5f	,0xab5f	,DKF_0	), // MODIFIER LETTER SMALL U WITH LEFT HOOK
/*SUPERSCRIPT        */	DEADTRANS(	0x007e	,0x005e	,0xab5e	,CHAIN	), // MODIFIER LETTER SMALL L WITH MIDDLE TILDE
/*SUPERSCRIPT        */	DEADTRANS(	L'l'	,0xab5e	,0xab5e	,DKF_0	), // MODIFIER LETTER SMALL L WITH MIDDLE TILDE
/*SUPERSCRIPT        */	DEADTRANS(	0x0153	,0x005e	,0xa7f9	,DKF_0	), // MODIFIER LETTER SMALL LIGATURE OE
/*SUPERSCRIPT        */	DEADTRANS(	0x00a9	,0x005e	,0xa7f9	,CHAIN	), // MODIFIER LETTER SMALL LIGATURE OE
/*SUPERSCRIPT        */	DEADTRANS(	L'c'	,0xa7f9	,0x1d9d	,DKF_0	), // MODIFIER LETTER SMALL C WITH CURL
/*SUPERSCRIPT        */	DEADTRANS(	L'd'	,0xa7f9	,0x1d9e	,DKF_0	), // MODIFIER LETTER SMALL ETH
/*SUPERSCRIPT        */	DEADTRANS(	0x0259	,0xa7f9	,0x1d4a	,DKF_0	), // MODIFIER LETTER SMALL SCHWA
/*SUPERSCRIPT        */	DEADTRANS(	L'h'	,0xa7f9	,0xab5c	,DKF_0	), // MODIFIER LETTER SMALL HENG
/*SUPERSCRIPT        */	DEADTRANS(	L'j'	,0xa7f9	,0x1da8	,DKF_0	), // MODIFIER LETTER SMALL J WITH CROSSED-TAIL
/*SUPERSCRIPT        */	DEADTRANS(	0x014b	,0xa7f9	,0x1d51	,DKF_0	), // MODIFIER LETTER SMALL ENG
/*SUPERSCRIPT        */	DEADTRANS(	L'O'	,0xa7f9	,0x1d3d	,DKF_0	), // MODIFIER LETTER CAPITAL OU
/*SUPERSCRIPT        */	DEADTRANS(	L'o'	,0xa7f9	,0x1d55	,CHAIN	), // MODIFIER LETTER SMALL BOTTOM HALF O
/*SUPERSCRIPT        */	DEADTRANS(	0x0028	,0x1d55	,0x1d54	,DKF_0	), // MODIFIER LETTER SMALL TOP HALF O
/*SUPERSCRIPT        */	DEADTRANS(	0x0029	,0x1d55	,0x1d55	,DKF_0	), // MODIFIER LETTER SMALL BOTTOM HALF O
/*SUPERSCRIPT        */	DEADTRANS(	0x0283	,0xa7f9	,0x1db4	,DKF_0	), // MODIFIER LETTER SMALL ESH
/*SUPERSCRIPT        */	DEADTRANS(	0x0292	,0xa7f9	,0x1dbe	,DKF_0	), // MODIFIER LETTER SMALL EZH
/*SUPERSCRIPT        */	DEADTRANS(	0x0026	,0xa7f9	,0x1dbd	,DKF_0	), // MODIFIER LETTER SMALL Z WITH CURL
/*SUPERSCRIPT        */	DEADTRANS(	0x002d	,0xa7f9	,0x1d2f	,DKF_0	), // MODIFIER LETTER CAPITAL BARRED B
/*SUPERSCRIPT        */	DEADTRANS(	0x0153	,0xa7f9	,0x1d9d	,CHAIN	), // MODIFIER LETTER SMALL C WITH CURL
/*SUPERSCRIPT        */	DEADTRANS(	L'c'	,0x1d9d	,0x1d9d	,DKF_0	), // MODIFIER LETTER SMALL C WITH CURL
/*SUPERSCRIPT        */	DEADTRANS(	L'j'	,0x1d9d	,0x1da8	,DKF_0	), // MODIFIER LETTER SMALL J WITH CROSSED-TAIL
/*SUPERSCRIPT        */	DEADTRANS(	L'z'	,0x1d9d	,0x1dbd	,DKF_0	), // MODIFIER LETTER SMALL Z WITH CURL
/*SUPERSCRIPT        */	DEADTRANS(	0x0153	,0x1d9d	,0x1da8	,DKF_0	), // MODIFIER LETTER SMALL J WITH CROSSED-TAIL
/*SUPERSCRIPT        */	DEADTRANS(	0x00a7	,0x005e	,0x2040	,DKF_0	), // CHARACTER TIE
/*SUPERSCRIPT        */	DEADTRANS(	0x00b0	,0x005e	,0x1e01	,CHAIN	), // LATIN SMALL LETTER A WITH RING BELOW
/*SUPERSCRIPT        */	DEADTRANS(	0x00b5	,0x005e	,0x02e0	,CHAIN	), // MODIFIER LETTER SMALL GAMMA
/*SUPERSCRIPT        */	DEADTRANS(	0x00c6	,0x005e	,0x1d2d	,DKF_0	), // MODIFIER LETTER CAPITAL AE
/*SUPERSCRIPT        */	DEADTRANS(	0x00e8	,0x005e	,0x02c0	,DKF_0	), // MODIFIER LETTER GLOTTAL STOP
/*SUPERSCRIPT        */	DEADTRANS(	0x00ea	,0x005e	,0x02df	,CHAIN	), // MODIFIER LETTER CROSS ACCENT
/*SUPERSCRIPT        */	DEADTRANS(	L'x'	,0x02df	,0x02df	,DKF_0	), // MODIFIER LETTER CROSS ACCENT
/*SUPERSCRIPT        */	DEADTRANS(	0x0028	,0x02df	,0x02bf	,DKF_0	), // MODIFIER LETTER LEFT HALF RING
/*SUPERSCRIPT        */	DEADTRANS(	0x0029	,0x02df	,0x02be	,DKF_0	), // MODIFIER LETTER RIGHT HALF RING
/*SUPERSCRIPT        */	DEADTRANS(	0x002b	,0x02df	,0x02d6	,DKF_0	), // MODIFIER LETTER PLUS SIGN
/*SUPERSCRIPT        */	DEADTRANS(	0x002d	,0x02df	,0x02d7	,DKF_0	), // MODIFIER LETTER MINUS SIGN
/*SUPERSCRIPT        */	DEADTRANS(	0x003d	,0x02df	,0x02ed	,DKF_0	), // MODIFIER LETTER UNASPIRATED
/*SUPERSCRIPT        */	DEADTRANS(	0x005b	,0x02df	,0x02de	,DKF_0	), // MODIFIER LETTER RHOTIC HOOK
/*SUPERSCRIPT        */	DEADTRANS(	0x00f9	,0x005e	,0x02c8	,DKF_0	), // MODIFIER LETTER VERTICAL LINE
/*SUPERSCRIPT        */	DEADTRANS(	0x2019	,0x005e	,0x02c8	,DKF_0	), // MODIFIER LETTER VERTICAL LINE
/*SUPERSCRIPT        */	DEADTRANS(	0x00eb	,0x005e	,0x02b6	,CHAIN	), // MODIFIER LETTER SMALL CAPITAL INVERTED R
/*SUPERSCRIPT        */	DEADTRANS(	L'H'	,0x02b6	,0x1d78	,DKF_0	), // MODIFIER LETTER CYRILLIC EN
/*SUPERSCRIPT        */	DEADTRANS(	L'I'	,0x02b6	,0x1da6	,DKF_0	), // MODIFIER LETTER SMALL CAPITAL I
/*SUPERSCRIPT        */	DEADTRANS(	L'L'	,0x02b6	,0x1dab	,DKF_0	), // MODIFIER LETTER SMALL CAPITAL L
/*SUPERSCRIPT        */	DEADTRANS(	L'N'	,0x02b6	,0x1db0	,DKF_0	), // MODIFIER LETTER SMALL CAPITAL N
/*SUPERSCRIPT        */	DEADTRANS(	L'U'	,0x02b6	,0x1db8	,DKF_0	), // MODIFIER LETTER SMALL CAPITAL U
/*SUPERSCRIPT        */	DEADTRANS(	0x0025	,0x02b6	,0x02b6	,DKF_0	), // MODIFIER LETTER SMALL CAPITAL INVERTED R
/*SUPERSCRIPT        */	DEADTRANS(	0x0028	,0x02d5	,0x02d3	,DKF_0	), // MODIFIER LETTER CENTRED LEFT HALF RING
/*SUPERSCRIPT        */	DEADTRANS(	0x0029	,0x02d5	,0x02d2	,DKF_0	), // MODIFIER LETTER CENTRED RIGHT HALF RING
/*SUPERSCRIPT        */	DEADTRANS(	0x002d	,0x02b6	,0x1da7	,DKF_0	), // MODIFIER LETTER SMALL CAPITAL I WITH STROKE
/*SUPERSCRIPT        */	DEADTRANS(	0x00f5	,0x005e	,0x1e75	,CHAIN	), // LATIN SMALL LETTER U WITH TILDE BELOW
/*SUPERSCRIPT        */	DEADTRANS(	L'a'	,0x02e0	,0x1d45	,DKF_0	), // MODIFIER LETTER SMALL ALPHA
/*SUPERSCRIPT        */	DEADTRANS(	L'b'	,0x02e0	,0x1d5d	,DKF_0	), // MODIFIER LETTER SMALL BETA
/*SUPERSCRIPT        */	DEADTRANS(	L'd'	,0x02e0	,0x1d5f	,DKF_0	), // MODIFIER LETTER SMALL DELTA
/*SUPERSCRIPT        */	DEADTRANS(	L'e'	,0x02e0	,0x1d4b	,DKF_0	), // MODIFIER LETTER SMALL OPEN E
/*SUPERSCRIPT        */	DEADTRANS(	L'f'	,0x02e0	,0x1d60	,DKF_0	), // MODIFIER LETTER SMALL GREEK PHI
/*SUPERSCRIPT        */	DEADTRANS(	L'g'	,0x02e0	,0x02e0	,DKF_0	), // MODIFIER LETTER SMALL GAMMA
/*SUPERSCRIPT        */	DEADTRANS(	L'i'	,0x02e0	,0x1da5	,DKF_0	), // MODIFIER LETTER SMALL IOTA
/*SUPERSCRIPT        */	DEADTRANS(	L't'	,0x02e0	,0x1dbf	,DKF_0	), // MODIFIER LETTER SMALL THETA
/*SUPERSCRIPT        */	DEADTRANS(	L'u'	,0x02e0	,0x1db7	,DKF_0	), // MODIFIER LETTER SMALL UPSILON
/*SUPERSCRIPT        */	DEADTRANS(	L'x'	,0x02e0	,0x1d61	,DKF_0	), // MODIFIER LETTER SMALL CHI
/*SUPERSCRIPT        */	DEADTRANS(	0x2212	,0x005e	,0x207b	,DKF_0	), // SUPERSCRIPT MINUS
/*SUPERSCRIPT        */	DEADTRANS(	0x2191	,0x005e	,0x2193	,CHAIN	), // DOWNWARDS ARROW
/*SUPERSCRIPT        */	DEADTRANS(	0x022f	,0x005e	,0x1ecd	,CHAIN	), // LATIN SMALL LETTER O WITH DOT BELOW
/*SUPERSCRIPT        */	DEADTRANS(	0x014d	,0x005e	,0x1e07	,CHAIN	), // LATIN SMALL LETTER B WITH LINE BELOW
/*SUPERSCRIPT        */	DEADTRANS(	0x024d	,0x005e	,0x0183	,CHAIN	), // LATIN SMALL LETTER B WITH TOPBAR
/*TILDE              */	DEADTRANS(	0x0020	,0x00f5	,0x0303	,DKF_0	), // COMBINING TILDE
/*TILDE              */	DEADTRANS(	0x0020	,0x1d6f	,0x0334	,DKF_0	), // COMBINING TILDE OVERLAY
/*TILDE              */	DEADTRANS(	0x0020	,0x00d5	,0x034c	,DKF_0	), // COMBINING ALMOST EQUAL TO ABOVE
/*TILDE              */	DEADTRANS(	0x202f	,0x00f5	,0x02dc	,DKF_0	), // SMALL TILDE
/*TILDE              */	DEADTRANS(	0x00a0	,0x00f5	,0x007e	,DKF_0	), // TILDE
/*TILDE              */	DEADTRANS(	L'A'	,0x00f5	,0x00c3	,DKF_0	), // LATIN CAPITAL LETTER A WITH TILDE
/*TILDE              */	DEADTRANS(	L'a'	,0x00f5	,0x00e3	,DKF_0	), // LATIN SMALL LETTER A WITH TILDE
/*TILDE              */	DEADTRANS(	L'b'	,0x00f5	,0x1d6c	,DKF_0	), // LATIN SMALL LETTER B WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'd'	,0x00f5	,0x1d6d	,DKF_0	), // LATIN SMALL LETTER D WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'E'	,0x00f5	,0x1ebc	,DKF_0	), // LATIN CAPITAL LETTER E WITH TILDE
/*TILDE              */	DEADTRANS(	L'e'	,0x00f5	,0x1ebd	,DKF_0	), // LATIN SMALL LETTER E WITH TILDE
/*TILDE              */	DEADTRANS(	L'F'	,0x00f5	,0x00aa	,DKF_0	), // FEMININE ORDINAL INDICATOR
/*TILDE              */	DEADTRANS(	L'f'	,0x00f5	,0x1d6e	,DKF_0	), // LATIN SMALL LETTER F WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'I'	,0x00f5	,0x0128	,DKF_0	), // LATIN CAPITAL LETTER I WITH TILDE
/*TILDE              */	DEADTRANS(	L'i'	,0x00f5	,0x0129	,DKF_0	), // LATIN SMALL LETTER I WITH TILDE
/*TILDE              */	DEADTRANS(	L'J'	,0x00f5	,0xa7ae	,DKF_0	), // LATIN CAPITAL LETTER SMALL CAPITAL I
/*TILDE              */	DEADTRANS(	L'j'	,0x00f5	,0x026a	,DKF_0	), // LATIN LETTER SMALL CAPITAL I
/*TILDE              */	DEADTRANS(	L'L'	,0x00f5	,0x2c62	,DKF_0	), // LATIN CAPITAL LETTER L WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'l'	,0x00f5	,0x026b	,DKF_0	), // LATIN SMALL LETTER L WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'M'	,0x00f5	,0x00ba	,DKF_0	), // MASCULINE ORDINAL INDICATOR
/*TILDE              */	DEADTRANS(	L'm'	,0x00f5	,0x1d6f	,DKF_0	), // LATIN SMALL LETTER M WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'N'	,0x00f5	,0x00d1	,DKF_0	), // LATIN CAPITAL LETTER N WITH TILDE
/*TILDE              */	DEADTRANS(	L'n'	,0x00f5	,0x00f1	,DKF_0	), // LATIN SMALL LETTER N WITH TILDE
/*TILDE              */	DEADTRANS(	L'O'	,0x00f5	,0x00d5	,DKF_0	), // LATIN CAPITAL LETTER O WITH TILDE
/*TILDE              */	DEADTRANS(	L'o'	,0x00f5	,0x00f5	,DKF_0	), // LATIN SMALL LETTER O WITH TILDE
/*TILDE              */	DEADTRANS(	L'p'	,0x00f5	,0x1d71	,DKF_0	), // LATIN SMALL LETTER P WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'r'	,0x00f5	,0x1d72	,DKF_0	), // LATIN SMALL LETTER R WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L's'	,0x00f5	,0x1d74	,DKF_0	), // LATIN SMALL LETTER S WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L't'	,0x00f5	,0x1d75	,DKF_0	), // LATIN SMALL LETTER T WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	L'U'	,0x00f5	,0x0168	,DKF_0	), // LATIN CAPITAL LETTER U WITH TILDE
/*TILDE              */	DEADTRANS(	L'u'	,0x00f5	,0x0169	,DKF_0	), // LATIN SMALL LETTER U WITH TILDE
/*TILDE              */	DEADTRANS(	L'V'	,0x00f5	,0x1e7c	,DKF_0	), // LATIN CAPITAL LETTER V WITH TILDE
/*TILDE              */	DEADTRANS(	L'v'	,0x00f5	,0x1e7d	,DKF_0	), // LATIN SMALL LETTER V WITH TILDE
/*TILDE              */	DEADTRANS(	L'Y'	,0x00f5	,0x1ef8	,DKF_0	), // LATIN CAPITAL LETTER Y WITH TILDE
/*TILDE              */	DEADTRANS(	L'y'	,0x00f5	,0x1ef9	,DKF_0	), // LATIN SMALL LETTER Y WITH TILDE
/*TILDE              */	DEADTRANS(	L'z'	,0x00f5	,0x1d76	,DKF_0	), // LATIN SMALL LETTER Z WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	0x0021	,0x00f5	,0x00a1	,DKF_0	), // INVERTED EXCLAMATION MARK
/*TILDE              */	DEADTRANS(	0x0022	,0x00f5	,0x201f	,DKF_0	), // DOUBLE HIGH-REVERSED-9 QUOTATION MARK
/*TILDE              */	DEADTRANS(	0x0023	,0x00f5	,0x201f	,DKF_0	), // DOUBLE HIGH-REVERSED-9 QUOTATION MARK
/*TILDE              */	DEADTRANS(	0x0027	,0x00f5	,0x201b	,DKF_0	), // SINGLE HIGH-REVERSED-9 QUOTATION MARK
/*TILDE              */	DEADTRANS(	0x0029	,0x00f5	,0x1eb5	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND TILDE
/*TILDE              */	DEADTRANS(	0x002a	,0x00f5	,0x02dc	,DKF_0	), // SMALL TILDE
/*TILDE              */	DEADTRANS(	0x002b	,0x00f5	,0x1d6f	,CHAIN	), // LATIN SMALL LETTER M WITH MIDDLE TILDE
/*TILDE              */	DEADTRANS(	0x002c	,0x00f5	,0x1ee1	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND TILDE
/*TILDE              */	DEADTRANS(	0x002d	,0x00f5	,0x2053	,DKF_0	), // SWUNG DASH
/*TILDE              */	DEADTRANS(	0x003d	,0x00f5	,0x2243	,DKF_0	), // ASYMPTOTICALLY EQUAL TO
/*TILDE              */	DEADTRANS(	0x003f	,0x00f5	,0x00bf	,DKF_0	), // INVERTED QUESTION MARK
/*TILDE              */	DEADTRANS(	0x005b	,0x00f5	,0x1d73	,DKF_0	), // LATIN SMALL LETTER R WITH FISHHOOK AND MIDDLE TILDE
/*TILDE              */	DEADTRANS(	0x005f	,0x00f5	,0x022d	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND MACRON
/*TILDE              */	DEADTRANS(	0x007e	,0x00f5	,0x00d5	,CHAIN	), // LATIN CAPITAL LETTER O WITH TILDE
/*TILDE              */	DEADTRANS(	0x00a3	,0x00f5	,0x1e75	,CHAIN	), // LATIN SMALL LETTER U WITH TILDE BELOW
/*TILDE              */	DEADTRANS(	0x00a9	,0x00f5	,0x00f1	,CHAIN	), // LATIN SMALL LETTER N WITH TILDE
/*TILDE              */	DEADTRANS(	0x0022	,0x00f1	,0x1e4f	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND DIAERESIS
/*TILDE              */	DEADTRANS(	0x0027	,0x00f1	,0x1e4d	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND ACUTE
/*TILDE              */	DEADTRANS(	0x00e1	,0x00f5	,0x1e4d	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND ACUTE
/*TILDE              */	DEADTRANS(	0x00ea	,0x00f5	,0x1ed7	,CHAIN	), // LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE
/*TILDE              */	DEADTRANS(	0x00eb	,0x00f5	,0x1e4f	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND DIAERESIS
/*TILDE              */	DEADTRANS(	0x00f5	,0x00f5	,0x00d5	,CHAIN	), // LATIN CAPITAL LETTER O WITH TILDE
/*TILDE              */	DEADTRANS(	0x2019	,0x00f5	,0x201b	,DKF_0	), // SINGLE HIGH-REVERSED-9 QUOTATION MARK
/*TILDE              */	DEADTRANS(	0x2610	,0x00f5	,0x274d	,DKF_0	), // SHADOWED WHITE CIRCLE
/*TILDE              */	DEADTRANS(	0x0229	,0x00f5	,0x1ee1	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND TILDE
/*TILDE              */	DEADTRANS(	0x014f	,0x00f5	,0x1eb5	,CHAIN	), // LATIN SMALL LETTER A WITH BREVE AND TILDE
/*TILDE              */	DEADTRANS(	0x014d	,0x00f5	,0x022d	,CHAIN	), // LATIN SMALL LETTER O WITH TILDE AND MACRON
/*TILDE              */	DEADTRANS(	0x01a1	,0x00f5	,0x1ee1	,CHAIN	), // LATIN SMALL LETTER O WITH HORN AND TILDE
/*TILDE&ACUTE_ACCENT */	DEADTRANS(	L'O'	,0x1e4d	,0x1e4c	,DKF_0	), // LATIN CAPITAL LETTER O WITH TILDE AND ACUTE
/*TILDE&ACUTE_ACCENT */	DEADTRANS(	L'o'	,0x1e4d	,0x1e4d	,DKF_0	), // LATIN SMALL LETTER O WITH TILDE AND ACUTE
/*TILDE&ACUTE_ACCENT */	DEADTRANS(	L'U'	,0x1e4d	,0x1e78	,DKF_0	), // LATIN CAPITAL LETTER U WITH TILDE AND ACUTE
/*TILDE&ACUTE_ACCENT */	DEADTRANS(	L'u'	,0x1e4d	,0x1e79	,DKF_0	), // LATIN SMALL LETTER U WITH TILDE AND ACUTE
/*TILDE&DIAERESIS    */	DEADTRANS(	L'O'	,0x1e4f	,0x1e4e	,DKF_0	), // LATIN CAPITAL LETTER O WITH TILDE AND DIAERESIS
/*TILDE&DIAERESIS    */	DEADTRANS(	L'o'	,0x1e4f	,0x1e4f	,DKF_0	), // LATIN SMALL LETTER O WITH TILDE AND DIAERESIS
/*TILDE&MACRON       */	DEADTRANS(	L'O'	,0x022d	,0x022c	,DKF_0	), // LATIN CAPITAL LETTER O WITH TILDE AND MACRON
/*TILDE&MACRON       */	DEADTRANS(	L'o'	,0x022d	,0x022d	,DKF_0	), // LATIN SMALL LETTER O WITH TILDE AND MACRON
/*TILDE_BELOW        */	DEADTRANS(	0x0020	,0x1e75	,0x0330	,DKF_0	), // COMBINING TILDE BELOW
/*TILDE_BELOW        */	DEADTRANS(	0x00a3	,0x1e75	,0x1dfd	,DKF_0	), // COMBINING ALMOST EQUAL TO BELOW
/*TILDE_BELOW        */	DEADTRANS(	0x00a0	,0x1e75	,0x02f7	,DKF_0	), // MODIFIER LETTER LOW TILDE
/*TILDE_BELOW        */	DEADTRANS(	0x202f	,0x1e75	,0x02f7	,DKF_0	), // MODIFIER LETTER LOW TILDE
/*TILDE_BELOW        */	DEADTRANS(	L'E'	,0x1e75	,0x1e1a	,DKF_0	), // LATIN CAPITAL LETTER E WITH TILDE BELOW
/*TILDE_BELOW        */	DEADTRANS(	L'e'	,0x1e75	,0x1e1b	,DKF_0	), // LATIN SMALL LETTER E WITH TILDE BELOW
/*TILDE_BELOW        */	DEADTRANS(	L'I'	,0x1e75	,0x1e2c	,DKF_0	), // LATIN CAPITAL LETTER I WITH TILDE BELOW
/*TILDE_BELOW        */	DEADTRANS(	L'i'	,0x1e75	,0x1e2d	,DKF_0	), // LATIN SMALL LETTER I WITH TILDE BELOW
/*TILDE_BELOW        */	DEADTRANS(	L'l'	,0x1e75	,0xab38	,DKF_0	), // LATIN SMALL LETTER L WITH DOUBLE MIDDLE TILDE
/*TILDE_BELOW        */	DEADTRANS(	L'U'	,0x1e75	,0x1e74	,DKF_0	), // LATIN CAPITAL LETTER U WITH TILDE BELOW
/*TILDE_BELOW        */	DEADTRANS(	L'u'	,0x1e75	,0x1e75	,DKF_0	), // LATIN SMALL LETTER U WITH TILDE BELOW
/*TILDE_BELOW        */	DEADTRANS(	0x0022	,0x1e75	,0x2e42	,DKF_0	), // DOUBLE LOW-REVERSED-9 QUOTATION MARK
/*TILDE_BELOW        */	DEADTRANS(	0x0027	,0x1e75	,0x02bd	,DKF_0	), // MODIFIER LETTER REVERSED COMMA
/*TILDE_BELOW        */	DEADTRANS(	0x003d	,0x1e75	,0x2248	,DKF_0	), // ALMOST EQUAL TO
/*TILDE_BELOW        */	DEADTRANS(	0x00f9	,0x1e75	,0x02bd	,DKF_0	), // MODIFIER LETTER REVERSED COMMA
/*TILDE_BELOW        */	DEADTRANS(	0x2019	,0x1e75	,0x02bd	,DKF_0	), // MODIFIER LETTER REVERSED COMMA
/*TILDE_MIDDLE       */	DEADTRANS(	L'l'	,0x1d6f	,0x026b	,DKF_0	), // LATIN SMALL LETTER L WITH MIDDLE TILDE
/*TILDE_MIDDLE       */	DEADTRANS(	L'm'	,0x1d6f	,0x1d6f	,DKF_0	), // LATIN SMALL LETTER M WITH MIDDLE TILDE
/*TILDE_MIDDLE       */	DEADTRANS(	L'n'	,0x1d6f	,0x1d70	,DKF_0	), // LATIN SMALL LETTER N WITH MIDDLE TILDE
/*TILDE_MIDDLE       */	DEADTRANS(	L'O'	,0x1d6f	,0x019f	,DKF_0	), // LATIN CAPITAL LETTER O WITH MIDDLE TILDE
/*TILDE_MIDDLE       */	DEADTRANS(	0x007e	,0x1d6f	,0xab38	,CHAIN	), // LATIN SMALL LETTER L WITH DOUBLE MIDDLE TILDE
/*TILDE_MIDDLE       */	DEADTRANS(	0x00f5	,0x1d6f	,0xab38	,CHAIN	), // LATIN SMALL LETTER L WITH DOUBLE MIDDLE TILDE
/*TURNED             */	DEADTRANS(	L'A'	,0x1d14	,0x2c6f	,DKF_0	), // LATIN CAPITAL LETTER TURNED A
/*TURNED             */	DEADTRANS(	L'a'	,0x1d14	,0x0250	,DKF_0	), // LATIN SMALL LETTER TURNED A
/*TURNED             */	DEADTRANS(	L'C'	,0x1d14	,0x0186	,DKF_0	), // LATIN CAPITAL LETTER OPEN O
/*TURNED             */	DEADTRANS(	L'c'	,0x1d14	,0x0254	,DKF_0	), // LATIN SMALL LETTER OPEN O
/*TURNED             */	DEADTRANS(	L'E'	,0x1d14	,0x018e	,DKF_0	), // LATIN CAPITAL LETTER REVERSED E
/*TURNED             */	DEADTRANS(	L'e'	,0x1d14	,0x01dd	,DKF_0	), // LATIN SMALL LETTER TURNED E
/*TURNED             */	DEADTRANS(	L'f'	,0x1d14	,0x025f	,DKF_0	), // LATIN SMALL LETTER DOTLESS J WITH STROKE
/*TURNED             */	DEADTRANS(	L'g'	,0x1d14	,0x1d77	,DKF_0	), // LATIN SMALL LETTER TURNED G
/*TURNED             */	DEADTRANS(	L'H'	,0x1d14	,0xa78d	,DKF_0	), // LATIN CAPITAL LETTER TURNED H
/*TURNED             */	DEADTRANS(	L'h'	,0x1d14	,0x0265	,DKF_0	), // LATIN SMALL LETTER TURNED H
/*TURNED             */	DEADTRANS(	L'i'	,0x1d14	,0x1d09	,DKF_0	), // LATIN SMALL LETTER TURNED I
/*TURNED             */	DEADTRANS(	L'K'	,0x1d14	,0xa7b0	,DKF_0	), // LATIN CAPITAL LETTER TURNED K
/*TURNED             */	DEADTRANS(	L'k'	,0x1d14	,0x029e	,DKF_0	), // LATIN SMALL LETTER TURNED K
/*TURNED             */	DEADTRANS(	L'L'	,0x1d14	,0xa780	,DKF_0	), // LATIN CAPITAL LETTER TURNED L
/*TURNED             */	DEADTRANS(	L'l'	,0x1d14	,0xa781	,DKF_0	), // LATIN SMALL LETTER TURNED L
/*TURNED             */	DEADTRANS(	L'M'	,0x1d14	,0x019c	,DKF_0	), // LATIN CAPITAL LETTER TURNED M
/*TURNED             */	DEADTRANS(	L'm'	,0x1d14	,0x026f	,DKF_0	), // LATIN SMALL LETTER TURNED M
/*TURNED             */	DEADTRANS(	L'o'	,0x1d14	,0xab43	,DKF_0	), // LATIN SMALL LETTER TURNED O OPEN-O
/*TURNED             */	DEADTRANS(	L'r'	,0x1d14	,0x0279	,DKF_0	), // LATIN SMALL LETTER TURNED R
/*TURNED             */	DEADTRANS(	L'T'	,0x1d14	,0xa7b1	,DKF_0	), // LATIN CAPITAL LETTER TURNED T
/*TURNED             */	DEADTRANS(	L't'	,0x1d14	,0x0287	,DKF_0	), // LATIN SMALL LETTER TURNED T
/*TURNED             */	DEADTRANS(	L'u'	,0x1d14	,0xab51	,DKF_0	), // LATIN SMALL LETTER TURNED UI
/*TURNED             */	DEADTRANS(	L'V'	,0x1d14	,0x0245	,DKF_0	), // LATIN CAPITAL LETTER TURNED V
/*TURNED             */	DEADTRANS(	L'v'	,0x1d14	,0x028c	,DKF_0	), // LATIN SMALL LETTER TURNED V
/*TURNED             */	DEADTRANS(	L'w'	,0x1d14	,0x028d	,DKF_0	), // LATIN SMALL LETTER TURNED W
/*TURNED             */	DEADTRANS(	L'y'	,0x1d14	,0x028e	,DKF_0	), // LATIN SMALL LETTER TURNED Y
/*TURNED             */	DEADTRANS(	L'2'	,0x1d14	,0x218a	,DKF_0	), // TURNED DIGIT TWO
/*TURNED             */	DEADTRANS(	L'3'	,0x1d14	,0x218b	,DKF_0	), // TURNED DIGIT THREE
/*TURNED             */	DEADTRANS(	L'8'	,0x1d14	,0x221e	,DKF_0	), // INFINITY
/*TURNED             */	DEADTRANS(	0x0021	,0x1d14	,0x00a1	,DKF_0	), // INVERTED EXCLAMATION MARK
/*TURNED             */	DEADTRANS(	0x0023	,0x1d14	,0x1d1f	,CHAIN	), // LATIN SMALL LETTER SIDEWAYS TURNED M
/*TURNED             */	DEADTRANS(	L'c'	,0x1d1f	,0x1d12	,DKF_0	), // LATIN SMALL LETTER SIDEWAYS OPEN O
/*TURNED             */	DEADTRANS(	L'I'	,0x1d1f	,0xa7f7	,DKF_0	), // LATIN EPIGRAPHIC LETTER SIDEWAYS I
/*TURNED             */	DEADTRANS(	L'm'	,0x1d1f	,0x1d1f	,DKF_0	), // LATIN SMALL LETTER SIDEWAYS TURNED M
/*TURNED             */	DEADTRANS(	L'o'	,0x1d1f	,0x1d11	,DKF_0	), // LATIN SMALL LETTER SIDEWAYS O
/*TURNED             */	DEADTRANS(	L'u'	,0x1d1f	,0x1d1d	,DKF_0	), // LATIN SMALL LETTER SIDEWAYS U
/*TURNED             */	DEADTRANS(	0x00eb	,0x1d1f	,0x1d1e	,DKF_0	), // LATIN SMALL LETTER SIDEWAYS DIAERESIZED U
/*TURNED             */	DEADTRANS(	0x002d	,0x1d14	,0xab42	,CHAIN	), // LATIN SMALL LETTER TURNED OE WITH HORIZONTAL STROKE
/*TURNED             */	DEADTRANS(	0x0153	,0xab42	,0xab42	,DKF_0	), // LATIN SMALL LETTER TURNED OE WITH HORIZONTAL STROKE
/*TURNED             */	DEADTRANS(	0x002f	,0x1d14	,0xab41	,CHAIN	), // LATIN SMALL LETTER TURNED OE WITH STROKE
/*TURNED             */	DEADTRANS(	L'o'	,0xab41	,0xab44	,DKF_0	), // LATIN SMALL LETTER TURNED O OPEN-O WITH STROKE
/*TURNED             */	DEADTRANS(	0x0153	,0xab41	,0xab41	,DKF_0	), // LATIN SMALL LETTER TURNED OE WITH STROKE
/*TURNED             */	DEADTRANS(	0x003c	,0x1d14	,0x1d1a	,CHAIN	), // LATIN LETTER SMALL CAPITAL TURNED R
/*TURNED             */	DEADTRANS(	L'E'	,0x1d1a	,0x2c7b	,DKF_0	), // LATIN LETTER SMALL CAPITAL TURNED E
/*TURNED             */	DEADTRANS(	L'M'	,0x1d1a	,0xa7fa	,DKF_0	), // LATIN LETTER SMALL CAPITAL TURNED M
/*TURNED             */	DEADTRANS(	L'R'	,0x1d1a	,0x1d1a	,DKF_0	), // LATIN LETTER SMALL CAPITAL TURNED R
/*TURNED             */	DEADTRANS(	0x003f	,0x1d14	,0x00bf	,DKF_0	), // INVERTED QUESTION MARK
/*TURNED             */	DEADTRANS(	L'h'	,0x027b	,0x02ae	,DKF_0	), // LATIN SMALL LETTER TURNED H WITH FISHHOOK
/*TURNED             */	DEADTRANS(	0x007b	,0x027b	,0x02af	,DKF_0	), // LATIN SMALL LETTER TURNED H WITH FISHHOOK AND TAIL
/*TURNED             */	DEADTRANS(	0x007b	,0x1d14	,0x027b	,DKF_0	), // LATIN SMALL LETTER TURNED R WITH HOOK
/*TURNED             */	DEADTRANS(	0x007c	,0x1d14	,0x0270	,CHAIN	), // LATIN SMALL LETTER TURNED M WITH LONG LEG
/*TURNED             */	DEADTRANS(	L'm'	,0x0270	,0x0270	,DKF_0	), // LATIN SMALL LETTER TURNED M WITH LONG LEG
/*TURNED             */	DEADTRANS(	L'r'	,0x0270	,0x027a	,DKF_0	), // LATIN SMALL LETTER TURNED R WITH LONG LEG
/*TURNED             */	DEADTRANS(	0x007d	,0x1d14	,0x0284	,CHAIN	), // LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK
/*TURNED             */	DEADTRANS(	L'f'	,0x0284	,0x0284	,DKF_0	), // LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK
/*TURNED             */	DEADTRANS(	L'r'	,0x0284	,0x2c79	,DKF_0	), // LATIN SMALL LETTER TURNED R WITH TAIL
/*TURNED             */	DEADTRANS(	0x00a4	,0x1d14	,0xa77f	,CHAIN	), // LATIN SMALL LETTER TURNED INSULAR G
/*TURNED             */	DEADTRANS(	L'G'	,0xa77f	,0xa77e	,DKF_0	), // LATIN CAPITAL LETTER TURNED INSULAR G
/*TURNED             */	DEADTRANS(	L'g'	,0xa77f	,0xa77f	,DKF_0	), // LATIN SMALL LETTER TURNED INSULAR G
/*TURNED             */	DEADTRANS(	0x00a9	,0x1d14	,0xab51	,DKF_0	), // LATIN SMALL LETTER TURNED UI
/*TURNED             */	DEADTRANS(	0x00b5	,0x1d14	,0x0252	,CHAIN	), // LATIN SMALL LETTER TURNED ALPHA
/*TURNED             */	DEADTRANS(	0x00e6	,0x1d14	,0x1d02	,DKF_0	), // LATIN SMALL LETTER TURNED AE
/*TURNED             */	DEADTRANS(	0x00f9	,0x1d14	,0x0252	,CHAIN	), // LATIN SMALL LETTER TURNED ALPHA
/*TURNED             */	DEADTRANS(	L'A'	,0x0252	,0x2c70	,DKF_0	), // LATIN CAPITAL LETTER TURNED ALPHA
/*TURNED             */	DEADTRANS(	L'a'	,0x0252	,0x0252	,DKF_0	), // LATIN SMALL LETTER TURNED ALPHA
/*TURNED             */	DEADTRANS(	L'd'	,0x0252	,0x018d	,DKF_0	), // LATIN SMALL LETTER TURNED DELTA
/*TURNED             */	DEADTRANS(	L'e'	,0x0252	,0x1d08	,DKF_0	), // LATIN SMALL LETTER TURNED OPEN E

/*** DEADTRANS LIST: END OF PASTE-AND-REPLACE. ***/
    0, 0
};

/***************************************************************************\
* aKeyNames[], aKeyNamesExt[]  - Virtual Scancode to Key Name tables
*
* Table attributes: Ordered Scan (by scancode), null-terminated
*
* Only the names of Extended, NumPad, Dead and Non-Printable keys are here.
* (Keys producing printable characters are named by that character)
\***************************************************************************/

static ALLOC_SECTION_LDATA VSC_LPWSTR aKeyNames[] = {
    0x01,    L"ECHAP",
    0x0e,    L"RET.ARR",
    0x0f,    L"TAB",
    0x1c,    L"ENTREE",
    0x1d,    L"CTRL",
    0x29,    L"VERR.PRO",	// Newly added.	== KANA toggle key.
    0x2a,    L"MAJ GAUCHE",
    0x36,    L"MAJ DROITE",
    0x37,    L"* (PAVE NUM.)",
    0x38,    L"ALT",
    0x39,    L"ESPACE",
    0x3a,    L"VERR.MAJ",
    0x3b,    L"F1",
    0x3c,    L"F2",
    0x3d,    L"F3",
    0x3e,    L"F4",
    0x3f,    L"F5",
    0x40,    L"F6",
    0x41,    L"F7",
    0x42,    L"F8",
    0x43,    L"F9",
    0x44,    L"F10",
    0x45,    L"PAUSE",
    0x46,    L"DEFIL",
    0x47,    L"7 (PAVE NUM.)",
    0x48,    L"8 (PAVE NUM.)",
    0x49,    L"9 (PAVE NUM.)",
    0x4a,    L"- (PAVE NUM.)",
    0x4b,    L"4 (PAVE NUM.)",
    0x4c,    L"5 (PAVE NUM.)",
    0x4d,    L"6 (PAVE NUM.)",
    0x4e,    L"+ (PAVE NUM.)",
    0x4f,    L"1 (PAVE NUM.)",
    0x50,    L"2 (PAVE NUM.)",
    0x51,    L"3 (PAVE NUM.)",
    0x52,    L"0 (PAVE NUM.)",
    0x53,    L". (PAVE NUM.)",
    0x54,    L"Sys Req",
    0x57,    L"F11",
    0x58,    L"F12",
    0x7c,    L"F13",
    0x7d,    L"F14",
    0x7e,    L"F15",
    0x7f,    L"F16",
    0x80,    L"F17",
    0x81,    L"F18",
    0x82,    L"F19",
    0x83,    L"F20",
    0x84,    L"F21",
    0x85,    L"F22",
    0x86,    L"F23",
    0x87,    L"F24",
    0   ,    NULL
};

static ALLOC_SECTION_LDATA VSC_LPWSTR aKeyNamesExt[] = {
    0x1c,    L"ENTREE (PAVE NUM.)",
    0x1d,    L"CTRL DROITE",
    0x35,    L"/ (PAVE NUM.)",
    0x37,    L"IMPECR",		// Was "Impr.Ecran"
    0x38,    L"ALTGR",		// Was "ALT DROITE"
    0x45,    L"VERR.NUM",
    0x46,    L"ATTN",		// == Break, = Ctrl + Pause
    0x47,    L"ORIGINE",
    0x48,    L"HAUT",
    0x49,    L"PG.PREC",
    0x4b,    L"GAUCHE",
    0x4d,    L"DROITE",
    0x4f,    L"FIN",
    0x50,    L"BAS",
    0x51,    L"PG.SUIV",
    0x52,    L"INS",
    0x53,    L"SUPPR",
    0x54,    L"<00>",
    0x56,    L"AIDE",
    0x5b,    L"WINDOWS GAUCHE",
    0x5c,    L"WINDOWS DROITE",
    0x5d,    L"APPLICATION",
    0   ,    NULL
};

/****************************************************************************************\
*  KbdTables
\****************************************************************************************/
static ALLOC_SECTION_LDATA KBDTABLES KbdTables = {
    /*
     * Modifier keys
     */
    &CharModifiers,
    /*
     * Characters tables
     */
    aVkToWcharTable,
    /*
     * Diacritics
     */
    aDeadKey,
    /*
     * Names of Keys
     */
    aKeyNames,
    aKeyNamesExt,
    aKeyNamesDead,
    /*
     * Scan codes to Virtual Keys
     */
    ausVK,
    sizeof(ausVK) / sizeof(ausVK[0]),
    aE0VscToVk,
    aE1VscToVk,
    /*
     * Locale-specific special processing // KLLF_ALTGR must NOT be disabled, because
     */                                   // RMENU can be reintroduced as T5E using
    MAKELONG(KLLF_ALTGR, KBD_VERSION),    // the Scan Code Mapper, see kbdcommon.H(250).
    /*
     * Ligatures
     */
    16,  // 16 is the maximum number of characters defined as ligatures length.
    sizeof(aLigature[0]),
    (PLIGATURE1)aLigature
};
PKBDTABLES KbdLayerDescriptor(VOID)
{
    return &KbdTables;
}
/****************************************************************************************\
*  End of kbfrintu.C
\****************************************************************************************/
// EOF
