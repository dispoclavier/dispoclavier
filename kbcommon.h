/****************************** H Module Header ***********************************\
* charset=ANSI
* Module Name=kbcommon.H
* Version=4.4
* Last edited=
2018-03-21T1441+0100
*
* Content=Keyboard layout header: Various defines for use by keyboard input code.
* Description=Kana toggle; Modifier keys; Compose key; Numerical keypad accessibility and enhancement.
* See kbd.h for a general description
*
* Copyright:
* © 1985..2001 Microsoft Corporation pro parte;
* © 2016..2018 M. S. (charupdate@orange.fr)
*
* Version history and modification log:
*
* Tue Mar 21, 2018  updated for implementing bépo (v 4.4)
* Tue Mar 21, 2018  completed updating comments (v 4.3)
* Thu Mar 15, 2018  updated comments for French prototyping (v 4.2)
* Sat Feb 17, 2018  updated for CLDR #10851 (PRI #367) prototyping
* Sat Feb 17, 2018  v4.1.0  renamed to 'kbcommon.h'
* Fri Nov 17, 2017  done with testing, reset to KANA
* Thu Nov 16, 2017  updated to test JUNJA and other VKs
* Mon Dec 12, 2016        revised comment on ligature table typedefs
* Tue Sep 20, 2016        revised comments on modifier bits
* Mon Sep 19, 2016  v4.0  moved allocation table typedef to locale header; 
* Fri Sep 02, 2016        reviewed comments before posting on GitLab
* Sun Aug 08, 2016  v3.0  Pause remapping commented out;
* Sun Jul 17, 2016
* Fri Jul 15, 2016
* Wed Jun 22, 2016  v2.0
* Fri Jun 03, 2016  
* Thu Jun 02, 2016        added Group Select key
* Sun May 22, 2016        moved TYPEDEF_LIGATURE(16) here and completed
* Sat May 21, 2016        commented out TYPEDEF_VK_TO_WCHARS(10)
* Sat Jan 31, 2016
* Sat Jan 30, 2016
* Fri Jan 29, 2016
* Thu Jan 28, 2016  v1.0  renamed to 'kbdcommon.H'
* Sat Dec 12, 2015  v0.0  renamed to 'kbdcom-A.H'
* Mon Oct 19, 2915
* Thu Oct 01, 2015
* Wed Sep 23, 2015  
* Tue Sep 22, 2015  merged general parts of keyboard specific headers into this.
* Fri Sep 18, 2015
* Thu Sep 17, 2015
* Wed Sep 16, 2015
* Tue Sep 15, 2015
* Thu Sep 10, 2015
* File History:
* Tue Sep 08, 2015  Forked from kbdfre.H
\**********************************************************************************/
/**********************************************************************************\
* 0  INTRODUCTION
*
* This header file provides general defines and some additional documentation
* for keyboard layout DLLs that conform to a future revised ISO/IEC 9995
* keyboard standard.
*
* 0.1  Target machines
*
* The goal has been to enhance all physical keyboards, namedly compact keyboards
* of laptop computers. As 91 % of the world's PCs are powered by Windows, keyboard
* standards today must conform to the frozen Windows APIs, particularly because
* the time when that part of Windows was under development was left unused as far
* as the on-going ISO/IEC 9995 standardization process was concerned.
* By contrast, porting the features to Linux is easy thanks to persistent
* development and free of charge fresh installs.
*
* 0.2  Used software
*
* Every proposed feature can be implemented on Windows using the environment of
* KbdUTool 3.40 shipped with Microsoft Keyboard Layout Creator 1.4, as well as
* the latter for the installers. No other software is needed to generate the
* binaries. A command line script may facilitate the use of KbdUTool. To edit
* certain parts of the sources, Microsoft Excel is recommended, along with a
* performative text editor (but one may do it in NotePad).
*
* 0.3  Features
*
* The proposed features include:
*  * Full support of the locale's precomposed characters in a standard manner.
*  * Easy access to digits and ASCII symbols on all keyboards (Kana toggle on E00).
*  * Ready numerical keypad on all alphabetical ISO keyboards (including key B00).
*  * Two supplemental modifiers are added on two toggle keys for multiscript input.
*  * The numerical keypad is multi-level thanks to the use of several shift states.
*  * Compact keyboards: Numpad digits are active as soon as the Fn key is pressed.
*  * Includes a Compose key emulation that does not require any supplemental key.
*
* 0.4  About keyboard levels and groups
*
* Usually keyboard layouts are divided into a number of shift states.
* ISO/IEC 9995 introduced the concept of keyboard layout groups.
*
* 0.4.1  User-friendliness and ergonomics
*
* This lead to user-unfriendly implementations and keycap engravings.
* On many keyboards there is no more place than for one supplemental
* modifier key beyond the two shift keys, and complex key actuations
* as they are specified in the standard, are not fit for general use.
*
* To stay user-friendly, any keyboard should not display more than five
* characters per key. Thus the deadkey accessed ISO groups should not be 
* printed on the keycaps. The Function layer may be indicated with a glyph 
* in the center of the keycap or in another free place. On Kana-togglable 
* keys, the Kana shift states should be centered:
*  ---------   ---------   ---------   ---------   ---------  
*  | 2   4 |   | 2   4 |   | 2     |   | 2  4  |   | 2 4   |  = with Shift
*  |   5   |   |   5   |   |   5   |   |       |   |     5 | 
*  | 1   3 |   |     3 |   |     3 |   |   3   |   |   3   |  = without Shift     
*  ---------   ---------   ---------   ---------   --------- 
* The ISO/IEC 9995-1 keycap design scheme is not as legible:
*  --------- 
*  | 2   6 |  Note: ISO/IEC 9995-1 prohibits the use of levels 4 and 8,
*  | 1   5 |        because that modifier combination is used as a remnant
*  | 3   7 |        group selector. That feature can be used on Linux only.
*  --------- 
*
* 0.4.2  Usefulness and practicity
*
* A closer analysis shows that locale-unrelated characters and dead keys
* should be deferred to a multiple group selector dead key and to composition.
* * A multiple group selector in third level on space bar is an easy access 
*   to multiple layout groups for bicameral letters and for symbols.
* * Compose is able (1) to emulate any dead key; (2) to represent digraphs and
*   those characters that can be resolved to a digraph, e.g. ‘Th’ for Þ,
*   ‘dh’ for ð, ‘sh’ for U+0283, ‘zh’ for U+0292, ‘ng’ for U+014B,
*   ‘ny’ for U+0272, ‘sz’ (additionally to the traditional ‘ss’) for ß.
*
* Mapping those foreign characters to live key positions is inappropriate
* as well as insufficient. This method has several disadvantages:
*  * It brings the need of peculiar multilingual keyboards, while multilingual
*    support should be included by default on every keyboard.
*  * It leads to incomplete keyboard layouts that are lacking indispensable
*    characters while claiming to support huge numbers of languages.
*  * It makes for confusing keycap engravings and overloaded keytops.
*  * It induces high training costs on complex keyboards.
*
* 
* 0.5  Proposed keyboard layout level scheme
*
* 0.5.1  Groups
*
* The fourth level is no longer prohibited, since the group selector cannot 
* be defined as a combination of level-2-selector and level-3-selector, 
* unless it is publicly accepted that the whole scheme is deliberately not
* cross-platform implementable. As that is not a working strategy, only those 
* features are retained that can be implemented both on any version of Windows
* from Windows 2000 upwards, and on any version of macOS from Mac OS X 10.2.
*
* As each dead key should be considered a group selector, the group concept
* is advantageously redefined to describe the state of the keyboard after any
* dead key (including Group selector and Compose key) has been pressed.
* Every subsequent dead key press that is chained with the previous one,
* opens the gate to a sub-group.
*
* This way, the perceived complexity of the UI is only as deep as the user is
* ready to dive, rather than overwhelming the user with an overloaded mapping.
* On the other hand, advanced users are given a convenient way to input any
* character of the mainly supported script, as well as an unlimited number of
* symbols and other characters.
* 
* 0.5.2  Levels
*
* To become more intelligible, the levels are reordered in two piles of two 
* levels each, numbered 1A, 2A, 1B, 2B. The pile selector is typically AltGr 
* or Right Option.
*
* To work around the inability of Windows to produce more than one single 
* UTF-16 code unit per dead key sequence, Windows is granted the use of the 
* Control + Alt key combination to access pile C with levels 1C and 2C on 
* a limited panel of keys typically not used for application shortcuts.
* By contrast, AltGr is no longer an equivalent of Ctrl + Alt, given the 
* multiple issues related to interference with application shortcuts. See:
http://keyman.typepad.com/keyman_weblog/2008/06/robust-key-mess.html
*
* When the last keypress in a dead key sequence is with legacy AltGr, Word 
* disregards the dead key. That does not occur when another modifier is used 
* on the AltGr key.
* 
* Some third party applications may not be able to process those modifiers.
*
* Additionally, on all operating systems, the use of upper levels of the Numbers 
* modifier can be used for input of additional characters in a locale tailoring,
* e.g. superscript small letters for locales using superscript abbreviations, 
* such as ordinal indicators, so as to get an interoperable digital representation.
*
\**********************************************************************************/
/**********************************************************************************\
* 1  ALPHABETIC AND PUNCTUATION KEY REMAPPINGS
*
* See VK redefines in the locale specific header files.
*
\**********************************************************************************/
/**********************************************************************************\
* 2  KANA TOGGLE KEY MAPPING
* 
* The following is added to remap key E00 (ISO/IEC 9995-1) to a KanaLock toggle.
* Key E00 is VK_OEM_3 on the US keyboard, and VK_OEM_7 on the French keyboard.
* Optionally, key C00 (VK_CAPITAL] can be used for that purpose.
*
* The Caps Lock and Programmer toggles may be inverted on Windows using the 
* built-in Scancode Mapper, if that is not done in the layout driver.
*
* This toggle is needed to switch between a language centered layout and
* an ASCII supporting layout. It solves the problem of access to digits
* on layouts that support many precomposed characters or direct access to some
* current punctuation on the upper row. Digits are then by default on level 1B,
* and duplicated on level 1A when Programmer mode is on.
*
* The supplemental layout toggle does exist on Linux likewise. On macOS while 
* the feature is unavailable, Caps Lock can be emulated using an iterative dead 
* key. (On macOS, any dead key can be iterative when its state is renewed after
* output, while Keyman can handle an unlimited number of custom flags.)
*
* Thus a supplemental toggle allows to get away from actual hybrid keyboard 
* layouts that are often not fit for most current purposes when precomposed
* characters for locales take the place of characters used in programming,
* while often not ensuring a correct input of the locales they are meant to
* support, or when they do, making the keyboard unfit for other purposes.
* According to modern usage, uppercase letters should be provided throughout,
* 
* The leftmost key in the upper row is ideally placed for a toggle, because
*  * it is worst placed for characters;
*  * it therefore contains the (presumably) least used characters;
*  * it is in the same row as the Caps Lock toggle;
*  * on native Windows keyboards a toggle always needs a dedicated key;
*  * in the base row on laptop computers there is no availability.
*
* However, if the Caps Lock toggle key is disliked, Kana Lock may be mapped
* on this key. E00 eventually may then be mapped to Caps Lock.
* 
* The modifier bit used for the Kana toggle is 0x08. Not using the Kana modifier
* for AltGr allows greater flexibility in mapping the Programmer mode.
* The recommended modifier bit for AltGr is 0x10. 
* Then, bicameral letters should not be mapped on levels accessed with AltGr
* (levels 1B and 2B), because on those levels Caps Lock is disabled.
*
* Keys with bicameral letters (in the alphanumerical block) must not be subject 
* to the Programmer toggle, because on keys where 0x08 is on, Caps Lock is 
* disabled likewise.
*
* See [WDK]\inc\api\kbd.h
* and [WDK]\inc\api\WINUSER.H
*
* > > THE ACTUAL MAPPING IS DONE IN THE LOCALE HEADER.
\**********************************************************************************/
// Key E00 to Kana Lock:
// #undef  T29
// #define T29 _EQ(                                     KANA                      )
//
// Key C00 (Caps Lock) to Kana Lock:
// #undef  T3A
// #define T3A _EQ(                                     KANA                      )
//
// Key E00 to Caps Lock:
// #undef  T29
// #define T29 _EQ(                                     CAPITAL                   )
//
// Applications (context menu) key to Kana Lock:
// #undef  X5D
// #define X5D _EQ(                                     KANA                      )
//
// Right Windows key to Kana Lock:
// #undef  X5C
// #define X5C _EQ(                                     KANA                      )
//
/**********************************************************************************\
* 3  KANA MODIFIER KEY MAPPING
*
* Originally a part of Japanese and Korean keyboards, Kana is actually used also
* as a Group Selector on Latin keyboards like the Canadian Multilingual Standard
* keyboard layout in its implementation on Windows.
*
* Mapping Kana is essentially a part of locale specific defines.
* See the locale headers for echoing the defines below and the actual setting.
*
\**********************************************************************************/
/**********************************************************************************\
* 3.1  KANA ON RIGHT ALT
*
* The following is added to remap key A08, that is the right hand Alt key
* (VK_RMENU, X38) to a Kana modifier key. See below on how to reintroduce RMENU.
*
* The right hand Alt key as a Kana modifier has two other advantages:
*   * It fits user habits.
*   * It does not impact low-level keyboard access using scancodes directly.
* 
* The virtual key name VK_OEM_AX is defined in WINUSER.H (587),
* and it is mentioned in kbd.h (1317).
*
* Right Alt may be reintroduced onto the keyboard by mapping
* the Applications (context menu) or Right Windows key scan code
* to an unused scancode defined as RMENU.
* The scancode used here is T5E (VK_OEM_BACKTAB), see kbd.h(1123).
\**********************************************************************************/
// Kana modifier on Right Alt:
// #undef  X38
// #define X38 _EQ(                                    OEM_AX                     )
// Unused scancode for optional mapping of Apps or RWin to Right Alt:
   #undef  T5E
   #define T5E _EQ(                                    RMENU                      )
