#include "tmonitor1.h"

#include <iostream>
#include <cstring>

using namespace std;

TMonitor1::TMonitor1():
    matrixType("")
  , resolution({0, 0})
  , diagonal(0)
  , frameRate(0)
  , loudspeakers(false)
{

}

TMonitor1::TMonitor1(const std::string lmodel,
                     const std::string lmatrixType,
                     const TMonitor1::TResolution lresolution,
                     const TMonitor1::TPorts lports,
                     const int ldiagonal,
                     const int lframeRate,
                     const float lweight,
                     const bool lloudspeakers):
    TDetails(lmodel, lports, lweight)
  , matrixType(lmatrixType)
  , resolution(lresolution)
  , diagonal(ldiagonal)
  , frameRate(lframeRate)
  , loudspeakers(lloudspeakers)
{

}

TMonitor1::TMonitor1(const TMonitor1 &other):
    TDetails(other)
  , matrixType(other.matrixType)
  , resolution(other.resolution)
  , diagonal(other.diagonal)
  , frameRate(other.frameRate)
  , loudspeakers(other.loudspeakers)
{

}

TMonitor1::~TMonitor1()
{

}

TMonitor1 &TMonitor1::operator =(const TMonitor1 &other)
{
    if(this == &other) return *this;

    matrixType = other.matrixType;
    resolution = other.resolution;
    diagonal = other.diagonal;
    frameRate = other.frameRate;
    loudspeakers = other.loudspeakers;

    return *this;
}

void TMonitor1::setMatrixType(const string lmatrixType)
{
    matrixType = lmatrixType;
}

string TMonitor1::getMatrixType() const
{
    return matrixType;
}

void TMonitor1::setResolution(const TMonitor1::TResolution lresolution)
{
    resolution = lresolution;
}

TMonitor1::TResolution TMonitor1::getResolution() const
{
    return resolution;
}

void TMonitor1::setDiagonal(const int ldiagonal)
{
    diagonal = ldiagonal;
}

int TMonitor1::getDiagonal() const
{
    return diagonal;
}

void TMonitor1::setFrameRate(const int lframeRate)
{
    frameRate = lframeRate;
}

int TMonitor1::getFrameRate() const
{
    return frameRate;
}

void TMonitor1::setLoudspeakers(const bool lloudspeakers)
{
    loudspeakers = lloudspeakers;
}

bool TMonitor1::getLoudspeakers() const
{
    return loudspeakers;
}

void TMonitor1::show() const
{
    const char *strPorts[] = {"undefined", "HDMI", "DisplayPort", "VGA", "DVI", "USB"};
    cout << "������: " << getModel() << "\n" //�������� �������� ����� �����, �.�. ��� ������� �������
         << "��� �������: " << matrixType << "\n"
         << "���������� ������: (" << resolution.height << ", "
                            << resolution.widht << ")\n"
         << "���� �����: " << strPorts[getPorts()] << "\n" //-\\- ���������� �������� ������ �� �������
         << "��������� ������: " << diagonal << "\"" << "\n"
         << "������� ������: " << frameRate << " ��" << "\n"
         << "���: " << getWeight() << " ��" << "\n" //-\\-
         << boolalpha << "������� � ��������: " << loudspeakers << "\n"
         << endl;
}
