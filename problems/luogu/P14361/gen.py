#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)

    for _ in range(t):
        n = random.choice([2, 4, 6, 8, 10])
        print(n)
        for _ in range(n):
            if random.randint(1, 5) == 1:
                x = random.randint(0, 20)
                print(x, x, random.randint(0, 20))
            else:
                print(random.randint(0, 20), random.randint(0, 20), random.randint(0, 20))


if __name__ == "__main__":
    main()
