#!/usr/bin/env python3
import random


def rand_word():
    length = random.randint(1, 5)
    alpha = "abc"
    return "".join(random.choice(alpha) for _ in range(length))


def main():
    random.seed()
    n = random.randint(1, 7)
    print(n)
    words = [rand_word() for _ in range(n)]
    for s in words:
        print(s)
    print(random.choice("abc"))


if __name__ == "__main__":
    main()
