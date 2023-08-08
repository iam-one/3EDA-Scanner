from serial import Serial
from convert import genMesh

buffer = ""

ser = Serial("/dev/ttyACM0", 9600, timeout=1)
ser.open()

try:
    while True:
        ser.write("Stream is activate.")
        if ser.readable(): buffer += ser.readline()
        data = buffer
        buffer = ""

except: ser.close()