import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]

matches = []
index = 1
for _ in range(n):
    start = data[index]
    end = data[index + 1]
    matches.append((end, start))
    index += 2

matches.sort()

answer = 0
last_end = 0
for end, start in matches:
    if start >= last_end:
        answer += 1
        last_end = end

print(answer)
