#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(3, 18)
    print(n)

    parents = []
    for i in range(1, n):
        parents.append(str(random.randint(0, i - 1)))
    print(" ".join(parents))

    q = random.randint(1, 10)
    print(q)

    for _ in range(q):
        m = random.randint(2, min(n, 8))
        people = random.sample(range(n), m)
        print(m, *people)


if __name__ == "__main__":
    main()
