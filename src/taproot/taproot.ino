#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);

  // vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(12);
  vw_setup(4000);  // Bits per sec
  pinMode(13, OUTPUT);

  // Start the receiver PLL running
  vw_rx_start();
  Serial.println("server setup!!!!!!!");
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    Serial.println((char*)buf);

    if(buf[0]=='1'){
      digitalWrite(13,1);
    }
    if(buf[0]=='0'){
      digitalWrite(13,0);
    }
  }
}
