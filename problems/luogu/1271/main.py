import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
m = data[1]
votes = data[2:]

count = [0] * (n + 1)
for vote in votes:
    count[vote] += 1

answer = []
for candidate in range(1, n + 1):
    answer.extend([str(candidate)] * count[candidate])

print(" ".join(answer))
