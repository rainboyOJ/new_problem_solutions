#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    m = random.randint(1, 6)
    print(n, m)
    print(" ".join(str(random.randint(1, 20)) for _ in range(n)))
    print(" ".join(str(random.randint(1, m)) for _ in range(n)))


if __name__ == "__main__":
    main()