/**********************************************************************************\
* 3.2  KANA ON LEFT ALT
*
* Following user preferences, the left-hand Alt key (A02) may be remapped
* to a Kana modifier:
*  * for layout symetrics;
*  * to have both AltGr and Kana shift states accessed with modifiers
* (which would exceed the conventional scheme but might be a way to conform
* to the inherited ISO/IEC 9995 group layouts that use 2 × 3 levels.
*
* However mapping Left Alt to a character layout modifier is not recommended
* on keyboards that are lacking key B00 and do not have Right Windows.
*
* Anyway, LEFT ALT CANNOT BE EFFICIENTLY REMAPPED IN THE LAYOUT DRIVER.
* This remapping can be performed using the Scan Code Mapper for keyboards,
* by adding a Scancode Map value to the following registry key:
* HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Keyboard Layout.
* See the ‘Scan Code Mapper for keyboards’ section in:
*        "Keyboard and mouse class drivers (Windows Drivers)" at:
https://msdn.microsoft.com/en-us/library/windows/hardware/jj128267(v=vs.85).aspx
*
\**********************************************************************************/
/**********************************************************************************\
* 3.3  KANA ON KEY B00 (VK_OEM_102)
* 
* On keyboards with either B00 (VK_OEM_102) or Right Windows (or both),
* B00 is preferredly mapped to Shift, following user preferences,
* while the actual Shift key or Left Windows key could be mapped to Alt.
* This remapping facilitates Ctrl + Alt (and Shift + Ctrl) key combinations.
*
* In the static ALLOC_SECTION_LDATA VK_TO_BIT aVkToBits[] the Kana modifier
* may be mirrored on B00 (OEM_WSCTRL), or B00 is used as the GRPSELT modifier.
* From there on the use of B00 is variant-depending, and the user may customize
* the mappings doing some fine tuning with the Scan Code Mapper, eventually
* by choosing from a set of predefined registry key values.
*
* The unused SC is T5A (VK_OEM_WSCTRL), see WINUSER.H(615) and kbd.h(1119).
* Conversely the original mapping of B00 as VK_OEM_102 may be restored
* using the Scan Code Mapper.
\**********************************************************************************/
// Kana modifier on B00 (VK_OEM_102):
// #undef  T56
// #define T56 _EQ(                                    OEM_WSCTRL                 )
// To restore the original mapping of B00:
   #undef  T5A
   #define T5A _EQ(                                    OEM_102                    )
