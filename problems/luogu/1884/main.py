import sys
from collections import Counter


data = iter(map(int, sys.stdin.buffer.read().split()))
events = []
for _ in range(next(data)):
    x1, y1, x2, y2 = (next(data) for _ in range(4))
    low, high = sorted((y1, y2))
    events += [(x1, 1, low, high), (x2, -1, low, high)]
events.sort()


def covered_length(active):
    total = 0
    right = None
    for (left, end), count in sorted(active.items()):
        if not count:
            continue
        if right is None or left > right:
            total += end - left
            right = end
        elif end > right:
            total += end - right
            right = end
    return total


active = Counter()
answer = 0
previous_x = events[0][0]
i = 0
while i < len(events):
    x = events[i][0]
    answer += (x - previous_x) * covered_length(active)
    while i < len(events) and events[i][0] == x:
        _, change, low, high = events[i]
        active[low, high] += change
        i += 1
    previous_x = x

print(answer)
