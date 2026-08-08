n, m, horse_x, horse_y = map(int, input().split())

blocked = [[False] * (m + 1) for _ in range(n + 1)]

for dx, dy in [
    (0, 0),
    (1, 2),
    (2, 1),
    (2, -1),
    (1, -2),
    (-1, -2),
    (-2, -1),
    (-2, 1),
    (-1, 2),
]:
    x = horse_x + dx
    y = horse_y + dy
    if 0 <= x <= n and 0 <= y <= m:
        blocked[x][y] = True

dp = [[0] * (m + 1) for _ in range(n + 1)]
dp[0][0] = 1

for x in range(n + 1):
    for y in range(m + 1):
        if blocked[x][y]:
            dp[x][y] = 0
            continue
        if x == 0 and y == 0:
            continue
        if x > 0:
            dp[x][y] += dp[x - 1][y]
        if y > 0:
            dp[x][y] += dp[x][y - 1]

print(dp[n][m])
