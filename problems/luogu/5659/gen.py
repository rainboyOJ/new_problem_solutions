#!/usr/bin/env python3
import random


def main():
    random.seed()

    test_count = random.randint(1, 3)
    print(test_count)

    for _ in range(test_count):
        n = random.randint(1, 8)
        perm = list(range(1, n + 1))
        random.shuffle(perm)

        print(n)
        print(" ".join(map(str, perm)))

        for i in range(2, n + 1):
            parent = random.randint(1, i - 1)
            print(parent, i)


if __name__ == "__main__":
    main()
