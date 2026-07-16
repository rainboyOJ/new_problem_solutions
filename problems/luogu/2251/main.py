import sys
from collections import deque


data = iter(map(int, sys.stdin.buffer.read().split()))
n, width = next(data), next(data)
values = [next(data) for _ in range(n)]
queue = deque()
answers = []

for i, value in enumerate(values):
    while queue and values[queue[-1]] >= value:
        queue.pop()
    queue.append(i)
    if queue[0] <= i - width:
        queue.popleft()
    if i + 1 >= width:
        answers.append(str(values[queue[0]]))
print("\n".join(answers))
