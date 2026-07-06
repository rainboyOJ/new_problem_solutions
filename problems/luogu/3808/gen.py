#!/usr/bin/env python3
import random


def main():
    random.seed()
    alphabet = "abc"
    n = random.randint(1, 12)
    print(n)
    for _ in range(n):
        length = random.randint(1, 5)
        print("".join(random.choice(alphabet) for _ in range(length)))
    text_len = random.randint(1, 25)
    print("".join(random.choice(alphabet) for _ in range(text_len)))


if __name__ == "__main__":
    main()
