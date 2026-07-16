import os
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
n, m = next(data), next(data)
rooms = array("q", (next(data) for _ in range(n)))
amount = array("q", [0]) * m
start = array("i", [0]) * m
end = array("i", [0]) * m
for i in range(m):
    amount[i], start[i], end[i] = next(data), next(data) - 1, next(data)


def feasible(count):
    difference = array("q", [0]) * (n + 1)
    for i in range(count):
        difference[start[i]] += amount[i]
        difference[end[i]] -= amount[i]
    used = 0
    for available, change in zip(rooms, difference):
        used += change
        if used > available:
            return False
    return True


if feasible(m):
    print(0)
else:
    left, right = 1, m
    while left < right:
        middle = (left + right) // 2
        if feasible(middle):
            left = middle + 1
        else:
            right = middle
    print(-1, left, sep="\n")
