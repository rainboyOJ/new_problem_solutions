#!/usr/bin/env python3
import random


def produce_h(p):
    p = p[:]
    h = []
    while len(p) > 1:
        if p[0] > p[-1]:
            h.append(p[1])
            p = p[1:]
        else:
            h.append(p[-2])
            p = p[:-1]
    return h


def main():
    random.seed()
    t = random.randint(1, 20)
    print(t)
    for _ in range(t):
        n = random.randint(2, 8)
        print(n)
        if random.randint(0, 1) == 0:
            p = list(range(1, n + 1))
            random.shuffle(p)
            h = produce_h(p)
        else:
            h = [random.randint(1, n) for _ in range(n - 1)]
        print(" ".join(map(str, h)))


if __name__ == "__main__":
    main()
