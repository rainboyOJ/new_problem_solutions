import sys
data = list(map(int, sys.stdin.buffer.read().split()))
n, m = data[:2]
ids = data[2:2 + n]
print('\n'.join(str(ids[q - 1]) for q in data[2 + n:2 + n + m]))
