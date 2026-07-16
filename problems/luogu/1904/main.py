import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
events = []
for left, height, right in zip(data, data, data):
    events += [(left, -height, right), (right, 0, 0)]
events.sort()

heap = [(0, 10**30)]
answer = []
i = 0
while i < len(events):
    x = events[i][0]
    while i < len(events) and events[i][0] == x:
        _, negative_height, right = events[i]
        if negative_height:
            heapq.heappush(heap, (negative_height, right))
        i += 1
    while heap[0][1] <= x:
        heapq.heappop(heap)
    height = -heap[0][0]
    if not answer or answer[-1] != height:
        answer += [x, height]

print(*answer)
