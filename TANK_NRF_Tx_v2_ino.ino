//ПЕРЕДАТЧИК

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

const uint64_t pipe1 = 0xF0F1F2F3F1LL;  //идентификатор передачи "труба1"
const uint64_t pipe2 = 0xF0F1F2F3F2LL;  //идентификатор передачи "труба1"
RF24 radio(9, 10);                     //CE, CSN

void setup() {
  Serial.begin(9600);
  radio.begin();
  delay(2);
  radio.setChannel(80);                 //канал (0-127)
  radio.setDataRate(RF24_250KBPS);       //скорость, RF24_250KBPS (на nRF24L01 "без +" не работает), RF24_1MBPS, RF24_2MBPS
  //меньше скорость, выше чувствительность приемника
  radio.setPALevel(RF24_PA_HIGH);      //мощность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,
  //radio.openWritingPipe(pipe);         //открываем трубу на передачу
}

void loop() {
  radio.openWritingPipe(pipe1);         //открываем 1 трубу на передачу
  int val1 = analogRead(A2);
  int data1 = val1;
  radio.write(&data1, sizeof(data1));    //отправляем данные и указываем сколько байт

  radio.openWritingPipe(pipe2);         //открываем 2 трубу на передачу
  int val2 = analogRead(A3);
  int data2 = val2;
  radio.write(&data2, sizeof(data2));    //отправляем данные и указываем сколько байт
  
  Serial.println(val1);
  Serial.println(val2);
}
