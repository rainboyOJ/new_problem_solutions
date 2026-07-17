import sys
from itertools import chain, cycle, islice, repeat

data = list(map(int, sys.stdin.read().split()))
n, runs = data[0], data[1:]
cells = list(chain.from_iterable(repeat(bit, length) for bit, length in zip(cycle("01"), runs)))
for row in range(n):
    print("".join(cells[row * n : (row + 1) * n]))
