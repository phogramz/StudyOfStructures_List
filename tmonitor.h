#ifndef TMONITOR_H
#define TMONITOR_H

#include <string>

class TMonitor
{
 public: 
    enum TPorts {undefined = 0, HDMI, DisplayPort, VGA, DVI, USB}; //новый тип переменных
    struct TResolution //разрешение экрана
    {
        int height;
        int widht;
    };
 private: //закрытые основные переменные класса
    //int Id;
    std::string model;
    std::string matrixType;
    TResolution resolution;
    TPorts ports;
    int diagonal;
    int frameRate;
    float weight;
    bool loudspeakers;
    char *str;

public:
    TMonitor(); //конструктор
    TMonitor(const std::string lmodel,
             const std::string lmatrixType,
             const TResolution lresolution,
             const TPorts lports,
             const int ldiagonal,
             const int lframeRate,
             const float lweight,
             const bool lloudspeakers,
             const char *lstr);
   ~TMonitor(); //деструктор

    //void setID(const int lId);
    //int getID() const;
    void setModel(const std::string lmodel);
    std::string getModel() const;
    void setMatrixType(const std::string lmatrixType);
    std::string getMatrixType() const;
    void setResolution (const TResolution lresolution);
    TResolution getResolution() const;
    void setPorts (const TPorts lports);
    TPorts getPorts() const;
    void setDiagonal(const int ldiagonal);
    int getDiagonal() const;
    void setFrameRate(const int lframeRate);
    int getFrameRate () const;
    void setWeight (const float lweight);
    float getWeight () const;
    void setLoudspeakers(const bool lloudspeakers);
    bool getLoudspeakers() const;

    void setStr(const char *lstr);
    char* getStr() const;

    void show() const;
};

#endif // TMONITOR_H
