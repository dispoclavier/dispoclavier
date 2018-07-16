/****************************** H Module Header ************************************\
* charset=ANSI
* Module Name=kbfrintu.H
* Version=1.1
* Last edited=
2018-03-21T1521+0100
*
* Content=keyboard layout header
* Description=Various defines for use by keyboard input code (see kbcommon.h).
* Locale=fr-FR
*
* Copyright:
* © 1985..2001 Microsoft Corporation pro parte;
* © 2017..2018 M. S. (charupdate@orange.fr)
*
* Version history and modification log:
*
* created by KBDTOOL v3.40 Sat Feb 17 08:59:15 2018
* modified:
* Wed Mar 21, 2018  updated in the wake of implementing bépo (v 1.1)
* Thu Mar 15, 2018  set version # to 1.0
* Mon Mar 12, 2018  synced version # with kbfrintu.keylayout (v 0.2.4)
* Sun Mar 11, 2018  reverted remapping on B07..B09 (version 0.2.0)
* Fri Mar 09, 2018  edited for kbfrintu.h
* Fri Mar 09, 2018  forked from kbenintu.h (http://charupdate.info/doc/kbenintu/)
\***********************************************************************************/
/*
 * kbd type should be controlled by cl command-line argument
 */
#define KBD_TYPE 4

/*
* Include the basis of all keyboard table values
#include "kbd.h"        [redundant]
*/
/***************************************************************************\
* 1  ALPHABETIC AND PUNCTUATION KEY REMAPPINGS
*
* The table below defines the virtual keys for various keyboard types where
* the keyboard differ from the US keyboard.
*
* _EQ() : all keyboard types have the same virtual key for this scancode
* _NE() : different virtual keys for this scancode, depending on kbd type
*
*     +------+ +----------+----------+----------+----------+----------+----------+
*     | Scan | |    kbd   |    kbd   |    kbd   |    kbd   |    kbd   |    kbd   |
*     | code | |   type 1 |   type 2 |   type 3 |   type 4 |   type 5 |   type 6 |
\****+-------+_+----------+----------+----------+----------+----------+----------+*/
//#undef  T0C
// #define T0C _EQ(                                    OEM_4                      )  is VK_OEM_MINUS again
#undef  T10
 #define T10 _EQ(                                        'A'                      )  // was VK_Q
#undef  T11
 #define T11 _EQ(                                        'Z'                      )  // was VK_W
#undef  T1A
 #define T1A _EQ(                                      OEM_6                      )  // was VK_OEM_4
#undef  T1B
 #define T1B _EQ(                                      OEM_1                      )  // was VK_OEM_6
#undef  T1E
 #define T1E _EQ(                                        'Q'                      )  // was VK_A
#undef  T27
 #define T27 _EQ(                                        'M'                      )  // was VK_OEM_1
#undef  T28
 #define T28 _EQ(                                      OEM_3                      )  // was VK_OEM_7
#undef  T29
 #define T29 _EQ(                                      OEM_7                      )  // was VK_OEM_3
#undef  T2C
 #define T2C _EQ(                                        'W'                      )  // was VK_Z
#undef  T32
 #define T32 _EQ(                                  OEM_COMMA                      )  // was VK_M
#undef  T33
 #define T33 _EQ(                                 OEM_PERIOD                      )  // was VK_OEM_COMMA
#undef  T34
 #define T34 _EQ(                                      OEM_2                      )  // was VK_OEM_PERIOD
#undef  T35
 #define T35 _EQ(                                      OEM_8                      )  // was VK_OEM_2

