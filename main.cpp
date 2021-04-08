//#include <QCoreApplication>
#include "tmenu.h"
#include "tlist.h"
#include <iostream>
#include <cstring>
#include <windows.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main()
{
    setlocale(LC_CTYPE, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    TList<TMonitor> _list;
    TMenu _menu;
    int button = _menu.button;
    bool check = true
       , isOpen = false;
    while (check == true)
    {
        system("cls");
        _menu.showMainMenu(button);
        switch (button)
        {
        case 1: _menu.openFile(&_list, &isOpen); break;
        case 2: _menu.showData(_list); break;
        case 3: _menu.addData(&_list); break;
        case 4: _menu.editData(&_list); break;
        case 5: _menu.deleteData(&_list); break;
        case 6: _menu.saveData(); break;
        case 7: _menu.outputFile(_list); break;
        case 8: _menu.aboutProgramm(); break;
        case 9: _menu.exitProgram(check); break;
        default:
            cerr << "Ошибка: такого пункта нет" << endl;
            break;
        //return a.exec();
        }
    }
    return 0;
}
