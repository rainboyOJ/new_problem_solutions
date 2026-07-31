#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    alphabet = "abc"
    n = random.randint(1, 5)
    length = random.randint(1, 8)
    words = set()
    while len(words) < n:
        words.add("".join(random.choice(alphabet) for _ in range(random.randint(1, 4))))
    print(n, length)
    for word in words:
        print(word)


if __name__ == "__main__":
    main()