/**************************************************************************************\
* 2  MODIFIER BITS RENAMING
*
* These defines give the modifier bits handy English names.
* See kbd.h(56) for a detailed description. See also kbcommon.h(351).
* For use in static ALLOC_SECTION_LDATA VK_TO_BIT, kbdfrf91.C(239).
*
\**************************************************************************************/
#define MODSHIFT   0x01  // == 0000 0001
#define MODCTRL    0x02  // == 0000 0010
#define MODALT     0x04  // == 0000 0100 (0x06 == Ctrl + Alt == AltGr)
#define MODKANA    0x08  // == 0000 1000 sensitive to VK_KANA == Programmer toggle
#define MODALTGR   0x10  // == 0001 0000 
#define MODNUM     0x20  // == 0010 0000 Numbers modifier (B00, to be remapped to A02)
#define MODGREEK   0x40  // == 0100 0000 additionally on CapsLock key
#define MODARAB    0x80  // == 1000 0000 additionally on Programmer toggle key
/**************************************************************************************\
* 3  MODIFIER KEY MAPPING
*
* These defines are added for the locale specific modifier key mapping.
* See kbcommon.h for a full description and the source defines.
\**************************************************************************************/
// For 0x10 modifier on Right Alt (formerly VK_RMENU):
   #undef  X38
   #define X38 _EQ(                                   OEM_AX                      )
// For 0x20 modifier on B00 (formerly VK_OEM_102):
   #undef  T56
   #define T56 _EQ(                               OEM_WSCTRL                      )
// For 0x08 toggle on E00:
   #undef  T29
   #define T29 _EQ(                                     KANA                      )
