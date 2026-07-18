from collections import deque
from math import inf

danger = {}
affected = ((0, 0), (1, 0), (-1, 0), (0, 1), (0, -1))

for _ in range(int(input())):
    x, y, time = map(int, input().split())
    for dx, dy in affected:
        point = x + dx, y + dy
        if point[0] >= 0 and point[1] >= 0:
            danger[point] = min(danger.get(point, inf), time)

queue = deque([] if danger.get((0, 0)) == 0 else [(0, 0, 0)])
visited = {(0, 0)}
answer = -1

while queue:
    x, y, time = queue.popleft()
    if (x, y) not in danger:
        answer = time
        break

    next_time = time + 1
    for dx, dy in affected[1:]:
        point = x + dx, y + dy
        if point[0] < 0 or point[1] < 0 or point in visited:
            continue
        if next_time >= danger.get(point, inf):
            continue
        visited.add(point)
        queue.append((*point, next_time))

print(answer)
