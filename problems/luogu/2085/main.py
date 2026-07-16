import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, required = next(data), next(data)
functions = [(next(data), next(data), next(data)) for _ in range(n)]


def value(function, x):
    a, b, c = functions[function]
    return a * x * x + b * x + c


heap = [(value(i, 1), i, 1) for i in range(n)]
heapq.heapify(heap)
answers = []
for _ in range(required):
    result, function, x = heapq.heappop(heap)
    answers.append(str(result))
    x += 1
    heapq.heappush(heap, (value(function, x), function, x))
print(*answers)
