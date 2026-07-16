import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
_ = next(data)
stack = []
answer = 0
for height in data:
    while stack and stack[-1] <= height:
        stack.pop()
    answer += len(stack)
    stack.append(height)
print(answer)
