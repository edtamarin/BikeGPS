# BikeGPS
ESP-based implementation of a GPS sensor and an OLED display. Intended to be used as a bike computer.
## Features
This system is using a GPS receiver to give the user feedback on his bike ride. Currently planned features are:
* Heading and position readouts  - **implemented**
* Time and # of satellites in LOS readouts - **implemented**
* Speed readout - *not implemented*
* Destination tracking - *not implemented*
* JSON route output - *not implemented*
## Hardware
* WeMos D1 mini (ESP8266-based chip)
* Monochrome 0.96" OLED
* u-Blox Neo-6M (GPS receiver)
* Power circuitry coming soon!
## Software dependencies
Since the main chip is based on ESP8266, ESP Arduino core is used.
Other libraries used in this project:
* [OLED display controller (SSD1306)](https://github.com/squix78/esp8266-oled-ssd1306)
* [ESP Software Serial](https://github.com/plerup/espsoftwareserial)
