#!/usr/bin/env python3
import random


def gen_case(n):
    pushed = list(range(1, n + 1))
    poped = list(range(1, n + 1))
    random.shuffle(poped)
    print(n)
    print(" ".join(map(str, pushed)))
    print(" ".join(map(str, poped)))


def main():
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        gen_case(n)


if __name__ == "__main__":
    main()
