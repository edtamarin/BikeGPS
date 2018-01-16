# BikeGPS
ESP-based implementation of a GPS sensor and an OLED display. Intended to be used as a bike computer.
# Hardware
* WeMos D1 mini (ESP8266-based chip)
* Monochrome 0.96" OLED
* u-Blox Neo-6M (GPS receiver)
# Software dependencies
Since the main chip is based on ESP8266, ESP Arduino core is used.
Other libraries used in this project:
* [OLED display controller (SSD1306)](https://github.com/squix78/esp8266-oled-ssd1306)
* [ESP Software Serial](https://github.com/plerup/espsoftwareserial)
