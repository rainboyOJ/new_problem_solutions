import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


a, b = read_all_ints()
print((a * 10 + b) // 19)
