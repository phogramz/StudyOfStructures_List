#include "tdetails.h"

#include <iostream>
#include <cstring>

using namespace std;

TDetails::TDetails():
    model("")
  , ports(undefined)
  , weight(0)
{

}

TDetails::TDetails(const std::string lmodel,
                   const TDetails::TPorts lports,
                   const float lweight):
    model(lmodel)
  , ports(lports)
  , weight(lweight)
{

}

TDetails::TDetails(const TDetails &other):
    model(other.model)
  , ports(other.ports)
  , weight(other.weight)
{

}

TDetails::~TDetails()
{

}

TDetails &TDetails::operator =(const TDetails &other)
{
    if(this == &other) return *this;

    model = other.model;
    ports = other.ports;
    weight = other.weight;

    return *this;
}

void TDetails::setModel(const string lmodel)
{
    model = lmodel;
}

string TDetails::getModel() const
{
    return model;
}

void TDetails::setPorts(const TDetails::TPorts lports)
{
    ports = lports;
}

TDetails::TPorts TDetails::getPorts() const
{
    return ports;
}

void TDetails::setWeight(const float lweight)
{
    weight = lweight;
}

float TDetails::getWeight() const
{
    return weight;
}

void TDetails::show() const
{
    const char *strPorts[] = {"undefined", "HDMI", "DisplayPort", "VGA", "DVI", "USB"};
    cout << "Модель: " << model << "\n"
         << "Порт входа: " << strPorts[ports] << "\n"
         << "Вес: " << weight << " кг" << "\n"
         << endl;
}
