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
        //int a,b;
        //while (true)
        //{
        //    a = _getch();
        //    b = _getch();
        //    cout << (int)a <<" "<< b << endl;
        //}
        menu();
    }
    void chess::menu()
    {
        int n;
        do
        {
            system("cls");
            cout << "\n Шахи\n\n1)Грати\n2)Істрія\n3)Вийти з гри\n\n>>";
            n = _getch();
            switch (n)
            {
            case 49:
            {
                game(ChessMap);
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
    void chess::game(string(&map)[8][8])
    {
        bool can;
        string name1, name2, time;
        system("cls");
        cout << "Введіть ім'я_прізвище першого гравця (білі фігури)\n>>";
        getline(cin, name1);
        system("cls");
        cout << "Введіть ім'я_прізвище другого гравця  (чорні фігури)\n>>";
        getline(cin, name2);
        system("cls");
        cout << "Введіть дату День.Місяць.Рік\n>>";
        getline(cin, time);
        while (true)
        {
            can = false;
            do {
            mapgen(map);
            whitemove(map,can);
            } while (!can);
            if (!BlackKingExist(map))
            {
                system("cls");
                cout << "\n\n\twhite win\n\n" << endl;
                ofstream file("data.txt", fstream::app);
                if (file.is_open())
                {
                    file << time << ' ' << name1 << ' ' << name2 << ' ' << "білі" << endl;
                }
                else
                {
                    ofstream file("data.txt");
                    file << time << ' ' << name1 << ' ' << name2 << ' ' << "білі" << endl;
                }
                system("pause");
                break;
            }
            can = false;
            do {
            mapgen(map);
            blackmove(map, can);
            } while (!can);
            if (!WhiteKingExist(map))
            {
                system("cls");
                cout << "\n\n\tblack win\n\n" << endl;
                ofstream file("data.txt", fstream::app); 
                if (file.is_open())
                {
                    file << time << ' ' << name1 << ' ' << name2 << ' ' << "чорні" << endl;
                }
                else
                {
                    ofstream file("data.txt");
                    file << time << ' ' << name1 << ' ' << name2 << ' ' << "чорні" << endl;
                }
                file.close();
                system("pause");
                break;
            }
        }
    }
    void chess::mapgen(string(&map)[8][8])
    {
        system("cls");
        cout << "   A  B  C  D  E  F  G  H " << endl;
        cout << "  ┌──┬──┬──┬──┬──┬──┬──┬──┐" << endl;
        for (int i  = 0; i < 8; i++)
        {
            cout << " " << 8 - i;
            cout << "│" << map[i][0] << "│" << map[i][1] << "│" << map[i][2] << "│" << map[i][3] << "│" << map[i][4] << "│" << map[i][5] << "│" << map[i][6] << "│" << map[i][7] << "│";
            cout << " " << 8 - i << endl;
            if (i == 7)
                break;
            cout << "  ├" << "──┼──┼──┼──┼──┼──┼──┼──" << "┤" << endl;
        }
        cout << "  └──┴──┴──┴──┴──┴──┴──┴──┘" << endl;
        cout << "   A  B  C  D  E  F  G  H " << endl;
    }
    void chess::whitemove(string(&map)[8][8], bool& can)
    {
        int beginmoveX, beginmoveY, endmoveX, endmoveY;
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
        if (whiteposible(map, beginmoveY, beginmoveX, endmoveY, endmoveX))
        {
            can = true;
            map[endmoveY][endmoveX] = map[beginmoveY][beginmoveX];
            map[beginmoveY][beginmoveX] = empty;
        }
        else
        {
            can = false;
            cout << " Неможливий хід!" << endl;
            Sleep(2000);
        }
    }
    void chess::blackmove(string(&map)[8][8], bool& can)
    {
        int beginmoveX, beginmoveY, endmoveX, endmoveY;
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
        if (blackposible(map, beginmoveY, beginmoveX, endmoveY, endmoveX))
        {
            can = true;
            map[endmoveY][endmoveX] = map[beginmoveY][beginmoveX];
            map[beginmoveY][beginmoveX] = empty;
        }
        else
        {
            can = false;
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
        file.clear();
        file.seekg(0);
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
    bool chess::WhiteKingExist(string map[8][8])
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (map[i][j] == whiteking)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool chess::BlackKingExist(string map[8][8])
    {
        for (int i = 0 ;i < 8;i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (map[i][j] == blackking)
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
    bool chess::whiteposible(string(&map)[8][8], int beginmoveY, int beginmoveX, int endmoveY, int endmoveX)
    {
        if (beginmoveY == endmoveY && beginmoveX == endmoveX)
        {
            return false;
        }
        if (white(map[endmoveY][endmoveX]))
        {
            return false;
        }
        if (!white(map[beginmoveY][beginmoveX]))
        {
            return false;
        }
        if (map[beginmoveY][beginmoveX] == whitepawn)
        {
            if (beginmoveY == 6 && map[beginmoveY - 1][beginmoveX] == empty && map[beginmoveY - 2][beginmoveX] == empty && beginmoveY - 2 == endmoveY && beginmoveX == endmoveX)
            {
                return true;
            }
            if (map[beginmoveY - 1][beginmoveX] == empty && beginmoveY - 1 == endmoveY && beginmoveX == endmoveX)
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
                        map[beginmoveY][beginmoveX] = whitequeen;
                        return true;
                    case 2:
                        map[beginmoveY][beginmoveX] = whiterook;
                        return true;
                    case 3:
                        map[beginmoveY][beginmoveX] = whitebishop;
                        return true;
                    case 4:
                        map[beginmoveY][beginmoveX] = whiteknight;
                        return true;
                    }
                }
                return true;
            }
            if ((beginmoveY - 1 == endmoveY && (beginmoveX - 1 == endmoveX  || beginmoveX + 1 == endmoveX)) && black(map[endmoveY][endmoveX]))//check on attack move
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
                        map[beginmoveY][beginmoveX] = whitequeen;
                        return true;
                    case 2:
                        map[beginmoveY][beginmoveX] = whiterook;
                        return true;
                    case 3:
                        map[beginmoveY][beginmoveX] = whitebishop;
                        return true;
                    case 4:
                        map[beginmoveY][beginmoveX] = whiteknight;
                        return true;
                    }
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == whiteking)
        {
            return abs(beginmoveY - endmoveY) <= 1 && abs(beginmoveX - endmoveX) <= 1;
        }
        if (map[beginmoveY][beginmoveX] == whitequeen)
        {
            if (beginmoveY == endmoveY || beginmoveX == endmoveX)//rook move
            {
                if (beginmoveX == endmoveX)//Y
                {
                    if (endmoveY < beginmoveY)//up
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (black(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY - i][beginmoveX] == empty))
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
                            if (black(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY + i][beginmoveX] == empty))
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
                            if (black(map[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY][beginmoveX + i] == empty))
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
                            if (black(map[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY][beginmoveX - i] == empty))
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
                            if (black(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY - i][beginmoveX + i] == empty))
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
                            if (black(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY - i][beginmoveX - i] == empty))
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
                            if (black(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY + i][beginmoveX + i] == empty))
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
                            if (black(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY + i][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == whiterook)
        {
            if (beginmoveX == endmoveX)//Y
            {
                if (endmoveY < beginmoveY)//up
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (black(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY - i][beginmoveX] == empty))
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
                        if (black(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY + i][beginmoveX] == empty))
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
                        if (black(map[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY][beginmoveX + i] == empty))
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
                        if (black(map[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == whitebishop)
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
                        if (black(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY - i][beginmoveX + i] == empty))
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
                        if (black(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY + i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY - i][beginmoveX - i] == empty))
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
                        if (black(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY + i][beginmoveX + i] == empty))
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
                        if (black(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY + i][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == whiteknight)
        {
            if ((abs(endmoveY - beginmoveY) == 2 && abs(endmoveX - beginmoveX) == 1) || (abs(endmoveY - beginmoveY) == 1 && abs(endmoveX - beginmoveX) == 2)) 
            {
                return true;
            }
        }
        return false;
    }
    bool chess::blackposible(string(&map)[8][8], int beginmoveY, int beginmoveX, int endmoveY, int endmoveX)
    {
        if (beginmoveY == endmoveY && beginmoveX == endmoveX)
        {
            return false;
        }
        if (black(map[endmoveY][endmoveX]))
        {
            return false;
        }
        if (!black(map[beginmoveY][beginmoveX]))
        {
            return false;
        }
        if (map[beginmoveY][beginmoveX] == blackpawn)
        {
            if (beginmoveY == 1 && map[beginmoveY + 1][beginmoveX] == empty && map[beginmoveY + 2][beginmoveX] == empty && beginmoveY + 2 == endmoveY && beginmoveX == endmoveX)
            {
                return true;
            }
            if (map[beginmoveY + 1][beginmoveX] == empty && beginmoveY + 1 == endmoveY && beginmoveX == endmoveX)//move
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
                        map[beginmoveY][beginmoveX] = blackqueen;
                        return true;
                    case 2:
                        map[beginmoveY][beginmoveX] = blackrook;
                        return true;
                    case 3:
                        map[beginmoveY][beginmoveX] = blackbishop;
                        return true;
                    case 4:
                        map[beginmoveY][beginmoveX] = blackknight;
                        return true;
                    }
                }
                return true;
            }
            if ((beginmoveY + 1 == endmoveY && (beginmoveX - 1 == endmoveX || beginmoveX + 1 == endmoveX)) && black(map[endmoveY][endmoveX]))//attack move
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
                        map[beginmoveY][beginmoveX] = blackqueen;
                        return true;
                    case 2:
                        map[beginmoveY][beginmoveX] = blackrook;
                        return true;
                    case 3:
                        map[beginmoveY][beginmoveX] = blackbishop;
                        return true;
                    case 4:
                        map[beginmoveY][beginmoveX] = blackknight;
                        return true;
                    }
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == blackking)
        {
            return abs(beginmoveY - endmoveY) <= 1 && abs(beginmoveX - endmoveX) <= 1;
        }
        if (map[beginmoveY][beginmoveX] == blackqueen)
        {
            if (beginmoveY == endmoveY || beginmoveX == endmoveX)//rook move
            {
                if (beginmoveX == endmoveX)//Y
                {
                    if (endmoveY < beginmoveY)//up
                    {
                        for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                        {
                            if (white(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY - i][beginmoveX] == empty))
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
                            if (white(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY + i][beginmoveX] == empty))
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
                            if (white(map[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY][beginmoveX + i] == empty))
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
                            if (white(map[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY][beginmoveX - i] == empty))
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
                            if (white(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY - i][beginmoveX + i] == empty))
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
                            if (white(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY - i][beginmoveX - i] == empty))
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
                            if (white(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY + i][beginmoveX + i] == empty))
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
                            if (white(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                            {
                                return true;
                            }
                            if (!(map[beginmoveY + i][beginmoveX - i] == empty))
                            {
                                return false;
                            }
                        }
                        return true;
                    }
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == blackrook)
        {
            if (beginmoveX == endmoveX)//Y
            {
                if (endmoveY < beginmoveY)//up
                {
                    for (int i = 1; i <= abs(beginmoveY - endmoveY); i++)
                    {
                        if (white(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY - abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY - i][beginmoveX] == empty))
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
                        if (white(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX]) && (beginmoveY + abs(beginmoveY - endmoveY)) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY + i][beginmoveX] == empty))
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
                        if (white(map[beginmoveY][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY][beginmoveX + i] == empty))
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
                        if (white(map[beginmoveY][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX - abs(beginmoveX - endmoveX)) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == blackbishop)
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
                        if (white(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY - i][beginmoveX + i] == empty))
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
                        if (white(map[beginmoveY - abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveY - i) == endmoveY)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY - i][beginmoveX - i] == empty))
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
                        if (white(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX + abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY + i][beginmoveX + i] == empty))
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
                        if (white(map[beginmoveY + abs(beginmoveY - endmoveY)][beginmoveX - abs(beginmoveX - endmoveX)]) && (beginmoveX + i) == endmoveX)
                        {
                            return true;
                        }
                        if (!(map[beginmoveY + i][beginmoveX - i] == empty))
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        if (map[beginmoveY][beginmoveX] == blackknight)
        {
            if ((abs(endmoveY - beginmoveY) == 2 && abs(endmoveX - beginmoveX) == 1) || (abs(endmoveY - beginmoveY) == 1 && abs(endmoveX - beginmoveX) == 2))
            {
                return true;
            }
        }
        return false;
    }
