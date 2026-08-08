import sys
data = list(map(int, sys.stdin.buffer.read().split()))
print(sorted(data[2:2 + data[0]])[data[1]])
