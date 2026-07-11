#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 5)
    m = random.randint(1, 6)

    cows = []
    used = [False] * 101

    tries = 0
    while len(cows) < n and tries < 2000:
        tries += 1
        length = random.randint(1, 8)
        s = random.randint(1, 100 - length + 1)
        t = s + length - 1
        ok = True
        for x in range(s, t + 1):
            if used[x]:
                ok = False
                break
        if not ok:
            continue
        for x in range(s, t + 1):
            used[x] = True
        c = random.randint(1, 12)
        cows.append((s, t, c))

    n = len(cows)
    max_need = max(c for _, _, c in cows)

    conditioners = []
    for _ in range(m - 1):
        length = random.randint(1, 30)
        a = random.randint(1, 100 - length + 1)
        b = a + length - 1
        p = random.randint(1, 12)
        cost = random.randint(1, 30)
        conditioners.append((a, b, p, cost))

    # 最后一台空调保证全开时一定可行。
    conditioners.append((1, 100, max_need, random.randint(1, 30)))

    print(n, m)
    for cow in cows:
        print(*cow)
    for ac in conditioners:
        print(*ac)


if __name__ == "__main__":
    main()
