import RPI.GPIO as GPIO
from serial import Serial
import convert
import numpy as np

GPIO.setmode(GPIO.BCM)

ser = Serial("/dev/ttyACM0", 9600, timeout=1)
# ser.open()
# ser.write()

try:
    while True:
        if ser.readable():
            data = ser.readline()

except:
    ser.close()