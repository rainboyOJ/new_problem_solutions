#!/usr/bin/env python3
import random


def main():
    cnt = [[0] * 6 for _ in range(3)]

    for i in range(3):
        small = random.randint(0, 5)
        for _ in range(small):
            j = random.randint(0, 5)
            cnt[i][j] += 1

    x1 = random.randint(-50, 50)
    x2 = random.randint(-50, 50)
    x3 = random.randint(-50, 50)
    print(x1, x2, x3)
    for i in range(3):
        print(*cnt[i])


if __name__ == "__main__":
    main()
