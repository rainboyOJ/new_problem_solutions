from collections import deque


n, m, start_x, start_y = map(int, input().split())
distance = [[-1] * m for _ in range(n)]
distance[start_x - 1][start_y - 1] = 0
queue = deque([(start_x - 1, start_y - 1)])
moves = ((-2, -1), (-2, 1), (-1, -2), (-1, 2),
         (1, -2), (1, 2), (2, -1), (2, 1))

while queue:
    x, y = queue.popleft()
    for dx, dy in moves:
        nxt_x, nxt_y = x + dx, y + dy
        if 0 <= nxt_x < n and 0 <= nxt_y < m and distance[nxt_x][nxt_y] == -1:
            distance[nxt_x][nxt_y] = distance[x][y] + 1
            queue.append((nxt_x, nxt_y))

print("\n".join(" ".join(map(str, row)) for row in distance))
