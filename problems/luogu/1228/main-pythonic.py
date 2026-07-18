def cover(top, left, size, special_x, special_y):
    if size == 1:
        return

    half = size // 2
    mid_x = top + half - 1
    mid_y = left + half - 1

    if special_x <= mid_x and special_y <= mid_y:
        answers.append((mid_x + 1, mid_y + 1, 1))
        cover(top, left, half, special_x, special_y)
        cover(top, left + half, half, mid_x, mid_y + 1)
        cover(top + half, left, half, mid_x + 1, mid_y)
        cover(top + half, left + half, half, mid_x + 1, mid_y + 1)
    elif special_x <= mid_x and special_y > mid_y:
        answers.append((mid_x + 1, mid_y, 2))
        cover(top, left, half, mid_x, mid_y)
        cover(top, left + half, half, special_x, special_y)
        cover(top + half, left, half, mid_x + 1, mid_y)
        cover(top + half, left + half, half, mid_x + 1, mid_y + 1)
    elif special_x > mid_x and special_y <= mid_y:
        answers.append((mid_x, mid_y + 1, 3))
        cover(top, left, half, mid_x, mid_y)
        cover(top, left + half, half, mid_x, mid_y + 1)
        cover(top + half, left, half, special_x, special_y)
        cover(top + half, left + half, half, mid_x + 1, mid_y + 1)
    else:
        answers.append((mid_x, mid_y, 4))
        cover(top, left, half, mid_x, mid_y)
        cover(top, left + half, half, mid_x, mid_y + 1)
        cover(top + half, left, half, mid_x + 1, mid_y)
        cover(top + half, left + half, half, special_x, special_y)

k = int(input())
x, y = map(int, input().split())

answers = []
cover(1, 1, 1 << k, x, y)

print("\n".join(f"{row} {col} {shape}" for row, col, shape in answers))
