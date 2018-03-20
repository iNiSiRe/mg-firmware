# A blank Mongoose OS app

## Overview

This is an empty app, serves as a skeleton for building Mongoose OS
apps from scratch.

## How to install this app

- Install and start [mos tool](https://mongoose-os.com/software.html)
- Switch to the Project page, find and import this app, build and flash it:

<p align="center">
  <img src="https://mongoose-os.com/images/app1.gif" width="75%">
</p>

Version: 1.19
Build ID: 1.19+0ec60a3~xenial0
Update channel: release

mos build --platform=esp8266 --local --verbose
curl -v -F file=@build/fw.zip -F commit_timeout=60 http://192.168.31.142/update

https://github.com/cesanta/mongoose-os.git