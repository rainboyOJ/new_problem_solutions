import os
import sys
from array import array


def read_ints():
    number = 0
    reading = False
    while chunk := os.read(0, 1 << 20):
        for byte in chunk:
            if 48 <= byte <= 57:
                number = number * 10 + byte - 48
                reading = True
            elif reading:
                yield number
                number = 0
                reading = False
    if reading:
        yield number


data = iter(read_ints())
n, window = next(data), next(data)
indices = array("i", [0]) * n
values = array("i", [0]) * n
head = tail = 0
output = []
write = sys.stdout.write

for i in range(n):
    value = next(data)
    while head < tail and indices[head] <= i - window:
        head += 1
    while head < tail and values[tail - 1] <= value:
        tail -= 1
    indices[tail] = i
    values[tail] = value
    tail += 1
    if i >= window - 1:
        output.append(str(values[head]))
        if len(output) == 8192:
            write("\n".join(output) + "\n")
            output.clear()

if output:
    write("\n".join(output) + "\n")
