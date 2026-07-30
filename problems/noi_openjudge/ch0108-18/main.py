size = int(input())
image = [list(map(int, input().split())) for _ in range(size)]

for top in range(size):
    for left in range(size):
        if image[top][left] != 0:
            continue
        right = left
        while right < size and image[top][right] == 0:
            right += 1
        bottom = top
        while bottom < size and image[bottom][left] == 0:
            bottom += 1
        print(max(0, bottom - top - 2) * max(0, right - left - 2))
        raise SystemExit

print(0)
