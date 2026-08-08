import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
a = data[1:1 + n]
diffs = sorted(map(lambda pair: abs(pair[1] - pair[0]), zip(a, a[1:])))
print("Jolly" if diffs == list(range(1, n)) else "Not jolly")
