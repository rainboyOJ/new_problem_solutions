directions = [
    (-1, -1), (-1, 0), (-1, 1),
    (0, -1),           (0, 1),
    (1, -1),  (1, 0),  (1, 1),
]

n, m = map(int, input().split())
grid = [input().strip() for _ in range(n)]
answer = []

for row in range(n):
    current = []
    for col in range(m):
        if grid[row][col] == "*":
            current.append("*")
            continue

        count = 0
        for dr, dc in directions:
            nr = row + dr
            nc = col + dc
            if 0 <= nr < n and 0 <= nc < m and grid[nr][nc] == "*":
                count += 1
        current.append(str(count))

    answer.append("".join(current))

print("\n".join(answer))
