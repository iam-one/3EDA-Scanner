import RPI.GPIO as GPIO
import serial

import numpy as np
from stl import mesh
import open3d as o3d

GPIO.setmode(GPIO.BCM)

ser = serial.Serial(‘/dev/ttyACM0’, 9600, timeout=1)
# ser.open()
# ser.write()

try:
    while True:
        res = ser.readline()

except:
    ser.close()