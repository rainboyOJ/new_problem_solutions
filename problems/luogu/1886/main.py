import os
import sys
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
n, window = next(data), next(data)
values = array("q", (next(data) for _ in range(n)))


def sliding(better):
    queue = array("i", [0]) * n
    result = array("q")
    head = tail = 0
    for i, value in enumerate(values):
        while head < tail and queue[head] <= i - window:
            head += 1
        while head < tail and better(value, values[queue[tail - 1]]):
            tail -= 1
        queue[tail] = i
        tail += 1
        if i >= window - 1:
            result.append(values[queue[head]])
    return result


def print_line(sequence):
    write = sys.stdout.write
    first = True
    for start in range(0, len(sequence), 8192):
        text = " ".join(map(str, sequence[start:start + 8192]))
        write(("" if first else " ") + text)
        first = False
    write("\n")


print_line(sliding(lambda new, old: new <= old))
print_line(sliding(lambda new, old: new >= old))
