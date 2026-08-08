import sys
from array import array
from collections import deque


input = sys.stdin.buffer.readline
rows, columns, side = map(int, input().split())
horizontal_min = []
horizontal_max = []

for _ in range(rows):
    row = list(map(int, input().split()))
    qmin, qmax = deque(), deque()
    row_min, row_max = array("i"), array("i")
    for j, value in enumerate(row):
        while qmin and qmin[0] <= j - side:
            qmin.popleft()
        while qmin and row[qmin[-1]] >= value:
            qmin.pop()
        qmin.append(j)
        while qmax and qmax[0] <= j - side:
            qmax.popleft()
        while qmax and row[qmax[-1]] <= value:
            qmax.pop()
        qmax.append(j)
        if j >= side - 1:
            row_min.append(row[qmin[0]])
            row_max.append(row[qmax[0]])
    horizontal_min.append(row_min)
    horizontal_max.append(row_max)

answer = 1 << 60
for column in range(columns - side + 1):
    qmin, qmax = deque(), deque()
    for i in range(rows):
        while qmin and qmin[0] <= i - side:
            qmin.popleft()
        while qmin and horizontal_min[qmin[-1]][column] >= horizontal_min[i][column]:
            qmin.pop()
        qmin.append(i)
        while qmax and qmax[0] <= i - side:
            qmax.popleft()
        while qmax and horizontal_max[qmax[-1]][column] <= horizontal_max[i][column]:
            qmax.pop()
        qmax.append(i)
        if i >= side - 1:
            answer = min(answer, horizontal_max[qmax[0]][column]
                         - horizontal_min[qmin[0]][column])

print(answer)
