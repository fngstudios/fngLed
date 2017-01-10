/**************************************************************
   fngLed Library
   fng Studios 2017
   v 0.1
   Library encargada de definir y controlar un led rgb.
   Recibe un string de 13 bytes con los parametros del led y
   gestiona el encendido segun modo, velocidad, status y colores.


***************************************************************/

#include "fngLed.h"

uint8_t fngLed::getStatus(){
  return this->_Status;
}

uint8_t fngLed::getMode(){
  return this->_Mode;
}

uint8_t fngLed::getSpeed(){
  return this->_Speed;
}

uint8_t fngLed::getMoodMode(){
  return this->_MoodMode;
}

void fngLed::shine(){
  analogWrite(this->_RedPin,this->_CurrentRed);
  analogWrite(this->_GreenPin,this->_CurrentGreen);
  analogWrite(this->_BluePin,this->_CurrentBlue);
}

void fngLed::turnOff(){
  analogWrite(this->_RedPin,0);
  analogWrite(this->_GreenPin,0);
  analogWrite(this->_BluePin,0);
}

void fngLed::setColor(uint8_t Red,uint8_t Green,uint8_t Blue){
  this->_CurrentRed = Red;
  this->_CurrentGreen = Green;
  this->_CurrentBlue = Blue;
}

void fngLed::begin(unsigned char RedPin,unsigned char GreenPin,unsigned char BluePin){
  this->_RedPin=RedPin;
  this->_GreenPin=GreenPin;
  this->_BluePin=BluePin;
  pinMode(this->_RedPin,OUTPUT);
  pinMode(this->_GreenPin,OUTPUT);
  pinMode(this->_BluePin,OUTPUT);
}

  void fngLed::update(uint8_t *data){
    this->_Status  = data[0];
    this->_Mode    = data[1];
    this->_Speed   = data[2];
    this->_CurrentRed =  data[3];
    this->_CurrentGreen = data[4];
    this->_CurrentBlue  = data[5];
    this->_FromRed = data[6];
    this->_FromGreen = data[7];
    this->_FromBlue = data[8];
    this->_ToRed = data[9];
    this->_ToGreen = data[10];
    this->_ToBlue = data[11];
    this->_MoodMode = data[12];

  }

  void fngLed::doOneOnOne(){
    static char estado = 0;
    switch (estado){
      case 0:       this->setColor(255,0,0);
                    this->shine();
                    break;
      case 1:       this->setColor(255,255,0);
                    this->shine();
                    break;
      case 2:       this->setColor(0,255,0);
                    this->shine();
                    break;
      case 3:       this->setColor(0,255,255);
                    this->shine();
                    break;
      case 4:       this->setColor(0,0,255);
                    this->shine();
                    break;
      case 5:       this->setColor(255,0,255);
                    this->shine();
                    break;
      case 6:       this->setColor(255,255,255);
                    this->shine();
                    break;
    }
    estado ++;
    if (estado>6){
      estado = 0;
    }
  }

  void fngLed::work(){

  if (this->getStatus()){
    switch (this->getMode()){

      case 0:         this->shine();
                      break;
      case 1:         if (this->canChange()){
                        this->setChangingTime(1);
                        this->doOneOnOne();
                      }
                      break;
      case 2:         if (this->canChange()){
                        this->setChangingTime(0);
                        this->doMood();
                      }
                      break;
      case 3:         if (this->canChange()){
                        this->setChangingTime(0);
                        this->doFromTo();
                      }
                      break;
    }
  }else if (!this->getStatus()){
    this->turnOff();
  }
}

 void fngLed::setChangingTime(unsigned char Type){
  if (Type==1){
    this->_ChangingTime = millis()+(255-this->getSpeed())*3;
  }else{
    this->_ChangingTime = millis()+(255-this->getSpeed())/8;
  }
}


uint8_t fngLed::canChange(){
  if (millis()>this->_ChangingTime){
    return 1;
  }else{
    return 0;
  }
}


void fngLed::doMood(){

  static unsigned char red = 0;
  static unsigned char green = 0;
  static unsigned char blue = 0;
  static char estado = 0;
  static char mode = 0;


  switch(estado){

    case 0:     red++;
                if (red == 255){
                  estado++;
                }
                break;
    case 2:     red--;
                if (red == 0){
                  estado++;
                }
                break;
    case 1:     green++;
                if (green == 255){
                  estado++;
                }
                break;
    case 4:     green--;
                if (green == 0){
                  estado++;
                }
                break;
    case 3:     blue++;
                if (blue == 255){
                  estado++;
                }
                break;
    case 5:     blue--;
                if (blue == 0){
                  estado = 0;
                }
                break;
  }
  this->setColor(red,green,blue);
  this->shine();
}
void fngLed::doFromTo(){

  static unsigned char red = 0;
  static unsigned char green = 0;
  static unsigned char blue = 0;
  static unsigned char ida = 1;

  if (ida){
    if (red < this->_ToRed ){
      red++;
    }
    if (green < this->_ToGreen ){
      green++;
    }
    if (blue < this->_ToBlue ){
      blue++;
    }
    if (red == this->_ToRed && green == this->_ToGreen && blue == this->_ToBlue){
      ida = 0;
    }
  }else{
    if (red > this->_FromRed ){
      red--;
    }
    if (green > this->_FromGreen ){
      green--;
    }
    if (blue > this->_FromBlue ){
      blue--;
    }
    if (red == this->_FromRed && green == this->_FromGreen && blue == this->_FromBlue){
      ida = 1;
    }
  }


  this->setColor(red,green,blue);
  this->shine();
}
