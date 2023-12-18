#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#include <algorithm>
#include "ClassChess.h"
using namespace std;
    chess::chess()
    {
        menu();
    }
    void chess::menu()
    {
        int n;
        do
        {
            system("cls");
            cout << "\n Шахи\n\n1)Грати\n2)Історія\n3)Вийти з гри\n\n>>";
            n = _getch();
            switch (n)
            {
            case 49:
            {
                game();
                break;
            }
            case 50:
            {
                history();
                break;
            }
            }
        } while (n != 51);
    }
    void chess::game()
    {
        string name1, name2;
        system("cls");
        cout << "Введіть ім'я_прізвище першого гравця (білі фігури)\n>>";
        getline(cin, name1);
        system("cls");
        cout << "Введіть ім'я_прізвище другого гравця  (чорні фігури)\n>>";
        getline(cin, name2);
        system("cls");
        while (true)
        {
            can = false;
            do {
                mapgen();
                whitemove();
            } while (!can);
            if (!BlackKingExist())
            {
                system("cls");
                cout << "\n\n\tБілі перемогли\n\n" << endl;
                ofstream file("data.txt", fstream::app);
                SYSTEMTIME systemtime;
                GetLocalTime(&systemtime);
                if (systemtime.wDay<10)
                {
                    if (systemtime.wMonth < 10)
                    {
                        file << systemtime.wYear << ".0" << systemtime.wMonth << ".0" << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "білі" << endl;
                    }
                    else
                    {
                        file << systemtime.wYear << "." << systemtime.wMonth << ".0" << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "білі" << endl;
                    }
                }
                else
                {
                    if (systemtime.wMonth < 10)
                    {
                        file << systemtime.wYear << ".0" << systemtime.wMonth << "." << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "білі" << endl;
                    }
                    else
                    {
                        file << systemtime.wYear << "." << systemtime.wMonth << "." << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "білі" << endl;
                    }
                }
                file.close();
                system("pause");
                break;
            }
            can = false;
            do {
                mapgen();
                blackmove();
            } while (!can);
            if (!WhiteKingExist())
            {
                system("cls");
                cout << "\n\n\tЧорні перемогли\n\n" << endl;
                ofstream file("data.txt", fstream::app); 
                SYSTEMTIME systemtime;
                GetLocalTime(&systemtime);
                if (systemtime.wDay < 10)
                {
                    if (systemtime.wMonth < 10)
                    {
                        file << systemtime.wYear << ".0" << systemtime.wMonth << ".0" << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "чорні" << endl;
                    }
                    else
                    {
                        file << systemtime.wYear << "." << systemtime.wMonth << ".0" << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "чорні" << endl;
                    }
                }
                else
                {
                    if (systemtime.wMonth < 10)
                    {
                        file << systemtime.wYear << ".0" << systemtime.wMonth << "." << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "чорні" << endl;
                    }
                    else
                    {
                        file << systemtime.wYear << "." << systemtime.wMonth << "." << systemtime.wDay << ' ' << name1 << ' ' << name2 << ' ' << "чорні" << endl;
                    }
                }
                file.close();
                system("pause");
                break;
            }
        }
    } 
    void chess::mapgen() const
    {
        system("cls");
        cout << "   A  B  C  D  E  F  G  H " << endl;
        cout << "  ┌──┬──┬──┬──┬──┬──┬──┬──┐" << endl;
        for (int i  = 0; i < 8; i++)
        {
            cout << " " << 8 - i;
            cout << "│" << ChessMap[i][0] << "│" << ChessMap[i][1] << "│" << ChessMap[i][2] << "│" << ChessMap[i][3] << "│" << ChessMap[i][4] << "│" << ChessMap[i][5] << "│" << ChessMap[i][6] << "│" << ChessMap[i][7] << "│";
            cout << " " << 8 - i << endl;
            if (i == 7)
                break;
            cout << "  ├" << "──┼──┼──┼──┼──┼──┼──┼──" << "┤" << endl;
        }
        cout << "  └──┴──┴──┴──┴──┴──┴──┴──┘" << endl;
        cout << "   A  B  C  D  E  F  G  H " << endl;
    }
    void chess::whitemove()
    {
        cout << "Хід білих" << endl;
        cout << "Введіть букву та цифру\nзвідки ви хочете піти,\nа потім куди" << endl << ">>";
        do
        {
            beginmoveX = _getch();
        } while (!(beginmoveX >= 97 && beginmoveX <= 104));//let
        cout << (char)beginmoveX;
        beginmoveX = beginmoveX - 97;
        do
        {
            beginmoveY = _getch();
        } while (!(beginmoveY >= 49 && beginmoveY <= 56));//num
        beginmoveY = beginmoveY - 48;
        cout << beginmoveY;
        beginmoveY = 8 - beginmoveY;
        cout << "->";
        do
        {
            endmoveX = _getch();
        } while (!(endmoveX >= 97 && endmoveX <= 104));//let
        cout << (char)endmoveX;
        endmoveX = endmoveX - 97 ;
        do
        {
            endmoveY = _getch();
        } while (!(endmoveY >= 49 && endmoveY <= 56));//num
        endmoveY = endmoveY - 48;
        cout << endmoveY;
        endmoveY = 8 - endmoveY;
        if (whiteposible())
        {
            if (ChessMap[beginmoveY][beginmoveX] == whiterook)
            {
                if ((beginmoveX == 0) && (beginmoveY == 7))
                    whiterookleftmove = true;
                else if ((beginmoveX == 7) && (beginmoveY == 7))
                    whiterookrightmove = true;
            }
            if (ChessMap[beginmoveY][beginmoveX] == whiteking)
                whitekingmove = true;
            ChessMap[endmoveY][endmoveX] = ChessMap[beginmoveY][beginmoveX];
            ChessMap[beginmoveY][beginmoveX] = empty;
            oldbeginmoveX = beginmoveX, oldbeginmoveY = beginmoveY, oldendmoveX = endmoveX, oldendmoveY = endmoveY;
            can = true;
        }
        else
        {
            cout << " Неможливий хід!" << endl;
            Sleep(2000);
        }
    }
    void chess::blackmove()
    {
        cout << "Хід чорних" << endl;
        cout << "Введіть букву та цифру\nзвідки ви хочете піти,\nа потім куди" << endl << ">>";
        do
        {
            beginmoveX = _getch();
        } while (!(beginmoveX >= 97 && beginmoveX <= 104));//let
        cout << (char)beginmoveX;
        beginmoveX = beginmoveX - 97;
        do
        {
            beginmoveY = _getch();
        } while (!(beginmoveY >= 49 && beginmoveY <= 56));//num
        beginmoveY = beginmoveY - 48;
        cout << beginmoveY;
        beginmoveY = 8 - beginmoveY;
        cout << "->";
        do
        {
            endmoveX = _getch();
        } while (!(endmoveX >= 97 && endmoveX <= 104));//let
        cout << (char)endmoveX;
        endmoveX = endmoveX - 97;
        do
        {
            endmoveY = _getch();
        } while (!(endmoveY >= 49 && endmoveY <= 56));//num
        endmoveY = endmoveY - 48;
        cout << endmoveY;
        endmoveY = 8 - endmoveY;
        if (blackposible())
        {
            if (ChessMap[beginmoveY][beginmoveX] == blackrook)
            {
                if ((beginmoveX == 0) && (beginmoveY = 0))
                    blackrookleftmove = true;
                else if ((beginmoveX == 7) && (beginmoveY = 0))
                    blackrookrightmove = true;
            }
            if (ChessMap[beginmoveY][beginmoveX] == blackking)
                blackkingmove = true;
            ChessMap[endmoveY][endmoveX] = ChessMap[beginmoveY][beginmoveX];
            ChessMap[beginmoveY][beginmoveX] = empty;
            oldbeginmoveX = beginmoveX, oldbeginmoveY = beginmoveY, oldendmoveX = endmoveX, oldendmoveY = endmoveY;
            can = true;
        }
        else
        {
            cout << " Неможливий хід!" << endl;
            Sleep(2000);
        }
    }
    void chess::history()
    {
        system("cls");
        ifstream file("data.txt");
        if (!file.is_open())
        {
            cout << "Помилка відкриття";
            return;
        }
        int size = 0;
        string tempstr2;
        while (getline(file, tempstr2))
        {
            size++;
        }
        file.clear();//clear the state flags of a file stream
        file.seekg(0);//set the position of the get pointer(read pointer) in the file stream to the beginning
        vector<string> ptr(size);
        vector<string> timeptr(size);
        vector<string> name1ptr(size);
        vector<string> name2ptr(size);
        vector<string> whowinptr(size);
        for (int i = 0; i < size; i++)
        {
            size_t pos1;
            size_t pos2;
            getline(file, ptr[i]);
            pos1 = 0;
            pos2 = ptr[i].find(' ');
            timeptr[i] = ptr[i].substr(pos1, pos2 - pos1);
            pos1 = pos2 + 1;
            pos2 = ptr[i].find(' ', pos1);
            name1ptr[i] = ptr[i].substr(pos1, pos2 - pos1);
            pos1 = pos2 + 1;
            pos2 = ptr[i].find(' ', pos1);
            name2ptr[i] = ptr[i].substr(pos1, pos2 - pos1);
            pos1 = pos2 + 1;
            pos2 = ptr[i].find(' ', pos1);
            whowinptr[i] = ptr[i].substr(pos1, pos2 - pos1);
        }
        int n;
        do
        {
            system("cls");
            for (int i = 0; i < size; i++)
            {
               cout << "\nДата: " << timeptr[i] << " Білі фігури: " << name1ptr[i] << " Чорні фігури: " << name2ptr[i] << " Перемогли: " << whowinptr[i] << endl;
            }
            cout <<"\n1)Сортування за датою\n2)Пошук за ім'ям\n3)Вийти\n\n>>";
            n = _getch();
            switch (n)
            {
            case 49:
            {
                sort(timeptr.begin(), timeptr.end(), [](string a, string b) { //lambda function
                        return a > b; 
                    });
                break;
            }
            case 50:
            {
                string tempstr1;
                do
                {
                    system("cls");
                    cout << "\n1)Гравець за білих\n2)Гравець за чорних\n3)Вийти\n\n>>";
                    n = _getch();
                    switch (n)
                    {
                    case 49:
                        tempstr1 = {};
                        do
                        {
                            system("cls");
                            cout << "\n>>";
                            cout << tempstr1;
                            n = _getch();
                            if (n == 8 && !(tempstr1.empty()))
                            { 
                                tempstr1.pop_back();
                                continue;
                            }
                            if (n == 8 && tempstr1.empty())
                                continue;
                            if(n == 13)
                                continue;

                            cout <<(char)n<<endl;
                            tempstr1 += n;
                            for (int i = 0; i < size; i++)
                            {
                                tempstr2 = {};
                                for (int j = 0; j < name1ptr[i].length(); j++)
                                {
                                    tempstr2 += name1ptr[i][j];
                                    if (tempstr1 == tempstr2)
                                    {
                                        cout << "\n\nДата: " << timeptr[i] << " Білі фігури: " << name1ptr[i] << " Чорні фігури: " << name2ptr[i] << " Перемогли: " << whowinptr[i];
                                        break;
                                    }
                                }
                            }
                            cout << "\n\n";
                            system("pause");
                        } while (n != 27);
                        break;
                    case 50:
                        tempstr1 = {};
                        do
                        {
                            system("cls");
                            cout << "\n>>";
                            cout << tempstr1;
                            n = _getch();
                            if (n == 8 && !(tempstr1.empty()))
                            {
                                tempstr1.pop_back();
                                continue;
                            }
                            if (n == 8 && tempstr1.empty())
                                continue;
                            if (n == 13)
                                continue;

                            cout << (char)n << endl;
                            tempstr1 += n;
                            for (int i = 0; i < size; i++)
                            {
                                tempstr2 = {};
                                for (int j = 0; j < name2ptr[i].length(); j++)
                                {
                                    tempstr2 += name2ptr[i][j];
                                    if (tempstr1 == tempstr2)
                                    {
                                        cout << "\n\nДата: " << timeptr[i] << " Білі фігури: " << name1ptr[i] << " Чорні фігури: " << name2ptr[i] << " Перемогли: " << whowinptr[i];
                                        break;
                                    }
                                }
                            }
                            cout << "\n\n";
                            system("pause");
                        } while (n != 27);
                        break;
                    }
                } while (n != 51);
                break;
            }
            }
        } while (n != 51);
    }
    bool chess::WhiteKingExist()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (ChessMap[i][j] == whiteking)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool chess::BlackKingExist()
    {
        for (int i = 0 ;i < 8;i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (ChessMap[i][j] == blackking)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool chess::white(string figure)
    {
        if ((figure == whiteking) || (figure == whitequeen) || (figure == whiterook) || (figure == whitebishop) || (figure == whiteknight) || (figure == whitepawn))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool chess::black(string figure)
    {
        if ((figure == blackking) || (figure == blackqueen) || (figure == blackrook) || (figure == blackbishop) || (figure == blackknight) || (figure == blackpawn))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool chess::whiteposible()
    {
        if (beginmoveY == endmoveY && beginmoveX == endmoveX)
        {
            return false;
        }
        if (white(ChessMap[endmoveY][endmoveX]))
        {
            return false;
        }
        if (!white(ChessMap[beginmoveY][beginmoveX]))
        {
            return false;
        }
        if (ChessMap[beginmoveY][beginmoveX] == whitepawn)
        {
            if (beginmoveY == 6 && ChessMap[beginmoveY - 1][beginmoveX] == empty && ChessMap[beginmoveY - 2][beginmoveX] == empty && beginmoveY - 2 == endmoveY && beginmoveX == endmoveX)
            {
                return true;
            }
            if (ChessMap[beginmoveY - 1][beginmoveX] == empty && beginmoveY - 1 == endmoveY && beginmoveX == endmoveX)
            {
                if (beginmoveY == 1 && endmoveY == 0)
                {
                    int tempnum;
                    cout << "\n Виберіть фігуру:\n\n (1) " << whitequeen << " (2) " << whiterook << " (3) " << whitebishop << " (4) " << whiteknight << endl;
                    do
                    {
                        tempnum = _getch();
                    } while (!(tempnum >= 49 && tempnum <= 52));
                    tempnum = tempnum - 48;
                    switch (tempnum)
                    {
                    case 1:
                        ChessMap[beginmoveY][beginmoveX] = whitequeen;
                        return true;
                    case 2:
                        ChessMap[beginmoveY][beginmoveX] = whiterook;
                        return true;
                    case 3:
                        ChessMap[beginmoveY][beginmoveX] = whitebishop;
                        return true;
                    case 4:
                        ChessMap[beginmoveY][beginmoveX] = whiteknight;
                        return true;
                    }
                }
                return true;
            }
            if ((ChessMap[oldendmoveY][oldendmoveX] == blackpawn) && (beginmoveY - 1 == endmoveY && (beginmoveX - 1 == endmoveX || beginmoveX + 1 == endmoveX)) && (oldbeginmoveY + 2 == oldendmoveY) && ((oldendmoveX + 1 == beginmoveX) || (oldendmoveX - 1 == beginmoveX)))
            {
                ChessMap[oldendmoveY][oldendmoveX] = empty;
                return true;
            }
            if ((beginmoveY - 1 == endmoveY && (beginmoveX - 1 == endmoveX  || beginmoveX + 1 == endmoveX)) && black(ChessMap[endmoveY][endmoveX]))//check on attack move
            {
                if (beginmoveY == 1 && endmoveY == 0)
                {
                    int tempnum;
                    system("cls");
                    cout << "\n Виберіть фігуру:\n\n (1) " << whitequeen << " (2) " << whiterook << " (3) " << whitebishop << " (4) " << whiteknight << endl;
                    do
                    {
                        tempnum = _getch();
                    } while (!(tempnum >= 49 && tempnum <= 52));
                    tempnum = tempnum - 48;
                    switch (tempnum)
                    {
                    case 1:
                        ChessMap[beginmoveY][beginmoveX] = whitequeen;
                        return true;
                    case 2:
                        ChessMap[beginmoveY][beginmoveX] = whiterook;
                        return true;
                    case 3:
                        ChessMap[beginmoveY][beginmoveX] = whitebishop;
                        return true;
                    case 4:
                        ChessMap[beginmoveY][beginmoveX] = whiteknight;
                        return true;
                    }
                }
                return true;
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == whiteking)
        {
            if (!whitekingmove)
            {
                if ((!whiterookleftmove) && ((beginmoveX - 2) == endmoveX) && (ChessMap[beginmoveY][beginmoveX - 1] == empty) && (ChessMap[beginmoveY][beginmoveX - 2] == empty) && (ChessMap[beginmoveY][beginmoveX - 3] == empty))
                {
                    ChessMap[7][0] = empty;
                    ChessMap[7][3] = whiterook;
                    return true;
                }
                if ((!whiterookrightmove) && ((beginmoveX + 2) == endmoveX) && (ChessMap[beginmoveY][beginmoveX + 1] == empty) && (ChessMap[beginmoveY][beginmoveX + 2] == empty))
                {
                    ChessMap[7][7] = empty;
                    ChessMap[7][5] = whiterook;
                    return true;
                }
            }
            return abs(beginmoveY - endmoveY) <= 1 && abs(beginmoveX - endmoveX) <= 1;
        }
        if (ChessMap[beginmoveY][beginmoveX] == whitequeen)
        {
            if (beginmoveY == endmoveY || beginmoveX == endmoveX)//rook move
            {
                if (beginmoveX == endmoveX)//Y
                {
                    if (endmoveY < beginmoveY)//up
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY - i][beginmoveX] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //down
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY + i][beginmoveX] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }

                if (beginmoveY == endmoveY)//X
                {
                    if (endmoveX > beginmoveX)//right
                    {
                        for (int i = 1; i <= abs(beginmoveX - endmoveX); i++)
                        {
                            if (black(ChessMap[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY][beginmoveX + i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //left
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(ChessMap[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
            }
            else //bishop move
            {
                if (beginmoveY > endmoveY)//Y+ 
                {
                    if (beginmoveX < endmoveX)//X+
                    {
                        if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY - i][beginmoveX + i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //X-
                    {
                        if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY - i][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
                else//Y-
                {
                    if (beginmoveX < endmoveX)//X+
                    {
                        if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY + i][beginmoveX + i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //X-
                    {
                        if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY + i][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == whiterook)
        {
            if (beginmoveX == endmoveX)//Y
            {
                if (endmoveY < beginmoveY)//up
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY - i][beginmoveX] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else if(beginmoveY == endmoveY) //down
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY + i][beginmoveX] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }

            if (beginmoveY == endmoveY)//X
            {
                if (endmoveX > beginmoveX)//right
                {
                    for (int i = 1; i <= abs(beginmoveX - endmoveX); i++)
                    {
                        if (black(ChessMap[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY][beginmoveX + i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else //left
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(ChessMap[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == whitebishop)
        {
            if (beginmoveY > endmoveY)//Y+ 
            {
                if (beginmoveX < endmoveX)//X+
                {
                    if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                    {
                        return false;
                    }
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY - i][beginmoveX + i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else //X-
                {
                    if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                    {
                        return false;
                    }
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY + i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY - i][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
            else//Y-
            {
                if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                {
                    return false;
                }
                if (beginmoveX < endmoveX )//X+
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY + i][beginmoveX + i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else //X-
                {
                    if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                    {
                        return false;
                    }
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY + i][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == whiteknight)
        {
            if ((abs(endmoveY - beginmoveY) == 2 && abs(endmoveX - beginmoveX) == 1) || (abs(endmoveY - beginmoveY) == 1 && abs(endmoveX - beginmoveX) == 2)) 
            {
                return true;
            }
        }
        return false;
    }
    bool chess::blackposible()
    {
        if (beginmoveY == endmoveY && beginmoveX == endmoveX)
        {
            return false;
        }
        if (black(ChessMap[endmoveY][endmoveX]))
        {
            return false;
        }
        if (!black(ChessMap[beginmoveY][beginmoveX]))
        {
            return false;
        }
        if (ChessMap[beginmoveY][beginmoveX] == blackpawn)
        {
            if (beginmoveY == 1 && ChessMap[beginmoveY + 1][beginmoveX] == empty && ChessMap[beginmoveY + 2][beginmoveX] == empty && beginmoveY + 2 == endmoveY && beginmoveX == endmoveX)
            {
                return true;
            }
            if (ChessMap[beginmoveY + 1][beginmoveX] == empty && beginmoveY + 1 == endmoveY && beginmoveX == endmoveX)//move
            {
                if (beginmoveY == 6 && endmoveY == 7)
                {
                    int tempnum;
                    cout << "\n Виберіть фігуру:\n\n (1) " << blackqueen << " (2) " << blackrook << " (3) " << blackbishop << " (4) " << blackknight << endl;
                    do
                    {
                        tempnum = _getch();
                    } while (!(tempnum >= 49 && tempnum <= 52));
                    tempnum = tempnum - 48;
                    switch (tempnum)
                    {
                    case 1:
                        ChessMap[beginmoveY][beginmoveX] = blackqueen;
                        return true;
                    case 2:
                        ChessMap[beginmoveY][beginmoveX] = blackrook;
                        return true;
                    case 3:
                        ChessMap[beginmoveY][beginmoveX] = blackbishop;
                        return true;
                    case 4:
                        ChessMap[beginmoveY][beginmoveX] = blackknight;
                        return true;
                    }
                }
                return true;
            }
            if ((ChessMap[oldendmoveY][oldendmoveX] == whitepawn) && (beginmoveY + 1 == endmoveY && (beginmoveX - 1 == endmoveX || beginmoveX + 1 == endmoveX)) && (oldbeginmoveY - 2 == oldendmoveY) && ((oldendmoveX + 1 == beginmoveX) || (oldendmoveX - 1 == beginmoveX)))
            {
                ChessMap[oldendmoveY][oldendmoveX] = empty;
                return true;
            }
            if ((beginmoveY + 1 == endmoveY && (beginmoveX - 1 == endmoveX || beginmoveX + 1 == endmoveX)) && white(ChessMap[endmoveY][endmoveX]))//attack move
            {

                if (beginmoveY == 6 && endmoveY == 7)
                {
                    int tempnum;
                    system("cls");
                    cout << "\n Виберіть фігуру:\n\n (1) " << blackqueen << " (2) " << blackrook << " (3) " << blackbishop << " (4) " << blackknight << endl;
                    do
                    {
                        tempnum = _getch();
                    } while (!(tempnum >= 49 && tempnum <= 52));
                    tempnum = tempnum - 48;
                    switch (tempnum)
                    {
                    case 1:
                        ChessMap[beginmoveY][beginmoveX] = blackqueen;
                        return true;
                    case 2:
                        ChessMap[beginmoveY][beginmoveX] = blackrook;
                        return true;
                    case 3:
                        ChessMap[beginmoveY][beginmoveX] = blackbishop;
                        return true;
                    case 4:
                        ChessMap[beginmoveY][beginmoveX] = blackknight;
                        return true;
                    }
                }
                return true;
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == blackking)
        {
            if (!blackkingmove)
            {
                if ((!blackrookleftmove) && ((beginmoveX - 2) == endmoveX) && (ChessMap[beginmoveY][beginmoveX - 1] == empty) && (ChessMap[beginmoveY][beginmoveX - 2] == empty) && (ChessMap[beginmoveY][beginmoveX - 3] == empty))
                {
                    ChessMap[0][0] = empty;
                    ChessMap[0][3] = whiterook;
                    return true;
                }
                if ((!blackrookrightmove) && ((beginmoveX + 2) == endmoveX) && (ChessMap[beginmoveY][beginmoveX + 1] == empty) && (ChessMap[beginmoveY][beginmoveX + 2] == empty))
                {
                    ChessMap[0][7] = empty;
                    ChessMap[0][5] = whiterook;
                    return true;
                }
            }
            return abs(beginmoveY - endmoveY) <= 1 && abs(beginmoveX - endmoveX) <= 1;
        }
        if (ChessMap[beginmoveY][beginmoveX] == blackqueen)
        {
            if (beginmoveY == endmoveY || beginmoveX == endmoveX)//rook move
            {
                if (beginmoveX == endmoveX)//Y
                {
                    if (endmoveY < beginmoveY)//up
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY - i][beginmoveX] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //down
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY + i][beginmoveX] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }

                if (beginmoveY == endmoveY)//X
                {
                    if (endmoveX > beginmoveX)//right
                    {
                        for (int i = 1; i <= abs(beginmoveX - endmoveX); i++)
                        {
                            if (white(ChessMap[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY][beginmoveX + i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //left
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(ChessMap[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
            }
            else //bishop move
            {
                if (beginmoveY > endmoveY)//Y+ 
                {
                    if (beginmoveX < endmoveX)//X+
                    {
                        if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY - i][beginmoveX + i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //X-
                    {
                        if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY - i][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
                else//Y-
                {
                    if (beginmoveX < endmoveX)//X+
                    {
                        if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY + i][beginmoveX + i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                    else //X-
                    {
                        if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                        {
                            return false;
                        }
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(ChessMap[beginmoveY + i][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == blackrook)
        {
            if (beginmoveX == endmoveX)//Y
            {
                if (endmoveY < beginmoveY)//up
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY - i][beginmoveX] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else if (beginmoveY == endmoveY) //down
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY + i][beginmoveX] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }

            if (beginmoveY == endmoveY)//X
            {
                if (endmoveX > beginmoveX)//right
                {
                    for (int i = 1; i <= abs(beginmoveX - endmoveX); i++)
                    {
                        if (white(ChessMap[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY][beginmoveX + i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else //left
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(ChessMap[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == blackbishop)
        {
            if (beginmoveY > endmoveY)//Y+ 
            {
                if (beginmoveX < endmoveX)//X+
                {
                    if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                    {
                        return false;
                    }
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY - i][beginmoveX + i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else //X-
                {
                    if (!(endmoveY == beginmoveY - abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                    {
                        return false;
                    }
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(ChessMap[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY - i][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
            else//Y-
            {
                if (beginmoveX < endmoveX)//X+
                {
                    if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX + abs(beginmoveY - endmoveY)))
                    {
                        return false;
                    }
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY + i][beginmoveX + i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
                else //X-
                {
                    if (!(endmoveY == beginmoveY + abs(beginmoveY - endmoveY) && endmoveX == beginmoveX - abs(beginmoveY - endmoveY)))
                    {
                        return false;
                    }
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(ChessMap[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(ChessMap[beginmoveY + i][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (ChessMap[beginmoveY][beginmoveX] == blackknight)
        {
            if ((abs(endmoveY - beginmoveY) == 2 && abs(endmoveX - beginmoveX) == 1) || (abs(endmoveY - beginmoveY) == 1 && abs(endmoveX - beginmoveX) == 2))
            {
                return true;
            }
        }
        return false;
    }
