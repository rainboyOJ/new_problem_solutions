#!/usr/bin/env python3
import random


def main():
    random.seed()

    row_cnt = random.randint(1, 6)
    col_cnt = random.randint(1, 6)
    tot = row_cnt * col_cnt
    k = random.randint(0, 12)

    print(row_cnt, col_cnt)
    print(k)
    for _ in range(k):
        x = random.randint(1, tot)
        y = random.randint(1, tot)
        print(x, y)


if __name__ == "__main__":
    main()
