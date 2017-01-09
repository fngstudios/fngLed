/**************************************************************
   fngLed Library
   fng Studios 2017
   v 0.1
   Library encargada de definir y controlar un led rgb.
   Recibe un string de 13 bytes con los parametros del led y 
   gestiona el encendido segun modo, velocidad, status y colores.
   
   
 **************************************************************/

#include "fngLed.h"

uint8_t fngLed::getStatus(){
  return _Status;
}
uint8_t fngLed::getMode(){
  return _Mode;
}
uint8_t fngLed::getSpeed(){
  return _Speed;
}
uint8_t fngLed::getMoodMode(){
  return _MoodMode;
}

void fngLed::shine(){
  analogWrite(_RedPin,_CurrentRed);
  analogWrite(_GreenPin,_CurrentGreen);
  analogWrite(_BluePin,_CurrentBlue);
}

void fngLed::begin(unsigned char RedPin,unsigned char GreenPin,unsigned char BluePin){
  _RedPin=RedPin;
  _GreenPin=GreenPin;
  _BluePin=BluePin;
  pinMode(_RedPin,OUTPUT);
  pinMode(_GreenPin,OUTPUT);
  pinMode(_BluePin,OUTPUT);
}

  void fngLed::update(uint8_t *data){
    _Status  = data[0];
    _Mode    = data[1];
    _Speed   = data[2];
    _CurrentRed =  data[3];
    _CurrentGreen = data[4];
    _CurrentBlue  = data[5];
    _FromRed = data[6];
    _FromGreen = data[7];
    _FromBlue = data[8];
    _ToRed = data[9];
    _ToGreen = data[10];
    _ToBlue = data[11];
    _MoodMode = data[12];
  }

  void fngLed::doOneOnOne(){
    static char estado = 0;
    switch (estado){
      case 0:       analogWrite(LED_RED,255);
                    analogWrite(LED_GREEN,0);
                    analogWrite(LED_BLUE,0);
                    break;
      case 1:       analogWrite(LED_RED,255);
                    analogWrite(LED_GREEN,255);
                    analogWrite(LED_BLUE,0);
                    break;
      case 2:       analogWrite(LED_RED,0);
                    analogWrite(LED_GREEN,255);
                    analogWrite(LED_BLUE,0);
                    break;
      case 3:       analogWrite(LED_RED,0);
                    analogWrite(LED_GREEN,255);
                    analogWrite(LED_BLUE,255);
                    break;
      case 4:       analogWrite(LED_RED,0);
                    analogWrite(LED_GREEN,0);
                    analogWrite(LED_BLUE,255);
                    break;
      case 5:       analogWrite(LED_RED,255);
                    analogWrite(LED_GREEN,0);
                    analogWrite(LED_BLUE,255);
                    break;
      case 6:       analogWrite(LED_RED,255);
                    analogWrite(LED_GREEN,255);
                    analogWrite(LED_BLUE,255);
                    break;

    }
    estado ++;
    if (estado>6){
      estado = 0;
    }
  }

  if (Led.getStatus()){
    switch (Led.getMode()){

      case 0:         Led.shine();
                      break;
      case 1:         if (canChange()){
                        setChangingTime(1);
                        Led.doOneOnOne();
                      }
                      break;
      case 2:         if (canChange()){
                        setChangingTime(0);
                        doMood();
                      }
                      break;
    }
  }else if (!Led.getStatus()){
    analogWrite(LED_RED,0);
    analogWrite(LED_GREEN,0);
    analogWrite(LED_BLUE,0);
  }
 
 
 void setChangingTime(unsigned char Type){
  if (Type==1){
    changingTime = millis()+(255-Led.getSpeed())*3;
  }else{
    changingTime = millis()+(255-Led.getSpeed())/8;
  }
}
unsigned char canChange(){
  if (millis()>changingTime){
    return 1;
  }else{
    return 0;
  }
}


void doMood(){

  static char red = 0;
  static char green = 0;
  static char blue = 0;
  static char estado = 0;
  static char mode = 0;


  switch(estado){

    case 0:     red++;
                analogWrite(LED_RED,red);
                if (red == wwsData[TO_RED]){
                  estado++;
                }
                break;
    case 2:     red--;
                analogWrite(LED_RED,red);
                if (red == wwsData[FROM_RED]){
                  estado++;
                }
                break;
    case 1:     green++;
                analogWrite(LED_GREEN,green);
                if (green == 255){
                  estado++;
                }
                break;
    case 4:     green--;
                analogWrite(LED_GREEN,green);
                if (green == 0){
                  estado++;
                }
                break;
    case 3:     blue++;
                analogWrite(LED_BLUE,blue);
                if (blue == 255){
                  estado++;
                }
                break;
    case 5:     blue--;
                analogWrite(LED_BLUE,blue);
                if (blue == 0){
                  estado = 0;
                }
                break;
  }
}
