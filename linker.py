import serial
import numpy as np
import pyvista as pv

from config import POINTCLOUD_PATH

buffer = ""

ser = serial.Serial()

ser.port = "/dev/tty.usbmodem21201"
ser.baudrate = 9600
ser.timeout = 0

ser.open()

with open(POINTCLOUD_PATH, 'w') as file:
    while True:
        if ser.readable():
            received = ser.readline()
            print(received)

            if received == "ended": break;
            else:
                file.wrtie(received)

    ser.close()