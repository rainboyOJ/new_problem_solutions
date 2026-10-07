#!/usr/bin/env python3
import random


VALID = [
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
    "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen", "twenty",
    "a", "both", "another", "first", "second", "third"
]

NOISE = [
    "Obama", "is", "Black", "hello", "world", "snowden", "code", "plane"
]


def main():
    random.seed()
    words = []
    for _ in range(6):
        if random.randint(1, 3) == 1:
            words.append(random.choice(VALID))
        else:
            words.append(random.choice(NOISE))
    words.append(".")
    print(" ".join(words))


if __name__ == "__main__":
    main()
