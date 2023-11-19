#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
using namespace std;
class chess
{

	//~chess();
    const string whiteking = u8"\u265A ", whitequeen = u8"\u265B ", blackrook = u8"\u2656 ", whitebishop = u8"\u265D ", whiteknight = u8"\u265E ", blackpawn = u8"\u2659 ", empty = "  ";
    const string blackking = u8"\u2654 ", blackqueen = u8"\u2655 ", whiterook = u8"\u265C ", blackbishop = u8"\u2657 ", blackknight = u8"\u2658 ", whitepawn = u8"\u265f";
    string ChessMap[8][8] = {
        blackrook,blackknight,blackbishop,blackqueen,blackking,blackbishop,blackknight,blackrook,
        blackpawn,blackpawn,blackpawn,blackpawn,blackpawn,blackpawn,blackpawn,blackpawn,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        empty,empty,empty,empty,empty,empty,empty,empty,
        whitepawn,whitepawn,whitepawn,whitepawn,whitepawn,whitepawn,whitepawn,whitepawn,
        whiterook,whiteknight,whitebishop,whitequeen,whiteking,whitebishop,whiteknight,whiterook
    };
public:
	 chess();
     ~chess();
void menu(string(&map)[8][8]);
void game(string(&map)[8][8]);
void mapgen(string(&map)[8][8]);
void whitemove(string(&map)[8][8], bool& can);
void blackmove(string(&map)[8][8], bool& can);
void history();
bool WhiteKingExist(string map[8][8]);
bool BlackKingExist(string map[8][8]);
bool white(string figure);
bool black(string figure);
bool whiteposible(string(&map)[8][8], int beginmoveY, int beginmoveX, int endmoveY, int endmoveX);
bool blackposible(string(&map)[8][8], int beginmoveY, int beginmoveX, int endmoveY, int endmoveX);
};