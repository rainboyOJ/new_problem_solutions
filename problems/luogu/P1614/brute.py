import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


data = read_all_ints()
n, m = data[0], data[1]
a = data[2:2 + n]
answer = min(sum(a[left:left + m]) for left in range(n - m + 1))
print(answer)
