/**************************************************************
   fngLed Library
   fng Studios 2017
   v 0.1
   Library encargada de definir y controlar un led rgb.
   Recibe un string de 13 bytes con los parametros del led y
   gestiona el encendido segun modo, velocidad, status y colores.


 **************************************************************/

#ifndef fngLed_h
#define fngLed_h

#include <Arduino.h>

class fngLed {

public:
  void work();
  void update(uint8_t *data);
  void begin(unsigned char RedPin,unsigned char GreenPin,unsigned char BluePin);
  void shine();
  void turnOff();
  void setChangingTime(unsigned char Type);
  uint8_t canChange();
  void setColor(uint8_t Red,uint8_t Green,uint8_t Blue);
  void doOneOnOne();
  void doMood();
  uint8_t getStatus();
  uint8_t getMode();
  uint8_t getSpeed();
  uint8_t getMoodMode();
  uint8_t getwwsDataLenght();
  unsigned char _CurrentRed;
  unsigned char _CurrentGreen;
  unsigned char _CurrentBlue;
  unsigned char _FromRed;
  unsigned char _FromGreen;
  unsigned char _FromBlue;
  unsigned char _ToRed;
  unsigned char _ToGreen;
  unsigned char _ToBlue;
  char wwsData[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
  unsigned char _wwsData_L = 13;
private:

  unsigned char _Mode;
  unsigned char _Status;
  unsigned char _Speed;
  unsigned char _MoodMode;
  unsigned long _ChangingTime = 0;
  unsigned char _RedPin;
  unsigned char _GreenPin;
  unsigned char _BluePin;
};

#endif
