import sys
from array import array


data = iter(map(int, sys.stdin.buffer.read().split()))
n, queries = next(data), next(data)
values = array("i", (next(data) for _ in range(n)))
logs = [0] * (n + 1)
for i in range(2, n + 1):
    logs[i] = logs[i // 2] + 1

table = [values]
level = 1
while 1 << level <= n:
    half = 1 << (level - 1)
    previous = table[-1]
    table.append(array("i", (min(previous[i], previous[i + half])
                             for i in range(n - (1 << level) + 1))))
    level += 1

answers = []
for _ in range(queries):
    left, right = next(data) - 1, next(data) - 1
    level = logs[right - left + 1]
    answers.append(str(min(table[level][left], table[level][right - (1 << level) + 1])))
print(*answers)
