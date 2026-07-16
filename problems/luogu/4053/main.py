import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
buildings = sorted(((next(data), next(data)) for _ in range(next(data))),
                   key=lambda item: item[1])
chosen = []
elapsed = 0

for duration, deadline in buildings:
    if elapsed + duration <= deadline:
        elapsed += duration
        heapq.heappush(chosen, -duration)
    elif chosen and -chosen[0] > duration:
        elapsed += duration + heapq.heapreplace(chosen, -duration)

print(len(chosen))
