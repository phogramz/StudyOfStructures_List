#ifndef TMENU_H
#define TMENU_H

#include "tmonitor.h"
#include "tlist.h"

class TMenu
{
private:
   //int openFile() const;

public:
   TMenu();//Construction

   int button = 0;
   int showMainMenu(int &)const;
   void openFile(TList<TMonitor>*_tempList, bool *isOpen) const;
   void showData(TList<TMonitor> tempList);
   void addData(TList<TMonitor> *tempList) const;
   void editData(TList<TMonitor> *tempLst);
   void deleteData(TList<TMonitor> *tempList) const;
   void saveData() const;
   void outputFile(TList<TMonitor> tempList) const;
   void aboutProgramm() const;
   int exitProgram(bool &);
};

int str_Amount(char s[30]);
void ReadData(TList<TMonitor> *tempList);
#endif // TMENU_H
