#!/usr/bin/env python3
import random
import string


def main():
    random.seed()
    alphabet = "ABCDEF"
    n = random.randint(1, 10)
    blocks = []
    for _ in range(4):
        blocks.append("".join(random.choice(alphabet) for _ in range(6)))

    print(n)
    for block in blocks:
        print(block)

    for _ in range(n):
        length = random.randint(1, 4)
        word = "".join(random.choice(alphabet) for _ in range(length))
        print(word)


if __name__ == "__main__":
    main()
