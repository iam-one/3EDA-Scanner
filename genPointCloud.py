import random

with open("./sample.txt", "w", encoding="utf-8") as file:
    for i in range(10000):
        data = ["", "", ""]
        for i in range(len(data)): data[i] = str(round((0.5 - random.random()) * 10.0, 6))

        file.write(", ".join(data) + "\n")