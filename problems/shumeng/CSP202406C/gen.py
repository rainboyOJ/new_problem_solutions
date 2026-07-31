#!/usr/bin/env python3
import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))
    n = random.randint(1, 8)
    words = []
    letters = set()
    total_occurrences = 0
    for _ in range(n):
        length = random.randint(1, 8)
        word = "".join(random.choice("abcde") for _ in range(length))
        words.append((word, random.randint(1, 20)))
        letters.update(word)
        total_occurrences += length
    maximum_merges = max(0, total_occurrences - n)
    extra = random.randint(0, min(10, maximum_merges))
    vocabulary_size = len(letters) + extra
    print(n, vocabulary_size)
    for word, frequency in words:
        print(word, frequency)


if __name__ == "__main__":
    main()
