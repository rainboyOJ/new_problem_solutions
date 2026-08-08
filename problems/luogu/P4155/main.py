import sys
from array import array


data = iter(map(int, sys.stdin.buffer.read().split()))
n, circumference = next(data), next(data)
intervals = []
for identity in range(n):
    left, right = next(data), next(data)
    if right < left:
        right += circumference
    intervals.append((left, right, identity))
intervals.sort()
intervals += [(left + circumference, right + circumference, identity)
              for left, right, identity in intervals]

size = 2 * n
next_interval = array("i", [0]) * size
right_pointer = 0
for i, (_, right, _) in enumerate(intervals):
    right_pointer = max(right_pointer, i)
    while right_pointer + 1 < size and intervals[right_pointer + 1][0] <= right:
        right_pointer += 1
    next_interval[i] = right_pointer

jump = [next_interval]
for _ in range(1, n.bit_length() + 1):
    previous = jump[-1]
    jump.append(array("i", map(previous.__getitem__, previous)))

answer = [0] * n
for start in range(n):
    limit = intervals[start][0] + circumference
    current = start
    used = 1
    for level in range(len(jump) - 1, -1, -1):
        destination = jump[level][current]
        if intervals[destination][1] < limit:
            current = destination
            used += 1 << level
    answer[intervals[start][2]] = used + 1

print(*answer)
