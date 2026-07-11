#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 30)
    f = random.randint(1, n)
    alphabet_size = random.randint(2, 6)
    letters = [chr(ord("a") + i) for i in range(alphabet_size)]
    s = "".join(random.choice(letters) for _ in range(n))

    print(n, f)
    print(s)


if __name__ == "__main__":
    main()
