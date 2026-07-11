#!/usr/bin/env python3
import random


def main():
    random.seed()
    base = "abcdeABCDE"
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        letters = random.sample(base, random.randint(1, 4))
        n = random.randint(1, 6)
        s = "".join(random.choice(letters) for _ in range(n))
        target = "".join(random.choice(letters) for _ in range(n))
        print(s)
        print(target)


if __name__ == "__main__":
    main()
