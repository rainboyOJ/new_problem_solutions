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
n, kinds = next(data), next(data)
artists = array("H", (next(data) for _ in range(n)))
counts = [0] * (kinds + 1)
left = covered = 0
answer = (0, n - 1)

for right, artist in enumerate(artists):
    if counts[artist] == 0:
        covered += 1
    counts[artist] += 1
    while covered == kinds:
        if right - left < answer[1] - answer[0]:
            answer = (left, right)
        counts[artists[left]] -= 1
        if counts[artists[left]] == 0:
            covered -= 1
        left += 1

print(answer[0] + 1, answer[1] + 1)
