#include "tmenu.h"
#include "tmonitor.h"
#include "tlist.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip> //setw
#include <conio.h>
#include <stdio.h>
#include <cstring>

#include <ctime>

using namespace std;

//  SECONDARY FUNCTIONS
//считает кол-во строк в файле
int str_Amount(char s[30])
{
    ifstream test(s);
    string str;
    int AMN = 0;

    while (getline (test, str))
        AMN++;
    test.close();
    return AMN;
}

//чтение данных из текстового файла в двухсвязный список
void ReadData(TList<TMonitor> *tempList)
{
    setlocale(LC_CTYPE, "Russian");
    char s[30] = "monitorcopy.db";
    int tempAmountOfMonitors = str_Amount(s);

    TMonitor rMonitor;//временный объект
    TMonitor::TResolution _resolution{0, 0};
    ifstream fl("monitorcopy.db", ifstream::in); //инициализирует переменную fl на чтение из неё

    string word; //временная строка(одно слово) для чтения
    bool b_word = false;
    float f_word = 0;
    int i_word = 0;
    int i = 0;

    //читает строку(слово) до ";" и сразу преобразует в необходимый тип
    while(i < tempAmountOfMonitors)
    {
        getline(fl, word, ';'); word.erase(0, 1); rMonitor.setModel(word); //erase кроме 1-го
        getline(fl, word, ';'); rMonitor.setMatrixType(word);
        getline(fl, word, ':'); i_word = stoi(word); _resolution.height = i_word;
        getline(fl, word, ';'); i_word = stoi(word); _resolution.widht = i_word;
            rMonitor.setResolution(_resolution);
        getline(fl, word, ';'); i_word = stoi(word); rMonitor.setDiagonal(i_word);
        getline(fl, word, ';'); i_word = stoi(word); rMonitor.setFrameRate(i_word);
        getline(fl, word, ';'); f_word = stof(word); rMonitor.setWeight(f_word);
        getline(fl, word, ';'); b_word = stoi(word); rMonitor.setLoudspeakers(b_word);
        i++;
        tempList->push_back(rMonitor);
    }
    fl.close();
}

//Вывод данных на экран(консоль) из списка
void TMenu::showData(TList<TMonitor> tempList)
{
    system("cls");
    ifstream fin("monitorcopy.db");
    int showMode = 0;
    if (tempList.getSize()<1)//fin.peek() == EOF)
    {
        cout << "Перед выводом данных необходимо открыть файл (меню - 1)." << endl;
        system("pause");
        fin.close();
        return;
    }
    cout << "Для вывода определённой записи введите её номер (все записи - 0)" << endl;
    cin >> showMode;
    int startRange = showMode - 1;
    if (showMode == 0)
    {
        showMode = tempList.getSize();
        startRange = 0;
    }
    cout << " №   "
         << "Модель\t" //string
         << "Тип матрицы\t" //string
         << "Разрешение   " //struct TResolution
         << "Диагональ   " //int
         << "Част. кадр.   " //int
         << "Вес   " //float
         << "Колонки\t" //bool
         << endl;
    cout << "==========================================================================================" << endl;
    TMonitor::TResolution _resolution;
    for (int i = startRange; i < showMode; i++)
    {
      cout << setw(2) << right << i+1 << "   "
           << setw(12) << left << tempList[i].getModel()
           << setw(16) << left << tempList[i].getMatrixType();
               _resolution = tempList[i].getResolution();
      cout << setw(4)  << left << _resolution.height
           << ":" << setw(10)  << left << _resolution.widht
           << setw(12) << left << tempList[i].getDiagonal()
           << setw(11) << left << tempList[i].getFrameRate()
           << setw(7) << left << tempList[i].getWeight()
           << setw(10) << left << boolalpha << tempList[i].getLoudspeakers()
           << endl;
    }
    cout << endl;
    system("pause");
}


//  MENU FUNCTIONS

TMenu::TMenu()
{

}

