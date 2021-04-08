#ifndef TDETAILS_H
#define TDETAILS_H

#include <string>
class TDetails
{
public:
   enum TPorts {undefined = 0, HDMI, DisplayPort, VGA, DVI, USB}; //����� ��� ����������

private: //�������� �������� ���������� ������
   std::string model;
   TPorts ports;
   float weight;

public:
   TDetails(); //�����������
   TDetails(const std::string lmodel,
            const TPorts lports,
            const float lweight);
   TDetails(const TDetails &other);

  ~TDetails(); //����������
   TDetails &operator = (const TDetails &other);

   void setModel(const std::string lmodel); //�����
   std::string getModel() const;
   void setPorts (const TPorts lports);
   TPorts getPorts() const;
   void setWeight(const float lweight);
   float getWeight () const;

   void show() const;
};

#endif // TDETAILS_H