/**************************************************************************************\
* 4  TYPEDEFS FOR ALLOCATION TABLE
*
* The following is added to allow for the accurate number of shift states in
* static ALLOC_SECTION_LDATA VK_TO_WCHARS<n> aVkToWch<n>[].
* This is an extension of kbd.h (403).
*
* For use with KbdUTool included in MSKLC 1.4, the code below is useless
* if the maximum number of shift states does not exceed 10.
* For use with WDK 7600.16385.1, the code below is useless
* if the maximum number of shift states does not exceed 9.
*
* For each allocation table whose number of shift states exceeds the covered
* range, a TYPEDEF_VK_TO_WCHARS(<n>) is needed,
* where <n> is the number of shift states.
\**************************************************************************************/
   TYPEDEF_VK_TO_WCHARS(11) // VK_TO_WCHARS11, *PVK_TO_WCHARS11;
   TYPEDEF_VK_TO_WCHARS(12) // VK_TO_WCHARS12, *PVK_TO_WCHARS12;
   TYPEDEF_VK_TO_WCHARS(13) // VK_TO_WCHARS13, *PVK_TO_WCHARS13;
   TYPEDEF_VK_TO_WCHARS(14) // VK_TO_WCHARS14, *PVK_TO_WCHARS14;
   TYPEDEF_VK_TO_WCHARS(15) // VK_TO_WCHARS15, *PVK_TO_WCHARS15;
   TYPEDEF_VK_TO_WCHARS(16) // VK_TO_WCHARS16, *PVK_TO_WCHARS16;
   TYPEDEF_VK_TO_WCHARS(17) // VK_TO_WCHARS17, *PVK_TO_WCHARS17;
   TYPEDEF_VK_TO_WCHARS(18) // VK_TO_WCHARS18, *PVK_TO_WCHARS18;
   TYPEDEF_VK_TO_WCHARS(19) // VK_TO_WCHARS19, *PVK_TO_WCHARS19;
   TYPEDEF_VK_TO_WCHARS(20) // VK_TO_WCHARS20, *PVK_TO_WCHARS20;
   TYPEDEF_VK_TO_WCHARS(21) // VK_TO_WCHARS21, *PVK_TO_WCHARS21;
   TYPEDEF_VK_TO_WCHARS(22) // VK_TO_WCHARS22, *PVK_TO_WCHARS22;
   TYPEDEF_VK_TO_WCHARS(23) // VK_TO_WCHARS23, *PVK_TO_WCHARS23;
   TYPEDEF_VK_TO_WCHARS(24) // VK_TO_WCHARS24, *PVK_TO_WCHARS24;
   TYPEDEF_VK_TO_WCHARS(25) // VK_TO_WCHARS25, *PVK_TO_WCHARS25;
   TYPEDEF_VK_TO_WCHARS(26) // VK_TO_WCHARS26, *PVK_TO_WCHARS26;
   TYPEDEF_VK_TO_WCHARS(27) // VK_TO_WCHARS27, *PVK_TO_WCHARS27;
   TYPEDEF_VK_TO_WCHARS(28) // VK_TO_WCHARS28, *PVK_TO_WCHARS28;
   TYPEDEF_VK_TO_WCHARS(29) // VK_TO_WCHARS29, *PVK_TO_WCHARS29;
   TYPEDEF_VK_TO_WCHARS(30) // VK_TO_WCHARS30, *PVK_TO_WCHARS30;
   TYPEDEF_VK_TO_WCHARS(31) // VK_TO_WCHARS31, *PVK_TO_WCHARS31;
   TYPEDEF_VK_TO_WCHARS(32) // VK_TO_WCHARS32, *PVK_TO_WCHARS32;
   TYPEDEF_VK_TO_WCHARS(33) // VK_TO_WCHARS33, *PVK_TO_WCHARS33;
   TYPEDEF_VK_TO_WCHARS(34) // VK_TO_WCHARS34, *PVK_TO_WCHARS34;
   TYPEDEF_VK_TO_WCHARS(35) // VK_TO_WCHARS35, *PVK_TO_WCHARS35;
   TYPEDEF_VK_TO_WCHARS(36) // VK_TO_WCHARS36, *PVK_TO_WCHARS36;
   TYPEDEF_VK_TO_WCHARS(37) // VK_TO_WCHARS37, *PVK_TO_WCHARS37;
   TYPEDEF_VK_TO_WCHARS(38) // VK_TO_WCHARS38, *PVK_TO_WCHARS38;
   TYPEDEF_VK_TO_WCHARS(39) // VK_TO_WCHARS39, *PVK_TO_WCHARS39;
   TYPEDEF_VK_TO_WCHARS(40) // VK_TO_WCHARS40, *PVK_TO_WCHARS40;
   TYPEDEF_VK_TO_WCHARS(41) // VK_TO_WCHARS41, *PVK_TO_WCHARS41;
   TYPEDEF_VK_TO_WCHARS(42) // VK_TO_WCHARS42, *PVK_TO_WCHARS42;
   TYPEDEF_VK_TO_WCHARS(43) // VK_TO_WCHARS43, *PVK_TO_WCHARS43;
   TYPEDEF_VK_TO_WCHARS(44) // VK_TO_WCHARS44, *PVK_TO_WCHARS44;
   TYPEDEF_VK_TO_WCHARS(45) // VK_TO_WCHARS45, *PVK_TO_WCHARS45;
   TYPEDEF_VK_TO_WCHARS(46) // VK_TO_WCHARS46, *PVK_TO_WCHARS46;
   TYPEDEF_VK_TO_WCHARS(47) // VK_TO_WCHARS47, *PVK_TO_WCHARS47;
   TYPEDEF_VK_TO_WCHARS(48) // VK_TO_WCHARS48, *PVK_TO_WCHARS48;
   TYPEDEF_VK_TO_WCHARS(49) // VK_TO_WCHARS49, *PVK_TO_WCHARS49;
   TYPEDEF_VK_TO_WCHARS(50) // VK_TO_WCHARS50, *PVK_TO_WCHARS50;
   TYPEDEF_VK_TO_WCHARS(51) // VK_TO_WCHARS51, *PVK_TO_WCHARS51;
   TYPEDEF_VK_TO_WCHARS(52) // VK_TO_WCHARS52, *PVK_TO_WCHARS52;
   TYPEDEF_VK_TO_WCHARS(53) // VK_TO_WCHARS53, *PVK_TO_WCHARS53;
   TYPEDEF_VK_TO_WCHARS(54) // VK_TO_WCHARS54, *PVK_TO_WCHARS54;
   TYPEDEF_VK_TO_WCHARS(55) // VK_TO_WCHARS55, *PVK_TO_WCHARS55;
   TYPEDEF_VK_TO_WCHARS(56) // VK_TO_WCHARS56, *PVK_TO_WCHARS56;
   TYPEDEF_VK_TO_WCHARS(57) // VK_TO_WCHARS57, *PVK_TO_WCHARS57;
   TYPEDEF_VK_TO_WCHARS(58) // VK_TO_WCHARS58, *PVK_TO_WCHARS58;
   TYPEDEF_VK_TO_WCHARS(59) // VK_TO_WCHARS59, *PVK_TO_WCHARS59;
/**********************************************************************************\
* End of kbfrintu.H
\**********************************************************************************/
// EOF
