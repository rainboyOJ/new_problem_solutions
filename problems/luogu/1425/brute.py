import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


a, b, c, d = read_all_ints()
start = a * 60 + b
end = c * 60 + d
print(*divmod(end - start, 60), end="")
