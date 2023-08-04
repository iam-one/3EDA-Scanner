from serial import Serial
from convert import genMesh

ser = Serial("/dev/ttyACM0", 9600, timeout=1)
ser.open()
ser.write()

try:
    while True:
        if ser.readable(): data = ser.readline()

except:
    ser.close()