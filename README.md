<p align="center">
  <img width=430 src="https://i.imgur.com/5b2XJhy.png"><br/>
  :sparkles: :floppy_disk: :herb: hack the plant :herb: :floppy_disk: :sparkles: 
</p>

# creepers
A network is composed of many creepers and a single taproot.

Each creeper is a sensor for one or more plants. It is composed of:
- An Arduino-compatible microcontroller (Arduino Uno, Arduino MEGA 2560, ATmega328, etc.)
- A humidity/temperature sensor ([HTU21D](https://learn.sparkfun.com/tutorials/htu21d-humidity-sensor-hookup-guide))
- A simple [photocell](https://learn.sparkfun.com/tutorials/photocell-hookup-guide)
- One or more soil sensors ([SEN-13322](https://www.sparkfun.com/products/13322))
- An RF link transmitter/receiver pair (such as [this 433 MHz kit](https://www.itead.cc/wiki/433Mhz_RF_Link_kit))
- One or more plants! 

The taproot is TBD; it will likely consist of:
- A Raspberry Pi
- An RF link transmitter/receiver pair
- A USB WiFi adapter
