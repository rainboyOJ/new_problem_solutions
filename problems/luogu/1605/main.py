n, m, obstacle_count = map(int, input().split())
start_x, start_y, finish_x, finish_y = map(int, input().split())
blocked = {tuple(map(int, input().split())) for _ in range(obstacle_count)}
visited = {(start_x, start_y)}


def dfs(x, y):
    if (x, y) == (finish_x, finish_y):
        return 1

    routes = 0
    for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        nxt = x + dx, y + dy
        if not (1 <= nxt[0] <= n and 1 <= nxt[1] <= m):
            continue
        if nxt in blocked or nxt in visited:
            continue
        visited.add(nxt)
        routes += dfs(*nxt)
        visited.remove(nxt)
    return routes


print(dfs(start_x, start_y))
