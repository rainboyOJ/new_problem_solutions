n, torch_count, glowstone_count = map(int, input().split())

lit = [[False for _ in range(n)] for _ in range(n)]


def light_cell(row, col):
    if 0 <= row < n and 0 <= col < n:
        lit[row][col] = True


for _ in range(torch_count):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    for dx in range(-2, 3):
        for dy in range(-2, 3):
            if abs(dx) + abs(dy) <= 2:
                light_cell(x + dx, y + dy)

for _ in range(glowstone_count):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    for dx in range(-2, 3):
        for dy in range(-2, 3):
            light_cell(x + dx, y + dy)

answer = 0
for row in range(n):
    for col in range(n):
        if not lit[row][col]:
            answer += 1

print(answer)
