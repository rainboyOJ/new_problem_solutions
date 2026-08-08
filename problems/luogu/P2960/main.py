import sys
from collections import deque


input = sys.stdin.buffer.readline
width, height, start_x, start_y = map(int, input().split())
field = [input().strip() for _ in range(height)]
start = (height - start_y, start_x - 1)
queue = deque([start])
distance = {start: 0}

while queue:
    row, column = queue.popleft()
    for dr in (-1, 0, 1):
        for dc in (-1, 0, 1):
            neighbor = row + dr, column + dc
            if (neighbor not in distance and 0 <= neighbor[0] < height
                    and 0 <= neighbor[1] < width and field[neighbor[0]][neighbor[1]] == 46):
                distance[neighbor] = distance[(row, column)] + 1
                queue.append(neighbor)
print(max(distance.values()))
