#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 40)
    q = random.randint(1, 40)
    values = random.sample(range(1, 300), n)
    print(n)
    print(" ".join(map(str, values)))
    print(q)
    for _ in range(q):
        if random.random() < 0.6:
            print(random.choice(values))
        else:
            print(random.randint(1, 300))


if __name__ == "__main__":
    main()
