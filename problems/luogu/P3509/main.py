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
n, k, moves = next(data), next(data), next(data)
position = array("q", (next(data) for _ in range(n)))
transition = array("i", [0]) * n
left, right = 0, k

for i in range(n):
    while right + 1 < n and position[right + 1] - position[i] < position[i] - position[left]:
        left += 1
        right += 1
    transition[i] = right if position[right] - position[i] > position[i] - position[left] else left

answer = array("i", range(n))
while moves:
    if moves & 1:
        answer = array("i", map(transition.__getitem__, answer))
    moves >>= 1
    if moves:
        transition = array("i", map(transition.__getitem__, transition))

write = sys.stdout.write
for start in range(0, n, 8192):
    block = " ".join(str(x + 1) for x in answer[start:start + 8192])
    write(("" if start == 0 else " ") + block)
write("\n")
