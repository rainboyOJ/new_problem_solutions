directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]


def move(row, col, direction):
    dr, dc = directions[direction]
    nr = row + dr
    nc = col + dc

    if not (0 <= nr < 10 and 0 <= nc < 10) or grid[nr][nc] == "*":
        return row, col, (direction + 1) % 4
    return nr, nc, direction


grid = [input().strip() for _ in range(10)]

for r in range(10):
    for c in range(10):
        if grid[r][c] == "C":
            cow_row, cow_col = r, c
        elif grid[r][c] == "F":
            farmer_row, farmer_col = r, c

cow_direction = 0
farmer_direction = 0
seen = set()
minutes = 0

while True:
    state = (
        cow_row, cow_col, cow_direction,
        farmer_row, farmer_col, farmer_direction,
    )
    if state in seen:
        print(0)
        break
    seen.add(state)

    cow_row, cow_col, cow_direction = move(cow_row, cow_col, cow_direction)
    farmer_row, farmer_col, farmer_direction = move(
        farmer_row, farmer_col, farmer_direction
    )
    minutes += 1

    if cow_row == farmer_row and cow_col == farmer_col:
        print(minutes)
        break
