#!/usr/bin/env python3
import random


def main():
    random.seed()
    a = random.randint(1, 50)
    b = random.randint(a, 50)
    c = random.randint(b, 50)

    values = [
        a,
        b,
        c,
        a + b,
        a + c,
        b + c,
        a + b + c,
    ]
    random.shuffle(values)

    print(" ".join(str(x) for x in values))


if __name__ == "__main__":
    main()
