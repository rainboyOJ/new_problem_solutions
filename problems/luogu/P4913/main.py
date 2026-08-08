import sys
from array import array


input = sys.stdin.buffer.readline
n = int(input())
left = array("i", [0])
right = array("i", [0])

for _ in range(n):
    left_child, right_child = map(int, input().split())
    left.append(left_child)
    right.append(right_child)

nodes = array("i", [1])
depths = array("i", [1])
maximum_depth = 0

while nodes:
    node = nodes.pop()
    depth = depths.pop()
    maximum_depth = max(maximum_depth, depth)
    if left[node]:
        nodes.append(left[node])
        depths.append(depth + 1)
    if right[node]:
        nodes.append(right[node])
        depths.append(depth + 1)

print(maximum_depth)
