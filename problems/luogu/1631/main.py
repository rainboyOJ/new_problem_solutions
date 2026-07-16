import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
first = [next(data) for _ in range(n)]
second = [next(data) for _ in range(n)]
heap = [(value + second[0], i, 0) for i, value in enumerate(first)]
heapq.heapify(heap)
answers = []

for _ in range(n):
    result, row, column = heapq.heappop(heap)
    answers.append(result)
    if column + 1 < n:
        column += 1
        heapq.heappush(heap, (first[row] + second[column], row, column))
print(*answers)
