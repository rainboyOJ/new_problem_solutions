import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
intervals = sorted((next(data), next(data)) for _ in range(n))
left, right = intervals[0]
answer = 0

for start, end in intervals[1:]:
    if start > right:
        answer += right - left
        left, right = start, end
    else:
        right = max(right, end)

print(answer + right - left)
