import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
_ = next(data)
current = answer = next(data)
for value in data:
    current = max(value, current + value)
    answer = max(answer, current)
print(answer)
