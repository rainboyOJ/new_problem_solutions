#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 20)
    print(t)
    for _ in range(t):
        n = random.randint(2, 8)
        c = random.randint(1, 5)
        q = random.randint(1, min(n - 1, 4))
        print(n, q, c)

        arr = []
        for _ in range(n):
            if random.random() < 0.45:
                arr.append(0)
            else:
                arr.append(random.randint(1, c))
        print(" ".join(map(str, arr)))

        used = set()
        for _ in range(q):
            while True:
                a = random.randint(1, n - 1)
                if a not in used:
                    used.add(a)
                    break
            h = random.randint(a + 1, n)
            print(a, h)


if __name__ == "__main__":
    main()
