# ESP8266/ESP32 firmware for smart home
Based on Mongoose OS

## How to build

mos build --platform=esp8266 --local --verbose

## How to perform OTA update

curl -v -F file=@build/fw.zip -F commit_timeout=60 http://192.168.31.142/update

## Links

https://github.com/cesanta/mongoose-os.git