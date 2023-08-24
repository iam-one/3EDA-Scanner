from serial import Serial
from convert import genMesh

buffer = ""

ser = Serial("/dev/ttyACM0", 9600, timeout=1)
ser.open()

try:
    ser.write("Stream is activate.")

    while True:
        if ser.readable(): buffer += ser.readline()
        data = buffer
        buffer = ""

except: ser.close()