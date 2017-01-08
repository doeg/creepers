#include <VirtualWire.h>

int count = 1;

void setup() {
  Serial.begin(9600);

  pinMode(13,OUTPUT);

  // vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(4000); // bps
}

void loop(){
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
