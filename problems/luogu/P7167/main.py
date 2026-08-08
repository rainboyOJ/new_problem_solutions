import sys
from array import array


data = iter(map(int, sys.stdin.buffer.read().split()))
n, queries = next(data), next(data)
diameter = array("q", [0]) * n
capacity = array("q", [0]) * (n + 1)
for i in range(n):
    diameter[i], capacity[i] = next(data), next(data)

next_larger = array("i", [n]) * (n + 1)
stack = []
for i, value in enumerate(diameter):
    while stack and diameter[stack[-1]] < value:
        next_larger[stack.pop()] = i
    stack.append(i)

levels = n.bit_length() + 1
jump = [next_larger]
total = [capacity]
for _ in range(1, levels):
    previous_jump, previous_total = jump[-1], total[-1]
    jump.append(array("i", (previous_jump[previous_jump[i]] for i in range(n + 1))))
    total.append(array("q", (previous_total[i] + previous_total[previous_jump[i]]
                             for i in range(n + 1))))

answers = []
for _ in range(queries):
    current, water = next(data) - 1, next(data)
    for level in range(levels - 1, -1, -1):
        if current < n and total[level][current] < water:
            water -= total[level][current]
            current = jump[level][current]
    answers.append(str(current + 1 if current < n else 0))
print("\n".join(answers))
