import sys


data = sys.stdin.buffer.read().split()
print(len(set(data[1:])))
