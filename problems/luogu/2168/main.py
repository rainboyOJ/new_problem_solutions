import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n, base = next(data), next(data)
heap = [(next(data), 0) for _ in range(n)]
padding = (base - 1 - (n - 1) % (base - 1)) % (base - 1)
heap.extend([(0, 0)] * padding)
heapq.heapify(heap)
total_cost = 0

while len(heap) > 1:
    chosen = [heapq.heappop(heap) for _ in range(base)]
    weight = sum(item[0] for item in chosen)
    depth = max(item[1] for item in chosen) + 1
    total_cost += weight
    heapq.heappush(heap, (weight, depth))

print(total_cost)
print(heap[0][1])
