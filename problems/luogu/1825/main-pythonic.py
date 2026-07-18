from collections import defaultdict, deque

n, m = map(int, input().split())
maze = [input().strip() for _ in range(n)]
portals = defaultdict(list)

for x, row in enumerate(maze):
    for y, cell in enumerate(row):
        if cell == "@":
            start = x, y
        elif cell.isupper():
            portals[cell].append((x, y))

other_end = {
    point: pair[1 - index]
    for pair in portals.values()
    for index, point in enumerate(pair)
}

queue = deque([(*start, 0)])
visited = {start}
answer = -1

while queue:
    x, y, distance = queue.popleft()
    if maze[x][y] == "=":
        answer = distance
        break

    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        nxt = x + dx, y + dy
        if not (0 <= nxt[0] < n and 0 <= nxt[1] < m):
            continue
        if maze[nxt[0]][nxt[1]] == "#":
            continue
        if nxt in other_end:
            nxt = other_end[nxt]
        if nxt not in visited:
            visited.add(nxt)
            queue.append((*nxt, distance + 1))

print(answer)
