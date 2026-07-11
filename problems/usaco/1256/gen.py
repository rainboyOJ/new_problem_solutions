#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    a = [random.randint(0, 20) for _ in range(n)]

    print(n)
    for i in range(n):
        line = []
        mn = a[i]
        mx = a[i]
        for j in range(i, n):
            mn = min(mn, a[j])
            mx = max(mx, a[j])
            line.append(mx - mn)
        print(*line)


if __name__ == "__main__":
    main()
