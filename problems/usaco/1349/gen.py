#!/usr/bin/env python3
import random


def main():
    random.seed()
    tests = random.randint(1, 8)
    print(tests)
    for _ in range(tests):
        n = random.randint(1, 8)
        h = [random.randint(1, 20) for _ in range(n)]
        a = [random.randint(1, 20) for _ in range(n)]
        t = list(range(n))
        random.shuffle(t)

        print(n)
        print(*h)
        print(*a)
        print(*t)


if __name__ == "__main__":
    main()
