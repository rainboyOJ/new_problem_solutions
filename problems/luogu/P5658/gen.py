#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 20)
    s = "".join(random.choice("()") for _ in range(n))
    print(n)
    print(s)
    if n >= 2:
        parents = [str(random.randint(1, i - 1)) for i in range(2, n + 1)]
        print(" ".join(parents))


if __name__ == "__main__":
    main()