//Вывод пунктов меню на экран (без интерактивного интерфейса)
int TMenu::showMainMenu(int &button) const
{
    setlocale (LC_ALL, "Russian");
    cout << " 1) Открыть файл \n"
         << " 2) Вывести данные на экран\n"
         << " 3) Добавить запись \n"
         << " 4) Редактировать запись \n"
         << " 5) Удалить запись \n"
         << " 6) Сохранить файл \n"
         << " 7) Вывести данные в файл\n"
         << " 8) О программе \n"
         << " 9) Выход \n"
         << endl;
    cout << "Введите номер интересующего пункта: ";
    cin >> button;
    cout << endl;
    return button;
}

//Создание копии файла с исходными данными (все изменения до сохранения находятся только в ней)
void TMenu::openFile(TList<TMonitor>*_tempList, bool *isOpen) const
{
   if (*isOpen)
   {
       cout << "Файл уже открыт. Повторное открытие не требуется." << endl;
       system("pause");
       return;
   }
    setlocale(LC_CTYPE, "Russian");
    ifstream fin("monitor.db");
    if (fin)
    {
        ofstream fout("monitorcopy.db");
        fout << fin.rdbuf();
        fout.close();
        fin.close();
    }

    ReadData(_tempList);
    cout << "Файл monitor.db открыт..." << endl;
    *isOpen = true;
    system("pause");
}

//Добавление данных в список(пользовательская часть)
void TMenu::addData(TList<TMonitor> *tempList) const
{
    TMonitor rMonitor;
    TMonitor::TResolution _resolution{0, 0};

    string word(""); //временная строка(одно слово) для чтения
    bool b_word = false;
    float f_word = 0;
    int i_word = 0;
    //const string n("\n");
    cout << "Вернуться в меню - 0/ Продолжить - 1 " << endl;
        cin >> i_word;
        if (i_word == 0)
        {
            return;
        }
    cout << "Модель добавляемого элемента(LG_32): ";
        cin >> word; rMonitor.setModel(word); cout << flush;
    cout << "Тип матрицы добавляемого элемента(OLED): ";
        cin >> word; rMonitor.setMatrixType(word); cout << flush;
    cout << "Разрешение экрана добавляемого элемента:\n";
        cout << "\t(высота): ";
        cin >> i_word; _resolution.height = i_word; cout << flush;
        cout << "\t(ширина): ";
        cin >> i_word; _resolution.widht = i_word; cout << flush;
    rMonitor.setResolution(_resolution);
    cout << "Диагональ добавляемого элемента(27): ";
        cin >> i_word; rMonitor.setDiagonal(i_word); cout << flush;
    cout << "Частота кадров добавляемого элемента(60): ";
        cin >> i_word; rMonitor.setFrameRate(i_word); cout << flush;
    cout << "Вес добавляемого элемента(3.1): ";
        cin >> f_word; rMonitor.setWeight(f_word); cout << flush;
    cout << "Наличие колонок добавляемого элемента (1-есть/0-нет): ";
        cin >> b_word; rMonitor.setLoudspeakers(b_word); cout << endl;

        tempList->push_back(rMonitor);
}

//Редактирование данных(пользовательская часть)
void TMenu::editData(TList<TMonitor> *tempList)
{
    TMonitor rMonitor;
    TMonitor::TResolution _resolution{0, 0};

    string word(""); //временная строка(одно слово) для чтения
    bool b_word = false;
    float f_word = 0;
    int i_word = 0
      , number = 0;

    this->showData(*tempList);
    cout << "Введите номер редактируемой записи (0-меню): ";
    cin >> number; cout << endl;
    if (number == 0)
    {
        return;
    }
    //number = _getch();

    cout << "Модель элемента(LG_32): ";
        cin >> word; rMonitor.setModel(word); cout << flush;
    cout << "Тип матрицы элемента(OLED): ";
        cin >> word; rMonitor.setMatrixType(word); cout << flush;
    cout << "Разрешение экрана элемента:\n";
        cout << "\t(высота): ";
        cin >> i_word; _resolution.height = i_word;
        cout << "\t(ширина): ";
        cin >> i_word; _resolution.widht = i_word; cout << flush;
    rMonitor.setResolution(_resolution);
    cout << "Диагональ элемента(27): ";
        cin >> i_word; rMonitor.setDiagonal(i_word); cout << flush;
    cout << "Частота кадров элемента(60): ";
        cin >> i_word; rMonitor.setFrameRate(i_word); cout << flush;
    cout << "Вес элемента(3.1): ";
        cin >> f_word; rMonitor.setWeight(f_word); cout << flush;
    cout << "Наличие колонок элемента (1-есть/0-нет): ";
        cin >> b_word; rMonitor.setLoudspeakers(b_word); cout << endl;

        int num = tempList->edit_node(rMonitor, --number);
        cout << "Элемент " << ++num << " отредактирован." << endl;
        system("pause");
}

