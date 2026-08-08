import os
from array import array
from itertools import islice


def read_ints():
    number = 0
    sign = 1
    reading = False
    while chunk := os.read(0, 1 << 20):
        for byte in chunk:
            if 48 <= byte <= 57:
                number = number * 10 + byte - 48
                reading = True
            else:
                if reading:
                    yield sign * number
                    number = 0
                    sign = 1
                    reading = False
                elif byte == 45:
                    sign = -1
    if reading:
        yield sign * number


data = iter(read_ints())
n, operations = next(data), next(data)
difference = array("i", [0]) * (n + 1)
previous = 0
for i in range(n):
    score = next(data)
    difference[i] = score - previous
    previous = score

for _ in range(operations):
    left, right, change = next(data), next(data), next(data)
    difference[left - 1] += change
    difference[right] -= change

score = 0
answer = 1 << 60
for change in islice(difference, n):
    score += change
    answer = min(answer, score)
print(answer)
