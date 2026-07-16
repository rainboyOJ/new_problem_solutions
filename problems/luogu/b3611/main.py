import sys


input = sys.stdin.buffer.readline
n = int(input())
rows = []
for _ in range(n):
    mask = 0
    for index, value in enumerate(map(int, input().split())):
        mask |= value << index
    rows.append(mask)
for middle in range(n):
    middle_bit = 1 << middle
    middle_row = rows[middle]
    for start in range(n):
        if rows[start] & middle_bit:
            rows[start] |= middle_row
for mask in rows:
    print(*(mask >> index & 1 for index in range(n)))
