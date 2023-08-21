import random
import math
from config import POINTCLOUD_PATH

radius = 0.0
reduce = False

with open(POINTCLOUD_PATH, "w", encoding="utf-8") as file:
    for t in range(10):
        for i in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (i + 1)))
            data[1] = str(radius * math.cos(5 * 1.8 * (i + 1)))
            data[2] = str("0.0")

            file.write(", ".join(data) + "\n")
        radius += 0.5

    print(radius)

    for m in range(10):
        for i in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (i + 1)))
            data[1] = str(radius * math.cos(5 * 1.8 * (i + 1)))
            data[2] = str(m * 0.5)

            file.write(", ".join(data) + "\n")

    print(radius)
    radius = 0.0

    for b in range(10):
        for i in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (i + 1)))
            data[1] = str(radius * math.cos(5 * 1.8 * (i + 1)))
            data[2] = str("5.0")

            file.write(", ".join(data) + "\n")
        radius += 0.5

    print(radius)