import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
_ = next(data)
stack = [0]
answer = 0
for _, height in zip(data, data):
    while stack[-1] > height:
        stack.pop()
    if stack[-1] < height:
        stack.append(height)
        answer += 1
print(answer)
