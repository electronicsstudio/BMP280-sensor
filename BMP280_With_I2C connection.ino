#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13  //SCL
#define BMP_MISO 12 //SDO
#define BMP_MOSI 11 //SDA
#define BMP_CS 10   //CSB

Adafruit_BMP280 bmp(BMP_CS); // SPI initialization with CS pin

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(100); // wait for native USB

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  Serial.print("$PBAR");
  Serial.print(",");
  Serial.print(bmp.readPressure());
  Serial.print(",");
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.print("*");
  Serial.println("");
  delay(500);
}
