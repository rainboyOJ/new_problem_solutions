#!/usr/bin/env python3
import random


def main():
    n = random.randint(2, 8)
    m = random.randint(n - 1, 35)
    A = random.randint(0, 4)
    B = random.randint(0, 12)
    C = random.randint(0, 12)

    trains = []
    now = 0
    # 先造一条保证可行的链。
    for s in range(1, n):
        p = now + random.randint(0, 4)
        q = p + random.randint(1, 4)
        trains.append((s, s + 1, p, q))
        now = q

    while len(trains) < m:
        x = random.randint(1, n - 1)
        y = random.randint(x + 1, n) if random.random() < 0.7 else random.randint(1, n)
        if x == y:
            continue
        p = random.randint(0, 20)
        q = random.randint(p + 1, min(30, p + 8))
        trains.append((x, y, p, q))

    random.shuffle(trains)

    print(n, len(trains), A, B, C)
    for item in trains:
        print(*item)


if __name__ == "__main__":
    main()
