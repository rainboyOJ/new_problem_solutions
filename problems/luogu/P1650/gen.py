#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    a = [str(random.randint(1, 20)) for _ in range(n)]
    b = [str(random.randint(1, 20)) for _ in range(n)]
    print(" ".join(a))
    print(" ".join(b))


if __name__ == "__main__":
    main()
