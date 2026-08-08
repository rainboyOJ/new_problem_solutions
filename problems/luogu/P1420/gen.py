#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    a = [random.randint(1, 20)]
    for _ in range(1, n):
        if random.random() < 0.5:
            a.append(a[-1] + 1)
        else:
            a.append(random.randint(1, 20))
    print(n)
    print(*a)


if __name__ == "__main__":
    main()
