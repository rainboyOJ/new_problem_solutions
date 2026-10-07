#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 18)
    print(n)
    for _ in range(n):
        length = random.randint(1, 8)
        parts = []
        for i in range(length):
            parts.append(random.choice(["s", "c"]))
        print("+".join(parts))


if __name__ == "__main__":
    main()
