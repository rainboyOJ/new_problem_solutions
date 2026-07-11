#!/usr/bin/env python3
import random
import string


def main():
    random.seed()
    n = random.randint(1, 30)
    k = random.randint(1, 20)

    words = []
    for _ in range(n):
        length = random.randint(1, min(15, k))
        word = "".join(random.choice(string.ascii_letters) for _ in range(length))
        words.append(word)

    print(n, k)
    print(" ".join(words))


if __name__ == "__main__":
    main()
