import random
import math
from config import POINTCLOUD_PATH

radius = 0.0

with open(POINTCLOUD_PATH, "w", encoding="utf-8") as file:
    for i in range(10):
        for j in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (j + 1)))
            data[1] = str(radius * math.cos(5 * 1.8 * (j + 1)))
            data[2] = str("0.0")

            file.write(", ".join(data) + "\n")

        radius += 0.5

    radius = 5.0

    for i in range(40):
        for j in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (j + 1)) + (random.randint(1, 9) / 25))
            data[1] = str(radius * math.cos(5 * 1.8 * (j + 1)) + (random.randint(1, 9) / 25))
            data[2] = str(0.5 * (i + 1))

            file.write(", ".join(data) + "\n")

    for i in range(3):
        radius -= 0.1
        for j in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (j + 1)) + (random.randint(1, 9) / 25))
            data[1] = str(radius * math.cos(5 * 1.8 * (j + 1)) + (random.randint(1, 9) / 25))
            data[2] = str(0.25 * (i + 1) + 20)

            file.write(", ".join(data) + "\n")

    radius += 0.1

    for i in range(2):
        radius += 0.1
        for j in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (j + 1)) + (random.randint(1, 9) / 25))
            data[1] = str(radius * math.cos(5 * 1.8 * (j + 1)) + (random.randint(1, 9) / 25))
            data[2] = str(0.25 * (i + 1) + 20.75)

            file.write(", ".join(data) + "\n")

    radius = 0.0

    for i in range(10):
        for j in range(40):
            data = ["", "", ""]
            data[0] = str(radius * math.sin(5 * 1.8 * (j + 1)))
            data[1] = str(radius * math.cos(5 * 1.8 * (j + 1)))
            data[2] = str("21.25")

            file.write(", ".join(data) + "\n")

        radius += 0.5