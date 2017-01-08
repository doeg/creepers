#include <VirtualWire.h>
#include "SparkFun_Si7021_Breakout_Library.h"

#define LED_PIN 13
#define PHOTOCELL_PIN A0

#define PACKET_SIZE 14 // bytes

void logData(unsigned long timestamp, int light, float humidity, float tempf);

// HTU21D temp/humidity sensor
Weather sensor;

int count = 1;

void setup() {
  Serial.begin(9600);

  sensor.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(PHOTOCELL_PIN, INPUT);

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

  char packet[4];
  packet[0] = '0' + timestamp;
  packet[1] = '0' + lightADC;
  packet[1] = '0' + humidity;
  packet[2] = '0' + tempf;

  Serial.println((char*) packet);

  packet[0] = (uint8_t)((timestamp >> 24) & 0xFF);
  packet[1] = (uint8_t)((timestamp >> 16) & 0xFF);
  packet[2] = (uint8_t)((timestamp >> 8) & 0xFF);
  packet[3] = (uint8_t)(timestamp & 0xFF);

  digitalWrite(13, HIGH);
  vw_send(packet, 4);
  vw_wait_tx();
  digitalWrite(13, LOW);
  delay(1000);

  char msg[7] = {'h','e','l','l','o',' ','#'};
  msg[6] = '0' + count;
  Serial.println((char*)msg);

  digitalWrite(13, HIGH);
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx();
  digitalWrite(13, LOW);
  delay(1000);
  count = count + 1;

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
