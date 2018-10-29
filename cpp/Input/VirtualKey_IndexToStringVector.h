#pragma once
#include "pch.h"

// List of Virtual-Key Codes pulled from https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes

static std::vector<Platform::String^> virtualKey_IndexToString = {
	/* Certain keys unknown/not listed, but maybe the key/index could still be generated, plus, I need filler. */
	"MINI",		/* 0x00 ; Undefined */
	"LM B",		/* 0x01 ; Left Mouse Button */
	"RM B",		/* 0x02 ; Right Mouse Button */
	"CNCL",		/* 0x03 ; Control Break Processing */
	"MM B",		/* 0x04 ; Middle Mouse Button (three-button mouse) */
	"X1MB",		/* 0x05 ; X1 Mouse Button */
	"X2MB",		/* 0x06 ; X2 Mouse Button */
	"0x07",		/* 0x07 ; Undefined */
	"BACK",		/* 0x08 ; BACKSPACE Key */
	"TAB",		/* 0x09 ; TAB Key */
	"0x0A",		/* 0x0A ; Reserved */
	"0x0B",		/* 0x0B ; Reserved */
	"CLR",		/* 0x0C ; CLEAR Key */
	"RTRN",		/* 0x0D ; ENTER Key */
	"0x0E",		/* 0x0E ; Undefined */
	"0x0F",		/* 0x0F ; Undefined */
	"SHFT",		/* 0x10 ; SHIFT Key */
	"CTRL",		/* 0x11 ; CTRL Key */
	"ALT",		/* 0x12 ; ALT Key */
	"PAUS",		/* 0x13 ; PAUSE Key */
	"CAPS",		/* 0x14 ; CAPS LOCK Key */
	"MODE",		/* 0x15 ; IME Mode (Kana/Hanguel/Hangul) */
	"0x16",		/* 0x16 ; Undefined */
	"JUNJ",		/* 0x17 ; IME Junja Mode */
	"FINL",		/* 0x18 ; IME Final Mode */
	"MODE",		/* 0x19 ; IME Mode (Kanji/Hanja) */
	"0x1A",		/* 0x1A ; Undefined */
	"ESC",		/* 0x1B ; ESC Key */
	"CONV",		/* 0x1C ; IME Convert */
	"NCNV",		/* 0x1D ; IME Non-Convert */
	"ACPT",		/* 0x1E ; IME Accept */
	"DIFM",		/* 0x1F ; IME Mode Change Request */
	"SPCE",		/* 0x20 ; SPACEBAR */
	"PGUP",		/* 0x21 ; PAGE UP Key */
	"PDWN",		/* 0x22 ; PAGE DOWN Key */
	"END",		/* 0x23 ; END Key */
	"HOME",		/* 0x24 ; HOME Key */
	"LARW",		/* 0x25 ; LEFT ARROW Key */
	"UARW",		/* 0x26 ; UP ARROW Key */
	"RARW",		/* 0x27 ; RIGHT ARROW Key */
	"DARW",		/* 0x28 ; DOWN ARROW Key */
	"SLCT",		/* 0x29 ; SELECT Key */
	"PRNT",		/* 0x2A ; PRINT Key */
	"EXEC",		/* 0x2B ; EXECUTE Key */
	"PSCR",		/* 0x2C ; PRINT SCREEN Key */
	"INS",		/* 0x2D ; INS Key */
	"DEL",		/* 0x2E ; DEL Key */
	"HELP",		/* 0x2F ; HELP Key */
	"0",		/* 0x30 ; 0 Key */
	"1",		/* 0x31 ; 1 Key */
	"2",		/* 0x32 ; 2 Key */
	"3",		/* 0x33 ; 3 Key */
	"4",		/* 0x34 ; 4 Key */
	"5",		/* 0x35 ; 5 Key */
	"6",		/* 0x36 ; 6 Key */
	"7",		/* 0x37 ; 7 Key */
	"8",		/* 0x38 ; 8 Key */
	"9",		/* 0x39 ; 9 Key */
	"0x3A",		/* 0x3A ; Undefined */
	"0x3B",		/* 0x3B ; Undefined */
	"0x3C",		/* 0x3C ; Undefined */
	"0x3D",		/* 0x3D ; Undefined */
	"0x3E",		/* 0x3E ; Undefined */
	"0x3F",		/* 0x3F ; Undefined */
	"0x40",		/* 0x40 ; Undefined */
	"A",		/* 0x41 ; A Key */
	"B",		/* 0x42 ; B Key */
	"C",		/* 0x43 ; C Key */
	"D",		/* 0x44 ; D Key */
	"E",		/* 0x45 ; E Key */
	"F",		/* 0x46 ; F Key */
	"G",		/* 0x47 ; G Key */
	"H",		/* 0x48 ; H Key */
	"I",		/* 0x49 ; I Key */
	"J",		/* 0x4A ; J Key */
	"K",		/* 0x4B ; K Key */
	"L",		/* 0x4C ; L Key */
	"M",		/* 0x4D ; M Key */
	"N",		/* 0x4E ; N Key */
	"O",		/* 0x4F ; O Key */
	"P",		/* 0x50 ; P Key */
	"Q",		/* 0x51 ; Q Key */
	"R",		/* 0x52 ; R Key */
	"S",		/* 0x53 ; S Key */
	"T",		/* 0x54 ; T Key */
	"U",		/* 0x55 ; U Key */
	"V",		/* 0x56 ; V Key */
	"W",		/* 0x57 ; W Key */
	"X",		/* 0x58 ; X Key */
	"Y",		/* 0x59 ; Y Key */
	"Z",		/* 0x5A ; Z Key */
	"LWIN",		/* 0x5B ; Left Windows Key */
	"RWIN",		/* 0x5C ; Right Windows Key */
	"APPS",		/* 0x5D ; Applications Key */
	"0x5E",		/* 0x5E ; Reserved */
	"SLEP",		/* 0x5F ; Computer Sleep Key */
	"NUM0",		/* 0x60 ; Numeric Key Pad 0 Key */
	"NUM1",		/* 0x61 ; Numeric Key Pad 1 Key */
	"NUM2",		/* 0x62 ; Numeric Key Pad 2 Key */
	"NUM3",		/* 0x63 ; Numeric Key Pad 3 Key */
	"NUM4",		/* 0x64 ; Numeric Key Pad 4 Key */
	"NUM5",		/* 0x65 ; Numeric Key Pad 5 Key */
	"NUM6",		/* 0x66 ; Numeric Key Pad 6 Key */
	"NUM7",		/* 0x67 ; Numeric Key Pad 7 Key */
	"NUM8",		/* 0x68 ; Numeric Key Pad 8 Key */
	"NUM9",		/* 0x69 ; Numeric Key Pad 9 Key */
	"MULT",		/* 0x6A ; Multiply Key */
	"ADD",		/* 0x6B ; Add Key */
	"SPRT",		/* 0x6C ; Separator Key */
	"SUB",		/* 0x6D ; Subtract Key */
	"DECI",		/* 0x6E ; Decimal Key */
	"DIVD",		/* 0x6F ; Divide Key */
	"F1",		/* 0x70 ; F1 Key */
	"F2",		/* 0x71 ; F2 Key */
	"F3",		/* 0x72 ; F3 Key */
	"F4",		/* 0x73 ; F4 Key */
	"F5",		/* 0x74 ; F5 Key */
	"F6",		/* 0x75 ; F6 Key */
	"F7",		/* 0x76 ; F7 Key */
	"F8",		/* 0x77 ; F8 Key */
	"F9",		/* 0x78 ; F9 Key */
	"F10",		/* 0x79 ; F10 Key */
	"F11",		/* 0x7A ; F11 Key */
	"F12",		/* 0x7B ; F12 Key */
	"F13",		/* 0x7C ; F13 Key */
	"F14",		/* 0x7D ; F14 Key */
	"F15",		/* 0x7E ; F15 Key */
	"F16",		/* 0x7F ; F16 Key */
	"F17",		/* 0x80 ; F17 Key */
	"F18",		/* 0x81 ; F18 Key */
	"F19",		/* 0x82 ; F19 Key */
	"F20",		/* 0x83 ; F20 Key */
	"F21",		/* 0x84 ; F21 Key */
	"F22",		/* 0x85 ; F22 Key */
	"F23",		/* 0x86 ; F23 Key */
	"F24",		/* 0x87 ; F24 Key */
	"0x88",		/* 0x88 ; Unassigned */
	"0x89",		/* 0x89 ; Unassigned */
	"0x8A",		/* 0x8A ; Unassigned */
	"0x8B",		/* 0x8B ; Unassigned */
	"0x8C",		/* 0x8C ; Unassigned */
	"0x8D",		/* 0x8D ; Unassigned */
	"0x8E",		/* 0x8E ; Unassigned */
	"0x8F",		/* 0x8F ; Unassigned */
	"NMLK",		/* 0x90 ; NUM LOCK Key */
	"SCLK",		/* 0x91 ; SCROLL LOCK Key */
	"0x92",		/* 0x92 ; OEM Specific */
	"0x93",		/* 0x93 ; OEM Specific */
	"0x94",		/* 0x94 ; OEM Specific */
	"0x95",		/* 0x95 ; OEM Specific */
	"0x96",		/* 0x96 ; OEM Specific */
	"0x97",		/* 0x97 ; Unassigned */
	"0x98",		/* 0x98 ; Unassigned */
	"0x99",		/* 0x99 ; Unassigned */
	"0x9A",		/* 0x9A ; Unassigned */
	"0x9B",		/* 0x9B ; Unassigned */
	"0x9C",		/* 0x9C ; Unassigned */
	"0x9D",		/* 0x9D ; Unassigned */
	"0x9E",		/* 0x9E ; Unassigned */
	"0x9F",		/* 0x9F ; Unassigned */
	"LSFT",		/* 0xA0 ; Left SHIFT Key */
	"RSFT",		/* 0xA1 ; Right SHIFT Key */
	"LCTL",		/* 0xA2 ; Left CONTROL Key */
	"RCTL",		/* 0xA3 ; Right CONTROL Key */
	"LMNU",		/* 0xA4 ; Left MENU Key */
	"RMNU",		/* 0xA5 ; Right Menu Key */
	"BBCK",		/* 0xA6 ; Browser Back Key */
	"BFWD",		/* 0xA7 ; Browser Forward Key */
	"BRFR",		/* 0xA8 ; Browser Refresh Key */
	"BSTP",		/* 0xA9 ; Browser Stop Key */
	"BSCH",		/* 0xAA ; Browser Search Key */
	"BFVT",		/* 0xAB ; Browser Favorites Key */
	"BHOM",		/* 0xAC ; Browser Start & Home Key */
	"MUTE",		/* 0xAD ; Volume Mute Key */
	"VDWN",		/* 0xAE ; Volume Down Key */
	"VUP",		/* 0xAF ; Volume Up Key */
	"NEXT",		/* 0xB0 ; Next Track Key */
	"PREV",		/* 0xB1 ; Previous Track Key */
	"STOP",		/* 0xB2 ; Stop Media Key */
	"PAUS",		/* 0xB3 ; Play/Pause Media Key */
	"MAIL",		/* 0xB4 ; Start Mail Key */
	"MDIA",		/* 0xB5 ; Select Media Key */
	"APP1",		/* 0xB6 ; Start Application 1 Key */
	"APP2",		/* 0xB7 ; Start Application 2 Key */
	"0xB8",		/* 0xB8 ; Reserved */
	"0xB9",		/* 0xB9 ; Reserved */
	";",		/* 0xBA ; The Semi-Colon & Colon Key */
	"+",		/* 0xBB ; The Plus Key */
	",",		/* 0xBC ; The Comma Key */
	"-",		/* 0xBD ; The Minus Key */
	".",		/* 0xBE ; The Period Key */
	"/",		/* 0xBF ; The Forward Slash & Question Mark Key */
	"`",		/* 0xC0 ; The Grave Accent & Tilde Key */
	"0xC1",		/* 0xC1 ; Reserved */
	"0xC2",		/* 0xC2 ; Reserved */
	"0xC3",		/* 0xC3 ; Reserved */
	"0xC4",		/* 0xC4 ; Reserved */
	"0xC5",		/* 0xC5 ; Reserved */
	"0xC6",		/* 0xC6 ; Reserved */
	"0xC7",		/* 0xC7 ; Reserved */
	"0xC8",		/* 0xC8 ; Reserved */
	"0xC9",		/* 0xC9 ; Reserved */
	"0xCA",		/* 0xCA ; Reserved */
	"0xCB",		/* 0xCB ; Reserved */
	"0xCC",		/* 0xCC ; Reserved */
	"0xCD",		/* 0xCD ; Reserved */
	"0xCE",		/* 0xCE ; Reserved */
	"0xCF",		/* 0xCF ; Reserved */
	"0xD0",		/* 0xD0 ; Reserved */
	"0xD1",		/* 0xD1 ; Reserved */
	"0xD2",		/* 0xD2 ; Reserved */
	"0xD3",		/* 0xD3 ; Reserved */
	"0xD4",		/* 0xD4 ; Reserved */
	"0xD5",		/* 0xD5 ; Reserved */
	"0xD6",		/* 0xD6 ; Reserved */
	"0xD7",		/* 0xD7 ; Reserved */
	"0xD8",		/* 0xD8 ; Unassigned */
	"0xD9",		/* 0xD9 ; Unassigned */
	"0xDA",		/* 0xDA ; Unassigned */
	"[",		/* 0xDB ; The Open Bracket & Open Brace Key */
	"\\",		/* 0xDC ; The Backslash & Pipe Key */
	"]",		/* 0xDD ; The Closed Bracket & Closed Brace Key */
	"'",		/* 0xDE ; The Single Quote & Double Quote Key */
	"MISC",		/* 0xDF ; Miscellaneous Characters */
	"0xE0",		/* 0xE0 ; Reserved */
	"0xE1",		/* 0xE1 ; OEM Specific */
	"0xE2",		/* 0xE2 ; OEM Specific */
	"0xE3",		/* 0xE3 ; OEM Specific */
	"0xE4",		/* 0xE4 ; OEM Specific */
	"IMEP",		/* 0xE5 ; IME PROCESS Key */
	"0xE6",		/* 0xE6 ; OEM Specific */
	"PACK",		/* 0xE7 ; Complex; See Website */
	"0xE8",		/* 0xE8 ; Unassigned */
	"0xE9",		/* 0xE9 ; OEM Specific */
	"0xEA",		/* 0xEA ; OEM Specific */
	"0xEB",		/* 0xEB ; OEM Specific */
	"0xEC",		/* 0xEC ; OEM Specific */
	"0xED",		/* 0xED ; OEM Specific */
	"0xEE",		/* 0xEE ; OEM Specific */
	"0xEF",		/* 0xEF ; OEM Specific */
	"0xF0",		/* 0xF0 ; OEM Specific */
	"0xF1",		/* 0xF1 ; OEM Specific */
	"0xF2",		/* 0xF2 ; OEM Specific */
	"0xF3",		/* 0xF3 ; OEM Specific */
	"0xF4",		/* 0xF4 ; OEM Specific */
	"0xF5",		/* 0xF5 ; OEM Specific */
	"ATTN",		/* 0xF6 ; Attn Key */
	"CRSL",		/* 0xF7 ; CrSel Key */
	"EXSL",		/* 0xF8 ; ExSel Key */
	"REOF",		/* 0xF9 ; Erease EOF Key */
	"PLAY",		/* 0xFA ; Play Key */
	"ZOOM",		/* 0xFB ; Zoom Key */
	"0xFC",		/* 0xFC ; Reserved */
	"PA1",		/* 0xFD ; PA1 Key */
	"CLER",		/* 0xFE ; Clear Key */
	"MAXI"		/* 0xFF ; Undefined */
};