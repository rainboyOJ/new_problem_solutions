import sys
from array import array


data = iter(map(int, sys.stdin.buffer.read().split()))
n, queries = next(data), next(data)
heights = array("i", (next(data) for _ in range(n)))
logs = [0] * (n + 1)
for i in range(2, n + 1):
    logs[i] = logs[i // 2] + 1

minimum = [heights]
maximum = [heights]
level = 1
while 1 << level <= n:
    half = 1 << (level - 1)
    length = n - (1 << level) + 1
    previous_min, previous_max = minimum[-1], maximum[-1]
    minimum.append(array("i", (min(previous_min[i], previous_min[i + half])
                               for i in range(length))))
    maximum.append(array("i", (max(previous_max[i], previous_max[i + half])
                               for i in range(length))))
    level += 1

answers = []
for _ in range(queries):
    left, right = next(data) - 1, next(data) - 1
    level = logs[right - left + 1]
    start = right - (1 << level) + 1
    high = max(maximum[level][left], maximum[level][start])
    low = min(minimum[level][left], minimum[level][start])
    answers.append(str(high - low))
print("\n".join(answers))
