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
//������� ���-�� ����� � �����
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

//������ ������ �� ���������� ����� � ����������� ������
void ReadData(TList<TMonitor> *tempList)
{
    setlocale(LC_CTYPE, "Russian");
    char s[30] = "monitorcopy.db";
    int tempAmountOfMonitors = str_Amount(s);

    TMonitor rMonitor;//��������� ������
    TMonitor::TResolution _resolution{0, 0};
    ifstream fl("monitorcopy.db", ifstream::in); //�������������� ���������� fl �� ������ �� ��

    string word; //��������� ������(���� �����) ��� ������
    bool b_word = false;
    float f_word = 0;
    int i_word = 0;
    int i = 0;

    //������ ������(�����) �� ";" � ����� ����������� � ����������� ���
    while(i < tempAmountOfMonitors)
    {
        getline(fl, word, ';'); word.erase(0, 1); rMonitor.setModel(word); //erase ����� 1-��
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

//����� ������ �� �����(�������) �� ������
void TMenu::showData(TList<TMonitor> tempList)
{
    system("cls");
    ifstream fin("monitorcopy.db");
    int showMode = 0;
    if (tempList.getSize()<1)//fin.peek() == EOF)
    {
        cout << "����� ������� ������ ���������� ������� ���� (���� - 1)." << endl;
        system("pause");
        fin.close();
        return;
    }
    cout << "��� ������ ����������� ������ ������� � ����� (��� ������ - 0)" << endl;
    cin >> showMode;
    int startRange = showMode - 1;
    if (showMode == 0)
    {
        showMode = tempList.getSize();
        startRange = 0;
    }
    cout << " �   "
         << "������\t" //string
         << "��� �������\t" //string
         << "����������   " //struct TResolution
         << "���������   " //int
         << "����. ����.   " //int
         << "���   " //float
         << "�������\t" //bool
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

//����� ������� ���� �� ����� (��� �������������� ����������)
int TMenu::showMainMenu(int &button) const
{
    setlocale (LC_ALL, "Russian");
    cout << " 1) ������� ���� \n"
         << " 2) ������� ������ �� �����\n"
         << " 3) �������� ������ \n"
         << " 4) ������������� ������ \n"
         << " 5) ������� ������ \n"
         << " 6) ��������� ���� \n"
         << " 7) ������� ������ � ����\n"
         << " 8) � ��������� \n"
         << " 9) ����� \n"
         << endl;
    cout << "������� ����� ������������� ������: ";
    cin >> button;
    cout << endl;
    return button;
}

//�������� ����� ����� � ��������� ������� (��� ��������� �� ���������� ��������� ������ � ���)
void TMenu::openFile(TList<TMonitor>*_tempList, bool *isOpen) const
{
   if (*isOpen)
   {
       cout << "���� ��� ������. ��������� �������� �� ���������." << endl;
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
    cout << "���� monitor.db ������..." << endl;
    *isOpen = true;
    system("pause");
}

//���������� ������ � ������(���������������� �����)
void TMenu::addData(TList<TMonitor> *tempList) const
{
    TMonitor rMonitor;
    TMonitor::TResolution _resolution{0, 0};

    string word(""); //��������� ������(���� �����) ��� ������
    bool b_word = false;
    float f_word = 0;
    int i_word = 0;
    //const string n("\n");
    cout << "��������� � ���� - 0/ ���������� - 1 " << endl;
        cin >> i_word;
        if (i_word == 0)
        {
            return;
        }
    cout << "������ ������������ ��������(LG_32): ";
        cin >> word; rMonitor.setModel(word); cout << flush;
    cout << "��� ������� ������������ ��������(OLED): ";
        cin >> word; rMonitor.setMatrixType(word); cout << flush;
    cout << "���������� ������ ������������ ��������:\n";
        cout << "\t(������): ";
        cin >> i_word; _resolution.height = i_word; cout << flush;
        cout << "\t(������): ";
        cin >> i_word; _resolution.widht = i_word; cout << flush;
    rMonitor.setResolution(_resolution);
    cout << "��������� ������������ ��������(27): ";
        cin >> i_word; rMonitor.setDiagonal(i_word); cout << flush;
    cout << "������� ������ ������������ ��������(60): ";
        cin >> i_word; rMonitor.setFrameRate(i_word); cout << flush;
    cout << "��� ������������ ��������(3.1): ";
        cin >> f_word; rMonitor.setWeight(f_word); cout << flush;
    cout << "������� ������� ������������ �������� (1-����/0-���): ";
        cin >> b_word; rMonitor.setLoudspeakers(b_word); cout << endl;

        tempList->push_back(rMonitor);
}

//�������������� ������(���������������� �����)
void TMenu::editData(TList<TMonitor> *tempList)
{
    TMonitor rMonitor;
    TMonitor::TResolution _resolution{0, 0};

    string word(""); //��������� ������(���� �����) ��� ������
    bool b_word = false;
    float f_word = 0;
    int i_word = 0
      , number = 0;

    this->showData(*tempList);
    cout << "������� ����� ������������� ������ (0-����): ";
    cin >> number; cout << endl;
    if (number == 0)
    {
        return;
    }
    //number = _getch();

    cout << "������ ��������(LG_32): ";
        cin >> word; rMonitor.setModel(word); cout << flush;
    cout << "��� ������� ��������(OLED): ";
        cin >> word; rMonitor.setMatrixType(word); cout << flush;
    cout << "���������� ������ ��������:\n";
        cout << "\t(������): ";
        cin >> i_word; _resolution.height = i_word;
        cout << "\t(������): ";
        cin >> i_word; _resolution.widht = i_word; cout << flush;
    rMonitor.setResolution(_resolution);
    cout << "��������� ��������(27): ";
        cin >> i_word; rMonitor.setDiagonal(i_word); cout << flush;
    cout << "������� ������ ��������(60): ";
        cin >> i_word; rMonitor.setFrameRate(i_word); cout << flush;
    cout << "��� ��������(3.1): ";
        cin >> f_word; rMonitor.setWeight(f_word); cout << flush;
    cout << "������� ������� �������� (1-����/0-���): ";
        cin >> b_word; rMonitor.setLoudspeakers(b_word); cout << endl;

        int num = tempList->edit_node(rMonitor, --number);
        cout << "������� " << ++num << " ��������������." << endl;
        system("pause");
}

//�������� ������ � ������(���������������� �����)
void TMenu::deleteData(TList<TMonitor> *tempList) const
{
    int deleteNumber = 0
      , num = 0;
    cout << "������� ����� �������� ������ �� ������(1-...)"
         << endl;
    cin >> deleteNumber;
        num = tempList->pop_indexNode(--deleteNumber);
        if (num == -1)
        {
            cout << "������: ������ �� ����������" << endl;
        }
        else
    cout << "������ " << ++num << " �������." << endl;
    system("pause");
}

//���������� ��������� ����� ������� �����
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

    cout << "��������� � ����� monitor.db ���������..." << endl;
    system("pause");
}

void TMenu::aboutProgramm() const
{
    system("cls");
    cout << "\n                   *� ���������* \n"
         << "   []============================================[] \n"
         << "   || ��������: ��������� ������������           || \n"
         << "   || ���������� � ��������������� �� ���������. || \n"
         << "   || ���� ����������: C++                       || \n"
         << "   || ���: ����                                  || \n"
         << "   || �����: ������ �������                      || \n"
         << "   ||           10/02/2021                       || \n"
         << "   []============================================[]"
         << endl;
    _getch();
}

//����� ������ � ���� ���� txt
void TMenu::outputFile(TList<TMonitor> tempList) const
{
    system("cls");
    ifstream fin("monitorcopy.db");
    if (fin.peek() == EOF)
    {
        cout << "����� ������� ������ ���������� ������� ���� (���� - 1)." << endl;
        system("pause");
        fin.close();
        return;
    }
    string nameOfFile("");
    cout << "   ����� � ����    \n"
         << "===================\n"
         << "������� �������� ����� (��� �������): "
         << flush;
    cin >> nameOfFile;
    nameOfFile += ".txt";
    ofstream fout(nameOfFile, ios_base::app);
    if (fout)
    {
        fout << " �   "
             << "������\t" //string
             << "��� �������\t" //string
             << "����������   " //struct TResolution
             << "���������   " //int
             << "����. ����.   " //int
             << "���   " //float
             << "�������\t" //bool
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
        cout << "���� � ����� ��������� ������� ������.\n"
                "(���������� ������� ��������)" << endl;
        system("pause");
        return;
    }
fout.close();
cout << "���� " << nameOfFile << " ������." << endl;
system("pause");
}

int TMenu::exitProgram(bool &check)
{
check = false;
return check;
}
