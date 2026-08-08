import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


data = read_all_ints()
n = data[0]
a = data[1:1 + n]
answer = 0
for left in range(n):
    right = left
    while right + 1 < n and a[right + 1] == a[right] + 1:
        right += 1
    answer = max(answer, right - left + 1)
print(answer)
