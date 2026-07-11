#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 20)
    s = "".join(random.choice("LR") for _ in range(n))
    a = [random.randint(1, 10) for _ in range(n)]

    print(n, m)
    print(s)
    print(*a)


if __name__ == "__main__":
    main()
