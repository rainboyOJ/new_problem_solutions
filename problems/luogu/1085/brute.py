import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


data = read_all_ints()
answer = 0
best = 8
for day in range(7):
    total = data[day * 2] + data[day * 2 + 1]
    if total > best:
        best = total
        answer = day + 1
print(answer, end="")
