#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTPIN 10
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHT22);

#define ONE_WIRE_BUS 11
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

 
float HOMEtemp_old = 0;
float HOMEhum_old = 0;
float PODVALtemp_old = 0;

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFFA5

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;


void setup(void) {
 tft.begin(0x9325);     //идентифицируем контроллер дисплея согласно библиотеке
 tft.cp437(true);       //разрешаем отображение знака "градусы" ('\xB0') в кириллической таблице библиотеки
 tft.setRotation(1);    //поворачиваем дисплей на 90 градусов
 dht.begin();           //запускаем датчик DHT22
 sensors.begin();       //запускаем d18b20
}

void loop(void) {  
 displayText();  
 delay(2000);
}

unsigned long TextTemp() {
  tft.print('\xD2');
  tft.print('\xE5');
  tft.print('\xEC');
  tft.print('\xEF');
  tft.print('\xE5');
  tft.print('\xF0');   
  tft.print('\xE0');
  tft.print('\xF2');
  tft.print('\xF3');
  tft.print('\xF0');
  tft.print('\xE0');
}


unsigned long displayText() {
  sensors.requestTemperatures();

  
//************************************* ПЕРЕМЕННЫЕ ДАТЧИКОВ ********************************************  
  float HOMEtemp = dht.readTemperature();           //Дом-температура
  float HOMEhum = dht.readHumidity();               //Дом-влажность
  float PODVALtemp = sensors.getTempCByIndex(0);    //Гараж-температура

//************************************* РАМКИ И ЛИНИИ НА ДИСПЛЕЕ ***************************************
  tft.fillScreen(BLACK);                            //обновляем экран, устанавливаем черный фон
  tft.drawRoundRect(5, 5, 200, 230, 9, WHITE);      //скругленный квадрат - Дом (x,y,weight,high,radius,color)
  tft.drawRoundRect(215, 5, 100, 80, 9, WHITE);     //скругленный квадрат - Гараж (x,y,weight,high,radius,color)
  tft.fillRoundRect(10, 90, 190, 65, 9, RED);       //красная скругленная рамка - Отопление (x,y,weight,high,radius,color)
  tft.fillRoundRect(215, 90, 100, 65, 9, BLUE);     //синяя скругленная рамка - Улица (x,y,weight,high,radius,color)
  
  tft.drawFastHLine (10, 35, 190, WHITE);           //горизонтальная линия - Дом (x,y,weight,color)
  tft.drawFastVLine (105, 120, 30, WHITE);          //вертикальная линия - Дом (x,y,weight,color)
  tft.drawFastHLine (220, 35, 90, WHITE);           //горизонтальная линия - Гараж (x,y,weight,color)


//************************************* ЗАГОЛОВКИ ******************************************************
//Дом
  tft.setCursor(15, 15);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print('\xC4');
  tft.print('\xEE');
  tft.print('\xEC');

//Отопление
  tft.setCursor(15, 95);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print('\xCE');
  tft.print('\xF2');
  tft.print('\xEE');
  tft.print('\xEF');
  tft.print('\xEB');
  tft.print('\xE5');   
  tft.print('\xED');
  tft.print('\xE8');
  tft.print('\xE5');

//Подвал
  tft.setCursor(15, 170);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print('\xCF');
  tft.print('\xEE');
  tft.print('\xE4');
  tft.print('\xE2');
  tft.print('\xE0');
  tft.print('\xEB');

//Гараж  
  tft.setCursor(225, 15);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print('\xC3');
  tft.print('\xE0');
  tft.print('\xF0');
  tft.print('\xE0');
  tft.print('\xE6');

//Улица 
  tft.setCursor(225, 95);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print('\xD3');
  tft.print('\xEB');
  tft.print('\xE8');
  tft.print('\xF6');
  tft.print('\xE0');








// Слово - Температура
  tft.setCursor(15, 45);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  TextTemp();

// Температура в доме
  tft.setCursor(15, 60);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(HOMEtemp, 1);
  tft.print('\xB0');
  tft.setTextColor(YELLOW);
  
if (HOMEtemp > HOMEtemp_old) {
  tft.print('\x1E'); 
}
if (HOMEtemp < HOMEtemp_old) {
  tft.print('\x1F');
}
  HOMEtemp_old = HOMEtemp;

  
    
// Слово - Влажность
  tft.setCursor(115, 45);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  tft.print('\xC2');
  tft.print('\xEB');
  tft.print('\xE0');
  tft.print('\xE6');
  tft.print('\xED');
  tft.print('\xEE');   
  tft.print('\xF1');
  tft.print('\xF2');
  tft.print('\xFC');

// Влажность в доме
  tft.setCursor(115, 60);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(HOMEhum, 1);
  tft.print('\x25'); //Знак - процент
  tft.setTextColor(YELLOW);

if (HOMEhum > HOMEhum_old) {
  tft.print('\x1E'); 
}
if (HOMEhum < HOMEhum_old) {
  tft.print('\x1F');
}
  HOMEhum_old = HOMEhum;










// Слово - Прямой
  tft.setCursor(15, 120);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print('\xCF');
  tft.print('\xF0');
  tft.print('\xFF');
  tft.print('\xEC');
  tft.print('\xEE');
  tft.print('\xE9');

// Отопление - Температура прямой
  tft.setCursor(15, 135);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("100.5");
  tft.print('\xB0');
  tft.setTextColor(YELLOW);
  tft.print('\x1F');


// Слово - Обратный
  tft.setCursor(115, 120);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print('\xCE');
  tft.print('\xE1');
  tft.print('\xF0');
  tft.print('\xE0');
  tft.print('\xF2');
  tft.print('\xED');
  tft.print('\xFB');
  tft.print('\xE9');


// Отопление - Температура обратный
  tft.setCursor(115, 135);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("100.5");
  tft.print('\xB0');
  tft.setTextColor(YELLOW);
  tft.print('\x1F');





// Слово - Температура
  tft.setCursor(15, 195);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  TextTemp();

// Температура в подвале
  tft.setCursor(15, 210);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(PODVALtemp, 1);      //температура в подвале
  tft.print('\xB0');
  tft.setTextColor(YELLOW);

if (PODVALtemp > PODVALtemp_old) {
  tft.print('\x1E'); 
}
if (PODVALtemp < PODVALtemp_old) {
  tft.print('\x1F');
}
  PODVALtemp_old = PODVALtemp;





  



// Слово - Температура
  tft.setCursor(225, 45);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  TextTemp();

// Температура в гараже
  tft.setCursor(225, 60);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("100.5");   //температура в гараже
  tft.print('\xB0');
  tft.setTextColor(YELLOW);
  tft.print('\x1E');  



// Слово - Температура
  tft.setCursor(225, 120);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  TextTemp();

// Температура на улице
  tft.setCursor(225, 135);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("100.5");
  tft.print('\xB0');
  tft.setTextColor(YELLOW);
  tft.print('\x1F');
}
