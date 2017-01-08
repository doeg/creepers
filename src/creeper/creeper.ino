#include <VirtualWire.h>
#include "SparkFun_Si7021_Breakout_Library.h"

#define LED_PIN 13
#define PHOTOCELL_PIN A0

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

void loop(){
  int lightADC = analogRead(PHOTOCELL_PIN);
  Serial.println(lightADC);

  float humidity = sensor.getRH();
  float tempf = sensor.getTempF();

  Serial.println(humidity);
  Serial.println(tempf);

  char msg[7] = {'h','e','l','l','o',' ','#'};
  msg[6] = '0' + count;
  Serial.println((char*)msg);

  digitalWrite(13, HIGH);
  vw_send((uint8_t *)msg, 7);
  vw_wait_tx();
  digitalWrite(13, LOW);
  delay(1000);
  count = count + 1;
  Serial.println();
}
