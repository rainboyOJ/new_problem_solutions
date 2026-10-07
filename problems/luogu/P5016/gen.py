#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 25)
    m = random.randint(2, n - 1)
    p1 = random.randint(1, n)
    s1 = random.randint(1, 50)
    s2 = random.randint(1, 50)
    print(n)
    print(" ".join(str(random.randint(1, 50)) for _ in range(n)))
    print(m, p1, s1, s2)


if __name__ == "__main__":
    main()
