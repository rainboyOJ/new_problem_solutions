#!/usr/bin/env python3
"""对拍数据生成器：两张二等座车票，保证不是同一个座位。"""
import sys

from cyaron import randint

CARS = [f"{i:02d}" for i in range(1, 18) if i not in (1, 16)]
LETTERS = "ABCDF"


def make_ticket(same_car, same_row, mode):
    car = CARS[randint(0, len(CARS) - 1)]
    if mode == "min":            # 最小规模：1 排，只有 A 与 B 两张不同的座位
        return car, f"{1:02d}A", car, f"{1:02d}B"
    car2 = car if same_car else CARS[randint(0, len(CARS) - 1)]
    row = randint(1, 18)
    if same_row:
        row2 = row
    else:
        row2 = randint(1, 18)
        while row2 == row and car2 == car:
            row2 = randint(1, 18)
    seat1 = f"{row:02d}{LETTERS[randint(0, 4)]}"
    seat2 = f"{row2:02d}{LETTERS[randint(0, 4)]}"
    while seat1 == seat2:
        seat2 = f"{row2:02d}{LETTERS[randint(0, 4)]}"
    return car, seat1, car2, seat2


def main():
    mode = sys.argv[1] if len(sys.argv) > 1 else "rand"
    if mode == "max":            # 最大排号、车厢号边界
        c1, c2 = CARS[0], CARS[-1]
        case = (c1, "18F", c2, "18D")
    elif mode == "adj":          # 全部落在过道两侧的邻接与跨过道位置
        car = CARS[randint(0, len(CARS) - 1)]
        row = randint(1, 18)
        left = (car, f"{row:02d}C")
        right = (car, f"{row:02d}D")
        who = randint(0, 1)
        a, b = (left, right) if who == 0 else (right, left)
        case = (a[0], a[1], b[0], b[1])
    else:
        same_car = randint(0, 1) == 1
        same_row = same_car and randint(0, 1) == 1
        case = make_ticket(same_car, same_row, "rand")
    print(*case)


if __name__ == "__main__":
    main()
