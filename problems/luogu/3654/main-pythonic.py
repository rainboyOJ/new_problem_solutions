r, c, k = map(int, input().split())
grid = [input().strip() for _ in range(r)]

if k == 1:
    print(sum(row.count(".") for row in grid))
else:
    answer = 0

    for row in range(r):
        for col in range(c - k + 1):
            if all(grid[row][col + offset] == "." for offset in range(k)):
                answer += 1

    for row in range(r - k + 1):
        for col in range(c):
            if all(grid[row + offset][col] == "." for offset in range(k)):
                answer += 1

    print(answer)
