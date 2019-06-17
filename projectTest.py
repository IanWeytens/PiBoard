from RPi import GPIO
import math
import time
import os
from LCD import Lcd

import serial
port ="/dev/ttyUSB0"

s1 = serial.Serial(port,9600)
s1.flushInput()

GPIO.setmode(GPIO.BCM)
rs = 26
e = 19
d0 = 13
d1 = 6
d2 = 22
d3 = 24
d4 = 21
d5 = 20
d6 = 16
d7 = 12
backlight = 0

IpAddress = os.popen('ip addr show wlan0').read().split("inet ")[1].split("/")[0]
lcd = Lcd(rs, e , d0, d1, d2, d3, d4, d5, d6, d7, backlight)
lcd.clear_display()
lcd.stuur_zin(IpAddress)
lcd.go_2nd_row()

print("test")
escwaarde = "start"
try:
    while True:
        escwaarde = "trala"
        if s1.inWaiting()>0:
            inputValue=s1.read(1)
            print(inputValue)
            esc = str(inputValue)
            print(esc[2:-1])
            lcd.clear_display()

            lcd.stuur_zin(IpAddress)
            lcd.go_2nd_row()

            lcd.stuur_zin(esc[2:-1]) #filtert de rare dingen weg g
except KeyboardInterrupt:
    raise
except:
    lcd.clear_display()
    lcd.stuur_zin("Afgesloten")
    print("afgesloten")
#
# def balkjes(waarde):
#     waarde = waarde / 9.0 * 16.0
#     return waarde
