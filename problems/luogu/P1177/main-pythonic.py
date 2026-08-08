import sys
data = list(map(int, sys.stdin.buffer.read().split()))
print(*sorted(data[1:1 + data[0]]))
