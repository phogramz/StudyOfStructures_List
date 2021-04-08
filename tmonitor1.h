#ifndef TMONITOR1_H
#define TMONITOR1_H

#include <tdetails.h>
#include <iostream>
#include <string>
#include <cstring>

class TMonitor1: public TDetails
{
 public:
    struct TResolution //разрешение экрана
    {
        int height;
        int widht;
    };
 private: //закрытые основные переменные класса
    std::string matrixType;
    TResolution resolution;
    int diagonal;
    int frameRate;
    bool loudspeakers;

public:
    TMonitor1(); //конструктор
    TMonitor1(const std::string lmodel,
              const std::string lmatrixType,
              const TResolution lresolution,
              const TPorts lports,
              const int ldiagonal,
              const int lframeRate,
              const float lweight,
              const bool lloudspeakers);
    TMonitor1(const TMonitor1 &other);
    //explicit TMonitor1(const std::string lmodel);
    ~TMonitor1(); //деструктор

    TMonitor1 &operator = (const TMonitor1 &other);
   // friend std::ostream& operator<<(std::ostream &os, const TMonitor1 &other);

    void setMatrixType(const std::string lmatrixType);
    std::string getMatrixType() const;
    void setResolution (const TResolution lresolution);
    TResolution getResolution() const;
    void setDiagonal(const int ldiagonal);
    int getDiagonal() const;
    void setFrameRate(const int lframeRate);
    int getFrameRate () const;
    void setLoudspeakers(const bool lloudspeakers);
    bool getLoudspeakers() const;

    void show() const;
};

#endif // TMONITOR1_H
