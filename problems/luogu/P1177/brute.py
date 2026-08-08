import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
print(*sorted(data[1:1 + n]))