//Удаление данных в список(пользовательская часть)
void TMenu::deleteData(TList<TMonitor> *tempList) const
{
    int deleteNumber = 0
      , num = 0;
    cout << "Введите номер удаяемой записи из списка(1-...)"
         << endl;
    cin >> deleteNumber;
        num = tempList->pop_indexNode(--deleteNumber);
        if (num == -1)
        {
            cout << "ОШИБКА: Запись не существует" << endl;
        }
        else
    cout << "Запись " << ++num << " удалена." << endl;
    system("pause");
}

//Перезапись исходного файла данными копии
void TMenu::saveData() const
{
    setlocale(LC_CTYPE, "Russian");
    ifstream fin("monitorcopy.db");
    if (fin)
    {
        ofstream fout("monitor.db");
        fout << fin.rdbuf();
        fout.close();
        fin.close();
    }

    cout << "Изменения в файле monitor.db сохранены..." << endl;
    system("pause");
}

void TMenu::aboutProgramm() const
{
    system("cls");
    cout << "\n                   *О ПРОГРАММЕ* \n"
         << "   []============================================[] \n"
         << "   || Описание: Программа обрабатывает           || \n"
         << "   || информацию о характеристиках ПК мониторов. || \n"
         << "   || Язык разработки: C++                       || \n"
         << "   || ВУЗ: МГСУ                                  || \n"
         << "   || Автор: Максим Морозов                      || \n"
         << "   ||           10/02/2021                       || \n"
         << "   []============================================[]"
         << endl;
    _getch();
}

//Вывод данных в файл типа txt
void TMenu::outputFile(TList<TMonitor> tempList) const
{
    system("cls");
    ifstream fin("monitorcopy.db");
    if (fin.peek() == EOF)
    {
        cout << "Перед выводом данных необходимо открыть файл (меню - 1)." << endl;
        system("pause");
        fin.close();
        return;
    }
    string nameOfFile("");
    cout << "   ВЫВОД В ФАЙЛ    \n"
         << "===================\n"
         << "Введите название файла (без формата): "
         << flush;
    cin >> nameOfFile;
    nameOfFile += ".txt";
    ofstream fout(nameOfFile, ios_base::app);
    if (fout)
    {
        fout << " №   "
             << "Модель\t" //string
             << "Тип матрицы\t" //string
             << "Разрешение   " //struct TResolution
             << "Диагональ   " //int
             << "Част. кадр.   " //int
             << "Вес   " //float
             << "Колонки\t" //bool
             << endl;
        fout << "==========================================================================================" << endl;
        TMonitor::TResolution _resolution;
        for (int i = 0; i < tempList.getSize(); i++)
        {
          fout << setw(2) << right << i+1 << "   "
               << setw(12) << left << tempList[i].getModel()
               << setw(16) << left << tempList[i].getMatrixType();
                   _resolution = tempList[i].getResolution();
          fout << setw(4)  << left << _resolution.height
               << ":" << setw(10)  << left << _resolution.widht
               << setw(12) << left << tempList[i].getDiagonal()
               << setw(11) << left << tempList[i].getFrameRate()
               << setw(7) << left << tempList[i].getWeight()
               << setw(10) << left << boolalpha << tempList[i].getLoudspeakers()
               << endl;
        }
    }
    else
    {
        cout << "Файл с таким названием создать нельзя.\n"
                "(Попробуйте сменить название)" << endl;
        system("pause");
        return;
    }
fout.close();
cout << "Файл " << nameOfFile << " создан." << endl;
system("pause");
}

int TMenu::exitProgram(bool &check)
{
check = false;
return check;
}