/**********************************************************************************\
* 3.4  KANA ON APPLICATIONS (CONTEXT MENU)
*
* Alternatively, Kana may be mapped to the Applications key,
* if this is not rather used for Compose, or quite unavailable.
* Keyboard layouts for shipping should not remap the Applications key,
* but they may provide the original scan code of VK_OEM_AX: T5C,
* so that the user will be able to map Kana to a key by using the above cited
* Scan Code Mapper (in case Right Alt stays AltGr for backwards compatibility).
\**********************************************************************************/
// Kana modifier on Applications:
// #undef  X5D
// #define X5D _EQ(                                    OEM_AX                     )
/**********************************************************************************\
* 4  HIGHER MODIFIER KEYS
*
* Beyond Kana, four other modifier keys are available for support of supplemental 
* shift states, notably the two Oyayubi modifiers and the Group Select Aping key.
*
* Both Oyayubi keys are used as supplemental modifiers on keyboards of the 
* Oasys terminals from Fujitsu. There are various uses of them on Western keyboards
* as well. For instance, a pair of supplemental modifiers is used on the German 
* Neo2 ergonomical layout. On Windows this is implemented using Right Oyayubi.
* To input sequences in other scripts, modifiers may also be added on toggle keys,
* in order to use the continuous keypress with the modifier, and short press-and-
* release with the toggle.
*
* The Group Select key is a modifier for which no public documentation is
* available. Supposedly this is an aping of the ISO/IEC 9995 group selector,
* hence its short name GRPSELTAP.
*
* The modifier bit 0x40 is not named but is nevertheless fully available.
*
* The code below is added to get more explicit or less confusing names.
* For locale specific modifier naming, please see the locale header files.
\**********************************************************************************/
#define KBDROYAYUBI   0x10      // KBDROYA in kbd.h(61), Right Oyayubi;
#define KBDLOYAYUBI   0x20      // KBDLOYA in kbd.h(62), Left Oyayubi.
#define KBDGRPSELT    0x80      // KBDGRPSELTAP in kbd.h(63)
/**********************************************************************************\
* 5  COMPOSE KEY MAPPING
*
* The Compose dead key may be Kana + Space, or AltGr + Space, depending on
* whether Right Alt is Kana or AltGr. But this combination is preferredly 
* used as group selector.
*
* Thus the Compose key may be mapped to any key place, e.g. AltGr + O.
*
* On keyboards with a Circumflex dead key, Compose may additionally be accessed
* by Circumflex, k; or by Circumflex, q, if this is not otherwise used.
*
* Compose may be mapped to whatever key (e.g. Applications, Right Windows)
* using the built-in Windows Scan Code Mapper for keyboards with the scan code
* of the Brazilian VK_ABNT_C2 (T7E).
* 
* The virtual key name VK_OEM_7 is available because T29 is remapped
* (please refer to #1).
*
* To activate this facility, please uncomment the #undef and #define below.
\**********************************************************************************/
// Compose on VK_ABNT_C2:
// #undef  T7E
// #define T7E _EQ(                                    OEM_7                      )
/**********************************************************************************\
* 6  NUMERICAL KEYPAD MAPPING
\**********************************************************************************/
/**********************************************************************************\
* 6.1  DIGITS AND DECIMAL SEPARATOR
*
* The following are added to disable Numpad Specials. 
* This allows netbook users to enter digits on the overlay numpad 
* without toggling NumLock. Pressing Function (and hold it down
* while entering the digits) is sufficient.
*  
* Numpad specials are legacy features that are no longer needed 
* since they are available on dedicated keys. 
* They are already disabled on performative products like the MacBook™,
* as well as on the entire panel of Apple™ Mac™ computers.
*
* The most what numpad specials can do today, is to worsen ergonomics 
* on compact keyboards like those of netbooks, where a numpad 
* is emulated on most models. This numpad is often referred to
* as “not existent”, because it is lacking ease of access to digit keys, 
* which is one of the main advantages of a numpad. Operators are already 
* available simply when Fn is pressed. Now, digits are, too.
*
\**********************************************************************************/
#undef  T47
#define T47 _EQ(                                     NUMPAD7                      )
#undef  T48
#define T48 _EQ(                                     NUMPAD8                      )
#undef  T49
#define T49 _EQ(                                     NUMPAD9                      )
#undef  T4B
#define T4B _EQ(                                     NUMPAD4                      )
#undef  T4C
#define T4C _EQ(                                     NUMPAD5                      )
#undef  T4D
#define T4D _EQ(                                     NUMPAD6                      )
#undef  T4F
#define T4F _EQ(                                     NUMPAD1                      )
#undef  T50
#define T50 _EQ(                                     NUMPAD2                      )
#undef  T51
#define T51 _EQ(                                     NUMPAD3                      )
#undef  T52
#define T52 _EQ(                                     NUMPAD0                      )
#undef  T53
#define T53 _EQ(                                     DECIMAL                      )
/**********************************************************************************\
* 6.2  NUMLOCK KEY A SECOND BACKSPACE
*
* The following was added to remap T45 (VK_NUMLOCK) to a second Backspace.
*
* This is inspired from Mac OS X. See #4.1 above.
*
* This define was also used for small laptops, where Numlock is coupled
* with the Function Lock On NumPad toggle. This toggle should be placed 
* in the Base shift state, or in the Function shift state on CapsLock.
* NumLock was then defined on Pause (see next).
*
* However, this proved not to work because Pause got the Backspace 
* functionality as well, worsening user experience on netbooks.
* Therefore, this remapping is better performed using the built-in
* Scan Code Mapper for Keyboards (see #2).
\**********************************************************************************/
// Num Lock to Backspace:
// #undef  T45
// #define T45 _EQ(                                     BACK                      )
/**********************************************************************************\
* 6.3  PAUSE KEY TO NUM LOCK TOGGLE
*
* The following was added to remap Y1D (VK_PAUSE) to Num Lock toggle.
*
* The Pause key functionality can be emulated (see hereafter), so that
* this well positioned key (as opposed to the NumLK in Fn layer on
* netbooks) was remapped to NumLock, unifying thus the layout for most
* keyboard models using physical keys (except small models without
* even an emulated Numpad). However, the Pause key proves to be relegated
* to shifted levels or even missing on many machines. That leads to 
* disable this remapping.
*
* A Num Lock toggle is needed even on desktop keyboards because
* Num Lock is turned on by default at boot.
*
* Num Lock must be turned off because when Num Lock is on, the Shift
* modifiers are disabled on the Num Pad (while CapsLock stays effective).
*
* The Pause key is used in command prompts. The effect of a stop
* can be obtained by using the Break key (VK_CANCEL, X46).
* On most keyboards, the Break key consists of Ctrl+Pause.
* To resume, type 'n' (no) before hitting the Enter key.
*
* Despite of being used in command prompts, the Pause key is
* nevertheless missing on some laptop models. This makes for 
* worktool value lowering. Consistently, these models usually
* lack even an emulated numpad either. This prevents users from
* entering special characters using the Alt+NumPad input method.
* Therefore, laptop computers without any numpad, whether emulated
* or physical, are not Windows conformant. Consequently, the purchase 
* of those laptops is strongly discouraged.
\**********************************************************************************/
// Pause to Num Lock:
// #undef  Y1D
// #define Y1D _EQ(                                     NUMLOCK                   )
/**********************************************************************************\
* 7  VARIOUS DEFINES
\**********************************************************************************/
/**********************************************************************************\
* 7.1  TYPE DEFINES FOR ALLOCATION TABLE
*
* See the TYPEDEF_VK_TO_WCHARS(<n>) in the locale specific header file.
* The typedefs below did not work when the number of shift states was changed,
* even though it was in the covered range.
\**********************************************************************************/
// TYPEDEF_VK_TO_WCHARS(11) // VK_TO_WCHARS11, *PVK_TO_WCHARS11;
// TYPEDEF_VK_TO_WCHARS(12) // VK_TO_WCHARS12, *PVK_TO_WCHARS12;
// TYPEDEF_VK_TO_WCHARS(13) // VK_TO_WCHARS13, *PVK_TO_WCHARS13;
// TYPEDEF_VK_TO_WCHARS(14) // VK_TO_WCHARS14, *PVK_TO_WCHARS14;
// TYPEDEF_VK_TO_WCHARS(15) // VK_TO_WCHARS15, *PVK_TO_WCHARS15;
// TYPEDEF_VK_TO_WCHARS(16) // VK_TO_WCHARS16, *PVK_TO_WCHARS16;
// TYPEDEF_VK_TO_WCHARS(17) // VK_TO_WCHARS17, *PVK_TO_WCHARS17;
// TYPEDEF_VK_TO_WCHARS(18) // VK_TO_WCHARS18, *PVK_TO_WCHARS18;
// TYPEDEF_VK_TO_WCHARS(19) // VK_TO_WCHARS19, *PVK_TO_WCHARS19;
// TYPEDEF_VK_TO_WCHARS(20) // VK_TO_WCHARS20, *PVK_TO_WCHARS20;
// TYPEDEF_VK_TO_WCHARS(21) // VK_TO_WCHARS21, *PVK_TO_WCHARS21;
// TYPEDEF_VK_TO_WCHARS(22) // VK_TO_WCHARS22, *PVK_TO_WCHARS22;
// TYPEDEF_VK_TO_WCHARS(23) // VK_TO_WCHARS23, *PVK_TO_WCHARS23;
// TYPEDEF_VK_TO_WCHARS(24) // VK_TO_WCHARS24, *PVK_TO_WCHARS24;
// TYPEDEF_VK_TO_WCHARS(25) // VK_TO_WCHARS25, *PVK_TO_WCHARS25;
// TYPEDEF_VK_TO_WCHARS(26) // VK_TO_WCHARS26, *PVK_TO_WCHARS26;
// TYPEDEF_VK_TO_WCHARS(27) // VK_TO_WCHARS27, *PVK_TO_WCHARS27;
// TYPEDEF_VK_TO_WCHARS(28) // VK_TO_WCHARS28, *PVK_TO_WCHARS28;
// TYPEDEF_VK_TO_WCHARS(29) // VK_TO_WCHARS29, *PVK_TO_WCHARS29;
// TYPEDEF_VK_TO_WCHARS(30) // VK_TO_WCHARS30, *PVK_TO_WCHARS30;
// TYPEDEF_VK_TO_WCHARS(31) // VK_TO_WCHARS31, *PVK_TO_WCHARS31;
// TYPEDEF_VK_TO_WCHARS(32) // VK_TO_WCHARS32, *PVK_TO_WCHARS32;
// TYPEDEF_VK_TO_WCHARS(33) // VK_TO_WCHARS33, *PVK_TO_WCHARS33;
// TYPEDEF_VK_TO_WCHARS(34) // VK_TO_WCHARS34, *PVK_TO_WCHARS34;
// TYPEDEF_VK_TO_WCHARS(35) // VK_TO_WCHARS35, *PVK_TO_WCHARS35;
// TYPEDEF_VK_TO_WCHARS(36) // VK_TO_WCHARS36, *PVK_TO_WCHARS36;
// TYPEDEF_VK_TO_WCHARS(37) // VK_TO_WCHARS37, *PVK_TO_WCHARS37;
// TYPEDEF_VK_TO_WCHARS(38) // VK_TO_WCHARS38, *PVK_TO_WCHARS38;
// TYPEDEF_VK_TO_WCHARS(39) // VK_TO_WCHARS39, *PVK_TO_WCHARS39;
/**********************************************************************************\
* 7.2  TYPE DEFINES FOR LIGATURE TABLE
*
* The following are added to allow for the maximum number (16) of code points
* that are supported as a sequence by the related Windows API, and to complete
* the range started in kbd.h(465..469) for smaller sequence tables.
*
*  |||   Note that kbd.h(469) defines sequences already up to five WCHARS,
*  |||   that is more than the implemented limitation in MSKLC 1.4 which
*  |||   is set to four WCHARS because it was believed that this was the 
*  |||   architectural limit. That is true for Shift + AltGr only. Longer 
*  |||   sequences in Shift + AltGr cause the keyboard layout to fail, and 
*  |||   the system to bug if that layout is the default.
*
\**********************************************************************************/
TYPEDEF_LIGATURE(6)   // LIGATURE6,  *PLIGATURE6
TYPEDEF_LIGATURE(7)   // LIGATURE7,  *PLIGATURE7
TYPEDEF_LIGATURE(8)   // LIGATURE8,  *PLIGATURE8
TYPEDEF_LIGATURE(9)   // LIGATURE9,  *PLIGATURE9
TYPEDEF_LIGATURE(10)  // LIGATURE10, *PLIGATURE10
TYPEDEF_LIGATURE(11)  // LIGATURE11, *PLIGATURE11
TYPEDEF_LIGATURE(12)  // LIGATURE12, *PLIGATURE12
TYPEDEF_LIGATURE(13)  // LIGATURE13, *PLIGATURE13
TYPEDEF_LIGATURE(14)  // LIGATURE14, *PLIGATURE14
TYPEDEF_LIGATURE(15)  // LIGATURE15, *PLIGATURE15
TYPEDEF_LIGATURE(16)  // LIGATURE16, *PLIGATURE16
/**********************************************************************************\
* 7.3  DEFINES FOR ALLOCATION TABLE
*
* The following are added to make the source code fit into the fixed 
* 8 characters tabulation width of the built-in Windows NotePad, for
* best display of static ALLOC_SECTION_LDATA VK_TO_WCHARS##n aVkToWch##n[].
* The original, unshortened values are: WCH_NONE, WCH_DEAD, WCH_LGTR.
*
* > Users of high-end text editors do not need to restrict themselves.
*
* > Tabulations are intended to facilitate the use of spreadsheet software.
*
\**********************************************************************************/
#define NONE 0xF000  // No character mapped.
#define DEAD 0xF001  // This key position is a dead key (WCHAR in the next line).
#define LGTR 0xF002  // Here is a sequence, look up in the Ligatures table.
/**********************************************************************************\
* 7.4  DEFINES FOR THE DEAD TRANSFORMS LIST
*
* The following are added to facilitate source layout with 8 char tabulations
* and to enhance transparency in static ALLOC_SECTION_LDATA DEADKEY aDeadKey[].
*
* The default define is in kbd.h(439):  #define DKF_DEAD  0x0001
* For 0x0000 no alternate flag name is defined in kbd.h.
* DKF stands for 'Dead Key Flag', which is null by default.
* This flag is referred to as a “uFlag” in kbd.h(437).
\**********************************************************************************/
#define DKF_0 0x0000  // name used for 0 flag
#define CHAIN 0x0001  // name used for 1 flag
/**********************************************************************************\
* End of kbcommon.H
\**********************************************************************************/
// EOF
