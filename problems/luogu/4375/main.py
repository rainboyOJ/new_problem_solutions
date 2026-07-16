import sys
from itertools import accumulate


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
values = [next(data) for _ in range(n)]
difference = [0] * (n + 1)

for sorted_position, original_position in enumerate(
    sorted(range(n), key=lambda i: (values[i], i))
):
    if original_position < sorted_position:
        difference[original_position + 1] += 1
        difference[sorted_position + 1] -= 1

print(max(1, max(accumulate(difference))))
