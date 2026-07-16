import sys
from heapq import heappop, heappush


data = list(map(int, sys.stdin.buffer.read().split()))
height = data[0]
steps = data[1:]
base = min(steps)
infinity = height + max(steps) + 1
distance = [infinity] * base
distance[1 % base] = 1
heap = [(1, 1 % base)]
while heap:
    current, residue = heappop(heap)
    if current != distance[residue]:
        continue
    for step in steps:
        next_residue = (residue + step) % base
        candidate = current + step
        if candidate < distance[next_residue]:
            distance[next_residue] = candidate
            heappush(heap, (candidate, next_residue))
print(sum((height - value) // base + 1 for value in distance if value <= height))
