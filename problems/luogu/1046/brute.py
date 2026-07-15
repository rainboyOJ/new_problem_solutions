import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


data = read_all_ints()
heights = data[:10]
reach = data[10] + 30
answer = 0
for height in heights:
    if height <= reach:
        answer += 1
print(answer, end="")
