import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
lower = []
upper = []
answers = []

for index in range(n):
    value = next(data)
    if not lower or value <= -lower[0]:
        heapq.heappush(lower, -value)
    else:
        heapq.heappush(upper, value)
    if len(lower) > len(upper) + 1:
        heapq.heappush(upper, -heapq.heappop(lower))
    elif len(upper) > len(lower):
        heapq.heappush(lower, -heapq.heappop(upper))
    if index % 2 == 0:
        answers.append(str(-lower[0]))

print("\n".join(answers))
