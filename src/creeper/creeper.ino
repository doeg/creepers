#include <VirtualWire.h>
#include "SparkFun_Si7021_Breakout_Library.h"
#include "../Creepers.h"

#define LED_PIN 13
#define PHOTOCELL_PIN A0

void logData(packet p);

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

  struct packet outbound;
  outbound.timestamp = millis();
  outbound.light = analogRead(PHOTOCELL_PIN);
  outbound.humidity = (int)(sensor.getRH() * 100);

  float tempf = sensor.getTempF();
  outbound.tempc = (int)((tempf - 32)/1.8 * 100);

  logData(outbound);

  char b[sizeof(outbound)];
  memcpy(b, &outbound, sizeof(outbound));

  digitalWrite(13, HIGH);

  vw_send((char*)b, sizeof(b));
  vw_wait_tx();

  digitalWrite(13, LOW);

  delay(1000);
}

void logData(packet p) {
  Serial.print("t: ");
  Serial.println(p.timestamp);

  Serial.print("L: ");
  Serial.println(p.light);

  Serial.print("H: ");
  Serial.println(p.humidity);

  Serial.print("T: ");
  Serial.println(p.tempc);
  Serial.println();
}

