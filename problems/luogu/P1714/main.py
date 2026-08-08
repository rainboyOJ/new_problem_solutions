import os
from array import array


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
n, limit = next(data), next(data)
queue_index = array("i", [0]) * (n + 1)
queue_value = array("q", [0]) * (n + 1)
head, tail = 0, 1
prefix = 0
answer = -10**30

for i in range(1, n + 1):
    prefix += next(data)
    while head < tail and queue_index[head] < i - limit:
        head += 1
    answer = max(answer, prefix - queue_value[head])
    while head < tail and queue_value[tail - 1] >= prefix:
        tail -= 1
    queue_index[tail] = i
    queue_value[tail] = prefix
    tail += 1

print(answer)
