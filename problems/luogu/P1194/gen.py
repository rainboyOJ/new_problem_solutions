#!/usr/bin/env python3
import random


def main():
    random.seed()

    direct_cost = random.randint(0, 15)
    gift_cnt = random.randint(1, 8)
    print(direct_cost, gift_cnt)

    a = [[0] * gift_cnt for _ in range(gift_cnt)]
    for i in range(gift_cnt):
        for j in range(i + 1, gift_cnt):
            w = random.randint(0, 15)
            a[i][j] = w
            a[j][i] = w

    for i in range(gift_cnt):
        print(*a[i])


if __name__ == "__main__":
    main()
