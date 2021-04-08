#include "tmonitor.h"
#include <iostream>
#include <cstring>

using namespace std;

TMonitor::TMonitor():
    //Id(0)
    model("")
  , matrixType("")
  , resolution({0, 0})
  , ports(undefined)
  , diagonal(0)
  , frameRate(0)
  , weight(0)
  , loudspeakers(false)
  , str(new char)
{

}

TMonitor::TMonitor(
                   const std::string lmodel,
                   const std::string lmatrixType,
                   const TMonitor::TResolution lresolution,
                   const TMonitor::TPorts lports,
                   const int ldiagonal,
                   const int lframeRate,
                   const float lweight,
                   const bool lloudspeakers,
                   const char *lstr):
    model(lmodel)
  , matrixType(lmatrixType)
  , resolution(lresolution)
  , ports(lports)
  , diagonal(ldiagonal)
  , frameRate(lframeRate)
  , weight(lweight)
  , loudspeakers(lloudspeakers)
  , str(new char[strlen(lstr) + 1])
{
    strcpy(str, lstr);
}

TMonitor::~TMonitor()
{
    //delete [] str;
}

//void TMonitor::setID(const int lId)
//{
//    Id = lId;
//}

//int TMonitor::getID() const
//{
//    return Id;
//}

void TMonitor::setModel(const string lmodel)
{
    model = lmodel;
}

string TMonitor::getModel() const
{
    return model;
}

void TMonitor::setMatrixType(const string lmatrixType)
{
    matrixType = lmatrixType;
}

string TMonitor::getMatrixType() const
{
    return matrixType;
}

void TMonitor::setResolution(const TMonitor::TResolution lresolution)
{
    resolution = lresolution;
}

TMonitor::TResolution TMonitor::getResolution() const
{
    return resolution;
}

void TMonitor::setPorts(const TMonitor::TPorts lports)
{
    ports = lports;
}

TMonitor::TPorts TMonitor::getPorts() const
{
    return ports;
}

void TMonitor::setDiagonal(const int ldiagonal)
{
    diagonal = ldiagonal;
}

int TMonitor::getDiagonal() const
{
    return diagonal;
}

void TMonitor::setFrameRate(const int lframeRate)
{
    frameRate = lframeRate;
}

int TMonitor::getFrameRate() const
{
    return frameRate;
}

void TMonitor::setWeight(const float lweight)
{
    weight = lweight;
}

float TMonitor::getWeight() const
{
    return weight;
}

void TMonitor::setLoudspeakers(const bool lloudspeakers)
{
    loudspeakers = lloudspeakers;
}

bool TMonitor::getLoudspeakers() const
{
    return loudspeakers;
}

void TMonitor::setStr(const char *lstr)
{
    delete [] str;
    str = nullptr;

    str = new char[strlen(lstr) + 1];
    strcpy(str, lstr);
}

char *TMonitor::getStr() const
{
    return str;
}

void TMonitor::show() const
{
    const char *strPorts[] = {"undefined", "HDMI", "DisplayPort", "VGA", "DVI", "USB"};
    cout
         << "Модель: " << model << "\n"
         << "Тип матрицы: " << matrixType << "\n"
         << "Разрешение экрана: (" << resolution.height << ", "
                            << resolution.widht << ")\n"
         << "Порт входа: " << strPorts[ports] << "\n"
         << "Диагональ экрана: " << diagonal << "\"" << "\n"
         << "Частота кадров: " << frameRate << " Гц" << "\n"
         << "Вес: " << weight << " кг" << "\n"
         << boolalpha << "Колонки в мониторе: " << loudspeakers << "\n"
         << endl;
}
