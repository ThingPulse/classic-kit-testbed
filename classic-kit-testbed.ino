#include "SSD1306Wire.h"
#include"DHTesp.h" 

SSD1306Wire  display(0x3c, D3, D4);
DHTesp dht;

boolean ledState = false;

void setup() {
  Serial.begin(115200);

  pinMode(D0, OUTPUT);

  dht.setup(D6,DHTesp::DHT11);
  delay(1000); 
  
  display.init();
  
  display.clear();
  display.setColor(WHITE);
  display.setFont(ArialMT_Plain_16);
}

void loop() {
  digitalWrite(D0, ledState);
  ledState = !ledState;

  display.clear();

  display.drawLine(0, 0, 128, 64);
  display.drawLine(0, 64, 128, 0);

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature(); 
  
  char buffer[] = "";
  sprintf(buffer, "%.1f°C", temperature);
  display.drawString(0, 24, buffer);
  sprintf(buffer, "%.1f%%", humidity);
  display.drawString(80, 24, buffer);
  
  display.display();
  
  delay(2000);
}
