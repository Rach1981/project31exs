// Project 31 - Temperature History Monitor

#include <Adafruit_ST7789.h>
#include <SPI.h>

// Display pins
#define TFT_CS   10
#define TFT_RST  9
#define TFT_DC   8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Temperature variables
int tcurrent = 0;
int tempArray[120];

// Read temperature from TMP36
void getTemp() {

  float sensor = 0;
  float voltage = 0;
  float celsius = 0;

  sensor = analogRead(A0);

  voltage = (sensor * 5000.0) / 1024.0;
  voltage = voltage - 500;
  celsius = voltage / 10;

  tcurrent = int(celsius);
  Serial.println(voltage);
  // Shift temperature history
  for (int i = 119; i > 0; i--) {
    tempArray[i] = tempArray[i - 1];
  }

  tempArray[0] = tcurrent;
}

void setup() {
  Serial.begin(9600);
  
  tft.init(240, 320);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);

  // initialize array
  for (int i = 0; i < 120; i++) {
    tempArray[i] = 0;
  }
}

void loop() {

  getTemp();

  tft.fillScreen(ST77XX_BLACK);

  // Display temperature
  tft.setCursor(40, 40);
  tft.setTextSize(3);
  tft.print("Temp");

  tft.setCursor(40, 90);
  tft.print(tcurrent);
  tft.print(" C");

  // Draw simple temperature graph
  for (int i = 0; i < 119; i++) {

    int y1 = 200 - tempArray[i];
    int y2 = 200 - tempArray[i + 1];

    tft.drawLine(i * 2, y1, (i + 1) * 2, y2, ST77XX_GREEN);
  }

  delay(2000);
}








