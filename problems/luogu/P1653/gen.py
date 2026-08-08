#!/usr/bin/env python3
import random


def main():
    random.seed()

    w = random.randint(1, 4)
    l = random.randint(1, 4)

    print(w, l)
    for _ in range(l):
        row = [str(random.randint(0, 4)) for _ in range(w)]
        print(" ".join(row))


if __name__ == "__main__":
    main()
