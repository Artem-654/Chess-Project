#pragma once
#include <string>
using namespace std;
class chess
{
    string figure;
    bool can, whiterookleftmove = false, whiterookrightmove = false, whitekingmove = false, blackrookleftmove = false, blackrookrightmove = false, blackkingmove = false;
    short int beginmoveY = 0, beginmoveX = 0, endmoveY = 0, endmoveX = 0;
    short int oldbeginmoveX = 0, oldbeginmoveY = 0, oldendmoveX = 0, oldendmoveY = 0;
    const string whiteking = u8"\u265A ", whitequeen = u8"\u265B ", whiterook = u8"\u265C ", whitebishop = u8"\u265D ", whiteknight = u8"\u265E ", whitepawn = u8"\u265f";
    const string blackking = u8"\u2654 ", blackqueen = u8"\u2655 ", blackrook = u8"\u2656 ", blackbishop = u8"\u2657 ", blackknight = u8"\u2658 ", blackpawn = u8"\u2659 ", empty = "  ";
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
void menu(); 
void game();
void mapgen() const;
void whitemove();
void blackmove();
void history();
bool WhiteKingExist();
bool BlackKingExist();
bool white(string figure);
bool black(string figure);
bool whiteposible();
bool blackposible();

};