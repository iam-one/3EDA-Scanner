import serial
import numpy as np
import pyvista as pv

from config import POINTCLOUD_PATH

ser = serial.Serial()

ser.port = "/dev/tty.usbmodem1201"
ser.baudrate = 9600
ser.timeout = 1

ser.open()

with open(POINTCLOUD_PATH, 'w', encoding="utf-8") as file:
    while True:
        if ser.readable():
            received = str(ser.readline())
            received = received.split("\'")[1].split("\\r")[0]
            print(received)

            if received == "ended": break;
            elif received != "limited" and received != "": file.write(received + "\n")

    ser.close()