from collections import deque

n, m = map(int, input().split())
field = [list(input().strip()) for _ in range(n)]
directions = [
    (dx, dy)
    for dx in (-1, 0, 1)
    for dy in (-1, 0, 1)
    if (dx, dy) != (0, 0)
]
ponds = 0

for start_x in range(n):
    for start_y in range(m):
        if field[start_x][start_y] != "W":
            continue
        ponds += 1
        field[start_x][start_y] = "."
        queue = deque([(start_x, start_y)])
        while queue:
            x, y = queue.popleft()
            for dx, dy in directions:
                nxt_x, nxt_y = x + dx, y + dy
                if 0 <= nxt_x < n and 0 <= nxt_y < m and field[nxt_x][nxt_y] == "W":
                    field[nxt_x][nxt_y] = "."
                    queue.append((nxt_x, nxt_y))

print(ponds)
