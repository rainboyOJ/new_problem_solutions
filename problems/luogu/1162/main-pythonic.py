from collections import deque

n = int(input())
grid = [[0] * (n + 2)]
grid += [[0, *map(int, input().split()), 0] for _ in range(n)]
grid += [[0] * (n + 2)]

grid[0][0] = -1
queue = deque([(0, 0)])
while queue:
    x, y = queue.popleft()
    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        nxt_x, nxt_y = x + dx, y + dy
        if 0 <= nxt_x < n + 2 and 0 <= nxt_y < n + 2 and grid[nxt_x][nxt_y] == 0:
            grid[nxt_x][nxt_y] = -1
            queue.append((nxt_x, nxt_y))

for row in grid[1:n + 1]:
    print(*(2 if value == 0 else max(value, 0) for value in row[1:n + 1]))
