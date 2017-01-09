#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Taproot initialized");

  pinMode(13, OUTPUT);

  // vw_set_ptt_inverted(true);
  vw_set_rx_pin(12);
  vw_setup(4000); // bps
  // Start the receiver PLL running
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    unsigned long timestamp;
    uint8_t tbuff[] = { buf[3], buf[2], buf[1], buf[0] };
    memcpy(&timestamp, &tbuff, sizeof(timestamp));
    Serial.print("t: ");
    Serial.println(timestamp);

    int light;
    uint8_t lbuff[] = { buf[5], buf[4] };
    memcpy(&light, &lbuff, sizeof(light));
    Serial.print("L: ");
    Serial.println(light);

    float humidity;
    uint8_t hbuff[] = { buf[9], buf[8], buf[7], buf[6] };
    memcpy(&humidity, &hbuff, sizeof(humidity));
    Serial.print("H: ");
    Serial.println(humidity);

    float temperature;
    uint8_t pbuff[] = { buf[13], buf[12], buf[11], buf[10] };
    memcpy(&temperature, &pbuff, sizeof(temperature));
    Serial.print("L: ");
    Serial.println(temperature);

    Serial.println();
  }
}
