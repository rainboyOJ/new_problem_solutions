import heapq
import sys
from bisect import bisect_left
from collections import Counter


data = iter(map(int, sys.stdin.buffer.read().split()))
length, width = next(data), next(data)
points = sorted(set((next(data), next(data)) for _ in range(next(data))))

# Rectangles whose left side is the field boundary.
ys = [0, width]
gap_count = Counter({width: 1})
max_gap_heap = [-width]
answer = 0
i = 0
while i < len(points):
    x = points[i][0]
    while max_gap_heap and not gap_count[-max_gap_heap[0]]:
        heapq.heappop(max_gap_heap)
    answer = max(answer, x * -max_gap_heap[0])
    j = i
    while j < len(points) and points[j][0] == x:
        if 0 < x < length:
            y = points[j][1]
            position = bisect_left(ys, y)
            if position == len(ys) or ys[position] != y:
                low, high = ys[position - 1], ys[position]
                gap_count[high - low] -= 1
                for gap in (y - low, high - y):
                    gap_count[gap] += 1
                    heapq.heappush(max_gap_heap, -gap)
                ys.insert(position, y)
        j += 1
    i = j

while max_gap_heap and not gap_count[-max_gap_heap[0]]:
    heapq.heappop(max_gap_heap)
answer = max(answer, length * -max_gap_heap[0])

# Rectangles whose left side passes through a production point.
point_count = len(points)
for left, anchor_y in points:
    lower, upper = 0, width
    split_at_anchor = False
    j = bisect_left(points, (left + 1, -1))
    while j < point_count:
        x, y = points[j]
        if split_at_anchor:
            below, above = anchor_y - lower, upper - anchor_y
            height = below if below > above else above
        else:
            height = upper - lower
        area = (x - left) * height
        if area > answer:
            answer = area
        if y < anchor_y:
            if y > lower:
                lower = y
        elif y > anchor_y:
            if y < upper:
                upper = y
        else:
            split_at_anchor = True
        j += 1
    if split_at_anchor:
        below, above = anchor_y - lower, upper - anchor_y
        height = below if below > above else above
    else:
        height = upper - lower
    area = (length - left) * height
    if area > answer:
        answer = area

print(answer)
