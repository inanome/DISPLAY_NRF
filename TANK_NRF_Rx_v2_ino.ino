//ПРИЕМНИК

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int ch1 = 3;
int ch2 = 5;
int dir = 4;

int Fpwm = 0;
int Bpwm = 0;

const uint64_t pipe1 = 0xF0F1F2F3F1LL;  //идентификатор передачи "труба1"
const uint64_t pipe2 = 0xF0F1F2F3F2LL;  //идентификатор передачи "труба1"
RF24 radio(7,8);                      //CE, CSN

void setup() {
  Serial.begin(9600);
  
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  pinMode(dir, OUTPUT);
  
  radio.begin();
  delay(2);
  radio.setChannel(80);                 //канал (0-127)
  radio.setDataRate(RF24_250KBPS);      //скорость, RF24_250KBPS (на nRF24L01 "без +" не работает), RF24_1MBPS, RF24_2MBPS
                                        //меньше скорость, выше чувствительность приемника
  radio.setPALevel(RF24_PA_HIGH);       //мощность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,
  radio.openReadingPipe(1, pipe1);      //открываем первую трубу с идентификатором "pipe", таких труб может быть 6 (0-5)
  radio.openReadingPipe(2, pipe2);      //открываем первую трубу с идентификатором "pipe", таких труб может быть 6 (0-5)
//radio.openReadingPipe(0,pipe01);      // или открываем все трубы разом
  radio.startListening();               //включаем применик, начинаем слушать трубу
//radio.stopListening();                //останавливаем прием если нужно что-то передать
}

void loop() {
  delay(500);
  uint8_t pipeNum = 0;
  
  if (radio.available(&pipeNum)){       // проверяем не пришло ли чего в буфер.
    if (pipeNum == 1) {
      int val1 = 0;
      radio.read(&val1, sizeof(val1));
      Serial.println(pipeNum);
      Serial.println(val1);
      Serial.println();
    }
    
    if (pipeNum == 2) {
      int val2 = 0;
      radio.read(&val2, sizeof(val2));
      Serial.println(pipeNum);
      Serial.println(val2);  
      Serial.println();    
    }
  }







  
//  int val;
//  if (radio.available()) {            //проверяем, не пришло ли чего в буфер
//   radio.read(&val, sizeof(val));    //читаем данные в переменную, указываем, сколько байт читаем
//   Serial.println(val);
//
//  if (val > 500 && val < 524) {
//    analogWrite(ch1, LOW);
//    analogWrite(ch2, LOW);
//  }
//
//  if (val >= 524) {
//    Fpwm = map(val, 524, 1023, 0, 255);
//    digitalWrite(dir, LOW);
//    analogWrite(ch1, Fpwm);
//  }
//
//  if (val <= 500) {
//    Bpwm = map(val, 500, 0, 0, 255);
//    digitalWrite(dir, HIGH);
//    analogWrite(ch2, Bpwm);
//    }
//  }
}
