import sys


data = list(map(int, sys.stdin.read().split()))
n = data[0]
runs = data[1:]

cells = []
value = "0"

for length in runs:
    cells.extend(value for _ in range(length))
    value = "1" if value == "0" else "0"

for row in range(n):
    left = row * n
    right = left + n
    print("".join(cells[left:right]))
