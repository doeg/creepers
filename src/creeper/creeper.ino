#include <VirtualWire.h>
#include "SparkFun_Si7021_Breakout_Library.h"

#define LED_PIN 13
#define PHOTOCELL_PIN A0

#define PACKET_SIZE 14 // bytes

void logData(unsigned long timestamp, int light, float humidity, float tempf);

uint8_t packet[14];

// HTU21D temp/humidity sensor
Weather sensor;

void setup() {
  Serial.begin(9600);
  Serial.println("Creeper initialized");

  pinMode(LED_PIN, OUTPUT);
  pinMode(PHOTOCELL_PIN, INPUT);

  sensor.begin();

  // vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(4000); // bps
}

void loop() {
  unsigned long timestamp = millis(); // 4 bytes
  int lightADC = analogRead(PHOTOCELL_PIN); // 2 bytes
  float humidity = sensor.getRH(); // 4 bytes
  float tempf = sensor.getTempF(); // 4 bytes

  logData(timestamp, lightADC, humidity, tempf);

  // Serialize the packet to an array of uint8_t so it can be sent via RF
  packet[0] = (uint8_t)((timestamp >> 24) & 0xFF);
  packet[1] = (uint8_t)((timestamp >> 16) & 0xFF);
  packet[2] = (uint8_t)((timestamp >> 8) & 0xFF);
  packet[3] = (uint8_t)(timestamp & 0xFF);

  packet[4] = (uint8_t)((lightADC >> 8) & 0xFF);
  packet[5] = (uint8_t)(lightADC & 0xFF);

  packet[6] = 0; // (uint8_t)((humidity >> 24) & 0xFF);
  packet[7] = 0; // (uint8_t)((humidity >> 16) & 0xFF);
  packet[8] = 0; // (uint8_t)((humidity >> 8) & 0xFF);
  packet[9] = 0; // (uint8_t)(humidity & 0xFF);

  packet[10] = 0; // = 0; // (uint8_t)((tempf >> 24) & 0xFF);
  packet[11] = 0; // (uint8_t)((tempf >> 16) & 0xFF);
  packet[12] = 0; // (uint8_t)((tempf >> 8) & 0xFF);
  packet[13] = 0; // (uint8_t)(tempf & 0xFF);

  Serial.println((char*) packet);

  digitalWrite(13, HIGH);
  vw_send(packet, 4);
  vw_wait_tx();
  digitalWrite(13, LOW);
  delay(1000);
}

void logData(unsigned long timestamp, int light, float humidity, float tempf) {
  Serial.print("t: ");
  Serial.println(timestamp);

  Serial.print("L: ");
  Serial.println(light);

  char humidityStr[16];
  dtostrf(humidity, 5, 2, humidityStr);
  Serial.print("H: ");
  Serial.println(humidityStr);

  char tempStr[16];
  dtostrf(tempf, 5, 2, tempStr);
  Serial.print("T: ");
  Serial.println(tempStr);
  Serial.println();
}

