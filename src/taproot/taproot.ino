#include <VirtualWire.h>
#include "../Creepers.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Taproot initialized");

  pinMode(13, OUTPUT);

  vw_set_rx_pin(12);
  vw_setup(4000); // bps

  // Start the receiver PLL running
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {

    packet inbound;
    memcpy(&inbound, buf, sizeof(inbound));

    Serial.println(inbound.timestamp);
    Serial.println(inbound.light);
    Serial.println(inbound.humidity);
    Serial.println(inbound.tempc);

    Serial.println();
  }
}
