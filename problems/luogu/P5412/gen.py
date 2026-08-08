#!/usr/bin/env python3
import random


def rand_height():
    return random.randint(1000, 2000)


def format_height(x):
    return f"{x // 10}.{x % 10}"


def main():
    random.seed()
    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n = random.randint(1, 20)
        print(n)
        genders = [str(random.randint(0, 1)) for _ in range(n)]
        heights = [format_height(rand_height()) for _ in range(n)]
        print(" ".join(genders))
        print(" ".join(heights))


if __name__ == "__main__":
    main()
