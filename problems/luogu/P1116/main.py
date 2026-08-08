import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
cars = data[1:1 + n]

answer = 0
for i in range(n):
    for j in range(i + 1, n):
        if cars[i] > cars[j]:
            answer += 1

print(answer)
